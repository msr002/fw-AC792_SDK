/***********************************************************
*  File: ty_uart_common_basic_service.c
*  Author: mjl
*  Date: 20210507
***********************************************************/
#include "wifi/wifi_connect.h"
#include "lcd_drive.h"
#include "string.h"

#include "tuya_fast_init.h"
#include "uni_log.h"
#include "tuya_cloud_types.h"
#include "tuya_cloud_com_defs.h"
#include "ty_cJSON.h"
#include "tuya_iot_wifi_api.h"
#include "svc_uart_queue.h"
#include "svc_uart_multi_thread.h"
#include "tuya_uart_public_recv_protocol.h"
#include "tuya_uart_public_send_protocol.h"
#include "tuya_uart_public_cmd_list.h"
#include "tuya_uart_common_basic_service.h"
#include "tuya_uart_public_iot.h"
#include "svc_lock_dp_report.h"
#include "uni_msg_queue.h"
#include "svc_lock_online_pw.h"
#include "svc_lock_offline_pw.h"
#include "svc_lock_dynamic_pw.h"
#include "tuya_ota.h"
#include "tuya_ipc_streamer.h"
#include "tuya_photo_and_stream.h"
#include "mqc_app.h"
#include "tuya_audio_source.h"
#include "tuya_device.h"
#include "tuya_low_power.h"
#include "tuya_video.h"
#include "ws_db_gw.h"
#include "tuya_driver.h"
#include "tuya_ui.h"
#include "tuya_fast_init.h"

#define USER_VERSION_LEN            16
#define FIRM_KEY_LEN                20

#define RESULT_SUCC              0x00
#define RESULT_FAILED            0x01

#define REPORT_SUCC              0x00
#define REPORT_NEED_WAIT         0x01
#define REPORT_FAILED            0x02

#define REPORT_DP_ID_ERR            0x03
#define REPORT_DP_TYPE_ERR            0x04

#define DEF_FRAME_BUF_SZ         300

#define ACTIVE_TIME_KEY          "active_time_key"
#define TI_GET_DP_CACHE_STATE    "tuya.device.dev.dp.get"
#define PRODUCT_INFO_KEY         "product_infor"

#define GET_BITMAP_PROT_LEN(max_len)      ((max_len) > 16 ? 4 : ((max_len)>8?2:1))

#define WF_ACTIVE_TIME_OUT   120

typedef UCHAR_T UART_WF_RESET_STATE_E;
#define WF_ST_LOCAL                0x00
#define WF_ST_REMOTE               0x01
#define WF_ST_REMOTE_FACTORY       0x02
#define WF_ST_DATA_RST             0x03

#define UART_SEND_TIME_OUT        1

typedef union {
    struct {
        UCHAR_T   photo_enable          : 1;
        UCHAR_T   trans_mode            : 1;
        UCHAR_T   operator              :1;
        UCHAR_T   reset_notice          : 1;
        UCHAR_T   upgrade               : 1;
        UCHAR_T   reserve               : 3;
    };
    UINT_T whole;
} DEV_ABILITY;

typedef struct {
    CHAR_T user_version[USER_VERSION_LEN];
    CHAR_T firm_key[FIRM_KEY_LEN];
    BOOL_T mcu_reset_flag;               //mcu重启标志
    BOOL_T init_flag;                	//设备初始化标志
    BOOL_T online_flag;              	//设备在线标志
    BOOL_T IsIndownload;              	//设备下载标志
    BOOL_T IsMcuUgReset;             	//设备升级MCU重启标志
    BOOL_T is_local_reset;              //是否本地重置
    GW_STATUS_E status;                      //工作状态
} MODULE_STATE_S;

//MCU信息
typedef struct {
    CHAR_T mcu_sw_ver[SW_VER_LEN + 1];               //版本信息
    CHAR_T product_key[PRODUCT_KEY_LEN + 1];         //产品key
    GW_WF_START_MODE start_mode;                     //wifi初始化模式
    DEV_ABILITY dev_ability;                         //设备能力
} MCU_INFO_S;

typedef struct {
    TY_RECV_HANDLE recv_handle;
    TY_SEND_HANDLE send_handle;
    TM_MSG_S      *send_record_tm_msg;
    TM_MSG_S      *get_time_tm_msg;
    TM_MSG_S      *get_time_gltm_msg;
    TIMER_ID       rp_timer_id;
    TIMER_ID       voice_test_timer_id;
    BOOL_T         is_init;
    CHAR_T         local_reset_type;
} TY_UART_CTRL_S;

#pragma pack(1)
typedef struct {
    UCHAR_T			dpid;	/* tuya datapoint id */
    UCHAR_T	        type;	/* tuya datapoint type */
    WORD_T			len;	/* tuya datapoint len */
    UCHAR_T			data[0];	/* tuya datapoint data */
} TY_DP_DATA_S;
#pragma pack()


typedef struct {
    UINT_T  type;
    UINT_T  pack_len;
} TY_UART_MCU_LEN_S;

STATIC TY_UART_MCU_LEN_S g_mcu_ota_msg[] = {
    {0, 256},
    {1, 512},
    {2, 1024},
};

STATIC MODULE_STATE_S module_state = {0};
STATIC MCU_INFO_S mcu_info = {0};
STATIC BASIC_SERVICE_INFO_S main_info  = {0};
STATIC TY_UART_CTRL_S uart_ctrl;
STATIC UCHAR_T wifi_state = 0x07;

VOID __wf_net_change(IN CONST GW_WIFI_NW_STAT_E stat);
STATIC VOID __dev_dp_recv_cb(IN CONST TY_DATAPOINT_DATA_S *datapoint);
STATIC VOID send_record_sync_cb(struct s_tm_msg *tm_msg);
STATIC VOID get_time_cb(struct s_tm_msg *tm_msg);
STATIC VOID get_gltime_cb(struct s_tm_msg *tm_msg);
VOID set_active_time(UINT_T time);
OPERATE_RET product_infor_delete(VOID);
OPERATE_RET delete_active_time(VOID);

STATIC TM_MSG_ENTRY_S tim_msg_tb[] = {
    {&(uart_ctrl.send_record_tm_msg), send_record_sync_cb},
    {&(uart_ctrl.get_time_tm_msg), get_time_cb},
    {&(uart_ctrl.get_time_gltm_msg), get_gltime_cb},
};

VOID_T ty_uart_send_data_direct(UCHAR_T cmd, UCHAR_T *data, UINT_T len)
{
    ty_uart_protocol_send_direct(uart_ctrl.send_handle, cmd, data, len);
}

STATIC BOOL_T __net_conn_ok(GW_WIFI_NW_STAT_E state)
{
    if ((state == STAT_STA_CONN) || (state == STAT_CLOUD_CONN)  || (state == STAT_AP_CLOUD_CONN)
        || (state == STAT_REG_FAIL)  || (state == STAT_OFFLINE)  || (state == STAT_MQTT_ONLINE)
        || (state == STAT_MQTT_OFFLINE) || (state == STAT_AP_STA_CONN)) {
        return TRUE;
    }
    return FALSE;
}
VOID send_wf_resrt_state(GW_RESET_TYPE_E type)
{
    UART_WF_RESET_STATE_E send_st;
    switch (type) {
    case GW_LOCAL_RESET_FACTORY:
    case GW_LOCAL_UNACTIVE:
        send_st = WF_ST_LOCAL;
        break;
    case GW_REMOTE_UNACTIVE:
        send_st = WF_ST_REMOTE;
        break;
    case GW_REMOTE_RESET_FACTORY:
        send_st = WF_ST_REMOTE_FACTORY;
        break;
    case GW_RESET_DATA_FACTORY:
        send_st = WF_ST_DATA_RST;
        break;
    default:
        PR_ERR("stat:%d is err !", type);
        return;
    }
    TY_SEND_SYN_CFG_S syn_cfg;
    syn_cfg.p_name = MOU_RESET_NAME;
    syn_cfg.timerout_ms = 500;
    syn_cfg.wait_cmd = MOUDULE_RESET_CMD;
    syn_cfg.ack_cb = NULL;
    ty_uart_protocol_send_syn(uart_ctrl.send_handle, MOUDULE_RESET_CMD, &send_st, 1, &syn_cfg);
}

STATIC VOID reset_wifi_store_info(VOID)
{
    struct wifi_mode_info  wifi_info;
    CHAR_T jl_on_ssid[32 + 1];
    INT_T num = 0;
    wifi_info.mode = STA_MODE;
    INT_T ret;

    ret = wifi_get_mode_stored_info(&wifi_info);
    PR_NOTICE("wifi_get_mode_stored_info : %d  ", ret);
    if (!ret) {
        PR_NOTICE("wifi_get_mode_stored_info : ssid %s  ", wifi_info.ssid);
        num = strlen(wifi_info.ssid);
        num = (num > 32) ? 32 : num;
        memset(jl_on_ssid, 0, 33);
        memcpy(jl_on_ssid, wifi_info.ssid, num);
        wifi_del_stored_sta_info(jl_on_ssid);
    }
    extern INT_T tuya_set_wifi_sta_store(BOOL_T status) ;
    tuya_set_wifi_sta_store(FALSE);
}

// 各种重置的回调接口
STATIC VOID __gw_reset_cb(GW_RESET_TYPE_E type)
{
    if (mcu_info.dev_ability.reset_notice) {
        send_wf_resrt_state(type);
        tuya_hal_system_sleep(10);
    }
    switch (uart_ctrl.local_reset_type) {
    case WIFI_RESET_CMD:
        ty_uart_protocol_send_direct(uart_ctrl.send_handle, WIFI_RESET_CMD, NULL, 0);
        break;
    case WIFI_RESET_SEL_CMD:
        ty_uart_protocol_send_direct(uart_ctrl.send_handle, WIFI_RESET_SEL_CMD, NULL, 0);
        break;
    case RESET_FACTORY_CMD:
        CHAR_T ret[2] = {0x0a, 0x00};
        ty_uart_protocol_send_direct(uart_ctrl.send_handle, MOUDULE_EXPAND_CMD, ret, SIZEOF(ret));
        break;
    }
    tuya_hal_system_sleep(50);

    extern OPERATE_RET ty_uart_delete_baud(VOID);
    ty_uart_delete_baud();
    product_infor_delete();
    stream_infor_delete();
    tuya_svc_lock_offline_pw_deinit();
    tuya_svc_lock_clr_flash_record();
    delete_active_time();
    tuya_lowpower_param_delete();
    tuya_fast_param_delete(UF_TY_CFG_PARAM_E);
    wd_mf_test_close_if_write(FALSE);
    if (GW_RESET_DATA_FACTORY != type) {
        reset_wifi_store_info();
        INT_T time_zone_seconds = 8 * 60 * 60;
        tuya_rtc_control(TUYA_DRV_CUSTOM_CMD, &time_zone_seconds); //设置默认时区，以s为单位
    }
    OPERATE_RET op_ret = OPRT_OK;
    if (FALSE == module_state.is_local_reset && GW_RESET_DATA_FACTORY != type) {
        PR_NOTICE("enter lowpower");
        GW_CNTL_S *gw_cntl = get_gw_cntl();
        gw_cntl->gw_wsm.nc_tp = GWNS_LOWPOWER;
        op_ret = wd_gw_wsm_write(&(gw_cntl->gw_wsm));
        if (OPRT_OK != op_ret) {
            PR_ERR("wd_gw_wsm_write failed! op_ret:%d", op_ret);
        }
    } else {
        if (module_state.is_local_reset) {
            PR_NOTICE("enter AP cfg");
            GW_CNTL_S *gw_cntl = get_gw_cntl();
            GW_WORK_STAT_MAG_S wsm;
            op_ret = wd_gw_wsm_read(&wsm);
            if ((op_ret == OPRT_OK) && (wsm.nc_tp != GWNS_UNCFG_AP)) {
                PR_NOTICE("wsm.nc_tp %d", wsm.nc_tp);
                wsm.nc_tp = GWNS_UNCFG_AP;
                op_ret = wd_gw_wsm_write(&wsm);
                if (OPRT_OK != op_ret) {
                    PR_ERR("wd_gw_wsm_write failed! op_ret:%d", op_ret);
                }
            }

        }

    }

    uart_ctrl.local_reset_type = 0;
    tuya_low_power_time_set_and_start(0);
    PR_NOTICE("__gw_reset_cb type %d", type);
    return ;
}

UINT_T get_active_time(VOID)
{
    OPERATE_RET op_ret;
    UCHAR_T *buff = NULL;
    UINT_T time, read_len;
    op_ret = wd_common_read(ACTIVE_TIME_KEY, &buff, &read_len);
    if (OPRT_OK != op_ret) {
        PR_DEBUG("msf_get_single err:%02x", op_ret);
        return 0;
    }
    PR_NOTICE("time:%s", buff);
    time = atoi(buff);
    Free(buff);
    return time;
}
OPERATE_RET delete_active_time(VOID)
{
    OPERATE_RET op_ret;
    op_ret = wd_common_delete(ACTIVE_TIME_KEY);
    if (OPRT_OK != op_ret) {
        PR_ERR("wd_common_delete err:%d", op_ret);
    }
    return op_ret;
}
VOID set_active_time(UINT_T time)
{
    OPERATE_RET op_ret;
    UCHAR_T buff[20] = {0};

    snprintf(buff, SIZEOF(buff), "%d", time);

    op_ret = wd_common_write(ACTIVE_TIME_KEY, buff, SIZEOF(buff));
    if (OPRT_OK != op_ret) {
        PR_ERR("set_active_time err:%d", op_ret);
    }
}
STATIC VOID wf_active_syn(VOID)
{
#define TIME_POSX_2016    1451577600
    TIME_T curPosix = uni_time_get_posix();
    if (curPosix < TIME_POSX_2016) {
        return;
    }
    set_active_time(curPosix);

    INT_T time_zone_seconds;
    if (OPRT_OK == uni_get_time_zone_seconds(&time_zone_seconds)) {
        tuya_rtc_control(TUYA_DRV_CUSTOM_CMD, &time_zone_seconds); // 激活回调，可以拿到配网时区信息，设置时区信息，以s为单位
    }

}
STATIC VOID __gw_status_cb(IN CONST GW_STATUS_E status)
{
    if (GW_ACTIVED == status) {
        wf_active_syn();
        tuya_low_power_time_set_and_start(LOW_POWER_FIRST_ACTIVE_TIME);
        ty_stream_actice_force_uplord();
    }
    if (GW_NORMAL == status) {
        bt_ble_not_allowed_init();
        tuya_ble_set_serv_switch(FALSE);;
    }
    module_state.status = status;
    PR_NOTICE("__gw_status_cb %d", status);
    return ;
}

STATIC OPERATE_RET __gw_ug_cb(IN CONST FW_UG_S *fw)
{
    OPERATE_RET op_ret = OPRT_OK;
    PR_NOTICE("gw_ug_cb Rev GW Upgrade Info");
    PR_NOTICE("fw->fw_url:%s", fw->fw_url);
    PR_NOTICE("fw->tp:%d fw->type:%d", fw->tp, fw->type);
    PR_NOTICE("fw->sw_ver:%s", fw->sw_ver);
    PR_DEBUG("fw->file_size:%d", fw->file_size);
    op_ret = tuya_mcu_ota_service_start(fw);
    if (OPRT_OK != op_ret) {
        PR_ERR("tuya_svc_mcu_ota_serve_start err:%d", op_ret);
    }
    return op_ret;
}

STATIC INT_T __pre_gw_ug_cb(IN CONST FW_UG_S *fw)
{
    INT_T op_ret = OPRT_OK;
    PR_NOTICE("Rev GW Upgrade Info");
    PR_NOTICE("fw->fw_url:%s", fw->fw_url);
    PR_NOTICE("fw->tp:%d fw->type:%d", fw->tp, fw->type);
    PR_NOTICE("fw->sw_ver:%s", fw->sw_ver);
    PR_NOTICE("fw->file_size:%d", fw->file_size);
    op_ret = pre_gw_ug_proc(fw);
    return op_ret;
}



/***********************************************************
*  Function:get_dev_info
*  Input: none
*  Output: none
*  Return: none
*  Note: 获取产品信息
***********************************************************/
STATIC OPERATE_RET __get_dev_info(IN UCHAR_T *pdata, IN UINT_T len)
{
    OPERATE_RET op_ret = OPRT_OK;
    PCHAR_T pstr = NULL, ver_str = NULL, product_key = NULL;
    ty_cJSON *root = NULL, *item = NULL;
    if (NULL == pdata || 0 == len) {
        return OPRT_INVALID_PARM;
    }
    PR_DEBUG("prod:%s", pdata);
    root = ty_cJSON_Parse(pdata);
    if (NULL == root) {
        PR_ERR("pdata:%s", pstr);
        op_ret = OPRT_CJSON_PARSE_ERR;
        return op_ret;
    }

    item = ty_cJSON_GetObjectItem(root, "p");
    if (NULL == item) {
        PR_ERR("get item product_id is failed");
        op_ret = OPRT_CJSON_PARSE_ERR;
        goto PROCE_END;
    } else {
        strcpy(mcu_info.product_key, item->valuestring);
    }

    item = ty_cJSON_GetObjectItem(root, "v");
    if (NULL == item) {
        PR_ERR("cj get item ver_str is failed");
        op_ret = OPRT_CJSON_PARSE_ERR;
        goto PROCE_END;
    }  else {
        strcpy(mcu_info.mcu_sw_ver, item->valuestring);
    }

    mcu_info.start_mode = WF_START_SMART_FIRST;
    item = ty_cJSON_GetObjectItem(root, "n");
    if (NULL == item) {
        mcu_info.start_mode = WF_START_SMART_FIRST;
    } else {
        if (0 == item->valueint) {
            mcu_info.start_mode = WF_START_SMART_FIRST;
        } else if (1 == item->valueint) {
            mcu_info.start_mode = WF_START_AP_ONLY;
        } else if (2 == item->valueint) {
            mcu_info.start_mode = WF_START_SMART_AP_CONCURRENT;
        }
    }

    item = ty_cJSON_GetObjectItem(root, "cap");
    if (NULL == item) {
        mcu_info.dev_ability.whole = 0;
    } else {
        mcu_info.dev_ability.whole = (UINT_T)item->valueint;
    }

PROCE_END:
    ty_cJSON_Delete(root);
    return op_ret;
}

STATIC OPERATE_RET product_infor_save(UCHAR_T *pdata, INT_T len)
{
    OPERATE_RET op_ret = OPRT_OK;
    BYTE_T *buf = pdata;

    PR_NOTICE("save product infor:%s", buf);

    op_ret = wd_common_write(PRODUCT_INFO_KEY, buf, len);
    if (OPRT_OK != op_ret) {
        PR_ERR("wd_common_write product_infor err:%d", op_ret);
    }

    PR_NOTICE("write product infor:%d", op_ret);

    return op_ret;
}

OPERATE_RET product_infor_delete(VOID)
{
    OPERATE_RET op_ret = OPRT_OK;
    op_ret = wd_common_delete(PRODUCT_INFO_KEY);
    if (OPRT_OK != op_ret) {
        PR_ERR("product_infor_delete product_infor err:%d", op_ret);
    }
    return op_ret;
}

BOOL_T product_infor_load(VOID)
{
    OPERATE_RET op_ret = OPRT_OK;
    BOOL_T result = FALSE;
    BYTE_T *infor = NULL;
    UINT_T infor_len = 0;

    op_ret = wd_common_read(PRODUCT_INFO_KEY, &infor, &infor_len);
    if (OPRT_OK != op_ret) {
        PR_ERR("wd_common_read infor err:%0d", op_ret);
        result = FALSE;
    } else {
        PR_NOTICE("load product infor : %s", infor);
        op_ret = __get_dev_info(infor, infor_len);
        if (op_ret != OPRT_OK) {
            PR_ERR("proc_product_infor error!");
            result = FALSE;
        } else {
            result = TRUE;
        }
    }
    if (infor != NULL) {
        Free(infor);
        infor = NULL;
    }
    return result;
}
OPERATE_RET tuya_prod_info_cloud_handle(VOID)
{
    OPERATE_RET op_ret = OPRT_OK;
    if (get_fs_is_update()) {
        PR_DEBUG("get_fs_is_update true!!!");
        return op_ret;
    }
    if (FALSE == module_state.init_flag) {
        TY_IOT_INFO_S  iot_info;
        strcpy(iot_info.firmware_key, main_info.firmware_key);
        strcpy(iot_info.firmware_version, main_info.firmware_version);
        strcpy(iot_info.product_key, mcu_info.product_key);
        strcpy(iot_info.app_sw_version, mcu_info.mcu_sw_ver);
        iot_info.cfg_mode = GWCM_LOW_POWER;
        iot_info.start_mode = WF_START_AP_ONLY;
        TY_IOT_CB_S ty_iot_cb;
        ty_iot_cb.gw_reset_cb = __gw_reset_cb;
        ty_iot_cb.gw_status_cb = __gw_status_cb;
        ty_iot_cb.gw_ug_cb = __gw_ug_cb;
        ty_iot_cb.ty_dev_dp_recv_cb = __dev_dp_recv_cb;
        ty_iot_cb.wf_nw_stat_cb = __wf_net_change;
        ty_iot_cb.pre_gw_ug_cb = __pre_gw_ug_cb;
        ty_photo_cloudp2p_iot_init();
        set_gw_active_timeout(WF_ACTIVE_TIME_OUT);
        tuya_uart_cloud_init(&iot_info, ty_iot_cb);
        tuya_iot_upload_rst_log_set(FALSE);
        if (mcu_info.dev_ability.upgrade) {
            tuya_set_is_mcu_req_ota(FALSE);
        } else {
            tuya_set_is_mcu_req_ota(TRUE);
        }
        PR_DEBUG("mcu_info.dev_ability.upgrade = %d", mcu_info.dev_ability.upgrade);
        module_state.init_flag = TRUE;
    } else {
        op_ret = tuya_svc_mcu_ota_ver_report_syn(mcu_info.mcu_sw_ver);
        if (OPRT_OK != op_ret) {
            PR_ERR("tuya_svc_mcu_ota_ver_report_syn err:%d", op_ret);
        }
    }
    return op_ret;
}

STATIC OPERATE_RET ty_uart_prod_info_handle(IN CHAR_T *p_name, IN TY_CMD_S *p_service_data)
{
    if (OPRT_OK == __get_dev_info(p_service_data->data, p_service_data->datalen)) {
        tuya_prod_info_cloud_handle();
#if defined(USE_TY_PID_MEMORY) && (USE_TY_PID_MEMORY == 1)
        if (OPRT_OK != product_infor_save(p_service_data->data, p_service_data->datalen)) {
            PR_ERR("product_infor_save error!");
        }
#endif
    }
    return OPRT_OK;
}

STATIC VOID tuya_device_record_dp_report(UINT_T timerID, PVOID_T pTimerArg)
{
    OPERATE_RET op_ret = OPRT_OK;
    PR_DEBUG("********************tuya_device_record_dp_report timer*********************");
    cmmod_start_tm_msg(uart_ctrl.send_record_tm_msg, 1000, TIMER_ONCE);
    return ;
}


STATIC VOID tuya_device_voice_test(UINT_T timerID, PVOID_T pTimerArg)
{
    OPERATE_RET op_ret = OPRT_OK;

    STATIC INT_T test_num = 0;
    PR_DEBUG("**************tuya_device_voice_test timer test_num=%d*************", test_num);

    tuya_play_local_audio(test_num);

    if (test_num) {
        test_num = 0;
    } else {
        test_num = 1;
    }
    sys_start_timer(uart_ctrl.voice_test_timer_id, 5000, TIMER_ONCE);
    return ;
}

VOID tuya_set_wifi_status(UCHAR_T state)
{
    wifi_state = state;
}

UCHAR_T tuya_get_wifi_status(VOID)
{
    return wifi_state;
}

BOOL_T tuya_wifi_is_in_net_cfg(VOID)
{
    GW_WIFI_NW_STAT_E conn_state;
    BOOL_T tuya_is_net_cfg = FALSE;
    get_wf_gw_nw_status(&conn_state);
    if ((conn_state == STAT_UNPROVISION) || (conn_state == STAT_AP_STA_UNCFG) || (conn_state == STAT_UNPROVISION_AP_STA_UNCFG)) {
        tuya_is_net_cfg = TRUE;
    }
    return tuya_is_net_cfg;
}

STATIC VOID ty_rssi_report(VOID)
{
    ty_cJSON *p_runstat_json = ty_cJSON_CreateObject();
    SCHAR_T rssi = 0;
    wf_station_get_conn_ap_rssi(&rssi);
    ty_cJSON_AddNumberToObject(p_runstat_json, "rssi", rssi);

    CHAR_T *tmp = ty_cJSON_PrintUnformatted(p_runstat_json);
    ty_cJSON_Delete(p_runstat_json);
    tuya_svc_online_log_upload_runstat(tmp);
    PR_DEBUG("health runtime report:%s", tmp);
    Free(tmp);
    return;
}

VOID __wf_net_change(IN CONST GW_WIFI_NW_STAT_E conn_state)
{
    OPERATE_RET op_ret = OPRT_OK;
    STATIC BOOL_T is_connect_cloud = FALSE;
    STATIC BOOL_T is_net_cfg = FALSE;
    switch (conn_state) {
    case STAT_UNPROVISION: {
        wifi_state = 0;
    }
    break;
    case STAT_AP_STA_UNCFG: {
        wifi_state = 1;
    }
    break;
    case STAT_AP_STA_DISC:
    case STAT_STA_DISC: {
        wifi_state = 2;
        if (is_connect_cloud) {
            is_connect_cloud = FALSE;
        }
    }
    break;
    case STAT_AP_STA_CONN:
    case STAT_STA_CONN: {
        wifi_state = 3;
    }
    break;
    case STAT_AP_CLOUD_CONN:
    case STAT_CLOUD_CONN: {
        wifi_state = 4;
        is_connect_cloud = TRUE;
        sys_start_timer(uart_ctrl.rp_timer_id, 500, TIMER_ONCE);
        STATIC BOOL_T ug_flag = FALSE;
        if (!ug_flag) {
            ty_rssi_report();
            tuya_iot_reset_upgrade_detect_timer(0x7fffffff);
            ug_flag = TRUE;
            ty_stream_init();
#ifdef CONFIG_IPERF_ENABLE
            //网络测试工具，使用iperf
            extern void iperf_test(void);
            iperf_test();
#endif

        }
        tuya_low_power_time_start_from_flash();
        if (FALSE == wd_mf_test_close_if_read()) {
            wd_mf_test_close_if_write(TRUE);
        }
    }
    break;
    case STAT_LOW_POWER: {
        wifi_state = 5;
    }
    break;
    default:
        return;

    }
    PR_NOTICE("wifi status is :%d %d", conn_state, wifi_state);
    if ((conn_state == STAT_UNPROVISION) || (conn_state == STAT_AP_STA_UNCFG) || (conn_state == STAT_UNPROVISION_AP_STA_UNCFG)) {
        tuya_low_power_time_set_and_start(LOW_POWER_NET_CFG_TIME);
        is_net_cfg = TRUE;
        tuya_qrcode_task_creat();
    } else {
        if (is_net_cfg) {
            if (wifi_state == 4) {
                tuya_low_power_time_start_from_flash();
                is_net_cfg = FALSE;
            } else {
                tuya_low_power_time_set_and_start(LOW_POWER_NET_CFG_TIME);
            }
        } else {
            tuya_low_power_time_set_and_start(0);
            if (wifi_state == 3 || wifi_state == 4) {
                int timestamp;
                tuya_rtc_time_get(&timestamp);
                uni_time_set_posix(timestamp, 0);
                PR_NOTICE("station connect timestamp=%d", timestamp);
            }
        }
    }
    //op_ret = ty_uart_protocol_in_queue(uart_ctrl.send_handle,WIFI_STATE_CMD,&wifi_state,UART_SEND_TIME_OUT,WIFI_STATE_STRING_NAME);
    op_ret = ty_uart_protocol_send_direct(uart_ctrl.send_handle, WIFI_STATE_CMD, &wifi_state, 1);
    if (OPRT_OK != op_ret) {
        PR_ERR("ty_uart_protocol_in_queue err:%d", op_ret);
    }
    return;
}

/**
 * tuya dp data processing.
 * @param  obj_dp   datapoint
 * @param  send_data   send_data
 * @return send data len
 */
STATIC UINT_T __ty_recev_dp_data_proc(IN TY_DATAPOINT_DATA_S *obj_dp, OUT CHAR_T *send_data)
{
    WORD_T  dp_data_len;
    UINT_T send_len = 0;

    switch (obj_dp->type) {
    case DP_TYPE_VALUE: {
        UINT_T val_data ;
        memcpy(&val_data, obj_dp->data, obj_dp->len);
        val_data = DWORD_SWAP(val_data);
        memcpy(send_data + 4, &val_data, obj_dp->len);
    }
    break;
    case DP_TYPE_BITMAP:
        if (obj_dp->len == 1) {
            send_data[4] = obj_dp->data[0];
        } else if (obj_dp->len == 2) {
            WORD_T bit;
            memcpy(&bit, obj_dp->data, obj_dp->len);
            bit = WORD_SWAP(bit);
            memcpy(send_data + 4, &bit, obj_dp->len);
        } else if (obj_dp->len == 4) {
            DWORD_T bit;
            memcpy(&bit, obj_dp->data, obj_dp->len);
            bit = DWORD_SWAP(bit);
            memcpy(send_data + 4, &bit, obj_dp->len);
        } else {
            PR_ERR("bit maplen err");
        }
        break;
    case DP_TYPE_RAW:
    case DP_TYPE_BOOL:
    case DP_TYPE_STRING:
    case DP_TYPE_ENUM:
        memcpy(send_data + 4, obj_dp->data, obj_dp->len);
        break;
    default:
        PR_ERR("unkown dp type");
        return send_len;
    }
    send_data[0] = obj_dp->dpid;
    send_data[1] = obj_dp->type;
    dp_data_len = obj_dp->len;
    dp_data_len = WORD_SWAP(dp_data_len);
    memcpy(send_data + 2, &dp_data_len, sizeof(WORD_T));
    send_len = obj_dp->len + 4;
    return send_len;
}

STATIC VOID __dev_dp_recv_cb(IN CONST TY_DATAPOINT_DATA_S *datapoint)
{
    PR_DEBUG("__dev_dp_recv_cb id %d type %d len %d", datapoint->dpid, datapoint->type, datapoint->len);
    UINT_T send_data_len = 0;
    CHAR_T *send_data = Malloc(4 + datapoint->len);
    if (NULL == send_data) {
        return;
    }
    send_data_len = __ty_recev_dp_data_proc(datapoint, send_data);
    if (send_data_len) {
        ty_uart_protocol_send_direct(uart_ctrl.send_handle, DATA_CTRL_CMD, send_data, send_data_len);
    }
    Free(send_data);
    tuya_low_power_time_set_and_start(0);
    return;
}

STATIC OPERATE_RET ty_uart_dp_download_handle(IN CHAR_T *p_name, IN TY_CMD_S *p_service_data)
{
    OPERATE_RET op_ret = OPRT_OK;
    PR_DEBUG("mcu receve dp control data");
    return op_ret;
}

STATIC OPERATE_RET __network_link_judge(TY_WIFI_UP_TYPE_E up_type)
{
    GW_WIFI_NW_STAT_E cur_nw_stat;
    get_wf_gw_nw_status(&cur_nw_stat);
    if ((cur_nw_stat < STAT_STA_CONN) && (cur_nw_stat != STAT_AP_STA_CONN)\
        || (cur_nw_stat == STAT_UNPROVISION_AP_STA_UNCFG)) {
        PR_NOTICE("wifi ble mode not config data not to send fail:%d", cur_nw_stat);
        return OPRT_NETWORK_ERROR;
    }
    if (WIFI_DATA_SYNC_UP == up_type) {
        GW_NW_STAT_T net_sta = get_gw_nw_status();
        if (net_sta != GNS_WAN_VALID) {
            PR_NOTICE("mqtt connect sever is fail");
            return OPRT_NETWORK_ERROR;
        }
    }
    if (!module_state.init_flag) {
        return OPRT_COM_ERROR;
    }

    return OPRT_OK;
}

STATIC UINT_T get_obj_dp_num(UCHAR_T *pdata, INT_T len)
{
    UINT_T offset = 0, num = 0;
    TY_DP_DATA_S *dp_data;

    if (NULL == pdata) {
        PR_ERR("pd is null");
        return 0;
    }

    while (len > SIZEOF(TY_DP_DATA_S) + offset) {
        dp_data = (TY_DP_DATA_S *)(pdata + offset);
        offset += (WORD_SWAP(dp_data->len) + SIZEOF(TY_DP_DATA_S));
        num++;
    }

    return num;
}

STATIC VOID_T __free_obj_dp_data(TY_LOCK_DP_S *dp_obj_data, UINT_T obj_dp_cnt)
{
    UINT_T i;
    TY_LOCK_DP_S *tmp;
    if (NULL == dp_obj_data) {
        return;
    }
    for (i = 0; i < obj_dp_cnt; i++) {
        tmp = dp_obj_data + i;
        Free(tmp->data);
    }
    if (dp_obj_data) {
        Free(dp_obj_data);
    }
}

STATIC OPERATE_RET __ty_uart_recevie_data_proc(IN CHAR_T *receve_data, IN UINT_T data_len, OUT TY_LOCK_DP_S **lock_dp, OUT UINT_T *lock_dp_num)
{
    UINT_T obj_num = 0;
    TY_LOCK_DP_S *obj_dp = NULL;
    TY_DP_DATA_S *data_dp = NULL;
    UCHAR_T  *one_dp_data = NULL;
    UINT_T one_dp_len = 0;
    UINT_T offset = 0;
    OPERATE_RET op_ret = OPRT_OK;
    obj_num = get_obj_dp_num(receve_data, data_len);
    if (obj_num) {
        obj_dp = (TY_LOCK_DP_S *)Malloc(obj_num * SIZEOF(TY_LOCK_DP_S));
        if (NULL == obj_dp) {
            PR_ERR("malloc failed!");
            return OPRT_MALLOC_FAILED;
        }
        memset(obj_dp, 0x00, obj_num * SIZEOF(TY_OBJ_DP_S));
    } else {
        *lock_dp = NULL;
        *lock_dp_num = 0;
        return OPRT_INVALID_PARM;
    }
    *lock_dp = obj_dp;
    *lock_dp_num = obj_num;
    PR_DEBUG("obj_dp=0x%x obj_num=%d ", obj_dp, obj_num);
    obj_num = 0;
    offset = 0;
    while (data_len > SIZEOF(TY_DP_DATA_S) + offset) {
        data_dp = (TY_DP_DATA_S *)(receve_data + offset);
        one_dp_len = WORD_SWAP(data_dp->len);
        PR_DEBUG("data_len =%d one_dp_len=%d offset=%d", data_len, one_dp_len, offset);
        if (one_dp_len > data_len - offset - SIZEOF(TY_DP_DATA_S)) {
            return OPRT_NOT_SUPPORTED;
        }
        one_dp_data = Malloc(one_dp_len);
        if (NULL == one_dp_data) {
            goto PROCE_END;
        }
        switch (data_dp->type) {
        case DP_TYPE_VALUE: {
            INT_T val_data;
            memcpy(&val_data, data_dp->data, one_dp_len);
            val_data = DWORD_SWAP(val_data);
            memcpy(one_dp_data, &val_data, one_dp_len);
        }
        break;
        case DP_TYPE_BITMAP:
            if (one_dp_len == 1) {
                memcpy(one_dp_data, data_dp->data, one_dp_len);
            } else if (one_dp_len == 2) {
                WORD_T bit;
                memcpy(&bit, data_dp->data, one_dp_len);
                bit = DWORD_SWAP(bit);
                memcpy(one_dp_data, &bit, one_dp_len);
            } else if (one_dp_len == 4) {
                DWORD_T bit;
                memcpy(&bit, data_dp->data, one_dp_len);
                bit = DWORD_SWAP(bit);
                memcpy(one_dp_data, &bit, one_dp_len);
            } else {
                PR_ERR("bit maplen err");
                goto PROCE_END;
            }
            break;
        case DP_TYPE_RAW:
        case DP_TYPE_BOOL:
        case DP_TYPE_STRING:
        case DP_TYPE_ENUM:
            memcpy(one_dp_data, data_dp->data, one_dp_len);
            break;
        default:
            PR_ERR("unkown dp type");
            goto PROCE_END;
        }

        obj_dp[obj_num].dpid = data_dp->dpid;
        obj_dp[obj_num].type = data_dp->type;
        obj_dp[obj_num].data_len = one_dp_len;
        obj_dp[obj_num].data = one_dp_data;
        offset += (one_dp_len + SIZEOF(TY_DP_DATA_S));
        if (data_len < offset) {
            goto PROCE_END;
        }
        obj_num++;
    }
    return op_ret;
PROCE_END:
    __free_obj_dp_data(obj_dp, obj_num);
    *lock_dp = NULL;
    *lock_dp_num = 0;
    op_ret = OPRT_COM_ERROR;
    return op_ret;
}

STATIC OPERATE_RET ty_uart_dp_upload_handle(IN CHAR_T *p_name, IN TY_CMD_S *p_service_data)
{
    OPERATE_RET op_ret = OPRT_OK;
    UCHAR_T result = RESULT_SUCC;
    op_ret = __network_link_judge(WIFI_DATA_ASYNC_UP);
    if (op_ret != OPRT_OK) {
        PR_ERR("data_upload_async_proc error.");
        result = RESULT_FAILED;
        goto PROC_ERR;
    }
    TY_LOCK_DP_S *lock_dp = NULL;
    UINT_T lock_dp_num = 0;
    op_ret = __ty_uart_recevie_data_proc(p_service_data->data, p_service_data->datalen, &lock_dp, &lock_dp_num);
    if (op_ret != OPRT_OK) {
        PR_ERR("__ty_recevie_data_proc error.");
        result = RESULT_FAILED;
        goto PROC_ERR;
    }
    op_ret = tuya_svc_lock_dp_report_syn(lock_dp, lock_dp_num, NULL, 5);
    if (op_ret != OPRT_OK) {
        PR_ERR("__ty_uplord_data_proc error.");
        if (OPRT_SVC_DP_ID_NOT_FOUND == op_ret) {
            result = REPORT_DP_ID_ERR;
        } else if (OPRT_SVC_DP_TP_NOT_MATCH == op_ret) {
            result = REPORT_DP_TYPE_ERR;
        } else {
            result = RESULT_FAILED;
        }
        __free_obj_dp_data(lock_dp, lock_dp_num);
        goto PROC_ERR;
    }
    __free_obj_dp_data(lock_dp, lock_dp_num);
    result = RESULT_SUCC;
PROC_ERR:
    ty_uart_protocol_send_direct(uart_ctrl.send_handle, DATA_RPT_CMD, &result, 1);
    return op_ret;
}

STATIC VOID send_record_sync_cb(struct s_tm_msg *tm_msg)
{
    OPERATE_RET op_ret = OPRT_OK;
    UCHAR_T result = RESULT_SUCC;
    PR_DEBUG("***************send_record_sync_cb********************");
    if (tuya_svc_lock_get_flash_record_num()) {
        op_ret = tuya_svc_lock_dp_report_one_flash_record_syn(3);
        if (op_ret != OPRT_OK) {
            result = REPORT_FAILED;
            ty_uart_protocol_send_direct(uart_ctrl.send_handle, DATA_RPT_WITH_RECORD_CMD, &result, 1);
            return;
        }
    } else {
        return;
    }
    if (tuya_svc_lock_get_flash_record_num()) {
        result = REPORT_NEED_WAIT;
        cmmod_start_tm_msg(uart_ctrl.send_record_tm_msg, 100, TIMER_ONCE);
    } else {
        result = REPORT_SUCC;
    }
    ty_uart_protocol_send_direct(uart_ctrl.send_handle, DATA_RPT_WITH_RECORD_CMD, &result, 1);
}

STATIC VOID get_time_cb(struct s_tm_msg *tm_msg)
{
    UCHAR_T data_tm[8] = {0};
    data_tm[0] = get_system_time(&data_tm[1], FALSE);
    ty_uart_protocol_send_direct(uart_ctrl.send_handle, GET_LOCAL_TIME_CMD, data_tm, SIZEOF(data_tm));
}

STATIC VOID get_gltime_cb(struct s_tm_msg *tm_msg)
{
    UCHAR_T data_tm[8] = {0};
    data_tm[0] = get_system_time(&data_tm[1], TRUE);
    ty_uart_protocol_send_direct(uart_ctrl.send_handle, GET_GTM_TIME_CMD, data_tm, SIZEOF(data_tm));
}

STATIC OPERATE_RET ty_uart_dp_upload_with_record_handle(IN CHAR_T *p_name, IN TY_CMD_S *p_service_data)
{
    OPERATE_RET op_ret = OPRT_OK;
    UCHAR_T result = RESULT_SUCC;

    TY_LOCK_DP_S *lock_dp = NULL;
    UINT_T lock_dp_num = 0;
    if (p_service_data->datalen <= 7) {
        result = REPORT_FAILED;
        goto PROC_ERR;
    }
    op_ret = __ty_uart_recevie_data_proc(p_service_data->data + 7, p_service_data->datalen - 7, &lock_dp, &lock_dp_num);
    if (op_ret != OPRT_OK) {
        PR_ERR("__ty_recevie_data_proc error. %d", op_ret);
        result = REPORT_FAILED;
        goto PROC_ERR;
    }
    DP_TIME_S dp_time;
    dp_time.type = p_service_data->data[0];
    dp_time.time.tm_year = (p_service_data->data[1] + 100);
    dp_time.time.tm_mon  = (p_service_data->data[2] - 1);
    dp_time.time.tm_mday = p_service_data->data[3];
    dp_time.time.tm_hour = p_service_data->data[4];
    dp_time.time.tm_min  = p_service_data->data[5];
    dp_time.time.tm_sec  = p_service_data->data[6];
    uvc_video_pause();
    op_ret = tuya_svc_lock_dp_report_with_record_syn(lock_dp, lock_dp_num, &dp_time, 5);
    uvc_video_resume();
    if (op_ret != OPRT_OK) {
        PR_ERR("__ty_uplord_data_proc error.");
        if (OPRT_SVC_DP_ID_NOT_FOUND == op_ret) {
            result = REPORT_DP_ID_ERR;
        } else if (OPRT_SVC_DP_TP_NOT_MATCH == op_ret) {
            result = REPORT_DP_TYPE_ERR;
        } else {
            result = REPORT_FAILED;
        }

        __free_obj_dp_data(lock_dp, lock_dp_num);
        goto PROC_ERR;
    }
    __free_obj_dp_data(lock_dp, lock_dp_num);
    result = REPORT_SUCC;
PROC_ERR:
    ty_uart_protocol_send_direct(uart_ctrl.send_handle, DATA_RPT_WITH_RECORD_CMD, &result, 1);
    return op_ret;
}


STATIC OPERATE_RET ty_uart_net_sta_handle(IN CHAR_T *p_name, IN TY_CMD_S *p_service_data)
{
    OPERATE_RET op_ret = OPRT_OK;
    //op_ret = tuya_svc_uart_queue_delete_current_member_for_name(p_name);
    //if(OPRT_OK != op_ret) {
    //    PR_NOTICE("tuya_svc_uart_queue_delete_no_member_for_name:%d",op_ret);
    //}
    return OPRT_OK;
}


STATIC OPERATE_RET ty_uart_mcu_ota_start_handle(IN CHAR_T *p_name, IN TY_CMD_S *p_service_data)
{
    OPERATE_RET op_ret = OPRT_OK;
    WORD_T len = p_service_data->datalen;
    UINT_T i = 0;
    UINT_T pack_len = 256;

    op_ret = tuya_svc_uart_queue_delete_current_member_for_name(p_name);
    if (OPRT_OK != op_ret) {
        PR_ERR("tuya_svc_uart_queue_delete_current_member_for_name err:%d", op_ret);
        return op_ret;
    }

    if (1 == len) {
        for (i = 0; i < CNTSOF(g_mcu_ota_msg); i++) {
            if (p_service_data->data[0] == g_mcu_ota_msg[i].type) {
                pack_len = g_mcu_ota_msg[i].pack_len;
            }
        }
    }

    PR_DEBUG("mcu ota len is %d", pack_len);
    op_ret = tuya_svc_mcu_ota_pack_len_set(pack_len);
    if (OPRT_OK != op_ret) {
        PR_ERR("tuya_svc_mcu_ota_pack_len_set err:%d", op_ret);
        return op_ret;
    }

    PR_DEBUG("mcu start ota post sem sucess");
    op_ret = tuya_mcu_ota_post(POST_SUCCESS);
    if (OPRT_OK != op_ret) {
        PR_ERR("tuya_mcu_ota_post err:%d", op_ret);
        return op_ret;
    }
    return op_ret;
}

STATIC OPERATE_RET ty_uart_mcu_ota_trans_handle(IN CHAR_T *p_name, IN TY_CMD_S *p_service_data)
{
    OPERATE_RET op_ret = OPRT_OK;
    op_ret = tuya_svc_uart_queue_delete_current_member_for_name(p_name);
    if (OPRT_OK != op_ret) {
        PR_ERR("tuya_svc_uart_queue_delete_current_member_for_name err:%d", op_ret);
        return op_ret;
    }

    PR_DEBUG("mcu data ota post sem sucess");
    op_ret = tuya_mcu_ota_post(POST_SUCCESS);
    if (OPRT_OK != op_ret) {
        PR_ERR("tuya_svc_mcu_ota_wait_type_post err:%d", op_ret);
        return op_ret;
    }
    return op_ret;
}

STATIC OPERATE_RET ty_uart_auto_upgrade_handle(IN CHAR_T *p_name, IN TY_CMD_S *p_service_data)
{
    OPERATE_RET op_ret = OPRT_OK;
    PR_DEBUG("mcu data ota post sem sucess");
    op_ret = ty_uart_protocol_syn_ack_post(uart_ctrl.send_handle, p_service_data->cmd, p_service_data->data, p_service_data->datalen);
    if (OPRT_OK != op_ret) {
        PR_ERR("tuya_svc_mcu_ota_wait_type_post err:%d", op_ret);
        return op_ret;
    }
}

VOID  set_local_reset(VOID)
{
    module_state.is_local_reset = TRUE;
}

STATIC OPERATE_RET ty_uart_reset_handle(IN CHAR_T *p_name, IN TY_CMD_S *p_service_data)
{
    OPERATE_RET op_ret = OPRT_OK;
    if (FALSE == module_state.init_flag) {
        return OPRT_OK;
    }
    module_state.is_local_reset = TRUE;
    uart_ctrl.local_reset_type = WIFI_RESET_CMD;

    //iot_wf_gw_unactive_custom_mode(WF_START_AP_ONLY);
    tuya_iot_wf_gw_reset();
    return op_ret;
}

STATIC OPERATE_RET ty_uart_reset_sel_handle(IN CHAR_T *p_name, IN TY_CMD_S *p_service_data)
{
    OPERATE_RET op_ret = OPRT_OK;
    WORD_T len = p_service_data->datalen;
    if (FALSE == module_state.init_flag) {
        return OPRT_OK;
    }
    module_state.is_local_reset = TRUE;
    uart_ctrl.local_reset_type = WIFI_RESET_SEL_CMD;

    if (len > 0) {
        if (p_service_data->data[0] == 0) {
            //PR_DEBUG("RESET TO RESET_EZ_MODE");
            //iot_wf_gw_unactive_custom_mode(WF_START_AP_ONLY);
        } else {
            //PR_DEBUG("RESET TO RESET_AP_MODE");
            //iot_wf_gw_unactive_custom_mode(WF_START_AP_ONLY);
        }
        tuya_iot_wf_gw_reset();
    } else {
        PR_ERR("cmd para err");
    }

    return op_ret;
}

OPERATE_RET ty_wifi_reset_handle(VOID)
{
    OPERATE_RET op_ret = OPRT_OK;
    if (FALSE == module_state.init_flag) {
        return OPRT_COM_ERROR;
    }
    module_state.is_local_reset = TRUE;
    op_ret = tuya_iot_wf_gw_reset();
    return op_ret;
}

OPERATE_RET sys_time_check(VOID)
{
    OPERATE_RET op_ret = OPRT_OK;
    ty_cJSON *result = NULL;
    GW_CNTL_S *gw_cntl = get_gw_cntl();
    if (NULL == gw_cntl) {
        op_ret = OPRT_INVALID_PARM;
        return op_ret;
    }

    WF_STATION_STAT_E stat;
    op_ret = tuya_hal_wifi_station_get_status(&stat);
    if (OPRT_OK != op_ret) {
        return OPRT_NETWORK_ERROR;
    } else if (WSS_GOT_IP != stat) {
        return OPRT_NETWORK_ERROR;
    }

    op_ret = iot_httpc_common_post("tuya.device.dynamic.config.get", "1.0", NULL, gw_cntl->gw_if.id, NULL, NULL, &result);
    if (OPRT_OK != op_ret) {
        PR_ERR("httpc_common_post tuya.device.dynamic.config.get failed! op_ret:%d", op_ret);
        return op_ret;
    }
    if (result == NULL) {
        PR_ERR("http TI_GW_DYN_CFG_GET result is null");
        op_ret = OPRT_COM_ERROR;
        return op_ret;
    }
    ty_cJSON_Delete(result);
    return OPRT_OK;

}

STATIC BOOL_T get_system_time(OUT UCHAR_T *ptime, BOOL_T is_gmt)
{
    OPERATE_RET  op_ret = OPRT_OK;
    POSIX_TM_S   tm;
    STATIC BOOL_T is_time_check = FALSE;

    if (is_time_check == FALSE) {
        op_ret = sys_time_check();
        if (op_ret != OPRT_OK) {
            return FALSE;
        } else {
            is_time_check = TRUE;
            tuya_rtc_time_set(uni_time_get_posix());
        }
    }
    if (TRUE == is_gmt) {
        op_ret = uni_time_get(&tm);
        if (OPRT_OK != op_ret) {
            PR_ERR("uni_time_get failed! op_ret:%d", op_ret);
            return FALSE;
        }
    } else {
        op_ret = uni_local_time_get(&tm);
        if (OPRT_OK != op_ret) {
            PR_ERR("uni_local_time_get failed! op_ret:%d", op_ret);
            return FALSE;
        }
    }
    *ptime++ = tm.tm_year - 100;
    *ptime++ = tm.tm_mon + 1;
    *ptime++ = tm.tm_mday;
    *ptime++ = tm.tm_hour;
    *ptime++ = tm.tm_min;
    *ptime++ = tm.tm_sec;
    *ptime++ = (0 != tm.tm_wday) ? tm.tm_wday : 7;
    return TRUE;
}
STATIC OPERATE_RET ty_uart_get_local_time_handle(IN CHAR_T *p_name, IN TY_CMD_S *p_service_data)
{
    OPERATE_RET op_ret = OPRT_OK;
    cmmod_start_tm_msg(uart_ctrl.get_time_tm_msg, 10, TIMER_ONCE);
    return op_ret;
}

STATIC OPERATE_RET ty_uart_get_gtm_time_handle(IN CHAR_T *p_name, IN TY_CMD_S *p_service_data)
{
    OPERATE_RET op_ret = OPRT_OK;
    cmmod_start_tm_msg(uart_ctrl.get_time_gltm_msg, 10, TIMER_ONCE);
    return op_ret;
}

STATIC UCHAR_T conv_rssi_data(SCHAR_T rssi)
{
    UCHAR_T ret = 0;
    if (rssi <= -100) {
        ret = 0;
    } else if ((rssi > -100) && (rssi <= -80)) {
        ret = 40;
    } else if ((rssi > -80) && (rssi <= -60)) {
        ret = 60;
    } else if ((rssi > -60) && (rssi <= -40)) {
        ret = 80;
    } else {
        ret = 100;
    }
    return ret;
}

STATIC OPERATE_RET ty_uart_get_wifi_signal_handle(IN CHAR_T *p_name, IN TY_CMD_S *p_service_data)
{
    OPERATE_RET op_ret = OPRT_OK;
    SCHAR_T rssi = 0;
    UCHAR_T ret_buf[2] = {0};
    op_ret = wf_station_get_conn_ap_rssi(&rssi);
    if (OPRT_OK != op_ret) {
        ret_buf[0] = 0x00;
        ret_buf[1] = 0x00;
    } else {
        ret_buf[0] = 0x01;
        ret_buf[1] = conv_rssi_data(rssi);
    }
    op_ret = ty_uart_protocol_send_direct(uart_ctrl.send_handle, GET_WF_SIGAL_CMD, ret_buf, SIZEOF(ret_buf));
    return op_ret;
}

STATIC OPERATE_RET ty_uart_set_log_level_handle(IN CHAR_T *p_name, IN TY_CMD_S *p_service_data)
{
    OPERATE_RET op_ret = OPRT_OK;
    CHAR_T *pdata = NULL;
    pdata = (CHAR_T *)p_service_data->data;
    switch (pdata[0]) {
    case 0: {
        UCHAR_T level = (UCHAR_T)pdata[1];
        SetLogManageAttr((LOG_LEVEL)pdata[1]);
        op_ret = ty_uart_protocol_send_direct(uart_ctrl.send_handle, SET_DB_LOG_LEVEL_CMD, (UCHAR_T *)&level, SIZEOF(UCHAR_T));
    }
    break;
    case 1: {
        UINT_T free_mem = 0;
        free_mem = tuya_hal_system_getheapsize();
        PR_NOTICE("FreeMemSize:%d", free_mem);
        free_mem = DWORD_SWAP(free_mem);
        op_ret = ty_uart_protocol_send_direct(uart_ctrl.send_handle, SET_DB_LOG_LEVEL_CMD, (UCHAR_T *)&free_mem, SIZEOF(UINT_T));
    }
    break;

    default:
        break;
    }
    return op_ret;
}


#pragma pack(1)
typedef struct {
    UCHAR_T   idx;
    UCHAR_T   valid_cnt;
    UCHAR_T   state;
    UCHAR_T   start_year;
    UCHAR_T   start_mon;
    UCHAR_T   start_day;
    UCHAR_T   start_hour;
    UCHAR_T   start_min;
    UCHAR_T   start_sec;
    UCHAR_T   end_year;
    UCHAR_T   end_mon;
    UCHAR_T   end_day;
    UCHAR_T   end_hour;
    UCHAR_T   end_min;
    UCHAR_T   end_sec;
    UCHAR_T   pass[0];
} ONE_MULTI_PASS;
typedef struct {
    UCHAR_T  allday;
    UCHAR_T  start_hour;
    UCHAR_T  start_min;
    UCHAR_T  end_hour;
    UCHAR_T  end_min;
    UCHAR_T  week;
} ONE_SCHEDULE;
typedef struct {
    UCHAR_T        schedule_cnt;
    ONE_SCHEDULE  arry[0];
} SCHEDULES;
typedef struct {
    UCHAR_T   ret;
    UCHAR_T   type;
    UCHAR_T   len;
    UCHAR_T   decode[0];
} OFFLINE_PASS_RET;
#pragma pack()

STATIC BOOL_T mk_one_multi_pass_frame(TY_PW_INFO_S *pass_info, OUT ONE_MULTI_PASS *per_pass)
{
    OPERATE_RET op_ret = OPRT_OK;
    ty_cJSON *item = NULL;
    UCHAR_T *pass_buf = NULL;
    if (NULL == pass_info || NULL == per_pass) {
        return FALSE;
    }
    per_pass->idx = (UCHAR_T)(pass_info->num - 900);
    per_pass->valid_cnt = pass_info->one_off;
    per_pass->state = pass_info->state;
    per_pass->start_year = (UCHAR_T)(pass_info->start_time.year - 100);
    per_pass->start_mon = (UCHAR_T)(pass_info->start_time.mon + 1);
    per_pass->start_day = (UCHAR_T)(pass_info->start_time.day);
    per_pass->start_hour = (UCHAR_T)(pass_info->start_time.hour);
    per_pass->start_min = (UCHAR_T)(pass_info->start_time.min);
    per_pass->start_sec = (UCHAR_T)(pass_info->start_time.sec);
    per_pass->end_year = (UCHAR_T)(pass_info->end_time.year - 100);
    per_pass->end_mon = (UCHAR_T)(pass_info->end_time.mon + 1);
    per_pass->end_day = (UCHAR_T)(pass_info->end_time.day);
    per_pass->end_hour = (UCHAR_T)(pass_info->end_time.hour);
    per_pass->end_min = (UCHAR_T)(pass_info->end_time.min);
    per_pass->end_sec = (UCHAR_T)(pass_info->end_time.sec);
    memcpy(per_pass->pass, pass_info->password, pass_info->pw_len);
    return TRUE;
}

STATIC BOOL_T mk_one_schedule_frame(IN TY_PW_SCHEDULE_S *schedule_info, INOUT ONE_SCHEDULE *schedule)
{

    if (NULL == schedule_info || NULL == schedule) {
        return FALSE;
    }
    schedule->allday = schedule_info->allday;
    schedule->start_hour = schedule_info->start_hour;
    schedule->start_min = schedule_info->start_min;
    schedule->end_hour = schedule_info->end_hour;
    schedule->end_min = schedule_info->end_min;
    schedule->week = schedule_info->week;
    return TRUE;
}

STATIC OPERATE_RET mk_multi_schedule_frame(TY_PW_INFO_S *pass_info, UCHAR_T pass_cnt)
{
    OPERATE_RET op_ret = OPRT_OK;
    CHAR_T *multi_buf = NULL;
    UINT_T frame_len = 0;
    UCHAR_T pass_len = 0;
    UINT_T i = 0;
    UINT_T j = 0;
    UINT_T package_idx = 0;
    UINT_T code_num_idx = 0;
    TY_PW_INFO_S *p_multi_pass = NULL;
    BOOL_T result;

    if (NULL == pass_info) {
        return OPRT_INVALID_PARM;
    }
    BOOL_T is_set_base = tuya_base_conversion_state();;

    multi_buf = (CHAR_T *)Malloc(DEF_FRAME_BUF_SZ);
    if (NULL == multi_buf) {
        return OPRT_MALLOC_FAILED;
    }
    memset(multi_buf, 0x00, DEF_FRAME_BUF_SZ);
    multi_buf[frame_len++] = 0x01;
    code_num_idx = frame_len;
    multi_buf[frame_len++] = 0;
    if (!is_set_base) {
        multi_buf[frame_len++] = 7;
    }
    package_idx = frame_len;
    multi_buf[frame_len++] = 0;

    for (i = 0; i < pass_cnt; i++) {
        p_multi_pass = pass_info + i;
        if (is_set_base) {
            multi_buf[frame_len++] = p_multi_pass->pw_len;
        }
        result = mk_one_multi_pass_frame(p_multi_pass, &multi_buf[frame_len]);
        if (FALSE == result) {
            op_ret = OPRT_COM_ERROR;
            goto PROCE_ERR;
        }
        SCHEDULES *schedules = (SCHEDULES *)(&multi_buf[frame_len] + SIZEOF(ONE_MULTI_PASS) + p_multi_pass->pw_len);
        schedules->schedule_cnt = p_multi_pass->schedule.cnt;
        for (j = 0; j < schedules->schedule_cnt; j++) {
            mk_one_schedule_frame(&(p_multi_pass->schedule.info[j]), &(schedules->arry[j]));
        }
        frame_len += SIZEOF(ONE_MULTI_PASS) +  p_multi_pass->pw_len + SIZEOF(SCHEDULES) + (SIZEOF(ONE_SCHEDULE) * schedules->schedule_cnt);
        multi_buf[code_num_idx] ++;

        if (4 == i && i + 1 < pass_cnt) {
            multi_buf[package_idx] = 0x80;
            ty_uart_protocol_send_direct(uart_ctrl.send_handle, GET_MUTI_SCHEDULE_PASS_CMD, multi_buf, frame_len);
            PR_DEBUG("send_buf_len = %d", frame_len);
            frame_len = package_idx + 1 ;
            memset(&multi_buf[package_idx], 0, DEF_FRAME_BUF_SZ - frame_len);
            multi_buf[code_num_idx] = 0;
            multi_buf[package_idx] = 0;
            multi_buf[package_idx] ++;
        }
    }
    if (0 != multi_buf[package_idx] & 0x7F) {
        tuya_hal_system_sleep(100);
    }
    tuya_print_data(multi_buf, frame_len);
    op_ret = ty_uart_protocol_send_direct(uart_ctrl.send_handle, GET_MUTI_SCHEDULE_PASS_CMD, multi_buf, frame_len);
    PR_DEBUG("send_buf_len = %d", frame_len);
PROCE_ERR:
    if (multi_buf) {
        Free(multi_buf);
    }
    return op_ret;
}

STATIC VOID tuya_lock_mult_online_pw_callback(IN BOOL_T ret, IN UCHAR_T pw_cnt, IN TY_PW_INFO_S *pw_info)
{
    INT_T i = 0, pw_idx = 0;
    TY_PW_INFO_S *p_info = NULL;
    PR_DEBUG("get pw ret = %d pw_cnt = %d ", ret, pw_cnt);
    if (FALSE == ret) {
        UCHAR_T result = 0;
        result = 0;
        ty_uart_protocol_send_direct(uart_ctrl.send_handle, GET_MUTI_SCHEDULE_PASS_CMD, &result, 1);
        return;
    } else if (0 == pw_cnt) {
        UCHAR_T no_pass_buf[2];
        no_pass_buf[0] = 1;
        no_pass_buf[1] = 0;
        ty_uart_protocol_send_direct(uart_ctrl.send_handle, GET_MUTI_SCHEDULE_PASS_CMD, no_pass_buf, SIZEOF(no_pass_buf));
        return;
    }
    mk_multi_schedule_frame(pw_info, pw_cnt);
    return;
}


STATIC OPERATE_RET ty_uart_get_mult_schedule_pass_handle(IN CHAR_T *p_name, IN TY_CMD_S *p_service_data)
{
    OPERATE_RET op_ret = OPRT_OK;
    GW_WIFI_NW_STAT_E cur_nw_stat;
    op_ret = get_wf_gw_nw_status(&cur_nw_stat);
    if (OPRT_OK == op_ret && (cur_nw_stat == STAT_CLOUD_CONN || cur_nw_stat == STAT_AP_CLOUD_CONN)) {
        op_ret = tuya_svc_lock_online_pw_get_pw_list(tuya_lock_mult_online_pw_callback);
    } else {
        UCHAR_T result = 0;
        ty_uart_protocol_send_direct(uart_ctrl.send_handle, GET_MUTI_SCHEDULE_PASS_CMD, &result, 1);
    }
    return op_ret;
}
STATIC OPERATE_RET mk_multi_frame(TY_PW_INFO_S *pass_info, UCHAR_T pass_cnt)
{
    OPERATE_RET op_ret = OPRT_OK;
    CHAR_T *multi_buf = NULL;
    UINT_T frame_len = 0;
    UCHAR_T pass_len = 0;
    UINT_T i = 0;
    UINT_T j = 0;
    UINT_T package_idx = 0;
    UINT_T code_num_idx = 0;
    TY_PW_INFO_S *p_multi_pass = NULL;
    BOOL_T result;

    if (NULL == pass_info) {
        return OPRT_INVALID_PARM;
    }
    multi_buf = (CHAR_T *)Malloc(DEF_FRAME_BUF_SZ);
    if (NULL == multi_buf) {
        return OPRT_MALLOC_FAILED;
    }
    memset(multi_buf, 0x00, DEF_FRAME_BUF_SZ);
    multi_buf[frame_len++] = 0x01;
    multi_buf[frame_len++] = pass_cnt;
    BOOL_T is_set_base = tuya_base_conversion_state();
    if (!is_set_base) {
        multi_buf[frame_len++] = 7;
    }
    for (i = 0; i < pass_cnt; i++) {
        p_multi_pass = pass_info + i;
        if (is_set_base) {
            multi_buf[frame_len++] = p_multi_pass->pw_len;
        }
        result = mk_one_multi_pass_frame(p_multi_pass, &multi_buf[frame_len]);
        if (FALSE == result) {
            op_ret = OPRT_COM_ERROR;
            goto PROCE_ERR;
        }
        frame_len += SIZEOF(ONE_MULTI_PASS) + p_multi_pass->pw_len ;
    }
    tuya_print_data(multi_buf, frame_len);
    op_ret = ty_uart_protocol_send_direct(uart_ctrl.send_handle, GET_MUTI_PASS_CMD, multi_buf, frame_len);
    PR_DEBUG("send_buf_len = %d", frame_len);
PROCE_ERR:
    if (multi_buf) {
        Free(multi_buf);
    }
    return op_ret;
}
STATIC VOID tuya_lock_online_pw_callback(IN BOOL_T ret, IN UCHAR_T pw_cnt, IN TY_PW_INFO_S *pw_info)
{
    INT_T i = 0, pw_idx = 0;
    TY_PW_INFO_S *p_info = NULL;
    PR_DEBUG("get pw ret = %d pw_cnt = %d ", ret, pw_cnt);
    if (FALSE == ret) {
        UCHAR_T result = 0;
        result = 0;
        ty_uart_protocol_send_direct(uart_ctrl.send_handle, GET_MUTI_PASS_CMD, &result, 1);
        return;
    } else if (0 == pw_cnt) {
        UCHAR_T no_pass_buf[2];
        no_pass_buf[0] = 1;
        no_pass_buf[1] = 0;
        ty_uart_protocol_send_direct(uart_ctrl.send_handle, GET_MUTI_PASS_CMD, no_pass_buf, SIZEOF(no_pass_buf));
        return;
    }
    mk_multi_frame(pw_info, pw_cnt);
    return;
}
STATIC OPERATE_RET ty_uart_get_mult_pass_handle(IN CHAR_T *p_name, IN TY_CMD_S *p_service_data)
{
    OPERATE_RET op_ret = OPRT_OK;
    GW_WIFI_NW_STAT_E cur_nw_stat;
    op_ret = get_wf_gw_nw_status(&cur_nw_stat);
    if (OPRT_OK == op_ret && (cur_nw_stat == STAT_CLOUD_CONN || cur_nw_stat == STAT_AP_CLOUD_CONN)) {
        op_ret = tuya_svc_lock_online_pw_get_pw_list(tuya_lock_online_pw_callback);
    } else {
        UCHAR_T result = 0;
        ty_uart_protocol_send_direct(uart_ctrl.send_handle, GET_MUTI_PASS_CMD, &result, 1);
    }
    return op_ret;
}
STATIC OPERATE_RET ty_uart_get_offline_pass_handle(IN CHAR_T *p_name, IN TY_CMD_S *p_service_data)
{
    OPERATE_RET op_ret = OPRT_OK;

    TY_OFFLINE_PW_INFO_S pw_info = {0};
    TY_OFFLINE_PW_RESULT_S result_buf;
    UCHAR_T result;
    OFFLINE_PASS_RET *sendbuf;
    pw_info.time.year = p_service_data->data[0] + 100;
    pw_info.time.mon = p_service_data->data[1] - 1;
    pw_info.time.day = p_service_data->data[2];
    pw_info.time.hour = p_service_data->data[3];
    pw_info.time.min = p_service_data->data[4];
    pw_info.time.sec = p_service_data->data[5];
    pw_info.pw_len = p_service_data->data[6];
    pw_info.pw = &p_service_data->data[7];
    memset(&result, 0, SIZEOF(TY_OFFLINE_PW_RESULT_S));

    op_ret = tuya_svc_lock_offline_pw_check(get_active_time(), &pw_info, &result_buf);
    if (OPRT_OK == op_ret) {
        PR_NOTICE("----------------offline pw verify result is %d------------------", result_buf.ret);
        if (0 == result_buf.ret) {
            PR_DEBUG("type = %d, decode len = %d", result_buf.type, result_buf.decode_len);
            sendbuf = Malloc(SIZEOF(OFFLINE_PASS_RET) + result_buf.decode_len + 1);
            if (NULL == sendbuf) {
                return OPRT_MALLOC_FAILED;
            }
            memset(sendbuf, 0, SIZEOF(OFFLINE_PASS_RET) + result_buf.decode_len + 1);

            sendbuf->ret = result_buf.ret;
            sendbuf->type = result_buf.type;
            sendbuf->len = result_buf.decode_len;
            memcpy(sendbuf->decode, result_buf.decode, result_buf.decode_len);
            op_ret = ty_uart_protocol_send_direct(uart_ctrl.send_handle, GET_OFFLINE_PASS_CMD, (UCHAR_T *)sendbuf, SIZEOF(OFFLINE_PASS_RET) + result_buf.decode_len);
            Free(sendbuf);
            return op_ret;
        }
    }
    result = 0x01;
    op_ret = ty_uart_protocol_send_direct(uart_ctrl.send_handle, GET_OFFLINE_PASS_CMD, &result, SIZEOF(result));

    return op_ret;
}

STATIC OPERATE_RET ty_uart_get_dynamic_pass_handle(IN CHAR_T *p_name, IN TY_CMD_S *p_service_data)
{
    OPERATE_RET op_ret = OPRT_OK;
    TY_DYNAMIC_PW_RET_E ret;
    TY_DYNAMIC_PW_INFO_S pw_info = {0};
    pw_info.time.year = p_service_data->data[0] + 100;
    pw_info.time.mon = p_service_data->data[1] - 1;
    pw_info.time.day = p_service_data->data[2];
    pw_info.time.hour = p_service_data->data[3];
    pw_info.time.min = p_service_data->data[4];
    pw_info.time.sec = p_service_data->data[5];
    BOOL_T is_set_base = tuya_base_conversion_state();
    if (is_set_base) {
        pw_info.pw_len = p_service_data->data[6];
        pw_info.password = &p_service_data->data[7];
    } else {
        pw_info.pw_len = 8;
        pw_info.password = &p_service_data->data[6];
    }

    op_ret = tuya_svc_lock_dynamic_pw_verify(&pw_info, &ret);
    op_ret = ty_uart_protocol_send_direct(uart_ctrl.send_handle, GET_DYN_PASS_CMD, &ret, 1);
    return op_ret;
}

STATIC OPERATE_RET ty_uart_set_base_conversion_handle(IN CHAR_T *p_name, IN TY_CMD_S *p_service_data)
{
    OPERATE_RET op_ret = OPRT_OK;
    UCHAR_T ret = 0;
    op_ret = tuya_base_conversion_init(p_service_data->data[0], p_service_data->data[1]);
    if (OPRT_OK == op_ret) {
        ret = 0;
    } else {
        ret = 1;
    }
    op_ret = ty_uart_protocol_send_direct(uart_ctrl.send_handle, SET_BASE_CNV_CMD, &ret, 1);
    return op_ret;
}


#pragma pack(1)
typedef struct {
    UCHAR_T  dp_num;
    UCHAR_T  dp_arr[0];
} DP_CACHE_STATE_S;
typedef struct {
    UCHAR_T   result;
    UCHAR_T   dp_num;
    UCHAR_T   dp[0];
} DP_CACHE_RESULT_S;
#pragma pack()

STATIC INT_T get_enum_id(UINT_T dpid, PCHAR_T enum_str)
{
    DP_PROP_VALUE_U  *prop_value = NULL;
    INT_T i;

    if (NULL == enum_str) {
        PR_ERR("enum_str is null");
        return (-1);
    }

    prop_value = tuya_iot_get_dp_prop_value(tuya_iot_get_gw_id(), dpid);
    if (NULL == prop_value) {
        PR_ERR("tuya_iot_get_dp_prop_value failed");
        return (-1);
    }

    for (i = 0; i < prop_value->prop_enum.cnt; i++) {
        if (0 == strcmp(enum_str, prop_value->prop_enum.pp_enum[i])) {
            return i;
        }
    }

    return (-1);
}
STATIC UINT_T parse_cj_dp_state(CONST IN ty_cJSON *root, INOUT TY_DP_DATA_S *dp_data)
{
    UCHAR_T dpid = 0x00;
    USHORT_T value_len = 0x00;
    DP_DESC_IF_S  *dp_desc = NULL;

    if (NULL == root || NULL == dp_data) {
        PR_ERR("param is err!");
        return 0;
    }

    dpid = atoi(root->string);

    dp_desc = tuya_iot_get_dp_desc(NULL, dpid);
    if (NULL == dp_desc) {
        PR_ERR("tuya_iot_get_dp_desc failed! dpid:%d", dpid);
        return 0;
    }

    dp_data->dpid = dpid;

    if (T_RAW == dp_desc->type) {
        UINT_T tmp = 0;

        dp_data->type = DP_TYPE_RAW;
        tmp = strlen(root->valuestring);
        if (0 != tuya_base64_decode((CHAR_T *)root->valuestring, (CHAR_T *)dp_data->data)) {
            PR_ERR("mbedtls_base64_decode failed!");
            return 0;
        }

    } else if (T_OBJ == dp_desc->type) {
        switch (dp_desc->prop_tp) {
        case PROP_BOOL:
            dp_data->type = DP_TYPE_BOOL;
            dp_data->data[0] = (ty_cJSON_True == root->type) ? 0x01 : 0x00;
            value_len = 1;
            break;
        case PROP_VALUE: {
            INT_T val_data = DWORD_SWAP(root->valueint);

            dp_data->type = DP_TYPE_VALUE;
            value_len = SIZEOF(val_data);
            memcpy(dp_data->data, (UCHAR_T *)&val_data, value_len);
        }
        break;
        case PROP_STR:
            dp_data->type = DP_TYPE_STRING;
            value_len = strlen(root->valuestring);
            memcpy(dp_data->data, root->valuestring, value_len);
            break;
        case PROP_ENUM: {
            INT_T temp;
            temp = get_enum_id(dpid, root->valuestring);
            if (temp < 0) {
                PR_ERR("not find enum id:%d str:%s", dpid, root->valuestring);
                return 0;
            }
            dp_data->type = DP_TYPE_ENUM;
            value_len = 0x01;
            dp_data->data[0] = (UCHAR_T)temp;
        }
        break;
        case PROP_BITMAP: {
            DP_PROP_VALUE_U *prop_value;

            prop_value = tuya_iot_get_dp_prop_value(tuya_iot_get_gw_id(), dpid);
            if (NULL == prop_value) {
                PR_ERR("tuya_iot_get_dp_prop_value failede!");
                return 0;
            }

            dp_data->type = DP_TYPE_BITMAP;

            value_len = GET_BITMAP_PROT_LEN(prop_value->prop_bitmap.max_len);
            if (1 == value_len) {
                dp_data->data[0] = (UCHAR_T)root->valueint;
            } else if (2 == value_len) {
                dp_data->data[0] = (root->valueint >> 8) & 0xFF;
                dp_data->data[1] =  root->valueint & 0xFF;
            } else {
                UINT_T bit = DWORD_SWAP(root->valueint);
                memcpy(dp_data->data, &bit, 4);
            }
        }
        break;
        default:
            break;
        }
    }
    dp_data->len = WORD_SWAP(value_len);
    return value_len + SIZEOF(TY_DP_DATA_S);
}

STATIC OPERATE_RET httpc_proc_dp_cache_state(IN ty_cJSON *result)
{
    UINT_T offset = 0, arr_sz, i, cj_val_len;
    ty_cJSON *item = NULL, *root = NULL;
    TY_DP_DATA_S *one_dp_data = NULL;
    DP_CACHE_RESULT_S *cache_prot = NULL;

    cache_prot = (DP_CACHE_RESULT_S *)Malloc(DEF_FRAME_BUF_SZ);
    if (NULL == cache_prot) {
        return OPRT_MALLOC_FAILED;
    }
    memset((UCHAR_T *)cache_prot, 0x00, DEF_FRAME_BUF_SZ);
    offset = SIZEOF(DP_CACHE_RESULT_S);

    cache_prot->result = 0x01;
    cache_prot->dp_num = 0x00;

    if (NULL == result) {
        PR_NOTICE("result:1 0 -----------------------------------");
        ty_uart_protocol_send_direct(uart_ctrl.send_handle, GET_REMOTE_DP_CACHE, (UCHAR_T *)cache_prot, offset);
        return OPRT_OK;
    }

    arr_sz = ty_cJSON_GetArraySize(result);
    for (i = 0; i < arr_sz; i++) {
        item = ty_cJSON_GetArrayItem(result, i);
        if (NULL == item) {
            PR_ERR("cJSON_GetArrayItem:%d failed", i);
            continue;
        }
        root = ty_cJSON_Parse(item->valuestring);
        if (NULL == root) {
            PR_ERR("cJSON_Parse:%s failed", item->valuestring);
            continue;
        }
        cj_val_len = (ty_cJSON_String == root->type) ? strlen(root->valuestring) : 4;
        if (offset + cj_val_len + SIZEOF(TY_DP_DATA_S) >= DEF_FRAME_BUF_SZ) {
            PR_NOTICE("result:1 0 1----------------------------------");
            ty_uart_protocol_send_direct(uart_ctrl.send_handle, GET_REMOTE_DP_CACHE, (UCHAR_T *)cache_prot, offset);
            offset = SIZEOF(DP_CACHE_RESULT_S);
            cache_prot->dp_num = 0;
        }
        one_dp_data = (TY_DP_DATA_S *)((UCHAR_T *)cache_prot + offset);
        offset += parse_cj_dp_state(root->child, one_dp_data);
        cache_prot->dp_num++;
        ty_cJSON_Delete(root);
    }

    if (0 == arr_sz || 0 != cache_prot->dp_num) {
        PR_NOTICE("result:1 0 2----------------------------------");
        ty_uart_protocol_send_direct(uart_ctrl.send_handle, GET_REMOTE_DP_CACHE, (UCHAR_T *)cache_prot, offset);
    }
    return OPRT_OK;
}

STATIC OPERATE_RET httpc_get_dp_cache_state(IN DP_CACHE_STATE_S *dp_state)
{
    UINT_T i;
    OPERATE_RET op_ret = OPRT_OK;
    PCHAR_T  out;
    ty_cJSON *root = NULL, *arry = NULL, *result = NULL;
    GW_CNTL_S *gw_cntl = get_gw_cntl();

    if (NULL == gw_cntl || NULL == dp_state) {
        return OPRT_INVALID_PARM;
    }
    root = ty_cJSON_CreateObject();
    if (NULL == root) {
        return OPRT_CR_CJSON_ERR;
    }
    if (0 != dp_state->dp_num) {
        arry = ty_cJSON_CreateArray();
        if (NULL == arry) {
            ty_cJSON_Delete(root);
            return OPRT_CR_CJSON_ERR;
        }
        for (i = 0; i < dp_state->dp_num; i++) {
            ty_cJSON_AddItemToArray(arry, ty_cJSON_CreateNumber((double)dp_state->dp_arr[i]));
        }
        ty_cJSON_AddItemToObject(root, "dps", arry);
    }
    out = ty_cJSON_PrintUnformatted(root);
    ty_cJSON_Delete(root);
    if (NULL == out) {
        return OPRT_MALLOC_FAILED;
    }
    PR_DEBUG("out:%s", out);
    op_ret = iot_httpc_common_post(TI_GET_DP_CACHE_STATE, "1.0", NULL, gw_cntl->gw_if.id, out, NULL, &result);
    Free(out), out = NULL;
    if (OPRT_OK != op_ret) {
        PR_ERR("httpc_common_post TI_GET_DP_CACHE_STATE failed! op_ret:%d", op_ret);
        return op_ret;
    }
    op_ret = httpc_proc_dp_cache_state(result);
    if (OPRT_OK != op_ret) {
        PR_ERR("httpc_proc_dp_cache_state failed! op_ret:%d", op_ret);
    }
    ty_cJSON_Delete(result);
    return op_ret;
}

STATIC OPERATE_RET ty_uart_get_dp_cache_handle(IN CHAR_T *p_name, IN TY_CMD_S *p_service_data)
{
    OPERATE_RET op_ret = OPRT_OK;
    UCHAR_T result = 0x00;
    DP_CACHE_STATE_S *dp_cache = NULL;
    dp_cache = (DP_CACHE_STATE_S *)p_service_data->data;
    op_ret = httpc_get_dp_cache_state(dp_cache);
    if (OPRT_OK != op_ret) {
        PR_ERR("httpc_get_dp_cache_state failed op_ret:%d", op_ret);
        op_ret = ty_uart_protocol_send_direct(uart_ctrl.send_handle, GET_REMOTE_DP_CACHE, (UCHAR_T *)&result, SIZEOF(result));
    }
    return op_ret;
}



STATIC OPERATE_RET ty_uart_photo_trigger_handle(IN CHAR_T *p_name, IN TY_CMD_S *p_service_data)
{
    OPERATE_RET op_ret = OPRT_OK;
    ty_photo_trigger_proc(p_service_data->data, p_service_data->datalen);
    return op_ret;
}

STATIC OPERATE_RET ty_uart_photo_upload_ack_handle(IN CHAR_T *p_name, IN TY_CMD_S *p_service_data)
{
    OPERATE_RET op_ret = OPRT_OK;
    return op_ret;
}
STATIC OPERATE_RET ty_uart_module_reset_ack_handle(IN CHAR_T *p_name, IN TY_CMD_S *p_service_data)
{
    OPERATE_RET op_ret = OPRT_OK;
    ty_uart_protocol_syn_ack_post(uart_ctrl.send_handle, p_service_data->cmd, p_service_data->data, p_service_data->datalen);
    return op_ret;
}

STATIC OPERATE_RET ty_uart_req_wifi_ota_handle(IN CHAR_T *p_name, IN TY_CMD_S *p_service_data)
{
    OPERATE_RET op_ret = OPRT_OK;
    //  op_ret = tuya_request_ota(FALSE);
    return op_ret;
}

STATIC OPERATE_RET ty_uart_req_mcu_ota_handle(IN CHAR_T *p_name, IN TY_CMD_S *p_service_data)
{
    OPERATE_RET op_ret = OPRT_OK;
    //  op_ret = tuya_request_ota(TRUE);
    return op_ret;
}

STATIC OPERATE_RET ty_uart_get_wifi_sta_handle(IN CHAR_T *p_name, IN TY_CMD_S *p_service_data)
{
    OPERATE_RET op_ret = OPRT_OK;
    UCHAR_T wifi_st[2] = {0};
    wifi_st[0] =  tuya_get_wifi_status();
    GW_WORK_STAT_T work_st = get_gw_active();
    if (ACTIVATED == work_st) {
        wifi_st[1] = 1;
    } else {
        wifi_st[1] = 0;
    }

    ty_uart_send_data_direct(GET_WIFI_STATE_CMD, &wifi_st, SIZEOF(wifi_st));
    return op_ret;
}

STATIC OPERATE_RET ty_uart_get_unix_time_handle(IN CHAR_T *p_name, IN TY_CMD_S *p_service_data)
{
    OPERATE_RET op_ret = OPRT_OK;

    return op_ret;
}

STATIC VOID tuya_device_lp_time_cb(UINT_T timerID, PVOID_T pTimerArg)
{
    PR_NOTICE("======================uart set low power=====================");
    device_spcl_enter_low_power();
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
    sys_start_timer(device_lp_timer_id, 500, TIMER_ONCE);
    return op_ret;
}

STATIC OPERATE_RET ty_uart_set_power_off_handle(IN CHAR_T *p_name, IN TY_CMD_S *p_service_data)
{
    OPERATE_RET op_ret = OPRT_OK;
    UCHAR_T ret = 0;
    op_ret = ty_uart_protocol_send_direct(uart_ctrl.send_handle, POWER_OFF_CMD, &ret, 1);
    tuya_device_low_power_init_and_start();

    return op_ret;
}

STATIC OPERATE_RET ty_uart_set_lcd_status_handle(IN CHAR_T *p_name, IN TY_CMD_S *p_service_data)
{
    OPERATE_RET op_ret = OPRT_OK;
    UCHAR_T ret = 0;
    GW_WIFI_NW_STAT_E cur_nw_stat = 0;
    op_ret = get_wf_gw_nw_status(&cur_nw_stat);
    if (OPRT_OK != op_ret) {
        PR_ERR("get_wf_gw_status err");
        ret = 1;
        op_ret = ty_uart_protocol_send_direct(uart_ctrl.send_handle, p_service_data->cmd, &ret, 1);
        return op_ret;
    }

    if ((cur_nw_stat == STAT_UNPROVISION) || (cur_nw_stat == STAT_AP_STA_UNCFG) || (cur_nw_stat == STAT_UNPROVISION_AP_STA_UNCFG)) {
        ret = 2;
        op_ret = ty_uart_protocol_send_direct(uart_ctrl.send_handle, p_service_data->cmd, &ret, 1);
        return op_ret;
    }
    if (0x01 == p_service_data->data[0]) {
        tuya_video_lcd_open(LCD_FROM_UART);
    } else if (0x00 == p_service_data->data[0]) {
        tuya_video_lcd_ctr(FALSE, LCD_FROM_UART, 0);
    }
    op_ret = ty_uart_protocol_send_direct(uart_ctrl.send_handle, p_service_data->cmd, &ret, 1);
    return op_ret;
}

STATIC OPERATE_RET ty_uart_set_camera_para_handle(IN CHAR_T *p_name, IN TY_CMD_S *p_service_data)
{
    OPERATE_RET op_ret = OPRT_OK;
    TY_CAMERA_PARAM camera_param;
    TY_AUDIO_PARAM audio_param;
    struct lcd_user_info user_info;
    TY_LORD_PARAM lord_param;
    INT_T w, h, r, f;
    INT_T chan, sample, bit;
    INT_T lcd_type = 0;
    UCHAR_T ret = 0;
    UINT_T read_len = 0;

    memset(&camera_param, 0, sizeof(TY_CAMERA_PARAM));
    op_ret = ty_param_load(CAMERA_CFG_PARAM_E, &camera_param, SIZEOF(TY_CAMERA_PARAM), &read_len);
    if ((op_ret != OPRT_OK) || (read_len != SIZEOF(TY_CAMERA_PARAM))) {
        camera_param.video_width = VEDIO_W_DEFAULT;
        camera_param.video_height = VEDIO_H_DEFAULT;
        camera_param.video_fps = VEDIO_FPS_DEFAULT;
        camera_param.video_rotat_angle = VEDIO_ROTE_DEFAULT;
        camera_param.video_power_off = USB_POWER_DEFAULT;
    }

    memset(&audio_param, 0, sizeof(TY_AUDIO_PARAM));
    op_ret = ty_param_load(AUDIO_CFG_PARAM_E, &audio_param, SIZEOF(TY_AUDIO_PARAM), &read_len);
    if ((op_ret != OPRT_OK) || (read_len != SIZEOF(TY_AUDIO_PARAM))) {
        audio_param.sample_rate = AUDIO_RATE_DEFAULT;
        audio_param.bit_dept = AUDIO_BIT_DEFAULT;
        audio_param.channel_num = AUDIO_CHANNEL_DEFAULT;
        audio_param.audio_power_off = USB_POWER_DEFAULT;
    }

    memset(&user_info, 0, sizeof(struct lcd_user_info));
    op_ret = ty_param_load(LCD_CFG_PARAM_E, &user_info, SIZEOF(struct lcd_user_info), &read_len);
    if ((op_ret != OPRT_OK) || (read_len != SIZEOF(struct lcd_user_info))) {
        user_info.lcd_if = LCD_HW_SEL_DEFAULT;
        user_info.lcd_vertical = LCD_VERTICAL_DEFAULT;
        user_info.lcd_horizontal = LCD_HONRIZONTAL_DEFAULT;
        user_info.lcd_inversion = LCD_INVERSION_DEFAULT;
        user_info.lcd_type = LCD_TYPE_DEFAULT;
    }

    op_ret = ty_param_load(LORD2_CFG_PARAM_E, &lord_param, SIZEOF(TY_LORD_PARAM), &read_len);
    if (op_ret != OPRT_OK || (read_len != SIZEOF(TY_LORD_PARAM))) {
        lord_param.phone_rotation = PHONE_ROTE_DEFAULT;
        lord_param.static_electricity_close = STATIC_ELEC_ST_DEFAULT;
        lord_param.local_door_bell_ring = LOCAL_DOOR_BELL_OPEN_DEFAULT;
        lord_param.lcd_auto_install_direction_open = LCD_AUTO_DIRECTION_OPEN_DEFAULT;
        lord_param.ui_language = UI_LANGUAGE_DEFAULT;
        lord_param.lcd_open_time = LCD_OPEN_TIME_DEFAULT;
    }

    w = (UCHAR_T)p_service_data->data[0] * 256 + (UCHAR_T)p_service_data->data[1];
    h = (UCHAR_T)p_service_data->data[2] * 256 + (UCHAR_T)p_service_data->data[3];
    f = (UCHAR_T)p_service_data->data[4] ;

    switch (p_service_data->data[5]) {
    case 0:
        r = 0;
        break;
    case 1:
        r = 90;
        break;
    case 2:
        r = 180;
        break;
    case 3:
        r = 270;
        break;

    default:
        r = -1;
        break;
    }

    chan = (UCHAR_T)p_service_data->data[6] ;
    bit = (UCHAR_T)p_service_data->data[7] ;
    sample = (UCHAR_T)p_service_data->data[8] * 256 + (UCHAR_T)p_service_data->data[9] ;


    camera_param.video_width = w;
    camera_param.video_height = h;
    camera_param.video_rotat_angle = r;
    camera_param.video_fps = f;
    camera_param.video_power_off = p_service_data->data[15];
    ty_param_save(CAMERA_CFG_PARAM_E, &camera_param, sizeof(TY_CAMERA_PARAM));
    PR_NOTICE("camera para %d %d %d %d", camera_param.video_width, camera_param.video_height, camera_param.video_rotat_angle, camera_param.video_fps);
    ty_set_camera_pic_w_h_r_f(w, h, r, f);

    if (chan && bit && sample) {
        audio_param.sample_rate = sample;
        audio_param.bit_dept = bit;
        audio_param.channel_num = chan;
        audio_param.audio_power_off = p_service_data->data[15];
        ty_param_save(AUDIO_CFG_PARAM_E, &audio_param, sizeof(TY_AUDIO_PARAM));
        ty_set_audio_cfg(audio_param.channel_num, audio_param.bit_dept, audio_param.sample_rate);
        PR_NOTICE("audio_param  %d %d %d ", audio_param.sample_rate, audio_param.bit_dept, audio_param.channel_num);
    }

    if (p_service_data->data[10] != 0) {
        user_info.lcd_type = (UCHAR_T)p_service_data->data[10];
        PR_NOTICE("lcd_param  %d ", user_info.lcd_type);
    }
    if (p_service_data->data[11] == 0 || p_service_data->data[11] == 1) {
        user_info.lcd_inversion = (UCHAR_T)p_service_data->data[11];
        PR_NOTICE("lcd_inversion  %d ", user_info.lcd_inversion);
    }
    if (p_service_data->data[12] == 0 || p_service_data->data[12] == 1) {
        user_info.lcd_if = (UCHAR_T)p_service_data->data[12];
        PR_NOTICE("lcd_if  %d ", user_info.lcd_if);
    }
    if (p_service_data->data[13] == 0 || p_service_data->data[13] == 1) {
        user_info.lcd_vertical = (UCHAR_T)p_service_data->data[13];
        PR_NOTICE("lcd_vertical  %d ", user_info.lcd_vertical);
    }
    if (p_service_data->data[14] == 0 || p_service_data->data[14] == 1) {
        user_info.lcd_horizontal = (UCHAR_T)p_service_data->data[14];
        PR_NOTICE("lcd_horizontal  %d ", user_info.lcd_horizontal);
    }
    ty_param_save(LCD_CFG_PARAM_E, &user_info, sizeof(struct lcd_user_info));

    TY_UF_CFG uf_cfg = {0};
    memcpy(&uf_cfg.lcd_info, &user_info, SIZEOF(struct lcd_user_info));
    memcpy(&uf_cfg.camera_param, &camera_param, SIZEOF(TY_CAMERA_PARAM));
    memcpy(&uf_cfg.audio_param, &audio_param, SIZEOF(TY_AUDIO_PARAM));
    memcpy(&uf_cfg.lord_param, &lord_param, SIZEOF(TY_LORD_PARAM));
    op_ret = tuya_fast_param_save(UF_TY_CFG_PARAM_E, &uf_cfg, SIZEOF(TY_UF_CFG));
    PR_NOTICE("tuya_fast_param_save op_ret=%d", op_ret);

    op_ret = ty_uart_protocol_send_direct(uart_ctrl.send_handle, p_service_data->cmd, &ret, 1);
    tuya_hal_system_sleep(100);
    tuya_hal_system_reset();

#if 0
    tuya_video_power_ctrl(FALSE);
    tuya_video_backlight_off();
    INT_T cnt = 0;
    while (1) {
        if (!dev_online("uvc")) {
            break;
        }
        cnt++;
        tuya_hal_system_sleep(100);
        if (cnt > 50) {
            break;
        }
    }

    user_lcd_init();
    audio_cfg_init();
    tuya_video_stop_syn();
    tuya_video_init();
#endif

    return op_ret;
}


STATIC OPERATE_RET ty_uart_reset_factory_handle(IN CHAR_T *p_name, IN TY_CMD_S *p_service_data)
{
    OPERATE_RET op_ret = OPRT_OK;
    module_state.is_local_reset = FALSE;
    uart_ctrl.local_reset_type = RESET_FACTORY_CMD;
    tuya_iot_wf_gw_reset();
    return op_ret;
}

STATIC OPERATE_RET ty_uart_get_usb_type_handle(IN CHAR_T *p_name, IN TY_CMD_S *p_service_data)
{
    OPERATE_RET op_ret = OPRT_OK;
    UCHAR_T ret[56];
    ret[0] = 0;
    ret[1] = (UCHAR_T) tuya_usb_param_get();
    ret[2] = 4; //7916

    UCHAR_T hw_len = strlen("1.0.0");
    ret[3] = hw_len;
    strcpy(ret + 4, "1.0.0");

    UCHAR_T firm_len = strlen(USER_SW_VER);
    ret[4 + hw_len] = 0;
    ret[5 + hw_len] = firm_len;
    strcpy(ret + 6 + hw_len, USER_SW_VER);
    op_ret = ty_uart_protocol_send_direct(uart_ctrl.send_handle, GET_MODULE_INFO_CMD, ret, 6 + hw_len + firm_len);
    return op_ret;
}

STATIC BOOL_T is_exist_auzkey(VOID)
{
    OPERATE_RET op_ret = OPRT_OK;

    //check if has authorized
    op_ret = wd_gw_base_if_read(&(get_gw_cntl()->gw_base));
    if (OPRT_OK != op_ret) {
        PR_ERR("read flash err");
        return FALSE;
    }

    // gateway base info verify
    if (0 == get_gw_cntl()->gw_base.auth_key[0] || \
        0 == get_gw_cntl()->gw_base.uuid[0]) {
        PR_ERR("please write uuid and auth_key first");
        return FALSE;
    }

    return TRUE;
}
STATIC OPERATE_RET ty_uart_prod_test_handle(IN CHAR_T *p_name, IN TY_CMD_S *p_service_data)
{
#define PT_CMD_NET_SCAN             0x00
#define PT_CMD_NET_CONNECT          0x01
#define PT_CMD_LCD_IMAGE_START      0x04
#define PT_CMD_LCD_IMAGE_STOP       0x05
#define PT_CMD_SPK_MIC_START        0x06
#define PT_CMD_SPK_MIC_STOP         0x07
#define PT_CMD_ENTER_LOWPOWER       0x08
#define PT_CMD_MIC_FIRST_SPK_NEXT   0x09
#define PT_CMD_DEVICE_TOTAL_TEST    0x0a

#define TY_WF_TEST_SSID          "tuya_mdev_test"
#define TY_WF_TEST_PSWD          "test1234"
#define PT_NET_TIMEOUT           20     //20s

    OPERATE_RET op_ret = OPRT_OK;
    UCHAR_T ret[2] = {0};
    UINT_T count = 0;
    switch (p_service_data->data[0]) {
    case PT_CMD_NET_SCAN:
        AP_IF_S *ap = NULL;
        if (FALSE == is_exist_auzkey()) {
            PR_ERR("no auzkey!!");
            ret[0] = 0x01;
            ret[1] = 0x01;
        } else {
            op_ret = wf_assign_ap_scan(TY_WF_TEST_SSID, &ap);
            if (OPRT_OK != op_ret) {
                PR_NOTICE("wf_assign_ap_scan failed(%d)", op_ret);
                wf_release_ap(ap);
                ap = NULL;
                ret[0] = 0x01;
                ret[1] = 0x00;
            } else {
                PR_NOTICE("scan test ssid succ!!!");
                ret[0] = 0x00;
                ret[1] = conv_rssi_data(ap->rssi);
                wf_release_ap(ap);
                ap = NULL;
            }
        }
        break;
    case PT_CMD_NET_CONNECT:
        op_ret = wf_wk_mode_set(WWM_STATION);
        if (OPRT_OK != op_ret) {
            PR_ERR("wf_wk_mode_set error:%d", op_ret);
            goto DEAL_ERR;
        }

        op_ret = wf_station_disconnect();
        if (op_ret != OPRT_OK) {
            PR_ERR("wf_station_disconnect err:%d", op_ret);
            goto DEAL_ERR;
        }

        op_ret = wf_station_connect(TY_WF_TEST_SSID, TY_WF_TEST_PSWD);
        if (op_ret != OPRT_OK) {
            PR_ERR("wf_station_connect err:%d", op_ret);
            goto DEAL_ERR;
        }
        WF_STATION_STAT_E wf_stat;
        UINT_T net_timeout = 0;
        while (net_timeout++ < PT_NET_TIMEOUT) {
            wf_station_stat_get(&wf_stat);
            PR_NOTICE("get wf stat = %d", wf_stat);
            if (wf_stat >= WSS_CONN_SUCCESS) {
                ret[0] = 0x00;
                ret[1] = 0x00;
                reset_wifi_store_info();
                break;
            }
            tuya_hal_system_sleep(1000);
        }
        if (net_timeout >= PT_NET_TIMEOUT) {
            ret[0] = 0x01;
            ret[1] = 0x00;
        }
        reset_wifi_store_info();
        break;
DEAL_ERR:
        ret[0] = 0x01;
        ret[1] = 0x01;
        reset_wifi_store_info();
        break;
    case PT_CMD_LCD_IMAGE_START:

        tuya_video_power_ctrl(TRUE);
        while (!ty_video_device_online()) {
            tuya_hal_system_sleep(100);
            count++;
            if (count > 50) {
                ret[0] = 0x01;
                ret[1] = 0x00;
                break;
            }
        }

        tuya_video_lcd_open(LCD_FROM_UART);
        break;
    case PT_CMD_LCD_IMAGE_STOP:
        tuya_video_lcd_ctr(FALSE, LCD_FROM_UART, 0);
        break;
    case PT_CMD_SPK_MIC_START:
#if TCFG_HOST_AUDIO_ENABLE
        tuya_video_power_ctrl(TRUE);
        tuya_lcd_ctrl_timer_off();
        while (!ty_audio_device_online()) {
            tuya_hal_system_sleep(100);
            count++;
            if (count > 50) {
                ret[0] = 0x01;
                ret[1] = 0x00;
                break;
            }
        }
#endif
        ty_device_audio_test(TRUE);
        break;
    case PT_CMD_SPK_MIC_STOP:
        ty_device_audio_test(FALSE);
        tuya_lcd_off_ctrl_start();
        break;
    case PT_CMD_ENTER_LOWPOWER:
        tuya_set_sys_power_off();
        break;
    case PT_CMD_MIC_FIRST_SPK_NEXT:
#if TCFG_HOST_AUDIO_ENABLE
        tuya_video_power_ctrl(TRUE);
        tuya_lcd_off_ctrl_start();
        while (!ty_audio_device_online()) {
            tuya_hal_system_sleep(100);
            count++;
            if (count > 50) {
                ret[0] = 0x01;
                ret[1] = 0x00;
                break;
            }
        }
#endif
        if (OPRT_OK != ty_device_first_recorder_next_paly_test(5)) {
            ret[0] = 0x01;
            ret[1] = 0x00;
            break;
        }
        break;

    case PT_CMD_DEVICE_TOTAL_TEST:
        GW_WIFI_NW_STAT_E cur_nw_stat = 0;
        OPERATE_RET op_ret = get_wf_gw_nw_status(&cur_nw_stat);
        if (OPRT_OK != op_ret) {
            PR_NOTICE("get_wf_gw_nw_status err");
            ret[0] = 0x01;
            ret[1] = 0x00;
            break;
        }
        if (cur_nw_stat != STAT_LOW_POWER) {
            PR_NOTICE("get_wf_gw_nw_status not in lowpower mode");
            ret[0] = 0x01;
            ret[1] = 0x00;
            break;
        }
        if (get_tuya_device_test_st()) {
            PR_NOTICE("test alreay start not over");
            ret[0] = 0x01;
            ret[1] = 0x00;
            break;
        }
        tuya_device_test();
        break;
    default:
        break;
    }
    op_ret = ty_uart_protocol_send_direct(uart_ctrl.send_handle, COMPLETE_PRODUCT_TEST, ret, 2);
    return op_ret;
}

STATIC OPERATE_RET ty_uart_heart_handle(IN CHAR_T *p_name, IN TY_CMD_S *p_service_data)
{
    OPERATE_RET op_ret = OPRT_OK;
    CHAR_T ret = 0;
    ty_uart_protocol_send_direct(uart_ctrl.send_handle, p_service_data->cmd, &ret, 1);
    return op_ret;
}
STATIC TY_CMD_CFG_S g_cmd_msg[] = {
    {HEART_STRING_NAME,             HEART_BEAT_CMD,         ty_uart_heart_handle,                0,     NULL},
    {PRODUCT_STRING_NAME,           PRODUCT_INFO_CMD,       ty_uart_prod_info_handle,            0,     NULL},
    {WIFI_STATE_STRING_NAME,        WIFI_STATE_CMD,         ty_uart_net_sta_handle,              0,     NULL},
    {WIFI_RESET_STRING_NAME,        WIFI_RESET_CMD,         ty_uart_reset_handle,                0,     NULL},
    {WIFI_RESET_SEL_STRING_NAME,    WIFI_RESET_SEL_CMD,     ty_uart_reset_sel_handle,            0,     NULL},
    {DP_UPLORD_STRING_NAME,         DATA_RPT_CMD,           ty_uart_dp_upload_handle,            0,     NULL},
    {DP_UPLORD_WITH_RECORD_STRING_NAME, DATA_RPT_WITH_RECORD_CMD, ty_uart_dp_upload_with_record_handle, 0, NULL},
    {DP_DOWNLOAD_STRING_NAME,       DATA_CTRL_CMD,          ty_uart_dp_download_handle,          0,     NULL},
    {GET_LOCAL_TIME_STRING_NAME,    GET_LOCAL_TIME_CMD,     ty_uart_get_local_time_handle,       0,     NULL},
    {GET_GTM_TIME_STRING_NAME,      GET_GTM_TIME_CMD,       ty_uart_get_gtm_time_handle,         0,     NULL},
    {MCU_OTA_START_STRING_NAME,     MCU_OTA_START_CMD,      ty_uart_mcu_ota_start_handle,        0,     NULL},
    {MCU_OTA_TRANS_STRING_NAME,     MCU_OTA_TRANS_CMD,      ty_uart_mcu_ota_trans_handle,        0,     NULL},
    {GET_WF_SIGAL_STRING_NAME,      GET_WF_SIGAL_CMD,       ty_uart_get_wifi_signal_handle,      0,     NULL},
    {SET_LOG_LEVEL_NAME,            SET_DB_LOG_LEVEL_CMD,   ty_uart_set_log_level_handle,        0,     NULL},
    {GET_MUTI_PASS_NAME,            GET_MUTI_PASS_CMD,      ty_uart_get_mult_pass_handle,        0,     NULL},
    {GET_MUTI_SCHEDULE_PASS_NAME,   GET_MUTI_SCHEDULE_PASS_CMD, ty_uart_get_mult_schedule_pass_handle, 0, NULL},
    {GET_OFFLINE_PASS_NAME,         GET_OFFLINE_PASS_CMD,   ty_uart_get_offline_pass_handle,     0,     NULL},
    {GET_DYN_PASS_NAME,             GET_DYN_PASS_CMD,       ty_uart_get_dynamic_pass_handle,     0,     NULL},
    {SET_BASE_CNV_NAME,             SET_BASE_CNV_CMD,       ty_uart_set_base_conversion_handle,  0,     NULL},
    {GET_REMOTE_DP_CACHE_NAME,      GET_REMOTE_DP_CACHE,    ty_uart_get_dp_cache_handle,         0,     NULL},
    {AUTO_UPGRADE_NAME,             AUTO_UPGRADE_CMD,       ty_uart_auto_upgrade_handle,         0,     NULL},
    {PHOTO_TRIGGER_NAME,            PHOTO_TRIGGER_CMD,      ty_uart_photo_trigger_handle,        0,     NULL},
    {PHOTO_UPLOAD_ACK_NAME,         PHOTO_UPLOAD_ACK_CMD,   ty_uart_photo_upload_ack_handle,     0,     NULL},
    {MOU_RESET_NAME,                MOUDULE_RESET_CMD,      ty_uart_module_reset_ack_handle,     0,     NULL},
    {REQ_WIFI_OTA_NAME,             REQ_WIFI_OTA_CMD,       ty_uart_req_wifi_ota_handle,         0,     NULL},
    {REQ_MCU_OTA_NAME,              REQ_MCU_OTA_CMD,        ty_uart_req_mcu_ota_handle,          0,     NULL},
    {GET_WIFI_STATE_NAME,           GET_WIFI_STATE_CMD,     ty_uart_get_wifi_sta_handle,         0,     NULL},
    {GET_UNIX_TIME_NAME,            GET_UNIX_TIME_CMD,      ty_uart_get_unix_time_handle,        0,     NULL},
    {POWER_OFF_NAME,                POWER_OFF_CMD,          ty_uart_set_power_off_handle,        0,     NULL},
    {SET_LCD_ST_NAME,               SET_LCD_ST_CMD,         ty_uart_set_lcd_status_handle,       0,     NULL},
    {NEW_SET_LCD_ST_NAME,           NEW_SET_LCD_ST_CMD,     ty_uart_set_lcd_status_handle,       0,     NULL},
    {SET_CAMERA_PAR_NAME,           SET_CAMERA_PAR_CMD,     ty_uart_set_camera_para_handle,      0,     NULL},
    {MOUDULE_EXPAND_NAME,           MOUDULE_EXPAND_CMD,     NULL,        RESET_FACTORY_CMD,     ty_uart_reset_factory_handle},
    {GET_MODULE_INFO_NAME,          GET_MODULE_INFO_CMD,    NULL,        0,      ty_uart_get_usb_type_handle},
    {COMPLETE_PRODUCT_TEST_NAME,    COMPLETE_PRODUCT_TEST,  ty_uart_prod_test_handle,            0,      NULL},
};



STATIC OPERATE_RET tuya_read_data_cb(IN TY_RECV_HANDLE recv_handle, IN CONST CHAR_T *p_buf, IN UINT_T buf_len, OUT UINT_T *p_read_len)
{
    return tuya_svc_uart_multi_thread_read(TY_UART0, (const UCHAR_T *)p_buf, buf_len, p_read_len);
}

STATIC OPERATE_RET tuya_recv_data_cb(IN TY_RECV_HANDLE recv_handle, IN TY_CMD_DATA_S *p_cmd_data)
{
    if (NULL == p_cmd_data) {
        return OPRT_INVALID_PARM;
    }
    if (p_cmd_data->cmd != HEART_BEAT_CMD && p_cmd_data->cmd != POWER_OFF_CMD) {
        tuya_low_power_time_set_and_start(0);
    }

    OPERATE_RET op_ret = OPRT_OK;
    PR_NOTICE("uart recv cmd %d", p_cmd_data->cmd);
    if (p_cmd_data->cmd == DATA_RPT_CMD || p_cmd_data->cmd == DATA_RPT_WITH_RECORD_CMD || p_cmd_data->cmd == PHOTO_TRIGGER_CMD) {
        tuya_print_data(p_cmd_data->data, p_cmd_data->datalen);
    }
    op_ret = ty_uart_cmd_list_proc((TY_CMD_S *)p_cmd_data);
    return op_ret;
}

STATIC OPERATE_RET tuya_send_frame_cb(IN TY_SEND_HANDLE send_handle, IN TY_SEND_FRAME_S *p_send_frame)
{
    OPERATE_RET op_ret = OPRT_OK;
    if (SEND_TYPE_DIRECT == p_send_frame->type) {
        op_ret = tuya_svc_uart_multi_thread_send(TY_UART0, (UCHAR_T *)p_send_frame->frame_data, p_send_frame->frame_len);
    } else if (SEND_TYPE_IN_QUE == p_send_frame->type) {
        PR_DEBUG("%s %d %d %d %d", p_send_frame->in_queue_cfg.p_name, p_send_frame->frame_len, p_send_frame->frame_data[3], p_send_frame->in_queue_cfg.timerout_s, p_send_frame->in_queue_cfg.send_time);
        op_ret = tuya_svc_uart_queue_data_in_queue(p_send_frame->in_queue_cfg.p_name, (UCHAR_T *)p_send_frame->frame_data, p_send_frame->frame_len, p_send_frame->in_queue_cfg.timerout_s, p_send_frame->in_queue_cfg.send_time);
    }
    return op_ret;
}

STATIC OPERATE_RET tuya_ota_frame_cb(IN TY_OTA_SEND_FRAME_S *p_ota_data)
{
    OPERATE_RET op_ret = OPRT_OK;

    if (OTA_SEND_TYPE_DIRECT == p_ota_data->type) {
        op_ret = ty_uart_protocol_send_direct(uart_ctrl.send_handle, p_ota_data->cmd, p_ota_data->data, p_ota_data->data_len);
    } else if (OTA_SEND_TYPE_IN_QUE_TIMER_SET == p_ota_data->type) {
        PR_DEBUG("%s %d %d %d %d", p_ota_data->cfg.in_queue_cfg.p_name, p_ota_data->data_len, p_ota_data->cmd, p_ota_data->cfg.in_queue_cfg.timerout_s, p_ota_data->cfg.in_queue_cfg.send_time);
        TY_SEND_IN_QUEUE_CFG_S inqueue_cfg;
        inqueue_cfg.p_name = p_ota_data->cfg.in_queue_cfg.p_name;
        inqueue_cfg.timerout_s = p_ota_data->cfg.in_queue_cfg.timerout_s;
        inqueue_cfg.send_time = p_ota_data->cfg.in_queue_cfg.send_time;
        op_ret = ty_uart_protocol_in_queue_timer_set(uart_ctrl.send_handle, p_ota_data->cmd, p_ota_data->data, p_ota_data->data_len, &inqueue_cfg);
    } else if (OTA_SEND_TYPE_IN_QUE_NORMAL == p_ota_data->type) {
        PR_DEBUG("%s %d %d", p_ota_data->cfg.in_queue_cfg.p_name, p_ota_data->data_len, p_ota_data->cmd);
        op_ret = ty_uart_protocol_in_queue(uart_ctrl.send_handle, p_ota_data->cmd, p_ota_data->data, p_ota_data->data_len, p_ota_data->cfg.in_queue_cfg.p_name);
    } else if (OTA_SEND_TYPE_SYN == p_ota_data->type) {
        PR_DEBUG("%s %d %d %d %d", p_ota_data->cfg.syn_cfg.p_name, p_ota_data->data_len, p_ota_data->cmd, p_ota_data->cfg.syn_cfg.timerout_ms, p_ota_data->cfg.syn_cfg.wait_cmd);
        TY_SEND_SYN_CFG_S syn_cfg;
        syn_cfg.p_name = p_ota_data->cfg.in_queue_cfg.p_name;
        syn_cfg.timerout_ms = p_ota_data->cfg.syn_cfg.timerout_ms;
        syn_cfg.wait_cmd = p_ota_data->cfg.syn_cfg.wait_cmd;
        syn_cfg.ack_cb = p_ota_data->cfg.syn_cfg.ack_cb;
        op_ret = ty_uart_protocol_send_syn(uart_ctrl.send_handle, p_ota_data->cmd, p_ota_data->data, p_ota_data->data_len, &syn_cfg);
    }
    return op_ret;
}

STATIC OPERATE_RET tuya_stream_frame_cb(IN TY_STREAM_SEND_FRAME_S *p_stream_data)
{
    OPERATE_RET op_ret = OPRT_OK;
    if (STREAM_SEND_TYPE_DIRECT == p_stream_data->type) {
        //PR_DEBUG("************************tuya_stream_frame_cb************************");
        op_ret = ty_uart_protocol_send_direct(uart_ctrl.send_handle, p_stream_data->cmd, p_stream_data->data, p_stream_data->data_len);
    } else if (STREAM_SEND_TYPE_IN_QUE_TIMER_SET == p_stream_data->type) {
        PR_DEBUG("%s %d %d %d %d", p_stream_data->cfg.in_queue_cfg.p_name, p_stream_data->data_len, p_stream_data->cmd, p_stream_data->cfg.in_queue_cfg.timerout_s, p_stream_data->cfg.in_queue_cfg.send_time);
        TY_SEND_IN_QUEUE_CFG_S inqueue_cfg;
        inqueue_cfg.p_name = p_stream_data->cfg.in_queue_cfg.p_name;
        inqueue_cfg.timerout_s = p_stream_data->cfg.in_queue_cfg.timerout_s;
        inqueue_cfg.send_time = p_stream_data->cfg.in_queue_cfg.send_time;
        op_ret = ty_uart_protocol_in_queue_timer_set(uart_ctrl.send_handle, p_stream_data->cmd, p_stream_data->data, p_stream_data->data_len, &inqueue_cfg);
    } else if (STREAM_SEND_TYPE_IN_QUE_NORMAL == p_stream_data->type) {
        PR_DEBUG("%s %d %d", p_stream_data->cfg.in_queue_cfg.p_name, p_stream_data->data_len, p_stream_data->cmd);
        op_ret = ty_uart_protocol_in_queue(uart_ctrl.send_handle, p_stream_data->cmd, p_stream_data->data, p_stream_data->data_len, p_stream_data->cfg.in_queue_cfg.p_name);
    } else if (STREAM_SEND_TYPE_SYN == p_stream_data->type) {
        PR_DEBUG("%s %d %d %d %d", p_stream_data->cfg.syn_cfg.p_name, p_stream_data->data_len, p_stream_data->cmd, p_stream_data->cfg.syn_cfg.timerout_ms, p_stream_data->cfg.syn_cfg.wait_cmd);
        TY_SEND_SYN_CFG_S syn_cfg;
        syn_cfg.p_name = p_stream_data->cfg.in_queue_cfg.p_name;
        syn_cfg.timerout_ms = p_stream_data->cfg.syn_cfg.timerout_ms;
        syn_cfg.wait_cmd = p_stream_data->cfg.syn_cfg.wait_cmd;
        syn_cfg.ack_cb = p_stream_data->cfg.syn_cfg.ack_cb;
        op_ret = ty_uart_protocol_send_syn(uart_ctrl.send_handle, p_stream_data->cmd, p_stream_data->data, p_stream_data->data_len, &syn_cfg);
    }
    return op_ret;
}

STATIC OPERATE_RET sys_timer_msg_funtion_init(VOID)
{
    OPERATE_RET op_ret = OPRT_OK;
    UINT_T i = 0;

    for (i = 0; i < CNTSOF(tim_msg_tb); i++) {
        op_ret = cmmod_cr_tm_msg_hand(tim_msg_tb[i].tmm_msg_cb, NULL, tim_msg_tb[i].tm_msg);
        if (OPRT_OK != op_ret) {
            PR_ERR("cmmod_cr_tm_msg_hand err");
            goto EXIT;
        }
        PR_DEBUG("cmmod_cr_tm_msg_hand timerid %d", tim_msg_tb[i].tm_msg);
    }
    return OPRT_OK;

EXIT:
    for (i = 0; i < CNTSOF(tim_msg_tb); i++) {
        cmmod_release_tm_msg(*(tim_msg_tb[i].tm_msg));
        *(tim_msg_tb[i].tm_msg) = NULL;
    }
    return op_ret;
}

OPERATE_RET ty_uart_basic_funtion_init(BASIC_SERVICE_INFO_S *info)
{
    OPERATE_RET op_ret = OPRT_OK;
    if (NULL == info) {
        return OPRT_INVALID_PARM;
    } else {
        memcpy(&main_info, info, SIZEOF(BASIC_SERVICE_INFO_S));
    }
    if (TRUE == uart_ctrl.is_init) {
        PR_NOTICE("have been init already");
        return OPRT_OK;
    }
    TY_RECV_CFG_S recv_cfg;
    recv_cfg.recv_cache_len = TY_UART_CACHE_LEN;
    recv_cfg.recv_cb = tuya_recv_data_cb;
    recv_cfg.read_cb = tuya_read_data_cb;
    op_ret =  ty_uart_protocol_recv_init(&(uart_ctrl.recv_handle), &recv_cfg);
    if (OPRT_OK != op_ret) {
        PR_ERR("ty_uart_protocol_recv_init err:%d", op_ret);
    }
    op_ret =  ty_uart_protocol_send_init(&(uart_ctrl.send_handle), tuya_send_frame_cb);
    if (OPRT_OK != op_ret) {
        PR_ERR("ty_uart_protocol_send_init err:%d", op_ret);
        return op_ret;
    }

    op_ret =  ty_uart_cmd_list_reg(g_cmd_msg, CNTSOF(g_cmd_msg));
    if (OPRT_OK != op_ret) {
        PR_ERR("ty_uart_service_list_init err:%d", op_ret);
        return op_ret;
    }

    op_ret = tuya_ota_service_init(tuya_ota_frame_cb);
    if (OPRT_OK != op_ret) {
        PR_ERR("tuya_mcu_ota_service_init err:%d", op_ret);
        return op_ret;
    }

    op_ret =  tuya_svc_lock_dp_report_init();
    if (OPRT_OK != op_ret) {
        PR_ERR("tuya_svc_lock_dp_report_init err:%d", op_ret);
        return op_ret;
    }

    op_ret =  sys_timer_msg_funtion_init();
    if (OPRT_OK != op_ret) {
        PR_ERR("sys_timer_msg_funtion_init err:%d", op_ret);
        return op_ret;
    }

    op_ret = tuya_svc_lock_offline_pw_init(500);
    if (OPRT_OK != op_ret) {
        PR_ERR("tuya_svc_lock_offline_pw_init failed op_ret:%d", op_ret);
        return op_ret;
    }

    op_ret = ty_photo_proc_init(tuya_stream_frame_cb);
    if (OPRT_OK != op_ret) {
        PR_ERR("ty_photo_proc_init failed op_ret:%d", op_ret);
        return op_ret;
    }
    PR_NOTICE("ty_uart_basic_funtion_init init ok");


    op_ret = sys_add_timer(tuya_device_record_dp_report, NULL, &(uart_ctrl.rp_timer_id));
    if (OPRT_OK != op_ret) {
        PR_ERR("sys_add_timer tuya_device_record_dp_report err:%d", op_ret);
        return op_ret;
    }

    op_ret = sys_add_timer(tuya_device_voice_test, NULL, &(uart_ctrl.voice_test_timer_id));
    if (OPRT_OK != op_ret) {
        PR_ERR("sys_add_timer tuya_device_record_dp_report err:%d", op_ret);
        return op_ret;
    }
    unm_set_dns_cache_priority(DNS_PRIO_REGION);

    //op_ret = ty_uart_protocol_in_queue(uart_ctrl.send_handle,WIFI_STATE_CMD,&wifi_state,UART_SEND_TIME_OUT,WIFI_STATE_STRING_NAME);
    op_ret = ty_uart_protocol_send_direct(uart_ctrl.send_handle, WIFI_STATE_CMD, &wifi_state, 1);
    uart_ctrl.is_init = TRUE;
    return op_ret;
}

TY_SEND_HANDLE tuya_get_send_handle(VOID)
{
    if (FALSE == uart_ctrl.is_init) {
        return NULL;
    }
    return uart_ctrl.send_handle;
}

BOOL_T tuya_get_module_is_init(VOID)
{
    if (FALSE == uart_ctrl.is_init) {
        return FALSE;
    }
    return module_state.init_flag;
}

OPERATE_RET tuya_send_wifi_status(VOID)
{
    //return ty_uart_protocol_in_queue(uart_ctrl.send_handle,WIFI_STATE_CMD,&wifi_state,UART_SEND_TIME_OUT,WIFI_STATE_STRING_NAME);
    return ty_uart_protocol_send_direct(uart_ctrl.send_handle, WIFI_STATE_CMD, &wifi_state, 1);
}

CHAR_T *tuya_get_mcu_version(VOID)
{
    return mcu_info.mcu_sw_ver;
}