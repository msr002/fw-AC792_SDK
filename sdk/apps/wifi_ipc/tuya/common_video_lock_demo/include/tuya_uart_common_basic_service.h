/***********************************************************
*  File: ty_uart_common_basic_service.h
*  Author: mjl
*  Date: 20210507
***********************************************************/
#ifndef _TUYA_UART_COMMON_BASIC_SERVICE_H
#define _TUYA_UART_COMMON_BASIC_SERVICE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "tuya_cloud_types.h"
#include "tuya_cloud_com_defs.h"

#define HEART_STRING_NAME          			    "uart0_heart"
#define PRODUCT_STRING_NAME          			"uart0_pro"
#define WIFI_STATE_STRING_NAME       			"uart0_sta"
#define WIFI_RESET_STRING_NAME       			"uart0_reset"
#define WIFI_RESET_SEL_STRING_NAME   			"uart0_reset_s"
#define DP_DOWNLOAD_STRING_NAME      			"uart0_down"
#define DP_UPLORD_STRING_NAME        			"uart0_up"
#define DP_UPLORD_WITH_RECORD_STRING_NAME       "uart0_up_rd"
#define GET_LOCAL_TIME_STRING_NAME   			"uart0_time"
#define GET_GTM_TIME_STRING_NAME     			"uart0_gtmtime"
#define MCU_OTA_START_STRING_NAME    			"uart0_mcusta"
#define MCU_OTA_TRANS_STRING_NAME    			"uart0_mcutrans"
#define GET_WF_SIGAL_STRING_NAME     			"uart0_siginal"
#define SET_LOG_LEVEL_NAME           			"uart0_set_log"
#define GET_MUTI_PASS_NAME  			        "uart0_pass"
#define GET_MUTI_SCHEDULE_PASS_NAME  			"uart0_m_pass"
#define GET_OFFLINE_PASS_NAME        			"uart0_offpass"
#define GET_DYN_PASS_NAME            			"uart0_dynpass"
#define SET_BASE_CNV_NAME            			"uart0_base"
#define GET_REMOTE_DP_CACHE_NAME     			"uart0_dpcache"
#define AUTO_UPGRADE_NAME            			"uart0_upgrade"
#define PHOTO_TRIGGER_NAME           			"uart0_trigger"
#define PHOTO_UPLOAD_ACK_NAME        			"uart0_photoack"
#define MOU_RESET_NAME        			        "uart0_reset_m"
#define REQ_WIFI_OTA_NAME        			    "uart0_wifi_ota"
#define REQ_MCU_OTA_NAME        			    "uart0_mcu_ota"
#define GET_WIFI_STATE_NAME                     "uart0_get_sta"
#define GET_UNIX_TIME_NAME                      "uart0_get_unix"
#define POWER_OFF_NAME                          "uart0_pwr_off"
#define MOUDULE_EXPAND_NAME                     "uart0_expand"
#define SET_LCD_ST_NAME                         "uart0_lcd_st"
#define GET_MODULE_INFO_NAME                    "uart0_m_info"
#define SET_CAMERA_PAR_NAME                     "uart0_cam"
#define MOUDULE_BT_NAME                         "uart0_bt"
#define NEW_SET_LCD_ST_NAME                     "uart0_lcd1_st"
#define COMPLETE_PRODUCT_TEST_NAME              "uart0_test"

#define TY_UART_CACHE_LEN        (1024+512)
#define FIRM_KEY_LEN			20
typedef enum {
    WF_STA_EZ = 0x00,
    WF_STA_AP,
    WF_STA_CONNECT_AP_ING,
    WF_STA_CONNECT_AP,
    WF_STA_CONNECT_MQTT,
    WF_STA_LOW_POWER,
} TY_NET_STA_E;

typedef enum {
    HEART_BEAT_CMD = 0x00,
    PRODUCT_INFO_CMD = 0x01,
    WIFI_STATE_CMD = 0x02,
    WIFI_RESET_CMD = 0x03,
    WIFI_RESET_SEL_CMD = 0x04,
    DATA_RPT_CMD = 0x05,
    GET_LOCAL_TIME_CMD = 0x06,
    DATA_RPT_WITH_RECORD_CMD = 0x08,
    DATA_CTRL_CMD = 0x09,
    GET_WF_SIGAL_CMD = 0x0b,
    REQ_WIFI_OTA_CMD = 0x0a,
    REQ_MCU_OTA_CMD = 0x0c,
    MCU_OTA_START_CMD = 0x0d,
    MCU_OTA_TRANS_CMD = 0x0e,
    GET_GTM_TIME_CMD = 0x10,
    GET_DYN_PASS_CMD = 0x12,
    GET_MUTI_PASS_CMD = 0x13,
    GET_MUTI_SCHEDULE_PASS_CMD = 0x14,
    GET_OFFLINE_PASS_CMD = 0x16,
    GET_WIFI_STATE_CMD = 0x1a,
    GET_UNIX_TIME_CMD = 0x1b,
    SET_BASE_CNV_CMD = 0x1c,
    GET_REMOTE_DP_CACHE = 0x15,
    AUTO_UPGRADE_CMD = 0x21,
    POWER_OFF_CMD = 0x22,
    MOUDULE_RESET_CMD = 0x25,
    MOUDULE_EXPAND_CMD = 0x34,
    MOUDULE_BT_CMD = 0x35,
    PHOTO_TRIGGER_CMD = 0x64,
    PHOTO_UPLOAD_ACK_CMD = 0x62,
    SET_LCD_ST_CMD = 0xd0,
    GET_MODULE_INFO_CMD = 0xd1,
    NEW_SET_LCD_ST_CMD = 0xd2,
    SET_CAMERA_PAR_CMD = 0xda,
    SET_DB_LOG_LEVEL_CMD = 0xdb,
    COMPLETE_PRODUCT_TEST = 0xf0,
} TY_CMD_E;

typedef enum {
    RESET_FACTORY_CMD = 0x0A,
} TY_MOUDULE_EXPAND_SON_CMD_E;

typedef enum {
    REPORT_BT_STATE_CMD = 0x04,
    GET_BT_STATE_CMD = 0x05,
    CLOSE_BT_CMD = 0x06,
} TY_MOUDULE_BT_SON_CMD_E;

typedef struct {
    UINT_T  ir_tx_default;
    UINT_T  ir_rx_default;
    UINT_T  ir_tx_num;
    UINT_T *ir_tx_arry;
    UINT_T  ir_rx_num;
    UINT_T *ir_rx_arry;
    UINT_T  all_pin_num;
    UINT_T *all_pin_arry;
} TY_GPIO_S;

typedef OPERATE_RET(*IR_APP_INIT)(UINT_T txpin, UINT_T rxpin);

typedef struct {
    TY_GPIO_S 	ty_gpio;
    IR_APP_INIT ir_app_init;
    CHAR_T      firmware_key[FIRM_KEY_LEN + 1];
    CHAR_T      firmware_version[SW_VER_LEN + 1];
} BASIC_SERVICE_INFO_S;

OPERATE_RET ty_uart_basic_funtion_init(BASIC_SERVICE_INFO_S *info);

#ifdef __cplusplus
}
#endif

#endif
