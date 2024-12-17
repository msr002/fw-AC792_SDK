#include "system/includes.h"
#include "action.h"
#include "app_config.h"
#include "storage_device.h"
#include "generic/log.h"
#include "event/key_event.h"
#include "lcd_config.h"
#include "net_event.h"

#include "server/video_dec_server.h"
#include "server/audio_server.h"
#include "server/ctp_server.h"
#include "server/rt_stream_pkg.h"
#include "wifi/wifi_connect.h"
#include "sock_api/sock_api.h"
#include "system/includes.h"
#include "lwip/sockets.h"
#include "json_c/json.h"
#include "json_c/json_tokener.h"
#include "http/http_cli.h"
#include "udp_multicast.h"
#include "pairing_data_model.h"
#include "arp_static_table.h"
#include "baby_monitor.h"

#define TWO_WAY_AUDIO_ENABLE 1          //双向语音对讲使能

#define CTP_CMD_PORT            3333    //CTP命令端口
#define RT_RECV_PORT            2224    //图传接收数据端口
#define RT_SEND_PORT            9981    //图传(音频)发送数据端口
#define FILE_THUMB_PORT         2226    //缩略图数据端口
#define FILE_RT_PORT            2223    //视频数据端口
#define HTTP_PORT               8080    //HTTP解析vs_list.txt端口

#define VIDEO_DEC_BUF_MAX_SIZE       512    //解码服务缓存,单位Kb,申请大小不能小于一帧图像的大小

#define CTP_RECV_BUF_MAX_LEN         200 * 1024 //UDP接收缓存,用于接收CTP包
#define PARSE_BUF_MAX_LEN            200 * 1024 //解析CTP包缓存

#define SEND_BUF_MAX_LEN             2 * 1024   //UDP发送缓存,用于BBM_RX发送音频包
#define AUDIO_DEC_BUF_MAX_LEN        2 * 1024   //解码音频缓存
#define AUDIO_ENC_BUF_MAX_LEN        2 * 1024   //编码音频缓存

#define RECV_TIMEOUT                300      //UDP socket recv超时时间设置

#define AUDIO_ENC_FRAME_SIZE    640     //每个音频包的大小，越大会导致延迟高

#define MAX_PAIR_NUM    MAX_ARP_STATIC_ENTRY    //最大配对数量
#define MIN_PAIR_CH     0                       //0
#define MAX_PAIR_CH     (MAX_PAIR_NUM - 1)      //6
#define INVALID_CH_NUM  99

#define CTP_FILE_THUMB_TASK_NAME        "thread_socket_thumb"

enum {
    BBM_MSG_CONNECT = 1,
    BBM_MSG_DISCONNECT,
    BBM_MSG_RECONNECT,
    BBM_MSG_START_RT,
    BBM_MSG_STOP_RT,
};

enum {
    BBM_TX_OFFLINE = 0,
    BBM_TX_ONLINE  = 1,
};

enum {
    BBM_RT_STREAM_STOP = 0,
    BBM_RT_STREAM_START  = 1,
};

//todo
//没头文件?
struct ctp_hdl {
    struct list_head entry;
    int id;
    int recv_thread_pid;
    void *sock_hdl;
    struct sockaddr_in dest_addr;
    int (*cb_func)(void *hdl, enum ctp_cli_msg_type type, const char *topic, const char *content, void *priv);
    void *priv;
    char *topic;
    unsigned int timeout;
    unsigned int timehdl;
    unsigned int timecheck;
    unsigned int timecheckout;
};



struct wifi_bbm_hdl {
    int ctp_recv_pid;
    int ctp_send_pid;
    int ctp_thumb_pid;
    int pairing_task_pid;
    int ctp_file_rt_pid;

    u8 ctp_recv_exit;
    u8 ctp_send_exit;
    u8 ctp_thumb_exit;
    u8 pairing_task_exit;
    u8 ctp_file_rt_exit;

    void *ctp_recv_sockfd;
    void *ctp_send_sockfd;
    void *ctp_thumb_sockfd;
    void *ctp_file_rt_sockfd;

    struct ctp_hdl *ctp_cli_hdl;
    struct server *video_dec_server;
    struct server *audio_dec_server;
    struct server *audio_enc_server;


    u32 old_frame_seq;

    //audio_dec
    u8 *audio_dec_buf;
    cbuffer_t audio_dec_save_cbuf;

    //audio_enc
    OS_SEM audio_enc_sem;
    u8 *audio_enc_buf;
    cbuffer_t audio_enc_save_cbuf;

    OS_SEM ctp_msg_sem;

    //file browser
    char vf_list[100];

    char **file_list;
    u16  file_total_num;

    //todo
    char dest_ip_addr[20];
    u8 dest_mac[6];
    u8 cur_channel;
    u8 online_table[MAX_PAIR_NUM];
    u32 online_cnt_table[MAX_PAIR_NUM];
    u32 online_timeout[MAX_PAIR_NUM];

    u8 rt_stream_state;
};
static struct wifi_bbm_hdl bbm_hdl;

#define __this (&bbm_hdl)


static int bbm_switch_camera(void);

static int vfs_audio_dec_fread(void *file, void *data, u32 len)
{
    u32 rlen = 0;

    do {
        rlen = cbuf_read(&__this->audio_dec_save_cbuf, data, len);
        if (rlen == len) {
            break;
        }
    } while (rlen);

    return len;
}

static int vfs_audio_dec_fclose(void *file)
{
    return 0;
}

static int vfs_audio_dec_flen(void *file)
{
    return 0;
}

static const struct audio_vfs_ops vfs_audio_dec_ops = {
    .fwrite = NULL,
    .fread  = vfs_audio_dec_fread,
    .fclose = vfs_audio_dec_fclose,
    .flen   = vfs_audio_dec_flen,
};

//编码器输出PCM数据
static int vfs_audio_enc_fwrite(void *file, void *data, u32 len)
{
    cbuffer_t *cbuf = (cbuffer_t *)file;
    if (0 == cbuf_write(cbuf, data, len)) {
        //上层buf写不进去时清空一下，避免出现声音滞后的情况
        cbuf_clear(cbuf);
    }
    os_sem_set(&__this->audio_enc_sem, 0);
    os_sem_post(&__this->audio_enc_sem);

    //此回调返回0录音就会自动停止
    return len;
}

static int vfs_audio_enc_fread(void *file, void *data, u32 len)
{
    cbuffer_t *cbuf = (cbuffer_t *)file;
    u32 rlen;

    do {
        //此处等待信号量是为了防止解码器因为读不到数而一直空转
        os_sem_pend(&__this->audio_enc_sem, 0);

        rlen = cbuf_get_data_size(cbuf);
        rlen = rlen > len ? len : rlen;
        if (cbuf_read(cbuf, data, rlen) > 0) {
            len = rlen;
            break;
        }

    } while (rlen);

    //返回成功读取的字节数
    return len;
}

static int vfs_audio_enc_fclose(void *file)
{
    return 0;
}

static int vfs_audio_enc_flen(void *file)
{
    return 0;
}

static const struct audio_vfs_ops vfs_audio_enc_ops = {
    .fwrite = vfs_audio_enc_fwrite,
    .fread  = vfs_audio_enc_fread,
    .fclose = vfs_audio_enc_fclose,
    .flen   = vfs_audio_enc_flen,
};



static int audio_dec_init(void)
{
    union audio_req req = {0};
    int err;

    __this->audio_dec_server = server_open("audio_server", "dec");
    if (!__this->audio_dec_server) {
        printf("open audio_dec_server fail");
        goto __err;
    }

    __this->audio_dec_buf = (u8 *)malloc(AUDIO_DEC_BUF_MAX_LEN);
    if (__this->audio_dec_buf == NULL) {
        printf("audio_dec_buf malloc fail");
        goto __err;

    }
    cbuf_init(&__this->audio_dec_save_cbuf, __this->audio_dec_buf, AUDIO_DEC_BUF_MAX_LEN);

    req.dec.cmd             = AUDIO_DEC_OPEN;
    req.dec.volume          = 100;
    req.dec.output_buf      = NULL;
    req.dec.output_buf_len  = 4096;
    req.dec.channel         = 1;
    req.dec.sample_rate     = 8000;
    req.dec.priority        = 1;
    req.dec.vfs_ops         = &vfs_audio_dec_ops;
    req.dec.dec_type 		= "pcm";
    req.dec.sample_source   = "dac";

    err = server_request(__this->audio_dec_server, AUDIO_REQ_DEC, &req);
    if (err) {
        printf("audio server req open err\n");
        goto __err;
    }

    req.dec.cmd = AUDIO_DEC_START;
    err = server_request(__this->audio_dec_server, AUDIO_REQ_DEC, &req);
    if (err) {
        printf("audio server req start err\n");
        goto __err;
    }

    return 0;

__err:
    if (__this->audio_dec_server) {
        server_close(__this->audio_dec_server);
        __this->audio_dec_server = NULL;
    }
    if (__this->audio_dec_buf) {
        free(__this->audio_dec_buf);
        __this->audio_dec_buf = NULL;
    }

    audio_dec_exit();
    return -1;
}


static int audio_dec_exit(void)
{
    union audio_req req = {0};

    if (__this->audio_dec_server) {
        req.dec.cmd = AUDIO_DEC_STOP;
        server_request(__this->audio_dec_server, AUDIO_REQ_DEC, &req);

        server_close(__this->audio_dec_server);
        __this->audio_dec_server = NULL;
    }
    if (__this->audio_dec_buf) {
        free(__this->audio_dec_buf);
        __this->audio_dec_buf = NULL;
    }

    return 0;
}

static int audio_dec_write_cbuf(u8 *buf, u32 size)
{
    u32 cur_size;
    cur_size =  cbuf_get_data_size(&__this->audio_dec_save_cbuf);

    if (cur_size + size >= AUDIO_DEC_BUF_MAX_LEN) {
        cbuf_clear(&__this->audio_dec_save_cbuf);
    }

    cbuf_write(&__this->audio_dec_save_cbuf, buf, size);

    return 0;
}

static int audio_dec_one_frame(u8 *buf, u32 size)
{
    audio_dec_write_cbuf(buf, size);

    return 0;
}

static int audio_enc_init(void)
{
    union audio_req req = {0};
    int err;

    os_sem_create(&__this->audio_enc_sem, 0);

    __this->audio_enc_server = server_open("audio_server", "enc");
    if (!__this->audio_enc_server) {
        printf("open audio_enc_server fail");
        goto __err;
    }

    __this->audio_enc_buf = (u8 *)malloc(AUDIO_ENC_BUF_MAX_LEN);
    if (__this->audio_enc_buf == NULL) {
        printf("audio_enc_buf malloc fail");
        goto __err;

    }
    cbuf_init(&__this->audio_enc_save_cbuf, __this->audio_enc_buf, AUDIO_ENC_BUF_MAX_LEN);

    req.enc.frame_size = AUDIO_ENC_FRAME_SIZE;
    req.enc.output_buf_len = req.enc.frame_size * 3; //底层缓冲buf至少设成3倍frame_size
    req.enc.cmd = AUDIO_ENC_OPEN;
    req.enc.channel = 1;
    req.enc.volume =  100;
    req.enc.sample_rate = 8000;
    req.enc.format = "pcm";
    req.enc.sample_source = "mic";
    req.enc.vfs_ops = &vfs_audio_enc_ops;
    req.enc.file = (FILE *)&__this->audio_enc_save_cbuf;

    err = server_request(__this->audio_enc_server, AUDIO_REQ_ENC, &req);
    if (err) {
        goto __err;
    }

    return 0;

__err:
    if (__this->audio_enc_server) {
        server_close(__this->audio_enc_server);
        __this->audio_enc_server = NULL;
    }
    if (__this->audio_enc_buf) {
        free(__this->audio_enc_buf);
        __this->audio_enc_buf = NULL;
    }
    return -1;
}

static int audio_enc_exit(void)
{
    union audio_req req = {0};

    if (__this->audio_enc_server) {
        req.enc.cmd = AUDIO_ENC_CLOSE;
        server_request(__this->audio_enc_server, AUDIO_REQ_ENC, &req);

        server_close(__this->audio_enc_server);
        __this->audio_enc_server = NULL;
    }
    if (__this->audio_enc_buf) {
        free(__this->audio_enc_buf);
        __this->audio_enc_buf = NULL;
    }

    os_sem_del(&__this->audio_enc_sem, OS_DEL_ALWAYS);

    return 0;
}

static int video_dec_init(void)
{
    struct video_dec_arg arg = {0};
    arg.dev_name = "video_dec";
    arg.video_buf_size = VIDEO_DEC_BUF_MAX_SIZE;

    __this->video_dec_server = server_open("video_dec_server", &arg);
    if (!__this->video_dec_server) {
        printf("open video_dec_server fail");
        return -EFAULT;
    }

    return 0;
}

static int video_dec_exit(void)
{
    union video_dec_req dec_req = {0};

    if (__this->video_dec_server) {
        server_request(__this->video_dec_server, VIDEO_REQ_DEC_STOP, &dec_req);

        server_close(__this->video_dec_server);
        __this->video_dec_server = NULL;
    }

    return 0;
}


static int video_dec_one_frame(u8 *buf, u32 size)
{
    if (!__this->video_dec_server) {
        printf("please open video_dec server first\n");
        return -EFAULT;
    }

    char fb_name[4];
    union video_dec_req dec_req = {0};

    sprintf(fb_name, "fb%d", 2);
    dec_req.dec.fb = fb_name;
    dec_req.dec.left = 0;
    dec_req.dec.top = 0;
    dec_req.dec.width = LCD_W;
    dec_req.dec.height = LCD_H;

    dec_req.dec.pctl = NULL;
    dec_req.dec.preview = 1;

    dec_req.dec.image.buf = buf;
    dec_req.dec.image.size = size;

    return server_request(__this->video_dec_server, VIDEO_REQ_DEC_IMAGE, &dec_req);
}

static int parse_recv_packet(u8 *recv_buf, u32 recv_len, u8 *data_buf, u32 *data_len)
{
    static u32 total_payload_len = 0;

    u32 position = 0;
    struct frm_head  *head_info;
    u32 frame_head_size = sizeof(struct frm_head);

    if (recv_len < frame_head_size) {
        printf(" recv_recv_len err\n");
        return 0;
    }

    do {
        head_info = (struct frm_head *)(recv_buf + position);

        if ((head_info->type & JPEG_TYPE_VIDEO) || (head_info->type & PCM_TYPE_AUDIO)) {
            if (head_info->frm_sz > PARSE_BUF_MAX_LEN) {
                printf("jpeg frame size too large :%d \n", head_info->frm_sz);
                return 0;
            }
            recv_len = recv_len - (frame_head_size + head_info->payload_size);
            if (recv_len < 0) {
                printf("remain recv_len err:%d \n", recv_len);
                return 0;
            }

            //如果当前的seq小于旧的seq,说明是旧的数据包,跳过不处理
            if (head_info->seq < __this->old_frame_seq) {
                goto continue_deal;
            }
            //如果当前seq大于旧的seq,认为是新的数据包,组包重新初始
            if (head_info->seq > __this->old_frame_seq) {
                __this->old_frame_seq = head_info->seq;
                total_payload_len = 0;
            }

            memcpy(data_buf + head_info->offset, (recv_buf + position) + frame_head_size,
                   head_info->payload_size);

            total_payload_len += head_info->payload_size;
            if (total_payload_len == head_info->frm_sz) {
                *data_len = total_payload_len;
                total_payload_len = 0;

                //接收到完整一帧
                return head_info->type;
            }
        } else {
            printf("recv type err:%d \n", head_info->type);
            return 0;
        }

continue_deal:
        position += (frame_head_size + head_info->payload_size);

    } while (recv_len > 0);

    return 0;
}

static void net_ctp_recv_task(void)
{
    int ret;
    int recv_len = 0;
    u32 data_size;
    u32 time = 0;
    int fps_cnt = 0;

    //网络包接收缓存
    u32 recv_buf_len = CTP_RECV_BUF_MAX_LEN;
    u8 *recv_buf = malloc(recv_buf_len);
    if (!recv_buf) {
        printf("ctp recv malloc recv buff err \n");
        goto exit;
    }

    //解析jpeg/pcm网络包缓存
    u8 *data_buf = malloc(PARSE_BUF_MAX_LEN);
    if (!data_buf) {
        printf("ctp recv malloc data buf err \n");
        goto exit;
    }

    //视频解码服务
    ret = video_dec_init();
    if (ret) {
        printf("video_dec_init err");
        goto exit;
    }

    //音频解码服务
    ret = audio_dec_init();
    if (ret) {
        printf("audio_dec_init err");
        goto exit;
    }

    //设置接收最大超时时间
    sock_set_recv_timeout(__this->ctp_recv_sockfd, RECV_TIMEOUT);

    //重置接收包序列
    __this->old_frame_seq = 0;

    while (1) {
        if (__this->ctp_recv_exit) {
            break;
        }

        recv_len = sock_recvfrom(__this->ctp_recv_sockfd, recv_buf, recv_buf_len, 0, NULL, NULL);

        if (recv_len <= 0) {
            printf("recv err \n");
            continue;
        }

        /* putchar('p'); */
        ret = parse_recv_packet(recv_buf, recv_len, data_buf, &data_size);

        if (ret & JPEG_TYPE_VIDEO) {
            if ((timer_get_ms() - time > 1000)) {
                time = timer_get_ms();
                printf("bbm video fps:%d\n", fps_cnt);
                fps_cnt = 0;
            }
            fps_cnt++;
            putchar('v');
            video_dec_one_frame(data_buf + 8, data_size - 8);
        } else if (ret & PCM_TYPE_AUDIO) {
            putchar('a');
            audio_dec_one_frame(data_buf, data_size);
        } else {
            /* putchar('e'); */
        }

    }

exit:
    if (recv_buf) {
        free(recv_buf);
    }
    if (data_buf) {
        free(data_buf);
    }
    if (__this->video_dec_server) {
        video_dec_exit();
    }
    if (__this->audio_dec_server) {
        audio_dec_exit();
    }
}

#if 0
static int parse_thumb_packet(u8 *recv_buf, int recv_len, u8 *data_buf, u32 *data_len)
{
    static u8 jpeg_flag = 0;
    static u32 jpeg_recv_size = 0;
    static u32 jpeg_total_size = 0;
    u32 offset = 0;

continue_parse:
    struct frm_head *frame_head = (struct frm_head *)(recv_buf + offset);

    switch (frame_head->type) {
    case MEDIA_INFO_TYPE:
        struct media_info *media = (struct media_info *)(recv_buf + sizeof(struct frm_head));
        //log
        printf("media w:%d h:%d fps:%d audio_rate:%d dur_time:%d fname:%s \n"
               , media->length, media->height, media->fps
               , media->audio_rate, media->dur_time, media->filename);

        if (recv_len > (offset + frame_head->frm_sz + 2 * sizeof(struct frm_head))) {
            //还有多的 frame_head
            offset += sizeof(struct frame_head) + frame_head->frm_sz;
            goto continue_parse;
        }
        break;
    case DATE_TIME_TYPE:
        //时间包,暂时不处理
        printf("date time\n");
        if (recv_len > (offset + frame_head->frm_sz + 2 * sizeof(struct frm_head))) {
            //还有多的 frame_head
            offset += sizeof(struct frame_head) + frame_head->frm_sz;
            goto continue_parse;
        }
        break;
    case PREVIEW_TYPE:
        //jpeg包
        u32 jpeg_size = frame_head->frm_sz;
        printf("jpeg_size :%d \n", jpeg_size);
        if (!jpeg_flag) {
            jpeg_flag = 1;
            u8 *data = (u8 *)frame_head + sizeof(struct frm_head);
            put_buf(data, 16);

            u32 payload_size = recv_len - offset - sizeof(struct frm_head);
            memcpy(data_buf +, data, payload_size);

            jpeg_recv_size += payload_size;
        } else {


            jpeg_recv_size += payload_size;
        }
    }
}
#endif

static void ctp_thumb_recv(struct net_ctp_thumb *thumb_data)
{
    int recv_len = 0;
    int timeout_cnt = 0;
    int file_cnt = 0;
    // 网络包接收缓存
    u8 *recv_buf = malloc(CTP_RECV_BUF_MAX_LEN);
    if (!recv_buf) {
        printf("ctp recv malloc recv buff err \n");
        goto exit;
    }

    u32 frame_head_size = sizeof(struct frm_head);
    sock_set_recv_timeout(__this->ctp_thumb_sockfd, 200);

    while (1) {
        recv_len = sock_recvfrom(__this->ctp_thumb_sockfd, recv_buf, frame_head_size, MSG_WAITALL, NULL, NULL);
        if (recv_len != frame_head_size) {
            printf("recv frame_head err \n");
            if (++timeout_cnt > 2) {
                break;
            }
            continue;
        }

        struct frm_head *frame_head = (struct frm_head *)recv_buf;

        switch (frame_head->type) {
        case MEDIA_INFO_TYPE:
            /* printf("media info type\n"); */
            recv_len = sock_recvfrom(__this->ctp_thumb_sockfd, recv_buf, frame_head->frm_sz, MSG_WAITALL, NULL, NULL);
            /* struct media_info *media = (struct media_info *)recv_buf; */
            /*             printf("media info w:%d h:%d fps:%d audio_rate:%d dur_time:%d fname:%s \n" */
            /* , media->length, media->height, media->fps */
            /* , media->audio_rate, media->dur_time, media->filename); */
            break;
        case DATE_TIME_TYPE:
            /* printf("time type\n"); */
            recv_len = sock_recvfrom(__this->ctp_thumb_sockfd, recv_buf, frame_head->frm_sz, MSG_WAITALL, NULL, NULL);
            /* int time; */
            /* memcpy(&time, recv_buf, 4); */
            /* printf("time:%d \n", time); */
            break;
        case PREVIEW_TYPE:
            printf("recv thumb cnt:%d \n", file_cnt);
            recv_len = sock_recvfrom(__this->ctp_thumb_sockfd, recv_buf, frame_head->frm_sz, MSG_WAITALL, NULL, NULL);
            if (recv_len < 0) {
                printf("recv frm err recv_len:%d\n", recv_len);
                recv_len = 0;
            }
            thumb_data->file_buf_len_list[file_cnt] = recv_len;
            memcpy(thumb_data->file_buf_list[file_cnt], recv_buf, recv_len);
            file_cnt++;
            if (file_cnt == thumb_data->file_num) {
                printf("recv thumb done\n");
                goto exit;
            }
            break;
        default:
            printf("default frame type \n");
            recv_len = sock_recvfrom(__this->ctp_thumb_sockfd, recv_buf, frame_head->frm_sz, MSG_WAITALL, NULL, NULL);
            break;
        }

    }
exit:
    os_sem_post(&thumb_data->sem);

    if (recv_buf) {
        free(recv_buf);
    }

}

static void ctp_thumb_task(void)
{
    int ret = 0;
    int i;
    int msg[8];
    struct net_ctp_thumb *thumb_data;

    char topic_1[] = "MULTI_COVER_FIGURE";
    char content_1[512];
    char temp_buf[128];

    while (1) {
        if (__this->ctp_thumb_exit) {
            printf("ctp thumb task exit\n");
            break;
        }

        ret = os_task_pend("taskq", msg, ARRAY_SIZE(msg));
        switch (ret) {
        case OS_TASKQ:
            switch (msg[0]) {
            case Q_MSG:
                thumb_data = (struct net_ctp_thumb *)msg[1];
                break;
            case Q_USER:
                continue;
                break;
            }
            break;
        default:
            break;
        }


        memset(content_1, 0x00, sizeof(content_1));
        strcat(content_1, "{\"op\":\"PUT\",\"param\":{");
        for (i = 0; i <  thumb_data->file_num; i++) {

            sprintf(temp_buf, "\"path_%d\":\"%s\",", i, __this->file_list[thumb_data->start_index + i]);
            strcat(content_1, temp_buf);
        }
        //去除,
        char *ptr = strrchr(content_1, ',');
        *ptr = '\0';
        strcat(content_1, "}}");
        printf("content: %s\n", content_1);

        /* sprintf(content_1, "{\"op\":\"PUT\",\"param\":{\"path_0\":\"%s\"}}", __this->file_list[file_index]); */
        ret = ctp_cli_send(__this->ctp_cli_hdl, topic_1, content_1);

        struct sockaddr_in dest;
        //tcp
        __this->ctp_thumb_sockfd = sock_reg(AF_INET, SOCK_STREAM, 0, NULL, NULL);
        if (__this->ctp_thumb_sockfd == NULL) {
            printf("sock_reg err\n");
            break;
        }
        dest.sin_family = AF_INET;
        dest.sin_addr.s_addr = inet_addr(__this->dest_ip_addr);
        dest.sin_port = htons(FILE_THUMB_PORT);
        if (0 != sock_connect(__this->ctp_thumb_sockfd, (struct sockaddr *)&dest, sizeof(struct sockaddr_in))) {
            printf("sock_connect fail.\n");
            break;
        }

        ctp_thumb_recv(thumb_data);

        sock_unreg(__this->ctp_thumb_sockfd);
        __this->ctp_thumb_sockfd = NULL;
    }

}

static void ctp_file_rt_task(void)
{
    int ret = 0;
    int recv_len = 0;
    u32 data_size;
    int msg[8];
    u8 end_flag = 0;

    //todo
    char topic_1[] = {"TIME_AXIS_PLAY"};
    char content_1[100];
    char file_name[100];
    u8 cnt = 3;
    u32 frame_head_size =  sizeof(struct frm_head);

    //网络包接收缓存
    u32 recv_buf_len = CTP_RECV_BUF_MAX_LEN;
    u8 *recv_buf = malloc(recv_buf_len);
    if (!recv_buf) {
        printf("ctp recv malloc recv buff err \n");
        goto exit;
    }

    //解析jpeg/pcm网络包缓存
    u8 *data_buf = malloc(PARSE_BUF_MAX_LEN);
    if (!data_buf) {
        printf("ctp recv malloc data buf err \n");
        goto exit;
    }

    //视频解码服务
    ret = video_dec_init();
    if (ret) {
        printf("video_dec_init err");
        goto exit;
    }

    //音频解码服务
    ret = audio_dec_init();
    if (ret) {
        printf("audio_dec_init err");
        goto exit;
    }


    sock_set_recv_timeout(__this->ctp_file_rt_sockfd, RECV_TIMEOUT);


    while (1) {
        if (__this->ctp_file_rt_exit) {
            break;
        }
        if (!end_flag) {
            if (os_taskq_accept(ARRAY_SIZE(msg), msg) != OS_TASKQ) {
                continue;
            }

            switch (msg[0]) {
            case Q_MSG:
                char *full_name = (char *)msg[1];
                int img_index = msg[2];
                int update_num = msg[3];

                snprintf(file_name, sizeof(file_name), "%s", full_name);
                printf("file_rt_file_name =%s\n", file_name);
                //todo 暂时写死时间是60s
                int offset = 60;
                sprintf(content_1, "{\"op\":\"PUT\",\"param\":{\"path\":\"%s\",\"offset\":%d}}", file_name, offset);
                ret = ctp_cli_send(__this->ctp_cli_hdl, topic_1, content_1);
                end_flag = 1;
                if (ret) {
                    printf("ctp_cli_send :%s err\n", topic_1);
                    return;
                }
                break;
            default:
                break;

            }

            if (file_name[0] == '\0') {
                continue;
            }
        }

        recv_len = sock_recvfrom(__this->ctp_file_rt_sockfd, recv_buf, frame_head_size, MSG_WAITALL, NULL, NULL);

        if (recv_len <= 0) {
            printf("recv err \n");
            end_flag = 0;
            memset(file_name, 0, sizeof(file_name));

            continue;
        }

        struct frm_head *frame_head = (struct frm_head *)recv_buf;

        switch (frame_head->type) {
        case MEDIA_INFO_TYPE:
            recv_len = sock_recvfrom(__this->ctp_file_rt_sockfd, recv_buf, frame_head->frm_sz, MSG_WAITALL, NULL, NULL);
            struct media_info *media = (struct media_info *)recv_buf;
            printf("media info w:%d h:%d fps:%d audio_rate:%d dur_time:%d fname:%s \n"
                   , media->length, media->height, media->fps
                   , media->audio_rate, media->dur_time, media->filename);
            break;

        case DATE_TIME_TYPE:
            recv_len = sock_recvfrom(__this->ctp_file_rt_sockfd, recv_buf, frame_head->frm_sz, MSG_WAITALL, NULL, NULL);
            int time;
            memcpy(&time, recv_buf, 4);
            printf("time:%d \n", time);
            break;

        case JPEG_TYPE_VIDEO:
            putchar('v');
            recv_len = sock_recvfrom(__this->ctp_file_rt_sockfd, recv_buf, frame_head->frm_sz, MSG_WAITALL, NULL, NULL);
            if (recv_len < 1024) {
                printf("recv video len err =%d\n", recv_len);
                end_flag = 0;
                memset(file_name, 0, sizeof(file_name));
                break;
            }
            video_dec_one_frame(recv_buf, recv_len);
            break;
        case  PCM_TYPE_AUDIO:
            putchar('a');
            recv_len = sock_recvfrom(__this->ctp_file_rt_sockfd, recv_buf, frame_head->frm_sz, MSG_WAITALL, NULL, NULL);
            if (recv_len < 0) {
                printf("recv audio len err =%d\n", recv_len);
                end_flag = 0;
                memset(file_name, 0, sizeof(file_name));
                break;
            }

            audio_dec_one_frame(recv_buf, recv_len);
            break;
        case PLAY_OVER_TYPE:
            end_flag = 0;
            memset(file_name, 0, sizeof(file_name));
            break;

        default:
            break;
        }

    }

exit:
    if (recv_buf) {
        free(recv_buf);
    }
    if (data_buf) {
        free(data_buf);
    }
    if (__this->video_dec_server) {
        video_dec_exit();
    }
    if (__this->audio_dec_server) {
        audio_dec_exit();
    }

}

static void net_ctp_send_task(void)
{
    int ret;
    int data_size;
    u8 *data_buf  = NULL;

    data_buf = malloc(SEND_BUF_MAX_LEN);
    if (!data_buf) {
        printf("ctp send malloc data buf err \n");
        goto exit;
    }
    ret = audio_enc_init();
    if (ret) {
        printf("audio_enc_init err");
        goto exit;
    }

    struct sockaddr_in dest_addr;
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_addr.s_addr = inet_addr(__this->dest_ip_addr);
    dest_addr.sin_port = htons(RT_SEND_PORT);

    while (1) {
        if (__this->ctp_send_exit) {
            break;
        }

        data_size = vfs_audio_enc_fread(&__this->audio_enc_save_cbuf, data_buf, AUDIO_ENC_FRAME_SIZE);
        if (!data_size) {
            printf("read audio enc data err \n");
            continue;
        }

        ret = sock_sendto(__this->ctp_send_sockfd, data_buf, data_size, 0, &dest_addr, sizeof(dest_addr));
        if (ret < 0) {
            printf("sock send err\n");
            continue;
        }
    }

exit:
    if (data_buf) {
        free(data_buf);
    }
    if (__this->audio_dec_server) {
        audio_enc_exit();
    }
}

static const char *json_parse_to_path(const char *parm_list)
{
    const char *tmp_value;
    json_object *new_obj = NULL;
    json_object *parm = NULL;
    json_object *tmp = NULL;
    new_obj = json_tokener_parse(parm_list);
    parm =  json_object_object_get(new_obj, "param");
    tmp =  json_object_object_get(parm, "path");
    if (tmp == NULL) {
        printf("err no path object \n");
        return NULL;
    }
    tmp_value = json_object_get_string(tmp);
    return tmp_value;
}

static int net_ctp_recv_callback(void *hdl, enum ctp_cli_msg_type type, const char *topic, const char *parm_list, void *priv)
{
    //ctp回复消息处理
    if (type == CTP_CLI_RECV_MSG) {
        if (strstr(topic, "FORWARD_MEDIA_FILES_LIST")) {
            const char *path = json_parse_to_path(parm_list);
            if (path) {
                strcpy(__this->vf_list, path);
            }
            os_sem_post(&__this->ctp_msg_sem);
        } else if (strstr(topic, "APP_ACCESS")) {
            os_sem_post(&__this->ctp_msg_sem);
        } else {
            /* printf("This msg not deal:topic:%s content:%s\n", topic, parm_list); */
        }
    }

    return 0;
}

static int ctp_rt_recv_init(void)
{
    printf("-----ctp_rt_recv_init----\n");
    int ret;
    struct sockaddr_in conn_addr;
    conn_addr.sin_family = AF_INET;
    conn_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    conn_addr.sin_port = htons(RT_RECV_PORT);

    __this->ctp_recv_sockfd = sock_reg(AF_INET, SOCK_DGRAM, 0, NULL, NULL);
    if (__this->ctp_recv_sockfd == NULL) {
        printf("sock_reg err\n");
        return -1;
    }

    ret = sock_set_reuseaddr(__this->ctp_recv_sockfd);
    if (ret) {
        printf("sock_set_reuseaddr err:%d\n", ret);
        goto err;
    }

    ret = sock_bind(__this->ctp_recv_sockfd, (struct sockaddr *)&conn_addr, sizeof(struct sockaddr));
    if (ret) {
        printf("sock_bind err:%d\n", ret);
        goto err;
    }

    thread_fork("thread_socket_recv", 25, 2048, 2048, &__this->ctp_recv_pid, net_ctp_recv_task, NULL);

    return 0;

err:
    if (__this->ctp_recv_sockfd) {
        sock_unreg(__this->ctp_recv_sockfd);
        __this->ctp_recv_sockfd = NULL;
    }
    return -1;
}

static int ctp_rt_recv_exit(void)
{
    printf("-----ctp_rt_recv_exit----\n");
    //kill thread
    if (__this->ctp_recv_pid) {
        __this->ctp_recv_exit = 1;
        thread_kill(&__this->ctp_recv_pid, KILL_WAIT);
        __this->ctp_recv_exit = 0;
        __this->ctp_recv_pid = 0;
    }

    //free socket
    if (__this->ctp_recv_sockfd) {
        sock_unreg(__this->ctp_recv_sockfd);
        __this->ctp_recv_sockfd = NULL;
    }

    printf("-----ctp_rt_recv_exit done----\n");

    return 0;
}

static int ctp_rt_send_init(void)
{
    printf("-----ctp_rt_send_init----\n");
    int ret;
    struct sockaddr_in conn_addr;
    conn_addr.sin_family = AF_INET;
    conn_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    conn_addr.sin_port = htons(RT_SEND_PORT);

    __this->ctp_send_sockfd = sock_reg(AF_INET, SOCK_DGRAM, 0, NULL, NULL);
    if (__this->ctp_send_sockfd == NULL) {
        printf("sock_reg err\n");
        goto err;
    }

    ret = sock_set_reuseaddr(__this->ctp_send_sockfd);
    if (ret) {
        printf("sock_set_reuseaddr err:%d\n", ret);
        goto err;
    }

    thread_fork("thread_socket_send", 15, 2048, 2048, &__this->ctp_send_pid, net_ctp_send_task, NULL);

    return 0;

err:
    if (__this->ctp_send_sockfd) {
        sock_unreg(__this->ctp_send_sockfd);
        __this->ctp_send_sockfd = NULL;
    }
    return -1;
}

static int ctp_rt_send_exit(void)
{
    printf("-----ctp_rt_send_exit----\n");
    //kill thread
    if (__this->ctp_send_pid) {
        __this->ctp_send_exit = 1;
        thread_kill(&__this->ctp_send_pid, KILL_WAIT);
        __this->ctp_send_exit = 0;
        __this->ctp_send_pid = 0;
    }

    //free socket
    if (__this->ctp_send_sockfd) {
        sock_unreg(__this->ctp_send_sockfd);
        __this->ctp_send_sockfd = NULL;
    }

    printf("-----ctp_rt_send_exit done----\n");

    return 0;
}

static int net_ctp_send_access(void)
{
    int ret;
    const char topic_1[] = {"APP_ACCESS"};
    const char content_1[] = {"{\"op\":\"PUT\",\"param\":{\"type\":\"0\",\"ver\":\"20700\"}}"};

    if (!__this->ctp_cli_hdl) {
        printf("ctp client hdl invalid\n");
        return -1;
    }

    //发送access命令
    ret = ctp_cli_send(__this->ctp_cli_hdl, topic_1, content_1);
    if (ret) {
        printf("ctp_cli_send :%s err\n", topic_1);
        return ret;
    }

    ret = os_sem_pend(&__this->ctp_msg_sem, 100);
    if (ret) {
        printf("wait access timeout :%d \n", ret);
    }

    return ret;
}

static int net_ctp_client_init(void)
{
    int ret;
    struct sockaddr_in dest_addr = {0};

    os_sem_create(&__this->ctp_msg_sem, 0);

    if (__this->cur_channel < 0 || __this->cur_channel > 5) {
        printf("no pair channel \n");
        goto err;
    }

    if (!__this->ctp_cli_hdl) {
        //ctp client初始化
        ctp_cli_init();

        /* 建立CTP连接 */
        dest_addr.sin_family = AF_INET;
        dest_addr.sin_addr.s_addr = inet_addr(__this->dest_ip_addr);
        dest_addr.sin_port = htons(CTP_CMD_PORT);
        __this->ctp_cli_hdl = ctp_cli_reg(1, &dest_addr, net_ctp_recv_callback, NULL);

        if (!__this->ctp_cli_hdl) {
            printf("\n--------------CTP_CMD_cli connect failed----------------\n");
            //释放资源
            ctp_cli_uninit();
            os_sem_del(&__this->ctp_msg_sem, OS_DEL_ALWAYS);
            goto err;
        }
    }

    //连接成功开启实时流
    printf("\n-----CTP_CLI_CONNECT_SUCC -----\n");

    ret = net_ctp_rt_start();
    if (ret) {
        goto err;
    }

    return 0;

err:
    __this->cur_channel = INVALID_CH_NUM;
    return -1;
}

static int net_ctp_client_exit(void)
{
    if (__this->ctp_cli_hdl) {
        ctp_cli_unreg(__this->ctp_cli_hdl);
        __this->ctp_cli_hdl = NULL;
        ctp_cli_uninit();
        os_sem_del(&__this->ctp_msg_sem, OS_DEL_ALWAYS);
    }


    return 0;
}

static int net_ctp_rt_start(void)
{
    int ret;
    const char topic_3[] = {"OPEN_RT_STREAM"};
    const char content_3[] = {"{\"op\":\"PUT\",\"param\":{\"rate\":\"3000\",\"w\":\"640\",\"fps\":\"20\",\"h\":\"480\",\"format\":\"1\"}}"};

    ret = net_ctp_send_access();
    if (ret) {
        printf("----ctp access fail----\n");
        return -1;
    }

    printf("\n----ctp access success----\n");

    //开启实时流命令
    ret = ctp_cli_send(__this->ctp_cli_hdl, topic_3, content_3);
    if (ret) {
        printf("ctp_cli_send :%s err\n", topic_3);
        return -1;
    }

    //创建接收实时流sock、线程
    ctp_rt_recv_init();

#if TWO_WAY_AUDIO_ENABLE
    ctp_rt_send_init();
#endif

    __this->rt_stream_state = BBM_RT_STREAM_START;

    return 0;
}

static int net_ctp_rt_stop(void)
{
    int ret;
    const char topic_3[] = {"CLOSE_RT_STREAM"};
    const char content_3[] = {"{\"op\":\"PUT\",\"param\":{\"status\":\"1\"}}"};

#if TWO_WAY_AUDIO_ENABLE
    ctp_rt_send_exit();
#endif

    //关闭socket、线程
    ctp_rt_recv_exit();

    //发送停止实时流命令
    if (__this->ctp_cli_hdl) {
        ret = ctp_cli_send(__this->ctp_cli_hdl, topic_3, content_3);
        if (ret) {
            printf("ctp_cli_send :%s err\n", topic_3);
            return -1;
        }
    }

    __this->rt_stream_state = BBM_RT_STREAM_STOP;

    return 0;
}

static int ctp_file_thumb_init(void)
{
    return thread_fork(CTP_FILE_THUMB_TASK_NAME, 15, 2048, 2048, &__this->ctp_thumb_pid, ctp_thumb_task, NULL);
}

static int ctp_file_thumb_exit(void)
{
    if (__this->ctp_thumb_pid) {
        __this->ctp_thumb_exit = 1;
        int msg = 1;
        os_taskq_post_type(CTP_FILE_THUMB_TASK_NAME, Q_USER, 1, &msg);
        thread_kill(&__this->ctp_thumb_pid, KILL_WAIT);
        __this->ctp_thumb_exit = 0;
        __this->ctp_thumb_pid = 0;
    }

    return 0;
}

static int ctp_file_rt_init(void)
{
    printf("-----ctp_file_rt_init----\n");
    int ret;
    struct sockaddr_in dest;

    //tcp
    __this->ctp_file_rt_sockfd = sock_reg(AF_INET, SOCK_STREAM, 0, NULL, NULL);
    if (__this->ctp_file_rt_sockfd == NULL) {
        printf("sock_reg err\n");
        return -1;
    }
    /*     ret = sock_set_reuseaddr(__this->ctp_thumb_sockfd); */
    /* if (ret) { */
    /* printf("sock_set_reuseaddr err:%d\n", ret); */
    /* goto err; */
    /* } */

    dest.sin_family = AF_INET;
    dest.sin_addr.s_addr = inet_addr(__this->dest_ip_addr);
    dest.sin_port = htons(FILE_RT_PORT);
    if (0 != sock_connect(__this->ctp_file_rt_sockfd, (struct sockaddr *)&dest, sizeof(struct sockaddr_in))) {
        printf("sock_connect fail.\n");
        goto err;
    }
    printf(" file rt  tcp connect success \n");

    thread_fork("thread_socket_file_rt", 25, 2048, 2048, &__this->ctp_file_rt_pid, ctp_file_rt_task, NULL);

    printf("-----ctp_file_rt_init done----\n");

    return 0;

err:
    if (__this->ctp_file_rt_sockfd) {
        sock_unreg(__this->ctp_file_rt_sockfd);
        __this->ctp_file_rt_sockfd = NULL;
    }
    return -1;
}

static int ctp_file_rt_exit(void)
{
    printf("-----ctp_file_rt_exit----\n");
    //kill thread
    __this->ctp_file_rt_exit = 1;
    thread_kill(&__this->ctp_file_rt_pid, KILL_WAIT);
    __this->ctp_file_rt_exit = 0;


    //free socket
    if (__this->ctp_file_rt_sockfd) {
        sock_unreg(__this->ctp_file_rt_sockfd);
        __this->ctp_file_rt_sockfd = NULL;
    }

    printf("-----ctp_file_rt_exit----\n");

    return 0;
}

static int get_file_name_cb(char *buf, void *priv)
{
    int i;
    json_object *new_obj;
    json_object *new_obj2;
    const char *json_str;
    json_str = strstr(buf, "{\"");
    if (!json_str) {
        printf("json buf err\n");
        return -1;
    }
    new_obj = json_tokener_parse(json_str);
    if (!new_obj) {
        printf("json_tokener_parse err\n");
        return -1;
    }

    json_object *file_list_array = json_object_object_get(new_obj, "file_list");
    if (file_list_array == NULL) {
        printf("file_list not found in JSON\n");
        json_object_put(new_obj);
        return -1;
    }

    int array_length = json_object_array_length(file_list_array);
    __this->file_total_num = array_length;

    int list_size = __this->file_total_num * sizeof(char *);
    __this->file_list = (char **)malloc(list_size);
    if (!__this->file_list) {
        printf("file_list malloc err \n");
        return -1;
    }
    memset(__this->file_list, 0x00, list_size);

    for (int i = 0; i < array_length; i++) {
        new_obj2 = json_object_array_get_idx(file_list_array, i);
        if (new_obj2 == NULL) {
            break;
        }

        const char *file_name = json_object_get_string(json_object_object_get(new_obj2, "f"));
        if (file_name == NULL) {
            printf("No 'f' field in file at index %d\n", i);
            continue;  // Skip this entry if no file name is found
        }

        __this->file_list[i] = (char *)malloc(strlen(file_name) + 1);
        if (__this->file_list[i] == NULL) {
            printf("Memory allocation failed for file_list[%d]\n", i);
            json_object_put(new_obj);
            goto err;
        }

        // 复制文件名到 file_list[i]
        strcpy(__this->file_list[i], file_name);
        /* printf("file_name->%s\n", __this->file_list[i]); */
    }

    json_object_put(new_obj);

    return 0;

err:
    if (__this->file_list) {
        for (i = 0; i < __this->file_total_num; i++) {
            if (__this->file_list[i]) {
                free(__this->file_list[i]);
                __this->file_list[i] = NULL;
            }
        }

        free(__this->file_list);
        __this->file_list = NULL;
    }
    return -1;
}

static int http_get_mothed(const char *url, int (*cb)(char *, void *), void *priv)
{
    int error = 0;
    http_body_obj http_body_buf;
    httpcli_ctx ctx;
    printf("profile_get_url->%s\n", url);
    memset(&http_body_buf, 0x0, sizeof(http_body_obj));
    memset(&ctx, 0x0, sizeof(httpcli_ctx));

    http_body_buf.recv_len = 0;
    http_body_buf.buf_len = 1 * 1024;
    http_body_buf.buf_count = 1;
    http_body_buf.p = (char *) malloc(http_body_buf.buf_len * sizeof(char));

    ctx.url = url;
    ctx.priv = &http_body_buf;
    ctx.connection = "close";
    ctx.timeout_millsec = 5000;
    error = httpcli_get(&ctx);
    if (error == HERROR_OK) {
        error = cb(http_body_buf.p, priv);
    } else {
        printf("http get err :%d \n", error);
        error = -1;
    }
    if (http_body_buf.p) {
        free(http_body_buf.p);
    }
    return error;
}

static int net_ctp_file_browser_init(void)
{
    int ret;

    char url[100];
    const char topic[] = {"FORWARD_MEDIA_FILES_LIST"};
    const char content[] = {"{\"op\":\"PUT\",\"param\":{\"type\":\"1\"}}"};

    if (!__this->ctp_cli_hdl) {
        printf("ctp cli hdl null !\n");
        return -1;
    }

    ret = ctp_cli_send(__this->ctp_cli_hdl, topic, content);
    if (ret) {
        printf("ctp_cli_send :%s err\n", topic);
        return -1;
    }

    ret = os_sem_pend(&__this->ctp_msg_sem, 1000);
    if (ret) {
        printf("ctp_msg_sem pend err:%d \n", ret);
        return -1;
    }
    /* printf("get vf_list path: %s \n", __this->vf_list); */

    sprintf(url, "http://%s:%d/%s", __this->dest_ip_addr, HTTP_PORT, __this->vf_list);
    ret = http_get_mothed(url, get_file_name_cb, NULL);
    if (ret) {
        printf("http get mothed err\n");
        return -1;
    }

    ret = ctp_file_thumb_init();
    if (ret) {
        printf("ctp file thumb init err\n");
        return -1;
    }

    return 0;
}

static int net_ctp_file_browser_exit(void)
{
    int i;
    ctp_file_thumb_exit();

    if (__this->file_list) {
        for (i = 0; i < __this->file_total_num; i++) {
            if (__this->file_list[i]) {
                free(__this->file_list[i]);
                __this->file_list[i] = NULL;
            }
        }

        free(__this->file_list);
        __this->file_list = NULL;
    }

    return 0;
}


static int ctp_file_browser_num(struct intent *it)
{
    u16 *file_total_num = (u16 *)it->data;
    *file_total_num = __this->file_total_num;

    return 0;
}

static int ctp_file_browser_list(struct intent *it)
{
    u8 ***file_list = (u8 ** *)it->data;
    *file_list = __this->file_list;

    return 0;
}


static int net_ctp_file_rt_start()
{
    int ret;

    /* if (!__this->ctp_cli_hdl) { */
    /* ret = net_ctp_init(); */
    /* if (ret) { */
    /* printf("net ctp init err\n"); */
    /* return -1; */
    /* } */
    /* } */

    ctp_file_rt_init();
    return 0;
}


static void fill_request_data(u8 *data, char *bbm_tx_ip_str, u8 *bbm_tx_mac)
{
    //获取本机MAC
    u8 bbm_rx_mac[6];
    char bbm_tx_mac_str[20];
    char bbm_rx_mac_str[20];
    char bbm_rx_ip_str[20];
    wifi_raw_get_mac(bbm_rx_mac);
    mac_to_string(bbm_rx_mac_str, bbm_rx_mac);

    //获取本机IP
    struct netif_info netif_info;
    lwip_get_netif_info(WIFI_RAW_NETIF, &netif_info);
    strcpy(bbm_rx_ip_str, inet_ntoa(netif_info.ip));

    mac_to_string(bbm_tx_mac_str, bbm_tx_mac);

    sprintf(data, PAIRING_REQUEST, bbm_rx_ip_str, bbm_rx_mac_str, bbm_tx_ip_str, bbm_tx_mac_str);
}

static int deal_pair_respone_package(u8 *payload_buf, char *set_bbm_tx_ip, u8 *set_bbm_tx_mac)
{
    //解析json
    json_object *new_obj = NULL;
    json_object *type_obj = NULL;
    json_object *data_obj = NULL;
    char *bbm_tx_ip_str, *bbm_tx_mac_str, *type;
    char mac_str[20];

    new_obj = json_tokener_parse(payload_buf);
    type_obj =  json_object_object_get(new_obj, "type");
    type = json_object_get_string(type_obj);

    if (!strcmp(type, "pair_rsp")) {
        data_obj =  json_object_object_get(new_obj, "data");
        bbm_tx_ip_str = json_object_get_string(json_object_object_get(data_obj, "bbm_tx_ip"));
        bbm_tx_mac_str = json_object_get_string(json_object_object_get(data_obj, "bbm_tx_mac"));

        printf("recv pair_rsp ip:%s mac:%s\n", bbm_tx_ip_str, bbm_tx_mac_str);
        char req_mac_str[20];
        mac_to_string(req_mac_str, set_bbm_tx_mac);
        if (strcmp(set_bbm_tx_ip, bbm_tx_ip_str) == 0 &&
            strcmp(req_mac_str, bbm_tx_mac_str) == 0) {
            return 0;
        }
    }

    return -1;
}

static void config_head_pair(void)
{
    u8 src_mac[6];
    u8 dest_mac[6] = {0x88, 0x88, 0x88, 0x88, 0x88, 0x88};
    wifi_raw_get_mac(src_mac);
    config_send_pkg_head(src_mac, dest_mac);
}

static int bbm_pairing_task(void *priv)
{
    u8 channel = (u8)priv;

    int ret;
    void *multi_sock = NULL;
    u8 *recv_buf = NULL, *send_buf = NULL, *tem_buf = NULL, *payload_buf = NULL;
    int recv_len, send_len, payload_len;
    struct sockaddr_in recv_addr;
    unsigned int addrlen = sizeof(recv_addr);

    multi_sock = sock_reg(AF_INET, SOCK_DGRAM, 0, NULL, NULL);
    if (multi_sock == NULL) {
        printf("sock_reg err\n");
        goto exit;
    }
    sock_set_recv_timeout(multi_sock, RECV_TIMEOUT);

    struct sockaddr_in dest_addr;
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_addr.s_addr = inet_addr(UDP_MULTICAST_ADDR);
    dest_addr.sin_port = htons(MULTICAST_PORT);

    recv_buf = malloc(PACKAGE_MAX_SIZE);
    send_buf = malloc(PACKAGE_MAX_SIZE);
    tem_buf = malloc(PACKAGE_MAX_SIZE);

    if ((!recv_buf) || (!send_buf) || (!tem_buf)) {
        printf("package buf malloc fail \n");
        goto exit;
    }


    struct arp_entry_t *arp_entry = arp_static_entry_alloc(channel);
    if (!arp_entry) {
        printf("arp_static_entry_alloc err ch:%d used \n", channel);
        goto exit;
    }
    char set_bbm_tx_ip[20];
    u8 set_bbm_tx_mac[6];

    strcpy(set_bbm_tx_ip, inet_ntoa(arp_entry->ipaddr));
    memcpy(set_bbm_tx_mac, arp_entry->ethaddr.addr, sizeof(set_bbm_tx_mac));

    //填充发送消息
    fill_request_data(tem_buf, set_bbm_tx_ip, set_bbm_tx_mac);
    send_len = package_assembly(tem_buf, strlen(tem_buf), send_buf, PACKAGE_MAX_SIZE);

    config_head_pair();

    while (1) {

        if (__this->pairing_task_exit) {
            log_d("pairing task exit  \n");
            arp_static_entry_free(channel);
            break;
        }

        //发送配对请求包
        send_len = sock_sendto(multi_sock, send_buf, send_len, 0, &dest_addr, sizeof(dest_addr));
        if (send_len < 0) {
            printf("sock send err\n");
            continue;
        }

        //接收配对响应包
        recv_len = sock_recvfrom(multi_sock, recv_buf, PACKAGE_MAX_SIZE, 0, &recv_addr, &addrlen);
        if (recv_len <= 0) {
            printf("multi recv err");
            continue;
        }
        printf("recv ip:%s port:%d \n", inet_ntoa(recv_addr.sin_addr), ntohs(recv_addr.sin_port));

        //检查包头
        payload_len = get_package_payload_len(recv_buf);
        if (payload_len < 0) {
            printf("package head err \n");
            continue;
        }
        payload_buf = recv_buf + (recv_len - payload_len);

        //检查配对信息是否正确
        ret = deal_pair_respone_package(payload_buf, set_bbm_tx_ip, set_bbm_tx_mac);
        if (ret) {
            printf("no respone package\n");
            continue;
        }

        u8 src_mac[6];
        wifi_raw_get_mac(src_mac);
        config_send_pkg_head(src_mac, set_bbm_tx_mac);

        //发送响应
        sprintf(tem_buf, PAIRING_ACK);
        send_len = package_assembly(tem_buf, strlen(tem_buf), send_buf, PACKAGE_MAX_SIZE);
        send_len = sock_sendto(multi_sock, send_buf, send_len, 0, &dest_addr, sizeof(dest_addr));
        if (send_len < 0) {
            printf("sock send err\n");
            continue;
        }

        printf("pair success \n");
        //写入flash
        arp_static_table_update_to_flash();

        //通知UI配对完成
        post_pair_msg_to_ui("pair success");


        //标记设备在线，并切换摄像头
        __this->online_table[channel] = BBM_TX_ONLINE;

        break;
    }

exit:
    if (multi_sock) {
        sock_unreg(multi_sock);
    }
    if (recv_buf) {
        free(recv_buf);
    }
    if (send_buf) {
        free(send_buf);
    }
    if (tem_buf) {
        free(tem_buf);
    }
}

//接收端进入配对模式
static int bbm_set_enter_pairing(u8 channel)
{
    thread_fork("bbm_pairing_task", 10, 2048, 2048, &__this->pairing_task_pid, bbm_pairing_task, channel);

    return 0;
}

static int bbm_set_exit_pairing(void)
{
    if (!__this->pairing_task_pid) {
        log_d("no pairing task run\n");
        return -1;
    }

    __this->pairing_task_exit = 1;
    thread_kill(&__this->pairing_task_pid, KILL_WAIT);
    __this->pairing_task_exit = 0;
    __this->pairing_task_pid = 0;

    return 0;
}


static int bbm_set_unpair(u8 channel)
{
    int ret;

    if (channel == __this->cur_channel) {
        //关闭
        net_ctp_rt_stop();
        net_ctp_client_exit();

        __this->cur_channel = INVALID_CH_NUM;
    }

    arp_static_entry_free(channel);

    arp_static_table_update_to_flash();

    bbm_switch_camera();

    return 0;
}

static u8 bbm_get_pair_status(u8 ch)
{
    struct arp_entry_t *arp_entry  = get_arp_static_entry_by_id(ch);
    if (arp_entry) {
        //已配对
        return 1;
    } else {
        //未配对
        return 0;
    }
}

static void ctp_client_manager_task(void)
{
    int res;
    int msg[8];

    while (1) {
        res = os_task_pend("taskq", msg, ARRAY_SIZE(msg));
        switch (res) {
        case OS_TASKQ:
            switch (msg[0]) {
            case Q_EVENT:
                break;
            case Q_MSG:
                switch (msg[1]) {
                case BBM_MSG_CONNECT:
                    net_ctp_client_init();
                    break;
                case BBM_MSG_DISCONNECT:
                    net_ctp_client_exit();
                    break;
                case BBM_MSG_START_RT:
                    net_ctp_rt_start();
                    break;
                case BBM_MSG_STOP_RT:
                    net_ctp_rt_stop();
                    break;
                case BBM_MSG_RECONNECT:
                    net_ctp_rt_stop();
                    net_ctp_client_exit();
                    net_ctp_client_init();
                    break;
                default:
                    break;
                }
                break;
            case Q_USER:
                break;
            default:
                break;
            }
            break;
        case OS_TIMER:
            break;
        case OS_TIMEOUT:
            break;
        default:
            break;
        }
    }
}

static int bbm_config_arp_entry(struct arp_entry_t *arp_entry)
{
    u8 src_mac[6];
    wifi_raw_get_mac(src_mac);
    memcpy(__this->dest_mac, arp_entry->ethaddr.addr, sizeof(__this->dest_mac));
    config_send_pkg_head(src_mac, __this->dest_mac);

    strcpy(__this->dest_ip_addr, inet_ntoa(arp_entry->ipaddr));

}

static int bbm_rx_init(void)
{
    int ret;
    int ch;
    __this->cur_channel = INVALID_CH_NUM;

    for (ch = MIN_PAIR_CH; ch < MAX_PAIR_NUM; ch++) {
        struct arp_entry_t *arp_entry  = get_arp_static_entry_by_id(ch);

        if (arp_entry && __this->online_table[ch] == BBM_TX_ONLINE) {
            bbm_config_arp_entry(arp_entry);
            printf("find arp_entry:%d  ip:%s \n", ch, __this->dest_ip_addr);

            __this->cur_channel = ch;
            net_ctp_client_init();
            break;
        }
    }

    return 0;
}

static int bbm_switch_camera(void)
{
    int ch;
    int is_find = 0;
    struct arp_entry_t *arp_entry;

    if (__this->cur_channel >= MIN_PAIR_CH && __this->cur_channel <= MAX_PAIR_CH) {

        ch = __this->cur_channel;
        do {
            //0-5往复循环
            ch++;
            if (ch > MAX_PAIR_CH) {
                ch = MIN_PAIR_CH;
            }

            //遍历了一圈没有找到可以用设备
            if (ch == __this->cur_channel) {
                printf("no available dev switch\n ");
                is_find = 0;
                break;
            }

            arp_entry = get_arp_static_entry_by_id(ch);
            if (arp_entry && __this->online_table[ch] == BBM_TX_ONLINE) {
                printf("find ch:%d dev switch\n", ch);
                //配对了且设备在线
                is_find = 1;
                break;
            }

        } while (1);

        if (is_find) {
            //关闭之前的
            net_ctp_rt_stop();
            net_ctp_client_exit();

            //开启新的
            bbm_config_arp_entry(arp_entry);
            __this->cur_channel  = ch;
            net_ctp_client_init();

            return 0;
        } else {
            return -1;
        }
    } else {
        for (ch = MIN_PAIR_CH; ch < MAX_PAIR_NUM; ch++) {
            arp_entry  = get_arp_static_entry_by_id(ch);

            if (arp_entry && __this->online_table[ch] == BBM_TX_ONLINE) {
                bbm_config_arp_entry(arp_entry);
                __this->cur_channel  = ch;
                net_ctp_client_init();

                return 0;
            }
        }

        return -1;
    }
}

static void bbm_check_switch_btn(void)
{
    u8 tx_online_cnt = 0;
    int i;

    for (i = 0; i < sizeof(__this->online_table); i++) {
        if (__this->online_table[i]) {
            tx_online_cnt++;
        }
    }

    if (tx_online_cnt > 1) {
        post_stream_msg_to_ui("show switch btn");
    } else {
        post_stream_msg_to_ui("hide switch btn");
    }
}

static void bbm_tx_online_timeout(void *priv)
{
    u32 ch = (u32)priv;
    //标记不在线
    __this->online_table[ch] = BBM_TX_OFFLINE;

    __this->online_timeout[ch] = 0;

    //log
    struct arp_entry_t *arp_entry = get_arp_static_entry_by_id(ch);
    if (arp_entry) {
        printf("ip:%s not online ! ", inet_ntoa(arp_entry->ipaddr));
    }

    if (__this->cur_channel == ch && __this->rt_stream_state == BBM_RT_STREAM_START) {
        net_ctp_rt_stop();
        net_ctp_client_exit();
        __this->cur_channel = INVALID_CH_NUM;
    }

    //检查是否显示切换按钮
    bbm_check_switch_btn();
}


static int baby_monitor_net_event_hander(struct intent *it)
{
    int i;
    int timeout = 1000;     //1000ms
    u32 ip_addr = it->data;
    u32 online_cnt = it->exdata;

    for (i = 0; i < MAX_PAIR_NUM; i++) {
        struct arp_entry_t *arp_entry = get_arp_static_entry_by_id(i);

        if (arp_entry && arp_entry->ipaddr.addr == ip_addr) {
            /* printf("ip:%s on cnt:%d \n", inet_ntoa(ip_addr), online_cnt); */
            /* printf("ch:%d on", i); */
            //标记设备在线
            __this->online_table[i] = BBM_TX_ONLINE;

            //当前没有显示设备
            if (__this->cur_channel == INVALID_CH_NUM) {
                bbm_switch_camera();
            } else if (__this->cur_channel == i) {
                //当前设备
                if (online_cnt < __this->online_cnt_table[i]) {
                    printf("cnt err ip:%s off", inet_ntoa(ip_addr));
                    if (__this->online_timeout[i]) {
                        sys_timeout_del(__this->online_timeout[i]);
                        __this->online_timeout[i] = 0;
                    }
                    //重启
                    net_ctp_rt_stop();
                    net_ctp_client_exit();
                    net_ctp_client_init();
                }
            }
            __this->online_cnt_table[i] = online_cnt;

            //创建超时定时器,timeout内还没收到在线时间,认为设备已下线
            //在超时定时器内标记设备下线
            if (!__this->online_timeout[i]) {
                __this->online_timeout[i]  = sys_timeout_add(i, bbm_tx_online_timeout, timeout);
            } else {
                //重置超时定时器时间
                sys_timer_modify(__this->online_timeout[i], timeout);
            }

            //检查是否显示切换按钮
            bbm_check_switch_btn();
        }
    }
    return 0;
}


static int state_machine(struct application *app, enum app_state state, struct intent *it)
{
    int ret = 0;
    u8 ch;
    switch (state) {
    case APP_STA_CREATE:
        log_d("\n>>>>> baby_monitor_init <<<<<\n");
        break;
    case APP_STA_START:
        if (!it) {
            break;
        }
        switch (it->action) {
        case ACTION_BBM_MAIN:
            log_d("\n>>>>>baby_monitor_main <<<<<\n");
            bbm_rx_init();
            break;
        case ACTION_BBM_START_RT:
            log_d("\n>>>>>baby_monitor start stream <<<<<\n");
            net_ctp_rt_start();
            break;
        case ACTION_BBM_STOP_RT:
            log_d("\n>>>>>baby_monitor stop stream <<<<<\n");
            net_ctp_rt_stop();
            break;
        case ACTION_BBM_GET_PAIR_STATUS:
            log_d("\n>>>>>baby_monitor get pair status <<<<<\n");
            ch = it->exdata;
            it->exdata = bbm_get_pair_status(ch);
            log_d("ch:%d pair status:%d \n", ch, it->exdata);
            break;
        case ACTION_BBM_ENTER_PAIRING:
            log_d("\n>>>>>baby_monitor start pairing <<<<<\n");
            ch = it->exdata;
            bbm_set_enter_pairing(ch);
            break;
        case ACTION_BBM_EXIT_PAIRING:
            log_d("\n>>>>>baby_monitor exit pairing <<<<<\n");
            bbm_set_exit_pairing();
            break;
        case ACTION_BBM_UNPAIR:
            log_d("\n>>>>>baby_monitor start unpair <<<<<\n");
            ch = it->exdata;
            bbm_set_unpair(ch);
            break;
        case ACTION_BBM_SWITCH_WIN:
            log_d("\n>>>>>baby_monitor switch win <<<<<\n");
            bbm_switch_camera();
            break;
        case ACTION_BBM_START_FILE_BROWSER:
            log_d("\n>>>>>baby_monitor start file stream <<<<<\n");
            ret = net_ctp_file_browser_init();
            break;
        case ACTION_BBM_STOP_FILE_BROWSER:
            log_d("\n>>>>>baby_monitor stop file stream <<<<<\n");
            net_ctp_file_browser_exit();
            break;
        case ACTION_BBM_GET_FILE_NUM:
            log_d("\n>>>>>baby_monitor get_file_browser num <<<<<\n");
            ctp_file_browser_num(it);
            break;
        case ACTION_BBM_GET_FILE_LIST:
            log_d("\n>>>>>baby_monitor get_file_browser list <<<<<\n");
            ctp_file_browser_list(it);
            break;
        case ACTION_BBM_GET_FILE_THUMB_REQ:
            log_d("\n>>>>>baby_monitor get_file_browser thumb <<<<<\n");
            int msg;
            msg = it->data;   //index
            os_taskq_post_type(CTP_FILE_THUMB_TASK_NAME, Q_MSG, 1, &msg);
            break;
        case  ACTION_BBM_ONLINE:
            baby_monitor_net_event_hander(it);
            break;

        }
        break;
    case APP_STA_PAUSE:
        break;
    case APP_STA_RESUME:
        break;
    case APP_STA_STOP:
        //todo
        break;
    case APP_STA_DESTROY:
        log_d("\n>>>>> baby_monitor_exit <<<<<\n");
        //todo
        break;
    default:
        break;
    }

    return ret;
}


static int baby_monitor_key_event_handler(struct key_event *key)
{
    int ret = false;
    printf("key->action:%d key->value:%d \n", key->action, key->value);
    if (key->action == KEY_EVENT_CLICK) {
        ret = true;
        switch (key->value) {
        case KEY_POWER:
            printf("KEY1\n");
            bbm_switch_camera();
            break;
        case KEY_MENU:
            printf("KEY2\n");
            break;
        case KEY_UP:
            printf("KEY3\n");
            break;
        case KEY_DOWN:
            printf("KEY4\n");
            net_ctp_file_rt_start();
            break;
        case KEY_OK:
            //todo  测试
            printf("KEY5\n");
            int msg[1];
            msg[0] = "storage/sd0/C/DCIM/1/VID_0001.AVI";
            os_taskq_post_type("thread_socket_file_rt", Q_MSG, 1, msg);

            break;
        default:
            printf("Unknow KEY\n");
            break;
        }
    }

    return ret;
}



static int baby_monitor_device_event_handler(struct sys_event *e)
{
    struct device_event *device_eve = (struct device_event *)e->payload;

    return false;
}

static int event_handler(struct application *app, struct sys_event *event)
{
    switch (event->type) {
    case SYS_KEY_EVENT:
        return  baby_monitor_key_event_handler((struct key_event *)event->payload);
    case SYS_DEVICE_EVENT:
        return  baby_monitor_device_event_handler(event);
    case SYS_NET_EVENT:
    /* return  baby_monitor_net_event_hander((void *)event->payload); */
    default:
        return false;
    }
}


static const struct application_operation baby_monitor_ops = {
    .state_machine  = state_machine,
    .event_handler  = event_handler,
};

REGISTER_APPLICATION(app_baby_monitor) = {
    .name 	= "baby_monitor",
    .action	= ACTION_BBM_MAIN,
    .ops 	= &baby_monitor_ops,
    .state  = APP_STA_DESTROY,
};

