#include "system/includes.h"
#include "baby_monitor.h"
#include "sock_api/sock_api.h"
#include "server/video_dec_server.h"
#include "server/audio_server.h"
#include "lcd_config.h"
#include "rt_stream_pkg.h"


#define FILE_PLAY_PORT          2223    //视频回放端口
#define CTP_RECV_BUF_MAX_LEN    200 * 1024 //接收缓存
#define VIDEO_DEC_BUF_MAX_SIZE       512    //解码服务缓存,单位Kb,申请大小不能小于一帧图像的大小
#define AUDIO_DEC_BUF_MAX_LEN        2 * 1024   //解码音频缓存

#define CTP_FILE_PLAY_TASK_NAME         "thread_socket_file_play"

static struct server *video_dec_server;
static struct server *audio_dec_server;
static cbuffer_t audio_dec_save_cbuf;
static u8 *audio_dec_buf;

static int vfs_audio_dec_fread(void *file, void *data, u32 len)
{
    u32 rlen = 0;

    do {
        rlen = cbuf_read(&audio_dec_save_cbuf, data, len);
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

static int video_dec_init(void)
{
    struct video_dec_arg arg = {0};
    arg.dev_name = "video_dec";
    arg.video_buf_size = VIDEO_DEC_BUF_MAX_SIZE;

    video_dec_server = server_open("video_dec_server", &arg);
    if (!video_dec_server) {
        printf("open video_dec_server fail");
        return -1;
    }

    return 0;
}

static int video_dec_exit(void)
{
    union video_dec_req dec_req = {0};

    if (video_dec_server) {
        server_request(video_dec_server, VIDEO_REQ_DEC_STOP, &dec_req);

        server_close(video_dec_server);
        video_dec_server = NULL;
    }

    return 0;
}


static int video_dec_one_frame(u8 *buf, u32 size)
{
    if (!video_dec_server) {
        printf("please open video_dec server first\n");
        return -1;
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

    return server_request(video_dec_server, VIDEO_REQ_DEC_IMAGE, &dec_req);
}

static int audio_dec_init(void)
{
    union audio_req req = {0};
    int err;

    audio_dec_server = server_open("audio_server", "dec");
    if (!audio_dec_server) {
        printf("open audio_dec_server fail");
        goto __err;
    }

    audio_dec_buf = (u8 *)malloc(AUDIO_DEC_BUF_MAX_LEN);
    if (audio_dec_buf == NULL) {
        printf("audio_dec_buf malloc fail");
        goto __err;

    }
    cbuf_init(&audio_dec_save_cbuf, audio_dec_buf, AUDIO_DEC_BUF_MAX_LEN);

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

    err = server_request(audio_dec_server, AUDIO_REQ_DEC, &req);
    if (err) {
        printf("audio server req open err\n");
        goto __err;
    }

    req.dec.cmd = AUDIO_DEC_START;
    err = server_request(audio_dec_server, AUDIO_REQ_DEC, &req);
    if (err) {
        printf("audio server req start err\n");
        goto __err;
    }

    return 0;

__err:
    audio_dec_exit();
    return -1;
}


static int audio_dec_exit(void)
{
    union audio_req req = {0};

    if (audio_dec_server) {
        req.dec.cmd = AUDIO_DEC_STOP;
        server_request(audio_dec_server, AUDIO_REQ_DEC, &req);

        server_close(audio_dec_server);
        audio_dec_server = NULL;
    }
    if (audio_dec_buf) {
        free(audio_dec_buf);
        audio_dec_buf = NULL;
    }

    return 0;
}

static int audio_dec_write_cbuf(u8 *buf, u32 size)
{
    u32 cur_size;
    cur_size =  cbuf_get_data_size(&audio_dec_save_cbuf);

    if (cur_size + size >= AUDIO_DEC_BUF_MAX_LEN) {
        cbuf_clear(&audio_dec_save_cbuf);
    }

    cbuf_write(&audio_dec_save_cbuf, buf, size);

    return 0;
}

static int audio_dec_one_frame(u8 *buf, u32 size)
{
    audio_dec_write_cbuf(buf, size);

    return 0;
}


static void ctp_file_play_task(void *priv)
{
    int ret;
    struct sockaddr_in dest;
    void *ctp_file_play_sockfd;

    struct bbm_client_hdl *bbm_hdl = priv;
    struct sockaddr_in *sockaddr = ctp_cli_get_hdl_addr(bbm_hdl->ctp_cli_hdl);
    u32 ip_addr = sockaddr->sin_addr.s_addr;

    int recv_len = 0;
    u8 *recv_buf = malloc(CTP_RECV_BUF_MAX_LEN);
    if (!recv_buf) {
        printf("ctp recv malloc recv buff err \n");
        goto exit;
    }

    ctp_file_play_sockfd = sock_reg(AF_INET, SOCK_STREAM, 0, NULL, NULL);
    if (ctp_file_play_sockfd == NULL) {
        printf("sock_reg err\n");
        goto exit;
    }

    dest.sin_family = AF_INET;
    dest.sin_addr.s_addr = ip_addr;
    dest.sin_port = htons(FILE_PLAY_PORT);
    sock_set_connect_to(ctp_file_play_sockfd, 1);
    if (0 != sock_connect(ctp_file_play_sockfd, (struct sockaddr *)&dest, sizeof(struct sockaddr_in))) {
        printf("sock_connect fail.\n");
        goto exit;
    }

    sock_set_recv_timeout(ctp_file_play_sockfd, 100);

    int video_frame_cnt = 0;
    int video_total_time = 0;
    int video_fps = 0;
    int video_total_frame = 0;
    int buf_len = 0;

    //重置播放进度条
    post_video_play_msg_to_ui("play_time", 0);

    //更改UI图标,播放中
    post_video_play_msg_to_ui("play_control", 1);



    while (1) {
        if (bbm_hdl->ctp_file_play_task_exit) {
            goto exit;
        }

        recv_len = sock_recvfrom(ctp_file_play_sockfd, recv_buf + buf_len, CTP_RECV_BUF_MAX_LEN - buf_len, 0, NULL, NULL);
        if (recv_len <= 0) {
            printf("video play recv err: %d \n", recv_len);
            continue;
        }
        buf_len += recv_len;

        while (buf_len >= sizeof(struct frm_head)) {
            struct frm_head *frame_head = (struct frm_head *)recv_buf;
            // 检查是否有完整的帧
            int frame_size = sizeof(struct frm_head) + frame_head->frm_sz;
            if (buf_len < frame_size) {
                break; // 不完整帧，等待更多数据
            }
            // 处理帧数据
            char *frame_data = recv_buf + sizeof(struct frm_head);
            switch (frame_head->type) {
            case MEDIA_INFO_TYPE:
                printf("media info type\n");
                struct media_info *media = (struct media_info *)frame_data;
                video_total_time = media->dur_time;
                video_fps = media->fps;
                video_total_frame = video_total_time * video_fps;
                video_frame_cnt = 0;
                break;
            case DATE_TIME_TYPE:
                /* printf("time type\n"); */
                break;
            case JPEG_TYPE_VIDEO:
                video_dec_one_frame(frame_data, frame_head->frm_sz);
                video_frame_cnt++;

                //计算进度条百分比(0-100),1s计算一次
                if (!(video_frame_cnt % video_fps)) {
                    int percent = (float)video_frame_cnt * 100 / video_total_frame;
                    post_video_play_msg_to_ui("play_time", percent);
                }
                break;
            case PCM_TYPE_AUDIO:
                audio_dec_one_frame(frame_data, frame_head->frm_sz);
                break;
            case PLAY_OVER_TYPE | LAST_FREG_MAKER:
            case PLAY_OVER_TYPE:
                printf("recv end type %d \n", frame_head->type);
                //更改UI图标,停止
                post_video_play_msg_to_ui("play_control", 0);
                goto exit;
            default:
                printf("default frame type :%d  \n", frame_head->type);
                goto exit;
            }
            // 移动缓冲区内容，移除已处理的帧
            memmove(recv_buf, recv_buf + frame_size, buf_len - frame_size);
            buf_len -= frame_size;
        }

    }
exit:
    bbm_hdl->video_play_state = BBM_FILE_PLAY_DONE;
    printf("ctp file play task exit \n");
    if (ctp_file_play_sockfd) {
        sock_unreg(ctp_file_play_sockfd);
        ctp_file_play_sockfd = NULL;
    }
    if (recv_buf) {
        free(recv_buf);
        recv_buf = NULL;
    }
}

int ctp_file_play_start(void *priv, int list_index)
{
    int ret;
    char topic_1[] = {"TIME_AXIS_PLAY"};
    char content_1[256];

    struct bbm_client_hdl *bbm_hdl = priv;

    char *file_path = NULL;

    if (!bbm_hdl->ctp_cli_hdl) {
        printf("ctp cli hdl is NULL ! \n");
        return -1;
    }
    if (!bbm_hdl->file_name_list) {
        printf(" file list is null ! \n");
        return -1;
    }

    file_path = bbm_hdl->file_name_list[list_index];
    printf("file path:%s \n", file_path);

    //TODO dur_time 参数没有实际效果
    sprintf(content_1, "{\"op\":\"PUT\",\"param\":{\"path\":\"%s\",\"offset\":0}}",
            file_path);

    ret = ctp_cli_send(bbm_hdl->ctp_cli_hdl, topic_1, content_1);
    if (ret) {
        printf("ctp_cli_send :%s err\n", topic_1);
        return -1;
    }

    bbm_hdl->video_play_state = BBM_FILE_PLAY_START;

    return thread_fork(CTP_FILE_PLAY_TASK_NAME, 12, 2048, 2048, &bbm_hdl->ctp_file_play_task_pid, ctp_file_play_task, priv);
}

int ctp_file_play_stop(void *priv)
{
    int ret;
    char topic_1[] = {"TIME_AXIS_PLAY_CTRL"};
    char content_1[64];

    struct bbm_client_hdl *bbm_hdl = priv;

    if (!bbm_hdl->ctp_cli_hdl) {
        printf("ctp cli hdl is NULL ! \n");
        return -1;
    }

    sprintf(content_1, "{\"op\":\"PUT\",\"param\":{\"status\":\"%d\"}}", FILE_PLAY_VIDEO_STOP);
    ret = ctp_cli_send(bbm_hdl->ctp_cli_hdl, topic_1, content_1);
    if (ret) {
        printf("ctp_cli_send :%s err\n", topic_1);
        return -1;
    }

    if (bbm_hdl->ctp_file_play_task_pid) {
        bbm_hdl->ctp_file_play_task_exit = 1;
        thread_kill(&bbm_hdl->ctp_file_play_task_pid, KILL_WAIT);
        bbm_hdl->ctp_file_play_task_exit = 0;
        bbm_hdl->ctp_file_play_task_pid = 0;
    }


    //更改UI图标,停止
    post_video_play_msg_to_ui("play_control", 0);

    bbm_hdl->video_play_state = BBM_FILE_PLAY_STOP;

    return 0;
}

int ctp_file_play_pause(void *priv)
{
    int ret;
    char topic_1[] = {"TIME_AXIS_PLAY_CTRL"};
    char content_1[64];
    struct bbm_client_hdl *bbm_hdl = priv;

    if (!bbm_hdl->ctp_cli_hdl) {
        printf("ctp cli hdl is NULL ! \n");
        return -1;
    }

    sprintf(content_1, "{\"op\":\"PUT\",\"param\":{\"status\":\"%d\"}}", FILE_PLAY_VIDEO_PAUSE);
    ret = ctp_cli_send(bbm_hdl->ctp_cli_hdl, topic_1, content_1);
    if (ret) {
        printf("ctp_cli_send :%s err\n", topic_1);
        return -1;
    }

    bbm_hdl->video_play_state = BBM_FILE_PLAY_PAUSE;
    //更改UI图标,停止
    post_video_play_msg_to_ui("play_control", 0);

    return 0;
}

int ctp_file_play_resume(void *priv)
{
    int ret;
    char topic_1[] = {"TIME_AXIS_PLAY_CTRL"};
    char content_1[64];
    struct bbm_client_hdl *bbm_hdl = priv;

    if (!bbm_hdl->ctp_cli_hdl) {
        printf("ctp cli hdl is NULL ! \n");
        return -1;
    }

    sprintf(content_1, "{\"op\":\"PUT\",\"param\":{\"status\":\"%d\"}}", FILE_PLAY_VIDEO_CONTINUE);
    ret = ctp_cli_send(bbm_hdl->ctp_cli_hdl, topic_1, content_1);
    if (ret) {
        printf("ctp_cli_send :%s err\n", topic_1);
        return -1;
    }

    bbm_hdl->video_play_state = BBM_FILE_PLAY_RESUME;
    //更改UI图标,播放中
    post_video_play_msg_to_ui("play_control", 1);

    return 0;
}

int ctp_file_play_switch(void *priv, int list_index)
{
    int ret = -1;
    struct bbm_client_hdl *bbm_hdl = priv;

    switch (bbm_hdl->video_play_state) {
    case BBM_FILE_PLAY_STOP:
        ret = ctp_file_play_start(priv, list_index);
        break;
    case BBM_FILE_PLAY_START:
    case BBM_FILE_PLAY_RESUME:
        ret = ctp_file_play_pause(priv);
        break;
    case BBM_FILE_PLAY_PAUSE:
        ret = ctp_file_play_resume(priv);
        break;
    case BBM_FILE_PLAY_DONE:
        ret = ctp_file_play_stop(priv);
        ret = ctp_file_play_start(priv, list_index);
        break;
    default:
        printf("Unknow state %d \n", bbm_hdl->video_play_state);
        break;
    }

    return 0;
}

int ctp_file_play_init(void)
{
    int ret;
    //视频解码服务
    ret = video_dec_init();
    if (ret) {
        printf("video_dec_init err");
        goto err;
    }
    //音频解码服务
    ret = audio_dec_init();
    if (ret) {
        printf("audio_dec_init err");
        goto err;
    }

    return 0;

err:
    if (video_dec_server) {
        video_dec_exit();
    }
    if (audio_dec_server) {
        audio_dec_exit();
    }

}

int ctp_file_play_exit(void)
{
    if (video_dec_server) {
        video_dec_exit();
    }
    if (audio_dec_server) {
        audio_dec_exit();
    }

    return 0;
}

