/***********************************************************
*  File: tuya_device.c
*  Author: mjl
*  Date: 20210507
***********************************************************/
#include "app_config.h"
#include "qrcode/qrcode.h"

#include "tuya_iot_wifi_api.h"
#include "tuya_iot_com_api.h"
#include "tuya_iot_internal_api.h"
#include "gw_intf.h"
#include "http_inf.h"
#include "tuya_bt.h"
#include "httpc.h"
#include "tuya_tls.h"
#include "ty_cJSON.h"
#include "uni_time_queue.h"
#include "uni_msg_queue.h"
#include "uni_log.h"
#include "tuya_uart.h"
#include "tuya_pwm.h"
#include "tuya_jl_gpio.h"
#include "tuya_adc.h"
#include "tuya_uart_common_basic_service.h"
#include "tuya_audio_source.h"
#include "uni_log.h"
#include "stdio.h"
#include "tuya_video.h"
#include "tuya_ui.h"

#define RESULTS_BUFFER_SIZE     255
#define MAX_JPEG_SIZE 50*1024
typedef struct {
    BOOL_T          qr_code_running;
    THRD_HANDLE     qrcode_hand;
    VOID_T         *qr_decoder;
    BOOL_T         get_qr_yuv_data;
    BOOL_T         get_qr_result;
} TY_QRCODE_CRTL;

typedef struct {
    UCHAR_T *data;
    UINT_T   data_size;
} QR_RESULTS_T;

STATIC TY_QRCODE_CRTL  g_qrcode_ctrl = {0};
STATIC QR_RESULTS_T identify_result = {0};
STATIC INT_T usb_type = USB_TYPE_NONE_E;
STATIC INT_T usb_auto_type = USB_TYPE_NONE_E;
STATIC TY_USB_PARAM usb_param = {0};
STATIC VOID tuya_qrcode_finish(VOID)
{
    UCHAR_T send_st = 6;
    ty_uart_send_data_direct(WIFI_STATE_CMD, &send_st, SIZEOF(UCHAR_T));
    tuya_set_wifi_status(send_st);
}


STATIC OPERATE_RET tuya_parse_wifi_cfg(CHAR_T *str)
{
    OPERATE_RET op_ret;
    ty_cJSON *root = cJSON_Parse(str);
    if (NULL == root) {
        PR_ERR("cjson parse err");
        return OPRT_CJSON_PARSE_ERR;
    }

    ty_cJSON *js_ssid = cJSON_GetObjectItem(root, "s");
    ty_cJSON *js_token = cJSON_GetObjectItem(root, "t");
    if (NULL == js_ssid || NULL == js_token) {
        PR_ERR("param is no correct");
        cJSON_Delete(root);
        return OPRT_INVALID_PARM;
    }

    ty_cJSON *js_pwd = cJSON_GetObjectItem(root, "p");

    wf_ap_stop();

    tuya_qrcode_finish();

    if (NULL != js_pwd) {
        op_ret = tuya_iot_gw_wf_user_cfg(js_ssid->valuestring, js_pwd->valuestring, js_token->valuestring);
    } else {
        op_ret = tuya_iot_gw_wf_user_cfg(js_ssid->valuestring, NULL, js_token->valuestring);
    }

    cJSON_Delete(root);
    return op_ret;
}



STATIC VOID_T qr_code_net_cfg_stop(VOID_T)
{
    if (g_qrcode_ctrl.qr_decoder) {
        qrcode_deinit(g_qrcode_ctrl.qr_decoder);
        g_qrcode_ctrl.qr_decoder = NULL;
    }
}

STATIC INT_T qr_code_net_cfg_process(CHAR_T *inputFrame, INT_T width, INT_T height, QR_RESULTS_T *decode_results)
{
    INT_T ret = -1, type = 0;
    CHAR_T *buf = NULL;
    INT_T buf_size = 0;
    INT_T md_detected = 0; //是否检测到运动物体
    INT_T enc_type = 4;
    if (NULL == g_qrcode_ctrl.qr_decoder) {
        g_qrcode_ctrl.qr_decoder   = qrcode_init(width, height, width, QRCODE_MODE_NORMAL, 60, 0, 0);
    }
    if (g_qrcode_ctrl.qr_decoder)  {
        qrcode_detectAndDecode(g_qrcode_ctrl.qr_decoder, inputFrame, &md_detected);
        ret = qrcode_get_result(g_qrcode_ctrl.qr_decoder,  &buf, &buf_size, &enc_type);
        type = qrcode_get_symbol_type(g_qrcode_ctrl.qr_decoder);
        PR_DEBUG("qr code type = %d buf_size=%d", type, buf_size);
        if (buf_size > 0 && ret == 0) {
            PR_DEBUG("qr code type = %d decode: %s ,buf_size=%d", type, buf, buf_size);
            memcpy(decode_results->data, buf, buf_size);
            decode_results->data_size = buf_size;
            ret = 0;
        } else {
            PR_DEBUG("qr code ret = %d", ret);
        }
    }
    return ret;
}



STATIC CHAR_T *my_mem_find_ffd9(CHAR_T *src, INT_T len)
{
    CHAR_T *result = NULL;
    CHAR_T substr[2] = {0xff, 0xd9};

    CHAR_T *find_src = src;
    INT_T i = 0;
    for (i = 0; i < len; i++) {
        if (0 == memcmp(find_src, substr, 2)) {
            result = find_src;
            break;
        }
        find_src++;
    }
    return result;
}


STATIC VOID tuya_device_net_time_cb(UINT_T timerID, PVOID_T pTimerArg)
{
    INT_T flag = 1;
    STATIC BOOL_T lcd_net_ok = FALSE;
    if (lcd_net_ok) {
        tuya_lcd_play_pic(UI_MSG_GET_SSID, &flag, sizeof(INT_T));
        tuya_video_lcd_ctr(FALSE, LCD_FROM_QRCODE, 0);
        return;
    }
    {
        if (4 == tuya_get_wifi_status()) {
            flag = 2;
            tuya_lcd_play_pic(UI_MSG_GET_SSID, &flag, sizeof(INT_T));
            lcd_net_ok = TRUE;
            sys_start_timer(timerID, 1000, TIMER_ONCE);
        } else {
            sys_start_timer(timerID, 500, TIMER_ONCE);
        }
    }


}

STATIC OPERATE_RET tuya_net_timer_init(VOID)
{
    OPERATE_RET op_ret = OPRT_OK;
    STATIC TIMER_ID  net_timer_id = 0;
    INT_T heap_size = 0;

    INT_T flag = 0;
    tuya_lcd_play_pic(UI_MSG_GET_SSID, &flag, sizeof(INT_T));

#if TCFG_HOST_AUDIO_ENABLE
    if (ty_audio_device_online())
#endif
    {
        PR_NOTICE("tuya_play_local_audio net cfg");
        tuya_play_local_audio(AUDIO_PLAY_VOICE_1);
    }

    op_ret = sys_add_timer(tuya_device_net_time_cb, NULL, &net_timer_id);
    if (OPRT_OK != op_ret) {
        PR_ERR("sys_add_timer tuya_uart_heart_timer_cb err:%d", op_ret);
        return op_ret;
    }
    op_ret = sys_start_timer(net_timer_id, 1500, TIMER_ONCE);
    if (OPRT_OK != op_ret) {
        PR_ERR("sys_start_timer err:%d", op_ret);
        return op_ret;
    }

    return op_ret;
}

OPERATE_RET tuya_usb_param_update(VOID)
{
    OPERATE_RET op_ret = OPRT_OK;
    UINT_T read_len = 0;
    INT_T param = 0;

    if (usb_type) {
        PR_NOTICE("usb_type =%d no need update.", usb_type);
        return op_ret;
    }
    if (ty_video_device_online()) {
        if (ty_audio_device_online()) {
            param = USB_TYPE_UVC_UAC_E;
        } else {
            param = USB_TYPE_UVC_E;
        }
        if (param != usb_auto_type) {
            usb_auto_type = param;
            op_ret = ty_param_save(USB_AUTO_CFG_PARAM_E, &param, SIZEOF(INT_T));
            PR_NOTICE("tuya_fast_param_save op_ret=%d", op_ret);
        }
        PR_NOTICE("usb_auto_type =%d update ok.", usb_auto_type);
    }

    return op_ret;
}

OPERATE_RET tuya_usb_param_direct_update(INT_T param)
{
    OPERATE_RET op_ret = OPRT_OK;
    UINT_T read_len = 0;

    if (usb_type) {
        PR_NOTICE("usb_type =%d no need update.", usb_type);
        return op_ret;
    }

    if (param != usb_auto_type) {
        usb_auto_type = param;
        op_ret = ty_param_save(USB_AUTO_CFG_PARAM_E, &param, SIZEOF(INT_T));
        PR_NOTICE("tuya_fast_param_save op_ret=%d", op_ret);
    }
    PR_NOTICE("usb_auto_type =%d update ok.", usb_auto_type);

    return op_ret;
}

OPERATE_RET tuya_usb_param_init(VOID)
{
    OPERATE_RET op_ret = OPRT_OK;
    UINT_T read_len = 0;
    op_ret = ty_param_load(USB_CFG_PARAM_E, &usb_param, SIZEOF(TY_USB_PARAM), &read_len);
    if (op_ret != OPRT_OK) {
        usb_type = 0;
    } else {
        usb_type = usb_param.usb_type;
    }
    op_ret = ty_param_load(USB_AUTO_CFG_PARAM_E, &usb_auto_type, SIZEOF(INT_T), &read_len);
    if (op_ret != OPRT_OK) {
        usb_auto_type = 0;
    }
    return op_ret;
}
INT_T ty_get_usb_spped(VOID)
{
    return usb_param.usb_speed;
}

INT_T tuya_usb_param_get(VOID)
{
    INT_T param = 0;
    if (usb_type) {
        param = usb_type;
    } else {
        param = usb_auto_type;
    }
    return param;
}
BOOL_T tuya_usb_auto_param_is_have(VOID)
{
    BOOL_T have_auto_param = false;
    if (usb_type) {
        have_auto_param = false;
    } else {
        have_auto_param = true;
    }
    return have_auto_param;
}
STATIC VOID_T tuya_qrcode_task(VOID)
{
    OPERATE_RET op_ret = 0;
    GW_WIFI_NW_STAT_E cur_nw_stat = 0;
    BOOL_T status = FALSE;

    identify_result.data = NULL;
    identify_result.data_size = RESULTS_BUFFER_SIZE;
    identify_result.data = tuya_hal_system_malloc(RESULTS_BUFFER_SIZE);
    if (identify_result.data == NULL) {
        PR_DEBUG("MALLOC FAIL \n\r");
    }
    memset(identify_result.data, 0, RESULTS_BUFFER_SIZE);
    g_qrcode_ctrl.qr_code_running = TRUE;


    GW_WORK_STAT_MAG_S gw_wsm;
    GW_CNTL_S *gw_cntl = get_gw_cntl();
    memcpy(&gw_wsm, &(gw_cntl->gw_wsm), SIZEOF(GW_WORK_STAT_MAG_S));
    gw_wsm.nc_tp = GWNS_LOWPOWER;
    op_ret = wd_gw_wsm_write(&gw_wsm);
    if (OPRT_OK != op_ret) {
        PR_ERR("wd_gw_wsm_write failed! op_ret:%d", op_ret);
    } else {
        PR_NOTICE("next power on enter normal");
    }
    tuya_video_lcd_ctr(TRUE, LCD_FROM_QRCODE, UI_MSG_CAMERA);
    while (1) {
#if TCFG_HOST_AUDIO_ENABLE
        if (ty_audio_device_online())
#endif
        {
            if (!status) {
                tuya_hal_system_sleep(500);
                tuya_play_local_audio(AUDIO_PLAY_VOICE_2);
                status = TRUE;
            }
        }

        op_ret = get_wf_gw_nw_status(&cur_nw_stat);
        if (OPRT_OK != op_ret) {
            tuya_hal_system_sleep(100);
            continue;
        }

        if (cur_nw_stat == STAT_LOW_POWER) {
            tuya_video_lcd_ctr(FALSE, LCD_FROM_QRCODE, 0);
            tuya_hal_system_sleep(500);
            extern VOID __wf_net_change(IN CONST GW_WIFI_NW_STAT_E conn_state);
            __wf_net_change(STAT_LOW_POWER);
            break;
        }

        if ((cur_nw_stat > STAT_AP_STA_UNCFG) && (cur_nw_stat != STAT_UNPROVISION_AP_STA_UNCFG)) {
            PR_NOTICE("now wifi net is %d, quit qrdecode task", cur_nw_stat);
            tuya_lcd_ctrl_timer_off();  //防止断电情况下 lcd关闭倒计时起作用
            tuya_usb_param_update();

            tuya_video_set_camera_status(FALSE);
            tuya_hal_system_sleep(500);
            tuya_net_timer_init();
            tuya_ble_set_serv_switch(FALSE);
            tuya_low_power_time_set_and_start(120000);
            break;
        }

        if (g_qrcode_ctrl.get_qr_result) {
            g_qrcode_ctrl.get_qr_yuv_data = FALSE;
        } else {
            g_qrcode_ctrl.get_qr_yuv_data = TRUE;
        }
        tuya_hal_system_sleep(500);
    }
    g_qrcode_ctrl.get_qr_yuv_data = FALSE;
    if (identify_result.data) {
        tuya_hal_system_free(identify_result.data);
        identify_result.data = NULL;
    }

    qr_code_net_cfg_stop();

    tuya_hal_system_sleep(100);
    g_qrcode_ctrl.qr_code_running = FALSE;

    if (cur_nw_stat == STAT_LOW_POWER) {
        tuya_set_sys_power_off();
    }
    op_ret = DeleteThrdHandle(g_qrcode_ctrl.qrcode_hand);
    if (op_ret != OPRT_OK) {
        PR_ERR("DeleteThrdHandle err");
    } else {
        g_qrcode_ctrl.qrcode_hand = NULL;
        PR_NOTICE("DeleteThrdHandle tuya_qrcode_task success");
    }

}
BOOL_T tuya_qrcode_is_run(VOID_T)
{
    return g_qrcode_ctrl.qr_code_running;
}
VOID_T tuya_qrcode_task_creat(VOID_T)
{
    OPERATE_RET op_ret = OPRT_OK;

    if (g_qrcode_ctrl.qrcode_hand != NULL) {
        PR_DEBUG("qrcode_task is not release!!");
        return ;
    }
    tuya_lcd_ctrl_timer_off();
    /*创建二维码相关任务*/
    THRD_PARAM_S thrd_param;
    thrd_param.priority = TRD_PRIO_6;
    thrd_param.stackDepth = 1024 * 5; // 二维码识别 栈空间需要很大，否则崩溃
    thrd_param.thrdname = "ty_qrcode_task";
    op_ret = CreateAndStart(&g_qrcode_ctrl.qrcode_hand, NULL, NULL, tuya_qrcode_task, NULL, &thrd_param);
    if (OPRT_OK != op_ret) {
        PR_ERR("Create qrcode_image_get error!: %d", op_ret);
        return ;
    }
}

VOID_T qr_code_yuv_data(CHAR_T *buf, INT_T size, INT_T width, INT_T height, CHAR_T type)
{
    INT_T ret = OPRT_COM_ERROR;
    STATIC INT_T qrcode_camera = 1;
    if (g_qrcode_ctrl.get_qr_yuv_data) {
        g_qrcode_ctrl.get_qr_yuv_data = FALSE;
        if (NULL == identify_result.data) {
            return;
        }
        if (qrcode_camera) {
            tuya_lcd_play_pic(UI_MSG_CAMERA, &qrcode_camera, sizeof(INT_T));
            qrcode_camera = 0;
        }
        PR_DEBUG("yuv buf=0x%x size=%d   width =%d height=%d", buf, size, width, height);
        PR_DEBUG("qr_code_net_cfg_process start");
        ret = qr_code_net_cfg_process(buf, width, height, &identify_result);
        PR_DEBUG("qr_code_net_cfg_process end");
        if (!ret) {
            PR_DEBUG("buf:%s", identify_result.data);
            ret = tuya_parse_wifi_cfg(identify_result.data);
            if (!ret) {
                g_qrcode_ctrl.get_qr_result = TRUE;
            }
        }


    }
}
