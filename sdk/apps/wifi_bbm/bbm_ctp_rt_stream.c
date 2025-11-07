#include "system/includes.h"
#include "lcd_config.h"
#include "server/ctp_server.h"
#include "sock_api/sock_api.h"
#include "baby_monitor.h"
#include "rt_stream_pkg.h"
#include "video_ioctl.h"
#include "server/video_server.h"
#include "server/audio_server.h"
#include "net_stream_info.h"
#include "stream_core.h"
#include "avilib.h"
#include "vrec_osd.h"
#include "udp_multicast.h"
#include "app_config.h"

#define STREAM_VIDEO_BUF_SIZE      (512 * 1024)
#define STREAM_AUDIO_BUF_SIZE      (128 * 1024)

//发送方式二选一,都为零时不发送数据包给TX设备
#if (RX_STREAM_SEND_ENABLE==1) && (RX_AUDIO_SEND_ENABLE==1)
#error "Only one method can be selected! (Only Audio) or (Audio+Video)"
#endif

#define CTP_RT_RECV_PORT            2224        //实时流接收数据端口
#define CTP_RT_SEND_PORT            9981        //图传(音频)发送数据端口
#define CTP_RT_RECV_BUF_SIZE        200 * 1024  //实时流socket接收缓存大小
#define CTP_RT_PARSE_BUF_SIZE       200 * 1024  //实时流解析CTP包缓存大小
#define RT_LBUF_SIZE                200 * 1024  //LBUF
#define CTP_RT_RECV_TIMEOUT         300         //实时流socket接收超时时间设置,单位ms

#define DISP_SMALL_WIDTH            320
#define DISP_SMALL_HEIGHT           240
#define MAX_WIN_MODE_NUM            4

#define OPEN_RT_TOPIC "OPEN_RT_STREAM"
#define OPEN_RT_CONTENT \
    "{\"op\":\"PUT\",\"param\":{" \
    "\"abr\":\"%d\",\"w\":\"%d\",\"fps\":\"%d\"," \
    "\"h\":\"%d\",\"id\":\"%d\",\"sub_id\":\"%d\"}}"

#define CLOSE_RT_TOPIC "CLOSE_RT_STREAM"
#define CLOSE_RT_CONTENT \
    "{\"op\":\"PUT\",\"param\":{" \
    "\"id\":\"%d\",\"sub_id\":\"%d\"}}"

#define OPEN_REC_TOPIC "OPEN_REC"
#define OPEN_REC_CONTENT \
    "{\"op\":\"PUT\",\"param\":{" \
    "\"w\":\"%d\",\"fps\":\"%d\",\"h\":\"%d\"," \
    "\"id\":\"%d\",\"sub_id\":\"%d\",\"abr\":\"%d\"," \
    "\"cycle_time\":\"%d\"}}"

#define CLOSE_REC_TOPIC "CLOSE_REC"
#define CLOSE_REC_CONTENT \
    "{\"op\":\"PUT\",\"param\":{" \
    "\"id\":\"%d\",\"sub_id\":\"%d\"}}"

#define SET_ABR_TOPIC "SET_VIDEO_ABR"
#define SET_ABR_CONTENT \
    "{\"op\":\"PUT\",\"param\":{" \
    "\"abr\":\"%d\",\"id\":\"%d\",\"sub_id\":\"%d\"}}"

#define TAKE_PHOTO_TOPIC "PHOTO_CTRL"
#define TAKE_PHOTO_CONTENT \
    "{\"op\":\"PUT\",\"param\":{" \
    "\"id\":\"%d\",\"sub_id\":\"%d\"}}"


//默认情况下
//video0(id:0)对应mipi摄像头
//video1(id:1)对应dvp摄像头
//video10(id:10)对应usb摄像头
//
//sub_id用于区分实时流/录像,
//usb摄像头也通过sub_id区分fusb/husb,0-4 -> fusb,5 - x -> husb
//以上id与board_develop.c文件对应
//启用对应设备时,TX设备的板级文件要开启对应的宏CONFIG_VIDEO*_ENABLE

//默认实时流参数
static struct video_rec_config default_rt_config = {
    .width = 640,
    .height = 480,
    .fps = 25,
    .abr_kbps = 2000,
    .id = 1,
    .sub_id = 0,
};

//默认录像参数
static struct video_rec_config default_rec_config = {
    .width = 640,
    .height = 480,
    .fps = 25,
    .abr_kbps = 2000,
    .id = 1,
    .sub_id = 1,
    .cycle_time = 3,
};


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

//实时流发送(音频+视频)
static void *video_server = NULL;
static u8 *stream_video_buf = NULL;
static u8 *stream_audio_buf = NULL;
static u8 send_ref_count = 0;

static u8 rt_stream_init = 0;

static int curr_win_mode;
static void *local_pipe_core;
static OS_SEM wait_big_win_create;


/* 1台设备：全屏 */
struct video_window disp_win_1[1] = {
    {
        .left   = 0,
        .top    = 0,
        .width  = LCD_W,
        .height = LCD_H,
        .combine = 1,
    },
};

/* 2台设备：左右分屏 */
struct video_window disp_win_2[2] = {
    {
        .left   = 0,
        .top    = 0,
        .width  = LCD_W / 2,
        .height = LCD_H,
        .combine = 1,
    },
    {
        .left   = LCD_W / 2,
        .top    = 0,
        .width  = LCD_W / 2,
        .height = LCD_H,
        .combine = 1,
    },
};

/* 3台设备：左半屏 + 右侧上下分屏 */
struct video_window disp_win_3[3] = {
    {
        .left   = 0,
        .top    = 0,
        .width  = LCD_W / 2,
        .height = LCD_H / 2,
        .combine = 1,
    },
    {
        .left   = LCD_W / 2,
        .top    = 0,
        .width  = LCD_W / 2,
        .height = LCD_H / 2,
        .combine = 1,
    },
    {
        .left   = LCD_W / 4,
        .top    = LCD_H / 2,
        .width  = LCD_W / 2,
        .height = LCD_H / 2,
        .combine = 1,
    },
};

/* 4台设备：四宫格 */
struct video_window disp_win_4[4] = {
    {
        .left   = 0,
        .top    = 0,
        .width  = LCD_W / 2,
        .height = LCD_H / 2,
        .combine = 1,
    },
    {
        .left   = LCD_W / 2,
        .top    = 0,
        .width  = LCD_W / 2,
        .height = LCD_H / 2,
        .combine = 1,
    },
    {
        .left   = 0,
        .top    = LCD_H / 2,
        .width  = LCD_W / 2,
        .height = LCD_H / 2,
        .combine = 1,
    },
    {
        .left   = LCD_W / 2,
        .top    = LCD_H / 2,
        .width  = LCD_W / 2,
        .height = LCD_H / 2,
        .combine = 1,
    },
};


//双向视频窗口切换
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
    VIDEO_TYPE_PACKET = 10,
    AUDIO_TYPE_PACKET,
    CONTINUE_PARSE_TYPE_PACKET,
    UNKNOW_TYPE_PACKET,
};

enum {
    Q_USER_EXIT = 1,
    Q_USER_START_REC,
    Q_USER_STOP_REC,
    Q_USER_SWITCH_VIDEO_WIN,
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
    int src_width;
    int src_height;

    //lbuf
    struct lbuff_head *lbuf_handle;
    u8 *lbuf_ptr;

    //thread
    int task_pid;
    char task_name[64];

    //rec
    avi_t *rec_out_fd;
};

static int check_local_video_is_running(void);

static int ctp_recv_sock_cb(enum sock_api_msg_type type, void *priv)
{
    if (ctp_rt_recv_task_exit) {
        printf("cpt recv cb func exit\n");
        return -1;
    }
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

static int deal_recv_packet(u8 *recv_buf, int recv_len, u32 ip_addr)
{
    struct rt_stream_dev *rt_dev;
    int msg[2];

    os_mutex_pend(&recv_mutex, 0);
    list_for_each_entry(rt_dev, &recv_dev_list_head, recv_entry) {
        if (rt_dev->ip_addr == ip_addr) {
            struct lbuf_data_head *lbuf_data = lbuf_alloc(rt_dev->lbuf_handle, recv_len);
            if (!lbuf_data) {
                printf("rt lbuf_alloc err ip:%d \n", ip_addr);
                lbuf_clear(rt_dev->lbuf_handle);
                os_mutex_post(&recv_mutex);
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
    u32 seq = 0;
    int frm_head_size = sizeof(struct frm_head);

    data_buf = malloc(AUDIO_RX_ENC_FRAME_SIZE + frm_head_size);
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
    dest_addr.sin_addr.s_addr = inet_addr(UDP_MULTICAST_ADDR);

    while (1) {
        if (ctp_rt_send_task_exit) {
            printf("ctp_rt_send_task exit \n");
            break;
        }

        data_size = bbm_audio_enc_get_data(data_buf + frm_head_size);
        if (data_size <= 0) {
            continue;
        }

        struct frm_head *frame_head = (struct frm_head *)data_buf;
        memset(frame_head, 0x00, frm_head_size);
        frame_head->offset = 0;
        frame_head->frm_sz = data_size;
        frame_head->type |= LAST_FREG_MAKER;
        frame_head->type |=  1;  //audio=1
        frame_head->timestamp = 0;
        frame_head->seq = seq++;
        frame_head->payload_size = data_size;

        ret = sock_sendto(ctp_rt_send_sockfd, data_buf, data_size + frm_head_size, 0, &dest_addr, sizeof(dest_addr));
        if (ret < 0) {
            printf("rt audio sock send err\n");
            continue;
        }
    }

exit:
    if (data_buf) {
        free(data_buf);
    }
    bbm_audio_enc_exit();
}

static int jpeg_get_size(u8 *stream, int len, int *width, int *height)
{
    u8 marker;
    int chunk_len;

    if ((stream[0] != 0xFF) || (stream[1] != 0xD8)) {
        printf("not jpg picture.");
        return -1;
    }

    stream += 2;

    while (1) {
        if (*stream++ != 0xFF) {
            return -2;
        }

        while (*stream == 0xFF) {
            stream++;
        }

        marker = *stream++;
        chunk_len = (u16)(stream[0] << 8) | stream[1];

        if (marker == 0xC0) {
            *height = (u16)((stream[3] << 8) | stream[4]);
            *width  = (u16)((stream[5] << 8) | stream[6]);
            break;
        }
        stream += chunk_len;
    }
    return 0;
}


static void rt_stream_dev_task(void *priv)
{
    struct rt_stream_dev *rt_dev = priv;
    struct parse_info parse_info = {0};

    int res;
    int msg[8];
    int ret;
    int time;
    int fps = 0;
    int abr = 0;
    int total = 0;
    char text[128];

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

                if ((timer_get_ms() - time) >= 1000) {
                    //调试信息
                    sprintf(text, "total:%d abr:%d  fps:%d", total / 1024, abr / 1024, fps);
                    time = timer_get_ms();
                    fps = 0;
                    abr = 0;
                    total = 0;

                    printf("%s \n", text);
                    //debug
                    /* post_stream_msg_to_ui("show stream info", text); */
                }
                total += lbuf_data->len;

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

                    int jpeg_width = 0, jpeg_height = 0;
                    ret = jpeg_get_size(jpeg_buf, jpeg_len, &jpeg_width, &jpeg_height);
                    if (ret || jpeg_width != rt_dev->src_width || jpeg_height != rt_dev->src_height) {
                        printf("jpeg fmt not match err:%d w:%d h:%d", ret, jpeg_width, jpeg_height);
                        continue;
                    }


                    fps++;
                    abr += jpeg_len;
                    if (rt_dev->pipe_core) {
                        bbm_pipe_disp_one_frame(rt_dev->pipe_core, jpeg_buf, jpeg_len);
                    }

                    if (rt_dev->rec_out_fd) {
                        AVI_write_frame(rt_dev->rec_out_fd, jpeg_buf, jpeg_len, 1);
                    }

                    /* printf("v:%d\n",jpeg_len); */
                } else if (parse_info.packet_type == AUDIO_TYPE_PACKET) {
                    /* int lev = calculate_db_level(parse_info.data_buf,parse_info.data_len); */
                    /* printf("lv:%d \n",lev); */
                    bbm_audio_dec_one_frame(parse_info.data_buf, parse_info.data_len);
                    if (rt_dev->rec_out_fd) {
                        AVI_write_audio(rt_dev->rec_out_fd, parse_info.data_buf, parse_info.data_len);
                    }
                    /* printf("a:%d\n",parse_info.data_len); */
                } else {
                    //continue parse
                    /* printf("c\n"); */
                }
                break;
            case Q_USER:
                if (msg[1] == Q_USER_EXIT) {
                    goto exit;
                } else if (msg[1] == Q_USER_START_REC) {
                    if (rt_dev->rec_out_fd) {
                        printf("rx rec is recording \n");
                        continue;
                    }
                    char *filename = "storage/sd0/C/DCIM/1/VID_****.AVI";
                    avi_t *out_fd = AVI_open_output_file(filename);

                    if (out_fd == NULL) {
                        printf("rx rec open file error\n");
                        continue;
                    }

                    AVI_set_video(out_fd, rt_dev->src_width, rt_dev->src_height, 25, "MJPG");
                    AVI_set_audio(out_fd, 1, 8000, 16, WAVE_FORMAT_PCM, 0);

                    rt_dev->rec_out_fd = out_fd;
                    printf("rx rec start \n");
                } else if (msg[1] == Q_USER_STOP_REC) {
                    if (rt_dev->rec_out_fd) {
                        AVI_close(rt_dev->rec_out_fd);
                        rt_dev->rec_out_fd = NULL;
                        printf("stop rec \n");
                    } else {
                        printf("rx rec not recording \n");
                    }
                } else if (msg[1] == Q_USER_SWITCH_VIDEO_WIN) {
                    printf("switch video win \n");
                    struct video_window *win =  &disp_win[curr_win_mode][1];
                    if (win) {
                        printf("remote win left:%d top:%d width:%d height:%d \n",
                               win->left, win->top, win->width, win->height);
                    }

                    bbm_video_pipe_exit(&rt_dev->pipe_core);
                    rt_dev->pipe_core = NULL;

                    if (win && win->width && win->height) {
                        int width = rt_dev->src_width;
                        int height = rt_dev->src_height;
                        struct video_format f = {0};
                        struct video_window *local_win = &disp_win[curr_win_mode][0];
                        int need_post_sem = 1;

                        //判断是否是小窗, 如果是小窗需要等大窗口先创建,否者小窗口会被大窗口覆盖
                        int local_video_is_running = check_local_video_is_running();
                        if (win->width < local_win->width && local_video_is_running) {
                            printf("remote need wait big win create \n");
                            if (os_sem_pend(&wait_big_win_create, 50) != 0) {
                                printf("wait big win create err \n");
                            }
                            need_post_sem = 0;
                        } else if (win->width > local_win->width && local_win->width != 0 && local_video_is_running) {

                            need_post_sem = 1;

                        } else {
                            need_post_sem = 0;
                        }

                        bbm_video_pipe_init_format(&f, win, width, height, NULL);
                        bbm_video_pipe_init(&rt_dev->pipe_core, &f);

                        if (need_post_sem) {
                            os_sem_post(&wait_big_win_create);
                        }

                    } else {
                        continue;
                    }


                } else {
                    printf("unknow user msg:%d \n", msg[1]);
                }

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
    if (rt_dev->rec_out_fd) {
        AVI_close(rt_dev->rec_out_fd);
        rt_dev->rec_out_fd = NULL;
    }
    printf("rt_stream_dev_task exit\n");
}

static int bbm_rt_send_only_audio_init(void)
{
    int ret;
    if (++send_ref_count > 1) {
        printf("-----send audio ref[%d], do not init----\n", send_ref_count);
        return 0;
    }

    printf("-----ctp_rt_audio_send_init----\n");

    ctp_rt_send_sockfd = sock_reg(AF_INET, SOCK_DGRAM, 0, NULL, NULL);
    if (ctp_rt_send_sockfd == NULL) {
        printf("sock_reg err\n");
        return -1;
    }

    thread_fork("thread_socket_send", 11, 2048, 2048, &ctp_rt_send_task_pid, ctp_rt_send_task, NULL);

    return 0;
}

static int bbm_rt_send_only_audio_exit(void)
{
    if (--send_ref_count > 0) {
        printf("-----send audio ref[%d], do not exit----\n", send_ref_count);
        return 0;
    }

    printf("-----ctp_rt_audio_send_exit----\n");

    ctp_rt_send_task_exit = 1;
    thread_kill(&ctp_rt_send_task_pid, KILL_WAIT);
    ctp_rt_send_task_exit = 0;

    sock_unreg(ctp_rt_send_sockfd);

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
        break;
    case VIDEO_SERVER_NET_ERR:
        printf("VIDEO_SERVER_NET_ERR\n");
        break;
    default :
        printf("unknow rec server cmd %x , %x!\n", argv[0], (int)priv);
        break;
    }
}

static int bbm_rt_send_stream_init(void)
{
    if (++send_ref_count > 1) {
        printf("-----send stream ref > 1, do not init----\n");
        return 0;
    }

    printf("-----ctp_rt_send_stream_init----\n");
    int ret;
    union video_req req = {0};
    struct video_text_osd text_osd;
    struct video_graph_osd graph_osd;
    u16 max_one_line_strnum;
    u16 osd_line_num;
    u16 osd_max_heigh;

    static u8 osd_buf[64];
    char dev_name[10];

    sprintf(dev_name, "video%d.%d", default_rt_config.id, default_rt_config.sub_id);

    video_server = server_open("video_server", dev_name);
    if (!video_server) {
        printf("video_server open err \n");
        goto err;
    }
    server_register_event_handler(video_server, NULL, rec_dev_server_event_handler);

    stream_video_buf = malloc(STREAM_VIDEO_BUF_SIZE);
    if (!stream_video_buf) {
        printf("malloc video rt buf err\n");
        goto err;
    }
    req.rec.buf = stream_video_buf;
    req.rec.buf_len = STREAM_VIDEO_BUF_SIZE;

    req.rec.channel     = default_rt_config.sub_id;
    req.rec.state       = VIDEO_STATE_START;
    req.rec.quality     = VIDEO_MID_Q;

    req.rec.width       = default_rt_config.width;
    req.rec.height      = default_rt_config.height;
    req.rec.fps         = 0;
    req.rec.real_fps    = default_rt_config.fps;
    req.rec.abr_kbps    = default_rt_config.abr_kbps;

    req.rec.format  = USER_VIDEO_FMT_AVI;
    req.rec.online  = 1;
    req.rec.cycle_time = 5 * 60;
    req.rec.audio.aud_interval_size = 2 * 640;
    req.rec.camera_type = VIDEO_CAMERA_NORMAL;
    req.rec.audio.sample_rate = VIDEO_REC_AUDIO_SAMPLE_RATE;
    req.rec.audio.channel   = 1;
    req.rec.audio.volume    = 100;

    stream_audio_buf = malloc(STREAM_AUDIO_BUF_SIZE);
    if (!stream_audio_buf) {
        printf("malloc audio rt buf err \n");
        goto err;
    }
    req.rec.audio.buf = stream_audio_buf;
    req.rec.audio.buf_len = STREAM_AUDIO_BUF_SIZE;

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

    struct net_stream_info s_info = {0};
    s_info.sample_rate = req.rec.audio.sample_rate;
    s_info.fps = default_rt_config.fps;
    s_info.abr_kbps = default_rt_config.abr_kbps;

    char net_path[128];
    sprintf(net_path, "udp://%s:%d", UDP_MULTICAST_ADDR, CTP_RT_SEND_PORT);
    printf("\n @@@@@@ path = %s\n", net_path);

    req.rec.target = VIDEO_TO_OUT;
    req.rec.out.path = net_path;
    req.rec.out.arg  = &s_info;
    req.rec.out.open = stream_open;
    req.rec.out.send = stream_write;
    req.rec.out.close = stream_close;

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
    /* req.rec.text_osd = &text_osd; */

    ret = server_request(video_server, VIDEO_REQ_REC, &req);
    if (ret) {
        puts("\n\n\nstart rec err\n\n\n");
        goto err;
    }

    req.rec.state = VIDEO_STATE_RESET_BITS_RATE;
    server_request(video_server, VIDEO_REQ_REC, &req);

    return 0;

err:
    if (video_server) {
        server_close(video_server);
        video_server = NULL;
    }
    if (stream_video_buf) {
        free(stream_video_buf);
        stream_video_buf = NULL;
    }
    if (stream_audio_buf) {
        free(stream_audio_buf);
        stream_audio_buf = NULL;
    }
    --send_ref_count;
    return -1;
}

static int bbm_rt_send_stream_exit(void)
{
    if (--send_ref_count > 0) {
        printf("-----send stream ref > 0, do not exit----\n");
        return 0;
    }

    printf("-----ctp_rt_send_stream_exit----\n");

    if (video_server) {
        union video_req req = {0};
        req.rec.channel = default_rt_config.sub_id;
        req.rec.state = VIDEO_STATE_STOP;
        server_request(video_server, VIDEO_REQ_REC, &req);
        server_close(video_server);
        video_server = NULL;
    }

    if (stream_video_buf) {
        free(stream_video_buf);
        stream_video_buf = NULL;
    }
    if (stream_audio_buf) {
        free(stream_audio_buf);
        stream_audio_buf = NULL;
    }

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

    ctp_rt_recv_sockfd = sock_reg(AF_INET, SOCK_DGRAM, 0, ctp_recv_sock_cb, NULL);
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

static int bbm_rt_dev_init(u32 ip_addr, struct video_window *win, int src_w, int src_h)
{
    int ret;
    u8 audio_dec_init = 0;
    u8 send_init = 0;

    printf("---bbm_rt_dev_init---\n");

    struct rt_stream_dev *rt_dev = malloc(sizeof(struct rt_stream_dev));
    if (!rt_dev) {
        printf("rt_stream_dev malloc err \n");
        goto err;
    }
    memset(rt_dev, 0x00, sizeof(struct rt_stream_dev));

    //param
    rt_dev->ip_addr = ip_addr;

#if RX_AUDIO_SEND_ENABLE
    bbm_rt_send_only_audio_init();
#endif
#if RX_STREAM_SEND_ENABLE
    bbm_rt_send_stream_init();
#endif
    send_init = 1;

    //video pipe
    if (win && win->width && win->height) {
        struct video_format f = {0};
        struct video_window *local_win = &disp_win[curr_win_mode][0];
        //判断是否是小窗, 如果是小窗需要等大窗口先创建,否者小窗口会被大窗口覆盖
        int local_video_is_running = check_local_video_is_running();
        if (win->width < local_win->width && local_video_is_running) {
            printf("remote need wait big win create \n");
            if (os_sem_pend(&wait_big_win_create, 50) != 0) {
                printf("wait big win create err \n");
            }
        }
        bbm_video_pipe_init_format(&f, win, src_w, src_h, NULL);
        ret = bbm_video_pipe_init(&rt_dev->pipe_core, &f);
        if (ret) {
            goto err;
        }
    }
    rt_dev->src_width = src_w;
    rt_dev->src_height = src_h;

    //lbuf
    rt_dev->lbuf_ptr = malloc(RT_LBUF_SIZE);
    if (rt_dev->lbuf_ptr == NULL) {
        printf("lbuf malloc buf err");
        goto err;
    }
    rt_dev->lbuf_handle = lbuf_init(rt_dev->lbuf_ptr, RT_LBUF_SIZE, 4, sizeof(struct lbuf_data_head));

    //thread
    sprintf(rt_dev->task_name, "rt_dev_task%d", rt_dev_task_name_cnt++);
    thread_fork(rt_dev->task_name, 11, 2048, 2048, &rt_dev->task_pid, rt_stream_dev_task, rt_dev);

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
        if (send_init) {
#if RX_AUDIO_SEND_ENABLE
            bbm_rt_send_only_audio_exit();
#endif
#if RX_STREAM_SEND_ENABLE
            bbm_rt_send_stream_exit();
#endif
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
    msg = Q_USER_EXIT;
    os_taskq_post_type(rt_dev->task_name, Q_USER, 1, &msg);
    thread_kill(&rt_dev->task_pid, KILL_WAIT);

    bbm_video_pipe_exit(&rt_dev->pipe_core);

    bbm_audio_dec_exit();

    if (rt_dev->lbuf_ptr) {
        free(rt_dev->lbuf_ptr);
    }

    free(rt_dev);

#if RX_AUDIO_SEND_ENABLE
    bbm_rt_send_only_audio_exit();
#endif
#if RX_STREAM_SEND_ENABLE
    bbm_rt_send_stream_exit();
#endif

    return 0;
}

//reconnect
int bbm_ctp_send_rt_start(void *priv)
{
    int ret;
    struct bbm_client_hdl *bbm_hdl = priv;
    void *ctp_cli_hdl = bbm_hdl->ctp_cli_hdl;

    char topic_3[32];
    char content_3[256];
    snprintf(topic_3, sizeof(topic_3), OPEN_RT_TOPIC);
    snprintf(content_3, sizeof(content_3), OPEN_RT_CONTENT,
             bbm_hdl->rt_config.abr_kbps, bbm_hdl->rt_config.width,
             bbm_hdl->rt_config.fps, bbm_hdl->rt_config.height,
             bbm_hdl->rt_config.id, bbm_hdl->rt_config.sub_id);
    ret = ctp_cli_send(ctp_cli_hdl, topic_3, content_3);

    if (ret) {
        printf("ctp_cli_send :%s err\n", topic_3);
        return -1;
    }

    return 0;
}

int bbm_ctp_rt_start(void *priv, struct video_window *win)
{
    int ret;
    char topic_3[32];
    char content_3[256];
    struct bbm_client_hdl *bbm_hdl = priv;
    void *ctp_cli_hdl = bbm_hdl->ctp_cli_hdl;

    memcpy(&bbm_hdl->rt_config, &default_rt_config, sizeof(default_rt_config));

#if BBM_LOCAL_CAMERA_DISP_ENABLE
    win = &disp_win[curr_win_mode][1];
#else
    //半屏降低摄像头分辨率分辨率
    if (win != &disp_win_1[0]) {
        bbm_hdl->rt_config.width = win->width;
        bbm_hdl->rt_config.height = win->height;
        /* bbm_hdl->rt_config.width = 192; */
        /* bbm_hdl->rt_config.height = 160; */
        bbm_hdl->rt_config.abr_kbps = 1000;
    }
#endif

    snprintf(topic_3, sizeof(topic_3), OPEN_RT_TOPIC);
    snprintf(content_3, sizeof(content_3), OPEN_RT_CONTENT,
             bbm_hdl->rt_config.abr_kbps, bbm_hdl->rt_config.width,
             bbm_hdl->rt_config.fps, bbm_hdl->rt_config.height,
             bbm_hdl->rt_config.id, bbm_hdl->rt_config.sub_id);

    ret = ctp_cli_send(ctp_cli_hdl, topic_3, content_3);
    if (ret) {
        printf("ctp_cli_send :%s err\n", topic_3);
        return -1;
    }

    ret = bbm_rt_dev_init(bbm_hdl->ip_addr, win, bbm_hdl->rt_config.width, bbm_hdl->rt_config.height);
    if (ret) {
        return -1;
    }


    return 0;
}

int bbm_ctp_rt_stop(void *priv)
{
    int ret;
    char topic_3[32];
    char content_3[256];

    struct bbm_client_hdl *bbm_hdl = priv;
    void *ctp_cli_hdl = bbm_hdl->ctp_cli_hdl;

    snprintf(topic_3, sizeof(topic_3), CLOSE_RT_TOPIC);
    snprintf(content_3, sizeof(content_3), CLOSE_RT_CONTENT,
             bbm_hdl->rt_config.id, bbm_hdl->rt_config.sub_id);

    bbm_rt_dev_exit(bbm_hdl->ip_addr);

    if (bbm_hdl->rx_is_recording) {
        bbm_hdl->rx_is_recording = 0;
    }

    //发送停止实时流命令
    ret = ctp_cli_send(ctp_cli_hdl, topic_3, content_3);
    if (ret) {
        printf("ctp_cli_send :%s err\n", topic_3);
    }

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
    rt_stream_init = 1;


#if BBM_LOCAL_CAMERA_DISP_ENABLE
    os_sem_create(&wait_big_win_create, 0);
    local_video_disp_start();
#endif


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


    rt_stream_init = 0;

#if BBM_LOCAL_CAMERA_DISP_ENABLE
    os_sem_del(&wait_big_win_create, OS_DEL_ALWAYS);
    local_video_disp_stop();
#endif

    return 0;
}


static int cal_source_crop(struct video_source_crop *crop, int factor, int src_width, int src_height)
{
    printf("zoom factor:%d \n", factor);
    //限制变焦倍数
    if (factor < 1 || factor > 4) {
        printf("zoom factor:%d is invalid \n", factor);
        return -1;
    }

    crop->width = src_width / factor;
    crop->height = src_height / factor;

    //硬件imc最大放大倍数不能超过4
    if (crop->width < (LCD_W / 4)) {
        crop->width = LCD_W / 4;
        crop->width = (crop->width + 15) & ~15;
    }
    if (crop->height < (LCD_H / 4)) {
        crop->height = LCD_H / 4;
        crop->height = (crop->height + 15) & ~15;
    }

    //居中变焦
    crop->x_offset = (src_width - crop->width) / 2;
    crop->y_offset = (src_height - crop->height) / 2;

    return 0;
}

//factor:变焦倍数
int bbm_rt_stream_digital_zomm(void *priv, int factor)
{
    int ret;
    struct video_source_crop crop;

    struct bbm_client_hdl *bbm_hdl = priv;
    struct rt_stream_dev *rt_dev;
    u8 find = 0;
    int src_w = bbm_hdl->rt_config.width;
    int src_h = bbm_hdl->rt_config.height;

    os_mutex_pend(&recv_mutex, 0);
    list_for_each_entry(rt_dev, &recv_dev_list_head, recv_entry) {
        if (rt_dev->ip_addr == bbm_hdl->ip_addr) {
            find = 1;
            break;
        }
    }
    os_mutex_post(&recv_mutex);

    if (!find) {
        printf("not found rt dev\n");
        return -1;
    }

    ret = cal_source_crop(&crop, factor, src_w, src_h);
    if (ret) {
        return -1;
    }

    return bbm_video_pipe_set_zoom(rt_dev->pipe_core, &crop);
}

int bbm_ctp_rec_start(void *priv)
{
    int ret;
    char topic_3[32];
    char content_3[256];

    struct bbm_client_hdl *bbm_hdl = priv;
    void *ctp_cli_hdl = bbm_hdl->ctp_cli_hdl;

    memcpy(&bbm_hdl->rec_config, &default_rec_config, sizeof(default_rec_config));

    snprintf(topic_3, sizeof(topic_3), OPEN_REC_TOPIC);
    snprintf(content_3, sizeof(content_3), OPEN_REC_CONTENT,
             bbm_hdl->rec_config.width, bbm_hdl->rec_config.fps,
             bbm_hdl->rec_config.height, bbm_hdl->rec_config.id,
             bbm_hdl->rec_config.sub_id, bbm_hdl->rec_config.abr_kbps,
             bbm_hdl->rec_config.cycle_time);

    ret = ctp_cli_send(ctp_cli_hdl, topic_3, content_3);
    if (ret) {
        printf("ctp_cli_send :%s err\n", topic_3);
        return -1;
    }

    return 0;
}

int bbm_ctp_rec_stop(void *priv)
{
    int ret;
    char topic_3[32];
    char content_3[256];

    struct bbm_client_hdl *bbm_hdl = priv;
    void *ctp_cli_hdl = bbm_hdl->ctp_cli_hdl;

    snprintf(topic_3, sizeof(topic_3), CLOSE_REC_TOPIC);
    snprintf(content_3, sizeof(content_3), CLOSE_REC_CONTENT,
             bbm_hdl->rec_config.id, bbm_hdl->rec_config.sub_id);

    ret = ctp_cli_send(ctp_cli_hdl, topic_3, content_3);
    if (ret) {
        printf("ctp_cli_send :%s err\n", topic_3);
        return -1;
    }

    return 0;
}

int bbm_ctp_take_photo(void *priv)
{
    int ret;
    char topic_3[32];
    char content_3[128];

    struct bbm_client_hdl *bbm_hdl = priv;
    void *ctp_cli_hdl = bbm_hdl->ctp_cli_hdl;

    snprintf(topic_3, sizeof(topic_3), TAKE_PHOTO_TOPIC);
    snprintf(content_3, sizeof(content_3), TAKE_PHOTO_CONTENT,
             bbm_hdl->rt_config.id, bbm_hdl->rt_config.sub_id);

    ret = ctp_cli_send(ctp_cli_hdl, topic_3, content_3);
    if (ret) {
        printf("ctp_cli_send :%s err\n", topic_3);
        return -1;
    }

    return 0;
}

int bbm_rx_rec_start(void *priv)
{
    struct rt_stream_dev *rt_dev;

    struct bbm_client_hdl *bbm_hdl = priv;

    os_mutex_pend(&recv_mutex, 0);
    list_for_each_entry(rt_dev, &recv_dev_list_head, recv_entry) {
        if (rt_dev->ip_addr == bbm_hdl->ip_addr) {
            int msg = Q_USER_START_REC;
            os_taskq_post_type(rt_dev->task_name, Q_USER, 1, &msg);
        }
    }
    os_mutex_post(&recv_mutex);

    return 0;

}

int bbm_rx_rec_stop(void *priv)
{
    int msg[2];
    struct rt_stream_dev *rt_dev;

    struct bbm_client_hdl *bbm_hdl = priv;

    os_mutex_pend(&recv_mutex, 0);
    list_for_each_entry(rt_dev, &recv_dev_list_head, recv_entry) {
        if (rt_dev->ip_addr == bbm_hdl->ip_addr) {
            int msg = Q_USER_STOP_REC;
            os_taskq_post_type(rt_dev->task_name, Q_USER, 1, &msg);
        }
    }
    os_mutex_post(&recv_mutex);

    return 0;
}

int bbm_ctp_set_abr(void *priv, int abr_val)
{
    int ret;
    char topic_3[32];
    char content_3[128];
    struct bbm_client_hdl *bbm_hdl = priv;
    void *ctp_cli_hdl = bbm_hdl->ctp_cli_hdl;

    //设置实时流码率
    snprintf(topic_3, sizeof(topic_3), SET_ABR_TOPIC);
    snprintf(content_3, sizeof(content_3), SET_ABR_CONTENT,
             abr_val, bbm_hdl->rt_config.id, bbm_hdl->rt_config.sub_id);

    ret = ctp_cli_send(ctp_cli_hdl, topic_3, content_3);
    if (ret) {
        printf("ctp_cli_send :%s err\n", topic_3);
        return -1;
    }

    bbm_hdl->rt_config.abr_kbps = abr_val;

    return 0;
}

static int check_local_video_is_running(void)
{
#if BBM_LOCAL_CAMERA_DISP_ENABLE
    return 1;
#else
    return 0;
#endif
}


static int local_video_disp_start(void)
{
    int camera_src_w = 640;
    int camera_src_h = 480;
    int camera_src_id = 1;
    int need_post_sem = 0;

    struct video_format f = {0};
    struct video_window *win = &disp_win[curr_win_mode][0];
    if (!win) {
        printf("err win ptr !\n");
        return -1;
    }

    printf("local win left:%d top:%d width:%d height:%d \n",
           win->left, win->top, win->width, win->height);

    if (win->width == 0 || win->height == 0) {
        return 0;
    }

    struct video_window *remote_win = &disp_win[curr_win_mode][1];
    if (win->width < remote_win->width) {
        printf("local need wait big win create \n");
        if (os_sem_pend(&wait_big_win_create, 50) != 0) {
            printf("wait big win create err \n");
        }
        need_post_sem = 0;
    } else if (win->width > remote_win->width && remote_win->width != 0) {

        need_post_sem = 1;

    } else {
        need_post_sem = 0;
    }

    bbm_video_pipe_init_format(&f, win, camera_src_w, camera_src_h, NULL);
    if (bbm_video_pipe_disp_init(&local_pipe_core, &f, camera_src_id)) {
        printf("bbm tx disp init err \n");
        return -1;
    }

    if (need_post_sem) {
        os_sem_post(&wait_big_win_create);
    }
    return 0;
}

static int local_video_disp_stop(void)
{
    return bbm_video_pipe_exit(&local_pipe_core);
}


//只支持一台设备连接
int bbm_switch_video_win(void *priv)
{
#if BBM_LOCAL_CAMERA_DISP_ENABLE
    int msg[2];
    curr_win_mode = (curr_win_mode + 1) % MAX_WIN_MODE_NUM;
    printf("switch disp win curr win :%d \n", curr_win_mode);

    struct rt_stream_dev *rt_dev;

    struct bbm_client_hdl *bbm_hdl = priv;

    os_mutex_pend(&recv_mutex, 0);
    list_for_each_entry(rt_dev, &recv_dev_list_head, recv_entry) {
        if (rt_dev->ip_addr == bbm_hdl->ip_addr) {
            int msg = Q_USER_SWITCH_VIDEO_WIN;
            os_taskq_post_type(rt_dev->task_name, Q_USER, 1, &msg);
        }
    }
    os_mutex_post(&recv_mutex);

    local_video_disp_stop();
    local_video_disp_start();
#endif
    return 0;
}






