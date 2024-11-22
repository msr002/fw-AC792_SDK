/**
 * @file    ty_uart_public_iot.c
 * @author  fengzhiquan@tuya.com
 * @brief   tuya iot os handle
 * @version 1.0
 * @date    2021-07-27
 * @copyright Copyright (c) tuya.inc 2020
 * Provide data point analysis, status callback and other related functions.
 */
#define __TY_UART_PUBLIC_IOT_GLOBALS
#include <string.h>
#include "mem_pool.h"
#include "uni_log.h"
#include "gw_intf.h"
#include "tuya_iot_wifi_api.h"
#include "tuya_uart_public_iot.h"

#define TY_DP_FRAME_MIN             5
#define DP_RECV_BUF_MAX             1024
#define WIFI_SYNC_TIMEOUT           5


typedef struct {
    BOOL_T          init_is;				/* flag of tuya cloud init */
    BOOL_T          mcu_ota_flag;           /* flag of sub device tp. default:FALSE tp=9*/
    UCHAR_T         mcu_ota_tp;             /* sub device tp */
    GW_STATUS_CHANGED_CB	gw_status_cb;	/* tuya gateway status changed callback */
    GW_UG_INFORM_CB		gw_ug_cb;			/* tuya gateway ota firmware available nofity callback. */
    GW_RESET_IFM_CB		gw_reset_cb;		/* tuya gateway restart callback */
    TY_DEV_DP_CB		ty_dev_dp_recv_cb;	/* tuya dp info cmd callback */
    GET_WF_NW_STAT_CB	wf_nw_stat_cb;		/* tuya network check callback (wifi version) */
    GW_UG_INFORM_CB		pre_gw_ug_cb;	    /* tuya gateway ota firmware available pre nofity callback. */
} TY_IOT_CLOUD_S;

STATIC 	TY_IOT_CLOUD_S g_ty_iot_cloud;

/**
 *Calculate the length of the bitmap type.
 * @param  bit_len   bit length.
 * @return length of the bitmap type.
 */
STATIC WORD_T __ty_bitmap_len_proc(UCHAR_T bit_len)
{
    WORD_T len;
    len = bit_len / 8 + ((bit_len % 8 == 0) ? 0 : 1);
    if (len > 4) {
        len = 4;
    }
    return len;
}

/**
 * tuya get data type and length.
 * @param  obj_dp   datapoint
 * @param  type   data type
 * @param  len   data length
 * @return pperation result
 */
STATIC OPERATE_RET __ty_get_obj_type_len(IN CONST TY_OBJ_DP_S *obj_dp, OUT UCHAR_T *type, OUT WORD_T *len)
{
    DEV_CNTL_N_S *dev_cntl = get_gw_dev_cntl();
    INT_T i = 0;
    DP_CNTL_S *dp_cntl =  NULL;
    for (i = 0; i < dev_cntl->dp_num; i++) {
        if (dev_cntl->dp[i].dp_desc.dp_id == obj_dp->dpid) {
            dp_cntl = &dev_cntl->dp[i];
            break;
        }
    }

    if (NULL == dp_cntl) {
        PR_ERR("dp_cntl is NULL");
        return OPRT_INVALID_PARM;
    }

    if (dp_cntl->dp_desc.mode == M_RO) {
        PR_ERR("dp_cntl->dp_desc.mode is M_RO");
        return OPRT_INVALID_PARM;
    }

    if (dp_cntl->dp_desc.type == T_OBJ) {
        switch (dp_cntl->dp_desc.prop_tp) {
        case PROP_BOOL:
            *type = 0x01;
            *len = 0x01;
            break;
        case PROP_VALUE:
            *type = 0x02;
            *len = 0x04;
            break;
        case PROP_STR:
            *type = 0x03;
            *len = strlen(obj_dp->value.dp_str);
            break;
        case PROP_ENUM:
            *type = 0x04;
            *len = 0x01;
            break;
        case PROP_BITMAP:
            *type = 0x05;
            *len = __ty_bitmap_len_proc(dp_cntl->prop.prop_bitmap.max_len);
            break;
        default:
            *type = 0x00;
            *len = 0;
            return OPRT_INVALID_PARM;
        }
    } else {
        PR_DEBUG("dp type is err (not obj_data)");
        return OPRT_INVALID_PARM;
    }
    return OPRT_OK;
}
/**
 * tuya data processing.
 * @param  obj_dp   datapoint
 * @param  type   data type
 * @param  len   data length
 * @param  buf   value data
 * @return null
 */
STATIC VOID __ty_data_proc(IN CONST TY_OBJ_DP_S *obj_dp, UCHAR_T type, WORD_T len, OUT UCHAR_T *buf)
{
    switch (type) {
    case DP_TYPE_BOOL:
        buf[0] = (obj_dp->value.dp_bool == ty_cJSON_False) ? 0x00 : 0x01;
        break;
    case DP_TYPE_VALUE: {
        UINT_T val_data = obj_dp->value.dp_value;
        memcpy(buf, &val_data, len);
    }
    break;
    case DP_TYPE_STRING:
        memcpy(buf, obj_dp->value.dp_str, len);
        break;
    case DP_TYPE_ENUM:
        buf[0] = obj_dp->value.dp_enum;
        break;
    case DP_TYPE_BITMAP:
        if (len == 1) {
            buf[0] = obj_dp->value.dp_bitmap;
        } else if (len == 2) {
            WORD_T bit = obj_dp->value.dp_bitmap;
            memcpy(buf, &bit, len);
        } else if (len == 4) {
            UINT_T bit = obj_dp->value.dp_bitmap;
            memcpy(buf, &bit, len);
        } else {
            PR_ERR("bit map len err");
        }
        break;
    default:
        break;
    }
    return ;
}
/**
 * tuya object datapoint processing.
 * @param  obj_dp   datapoint
 * @return none
 */
STATIC VOID __ty_obj_datapoint_proc(IN CONST TY_OBJ_DP_S *obj_dp)
{
    UCHAR_T type;
    WORD_T len;
    OPERATE_RET ret = OPRT_OK;
    TY_DATAPOINT_DATA_S *dp_data = NULL;

    ret = __ty_get_obj_type_len(obj_dp, &type, &len);
    if (ret != OPRT_OK) {
        PR_ERR("ty_type_len_proc fail");
        return;
    }
    dp_data = (TY_DATAPOINT_DATA_S *)Malloc(SIZEOF(TY_DATAPOINT_DATA_S));
    if (dp_data == NULL) {
        PR_ERR("datapoint data malloc faild!");
        return;
    }
    memset(dp_data, 0, SIZEOF(TY_DATAPOINT_DATA_S));
    dp_data->data = Malloc(len + 1);
    if (NULL == dp_data->data) {
        Free(dp_data);
        return;
    }
    PR_DEBUG("obj_dp->dpid:%d,type:%d,len:%d", obj_dp->dpid, type, len);
    dp_data->dpid = obj_dp->dpid;
    dp_data->type = type;
    dp_data->len = len;
    __ty_data_proc(obj_dp, type, len, dp_data->data);
    if (NULL != g_ty_iot_cloud.ty_dev_dp_recv_cb) {
        g_ty_iot_cloud.ty_dev_dp_recv_cb(dp_data);
    }
    Free(dp_data->data);
    Free(dp_data);
    return;
}

/**
 * tuya raw datapoint processing.
 * @param  raw_dp   datapoint
 * @return none
 */
STATIC VOID __ty_raw_datapoint_proc(IN CONST TY_RECV_RAW_DP_S *raw_dp)
{
    if (NULL == raw_dp) {
        PR_ERR("ty_raw_datapoint_proc parm null");
        return;
    }

    TY_DATAPOINT_DATA_S *dp_data = NULL;
    dp_data = (UCHAR_T *)Malloc(SIZEOF(TY_DATAPOINT_DATA_S));
    if (dp_data == NULL) {
        PR_ERR("datapoint data malloc faild!");
        return;
    }
    memset(dp_data, 0, SIZEOF(TY_DATAPOINT_DATA_S));
    dp_data->data = Malloc(raw_dp->len + 1);
    if (NULL == dp_data->data) {
        Free(dp_data);
        return;
    }
    dp_data->dpid = raw_dp->dpid;
    dp_data->type = DP_TYPE_RAW;
    dp_data->len = raw_dp->len;
    memcpy(dp_data->data, raw_dp->data, raw_dp->len);
    PR_DEBUG("__ty_raw_datapoint_proc dpid=%d type=%d  len=%d", dp_data->dpid, dp_data->type, dp_data->len);
    if (NULL != g_ty_iot_cloud.ty_dev_dp_recv_cb) {
        g_ty_iot_cloud.ty_dev_dp_recv_cb(dp_data);
    }
    Free(dp_data->data);
    Free(dp_data);
    return;
}

/**
 * tuya device status update.
 * @param  status   device statusv
 * @return none
 */
STATIC VOID status_changed_cb(IN CONST GW_STATUS_E status)
{
    PR_DEBUG("gw status changed to %d", status);
    if (NULL != g_ty_iot_cloud.gw_status_cb) {
        g_ty_iot_cloud.gw_status_cb(status);
    }
    return;
}

/**
 * tuya network status change callback.
 * @param  conn_state   network status
 * @return none
 */
STATIC VOID recv_net_status(IN CONST GW_WIFI_NW_STAT_E conn_state)
{
    PR_DEBUG("receive net status changed to %d", conn_state);
    if (NULL != g_ty_iot_cloud.wf_nw_stat_cb) {
        g_ty_iot_cloud.wf_nw_stat_cb(conn_state);
    }
    return;
}

/**
 * tuya gateway upgrade pre-condition callback.
 * @param  fw   device upgrade information
 * @return 0
 */
STATIC INT_T gw_ug_inform_cb(IN CONST FW_UG_S *fw)
{
    INT_T op_ret = OPRT_OK;
    PR_DEBUG("receive gw upgrade info");
    PR_DEBUG("fw->fw_url:%s", fw->fw_url);
    PR_DEBUG("fw->fw_hmac:%s", fw->fw_hmac);
    PR_DEBUG("fw->sw_ver:%s", fw->sw_ver);
    PR_DEBUG("fw->file_size:%d", fw->file_size);
    if (NULL != g_ty_iot_cloud.gw_ug_cb) {
        op_ret = g_ty_iot_cloud.gw_ug_cb(fw);
    }
    return op_ret;
}

STATIC INT_T pre_gw_ug_inform_cb(IN CONST FW_UG_S *fw)
{
    INT_T op_ret = OPRT_OK;
    PR_DEBUG("pre receive gw upgrade info");
    PR_DEBUG("fw->fw_url:%s", fw->fw_url);
    PR_DEBUG("fw->fw_hmac:%s", fw->fw_hmac);
    PR_DEBUG("fw->sw_ver:%s", fw->sw_ver);
    PR_DEBUG("fw->file_size:%d", fw->file_size);
    if (NULL != g_ty_iot_cloud.pre_gw_ug_cb) {
        op_ret = g_ty_iot_cloud.pre_gw_ug_cb(fw);
    }
    return op_ret;
}

/**
 * @brief device reset proc callback
 * @param type   reset reason
 * @retval none
 */
STATIC VOID dev_reset_cb(GW_RESET_TYPE_E type)
{
    /* attention: before restart ,need to save in flash */
    PR_DEBUG("device reset... type:[%d]", type);
    if (NULL != g_ty_iot_cloud.gw_reset_cb) {
        g_ty_iot_cloud.gw_reset_cb(type);
    }
    return;
}

/**
 * tuya handler to process structured DP info.
 * @param  dp_qry   structured datapoint information
 * @return none
 */
STATIC VOID dev_obj_dp_cb(IN CONST TY_RECV_OBJ_DP_S *dp)
{
    INT_T i = 0;
    for (i = 0; i < dp->dps_cnt; i++) {
        __ty_obj_datapoint_proc(&dp->dps[i]);
        tuya_hal_system_sleep(50);
    }
    return;
}

/**
 * tuya handler to process raw DP info.
 * @param  dp_qry   raw datapoint information
 * @return none
 */
STATIC VOID dev_raw_dp_cb(IN CONST TY_RECV_RAW_DP_S *dp)
{
    PR_DEBUG("dpid:%d recv len:%d", dp->dpid, dp->len);

    __ty_raw_datapoint_proc(dp);
    return;
}

/**
 * tuya handler to process structured DP query info.
 * @param  dp_qry   Definition of DP query
 * @return none
 */
STATIC VOID dev_dp_query_cb(IN CONST TY_DP_QUERY_S *dp_qry)
{
    PR_DEBUG("Recv DP Query Cmd");
}

/**
 * tuya sub-device upgrade pre-condition callback.
 * @param  dev_id   device id
 * @param  fw   device upgrade information
 * @return 0
 */
STATIC INT_T dev_ug_inform_cb(IN CONST CHAR_T *dev_id, IN CONST FW_UG_S *fw)
{
    PR_DEBUG("Rev GW Upgrade Info");
    PR_DEBUG("device id:%s", dev_id);
    PR_DEBUG("fw->fw_url:%s", fw->fw_url);
    PR_DEBUG("fw->fw_hmac:%s", fw->fw_hmac);
    PR_DEBUG("fw->sw_ver:%s", fw->sw_ver);
    PR_DEBUG("fw->file_size:%d", fw->file_size);
    return 0;
}


/**
 * tuya uart cloud init.
 * @param  p_iot_info   iot configuration information
 * @param  ty_iot_cb   tuya iot receive and notify callback
 * @return Function Operation Result  OPRT_OK is ok other is fail
 */
OPERATE_RET tuya_uart_cloud_init(IN TY_IOT_INFO_S *p_iot_info, IN TY_IOT_CB_S ty_iot_cb)
{
    OPERATE_RET op_ret = OPRT_COM_ERROR;
    TY_IOT_CBS_S wf_cbs = {
        .gw_status_cb = status_changed_cb, \
        .gw_ug_cb = gw_ug_inform_cb, \
        .gw_reset_cb = dev_reset_cb, \
        .dev_obj_dp_cb = dev_obj_dp_cb, \
        .dev_raw_dp_cb = dev_raw_dp_cb, \
        .dev_dp_query_cb = dev_dp_query_cb, \
        .dev_ug_cb = dev_ug_inform_cb,
        .pre_gw_ug_cb = pre_gw_ug_inform_cb
    };

    g_ty_iot_cloud.gw_status_cb = ty_iot_cb.gw_status_cb;
    g_ty_iot_cloud.gw_ug_cb = ty_iot_cb.gw_ug_cb;
    g_ty_iot_cloud.gw_reset_cb = ty_iot_cb.gw_reset_cb;
    g_ty_iot_cloud.wf_nw_stat_cb = ty_iot_cb.wf_nw_stat_cb;
    g_ty_iot_cloud.ty_dev_dp_recv_cb = ty_iot_cb.ty_dev_dp_recv_cb;
    g_ty_iot_cloud.pre_gw_ug_cb = ty_iot_cb.pre_gw_ug_cb;
    op_ret = tuya_iot_wf_mcu_dev_init(p_iot_info->cfg_mode, p_iot_info->start_mode, \
                                      &wf_cbs, p_iot_info->firmware_key, \
                                      p_iot_info->product_key, p_iot_info->firmware_version, \
                                      p_iot_info->app_sw_version);

    if (OPRT_OK != op_ret) {
        PR_ERR("tuya iot wifi init faild ! err:%d", op_ret);
        return op_ret;
    }

    op_ret = tuya_iot_reg_get_wf_nw_stat_cb(recv_net_status);
    if (OPRT_OK != op_ret) {
        PR_ERR("tuya iot register wifi status faild ! err:%d", op_ret);
        return op_ret;
    }

    g_ty_iot_cloud.init_is = TRUE;
    return OPRT_OK;
}

STATIC WORD_T __get_obj_dp_cnt(WORD_T len, UCHAR_T *data)
{
    WORD_T obj_dp_cnt = 0;
    WORD_T offset = 0;
    WORD_T all_len = len; // WORD_SWAP(len);
    TY_DATAPOINT_DATA_S *dp_data = NULL;
    PR_DEBUG("all_len :%d", all_len);
    while ((all_len - offset) >= TY_DP_FRAME_MIN) {
        dp_data = (TY_DATAPOINT_DATA_S *)(data + offset);
        offset += (4 + WORD_SWAP(dp_data->len));
        PR_DEBUG("dp_data->type :%d,offset:%d", dp_data->type, offset);
        if (dp_data->type >= DP_TYPE_BOOL && dp_data->type <= DP_TYPE_BITMAP) {
            obj_dp_cnt++;
        }
    }
    return obj_dp_cnt;
}

STATIC VOID_T __free_obj_dp_data(TY_OBJ_DP_S *dp_obj_data, WORD_T obj_dp_cnt)
{
    UINT_T i;
    TY_OBJ_DP_S *tmp;
    for (i = 0; i < obj_dp_cnt; i++) {
        tmp = dp_obj_data + i;
        if (tmp->type == PROP_STR) {
            if (tmp->value.dp_str) {
                Free(tmp->value.dp_str), tmp->value.dp_str = NULL;
            }
        }
    }
    if (dp_obj_data) {
        Free(dp_obj_data), dp_obj_data = NULL;
    }
}
