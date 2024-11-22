/***********************************************************
*  File: tuya_low_power.c
*  Author: mjl
*  Date: 20210507
***********************************************************/
#include "app_config.h"
#include "uni_log.h"
#include "tuya_iot_wifi_api.h"
#include "tuya_iot_com_api.h"
#include "tuya_iot_internal_api.h"
#include "tuya_hal_system.h"
#include "sys_timer.h"
#include "tuya_device.h"
#include "tuya_uf_db.h"
#include "tuya_video.h"
#include "tuya_low_power.h"
#include "tuya_uart_common_basic_service.h"

#define  TY_RTC_WKUP_TIME_SEC  (3600*12)
#define LP_FILE_NAME  "ty_lp_file"

#define WRITE_FLASH_INTERVAL  3000
#define FORCE_ENTER_LOWPOWER_INTERVAL  (5*60*1000)

STATIC TIMER_ID  lp_timer_id = 0;
STATIC TIMER_ID  sp_lp_timer_id = 0;
STATIC TIMER_ID  lp_flash_timer_id = 0;
STATIC TIMER_ID  force_lp_timer_id = 0;
STATIC TIMER_ID  lcd_ctr_timer_id = 0;
STATIC UINT_T  low_timer_interval = LOW_POWER_DEFAILT_TIME;
STATIC UINT_T  flash_low_timer_interval = LOW_POWER_DEFAILT_TIME;
STATIC UINT_T  LCD_timer_interval = LCD_PLAY_DEFAILT_TIME;
STATIC UCHAR_T lcd_timer_init = 0;
STATIC UCHAR_T low_power_timer_init = 0;
STATIC BOOL_T enter_once = FALSE;
VOID tuya_low_power_time_set_and_start(UINT_T time);
STATIC OPERATE_RET tuya_low_power_timer_start(VOID);
STATIC OPERATE_RET tuya_lowpower_param_write(CHAR_T *pbuf, UINT_T len)
{
    uFILE *fd = NULL;

    if (NULL == pbuf || len == 0) {
        return OPRT_INVALID_PARM;
    }
    fd = ufopen(LP_FILE_NAME, "w");
    if (NULL == fd) {
        return OPRT_OPEN_FILE_FAILED;
    }

    ufwrite(fd, pbuf, len);

    ufclose(fd);

    return OPRT_OK;
}

STATIC OPERATE_RET tuya_lowpower_param_read(CHAR_T **pbuf, UINT_T *len)
{
    uFILE *fd = NULL;
    UINT_T read_len = 0;
    INT_T file_len = 0;
    CHAR_T *file_buf;

    file_len = ufgetsize(LP_FILE_NAME);
    if (file_len <= 0) {
        return OPRT_OPEN_FILE_FAILED;
    }
    file_buf = Malloc(file_len + 1);
    if (NULL == file_buf) {
        return OPRT_MALLOC_FAILED;
    }
    fd = ufopen(LP_FILE_NAME, (UCHAR_T *)"r");
    if (NULL == fd) {
        Free(file_buf);
        return OPRT_OPEN_FILE_FAILED;
    }
    read_len = ufread(fd, file_buf, file_len);
    ufclose(fd);
    if (file_len != read_len) {
        Free(file_buf);
        return OPRT_COM_ERROR;
    }
    *pbuf = file_buf;
    *len = read_len;
    return OPRT_OK;
}

OPERATE_RET tuya_lowpower_param_delete(VOID)
{
    uFILE *fd = NULL;
    OPERATE_RET op_ret = OPRT_OK;
    PR_DEBUG("tuya_lowpower_param_delete");
    if (TRUE == ufexist(LP_FILE_NAME)) {
        op_ret = ufdelete(LP_FILE_NAME);
        if (OPRT_OK != op_ret) {
            PR_ERR("ufdelete :%s op_ret:%d", LP_FILE_NAME, op_ret);
            return op_ret;
        }
    }
    return OPRT_OK;
}

STATIC VOID tuya_device_write_flash_param_time_cb(UINT_T timerID, PVOID_T pTimerArg)
{
    UINT_T param[2] = {0};
    PR_DEBUG("tuya_device_write_flash_param LCD_timer_interval=%d low_timer_interval=%d", LCD_timer_interval, flash_low_timer_interval);
    param[0] = flash_low_timer_interval;
    param[1] = LCD_timer_interval;
    tuya_lowpower_param_write((CHAR_T *)param, 2 * SIZEOF(UINT_T));
}
STATIC VOID tuya_enter_deep_sleep_rp_status(VOID)
{
    UCHAR_T send_st = 9;
    ty_uart_send_data_direct(WIFI_STATE_CMD, &send_st, SIZEOF(UCHAR_T));
}
extern VOID power_set_soft_poweroff(UINT_T ms);
VOID tuya_set_sys_power_off(VOID)
{
    //SD卡电源使能
    tuya_jl_gpio_inout_set(POWER_SD_CARD_GPIO_PA1, FALSE);
    tuya_jl_gpio_write(POWER_SD_CARD_GPIO_PA1, TRUE);
    //RGB屏背光PWM控制信号
    tuya_lcd_back_light_power_ctr(FALSE);
    //LCD屏电源使能
    tuya_jl_gpio_inout_set(POWER_LCD_GPIO_PB5, FALSE);
    tuya_jl_gpio_write(POWER_LCD_GPIO_PB5, TRUE);


    tuya_enter_deep_sleep_rp_status();
#if TCFG_HOST_AUDIO_ENABLE
    usb_audio_close_process(1);
    uvc_host_camera_out(1);
    tuya_hal_system_sleep(100);
#else
    tuya_hal_system_sleep(100);
#endif
#ifdef CONFIG_RTC_ENABLE                //RTC时钟开关
#if defined(TY_SET_RTC_ALARM_ENABLE) && (TY_SET_RTC_ALARM_ENABLE == 1)
    alarm_wkup_ctrl(1, TY_RTC_WKUP_TIME_SEC, 0); //使用外部RTC电源 关机
#endif
#endif

    //USB摄像头电源使能  true 打开 fals 关闭
    tuya_jl_gpio_inout_set(POWER_USB_GPIO_PA3, FALSE);
    tuya_jl_gpio_write(POWER_USB_GPIO_PA3, FALSE);
    //5V电源使能
    tuya_jl_gpio_inout_set(POWER_5V_GPIO_PA2, FALSE);
    tuya_jl_gpio_write(POWER_5V_GPIO_PA2, FALSE);

    power_set_soft_poweroff(0);
    return;
}
VOID device_spcl_enter_low_power(VOID)
{
#if defined(MCU_CTRL_LOWPER) && (MCU_CTRL_LOWPER == 1)
    if ((FALSE == get_fs_is_update()) && (FALSE == get_ug_flag())) {
        tuya_set_sys_power_off();
    }
#else
#if WIFI_TEST_RX
#else
    if (tuya_qrcode_is_run()) {
        PR_NOTICE("======================exit net cfg=====================\n");
        tuya_set_sys_power_off();
    }
    if ((FALSE == get_fs_is_update()) && (FALSE == get_ug_flag()) && (FALSE == ty_get_stream_status()) && (FALSE == tuya_video_lcd_open_status_get())) {
        PR_NOTICE("======================enter low power=====================\n");
        tuya_set_sys_power_off();
    }
#endif
#endif
}
VOID tuya_force_enter_low_power(UINT_T interval)
{
    sys_start_timer(sp_lp_timer_id, interval, TIMER_ONCE);
}
VOID device_enter_low_power(VOID)
{
#if defined(MCU_CTRL_LOWPER) && (MCU_CTRL_LOWPER == 1)
    if ((FALSE == get_fs_is_update()) && (FALSE == get_ug_flag())) {

        if (0 == tuya_jl_gpio_read(PORT_WAKEUP_IO0)) {
            //tuya_hal_system_sleep(500); //防止低功耗前lcd闪屏
            PR_NOTICE("======================enter low power=====================\n");
            tuya_set_sys_power_off();
        } else {
            tuya_low_power_timer_start();
        }

    }
#else
#if WIFI_TEST_RX
#else
    if ((FALSE == get_fs_is_update()) && (FALSE == get_ug_flag())) {

        if (0 == tuya_jl_gpio_read(PORT_WAKEUP_IO0)) {
            //tuya_hal_system_sleep(500); //防止低功耗前lcd闪屏
            PR_NOTICE("======================enter low power=====================\n");
            tuya_set_sys_power_off();
        } else {
            tuya_low_power_timer_start();
        }

    }
#endif
#endif
}

STATIC VOID tuya_device_entr_lp_time_cb(UINT_T timerID, PVOID_T pTimerArg)
{
    if (!low_power_timer_init) {
        return ;
    }
    device_enter_low_power();
}

STATIC VOID tuya_device_entr_sp_lp_time_cb(UINT_T timerID, PVOID_T pTimerArg)
{
    PR_NOTICE("======================sp enter low power=====================\n");
    if ((FALSE == get_fs_is_update()) && (FALSE == get_ug_flag())) {
        tuya_set_sys_power_off();
    }
}

STATIC VOID tuya_device_entr_force_lp_time_cb(UINT_T timerID, PVOID_T pTimerArg)
{
    if ((FALSE == get_fs_is_update()) && (FALSE == get_ug_flag())) {
        PR_NOTICE("======================enter low power=====================\n");
        tuya_set_sys_power_off();
    }
}

OPERATE_RET tuya_low_power_init(VOID)
{
    OPERATE_RET op_ret = OPRT_OK;
    if (low_power_timer_init) {
        return op_ret;
    }
    op_ret = sys_add_timer(tuya_device_entr_lp_time_cb, NULL, &lp_timer_id);
    if (OPRT_OK != op_ret) {
        PR_ERR("sys_add_timer tuya_device_entr_lp_time_cb err:%d", op_ret);
        return op_ret;
    }

    op_ret = sys_add_timer(tuya_device_entr_sp_lp_time_cb, NULL, &sp_lp_timer_id);
    if (OPRT_OK != op_ret) {
        PR_ERR("sys_add_timer tuya_device_entr_sp_lp_time_cb err:%d", op_ret);
        return op_ret;
    }
    op_ret = sys_add_timer(tuya_device_write_flash_param_time_cb, NULL, &lp_flash_timer_id);
    if (OPRT_OK != op_ret) {
        PR_ERR("sys_add_timer tuya_device_write_flash_param_time_cb err:%d", op_ret);
        return op_ret;
    }

    op_ret = sys_add_timer(tuya_device_entr_force_lp_time_cb, NULL, &force_lp_timer_id);
    if (OPRT_OK != op_ret) {
        PR_ERR("sys_add_timer tuya_device_write_flash_param_time_cb err:%d", op_ret);
        return op_ret;
    } else {
        sys_start_timer(force_lp_timer_id, FORCE_ENTER_LOWPOWER_INTERVAL, TIMER_ONCE);
    }
    CHAR_T *param = NULL;
    UINT_T param_len = 0;
    op_ret = tuya_lowpower_param_read(&param, &param_len);
    if (OPRT_OK == op_ret && param_len == 8) {
        memcpy(&low_timer_interval, param, 4);
        flash_low_timer_interval = low_timer_interval;
        memcpy(&LCD_timer_interval, param + 4, 4);
        PR_NOTICE("param_len=%d LCD_timer_interval=%d low_timer_interval=%d", param_len, LCD_timer_interval, low_timer_interval);
    } else {
        low_timer_interval = ty_get_lcd_open_default_time() * 1000;
        flash_low_timer_interval = low_timer_interval;
        LCD_timer_interval = low_timer_interval;
    }

    if (param) {
        Free(param);
    }
    low_power_timer_init = 1;
    tuya_low_power_time_set_and_start(0);
    return op_ret;
}

STATIC OPERATE_RET tuya_low_power_timer_start(VOID)
{
    if (!low_power_timer_init) {
        return OPRT_COM_ERROR;
    }
    if (get_fs_is_update() || get_ug_flag()) {
        low_timer_interval = LOW_POWER_UPDATE_TIME;
        PR_DEBUG("file update tuya_low_power_timer_start %d", low_timer_interval);
    } else {
        // PR_DEBUG("tuya_low_power_timer_start %d",low_timer_interval);
    }
    return sys_start_timer(lp_timer_id, low_timer_interval, TIMER_ONCE);
}

OPERATE_RET tuya_low_power_timer_stop()
{
    if (!low_power_timer_init) {
        return OPRT_COM_ERROR;
    }
    if (lp_timer_id) {
        return sys_stop_timer(lp_timer_id);
    } else {
        return OPRT_INVALID_PARM;
    }

}

VOID tuya_low_power_timer_increase_and_start(UINT_T increase_time)
{
    if (!low_power_timer_init) {
        return ;
    }
    enter_once = FALSE;
    if (flash_low_timer_interval != low_timer_interval) {
        low_timer_interval = flash_low_timer_interval;
    }
    if (low_timer_interval >= LOW_POWER_MAX_TIME) {
        tuya_low_power_timer_start();
        return;
    }
    low_timer_interval += increase_time;
    flash_low_timer_interval = low_timer_interval;
    //PR_NOTICE("low_timer_interval=%d",low_timer_interval);

    sys_start_timer(lp_flash_timer_id, WRITE_FLASH_INTERVAL, TIMER_ONCE);
    tuya_low_power_timer_start();
}

VOID tuya_low_power_timer_deincrease_and_start(UINT_T decrease_time)
{
    if (!low_power_timer_init) {
        return ;
    }
    enter_once = FALSE;
    if (flash_low_timer_interval != low_timer_interval) {
        low_timer_interval = flash_low_timer_interval;
    }
    if (low_timer_interval <= LOW_POWER_MIN_TIME) {
        low_timer_interval = LOW_POWER_MIN_TIME;
        tuya_low_power_timer_start();
        return;
    }
    low_timer_interval -= decrease_time;
    flash_low_timer_interval = low_timer_interval;
    //PR_NOTICE("low_timer_interval=%d",low_timer_interval);
    sys_start_timer(lp_flash_timer_id, WRITE_FLASH_INTERVAL, TIMER_ONCE);
    tuya_low_power_timer_start();
}

VOID tuya_low_power_timer_flash_set_and_start(UINT_T time)
{
    if (!low_power_timer_init) {
        return ;
    }
    low_timer_interval = time;
    flash_low_timer_interval = low_timer_interval;
    //PR_NOTICE("low_timer_interval=%d",low_timer_interval);
    enter_once = FALSE;
    sys_start_timer(lp_flash_timer_id, WRITE_FLASH_INTERVAL, TIMER_ONCE);
    tuya_low_power_timer_start();
}

VOID tuya_low_power_time_start_from_flash(VOID)
{
    if (!low_power_timer_init) {
        return ;
    }
    low_timer_interval = flash_low_timer_interval;
    enter_once = FALSE;
    //PR_DEBUG("low_timer_interval=%d flash_low_timer_interval=%d",low_timer_interval,flash_low_timer_interval);
    tuya_low_power_timer_start();
}

VOID tuya_low_power_time_set_and_start(UINT_T time)
{
    if (!low_power_timer_init) {
        return ;
    }
    if (time) {
        if (time >= low_timer_interval) {
            low_timer_interval = time;
        }
        PR_DEBUG("low_timer_interval=%d time=%d flash_low_timer_interval=%d", low_timer_interval, time, flash_low_timer_interval);
    } else {
        PR_DEBUG("low_timer_interval=%d ,time=%d flash_low_timer_interval=%d", low_timer_interval, time, flash_low_timer_interval);
    }
    enter_once = FALSE;
    tuya_low_power_timer_start();
}

///////////////////////////////////////////////////////////////////////////////

STATIC OPERATE_RET tuya_lcd_timer_start(VOID)
{
    if (!lcd_timer_init) {
        return OPRT_COM_ERROR;
    }
    //PR_NOTICE("LCD_timer_interval=%d ",LCD_timer_interval);
    return sys_start_timer(lcd_ctr_timer_id, LCD_timer_interval, TIMER_ONCE);
}

STATIC VOID tuya_lcd_ctrl_cb(UINT_T timerID, PVOID_T pTimerArg)
{
    if (!lcd_timer_init) {
        return;
    }

    GW_WIFI_NW_STAT_E cur_nw_stat = 0;
    INT_T op_ret = get_wf_gw_nw_status(&cur_nw_stat);
    if (OPRT_OK == op_ret) {
        if (cur_nw_stat == STAT_AP_STA_UNCFG || cur_nw_stat == STAT_UNPROVISION || cur_nw_stat == STAT_UNPROVISION_AP_STA_UNCFG) {
            tuya_lcd_timer_start();
            return;
        }
    }
    PR_NOTICE("tuya_video_lcd_ctr false ");
    tuya_video_lcd_ctr(FALSE, LCD_FROM_TIMER, 0);
}




OPERATE_RET tuya_video_lcd_ctrl_init(VOID)
{
    OPERATE_RET op_ret = OPRT_OK;
    if (lcd_timer_init) {
        return op_ret;
    }
    op_ret = sys_add_timer(tuya_lcd_ctrl_cb, NULL, &lcd_ctr_timer_id);
    if (OPRT_OK != op_ret) {
        PR_ERR("sys_add_timer tuya_device_entr_lp_time_cb err:%d", op_ret);
        return op_ret;
    }
    lcd_timer_init = 1;
    //PR_NOTICE("tuya_video_lcd_ctrl_init ");
    tuya_lcd_timer_start();
    return op_ret;
}

VOID tuya_lcd_timer_increase_and_start(UINT_T increase_time)
{
    if (!lcd_timer_init) {
        return;
    }
    if (LCD_timer_interval >= LCD_PLAY_MAX_TIME) {
        tuya_lcd_timer_start();
        return;
    }
    LCD_timer_interval += increase_time;
    //PR_NOTICE("LCD_timer_interval=%d",LCD_timer_interval);
    sys_start_timer(lp_flash_timer_id, WRITE_FLASH_INTERVAL, TIMER_ONCE);
    tuya_lcd_timer_start();
}

VOID tuya_lcd_timer_deincrease_and_start(UINT_T decrease_time)
{
    if (!lcd_timer_init) {
        return;
    }
    if (LCD_timer_interval <= LCD_PLAY_MIN_TIME) {
        LCD_timer_interval = LCD_PLAY_MIN_TIME;
        tuya_lcd_timer_start();
        return;
    }
    LCD_timer_interval -= decrease_time;
    //PR_NOTICE("LCD_timer_interval=%d",LCD_timer_interval);
    sys_start_timer(lp_flash_timer_id, WRITE_FLASH_INTERVAL, TIMER_ONCE);
    tuya_lcd_timer_start();
}

VOID tuya_lcd_timer_set_and_start(UINT_T time)
{
    if (!lcd_timer_init) {
        return;
    }
    LCD_timer_interval = time;
    //PR_NOTICE("LCD_timer_interval=%d",LCD_timer_interval);
    sys_start_timer(lp_flash_timer_id, WRITE_FLASH_INTERVAL, TIMER_ONCE);
    tuya_lcd_timer_start();
}
VOID tuya_lcd_off_ctrl_start(VOID)
{
    if (!lcd_timer_init) {
        return;
    }
    //PR_NOTICE("tuya_lcd_off_ctrl_start ");
    tuya_lcd_timer_start();
}

VOID tuya_lcd_ctrl_timer_off(VOID)
{
    if (!lcd_timer_init) {
        return;
    }
    if (lcd_ctr_timer_id) {
        sys_stop_timer(lcd_ctr_timer_id);
        //PR_NOTICE("tuya_lcd_ctrl_timer_off");
    }

}

UINT_T tuya_lcd_timer_get(VOID)
{
    if (!lcd_timer_init) {
        return LCD_PLAY_DEFAILT_TIME;
    }
    return LCD_timer_interval;
}
