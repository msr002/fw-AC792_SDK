#include "system/includes.h"
#include "lcd_config.h"
#include "server/ctp_server.h"
#include "sock_api/sock_api.h"
#include "baby_monitor.h"
#include "rt_stream_pkg.h"
#include "video_ioctl.h"

#define CTP_RT_RECV_PORT            2224        //实时流接收数据端口
#define CTP_RT_SEND_PORT            9981        //图传(音频)发送数据端口
#define CTP_RT_RECV_BUF_SIZE        100 * 1024  //实时流socket接收缓存大小
#define CTP_RT_PARSE_BUF_SIZE       100 * 1024  //实时流解析CTP包缓存大小
#define RT_LBUF_SIZE                200 * 1024  //LBUF
#define CTP_RT_RECV_TIMEOUT         300         //实时流socket接收超时时间设置,单位ms

#define SEND_BUF_MAX_LEN             2 * 1024   //UDP发送缓存,用于BBM_RX发送音频包

//实时流接收
static int ctp_rt_recv_task_pid;   //实时流接收线程PID
static void *ctp_rt_recv_sockfd;   //实时流接收socket
static u8 ctp_rt_recv_task_exit;   //实时流接收线程退出标记
static u32 rt_dev_task_name_cnt = 0;

static struct list_head recv_dev_list_head;
static OS_MUTEX recv_mutex;

//实时流发送(音频)
static int ctp_rt_send_task_pid;   //实时流发送线程PID
static void *ctp_rt_send_sockfd;   //实时流发送socket
static u8 ctp_rt_send_task_exit;   //实时流发送线程退出标记

static u8 rt_stream_init = 0;

static struct list_head send_dev_list_head;
static OS_MUTEX send_mutex;


struct video_window disp_win[3] = {
    //Main Win
    {
        .left 	 = 0,
        .top  	 = 0,
        .width  = LCD_W,
        .height = LCD_H,
        .combine = 1,
    },
    //Left Half Win
    {
        .left 	 = 0,
        .top  	 = 0,
        .width  = LCD_W / 2,
        .height = LCD_H,
        .combine = 1,
    },
    //Rigth Half Win
    {
        .left 	 = LCD_W / 2,
        .top  	 = 0,
        .width  = LCD_W / 2,
        .height = LCD_H,
        .combine = 1,
    },
};

enum {
    VIDEO_TYPE_PACKET = 10,
    AUDIO_TYPE_PACKET,
    CONTINUE_PARSE_TYPE_PACKET,
    UNKNOW_TYPE_PACKET,
};

struct parse_info {
    u8 *data_buf;        //解析出来的数据缓存
    int data_len;
    u8 packet_type;     //解析出的数据类型(视频/音频)
    u32 old_frame_seq;  //媒体包序列
};

struct lbuf_data_head {
    int len;
    u8 data[0];
};

struct rt_stream_dev {
    struct list_head recv_entry;
    struct list_head send_entry;
    u32 ip_addr;

    //video pipeline
    void *pipe_core;
    struct video_window win;

    //lbuf
    struct lbuff_head *lbuf_handle;
    u8 *lbuf_ptr;

    //thread
    int task_pid;
    char task_name[64];
};


static int parse_recv_packet(u8 *recv_buf, int recv_len, struct parse_info *parse_info)
{
    static u32 total_payload_len = 0;

    u32 position = 0;
    struct frm_head  *head_info;
    u32 frame_head_size = sizeof(struct frm_head);

    if (recv_len < frame_head_size) {
        printf(" recv_recv_len err\n");
        return -1;
    }

    do {
        head_info = (struct frm_head *)(recv_buf + position);

        if ((head_info->type & JPEG_TYPE_VIDEO) || (head_info->type & PCM_TYPE_AUDIO)) {
            if (head_info->frm_sz > CTP_RT_PARSE_BUF_SIZE) {
                printf("jpeg frame size too large :%d \n", head_info->frm_sz);
                return -1;
            }
            recv_len = recv_len - (frame_head_size + head_info->payload_size);
            if (recv_len < 0) {
                printf("remain recv_len err:%d \n", recv_len);
                return -1;
            }

            //如果当前的seq小于旧的seq,说明是旧的数据包,跳过不处理
            if (head_info->seq < parse_info->old_frame_seq) {
                goto continue_deal;
            }
            //如果当前seq大于旧的seq,认为是新的数据包,组包重新初始
            if (head_info->seq > parse_info->old_frame_seq) {
                parse_info->old_frame_seq = head_info->seq;
                total_payload_len = 0;
            }

            memcpy(parse_info->data_buf + head_info->offset,
                   (recv_buf + position) + frame_head_size,
                   head_info->payload_size);

            total_payload_len += head_info->payload_size;

            //接收到完整一帧
            if (total_payload_len == head_info->frm_sz) {
                parse_info->data_len = total_payload_len;
                total_payload_len = 0;

                if (head_info->type & JPEG_TYPE_VIDEO) {
                    parse_info->packet_type =  VIDEO_TYPE_PACKET;
                } else {
                    parse_info->packet_type =  AUDIO_TYPE_PACKET;
                }
                return 0;
            }
        } else {
            printf("recv type err:%d \n", head_info->type);
            parse_info->packet_type = UNKNOW_TYPE_PACKET;
            return 0;
        }

continue_deal:
        position += (frame_head_size + head_info->payload_size);

    } while (recv_len > 0);

    parse_info->packet_type = CONTINUE_PARSE_TYPE_PACKET;
    return 0;
}

static int deal_recv_packet(u8 *recv_buf, int recv_len, u32 ip_addr)
{
    struct rt_stream_dev *rt_dev;
    int msg[2];

    os_mutex_pend(&recv_mutex, 0);
    list_for_each_entry(rt_dev, &recv_dev_list_head, recv_entry) {
        if (rt_dev->ip_addr == ip_addr) {
            struct lbuf_data_head *lbuf_data = lbuf_alloc(rt_dev->lbuf_handle, recv_len);
            if (!lbuf_data) {
                printf("rt lbuf_alloc err\n");
                return -1;
            }
            lbuf_data->len = recv_len;
            memcpy(lbuf_data->data, recv_buf, recv_len);
            lbuf_push(lbuf_data, BIT(0));
            os_taskq_post_type(rt_dev->task_name, Q_MSG, ARRAY_SIZE(msg), msg);
        }
    }
    os_mutex_post(&recv_mutex);

    return 0;
}

static void ctp_rt_recv_task(void *priv)
{
    struct sockaddr_in dstaddr;
    u32 addrlen = sizeof(dstaddr);
    u8 *recv_buf;
    int recv_len;
    int ret;

    recv_buf = malloc(CTP_RT_RECV_BUF_SIZE);
    if (!recv_buf) {
        printf("ctp recv task malloc recv buff err \n");
        goto exit;
    }


    sock_set_recv_timeout(ctp_rt_recv_sockfd, CTP_RT_RECV_TIMEOUT);

    while (1) {
        if (ctp_rt_recv_task_exit) {
            printf("cpt rt recv task exit \n");
            break;
        }

        recv_len = sock_recvfrom(ctp_rt_recv_sockfd,
                                 recv_buf, CTP_RT_RECV_BUF_SIZE, 0, &dstaddr, &addrlen);
        if (recv_len <= 0) {
            printf("rt recv err:%d \n", recv_len);
            continue;
        }
        deal_recv_packet(recv_buf, recv_len, dstaddr.sin_addr.s_addr);
    }

exit:
    if (recv_buf) {
        free(recv_buf);
    }
}

static void ctp_rt_send_task(void)
{
    int ret;
    int data_size;
    u8 *data_buf  = NULL;

    data_buf = malloc(SEND_BUF_MAX_LEN);
    if (!data_buf) {
        printf("ctp send malloc data buf err \n");
        goto exit;
    }

    ret = bbm_audio_enc_init();
    if (ret) {
        printf("audio_enc_init err");
        goto exit;
    }

    struct sockaddr_in dest_addr;
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(CTP_RT_SEND_PORT);

    while (1) {
        if (ctp_rt_send_task_exit) {
            printf("ctp_rt_send_task exit \n");
            break;
        }

        data_size = bbm_audio_enc_get_data(data_buf);
        if (data_size <= 0) {
            continue;
        }

        os_mutex_pend(&send_mutex, 0);
        struct rt_stream_dev *rt_dev;
        list_for_each_entry(rt_dev, &send_dev_list_head, send_entry) {
            dest_addr.sin_addr.s_addr = rt_dev->ip_addr;
            ret = sock_sendto(ctp_rt_send_sockfd, data_buf, data_size, 0, &dest_addr, sizeof(dest_addr));
            if (ret < 0) {
                printf("rt stream sock send err\n");
                continue;
            }
        }
        os_mutex_post(&send_mutex);
    }

exit:
    if (data_buf) {
        free(data_buf);
    }
    bbm_audio_enc_exit();
}


static void rt_stream_dev_task(void *priv)
{
    struct rt_stream_dev *rt_dev = priv;
    struct parse_info parse_info = {0};

    int res;
    int msg[8];
    int ret;

    parse_info.data_buf = malloc(CTP_RT_PARSE_BUF_SIZE);
    if (!parse_info.data_buf) {
        printf("malloc parse data buf err \n");
        goto exit;
    }

    while (1) {
        res = os_task_pend("taskq", msg, ARRAY_SIZE(msg));

        switch (res) {
        case OS_TASKQ:
            switch (msg[0]) {
            case Q_MSG:
                struct lbuf_data_head *lbuf_data = lbuf_pop(rt_dev->lbuf_handle, BIT(0));
                if (!lbuf_data) {
                    printf("lbuf pop err");
                    break;
                }
                ret = parse_recv_packet(lbuf_data->data, lbuf_data->len,
                                        &parse_info);
                if (ret) {
                    printf("parse_recv_packet err \n");
                    lbuf_free(lbuf_data);
                    break;
                }
                lbuf_free(lbuf_data);

                if (parse_info.packet_type == VIDEO_TYPE_PACKET) {
                    //8字节头部
                    u8 *jpeg_buf = parse_info.data_buf + 8;
                    u32 jpeg_len = parse_info.data_len - 8;
                    bbm_pipe_disp_one_frame(rt_dev->pipe_core, jpeg_buf, jpeg_len);
                } else if (parse_info.packet_type == AUDIO_TYPE_PACKET) {
                    bbm_audio_dec_one_frame(parse_info.data_buf, parse_info.data_len);
                } else {
                    //continue parse
                }
                break;
            case Q_USER:
                goto exit;
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
    }

exit:
    if (parse_info.data_buf) {
        free(parse_info.data_buf);
    }
    printf("rt_stream_dev_task exit\n");
}

static int bbm_rt_send_init(void)
{
    printf("-----ctp_rt_send_init----\n");
    int ret;
    struct sockaddr_in conn_addr;
    conn_addr.sin_family = AF_INET;
    conn_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    conn_addr.sin_port = htons(CTP_RT_SEND_PORT);

    ctp_rt_send_sockfd = sock_reg(AF_INET, SOCK_DGRAM, 0, NULL, NULL);
    if (ctp_rt_send_sockfd == NULL) {
        printf("sock_reg err\n");
        return -1;
    }

    INIT_LIST_HEAD(&send_dev_list_head);
    os_mutex_create(&send_mutex);

    thread_fork("thread_socket_send", 12, 2048, 2048, &ctp_rt_send_task_pid, ctp_rt_send_task, NULL);

    return 0;
}

static int bbm_rt_send_exit(void)
{
    printf("-----ctp_rt_send_exit----\n");

    ctp_rt_send_task_exit = 1;
    thread_kill(&ctp_rt_send_task_pid, KILL_WAIT);
    ctp_rt_send_task_exit = 0;

    sock_unreg(ctp_rt_send_sockfd);

    os_mutex_del(&send_mutex, OS_DEL_ALWAYS);

    return 0;
}

static int bbm_rt_recv_init(void)
{
    printf("-----bbm_rt_recv_init----\n");
    int ret;

    struct sockaddr_in conn_addr;
    conn_addr.sin_family = AF_INET;
    conn_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    conn_addr.sin_port = htons(CTP_RT_RECV_PORT);

    ctp_rt_recv_sockfd = sock_reg(AF_INET, SOCK_DGRAM, 0, NULL, NULL);
    if (ctp_rt_recv_sockfd == NULL) {
        printf("sock_reg err\n");
        return -1;
    }

    ret = sock_bind(ctp_rt_recv_sockfd, (struct sockaddr *)&conn_addr, sizeof(struct sockaddr));
    if (ret) {
        printf("sock_bind err:%d\n", ret);
        sock_unreg(ctp_rt_recv_sockfd);
        ctp_rt_recv_sockfd = NULL;
        return -1;
    }

    INIT_LIST_HEAD(&recv_dev_list_head);
    os_mutex_create(&recv_mutex);

    return thread_fork("ctp_rt_recv_task", 12, 2048, 2048, &ctp_rt_recv_task_pid, ctp_rt_recv_task, NULL);
}

static int bbm_rt_recv_exit(void)
{
    printf("-----bbm_rt_recv_exit----\n");
    ctp_rt_recv_task_exit = 1;
    thread_kill(&ctp_rt_recv_task_pid, KILL_WAIT);
    ctp_rt_recv_task_exit = 0;

    sock_unreg(ctp_rt_recv_sockfd);

    os_mutex_del(&recv_mutex, OS_DEL_ALWAYS);

    return 0;
}

static int bbm_rt_dev_init(u32 ip_addr, int disp_mode)
{
    int ret;
    u8 audio_dec_init = 0;

    printf("---bbm_rt_dev_init---\n");

    struct rt_stream_dev *rt_dev = malloc(sizeof(struct rt_stream_dev));
    if (!rt_dev) {
        printf("rt_stream_dev malloc err \n");
        goto err;
    }
    memset(rt_dev, 0x00, sizeof(struct rt_stream_dev));

    //param
    rt_dev->ip_addr = ip_addr;

    //video pipe
    ret = bbm_video_pipe_init(&rt_dev->pipe_core, &disp_win[disp_mode]);
    if (ret) {
        goto err;
    }

    //lbuf
    rt_dev->lbuf_ptr = malloc(RT_LBUF_SIZE);
    if (rt_dev->lbuf_ptr == NULL) {
        printf("lbuf malloc buf err");
        goto err;
    }
    rt_dev->lbuf_handle = lbuf_init(rt_dev->lbuf_ptr, RT_LBUF_SIZE, 4, sizeof(struct lbuf_data_head));

    //thread
    sprintf(rt_dev->task_name, "rt_dev_task%d", rt_dev_task_name_cnt++);
    thread_fork(rt_dev->task_name, 15, 2048, 2048, &rt_dev->task_pid, rt_stream_dev_task, rt_dev);

    //audio dec
    ret = bbm_audio_dec_init();
    if (ret) {
        goto err;
    }
    audio_dec_init = 1;

    //recv list
    os_mutex_pend(&recv_mutex, 0);
    list_add_tail(&rt_dev->recv_entry, &recv_dev_list_head);
    os_mutex_post(&recv_mutex);

    //send list
    os_mutex_pend(&send_mutex, 0);
    list_add_tail(&rt_dev->send_entry, &send_dev_list_head);
    os_mutex_post(&send_mutex);

    return 0;

err:
    if (rt_dev) {
        if (rt_dev->pipe_core) {
            bbm_video_pipe_exit(&rt_dev->pipe_core);
        }
        if (rt_dev->lbuf_ptr) {
            free(rt_dev->lbuf_ptr);
        }
        if (audio_dec_init) {
            bbm_audio_dec_exit();
        }
        free(rt_dev);
    }
    return -1;
}

static int bbm_rt_dev_exit(u32 ip_addr)
{
    int msg;
    struct rt_stream_dev *rt_dev, *n;

    printf("---bbm_rt_dev_exit---\n");

    os_mutex_pend(&recv_mutex, 0);
    list_for_each_entry_safe(rt_dev, n, &recv_dev_list_head, recv_entry) {
        if (rt_dev->ip_addr == ip_addr) {
            list_del(&rt_dev->recv_entry);
            break;
        }
    }
    os_mutex_post(&recv_mutex);

    os_taskq_del_type(rt_dev->task_name, Q_MSG);
    os_taskq_post_type(rt_dev->task_name, Q_USER, 1, &msg);
    thread_kill(&rt_dev->task_pid, KILL_WAIT);

    bbm_video_pipe_exit(&rt_dev->pipe_core);

    bbm_audio_dec_exit();

    if (rt_dev->lbuf_ptr) {
        free(rt_dev->lbuf_ptr);
    }


    os_mutex_pend(&send_mutex, 0);
    list_for_each_entry_safe(rt_dev, n, &send_dev_list_head, send_entry) {
        if (rt_dev->ip_addr == ip_addr) {
            list_del(&rt_dev->send_entry);
            break;
        }
    }
    os_mutex_post(&send_mutex);


    free(rt_dev);

    return 0;
}

int bbm_ctp_rt_start(void *ctp_cli_hdl, int disp_mode)
{
    int ret;
    const char topic_3[] = {"OPEN_RT_STREAM"};
    const char content_3[] = {"{\"op\":\"PUT\",\"param\":{\"abr\":\"1500\",\"w\":\"640\",\"fps\":\"20\",\"h\":\"480\",\"id\":\"0\",\"sub_id\":\"0\"}}"};

    struct sockaddr_in *sockaddr = ctp_cli_get_hdl_addr(ctp_cli_hdl);
    u32 ip_addr = sockaddr->sin_addr.s_addr;

    ret = bbm_ctp_send_access(ctp_cli_hdl);
    if (ret) {
        return -1;
    }

    ret = ctp_cli_send(ctp_cli_hdl, topic_3, content_3);
    if (ret) {
        printf("ctp_cli_send :%s err\n", topic_3);
        return -1;
    }

    ret = bbm_rt_dev_init(ip_addr, disp_mode);
    if (ret) {
        return -1;
    }


    return 0;
}

int bbm_ctp_rt_stop(void *ctp_cli_hdl)
{
    int ret;
    const char topic_3[] = {"CLOSE_RT_STREAM"};
    const char content_3[] = {"{\"op\":\"PUT\",\"param\":{\"id\":\"0\",\"sub_id\":\"0\"}}"};
    struct sockaddr_in *sockaddr = ctp_cli_get_hdl_addr(ctp_cli_hdl);
    u32 ip_addr =  sockaddr->sin_addr.s_addr;

    //发送停止实时流命令
    ret = ctp_cli_send(ctp_cli_hdl, topic_3, content_3);
    if (ret) {
        printf("ctp_cli_send :%s err\n", topic_3);
        return -1;
    }

    bbm_rt_dev_exit(ip_addr);


    return 0;
}


int bbm_rt_stream_init(void)
{
    int ret;

    if (rt_stream_init) {
        printf("rt stream already init \n");
        return 0;
    }
    ret = bbm_rt_recv_init();
    if (ret) {
        return -1;
    }
    ret = bbm_rt_send_init();
    if (ret) {
        bbm_rt_recv_exit();
        return -1;
    }
    rt_stream_init = 1;


    return 0;
}

int bbm_rt_stream_exit(void)
{
    int ret;
    if (!rt_stream_init) {
        printf("rt stream already exit \n");
        return 0;
    }

    ret = bbm_rt_recv_exit();
    ret = bbm_rt_send_exit();

    rt_stream_init = 0;

    return 0;
}


static int cal_source_crop(struct video_source_crop *crop, int factor)
{
    //限制变焦倍数
    if (factor < 1 && factor > 4) {
        printf("zoom factor:%d is invalid \n", factor);
        return -1;
    }

    //TODO
    //默认VGA
    int src_width = 640;
    int src_height = 480;

    crop->width = src_width / factor;
    crop->height = src_height / factor;

    //居中变焦
    crop->x_offset = (src_width - crop->width) / 2;
    crop->y_offset = (src_height - crop->height) / 2;

    return 0;
}

//factor:变焦倍数
int bbm_rt_stream_digital_zomm(void *ctp_cli_hdl, int factor)
{
    int ret;
    struct video_source_crop crop;

    struct sockaddr_in *sockaddr = ctp_cli_get_hdl_addr(ctp_cli_hdl);
    u32 ip_addr = sockaddr->sin_addr.s_addr;
    struct rt_stream_dev *rt_dev;
    u8 find = 0;

    os_mutex_pend(&recv_mutex, 0);
    list_for_each_entry(rt_dev, &recv_dev_list_head, recv_entry) {
        if (rt_dev->ip_addr == ip_addr) {
            find = 1;
            break;
        }
    }
    os_mutex_post(&recv_mutex);

    if (!find) {
        printf("not found rt dev\n");
        return -1;
    }

    ret = cal_source_crop(&crop, factor);
    if (ret) {
        return -1;
    }

    return bbm_video_pipe_set_zoom(rt_dev->pipe_core, &crop);
}

int bbm_rt_stream_reset_pipe(void *ctp_cli_hdl, int disp_mode)
{
    struct rt_stream_dev *rt_dev, *n;
    int msg;

    struct sockaddr_in *sockaddr = ctp_cli_get_hdl_addr(ctp_cli_hdl);
    u32 ip_addr = sockaddr->sin_addr.s_addr;

    os_mutex_pend(&recv_mutex, 0);
    list_for_each_entry(rt_dev, &recv_dev_list_head, recv_entry) {
        if (rt_dev->ip_addr == ip_addr) {
            list_del(&rt_dev->recv_entry);
            break;
        }
    }
    os_mutex_post(&recv_mutex);

    os_taskq_del_type(rt_dev->task_name, Q_MSG);
    os_taskq_post_type(rt_dev->task_name, Q_USER, 1, &msg);
    thread_kill(&rt_dev->task_pid, KILL_WAIT);

    lbuf_clear(rt_dev->lbuf_handle);

    bbm_video_pipe_exit(&rt_dev->pipe_core);

    bbm_video_pipe_init(&rt_dev->pipe_core, &disp_win[disp_mode]);

    thread_fork(rt_dev->task_name, 15, 2048, 2048, &rt_dev->task_pid, rt_stream_dev_task, rt_dev);

    os_mutex_pend(&recv_mutex, 0);
    list_add_tail(&rt_dev->recv_entry, &recv_dev_list_head);
    os_mutex_post(&recv_mutex);

    return 0;
}

int bbm_ctp_rec_start(void *ctp_cli_hdl)
{
    int ret;
    const char topic_3[] = {"OPEN_REC"};
    const char content_3[] = {"{\"op\":\"PUT\",\"param\":{\"w\":\"640\",\"fps\":\"25\",\"h\":\"480\",\"id\":\"0\",\"sub_id\":\"1\",\"abr\":\"4000\",\"cycle_time\":\"1\"}}"};

    ret = ctp_cli_send(ctp_cli_hdl, topic_3, content_3);
    if (ret) {
        printf("ctp_cli_send :%s err\n", topic_3);
        return -1;
    }

    return 0;
}

int bbm_ctp_rec_stop(void *ctp_cli_hdl)
{
    int ret;
    const char topic_3[] = {"CLOSE_REC"};
    const char content_3[] = {"{\"op\":\"PUT\",\"param\":{\"id\":\"0\",\"sub_id\":\"1\"}}"};

    ret = ctp_cli_send(ctp_cli_hdl, topic_3, content_3);
    if (ret) {
        printf("ctp_cli_send :%s err\n", topic_3);
        return -1;
    }

    return 0;
}





