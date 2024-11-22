/***********************************************************
*  File: tuya_device.c
*  Author: mjl
*  Date: 20210507
***********************************************************/
#include "app_config.h"
#include "event/key_event.h"
#include "key/key_driver.h"
#include "key/iokey.h"

#include "uni_log.h"
#include "tuya_hal_system.h"
#include "sys_timer.h"
#include "gpio_test.h"
#include "tuya_os_adapter.h"
#include "tuya_iot_wifi_api.h"
#include "tuya_iot_com_api.h"
#include "tuya_iot_internal_api.h"
#include "gw_intf.h"
#include "tuya_device.h"
#include "tuya_button_app.h"
#include "tuya_video.h"
#include "tuya_ui.h"


STATIC BUTTON_KEY_CALLBACK  key_prod_test_cb = NULL;
STATIC BUTTON_KEY_CALLBACK  device_prod_test_cb = NULL;
STATIC INT_T app_key_deal(CHAR_T key_action, CHAR_T key_value)
{
    INT_T ret = TRUE;
    OPERATE_RET op_ret = 0;
    GW_WIFI_NW_STAT_E cur_nw_stat = 0;

    if (FALSE == tuya_get_module_is_init()) {
        goto BUTTON_DEAL;
    }
    op_ret = get_wf_gw_nw_status(&cur_nw_stat);
    if (OPRT_OK != op_ret) {
        PR_ERR("get_wf_gw_status err");
        return ret;
    }
    if ((cur_nw_stat == STAT_UNPROVISION) || (cur_nw_stat == STAT_AP_STA_UNCFG) || (cur_nw_stat == STAT_UNPROVISION_AP_STA_UNCFG)) {
        if (key_action == KEY_EVENT_LONG && key_value == APP_KEY_RIGHT) {
            GW_CNTL_S *gw_cntl = get_gw_cntl();
            gw_cntl->gw_wsm.nc_tp = GWNS_LOWPOWER;
            op_ret = wd_gw_wsm_write(&(gw_cntl->gw_wsm));
            if (OPRT_OK != op_ret) {
                PR_ERR("wd_gw_wsm_write failed! op_ret:%d", op_ret);
            }
            tuya_set_sys_power_off();
        }
        return ret;
    }
    if (get_fs_is_update() || get_ug_flag()) {
        return ret;
    }

BUTTON_DEAL:
    ui_key_control(key_value, key_action);
    return ret;
}


STATIC INT_T key_event_handler(struct key_event *key)
{
    PR_DEBUG("key %d value %d action %d", key->type, key->value, key->action);
    INT_T ret = FALSE;
    INT_T gpio_num = 0;
    switch (key->action) {
    case KEY_EVENT_CLICK:
        if (key_prod_test_cb) {
            switch (key->value) {
            case APP_KEY_MENU:
                gpio_num = BUTTON_MENU_GPIO_PD2;
                break;
            case APP_KEY_LEFT:
                gpio_num = BUTTON_UP_GPIO_PB0;
                break;
            case APP_KEY_RIGHT:
                gpio_num = BUTTON_DOWN_GPIO_PB2;
                break;

            default:
                ret = FALSE;
                return ret;
            }
            key_prod_test_cb(gpio_num, key->action);
            ret = TRUE;
        } else {
            if (FALSE == get_tuya_device_test_st()) {
                ret = app_key_deal(key->action, key->value);
            } else {
                if (device_prod_test_cb) {
                    device_prod_test_cb(gpio_num, key->action);
                }
            }
        }
        break;
    case KEY_EVENT_LONG:
        if (!key_prod_test_cb) {
            if (FALSE == get_tuya_device_test_st()) {
                ret = app_key_deal(key->action, key->value);
            } else {
                if (device_prod_test_cb) {
                    device_prod_test_cb(gpio_num, key->action);
                }
            }
        }
        break;
    default:
        break;
    }
    return ret;
}


OPERATE_RET tuya_button_init(VOID)
{
    extern VOID register_jl_sys_key_event_handler(INT_T(*handler)(struct key_event *));
    STATIC CHAR_T init = 0;
    if (init) {
        return OPRT_OK;
    }
    register_jl_sys_key_event_handler(key_event_handler);
    PR_DEBUG("tuya_button_init");
    init = 1;
    return OPRT_OK;
}

OPERATE_RET tuya_button_prod_test_cb_reg(BUTTON_KEY_CALLBACK cb)
{
    if (NULL == cb) {
        return OPRT_INVALID_PARM;
    }
    key_prod_test_cb = cb;
    return OPRT_OK;
}

OPERATE_RET tuya_button_device_prod_test_cb_reg(BUTTON_KEY_CALLBACK cb)
{
    device_prod_test_cb = cb;
    return OPRT_OK;
}