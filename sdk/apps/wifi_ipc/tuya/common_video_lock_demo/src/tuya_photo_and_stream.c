/**
 * @file    tuya_photo_and_stream.c
 * @author  mjl@tuya.com
 * @version 1.0
 * @date    2021-07-27
 * @copyright Copyright (c) tuya.inc 2020
 */
#define __TY_PHOTO_AND_STREAM_GLOBALS
#include "app_config.h"
#include "asm/jpeg_codec.h"
#include "asm/aes_hw.h"
#include "string.h"

#include "tuya_photo_and_stream.h"
#include "gw_intf.h"
#include "uni_log.h"
#include "tuya_cloud_types.h"
#include "tuya_cloud_com_defs.h"
#include "ty_cJSON.h"
#include "tuya_iot_wifi_api.h"
#include "uni_msg_queue.h"
#include "tuya_ipc_streamer.h"
#include "tuya_uart_common_basic_service.h"
#include "tuya_device.h"
#include "app_agent.h"
#include "tuya_low_power.h"
#include "tuya_video.h"
#include "tuya_fast_init.h"

#include "tuya_hal_mutex.h"
#include "tuya_hal_system.h"
#include "uni_time.h"
#include "time.h"

#define PT_TRIGGER_RET_SUCCESS          0x00
#define PT_TRIGGER_RET_FIALED           0x01

#define TRIGGER_TYPE_INIT           0x00
#define TRIGGER_TYPE_PHOTO          0x01
#define TRIGGER_TYPE_STREAM         0x02

typedef UCHAR_T TRANS_STATE_E;
#define PT_PROC_NULL                    0x00
#define PT_PROC_START                   0x01
#define PT_PROC_READY                   0x02
#define PT_PROC_UPLOAD                  0x03
#define PT_PROC_FAILED                  0x04

/* #define PHONE_ROTE_DEFAULT       0 */

#define PT_DATA_INIT                     0
#define PT_STREAM_START                  1
#define PT_DATA_END                      2
#define PT_UP_SKILL                      3
#define PT_UP_STREAM                     4
#define PT_FORCE_UP_SKILL                6
#define PT_STREAM_DATA_START             7

#define PT_RET_SUCC                     0x00
#define PT_RET_NET_FAILED               0x01
#define PT_RET_SIZE_OUT                 0x02
#define PT_RET_TIME_OUT                 0x03
#define PT_RET_OTHER_FAILED             0x04
#define PT_RET_STREAM_STOP              0x05

#define PHOTO_NAME_SIZE         20
#define MEDIA_NAME_SIZE         17
#define UPLOAD_TIMEBUFF_SIZE    6
#define FORCE_PUSH_STREAM_OFF_TIMEOUT     (4*60*1000)
#define TRIGGER_TIMEOUT                   30*1000
#define DATA_TIMEOUT                   10*1000
#define USB_IN_TIMEOUT                 10*1000

#define PT_SYS_DP                            212
#define unlock_fingerprint                   1
#define unlock_face                          6
#define photo_again                          47
#define alarm_lock                           8
#define unlock_app                           15



#define TY_URL_BIZTYPE_IMAGE    "lock_snapshot_image"
#define TY_URL_CONTENTYPE_IMAGE "image/jpg"
#define TY_DP212_VER_50         "5.0"
#define TY_DP212_TYPE_IMAGE     "image"
#define TY_DP212_TYPE_MEDIA     "media"
#define TY_DP212_CMD_COVER      "door_lock_video_cover"
#define TY_DP212_CMD_VIDEO      "door_lock_video"
#define TY_DP212_WITH_RESORCES  "resources"
#define TY_SVC_STREAM_GET_ATOP  "tuya.device.rtc.stream.push.start"
#define TY_SVC_STREAM_GET_VER   "1.0"
#define TY_SVC_PHOTO_GET_ATOP  "tuya.device.rtc.image.push"
#define TY_SVC_PHOTO_GET_VER   "1.0"
#define TY_SVC_DEV_SKILL_UPDATE "tuya.device.skill.update"
#define TY_SVC_SKILL_UPDATE_VER   "1.0"
#define TY_SVC_CAMER_INFO       "camer_info"

#define  IPC_SKILLS_BUF_LEN  128u
#define TUYA_P2P_TYPE           4

typedef unsigned short WORD;

//#define TY_STREAM_VIDEO_FPS     25
#define TY_STREAM_AUDIO_FPS     25

#define STREAM_BUFFER_MAX_NUM  30
//#define AUDIO_BUFFER_LEN      (1280 * 2)
#define IPC_ENCRYPTION_SPACE_HEAD 128

TIME_T time_overall = 0;


typedef struct {
    UINT_T              cmd;
    UCHAR_T             *data;
    UINT_T              data_len;
} PHOTO_CTRL_MSG;

typedef struct {
    BOOL_T          photo_init;
    UCHAR_T         trigger_type;
    UINT_T          audio_seq;
    UINT_T          photo_id;
    UINT_T          seq_id;
    THRD_HANDLE     handle;
    OS_QUEUE        msg_que;
    TIMER_ID        timer;
    TRANS_STATE_E   proc_state;
    BOOL_T          is_busy;
    BOOL_T          stream_is_busy;
    BOOL_T          is_support_audio;
    TY_STREAM_SEND_FRAME_HANDLE_CB cb;
    BOOL_T          stream_is_over_time;
    UCHAR_T         tm[UPLOAD_TIMEBUFF_SIZE];
} PHOTO_CRTL;

typedef struct {
    BOOL_T          stream_que_init;
    OS_QUEUE        stream_queue;
    UINT_T          queue_cnt;
    MUTEX_HANDLE    queue_mutex;
    CHAR_T         *audio_buffer;  //用于临时缓存音频数据
    UINT_T          audio_put_len; //用于记录缓存中放入的音频帧长度
} STREAM_CRTL;

typedef struct {
    UCHAR_T         time_flag;
    UCHAR_T         tm[UPLOAD_TIMEBUFF_SIZE];
    USHORT_T        id;
    USHORT_T        event_type;
    CHAR_T         name[MEDIA_NAME_SIZE];
    UINT_T          expire;
    BYTE_T         *url;
    CHAR_T        *key;
    CHAR_T        *ckey;
    CHAR_T        *auth;
    CHAR_T        *date;
    CHAR_T        *cont;
    CHAR_T        *url_id;
    CHAR_T        *bucket;
} UPLOAD_INFO;

#pragma pack(1)
typedef struct {
    UCHAR_T     sub_cmd;
    USHORT_T    event_type;
    UCHAR_T     trigger_type;
    UCHAR_T     ph_reserve1;
    UCHAR_T     ph_reserve2;
    UCHAR_T     time_flag;
    UCHAR_T     time[6];
} PT_TRIGGER_PROT;
#pragma pack()

STATIC PHOTO_CRTL g_pt_ctrl;
/* STATIC PHOTO_CRTL g_pt_ctrl2; */
STATIC UPLOAD_INFO *g_photo_info = NULL;
STATIC UPLOAD_INFO *g_stream_info = NULL;
/* STATIC UPLOAD_INFO *g_stream2_info = NULL; */
STATIC UINT_T first_image_len = 0;
STATIC CHAR_T ipc_skills[IPC_SKILLS_BUF_LEN];
STATIC BOOL_T send_frame_type = FALSE;
STATIC UINT64_T first_image_timestamp_ms = 0;

STATIC STREAM_CRTL g_stream_ctrl = {0};
/* STATIC STREAM_CRTL g_stream2_ctrl = {0}; */

STATIC TY_CAMERA_PARAM camera_param = {
    .video_width = VEDIO_W_DEFAULT,
    .video_height = VEDIO_H_DEFAULT,
    .video_rotat_angle = VEDIO_ROTE_DEFAULT,
    .video_fps = VEDIO_FPS_DEFAULT,
};

STATIC TY_AUDIO_PARAM audio_param = {
    .channel_num = AUDIO_CHANNEL_DEFAULT,
    .bit_dept = AUDIO_BIT_DEFAULT,
    .sample_rate = AUDIO_RATE_DEFAULT,
};

//STATIC TIMER_ID print_net_rate_timer = 0;
STATIC VOID print_net_timer_cb(UINT_T timerID, PVOID_T pTimerArg);
STATIC VOID ty_data_info_clean(UPLOAD_INFO **info);
STATIC VOID tuya_doorbell_upload(UPLOAD_INFO *upload_info);


//////////////////////////////
void put_alarm()
{
    TY_OBJ_DP_VALUE_U dp_value;
    dp_value.dp_value = 1;
    dp_value.dp_bool = 1;
    dp_value.dp_enum = 2;

    TY_OBJ_DP_S dp_data;
    dp_data.dpid = alarm_lock;//unlock_app;//alarm_lock;//unlock_face;//unlock_face;
    dp_data.type = PROP_ENUM;//PROP_VALUE;//PROP_ENUM;//PROP_VALUE;//PROP_VALUE;
    dp_data.value = dp_value;
    dp_data.time_stamp = time_overall;//time;

    PR_DEBUG("time:%d", dp_data.time_stamp);
    dev_report_dp_stat_sync(get_gw_cntl()->gw_if.id, &dp_data, 1, 5);
}
////////////////////////////////

int GetFrameType(char *nal)
{
    int frame_type = 0;

    if (nal[0] == 0x00 && nal[1] == 0x00 && nal[2] ==  0x00 && nal[3] == 0x01) {
        frame_type = nal[4] & 0x1f;
    } else if (nal[0] == 0x00 && nal[1] == 0x00 && nal[2] ==  0x00 && nal[3] == 0x00 && nal[4] == 0x01) {
        frame_type = nal[5] & 0x1f;
    } else {
        return -1;
    }
    return frame_type;
}

OPERATE_RET ty_param_load(CHAR_T *type, UCHAR_T *input_param, UINT_T input_len, UINT_T *out_read_len)
{
    OPERATE_RET op_ret = OPRT_OK;
    UCHAR_T *load_param = NULL;
    UINT_T param_len;

    if (NULL == input_param || input_len == 0) {
        PR_ERR("ty_param_load input_param err!");
        return OPRT_INVALID_PARM;
    }

    op_ret = wd_common_read(type, &load_param, &param_len);
    if (OPRT_OK != op_ret) {
        PR_ERR("ty_param_load  err:%0d", op_ret);
        return op_ret;
    } else {
        if (input_len < param_len) {
            PR_ERR("ty_param_load input_len < param_len");
            Free(load_param);
            return OPRT_COM_ERROR;
        }
        memcpy(input_param, load_param, param_len);
        *out_read_len = param_len;
        PR_NOTICE("ty_param_load success!");
        Free(load_param);
    }
    return op_ret;
}

OPERATE_RET ty_param_save(CHAR_T *type, UCHAR_T *input_param, UINT_T inlen)
{
    OPERATE_RET op_ret = OPRT_OK;

    if (NULL == input_param || inlen == 0) {
        PR_ERR("ty_sn_save input_param err!");
        return OPRT_INVALID_PARM;
    }

    op_ret = wd_common_write(type, input_param, inlen);
    if (OPRT_OK != op_ret) {
        PR_ERR("wd_common_write camera_param err:%d", op_ret);
    } else {
        PR_NOTICE("save  success");
    }
    return op_ret;
}


////////////////////////////////////

STATIC OPERATE_RET ty_photo_send_msg(IN CONST UINT_T msgid, IN CONST VOID *data, IN CONST UINT_T len)
{
    PR_DEBUG("ty photo send msd");
    OPERATE_RET op_ret = OPRT_OK;

    PHOTO_CTRL_MSG *msg_data;
//    PR_DEBUG("malloc data");
    msg_data = Malloc(SIZEOF(PHOTO_CTRL_MSG) + 1);
    if (!msg_data) {
        return OPRT_MALLOC_FAILED;
    }
    memset(msg_data, 0, SIZEOF(PHOTO_CTRL_MSG) + 1);
    msg_data->cmd = msgid;

//    PR_DEBUG("printf data:");
//    put_buf(data, len);
    if (data && len) {
        msg_data->data = Malloc(len + 1);
        if (!(msg_data->data)) {
            if (msg_data) {
                Free(msg_data);
            }
            return OPRT_MALLOC_FAILED;
        }
        memset(msg_data->data, 0, len + 1);
        memcpy(msg_data->data, data, len);
        msg_data->data_len = len;
    }
    PR_DEBUG("into os_q_post, msg_cmd:%d", msg_data->cmd);
    op_ret = os_q_post(&g_pt_ctrl.msg_que, msg_data);

    if (OPRT_OK != op_ret) {
        if (msg_data->data) {
            Free(msg_data->data);
        }
        if (msg_data) {
            Free(msg_data);
        }
        return op_ret;
    }
    PR_DEBUG("ty_photo_send_msg");
    return OPRT_OK;
}

////////////////////////////////////////////
#define IPC_STREAM_MAX_NUM      10
#if (__SDRAM_SIZE__ == (8 * 1024 * 1024))
#define MAX_FRGE_SIZE           (1024*100) //(1024*40)
#else if (__SDRAM_SIZE__ == (16 * 1024 * 1024))
#define MAX_FRGE_SIZE           (1024*200)
#endif

#pragma pack(1)
typedef struct {
    UINT_T      seqNo;
    UCHAR_T     fragStatus;
    UCHAR_T     fragNo;
    USHORT_T    frameType;
    UINT64_T    timestamp_ms;
    UINT_T      len;
    UCHAR_T     data[0];
} SVC_STREAM_INFO;
#pragma pack()


//STATIC P_QUEUE_CLASS stream_queue;
STATIC BOOL_T ipc_push_stream_start = FALSE;//FALSE;
STATIC BOOL_T is_ipc_stream_que_init = FALSE;
STATIC SVC_STREAM_INFO *last_stream_info = NULL;
//STATIC P_QUEUE_CLASS audio_stream_queue;

/////////////////////////////////////
BOOL_T tuya_push_stream_status_get(VOID)
{
    return ipc_push_stream_start;
}
STATIC VOID tuya_push_stream_start(VOID)
{
    ipc_push_stream_start = TRUE;
//    g_pt_ctrl.audio_seq = 0;
//    sys_start_timer(print_net_rate_timer, 1000, TIMER_ONCE);
}

STATIC VOID tuya_push_stream_stop(VOID)
{
    ipc_push_stream_start = FALSE;
//    sys_stop_timer(print_net_rate_timer);
}


STATIC SVC_STREAM_INFO *ipc_stream_out_queue(VOID)
{
//    PR_DEBUG("into ipc stream out queue!");
    SVC_STREAM_INFO *info = NULL;
    OPERATE_RET op_ret = OPRT_OK;

    tuya_hal_mutex_lock(g_stream_ctrl.queue_mutex);
//    PR_DEBUG("ipc_stream_out_queue os_q_pend");

    int msg[16] = {0,};
    op_ret = os_q_recv(&g_stream_ctrl.stream_queue, msg, 1);
    if (op_ret) {
        tuya_hal_mutex_unlock(g_stream_ctrl.queue_mutex);
        return NULL;
    } else {
        g_stream_ctrl.queue_cnt--;
    }
    info = (SVC_STREAM_INFO *)msg[0];
    tuya_hal_mutex_unlock(g_stream_ctrl.queue_mutex);

    return info;
}

STATIC VOID tuya_clear_stream_que(VOID)
{
    PR_DEBUG("clear stream que");
    UINT_T i = 0, queue_cnt = 0;
    SVC_STREAM_INFO *stream_info = NULL;
    queue_cnt = g_stream_ctrl.queue_cnt;
    for (i = 0; i < queue_cnt; i++) {
        stream_info = ipc_stream_out_queue();
        if (stream_info) {
            /* putchar('c'); */
            Free(stream_info);
            stream_info = NULL;
        }
    }
    return ;
}


STATIC OPERATE_RET ipc_stream_in_queue(CHAR_T *p_image_data, UINT_T image_len, USHORT_T type)
{
    /* TAL_PR_DEBUG("ipc_stream_in_queue!"); */
    SVC_STREAM_INFO *pstream_info = NULL;
    UCHAR_T image_max_frage = 0;
    UCHAR_T i = 0;
    UINT_T malloc_len = 0;
    UINT64_T    cur_timestamp_ms;
    OPERATE_RET ret = OPRT_OK;
    STATIC UCHAR_T frage = 0;
    UINT_T timeout = 0;

    if (!ipc_push_stream_start) {
        /* TAL_PR_DEBUG("ipc push stream not start"); */
        return OPRT_COM_ERROR;
    }


    image_max_frage = (image_len + (MAX_FRGE_SIZE - 1)) / MAX_FRGE_SIZE;


    tuya_hal_mutex_lock(g_stream_ctrl.queue_mutex);

#if 1
    if (g_stream_ctrl.queue_cnt > STREAM_BUFFER_MAX_NUM - 5) {
//        PR_WARN("need get i frame, heap=%d\n",tuya_hal_system_getheapsize());
//        PR_WARN("g_stream_ctrl :%d", g_stream_ctrl.queue_cnt);
        tuya_clear_stream_que();
        tuya_hal_mutex_unlock(g_stream_ctrl.queue_mutex);
        return OPRT_OK;
    }


    cur_timestamp_ms = tal_time_get_posix_ms();
    for (i = 0; i < image_max_frage; i++) {
        if (i == image_max_frage - 1) {
            malloc_len = sizeof(SVC_STREAM_INFO) + image_len % MAX_FRGE_SIZE;
        } else {
            malloc_len = sizeof(SVC_STREAM_INFO) + MAX_FRGE_SIZE;
        }
//        PR_DEBUG("malloc data");
        pstream_info = Malloc(malloc_len);
        if (NULL == pstream_info) {
            PR_ERR("malloc failed");
            tuya_hal_mutex_unlock(g_stream_ctrl.queue_mutex);
            return OPRT_MALLOC_FAILED;
        }
        pstream_info->frameType = type;
        pstream_info->timestamp_ms = cur_timestamp_ms;
        pstream_info->seqNo = g_pt_ctrl.seq_id;
        pstream_info->len = malloc_len - sizeof(SVC_STREAM_INFO);
        memcpy(pstream_info->data, p_image_data + i * MAX_FRGE_SIZE, pstream_info->len);
        if (1 == image_max_frage) {
            pstream_info->fragStatus = STREAMING_FRAG_DISABLE;
            pstream_info->fragNo = 0;
            g_pt_ctrl.seq_id++;
        } else if (2 == image_max_frage) {
            if (i == 0) {
                pstream_info->fragStatus = STREAMING_FRAG_START;
                pstream_info->fragNo = 0;
            } else {
                pstream_info->fragStatus = STREAMING_FRAG_END;
                pstream_info->fragNo = 1;
                g_pt_ctrl.seq_id++;
            }
        } else {
            if (i == 0) {
                pstream_info->fragStatus = STREAMING_FRAG_START;
                frage = 0;
                pstream_info->fragNo = 0;
            } else if (i == image_max_frage - 1) {
                pstream_info->fragStatus = STREAMING_FRAG_END;
                frage++;
                pstream_info->fragNo = frage;
                g_pt_ctrl.seq_id++;
            } else {
                pstream_info->fragStatus = STREAMING_FRAG_INSIDE;
                frage++;
                pstream_info->fragNo = frage;
            }

        }

        ret = os_q_post(&g_stream_ctrl.stream_queue, (CONST UCHAR_T *)pstream_info);
        if (ret) {
            PR_DEBUG("post work_mode_queue failed, ret(%d)\n", ret);
            Free(pstream_info);
            ret = OPRT_COM_ERROR;
        } else {
            g_stream_ctrl.queue_cnt++;
        }
        //PR_DEBUG("frameType %d inque 0x%x t %lld seqNo %d len %d frag %d %d\r\n",pstream_info->frameType, pstream_info,pstream_info->timestamp_ms,pstream_info->seqNo,pstream_info->len,pstream_info->fragStatus,pstream_info->fragNo);
    }
    tuya_hal_mutex_unlock(g_stream_ctrl.queue_mutex);
#endif
    return ret;
}



OPERATE_RET ty_stream_in_queue(CHAR_T *p_image_data, UINT_T image_len, UINT_T frame_type)
{
//    PR_DEBUG("ty_stream_in_queue");
    /* if (!ipc_push_stream_start) { */
    /* return OPRT_NOT_SUPPORTED; */
    /* } */
    if (!image_len) {
        return OPRT_INVALID_PARM;
    }
//    PR_NOTICE("put data to stream queue");
    /* PR_NOTICE("put %d to stream queue", image_len); */
    return ipc_stream_in_queue(p_image_data, image_len, frame_type);
}


STATIC OPERATE_RET ty_stream_clear_and_in_queue(CHAR_T *p_image_data, UINT_T image_len)
{
    tuya_clear_stream_que();
    return ipc_stream_in_queue(p_image_data, image_len, E_VIDEO_I_FRAME);
}


VOID ty_audio_stream_in_queue(CHAR_T *p_audio_data, UINT_T audio_len)
{
    if (g_pt_ctrl.trigger_type == TRIGGER_TYPE_PHOTO) {
        return ;
    }
    if (!ipc_push_stream_start) {
        return ;
    }
    if (!audio_len) {
        return;
    }
//    PR_DEBUG("put audio data");
//    put_buf(p_audio_data, audio_len);

    ipc_stream_in_queue(p_audio_data, audio_len, E_AUDIO_FRAME);
    return ;
}

STATIC OPERATE_RET ty_stream_queue_init(VOID)
{
    PR_DEBUG("into ty_stream_queue_init");
    OPERATE_RET op_ret = OPRT_OK;
    if (g_stream_ctrl.stream_que_init) {
        return op_ret;
    }

    QS queue_size = (SIZEOF(SVC_STREAM_INFO *) * STREAM_BUFFER_MAX_NUM + sizeof(WORD) - 1) / sizeof(WORD);

    op_ret = os_q_create(&g_stream_ctrl.stream_queue, queue_size);
    if (NULL == &g_stream_ctrl.stream_queue) {
        return OPRT_COM_ERROR;
    }
    op_ret = tuya_hal_mutex_create_init(&g_stream_ctrl.queue_mutex);
    if (OPRT_OK != op_ret) {
        return op_ret;
    }
//    sys_add_timer(print_net_timer_cb, NULL, &print_net_rate_timer);
    g_stream_ctrl.stream_que_init = TRUE;
    return op_ret;
}

BOOL_T ty_stream_is_support(VOID)
{
    BOOL_T op_ret = FALSE;
    op_ret = TRUE;
    return op_ret;
}

//////////////////////////////////////////////
STATIC VOID photo_ack_time_Proc(VOID)
{
    OPERATE_RET  op_ret = OPRT_OK;
    POSIX_TM_S   tm;

    op_ret = uni_local_time_get(&tm);
    if (OPRT_OK != op_ret) {
        PR_ERR("uni_local_time_get failed! op_ret:%d", op_ret);
        return ;
    }

    /*convert*/
    g_photo_info->tm[0] = tm.tm_year - 100;
    g_photo_info->tm[1] = tm.tm_mon + 1;
    g_photo_info->tm[2] = tm.tm_mday;
    g_photo_info->tm[3] = tm.tm_hour;
    g_photo_info->tm[4] = tm.tm_min;
    g_photo_info->tm[5] = tm.tm_sec;

    return ;
}
STATIC TIME_T ty_trigger_time_proc(BOOL_T time_flag, UCHAR_T *time)
{
    TIME_T time_t = 0;
    INT_T zone_num = 0;

    if (time_flag > 0) {

        POSIX_TM_S  stu_timer;
        stu_timer.tm_year = (time[0] + 100); //(2000-1900)
        stu_timer.tm_mon  = (time[1] - 1);
        stu_timer.tm_mday = time[2];
        stu_timer.tm_hour = time[3];
        stu_timer.tm_min  = time[4];
        stu_timer.tm_sec  = time[5];
        time_t = uni_mktime(&stu_timer);

        if (0x01 == time_flag) {
            if (uni_get_time_zone_seconds(&zone_num) != OPRT_OK) {
                PR_ERR("tuya_get_time_zone err ");
            }

            PR_DEBUG("zone_num %d", zone_num);
            time_t -= zone_num;

            if (TRUE == uni_is_in_sum_zone(time_t)) {
                PR_DEBUG("sumer timer");
                time_t -= 3600;
            }
        }
    } else {
        time_t = uni_time_get_posix();
        photo_ack_time_Proc();

    }
    PR_DEBUG("time:%d,time flag:%d", time_t, time_flag);
    return time_t;
}

STATIC OPERATE_RET ty_data_init_photo(PVOID_T msgdata)
{
    if (NULL != g_photo_info) {
        ty_data_info_clean(&g_photo_info);
        g_photo_info = NULL;
    }
//    PR_DEBUG("malloc data");
    g_photo_info = (UPLOAD_INFO *)Malloc(SIZEOF(UPLOAD_INFO));
    if (NULL == g_photo_info) {
        PR_ERR("g_photo_info malloc error");
        return OPRT_MALLOC_FAILED;
    }
    memset(g_photo_info, 0, SIZEOF(UPLOAD_INFO));
    PT_TRIGGER_PROT *pdata = (PT_TRIGGER_PROT *)msgdata;
    g_photo_info->event_type = WORD_SWAP(pdata->event_type);
    g_photo_info->id = 0;
    g_photo_info->time_flag = pdata->time_flag;
    memcpy(g_photo_info->tm, pdata->time, UPLOAD_TIMEBUFF_SIZE);

    PR_DEBUG("ty_data_init_photo success! heapsize:%d", tuya_hal_system_getheapsize());
    return OPRT_OK;
}

STATIC OPERATE_RET ty_data_init_stream(PVOID_T msgdata)
{
    PR_DEBUG("into ty_data_init_steam!");
    if (NULL != g_stream_info) {
        ty_data_info_clean(&g_stream_info);
        g_stream_info = NULL;
    }
//    PR_DEBUG("malloc data");
    g_stream_info = (UPLOAD_INFO *)Malloc(SIZEOF(UPLOAD_INFO));
    if (NULL == g_stream_info) {
        PR_ERR("g_stream_info malloc error");
        return OPRT_MALLOC_FAILED;
    }
    memset(g_stream_info, 0, SIZEOF(UPLOAD_INFO));

    //get photo_ctrl infomation
    PT_TRIGGER_PROT *pdata = (PT_TRIGGER_PROT *)msgdata;
    g_stream_info->event_type = WORD_SWAP(pdata->event_type);
    g_stream_info->id = 0;
    g_stream_info->time_flag = pdata->time_flag;
    memcpy(g_stream_info->tm, pdata->time, UPLOAD_TIMEBUFF_SIZE);

    PR_DEBUG("ty_data_init_stream success! heapsize:%d", tuya_hal_system_getheapsize());
    return OPRT_OK;
}

STATIC OPERATE_RET ty_photo_data_init_proc(PVOID_T msgdata)
{
    OPERATE_RET op_ret = OPRT_OK;

    g_pt_ctrl.is_busy = TRUE;
    g_pt_ctrl.stream_is_over_time = FALSE;
    g_pt_ctrl.proc_state = PT_PROC_NULL;
    send_frame_type = FALSE;

//    sys_stop_timer(g_pt_ctrl.timer);
    memset(g_pt_ctrl.tm, 0, UPLOAD_TIMEBUFF_SIZE);
    op_ret = ty_data_init_photo(msgdata);
    if (op_ret != OPRT_OK) {
        return op_ret;
    }
    if (g_pt_ctrl.trigger_type == TRIGGER_TYPE_STREAM) {
        op_ret = ty_data_init_stream(msgdata);
        if (op_ret != OPRT_OK) {
            return op_ret;
        }
    }

    return op_ret;
}

STATIC VOID ty_photo_update_ack(USHORT_T id, UCHAR_T *time, UCHAR_T result)
{
    PR_NOTICE("ty_photo_ack result:%d 0x%x", result, g_pt_ctrl.cb);
    UCHAR_T data[9] = {0};
    data[0] = (id >> 8) & 0xFF ;
    data[1] = id & 0xFF ;
    if (time) {
        memcpy(&data[2], time, UPLOAD_TIMEBUFF_SIZE);
    }
    data[8] = result;
    if (g_pt_ctrl.cb) {
        PR_NOTICE("ty_photo_ack result:%d", result);
        TY_STREAM_SEND_FRAME_S send_data;
        send_data.type = STREAM_SEND_TYPE_DIRECT;
        send_data.cmd = PHOTO_UPLOAD_ACK_CMD;
        send_data.data_len = SIZEOF(data);
        send_data.data = (UCHAR_T *)&data[0];
        g_pt_ctrl.cb(&send_data);
    }
}



STATIC INT_T __event_cb(IN CONST TRANSFER_EVENT_E event)
{

//    PR_DEBUG("into __event_cb");
    PR_NOTICE("*************************");
    PR_NOTICE("svc_stream state is %d", event);
    PR_NOTICE("*************************");
    UCHAR_T ret;
    TIME_T time_t = 0;
    TIME_T rtc_time_sec;
    struct tm *time_info;
    POSIX_TM_S  stu_timer;
    if ((event == TRANS_STREAMING_VIDEO_START) && (!g_pt_ctrl.stream_is_busy)) {
        g_pt_ctrl.stream_is_busy = TRUE;
        g_pt_ctrl.stream_is_over_time = FALSE;
        g_pt_ctrl.proc_state = PT_PROC_READY;

        ret = PT_RET_SUCC;
        ty_photo_send_msg(PT_STREAM_DATA_START, &ret, 1);
    }
    if ((event == TRANS_STREAMING_VIDEO_STOP) && g_pt_ctrl.stream_is_busy) {

//        tuya_push_stream_stop();
        if (FALSE == g_pt_ctrl.stream_is_over_time) {
            if (g_pt_ctrl.trigger_type == TRIGGER_TYPE_PHOTO) {
                ret = PT_RET_SUCC;
                /* 传图之后要更改到传流的类型，防止app直接拉流拉不到 */
                g_pt_ctrl.trigger_type = TRIGGER_TYPE_STREAM;
                ty_photo_send_msg(PT_DATA_END, &ret, 1);
                return 0;  // 图片直接返回
            } else if (g_pt_ctrl.trigger_type == TRIGGER_TYPE_STREAM) {
                ret = PT_RET_STREAM_STOP;
                ty_photo_send_msg(PT_DATA_END, &ret, 1);
            } else {
                ret = PT_RET_STREAM_STOP;
                ty_photo_send_msg(PT_DATA_END, &ret, 1);
            }
        } else {
            g_pt_ctrl.stream_is_over_time = FALSE;
        }
        g_pt_ctrl.stream_is_busy = FALSE;

    }

    return 0;
}

extern INT_T get_image_jpeg(INT_T **jpeg_buf, INT_T *real_len, INT_T time_out);
extern INT_T ty_device_write_voice_data(VOID *data, UINT_T len);
extern INT_T ty_device_get_voice_data(VOID *data, UINT_T max_len);
STATIC INT_T jpeg_count = 0;
STATIC UINT_T tatal_size = 0;
STATIC INT_T voice_count = 0;
STATIC VOID print_net_timer_cb(UINT_T timerID, PVOID_T pTimerArg)
{
    if (tuya_push_stream_status_get()) {
//        sys_start_timer(print_net_rate_timer, 1000, TIMER_ONCE);
//        PR_NOTICE("stream video fps %d audio fps %d free que num %d net %d kb/s",  \
//                    jpeg_count,voice_count,GetCurFreeQueNum(g_stream_ctrl.stream_queue),tatal_size/1024);
        jpeg_count = 0;
        tatal_size = 0;
        voice_count = 0;
    }
}

INT_T __get_frame_cb(IN INT_T get_latest_frame, IN STREAM_TYPE_E stream_type, IN INT_T retry, OUT FRAME_INFO_S *frame_info)
{
    /* PR_DEBUG("into get frame cb"); */
    TIME_S time_s = 0;
    TIME_S time_ms = 0;
    OPERATE_RET op_ret = OPRT_OK;
    UINT_T send_len = 0;
    INT_T time1 = 0;
    INT_T time2 = 0;

    if (NULL != last_stream_info) {
        Free(last_stream_info);
        last_stream_info = NULL;
    }
    SVC_STREAM_INFO *stream_info = NULL;
    //PR_DEBUG("out stream data");
    stream_info = ipc_stream_out_queue();
    /* PR_DEBUG("out stream data"); */
    /* malloc_stats(); 	 */
    if (stream_info) {
        frame_info->type = stream_info->frameType;
        frame_info->timestamp = stream_info->timestamp_ms;
        frame_info->pts = frame_info->timestamp * 1000;
        frame_info->data = stream_info->data;
        frame_info->size = stream_info->len;
        frame_info->seqNo = stream_info->seqNo;
        frame_info->fragStatus = stream_info->fragStatus;    //音频数据无需分包
        frame_info->fragNo = stream_info->fragNo;
        last_stream_info = stream_info;
    } else {
        PR_DEBUG("wait");
        return OPRT_COM_ERROR;
    }

    //PR_DEBUG("type=%d timestamp=%lld size=%d ", frame_info->type, frame_info->timestamp, frame_info->size);
    tatal_size += frame_info->size;
//    PR_DEBUG_RAW("No=%d len=%d type=%d frag_st=%d  frag_no=%d timestap=%lld\r\n",frame_info->seqNo,frame_info->size,frame_info->type,frame_info->fragStatus,frame_info->fragNo,frame_info->timestamp);

    return OPRT_OK;
}

VOID __recv_audio_cb(IN CONST TRANSFER_AUDIO_FRAME_S *p_audio_frame)
{
    OPERATE_RET op_ret = OPRT_OK;
//    PR_NOTICE("__recv_audio_cb recv len %d audio_codec %d audio_databits %d audio_sample %d", p_audio_frame->buf_len,p_audio_frame->audio_codec,p_audio_frame->audio_databits,p_audio_frame->audio_sample);
    ty_device_write_net_voice_data(p_audio_frame->p_audio_buf, p_audio_frame->buf_len);
    return ;
}

STATIC OPERATE_RET ty_update_skill_and_rotate(INT_T rotate)
{
    PR_DEBUG("into update skill and rotate!");
    OPERATE_RET op_ret = OPRT_OK;
    CHAR_T skill_info[512];
    tuya_ipc_streamer_set_max_frame_size(MAX_FRGE_SIZE);
//    tuya_ipc_streamer_set_memory_save_mode();
    TSTREAMER_S *pstreamer = GetTStreamerInstance();
    if (pstreamer) {
        /* pstreamer->SupportAudio(g_pt_ctrl.is_support_audio); */
        pstreamer->FillSkills(skill_info, sizeof(skill_info));
    }


    GW_CNTL_S *gw_cntl = get_gw_cntl();
    PR_DEBUG("http deveice update skill!");
    op_ret = http_device_update_skill(gw_cntl->gw_if.id, skill_info);
    if (op_ret != OPRT_OK) {
        PR_ERR("http_device_update_skill failed!!");
    } else {
        PR_NOTICE("svc_stream_start done!! g_pt_ctrl.is_support_audio =%d rotate=%d", g_pt_ctrl.is_support_audio, rotate);
        if (rotate == 0 || rotate == 90 || rotate == 180 || rotate == 270) {
            op_ret = tuya_rotating_upload(rotate);
        }

    }
    return op_ret;
}


STATIC OPERATE_RET httpc_proc_url_state(ty_cJSON *result, UPLOAD_INFO *upload_info)
{
    UINT_T url_len = 0;
    ty_cJSON *item = NULL, *root = NULL, *header = NULL, *auth = NULL, *date = NULL, *cont = NULL, *key = NULL, *ckey = NULL;
    OPERATE_RET op_ret = OPRT_OK;
    PR_DEBUG("httpc_proc_url_state:%d", tuya_hal_system_getheapsize());
    item = ty_cJSON_GetObjectItem(result, "url");
    if (NULL == item) {
        PR_ERR("ty_cJSON_GetObjectItem url err");
        return OPRT_CJSON_GET_ERR;
    }
//    PR_DEBUG("malloc data");
    upload_info->url = (BYTE_T *)Malloc(strlen(item->valuestring) + 1);
    if (NULL == upload_info->url) {
        PR_ERR("httpc_proc_url_state url malloc error");
        return OPRT_MALLOC_FAILED;
    }

    memset(upload_info->url, 0, strlen(item->valuestring) + 1);
    memcpy(upload_info->url, item->valuestring, strlen(item->valuestring));

    PR_DEBUG("recv url:%s, url:%s,len:%d", item->valuestring, upload_info->url, strlen(item->valuestring));

    item = ty_cJSON_GetObjectItem(result, "allocateId");
    if (NULL == item) {
        PR_ERR("ty_cJSON_GetObjectItem allocateId err");
        return OPRT_CJSON_GET_ERR;
    }

    PR_DEBUG("url_id len = %d", strlen(item->valuestring) + 1);
    upload_info->url_id = (BYTE_T *)Malloc(strlen(item->valuestring) + 1);
    if (NULL == upload_info->url_id) {
        PR_ERR("httpc_proc_url_state url_id malloc error");
        return OPRT_MALLOC_FAILED;
    }
    memset(upload_info->url_id, 0, strlen(item->valuestring) + 1);
    memcpy(upload_info->url_id, item->valuestring, strlen(item->valuestring));

    item = ty_cJSON_GetObjectItem(result, "bucket");
    if (NULL == item) {
        PR_ERR("ty_cJSON_GetObjectItem bucket err");
        return OPRT_CJSON_GET_ERR;
    }

    upload_info->bucket = (BYTE_T *)Malloc(strlen(item->valuestring) + 1);
    if (NULL == upload_info->bucket) {
        PR_ERR("httpc_proc_url_state bucket malloc error");
        return OPRT_MALLOC_FAILED;
    }
    memset(upload_info->bucket, 0, strlen(item->valuestring) + 1);
    memcpy(upload_info->bucket, item->valuestring, strlen(item->valuestring));

    item = ty_cJSON_GetObjectItem(result, "expire");
    if (NULL == item) {
        PR_ERR("ty_cJSON_GetObjectItem expire err");
    } else {
        upload_info->expire = item->valueint;
        PR_DEBUG("recv expire:%d", upload_info->expire);
    }
    key = ty_cJSON_GetObjectItem(result, "localKey");
    if (NULL == key) {
        PR_ERR("cJSON_Parse:%s failed", result->valuestring);
        return OPRT_CJSON_PARSE_ERR;
    }
    upload_info->key = (UCHAR_T *)Malloc((strlen(key->valuestring) + 1) * SIZEOF(UCHAR_T));
    if (NULL == upload_info->key) {
        PR_ERR("httpc_proc_url_state photo_key malloc error");
        return OPRT_MALLOC_FAILED;
    }
    memset(upload_info->key, 0, (strlen(key->valuestring) + 1)*SIZEOF(UCHAR_T));
    memcpy(upload_info->key, key->valuestring, strlen(key->valuestring));
    PR_DEBUG("recv key:%s,photo_key:%s,len:%d",  key->valuestring, upload_info->key, strlen(key->valuestring));

    ckey = ty_cJSON_GetObjectItem(result, "cloudKey");
    if (NULL == ckey) {
        PR_ERR("cJSON_Parse:%s failed", result->valuestring);
        return OPRT_CJSON_PARSE_ERR;
    }
    upload_info->ckey = (UCHAR_T *)Malloc((strlen(ckey->valuestring) + 1) * SIZEOF(UCHAR_T));
    if (NULL == upload_info->ckey) {
        PR_ERR("httpc_proc_url_state photo_url malloc error");
        return OPRT_MALLOC_FAILED;
    }
    memset(upload_info->ckey, 0, (strlen(ckey->valuestring) + 1)*SIZEOF(UCHAR_T));
    memcpy(upload_info->ckey, ckey->valuestring, strlen(ckey->valuestring));
    PR_DEBUG("recv ckey:%s,photo_ckey:%s,len:%d",  ckey->valuestring, upload_info->ckey, strlen(ckey->valuestring));

    PR_DEBUG("httpc_proc_url_state succ!:%d", tuya_hal_system_getheapsize());

    return OPRT_OK;
}

STATIC OPERATE_RET tuya_svc_stream_proc_result(ty_cJSON *result)
{
    PR_DEBUG("into ty svc stream proc result");
    UINT_T url_len = 0;
    ty_cJSON *streamPush = NULL, *cloudStorage = NULL, *imgCloudStorage = NULL;
    OPERATE_RET op_ret = OPRT_OK;
    PR_DEBUG("tuya_svc_stream_proc_result:%d", tuya_hal_system_getheapsize());

    //cloudstorage image info
    imgCloudStorage = ty_cJSON_GetObjectItem(result, "imgCloudStorage");
    if (NULL == imgCloudStorage) {
        PR_ERR("ty_cJSON_GetObjectItem imgCloudStorage err");
        return OPRT_CJSON_GET_ERR;
    } else {
        PR_DEBUG("get imgCloudStorage!!!!");
        op_ret = httpc_proc_url_state(imgCloudStorage, g_photo_info);
        if (op_ret != OPRT_OK) {
            PR_ERR("get imgCloudStorage err!");
            return op_ret;
        }
    }

    //cloudstorage media info
    if (g_pt_ctrl.trigger_type == TRIGGER_TYPE_STREAM) {
        cloudStorage = ty_cJSON_GetObjectItem(result, "cloudStorage");
        if (NULL == cloudStorage) {
            PR_ERR("ty_cJSON_GetObjectItem cloudStorage err");
            return OPRT_CJSON_GET_ERR;
        } else {
            PR_DEBUG("get cloudStorage!");
            op_ret = httpc_proc_url_state(cloudStorage, g_stream_info);
            if (op_ret != OPRT_OK) {
                PR_ERR("get cloudStorage err!");
                return op_ret;
            }
        }
    }
    return OPRT_OK;
}

STATIC OPERATE_RET tuya_svc_stream_start(UCHAR_T type)
{
    PR_NOTICE("tuya svc stream start !推流开始");
    OPERATE_RET op_ret = OPRT_OK;
    ty_cJSON *root = NULL, *result = NULL;
    CHAR_T *out = NULL;
    root = ty_cJSON_CreateObject();
    if (NULL == root) {
        PR_ERR("cjson creat error");
        return OPRT_CR_CJSON_ERR;
    }
    PR_NOTICE("get gw cntl!");
    GW_CNTL_S *gw_cntl = get_gw_cntl();
    if (gw_cntl == NULL) {
        PR_ERR("get_gw_cntl get null");
        return OPRT_COM_ERROR;
    }

    ty_cJSON_AddStringToObject(root, "devId", gw_cntl->gw_if.id);
    ty_cJSON_AddNumberToObject(root, "streamType", type); //buff

    TIME_T tm = uni_time_get_posix();
//    PR_NOTICE("tm:%d", tm);
//    if(g_photo_info->name == NULL)
//    {
//        PR_NOTICE("photo_info-> name is null");
//        return OPRT_COM_ERROR;
//    }
    INT_T snlen = snprintf((CHAR_T *)g_photo_info->name, PHOTO_NAME_SIZE, "%010d.%s", tm, "jpg"); //time.jpg;
//    PR_NOTICE("snpritf exit;");
    ty_cJSON_AddStringToObject(root, "fileName", (CHAR_T *)g_photo_info->name); //buff
    ty_cJSON_AddStringToObject(root, "bizType", TY_URL_BIZTYPE_IMAGE);
    ty_cJSON_AddStringToObject(root, "contentType", TY_URL_CONTENTYPE_IMAGE);

    out = ty_cJSON_PrintUnformatted(root);
    PR_DEBUG("tuya_svc_stream_get out :%s", out);
    ty_cJSON_Delete(root);
    root = NULL;
    if (NULL == out) {
        PR_ERR("cJSON_PrintUnformatted failed");
        return OPRT_COM_ERROR ;
    }
    if (g_pt_ctrl.trigger_type == TRIGGER_TYPE_PHOTO) {
        op_ret = iot_httpc_common_post(TY_SVC_PHOTO_GET_ATOP, TY_SVC_PHOTO_GET_VER, NULL, gw_cntl->gw_if.id, out, NULL, &result);
    } else {
        op_ret = iot_httpc_common_post(TY_SVC_STREAM_GET_ATOP, TY_SVC_STREAM_GET_VER, NULL, gw_cntl->gw_if.id, out, NULL, &result);
    }


    Free(out);
    out = NULL;

    if (OPRT_OK != op_ret) {
        PR_ERR("httpc_common_post TY_SVC_STREAM_GET_ATOP failed! op_ret:%d", op_ret);
        return op_ret;
    }

    if (result == NULL) {
        PR_ERR("http TY_SVC_STREAM_GET_ATOP result is null");
        op_ret = OPRT_COM_ERROR;
        return op_ret;
    }

    op_ret = tuya_svc_stream_proc_result(result); //,info
    if (OPRT_OK != op_ret) {
        PR_ERR("httpc_proc_url_state failed! op_ret:%d", op_ret);
    }
    PR_NOTICE("ty_photo_url_get succ!:%d", tuya_hal_system_getheapsize());

    ty_cJSON_Delete(result);
    result = NULL;


    if (g_pt_ctrl.trigger_type == TRIGGER_TYPE_PHOTO) {
        ty_sys_dp_upload_photo(g_photo_info);
    } else if (g_pt_ctrl.trigger_type == TRIGGER_TYPE_STREAM) {
        ty_sys_dp_upload_media(g_stream_info);
        put_alarm();
//        tuya_doorbell_upload(g_photo_info);
    }
    return op_ret;
}


OPERATE_RET get_camer_config(IN CHAR_T *pstr, OUT IPC_MEDIA_INFO_S  *av_info, OUT INT_T *flash_rotat_angle, BOOL_T *is_uplord_new_skill, BOOL_T *is_support_audio)
{
    OPERATE_RET op_ret = OPRT_OK;
    cJSON *root = NULL;
    cJSON *item;
    PR_DEBUG("get_camer_config info:%s", pstr);
    root = cJSON_Parse(pstr);
    if (NULL == root) {
        PR_ERR("pdata:%s", pstr);
        return OPRT_COM_ERROR;
    }

    item = cJSON_GetObjectItem(root, "is_uplord_new_skill");
    if (NULL == item) {
        PR_ERR("cj get itemfailed");
        op_ret = OPRT_INVALID_PARM;
        goto PROCE_END;
    } else {
        *is_uplord_new_skill = item->valueint;
    }

    item = cJSON_GetObjectItem(root, "is_support_audio");
    if (NULL == item) {
        PR_ERR("cj get itemfailed");
        op_ret = OPRT_INVALID_PARM;
        goto PROCE_END;
    } else {
        *is_support_audio = item->valueint;
    }
    item = cJSON_GetObjectItem(root, "video_fps");
    if (NULL == item) {
        PR_ERR("cj get itemfailed");
        op_ret = OPRT_INVALID_PARM;
        goto PROCE_END;
    } else {
        av_info->video_fps[E_CHANNEL_VIDEO_MAIN] = item->valueint;
    }

    item = cJSON_GetObjectItem(root, "video_width");
    if (NULL == item) {
        PR_ERR("cj get item failed");
        op_ret = OPRT_INVALID_PARM;
        goto PROCE_END;
    } else {
        av_info->video_width[E_CHANNEL_VIDEO_MAIN] = item->valueint;
    }

    item = cJSON_GetObjectItem(root, "video_height");
    if (NULL == item) {
        PR_ERR("cj get item failed");
        op_ret = OPRT_INVALID_PARM;
        goto PROCE_END;
    } else {
        av_info->video_height[E_CHANNEL_VIDEO_MAIN] = item->valueint;
    }

    item = cJSON_GetObjectItem(root, "video_codec");
    if (NULL == item) {
        PR_ERR("cj get item  failed");
        op_ret = OPRT_INVALID_PARM;
        goto PROCE_END;
    } else {
        av_info->video_codec[E_CHANNEL_VIDEO_MAIN] = item->valueint;
    }

    item = cJSON_GetObjectItem(root, "audio_codec");
    if (NULL == item) {
        PR_ERR("cj get item failed");
        op_ret = OPRT_INVALID_PARM;
        goto PROCE_END;
    } else {
        av_info->audio_codec[E_CHANNEL_AUDIO] = item->valueint;
    }

    item = cJSON_GetObjectItem(root, "audio_sample");
    if (NULL == item) {
        PR_ERR("cj get item failed");
        op_ret = OPRT_INVALID_PARM;
        goto PROCE_END;
    } else {
        av_info->audio_sample[E_CHANNEL_AUDIO] = item->valueint;
    }

    item = cJSON_GetObjectItem(root, "audio_databits");
    if (NULL == item) {
        PR_ERR("cj get item failed");
        op_ret = OPRT_INVALID_PARM;
        goto PROCE_END;
    } else {
        av_info->audio_databits[E_CHANNEL_AUDIO] = item->valueint;
    }
    item = cJSON_GetObjectItem(root, "audio_channel");
    if (NULL == item) {
        PR_ERR("cj get item  failed");
        op_ret = OPRT_INVALID_PARM;
        goto PROCE_END;
    } else {
        av_info->audio_channel[E_CHANNEL_AUDIO] = item->valueint;
    }
    item = cJSON_GetObjectItem(root, "audio_fps");
    if (NULL == item) {
        PR_ERR("cj get item failed");
        op_ret = OPRT_INVALID_PARM;
        goto PROCE_END;
    } else {
        av_info->audio_fps[E_CHANNEL_AUDIO] = item->valueint;
    }

    item = cJSON_GetObjectItem(root, "rotat_angle");
    if (NULL == item) {
        PR_ERR("cj get item failed");
        op_ret = OPRT_INVALID_PARM;
        goto PROCE_END;
    } else {
        *flash_rotat_angle = item->valueint;
    }

PROCE_END:
    cJSON_Delete(root);

    return op_ret;
}

STATIC OPERATE_RET save_camer_config(IN IPC_MEDIA_INFO_S  *av_info, INT_T rotat_angle, BOOL_T is_uplord_new_skill, BOOL_T is_support_audio)
{
    UINT_T i;
    OPERATE_RET op_ret = OPRT_OK;
    PCHAR_T  out;
    cJSON *root = NULL;

    root = cJSON_CreateObject();
    if (NULL == root) {
        return OPRT_CR_CJSON_ERR;
    }
    cJSON_AddNumberToObject(root, "is_uplord_new_skill", is_uplord_new_skill);
    cJSON_AddNumberToObject(root, "is_support_audio", is_support_audio);
    cJSON_AddNumberToObject(root, "video_fps", av_info->video_fps[E_CHANNEL_VIDEO_MAIN]);
    cJSON_AddNumberToObject(root, "video_width", av_info->video_width[E_CHANNEL_VIDEO_MAIN]);
    cJSON_AddNumberToObject(root, "video_height", av_info->video_height[E_CHANNEL_VIDEO_MAIN]);
    cJSON_AddNumberToObject(root, "video_codec", av_info->video_codec[E_CHANNEL_VIDEO_MAIN]);
    cJSON_AddNumberToObject(root, "audio_codec", av_info->audio_codec[E_CHANNEL_AUDIO]);
    cJSON_AddNumberToObject(root, "audio_sample", av_info->audio_sample[E_CHANNEL_AUDIO]);
    cJSON_AddNumberToObject(root, "audio_databits", av_info->audio_databits[E_CHANNEL_AUDIO]);
    cJSON_AddNumberToObject(root, "audio_channel", av_info->audio_channel[E_CHANNEL_AUDIO]);
    cJSON_AddNumberToObject(root, "audio_fps", av_info->audio_fps[E_CHANNEL_AUDIO]);
    cJSON_AddNumberToObject(root, "rotat_angle", rotat_angle);
    out = cJSON_PrintUnformatted(root);
    cJSON_Delete(root);
    if (NULL == out) {
        return OPRT_MALLOC_FAILED;
    }
    PR_NOTICE("save_camer_config:%s", out);

    op_ret = wd_common_write(TY_SVC_CAMER_INFO, out, strlen(out));

    Free(out);

    return op_ret;
}


OPERATE_RET stream_infor_delete(VOID)
{
    OPERATE_RET op_ret = OPRT_OK;
    op_ret = wd_common_delete(TY_SVC_CAMER_INFO);
    if (OPRT_OK != op_ret) {
        PR_ERR("stream_infor_delete  err:%d", op_ret);
    }
    return op_ret;
}

STATIC BOOL_T ty_check_camer_info(IPC_MEDIA_INFO_S *av_info, IPC_MEDIA_INFO_S *flash_info)
{
    BOOL_T ret = TRUE;
    if (!g_pt_ctrl.is_support_audio) {
        if (av_info->video_fps[E_CHANNEL_VIDEO_MAIN] !=  flash_info->video_fps[E_CHANNEL_VIDEO_MAIN]  \
            || av_info->video_width[E_CHANNEL_VIDEO_MAIN] !=  flash_info->video_width[E_CHANNEL_VIDEO_MAIN] \
            || av_info->video_height[E_CHANNEL_VIDEO_MAIN] !=  flash_info->video_height[E_CHANNEL_VIDEO_MAIN]  \
            || av_info->video_codec[E_CHANNEL_VIDEO_MAIN] !=  flash_info->video_codec[E_CHANNEL_VIDEO_MAIN]) {
            return FALSE;
        }
    } else {
        if (av_info->video_fps[E_CHANNEL_VIDEO_MAIN] !=  flash_info->video_fps[E_CHANNEL_VIDEO_MAIN]  \
            || av_info->video_width[E_CHANNEL_VIDEO_MAIN] !=  flash_info->video_width[E_CHANNEL_VIDEO_MAIN] \
            || av_info->video_height[E_CHANNEL_VIDEO_MAIN] !=  flash_info->video_height[E_CHANNEL_VIDEO_MAIN]  \
            || av_info->video_codec[E_CHANNEL_VIDEO_MAIN] !=  flash_info->video_codec[E_CHANNEL_VIDEO_MAIN] \
            || av_info->audio_codec[E_CHANNEL_AUDIO] !=  flash_info->audio_codec[E_CHANNEL_AUDIO]  \
            || av_info->audio_sample[E_CHANNEL_AUDIO] !=  flash_info->audio_sample[E_CHANNEL_AUDIO] \
            || av_info->audio_databits[E_CHANNEL_AUDIO] !=  flash_info->audio_databits[E_CHANNEL_AUDIO]  \
            || av_info->audio_channel[E_CHANNEL_AUDIO] !=  flash_info->audio_channel[E_CHANNEL_AUDIO]  \
            || av_info->audio_fps[E_CHANNEL_AUDIO] !=  flash_info->audio_fps[E_CHANNEL_AUDIO]) {
            return FALSE;
        }
    }

    return ret;
}

STATIC UINT_T get_camera_is_h264(VOID_T)
{
    //0 jpeg 1 264  2 265
    return 0;
}

STATIC OPERATE_RET ty_photo_stream_init(UCHAR_T trigger_type)
{
    PR_NOTICE("into photo stream init!");
    OPERATE_RET op_ret = OPRT_OK;
    IPC_MEDIA_INFO_S av_info = {0};

    UINT_T out_video_width = camera_param.video_width;
    UINT_T out_video_height = camera_param.video_height;
#if (TCFG_HOST_AUDIO_ENABLE==1)
    ty_usb_audio_get_cfg(&audio_param.channel_num, &audio_param.bit_dept, &audio_param.sample_rate);
    PR_NOTICE("camera param:sample_rate %d bit_dept %d channel_num %d", audio_param.sample_rate, audio_param.bit_dept, audio_param.channel_num);
#endif
    if (0 == audio_param.sample_rate) {
        audio_param.sample_rate = AUDIO_RATE_DEFAULT;
    }
    if (trigger_type == TRIGGER_TYPE_PHOTO) {
        g_pt_ctrl.is_support_audio = FALSE;
        av_info.channel_enable[E_CHANNEL_VIDEO_MAIN] = TRUE;
        av_info.video_fps[E_CHANNEL_VIDEO_MAIN] = camera_param.video_fps;
        av_info.video_gop[E_CHANNEL_VIDEO_MAIN] = 0;
        av_info.video_bitrate[E_CHANNEL_VIDEO_MAIN] = TUYA_VIDEO_BITRATE_64K;//TUYA_VIDEO_BITRATE_2M;//TUYA_VIDEO_BITRATE_64K;

        av_info.video_width[E_CHANNEL_VIDEO_MAIN] = out_video_width;
        av_info.video_height[E_CHANNEL_VIDEO_MAIN] = out_video_height;
        av_info.video_freq[E_CHANNEL_VIDEO_MAIN] = 90000;
        av_info.video_codec[E_CHANNEL_VIDEO_MAIN] = TUYA_CODEC_VIDEO_MJPEG;
    } else if (trigger_type == TRIGGER_TYPE_STREAM) {
        g_pt_ctrl.is_support_audio = TRUE;
        av_info.channel_enable[E_CHANNEL_VIDEO_MAIN] = TRUE;
        av_info.video_fps[E_CHANNEL_VIDEO_MAIN] = 10;//camera_param.video_fps;
        if (0 == get_camera_is_h264()) {
            av_info.video_gop[E_CHANNEL_VIDEO_MAIN] = 0;
        } else {
            av_info.video_gop[E_CHANNEL_VIDEO_MAIN] = 30;
        }

        av_info.video_bitrate[E_CHANNEL_VIDEO_MAIN] = TUYA_VIDEO_BITRATE_64K;//TUYA_VIDEO_BITRATE_2M;//TUYA_VIDEO_BITRATE_64K;//TUYA_VIDEO_BITRATE_1M;//TUYA_VIDEO_BITRATE_64K;

        av_info.video_freq[E_CHANNEL_VIDEO_MAIN] = 90000;

//        if(0==get_camera_is_h264()) {
        av_info.video_width[E_CHANNEL_VIDEO_MAIN] = out_video_width;
        av_info.video_height[E_CHANNEL_VIDEO_MAIN] = out_video_height;
        av_info.video_codec[E_CHANNEL_VIDEO_MAIN] = TUYA_CODEC_VIDEO_MJPEG;
//        } else {
//            get_h264_width_and_height(&out_video_width, &out_video_height);
//            av_info.video_width[E_CHANNEL_VIDEO_MAIN] = out_video_width;
//            av_info.video_height[E_CHANNEL_VIDEO_MAIN] = out_video_height;
//            av_info.video_codec[E_CHANNEL_VIDEO_MAIN] = TUYA_CODEC_VIDEO_H264;
//        }

        av_info.audio_codec[E_CHANNEL_AUDIO] = TUYA_CODEC_AUDIO_PCM;
        av_info.audio_sample[E_CHANNEL_AUDIO] = 8000; //audio_param.sample_rate;
        av_info.audio_databits[E_CHANNEL_AUDIO] = 16;//audio_param.bit_dept;
        av_info.audio_channel[E_CHANNEL_AUDIO] = TUYA_AUDIO_CHANNEL_MONO;
        av_info.audio_fps[E_CHANNEL_AUDIO] = TY_STREAM_AUDIO_FPS;
    } else if (trigger_type == TRIGGER_TYPE_INIT) {
        g_pt_ctrl.is_support_audio = TRUE;
        av_info.channel_enable[E_CHANNEL_VIDEO_MAIN] = TRUE;
        av_info.video_fps[E_CHANNEL_VIDEO_MAIN] = camera_param.video_fps;
        if (0 == get_camera_is_h264()) {
            av_info.video_gop[E_CHANNEL_VIDEO_MAIN] = 0;
        } else {
            av_info.video_gop[E_CHANNEL_VIDEO_MAIN] = 30;
        }

        av_info.video_bitrate[E_CHANNEL_VIDEO_MAIN] = TUYA_VIDEO_BITRATE_64K;//TUYA_VIDEO_BITRATE_64K;//TUYA_VIDEO_BITRATE_1M;//TUYA_VIDEO_BITRATE_64K;

        av_info.video_freq[E_CHANNEL_VIDEO_MAIN] = 90000;

        if (0 == get_camera_is_h264()) {
            av_info.video_width[E_CHANNEL_VIDEO_MAIN] = out_video_width;
            av_info.video_height[E_CHANNEL_VIDEO_MAIN] = out_video_height;
            av_info.video_codec[E_CHANNEL_VIDEO_MAIN] = TUYA_CODEC_VIDEO_MJPEG;
        } else {
            get_h264_width_and_height(&out_video_width, &out_video_height);
            av_info.video_width[E_CHANNEL_VIDEO_MAIN] = out_video_width;
            av_info.video_height[E_CHANNEL_VIDEO_MAIN] = out_video_height;
            av_info.video_codec[E_CHANNEL_VIDEO_MAIN] = TUYA_CODEC_VIDEO_H264;
        }

        av_info.audio_codec[E_CHANNEL_AUDIO] = TUYA_CODEC_AUDIO_PCM;
        av_info.audio_sample[E_CHANNEL_AUDIO] = audio_param.sample_rate;
        av_info.audio_databits[E_CHANNEL_AUDIO] = audio_param.bit_dept;
        av_info.audio_channel[E_CHANNEL_AUDIO] = TUYA_AUDIO_CHANNEL_MONO;
        av_info.audio_fps[E_CHANNEL_AUDIO] = TY_STREAM_AUDIO_FPS;
    }

    BOOL_T need_uplord_skill = FALSE;
    IPC_MEDIA_INFO_S flash_av_info = {0};
    INT_T flash_rotat_angle = 0;
    INT_T uplord_rotat_angle = -1;
    TY_LORD_PARAM uplord_param = {0};
    INT_T read_len = 0;
    CHAR_T *flash_dat = NULL;
    UINT_T flash_len = 0;
    BOOL_T is_support_audio;
    BOOL_T is_uplord_new_skill;
    op_ret = wd_common_read(TY_SVC_CAMER_INFO, &flash_dat, &flash_len);
    if (OPRT_OK != op_ret) {
        need_uplord_skill = TRUE;
        PR_DEBUG("wd_common_read fail need_uplord_skill");
    } else {
        if (OPRT_OK != get_camer_config(flash_dat, &flash_av_info, &flash_rotat_angle, &is_uplord_new_skill, &is_support_audio)) {
            need_uplord_skill = TRUE;
            PR_DEBUG("get_camer_config fail need_uplord_skill");
        } else {
            if (trigger_type) {
                if (!is_uplord_new_skill) {
                    need_uplord_skill = TRUE;
                    PR_DEBUG("uplord fail need_uplord_skill");
                } else if (FALSE == ty_check_camer_info(&flash_av_info, &av_info)) {
                    need_uplord_skill = TRUE;
                    PR_DEBUG("check fail need_uplord_skill");
                } else if (is_support_audio != g_pt_ctrl.is_support_audio) {
                    need_uplord_skill = TRUE;
                    PR_DEBUG("is_support_audio fail need_uplord_skill");
                }
            } else {
                if (!is_uplord_new_skill) {
                    need_uplord_skill = TRUE;
                    memcpy(&av_info, &flash_av_info, SIZEOF(IPC_MEDIA_INFO_S));
                    PR_DEBUG("____uplord fail need_uplord_skill");
                }
            }
        }

    }
    Free(flash_dat);
    flash_dat = NULL;
    tuya_ipc_streamer_set_max_frame_size(MAX_FRGE_SIZE);
//    tuya_ipc_streamer_set_memory_save_mode();
    PR_DEBUG("set pstreamer cb ");

    TSTREAMER_S *pstreamer = GetTStreamerInstance();
    pstreamer->RegisterCb(__event_cb, __recv_audio_cb, __get_frame_cb);
    pstreamer->SupportAudio(g_pt_ctrl.is_support_audio);
    //pstreamer->SetFrameInterval(5);
    pstreamer->SetMediaSetting(&av_info);

    /* if (need_uplord_skill) { */
    /* op_ret = ty_param_load(LORD_CFG_PARAM_E, &uplord_rotat_angle, sizeof(INT_T), &read_len); */
    /* if (OPRT_OK != op_ret) { */
    /* if (OPRT_OK != ty_param_load(LORD2_CFG_PARAM_E, &uplord_param, sizeof(TY_LORD_PARAM), &read_len)) { */
    /* uplord_rotat_angle = PHONE_ROTE_DEFAULT; */
    /* } else { */
    /* uplord_rotat_angle = uplord_param.phone_rotation; */
    /* } */
    /* } */
    uplord_rotat_angle = camera_param.video_rotat_angle;
    PR_DEBUG("into ty update skill rotate, rotat:%d", uplord_rotat_angle);
    op_ret = ty_update_skill_and_rotate(uplord_rotat_angle);
    if (OPRT_OK == op_ret) {
        is_uplord_new_skill = TRUE;
        save_camer_config(&av_info, uplord_rotat_angle, is_uplord_new_skill, g_pt_ctrl.is_support_audio);
    }
    /* } else { */
    /* PR_DEBUG("not need_uplord_skill!!"); */
    /* } */
    return op_ret;
}

STATIC OPERATE_RET ty_photo_stream_first_uplord(UCHAR_T trigger_type)
{
    OPERATE_RET op_ret = OPRT_OK;
    IPC_MEDIA_INFO_S av_info = {0};

    UINT_T out_video_width = camera_param.video_width;
    UINT_T out_video_height = camera_param.video_height;
#if (TCFG_HOST_AUDIO_ENABLE==1)
    ty_usb_audio_get_cfg(&audio_param.channel_num, &audio_param.bit_dept, &audio_param.sample_rate);
    PR_NOTICE("camera param:sample_rate %d bit_dept %d channel_num %d", audio_param.sample_rate, audio_param.bit_dept, audio_param.channel_num);
#endif
    if (0 == audio_param.sample_rate) {
        audio_param.sample_rate = AUDIO_RATE_DEFAULT;
    }
    if (trigger_type == TRIGGER_TYPE_PHOTO) {
        g_pt_ctrl.is_support_audio = FALSE;
        av_info.channel_enable[E_CHANNEL_VIDEO_MAIN] = TRUE;
        av_info.video_fps[E_CHANNEL_VIDEO_MAIN] = camera_param.video_fps;
        av_info.video_gop[E_CHANNEL_VIDEO_MAIN] = 0;
        av_info.video_bitrate[E_CHANNEL_VIDEO_MAIN] = TUYA_VIDEO_BITRATE_64K;

        av_info.video_width[E_CHANNEL_VIDEO_MAIN] = out_video_width;
        av_info.video_height[E_CHANNEL_VIDEO_MAIN] = out_video_height;
        av_info.video_freq[E_CHANNEL_VIDEO_MAIN] = 90000;
        av_info.video_codec[E_CHANNEL_VIDEO_MAIN] = TUYA_CODEC_VIDEO_MJPEG;
    } else if (trigger_type == TRIGGER_TYPE_STREAM) {
        g_pt_ctrl.is_support_audio = TRUE;
        av_info.channel_enable[E_CHANNEL_VIDEO_MAIN] = TRUE;
        av_info.video_fps[E_CHANNEL_VIDEO_MAIN] = camera_param.video_fps;
        if (0 == get_camera_is_h264()) {
            av_info.video_gop[E_CHANNEL_VIDEO_MAIN] = 0;
        } else {
            av_info.video_gop[E_CHANNEL_VIDEO_MAIN] = 30;
        }

        av_info.video_bitrate[E_CHANNEL_VIDEO_MAIN] = TUYA_VIDEO_BITRATE_64K;

        av_info.video_freq[E_CHANNEL_VIDEO_MAIN] = 90000;

        if (0 == get_camera_is_h264()) {
            av_info.video_width[E_CHANNEL_VIDEO_MAIN] = out_video_width;
            av_info.video_height[E_CHANNEL_VIDEO_MAIN] = out_video_height;
            av_info.video_codec[E_CHANNEL_VIDEO_MAIN] = TUYA_CODEC_VIDEO_MJPEG;
        } else {
            get_h264_width_and_height(&out_video_width, &out_video_height);
            av_info.video_width[E_CHANNEL_VIDEO_MAIN] = out_video_width;
            av_info.video_height[E_CHANNEL_VIDEO_MAIN] = out_video_height;
            av_info.video_codec[E_CHANNEL_VIDEO_MAIN] = TUYA_CODEC_VIDEO_H264;
        }

        av_info.audio_codec[E_CHANNEL_AUDIO] = TUYA_CODEC_AUDIO_PCM;
        av_info.audio_sample[E_CHANNEL_AUDIO] = audio_param.sample_rate;
        av_info.audio_databits[E_CHANNEL_AUDIO] = audio_param.bit_dept;
        av_info.audio_channel[E_CHANNEL_AUDIO] = TUYA_AUDIO_CHANNEL_MONO;
        av_info.audio_fps[E_CHANNEL_AUDIO] = TY_STREAM_AUDIO_FPS;
    } else if (trigger_type == TRIGGER_TYPE_INIT) {
        g_pt_ctrl.is_support_audio = TRUE;
        av_info.channel_enable[E_CHANNEL_VIDEO_MAIN] = TRUE;
        av_info.video_fps[E_CHANNEL_VIDEO_MAIN] = camera_param.video_fps;
        if (0 == get_camera_is_h264()) {
            av_info.video_gop[E_CHANNEL_VIDEO_MAIN] = 0;
        } else {
            av_info.video_gop[E_CHANNEL_VIDEO_MAIN] = 30;
        }

        av_info.video_bitrate[E_CHANNEL_VIDEO_MAIN] = TUYA_VIDEO_BITRATE_64K;

        av_info.video_freq[E_CHANNEL_VIDEO_MAIN] = 90000;

        if (0 == get_camera_is_h264()) {
            av_info.video_width[E_CHANNEL_VIDEO_MAIN] = out_video_width;
            av_info.video_height[E_CHANNEL_VIDEO_MAIN] = out_video_height;
            av_info.video_codec[E_CHANNEL_VIDEO_MAIN] = TUYA_CODEC_VIDEO_MJPEG;
        } else {
            get_h264_width_and_height(&out_video_width, &out_video_height);
            av_info.video_width[E_CHANNEL_VIDEO_MAIN] = out_video_width;
            av_info.video_height[E_CHANNEL_VIDEO_MAIN] = out_video_height;
            av_info.video_codec[E_CHANNEL_VIDEO_MAIN] = TUYA_CODEC_VIDEO_H264;
        }

        av_info.audio_codec[E_CHANNEL_AUDIO] = TUYA_CODEC_AUDIO_PCM;
        av_info.audio_sample[E_CHANNEL_AUDIO] = audio_param.sample_rate;
        av_info.audio_databits[E_CHANNEL_AUDIO] = audio_param.bit_dept;
        av_info.audio_channel[E_CHANNEL_AUDIO] = TUYA_AUDIO_CHANNEL_MONO;
        av_info.audio_fps[E_CHANNEL_AUDIO] = TY_STREAM_AUDIO_FPS;
    }

    INT_T uplord_rotat_angle = -1;
    TY_LORD_PARAM uplord_param = {0};
    INT_T read_len = 0;

    tuya_ipc_streamer_set_max_frame_size(MAX_FRGE_SIZE);
//    tuya_ipc_streamer_set_memory_save_mode();
    TSTREAMER_S *pstreamer = GetTStreamerInstance();
    if (pstreamer) {
        pstreamer->RegisterCb(__event_cb, __recv_audio_cb, __get_frame_cb);
        pstreamer->SupportAudio(g_pt_ctrl.is_support_audio);
        //pstreamer->SetFrameInterval(5);
        pstreamer->SetMediaSetting(&av_info);
    }

    op_ret = ty_param_load(LORD_CFG_PARAM_E, &uplord_rotat_angle, sizeof(INT_T), &read_len);
    op_ret = ty_param_load(LORD_CFG_PARAM_E, (UCHAR_T *)(&uplord_param), sizeof(TY_LORD_PARAM), &read_len);
    if (OPRT_OK != op_ret) {
        if (OPRT_OK != ty_param_load(LORD2_CFG_PARAM_E, &uplord_param, sizeof(TY_LORD_PARAM), &read_len)) {
            uplord_rotat_angle = PHONE_ROTE_DEFAULT;
        } else {
            uplord_rotat_angle = uplord_param.phone_rotation;
        }
    }
    /* uplord_rotat_angle = 90; */

    op_ret = ty_update_skill_and_rotate(uplord_rotat_angle);
    if (OPRT_OK == op_ret) {
        save_camer_config(&av_info, uplord_rotat_angle, TRUE, g_pt_ctrl.is_support_audio);
    } else {
        save_camer_config(&av_info, uplord_rotat_angle, FALSE, g_pt_ctrl.is_support_audio);
    }

    return op_ret;
}

STATIC OPERATE_RET ty_photo_stream_init_and_start(VOID)
{
    PR_DEBUG("into photo stream init and start!");
    OPERATE_RET op_ret = OPRT_OK;
    UCHAR_T type = E_STREAM_VIDEO_MAIN;
    if (g_pt_ctrl.trigger_type == TRIGGER_TYPE_PHOTO) {
        type = E_STREAM_VIDEO_MAIN;
    } else {
        type = E_STREAM_VIDEO_AUDIO;
    }
    g_pt_ctrl.proc_state = PT_PROC_START;
    op_ret = ty_photo_stream_init(g_pt_ctrl.trigger_type);
    if (op_ret == OPRT_OK) {
        PR_DEBUG("svc stream start!");
        op_ret = tuya_svc_stream_start(type);
    }
    return op_ret;
}

STATIC OPERATE_RET ty_sys_dp_upload_photo(UPLOAD_INFO *upload_info)
{
    OPERATE_RET op_ret = OPRT_OK;
    ty_cJSON *root = NULL, *pt_arry = NULL, *file_arry = NULL, *ext = NULL;
    UCHAR_T *out = NULL;
    UCHAR_T expire_time[11];
    memset(expire_time, 0, sizeof(expire_time));
    PR_NOTICE("ty_sys_dp_upload_photo :%d", tuya_hal_system_getheapsize());
    root = ty_cJSON_CreateObject();
    ext = ty_cJSON_CreateObject();
    pt_arry = ty_cJSON_CreateArray();
    file_arry = ty_cJSON_CreateArray();

    if (upload_info == NULL) {
        PR_ERR("ty_sys_dp_upload_photo param error!");
        return OPRT_INVALID_PARM;
    }
    if ((NULL == root) || (NULL == pt_arry) || (NULL == file_arry) || (NULL == ext)) {
        PR_ERR("cjson creat error");
        return OPRT_CR_CJSON_ERR;
    }

    ty_cJSON_AddStringToObject(root, "v", TY_DP212_VER_50);
    ty_cJSON_AddStringToObject(root, "cmd", TY_DP212_CMD_COVER);
    ty_cJSON_AddStringToObject(root, "type", TY_DP212_TYPE_IMAGE);
    ty_cJSON_AddStringToObject(root, "with", TY_DP212_WITH_RESORCES);
    ty_cJSON_AddBoolToObject(root, "alarm", TRUE);//默认给1

    /*add time segment*/
    TIME_T time = ty_trigger_time_proc(upload_info->time_flag, upload_info->tm);
    time_overall = time;
    ty_cJSON_AddNumberToObject(root, "time", time);
    sprintf(expire_time, "%d", time + upload_info->expire);

    /*add files segment*/
    ty_cJSON_AddItemToArray(pt_arry, ty_cJSON_CreateString(upload_info->bucket));
    ty_cJSON_AddItemToArray(pt_arry, ty_cJSON_CreateString(upload_info->ckey));
    ty_cJSON_AddItemToArray(pt_arry, ty_cJSON_CreateString(upload_info->key));
    ty_cJSON_AddItemToArray(pt_arry, ty_cJSON_CreateString(expire_time));
    ty_cJSON_AddItemToArray(file_arry, pt_arry);

    ty_cJSON_AddItemToObject(root, "files", file_arry);

    /*add ext segment*/
    ty_cJSON_AddBoolToObject(ext, "record", TRUE);
    ty_cJSON_AddNumberToObject(ext, "id", upload_info->id);
    ty_cJSON_AddNumberToObject(ext, "type", upload_info->event_type);
    ty_cJSON_AddStringToObject(ext, "fileId", upload_info->url_id);
    ty_cJSON_AddBoolToObject(ext, "hasMedia", FALSE);
    ty_cJSON_AddItemToObject(root, "ext", ext);

    out = ty_cJSON_PrintUnformatted(root);

    PR_DEBUG("ty_photo_sys_dp_upload out :%s", out);

    ty_cJSON_Delete(root);
    root = NULL;
    if (NULL == out) {
        PR_ERR("cJSON_PrintUnformatted failed");
        return OPRT_COM_ERROR;
    }

    op_ret = dev_report_dp_raw_sync_extend_with_time(get_gw_cntl()->gw_if.id, PT_SYS_DP, out, strlen(out), 5, TRUE, NULL);
    if (OPRT_OK != op_ret) {
        PR_ERR("dev_report_dp_raw_sync failed op_ret:%d", op_ret);
        Free(out);
        out = NULL;
        return OPRT_COM_ERROR;
    }
    Free(out);
    out = NULL;

    PR_NOTICE("ty_photo_sys_dp_upload succ:%d", tuya_hal_system_getheapsize());
    return OPRT_OK;
}

STATIC OPERATE_RET ty_sys_dp_upload_media(UPLOAD_INFO *upload_info)
{
    OPERATE_RET op_ret = OPRT_OK;
    ty_cJSON *root = NULL, *pt_arry = NULL, *md_arry = NULL, *file_arry = NULL, *ext = NULL;
    UCHAR_T *out = NULL;
    UCHAR_T expire_time[20];
    memset(expire_time, 0, sizeof(expire_time));
    PR_NOTICE("ty_sys_dp_upload_media :%d", tuya_hal_system_getheapsize());
    root = ty_cJSON_CreateObject();
    ext = ty_cJSON_CreateObject();
    pt_arry = ty_cJSON_CreateArray();
    md_arry = ty_cJSON_CreateArray();
    file_arry = ty_cJSON_CreateArray();

    if (upload_info == NULL) {
        PR_ERR("ty_sys_dp_upload_media param error!");
        return OPRT_INVALID_PARM;
    }

    if ((NULL == root) || (NULL == pt_arry) || (NULL == file_arry) || (NULL == ext)) {
        PR_ERR("cjson creat error");
        return OPRT_CR_CJSON_ERR;
    }

    ty_cJSON_AddStringToObject(root, "v", TY_DP212_VER_50);
    ty_cJSON_AddStringToObject(root, "cmd", TY_DP212_CMD_VIDEO);
    ty_cJSON_AddStringToObject(root, "type", TY_DP212_TYPE_MEDIA);
    ty_cJSON_AddStringToObject(root, "with", TY_DP212_WITH_RESORCES);
    ty_cJSON_AddBoolToObject(root, "alarm", TRUE);//默认给1

    /*add time segment*/
//    TIME_T time = ty_trigger_time_proc(upload_info->time_flag,upload_info->tm);
    TIME_T time = uni_time_get_posix();
    ty_cJSON_AddNumberToObject(root, "time", time);
    time_overall = time;
    /*add files segment*/
    ty_cJSON_AddItemToArray(pt_arry, ty_cJSON_CreateString(g_photo_info->bucket));
    ty_cJSON_AddItemToArray(pt_arry, ty_cJSON_CreateString(g_photo_info->ckey));
    ty_cJSON_AddItemToArray(pt_arry, ty_cJSON_CreateString(g_photo_info->key));
    sprintf(expire_time, "%d", time + g_photo_info->expire);
    ty_cJSON_AddItemToArray(pt_arry, ty_cJSON_CreateString(expire_time));
    ty_cJSON_AddItemToArray(file_arry, pt_arry);

    ty_cJSON_AddItemToArray(md_arry, ty_cJSON_CreateString(upload_info->bucket));
    ty_cJSON_AddItemToArray(md_arry, ty_cJSON_CreateString(upload_info->ckey));
    ty_cJSON_AddItemToArray(md_arry, ty_cJSON_CreateString(upload_info->key));
    sprintf(expire_time, "%d", time + upload_info->expire);
    ty_cJSON_AddItemToArray(md_arry, ty_cJSON_CreateString(expire_time));
    ty_cJSON_AddItemToArray(file_arry, md_arry);

    ty_cJSON_AddItemToObject(root, "files", file_arry);

    /*add ext segment*/
    ty_cJSON_AddBoolToObject(ext, "record", TRUE);
    ty_cJSON_AddNumberToObject(ext, "id", upload_info->id);
    ty_cJSON_AddNumberToObject(ext, "type", upload_info->event_type);
    ty_cJSON_AddStringToObject(ext, "fileId", upload_info->url_id);
    ty_cJSON_AddItemToObject(root, "ext", ext);

    out = ty_cJSON_PrintUnformatted(root);

    PR_DEBUG("ty_photo_sys_dp_upload out :%s", out);

    ty_cJSON_Delete(root);
    root = NULL;
    if (NULL == out) {
        PR_ERR("cJSON_PrintUnformatted failed");
        return OPRT_COM_ERROR;
    }

    op_ret = dev_report_dp_raw_sync_extend_with_time(get_gw_cntl()->gw_if.id, PT_SYS_DP, out, strlen(out), 5, TRUE, NULL);
    if (OPRT_OK != op_ret) {
        PR_ERR("dev_report_dp_raw_sync failed op_ret:%d", op_ret);
        Free(out);
        out = NULL;
        return OPRT_COM_ERROR;
    }
    Free(out);
    out = NULL;

    PR_NOTICE("ty_photo_sys_dp_upload succ:%d", tuya_hal_system_getheapsize());
    return OPRT_OK;
}

STATIC VOID ty_data_info_clean(UPLOAD_INFO **info)
{
    UPLOAD_INFO *upload_info = *info;
    //PR_NOTICE("ty_data_info_clean :%d",tuya_hal_system_getheapsize());
    if (NULL == upload_info) {
        PR_NOTICE("g_photo_info is null,do not need free");
        return;
    }
    if (NULL != upload_info->url) {
        PR_DEBUG("free photo_url");
        Free(upload_info->url);
        upload_info->url = NULL;
    }
    if (NULL != upload_info->auth) {
        PR_DEBUG("free photo_auth");
        Free(upload_info->auth);
        upload_info->auth = NULL;
    }
    if (NULL != upload_info->date) {
        PR_DEBUG("free photo_date");
        Free(upload_info->date);
        upload_info->date = NULL;
    }
    if (NULL != upload_info->cont) {
        PR_DEBUG("free photo_cont");
        Free(upload_info->cont);
        upload_info->cont = NULL;
    }
    if (NULL != upload_info->ckey) {
        PR_DEBUG("free photo_ckey");
        Free(upload_info->ckey);
        upload_info->ckey = NULL;
    }
    if (NULL != upload_info->url_id) {
        PR_DEBUG("free id");
        Free(upload_info->url_id);
        upload_info->url_id = NULL;
    }
    if (NULL != upload_info->key) {
        PR_DEBUG("free photo_key");
        Free(upload_info->key);
        upload_info->key = NULL;
    }

    if (NULL != upload_info->bucket) {
        PR_DEBUG("free bucket");
        Free(upload_info->bucket);
        upload_info->bucket = NULL;
    }
    if (NULL != upload_info) {
        PR_DEBUG("free g_photo_info");
        Free(upload_info);
        upload_info = NULL;
        *info = NULL;
    }
    //PR_NOTICE("ty_photo_info_clean succ!!!");
    return;
}
/***********************************************************
*  Function: tuya_doorbell_mq43_msg_upload
*  Input: none
*  Output: none
*  Return: none
*  Note: 43 Popup window
***********************************************************/
STATIC OPERATE_RET tuya_doorbell_mq43_msg_upload(UPLOAD_INFO *upload_info)
{
    OPERATE_RET op_ret = OPRT_OK;
    ty_cJSON *root = NULL, *data = NULL;
    UCHAR_T *out = NULL;
    UINT_T wakeup_data;
    GW_CNTL_S *gw_cntl = get_gw_cntl();

    if (NULL == gw_cntl) {
        PR_ERR("get_gw_cntl is null");
        return OPRT_COM_ERROR;
    }

    PR_NOTICE("ty_doorbell_mq43_msg_upload :%d", tuya_hal_system_getheapsize());
    root = ty_cJSON_CreateObject();
    if (NULL == root) {
        return OPRT_MALLOC_FAILED;
    }

    ty_cJSON_AddNumberToObject(root, "protocol", 43);
    TIME_T time = ty_trigger_time_proc(upload_info->time_flag, upload_info->tm);
    ty_cJSON_AddNumberToObject(root, "time", time);

    ty_cJSON_AddStringToObject(root, "etype", "doorlock");

    CHAR_T edata1[20] = {0};
    CHAR_T edata2[20] = {0};
    CHAR_T edata3[40] = {0};

    wakeup_data = hash_crc32i_total(gw_cntl->gw_actv.local_key, strlen(gw_cntl->gw_actv.local_key));

    snprintf(edata1, 20, "%x", wakeup_data);
    snprintf(edata2, 20, "%d", (INT_T)time);
    strncpy(edata3, edata1, 39);
    strcat(edata3, edata2);
    ty_cJSON_AddStringToObject(root, "edata", edata3);

    ty_cJSON_AddStringToObject(root, "filename", upload_info->name);

    ty_cJSON_AddStringToObject(root, "devId", gw_cntl->gw_if.id);

    out = ty_cJSON_PrintUnformatted(root);
    PR_DEBUG("ty_doorbell_mq43_msg_upload out :%s", out);
    ty_cJSON_Delete(root);
    root = NULL;
    if (NULL == out) {
        PR_ERR("cJSON_PrintUnformatted failed");
        return OPRT_COM_ERROR;
    }

    INT_T ret = mqc_send_custom_mqtt_msg(43, out);
    if (OPRT_OK > ret) {
        PR_ERR("mqc_send_custom_mqtt_msg failed op_ret:%d", ret);
        Free(out);
        out = NULL;
        return OPRT_COM_ERROR;
    }
    Free(out);
    out = NULL;

    PR_NOTICE("ty_doorbell_mq43_msg_upload succ:%d,ret:%d", tuya_hal_system_getheapsize(), ret);
    return OPRT_OK;
}

STATIC VOID tuya_doorbell_upload(UPLOAD_INFO *upload_info)
{
    PR_NOTICE("evevt type is:%d", upload_info->event_type);
    if (upload_info->event_type == PT_EVENT_ALARM_PRY || \
        upload_info->event_type == PT_EVENT_ALARM_REMOTE || \
        upload_info->event_type == PT_EVENT_ULOCK_REMOTE || \
        upload_info->event_type == PT_EVENT_DOORBELL_REQUEST || \
        upload_info->event_type == PT_EVENT_DOORBELL_AND_REMOTE || \
        upload_info->event_type == PT_EVENT_ALARM_STAY) {
        //tuya_doorbell_mq43_msg_upload(upload_info);
    }
}


STATIC VOID photo_process(PVOID_T pArg)
{
    PR_ERR("into photo process");
    OPERATE_RET op_ret = OPRT_OK;
//    P_MSG_LIST msgListNode;
    PHOTO_CTRL_MSG *msg_data;
    UCHAR_T ret = 0;
    GW_WIFI_NW_STAT_E cur_nw_stat;
    STATIC UINT_T cnt = 0;
    int msg[16] = {0,};
    while (1) {
//        op_ret = WaitMessage(g_pt_ctrl.msg_que,&msgListNode);
        PR_DEBUG("into os_q_pend");
        op_ret = os_q_pend(&g_pt_ctrl.msg_que, 0, msg);
        if (op_ret != OPRT_OK && msg[0] == NULL) {
            if (op_ret != OPRT_MSG_LIST_EMPTY) {
                PR_ERR("WaitMessage op_ret:%d", op_ret);
            }
            continue;
        }
        msg_data = (PHOTO_CTRL_MSG *)msg[0];
        PR_NOTICE("os_q_pend cmd %d", msg_data->cmd);
        PR_DEBUG("printf pend data:");
        put_buf(msg_data->data, msg_data->data_len);
        switch (msg_data->cmd) {
        case PT_DATA_INIT: {
            PR_DEBUG("into data init!");
            g_pt_ctrl.photo_id = 0;
            g_pt_ctrl.seq_id = 0;
            g_pt_ctrl.audio_seq = 0;
            struct jpeg_image_info image_info = {0};
            op_ret = ty_photo_data_init_proc(msg_data->data);
            if (op_ret != OPRT_OK) {
                ret = PT_RET_OTHER_FAILED;
                PR_ERR("ty_photo_data_init_proc op_ret:%d", op_ret);
                ty_photo_send_msg(PT_DATA_END, &ret, 1);
            } else {
                PR_DEBUG("into ty photo send msg");
                ty_photo_send_msg(PT_STREAM_START, NULL, 0);
            }
        }
        break;
        case PT_STREAM_START: {
            PR_DEBUG("into stream start!");
            if (g_pt_ctrl.is_busy != TRUE) {
                break;
            }
            op_ret = get_wf_gw_nw_status(&cur_nw_stat);
            if (OPRT_OK == op_ret && (cur_nw_stat == STAT_CLOUD_CONN || cur_nw_stat == STAT_AP_CLOUD_CONN)) {
                op_ret = ty_photo_stream_init_and_start();
                if (op_ret != OPRT_OK) {
                    ret = PT_RET_NET_FAILED;
                    ty_photo_send_msg(PT_DATA_END, &ret, 1);
                } else {
                    PR_NOTICE("TUYA_STREAM_START succ!:%d", tuya_hal_system_getheapsize());
                }
            } else {
                tuya_hal_system_sleep(10);
                ty_photo_send_msg(PT_STREAM_START, NULL, 0);
            }
        }
        break;

        case PT_DATA_END: {
//                PR_DEBUG("into data end!");
            UCHAR_T msg_result = *((UCHAR_T *)msg_data->data);
            PR_NOTICE("ty_photo_ack = %d g_photo_info=%d", msg_result, g_photo_info);
#if 1
            ty_data_info_clean(&g_photo_info);
            ty_data_info_clean(&g_stream_info);
            tuya_clear_stream_que();
            if (NULL != last_stream_info) {
                free(last_stream_info);
                last_stream_info = NULL;
            }
            //todo
            if (g_pt_ctrl.trigger_type == TRIGGER_TYPE_STREAM) {
                ty_device_net_audio(FALSE);
            }

            g_pt_ctrl.stream_is_busy = FALSE;
            g_pt_ctrl.is_busy = FALSE;
            first_image_len = 0;

#endif // 1

            PR_NOTICE("PT_DATA_END succ! type=%d", g_pt_ctrl.trigger_type);
        }
        break;
        case PT_STREAM_DATA_START: {
            PR_DEBUG("into stream data start!");
            UCHAR_T msg_result = *((UCHAR_T *)msg_data->data);

            PR_NOTICE("ty_photo_ack = %d g_photo_info=%d", msg_result, g_photo_info);
            PR_NOTICE("PT_STREAM_DATA_START succ! type=%d", g_pt_ctrl.trigger_type);
//                tuya_push_stream_start();
//                sys_start_timer(g_pt_ctrl.timer, DATA_TIMEOUT, TIMER_ONCE);
            if (FALSE == is_audio_play_open()) {
                ty_device_net_audio(TRUE);
            }
            if (g_pt_ctrl.trigger_type == TRIGGER_TYPE_STREAM) {
                if (g_photo_info) {
                    memcpy(g_pt_ctrl.tm, g_photo_info->tm, UPLOAD_TIMEBUFF_SIZE);
                }
            }
            ty_data_info_clean(&g_photo_info);
            ty_data_info_clean(&g_stream_info);
            g_pt_ctrl.is_busy = FALSE;
        }
        break;
        }

        if (msg_data) {
            if (msg_data->data) {
                tal_free(msg_data->data);
            }
            tal_free(msg_data);
            msg_data = NULL;
        }
    }
}

STATIC VOID ty_stream_timeout_cb(UINT_T timerID, PVOID_T pTimerArg)
{
    UCHAR_T ret = PT_RET_TIME_OUT;
    USHORT_T id = 0;
    PR_NOTICE("ty_stream_timeout_cb proc_state =%d g_pt_ctrl.is_busy=%d", g_pt_ctrl.proc_state, g_pt_ctrl.is_busy);
    if (PT_PROC_NULL == g_pt_ctrl.proc_state || PT_PROC_START == g_pt_ctrl.proc_state) {
        ret = PT_RET_NET_FAILED;
    }
    g_pt_ctrl.stream_is_over_time = TRUE;
    ty_photo_send_msg(PT_DATA_END, &ret, 1);
    return ;
}

OPERATE_RET ty_photo_proc_init(TY_STREAM_SEND_FRAME_HANDLE_CB cb)
{
#if 1
    OPERATE_RET op_ret = OPRT_OK;
    TAL_PR_DEBUG("ty_photo_proc_init");
    if (g_pt_ctrl.photo_init) {
        PR_NOTICE("ty_photo_proc_init is already done!!!");
        return op_ret;
    }
//    if(NULL == cb) {
//        return OPRT_INVALID_PARM;
//    }

    memset(&g_pt_ctrl, 0, sizeof(PHOTO_CRTL));
    g_pt_ctrl.trigger_type = TRIGGER_TYPE_INIT;
//	g_pt_ctrl.cb = cb;
    PR_DEBUG("ty_photo_proc_init os_q_create");
    QS queue_size = (SIZEOF(PHOTO_CTRL_MSG *) * 20 + sizeof(WORD) - 1) / sizeof(WORD);
    op_ret = os_q_create(&g_pt_ctrl.msg_que, queue_size);
    if (OPRT_OK != op_ret) {
        PR_ERR("os_q_create op_ret:%d", op_ret);
        return op_ret;
    }

    op_ret = ty_stream_queue_init();
    if (OPRT_OK != op_ret) {
        PR_ERR("ty_stream_queue_init op_ret:%d", op_ret);
        return op_ret;
    }

    THRD_PARAM_S thrd_param;
    thrd_param.priority = TRD_PRIO_2;
    thrd_param.stackDepth = 1024 * 5;
    thrd_param.thrdname = "ty_photo_task";
    op_ret = CreateAndStart(&g_pt_ctrl.handle, NULL, NULL, photo_process, NULL, &thrd_param);
    if (OPRT_OK != op_ret) {
        PR_ERR("CreateAndStart failed!");
        return op_ret;
    }

//    op_ret = sys_add_timer(ty_stream_timeout_cb, NULL, &g_pt_ctrl.timer);
//    if(op_ret != OPRT_OK) {
//        PR_ERR("sys_add_timer query_master_tm_cb failed! op_ret:%d", op_ret);
//        return op_ret;
//    }
#endif // 0

    tuya_ipc_streamer_init();
    tuya_ipc_packager_init();
    tuya_ipc_encrypt_init();

    g_pt_ctrl.photo_init = TRUE;

    PR_NOTICE("ty_photo_proc_init malloc sucess:%d", tuya_hal_system_getheapsize());
    return OPRT_OK;
}

OPERATE_RET ty_photo_trigger_proc(UCHAR_T *data, UINT_T len)
{
    printf("ty photo trigger proc!");
    OPERATE_RET op_ret = OPRT_OK;
    PT_TRIGGER_PROT *pdata = NULL;
    UCHAR_T result = PT_TRIGGER_RET_SUCCESS;
    GW_WIFI_NW_STAT_E cur_nw_stat = 0;

    if ((data == NULL) || (len == 0)) {
        PR_ERR("ty_photo_trigger param data error");
        result = PT_TRIGGER_RET_FIALED;
        op_ret = OPRT_COM_ERROR;
        goto ext;
    }

//	if (0 == tuya_video_camera_power_off_status()) {
//        if(!dev_online("uvc")) {
//            PR_ERR("photo proc not init,Please check whether the function is enabled");
//            result = PT_TRIGGER_RET_FIALED;
//            op_ret = OPRT_COM_ERROR;
//            goto ext;
//        }
//	}
    if (!g_pt_ctrl.photo_init) {
        PR_ERR("photo proc not init,Please check whether the function is enabled");
        result = PT_TRIGGER_RET_FIALED;
        op_ret = OPRT_COM_ERROR;
        goto ext;
    }

    op_ret = get_wf_gw_nw_status(&cur_nw_stat);
    if (OPRT_OK != op_ret) {
        PR_ERR("get_wf_gw_nw_status err =%d", op_ret);
        result = PT_TRIGGER_RET_FIALED;
        op_ret = OPRT_COM_ERROR;
        goto ext;
    }

    GW_CNTL_S *gw_cntl = get_gw_cntl();
    if (gw_cntl->gw_wsm.stat != ACTIVATED) {
        PR_ERR("ty_photo_trigger_proc dev is not actived %d %s %s %s!!!", gw_cntl->gw_wsm.stat, gw_cntl->gw_wsm.token, gw_cntl->gw_wsm.region, gw_cntl->gw_wsm.regist_key);
        result = PT_TRIGGER_RET_FIALED;
        op_ret = OPRT_COM_ERROR;
        goto ext;
    }

    if (g_pt_ctrl.is_busy || g_pt_ctrl.stream_is_busy) {
        PR_ERR("ty_photo_trigger_proc is busy %d %d", g_pt_ctrl.is_busy, g_pt_ctrl.stream_is_busy);
        result = PT_TRIGGER_RET_FIALED;
        op_ret = OPRT_COM_ERROR;
        goto ext;
    }

    pdata = (PT_TRIGGER_PROT *)data;
#if  defined(TRIGGER_64_OPEN_LCD) && (TRIGGER_64_OPEN_LCD == 1)
    if ((WORD_SWAP(pdata->event_type) == PT_EVENT_ALARM_REMOTE)
        || (WORD_SWAP(pdata->event_type) == PT_EVENT_ULOCK_REMOTE) || (WORD_SWAP(pdata->event_type) == PT_EVENT_DOORBELL_REQUEST)
        || (WORD_SWAP(pdata->event_type) == PT_EVENT_DOORBELL_AND_REMOTE)) {
//        tuya_video_ctr(TRUE,0);
    }
#else
//    tuya_video_ctr(TRUE,0);
#endif
    PR_NOTICE("tuya_video_ctr");
    if (pdata->trigger_type == TRIGGER_TYPE_PHOTO ||  pdata->trigger_type == TRIGGER_TYPE_STREAM) {
        g_pt_ctrl.trigger_type = pdata->trigger_type;
        op_ret = ty_photo_send_msg(PT_DATA_INIT, pdata, len);

    } else {
        PR_ERR("trigger type error!!!");
        result = PT_TRIGGER_RET_FIALED;
        op_ret = OPRT_COM_ERROR;
        goto ext;
    }


ext:
    if (g_pt_ctrl.cb) {
        TY_STREAM_SEND_FRAME_S send_data;
        send_data.type = STREAM_SEND_TYPE_DIRECT;
        send_data.cmd = PHOTO_TRIGGER_CMD;
        send_data.data_len = SIZEOF(UCHAR_T);
        send_data.data = &result;
        g_pt_ctrl.cb(&send_data);
    }
    tuya_low_power_time_set_and_start(LOW_POWER_STREAM_TIME);
    return op_ret;
}

STATIC VOID __ipc_http_fill_skills_cb(INOUT CHAR_T *skills)
{
    if (NULL == skills) {
        return;
    }
    INT_T Num = 0;
    strcat(skills, "{\\\"localStorage\\\":1");
    strcat(skills, ",\\\"cloudP2P\\\":1");
    strcat(skills, ",\\\"cloudGW\\\":1}");
}

OPERATE_RET ty_photo_cloudp2p_iot_init(VOID)
{
    memset(ipc_skills, 0, sizeof(ipc_skills));
    strcpy(ipc_skills, "\"skillParam\":\"");
    snprintf(ipc_skills + strlen(ipc_skills), IPC_SKILLS_BUF_LEN - strlen(ipc_skills), "{\\\"type\\\":%d,\\\"skill\\\":", TUYA_P2P_TYPE);
    __ipc_http_fill_skills_cb(ipc_skills);
    strcat(ipc_skills, "}\"");
    PR_DEBUG("cloudp2p_iot_init ! %s", ipc_skills);
    gw_active_set_ext_param(ipc_skills);
    return 0;
}


STATIC OPERATE_RET tuya_rotating_upload(UINT_T rotation_angle)
{
#define MATOP_POST_DATA_LEN               30
#define MATOP_POST_DATA_LEN_RESERVED      35

    OPERATE_RET op_ret = OPRT_OK;

    ty_cJSON *root = NULL, *result = NULL;
    CHAR_T *out = NULL;
    root = ty_cJSON_CreateObject();
    if (NULL == root) {
        PR_ERR("cjson creat error");
        return OPRT_CR_CJSON_ERR;
    }
    CHAR_T *post_data = Malloc(MATOP_POST_DATA_LEN_RESERVED);
    if (post_data == NULL) {
        PR_ERR("Malloc Fail");
        return OPRT_MALLOC_FAILED;
    }
    memset(post_data, 0, MATOP_POST_DATA_LEN_RESERVED);

    snprintf(post_data, MATOP_POST_DATA_LEN, "{\"LOCK_ROTATE_ANGLE\":\"%d\"}", rotation_angle);

    PR_DEBUG("TI_DEV_SKILL_UPDATE post_data:%s", post_data);


    GW_CNTL_S *gw_cntl = get_gw_cntl();
    ty_cJSON_AddStringToObject(root, "devId", gw_cntl->gw_if.id);

    ty_cJSON_AddStringToObject(root, "propKvs", post_data); //buff

    Free(post_data);
    post_data = NULL;


    out = ty_cJSON_PrintUnformatted(root);
    PR_DEBUG("tuya_svc_stream_get out :%s", out);
    ty_cJSON_Delete(root);
    root = NULL;
    if (NULL == out) {
        PR_ERR("cJSON_PrintUnformatted failed");
        return OPRT_COM_ERROR ;
    }

    op_ret = iot_httpc_common_post_simple("tuya.device.props.save", "1.0", out, NULL, &result);

    Free(out);
    out = NULL;


    if (OPRT_OK != op_ret) {
        PR_ERR("httpc_common_post TY_SVC_ROATING_SET_ATOP failed! op_ret:%d", op_ret);
        return op_ret;
    }

    PR_NOTICE("rotation angle upload success");

    ty_cJSON_Delete(result);
    result = NULL;

    return op_ret;
}

VOID ty_stream_init(VOID)
{
    ty_photo_send_msg(PT_UP_SKILL, NULL, 0);
    return ;
}

VOID ty_stream_actice_force_uplord(VOID)
{
    ty_photo_send_msg(PT_FORCE_UP_SKILL, NULL, 0);
    return ;
}

BOOL_T ty_get_stream_status(VOID)
{
    return g_pt_ctrl.stream_is_busy;
}

VOID ty_set_camera_pic_w_h(INT_T w, INT_T h)
{
    camera_param.video_width = w;
    camera_param.video_height = h;
    return ;
}

VOID ty_set_camera_pic_w_h_r_f(INT_T w, INT_T h, INT_T rotation, INT_T f)
{
    camera_param.video_width = w;
    camera_param.video_height = h;
    camera_param.video_rotat_angle = rotation;
    camera_param.video_fps = f;
    return ;
}
VOID ty_get_camera_pic_w_h(INT_T *w, INT_T *h)
{
    *w = camera_param.video_width;
    *h = camera_param.video_height;
    return ;
}
VOID ty_get_camera_pic_w_h_r_f(INT_T *w, INT_T *h, INT_T *rotation, INT_T *f)
{
    *w = camera_param.video_width;
    *h = camera_param.video_height;
    *rotation = camera_param.video_rotat_angle;
    *f = camera_param.video_fps;
    return ;
}

VOID ty_set_audio_cfg(INT_T chan, INT_T bit, INT_T rate)
{
    audio_param.sample_rate = rate;
    audio_param.bit_dept = bit;
    audio_param.channel_num = chan;
    return ;
}
INT_T ty_get_audio_rate(VOID)
{
    return audio_param.sample_rate;
}

void test_stream()
{
    PR_DEBUG("into test stream");

//    ty_photo_proc_init(NULL);

    PT_TRIGGER_PROT msg_data;
    msg_data.sub_cmd = 0x00;
    msg_data.event_type = 0x0000;
    msg_data.trigger_type = TRIGGER_TYPE_STREAM; //TRIGGER_TYPE_PHOTO;//TRIGGER_TYPE_STREAM;
    msg_data.ph_reserve1 = 0x00;
    msg_data.ph_reserve2 = 0x00;
    msg_data.time_flag = 0x01;//0x01;

    TIME_T rtc_time_sec;
    rtc_time_sec = uni_time_get_posix();
    PR_DEBUG("time_sec:%d", rtc_time_sec);
    // 将时间秒数转换为年月日、时分秒
    struct tm *time_info;
    time_info = localtime((time_t *)&rtc_time_sec);
    // 填充时间字段
    msg_data.time[0] = (UCHAR_T)(time_info->tm_year - 100);  // 年份 (tm_year 是从 1900 开始, 减去 2000)
    msg_data.time[1] = (UCHAR_T)(time_info->tm_mon + 1);     // 月份 (tm_mon 是从 0 开始, 所以加 1)
    msg_data.time[2] = (UCHAR_T)time_info->tm_mday;          // 日期
    msg_data.time[3] = (UCHAR_T)time_info->tm_hour;          // 时钟
    msg_data.time[4] = (UCHAR_T)time_info->tm_min;           // 分钟
    msg_data.time[5] = (UCHAR_T)time_info->tm_sec;           // 秒钟

    g_pt_ctrl.trigger_type = TRIGGER_TYPE_STREAM;//TRIGGER_TYPE_PHOTO;//TRIGGER_TYPE_STREAM;
    ty_photo_send_msg(PT_DATA_INIT, &msg_data, sizeof(PT_TRIGGER_PROT));
    tuya_push_stream_start();
}


