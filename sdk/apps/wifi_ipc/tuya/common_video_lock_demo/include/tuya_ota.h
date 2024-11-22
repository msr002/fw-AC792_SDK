/***********************************************************
*  File: tuya_ota.h
*  Author: mengjinlong
*  Date: 201211101
***********************************************************/
#ifndef _TUYA_OTA_H
#define _TUYA_OTA_H

#ifdef __cplusplus
extern "C" {
#endif
#include "tuya_cloud_types.h"
#include "tuya_uart_legacy.h"
#include "tuya_cloud_com_defs.h"
#include "svc_mcu_ota.h"
typedef enum {
    OTA_SEND_TYPE_DIRECT = 0,          /*send frame data directly*/
    OTA_SEND_TYPE_SYN,              /*send frame data syn*/
    OTA_SEND_TYPE_IN_QUE_NORMAL,       /*send frame data in queue,wait ack cmd*/
    OTA_SEND_TYPE_IN_QUE_TIMER_SET,    /*send frame data in queue,wait ack cmd*/
} TY_OTA_SEND_TYPE_E;

typedef struct {
    CHAR_T         *p_name;        /*tuya send frame data name*/
    UINT_T          timerout_s;		/*tuya send frame time out*/
    UINT_T          send_time;	    /*tuya send frame send times*/
} TY_OTA_SEND_IN_QUEUE_CFG_S;

typedef struct {
    CHAR_T         *p_name;        /*tuya send frame data name*/
    UINT_T          timerout_ms;		/*tuya send frame time out*/
    UCHAR_T         wait_cmd;	    /*tuya wait cmd*/
    TY_SYN_ACK_HANDLE_CB ack_cb;    /*tuya ack cmd cb*/
} TY_OTA_SEND_SYN_CFG_S;

typedef struct {
    TY_OTA_SEND_TYPE_E          type;           /*tuya send  data type*/
    UCHAR_T                     cmd;           /*tuya send  cmd*/
    UINT_T 		            data_len;		/*tuya send data len*/
    CHAR_T 		            *data;	        /*tuya send  data content*/
    union {
        TY_OTA_SEND_IN_QUEUE_CFG_S  in_queue_cfg;   /*the queue config of sending by queue,if type is SEND_TYPE_IN_QUE_TIMER_SET or SEND_TYPE_IN_QUE_NORMAL,this param can be used*/
        TY_OTA_SEND_SYN_CFG_S   syn_cfg;        /*the queue config of sending by queue,if type is OTA_SEND_TYPE_SYN ,this param can be used*/
    } cfg;
} TY_OTA_SEND_FRAME_S;

typedef OPERATE_RET(*TY_OTA_SEND_FRAME_HANDLE_CB)(IN TY_OTA_SEND_FRAME_S *p_send_frame);

OPERATE_RET tuya_ota_service_init(IN TY_OTA_SEND_FRAME_HANDLE_CB cb);
OPERATE_RET tuya_mcu_ota_service_start(IN FW_UG_S *fw);
OPERATE_RET tuya_mcu_ota_post(IN TY_OTA_POST_RESULT_E result);
INT_T pre_gw_ug_proc(IN CONST FW_UG_S *fw);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
