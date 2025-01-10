#ifndef __BABY_MONITOR_H
#define __BABY_MONITOR_H

#include "system/includes.h"
#include "app_config.h"

struct net_ctp_thumb {
    int start_index;
    int file_num;
    u8 **file_buf_list;
    int *file_buf_len_list;
    OS_SEM sem;
};

struct bbm_client_hdl {
    OS_SEM ctp_msg_sem;         //CTP接收消息同步信号量
    int ctp_msg_arg;
    void *ctp_cli_hdl;          //CTP CLIENT
    u32 ip_addr;

    int ctp_get_file_task_pid;
    u8 ctp_get_file_task_exit;
    char **file_name_list;
    int  file_total_num;
    char vf_list[128];

    int ctp_file_thumb_task_pid;
    u8 ctp_file_thumb_task_exit;
    char ctp_file_thumb_task_name[64];

    int ctp_file_play_task_pid;
    u8 ctp_file_play_task_exit;
    u8 video_play_state;
};

struct video_rec_config {
    u16 width;
    u16 height;

    u8 id;
    u8 sub_id;
    u8 fps;
    u16 abr_kbps;
    u8 cycle_time;

    char *net_path;
    void *priv;
};

enum {
    BBM_FILE_PLAY_STOP = 0,
    BBM_FILE_PLAY_START,
    BBM_FILE_PLAY_PAUSE,
    BBM_FILE_PLAY_RESUME,
    BBM_FILE_PLAY_DONE,
};

enum {
    RT_DISP_WIN_MAIN = 0,
    RT_DISP_WIN_LEFT,
    RT_DISP_WIN_RIGHT,
};

enum {
    FILE_PLAY_VIDEO_CONTINUE = 0,
    FILE_PLAY_VIDEO_PAUSE,
    FILE_PLAY_VIDEO_STOP,
};








#endif /* __BABY_MONITOR_H */

