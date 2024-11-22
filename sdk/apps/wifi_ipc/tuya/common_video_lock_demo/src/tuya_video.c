#include "app_config.h"

/* #ifdef CONFIG_TUYA_SDK_ENABLE */
#include "stream_core.h"
#include "system/includes.h"
#include "device/device.h"
#include "server/video_server.h"
#include "event/device_event.h"
#include "server/video_dec_server.h"
#include "yuv_soft_scalling.h"
#include "update.h"
#include "server/server_core.h"
#include "event/key_event.h"
#include "tuya_hal_network.h"
#include "uni_log.h"
#include "tuya_hal_system.h"
#include "sys_timer.h"
#include "tuya_audio_source.h"
#include "tuya_hal_mutex.h"
#include "tuya_device.h"
#include "sys_timer.h"
#include "tuya_cloud_types.h"
#include "tuya_cloud_com_defs.h"
#include "cJSON.h"
#include "ty_cJSON.h"
#include "tuya_iot_wifi_api.h"
#include "uni_thread.h"
#include "uni_msg_queue.h"
#include "tuya_hal_semaphore.h"
#include "tuya_video.h"
#include "tuya_ipc_streamer.h"

#include "tkl_queue.h"
#include "lcd_config.h"
#include "app_database.h"
/***************************************************************************************/

#define TY_USE_IMAGE_TIMER  0
#define LCD_USE_YUV_CUT  0

#if  defined(TY_OLD_BORD) && (TY_OLD_BORD == 1)
#define  BUTTON_MENU_WAKE_UP_BIT            U8_BIT(1)
#define  POWER_EN_WAKE_UP_BIT               U8_BIT(0)
#define  DOOR_BELL_WAKE_UP_BIT              U8_BIT(2)
#else
#define  BUTTON_MENU_WAKE_UP_BIT            U8_BIT(1)
#define  POWER_EN_WAKE_UP_BIT               U8_BIT(0)
#define  DOOR_BELL_WAKE_UP_BIT              U8_BIT(2)
#define  UART_WAKE_UP_BIT                   U8_BIT(3)
#endif

#define CAMERA_INIT_DELAY_MS   10
#define CAMERA_MAX_JPEG_SIZE   200*1024 //JPEG_DEFAULT_BUFF_SIZE
#define AUDIO_MAX_SIZE   64*1024 //audio_DEFAULT_BUFF_SIZE
#define CAMERA_H264_MAX_SIZE   (80*1024)
#define USB_AUDIO_BUF_SIZE     (16*1024)
//#define MSG_START_VIDEO   1
//#define MSG_STOP_VIDEO    2
//#define MSG_LCD_BL_ON     3
//#define MSG_LCD_BL_OFF    4
#define MSG_START_VIDEO_SYN   5
#define MSG_STOP_VIDEO_SYN    6
#define MSG_START_VIDEO_SYN_WITHOUT_CAMER_ON_STATUS   7
#define MSG_LCD_BL_ON_SYN     8
#define MSG_LCD_BL_OFF_SYN    9
#define MSG_STOP_VIDEO_NEW_SYN    10

#define TY_DROP_JPEG_COUNT    15
#define TY_VIDEO_TASK_NAME    "ty_video_task"
#define TY_CAMERA_TASK_NAME    "camera_deal_task"

#define TY_WAIT_SEM_TIMEOUT   8000

typedef unsigned short WORD;

typedef struct {
    BOOL_T          lcd_open;
    BOOL_T          lcd_display_camera;
    BOOL_T          camera_open;
    BOOL_T          show_page_open;
    BOOL_T          is_clear_jpeg_lbuf;
    BOOL_T          camera_start[4];
    BOOL_T          rec_start[4];
    UINT_T          lcd_width;
    UINT_T          lcd_height;
    MUTEX_HANDLE    mutex;
    SEM_HANDLE      semphore;
    OS_QUEUE        msg_que;
    THRD_HANDLE     task_handle;
    THRD_HANDLE     task_stream_handle;
    BOOL_T          camera_online;
    BOOL_T          audio_online;
    TIMER_ID        restart_camera_id;
} TY_VIDEO_CTRL;

//#pragma pack(4)
typedef struct {
    UINT_T              cmd;
    UCHAR_T             *data;
    UINT_T              data_len;
} TY_VIDEO_CTRL_MSG;
//#pragma pack()

STATIC TY_VIDEO_CTRL g_video_ctrl = {0};
STATIC UCHAR_T  uvcid = 1;
STATIC CHAR_T  audioid = -1;
STATIC union video_req req = {0};
/* STATIC int video0 = 0; */
/* STATIC int video1 = 0; */
/* STATIC int video2 = 0; */
STATIC struct server *video_server[4] = {NULL,};
STATIC struct server *video_rec[4] = {NULL,};
STATIC struct servet *video_display[4] = {NULL,};
STATIC CHAR_T req_buf[CAMERA_MAX_JPEG_SIZE];
STATIC CHAR_T req_audio_buf[AUDIO_MAX_SIZE];
STATIC CHAR_T h264_buf[CAMERA_H264_MAX_SIZE];
STATIC INT_T yuv_data_size = 480 * 320 * 3 / 2;
STATIC UCHAR_T get_one_photo_jpeg = 0;
STATIC INT_T get_one_photo_jpeg_real_len = 0;
STATIC CHAR_T *get_one_photo_jpeg_buf = 0;
STATIC INT_T get_one_photo_jpeg_result = 0;
STATIC INT_T drop_jpeg_count = 0;
//STATIC INT_T camera_power_off = 0;
STATIC CHAR_T *yuv_temp = NULL;
STATIC UINT_T camera_is_h264 = 0;
STATIC UINT_T camera_h264_w = 0;
STATIC UINT_T camera_h264_h = 0;
STATIC INT_T video_state = 0;

STATIC int rec_state = 0;
STATIC u8 disp_state = 0;

char *audio_buf[CONFIG_VIDEO_REC_NUM] = {NULL,};
char *video_buf[CONFIG_VIDEO_REC_NUM] = {NULL,};


/* typedef struct { */

/* } ty_file; */
u8 gsen_lock;
struct vfscan *f_scan[2][CONFIG_VIDEO_REC_NUM];
u16 file_number[2][CONFIG_VIDEO_REC_NUM];
u16 old_file_number[2][CONFIG_VIDEO_REC_NUM];

u32 total_size;
u32 lock_fsize;

u8 need_restart_rec;

FILE *file[CONFIG_VIDEO_REC_NUM];
FILE *new_file[CONFIG_VIDEO_REC_NUM];
u32 new_file_size[CONFIG_VIDEO_REC_NUM];
char fname[CONFIG_VIDEO_REC_NUM][MAX_FILE_NAME_LEN];

#define TY_AUDIO_BUF_SIZE  64*1024
#define TY_VREC_FBUF_SIZE  512*1024 //200*1024
#define LOCK_FILE_PERCENT	40    //0~100

static const char *rec_dir[][2] = {
#ifdef CONFIG_EMR_DIR_ENABLE
    {CONFIG_REC_DIR_0, CONFIG_EMR_REC_DIR_0},
    {CONFIG_REC_DIR_1, CONFIG_EMR_REC_DIR_1},
    {CONFIG_REC_DIR_2, CONFIG_EMR_REC_DIR_2},
    {CONFIG_REC_DIR_2, CONFIG_EMR_REC_DIR_2},
#else
    {CONFIG_REC_DIR_0, CONFIG_REC_DIR_0},
    {CONFIG_REC_DIR_1, CONFIG_REC_DIR_1},
    {CONFIG_REC_DIR_2, CONFIG_REC_DIR_2},
    {CONFIG_REC_DIR_2, CONFIG_REC_DIR_2},
#endif
};


static const char *rec_path[][2] = {
#ifdef CONFIG_EMR_DIR_ENABLE
    {CONFIG_REC_PATH_0, CONFIG_EMR_REC_PATH_0},
    {CONFIG_REC_PATH_1, CONFIG_EMR_REC_PATH_1},
    {CONFIG_REC_PATH_2, CONFIG_EMR_REC_PATH_2},
    {CONFIG_REC_PATH_2, CONFIG_EMR_REC_PATH_2},
#else
    {CONFIG_REC_PATH_0, CONFIG_REC_PATH_0},
    {CONFIG_REC_PATH_1, CONFIG_REC_PATH_1},
    {CONFIG_REC_PATH_2, CONFIG_REC_PATH_2},
    {CONFIG_REC_PATH_2, CONFIG_REC_PATH_2},
#endif
};



void video_convert(INT_T flag); //双路摄像头切换

STATIC OPERATE_RET tuya_send_video_msg(IN CONST UINT_T msgid, IN CONST VOID_T *data, IN CONST UINT_T len)
{
    PR_NOTICE("into tuya_send_video_msg");
    OPERATE_RET op_ret = OPRT_OK;
//    INT_T msg_num = 0;
    if (&g_video_ctrl.msg_que == NULL) {
        return OPRT_MSG_OUT_OF_LMT;
    }
    TY_VIDEO_CTRL_MSG *msg_data;
    PR_NOTICE("sizeof TY_video_ctrl_msg:%d\n", sizeof(TY_VIDEO_CTRL_MSG));
    msg_data = Malloc(sizeof(TY_VIDEO_CTRL_MSG) + 1);
    if (!msg_data) {
        return OPRT_MALLOC_FAILED;
    }
    memset(msg_data, 0, SIZEOF(TY_VIDEO_CTRL_MSG) + 1);
    msg_data->cmd = msgid;

    if (data && len) {
        msg_data->data = Malloc(len + 1);
        if (!msg_data->data) {
            if (msg_data) {
                Free(msg_data);
            }
            return OPRT_MALLOC_FAILED;
        }
        memset(msg_data->data, 0, len + 1);
        memcpy(msg_data->data, data, len);
        msg_data->data_len = len;
    } else {
        msg_data->data = NULL;
//        cur_len = 0;
    }

    op_ret = os_q_post(&g_video_ctrl.msg_que, msg_data);
    if (OPRT_OK != op_ret) {
        if (msg_data->data) {
            Free(msg_data->data);
        }
        if (msg_data) {
            Free(msg_data);
        }
        return op_ret;
    }

    return OPRT_OK;
}



VOID_T tuya_video_stop_syn(VOID_T)
{
    SEM_HANDLE wait_sem = NULL;
    OPERATE_RET op_ret = OPRT_OK;
    op_ret = tuya_hal_semaphore_create_init(&wait_sem, 0, 1);
    if (OPRT_OK != op_ret) {
        PR_ERR(" Malloc fail");
        return;
    }
    op_ret = tuya_send_video_msg(MSG_STOP_VIDEO_SYN, &wait_sem, SIZEOF(SEM_HANDLE));
    if (OPRT_OK != op_ret) {
        tuya_hal_semaphore_release(wait_sem);
        PR_ERR(" send fail");
        return;
    }
    tuya_hal_semaphore_wait(wait_sem);
    //PR_NOTICE("tuya_video_stop_syn");
    tuya_hal_semaphore_release(wait_sem);
}

VOID_T tuya_video_stop_new_syn(INT_T force)
{
    INT_T send_data[2] ;
    send_data[0] = force;

    SEM_HANDLE wait_sem = NULL;
    OPERATE_RET op_ret = OPRT_OK;
    op_ret = tuya_hal_semaphore_create_init(&wait_sem, 0, 1);
    if (OPRT_OK != op_ret) {
        PR_ERR(" Malloc fail");
        return;
    }
    send_data[1] = wait_sem;
    op_ret =  tuya_send_video_msg(MSG_STOP_VIDEO_NEW_SYN, &send_data, SIZEOF(send_data));
    if (OPRT_OK != op_ret) {
        PR_ERR(" send fail");
        tuya_hal_semaphore_release(wait_sem);
        return;
    }
    tuya_hal_semaphore_wait(wait_sem);
    //PR_NOTICE("tuya_video_stop_new_syn");
    tuya_hal_semaphore_release(wait_sem);
}
VOID_T tuya_video_start_syn(VOID_T)
{
    PR_NOTICE("into tuya video start syn!");
    SEM_HANDLE wait_sem = NULL;
    OPERATE_RET op_ret = OPRT_OK;
    op_ret = tuya_hal_semaphore_create_init(&wait_sem, 0, 1);
    if (OPRT_OK != op_ret) {
        PR_ERR(" Malloc fail");
        return;
    }
    op_ret = tuya_send_video_msg(MSG_START_VIDEO_SYN, &wait_sem, SIZEOF(SEM_HANDLE));
    if (OPRT_OK != op_ret) {
        PR_ERR(" send fail");
        tuya_hal_semaphore_release(wait_sem);
        return;
    }
    tuya_hal_semaphore_wait(wait_sem);
    PR_NOTICE("tuya_video_start_syn");
    tuya_hal_semaphore_release(wait_sem);
}
VOID_T tuya_video_start_syn_without_camer_on(VOID_T)
{
    SEM_HANDLE wait_sem = NULL;
    OPERATE_RET op_ret = OPRT_OK;
    op_ret = tuya_hal_semaphore_create_init(&wait_sem, 0, 1);
    if (OPRT_OK != op_ret) {
        PR_ERR(" Malloc fail");
        return;
    }
    op_ret = tuya_send_video_msg(MSG_START_VIDEO_SYN_WITHOUT_CAMER_ON_STATUS, &wait_sem, SIZEOF(SEM_HANDLE));
    if (OPRT_OK != op_ret) {
        PR_ERR(" send fail");
        tuya_hal_semaphore_release(wait_sem);
        return;
    }
    tuya_hal_semaphore_wait(wait_sem);
    //PR_NOTICE("tuya_video_start_syn_without_camer_on");
    tuya_hal_semaphore_release(wait_sem);
}

VOID_T tuya_lcd_bl_on_syn(INT_T from_set, INT_T pic)
{
    INT_T send_data[3] ;
    send_data[0] = from_set;
    send_data[1] = pic;

    SEM_HANDLE wait_sem = NULL;
    OPERATE_RET op_ret = OPRT_OK;
    op_ret = tuya_hal_semaphore_create_init(&wait_sem, 0, 1);
    if (OPRT_OK != op_ret) {
        PR_ERR(" Malloc fail");
        return;
    }
    send_data[2] = (INT_T) wait_sem;
    op_ret = tuya_send_video_msg(MSG_LCD_BL_ON_SYN, &send_data, SIZEOF(send_data));
    if (OPRT_OK != op_ret) {
        PR_ERR(" send fail");
        tuya_hal_semaphore_release(wait_sem);
        return;
    }
    tuya_hal_semaphore_wait(wait_sem);
    //PR_NOTICE("tuya_lcd_bl_on_syn");
    tuya_hal_semaphore_release(wait_sem);
}

VOID_T tuya_lcd_bl_off_syn(VOID_T)
{
    SEM_HANDLE wait_sem = NULL;
    OPERATE_RET op_ret = OPRT_OK;
    op_ret = tuya_hal_semaphore_create_init(&wait_sem, 0, 1);
    if (OPRT_OK != op_ret) {
        PR_ERR(" Malloc fail");
        return;
    }
    op_ret = tuya_send_video_msg(MSG_LCD_BL_OFF_SYN, &wait_sem, SIZEOF(SEM_HANDLE));
    if (OPRT_OK != op_ret) {
        PR_ERR(" send fail");
        tuya_hal_semaphore_release(wait_sem);
        return;
    }
    tuya_hal_semaphore_wait(wait_sem);
    //PR_NOTICE("tuya_lcd_bl_off_syn");
    tuya_hal_semaphore_release(wait_sem);
}

VOID_T tuya_video_backlight_off(VOID_T)
{
    tuya_lcd_bl_off_syn();
    return ;
}
VOID_T tuya_video_ctr(BOOL_T status, INT_T force)
{
    if (status) {
        tuya_video_start_syn();
    } else  {
        tuya_video_stop_new_syn(force);
    }
    return ;
}

CHAR_T *my_mem_find_str(UCHAR_T *src, UINT_T len, UCHAR_T **p_start, UCHAR_T **p_end, UCHAR_T **p_h264_start, UINT_T *p_h264_len, UINT_T *p_h264_type)
{
#define FAST_MAX_DATA_LEN   520    //必须>512
    CHAR_T *result = NULL;
    UCHAR_T *cur = src;
    UCHAR_T *last_cur = src;
    UCHAR_T seg_have = 0;
    UCHAR_T *start = NULL;
    UCHAR_T *end = NULL;
    UCHAR_T flag = 0;
    UCHAR_T end_flag = 0;
    UINT_T total_len = 0;
    UINT_T fast_find_ff_d9 = 0;
    UCHAR_T fast_find_ff_d9_count = 0;
    UINT_T h264_pos = 0;
    UINT_T ex_h264_len = 0;
    UINT_T ex_h264_type = 0;
    STATIC INT_T h264_p_count = 0;
    while (cur < src + len) {
        switch (cur[0]) {
        case 0xff: {
            seg_have = 1;
            last_cur = cur;
            switch (cur[1]) {
            case 0xd8:
                flag = 1;
                start = cur;
                cur += 2;
                ex_h264_len = 0;
                break;

            case 0xda:
                cur = src + len - FAST_MAX_DATA_LEN;
                fast_find_ff_d9 = 1;

                //  cur += 2;
                //  fast_find_ff_d9 = 0;
                break;

            case 0xd9:
                if (flag) {
                    end_flag = 1;
                    end = cur;
                }
                break;

            case 0xe7:
            case 0xe8:
            case 0xe9:
#if 0
                camera_is_h264 = 1;

                total_len = cur[2];
                total_len = (total_len << 8) + cur[3];
                memcpy(h264_buf + ex_h264_len, cur + 14, total_len - 12);
                ex_h264_len += (total_len - 12);
                if (cur[1] == 0xe7) {
                    ex_h264_type = GetFrameType(h264_buf);
                    camera_h264_w = 640;
                    camera_h264_h = 480;

                    PR_NOTICE("h264_p_count = %d", h264_p_count);
                }
                cur = cur + 2 + total_len;

#endif // 0
                break;

            case 0xe0:
            case 0xe1:
            case 0xe2:
            case 0xe3:
            case 0xe4:
            case 0xe5:
            case 0xe6:
                goto JUMP_POSITION;
                break;

            case 0xea:
            case 0xeb:
            case 0xec:
            case 0xed:
            case 0xee:
            case 0xef:
                goto JUMP_POSITION;
                break;


            case 0xdb:
            case 0xdc:
            case 0xdd:
            case 0xde:
            case 0xdf:
                goto JUMP_POSITION;
                break;


            case 0xc0:
            case 0xc2:
            case 0xc4:
                goto JUMP_POSITION;
                break;

            case 0xc1:
            case 0xc3:
            case 0xc5:
            case 0xc6:
            case 0xc7:
            case 0xcc:
            case 0xcd:
            case 0xce:
            case 0xcf:
JUMP_POSITION:
                total_len = cur[2];
                total_len = (total_len << 8) + cur[3];
                cur = cur + 2 + total_len;
                break;

            default:
                seg_have = 0;
                cur++;
                if (fast_find_ff_d9) {
                    fast_find_ff_d9_count++;
                }
                break;

            }
#if 0
            if (seg_have) {
                if (last_cur[1] == 0xd8 || last_cur[1] == 0xd9) {
                    PR_NOTICE("find 0xff 0x%2x pos=%d count=%d\n", last_cur[1], last_cur - src, fast_find_ff_d9_count);
                } else if (last_cur[1] == 0xe7 || last_cur[1] == 0xe8 || last_cur[1] == 0xe9) {
                    PR_NOTICE("find 0xff 0x%2x pos=%d len=%d ex_h264_type=%d ex_h264_len=%d\n", last_cur[1], last_cur - src, total_len, ex_h264_type, ex_h264_len);
                } else {
                    PR_NOTICE("find 0xff 0x%2x pos=%d len=%d\n", last_cur[1], last_cur - src, total_len);
                }
            }
#endif
        }
        break;

        default:
            if (fast_find_ff_d9) {
                fast_find_ff_d9_count++;
            }

            cur++;
            break;
        }
        if (end_flag) {
            //PR_NOTICE("position 0x%x len %d  data 0x%x 0x%x 0x%x 0x%x\n",cur,len,cur[0],cur[1],cur[2],cur[3]);
            *p_start = start;
            *p_end = end;
            if (ex_h264_len) {
                *p_h264_start = h264_buf;
                *p_h264_len = ex_h264_len;
                *p_h264_type = ex_h264_type;
            }
            return cur;
        }

    }
    return result;
}

#if TY_USE_IMAGE_TIMER
STATIC VOID tuya_restart_camera_time_cb(UINT_T timerID, PVOID_T pTimerArg)
{
    if (g_video_ctrl.camera_open) {
        uvc_set_flash_control_status(0);
    }
}
#endif
#if  0
STATIC INT_T uvc_jpeg_cb(UCHAR_T type, UCHAR_T *buf, UINT_T size)
{
#define jl_ntohl(x) (UINT_T)((((UINT_T)(x))>>24) | ((((UINT_T)(x))>>8)&0xff00) | (((UINT_T)(x))<<24) | ((((UINT_T)(x))&0xff00)<<8))
#define JL_ENDF     	jl_ntohl(0x56185719)
#define JPEG_HEAD 		0xE0FFD8FF
#define JL_000DC		jl_ntohl(0x30306463)
#define JL_001WB		jl_ntohl(0x30317762)
    STATIC INT_T last_time_ms = 0;
    STATIC INT_T jpeg_count = 0;
    INT_T now_time_ms = 0;
    INT_T ret = 0;
    INT_T w = 0;
    INT_T h = 0;
    UINT_T *head = (UINT_T *)buf;
    UCHAR_T *tail = NULL;
    UINT_T data_len = size;
    UINT_T jpeg_size = 0;
    UCHAR_T *head_ffd8 = NULL;
    UCHAR_T *tail_ffd9 = NULL;


#if 0
    if (type == VIDEO_REC_JPEG_TYPE_VIDEO) {
        if (size > CAMERA_MAX_JPEG_SIZE) {
            PR_DEBUG("VDPKBUFF_SIZE no enough !!!\n");
            return size;
        }
        //PR_NOTICE("jpeg %d\n",size);
        if (!g_video_ctrl.camera_open) {
            jpeg_count++;
            now_time_ms = tuya_hal_get_systemtickcount();
            if (now_time_ms - 500 > last_time_ms) {
                PR_NOTICE(" %d %d ", jpeg_count, size);
                last_time_ms = tuya_hal_get_systemtickcount();
                jpeg_count = 0;
            }
            return size;
        }
        if (get_ug_flag()) {
            //PR_NOTICE("retun jpeg %d\n",size);
            return size;
        }
        if ((*head == JL_000DC && *(head + 2) == JPEG_HEAD) || *(head + 2) == JPEG_HEAD) {
            head_ffd8 = buf + 8;
            data_len = size - 8;

            if (tuya_push_stream_status_get()) {
                ty_stream_in_queue(head_ffd8, data_len);
            }

            if (get_one_photo_jpeg) {
                get_one_photo_jpeg_buf = Malloc(jpeg_size);
                if (get_one_photo_jpeg_buf) {
                    memcpy(get_one_photo_jpeg_buf, head_ffd8, jpeg_size);
                    get_one_photo_jpeg_real_len = jpeg_size;
                    get_one_photo_jpeg_result = 0;
                } else {
                    get_one_photo_jpeg_real_len = 0;
                    get_one_photo_jpeg_result = -1;
                }
                //PR_NOTICE("get_one_photo_jpeg=%d",get_one_photo_jpeg_real_len);

                get_one_photo_jpeg = 0;
                tuya_hal_semaphore_post(g_video_ctrl.semphore);
            }
            if (tuya_video_lcd_display_status_get()) {
                ret = jpeg2yuv_jpeg_frame_write(head_ffd8, data_len);
                if (ret) {
                    PR_DEBUG("jpeg2yuv_jpeg_frame_write ignore");
                } else {
                    jpeg_count ++;
                }
#if TY_LCD_VIDEO_DEBUG_TIME
                now_time_ms = tuya_hal_get_systemtickcount();
                if (now_time_ms - 100 > last_time_ms) {
                    ty_get_camera_pic_w_h(&w, &h);
                    PR_NOTICE("jpeg fps %d now tick %d last tick %d w=%d h=%d size=%d \r\n", jpeg_count, now_time_ms, last_time_ms, w, h, size);
                    last_time_ms = tuya_hal_get_systemtickcount();
                    jpeg_count = 0;
                }
#endif
            }
        }
    }
#else
    CHAR_T substr_ffd8[2] = {0xff, 0xd8};
    CHAR_T substr_ffd9[2] = {0xff, 0xd9};
    if (type == VIDEO_REC_JPEG_TYPE_VIDEO) {
        if (drop_jpeg_count < TY_DROP_JPEG_COUNT) {
            drop_jpeg_count++;
            return size;
        }
        if (data_len > CAMERA_MAX_JPEG_SIZE) {
            PR_DEBUG("VDPKBUFF_SIZE no enough !!!\n");
            return size;
        }
        //PR_NOTICE("in jpeg %d\n",size);
        if (!g_video_ctrl.camera_open) {
            jpeg_count++;
            now_time_ms = tuya_hal_get_systemtickcount();
            if (now_time_ms - 500 > last_time_ms) {
                PR_NOTICE(" %d %d ", jpeg_count, size);
                last_time_ms = tuya_hal_get_systemtickcount();
                jpeg_count = 0;
            }
            return size;
        }
        if (get_ug_flag()) {
            //PR_NOTICE("retun jpeg %d\n",size);
            return size;
        }
        if ((*head == JL_000DC && *(head + 2) == JPEG_HEAD) || *(head + 2) == JPEG_HEAD) {
            head_ffd8 = buf + 8;
            data_len = size - 8;
            if (data_len < 1024) {
                return size;
            }
#if TY_USE_IMAGE_TIMER
            sys_start_timer(g_video_ctrl.restart_camera_id, 300, TIMER_ONCE);
#endif
            while (1) {
                if (my_mem_find_str(head_ffd8, data_len, &head_ffd8, &tail_ffd9)) {
                    jpeg_size = tail_ffd9 + 2 - head_ffd8;
                    if (jpeg_size <= 2048) {
                        break;
                    }
                } else {
                    break;
                }

                //PR_NOTICE("jpeg %d\n",jpeg_size);
                if (tuya_push_stream_status_get()) {
                    ty_stream_in_queue(head_ffd8, (UINT_T)jpeg_size);
                }
                if (get_one_photo_jpeg) {
                    get_one_photo_jpeg_buf = Malloc(jpeg_size);
                    if (get_one_photo_jpeg_buf) {
                        memcpy(get_one_photo_jpeg_buf, head_ffd8, jpeg_size);
                        get_one_photo_jpeg_real_len = jpeg_size;
                        get_one_photo_jpeg_result = 0;
                    } else {
                        get_one_photo_jpeg_real_len = 0;
                        get_one_photo_jpeg_result = -1;
                    }
                    //PR_NOTICE("get_one_photo_jpeg=%d",get_one_photo_jpeg_real_len);

                    get_one_photo_jpeg = 0;
                    tuya_hal_semaphore_post(g_video_ctrl.semphore);
                }
                if (tuya_video_lcd_display_status_get()) {
                    ret = jpeg2yuv_jpeg_frame_write((UCHAR_T *)head_ffd8, (UINT_T)jpeg_size);
                    if (ret) {
                        PR_DEBUG("jpeg2yuv_jpeg_frame_write ignore");
                    } else {
                        jpeg_count ++;
                    }

#if TY_LCD_VIDEO_DEBUG_TIME
                    now_time_ms = tuya_hal_get_systemtickcount();
                    if (now_time_ms - 100 > last_time_ms) {
                        ty_get_camera_pic_w_h(&w, &h);
                        //PR_NOTICE("jpeg fps %d w=%d h=%d size=%d ",jpeg_count,w,h,jpeg_size);
                        last_time_ms = tuya_hal_get_systemtickcount();
                        jpeg_count = 0;
                    }
#endif

                }
                if (buf + size - tail_ffd9 < 2048) {
                    break;
                } else {
                    head_ffd8 = tail_ffd9 + 2;
                    data_len -= jpeg_size;
#if TY_LCD_VIDEO_DEBUG_TIME
                    PR_NOTICE("jpeg size %d left size %d total size %d", jpeg_size, data_len, size);
#endif
                }

            }
        }
    } else {
        PR_NOTICE("type=%d %d\n", type, size);
    }
    //PR_NOTICE("end jpeg %d\n",size);
#endif
    //memset(buf,0,size);
    return size;
}
#else

#define VPBUF_SIZE CAMERA_MAX_JPEG_SIZE/2
struct strm_ptl_info {
    u8 kill;
    u8 vd_use;
    u8 ad_use;
    u8 err;
    u8 init;
    u8 copy;
    SEM_HANDLE sem;
    u8 *video_pkbuff;
    u32 vd_len;
};
struct strm_ptl_info strm_ptl_info_ = {0};
#define strm_ptl (&strm_ptl_info_)

/* STATIC INT_T ty_video_frame_cb(UCHAR_T type, UCHAR_T *buf, UINT_T size) */
STATIC INT_T ty_stream_write(void *file,  UCHAR_T *buf, UINT_T size, UCHAR_T type)
{
    /* PR_NOTICE("into ty video frame cb, buf size:%d", size); */
    PR_DEBUG("buf size:%d", size);
    if (size == 512 || size == 8192) {
        return size;
    }
    /* put_buf(buf, 64);	 */
#define jl_ntohl(x) (UINT_T)((((UINT_T)(x))>>24) | ((((UINT_T)(x))>>8)&0xff00) | (((UINT_T)(x))<<24) | ((((UINT_T)(x))&0xff00)<<8))
#define JL_ENDF     	jl_ntohl(0x56185719)
#define JPEG_HEAD 		0xE0FFD8FF
#define JL_000DC		jl_ntohl(0x30306463)
#define JL_001WB		jl_ntohl(0x30317762)
    u32 *head = (u32 *)buf;
    if (!strm_ptl->init || strm_ptl->err || strm_ptl->kill) {
        return size;
    } else if ((size <= 8) && (*head == JL_ENDF)) {
        return size;
    }

    if (type == VIDEO_REC_JPEG_TYPE_VIDEO) {

        if (drop_jpeg_count < TY_DROP_JPEG_COUNT) {
            drop_jpeg_count++;
            return size;
        }
        if (size > VPBUF_SIZE) {
            PR_NOTICE("VDPKBUFF_SIZE no enough !!!\n");
            return size;
        }

        if ((*head == JL_000DC && *(head + 2) == JPEG_HEAD) || *(head + 2) == JPEG_HEAD) {
            buf += 8;
            size -= 8;
        }
        /* if (!strm_ptl->vd_use && !strm_ptl->kill) { */
        strm_ptl->copy = true;
        strm_ptl->vd_use = true;
        strm_ptl->vd_len = size;
        /* PR_NOTICE("video buf size : %d", size); */
        memcpy(strm_ptl->video_pkbuff, buf, size);
        strm_ptl->copy = false;
        tuya_hal_semaphore_post(strm_ptl->sem);
        /* } */
    }
    return size;
}

void *ty_stream_open(const char *path, const char *mode)
{
    return 1;
}

void ty_stream_close(void *file)
{

}


STATIC UINT_T get_camera_is_h264(VOID_T)
{
    //0 jpeg 1 264  2 265
    return 0;
}

void get_h264_width_and_height(UINT_T *width, UINT_T *height)
{
    *width = camera_h264_w;
    *height = camera_h264_h;
}

#if 1

/*
 * 判断SD卡是否挂载成功和簇大小是否大于32K
 */
static int storage_device_available()
{
    struct vfs_partition *part;

    if (storage_device_ready() == 0) {
        return false;
    } else {
        part = fget_partition(CONFIG_ROOT_PATH);
        PR_DEBUG("part_fs_attr: %x\n", part->fs_attr);
#ifdef CONFIG_JLFAT_ENABLE
        if (part->clust_size < 32 * 1024 || (part->fs_attr & F_ATTR_RO)) {
#else
        if (part->clust_size < 32 || (part->fs_attr & F_ATTR_RO)) {
#endif
            return false;
        }
        /* total_size = part->total_size; */
    }

    return true;
}

static const char *rec_file_name(int format)
{
#if NAME_FILE_BY_DATE
    struct sys_time time;
    static char file_name[MAX_FILE_NAME_LEN];

    if (__get_sys_time(&time) == 0) {
        if (format == VIDEO_FMT_AVI) {
            sprintf(file_name, "VID_%d%02d%02d_%02d%02d%02d.AVI",
                    time.year, time.month, time.day, time.hour, time.min, time.sec);
        } else if (format == VIDEO_FMT_MOV) {
            sprintf(file_name, "VID_%d%02d%02d_%02d%02d%02d.MOV",
                    time.year, time.month, time.day, time.hour, time.min, time.sec);
        } else if (format == VIDEO_FMT_MP4) {
            sprintf(file_name, "VID_%d%02d%02d_%02d%02d%02d.MP4",
                    time.year, time.month, time.day, time.hour, time.min, time.sec);
        }
        return file_name;
    }
#endif

    if (format == VIDEO_FMT_AVI) {
        return "VID_****.AVI";
    } else if (format == VIDEO_FMT_MP4) {
        return "VID_****.MP4";
    } else {
        return "VID_****.MOV";
    }
}

char *video_rec_finish_get_name(FILE *fd, int index, u8 is_emf)  //index ：video0前视0，video1则1，video2则2 , is_emf 紧急文件
{
    static char path[64] ALIGNE(32) = {0};
    u8 name[64];
    u8 *dir;
    int err;

#ifdef CONFIG_ENABLE_VLIST
    memset(path, 0, sizeof(path));
    err = fget_name(fd, name, 64);
    printf("finish_get_name: %s \n", name);
    if (err <= 0) {
        return NULL;
    }
    if (index < 0) {
        strcpy(path, name);
        return path;
    }
    switch (index) {
    case 0:
        dir = CONFIG_REC_PATH_0;
        break;
    case 1:
        dir = CONFIG_REC_PATH_1;
        break;
    case 2:
        dir = CONFIG_REC_PATH_2;
        break;
    default:
        return NULL;
    }
#ifdef CONFIG_EMR_DIR_ENABLE
    if (is_emf) {
        sprintf(path, "%s%s%s", dir, CONFIG_EMR_REC_DIR, name);
    } else
#endif
    {
        sprintf(path, "%s%s", dir, name);
    }

    return  path;
#else
    return NULL;
#endif
}


static void video_rec_get_remain_time(void)
{
    static char retime_buf[30];
    int err;
    u32 cur_space = 0;
    u32 one_pic_size;
    int hour = 0, min = 0, sec = 0;
    int second = 0;
    u32 gap_time = 0;//db_select("gap");
    /* #ifdef CONFIG_WIFI_ENABLE */
    /* u8 fps = video_rec_get_fps(); */
    /* #else */
    u8 fps = 10;
    /* #endif */
#if 0 //TODO
    if (gap_time) {
        fps = 1000 / gap_time;
    }
#endif

    /*
     * 这里填入SD卡剩余录像时间
     */
    if (storage_device_available()) {
        PR_DEBUG("calc_free_space...\n");
        err = fget_free_space(CONFIG_ROOT_PATH, &cur_space);
        if (err) {
            if (fget_err_code(CONFIG_ROOT_PATH) == -EIO) {
                /* video_rec_post_msg("fsErr"); */
            }
        } else {
            u32 res = 2;//db_select("res");
            if (res == VIDEO_RES_1080P) {
                one_pic_size = (0x21000 + 0xa000) / 1024;
            } else if (res == VIDEO_RES_720P) {
                one_pic_size = (0x13000 + 0xa000) / 1024;
            } else {
                one_pic_size = (0xa000 + 0xa000) / 1024;
            }
            printf("cur_space:%d one_pic_size:%d fps:%d", cur_space, one_pic_size, fps);
            hour = (cur_space / one_pic_size) / fps / 60 / 60;
            min = (cur_space / one_pic_size) / fps / 60 % 60;
            sec = (cur_space / one_pic_size) / fps % 60;
            second = hour * 3600 + min * 60 + sec;

            printf("retime_buf %02d:%02d:%02d", hour, min, sec);

            /* video_rec_post_msg("Remain:s=%4", ((u32)(second))); */
        }
        PR_DEBUG("calc_free_space_exit\n");
    }
}

/*码率控制，根据具体分辨率设置*/
int video_rec_get_abr(u32 width)
{
    if (width <= 720) {
        /* return 8000; */
        return 4000;
    } else if (width <= 1280) {
        return 8000;
        /* return 10000; */
    } else if (width <= 1920) {
        return 10000;
    } else {
        return 8000;
    }
}

/*动态设置码流*/
static void video_rec_set_bitrate(struct server *video_server, unsigned int bits_rate)
{
    union video_req req = {0};

    /*录像默认使用1通道*/
    req.rec.channel = 0;

    req.rec.state = VIDEO_STATE_RESET_BITS_RATE;
    req.rec.abr_kbps = bits_rate;

    server_request(video_server, VIDEO_REQ_REC, &req);
}


/*
 *根据录像不同的时间和分辨率，设置不同的录像文件大小
 */
static u32 video_rec_get_fsize(u8 cycle_time, u16 vid_width, int format)
{
    u32 fsize;

    if (cycle_time == 0) {
        cycle_time = 5;
    }

    fsize = /*video_rec_get_abr(vid_width)*/1300 * cycle_time * 10000;
    if (format == VIDEO_FMT_AVI) {
        fsize = fsize + fsize / 4;
    }

    return fsize;
}


static int video_rec_cmp_fname(void *afile, void *bfile)
{
    int alen, blen;
    char afname[MAX_FILE_NAME_LEN];
    char bfname[MAX_FILE_NAME_LEN];

    if ((afile == NULL) || (bfile == NULL)) {
        return 0;
    }
    printf("video_rec_cmp_fname: %p, %p\n", afile, bfile);

    alen = fget_name(afile, (u8 *)afname, MAX_FILE_NAME_LEN);
    if (alen <= 0) {
        PR_DEBUG("fget_name: afile=%x\n", afile);
        return 0;
    }
    ASCII_ToUpper(afname, alen);

    blen = fget_name(bfile, (u8 *)bfname, MAX_FILE_NAME_LEN);
    if (blen <= 0) {
        PR_DEBUG("fget_name: bfile=%x\n", bfile);
        return 0;
    }
    ASCII_ToUpper(bfname, blen);

    printf("afname: %s, bfname: %s\n", afname, bfname);

    if (alen == blen && !strcmp(afname, bfname)) {
        return 1;
    }

    return 0;
}


static void video_rec_fscan_release(int lock_dir)
{
    printf("video_rec_fscan_release: %d\n", lock_dir);
    for (int i = 0; i < CONFIG_VIDEO_REC_NUM; i++) {
        if (f_scan[lock_dir][i]) {
            fscan_release(f_scan[lock_dir][i]);
            f_scan[lock_dir][i] = NULL;
        }
    }
}

static void video_rec_fscan_dir(int id, int lock_dir, const char *path)
{
    const char *str;
#ifdef CONFIG_EMR_DIR_ENABLE
    str = "-tMOVAVIMP4 -sn";
#else
    str = lock_dir ? "-tMOVAVIMP4 -sn -ar" : "-tMOVAVIMP4 -sn -a/r";
#endif
    if (f_scan[lock_dir][id]) {
        if (old_file_number[lock_dir][id] == 0) {
            puts("--------delete_all_scan_file\n");
            fscan_release(f_scan[lock_dir][id]);
            f_scan[lock_dir][id] = NULL;
        }
    }

    if (!f_scan[lock_dir][id]) {
        f_scan[lock_dir][id] = fscan(path, str, 9);
        if (!f_scan[lock_dir][id]) {
            old_file_number[lock_dir][id] = 0;
        } else {
            old_file_number[lock_dir][id] = f_scan[lock_dir][id]->file_number;
        }
        file_number[lock_dir][id] = old_file_number[lock_dir][id];
        printf("fscan_dir: %d, file_number = %d\n", id, file_number[lock_dir][id]);
    }
}


static void video_rec_rename_file(int id, FILE *file, int fsize, int format)
{
    char file_name[32];

    new_file[id] = NULL;

#if 0
    int err = fcheck(file);
    if (err) {
        puts("fcheck fail\n");
#ifdef CONFIG_WIFI_ENABLE
        video_rec_delect_notify(file, -1);
#endif
        fdelete(file);
        return;
    }
#endif

    int size = flen(file);
    int persent = (size / 1024) * 100 / (fsize / 1024);

    printf("rename file: persent=%d, %d,%d\n", persent, size >> 20, fsize >> 20);

    if (persent >= 90 && persent <= 110) {
        sprintf(file_name, "%s%s", rec_dir[id][0], rec_file_name(format));

        printf("fmove: %d, %d, %s\n", id, format, file_name);

#ifdef CONFIG_WIFI_ENABLE
        video_rec_delect_notify(file, -1);
#endif

        int err = fmove(file, file_name, &new_file[id], 1, strlen(file_name));
        if (err == 0) {
            fseek(new_file[id], fsize, SEEK_SET);
            fseek(new_file[id], 0, SEEK_SET);
            return;
        }
        puts("fmove_file_faild\n");
    }
#ifdef CONFIG_WIFI_ENABLE
    /* video_rec_delect_notify(file, -1); */
#endif

    fdelete(file);
}


static FILE *video_rec_get_first_file(int id)
{
    int max_index = -1;
    int max_file_number = 0;
    int persent = lock_fsize * 100 / total_size;
    int lock_dir = !!(persent > LOCK_FILE_PERCENT);

    PR_DEBUG("lock_file_persent: %d, %d, size: %dMB\n", id, persent, lock_fsize / 1024);

#ifdef CONFIG_VIDEO0_ENABLE
    video_rec_fscan_dir(0, lock_dir, rec_path[0][lock_dir]);
#endif
#ifdef CONFIG_VIDEO1_ENABLE
    video_rec_fscan_dir(1, lock_dir, rec_path[1][lock_dir]);
#endif
#ifdef CONFIG_VIDEO2_ENABLE
    video_rec_fscan_dir(2, lock_dir, rec_path[2][lock_dir]);
#endif
#ifdef CONFIG_VIDEO3_ENABLE
    video_rec_fscan_dir(3, lock_dir, rec_path[2][lock_dir]);
#endif


    for (int i = 0; i < CONFIG_VIDEO_REC_NUM; i++) {
        if (f_scan[lock_dir][i]) {
            if (max_file_number < file_number[lock_dir][i]) {
                max_file_number = file_number[lock_dir][i];
                max_index = i;
            }
        }
    }

    if (max_index < 0) {
        return NULL;
    }
    if (max_index != id && id >= 0) {
        /* 查看优先删除的文件夹是否满足删除条件 */
        if (file_number[lock_dir][id] + 3 > file_number[lock_dir][max_index]) {
            max_index = id;
        }
    }


    PR_DEBUG("fselect file from dir %d, %d\n", lock_dir, max_index);


    if (f_scan[lock_dir][max_index]) {
        FILE *f = fselect(f_scan[lock_dir][max_index], FSEL_FIRST_FILE, 0);
        if (f) {

            if (lock_dir == 0) {
                if (video_rec_cmp_fname(file[max_index], f)) {
                    fclose(f);
                    return NULL;
                }
            } else {
                lock_fsize -= flen(f) / 1024;
                PR_DEBUG("lock fsize - = %d\n", lock_fsize);
            }

            file_number[lock_dir][max_index]--;
            old_file_number[lock_dir][max_index]--;
            if (old_file_number[lock_dir][max_index] == 0) {
                video_rec_fscan_release(lock_dir);
            }
        }
#ifdef CONFIG_WIFI_ENABLE
        video_rec_delect_notify(f, -1);
#endif
        return f;
    } else {
        PR_DEBUG("f_scan[%d][%d] err", lock_dir, max_index);
        return NULL;
    }
    return NULL;
}






static int video_rec_create_file(int id, u32 fsize, int format, const char *path)
{
    FILE *file;
    int try_cnt = 0;
    char file_path[64];
    sprintf(file_path, "%s%s", path, rec_file_name(format));

    printf("fopen: %s, %dMB\n", file_path, fsize >> 20);

    do {
        file = fopen(file_path, "w+");
        if (!file) {
            PR_DEBUG("fopen faild\n");
            break;
        }
        if (!fseek(file, fsize, SEEK_SET)) {
            goto __exit;
        }
        PR_DEBUG("fseek faild\n");
        fdelete(file);

    } while (++try_cnt < 2);

    return -EIO;

__exit:
    fseek(file, 0, SEEK_SET);
    new_file_size[id] = fsize;
    new_file[id] = file;
    printf("id:%d size:%d file:%x", id, new_file_size[id], new_file[id]);

    return 0;
}
#define VIDEO_REC_FORMAT   VIDEO_FMT_AVI
#define VIDEO_REC_WIDTH    640
static int video_rec_del_old_file()
{
    int i;
    int err;
    FILE *file;
    int fsize[4] = {0, 0, 0, 0};
    u32 cur_space;
    u32 need_space = 0;
    u32 gap_time = 0;//db_select("gap");
    int cyc_time = 5;//60;//5;//db_select("cyc");
    int format[4] = { VIDEO_REC_FORMAT, VIDEO_REC_FORMAT, VIDEO_REC_FORMAT, VIDEO_REC_FORMAT};
    /* u32 gap_time; */
    /* int cys_time; */
#ifdef CONFIG_VIDEO0_ENABLE
    if (!new_file[0]) {
        fsize[0] =  video_rec_get_fsize(cyc_time, VIDEO_REC_WIDTH/*rec_pix_w[db_select("res")]*/, VIDEO_REC_FORMAT);
        if (gap_time) {
            fsize[0] = fsize[0] / (30 * gap_time / 1000);
        }
        need_space += fsize[0];
    }
#endif

    /* if (db_select("two")) { */
#ifdef CONFIG_VIDEO1_ENABLE
    if (!new_file[1]) {
        fsize[1] =  video_rec_get_fsize(cyc_time, VIDEO_REC_WIDTH, VIDEO_REC_FORMAT);
        if (gap_time) {
            fsize[1] = fsize[1] / (30 * gap_time / 1000);
        }
        need_space += fsize[1];
    }
#endif

#ifdef CONFIG_VIDEO2_ENABLE
    if (!new_file[2]) {
        fsize[2] =  video_rec_get_fsize(cyc_time, VIDEO_REC_WIDTH, VIDEO_REC_FORMAT);
        //数字后拉不支持间隔录像
        /* if(gap_time){ */
        /* } */
        need_space += fsize[2];
    }
#endif

#ifdef CONFIG_VIDEO3_ENABLE
    if (!new_file[3]) {
        fsize[3] =  video_rec_get_fsize(cyc_time, VIDEO_REC_WIDTH, VIDEO_REC_FORMAT);
        if (gap_time) {
            fsize[3] = fsize[3] / (30 * gap_time / 1000);
        }
        need_space += fsize[3];
    }
#endif

    /* } */

    err = fget_free_space(CONFIG_ROOT_PATH, &cur_space);
    if (err) {
        return err;
    }

    printf("space: %dMB, %dMB\n", cur_space / 1024, need_space / 1024 / 1024);

    if (cur_space >= 3 * (need_space / 1024)) {
        for (i = 0; i < CONFIG_VIDEO_REC_NUM; i++) {
            if (fsize[i] != 0) {
                printf("fsize:%d  format:%d  rec_path:%s", fsize[i], format[i], rec_path[i][0]);
                err = video_rec_create_file(i, fsize[i], format[i], rec_path[i][0]);
                if (err) {
                    return err;
                }
            }
        }
        return 0;
    }


    while (1) {
        if (cur_space >= (need_space / 1024) * 2) {
            break;
        }
        for (i = 0; i < CONFIG_VIDEO_REC_NUM; i++) {
            if (fsize[i] != 0) {
                file = video_rec_get_first_file(i);
                if (!file) {
                    return -ENOMEM;
                }
                fdelete(file);
            }
        }
        fget_free_space(CONFIG_ROOT_PATH, &cur_space);
        printf("Delete file ,remain space:%d", cur_space);
    }

    for (i = 0; i < CONFIG_VIDEO_REC_NUM; i++) {
        if (fsize[i] != 0) {
            file = video_rec_get_first_file(i);
            if (file) {
                video_rec_rename_file(i, file, fsize[i], format[i]);
            }
            if (!new_file[i]) {
                err = video_rec_create_file(i, fsize[i], format[i], rec_path[i][0]);
                if (err) {
                    return err;
                }
            }
        }
    }

    return 0;
}

static int video_rec_scan_lock_file()
{
#ifdef CONFIG_EMR_DIR_ENABLE
    const char *str = "-tMOVAVIMP4 -sn";
#else
    const char *str = "-tMOVAVIMP4 -sn -ar";
#endif

    lock_fsize = 0;
    for (int i = 0; i < ARRAY_SIZE(rec_path); i++) {
        f_scan[1][i] = fscan(rec_path[i][1], str, 9);
        if (f_scan[1][i] == NULL) {
            continue;
        }
        int sel_mode = FSEL_FIRST_FILE;
        while (1) {
            FILE *file = fselect(f_scan[1][i], sel_mode, 0);
            if (!file) {
                break;
            }
            lock_fsize += (flen(file) / 1024);
            sel_mode = FSEL_NEXT_FILE;
            fclose(file);
        }
    }
    PR_DEBUG("lock_file_size: %dMB\n", lock_fsize / 1024);

    return 0;
}

/*
 *设置保护文件，必须要在关闭文件之前调用
 */
static int video_rec_lock_file(void *file, u8 lock)
{
    int attr;

    if (!file) {
        puts("lock file null\n");
        return -1;
    }

    fget_attr(file, &attr);

    if (lock) {
        if (attr & F_ATTR_RO) {
            return 0;
        }
        attr |= F_ATTR_RO;
    } else {
        if (!(attr & F_ATTR_RO)) {
            return 0;
        }
        attr &= ~F_ATTR_RO;
    }
    fset_attr(file, attr);

    return 0;
}

static void find_lock_file_to_move(int dev_id)
{
    char fpath[128];
    sprintf(fpath, CONFIG_ROOT_PATH"%s", rec_dir[dev_id][0]);
    struct vfscan *fs = fscan(fpath, "-tAVI -sn -ar", 9);
    FILE *file = NULL;
    if (fs) {
        file = fselect(fs, FSEL_LAST_FILE, 0);
        if (file) {
            int err = fmove(file, rec_dir[dev_id][1], NULL, 0, strlen(rec_dir[dev_id][1]));
            if (!err) {
                PR_DEBUG("fmove sucess\n");
            }
        }
    }

    fscan_release(fs);
}

static void video_rec_close_file(int dev_id)
{
    if (!file[dev_id]) {
        return;
    }
#ifdef CONFIG_WIFI_ENABLE
    char is_emf = 0;

    char *path = video_rec_finish_get_name(file[dev_id], dev_id, is_emf);
#endif

#if 0
    if (gsen_lock & BIT(dev_id)) {
        gsen_lock &= ~BIT(dev_id);
        lock_fsize += flen(file[dev_id]) / 1024;
        video_rec_lock_file(file[dev_id], 1);
        /* video_rec_post_msg("unlockREC"); */

#ifdef CONFIG_WIFI_ENABLE
#ifdef CONFIG_EMR_DIR_ENABLE
        is_emf = TRUE;
#endif
        path = video_rec_finish_get_name(file[dev_id], dev_id, is_emf);
#endif
        fclose(file[dev_id]);
        file[dev_id] = NULL;
#ifdef CONFIG_EMR_DIR_ENABLE
        find_lock_file_to_move(dev_id);
#endif
    }
#endif  //0
    if (file[dev_id]) {
        fclose(file[dev_id]);
    }
    file[dev_id] = NULL;

#ifdef CONFIG_WIFI_ENABLE
    if (path) { //必须关闭文件之后才能调用，否则在读取文件信息不全！！！
        /* video_rec_finish_notify(path); */
    }
#endif
}

#endif


STATIC VOID_T stream_protocol_task(PVOID_T pArg)
{
    /* PR_NOTICE("into stream protocol task!"); */
    STATIC INT_T last_time_ms = 0;
    STATIC INT_T jpeg_count = 0;
    INT_T now_time_ms = 0;
    INT_T ret = 0;
    INT_T w = 0;
    INT_T h = 0;

    UINT_T data_len = 0;
    UINT_T jpeg_size = 0;
    UCHAR_T *head_ffd8 = NULL;
    UCHAR_T *tail_ffd9 = NULL;
    UCHAR_T *h264_head = NULL;
    UINT_T h264_len = 0;
    UINT_T h264_type = 0;
    UCHAR_T *buf = NULL;
    UINT_T  size = 0;
    STATIC BOOL_T  inqueue_err = 0;
    STATIC BOOL_T  last_inqueue_err = 0;
    strm_ptl->init = true;
    PR_NOTICE("stream_protocol run");
    while (1) {
        ret = tuya_hal_semaphore_wait(strm_ptl->sem);

        /* if (strm_ptl->vd_use) { */
        head_ffd8 = strm_ptl->video_pkbuff;
        data_len = strm_ptl->vd_len;
        buf = strm_ptl->video_pkbuff;
        size = strm_ptl->vd_len;
        while (1) {
//            PR_NOTICE("put data to queue!");
            /*  -----------------------将摄像头数据通过 ty_stream_in_queue 函数放入队列中------------------*/
            /* PR_DEBUG("head_ffd8 data len:%d", data_len); */
            /* if(data_len == 512) { */
            /* PR_DEBUG("put video data:"); */
            /* put_buf(head_ffd8, 32);	 */
            /* } */
            if (my_mem_find_str(head_ffd8, data_len, &head_ffd8, &tail_ffd9, &h264_head, &h264_len, &h264_type)) {
                jpeg_size = tail_ffd9 + 2 - head_ffd8;
                /* PR_DEBUG("jpeg_size:%d", jpeg_size); */
                if (jpeg_size <= 2048) {
                    PR_NOTICE("jpeg size < 2048");
                    break;
                }
            } else {
                break;
            }
            /* if(tuya_push_stream_status_get()) { */
//                    if(h264_head && h264_len && h264_type) {
//                    } else  {
//                        PR_NOTICE("将视频数据放入队列中");
            /* PR_NOTICE("put video data to queue, jpeg_size:%d", jpeg_size);//data_len);//jpeg_size); */
            /* malloc_stats(); */
            ty_stream_in_queue(head_ffd8, (UINT_T)jpeg_size, E_VIDEO_I_FRAME);
//                    }
//                }
//                if(get_one_photo_jpeg) {
//                    get_one_photo_jpeg_buf = Malloc(jpeg_size);
//                    if(get_one_photo_jpeg_buf) {
//                        memcpy(get_one_photo_jpeg_buf,head_ffd8,jpeg_size);
//                        get_one_photo_jpeg_real_len = jpeg_size;
//                        get_one_photo_jpeg_result = 0;
//                    } else {
//                        get_one_photo_jpeg_real_len = 0;
//                        get_one_photo_jpeg_result = -1;
//                    }
//                    PR_NOTICE("get_one_photo_jpeg=%d",get_one_photo_jpeg_real_len);
//
//                    get_one_photo_jpeg = 0;
//                    tuya_hal_semaphore_post(g_video_ctrl.semphore);
//                }
            if (buf + size - tail_ffd9 < 2048) {
                break;
            } else {
                head_ffd8 = tail_ffd9 + 2;
                data_len -= jpeg_size;
#if TY_LCD_VIDEO_DEBUG_TIME
                PR_NOTICE("jpeg size %d left size %d total size %d", jpeg_size, data_len, size);
#endif
            }
        }
        strm_ptl->vd_use = false;
        /* } */

    }

}
OPERATE_RET stream_protocol_task_create(void)
{
    OPERATE_RET op_ret = OPRT_OK;
    if (strm_ptl->init) {
        return OPRT_OK;
    }
    strm_ptl->kill = 0;
    strm_ptl->err = 0;
    strm_ptl->vd_use = 0;
    strm_ptl->ad_use = 0;

    tuya_hal_semaphore_create_init(&strm_ptl->sem, 0, 1);
    strm_ptl->video_pkbuff = Malloc(VPBUF_SIZE);
    if (!strm_ptl->video_pkbuff) {
        strm_ptl->err = true;
        PR_ERR("stream_protocol_task malloc err");
        return OPRT_MALLOC_FAILED;
    }

    THRD_PARAM_S thrd_param;
    thrd_param.priority = TRD_PRIO_0;//+10;//+5;
    thrd_param.stackDepth = 1024 * 4;
    thrd_param.thrdname = "ty_stream_protocol_task";
    op_ret = CreateAndStart(&g_video_ctrl.task_stream_handle, NULL, NULL, stream_protocol_task, NULL, &thrd_param);
    if (OPRT_OK != op_ret) {
        PR_ERR("stream_protocol_task err");
        strm_ptl->kill = true;
        strm_ptl->init = false;
    }
    return op_ret;
}

#endif

INT_T get_image_jpeg(CHAR_T **jpeg_buf, INT_T *real_len, INT_T time_out)
{
    STATIC UCHAR_T count = 0;
    if (0 == jpeg_buf || 0 == real_len) {
        return -1;
    }
    g_video_ctrl.camera_open = true;
    get_one_photo_jpeg = 1;
    get_one_photo_jpeg_result = -1;
    get_one_photo_jpeg_buf = NULL;
    tuya_hal_semaphore_waittimeout(g_video_ctrl.semphore, time_out);
    count = 0;
    *real_len = get_one_photo_jpeg_real_len;
    *jpeg_buf = get_one_photo_jpeg_buf;
    return get_one_photo_jpeg_result;
}

/**
 * @berief: uvc server close and stop uvc recode
 * @param   none
 * @return: none
 * @retval: none
 */
INT_T  uvc_video_stop(VOID_T)
{
    /* if (0 == g_video_ctrl.mutex) { */
    /* tuya_hal_mutex_create_init(&g_video_ctrl.mutex); */
    /* } */
    /* #if TY_USE_IMAGE_TIMER */
    /* sys_stop_timer(g_video_ctrl.restart_camera_id); */
    /* #endif */
    /* tuya_hal_mutex_lock(g_video_ctrl.mutex); */
    if (!g_video_ctrl.camera_start[2]) {
        PR_DEBUG("video%d is not start!");
        /* tuya_hal_mutex_unlock(g_video_ctrl.mutex); */
        return -1;
    }
    if (video_server[2]) {
        req.rec.channel = 0;
        req.rec.state = VIDEO_STATE_STOP;
        server_request(video_server[2], VIDEO_REQ_REC, &req);
        PR_NOTICE("video server stop");
        g_video_ctrl.camera_start[2] = FALSE;
        /* tuya_hal_mutex_unlock(g_video_ctrl.mutex); */
        return 0;
    } else {
        /* tuya_hal_mutex_unlock(g_video_ctrl.mutex); */
        return -1;
    }

}
INT_T  uvc_video_resume(VOID_T)
{
#if 0
    if (0 == g_video_ctrl.mutex) {
        tuya_hal_mutex_create_init(&g_video_ctrl.mutex);
    }
    tuya_hal_mutex_lock(g_video_ctrl.mutex);
    if (video_server[2]) {
        req.rec.state = VIDEO_STATE_RESUME;
        server_request(video_server[2], VIDEO_REQ_REC, &req);
        PR_NOTICE("video server resum");
        tuya_hal_mutex_unlock(g_video_ctrl.mutex);
        return 0;
    } else {
        tuya_hal_mutex_unlock(g_video_ctrl.mutex);
        return -1;
    }
#endif
}

INT_T  uvc_video_pause(VOID_T)
{
#if 0
    if (0 == g_video_ctrl.mutex) {
        tuya_hal_mutex_create_init(&g_video_ctrl.mutex);
    }
    tuya_hal_mutex_lock(g_video_ctrl.mutex);
    if (video_server[2]) {
        req.rec.state = VIDEO_STATE_PAUSE;
        server_request(video_server[2], VIDEO_REQ_REC, &req);
        PR_NOTICE("video server pause");
        tuya_hal_mutex_unlock(g_video_ctrl.mutex);
        return 0;
    } else {
        tuya_hal_mutex_unlock(g_video_ctrl.mutex);
        return -1;
    }
#endif
}

#define SCREEN_W   LCD_W
#define SCREEN_H   LCD_H
static struct video_window disp_window[DISP_MAX_WIN][4] = {0};

static void ty_video_set_disp_window()
{
    u16 small_screen_w;
    u16 small_screen_h;

    if (LCD_W > 1280) {
        small_screen_w = 480; //16 aline
        small_screen_h = 400; //16 aline
    } else if (LCD_W > 480) {
        small_screen_w = 320; //16 aline
        small_screen_h = 240; //16 aline
    } else {
        small_screen_w = 192; //16 aline
        small_screen_h = 160; //16 aline
    }

    //DISP_MAIN_WIN
    disp_window[DISP_MAIN_WIN][0].width  = SCREEN_W;
    disp_window[DISP_MAIN_WIN][0].height = SCREEN_H;
    disp_window[DISP_MAIN_WIN][1].width  = small_screen_w;
    disp_window[DISP_MAIN_WIN][1].height = small_screen_h;
    disp_window[DISP_MAIN_WIN][2].left   = SCREEN_W - small_screen_w;
    disp_window[DISP_MAIN_WIN][2].width  = small_screen_w;
    disp_window[DISP_MAIN_WIN][2].height = small_screen_h;

    //DISP_HALF_WIN
    disp_window[DISP_HALF_WIN][0].width  = SCREEN_W;// / 2;
    disp_window[DISP_HALF_WIN][0].height = SCREEN_H / 2;
    disp_window[DISP_HALF_WIN][1].left   = SCREEN_W / 2;
    disp_window[DISP_HALF_WIN][1].width  = SCREEN_W / 2;
    disp_window[DISP_HALF_WIN][1].height = SCREEN_H;
    /* disp_window[DISP_HALF_WIN][2].left   = SCREEN_W / 2; */
    disp_window[DISP_HALF_WIN][2].top   = SCREEN_H / 2;
    disp_window[DISP_HALF_WIN][2].width  = SCREEN_W;
    disp_window[DISP_HALF_WIN][2].height = SCREEN_H / 2;

    //DISP_FRONT_WIN
    disp_window[DISP_FRONT_WIN][0].width  = SCREEN_W;
    disp_window[DISP_FRONT_WIN][0].height = SCREEN_H;
    disp_window[DISP_FRONT_WIN][1].width  = (u16) - 1;
    disp_window[DISP_FRONT_WIN][1].height = SCREEN_H;

    //DISP_BACK_WIN
    disp_window[DISP_BACK_WIN][0].width  = (u16) - 1;
    disp_window[DISP_BACK_WIN][0].height = SCREEN_H;
    disp_window[DISP_BACK_WIN][1].width  = SCREEN_W;
    disp_window[DISP_BACK_WIN][1].height = SCREEN_H;
    disp_window[DISP_BACK_WIN][2].width  = SCREEN_W;
    disp_window[DISP_BACK_WIN][2].height = SCREEN_H;

    //DISP_PARK_WIN
    disp_window[DISP_PARK_WIN][0].width  = (u16) - 1;
    disp_window[DISP_PARK_WIN][0].height = SCREEN_H;
    disp_window[DISP_PARK_WIN][1].width  = SCREEN_W;
    disp_window[DISP_PARK_WIN][1].height = SCREEN_H;
    disp_window[DISP_PARK_WIN][2].width  = SCREEN_W;
    disp_window[DISP_PARK_WIN][2].height = SCREEN_H;
}


static void video_set_disp_mirror(int id, u16 mirror)
{
    for (int i = 0; i < DISP_MAX_WIN; i++) {
        disp_window[i][id].mirror = mirror;
    }
}



int  tuya_video_display(INT_T id, const struct video_window *win)
{
    union video_req req = {0};
    char fb_name[4];
    static char dev_name[20];

    /* if (0 == g_video_ctrl.mutex) { */
    /* tuya_hal_mutex_create_init(&g_video_ctrl.mutex); */
    /* } */
    /* tuya_hal_mutex_lock(g_video_ctrl.mutex); */

    if (id == 2) {
        if (uvc_host_online() < 0) {
            PR_DEBUG("uvc is not online");
            /* tuya_hal_mutex_unlock(g_video_ctrl.mutex); */
            return -1;
        }
    }

#ifdef CONFIG_DISPLAY_ENABLE
    printf("video_disp_start: %d, %d x %d\n", id, win->width, win->height);

    if (win->width == (u16) - 1) {
        puts("video_disp_hide\n");
        /* tuya_hal_mutex_unlock(g_video_ctrl.mutex); */
        return -1;
    }
#ifdef CONFIG_VIDEO2_ENABLE
    if (id == 2) {
        if (uvc_host_online() < 0) {
            /* tuya_hal_mutex_unlock(g_video_ctrl.mutex); */
            return -1;
        }
    }
#endif
    sprintf(dev_name, "video%d.%d", id, 1);
    if (!video_display[id]) {
        video_display[id] = server_open("video_server", (void *)dev_name);
        if (!video_display[id]) {
            PR_DEBUG("open video_server: faild, id = %d\n", id);
            /* tuya_hal_mutex_unlock(g_video_ctrl.mutex); */
            return -1;
        }
    } else {
        PR_DEBUG("video server has open");
        /* tuya_hal_mutex_unlock(g_video_ctrl.mutex); */
        return 0;
    }
    memset(fb_name, 0, sizeof(fb_name));
    sprintf(fb_name, "fb%d", id + 1);
    req.display.fb 		        = fb_name;
    req.display.left  	        = win->left;
    req.display.top 	        = win->top;
    req.display.width 	        = win->height;//win->width;//win->height;
    req.display.height 	        = win->width;
    req.display.border_left     = win->border_left;
    req.display.border_top      = win->border_top;
    req.display.border_right    = win->border_right;
    req.display.border_bottom   = win->border_bottom;
    req.display.mirror   		= 0;//win->mirror;
    req.display.jaggy			= 0;	// IMC 抗锯齿
    req.display.state 	        = VIDEO_STATE_START;
    req.display.pctl            = NULL;

    /* #ifndef CONFIG_VIDEO2_ENABLE */
    if (id != 2) {
        req.display.camera_config   = NULL;
        req.display.camera_type     = VIDEO_CAMERA_NORMAL;
        req.display.src_w           = CONFIG_VIDEO_IMAGE_W;//640;
        req.display.src_h           = CONFIG_VIDEO_IMAGE_H;//480;
        req.display.rotate          = 90;
    } else {
        /* #else */
        req.display.uvc_id          = uvc_host_online();
        req.display.camera_config   = NULL;
        req.display.camera_type     = VIDEO_CAMERA_UVC;
        req.display.src_w           = CONFIG_VIDEO_IMAGE_W;//640;
        req.display.src_h           = CONFIG_VIDEO_IMAGE_H;//480;
        req.display.rotate          = 90; //usb后视频图像旋转显示
        /* #endif // CONFIG_VIDEO2_ENABLE */
    }
    if (video_display[id]) {
        int err = server_request(video_display[id], VIDEO_REQ_DISPLAY, &req);
        if (err) {
            printf("video server request error!");
            server_close(video_display[id]);
            video_display[id] = NULL;
            /* tuya_hal_mutex_unlock(g_video_ctrl.mutex); */
            return -1;
        }
        return err;
    }
    return -1;
    /* tuya_hal_mutex_unlock(g_video_ctrl.mutex); */
#endif
}

int tuya_uvc_display()
{
    union video_req req = {0};
    char fb_name[4];
    static char dev_name[20];
#ifdef CONFIG_DISPLAY_ENABLE
    /* if(video_display[id] == NULL) */
    /* { */
    /* #ifdef CONFIG_VIDEO0_ENABLE */
    /* video_display = server_open("video_server", "video0.1"); */
    /* #endif // CONFIG_VIDEO2_ENABLE */
    /* #ifdef CONFIG_VIDEO1_ENABLE */
    /* video_display = server_open("video_server", "video1.1"); */
    /* #endif // CONFIG_VIDEO2_ENABLE */
#ifdef CONFIG_VIDEO2_ENABLE
    video_display[2] = server_open("video_server", "video2.1");
#endif // CONFIG_VIDEO2_ENABLE
    /* } */
    /* printf("video_disp_start: %d, %d x %d\n", id, win->width, win->height); */

    /* if (win->width == (u16) - 1) { */
    /* puts("video_disp_hide\n"); */
    /* return 0; */
    /* } */
#ifdef CONFIG_VIDEO2_ENABLE
    /* if(id == 2){ */
    if (uvc_host_online() < 0) {
        return -EFAULT;
    }
    /* } */
#endif

#ifdef CONFIG_VIDEO2_ENABLE
    sprintf(fb_name, "fb%d", 2 + 1);
#endif // CONFIG_VIDEO2_ENABLE

    req.display.fb 		        = fb_name;//"fb3";
    req.display.left  	        = 0;
    req.display.top 	        = 0;
    req.display.width 	        = 800;
    req.display.height 	        = 480;
    req.display.border_left     = 0;
    req.display.border_top      = 0;
    req.display.border_right    = 0;
    req.display.border_bottom   = 0;
    req.display.win_type        = 0;
    req.display.src_crop_enable = 0;
    req.display.mirror          = 0;  //1: 显示镜像、垂直、水平
    req.display.jaggy           = 0;
    req.display.state 	        = VIDEO_STATE_START;
    req.display.pctl            = NULL;

#ifndef CONFIG_VIDEO2_ENABLE
    req.display.camera_config   = NULL;
    req.display.camera_type     = VIDEO_CAMERA_NORMAL;
#else
    req.display.uvc_id          = uvc_host_online();
    req.display.camera_config   = NULL;
    req.display.camera_type     = VIDEO_CAMERA_UVC;
    req.display.src_w           = CONFIG_VIDEO_IMAGE_W;
    req.display.src_h           = CONFIG_VIDEO_IMAGE_H;
    req.display.rotate          = 90; //usb后视频图像旋转显示
#endif // CONFIG_VIDEO2_ENABLE
    if (video_display[2]) {
        int err = server_request(video_display[2], VIDEO_REQ_DISPLAY, &req);
        if (err) {
            printf("video server request error!");
            server_close(video_display[2]);
            video_display[2] = NULL;
            return -EFAULT;
        }
    }
#endif
}



void tuya_display_stop(int id)
{
    union video_dec_req dec_req = {0};
    union video_req req = {0};

    if (video_display[id]) {
        req.display.state 	= VIDEO_STATE_STOP;
        server_request(video_display[id], VIDEO_REQ_DISPLAY, &req);
        server_close(video_display[id]);
        video_display[id] = NULL;
    }
}

static int video_disp_win_switch(int mode, int dev_id)
{
    int i;
    int err = 0;
    int next_win = 0;
    int curr_win = disp_state;
    static u16 mirror[4] = {0};

#ifdef CONFIG_DISPLAY_ENABLE
    switch (mode) {
    case DISP_WIN_SW_SHOW_PARKING:
        /* if (!video_online[disp_park_sel]) { */
        /* return -ENODEV; */
        /* } */
        next_win        = DISP_PARK_WIN;
        break;
    case DISP_WIN_SW_HIDE_PARKING:
        next_win = curr_win;
        curr_win = DISP_PARK_WIN;
        break;
    case DISP_WIN_SW_SHOW_SMALL:
        curr_win        = DISP_MAIN_WIN;
        next_win        = DISP_MAIN_WIN;
        break;
    case DISP_WIN_SW_SHOW_NEXT:
        /* if (video_rec_online_nums() < 2) { */
        /* return 0; */
        /* } */
#if 0
        if (get_parking_status() == 1) {
            return 0;
        }
#endif
        next_win = curr_win;

        if (++next_win >= DISP_PARK_WIN) {
            next_win = DISP_MAIN_WIN;
        }
        break;
    case DISP_WIN_SW_DEV_IN:
        if (curr_win != DISP_MAIN_WIN) {
            return 0;
        }
        next_win = curr_win;
        break;
    case DISP_WIN_SW_DEV_OUT:
        next_win = DISP_MAIN_WIN;
        break;
    case DISP_WIN_SW_MIRROR:
        /* mirror[dev_id] = !mirror[dev_id]; */
        /* video_set_disp_mirror(dev_id, mirror[dev_id]); */
        next_win = curr_win;
        break;
    default:
        return -EINVAL;
    }


    for (i = 1; i < CONFIG_VIDEO_REC_NUM; i++) {
        /* video_disp_stop(i); */
        tuya_display_stop(i);
    }

    if (curr_win != next_win || mode == DISP_WIN_SW_MIRROR) {
        /* video_disp_stop(0); */
        tuya_display_stop(0);
        err = tuya_video_display(0, &disp_window[next_win][0]);
    }

    for (i = 0; i < CONFIG_VIDEO_REC_NUM; i++) {
        err = tuya_video_display(i, &disp_window[next_win][0]);
        if (err == 0) {
            break;
        }
    }

    if (next_win != DISP_PARK_WIN) {
        disp_state = next_win;
    }

#endif

    return err;
}

int display_convert(int flag)
{
    int ret;
    ty_video_set_disp_window();
    for (int i = 0; i < 4; i++) {
        tuya_display_stop(i);
    }
    switch (video_state) {
    case 2: //mipi
        ret = tuya_video_display(0, &disp_window[DISP_MAIN_WIN][0]);
        break;
    case 6: //mipi + uvc
#if 0
        if (!flag) {
            ret = tuya_video_display(0, &disp_window[DISP_MAIN_WIN][0]);
            if (ret == 0) {
                ret = tuya_video_display(2, &disp_window[DISP_MAIN_WIN][2]);
            } else {
                ret = tuya_video_display(2, &disp_window[DISP_MAIN_WIN][0]);
            }
        } else {
            ret = tuya_video_display(2, &disp_window[DISP_MAIN_WIN][0]);
            if (ret == 0) {
                ret = tuya_video_display(0, &disp_window[DISP_MAIN_WIN][2]);
            } else {
                ret = tuya_video_display(0, &disp_window[DISP_MAIN_WIN][0]);
            }
        }
#endif
        ret = tuya_video_display(0, &disp_window[DISP_HALF_WIN][0]);
        if (ret == 0) {
            ret = tuya_video_display(2, &disp_window[DISP_HALF_WIN][2]);
        } else {
            ret = tuya_video_display(2, &disp_window[DISP_MAIN_WIN][0]);
        }
        if (ret != 0) {
            tuya_display_stop(0);
            ret = tuya_video_display(0, &disp_window[DISP_MAIN_WIN][0]);
        }
        break;
    case 3: //dvp
        ret = tuya_video_display(1, &disp_window[DISP_MAIN_WIN][0]);
        break;
    case 7: //dvp + uvc
#if 0
        if (!flag) {
            ret = tuya_video_display(1, &disp_window[DISP_MAIN_WIN][0]);
            if (ret == 0) {
                ret = tuya_video_display(2, &disp_window[DISP_MAIN_WIN][2]);
            } else {
                ret = tuya_video_display(2, &disp_window[DISP_MAIN_WIN][0]);
            }
        } else {
            ret = tuya_video_display(2, &disp_window[DISP_MAIN_WIN][0]);
            if (ret == 0) {
                ret = tuya_video_display(1, &disp_window[DISP_MAIN_WIN][2]);
            } else {
                ret = tuya_video_display(1, &disp_window[DISP_MAIN_WIN][0]);
            }
        }
#endif
        ret = tuya_video_display(1, &disp_window[DISP_HALF_WIN][0]);
        if (ret == 0) {
            ret = tuya_video_display(2, &disp_window[DISP_HALF_WIN][2]);
        } else {
            ret = tuya_video_display(2, &disp_window[DISP_MAIN_WIN][0]);
        }
        if (ret != 0) {
            tuya_display_stop(1);
            ret = tuya_video_display(1, &disp_window[DISP_MAIN_WIN][0]);
        }
        break;
    case 4: //uvc
        ret = tuya_video_display(2, &disp_window[DISP_MAIN_WIN][0]);
        break;
    case 8: // video3
        ret = tuya_video_display(3, &disp_window[DISP_MAIN_WIN][0]);
        break;
    case 12:// video+uvc
#if 0
        if (!flag) {
            ret = tuya_video_display(3, &disp_window[DISP_MAIN_WIN][0]);
            if (ret == 0) {
                ret = tuya_video_display(2, &disp_window[DISP_MAIN_WIN][2]);
            } else {
                ret = tuya_video_display(2, &disp_window[DISP_MAIN_WIN][0]);
            }
        } else {
            ret = tuya_video_display(2, &disp_window[DISP_MAIN_WIN][0]);
            if (ret == 0) {
                ret = tuya_video_display(3, &disp_window[DISP_MAIN_WIN][2]);
            } else {
                ret = tuya_video_display(3, &disp_window[DISP_MAIN_WIN][0]);
            }
        }
#endif
        ret = tuya_video_display(3, &disp_window[DISP_HALF_WIN][0]);
        if (ret == 0) {
            ret = tuya_video_display(2, &disp_window[DISP_HALF_WIN][2]);
        } else {
            ret = tuya_video_display(2, &disp_window[DISP_MAIN_WIN][0]);
        }
        if (ret != 0) {
            tuya_display_stop(3);
            ret = tuya_video_display(3, &disp_window[DISP_MAIN_WIN][0]);
        }
        break;
    case 5: //mipi+dvp
#if 0
        if (!flag) {
            ret = tuya_video_display(0, &disp_window[DISP_MAIN_WIN][0]);
            if (ret == 0) {
                ret = tuya_video_display(1, &disp_window[DISP_MAIN_WIN][2]);
            } else {
                ret = tuya_video_display(1, &disp_window[DISP_MAIN_WIN][0]);
            }
        } else {
            ret = tuya_video_display(1, &disp_window[DISP_MAIN_WIN][0]);
            if (ret == 0) {
                ret = tuya_video_display(0, &disp_window[DISP_MAIN_WIN][2]);
            } else {
                ret = tuya_video_display(0, &disp_window[DISP_MAIN_WIN][0]);
            }
        }
#endif
        ret = tuya_video_display(0, &disp_window[DISP_HALF_WIN][0]);
        if (ret == 0) {
            ret = tuya_video_display(1, &disp_window[DISP_HALF_WIN][2]);
        } else {
            ret = tuya_video_display(1, &disp_window[DISP_MAIN_WIN][0]);
        }
        if (ret != 0) {
            tuya_display_stop(0);
            ret = tuya_video_display(0, &disp_window[DISP_MAIN_WIN][0]);
        }
        break;
    case 11: //mipi video 3+dvp
#if 0
        if (!flag) {
            ret = tuya_video_display(1, &disp_window[DISP_MAIN_WIN][0]);
            if (ret == 0) {
                ret = tuya_video_display(3, &disp_window[DISP_MAIN_WIN][2]);
            } else {
                ret = tuya_video_display(3, &disp_window[DISP_MAIN_WIN][0]);
            }
        } else {
            ret = tuya_video_display(3, &disp_window[DISP_MAIN_WIN][0]);
            if (ret == 0) {
                ret = tuya_video_display(1, &disp_window[DISP_MAIN_WIN][2]);
            } else {
                ret = tuya_video_display(1, &disp_window[DISP_MAIN_WIN][0]);
            }
        }
#endif
        ret = tuya_video_display(1, &disp_window[DISP_HALF_WIN][0]);
        if (ret == 0) {
            ret = tuya_video_display(3, &disp_window[DISP_HALF_WIN][2]);
        } else {
            ret = tuya_video_display(3, &disp_window[DISP_MAIN_WIN][0]);
        }
        if (ret != 0) {
            tuya_display_stop(1);
            ret = tuya_video_display(1, &disp_window[DISP_MAIN_WIN][0]);
        }
        break;
    default:
        ret = -1;
        break;
    }
    return ret;
}


/**
 * @berief: uvc server open and start uvc recode
 * @param   none
 * @return: none
 * @retval: none
 */
INT_T  uvc_video_start(INT_T img_w, INT_T img_h, INT_T fps)
{
    INT_T ret = 0;
    PR_DEBUG("---------uvc online :%d", dev_online("uvc"));
    if (!dev_online("uvc")) {
        PR_ERR("uvc is not online");
        return -EFAULT;
    }

    /* if (0 == g_video_ctrl.mutex) { */
    /* tuya_hal_mutex_create_init(&g_video_ctrl.mutex); */
    /* } */
    /*打开摄像头*/
    /* tuya_hal_mutex_lock(g_video_ctrl.mutex); */

    if (video_server[2]) {
        if (g_video_ctrl.camera_start[2]) {
            PR_NOTICE("camera_start is already start");
            /* tuya_hal_mutex_unlock(g_video_ctrl.mutex); */
            return 0;
        }

        /* _start: */
        req.rec.camera_type = VIDEO_CAMERA_NORMAL;
        req.rec.channel = 0;
        req.rec.width 	= img_w;//CONFIG_USER_VIDEO_WIDTH;
        req.rec.src_w 	= img_w;//CONFIG_USER_VIDEO_WIDTH;
        req.rec.height 	= img_h;//CONFIG_USER_VIDEO_HEIGHT;
        req.rec.src_h 	= img_h;//CONFIG_USER_VIDEO_HEIGHT;
        req.rec.state 	= VIDEO_STATE_START;
        req.rec.format 	= USER_VIDEO_FMT_AVI;
        req.rec.quality = VIDEO_LOW_Q;//VIDEO_MID_Q;
        req.rec.fps = 10;//25;//fps;//10;
#ifdef CONFIG_VIDEO2_ENABLE
        req.rec.uvc_id = uvc_host_online();
#endif
        req.rec.real_fps = 10;// 25;//fps;

        req.rec.cycle_time = 1;//60;
        req.rec.abr_kbps = user_video_rec_get_abr(req.rec.width);//1300;//user_video_rec_get_abr(req.rec.width);//JPEG图片码率

        memset(req_buf, 0, CAMERA_MAX_JPEG_SIZE);
        req.rec.buf = req_buf;
        req.rec.buf_len = CAMERA_MAX_JPEG_SIZE;
        PR_DEBUG("video req.rec.buf : 0x%x", req.rec.buf);

        /* req.rec.packet_cb = ty_video_frame_cb;//uvc_jpeg_cb;//注册数据包回调函数进行协议转发 */
//        if(!g_video_ctrl.lcd_open) {
//            drop_jpeg_count = 0;
//        } else {
        drop_jpeg_count = TY_DROP_JPEG_COUNT + 1;
//        }


        /* server_request(video_server[2], VIDEO_REQ_SET_PACKET_CALLBACK, &req); */
        ret = server_request(video_server[2], VIDEO_REQ_REC, &req);
        if (0 == ret) {
            g_video_ctrl.camera_start[2] = TRUE;
            PR_NOTICE("video server open w=%d h=%d f=%d", img_w, img_h, fps);
        } else {
            PR_NOTICE("video server open err ! w=%d h=%d f=%d", img_w, img_h, fps);
        }

        /* tuya_hal_mutex_unlock(g_video_ctrl.mutex); */

        return ret;
    } else {
        PR_DEBUG("video server open -1");
        /* tuya_hal_mutex_unlock(g_video_ctrl.mutex); */
        return -1;
    }
}

#if 1
static void rec_dev_server_event_handler(void *priv, int argc, int *argv)
{
    /*
     *该回调函数会在录像过程中，写卡出错被当前录像APP调用，例如录像过程中突然拔卡
     */
    int mark = 2;
    struct intent it;

    switch (argv[0]) {
    case VIDEO_SERVER_UVM_ERR:
        PR_DEBUG("APP_UVM_DEAL_ERR\n");
        break;
    case VIDEO_SERVER_PKG_ERR:
        PR_DEBUG("video_server_pkg_err\n");
        /* if (state == VIDREC_STA_START) { */
        /* #ifdef CONFIG_WIFI_ENABLE */
        /* video_rec_err_notify("VIDEO_REC_ERR"); */
        /* #endif */
        ty_rec_stop(priv);
        /* } */
        break;
    case VIDEO_SERVER_PKG_END:
        PR_DEBUG("video_server_pkg_end\n");
        /* if (db_select("cyc")) { */
        ty_rec_savefile((int)priv);
        /* } else { */
        /* ty_rec_stop(priv); */
        /* video_rec_stop(0); */
        /* } */
        break;
    case VIDEO_SERVER_NET_ERR:
        PR_DEBUG("\nVIDEO_SERVER_NET_ERR\n");
        /* init_intent(&it); */
        /* it.data = &mark; */
        /* net_video_rec_stop(0); */
        /* set_net_video_rec_state(0); */
        /* __this_net->is_open = FALSE; */
        break;

    default :
        PR_DEBUG("unknow rec server cmd %x , %x!\n", argv[0], (int)priv);
        break;
    }
}

#endif


#if 1
int ty_rec_start(int id)
{
    int err;
    union video_req req = {0};
    struct video_text_osd text_osd;
    struct video_graph_osd graph_osd;
    u16 max_one_line_strnum;
    u16 osd_line_num;
    u16 osd_max_heigh;
    static char dev_name[20];

    int w, h, r, f;
    ty_get_camera_pic_w_h_r_f(&w, &h, &r, &f);

    puts("start_video_rec\n");
    if (0 == g_video_ctrl.mutex) {
        tuya_hal_mutex_create_init(&g_video_ctrl.mutex);
    }
    tuya_hal_mutex_lock(g_video_ctrl.mutex);


    if (g_video_ctrl.rec_start[id]) {
        PR_NOTICE("rec_start is already start");
        tuya_hal_mutex_unlock(g_video_ctrl.mutex);
        return 0;
    }

    if (id == 2) {
        if (uvc_host_online() < 0) {
            PR_DEBUG("uvc is not online");
            tuya_hal_mutex_unlock(g_video_ctrl.mutex);
            return -1;
        }
    }

    if (!audio_buf[id]) {
        audio_buf[id] = malloc(TY_AUDIO_BUF_SIZE);
        if (!audio_buf[id]) {
            PR_DEBUG("malloc audio buf err");
            tuya_hal_mutex_unlock(g_video_ctrl.mutex);
            return -1;
        }
    }

    if (!video_buf[id]) {
        video_buf[id] = malloc(TY_VREC_FBUF_SIZE);
        if (!video_buf[id]) {
            PR_DEBUG("malloc audio buf err");
            tuya_hal_mutex_unlock(g_video_ctrl.mutex);
            return -1;
        }
    }

    PR_DEBUG("open video%d, rec_start[%d]:%d", id, id, g_video_ctrl.rec_start[id]);


    if (video_server[id] != NULL) {
        video_rec[id] = video_server[id];
    }

    /* server_register_event_handler(video_rec[id], (VOID_T *)id, rec_dev_server_event_handler); */

    /* if (!video_server[id]) { */
    /* sprintf(dev_name, "video%d.%d", id, 0); */
    /* video_rec[id] = server_open("video_server", (void*)dev_name); */
    /* if (!video_rec[id]) { */
    /* tuya_hal_mutex_unlock(g_video_ctrl.mutex); */
    /* return -1; */
    /* } */
    /* server_register_event_handler(video_rec0, (void *)0, rec_dev_server_event_handler); */
    /* } */

    /* u32 res = db_select("res"); */
    /*
     *通道号，分辨率，封装格式，写卡的路径
     */

    if (id == 2) {
        req.rec.online = 0;
    } else {
        req.rec.online = 1;
    }
    req.rec.enable_dri  = 0;
    req.rec.channel     = 0;
    req.rec.camera_type = VIDEO_CAMERA_NORMAL;
    req.rec.width 	    = w;//w;//640;
    req.rec.height 	    = h;//h;//480;
    req.rec.format 	    = VIDEO_FMT_AVI;
    req.rec.state 	    = VIDEO_STATE_START;
    req.rec.file        = file[id]; //写卡
#ifdef CONFIG_WIFI_ENABLE
    req.rec.fsize = new_file_size[id];
#endif


    /*
     *帧率为0表示使用摄像头的帧率
     */
    req.rec.quality     = VIDEO_MID_Q;//VIDEO_LOW_Q;//VIDEO_MID_Q;//VIDEO_LOW_Q;//VIDEO_MID_Q;//VIDEO_LOW_Q;//VIDEO_MID_Q;
    if (id == 2) {
        req.rec.fps = f;
        req.rec.real_fps = f;
        req.rec.uvc_id = uvc_host_online();
    } else {
        req.rec.fps 	    = f;
        req.rec.real_fps 	= f;//video_rec_get_fps();
    }
    /* #ifdef CONFIG_WIFI_ENABLE */
    /* req.rec.fps 	    = 0; */
    /* req.rec.real_fps 	= 25;//video_rec_get_fps(); */
    /* #else */
    /* req.rec.fps 	    = 0; */
    /* req.rec.real_fps 	= 0; */
    /* #endif */

#if 1
    /*
     *采样率，通道数，录像音量，音频使用的循环BUF,录不录声音
     */
    req.rec.audio.sample_rate = 8000;
    req.rec.audio.channel 	= 1;
    req.rec.audio.volume    = 100;
    req.rec.audio.buf = audio_buf[id];
    req.rec.audio.buf_len = AUDIO_BUF_SIZE;

    /* req.rec.audio.sample_source = "mic"; */
    //req.rec.audio.sample_source = "user";
    /* req.rec.audio.fmt_format = AUDIO_FMT_PCM; */
    req.rec.pkg_mute.aud_mute = 1;//!db_select("mic");
#endif
    /*
     *码率，I帧和P帧比例，必须是偶数（当录MOV的时候才有效）,
     *roio_xy :值表示宏块坐标， [6:0]左边x坐标 ，[14:8]右边x坐标，[22:16]上边y坐标，[30:24]下边y坐标,写0表示1个宏块有效
     * roio_ratio : 区域比例系数
     */
    req.rec.abr_kbps = 1300;//video_rec_get_abr(req.rec.width);

#if defined __CPU_AC5401__
    req.rec.IP_interval = 0;
#elif defined __CPU_AC5601__
    if (req.rec.height > 720) {
        req.rec.IP_interval = 1;
    } else {
        req.rec.IP_interval = 0;
    }
#endif

#if 0
    /*感兴趣区域为下方 中间 2/6 * 4/6 区域，可以调整
    	感兴趣区域qp 为其他区域的 70% ，可以调整
    */
    /* req.rec.roi.roio_xy = (req.rec.height * 5 / 6 / 16) << 24 | (req.rec.height * 3 / 6 / 16) << 16 | (req.rec.width * 5 / 6 / 16) << 8 | (req.rec.width) * 1 / 6 / 16; */
    /* req.rec.roi.roi1_xy = (req.rec.height * 11 / 12 / 16) << 24 | (req.rec.height * 4 / 12 / 16) << 16 | (req.rec.width * 11 / 12 / 16) << 8 | (req.rec.width) * 1 / 12 / 16; */
    /* req.rec.roi.roi2_xy = 0; */
    /* req.rec.roi.roi3_xy = (1 << 24) | (0 << 16) | ((req.rec.width / 16) << 8) | 0; */
    /* req.rec.roi.roio_ratio = 256 * 70 / 100 ; */
    /* req.rec.roi.roio_ratio1 = 256 * 90 / 100; */
    /* req.rec.roi.roio_ratio2 = 0; */
    /* req.rec.roi.roio_ratio3 = 256 * 80 / 100; */


    /*
     * osd 相关的参数，注意坐标位置，x要64对齐，y要16对齐,底下例子是根据图像大小偏移到右下
     */
    text_osd.font_w = 16;
    text_osd.font_h = 32;

    max_one_line_strnum = strlen(video_rec_osd_buf);//21;
    osd_line_num = 1;
    /* if (db_select("num")) { */
    /* osd_line_num = 2; */
    /* } */
    osd_max_heigh = (req.rec.height == 1088) ? 1080 : req.rec.height ;
    text_osd.x = (req.rec.width - max_one_line_strnum * text_osd.font_w) / 64 * 64;
    text_osd.y = (osd_max_heigh - text_osd.font_h * osd_line_num) / 16 * 16;
    text_osd.color[0] = 0x057d88;
    text_osd.color[1] = 0xe20095;
    text_osd.color[2] = 0xe20095;
    text_osd.bit_mode = 2;
    text_osd.text_format = video_rec_osd_buf;
    text_osd.font_matrix_table = osd_str_total;
    text_osd.font_matrix_base = osd2_str_matrix;
    text_osd.font_matrix_len = sizeof(osd2_str_matrix);
    text_osd.direction = 1;


#ifdef CONFIG_OSD_LOGO
    graph_osd.bit_mode = 16;//2bit的osd需要配置3个color
    graph_osd.x = 0;
    graph_osd.y = 0;
    graph_osd.width = 256;
    graph_osd.height = 256;
    graph_osd.icon = icon_osd_buf;
    graph_osd.icon_size = sizeof(icon_osd_buf);
#endif
    req.rec.text_osd = NULL;
    req.rec.graph_osd = NULL;
    if (db_select("dat")) {
        req.rec.text_osd = &text_osd;
#ifdef CONFIG_OSD_LOGO
        req.rec.graph_osd = &graph_osd;
#endif
    }

    /*
     *慢动作倍数(与延时摄影互斥,无音频); 延时录像的间隔ms(与慢动作互斥,无音频)
     */
    req.rec.slow_motion = 0;
    if (req.rec.camera_type != VIDEO_CAMERA_UVC) {
        /* req.rec.tlp_time = db_select("gap"); */
        if (req.rec.tlp_time) {
            req.rec.real_fps = 1000 / req.rec.tlp_time;
            req.rec.pkg_fps = video_rec_get_fps();
        }
    } else {
        req.rec.tlp_time = 0;
    }

    if (req.rec.slow_motion || req.rec.tlp_time) {
        req.rec.audio.sample_rate = 0;
        req.rec.audio.channel 	= 0;
        req.rec.audio.volume    = 0;
        req.rec.audio.buf = 0;
        req.rec.audio.buf_len = 0;
    }
#endif

    req.rec.buf = video_buf[id];
    req.rec.buf_len = TY_VREC_FBUF_SIZE;

    /* #ifdef CONFIG_FILE_PREVIEW_ENABLE */
    /* req.rec.rec_small_pic 	= 1; */
    /* #else */
    req.rec.rec_small_pic 	= 0;
    /* #endif */

    /*
     *循环录像时间，文件大小
     */
    req.rec.cycle_time = 1;//db_select("cyc");
    if (req.rec.cycle_time == 0) {
        req.rec.cycle_time = 5;
    }

    /* #ifdef DIGITAL_SCALE */
    /* req.rec.src_crop_enable = VIDEO_CROP_ENABNLE | VIDEO_LARGE_IMAGE;////支持通过配置比例对IMC源数据进行裁剪,使用数字变焦需要写1 */
    /* req.rec.sca.x = (1280 - x_offset) / 2; */
    /* req.rec.sca.y = (720 - y_offset) / 2; */
    /* req.rec.sca.tar_w = x_offset; */
    /* req.rec.sca.tar_h = y_offset; */
    /* #else */
    /* req.rec.src_crop_enable = 0; */
    /* #endif */

    req.rec.cycle_time = req.rec.cycle_time * 60;

    /* #if CAMERA_THUMBNAIL_ENABLE */
    /* #endif */

    err = server_request(video_rec[id], VIDEO_REQ_REC, &req);
    if (err != 0) {
        puts("\n\n\nstart rec err\n\n\n");
    } else {
        PR_DEBUG("start rec:%d succ", id);
        g_video_ctrl.rec_start[id] = TRUE;
    }

    tuya_hal_mutex_unlock(g_video_ctrl.mutex);
    /* state = VIDREC_STA_START; */

    return err;
}

static int ty_rec_savefile(int id)
{
    union video_req req = {0};
    int err;
    int w, h, r, f;
    ty_get_camera_pic_w_h_r_f(&w, &h, &r, &f);
    if (!file[id]) {
        return -ENOENT;
    }
    if (0 == g_video_ctrl.mutex) {
        tuya_hal_mutex_create_init(&g_video_ctrl.mutex);
    }
    tuya_hal_mutex_lock(g_video_ctrl.mutex);

    if (!video_rec[id]) {
        printf("video_rec%d is null", id);
        tuya_hal_mutex_unlock(g_video_ctrl.mutex);
        return -1;
    }

    if (!g_video_ctrl.rec_start[id]) {
        printf("video%d rec is not open", id);
        tuya_hal_mutex_unlock(g_video_ctrl.mutex);
        return -1;
    }

    if (need_restart_rec) {
        PR_DEBUG("need restart rec");
        for (int i = 0; i < 4; i++) {
            ty_rec_stop(i);
        }
        /* video_rec_start(); */
        ty_rec_switch();
        return 0;
    }

    printf("\nvideo_rec_start_new_file: %d\n", id);

    video_rec_close_file(id);

    if (new_file[id] == NULL) {
        err = video_rec_del_old_file();
        if (err) {
            printf("vido rec del old file err");
            tuya_hal_mutex_unlock(g_video_ctrl.mutex);
            return -1;
            /* video_rec_post_msg("fsErr"); */
            /* goto __err; */
        }
        /* key_event_disable(); */
        /* touch_event_disable(); */
        /* sys_timeout_add(NULL, key_and_touch_enable, 2000); */
        /* post_msg = 1; */
    }
    file[id]     = new_file[id];
    new_file[id] = NULL;


    /* u32 res = db_select("res"); */

    req.rec.channel = 0;
    req.rec.width 	= w;//640;//rec_pix_w[res];
    req.rec.height 	= h;//480;//rec_pix_h[res];
    req.rec.format 	= VIDEO_FMT_AVI;
    req.rec.state 	= VIDEO_STATE_SAVE_FILE;
    req.rec.file    = file[id];

    /* #ifdef CONFIG_WIFI_ENABLE */
    if (id == 2) {
        req.rec.fps = f;
        req.rec.real_fps = f;
        req.rec.uvc_id = uvc_host_online();
    } else {
        req.rec.fps 	    = f;
        req.rec.real_fps 	= f;//video_rec_get_fps();
    }
    /* #else */
    /* req.rec.fps 	    = 0; */
    /* req.rec.real_fps 	= 0; */
    /* #endif */

    req.rec.cycle_time = 1;//db_select("cyc");
    if (req.rec.cycle_time == 0) {
        req.rec.cycle_time = 5;
    }

    req.rec.cycle_time = req.rec.cycle_time * 60;

    /* #if CAMERA_THUMBNAIL_ENABLE */
    /* struct jpg_thumbnail thumbnails; */
    /* err = camera_take_thumbnail(0); */
    /* if (!err) { */
    /* log_i("add thumbnail\n"); */
    /* thumbnails.enable = 1; */
    /* thumbnails.buf = thumbnail_img_buf; */
    /* thumbnails.len = thumbnail_img_size; */
    /* req.rec.thumbnails = &thumbnails; */
    /* } */
    /* #endif */


#if 1
    /*
     *采样率，通道数，录像音量，音频使用的循环BUF,录不录声音
     */
    req.rec.audio.sample_rate = 8000;
    req.rec.audio.channel 	= 1;
    req.rec.audio.volume    = 100;//AUDIO_VOLUME;
    req.rec.pkg_mute.aud_mute = 1;//!db_select("mic");
#endif
    /* req.rec.tlp_time = db_select("gap"); */
    /* if (req.rec.tlp_time) { */
    /* req.rec.real_fps = 1000 / req.rec.tlp_time; */
    /* req.rec.pkg_fps = video_rec_get_fps(); */
    /* } */



    err = server_request(video_rec[id], VIDEO_REQ_REC, &req);
    if (err != 0) {
        PR_DEBUG("rec%d_save_file: err=%d\n", id, err);
        ty_rec_stop(id);
        /* return err; */
    }
    tuya_hal_mutex_unlock(g_video_ctrl.mutex);
    return err;
    /* return 0; */
}


static int ty_rec_stop(int id)
{
    union video_req req = {0};
    int err;
    /* __this_net->net_state = VIDREC_STA_STOPING; */
    if (0 == g_video_ctrl.mutex) {
        tuya_hal_mutex_create_init(&g_video_ctrl.mutex);
    }
    tuya_hal_mutex_lock(g_video_ctrl.mutex);

    if (g_video_ctrl.rec_start[id] == NULL) {
        printf("video%d rec is not start", id);
        tuya_hal_mutex_unlock(g_video_ctrl.mutex);
        return -1;
    }
    if (video_rec[id]) {

        PR_DEBUG("\nnet video rec%d stop\n", id);
        req.rec.channel = 0;
        req.rec.state = VIDEO_STATE_STOP;
        err = server_request(video_rec[id], VIDEO_REQ_REC, &req);
        if (err != 0) {
            printf("\nstop rec err 0x%x\n", err);
        } else {
            video_rec_close_file(id);
            g_video_ctrl.rec_start[id] = FALSE;
            rec_state = 0;
        }
        /* net_video_rec_set_bitrate(video_rec_get_abr(__this_net->net_videoreq[0].rec.width)); */
        /* if (close) { */
        /* server_close(__this_net->net_video_rec); */
        /* __this_net->net_video_rec = NULL; */
        /* } */
    } else {
        err = -1;
    }

    /* __this_net->net_state = VIDREC_STA_STOP; */

    printf("\nty rec%d stop end\n", id);

    tuya_hal_mutex_unlock(g_video_ctrl.mutex);
    return err;

}

int ty_rec_switch() //录像入口
{

    int ret;
    if (!storage_device_available()) {
        printf("sd is not online");
        return 0;
    }
    /* for(int i=0; i<4; i++) { */
    /* if(g_video_ctrl.rec_start[i]) { */
    /* goto __start;	 */
    /* } */
    /* } */
    for (int i = 0; i < 4; i++) {
        ty_video_stop(i);
    }
    /*
    * 判断SD卡空间，删除旧文件并创建新文件
    */
    ret = video_rec_del_old_file();
    if (ret) {
        PR_DEBUG("start free space err\n");
        /* video_rec_post_msg("fsErr"); */
        return -1;//VREC_ERR_START_FREE_SPACE;
    }

    for (int i = 0; i < CONFIG_VIDEO_REC_NUM; i++) {
        file[i] = new_file[i];
        new_file[i] = NULL;
    }
    /* __start: */
    switch (video_state) {
    case 2: //mipi
        ret = ty_rec_start(0);
        if (ret != 0) {
            ty_rec_stop(0);
        }
        break;
    case 3: //dvp
        ret = ty_rec_start(1);
        if (ret != 0) {
            ty_rec_stop(1);
        }
        break;
    case 4: //uvc
        ret = ty_rec_start(2);
        if (ret != 0) {
            ty_rec_stop(2);
        }
        break;
    case 8: //video3
        ret = ty_rec_start(3);
        if (ret != 0) {
            ty_rec_stop(3);
        }
        break;
    case 5: //mipi+dvp
        ret = ty_rec_start(0);
        if (ret != 0) {
            PR_DEBUG("ty rec start failed");
            ty_rec_stop(0);
        }
        ret = ty_rec_start(1);
        if (ret != 0) {
            ty_rec_stop(1);
        }
        break;
    case 6://mipi+uvc
        ret = ty_rec_start(0);
        if (ret != 0) {
            ty_rec_stop(0);
        }
        ret = ty_rec_start(2);
        if (ret != 0) {
            ty_rec_stop(2);
        }
        break;
    case 7: //dvp+uvc
        ret = ty_rec_start(1);
        if (ret != 0) {
            ty_rec_stop(1);
        }
        ret = ty_rec_start(2);
        if (ret != 0) {
            ty_rec_stop(2);
        }
        /* video_convert(0); */
        break;
    case 11: //video 3+dvp
        ret = ty_rec_start(1);
        if (ret != 0) {
            ty_rec_stop(1);
        }
        ret = ty_rec_start(3);
        if (ret != 0) {
            ty_rec_stop(3);
        }
        break;
    case 12://video3+uvc
        ret = ty_rec_start(2);
        if (ret != 0) {
            ty_rec_stop(0);
        }
        ret = ty_rec_start(3);
        if (ret != 0) {
            ty_rec_stop(3);
        }
        break;

    default:
        break;
    }

    rec_state = 1;
    video_convert(0);
    return ret;
}

#endif

INT_T  ty_video_start(INT_T id, INT_T img_w, INT_T img_h, INT_T fps) //net
{
    PR_DEBUG("into ty video start id:%d", id);
    INT_T ret = 0;
    STATIC char dev_name[20];
    if (0 == g_video_ctrl.mutex) {
        tuya_hal_mutex_create_init(&g_video_ctrl.mutex);
    }
    /* 打开摄像头 */
    tuya_hal_mutex_lock(g_video_ctrl.mutex);

    if (video_server[id]) {
        PR_DEBUG("open video%d, g_video_ctrl.camera_start[%d]:%d", id, id, g_video_ctrl.camera_start[id]);
        if (g_video_ctrl.camera_start[id]) {
            PR_NOTICE("camera_start is already start");
            tuya_hal_mutex_unlock(g_video_ctrl.mutex);
            return 0;
        }

        req.rec.camera_type = VIDEO_CAMERA_NORMAL;
        req.rec.channel = 1;
        req.rec.width 	= img_w;//img_w;//CONFIG_USER_VIDEO_WIDTH;
        req.rec.src_w 	= 1280;//CONFIG_USER_VIDEO_WIDTH;
        req.rec.height 	= img_h;//img_h;//CONFIG_USER_VIDEO_HEIGHT;
        req.rec.src_h 	= 720;//CONFIG_USER_VIDEO_HEIGHT;
        req.rec.state 	= VIDEO_STATE_START;
        req.rec.format 	= USER_VIDEO_FMT_AVI;
        req.rec.quality = VIDEO_MID_Q;//VIDEO_LOW_Q;//VIDEO_MID_Q;

        req.rec.IP_interval = 0;
        if (id == 2) {
            req.rec.online = 0;
        } else {
            req.rec.online = 1;
        }

        if (id == 2) {
            if (uvc_host_online() < 0) {
                tuya_hal_mutex_unlock(g_video_ctrl.mutex);
                return -1;
            }
#ifdef CONFIG_VIDEO2_ENABLE
            req.rec.uvc_id = uvc_host_online();
#endif
        }
        req.rec.fps = fps;//10;
        req.rec.real_fps = fps;

        req.rec.cycle_time = 1;
        req.rec.cycle_time = req.rec.cycle_time * 60;
        req.rec.abr_kbps = 1300;//1300;//1000;// user_video_rec_get_abr(req.rec.width);//user_video_rec_get_abr(req.rec.width); //2800;//8000;//2800;// user_video_rec_get_abr(req.rec.width);//1300;//user_video_rec_get_abr(req.rec.width);//JPEG图片码率

        memset(req_buf, 0, CAMERA_MAX_JPEG_SIZE);
        req.rec.buf = req_buf;
        req.rec.buf_len = CAMERA_MAX_JPEG_SIZE;
        /* PR_DEBUG("video req.rec.buf : 0x%x", req.rec.buf); */

        /* req.rec.packet_cb = ty_video_frame_cb;//uvc_jpeg_cb;//注册数据包回调函数进行协议转发 */
        /* server_request(video_server[id], VIDEO_REQ_SET_PACKET_CALLBACK, &req); */

        drop_jpeg_count = TY_DROP_JPEG_COUNT + 1;

#if 0
        if (g_video_ctrl.rec_start[id]) {
            /*
             *采样率，通道数，录像音量，音频使用的循环BUF,录不录声音
            */
            memset(req_audio_buf, 0, AUDIO_MAX_SIZE);
            req.rec.audio.sample_rate = 8000;
            req.rec.audio.channel 	= 1;
            req.rec.audio.volume    = 100;
            req.rec.audio.buf = req_audio_buf;//audio_buf[id];
            req.rec.audio.buf_len = AUDIO_MAX_SIZE;

            /* req.rec.audio.sample_source = "mic"; */
            //req.rec.audio.sample_source = "user";
            /* req.rec.audio.fmt_format = AUDIO_FMT_PCM; */
            req.rec.pkg_mute.aud_mute = 1;//!db_select("mic");
        }
#endif

        //数据外引，用于网络
#if 1
        req.rec.target = VIDEO_TO_OUT;
        req.rec.out.path = NULL;//req.rec.net_par.netpath;
        req.rec.out.arg  = NULL;
        req.rec.out.open = ty_stream_open;//NULL;//stream_open;
        req.rec.out.send = ty_stream_write;//stream_write;
        req.rec.out.close = ty_stream_close;//NULL;//stream_close;
#endif
        ret = server_request(video_server[id], VIDEO_REQ_REC, &req);
        if (0 == ret) {
            g_video_ctrl.camera_start[id] = TRUE;
            PR_NOTICE("video server open w=%d h=%d f=%d", img_w, img_h, fps);
        } else {
            PR_NOTICE("video server open err ! w=%d h=%d f=%d", img_w, img_h, fps);
        }

        tuya_hal_mutex_unlock(g_video_ctrl.mutex);

        return ret;
    } else {
        ret = -1;
        tuya_hal_mutex_unlock(g_video_ctrl.mutex);
        return ret;
    }
}

INT_T  ty_video_stop(INT_T id)
{
    PR_DEBUG("into ty video stop");
    if (0 == g_video_ctrl.mutex) {
        tuya_hal_mutex_create_init(&g_video_ctrl.mutex);
    }
    /* #if TY_USE_IMAGE_TIMER */
    /* sys_stop_timer(g_video_ctrl.restart_camera_id); */
    /* #endif */
    tuya_hal_mutex_lock(g_video_ctrl.mutex);
    if (!g_video_ctrl.camera_start[id]) {
        printf("video%d is not open", id);
        tuya_hal_mutex_unlock(g_video_ctrl.mutex);
        return -1;
    }
    if (video_server[id]) {
        req.rec.channel = 1;
        req.rec.state = VIDEO_STATE_STOP;
        server_request(video_server[id], VIDEO_REQ_REC, &req);
        PR_NOTICE("video server stop");
        g_video_ctrl.camera_start[id] = FALSE;
        tuya_hal_mutex_unlock(g_video_ctrl.mutex);
        return 0;
    } else {
        tuya_hal_mutex_unlock(g_video_ctrl.mutex);
        return -1;
    }
}

void video_convert(INT_T flag) //双路摄像头切换
{
    int w, h, r, f;
    int ret;
    ty_get_camera_pic_w_h_r_f(&w, &h, &r, &f);
    PR_DEBUG("video_state:%d, flag:%d", video_state, flag);
    for (int i = 0; i < 4; i++) {
        ty_video_stop(i);
    }
    switch (video_state) {
    case 2: //mipi
        ret = ty_video_start(0, w, h, f);
        break;
    case 3: //dvp
        ret = ty_video_start(1, w, h, f);
        break;
    case 4: //uvc
        ret = ty_video_start(2, w, h, f);
        /* uvc_video_start(w, h, f); */
        break;
    case 8: //mipi video3
        ret = ty_video_start(3, w, h, f);
        /* uvc_video_start(w, h, f); */
        break;
    case 5: //mipi+dvp
        if (!flag) {
            /* ty_video_stop(1); */
            ret = ty_video_start(0, w, h, f);
            if (ret != 0) {
                ty_video_start(1, w, h, f);
            }
        } else {
            /* ty_video_stop(0); */
            ret = ty_video_start(1, w, h, f);
            if (ret != 0) {
                ty_video_start(0, w, h, f);
            }
        }
        break;
    case 6://mipi+uvc
        if (!flag) {
            /* ty_video_stop(2); */
            ret = ty_video_start(0, w, h, f);
            if (ret != 0) {
                ty_video_start(2, w, h, f);
                /* uvc_video_start(w, h, f); */
            }
        } else {
            /* ty_video_stop(0); */
            ret = ty_video_start(2, w, h, f);
            /* ret = uvc_video_start(w, h, f); */
            if (ret != 0) {
                ty_video_start(0, w, h, f);
            }
        }
        break;
    case 7: //dvp+uvc
        if (!flag) {
            /* ty_video_stop(2); */
            ret = ty_video_start(1, w, h, f);
            if (ret != 0) {
                ty_video_start(2, w, h, f);
                /* uvc_video_start(w, h, f); */
            }
        } else {
            /* ty_video_stop(1); */
            ret = ty_video_start(2, w, h, f);
            /* ret = uvc_video_start(w, h, f); */
            if (ret != 0) {
                ty_video_start(1, w, h, f);
            }
        }
        break;
    case 11: //mipi video 3+dvp
        if (!flag) {
            /* ty_video_stop(1); */
            ret = ty_video_start(3, w, h, f);
            if (ret != 0) {
                ty_video_start(1, w, h, f);
            }
        } else {
            /* ty_video_stop(3); */
            ret = ty_video_start(1, w, h, f);
            if (ret != 0) {
                ty_video_start(3, w, h, f);
            }
        }
        break;
    case 12://mipi video3+uvc
        if (!flag) {
            /* ty_video_stop(2); */
            ret = ty_video_start(3, w, h, f);
            if (ret != 0) {
                ty_video_start(2, w, h, f);
                /* uvc_video_start(w, h, f); */
            }
        } else {
            /* ty_video_stop(3); */
            ret = ty_video_start(2, w, h, f);
            /* ret = uvc_video_start(w, h, f); */
            if (ret != 0) {
                ty_video_start(3, w, h, f);
            }
        }
        break;

    default:
        break;
    }
    return;
}

static int ty_video_take_photo(void)
{
    union video_req req = {0};
    for (int i = 0; i < 4; i++) {
        if (g_video_ctrl.camera_start[i]) {
            PR_DEBUG("video%d is online", i);
            if (i == 0) {
                req.rec.rec_save_path = CAMERA0_CAP_PATH"img_***.jpg";
            } else if (i == 1) {
                req.rec.rec_save_path = CAMERA1_CAP_PATH"img_***.jpg";
            } else if (i == 2) {
                req.rec.rec_save_path = CAMERA1_CAP_PATH"img_***.jpg";
            } else {
                req.rec.rec_save_path = CAMERA2_CAP_PATH"img_***.jpg";
            }
            req.rec.channel = 1;
            /* req.rec.rec_save_path = CAMERA0_CAP_PATH"img_***.jpg"; */
            int ret = server_request(video_server[i], VIDEO_REQ_SAVE_FRAME, &req);

            if (ret != 0) {
                printf("save photo error");
            } else {
                printf("save photo to sd card succ");
            }
            return 0;
        }
    }
}

#if TCFG_HOST_AUDIO_ENABLE
CHAR_T get_audio_id(VOID_T)
{
    return audioid;
}
#endif

BOOL_T ty_audio_device_online(VOID_T)
{
//    return g_video_ctrl.audio_online;
    return true;
}
BOOL_T ty_video_device_online(VOID_T)
{
//    return g_video_ctrl.camera_online;
    return true;
}
STATIC INT_T video_rec_device_event_handler(struct device_event *event)
{
    INT_T err;
    UCHAR_T *tpye;
    INT_T w, h, r, f;
    if (!ASCII_StrCmp(event->arg, "usb_host*", 9)) {
        switch (event->event) {
        case DEVICE_EVENT_IN:
#if 0
            tpye = (UCHAR_T *)event->value;
            if (get_fs_is_update()) {
                break;
            }
            if (get_fs_is_config()) {
                break;
            }
            if (strstr(tpye, "uvc")) {
                uvcid = tpye[3] - '0';

                if (tuya_usb_auto_param_is_have()) {
                    if (USB_TYPE_NONE_E == tuya_usb_param_get()) {
                        tuya_usb_param_direct_update(USB_TYPE_UVC_E);
                    }
                }
                if ((true != get_fs_is_update())) {
                    tuya_video_stop_syn();
                    if (camera_power_off) {
                        tuya_video_start_syn_without_camer_on();
                    }
                } else {
                    break;
                }
                if (g_video_ctrl.lcd_open && (false == ty_lcd_in_ui_page()) && (true != get_fs_is_update())) {
                    PR_NOTICE("lcd status %d", g_video_ctrl.lcd_open);
                    tuya_video_lcd_ctr(true, LCD_FROM_APP, UI_MSG_CAMERA);
                } else if (ty_get_stream_status()) {
                    tuya_video_start_syn();
                }
                g_video_ctrl.camera_online = true;
                PR_NOTICE("UVC online : %s, id=%d usb_type=%d", tpye, uvcid, tuya_usb_param_get());
            }
#if TCFG_HOST_AUDIO_ENABLE
            if (strstr(tpye, "audio")) {
                audioid = tpye[5] - '0';

                if (tuya_usb_auto_param_is_have()) {
                    if (USB_TYPE_UVC_UAC_E != tuya_usb_param_get()) {
                        tuya_usb_param_direct_update(USB_TYPE_UVC_UAC_E);
                    }
                }
                // tuya_usb_audio_stop_play();
                // tuya_usb_audio_stop_record();
                g_video_ctrl.audio_online = true;
                PR_NOTICE("audio online : %s, id=%d usb_type=%d", tpye, audioid, tuya_usb_param_get());
            }
#endif
#endif // 0

            break;
        case DEVICE_EVENT_OUT:
#if 0
            tpye = (UCHAR_T *)event->value;
            if (strstr(tpye, "uvc")) {

                uvcid = tpye[3] - '0';
                tuya_video_stop_syn();
                g_video_ctrl.camera_online = false;
                PR_NOTICE("UVC  offline : %s, id=%d", tpye, uvcid);
            }
#if TCFG_HOST_AUDIO_ENABLE
            if (strstr(tpye, "audio")) {
                audioid = tpye[5] - '0';
                PR_NOTICE("audio offline : %s, id=%d", tpye, audioid);
                audioid = -1;
                g_video_ctrl.audio_online = false;
            }
#endif
#endif // 0
            break;
        }
    } else if (!ASCII_StrCmp(event->arg, "sd*", 4)) {
        switch (event->event) {
        case DEVICE_EVENT_IN:
            PR_NOTICE("sd in");
            break;
        case DEVICE_EVENT_OUT:
            PR_NOTICE("sd out");
            break;
        }
    } else if (!ASCII_StrCmp(event->arg, "sys_power", 7)) {
        switch (event->event) {
        case DEVICE_EVENT_POWER_CHARGER_IN:
            PR_NOTICE("CHAR_Tger in\n");
            break;
        case DEVICE_EVENT_POWER_CHARGER_OUT:
            PR_NOTICE("CHAR_Tger out\n");
            break;
        case DEVICE_EVENT_POWER_PERCENT:;//电池电量
            INT_T battery_val = event->value;
            PR_NOTICE("battery_val = %d \n", battery_val);
            break;
        }
    } else if (!strcmp(event->arg, "camera0_err")) {
        PR_NOTICE("camera0_err\n");
    }
    return false;
}

/**
 * @berief: camera data show on lcd device
 * @param   data leb
 * @return: none
 * @retval: none
 */
#if 0
VOID_T camera_show_lcd(UCHAR_T *buf, UINT_T size, INT_T width, INT_T height, UCHAR_T type)
{
    //PR_NOTICE("camera_show_lcd:%d %d %d %d\r\n",size,width,height,type);
    UCHAR_T *p_yuv_buf = buf;
    INT_T out_width;
    INT_T out_height;
    INT_T in_width;
    INT_T in_height;
    BOOL_T err_res = false;
    UCHAR_T yuv_type = type;
    INT_T w, h, f;
    INT_T rotat_angle = 0;
    INT_T ret;

    out_width = g_video_ctrl.lcd_width;
    out_height = g_video_ctrl.lcd_height;
#if TY_LCD_VIDEO_DEBUG_TIME
    INT_T time_ms_1 = tuya_hal_get_systemtickcount();
#endif
    ty_get_camera_pic_w_h_r_f(&w, &h, &rotat_angle, &f);

    if (width < height) {
        in_width = width;
        in_height = height;
    } else {
        in_width = height;
        in_height = width;
    }

    if (((320 == g_video_ctrl.lcd_width) && (480 == g_video_ctrl.lcd_height)) || ((240 == g_video_ctrl.lcd_width) && (320 == g_video_ctrl.lcd_height))) {

        if ((out_width > in_width && out_height >= in_height) || (out_width >= in_width && out_height > in_height)) {
            PR_NOTICE("lcd camera width:%d, height:%d,out_width:%d out_height %d\r\n", width, height, out_width, out_height);
            return;
        }

        if ((width == g_video_ctrl.lcd_width) && (height == g_video_ctrl.lcd_height)) {
            if (rotat_angle == 180) {
                if (!yuv_temp) {
                    yuv_temp = Malloc(g_video_ctrl.lcd_width * g_video_ctrl.lcd_height * 3 / 2 + 10);
                }
                YUV420p_REVERSAL(buf, yuv_temp, width, height, &out_width, &out_height, rotat_angle);
                p_yuv_buf = yuv_temp;
            } else {
                if (yuv_temp) {
                    Free(yuv_temp);
                    yuv_temp = NULL;
                }
                p_yuv_buf = buf;
            }
            out_width = g_video_ctrl.lcd_width;
            out_height = g_video_ctrl.lcd_height;

        } else if ((width == g_video_ctrl.lcd_height) && (height == g_video_ctrl.lcd_width)) {
            if (!yuv_temp) {
                yuv_temp = Malloc(g_video_ctrl.lcd_width * g_video_ctrl.lcd_height * 3 / 2 + 10);
            }
            if (rotat_angle != 90 && rotat_angle != 270) {
                YUV420p_REVERSAL(buf, yuv_temp, width, height, &out_width, &out_height, 270);
                p_yuv_buf = yuv_temp;
            } else  {
                YUV420p_REVERSAL(buf, yuv_temp, width, height, &out_width, &out_height, rotat_angle);
                p_yuv_buf = yuv_temp;
            }
            out_width = g_video_ctrl.lcd_width;
            out_height = g_video_ctrl.lcd_height;
        } else if (height > width) {
#if LCD_USE_YUV_CUT
            YUV420p_Cut(buf, width, height, NULL, yuv_data_size, (width - g_video_ctrl.lcd_width) / 2, g_video_ctrl.lcd_width, (height - g_video_ctrl.lcd_height) / 2, g_video_ctrl.lcd_height);
#else
            YUV420p_Soft_Scaling(buf, NULL, width, height, g_video_ctrl.lcd_width, g_video_ctrl.lcd_height);   //约耗时40ms
#endif
            if (rotat_angle == 180) {
                if (!yuv_temp) {
                    yuv_temp = Malloc(g_video_ctrl.lcd_width * g_video_ctrl.lcd_height * 3 / 2 + 10);
                }
                YUV420p_REVERSAL(buf, yuv_temp, g_video_ctrl.lcd_width, g_video_ctrl.lcd_height, &out_width, &out_height, rotat_angle);
                p_yuv_buf = yuv_temp;
            } else {
                if (yuv_temp) {
                    Free(yuv_temp);
                    yuv_temp = NULL;
                }
                p_yuv_buf = buf;
            }
            out_width = g_video_ctrl.lcd_width;
            out_height = g_video_ctrl.lcd_height;
        } else if (height < width) {
#if LCD_USE_YUV_CUT
            YUV420p_Cut(buf, width, height, NULL, yuv_data_size, (width - g_video_ctrl.lcd_height) / 2, g_video_ctrl.lcd_height, (height - g_video_ctrl.lcd_width) / 2, g_video_ctrl.lcd_width);
#else
            YUV420p_Soft_Scaling(buf, NULL, width, height, g_video_ctrl.lcd_height, g_video_ctrl.lcd_width);   //约耗时40ms
#endif
            if (!yuv_temp) {
                yuv_temp = Malloc(g_video_ctrl.lcd_width * g_video_ctrl.lcd_height * 3 / 2 + 10);
            }
            if (rotat_angle != 90 && rotat_angle != 270) {
                YUV420p_REVERSAL(buf, yuv_temp, g_video_ctrl.lcd_height, g_video_ctrl.lcd_width, &out_width, &out_height, 270);
                p_yuv_buf = yuv_temp;
            } else  {
                YUV420p_REVERSAL(buf, yuv_temp, g_video_ctrl.lcd_height, g_video_ctrl.lcd_width, &out_width, &out_height, rotat_angle);
                p_yuv_buf = yuv_temp;
            }
            out_width = g_video_ctrl.lcd_width;
            out_height = g_video_ctrl.lcd_height;
        } else {
            err_res = true;
        }
    } else {
        err_res = true;
    }


#if TY_LCD_VIDEO_DEBUG_TIME
    INT_T time_ms_2 = tuya_hal_get_systemtickcount();
    PR_NOTICE("YUV420p_Soft_Scaling+Rotate=%dms type=%d w=%d h=%d\n", (time_ms_2 - time_ms_1) * 10, type, width, height);
#endif
    if (err_res) {
        PR_NOTICE("unkown camera width:%d, height:%d,out_width:%d out_height %d\r\n", width, height, out_width, out_height);
        return;
    }

    if (g_video_ctrl.lcd_display_camera) {
        if (tuya_qrcode_is_run()) {
            if (!g_video_ctrl.camera_open) {
                //PR_NOTICE("n1");
                return ;
            }
            set_compose_mode(0, 0, 0, 0);

            ty_set_camera_pic_w_h(width, height);
        } else if (tuya_logo_is_display()) {
            set_compose_mode(0, 0, 0, 0);
        } else {
            if (!g_video_ctrl.camera_open) {
                //PR_NOTICE("n2");
                return ;
            }
            if (g_video_ctrl.show_page_open) {
                tuya_lcd_play_pic_syn(UI_MSG_CAMERA_SYN);
                g_video_ctrl.show_page_open = false;
            }
            set_compose_mode(2, 50, g_video_ctrl.lcd_height - 100, 100);
            ty_set_camera_pic_w_h(width, height);
        }
        //PR_NOTICE("R\n");
    } else {
        //PR_NOTICE("N");
    }
    qr_code_yuv_data(p_yuv_buf, yuv_data_size, out_width, out_height, type);
}
#endif // 0

STATIC VOID_T __video_task(PVOID_T pArg)
{
    OPERATE_RET op_ret = OPRT_OK;
    TY_VIDEO_CTRL_MSG *msg_data;
    INT_T w, h, r, f;
    int msg[16] = {0,};

    /* ty_video_set_disp_window(); */
    /* video_convert(0); */
    /* display_convert(0); */
    /* wait_completion(storage_device_ready, ty_rec_switch, NULL, NULL);	 */

    while (1) {
        //阻塞等待消息
        op_ret = os_q_pend(&g_video_ctrl.msg_que, 0, msg);
        if (op_ret != OPRT_OK && msg[0] == NULL) {
            if (op_ret != OPRT_MSG_LIST_EMPTY) {
                PR_ERR("WaitMessage op_ret:%d", op_ret);
            }
            continue;
        }
        msg_data = (TY_VIDEO_CTRL_MSG *)msg[0];
        switch (msg_data->cmd) {
        case MSG_START_VIDEO_SYN:
        case MSG_START_VIDEO_SYN_WITHOUT_CAMER_ON_STATUS: {
#if 0
            if (!g_video_ctrl.camera_open) {
                if (dev_online("uvc")) {
                    if (msg_data->cmd != MSG_START_VIDEO_SYN_WITHOUT_CAMER_ON_STATUS) {
                        g_video_ctrl.camera_open = true;
                        if (g_video_ctrl.show_page_open) {
                            /*                                tuya_lcd_play_pic_syn(UI_MSG_CAMERA_SYN);*/
                            g_video_ctrl.show_page_open = false;
                        }

                    }
                    ty_get_camera_pic_w_h_r_f(&w, &h, &r, &f);
                    uvc_video_satrt(w, h, f);
                }
            } else {
                PR_NOTICE("camera already open");
            }

//                tuya_hal_semaphore_post((SEM_HANDLE)flag);
            PR_NOTICE("uvc_video_satrt os_sem_post");

#endif
        }
        break;

        case MSG_STOP_VIDEO_SYN: {
#if 0
            uvc_video_stop();
            g_video_ctrl.camera_open = false;
//                tuya_hal_semaphore_post((SEM_HANDLE)flag);
            //PR_NOTICE("uvc_video_stop os_sem_post");
#endif
        }
        break;
        case MSG_STOP_VIDEO_NEW_SYN: {
#if 0
            VOID_T *sem;
            INT_T *p = (INT_T *)(msg_data->data);
            p++;
            sem = *p;
            if (flag == 1) {
                uvc_video_stop();
                g_video_ctrl.camera_open = false;
                goto common_deal;
            } else if (flag == 0) {
                if (!g_video_ctrl.camera_open) {
                    uvc_video_stop();
                    goto common_deal;
                }
                if (ty_get_stream_status()) {
                    goto common_deal;
                }
                uvc_video_stop();
                g_video_ctrl.camera_open = false;
            }
common_deal:
            tuya_hal_semaphore_post((SEM_HANDLE)sem);
            PR_NOTICE("uvc_video_satrt os_sem_post");
#endif // 0
        }
        break;

        case MSG_LCD_BL_ON_SYN: {
#if 0
            INT_T from_set;
            INT_T pic;
            VOID_T *sem;
            INT_T *p = (INT_T *)(msg_data->data);
            from_set = *p;
            p++;
            pic = *p;
            p++;
            sem = *p;

            PR_DEBUG("pic=%d ", pic);
//                #if 0
            if (UI_MSG_CONFIG_SET == pic) {
                tuya_video_lcd_display_status_set(false);
                if ((false == ty_get_stream_status()) && g_video_ctrl.camera_open) {
                    uvc_video_stop();
                    if (camera_power_off) {
                        tuya_video_power_ctrl(false);
                    }
                    g_video_ctrl.camera_open = false;
                }
                tuya_lcd_play_pic_syn(UI_MSG_CONFIG_SET_SYN);
            } else if (UI_MSG_LOGO == pic) {
                tuya_video_lcd_display_status_set(true);
                g_video_ctrl.show_page_open = true;
                PR_NOTICE("show_page_open=%d %d %d", g_video_ctrl.show_page_open, ty_get_stream_status(), g_video_ctrl.camera_open);
                if (false == ty_get_stream_status() && !g_video_ctrl.camera_open) {
                    if (dev_online("uvc")) {
                        tuya_lcd_play_pic_syn(UI_MSG_NULL_SYN);
                    } else {
                        tuya_lcd_play_pic_syn(UI_MSG_LOGO_SYN);
                    }
                }
            } else if (UI_MSG_NULL == pic) {
                tuya_video_lcd_display_status_set(true);
                g_video_ctrl.show_page_open = true;
                tuya_lcd_play_pic_syn(UI_MSG_NULL_SYN);
            } else {
                tuya_video_lcd_display_status_set(true);
                g_video_ctrl.show_page_open = true;
            }
            os_time_dly(5);    // 上面首页屏显异步 增加延时 防止前一次开屏画面残留。
            tuya_lcd_back_light_power_ctr(true);
            if (LCD_FROM_QRCODE != from_set && FALSE == tuya_wifi_is_in_net_cfg()) {
                tuya_lcd_off_ctrl_start();
                tuya_low_power_time_set_and_start(0);
            }

            tuya_hal_semaphore_post((SEM_HANDLE)sem);
            //PR_NOTICE("uvc_video_satrt os_sem_post");
#endif // 0
        }
        break;
        case MSG_LCD_BL_OFF_SYN: {
            PR_NOTICE("uvc_video_satrt os_sem_post");
        }
        break;

        default:
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


VOID_T ty_update_cb(INT_T satus, INT_T percent)
{
    INT_T ret = satus;
    OPERATE_RET op_ret = OPRT_OK;
    GW_WIFI_NW_STAT_E cur_nw_stat = 0;
    op_ret = get_wf_gw_nw_status(&cur_nw_stat);
    if (OPRT_OK == op_ret) {
        if ((cur_nw_stat == STAT_UNPROVISION) || (cur_nw_stat == STAT_AP_STA_UNCFG) || (cur_nw_stat == STAT_UNPROVISION_AP_STA_UNCFG)) {
            return;
        }
    }
    if (satus == UPDATA_READY) {
        if (wifi_is_on()) {
            wifi_off();
            while (wifi_is_on()) {
                vTaskDelay(50);
            }
        }

        tuya_video_stop_syn();
        tuya_video_power_ctrl(false);
    } else if (satus == UPDATA_SUCC || satus == UPDATA_DEV_ERR)  {
    } else if (satus == UPDATA_NON && (percent % 10 == 0))  {
    }
}



OPERATE_RET cameraPara_init(TY_CAMERA_PARAM *camera_param)
{
//    camera_power_off = camera_param->video_power_off;
//    PR_NOTICE("camera param:%d %d %d %d %d" ,camera_param->video_width,camera_param->video_height,camera_param->video_rotat_angle,camera_param->video_fps,camera_power_off);
    ty_set_camera_pic_w_h_r_f(camera_param->video_width, camera_param->video_height, camera_param->video_rotat_angle, camera_param->video_fps);
    return OPRT_OK;
}
extern INT_T button_init_value;
extern INT_T door_bell_init_value;
extern BOOL_T  door_bell_init_up;
VOID_T tuya_usb_power_init(VOID_T)
{
    UCHAR_T wk_up_pin = system_reset_wake_up_pin();

    if (ty_get_usb_spped()) {
        ty_set_usb_usb_mode(1);
    }
    BOOL_T usb_power_st = FALSE;
#if TY_USE_IMAGE_TIMER
    sys_add_timer(tuya_restart_camera_time_cb, NULL, &g_video_ctrl.restart_camera_id);
#endif
}
INT_T tuya_video_init(TY_CAMERA_PARAM *camera_param)
{
    TAL_PR_DEBUG("into tuya video init");
    STATIC UCHAR_T init = 0;
    OPERATE_RET op_ret;
    INT_T w, h;

    memset(g_video_ctrl.rec_start, 0, 4);
    memset(g_video_ctrl.camera_start, 0, 4);


    g_video_ctrl.lcd_width = camera_param->video_width;//640;
    g_video_ctrl.lcd_height = camera_param->video_height;//480;

    cameraPara_init(camera_param);
    PR_NOTICE("tuya_video_init get lcd %d %d\n", g_video_ctrl.lcd_width, g_video_ctrl.lcd_height);
    if (NULL == video_server[0] || NULL == video_server[1] || NULL == video_server[2] || NULL == video_server[3]) {

#ifdef CONFIG_VIDEO0_ENABLE
        video_server[0] = server_open("video_server", "video0.0");
        if (video_server[0]) {
            video_state = video_state + 2;
        }
        server_register_event_handler_to_task(video_server[0], (VOID_T *)0, rec_dev_server_event_handler, "app_core");
#endif

#ifdef CONFIG_VIDEO1_ENABLE
        video_server[1] = server_open("video_server", "video1.0");
        if (video_server[1]) {
            video_state = video_state + 3;
        }
        server_register_event_handler_to_task(video_server[1], (VOID_T *)1, rec_dev_server_event_handler, "app_core");
#endif

#ifdef CONFIG_VIDEO2_ENABLE
        video_server[2] = server_open("video_server", "video2.0");
        if (video_server[2]) {
            video_state = video_state + 4;
        }
        server_register_event_handler_to_task(video_server[2], (VOID_T *)2, rec_dev_server_event_handler, "app_core");
#endif
#ifdef CONFIG_VIDEO3_ENABLE
        video_server[3] = server_open("video_server", "video3.0");
        if (video_server[3]) {
            video_state = video_state + 8;
        }
        server_register_event_handler_to_task(video_server[3], (VOID_T *)3, rec_dev_server_event_handler, "app_core");
#endif

        //server_register_event_handler_to_task(video_server, (VOID_T *)0, rec_dev_server_event_handler,"app_core");
    }
    PR_DEBUG("video_state = %d", video_state);

    if (!init) {
        tuya_hal_semaphore_create_init(&g_video_ctrl.semphore, 0, 1);
        QS queue_size = (SIZEOF(TY_VIDEO_CTRL_MSG *) * 20 + sizeof(WORD) - 1) / sizeof(WORD);
        op_ret = os_q_create(&g_video_ctrl.msg_que, queue_size);

        if (op_ret != OPRT_OK) {
            PR_NOTICE("tal queue creat init error!");
        }
        /* #ifndef CONFIG_VIDEO2_ENABLE */
        /* uvc_video_start(640, 480, 10); */
        /* uvc_video_start(camera_param->video_width, camera_param->video_height, camera_param->video_fps); */
        /* ty_video_set_disp_window(); */

        video_convert(0);
        display_convert(0);

        /* tuya_video_display(1, &disp_window[DISP_MAIN_WIN][0]); */
        /* video_disp_win_switch(DISP_WIN_SW_SHOW_SMALL, 1); */
        /* video_disp_win_switch(k */
        /* #endif */
        /* THRD_PARAM_S thrd_param; */
        /* thrd_param.priority = TRD_PRIO_1; */
        /* thrd_param.stackDepth = 1024*4; */
        /* thrd_param.thrdname = TY_VIDEO_TASK_NAME; */
        /* CreateAndStart(&g_video_ctrl.task_handle,NULL,NULL,__video_task,NULL,&thrd_param);	 */

        stream_protocol_task_create();

#if 1
        /* wait_completion(storage_device_ready, ty_rec_switch, NULL, NULL);	 */

        /* video_convert(0); */
        /* while(!storage_device_ready()); */
        /* ty_rec_switch(); */
#endif

    }

    init = 1;
    return 0;
}


/*UVC插拔的事件总入口*/
static int video_event_handler(struct sys_event *e)
{
    struct device_event *event = (struct device_event *)e->payload;
    int err = 0;
    INT_T w, h, r, f;
    if (e->from == DEVICE_EVENT_FROM_SD) {
        switch (event->event) {
        case DEVICE_EVENT_IN:
            printf("sd card in");
            ty_rec_switch();
            break;
        case DEVICE_EVENT_OUT:
            printf("sd card out");
            for (int i = 0; i < 4; i++) {
                ty_rec_stop(i);
            }
            break;
        }
    }
#ifdef CONFIG_VIDEO2_ENABLE
    else if (e->from == DEVICE_EVENT_FROM_USB_HOST) {
        if (event->event == DEVICE_EVENT_IN) {
            if (!strncmp((const char *)event->value, "uvc", 3)) {
                PR_DEBUG("uvc_id:%d", uvc_host_online());
                display_convert(0);
                video_convert(1);
                if (rec_state) {
                    for (int i = 0; i < 4; i++) {
                        ty_rec_stop(i);
                    }
                    ty_rec_switch();
                }
                printf("\n[ debug ]--func=%s line=%d\n", __func__, __LINE__);
            }
        } else if (event->event == DEVICE_EVENT_OUT) {
            if (!strncmp((const char *)event->value, "uvc", 3)) {
                display_convert(0);
                if (rec_state) {
                    for (int i = 0; i < 4; i++) {
                        ty_rec_stop(i);
                    }
                    ty_rec_switch();
                }
                video_convert(0);
                printf("\n[ debug ]--func=%s line=%d\n", __func__, __LINE__);
            }

        }
    }
#endif

    return 0;
}

/*
 * 静态注册设备事件回调函数，优先级为0
 */
SYS_EVENT_STATIC_HANDLER_REGISTER(ty_device_event, 0) = {
    .event_type     = SYS_DEVICE_EVENT,
    .prob_handler   = video_event_handler,
    .post_handler   = NULL,
};

/*
 *按键响应函数
 */
static int video_key_event_handler(struct sys_event *e)
{
    int err;
    static int flag = 0;
    struct key_event *key = (struct key_event *)e->payload;
    /* #ifdef UVC_CMA_GRAY */
    /* VGA UVC黑白切换功能 */
    /* void *uvc_test; */
    /* static u32 flag = 0; */
    /* #endif */

    printf("key value:%d ", key->value);
    switch (key->action) {
    case KEY_EVENT_CLICK:
        switch (key->value) {
        case KEY_OK:
            PR_DEBUG("convert video0");
            /* flag = !flag; */
            video_convert(0);
            break;
        case KEY_MENU:
            break;
        case KEY_POWER:
            /* ty_rec_switch(); */
            /* display_convert(1); */
            break;
        case KEY_MODE:
            /* for (int i = 0; i < 4; i++) { */
            /* ty_rec_stop(i); */
            /* } */
            /* flag = !flag; */
            /* display_convert(0); */
            break;
        case KEY_UP:
            printf("key3 \n\n\n\n");
            ty_video_take_photo();
            break;
        case KEY_DOWN:
            PR_DEBUG("convert video2");
            video_convert(1);
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }

    return false;
}

SYS_EVENT_STATIC_HANDLER_REGISTER(ty_key_event, 0) = {
    .event_type     = SYS_KEY_EVENT,
    .prob_handler   = video_key_event_handler,
    .post_handler   = NULL,
};

/* #endif */
