/***********************************************************
*  File: tuya_device.c
*  Author: mjl
*  Date: 20210507
***********************************************************/
#include "app_config.h"
#include "tuya_fast_init.h"
#include "tuya_audio_source.h"
#include "base_event_info.h"
#include "tuya_device.h"
#include "uni_log.h"
#include "tuya_hal_system.h"
#include "sys_timer.h"
#include "tuya_video.h"
#include "tuya_rtc.h"
#include "tuya_cloud_wifi_defs.h"
STATIC CHAR_T *p_detect_revc_buf = NULL;
STATIC BOOL_T is_get_pid_info_from_flash = FALSE;
STATIC UINT_T detect_baud;
STATIC BOOL_T enter_mf_flag = FALSE;
STATIC TIMER_ID  prod_test_timer_id = 0;

BOOL_T ty_is_in_mf_test(VOID)
{
    return enter_mf_flag;
}

INT_T event_subscribe_early_init_cb(VOID *data)
{
#ifdef SYS_DEBUG_OPEN
    SetLogManageAttr(TY_LOG_LEVEL_ERR);
#else
    SetLogManageAttr(TY_LOG_LEVEL_NOTICE);
#endif
    pre_app_fast_init();
    return OPRT_OK;
}

VOID pre_app_init(VOID)
{
    //user_lcd_set_default_id(5);
    //ty_set_camera_pic_w_h_r_f(480,320,90,15);
    //http_recv_timeout_set(10);
    ty_subscribe_event(EVENT_SDK_EARLY_INIT_OK, "early_init", event_subscribe_early_init_cb, 0);
}

VOID mf_user_pre_gpio_test_cb(VOID)
{

}

TIMER_ID rtc_sys_timer;
BOOL_T rtc_test_ok = FALSE;
BOOL_T rtc_prod_test_result(VOID)
{
    return rtc_test_ok;
}

VOID sys_rtc_timer_cb(UINT_T timerID, PVOID_T pTimerArg)
{
    time_t timestamp = 0;
    static time_t previous_timestamp = 0;
    tuya_rtc_time_get(&timestamp);
    if (previous_timestamp != 0) {
        if (timestamp != previous_timestamp) {
            rtc_test_ok = TRUE;
        } else {
            rtc_test_ok = FALSE;
        }
        sys_stop_timer(rtc_sys_timer);
        previous_timestamp = 0;
    } else {
        previous_timestamp = timestamp;
    }
    PR_NOTICE("timestamp=%d,rtc_testing:%d", timestamp, rtc_test_ok);
}
#if 0
VOID mf_user_enter_callback(VOID)   // 进入产测回调 进入条件 1、需要移除配网 2、需要在上位机启动后 重启模组。
{
    extern OPERATE_RET product_infor_delete(VOID);
    STATIC BOOL_T flag = FALSE;
    enter_mf_flag = TRUE;
    time_t timestamp = 0;
    INT_T time_zone_seconds;

    tuya_rtc_init();
    tuya_rtc_time_get(&timestamp);
    if (timestamp <= atoi(APP_TIMESTAMP)) {
        timestamp = atoi(APP_TIMESTAMP);
        tuya_rtc_time_set(timestamp);
    }
    tuya_rtc_control(TUYA_DRV_CONFIG_CMD, &time_zone_seconds); // 获取时区信息，以s为单位
    uni_time_set_posix(timestamp, 0);
    uni_set_time_zone_seconds(time_zone_seconds);
    PR_NOTICE("timestamp=%d time_zone_seconds=%d", timestamp, time_zone_seconds);

    system_timer_init();
    sys_add_timer(sys_rtc_timer_cb, NULL, &rtc_sys_timer);
    sys_start_timer(rtc_sys_timer, 1200, TIMER_CYCLE);
    rtc_test_ok = FALSE;

    if (!flag) {
        flag = TRUE;
        tuya_cfg_param_init();
        tuya_lcd_ctrl_timer_off();
        tuya_low_power_timer_stop();
    }
}

// 产测回调 进入条件 1、需要移除配网 2、需要在上位机启动后 重启模组。
OPERATE_RET mf_user_product_test_cb(USHORT_T cmd, UCHAR_T *data, UINT_T len, OUT UCHAR_T **ret_data, OUT USHORT_T *ret_len)
{
    OPERATE_RET op_ret = OPRT_OK;
    PR_DEBUG("###########cmd:%02x len:%d###########", cmd, len);
    tuya_print_data(data, len);

    op_ret = tuya_prod_test(cmd, data, len, ret_data, ret_len);
    return OPRT_OK;
}
#endif // 0


//VOID pre_device_init(VOID)
//{
////    PR_NOTICE("********* firm name : %s version : %s**********", APP_BIN_NAME,USER_SW_VER);
//}




STATIC VOID tuya_device_test_time_cb(UINT_T timerID, PVOID_T pTimerArg)
{
    GW_WIFI_NW_STAT_E cur_nw_stat = 0;
    STATIC UINT_T test_cnt = 0;
    STATIC UINT_T level_cnt = 0;
#define TEST_TIMER_INTERVAL         500
#define MAX_ENTER_DEVICE_TEST_TIME  (3000/TEST_TIMER_INTERVAL)
    OPERATE_RET op_ret = get_wf_gw_nw_status(&cur_nw_stat);
    if (OPRT_OK != op_ret) {
        PR_NOTICE("get_wf_gw_nw_status err");
        return;
    }
    if (cur_nw_stat != STAT_LOW_POWER) {
        PR_NOTICE("get_wf_gw_nw_status not in lowpower mode");
        return;
    }
    test_cnt++;
    if (test_cnt < MAX_ENTER_DEVICE_TEST_TIME) {
        sys_start_timer(prod_test_timer_id, TEST_TIMER_INTERVAL, TIMER_ONCE);
    }

//    INT_T wk_up_reason = system_reset_reason_get();
//
//    INT_T button_value = tuya_jl_gpio_read(BUTTON_MENU_GPIO_PD2);
//    #if defined(TY_BUTTON_HIGH_ACTIVE) && (TY_BUTTON_HIGH_ACTIVE == 1)
//    if((wk_up_reason & (SYS_RST_VDDIO_LOW_PWR | SYS_RST_VDDIO_PWR_ON)) && (button_value) && false == ty_is_in_mf_test())
//    #else
//    if((wk_up_reason & (SYS_RST_VDDIO_LOW_PWR | SYS_RST_VDDIO_PWR_ON)) && (!button_value) && false == ty_is_in_mf_test())
//    #endif
//    {
//        level_cnt++;
//        if(level_cnt >= MAX_ENTER_DEVICE_TEST_TIME) {
//            tuya_device_test();
//        }
//
//    }
}

STATIC OPERATE_RET tuya_device_prod_test_timer_init(VOID)
{
    OPERATE_RET op_ret = OPRT_OK;
    op_ret = sys_add_timer(tuya_device_test_time_cb, NULL, &prod_test_timer_id);
    if (OPRT_OK != op_ret) {
        PR_ERR("sys_add_timer tuya_device_test_lcd_time_cb err:%d", op_ret);
        return op_ret;
    }
    op_ret = sys_start_timer(prod_test_timer_id, 1000, TIMER_ONCE);
    if (OPRT_OK != op_ret) {
        PR_ERR("sys_start_timer  test_lcd_timer_id err:%d", op_ret);
        return op_ret;
    }
    return op_ret;
}

VOID app_init(VOID)
{
#define LOW_POWER_MODE_TIMEOUT 180
    tuya_iot_wf_timeout_set(LOW_POWER_MODE_TIMEOUT);
    OPERATE_RET op_ret = OPRT_OK;
    tuya_cfg_param_init();
    tuya_usb_param_init();
    tuya_usb_power_init();
    tuya_low_power_init();
    tuya_video_lcd_ctrl_init();
    tuya_sd_card_prod_test();
    // #ifdef SYS_DEBUG_OPEN
    // op_ret = tuya_device_system_heapsize_timer_init();
    // if(OPRT_OK != op_ret) {
    //     PR_ERR("tuya_device_system_heapsize_timer_init err:%d",op_ret);
    //     return ;
    // }
    // #endif

#if 0
    op_ret = tuya_device_test_lcd_timer_init();
    if (OPRT_OK != op_ret) {
        PR_ERR("tuya_device_system_heapsize_timer_init err:%d", op_ret);
        return ;
    }
#endif

    op_ret = tuya_device_prod_test_timer_init();
    if (OPRT_OK != op_ret) {
        PR_ERR("tuya_device_system_heapsize_timer_init err:%d", op_ret);
        return ;
    }

//    #if defined(USE_TY_PID_MEMORY) && (USE_TY_PID_MEMORY == 1)
//    op_ret = ty_uart_read_baud(&detect_baud);
//    if(OPRT_OK == op_ret) {
//        PR_NOTICE("ty_uart_read_baud %d",detect_baud);
//        is_get_pid_info_from_flash = product_infor_load();
//    }
//    #endif
//    if(FALSE == is_get_pid_info_from_flash) {
//
//        TY_BAUD_CFG_S baud_cfg = {
//            .send_probe_interval = 0,
//            .read_detect_interval = 0,
//            .baud_list = {
//                .arry_num = 0,
//                .baud_arry =NULL
//            },
//            .data_recv = ty_uart_detect_data_recv_cb,
//            .dev_cbs = {
//                .dev_init = ty_uart_detect_dev_init,
//                .dev_deinit = ty_uart_detect_dev_deinit,
//                .dev_send_packet = ty_uart_detect_data_send_cb,
//                .dev_read_data = ty_uart_detect_data_read_raw_cb
//            }
//        };
//        //自适应锁板mcu波特率 阻塞型，以baud_list设置（不设置默认9600和115200两种）轮询发送ty_uart_detect_data_send_cb中设置的内容，识别到涂鸦协议将以ty_uart_detect_data_recv_cb回调送会应用。
//        op_ret = ty_uart_auto_adapt_baud_block(&baud_cfg,&detect_baud);
//
//        if(OPRT_OK != op_ret) {
//            PR_ERR("ty_uart_auto_adapt_baud_block err:%d",op_ret);
//        }
//    }
    return;
}

//VOID mf_user_callback(VOID)
//{
//
//}

OPERATE_RET user_product_test_cb(USHORT_T cmd, UCHAR_T *data, UINT_T len, OUT UCHAR_T **ret_data, OUT USHORT_T *ret_len)
{
    return OPRT_OK;
}


#if defined(TY_GPIO_TEST_V2) && (TY_GPIO_TEST_V2 == 1)
BOOL_T gpio_test(IN CONST CHAR_T *in, OUT CHAR_T *out)
{
    return gpio_test_all(in, out);
}

#else
BOOL_T gpio_test(VOID)
{
    return gpio_test_all();
}
#endif



STATIC VOID tuya_device_system_heapsize_time_cb(UINT_T timerID, PVOID_T pTimerArg)
{
    OPERATE_RET op_ret = OPRT_OK;
    INT_T heap_size = 0;
    extern VOID get_task_state(VOID *parm);
    get_task_state(NULL); //1分钟以内调用一次才准确
    malloc_stats();

}

STATIC OPERATE_RET tuya_device_system_heapsize_timer_init(VOID)
{
    OPERATE_RET op_ret = OPRT_OK;
    STATIC TIMER_ID  sys_timer_id = 0;
    INT_T heap_size = 0;
    op_ret = sys_add_timer(tuya_device_system_heapsize_time_cb, NULL, &sys_timer_id);
    if (OPRT_OK != op_ret) {
        PR_ERR("sys_add_timer tuya_uart_heart_timer_cb err:%d", op_ret);
        return op_ret;
    }
    heap_size = tuya_hal_system_getheapsize();
    PR_DEBUG("system heapsize is:%d", heap_size);
    op_ret = sys_start_timer(sys_timer_id, 5000, TIMER_CYCLE);
    if (OPRT_OK != op_ret) {
        PR_ERR("sys_start_timer err:%d", op_ret);
        return op_ret;
    }

    return op_ret;
}

#if 0
STATIC VOID tuya_device_test_lcd_time_cb(UINT_T timerID, PVOID_T pTimerArg)
{
#define T_BLUE         	 0x001F
#define T_RED           	 0xF800
#define T_GREEN         	 0x07E0

    STATIC INT_T cnt = 0;
    UINT_T color = T_RED;
    switch (cnt) {
    case 0:
        color = T_RED;
        PR_NOTICE("r");
        break;

    case 1:
        color = T_GREEN;
        PR_NOTICE("g");
        break;

    case 2:
        color = T_BLUE;
        PR_NOTICE("b");
        break;
    }
    lcd_clear_screen(color);
    cnt++;
    if (cnt == 3) {
        cnt = 0;
    }
}
STATIC OPERATE_RET tuya_device_test_lcd_timer_init(VOID)
{
    OPERATE_RET op_ret = OPRT_OK;
    STATIC TIMER_ID  test_lcd_timer_id = 0;
    INT_T heap_size = 0;
    tuya_lcd_back_light_power_ctr(TRUE);
    op_ret = sys_add_timer(tuya_device_test_lcd_time_cb, NULL, &test_lcd_timer_id);
    if (OPRT_OK != op_ret) {
        PR_ERR("sys_add_timer tuya_device_test_lcd_time_cb err:%d", op_ret);
        return op_ret;
    }
    op_ret = sys_start_timer(test_lcd_timer_id, 2000, TIMER_CYCLE);
    if (OPRT_OK != op_ret) {
        PR_ERR("sys_start_timer  test_lcd_timer_id err:%d", op_ret);
        return op_ret;
    }

    return op_ret;
}



STATIC OPERATE_RET ty_uart_funtion_queue_member_cb(IN CONST CHAR_T *p_name, IN UCHAR_T *p_data, IN UINT_T len)
{
    if ((NULL == p_data) || (NULL == p_name)) {
        PR_ERR("ty_uart_funtion_queue_member_cb in parm err pointer is null");
        return OPRT_INVALID_PARM;
    }

    if (0 == len) {
        PR_ERR("ty_uart_funtion_queue_member_cb in parm len is 0");
        return OPRT_INVALID_PARM;
    }

    PR_DEBUG("uart queue memeber send name is:%s", p_name);

    OPERATE_RET op_ret = OPRT_OK;
    if (0 == memcmp(p_name, "uart0", 5)) {
        op_ret = tuya_svc_uart_multi_thread_send(TY_UART, p_data, len);
        if (OPRT_OK != op_ret) {
            PR_ERR("tuya_svc_uart_multi_thread_send err:%d", op_ret);
            return op_ret;
        }
    }

    return op_ret;
}

STATIC OPERATE_RET ty_uart_funtion_queue_self_delete_member_cb(IN CONST CHAR_T *p_name, IN UCHAR_T *p_data, IN UINT_T len)
{
    if ((NULL == p_data) || (NULL == p_name)) {
        PR_ERR("ty_uart_funtion_queue_member_cb in parm err pointer is null");
        return OPRT_INVALID_PARM;
    }

    PR_DEBUG("uart queue self delete memeber name is:%s", p_name);
    return OPRT_OK;
}



STATIC OPERATE_RET ty_uart_first_pack_handle(VOID)
{
    OPERATE_RET op_ret = OPRT_OK;
    TY_CMD_DATA_S data;
    if (p_detect_revc_buf) {
        data.version = p_detect_revc_buf[2];
        data.cmd = p_detect_revc_buf[3];
        data.datalen = p_detect_revc_buf[4] * 256 + p_detect_revc_buf[5];
        data.data = p_detect_revc_buf + 6;
        op_ret = ty_uart_cmd_list_proc(&data);
    }
    return op_ret;
}
#endif // 0

OPERATE_RET device_init(VOID)
{

    OPERATE_RET op_ret = OPRT_OK;
#if 0
    TY_UART_MULTI_CONFIG_S uart_config = {
        .port = TY_UART,
        .baud_rate = detect_baud,
        .bits = TYWL_8B,
        .parity = TYP_NONE,
        .stop = TYS_STOPBIT1,
        .cache_len = TY_UART_CACHE_LEN,
        .unblock_marks = TRUE
    };

    op_ret = tuya_svc_uart_multi_thread_init(uart_config);
    if (OPRT_OK != op_ret) {
        PR_ERR("tuya_svc_uart_multi_thread_init err:%d", op_ret);
        return op_ret;
    }
    op_ret = tuya_svc_uart_queue_sever_init(ty_uart_funtion_queue_member_cb, ty_uart_funtion_queue_self_delete_member_cb, TY_UART_QUEUE_NUM_MAX);
    if (OPRT_OK != op_ret) {
        PR_ERR("tuya_svc_uart_queue_sever_init err:%d", op_ret);
        return op_ret;
    }

    BASIC_SERVICE_INFO_S info = {0};
    strcpy(info.firmware_key, FIRM_KEY);
    strcpy(info.firmware_version, USER_SW_VER);
    op_ret =  ty_uart_basic_funtion_init(&info);
    if (OPRT_OK != op_ret) {
        PR_ERR("ty_uart_recv_funtion_init err:%d", op_ret);
        return op_ret;
    }
#endif // 0
    if (FALSE == is_get_pid_info_from_flash) {
        op_ret =  ty_uart_first_pack_handle();
        if (OPRT_OK != op_ret) {
            PR_ERR("ty_uart_first_pack_handle err:%d", op_ret);
            return op_ret;
        }
    } else {
        tuya_prod_info_cloud_handle();
    }


    return OPRT_OK;
}
