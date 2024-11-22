/**
 * @file tuya_app_main.c
 * @author www.tuya.com
 * @brief tuya_app_main module is used to
 * @version 0.1
 * @date 2022-10-28
 *
 * @copyright Copyright (c) tuya.inc 2022
 *
 */

#include <stdlib.h>
#include "app_config.h"

#ifdef CONFIG_TUYA_SDK_ENABLE


#include "tuya_iot_config.h"
#include "tuya_cloud_types.h"
#include "tuya_svc_netmgr.h"
#if defined(ENABLE_WIFI_SERVICE) && (ENABLE_WIFI_SERVICE == 1)
#include "tuya_iot_wifi_api.h"
#endif
#if defined(ENABLE_WIRED) && (ENABLE_WIRED == 1)
#include "tuya_iot_base_api.h"
#endif
#include "tuya_iot_com_api.h"
#include "tuya_ws_db.h"

#include "tal_system.h"
#include "tal_log.h"
#include "base_event.h"
#include "mf_test.h"
#include "mqc_app.h"
#if defined(ENABLE_LWIP) && (ENABLE_LWIP == 1)
#include "lwip_init.h"
#endif

#include "tal_uart.h"
#include "dp_process.h"
#include "app_key.h"
#include "app_led.h"

#include "system/includes.h"
#include "uni_log.h"
#include "tal_bluetooth_def.h"

#include "wifi/wifi_connect.h"
#include "app_agent.h"
#include "tuya_video.h"
/***********************************************************
************************macro define************************
***********************************************************/

/* #define PID         "l7lamnxhzgbwvugw" */
/* #define UUID        "uuid0bb4d9704ca45adc" */
/* #define AUTHKEY     "VN18AD3JIttDR74LXN1D2T92XvHLCJy3" */


/* #define PID         "o0jaxrxrjdanps7w" */
/* #define UUID        "uuida80736284ad3d95a" */
/* #define AUTHKEY     "buWiMl8xVAiBEAGy1iVAOXgP42IOGHBv" */

#define PID         "ozmalwlwtiuuryfh"
#define UUID        "uuid5060dd9b1a5eacb5"
#define AUTHKEY     "nehy6loYkolUBZhx30hAubyiD3GJIN3w"


#define USER_SW_VER   "0.0.1"
#define APP_BIN_NAME  "tuya"

#define video_request_realtime 63

int reset_flag = false;
/* The registration code here does not work, you need to apply for a new one.
 * https://developer.tuya.com/cn/docs/iot/lisence-management?id=Kb4qlem97idl0
 */
// #define UUID     "f998xxxxxxxx2409"
// #define AUTHKEY  "WEHAxxxxxxxxxxxxxxxxxxxxxxxxVVkf"

/* network button, LED pin */
//#define KEY_PIN 7
//#define LED_PIN 17



/***********************************************************
***********************function define**********************
***********************************************************/

/***********************************************************
********************function declaration********************
***********************************************************/
extern void tuya_ble_enable_debug(bool enable);

/***********************************************************
***********************variable define**********************
***********************************************************/
/* app thread handle */
STATIC THREAD_HANDLE ty_app_thread = NULL;

/***********************************************************
***********************function define**********************
***********************************************************/
#if defined(ENABLE_QRCODE_ACTIVE) && (ENABLE_QRCODE_ACTIVE == 1)
// qrcode打印
extern INT_T qrcode_exec(INT_T argc, CHAR_T **argv);
STATIC INT_T __qrcode_printf(CHAR_T *msg)
{
    CHAR_T *qrcode_argv[] = {
        "qrcode_exec", "-m", "3", "-t", "ansiutf8", msg
    };

    return qrcode_exec(sizeof(qrcode_argv) / sizeof(qrcode_argv[0]), qrcode_argv);
}

// TuyaOS获取到短链接之后调用此接口输出qrcode打印
STATIC VOID __qrcode_active_shourturl_cb(CONST CHAR_T *shorturl)
{
    if (NULL == shorturl) {
        return;
    }

    TAL_PR_DEBUG("shorturl : %s", shorturl);
    ty_cJSON *item = ty_cJSON_Parse(shorturl);
    __qrcode_printf(ty_cJSON_GetObjectItem(item, "shortUrl")->valuestring);
    ty_cJSON_Delete(item);

    return;
}

#endif

/**
 * @brief SOC device upgrade entry
 *
 * @param[in] fw: firmware info
 *
 * @return OPRT_OK on success. Others on error, please refer to "tuya_error_code.h".
 */
STATIC OPERATE_RET __soc_dev_rev_upgrade_info_cb(IN CONST FW_UG_S *fw)
{
    TAL_PR_DEBUG("SOC Rev Upgrade Info");
    TAL_PR_DEBUG("fw->tp:%d", fw->tp);
    TAL_PR_DEBUG("fw->fw_url:%s", fw->fw_url);
    TAL_PR_DEBUG("fw->fw_hmac:%s", fw->fw_hmac);
    TAL_PR_DEBUG("fw->sw_ver:%s", fw->sw_ver);
    TAL_PR_DEBUG("fw->file_size:%u", fw->file_size);

    return OPRT_OK;
}

/**
 * @brief SOC device cloud state change callback
 *
 * @param[in] status: current status
 *
 * @return none
 */
STATIC VOID_T __soc_dev_status_changed_cb(IN CONST GW_STATUS_E status)
{
    TAL_PR_DEBUG("SOC TUYA-Cloud Status:%d", status);
    return;
}


/**
 * @brief SOC device DP query entry
 *
 * @param[in] dp_qry: DP query list
 *
 * @return none
 */
STATIC VOID_T __soc_dev_dp_query_cb(IN CONST TY_DP_QUERY_S *dp_qry)
{
    UINT32_T index = 0;

    TAL_PR_DEBUG("SOC Rev DP Query Cmd");

    if (dp_qry->cid != NULL) {
        TAL_PR_ERR("soc not have cid.%s", dp_qry->cid);
    }

    if (dp_qry->cnt == 0) {
        TAL_PR_DEBUG("soc rev all dp query");
        respone_device_all_status();
    } else {
        TAL_PR_DEBUG("soc rev dp query cnt:%d", dp_qry->cnt);
        for (index = 0; index < dp_qry->cnt; index++) {
            TAL_PR_DEBUG("rev dp query:%d", dp_qry->dpid[index]);
            // UserTODO
        }
    }

    return;
}

/**
 * @brief SOC device format command data delivery entry
 *
 * @param[in] dp: obj dp info
 *
 * @return none
 */
STATIC VOID_T __soc_dev_obj_dp_cmd_cb(IN CONST TY_RECV_OBJ_DP_S *dp)
{

    TAL_PR_DEBUG("SOC Rev DP Obj Cmd t1:%d t2:%d CNT:%u", dp->cmd_tp, dp->dtt_tp, dp->dps_cnt);
    dp_obj_process(dp->dps, dp->dps_cnt);

    return;
}

/**
 * @brief SOC device transparently transmits command data delivery entry
 *
 * @param[in] dp: raw dp info
 *
 * @return none
 */
STATIC VOID_T __soc_dev_raw_dp_cmd_cb(IN CONST TY_RECV_RAW_DP_S *dp)
{
    TAL_PR_DEBUG("SOC Rev DP Raw Cmd t1:%d t2:%d dpid:%d len:%u", dp->cmd_tp, dp->dtt_tp, dp->dpid, dp->len);

    switch (dp->dpid) {
    case video_request_realtime:
        PR_DEBUG("触发推流");
        /* malloc_stats();  */
        test_stream();
        break;

    default:
        break;

    }
//    if(dp->data && dp->len)
//    {
//        dp_raw_process(dp->dpid, dp->data, dp->len);
//    }

    return;
}

/**
 * @brief  app process when device reset
 *
 * @param[in] type: gateway reset type
 *
 * @return none
 */
STATIC VOID_T __soc_dev_reset_inform_cb(GW_RESET_TYPE_E type)
{
    TAL_PR_DEBUG("reset type %d", type);
    if (GW_LOCAL_RESET_FACTORY == type) { // 本地恢复出厂重置
        printf("本地恢复出厂设置");
        if (reset_flag) {
            reset_flag = true;
        }
    } else if (GW_REMOTE_UNACTIVE == type) { // App 普通重置（解除绑定）
        struct wifi_stored_sta_info wifi_stored_sta_info[32];
        u8 ssid_stored_cnt;
        ssid_stored_cnt = wifi_get_stored_sta_info(wifi_stored_sta_info);
        for (int i = 0; i < ssid_stored_cnt; i++) {
            printf("wifi_get_stored_sta_info[%d]= %s \r\n", i, wifi_stored_sta_info[i].ssid);
            wifi_del_stored_sta_info(wifi_stored_sta_info[i].ssid); //删除
        }

        tuya_iot_wf_gw_unactive();
    } else if (GW_LOCAL_UNACTIVE == type) { // 本地普通重置（解除绑定）
        printf("本地普通重置");
    } else if (GW_REMOTE_RESET_FACTORY == type) { // App 恢复出厂重置
        struct wifi_stored_sta_info wifi_stored_sta_info[32];
        u8 ssid_stored_cnt;
        ssid_stored_cnt = wifi_get_stored_sta_info(wifi_stored_sta_info);
        for (int i = 0; i < ssid_stored_cnt; i++) {
            printf("1:wifi_get_stored_sta_info[%d]= %s \r\n", i, wifi_stored_sta_info[i].ssid);
            wifi_del_stored_sta_info(wifi_stored_sta_info[i].ssid); //删除
        }

        tuya_iot_wf_gw_reset();
    } else if (GW_RESET_DATA_FACTORY == type) { // 激活时数据重置（详见 FAQ）

    }

    return;
}

/**
 * @brief SOC external network status change callback
 *
 * @param[in/out] data
 * @return STATIC
 */
STATIC OPERATE_RET __soc_dev_net_status_cb(VOID *data)
{
    STATIC BOOL_T s_syn_all_status = FALSE;

    TAL_PR_DEBUG("network status changed!");
    if (tuya_svc_netmgr_linkage_is_up(LINKAGE_TYPE_DEFAULT)) {
        TAL_PR_DEBUG("linkage status changed, current status is up");
        if (get_mqc_conn_stat()) {
            TAL_PR_DEBUG("mqtt is connected!");
            if (FALSE == s_syn_all_status) {
                upload_device_all_status();
                s_syn_all_status = TRUE;
            }
            // UserTODO
            /*------------- 流媒体服务----------------------------*/
            //推流初始化
            ty_photo_proc_init(NULL);
        }
    } else {
        TAL_PR_DEBUG("linkage status changed, current status is down");

        // UserTODO
    }

    return OPRT_OK;
}

/**
 * @brief mf uart init
 *
 * @param[in] baud: Baud rate
 * @param[in] bufsz: uart receive buffer size
 *
 * @return none
 */
VOID mf_uart_init_callback(UINT_T baud, UINT_T bufsz)
{
    TAL_UART_CFG_T cfg;
    memset(&cfg, 0, sizeof(TAL_UART_CFG_T));
    cfg.base_cfg.baudrate = baud;
    cfg.base_cfg.databits = TUYA_UART_DATA_LEN_8BIT;
    cfg.base_cfg.parity = TUYA_UART_PARITY_TYPE_NONE;
    cfg.base_cfg.stopbits = TUYA_UART_STOP_LEN_1BIT;
    cfg.rx_buffer_size = bufsz;

    tal_uart_init(TUYA_UART_NUM_0, &cfg);

    return;
}

/**
 * @brief mf uart free
 *
 * @param[in] none
 *
 * @return none
 */
VOID mf_uart_free_callback(VOID)
{
    tal_uart_deinit(TUYA_UART_NUM_0);
    return;
}

/**
 * @brief mf uart send function
 *
 * @param[in] data: send data
 * @param[in] len: send data length
 *
 * @return none
 */
VOID mf_uart_send_callback(IN BYTE_T *data, IN CONST UINT_T len)
{
    tal_uart_write(TUYA_UART_NUM_0, data, len);
    return;
}

/**
 * @brief mf uart receive function
 *
 * @param[in] buf: receive buffer
 * @param[in] len: receive buffer max length
 *
 * @return receive data length
 */
UINT_T mf_uart_recv_callback(OUT BYTE_T *buf, IN CONST UINT_T len)
{
    return tal_uart_read(TUYA_UART_NUM_0, buf, len);
}

/**
 * @brief Product test callback function
 *
 * @param[in] cmd: Command
 * @param[in] data: data
 * @param[out] ret_data: Resulting data
 * @param[out] ret_len: Resulting data length
 *
 * @return OPRT_OK on success. Others on error, please refer to "tuya_error_code.h".
 */
OPERATE_RET mf_user_product_test_callback(USHORT_T cmd, UCHAR_T *data, UINT_T len, OUT UCHAR_T **ret_data, OUT USHORT_T *ret_len)
{
    /* USER todo */
    //gpio  test  refer to tuyaos_demo_examples -> src/examples/service_mf_test

    return OPRT_OK;
}

/**
 * @brief mf configure write callback functions
 *
 * @param[in] none
 *
 * @return none
 */
VOID mf_user_callback(VOID)
{
    return ;
}

/**
 * @brief Callback function before entering the production test
 *
 * @param[in] none
 *
 * @return none
 */
VOID mf_user_enter_mf_callback(VOID)
{
    return ;
}


/**
 * @brief SOC device initialization
 *
 * @param[in] none
 *
 * @return OPRT_OK on success. Others on error, please refer to "tuya_error_code.h".
 */
OPERATE_RET __soc_device_init(VOID_T)
{
    OPERATE_RET rt = OPRT_OK;

    ty_subscribe_event(EVENT_LINK_UP, "quickstart", __soc_dev_net_status_cb, SUBSCRIBE_TYPE_NORMAL);
    ty_subscribe_event(EVENT_LINK_DOWN, "quickstart", __soc_dev_net_status_cb, SUBSCRIBE_TYPE_NORMAL);
    ty_subscribe_event(EVENT_MQTT_CONNECTED, "quickstart", __soc_dev_net_status_cb, SUBSCRIBE_TYPE_NORMAL);

#if (defined(UUID) && defined(AUTHKEY))
//#ifndef ENABLE_KV_FILE
    TUYA_CALL_ERR_LOG(ws_db_init_mf());
//#endif
    /* Set authorization information
     * Note that if you use the default authorization information of the code, there may be problems of multiple users and conflicts,
     * so try to use all the authorizations purchased from the tuya iot platform.
     * Buying guide: https://developer.tuya.com/cn/docs/iot/lisence-management?id=Kb4qlem97idl0.
     * You can also apply for two authorization codes for free in the five-step hardware development stage of the Tuya IoT platform.
     * Authorization information can also be written through the production testing tool.
     * When the production testing function is started and the authorization is burned with the Tuya Cloud module tool,
     * please comment out this piece of code.
     */
#ifdef ENABLE_WIFI_SERVICE
    WF_GW_PROD_INFO_S prod_info = {UUID, AUTHKEY};
    TUYA_CALL_ERR_RETURN(tuya_iot_set_wf_gw_prod_info(&prod_info));
#else
    GW_PROD_INFO_S prod_info = {UUID, AUTHKEY};
    TUYA_CALL_ERR_RETURN(tuya_iot_set_gw_prod_info(&prod_info));
#endif

#else
    /*authorization is burned with the Tuya Cloud module tool
     *If you want to get the specific details, such as GPIO TEST,
     *please refer to the tuyaos_demo_examples -> src/examples/service_mf_test.*/
    MF_IMPORT_INTF_S intf = {0};

    intf.uart_init = mf_uart_init_callback;
    intf.uart_free = mf_uart_free_callback;
    intf.uart_send = mf_uart_send_callback;
    intf.uart_recv = mf_uart_recv_callback;

    intf.mf_user_product_test = mf_user_product_test_callback;
    intf.user_callback = mf_user_callback;
    intf.user_enter_mf_callback = mf_user_enter_mf_callback;

    TUYA_CALL_ERR_RETURN(mf_init(&intf, APP_BIN_NAME, USER_SW_VER, TRUE));

    TAL_PR_NOTICE("mf_init successfully");
#endif

    /* Initialize TuyaOS product information */
    TY_IOT_CBS_S iot_cbs = {0};
    iot_cbs.gw_status_cb    = __soc_dev_status_changed_cb;
    iot_cbs.gw_ug_cb        = __soc_dev_rev_upgrade_info_cb;
    iot_cbs.gw_reset_cb     = __soc_dev_reset_inform_cb;
    iot_cbs.dev_obj_dp_cb   = __soc_dev_obj_dp_cmd_cb;
    iot_cbs.dev_raw_dp_cb   = __soc_dev_raw_dp_cmd_cb;
    iot_cbs.dev_dp_query_cb = __soc_dev_dp_query_cb;


    /*----------------------------------------------------*/
#if defined(ENABLE_QRCODE_ACTIVE) && (ENABLE_QRCODE_ACTIVE == 1)
    iot_cbs.active_shorturl = __qrcode_active_shourturl_cb;
#endif

#ifdef ENABLE_WIFI_SERVICE
    TUYA_CALL_ERR_RETURN(tuya_iot_wf_soc_dev_init(GWCM_OLD, WF_START_SMART_AP_CONCURRENT, &iot_cbs, PID, USER_SW_VER));
#ifdef ENABLE_WIRED
    // init wired linkage
    TUYA_CALL_ERR_RETURN(tuya_svc_wired_init());
#endif
#else
    TUYA_CALL_ERR_RETURN(tuya_iot_soc_init(&iot_cbs, PID, USER_SW_VER));
#endif
    tuya_ble_enable_debug(false);

    /* Network button, LED initialization */
//    app_led_init(LED_PIN);
//    app_key_init(KEY_PIN);

    return 0;
}

/* typedef struct { */
/* INT_T channel_num; */
/* INT_T bit_dept; */
/* INT_T sample_rate; */
/* INT_T audio_power_off; */
/* } TY_AUDIO_PARAM; */

INT_T event_subscribe_early_init_cb1(VOID *data)
{
    TY_AUDIO_PARAM audio_param;
    audio_param.audio_power_off = true;
    audio_param.bit_dept = 16;
    audio_param.channel_num = 1;
    audio_param.sample_rate = 8000;
    tuya_audio_init(&audio_param);

    TY_CAMERA_PARAM carmer_param;
    carmer_param.video_width = CONFIG_VIDEO_IMAGE_W;
    carmer_param.video_height = CONFIG_VIDEO_IMAGE_H;
    carmer_param.video_fps = 10;//10;//10;//10;
    carmer_param.video_rotat_angle = 180;
    carmer_param.video_power_off = 1;
    tuya_video_init(&carmer_param);

    ty_photo_cloudp2p_iot_init();
    return OPRT_OK;
}

STATIC VOID_T user_main(VOID_T)
{
    printf("into user main!");
    OPERATE_RET rt = OPRT_OK;

    /* Initialization, because DB initialization takes a long time,
     * which affects the startup efficiency of some devices,
     * so special processing is performed during initialization to delay initialization of DB
     */

    ty_subscribe_event(EVENT_SDK_EARLY_INIT_OK, "early_init", event_subscribe_early_init_cb1, 0);

    lan_pro_cntl_disable();
    TY_INIT_PARAMS_S init_param = {0};
    init_param.init_db = TRUE;
    strcpy(init_param.sys_env, TARGET_PLATFORM);
    TUYA_CALL_ERR_LOG(tuya_iot_init_params(NULL, &init_param));

    TAL_PR_NOTICE("sdk_info:%s", tuya_iot_get_sdk_info());                        /* print SDK information */

    TAL_PR_NOTICE("name:%s:%s", APP_BIN_NAME, USER_SW_VER);                       /* print the firmware name and version */

    TAL_PR_NOTICE("firmware compiled at %s %s", __DATE__, __TIME__);              /* print firmware compilation time */

    TAL_PR_NOTICE("system reset reason:[%d]", tal_system_get_reset_reason(NULL)); /* print system reboot causes */

    tal_log_set_manage_attr(TAL_LOG_LEVEL_DEBUG);
    /* Initialization device */
    TAL_PR_DEBUG("device_init in");

    TUYA_CALL_ERR_LOG(__soc_device_init());
    TAL_PR_DEBUG("device_init exit");

    return;
}

/**
* @brief  task thread
*
* @param[in] arg:Parameters when creating a task
* @return none
*/
STATIC VOID_T tuya_app_thread(VOID_T *arg)
{
    /* Initialization LWIP first!!! */
#if defined(ENABLE_LWIP) && (ENABLE_LWIP == 1)
    TUYA_LwIP_Init();
#endif
    printf("tuya_app_thread!");
    user_main();
    TAL_PR_DEBUG("user main exit");
    tal_thread_delete(ty_app_thread);
    /* thread_kill(ty_app_thread, KILL_WAIT); */
    ty_app_thread = NULL;
    /* return; */
}

/**
 * @brief user entry function
 *
 * @param[in] none:
 *
 * @return none
 */
VOID_T tuya_app_main(VOID)
{
    THREAD_CFG_T thrd_param = {4096, 10, "tuya_app_main"};
    tal_thread_create_and_start(&ty_app_thread, NULL, NULL, tuya_app_thread, NULL, &thrd_param);
    return;
}
late_initcall(tuya_app_main);
#endif //CONFIG_TUYA_SDK_ENABLE

