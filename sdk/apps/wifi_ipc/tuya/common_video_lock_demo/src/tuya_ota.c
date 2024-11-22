/***********************************************************
*  File: tuya_ota.c
*  Author: mengjinlong
*  Date: 201211101
***********************************************************/
#include "tuya_device.h"
#include "uni_log.h"
#include "svc_uart_queue.h"
#include "svc_mcu_ota.h"
#include "svc_uart_multi_thread.h"
#include "tuya_uart_common_basic_service.h"
#include "tuya_uart_public_send_protocol.h"
#include "tuya_ota.h"
#include "base_event_info.h"
#include "tuya_svc_upgrade.h"
#include "sys_timer.h"
#include "gw_intf.h"
#include "tuya_low_power.h"
#include "tuya_ui.h"
#define TY_UART_MCU_OTA_LEN        (256)
#define TY_UART_MCU_OTA_OFFSET_LEN (4)
#define TY_UART_MCU_OTA_TIMER_S    (5)
#define TY_UART_MCU_OTA_CYC_TIME   (3)

#define OTA_WF                    0x00
#define OTA_MCU                   0x01


#define UPGRADE_STATE_DETECT       0x00
#define UPGRADE_STATE_ALREADY_NEW  0x01
#define UPGRADE_STATE_RUNNING      0x02
#define UPGRADE_STATE_SUCC         0x03
#define UPGRADE_STATE_FAILED       0x04


#define UPGRADE_CONTINUE       0x00
#define UPGRADE_LOW_BATTERY_REFUSE       0x01
#define UPGRADE_REFUSE_UNKONWN      0x02

#define UPGRADE_RECEIVE            0x00
#define UPGRADE_PROCESS            0x01
#define UPGRADE_FINISHED           0x02
#define UPGRADE_FAILED             0x03

#define OTA_PROCESS_NOTIFY  "ota.process.notify"
#define OTA_FAILED_NOTIFY  "ota.failed.notify"
#define OTA_FINISHED_NOTIFY  "ota.finished.notify"

#define QUERY_UG_TIMEOUT         4500

typedef struct {
    UINT_T file_len;
} TY_MCU_OTA_MSG;

STATIC TY_MCU_OTA_MSG g_mcu_msg = {
    .file_len = 0,
};
typedef struct {
    TIMER_ID           query_gw_timeout;
    TIMER_ID           send_ota_timeout;
    UCHAR_T            ug_state;
    BOOL_T             is_mcu_request_ota;
    DEV_TYPE_T         ota_type;
    CHAR_T             sw_ver[SW_VER_LEN + 1];
    BOOL_T            ug_flag;
} TY_DEV_OTA_CTRL;

STATIC TY_DEV_OTA_CTRL g_dev_ota_ctrl = {0};
STATIC OPERATE_RET ty_uart_mcu_ota_start_cb(IN CONST FW_UG_S *p_ug_info, OUT TY_OTA_PACK_E *action_type);
STATIC OPERATE_RET ty_uart_mcu_ota_data_cb(IN CONST UCHAR_T *p_data, IN CONST UINT_T len, IN UINT_T offset, OUT TY_OTA_PACK_E *action_type);
STATIC OPERATE_RET ty_uart_mcu_ota_end_status_cb(IN TY_OTA_END_STATUS_E status, IN UINT_T offset);

STATIC TY_OTA_CB_HANDLE_S g_ota_msg = {\
                                       .iot_dev_ota_start_cb = ty_uart_mcu_ota_start_cb, \
                                       .iot_dev_ota_data_cb =  ty_uart_mcu_ota_data_cb, \
                                       .iot_dev_ota_end_sta_cb = ty_uart_mcu_ota_end_status_cb, \
                                      };
STATIC TY_OTA_SEND_FRAME_HANDLE_CB g_ota_send_cb = NULL;


STATIC OPERATE_RET tuya_ota_send_cmd(IN TY_OTA_SEND_TYPE_E type, IN UCHAR_T cmd, IN CHAR_T *data, IN UINT_T data_len, PVOID_T arg)
{
    OPERATE_RET op_ret = OPRT_COM_ERROR;
    if (g_ota_send_cb) {
        TY_OTA_SEND_FRAME_S send_data = {0};
        send_data.type = type;
        send_data.cmd = cmd;
        send_data.data_len = data_len;
        send_data.data = data;
        if (OTA_SEND_TYPE_SYN == type) {
            if (NULL == arg) {
                op_ret = OPRT_INVALID_PARM;
                return op_ret;
            }
            TY_OTA_SEND_SYN_CFG_S *syn = (TY_OTA_SEND_SYN_CFG_S *)arg;
            memcpy(&send_data.cfg.syn_cfg, syn, SIZEOF(TY_OTA_SEND_SYN_CFG_S));
        } else if (OTA_SEND_TYPE_IN_QUE_NORMAL == type || OTA_SEND_TYPE_IN_QUE_TIMER_SET == type) {
            if (NULL == arg) {
                op_ret = OPRT_INVALID_PARM;
                return op_ret;
            }
            TY_OTA_SEND_IN_QUEUE_CFG_S *cfg = (TY_OTA_SEND_IN_QUEUE_CFG_S *)arg;
            memcpy(&send_data.cfg.in_queue_cfg, cfg, SIZEOF(TY_OTA_SEND_IN_QUEUE_CFG_S));
        }
        op_ret = g_ota_send_cb(&send_data);
    }
    return op_ret;
}


STATIC VOID tuya_auto_upgrade_send_cmd(IN UCHAR_T ota_cmd, IN UCHAR_T ota_type, IN UCHAR_T result)
{
    UCHAR_T data[2];
    data[0] = result;
    data[1] = ota_type;
    tuya_ota_send_cmd(OTA_SEND_TYPE_DIRECT, ota_cmd, data, SIZEOF(data), NULL);
}

STATIC VOID tuya_request_upgrade_send_cmd(IN UCHAR_T req_ota_cmd, IN UCHAR_T stat)
{
    tuya_ota_send_cmd(OTA_SEND_TYPE_DIRECT, req_ota_cmd, &stat, 1, NULL);
}

STATIC VOID tuya_request_set_upgrade(IN UCHAR_T req_ota_cmd, IN UCHAR_T stat)
{
    g_dev_ota_ctrl.ug_state = stat;
    tuya_request_upgrade_send_cmd(req_ota_cmd, stat);
}

STATIC VOID tuya_send_ota_status(IN UCHAR_T req_ota_stat, IN UCHAR_T auto_ota_stat)
{
    if (g_dev_ota_ctrl.is_mcu_request_ota) {
        if (g_dev_ota_ctrl.ota_type == DEV_NM_ATH_SNGL) {
            tuya_request_set_upgrade(REQ_WIFI_OTA_CMD, req_ota_stat);
        } else if (g_dev_ota_ctrl.ota_type == DEV_NM_NOT_ATH_SNGL) {
            tuya_request_set_upgrade(REQ_MCU_OTA_CMD, req_ota_stat);
        }
    } else {
        if (g_dev_ota_ctrl.ota_type == DEV_NM_ATH_SNGL) {
            tuya_auto_upgrade_send_cmd(AUTO_UPGRADE_CMD, OTA_WF, auto_ota_stat);
        } else if (g_dev_ota_ctrl.ota_type == DEV_NM_NOT_ATH_SNGL) {
            tuya_auto_upgrade_send_cmd(AUTO_UPGRADE_CMD, OTA_MCU, auto_ota_stat);
        }
    }
}


STATIC OPERATE_RET ty_uart_mcu_ota_start_cb(IN CONST FW_UG_S *p_ug_info, OUT TY_OTA_PACK_E *action_type)
{
    OPERATE_RET op_ret = OPRT_OK;
    UINT_T  len = 0;

    len = p_ug_info->file_size;
    g_mcu_msg.file_len = len;
    UCHAR_T file_len_buf[4] = {0};
    memset(file_len_buf, 0, SIZEOF(file_len_buf));
    /*大端模式*/
    file_len_buf[0] = (len >> 24) & 0xFF;
    file_len_buf[1] = (len >> 16) & 0xFF;
    file_len_buf[2] = (len >> 8) & 0xFF;
    file_len_buf[3] = (len) & 0xFF;
    TY_OTA_SEND_IN_QUEUE_CFG_S  in_queue_cfg;
    in_queue_cfg.p_name = MCU_OTA_START_STRING_NAME;
    in_queue_cfg.timerout_s = TY_UART_MCU_OTA_TIMER_S;
    in_queue_cfg.send_time = TY_UART_MCU_OTA_CYC_TIME;
    tuya_ota_send_cmd(OTA_SEND_TYPE_IN_QUE_TIMER_SET, MCU_OTA_START_CMD, file_len_buf, SIZEOF(file_len_buf), (PVOID_T)(&in_queue_cfg));
    *action_type = OTA_PACK_WAIT;
    sys_stop_timer(g_dev_ota_ctrl.send_ota_timeout);
    sys_start_timer(g_dev_ota_ctrl.send_ota_timeout, (TY_UART_MCU_OTA_TIMER_S * TY_UART_MCU_OTA_CYC_TIME + TY_UART_MCU_OTA_TIMER_S) * 1000, TIMER_ONCE);
    return op_ret;
}

STATIC OPERATE_RET ty_uart_mcu_ota_data_cb(IN CONST UCHAR_T *p_data, IN CONST UINT_T len, IN UINT_T offset, OUT TY_OTA_PACK_E *action_type)
{

    OPERATE_RET op_ret = OPRT_OK;
    UINT_T malloc_len = len + TY_UART_MCU_OTA_OFFSET_LEN;

    UCHAR_T  *p_uart_buf = (UCHAR_T *)Malloc(malloc_len);
    if (NULL == p_uart_buf) {
        PR_ERR("malloc len %d err", malloc_len);
        return OPRT_MALLOC_FAILED;
    }

    memset(p_uart_buf, 0, malloc_len);

    p_uart_buf[0] = ((offset >> 24) & 0xFF);
    p_uart_buf[1] = ((offset >> 16) & 0xFF);
    p_uart_buf[2] = ((offset >> 8) & 0xFF);
    p_uart_buf[3] = (offset & 0xFF);

    if (0 != len) {
        memcpy(p_uart_buf + TY_UART_MCU_OTA_OFFSET_LEN, p_data, len);
    }

    TY_OTA_SEND_IN_QUEUE_CFG_S  in_queue_cfg;
    in_queue_cfg.p_name = MCU_OTA_TRANS_STRING_NAME;
    in_queue_cfg.timerout_s = TY_UART_MCU_OTA_TIMER_S;
    in_queue_cfg.send_time = TY_UART_MCU_OTA_CYC_TIME;
    tuya_ota_send_cmd(OTA_SEND_TYPE_IN_QUE_TIMER_SET, MCU_OTA_TRANS_CMD, p_uart_buf, malloc_len, (PVOID_T)(&in_queue_cfg));
    Free(p_uart_buf);
    p_uart_buf = NULL;

    *action_type = OTA_PACK_WAIT;
    sys_stop_timer(g_dev_ota_ctrl.send_ota_timeout);
    sys_start_timer(g_dev_ota_ctrl.send_ota_timeout, (TY_UART_MCU_OTA_TIMER_S * TY_UART_MCU_OTA_CYC_TIME + TY_UART_MCU_OTA_TIMER_S) * 1000, TIMER_ONCE);
    return op_ret;
}

STATIC OPERATE_RET ty_uart_mcu_ota_finish_ok(VOID)
{
    OPERATE_RET op_ret = OPRT_OK;
    UCHAR_T file_len_buf[4] = {0};
    memset(file_len_buf, 0, SIZEOF(file_len_buf));
    sys_stop_timer(g_dev_ota_ctrl.send_ota_timeout);
    /*大端模式*/
    file_len_buf[0] = (g_mcu_msg.file_len >> 24) & 0xFF;
    file_len_buf[1] = (g_mcu_msg.file_len >> 16) & 0xFF;
    file_len_buf[2] = (g_mcu_msg.file_len >> 8) & 0xFF;
    file_len_buf[3] = (g_mcu_msg.file_len) & 0xFF;

    TY_OTA_SEND_IN_QUEUE_CFG_S  in_queue_cfg;
    in_queue_cfg.p_name = MCU_OTA_TRANS_STRING_NAME;
    in_queue_cfg.timerout_s = TY_UART_MCU_OTA_TIMER_S;
    in_queue_cfg.send_time = TY_UART_MCU_OTA_CYC_TIME;
    tuya_ota_send_cmd(OTA_SEND_TYPE_IN_QUE_TIMER_SET, MCU_OTA_TRANS_CMD, file_len_buf, SIZEOF(file_len_buf), (PVOID_T)(&in_queue_cfg));
    if (OPRT_OK != op_ret) {
        PR_ERR("ty_uart_protocol_in_queue_timer_set err:%d", op_ret);
    } else {
        strcpy(get_gw_cntl()->gw_if.attr[0].ver, g_dev_ota_ctrl.sw_ver);
        get_gw_cntl()->gw_if.attr[0].tp = GP_DEV_MCU;
        op_ret = http_gw_update_version_v41();
        if (OPRT_OK != op_ret) {
            PR_ERR("version_update err! op_ret:%d", op_ret);
            tuya_send_ota_status(UPGRADE_STATE_FAILED, UPGRADE_FAILED);
        } else {
#define PRODUCT_INFO_KEY         "product_infor"
            wd_common_delete(PRODUCT_INFO_KEY);
            PR_NOTICE("upgrade success!!!");
            tuya_send_ota_status(UPGRADE_STATE_SUCC, UPGRADE_FINISHED);
        }
    }
    return op_ret;
}
STATIC OPERATE_RET ty_uart_mcu_ota_end_status_cb(IN TY_OTA_END_STATUS_E status, IN UINT_T offset)
{
    OPERATE_RET op_ret = OPRT_OK;
    return op_ret;
}
STATIC OPERATE_RET tuya_upgrade_syn_send_ack_handle(IN CHAR_T *data, IN UINT_T datalen)
{
    PR_NOTICE("data0=%d len =%d", data[0], datalen);
    if (data[0]) {
        return OPRT_NOT_SUPPORTED;
    } else {
        return OPRT_OK;
    }
}

INT_T pre_gw_ug_proc(IN CONST FW_UG_S *fw)
{
    OPERATE_RET op_ret = OPRT_OK;
    UCHAR_T upgrade_send_data[2] = {0, 0};
    TI_UPGRD_STAT_S ret = TUS_DOWNLOAD_ERROR_UNKONW;

    if (NULL == fw) {
        PR_ERR("FW_UG is null!");
        return TUS_DOWNLOAD_ERROR_UNKONW;
    }
    tuya_iot_reset_upgrade_detect_timer(0x7fffffff);
    PR_NOTICE("pre_gw_ug_proc-------------- %d", fw->type);
    if (UPGRADE_TYPE_NORMAL == fw->type) {
        upgrade_send_data[0] = UPGRADE_RECEIVE;
    } else if (UPGRADE_TYPE_SILENT == fw->type) {
        upgrade_send_data[0] = UPGRADE_RECEIVE;
    } else {
        PR_ERR("UPGRADE_TYPE_error!!!");
        return TUS_DOWNLOAD_ERROR_UNKONW;
    }

    if (DEV_NM_ATH_SNGL == fw->tp) {
        upgrade_send_data[1] = OTA_WF;
        g_dev_ota_ctrl.ota_type = fw->tp;
    } else if (DEV_NM_NOT_ATH_SNGL == fw->tp) {
        upgrade_send_data[1] = OTA_MCU;
        g_dev_ota_ctrl.ota_type = fw->tp;
    } else {
        PR_ERR("DEV tp is error:%d", fw->tp);
        return TUS_DOWNLOAD_ERROR_UNKONW;
    }
    memset(g_dev_ota_ctrl.sw_ver, 0, SIZEOF(g_dev_ota_ctrl.sw_ver));
    strcpy(g_dev_ota_ctrl.sw_ver, fw->sw_ver);
    if (FALSE == g_dev_ota_ctrl.is_mcu_request_ota) {
        TY_OTA_SEND_SYN_CFG_S  syn_cfg;
        syn_cfg.p_name = AUTO_UPGRADE_NAME;
        syn_cfg.timerout_ms = 3000;
        syn_cfg.wait_cmd = AUTO_UPGRADE_CMD;
        syn_cfg.ack_cb = tuya_upgrade_syn_send_ack_handle;
        op_ret = tuya_ota_send_cmd(OTA_SEND_TYPE_SYN, AUTO_UPGRADE_CMD, upgrade_send_data, SIZEOF(upgrade_send_data), (PVOID_T)(&syn_cfg));
        tuya_low_power_time_set_and_start(LOW_POWER_UPDATE_TIME);
    }
    if (OPRT_OK == op_ret) {
        ret = TUS_RD;
    }
    PR_NOTICE("pre_gw_ug_proc ret-------------- %d %d", ret, g_dev_ota_ctrl.is_mcu_request_ota);
    sys_stop_timer(g_dev_ota_ctrl.query_gw_timeout);
    return ret;
}




STATIC VOID tuya_device_update_time_cb(UINT_T timerID, PVOID_T pTimerArg)
{
    INT_T ret = 1;
    tuya_send_ui_msg(UI_MSG_UPDATE_ONLY, &ret, sizeof(INT_T));
}
STATIC TIMER_ID device_update_timer_id = 0;
STATIC OPERATE_RET tuya_device_update_init_and_start(VOID)
{
    OPERATE_RET op_ret = OPRT_OK;
    if (0 == device_update_timer_id) {
        op_ret = sys_add_timer(tuya_device_update_time_cb, NULL, &device_update_timer_id);
        if (OPRT_OK != op_ret) {
            PR_ERR("sys_add_timer tuya_device_update_time_cb err:%d", op_ret);
            return op_ret;
        }
    }
    sys_start_timer(device_update_timer_id, 100, TIMER_ONCE);
    return op_ret;
}

STATIC INT_T event_process_cb(VOID *data)
{
    g_dev_ota_ctrl.ug_flag = true;
    tuya_send_ota_status(UPGRADE_STATE_RUNNING, UPGRADE_PROCESS);
    PR_NOTICE("event_process_cb----------");
    tuya_low_power_timer_stop();
    uvc_video_stop();
    tuya_lcd_back_light_power_ctr(true);
    tuya_lcd_ctrl_timer_off();
    tuya_device_update_init_and_start();
    return OPRT_OK;
}

STATIC INT_T event_failed_cb(VOID *data)
{
    tuya_send_ota_status(UPGRADE_STATE_FAILED, UPGRADE_FAILED);
    g_dev_ota_ctrl.ug_flag = false;
    PR_NOTICE("event_failed_cb----------");
    INT_T ret = 3;
    tuya_send_ui_msg(UI_MSG_UPDATE_ONLY, &ret, sizeof(INT_T));
    tuya_low_power_time_start_from_flash();
    return OPRT_OK;
}


STATIC VOID tuya_device_lp_time_cb(UINT_T timerID, PVOID_T pTimerArg)
{
    tuya_hal_system_reset();
}
STATIC TIMER_ID device_lp_timer_id = 0;
STATIC OPERATE_RET tuya_device_low_power_init_and_start(VOID)
{
    OPERATE_RET op_ret = OPRT_OK;
    if (0 == device_lp_timer_id) {
        op_ret = sys_add_timer(tuya_device_lp_time_cb, NULL, &device_lp_timer_id);
        if (OPRT_OK != op_ret) {
            PR_ERR("sys_add_timer tuya_device_entr_lp_time_cb err:%d", op_ret);
            return op_ret;
        }
    }
    sys_start_timer(device_lp_timer_id, 1000, TIMER_ONCE);
    return op_ret;
}
STATIC INT_T event_finished_cb(VOID *data)
{
    OPERATE_RET op_ret = OPRT_OK;
    g_dev_ota_ctrl.ug_flag = false;
    if (DEV_NM_NOT_ATH_SNGL == g_dev_ota_ctrl.ota_type) {
        op_ret = ty_uart_mcu_ota_finish_ok();
    } else {
        tuya_send_ota_status(UPGRADE_STATE_SUCC, UPGRADE_FINISHED);
    }
    PR_NOTICE("event_finished_cb-----------");
    INT_T ret = 2;
    tuya_send_ui_msg(UI_MSG_UPDATE_ONLY, &ret, sizeof(INT_T));
    tuya_device_low_power_init_and_start();
    return OPRT_OK;
}

BOOL_T get_ug_flag()
{
    return g_dev_ota_ctrl.ug_flag;
}


STATIC VOID query_gw_ug_timeout_cb(UINT_T timerID, PVOID_T pTimerArg)
{
    if (DEV_NM_ATH_SNGL == g_dev_ota_ctrl.ota_type) {
        tuya_request_set_upgrade(REQ_WIFI_OTA_CMD, UPGRADE_STATE_ALREADY_NEW);
    } else {
        tuya_request_set_upgrade(REQ_MCU_OTA_CMD, UPGRADE_STATE_ALREADY_NEW);
    }
    tuya_low_power_time_start_from_flash();

}


STATIC VOID send_ota_timeout_cb(UINT_T timerID, PVOID_T pTimerArg)
{
    PR_DEBUG("send_ota_timeout_cb POST_FAIL");
    tuya_svc_mcu_ota_wait_type_post(POST_FAIL);
    event_failed_cb(NULL);
}

OPERATE_RET tuya_ota_service_init(IN TY_OTA_SEND_FRAME_HANDLE_CB cb)
{
    OPERATE_RET op_ret = OPRT_OK;

    STATIC UCHAR_T init = 0;
    if (init) {
        return op_ret;
    }
    if (cb) {
        g_ota_send_cb = cb;
    } else {
        PR_ERR("cb is null");
        return OPRT_INVALID_PARM;
    }

    op_ret = sys_add_timer(query_gw_ug_timeout_cb, NULL, &g_dev_ota_ctrl.query_gw_timeout);
    if (op_ret != OPRT_OK) {
        PR_ERR("sys_add_timer query_prod_infor_tm_cb failed! op_ret:%d", op_ret);
        return op_ret;
    }

    op_ret = sys_add_timer(send_ota_timeout_cb, NULL, &g_dev_ota_ctrl.send_ota_timeout);
    if (op_ret != OPRT_OK) {
        PR_ERR("sys_add_timer query_prod_infor_tm_cb failed! op_ret:%d", op_ret);
        return op_ret;
    }
    g_dev_ota_ctrl.ug_state = UPGRADE_STATE_ALREADY_NEW;

    ty_subscribe_event(EVENT_OTA_PROCESS_NOTIFY, OTA_PROCESS_NOTIFY, event_process_cb, 0);
    ty_subscribe_event(EVENT_OTA_FAILED_NOTIFY, OTA_FAILED_NOTIFY, event_failed_cb, 0);
    ty_subscribe_event(EVENT_OTA_FINISHED_NOTIFY, OTA_FINISHED_NOTIFY, event_finished_cb, 0);
    op_ret = tuya_svc_mcu_ota_serve_init(g_ota_msg, TY_UART_MCU_OTA_LEN);
    if (OPRT_OK != op_ret) {
        PR_ERR("svc_mcu_ota_serve_init err:%d", op_ret);
        return op_ret;
    }

    init = 1;
    return op_ret;
}

OPERATE_RET tuya_mcu_ota_service_start(IN FW_UG_S *fw)
{
    sys_stop_timer(g_dev_ota_ctrl.query_gw_timeout);

    return tuya_svc_mcu_ota_serve_start(fw);
}

OPERATE_RET tuya_mcu_ota_post(IN TY_OTA_POST_RESULT_E result)
{
    return tuya_svc_mcu_ota_wait_type_post(result);
}

OPERATE_RET tuya_set_is_mcu_req_ota(BOOL_T flag)
{
    g_dev_ota_ctrl.is_mcu_request_ota = flag;
}

OPERATE_RET tuya_request_ota(IN UCHAR_T is_req_mcu_ota)
{
    OPERATE_RET op_ret = OPRT_OK;
    if (UPGRADE_STATE_DETECT == g_dev_ota_ctrl.ug_state || \
        UPGRADE_STATE_RUNNING == g_dev_ota_ctrl.ug_state) {
        PR_NOTICE("ug_state:%d", g_dev_ota_ctrl.ug_state);
        return OPRT_COM_ERROR;
    }
    sys_stop_timer(g_dev_ota_ctrl.query_gw_timeout);
    tuya_iot_reset_upgrade_detect_timer(1);
    if (is_req_mcu_ota) {
        g_dev_ota_ctrl.ota_type = DEV_NM_NOT_ATH_SNGL;
        tuya_request_set_upgrade(REQ_MCU_OTA_CMD, UPGRADE_STATE_DETECT);
    } else {
        g_dev_ota_ctrl.ota_type = DEV_NM_ATH_SNGL;
        tuya_request_set_upgrade(REQ_WIFI_OTA_CMD, UPGRADE_STATE_DETECT);
    }
    sys_start_timer(g_dev_ota_ctrl.query_gw_timeout, QUERY_UG_TIMEOUT, TIMER_ONCE);
    tuya_low_power_time_set_and_start(LOW_POWER_UPDATE_TIME);
    return op_ret;
}

