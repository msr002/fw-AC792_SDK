#include "system/includes.h"
#include "server/video_server.h"
#include "server/audio_server.h"
#include "lcd_config.h"
#include "event/key_event.h"
#include "event/device_event.h"
#include "event/net_event.h"
#include "action.h"
#include "app_config.h"
#include "vrec_osd.h"
#include "baby_monitor.h"
#include "stream_core.h"
#include "sock_api/sock_api.h"
#include "ctp_server.h"
#include "net_stream_info.h"
#include "rt_stream_pkg.h"
#include "udp_multicast.h"
#include "pairing_data_model.h"
#include "asm/usb.h"

#define VIDEO_OSD_BUF_SIZE      64                  //水印缓存
#define VIDEO_RT_BUF_SIZE       200 * 1024          //实时流缓存
#define VIDEO_REC_BUF_SIZE      1 * 1024 * 1024     //录像视频(JPG)缓存,内存充足的情况下建议给大点

#define AUDIO_BUF_SIZE          64 * 1024           //实时流or录像音频缓存
#define AUDIO_VOLUME	        100                 //实时流or录像音频音量
#define AUDIO_RT_INTERVAL_SIZE      2*640             //实时流音频包大小,尽量设置小一些降低延迟
#define AUDIO_REC_INTERVAL_SIZE     8192            //录像音频包大小

#define STREAM_RECV_BUF_SIZE        200 * 1024  //实时流socket接收缓存大小
#define STREAM_PARSE_BUF_SIZE       200 * 1024  //实时流解析CTP包缓存大小
#define STREAM_RECV_PORT            9981
#define STREAM_RECV_TASK_NAME       "ctp_rt_recv_task"

#define USB_CDC_BUF_SIZE            512
#define USB_PAIR_PKG_MAX_SIZE       1024
#define USB_PAIR_LBUF_SIZE          1024 * 3

#define DISP_SMALL_WIDTH            320
#define DISP_SMALL_HEIGHT           240
#define MAX_WIN_MODE_NUM            4

#define OFFLINE_TIMEOUT_MS           1000*10

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

enum {
    WIFI_RAW_MODE = 0,
    WIFI_MODE,
};


static struct video_window disp_win[MAX_WIN_MODE_NUM][2] = {
    {
        {
            .left   = 0,
            .top    = 0,
            .width  = LCD_W,
            .height = LCD_H,
            .combine = 1,
        },
        {
            .left   = LCD_W - DISP_SMALL_WIDTH,
            .top    = LCD_H - DISP_SMALL_HEIGHT,
            .width  = DISP_SMALL_WIDTH,
            .height = DISP_SMALL_HEIGHT,
            .combine = 1,
        },
    },
    {
        {
            .left   = LCD_W - DISP_SMALL_WIDTH,
            .top    = LCD_H - DISP_SMALL_HEIGHT,
            .width  = DISP_SMALL_WIDTH,
            .height = DISP_SMALL_HEIGHT,
            .combine = 1,
        },
        {
            .left   = 0,
            .top    = 0,
            .width  = LCD_W,
            .height = LCD_H,
            .combine = 1,
        },
    },
    {
        {
            .left   = 0,
            .top    = 0,
            .width  = LCD_W,
            .height = LCD_H,
            .combine = 1,
        },
        {
            .left   = 0,
            .top    = 0,
            .width  = 0,
            .height = 0,
            .combine = 0,
        },
    },
    {
        {
            .left   = 0,
            .top    = 0,
            .width  = 0,
            .height = 0,
            .combine = 0,
        },
        {
            .left   = 0,
            .top    = 0,
            .width  = LCD_W,
            .height = LCD_H,
            .combine = 1,
        },
    },
};

enum {
    SWITCH_VIDEO_WIN = 1,
    SET_AUDIO_VOL,
};

struct video_rec_hdl {
    struct list_head dev_list_head;
    u8 cur_wifi_mode;

    u8 *usb_cdc_buf;
    u8 *usb_pair_lbuf_ptr;
    struct lbuff_head *usb_pair_lbuf_hdl;
    int usb_pair_task_pid;

    void *disp_pipe_core;
    int curr_win_mode;
    OS_SEM wait_big_win_create;

    u16 offline_timeout_timer;
};
struct video_rec_hdl rec_handler;
#define __this 	(&rec_handler)

struct stream_recv_hdl {
    int stream_recv_task_exit;
    int stream_recv_task_pid;
    void *stream_recv_sockfd;
    void *pipe_core;
    int video_is_running;
    int video_width;
    int video_height;
    int  audio_init;
};

//id用于区别摄像头设备(板级对应)比如id0(video0)->MIPI摄像头
//sub_id,在此工程中用于区别同一摄像头设备的实时流/录像
struct video_dev_hdl {
    struct list_head entry;
    struct server *video_server;
    char *video_osd_buf;
    char *video_buf;
    char *audio_buf;
    struct video_rec_config config;
    void *file;

    struct stream_recv_hdl *stream_recv_hdl;
};

static int check_local_video_is_running(void);
static int check_remote_video_is_running(void);


static int video_rec_close_file(struct video_dev_hdl *dev_hdl)
{
    int ret;
    char fname[32];
    char path[128];

    if (!dev_hdl->file) {
        printf("close file is null \n");
        return 0;
    }

    ret = fget_name(dev_hdl->file, fname, ARRAY_SIZE(fname));
    if (ret <= 0) {
        printf("fget_name err\n");
        fclose(dev_hdl->file);
        return -1;
    }
    strcpy(path, CONFIG_REC_PATH_0);
    strcat(path, fname);

    fclose(dev_hdl->file);
    dev_hdl->file = NULL;

    FILE_LIST_ADD(0, path, 0);

    return 0;
}

static void rec_dev_server_event_handler(void *priv, int argc, int *argv)
{
    switch (argv[0]) {
    case VIDEO_SERVER_UVM_ERR:
        printf("APP_UVM_DEAL_ERR\n");
        break;
    case VIDEO_SERVER_PKG_ERR:
        printf("VIDEO_SERVER_PKG_ERR\n");
        break;
    case VIDEO_SERVER_PKG_END:
        printf("VIDEO_SERVER_PKG_END\n");
        struct video_dev_hdl *hdl = priv;
        //循环录影
        video_rec_close_file(hdl);
        video_rec_create_file(hdl);
        video_savefile(hdl);
        break;
    case VIDEO_SERVER_NET_ERR:
        printf("VIDEO_SERVER_NET_ERR\n");
        break;
    default :
        printf("unknow rec server cmd %x , %x!\n", argv[0], (int)priv);
        break;
    }
}

static u32 video_rec_get_fsize(u16 abr, u8 cycle_time)
{
    u32 fsize;

    fsize = abr * cycle_time * 10000;

    fsize = fsize + fsize / 4;

    return fsize;
}

static int video_rec_del_first_file(void)
{
    struct vfscan *fs = NULL;
    void *file = NULL;

    fs = fscan(CONFIG_REC_PATH_0, "-d -tPNGBINAVITTLDAT -sn", 2);
    file = fselect(fs, FSEL_FIRST_FILE, 0);
    fdelete(file);

    return 0;
}

static int video_rec_create_file(struct video_dev_hdl *dev_hdl)
{
    int i;
    int err;
    FILE *file;
    u32 cur_space;
    u32 need_space = 0;

    need_space =  video_rec_get_fsize(dev_hdl->config.abr_kbps, dev_hdl->config.cycle_time);

    err = fget_free_space(CONFIG_ROOT_PATH, &cur_space);
    if (err) {
        printf("fget free space err\n");
        return err;
    }

    printf("video rec cur space: %dMB, need: %dMB\n", cur_space / 1024, need_space / 1024 / 1024);

    //TODO
    while (cur_space < need_space / 1024) {
        video_rec_del_first_file();

        err = fget_free_space(CONFIG_ROOT_PATH, &cur_space);
        if (err) {
            return err;
        }
    }

    file = fopen(CONFIG_REC_PATH_0"VID_****.AVI", "w+");
    if (!file) {
        printf("video rec fopen err\n");
        return -1;
    }
    err = fseek(file, need_space, SEEK_SET);
    if (err) {
        printf("video rec fseek err \n");
        fclose(file);
        return -1;
    }

    fseek(file, 0, SEEK_SET);

    dev_hdl->file = file;

    return 0;
}

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
            if (head_info->frm_sz > STREAM_PARSE_BUF_SIZE) {
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
                printf("old frame \n");
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

static int stream_recv_sock_cb(enum sock_api_msg_type type, void *priv)
{
    struct stream_recv_hdl *recv_hdl  = priv;
    if (recv_hdl->stream_recv_task_exit) {
        printf("stream recv cb func exit\n");
        return -1;
    }
    return 0;
}

static void stream_recv_task(void *priv)
{
    struct sockaddr_in dstaddr;
    u32 addrlen = sizeof(dstaddr);
    u8 *recv_buf;
    int recv_len;
    int ret;

    int res;
    int msg[8];
    int time;
    int fps = 0;
    int abr = 0;
    int total = 0;
    char text[128];

    struct stream_recv_hdl *recv_hdl = priv;
    struct video_window  *win =  &disp_win[__this->curr_win_mode][1];

    recv_buf = malloc(STREAM_RECV_BUF_SIZE);
    if (!recv_buf) {
        printf("stream recv task malloc recv buff err \n");
        goto exit;
    }

    struct parse_info parse_info = {0};
    struct frm_head  frame_head;
    parse_info.data_buf = malloc(STREAM_PARSE_BUF_SIZE);
    if (!parse_info.data_buf) {
        printf("malloc parse data buf err \n");
        goto exit;
    }

    while (1) {
        if (recv_hdl->stream_recv_task_exit) {
            printf("stream recv task exit \n");
            break;
        }

        if (os_taskq_accept(ARRAY_SIZE(msg), msg) == OS_TASKQ) {
            /* int err = os_taskq_post_type(DECODE_TASK_NAME, Q_MSG, 3, msg); */
            if (msg[0] == Q_MSG) {
                switch (msg[1]) {
                case SWITCH_VIDEO_WIN:
                    printf("stream recv switch video win \n");
                    win =  &disp_win[__this->curr_win_mode][1];

                    if (win) {
                        printf("remote win left:%d top:%d width:%d height:%d \n",
                               win->left, win->top, win->width, win->height);
                    }

                    bbm_video_pipe_exit(&recv_hdl->pipe_core);
                    recv_hdl->pipe_core = NULL;
                    break;
                default:
                    break;
                }
            }
        }

        recv_len = sock_recvfrom(recv_hdl->stream_recv_sockfd,
                                 recv_buf, STREAM_RECV_BUF_SIZE, 0, &dstaddr, &addrlen);
        if (recv_len <= 0) {
            printf("rt recv err:%d \n", recv_len);
            continue;
        }

        if ((timer_get_ms() - time) >= 1000) {
            //调试信息
            sprintf(text, "total:%d abr:%d  fps:%d", total / 1024, abr / 1024, fps);
            time = timer_get_ms();
            fps = 0;
            abr = 0;
            total = 0;

            //debug
            printf("%s \n", text);

        }
        total += recv_len;
        ret = parse_recv_packet(recv_buf, recv_len, &parse_info);
        if (ret) {
            printf("parse_recv_packet err \n");
            continue;
        }

        if (parse_info.packet_type == VIDEO_TYPE_PACKET) {
            //8字节头部
            u8 *jpeg_buf = parse_info.data_buf + 8;
            int jpeg_len = parse_info.data_len - 8;

            while (jpeg_len > 32) {
                if (jpeg_buf[jpeg_len - 2] == 0xFF && jpeg_buf[jpeg_len - 1] == 0XD9) {
                    break;
                }
                jpeg_len--;
            }
            if (jpeg_len < 32 || jpeg_buf[0] != 0xFF || jpeg_buf[1] != 0xD8 ||
                jpeg_buf[jpeg_len - 2] != 0xFF || jpeg_buf[jpeg_len - 1] != 0XD9) {
                printf("err jpeg !!! \n");
                continue;
            }
            fps++;
            abr += jpeg_len;

            if (!recv_hdl->pipe_core) {
                recv_hdl->video_is_running = 1;
                int width = recv_hdl->video_width;
                int height = recv_hdl->video_height;

                if (win && win->width && win->height) {
                    struct video_format f = {0};
                    struct video_window *local_win = &disp_win[__this->curr_win_mode][0];
                    int need_post_sem = 1;

                    //判断是否是小窗, 如果是小窗需要等大窗口先创建,否者小窗口会被大窗口覆盖
                    int local_video_is_running = check_local_video_is_running();
                    if (win->width < local_win->width && local_video_is_running) {
                        printf("remote need wait big win create \n");
                        if (os_sem_pend(&__this->wait_big_win_create, 50) != 0) {
                            printf("wait big win create err \n");
                        }
                        need_post_sem = 0;
                    } else if (win->width > local_win->width && local_win->width != 0 && local_video_is_running) {

                        need_post_sem = 1;

                    } else {
                        need_post_sem = 0;
                    }

                    bbm_video_pipe_init_format(&f, win, width, height, NULL);
                    bbm_video_pipe_init(&recv_hdl->pipe_core, &f);

                    if (need_post_sem) {
                        os_sem_post(&__this->wait_big_win_create);
                    }

                } else {
                    continue;
                }
            }
            bbm_pipe_disp_one_frame(recv_hdl->pipe_core, jpeg_buf, jpeg_len);
            /* printf("v:%d\n",jpeg_len); */
        } else if (parse_info.packet_type == AUDIO_TYPE_PACKET) {
            if (!recv_hdl->audio_init) {
                bbm_audio_dec_init();
                recv_hdl->audio_init = 1;
            }
            bbm_audio_dec_one_frame(parse_info.data_buf, parse_info.data_len);
            /* printf("a:%d\n",parse_info.data_len); */
        } else {
            //continue parse
            /* printf("c\n"); */
        }
    }

exit:
    recv_hdl->video_is_running = 0;

    if (recv_hdl->pipe_core) {
        bbm_video_pipe_exit(&recv_hdl->pipe_core);
        recv_hdl->pipe_core = NULL;
    }
    if (recv_hdl->audio_init) {
        bbm_audio_dec_exit();
        recv_hdl->audio_init = 0;
    }

    if (recv_buf) {
        free(recv_buf);
    }
    if (parse_info.data_buf) {
        free(parse_info.data_buf);
    }
}

static int stream_recv_init(struct stream_recv_hdl *recv_hdl)
{
    printf("-----bbm_stream_recv_init----\n");
    int ret;

    struct sockaddr_in conn_addr;
    conn_addr.sin_family = AF_INET;
    conn_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    conn_addr.sin_port = htons(STREAM_RECV_PORT);

    recv_hdl->stream_recv_sockfd = sock_reg(AF_INET, SOCK_DGRAM, 0, stream_recv_sock_cb, recv_hdl);
    if (recv_hdl->stream_recv_sockfd == NULL) {
        printf("sock_reg err\n");
        return -1;
    }

    ret = sock_bind(recv_hdl->stream_recv_sockfd, (struct sockaddr *)&conn_addr, sizeof(struct sockaddr));
    if (ret) {
        printf("sock_bind err:%d\n", ret);
        sock_unreg(recv_hdl->stream_recv_sockfd);
        recv_hdl->stream_recv_sockfd = NULL;
        return -1;
    }

    struct ip_mreq McastAdrr;
    McastAdrr.imr_multiaddr.s_addr = inet_addr(UDP_MULTICAST_ADDR);
    McastAdrr.imr_interface.s_addr = htonl(INADDR_ANY);
    ret = sock_setsockopt(recv_hdl->stream_recv_sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &McastAdrr, sizeof(McastAdrr));
    if (ret) {
        printf("%s %d->Error in sock_setsockopt\n", __func__, __LINE__);
        sock_unreg(recv_hdl->stream_recv_sockfd);
        recv_hdl->stream_recv_sockfd = NULL;
        return -1;
    }

    thread_fork(STREAM_RECV_TASK_NAME, 12, 2048, 2048, &recv_hdl->stream_recv_task_pid, stream_recv_task, recv_hdl);

    return 0;
}

static int stream_recv_exit(struct stream_recv_hdl *recv_hdl)
{
    printf("-----bbm_rt_recv_exit----\n");
    recv_hdl->stream_recv_task_exit = 1;
    thread_kill(&recv_hdl->stream_recv_task_pid, KILL_WAIT);
    recv_hdl->stream_recv_task_exit = 0;

    sock_unreg(recv_hdl->stream_recv_sockfd);
    return 0;
}

static int video_savefile(struct video_dev_hdl *dev_hdl)
{
    union video_req req = {0};
    int err;

    req.rec.channel = dev_hdl->config.sub_id;
    req.rec.width 	= dev_hdl->config.width;
    req.rec.height 	= dev_hdl->config.height;
    req.rec.format  = VIDEO_FMT_AVI;
    req.rec.state 	= VIDEO_STATE_SAVE_FILE;
    req.rec.file    = dev_hdl->file;

    req.rec.fps 	    = dev_hdl->config.fps;
    req.rec.real_fps 	= dev_hdl->config.fps;
    req.rec.abr_kbps    = dev_hdl->config.abr_kbps;
    req.rec.cycle_time  = dev_hdl->config.cycle_time * 60;

    req.rec.audio.sample_rate = VIDEO_REC_AUDIO_SAMPLE_RATE;
    req.rec.audio.channel   = 1;
    req.rec.audio.volume    = AUDIO_VOLUME;

    err = server_request(dev_hdl->video_server, VIDEO_REQ_REC, &req);
    if (err != 0) {
        printf("video_save_file: err=%d\n", err);
        return err;
    }

    return 0;
}

static int video_start(struct video_rec_config *config)
{
    int ret;
    char dev_name[20];
    u8 *osd_buf;
    union video_req req = {0};
    struct video_text_osd text_osd;
    struct video_graph_osd graph_osd;
    u16 max_one_line_strnum;
    u16 osd_line_num;
    u16 osd_max_heigh;
    struct video_dev_hdl *dev_hdl = NULL;

    u8 id = config->id;
    u8 sub_id = config->sub_id;

    dev_hdl = malloc(sizeof(struct video_dev_hdl));
    if (!dev_hdl) {
        printf("malloc dev_hdl err\n");
        goto err;
    }
    memset(dev_hdl, 0x00, sizeof(struct video_dev_hdl));
    memcpy(&dev_hdl->config, config, sizeof(struct video_rec_config));

    sprintf(dev_name, "video%d.%d", id, sub_id);
    printf("video_rec_start: %s \n", dev_name);

    dev_hdl->video_server = server_open("video_server", dev_name);
    if (!dev_hdl->video_server) {
        printf("video_server open err \n");
        goto err;
    }
    server_register_event_handler(dev_hdl->video_server, dev_hdl, rec_dev_server_event_handler);

    //video
    req.rec.channel     = sub_id;
    req.rec.state       = VIDEO_STATE_START;
    req.rec.quality     = VIDEO_MID_Q;

    req.rec.width       = config->width;
    req.rec.height      = config->height;
    req.rec.fps         = 0;
    req.rec.real_fps    = config->fps;
    req.rec.abr_kbps    = config->abr_kbps;

    //区分录像还是实时流
    if (config->net_path) {
        //实时流
        req.rec.buf_len = VIDEO_RT_BUF_SIZE;
        req.rec.format  = USER_VIDEO_FMT_AVI;
        req.rec.online  = 1;
        req.rec.cycle_time = 5 * 60;

        req.rec.audio.aud_interval_size =
            config->aud_interval_size ? config->aud_interval_size : AUDIO_RT_INTERVAL_SIZE;

        dev_hdl->stream_recv_hdl = malloc(sizeof(struct stream_recv_hdl));
        if (dev_hdl->stream_recv_hdl) {
            memset(dev_hdl->stream_recv_hdl, 0x00, sizeof(struct stream_recv_hdl));
            //宽高默认和发送端一致
            dev_hdl->stream_recv_hdl->video_width = config->width;
            dev_hdl->stream_recv_hdl->video_height = config->height;
            stream_recv_init(dev_hdl->stream_recv_hdl);
        }

    } else {
        //录像
        req.rec.buf_len = VIDEO_REC_BUF_SIZE;
        req.rec.format  = VIDEO_FMT_AVI;
        req.rec.online  = 1;

        if (!config->cycle_time) {
            config->cycle_time = 3;
        }
        req.rec.cycle_time = config->cycle_time * 60;

        req.rec.audio.aud_interval_size = AUDIO_REC_INTERVAL_SIZE;

        ret = video_rec_create_file(dev_hdl);
        if (ret) {
            goto err;
        }

        req.rec.file    = dev_hdl->file;
    }

    //uvc
    if (id == 10) {
        req.rec.camera_type = VIDEO_CAMERA_UVC;
        if (sub_id < 5) {
            req.rec.uvc_id = 0;
        } else {
            req.rec.uvc_id = 1;
        }
        if (uvc_host_online() < 0) {
            printf(" uvc host online err !\n");
            goto err;
        }
        //实时流+录像联动jpeg数量不够
        req.rec.online  = 0;
    } else {
        req.rec.camera_type = VIDEO_CAMERA_NORMAL;
    }


    dev_hdl->video_buf = malloc(req.rec.buf_len);
    if (!dev_hdl->video_buf) {
        printf("malloc video rt buf err\n");
        goto err;
    }
    req.rec.buf = dev_hdl->video_buf;

    //OSD
    dev_hdl->video_osd_buf = malloc(VIDEO_OSD_BUF_SIZE);
    if (!dev_hdl->video_osd_buf) {
        printf("malloc video rt osd buf err\n");
        goto err;
    }
    memset(dev_hdl->video_osd_buf, 0x00, VIDEO_OSD_BUF_SIZE);
    osd_buf = dev_hdl->video_osd_buf;

    memset(osd_buf, ' ', 8);
    osd_buf[8] = '\\';
    memcpy(osd_buf + 9, osd_str_buf, strlen(osd_str_buf));
    text_osd.font_w = 16;
    text_osd.font_h = 32;
    max_one_line_strnum = strlen(osd_buf);
    osd_line_num = 1;
    osd_max_heigh = (req.rec.height == 1088) ? 1080 : req.rec.height ;
    text_osd.x = (req.rec.width - max_one_line_strnum * text_osd.font_w) / 64 * 64;
    text_osd.y = (osd_max_heigh - text_osd.font_h * osd_line_num) / 16 * 16;
    text_osd.color[0] = 0x057d88;
    text_osd.color[1] = 0xe20095;
    text_osd.color[2] = 0xe20095;
    text_osd.bit_mode = 2;
    text_osd.text_format = osd_buf;
    text_osd.font_matrix_table = osd_str_total;
    text_osd.font_matrix_base = osd2_str_matrix;
    text_osd.font_matrix_len = sizeof(osd2_str_matrix);
    text_osd.direction = 1;

    //实时流不开启水印
    if (config->net_path) {
        req.rec.text_osd = NULL;
    } else {
        req.rec.text_osd = &text_osd;
    }
    req.rec.graph_osd = NULL;//&graph_osd;

    //audio
    req.rec.audio.sample_rate = VIDEO_REC_AUDIO_SAMPLE_RATE;
    req.rec.audio.channel   = 1;
    req.rec.audio.volume    = AUDIO_VOLUME;

    dev_hdl->audio_buf = malloc(AUDIO_BUF_SIZE);
    if (!dev_hdl->audio_buf) {
        printf("malloc audio rt buf err \n");
        goto err;
    }
    req.rec.audio.buf = dev_hdl->audio_buf;
    req.rec.audio.buf_len = AUDIO_BUF_SIZE;

    //回声消除,默认使用软件的
    //如要改动其他采样率或硬件回声消除请查看开源文档
    req.rec.audio.aec_enable = 1;
    struct aec_s_attr aec_param = {0};
    req.rec.audio.aec_attr = &aec_param;

    extern void get_cfg_file_aec_config(struct aec_s_attr * aec_param);
    get_cfg_file_aec_config(&aec_param);

    if (aec_param.EnableBit == 0) {
        req.rec.audio.aec_enable = 0;
        req.rec.audio.aec_attr = NULL;
    }
    aec_param.wideband = 0;
    aec_param.hw_delay_offset = 75;


    //实时流
    if (config->net_path) {
        struct net_stream_info s_info = {0};
        s_info.sample_rate = req.rec.audio.sample_rate;
        s_info.fps = config->fps;
        s_info.abr_kbps = config->abr_kbps;

        strcpy(req.rec.net_par.netpath, config->net_path);
        printf("\n @@@@@@ path = %s\n", req.rec.net_par.netpath);
        req.rec.target = VIDEO_TO_OUT;
        req.rec.out.path = req.rec.net_par.netpath;
        req.rec.out.arg  = &s_info;
        req.rec.out.open = stream_open;
        req.rec.out.send = stream_write;
        req.rec.out.close = stream_close;
    }

    ret = server_request(dev_hdl->video_server, VIDEO_REQ_REC, &req);
    if (ret) {
        puts("\n\n\nstart rec err\n\n\n");
        goto err;
    }

    if (config->net_path) {
        req.rec.state = VIDEO_STATE_RESET_BITS_RATE;
        server_request(dev_hdl->video_server, VIDEO_REQ_REC, &req);
    }

    list_add_tail(&dev_hdl->entry, &__this->dev_list_head);

    return 0;

err:
    if (dev_hdl) {
        if (dev_hdl->video_buf) {
            free(dev_hdl->video_buf);
        }
        if (dev_hdl->video_osd_buf) {
            free(dev_hdl->video_osd_buf);
        }
        if (dev_hdl->audio_buf) {
            free(dev_hdl->audio_buf);
        }
        if (dev_hdl->stream_recv_hdl) {
            stream_recv_exit(dev_hdl->stream_recv_hdl);
            free(dev_hdl->stream_recv_hdl);
        }

        server_close(dev_hdl->video_server);

        free(dev_hdl);
    }
    return -1;
}

static int video_stop(struct video_rec_config *config)
{
    struct video_dev_hdl *dev_hdl = NULL;

    union video_req req = {0};
    int ret;
    u8 id = config->id;
    u8 sub_id = config->sub_id;
    u8 find = 0;

    list_for_each_entry(dev_hdl, &__this->dev_list_head, entry) {
        if (dev_hdl->config.id == id && dev_hdl->config.sub_id == sub_id) {
            find = 1;
            list_del(&dev_hdl->entry);
            break;
        }
    }

    if (!find) {
        printf(" not found dev hdl  id:%d sub_id:%d \n", id, sub_id);
        return -1;
    }

    req.rec.channel = dev_hdl->config.sub_id;
    req.rec.state = VIDEO_STATE_STOP;
    ret = server_request(dev_hdl->video_server, VIDEO_REQ_REC, &req);
    if (ret) {
        printf("\nstop rec err 0x%x\n", ret);
        return -1;
    }

    video_rec_close_file(dev_hdl);

    server_close(dev_hdl->video_server);


    if (dev_hdl->video_buf) {
        free(dev_hdl->video_buf);
    }
    if (dev_hdl->video_osd_buf) {
        free(dev_hdl->video_osd_buf);
    }
    if (dev_hdl->audio_buf) {
        free(dev_hdl->audio_buf);
    }
    if (dev_hdl->stream_recv_hdl) {
        stream_recv_exit(dev_hdl->stream_recv_hdl);
        free(dev_hdl->stream_recv_hdl);
    }


    free(dev_hdl);

    return 0;
}

static int video_stop_all(void)
{
    struct video_dev_hdl *dev_hdl = NULL;
    struct video_dev_hdl *n = NULL;

    union video_req req = {0};
    int ret;

    list_for_each_entry_safe(dev_hdl, n, &__this->dev_list_head, entry) {
        list_del(&dev_hdl->entry);
        req.rec.channel = dev_hdl->config.sub_id;
        req.rec.state = VIDEO_STATE_STOP;
        ret = server_request(dev_hdl->video_server, VIDEO_REQ_REC, &req);
        if (ret) {
            printf("\nstop rec err 0x%x\n", ret);
            return -1;
        }
        video_rec_close_file(dev_hdl);

        server_close(dev_hdl->video_server);

        if (dev_hdl->video_buf) {
            free(dev_hdl->video_buf);
        }
        if (dev_hdl->video_osd_buf) {
            free(dev_hdl->video_osd_buf);
        }
        if (dev_hdl ->audio_buf) {
            free(dev_hdl->audio_buf);
        }

        if (dev_hdl->stream_recv_hdl) {
            stream_recv_exit(dev_hdl->stream_recv_hdl);
            free(dev_hdl->stream_recv_hdl);
        }
        free(dev_hdl);
    }

    return 0;
}

static int video_stop_all_rec(void)
{
    struct video_dev_hdl *dev_hdl = NULL;
    struct video_dev_hdl *n = NULL;

    union video_req req = {0};
    int ret;

    list_for_each_entry_safe(dev_hdl, n, &__this->dev_list_head, entry) {
        if (!dev_hdl->file) {
            //实时流
            continue;
        }

        list_del(&dev_hdl->entry);
        req.rec.channel = dev_hdl->config.sub_id;
        req.rec.state = VIDEO_STATE_STOP;
        ret = server_request(dev_hdl->video_server, VIDEO_REQ_REC, &req);
        if (ret) {
            printf("\nstop rec err 0x%x\n", ret);
            return -1;
        }
        video_rec_close_file(dev_hdl);

        server_close(dev_hdl->video_server);

        if (dev_hdl->video_buf) {
            free(dev_hdl->video_buf);
        }
        if (dev_hdl->video_osd_buf) {
            free(dev_hdl->video_osd_buf);
        }
        if (dev_hdl ->audio_buf) {
            free(dev_hdl->audio_buf);
        }

        if (dev_hdl->stream_recv_hdl) {
            stream_recv_exit(dev_hdl->stream_recv_hdl);
            free(dev_hdl->stream_recv_hdl);
        }
        free(dev_hdl);
    }

    return 0;
}


static int video_set_abr(struct video_rec_config *config)
{
    int ret = 0;
    union video_req req = {0};
    u8 find = 0;
    u8 id = config->id;
    u8 sub_id = config->sub_id;
    struct video_dev_hdl *dev_hdl = NULL;

    printf("set abr:%d id:%d  sub_id:%d \n"
           , config->abr_kbps, config->id, config->sub_id);

    list_for_each_entry(dev_hdl, &__this->dev_list_head, entry) {
        if (dev_hdl->config.id == id && dev_hdl->config.sub_id == sub_id) {
            find = 1;
            break;
        }
    }

    if (!find) {
        printf(" video_set_abr not found dev hdl id:%d sub_id:%d \n", id, sub_id);
        return -1;
    }

    req.rec.state = VIDEO_STATE_RESET_BITS_RATE;
    req.rec.channel     = sub_id;
    req.rec.abr_kbps    = config->abr_kbps;

    if (dev_hdl->video_server) {
        ret = server_request(dev_hdl->video_server, VIDEO_REQ_REC, &req);
        if (ret) {
            printf("reset bits rate err :%d \n", ret);
        }
    }

    return ret;
}

static int video_take_photo(struct video_rec_config *config)
{
    int ret = -1;
    int find = 0;
    char buf[128];
    char fname[32];
    union video_req req = {0};
    struct video_dev_hdl *dev_hdl = NULL;
    void *fp;

    u8 id = config->id;
    u8 sub_id = config->sub_id;

    list_for_each_entry(dev_hdl, &__this->dev_list_head, entry) {
        if (dev_hdl->config.id == id && dev_hdl->config.sub_id == sub_id) {
            find = 1;
            break;
        }
    }

    if (find) {
        if (dev_hdl->video_server) {
            printf("video save frame \n");
            fp = fopen(CAMERA0_CAP_PATH"img_****.jpg", "w+");
            if (!fp) {
                printf("video take photo fopen err \n");
                return -1;
            }
            ret = fget_name(fp, fname, ARRAY_SIZE(fname));
            if (ret <= 0) {
                printf("video take photo fget_name err\n");
                fclose(fp);
                return -1;
            }
            fclose(fp);
            sprintf(buf, "%s%s", CAMERA0_CAP_PATH, fname);
            req.rec.rec_save_path = buf;
            req.rec.channel = sub_id;
            ret = server_request(dev_hdl->video_server, VIDEO_REQ_SAVE_FRAME, &req);
            if (ret) {
                printf("video save frame err:%d \n", ret);
            } else {
#if defined CONFIG_ENABLE_VLIST
                sprintf(buf, "%s", req.rec.rec_save_path);
                FILE_LIST_ADD(0, buf, 0);
#endif
            }
        }
    }

    return ret;
}


static int video_get_status(struct video_rec_config *config, int *status)
{
    u8 id = config->id;
    u8 sub_id = config->sub_id;
    struct video_dev_hdl *dev_hdl = NULL;

    list_for_each_entry(dev_hdl, &__this->dev_list_head, entry) {
        if (dev_hdl->config.id == id && dev_hdl->config.sub_id == sub_id) {
            *status = 1;
            return 0;
        }
    }

    *status = 0;

    return 0;
}

static int switch_wifi_mode(void)
{
    if (__this->cur_wifi_mode == WIFI_RAW_MODE) {
        usb_pair_stop();
        video_stop_all();
        if (__this->offline_timeout_timer) {
            sys_timeout_del(__this->offline_timeout_timer);
            __this->offline_timeout_timer = 0;
        }

        wifi_raw_exit();
        wifi_init();
        __this->cur_wifi_mode = WIFI_MODE;

    } else {
        video_stop_all();
        wifi_exit();
        wifi_raw_init();
        usb_pair_start();
        __this->cur_wifi_mode = WIFI_RAW_MODE;
    }
}

static int usb_pair_start(void)
{
    __this->usb_pair_lbuf_ptr = malloc(USB_PAIR_LBUF_SIZE);
    if (!__this->usb_pair_lbuf_ptr) {
        printf("usb pair lbuf ptr malloc fail \n");
        goto err;
    }
    __this->usb_pair_lbuf_hdl = lbuf_init(__this->usb_pair_lbuf_ptr, USB_PAIR_LBUF_SIZE,
                                          8, sizeof(struct lbuf_pair_data_head));
    if (!__this->usb_pair_lbuf_hdl) {
        printf("usb pair lbuf init fail \n");
        goto err;
    }

    extern void usb_cdc_pair_task(void *priv);
    int ret = thread_fork("bbm_tx_usb_pair_task", 10, 2048, 2048, &__this->usb_pair_task_pid,
                          usb_cdc_pair_task, __this->usb_pair_lbuf_hdl);
    if (ret) {
        printf("bbm tx usb pair task create fail :%d \n", ret);
        goto err;
    }

    return 0;
err:
    if (__this->usb_pair_lbuf_ptr) {
        free(__this->usb_pair_lbuf_ptr);
        __this->usb_pair_lbuf_ptr = NULL;
        __this->usb_pair_lbuf_hdl = NULL;
    }
    return -1;
}

static int usb_pair_stop(void)
{
    if (__this->usb_pair_task_pid) {
        thread_kill(&__this->usb_pair_task_pid, KILL_WAIT);
    }

    if (__this->usb_pair_lbuf_ptr) {
        free(__this->usb_pair_lbuf_ptr);
        __this->usb_pair_lbuf_ptr = NULL;
        __this->usb_pair_lbuf_hdl = NULL;
    }
}

static int local_video_disp_start(void)
{
    int camera_src_w = 640;
    int camera_src_h = 480;
    int camera_src_id = 1;
    int remote_video_is_running = 0;
    int need_post_sem = 0;

    struct video_format f = {0};
    struct video_window *win = &disp_win[__this->curr_win_mode][0];
    if (!win) {
        printf("err win ptr !\n");
        return -1;
    }

    printf("local win left:%d top:%d width:%d height:%d \n",
           win->left, win->top, win->width, win->height);

    if (win->width == 0 || win->height == 0) {
        return 0;
    }

    struct video_window *remote_win = &disp_win[__this->curr_win_mode][1];
    remote_video_is_running = check_remote_video_is_running();
    if (win->width < remote_win->width && remote_video_is_running) {
        printf("local need wait big win create \n");
        if (os_sem_pend(&__this->wait_big_win_create, 50) != 0) {
            printf("wait big win create err \n");
        }
        need_post_sem = 0;
    } else if (win->width > remote_win->width && remote_win->width != 0 && remote_video_is_running) {

        need_post_sem = 1;

    } else {
        need_post_sem = 0;
    }

    bbm_video_pipe_init_format(&f, win, camera_src_w, camera_src_h, NULL);
    if (need_post_sem) {
        os_sem_post(&__this->wait_big_win_create);
    }

    if (bbm_video_pipe_disp_init(&__this->disp_pipe_core, &f, camera_src_id)) {
        printf("bbm tx disp init err \n");
        return -1;
    }
    return 0;
}

static int local_video_disp_stop(void)
{
    return bbm_video_pipe_exit(&__this->disp_pipe_core);
}

static int check_local_video_is_running(void)
{
#if BBM_LOCAL_CAMERA_DISP_ENABLE
    return 1;
#else
    return 0;
#endif
}

static int check_remote_video_is_running(void)
{
    struct video_dev_hdl *dev_hdl = NULL;
    list_for_each_entry(dev_hdl, &__this->dev_list_head, entry) {
        struct stream_recv_hdl *recv_hdl = dev_hdl->stream_recv_hdl;
        if (recv_hdl) {
            return recv_hdl->video_is_running;
        }
    }
}

static int switch_disp_win(void)
{
    int msg[2];
    __this->curr_win_mode = (__this->curr_win_mode + 1) % MAX_WIN_MODE_NUM;
    printf("switch disp win curr win :%d \n", __this->curr_win_mode);

    msg[0] = SWITCH_VIDEO_WIN;
    int err = os_taskq_post_type(STREAM_RECV_TASK_NAME, Q_MSG, ARRAY_SIZE(msg), msg);
    if (err) {
        printf("taskq post task:%s  err:%d", STREAM_RECV_TASK_NAME, err);
    }

    local_video_disp_stop();
    local_video_disp_start();
}

static void video_rec_main_init(void)
{
    memset(__this, 0, sizeof(struct video_rec_hdl));
    INIT_LIST_HEAD(&__this->dev_list_head);
    os_sem_create(&__this->wait_big_win_create, 0);
    usb_pair_start();


#if BBM_LOCAL_CAMERA_DISP_ENABLE
    local_video_disp_start();
#else
    __this->curr_win_mode = 3;
#endif
}

void offline_timeout_cb(void *priv)
{
    if (__this->cur_wifi_mode != WIFI_RAW_MODE) {
        return;
    }
    printf("bbm rx device offline \n");

    if (__this->offline_timeout_timer) {
        sys_timeout_del(__this->offline_timeout_timer);
        __this->offline_timeout_timer = 0;
    }

    video_stop_all();
}

static int video_rec_state_machine(struct application *app, enum app_state state, struct intent *it)
{
    int ret = 0;

    switch (state) {
    case APP_STA_CREATE:
        log_d("\n >>>>>>> video_rec: create\n");
        break;
    case APP_STA_START:
        if (!it) {
            break;
        }
        switch (it->action) {
        case ACTION_VIDEO_REC_MAIN:
            puts("ACTION_VIDEO_REC_MAIN\n");
            video_rec_main_init();
            break;
        case ACTION_VIDEO_START:
            puts("ACTION_VIDEO_START\n");
            ret = video_start(it->exdata);
            break;
        case ACTION_VIDEO_STOP:
            puts("ACTION_VIDEO_STOP\n");
            ret = video_stop(it->exdata);
            break;
        case ACTION_VIDEO_STOP_ALL:
            puts("ACTION_VIDEO_STOP_ALL\n");
            ret = video_stop_all();
            break;
        case ACTION_VIDEO_SET_ABR:
            puts("ACTION_VIDEO_SET_ABR\n");
            ret = video_set_abr(it->exdata);
            break;
        case ACTION_VIDEO_GET_STATUS:
            puts("ACTION_VIDEO_GET_STATUS\n");
            ret = video_get_status(it->exdata, it->data);
            break;
        case ACTION_VIDEO_TAKE_PHOTO:
            puts("ACTION_VIDEO_TAKE_PHOTO\n");
            ret = video_take_photo(it->exdata);
            break;
        }
        break;
    case APP_STA_PAUSE:
        puts("--------app_rec: APP_STA_PAUSE\n");
        break;
    case APP_STA_RESUME:
        puts("--------app_rec: APP_STA_RESUME\n");
        break;
    case APP_STA_STOP:
        puts("--------app_rec: APP_STA_STOP\n");
        break;
    case APP_STA_DESTROY:
        break;
    }

    return ret;
}


static int video_rec_key_event_handler(struct key_event *key)
{
    int ret = false;
    printf("key->action:%d key->value:%d \n", key->action, key->value);

#ifdef CONFIG_BBM_TX
    switch (key->value) {
    case KEY_POWER:
        printf("KEY1\n");
        break;
    case KEY_MENU:
        printf("KEY2\n");
        break;
    case KEY_UP:
        if (key->action == KEY_EVENT_CLICK) {
            printf("KEY3\n");
#if BBM_LOCAL_CAMERA_DISP_ENABLE
            ret = true;
            switch_disp_win();
#endif
        }
        break;
    case KEY_DOWN:
        if (key->action == KEY_EVENT_CLICK) {
            printf("KEY4\n");
            ret = true;
            switch_wifi_mode();
        }
        break;
    case KEY_OK:
        ret = true;
        if (key->action == KEY_EVENT_DOWN) {
            printf("KEY5 DOWN\n");
            if (__this->cur_wifi_mode == WIFI_RAW_MODE) {
                bbm_tx_enter_pairing();
            }
        } else if (key->action == KEY_EVENT_UP) {
            printf("KEY5 UP\n");
            if (__this->cur_wifi_mode == WIFI_RAW_MODE) {
                bbm_tx_exit_pairing();
            }
        }
        break;
    }
#endif

    return ret;
}

static int video_rec_device_event_handler(struct sys_event *e)
{
    int ret = false;
    int rlen = 0;
    char buf[16];
    struct device_event *device_eve = (struct device_event *)e->payload;

    if (e->from == DEVICE_EVENT_FROM_SD) {
        switch (device_eve->event) {
        case DEVICE_EVENT_IN:
            FILE_LIST_IN_MEM(1);
            ret = true;
            break;
        case DEVICE_EVENT_OUT:
            FILE_LIST_EXIT();
            snprintf(buf, sizeof(buf), "online:0");
            CTP_CMD_COMBINED(NULL, CTP_NO_ERR, "SD_STATUS", "NOTIFY", buf);
            ret = true;
            video_stop_all_rec();
            break;
        default:
            break;
        }
    } else if (e->from == DEVICE_EVENT_FROM_CFG_TOOL) {
#if BBM_USB_PAIR_ENABLE
        printf("DEVICE_EVENT_FROM_CFG_TOOL \n");
        if (!__this->usb_cdc_buf) {
            __this->usb_cdc_buf = malloc(USB_CDC_BUF_SIZE);
            if (!__this->usb_cdc_buf) {
                printf("usb_cdc_buf malloc fail \n");
                return false;
            }
        }

        const usb_dev usb_id = device_eve->value;
        rlen = cdc_read_data(usb_id, __this->usb_cdc_buf, USB_CDC_BUF_SIZE);
        if (__this->cur_wifi_mode == WIFI_RAW_MODE && __this->usb_pair_lbuf_hdl) {
            static struct lbuf_pair_data_head *lbuf_data = NULL;
            static int total_len = 0;

            package_head *head = __this->usb_cdc_buf;

            if (head->magic == PACKAGE_MAGIC) {
                printf("head len:%d ", head->len);

                if (!lbuf_data) {
                    lbuf_data = lbuf_alloc(__this->usb_pair_lbuf_hdl, USB_PAIR_PKG_MAX_SIZE);
                    if (!lbuf_data) {
                        printf("bbm usb pair lbuf_alloc err \n");
                        return false;
                    }
                }

                lbuf_data->usb_id = usb_id;
                lbuf_data->len = 0;

                total_len = head->len;
            }

            if (lbuf_data) {
                if (lbuf_data->len + rlen > USB_PAIR_PKG_MAX_SIZE) {
                    printf("usb pair pkg over \n");
                    lbuf_data->len = 0;
                }

                memcpy(lbuf_data->data + lbuf_data->len, __this->usb_cdc_buf, rlen);
                lbuf_data->len += rlen;

                if (lbuf_data->len == total_len + sizeof(package_head)) {
                    lbuf_push(lbuf_data, BIT(0));
                    lbuf_data = NULL;
                }
            }

        }
        ret = true;
#endif
    }

    return ret;
}

int video_rec_net_event_hander(void *e)
{
    struct net_event *event = (struct net_event *)e;
    struct ctp_arg *event_arg = (struct ctp_arg *)event->arg;
    /* struct net_event *net = &event->u.net; */

    switch (event->event) {
    case NET_EVENT_CMD:
        printf("IN NET_EVENT_CMD\n");
        ctp_cmd_analysis(event_arg->topic, event_arg->content, event_arg->cli);
        if (event_arg->content) {
            free(event_arg->content);
        }
        event_arg->content = NULL;
        if (event_arg) {
            free(event_arg);
        }
        event_arg = NULL;
        return true;
        break;
    case NET_EVENT_DATA:
        /* printf("IN NET_EVENT_DATA\n"); */
        break;
    }
    return false;
}

/*录像app的事件总入口*/
static int video_rec_event_handler(struct application *app, struct sys_event *event)
{
    switch (event->type) {
    case SYS_KEY_EVENT:
        return video_rec_key_event_handler((struct key_event *)event->payload);
    case SYS_DEVICE_EVENT:
        return video_rec_device_event_handler(event);
    case SYS_NET_EVENT:
        return video_rec_net_event_hander((void *)event->payload);
    default:
        return false;
    }
}

static int video_rec_msg_handler(struct application *app, int *msg)
{
    switch (msg[0]) {
    case ACTION_BBM_ONLINE:
        if (!__this->offline_timeout_timer) {
            __this->offline_timeout_timer =  sys_timeout_add(NULL, offline_timeout_cb, OFFLINE_TIMEOUT_MS);
        } else {
            sys_timer_modify(__this->offline_timeout_timer, OFFLINE_TIMEOUT_MS);
        }
        break;
    default:
        break;
    }
    return 0;
}

static const struct application_operation video_rec_ops = {
    .state_machine  = video_rec_state_machine,
    .event_handler 	= video_rec_event_handler,
    .msg_handler    = video_rec_msg_handler,
};

REGISTER_APPLICATION(app_video_rec) = {
    .name 	= "video_rec",
    .action	= ACTION_VIDEO_REC_MAIN,
    .ops 	= &video_rec_ops,
    .state  = APP_STA_DESTROY,
};





