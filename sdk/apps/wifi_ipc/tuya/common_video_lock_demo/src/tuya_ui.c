#include "app_config.h"
#include "system/includes.h"
#include "ui/ui.h"
#include "ui_api.h"
#include "font/language_list.h"
#include "event/key_event.h"
#include "lcd_te_driver.h"
#include "update.h"
#include "ename.h"
#include "time.h"

#include "tuya_ui.h"
#include "uni_time.h"
#include "uni_log.h"
#include "uni_msg_queue.h"
#include "tuya_button_app.h"
#include "tuya_video.h"
#include "sdk_version.h"
#include "sys_timer.h"
#include "uni_thread.h"
#include "tuya_driver.h"
#include "tuya_cloud_types.h"
#include "tuya_cloud_com_defs.h"
#include "tuya_iot_wifi_api.h"
#include "tuya_prod_test.h"
#include "tuya_fast_init.h"
#include "svc_weather_service.h"
/***************************************************************************************/
#ifdef CONFIG_UI_ENABLE

#define PAGE_LOGO              PAGE_0
#define PAGE_UPDATE            PAGE_1
#define PAGE_QR_REC            PAGE_2
#define PAGE_SYS_SET           PAGE_3
#define PAGE_SYS_PARAM_SET     PAGE_9
#define PAGE_FIRME_VERSION     PAGE_4
#define PAGE_GET_WIFI_CONFIG   PAGE_5
#define PAGE_ENTER_WIFI_CONFIG PAGE_6

#define PAGE_LCD_DISPLAY_TIME_CONFIG PAGE_10
#define PAGE_LANGUAGE_CONFIG         PAGE_8
#define PAGE_DATE_CONFIG             PAGE_7
#define PAGE_DEVICE_TEST             PAGE_11
#define TY_UI_TASK_NAME  "ty_ui"
#define TY_UI_WAIT_SEM_TIMEOUT  3000
enum {
    UI_PAGE_Y_0, //一级页面
    UI_PAGE_Y_1, //二级页面
    UI_PAGE_Y_2,
    UI_PAGE_Y_3,
};

enum {
    UI_PAGE_RT_CAMERA_INDEX_0,
    UI_PAGE_SYS_SET_INDEX_1,
    UI_PAGE_WIFI_INDEX_2,
    UI_PAGE_DEV_INFO_INDEX_3,
};

enum {
    UI_PAGE_SYS_CONFIG_INDEX_0_RT_CAMERA,
    UI_PAGE_SYS_CONFIG_INDEX_1_LCD_SET,
    UI_PAGE_SYS_CONFIG_INDEX_2_LANG,
    UI_PAGE_SYS_CONFIG_INDEX_3_TIME,
};

enum {
    UI_PAGE_LCD_CONFIG_INDEX_0,
    UI_PAGE_LCD_CONFIG_INDEX_1,
    UI_PAGE_LCD_CONFIG_INDEX_2,
};
enum {
    UI_PAGE_LANG_CONFIG_INDEX_0,
    UI_PAGE_LANG_CONFIG_INDEX_1,
};
enum {
    UI_PAGE_LCD_CONFIRM,
    UI_PAGE_LCD_CONCELL,
};

enum {
    UI_PAGE_TIME_0,
    UI_PAGE_TIME_1,
    UI_PAGE_TIME_2,
    UI_PAGE_TIME_3,
    UI_PAGE_TIME_4,
    UI_PAGE_TIME_5,
    UI_PAGE_TIME_6_CONFIRM,
    UI_PAGE_TIME_7_CONCELL,
};

typedef struct key_note_hdl { //按键记录按键光标位置信息
    UCHAR_T page_x; //记录光标位置
    UCHAR_T page_y; //记录页信息
    UCHAR_T page_wifi_x;//记录wifi二级界面光标信息
    UCHAR_T page2_x;//记录系统设置二级界面光标信息
    UCHAR_T page3_x;//记录系统设置三级界面光标信息
    UCHAR_T page3_y;//记录系统设置三级界确认信息
} KEY_NOTE_HDL;


STATIC CHAR_T ui_page = 0;
STATIC CHAR_T ui_last_page = 0;
STATIC KEY_NOTE_HDL note = {0};
STATIC struct utime g_time_r;
STATIC struct utime time_r;
STATIC TIMER_ID  lcd_timer = 0;
STATIC BOOL_T logo_diplay = FALSE;
STATIC CHAR_T file_log_buf[20 * 1024] = {0};
STATIC TY_LOGO *file_buf = file_log_buf;
STATIC INT_T languae = Chinese_Simplified;
STATIC THRD_HANDLE ui_handle = NULL;
STATIC MSG_QUE_HANDLE  ui_msg_que = NULL;
STATIC INT_T last_ui = -1;
STATIC INT_T update_wifi_rssi_ui_flag = 0;
STATIC TIMER_ID  ui_timer_id = 0;
STATIC UCHAR_T menu_first_click = 0;

OPERATE_RET tuya_send_ui_msg(IN CONST UINT_T msgid, IN CONST VOID *data, IN CONST UINT_T len)
{
    OPERATE_RET op_ret = OPRT_OK;
    INT_T msg_num = 0;
    if (!ui_msg_que) {
        return OPRT_MSG_OUT_OF_LMT;
    }
    op_ret = GetMsgNodeNum(ui_msg_que, &msg_num);
    if ((OPRT_OK == op_ret) && (msg_num >= 20)) {
        PR_ERR("msg_num is out of range");
        return OPRT_MSG_OUT_OF_LMT;
    }

    P_MSG_DATA msg_data;
    UINT_T cur_len = len;

    if (data && len) {
        msg_data = Malloc(len + 1);
        if (!msg_data) {
            return OPRT_MALLOC_FAILED;
        }
        memset(msg_data, 0, len + 1);
        memcpy(msg_data, data, len);
    } else {
        msg_data = NULL;
        cur_len = 0;
    }

    op_ret = PostMessage(ui_msg_que, msgid, msg_data, cur_len);
    if (OPRT_OK != op_ret) {
        return op_ret;
    }

    return OPRT_OK;
}

OPERATE_RET tuya_lcd_play_pic(INT_T pic_id, CHAR_T *data, INT_T data_len)
{
    PR_DEBUG("tuya_lcd_play_pic %d data_len %d", pic_id, data_len);

    return tuya_send_ui_msg(pic_id, data, data_len);
}

BOOL_T ty_lcd_in_ui_page(VOID_T)
{
    BOOL_T in_page = FALSE;
    if (UI_MSG_CONFIG_SET_SYN == ui_page || UI_MSG_CONFIG_SET == ui_page || UI_MSG_SYS_SET == ui_page || UI_MSG_DEV_INFO == ui_page ||  \
        UI_MSG_GET_SSID == ui_page || UI_MSG_WIFI_SET_MODE == ui_page || UI_MSG_LOCAL_IMAGE == ui_page || \
        UI_MSG_LCD_SET == ui_page || UI_MSG_LANG_SET == ui_page || UI_MSG_TIME_SET == ui_page || UI_MSG_WIFI_SET_MODE_TEST == ui_page || \
        UI_MSG_SOUND_TEST == ui_page || UI_MSG_CAMERA_TEST == ui_page || UI_MSG_END_TEST == ui_page) {

        in_page = TRUE;
    }
    return in_page;
}
BOOL_T tuya_logo_is_display(VOID_T)
{
    return logo_diplay;
}

BOOL_T tuya_logo_set_status(BOOL_T status)
{
    logo_diplay = status;
}
STATIC OPERATE_RET network_link_judge(VOID)
{
    GW_WIFI_NW_STAT_E cur_nw_stat;
    get_wf_gw_nw_status(&cur_nw_stat);
    if ((cur_nw_stat < STAT_STA_CONN) && (cur_nw_stat != STAT_AP_STA_CONN)\
        || (cur_nw_stat == STAT_UNPROVISION_AP_STA_UNCFG)) {
        //PR_NOTICE("wifi ble mode not config :%d",cur_nw_stat);
        return OPRT_NETWORK_ERROR;
    }
    return OPRT_OK;
}

VOID_T ui_timer_reset_display(VOID)
{
    last_ui = -1;
}




VOID_T tuya_get_week_day(CHAR_T *str, INT_T len, INT_T week_day)
{
    switch (week_day) {
    case 0:
        snprintf(str, len, "星期日");
        break;
    case 1:
        snprintf(str, len, "星期一");
        break;
    case 2:
        snprintf(str, len, "星期二");
        break;
    case 3:
        snprintf(str, len, "星期三");
        break;
    case 4:
        snprintf(str, len, "星期四");
        break;
    case 5:
        snprintf(str, len, "星期五");
        break;
    case 6:
        snprintf(str, len, "星期六");
        break;
    }
    return ;
}


STATIC INT_T rtc_dev_time_get(struct utime *time)
{
    struct sys_time ui_rtc_time;
    POSIX_TM_S gm_time = {0};
    INT_T timestamp;
    gm_time.tm_year = time->year - 1900;
    gm_time.tm_mon = time->month - 1;
    gm_time.tm_mday = time->day;
    gm_time.tm_hour = time->hour;
    gm_time.tm_min = time->min;
    gm_time.tm_sec = time->sec;

    timestamp = uni_mktime(&gm_time);
    //PR_NOTICE("rtc_dev_time_get timestamp=%d  %d-%d-%d %d:%d:%d",*timestamp,ui_rtc_time.year,ui_rtc_time.month,ui_rtc_time.day,ui_rtc_time.hour,ui_rtc_time.min,ui_rtc_time.sec);
    return timestamp;
}

STATIC VOID_T ui_timer_update(INT_T update_flash_flag)
{

    STATIC BOOL_T flash_flag = TRUE;
    OPERATE_RET op_ret;
    UCHAR_T str[20] = {0};
    POSIX_TM_S gm_time;
    if (OPRT_OK == uni_local_time_get(&gm_time)) {
        time_r.year = (USHORT_T) gm_time.tm_year + 1900 ;
        time_r.month = (CHAR_T)gm_time.tm_mon + 1;
        time_r.day = (CHAR_T)gm_time.tm_mday;
        time_r.hour = (CHAR_T)gm_time.tm_hour;
        time_r.min = (CHAR_T)gm_time.tm_min;
        time_r.sec = (CHAR_T)gm_time.tm_sec;
    } else {
        time_r.year = 2000 ;
        time_r.month = 1;
        time_r.day = 1;
        time_r.hour = 8;
        time_r.min = 0;
        time_r.sec = 0;
    }



    PR_DEBUG("get_sys_time: %d-%d-%d %d:%d:%d", time_r.year, time_r.month, time_r.day, time_r.hour, time_r.min, time_r.sec);
    if (UI_MSG_CAMERA != ui_page) {
        last_ui = -1;
    }
    switch (ui_page) {
    case UI_MSG_LOGO:
    case UI_MSG_LOGO_SYN:
#if  defined(TY_NEED_LOGO_TIME) && (TY_NEED_LOGO_TIME == 1)
        //tuya_get_week_day(str,sizeof(str),gm_time.tm_wday);
        ui_time_update_by_id(BASEFORM_2, &time_r);
        ui_time_update_by_id(BASEFORM_3, &time_r);
        if (update_flash_flag) {
            if (flash_flag) {
                flash_flag = false;
                ui_pic_show_image_by_id(BASEFORM_73, 0);
            } else {
                flash_flag = TRUE;
                ui_pic_show_image_by_id(BASEFORM_73, 1);
            }
        }
#endif
        CHAR_T *head_ffd8 = NULL;
        CHAR_T *tail_ffd9 = NULL;
        if (logo_diplay) {
            if (file_buf->logo_flag && file_buf->logo_len < 20 * 1024 && my_mem_find_str(file_buf->logo_data, file_buf->logo_len, &head_ffd8, &tail_ffd9)) {
                tuya_video_lcd_display_status_set(TRUE);
                jpeg2yuv_jpeg_frame_write(file_buf->logo_data, (UINT_T)file_buf->logo_len);
            }
        }


        break;
    case UI_MSG_CONFIG_SET:
    case UI_MSG_CONFIG_SET_SYN:
        //tuya_get_week_day(str,sizeof(str),gm_time.tm_wday);
        ui_show_main(BASEFORM_19);
        ui_time_update_by_id(BASEFORM_19, &time_r);
        ui_time_update_by_id(BASEFORM_21, &time_r);
        //ui_text_show_index_by_id(BASEFORM_20,gm_time.tm_wday);
        if (update_flash_flag) {
            if (flash_flag) {
                flash_flag = false;
                ui_pic_show_image_by_id(BASEFORM_74, 0);
            } else {
                flash_flag = TRUE;
                ui_pic_show_image_by_id(BASEFORM_74, 1);
            }
        }
        break;
    case UI_MSG_CAMERA:
    case UI_MSG_CAMERA_SYN:
        if (tuya_wifi_is_in_net_cfg()) {
            break;
        }
        ui_time_update_by_id(BASEFORM_9, &time_r);
        ui_time_update_by_id(BASEFORM_23, &time_r);
        if (update_flash_flag) {
            if (flash_flag) {
                flash_flag = false;
                ui_pic_show_image_by_id(BASEFORM_22, 0);
            } else {
                flash_flag = TRUE;
                ui_pic_show_image_by_id(BASEFORM_22, 1);
            }
        }
        break;

    }

}




STATIC VOID_T ui_fs_update_percent(INT_T ret)
{
    switch (ret) {
    case UPDATA_NON:
        struct unumber timer;
        timer.type = TYPE_NUM;
        timer.numbs = 2;
        timer.number[0] = get_fs_update_percent();
        // 显示升级进度条
        INT_T w = 0;
        INT_T h = 0;
        lcd_get_width_height(&w, &h);
        if (240 == w && 320 == h) {
            ui_pic_show_image_by_id(BASEFORM_25, timer.number[0] / 20);
        } else {
            ui_pic_show_image_by_id(BASEFORM_38, timer.number[0] / 20);
        }
        ui_number_update_by_id(BASEFORM_154, &timer);
    case UPDATA_READY:
        ui_text_show_index_by_id(BASEFORM_12, 0);
        break;
    case UPDATA_SUCC:
        ui_text_show_index_by_id(BASEFORM_12, 1);
        break;
    case UPDATA_DEV_ERR:
        ui_text_show_index_by_id(BASEFORM_12, 2);
        break;

    }

}

/**
 * Returns 1 if current year id a leap year
 */
STATIC INT_T __is_leap(u16 yr)
{
    if (!(yr % 100)) {
        return (yr % 400 == 0) ? 1 : 0;
    } else {
        return (yr % 4 == 0) ? 1 : 0;
    }
}

STATIC u8 ty_get_valid_date_time(struct utime *date)
{
    u8  day = 0;
    if ((date->month >= 12) || (date->month == 0)) {
        PR_ERR("date month err!");
        return 0;
    }
    switch (date->month) {
    case 4:
    case 6:
    case 9:
    case 11:
        day = 30;
        break;
    case 2:
        if (!__is_leap(date->year)) {
            day = 28;
        } else {
            day = 29;
        }
        break;
    default:
        day = 31;
        break;
    }
    return day;
}


STATIC VOID_T time_set_page(CHAR_T day, CHAR_T dir) //0加时间 1减时间 day时间选择
{
    struct unumber timer;

    timer.type = TYPE_NUM;
    timer.numbs = 2;

    if (dir) { //加时间
        switch (day) {
        case 0://年
            g_time_r.year++;
            timer.number[0] = g_time_r.year;
            ui_number_update_by_id(BASEFORM_132, &timer);
            break;

        case 1://月
            g_time_r.month++;

            if (g_time_r.month == 13) {
                g_time_r.month = 1;
            }

            timer.number[0] = g_time_r.month;
            ui_number_update_by_id(BASEFORM_133, &timer);
            break;

        case 2://日
            g_time_r.day++;

            if (g_time_r.day == (ty_get_valid_date_time(&g_time_r) + 1)) {
                g_time_r.day = 1;
            }

            timer.number[0] = g_time_r.day;
            ui_number_update_by_id(BASEFORM_134, &timer);
            break;

        case 3://时
            g_time_r.hour++;

            if (g_time_r.hour == 24) {
                g_time_r.hour = 0;
            }

            timer.number[0] = g_time_r.hour;
            ui_number_update_by_id(BASEFORM_135, &timer);
            break;

        case 4://分
            g_time_r.min++;

            if (g_time_r.min == 60) {
                g_time_r.min = 0;
            }

            timer.number[0] = g_time_r.min;
            ui_number_update_by_id(BASEFORM_136, &timer);
            break;

        case 5://退出
            g_time_r.sec++;

            if (g_time_r.sec == 60) {
                g_time_r.sec = 0;
            }

            timer.number[0] = g_time_r.sec;
            ui_number_update_by_id(BASEFORM_137, &timer);
            break;
        }
    } else { //减时间
        switch (day) {
        case 0://年
            g_time_r.year--;

            if (g_time_r.year == 0) {
                g_time_r.year = 2022;
            }

            timer.number[0] = g_time_r.year;
            ui_number_update_by_id(BASEFORM_132, &timer);
            break;

        case 1://月
            g_time_r.month--;

            if (g_time_r.month == 0) {
                g_time_r.month = 12;
            }

            timer.number[0] = g_time_r.month;
            ui_number_update_by_id(BASEFORM_133, &timer);
            break;

        case 2://日
            g_time_r.day--;

            if (g_time_r.day == 0) {
                g_time_r.day = ty_get_valid_date_time(&g_time_r);
            }

            timer.number[0] = g_time_r.day;
            ui_number_update_by_id(BASEFORM_134, &timer);
            break;

        case 3://时
            g_time_r.hour--;

            if (g_time_r.hour == 255) {
                g_time_r.hour = 23;
            }

            timer.number[0] = g_time_r.hour;
            ui_number_update_by_id(BASEFORM_135, &timer);
            break;

        case 4://分
            g_time_r.min--;

            if (g_time_r.min == 255) {
                g_time_r.min = 59;
            }

            timer.number[0] = g_time_r.min;
            ui_number_update_by_id(BASEFORM_136, &timer);
            break;

        case 5://退出
            g_time_r.sec--;

            if (g_time_r.sec == 255) {
                g_time_r.sec = 59;
            }

            timer.number[0] = g_time_r.sec;
            ui_number_update_by_id(BASEFORM_137, &timer);
            break;
        }
    }
}
VOID_T time_updata(VOID_T)
{
    struct unumber timer;

    timer.type = TYPE_NUM;
    timer.numbs = 2;
    timer.number[0] = g_time_r.year;

    ui_show_main(BASEFORM_132);
    ui_number_update_by_id(BASEFORM_132, &timer);

    timer.number[0] = g_time_r.month;
    ui_number_update_by_id(BASEFORM_133, &timer);

    timer.number[0] = g_time_r.day;
    ui_number_update_by_id(BASEFORM_134, &timer);

    timer.number[0] = g_time_r.hour;
    ui_number_update_by_id(BASEFORM_135, &timer);

    timer.number[0] = g_time_r.min;
    ui_number_update_by_id(BASEFORM_136, &timer);

    timer.number[0] = g_time_r.sec;
    //timer.number[0] = 00;
    ui_number_update_by_id(BASEFORM_137, &timer);
}


VOID_T ui_page1x_index_update(VOID_T)
{
    INT_T w = 0;
    INT_T h = 0;
    lcd_get_width_height(&w, &h);
    if (240 == w && 320 == h) {
        ui_text_show_index_by_id(BASEFORM_58, 1);
        ui_text_show_index_by_id(BASEFORM_60, 1);
        ui_text_show_index_by_id(BASEFORM_61, 1);
        ui_text_show_index_by_id(BASEFORM_62, 1);
    }
    switch (note.page_x) {
    case UI_PAGE_RT_CAMERA_INDEX_0:
        ui_no_highlight_element_by_id(BASEFORM_54);
        ui_no_highlight_element_by_id(BASEFORM_56);
        ui_no_highlight_element_by_id(BASEFORM_35);
        ui_highlight_element_by_id(BASEFORM_53);
        break;
    case UI_PAGE_SYS_SET_INDEX_1:
        ui_no_highlight_element_by_id(BASEFORM_56);
        ui_no_highlight_element_by_id(BASEFORM_35);
        ui_no_highlight_element_by_id(BASEFORM_53);
        ui_highlight_element_by_id(BASEFORM_54);
        break;

    case UI_PAGE_WIFI_INDEX_2:
        ui_no_highlight_element_by_id(BASEFORM_35);
        ui_no_highlight_element_by_id(BASEFORM_53);
        ui_no_highlight_element_by_id(BASEFORM_54);
        ui_highlight_element_by_id(BASEFORM_56);
        break;

    case UI_PAGE_DEV_INFO_INDEX_3:
        ui_no_highlight_element_by_id(BASEFORM_53);
        ui_no_highlight_element_by_id(BASEFORM_54);
        ui_no_highlight_element_by_id(BASEFORM_56);
        ui_highlight_element_by_id(BASEFORM_35);
        break;
    }
}

VOID_T ui_page2x_index_update(VOID_T)
{
    switch (note.page_x) {
    case UI_PAGE_SYS_SET_INDEX_1:
        switch (note.page2_x) {
        case UI_PAGE_SYS_CONFIG_INDEX_0_RT_CAMERA:
            ui_no_highlight_element_by_id(BASEFORM_80);
            ui_no_highlight_element_by_id(BASEFORM_83);
            ui_highlight_element_by_id(BASEFORM_79);
            break;
        case UI_PAGE_SYS_CONFIG_INDEX_1_LCD_SET:
            ui_no_highlight_element_by_id(BASEFORM_79);
            ui_no_highlight_element_by_id(BASEFORM_82);
            ui_highlight_element_by_id(BASEFORM_80);
            break;

        case UI_PAGE_SYS_CONFIG_INDEX_2_LANG:
            ui_no_highlight_element_by_id(BASEFORM_80);
            ui_no_highlight_element_by_id(BASEFORM_83);
            ui_highlight_element_by_id(BASEFORM_82);
            break;

        case UI_PAGE_SYS_CONFIG_INDEX_3_TIME:
            ui_no_highlight_element_by_id(BASEFORM_82);
            ui_no_highlight_element_by_id(BASEFORM_79);
            ui_highlight_element_by_id(BASEFORM_83);
            break;


        }
        break;

    }
}

VOID_T ui_page3x_index_update(BOOL_T flag)
{
    switch (note.page_x) {
    case UI_PAGE_SYS_SET_INDEX_1:
        switch (note.page2_x) {
        case UI_PAGE_SYS_CONFIG_INDEX_1_LCD_SET:

            switch (note.page3_x) {
            case UI_PAGE_LCD_CONFIG_INDEX_0:
                ui_no_highlight_element_by_id(BASEFORM_112);
                ui_no_highlight_element_by_id(BASEFORM_113);
                ui_highlight_element_by_id(BASEFORM_111);
                break;

            case UI_PAGE_LCD_CONFIG_INDEX_1:
                ui_no_highlight_element_by_id(BASEFORM_111);
                ui_no_highlight_element_by_id(BASEFORM_113);
                ui_highlight_element_by_id(BASEFORM_112);
                break;

            case UI_PAGE_LCD_CONFIG_INDEX_2:
                ui_no_highlight_element_by_id(BASEFORM_111);
                ui_no_highlight_element_by_id(BASEFORM_112);
                ui_highlight_element_by_id(BASEFORM_113);
                break;
            }
            break;
        case UI_PAGE_SYS_CONFIG_INDEX_2_LANG:
            switch (note.page3_x) {
            case UI_PAGE_LANG_CONFIG_INDEX_0:
                ui_no_highlight_element_by_id(BASEFORM_26);
                ui_highlight_element_by_id(BASEFORM_121);
                break;
            case UI_PAGE_LANG_CONFIG_INDEX_1:
                ui_no_highlight_element_by_id(BASEFORM_121);
                ui_highlight_element_by_id(BASEFORM_26);
                break;
            }
            break;

        case UI_PAGE_SYS_CONFIG_INDEX_3_TIME:
            switch (note.page3_x) {
            case UI_PAGE_TIME_0:
                ui_no_highlight_element_by_id(BASEFORM_102);
                ui_no_highlight_element_by_id(BASEFORM_108);
                if (flag) {
                    ui_highlight_element_by_id(BASEFORM_106);
                } else {
                    ui_no_highlight_element_by_id(BASEFORM_106);
                }
                break;

            case UI_PAGE_TIME_1:
                ui_no_highlight_element_by_id(BASEFORM_106);
                ui_no_highlight_element_by_id(BASEFORM_123);

                if (flag) {
                    ui_highlight_element_by_id(BASEFORM_108);
                } else {
                    ui_no_highlight_element_by_id(BASEFORM_108);
                }
                break;

            case UI_PAGE_TIME_2:
                ui_no_highlight_element_by_id(BASEFORM_108);
                ui_no_highlight_element_by_id(BASEFORM_124);
                if (flag) {
                    ui_highlight_element_by_id(BASEFORM_123);
                } else {
                    ui_no_highlight_element_by_id(BASEFORM_123);
                }
                break;

            case UI_PAGE_TIME_3:
                ui_no_highlight_element_by_id(BASEFORM_123);
                ui_no_highlight_element_by_id(BASEFORM_125);
                if (flag) {
                    ui_highlight_element_by_id(BASEFORM_124);
                } else {
                    ui_no_highlight_element_by_id(BASEFORM_124);
                }
                break;
            case UI_PAGE_TIME_4:
                ui_no_highlight_element_by_id(BASEFORM_124);
                ui_no_highlight_element_by_id(BASEFORM_126);
                if (flag) {
                    ui_highlight_element_by_id(BASEFORM_125);
                } else {
                    ui_no_highlight_element_by_id(BASEFORM_125);
                }
                break;
            case UI_PAGE_TIME_5:
                ui_no_highlight_element_by_id(BASEFORM_125);
                ui_no_highlight_element_by_id(BASEFORM_88);
                if (flag) {
                    ui_highlight_element_by_id(BASEFORM_126);
                } else {
                    ui_no_highlight_element_by_id(BASEFORM_126);
                }
                break;

            case UI_PAGE_TIME_6_CONFIRM:
                ui_no_highlight_element_by_id(BASEFORM_126);
                ui_no_highlight_element_by_id(BASEFORM_102);
                ui_highlight_element_by_id(BASEFORM_88);
                break;

            case UI_PAGE_TIME_7_CONCELL:
                ui_no_highlight_element_by_id(BASEFORM_88);
                ui_no_highlight_element_by_id(BASEFORM_106);
                ui_highlight_element_by_id(BASEFORM_102);
                break;
            }
            break;
        }
        break;
    }
}

STATIC VOID ty_weather_service_wk_cb(VOID *data)
{
    CHAR_T *p_parm = "[\"w.temp\",\"w.pm25\",\"w.humidity\",\"w.condition\",\"w.conditionNum\"]";
    CHAR_T *pp_out = NULL;
    UINT_T p_nex_time_min = 0;

    ty_cJSON *root = NULL;
    ty_cJSON *cjson = NULL;
    int ret_status = tuya_svc_weather_get_data_https_synchronization(p_parm, &pp_out, &p_nex_time_min);
    if (ret_status == OPRT_OK) {
        PR_NOTICE("weather data:%d,%d,%s", ret_status, p_nex_time_min, pp_out);
        root = ty_cJSON_Parse(pp_out);
        if (NULL == root) {
            PR_ERR(" parse err");
            return;
        }
        CHAR_T *ui_page = (CHAR_T *)data;
        if ((*ui_page != UI_MSG_CONFIG_SET) && (*ui_page != UI_MSG_CONFIG_SET_SYN)) {
            return;
        }
        cjson = ty_cJSON_GetObjectItem(root, "w.temp");
        if (cjson) {
            UCHAR_T temp_str[6] = {0};
            snprintf(temp_str, sizeof(temp_str), "%d", cjson->valueint);
            ui_show_main(BASEFORM_10);
            if (Chinese_Simplified == languae) {
                ui_text_set_textu_by_id(BASEFORM_10, temp_str, strlen(temp_str), FONT_DEFAULT);
            } else if (English == languae) {
                ui_text_set_text_by_id(BASEFORM_10, temp_str, strlen(temp_str), FONT_DEFAULT);
            } else {
                ui_text_set_text_by_id(BASEFORM_10, temp_str, strlen(temp_str), FONT_DEFAULT);
            }

            ui_pic_show_image_by_id(BASEFORM_76, 0);
        }
        /*
        cjson = ty_cJSON_GetObjectItem(root, "w.pm25");
        if (cjson) {
            UCHAR_T pm25_str[15] ={0};
           // snprintf(temp_str,sizeof(temp_str),"%d",cjson->valueint);
           snprintf(pm25_str,sizeof(pm25_str),"%d",cjson->valueint);
           snprintf(pm25_str,sizeof(pm25_str),"%s","μg/m³");
            ui_show_main(BASEFORM_39);
            if (Chinese_Simplified == languae) {
                ui_text_set_textu_by_id(BASEFORM_39, pm25_str, strlen(pm25_str), FONT_DEFAULT);
            } else if (English == languae) {
                ui_text_set_text_by_id(BASEFORM_39, pm25_str, strlen(pm25_str), FONT_DEFAULT);
            } else {
                ui_text_set_text_by_id(BASEFORM_39, pm25_str, strlen(pm25_str), FONT_DEFAULT);
            }

        }
        */
        cjson = ty_cJSON_GetObjectItem(root, "w.conditionNum");
        if (cjson) {
            switch (atoi(cjson->valuestring)) {
            case 120:
            case 119: // 晴
            case 146:
                ui_pic_show_image_by_id(BASEFORM_75, 0);
                ui_text_show_index_by_id(BASEFORM_16, 0);
                break;
            case 129: // 少云
            case 142: //多云
                ui_pic_show_image_by_id(BASEFORM_75, 1);
                ui_text_show_index_by_id(BASEFORM_16, 1);
                break;
            case 132: // 阴
                ui_pic_show_image_by_id(BASEFORM_75, 2);
                ui_text_show_index_by_id(BASEFORM_16, 2);
                break;
            case 104:
            case 105: // 雪
            case 124:
            case 126:
            case 128:
            case 130:
            case 131:
            case 138:
                ui_pic_show_image_by_id(BASEFORM_75, 4);
                ui_text_show_index_by_id(BASEFORM_16, 4);
                break;
            case 140: // 霾
                ui_pic_show_image_by_id(BASEFORM_75, 5);
                ui_text_show_index_by_id(BASEFORM_16, 5);
                break;
            case 115: // 冰雹
            case 127:
            case 133:
                ui_pic_show_image_by_id(BASEFORM_75, 6);
                ui_text_show_index_by_id(BASEFORM_16, 6);
                break;
            case 103: // 扬尘
            case 109:
            case 114:
            case 116:
            case 117:
                ui_pic_show_image_by_id(BASEFORM_75, 7);
                ui_text_show_index_by_id(BASEFORM_16, 7);
                break;
            default:
                ui_pic_show_image_by_id(BASEFORM_75, 3);
                ui_text_show_index_by_id(BASEFORM_16, 3);
                break;
            }
        }
    }
    free(pp_out);
}


STATIC VOID ty_ui(PVOID_T pArg)
{
    OPERATE_RET op_ret = OPRT_OK;
    INT_T update_flash = 0;
    P_MSG_LIST msgListNode;

    set_lcd_show_data_mode(ui_camera);
    ui_show_main(PAGE_LOGO);
    if (languae != ui_language_get()) {
        PR_NOTICE("now %d ui_language_set %d", ui_language_get(), languae);
        ui_language_set(languae);
    }
    ui_data_clear();
    while (1) {

        op_ret = WaitMessage(ui_msg_que, &msgListNode);
        if (op_ret != OPRT_OK) {
            if (op_ret != OPRT_MSG_LIST_EMPTY) {
                PR_ERR("WaitMessage op_ret:%d", op_ret);
            }
            continue;
        }

        INT_T flag = 0;
        INT_T *p = (INT_T *)(msgListNode->msg.pMsgData);
        if (p) {
            flag = p[0];
        }
        //PR_NOTICE("ui  cmd %d flag %d",msgListNode->msg.msgID,flag);

        switch (msgListNode->msg.msgID) {
        case UI_MSG_NULL:
        case UI_MSG_NULL_SYN:
            ui_page = msgListNode->msg.msgID;
            set_lcd_show_data_mode(ui);
            ui_send_clear();
            if (msgListNode->msg.msgID == UI_MSG_NULL_SYN) {
                tuya_hal_semaphore_post((SEM_HANDLE)flag);
                PR_NOTICE("UI_MSG_NULL semaphore_post");
            }
            break;
        case UI_MSG_LOGO:
        case UI_MSG_LOGO_SYN:
            ui_page = msgListNode->msg.msgID;
            ui_data_clear();
            if (LOGO_USE_USER != file_buf->logo_flag) {
                set_lcd_show_data_mode(ui);
                logo_diplay = false;
                ui_show_main(PAGE_LOGO);
                ui_show_main(BASEFORM_99);
                ui_text_show_index_by_id(BASEFORM_15, 0);
#if  defined(TY_NEED_LOGO_TIME) && (TY_NEED_LOGO_TIME == 1)
                ui_show_main(BASEFORM_2);
                ui_show_main(BASEFORM_3);
                ui_show_main(BASEFORM_73);
#endif
                ui_timer_update(update_flash);
            } else {
                set_lcd_show_data_mode(ui_camera);
                logo_diplay = TRUE;
                ui_show_main(PAGE_LOGO);
#if  defined(TY_NEED_LOGO_TIME) && (TY_NEED_LOGO_TIME == 1)
                ui_show_main(BASEFORM_2);
                ui_show_main(BASEFORM_3);
                ui_show_main(BASEFORM_73);
#endif
                CHAR_T *head_ffd8 = NULL;
                CHAR_T *tail_ffd9 = NULL;

                if (file_buf->logo_flag && file_buf->logo_len < 20 * 1024 && my_mem_find_str(file_buf->logo_data, file_buf->logo_len, &head_ffd8, &tail_ffd9)) {
                    tuya_video_lcd_display_status_set(TRUE);
                    ui_timer_update(update_flash);
                    os_time_dly(10);
                    PR_NOTICE("jpeg2yuv_jpeg_frame_write");
                } else {
                    logo_diplay = false;
                    set_lcd_show_data_mode(ui);
                    ui_show_main(PAGE_LOGO);
                    ui_show_main(BASEFORM_99);
                    ui_text_show_index_by_id(BASEFORM_15, 0);
#if  defined(TY_NEED_LOGO_TIME) && (TY_NEED_LOGO_TIME == 1)
                    ui_show_main(BASEFORM_2);
                    ui_show_main(BASEFORM_3);
                    ui_show_main(BASEFORM_73);
#endif
                    ui_timer_update(update_flash);
                    PR_NOTICE("no jpeg2yuv_jpeg_frame_write");
                }
            }
            sys_start_timer(ui_timer_id, 1000, TIMER_ONCE);
            if (msgListNode->msg.msgID == UI_MSG_LOGO_SYN) {
                tuya_hal_semaphore_post((SEM_HANDLE)flag);
                PR_NOTICE("UI_MSG_LOGO_SYN semaphore_post");
            }
            break;
        case UI_MSG_UPDATE:
            set_lcd_show_data_mode(ui);

            ui_page = msgListNode->msg.msgID;
            ui_show_main(PAGE_UPDATE);
            ui_show_main(BASEFORM_154);
            ui_show_main(BASEFORM_30);
            // 显示升级进度条
            INT_T w = 0;
            INT_T h = 0;
            lcd_get_width_height(&w, &h);
            if (240 == w && 320 == h) {
                ui_show_main(BASEFORM_25);
                ui_show_main(BASEFORM_27);
                ui_hide_main(BASEFORM_33);
                ui_hide_main(BASEFORM_38);
            } else {
                ui_hide_main(BASEFORM_25);
                ui_hide_main(BASEFORM_27);
                ui_show_main(BASEFORM_33);
                ui_show_main(BASEFORM_38);
            }
            break;
        case UI_MSG_UPDATE_ONLY:
            set_lcd_show_data_mode(ui);

            ui_page = msgListNode->msg.msgID;
            ui_show_main(PAGE_UPDATE);

            if (3 == flag) {
                ui_text_show_index_by_id(BASEFORM_12, 2);
            } else if (2 == flag) {
                ui_text_show_index_by_id(BASEFORM_12, 1);
            } else if (1 == flag) {
                ui_text_show_index_by_id(BASEFORM_12, 0);
            } else if (4 == flag) {
                ui_text_show_index_by_id(BASEFORM_12, 3);
            } else if (5 == flag) {
                ui_text_show_index_by_id(BASEFORM_12, 4);
            } else if (6 == flag) {
                ui_text_show_index_by_id(BASEFORM_12, 5);
            } else if (7 == flag) {
                ui_text_show_index_by_id(BASEFORM_12, 6);
            }
            ui_hide_main(BASEFORM_154);
            ui_hide_main(BASEFORM_30);
            ui_hide_main(BASEFORM_25);
            ui_hide_main(BASEFORM_27);
            ui_hide_main(BASEFORM_33);
            ui_hide_main(BASEFORM_38);
            break;
        case UI_MSG_CAMERA:
        case UI_MSG_CAMERA_SYN:
            logo_diplay = FALSE;
            ui_data_clear();
            set_lcd_show_data_mode(ui_camera);
            ui_page = msgListNode->msg.msgID;
            if (ui_page != ui_last_page) {
                ui_show_main(PAGE_QR_REC);
            }

            if (msgListNode->msg.msgID != UI_MSG_CAMERA_SYN) {
                if (flag) {
                    ui_text_show_index_by_id(BASEFORM_140, 0);
                } else {
                    ui_show_main(BASEFORM_9);
                    ui_show_main(BASEFORM_23);
                    ui_show_main(BASEFORM_22);
                    ui_timer_update(update_flash);
                }
            } else {
                ui_show_main(BASEFORM_9);
                ui_show_main(BASEFORM_23);
                ui_show_main(BASEFORM_22);
                ui_timer_update(update_flash);
            }


            static INT_T now_ui = 0;
            SCHAR_T wifi_rssi = 0;
            if (network_link_judge() == OPRT_OK) {
                op_ret = wf_station_get_conn_ap_rssi(&wifi_rssi);
                if (OPRT_OK != op_ret) {
                    PR_DEBUG("not get rssi!");
                    now_ui = 3;
                } else {
                    PR_DEBUG("get rssi %d!", wifi_rssi);
                    if (wifi_rssi >= -40) {
                        now_ui = 3;
                    } else if (wifi_rssi < -40 &&  wifi_rssi >= -50) {
                        now_ui = 2;
                    } else if (wifi_rssi < -50) {
                        now_ui = 1;
                    }
                }
            } else {
                now_ui = 0;
            }

            ui_pic_show_image_by_id(BASEFORM_11, now_ui);
            last_ui = now_ui;
            sys_start_timer(ui_timer_id, 1000, TIMER_ONCE);
            if (msgListNode->msg.msgID == UI_MSG_CAMERA_SYN) {
                tuya_hal_semaphore_post((SEM_HANDLE)flag);
                PR_NOTICE("UI_MSG_CAMERA_SYN semaphore_post");
            }

            break;
        case UI_MSG_CONFIG_SET:
        case UI_MSG_CONFIG_SET_SYN:
            set_lcd_show_data_mode(ui);
            ui_page = msgListNode->msg.msgID;
            ui_show_main(PAGE_SYS_SET);
            ui_show_main(BASEFORM_62);
            ui_no_highlight_element_by_id(BASEFORM_53);
            ui_page1x_index_update();
            ui_timer_update(update_flash);
            sys_start_timer(ui_timer_id, 1000, TIMER_ONCE);
            if (msgListNode->msg.msgID == UI_MSG_CONFIG_SET_SYN) {
                tuya_hal_semaphore_post((SEM_HANDLE)flag);
                PR_NOTICE("UI_MSG_CONFIG_SET_SYN semaphore_post");
            }
            ty_work_queue_add(ty_weather_service_wk_cb, &ui_page);

            break;
        case UI_MSG_LCD_SET:
            set_lcd_show_data_mode(ui);
            ui_page = msgListNode->msg.msgID;
            if (flag) {
                ui_show_main(PAGE_LCD_DISPLAY_TIME_CONFIG);
                note.page3_x = tuya_lcd_timer_get() / 1000 / 10 - 1;
                PR_NOTICE("note.page3_x=%d tuya_lcd_timer_get=%d", note.page3_x, tuya_lcd_timer_get());
                ui_page3x_index_update(TRUE);
            } else {
                ui_hide_main(PAGE_LCD_DISPLAY_TIME_CONFIG);
                tuya_lcd_play_pic(UI_MSG_SYS_SET, NULL, 0);
            }

            break;
        case UI_MSG_LANG_SET:
            set_lcd_show_data_mode(ui);
            ui_page = msgListNode->msg.msgID;
            if (flag) {
                ui_show_main(PAGE_LANGUAGE_CONFIG);
                ui_page3x_index_update(TRUE);
            } else {
                ui_hide_main(PAGE_LANGUAGE_CONFIG);
                tuya_lcd_play_pic(UI_MSG_SYS_SET, NULL, 0);
            }
            break;
        case UI_MSG_TIME_SET:
            set_lcd_show_data_mode(ui);
            ui_page = msgListNode->msg.msgID;
            if (flag) {
                ui_timer_update(false);
                memcpy(&g_time_r, &time_r, sizeof(struct utime));
                ui_show_main(PAGE_DATE_CONFIG);
                time_updata();
                ui_page3x_index_update(TRUE);

            } else {
                ui_hide_main(PAGE_DATE_CONFIG);
                tuya_lcd_play_pic(UI_MSG_SYS_SET, NULL, 0);
            }
            break;

        case UI_MSG_SYS_SET:
            set_lcd_show_data_mode(ui);
            ui_page = msgListNode->msg.msgID;
            ui_show_main(PAGE_SYS_PARAM_SET);
            ui_no_highlight_element_by_id(BASEFORM_79);
            ui_page2x_index_update();
            break;

        case UI_MSG_GET_SSID:
            set_lcd_show_data_mode(ui);
            if (1 == flag) {
                ui_hide_main(PAGE_GET_WIFI_CONFIG);
                ui_page = UI_MSG_NULL;
            } else if (0 == flag) {
                ui_page = msgListNode->msg.msgID;
                ui_show_main(PAGE_GET_WIFI_CONFIG);
                ui_pic_show_image_by_id(BASEFORM_165, 0);
                ui_text_show_index_by_id(BASEFORM_43, 0);
            } else if (2 == flag) {
                ui_page = msgListNode->msg.msgID;
                ui_show_main(PAGE_GET_WIFI_CONFIG);
                ui_pic_show_image_by_id(BASEFORM_165, 1);
                ui_text_show_index_by_id(BASEFORM_43, 1);
            }
            break;

        case UI_MSG_DEV_INFO:
            set_lcd_show_data_mode(ui);
            ui_page = msgListNode->msg.msgID;
            ui_show_main(PAGE_FIRME_VERSION);
            UCHAR_T str[20] = {0};
            snprintf(str, sizeof(str), "%s", USER_SW_VER);
            if (Chinese_Simplified == languae) {
                ui_text_set_textu_by_id(BASEFORM_81, str, strlen(str), FONT_DEFAULT);
            } else if (English == languae) {
                ui_text_set_text_by_id(BASEFORM_81, str, strlen(str), FONT_DEFAULT);
            } else {
                ui_text_set_text_by_id(BASEFORM_81, str, strlen(str), FONT_DEFAULT);
            }

            //ui_text_set_text_by_id(BASEFORM_81, str, strlen(str), FONT_DEFAULT);
            snprintf(str, sizeof(str), "%s", tuya_get_mcu_version());

            if (Chinese_Simplified == languae) {
                ui_text_set_textu_by_id(BASEFORM_143, str, strlen(str), FONT_DEFAULT);
            } else if (English == languae) {
                ui_text_set_text_by_id(BASEFORM_143, str, strlen(str), FONT_DEFAULT);
            } else {
                ui_text_set_text_by_id(BASEFORM_143, str, strlen(str), FONT_DEFAULT);
            }
            break;


        case  UI_MSG_WIFI_SET_MODE:
            set_lcd_show_data_mode(ui);
            ui_page = msgListNode->msg.msgID;
            ui_show_main(PAGE_ENTER_WIFI_CONFIG);
            UCHAR_T wifi_str[10] = {0};
            SCHAR_T rssi = 0;
            op_ret = wf_station_get_conn_ap_rssi(&rssi);
            if (OPRT_OK != op_ret) {
                PR_NOTICE("not get rssi!");
                rssi = 0;
            } else {
                PR_NOTICE("get rssi %d!", rssi);
            }
            snprintf(wifi_str, sizeof(wifi_str), "%d", rssi);
            if (Chinese_Simplified == languae) {
                ui_text_set_textu_by_id(BASEFORM_148, wifi_str, strlen(wifi_str), FONT_DEFAULT);
            } else if (English == languae) {
                ui_text_set_text_by_id(BASEFORM_148, wifi_str, strlen(wifi_str), FONT_DEFAULT);
            } else {
                ui_text_set_text_by_id(BASEFORM_148, wifi_str, strlen(wifi_str), FONT_DEFAULT);
            }
            break;

        case  UI_MSG_WIFI_SET_MODE_TEST:
            set_lcd_show_data_mode(ui);
            ui_page = msgListNode->msg.msgID;
            if (ui_page != ui_last_page) {
                ui_show_main(PAGE_DEVICE_TEST);
                ui_show_main(BASEFORM_46);
                ui_show_main(BASEFORM_47);
                ui_show_main(BASEFORM_48);
                ui_show_main(BASEFORM_50);
                ui_show_main(BASEFORM_51);
                ui_show_main(BASEFORM_52);

                ui_highlight_element_by_id(BASEFORM_46);
                ui_no_highlight_element_by_id(BASEFORM_52);
                ui_no_highlight_element_by_id(BASEFORM_50);
                ui_no_highlight_element_by_id(BASEFORM_47);
                ui_no_highlight_element_by_id(BASEFORM_51);
            }
            UCHAR_T wifi_str1[10] = {0};
            PR_NOTICE("get rssi %d!", flag);
            snprintf(wifi_str1, sizeof(wifi_str1), "%d", flag);
            if (Chinese_Simplified == languae) {
                ui_text_set_textu_by_id(BASEFORM_52, wifi_str1, strlen(wifi_str1), FONT_DEFAULT);
            } else if (English == languae) {
                ui_text_set_text_by_id(BASEFORM_52, wifi_str1, strlen(wifi_str1), FONT_DEFAULT);
            } else {
                ui_text_set_text_by_id(BASEFORM_52, wifi_str1, strlen(wifi_str1), FONT_DEFAULT);
            }
            struct unumber timer1;
            timer1.type = TYPE_NUM;
            timer1.numbs = 2;
            timer1.number[0] = p[1];
            ui_number_update_by_id(BASEFORM_48, &timer1);
            break;

        case  UI_MSG_SOUND_TEST:
            set_lcd_show_data_mode(ui);
            ui_page = msgListNode->msg.msgID;
            if ((ui_page != ui_last_page) && (ui_last_page != UI_MSG_WIFI_SET_MODE_TEST)) {
                ui_show_main(PAGE_DEVICE_TEST);
            }
            ui_highlight_element_by_id(BASEFORM_47);
            ui_no_highlight_element_by_id(BASEFORM_50);
            ui_no_highlight_element_by_id(BASEFORM_52);
            ui_no_highlight_element_by_id(BASEFORM_46);
            ui_no_highlight_element_by_id(BASEFORM_51);

            struct unumber timer;
            timer.type = TYPE_NUM;
            timer.numbs = 2;
            timer.number[0] = flag;
            ui_number_update_by_id(BASEFORM_48, &timer);
            break;

        case  UI_MSG_CAMERA_TEST:
            set_lcd_show_data_mode(ui);
            ui_page = msgListNode->msg.msgID;
            if ((ui_page != ui_last_page) && (ui_last_page != UI_MSG_SOUND_TEST) && (ui_last_page != UI_MSG_WIFI_SET_MODE_TEST)) {
                ui_show_main(PAGE_DEVICE_TEST);
            }
            ui_highlight_element_by_id(BASEFORM_51);
            ui_no_highlight_element_by_id(BASEFORM_50);
            ui_no_highlight_element_by_id(BASEFORM_52);
            ui_no_highlight_element_by_id(BASEFORM_46);
            ui_no_highlight_element_by_id(BASEFORM_47);
            struct unumber timer2;
            timer2.type = TYPE_NUM;
            timer2.numbs = 2;
            timer2.number[0] = flag;
            ui_number_update_by_id(BASEFORM_48, &timer2);
            break;

        case  UI_MSG_END_TEST:
            set_lcd_show_data_mode(ui);
            ui_page = msgListNode->msg.msgID;
            if ((ui_page != ui_last_page) && (ui_last_page != UI_MSG_SOUND_TEST) && (ui_last_page != UI_MSG_WIFI_SET_MODE_TEST)) {
                ui_show_main(PAGE_DEVICE_TEST);
            }
            ui_hide_main(BASEFORM_46);
            ui_hide_main(BASEFORM_50);
            ui_hide_main(BASEFORM_51);
            ui_hide_main(BASEFORM_52);
            ui_hide_main(BASEFORM_47);
            ui_show_main(BASEFORM_48);
            ui_show_main(BASEFORM_55);
            if ((p[1] >= TY_DEVICE_TEST_WIFI) && (p[1] < TY_DEVICE_TEST_LCD_STOP)) {
                if (p[2] == 1) {
                    ui_text_show_index_by_id(BASEFORM_55, 2);
                    ui_highlight_element_by_id(BASEFORM_55);
                } else if (p[2] == 2) {
                    ui_text_show_index_by_id(BASEFORM_55, 3);
                    ui_highlight_element_by_id(BASEFORM_55);
                } else if (p[2] == 3) {
                    ui_text_show_index_by_id(BASEFORM_55, 4);
                    ui_highlight_element_by_id(BASEFORM_55);
                } else {
                    ui_text_show_index_by_id(BASEFORM_55, 1);
                    ui_highlight_element_by_id(BASEFORM_55);
                }

            } else if (p[1] == TY_DEVICE_TEST_LCD_STOP) {
                ui_text_show_index_by_id(BASEFORM_55, 5);
                ui_no_highlight_element_by_id(BASEFORM_55);
            }

            struct unumber timer3;
            timer3.type = TYPE_NUM;
            timer3.numbs = 2;
            timer3.number[0] = flag;
            ui_number_update_by_id(BASEFORM_48, &timer3);
            break;

        case UI_MSG_UPADTE_TIME:
            ui_timer_update(flag);
            break;
        case UI_MSG_UPADTE_PERCENT:
            ui_fs_update_percent(flag);
            break;

        }


        ui_last_page = ui_page;

        if (msgListNode->msg.pMsgData) {
            Free(msgListNode->msg.pMsgData);
        }
        DelAndFreeMsgNodeFromQueue(ui_msg_que, msgListNode);
    }
}


STATIC VOID lcd_timer_cb(UINT_T timerID, PVOID_T pTimerArg)
{
    STATIC BOOL_T flag = TRUE;
    if (flag) {
        flag = false;
    } else {
        flag = TRUE;
    }
    ui_page3x_index_update(flag);
    if (note.page_x == UI_PAGE_SYS_SET_INDEX_1 && note.page2_x == UI_PAGE_SYS_CONFIG_INDEX_3_TIME && note.page_y >= UI_PAGE_Y_2) {
        sys_start_timer(lcd_timer, 500, TIMER_ONCE);
    }
}
STATIC VOID_T tuya_deal_page(BOOL_T key_up, UCHAR_T *cur_x_index, UCHAR_T max_index)
{
    UCHAR_T index = *cur_x_index;
    if (!key_up) {
        index++;
        if (index == max_index + 1) {
            index = 0;
        }

    } else {
        index--;
        if (index == 255) {
            index = max_index;
        }
    }
    *cur_x_index = index;
    return;
}

STATIC BOOL_T tuya_deal_page_y_one(BOOL_T key_up)
{
    BOOL_T post_nex_ui_index = TRUE;
    tuya_deal_page(key_up, &note.page_x, UI_PAGE_DEV_INFO_INDEX_3);
    return post_nex_ui_index;
}

STATIC BOOL_T tuya_deal_page_y_two(BOOL_T key_up)
{
    BOOL_T post_nex_ui_index = false;
    switch (note.page_x) {
    case UI_PAGE_RT_CAMERA_INDEX_0:
        break;
    case UI_PAGE_SYS_SET_INDEX_1:
        tuya_deal_page(key_up, &note.page2_x, UI_PAGE_DEV_INFO_INDEX_3);
        post_nex_ui_index = TRUE;
        break;
    case UI_PAGE_WIFI_INDEX_2:
        break;
    case UI_PAGE_DEV_INFO_INDEX_3:
        break;
    }
    return post_nex_ui_index;
}

STATIC BOOL_T tuya_deal_page_y_three(BOOL_T key_up)
{
    BOOL_T post_nex_ui_index = false;
    switch (note.page_x) {
    case UI_PAGE_RT_CAMERA_INDEX_0:
        break;
    case UI_PAGE_SYS_SET_INDEX_1:
        switch (note.page2_x) {
        case UI_PAGE_SYS_CONFIG_INDEX_1_LCD_SET:
            tuya_deal_page(key_up, &note.page3_x, UI_PAGE_LCD_CONFIG_INDEX_2);
            post_nex_ui_index = TRUE;
            break;
        case UI_PAGE_SYS_CONFIG_INDEX_2_LANG:
            tuya_deal_page(key_up, &note.page3_x, UI_PAGE_LANG_CONFIG_INDEX_1);
            post_nex_ui_index = TRUE;
            break;
        case UI_PAGE_SYS_CONFIG_INDEX_3_TIME:

            if (note.page3_y) {
                time_set_page(note.page3_x, key_up);

            } else {
                tuya_deal_page(key_up, &note.page3_x, UI_PAGE_TIME_7_CONCELL);
                post_nex_ui_index = TRUE;
            }
            break;
        }

        break;

    case UI_PAGE_WIFI_INDEX_2:

        break;

    case UI_PAGE_DEV_INFO_INDEX_3:
        break;

    }
    return post_nex_ui_index;
}

STATIC BOOL_T tuya_page_index(BOOL_T key_up)
{
    BOOL_T post_nex_ui_index = false;
    switch (note.page_y) {
    case UI_PAGE_Y_0:	     //一级页面
        post_nex_ui_index = tuya_deal_page_y_one(key_up);
        ui_page1x_index_update();
        break;
    case UI_PAGE_Y_1:	     //二级页面
        post_nex_ui_index = tuya_deal_page_y_two(key_up);
        ui_page2x_index_update();
        break;
    case UI_PAGE_Y_2:
        post_nex_ui_index = tuya_deal_page_y_three(key_up);
        ui_page3x_index_update(TRUE);
        break;

    }
    return post_nex_ui_index;
}


STATIC BOOL_T tuya_deal_page_enter_one(BOOL_T is_enter)
{
    BOOL_T enter_flag = false;
    tuya_lcd_play_pic(UI_MSG_CONFIG_SET, NULL, 0);
    enter_flag = TRUE;
    return enter_flag;
}

STATIC BOOL_T tuya_deal_page_enter_two(BOOL_T is_enter)
{
    BOOL_T enter_flag = false;

    switch (note.page_x) {
    case UI_PAGE_RT_CAMERA_INDEX_0:
        if (tuya_video_camera_power_off_status()) {
            tuya_video_lcd_ctr(TRUE, LCD_FROM_APP, UI_MSG_LOGO);
        } else {
            tuya_video_lcd_ctr(TRUE, LCD_FROM_APP, UI_MSG_LOGO);
        }
        enter_flag = false;
        break;
    case UI_PAGE_SYS_SET_INDEX_1:
        tuya_lcd_play_pic(UI_MSG_SYS_SET, NULL, 0);
        enter_flag = TRUE;
        break;

    case UI_PAGE_WIFI_INDEX_2:
        tuya_lcd_play_pic(UI_MSG_WIFI_SET_MODE, NULL, 0);
        enter_flag = TRUE;
        break;

    case UI_PAGE_DEV_INFO_INDEX_3:
        tuya_lcd_play_pic(UI_MSG_DEV_INFO, NULL, 0);
        enter_flag = TRUE;
        break;

    }
    return enter_flag;
}


STATIC BOOL_T tuya_deal_page_enter_three(BOOL_T is_enter)
{
    BOOL_T enter_flag = false;
    INT_T enter_TRUE = 1;
    switch (note.page_x) {

    case UI_PAGE_SYS_SET_INDEX_1:
        switch (note.page2_x) {
        case UI_PAGE_SYS_CONFIG_INDEX_0_RT_CAMERA:
            if (tuya_video_camera_power_off_status()) {
                tuya_video_lcd_ctr(TRUE, LCD_FROM_APP, UI_MSG_LOGO);
            } else {
                tuya_video_lcd_ctr(TRUE, LCD_FROM_APP, UI_MSG_LOGO);
            }
            enter_flag = false;
            break;

        case UI_PAGE_SYS_CONFIG_INDEX_1_LCD_SET:
            enter_flag = TRUE;
            tuya_lcd_play_pic(UI_MSG_LCD_SET, &enter_TRUE, sizeof(INT_T));

            break;

        case UI_PAGE_SYS_CONFIG_INDEX_2_LANG:
            enter_flag = TRUE;
            tuya_lcd_play_pic(UI_MSG_LANG_SET, &enter_TRUE, sizeof(INT_T));

            break;

        case UI_PAGE_SYS_CONFIG_INDEX_3_TIME:
            enter_flag = TRUE;
            tuya_lcd_play_pic(UI_MSG_TIME_SET, &enter_TRUE, sizeof(INT_T));

            break;


        }
        break;
    case UI_PAGE_WIFI_INDEX_2:

        tuya_lcd_play_pic(UI_MSG_WIFI_SET_MODE, NULL, 0);
        enter_flag = false;

        break;


    }
    return enter_flag;
}


STATIC BOOL_T tuya_deal_page_enter_three_confirm(BOOL_T is_enter)
{
    BOOL_T enter_flag = false;
    INT_T enter_TRUE = 0;
    switch (note.page_x) {
    case UI_PAGE_SYS_SET_INDEX_1:
        switch (note.page2_x) {
        case UI_PAGE_SYS_CONFIG_INDEX_1_LCD_SET:
            tuya_lcd_timer_set_and_start((note.page3_x * 10 + 10) * 1000);
            tuya_low_power_timer_flash_set_and_start((note.page3_x * 10 + 10) * 1000);
            tuya_lcd_play_pic(UI_MSG_LCD_SET, &enter_TRUE, sizeof(INT_T));
            note.page_y = UI_PAGE_Y_2;
            break;
        case UI_PAGE_SYS_CONFIG_INDEX_2_LANG:
            if (note.page3_x == 0) {
                languae = Chinese_Simplified;
            } else if (note.page3_x == 1) {
                languae = English;
            }
            ui_language_set(languae);
            tuya_fast_param_save(LCD_UI_LANGUAGE_ID, &languae, sizeof(INT_T));
            tuya_lcd_play_pic(UI_MSG_LANG_SET, &enter_TRUE, sizeof(INT_T));
            note.page_y = UI_PAGE_Y_2;
            break;

        case UI_PAGE_SYS_CONFIG_INDEX_3_TIME:
            note.page3_y++;
            if (note.page3_y == 2) {
                note.page3_y = 0;
            }
            if (!lcd_timer) {
                sys_add_timer(lcd_timer_cb, NULL, &lcd_timer);
            }
            if (note.page3_y) {
                sys_start_timer(lcd_timer, 500, TIMER_ONCE);
            } else {
                sys_stop_timer(lcd_timer);
                ui_page3x_index_update(TRUE);
            }
            if (note.page3_x == UI_PAGE_TIME_6_CONFIRM) {
                INT_T time_stamp = rtc_dev_time_get(&g_time_r);
                INT_T time_zone_seconds = 0;
                if (OPRT_OK == uni_get_time_zone_seconds(&time_zone_seconds)) {
                    time_stamp -= time_zone_seconds;
                } else {
                    time_stamp -= 80 * 60 * 60;
                }
                tuya_rtc_time_set(time_stamp);
                uni_time_set_posix(time_stamp, 0);
                tuya_lcd_play_pic(UI_MSG_TIME_SET, &enter_TRUE, sizeof(INT_T));
                note.page_y = UI_PAGE_Y_2;
                sys_stop_timer(lcd_timer);
            } else if (note.page3_x == UI_PAGE_TIME_7_CONCELL) {
                tuya_lcd_play_pic(UI_MSG_TIME_SET, &enter_TRUE, sizeof(INT_T));
                note.page_y = UI_PAGE_Y_2;
                sys_stop_timer(lcd_timer);
            }

            break;

        }

        break;

    }
    return enter_flag;
}
STATIC VOID_T tuya_page_enter(BOOL_T is_enter)
{
    BOOL_T enter_flag = false;
    if (is_enter) {
        note.page_y++;
    } else {
        if (note.page_y > 0) {
            note.page_y--;
        }
    }

    switch (note.page_y) {
    case UI_PAGE_Y_0:	     //一级页面
        enter_flag = tuya_deal_page_enter_one(is_enter);
        break;
    case UI_PAGE_Y_1:	     //二级页面
        enter_flag = tuya_deal_page_enter_two(is_enter);
        break;
    case UI_PAGE_Y_2:	 //三级页面
        note.page3_x = 0;
        note.page3_y = 0;
        enter_flag = tuya_deal_page_enter_three(is_enter);
        break;
    case UI_PAGE_Y_3:	      //三级页面确认
        enter_flag = tuya_deal_page_enter_three_confirm(is_enter);
        break;

    }
    if (false == enter_flag) {
        if (is_enter) {
            if (note.page_y > 0) {
                note.page_y--;
            }
        } else {
            note.page_y++;
        }
    }
    return;
}

INT_T ui_key_control(CHAR_T value, CHAR_T action) //纯ui按键控制
{
    INT_T msg;
    if (KEY_EVENT_CLICK == action) {

        switch (value) {
        case APP_KEY_RIGHT:
            PR_NOTICE(">>>>>>>>>>>>>>>>APP_KEY_RIGHT");//向下
            if (FALSE == tuya_video_lcd_open_status_get() || FALSE == ty_lcd_in_ui_page()) {
                break;
            }
            tuya_page_index(false);
            break;

        case APP_KEY_LEFT:
            if (FALSE == tuya_video_lcd_open_status_get() || FALSE == ty_lcd_in_ui_page()) {
                break;
            }
            PR_NOTICE(">>>>>>>>>>>>>>>APP_KEY_LEFT");//向上
            tuya_page_index(TRUE);
            break;

        case APP_KEY_MENU:
            if (tuya_video_lcd_open(LCD_FROM_BUTTON)) {
                menu_first_click = TRUE;
                break;
            }
            PR_NOTICE(">>>>>>>>>>>>>>>>APP_KEY_MENU");  //确定
            //目前在一级菜单 二级菜单控制 note.page_y = 0; 表示退出二级菜单
            tuya_page_enter(TRUE);
            break;

        }
        PR_NOTICE("note.page_x=%d note.page_y=%d note.page2_x=%d note.page3_x=%d note.page3_y=%d", note.page_x, note.page_y, note.page2_x, note.page3_x, note.page3_y);
    } else if (KEY_EVENT_LONG == action) {

        switch (value) {
        case APP_KEY_RIGHT:
            extern BOOL_T  power_up_init_time_flag;
            PR_NOTICE("tuya_video_lcd_open_status_get=%d ui_page=%d power_up_init_time_flag=%d", tuya_video_lcd_open_status_get(), ui_page, power_up_init_time_flag);
            if (tuya_video_lcd_open_status_get() && (FALSE == ty_lcd_in_ui_page()) && ((FALSE == tuya_is_button_wk_up()) || (tuya_is_button_wk_up() && power_up_init_time_flag))) {
                note.page_y = 0;
                tuya_video_lcd_ctr(TRUE, LCD_FROM_BUTTON, UI_MSG_CONFIG_SET);
            } else if (tuya_video_lcd_open_status_get() && (UI_MSG_CONFIG_SET == ui_page || UI_MSG_CONFIG_SET_SYN == ui_page)) {
                note.page_y = 0;
                if (tuya_video_camera_power_off_status()) {
                    tuya_video_lcd_ctr(TRUE, LCD_FROM_APP, UI_MSG_LOGO);
                } else {
                    tuya_video_lcd_ctr(TRUE, LCD_FROM_APP, UI_MSG_LOGO);
                }
            } else if (tuya_video_lcd_open_status_get() && ty_lcd_in_ui_page()) {
                tuya_page_enter(false);
            }
            break;
        case APP_KEY_MENU:
            note.page_y = 0;
            tuya_video_lcd_ctr(FALSE, LCD_FROM_BUTTON, 0);
            break;
        }
    }

    tuya_lcd_off_ctrl_start();
    tuya_low_power_time_set_and_start(0);

    return 0;
}



STATIC VOID tuya_ui_time_cb(UINT_T timerID, PVOID_T pTimerArg)
{
    INT_T update_flash = 1;
    STATIC INT_T last_timestamp = 0;
    INT_T timestamp = 0;
    if (UI_MSG_CONFIG_SET == ui_page || UI_MSG_LOGO == ui_page || UI_MSG_CONFIG_SET_SYN == ui_page || UI_MSG_LOGO_SYN == ui_page || UI_MSG_CAMERA == ui_page || UI_MSG_CAMERA_SYN == ui_page) {
        if (FALSE == tuya_video_lcd_open_status_get()) {
            sys_start_timer(ui_timer_id, 1000, TIMER_ONCE);
            return;
        }
        timestamp = uni_time_get_posix();
        if (timestamp == last_timestamp) {
            sys_start_timer(ui_timer_id, 1000, TIMER_ONCE);
            return;
        }
        last_timestamp = timestamp;
        tuya_lcd_play_pic(UI_MSG_UPADTE_TIME, &update_flash, sizeof(INT_T));
        sys_start_timer(ui_timer_id, 1000, TIMER_ONCE);
    }
}
STATIC OPERATE_RET tuya_ui_timer_init(VOID)
{
    OPERATE_RET op_ret = OPRT_OK;
    op_ret = system_timer_init();
    if (OPRT_OK != op_ret) {
        PR_ERR("system_timer_init  err:%d", op_ret);
        return op_ret;
    }
    op_ret = sys_add_timer(tuya_ui_time_cb, NULL, &ui_timer_id);
    if (OPRT_OK != op_ret) {
        PR_ERR("sys_add_timer tuya_ui_timer_init err:%d", op_ret);
        return op_ret;
    }
    return op_ret;
}

VOID tuya_lcd_play_pic_syn(INT_T ui_num)
{
    if (ui_num != UI_MSG_CONFIG_SET_SYN && ui_num != UI_MSG_LOGO_SYN && ui_num != UI_MSG_NULL_SYN && UI_MSG_CAMERA_SYN != ui_num) {
        return;
    }
    SEM_HANDLE wait_sem = NULL;
    OPERATE_RET op_ret = OPRT_OK;
    op_ret = tuya_hal_semaphore_create_init(&wait_sem, 0, 1);
    if (OPRT_OK != op_ret) {
        PR_ERR("tuya_lcd_play_pic_syn malloc fail");
        return;
    }
    op_ret = tuya_lcd_play_pic(ui_num, &wait_sem, SIZEOF(SEM_HANDLE));
    if (OPRT_OK != op_ret) {
        PR_ERR("tuya_lcd_play_pic_syn send fail");
        tuya_hal_semaphore_release(wait_sem);
        return;
    }
    tuya_hal_semaphore_waittimeout(wait_sem, TY_UI_WAIT_SEM_TIMEOUT);
    tuya_hal_semaphore_release(wait_sem);
}

VOID ty_ui_init(VOID)
{
    STATIC UCHAR_T init = 0;
    OPERATE_RET op_ret;

    op_ret = tuya_fast_param_read(LCD_UI_LANGUAGE_ID, &languae, sizeof(INT_T));
    if (op_ret <= 0) {
        //PR_NOTICE("syscfg_read language failed! op_ret:%d ", op_ret);
        languae = ty_get_ui_default_language();
    } else {
        if (languae != Chinese_Simplified && languae != English) {
            languae = Chinese_Simplified;
        }
        PR_NOTICE("languae=%d", languae);
    }
    file_buf = file_log_buf;
    norflash_open(NULL, NULL, NULL);
    memset(file_buf, 0, 20 * 1024);
    norflash_origin_read(file_buf, 0x3DD000, 20 * 1024);

    if (init) {
        return;
    }
    op_ret = tuya_ui_timer_init();
    if (OPRT_OK != op_ret) {
        PR_ERR("tuya_ui_timer_init op_ret:%d", op_ret);
        return ;
    }
    op_ret = CreateMsgQueAndInit(&ui_msg_que);
    if (OPRT_OK != op_ret) {
        PR_ERR("CreateMsgQueAndInit op_ret:%d", op_ret);
        return ;
    }
    THRD_PARAM_S thrd_param;
    thrd_param.priority = TRD_PRIO_0;
    thrd_param.stackDepth = 1024 * 4;
    thrd_param.thrdname = TY_UI_TASK_NAME;
    op_ret = CreateAndStart(&ui_handle, NULL, NULL, ty_ui, NULL, &thrd_param);
    if (OPRT_OK != op_ret) {
        PR_ERR("CreateAndStart failed!");
        return ;
    }

    init = 1;

    return ;
}
VOID tuya_set_ui_language(int language_num)
{
    languae = language_num;
}

#endif
