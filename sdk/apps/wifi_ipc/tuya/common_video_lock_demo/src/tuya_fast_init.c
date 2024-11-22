#include "app_config.h"
#include "uni_log.h"
#include "tuya_cloud_types.h"
#include "tuya_cloud_com_defs.h"
#include "ty_cJSON.h"
#include "tuya_iot_wifi_api.h"
#include "tuya_uf_db.h"
#include "tuya_fast_init.h"
#include "tuya_video.h"
#include "tuya_device.h"
#include "tuya_rtc.h"
#include "sys_timer.h"
#include "tuya_cloud_error_code.h"

STATIC TIMER_ID  en_timer_id = 0;
STATIC TIMER_ID door_bell_timer_id = 0;
BOOL_T  door_bell_init_up = FALSE;
STATIC BOOL_T fast_init = FALSE;
BOOL_T  power_up_init_time_flag = FALSE;
STATIC TY_LORD_PARAM lord_param = {0};
#if defined(TY_BUTTON_HIGH_ACTIVE) && (TY_BUTTON_HIGH_ACTIVE == 1)
INT_T button_init_value = 0;
#else
INT_T button_init_value = 1;
#endif
INT_T door_bell_init_value = 0;
INT_T ty_get_lcd_is_auto_install_direction(VOID);

OPERATE_RET tuya_fast_param_save(IN CONST CHAR_T *file_name, IN UCHAR_T *data, UINT_T len)
{
    uFILE *fd = NULL;
    if (NULL == file_name || NULL == data) {
        return OPRT_INVALID_PARM;
    }

    fd = ufopen(file_name, (CHAR_T *)"w+");
    if (NULL == fd) {
        return OPRT_OPEN_FILE_FAILED;
    }
    ufwrite(fd, data, len);
    ufclose(fd);

    return OPRT_OK;
}

INT_T tuya_fast_param_read(IN CONST CHAR_T *file_name, INOUT UCHAR_T *data, IN UINT_T data_buf_max_len)
{
    uFILE *fd = NULL;
    INT_T read = 0;
    if (NULL == file_name || NULL == data || data_buf_max_len == 0) {
        PR_ERR("data is NULL or data_buf_max_len is 0 !");
        return OPRT_INVALID_PARM;
    }

    fd = ufopen((CHAR_T *)file_name, (CHAR_T *)"r");
    if (NULL == fd) {
        PR_ERR("ufopen file %s is NULL!", file_name);
        return OPRT_OPEN_FILE_FAILED;
    }

    ufseek(fd, 0, UF_SEEK_SET);
    read = ufread(fd, data, data_buf_max_len);
    ufclose(fd);
    return read;
}

OPERATE_RET tuya_fast_param_delete(IN CONST CHAR_T *file_name)
{
    uFILE *fd = NULL;
    OPERATE_RET op_ret = OPRT_OK;
    PR_DEBUG("tuya_lowpower_param_delete");
    if (TRUE == ufexist(file_name)) {
        op_ret = ufdelete(file_name);
        if (OPRT_OK != op_ret) {
            PR_ERR("ufdelete :%s op_ret:%d", file_name, op_ret);
            return op_ret;
        }
    }
    return OPRT_OK;
}

#if 0
STATIC VOID tuya_bord_power_init(VOID)
{
    //5V电源使能
    tuya_jl_gpio_inout_set(POWER_5V_GPIO_PA2, FALSE);
    tuya_jl_gpio_write(POWER_5V_GPIO_PA2, TRUE);

    //SD卡电源使能
    tuya_jl_gpio_inout_set(POWER_SD_CARD_GPIO_PA1, FALSE);
    tuya_jl_gpio_write(POWER_SD_CARD_GPIO_PA1, FALSE);

    //LCD屏电源使能
    tuya_jl_gpio_inout_set(POWER_LCD_GPIO_PB5, FALSE);
    tuya_jl_gpio_write(POWER_LCD_GPIO_PB5, FALSE);

    //USB摄像头电源使能  true 打开 fals 关闭
    tuya_video_power_ctrl(FALSE);

    //RGB屏背光PWM控制信号
    tuya_lcd_back_light_power_ctr(FALSE);
    //LCD RD
    tuya_jl_gpio_inout_set(IO_PORTC_09, FALSE);
    tuya_jl_gpio_write(IO_PORTC_09, TRUE);
    //os_time_dly(10);
    tuya_jl_gpio_inout_set(BUTTON_MENU_GPIO_PD2, TRUE);
    tuya_jl_gpio_mode_set(BUTTON_MENU_GPIO_PD2, PIN_MODE_PULL_NONE);

    tuya_jl_gpio_inout_set(LCD_CHECK_GPIO_PA10, TRUE);
    tuya_jl_gpio_mode_set(LCD_CHECK_GPIO_PA10, PIN_MODE_PULL_NONE);
}

STATIC VOID doorbell_cb(UINT_T timerID, PVOID_T pTimerArg)
{
    INT_T value = 0;
    STATIC BOOL_T is_first = FALSE;
    STATIC INT_T last_value = 0xff;

    value = tuya_jl_gpio_read(PORT_WAKEUP_IO2);
    if ((1 == value) && (last_value == 0)) {  //上升沿
        PR_NOTICE("doorbell_cb");
        if (ty_get_local_ring()) {
            tuya_audio_hw_local_play(1);
        }
        tuya_video_lcd_open(LCD_FROM_INTR);
        door_bell_init_up = TRUE;
    }
    last_value = value;
    sys_start_timer(door_bell_timer_id, 100, TIMER_ONCE);
}

STATIC VOID tuya_doorbell_init(VOID)
{
    STATIC CHAR_T init = 0;
    if (init) {
        return;
    }
    tuya_jl_gpio_inout_set(PORT_WAKEUP_IO2, TRUE);
    tuya_jl_gpio_mode_set(PORT_WAKEUP_IO2, PIN_MODE_PULL_DOWN);
    sys_add_timer(doorbell_cb, NULL, &door_bell_timer_id);
    if (door_bell_timer_id) {
        sys_start_timer(door_bell_timer_id, 10, TIMER_ONCE);
    }
    init = 1;
}


STATIC VOID power_en_wak_up_cb(UINT_T timerID, PVOID_T pTimerArg)
{
    INT_T value = 0;
    STATIC INT_T last_value = 0xff;
    STATIC INT_T time_cnt = 0;
    STATIC BOOL_T time_cnt_flag = 0;
    if (!time_cnt_flag) {
        time_cnt++;
        if (time_cnt < 2) {
            PR_NOTICE("power_up_init_time_flag false %d", time_cnt);
        } else {
            power_up_init_time_flag = TRUE;  //1s
            time_cnt_flag = TRUE;
            PR_NOTICE("power_up_init_time_flag true");
        }
    }

    if (FALSE == tuya_get_module_is_init()) {
        return;
    }
    value = tuya_jl_gpio_read(PORT_WAKEUP_IO0);
    if ((1 == value) && (last_value == 0)) {
        PR_NOTICE("power_en up");
        tuya_send_wifi_status();
    }

    if ((0 == value) && (last_value == 1)) {
        PR_NOTICE("power_en down");
        device_spcl_enter_low_power();
    }

    last_value = value;
}
void set_static_electricity_level(void)
{
    tuya_jl_gpio_inout_set(PORT_WAKEUP_IO2, TRUE);
    tuya_jl_gpio_mode_set(PORT_WAKEUP_IO2, PIN_MODE_PULL_DOWN);
    tuya_jl_gpio_inout_set(BUTTON_MENU_GPIO_PD2, TRUE);
    tuya_jl_gpio_mode_set(BUTTON_MENU_GPIO_PD2, PIN_MODE_PULL_NONE);

    door_bell_init_value = tuya_jl_gpio_read(PORT_WAKEUP_IO2);
    button_init_value = tuya_jl_gpio_read(BUTTON_MENU_GPIO_PD2);
    user_printf("door_bell_init_value=%d button_init_value=%d\n", door_bell_init_value, button_init_value);
}

STATIC VOID tuya_power_en_init(VOID)
{
    STATIC CHAR_T init = 0;
    if (init) {
        return;
    }
    tuya_jl_gpio_inout_set(PORT_WAKEUP_IO0, TRUE);
    tuya_jl_gpio_mode_set(PORT_WAKEUP_IO0, PIN_MODE_PULL_DOWN);
    sys_add_timer(power_en_wak_up_cb, NULL, &en_timer_id);
    if (en_timer_id) {
        sys_start_timer(en_timer_id, 500, TIMER_CYCLE);
    }
    init = 1;
}

STATIC VOID tuya_device_rtc_init(VOID)
{
    time_t timestamp = 0;
    INT_T time_zone_seconds;
    STATIC CHAR_T init = 0;
    if (init) {
        return;
    }
    tuya_rtc_time_get(&timestamp);
    if (timestamp <= 1664467200)  {   //小于22年9点30分
        timestamp = 946684800;        //设置为2000年
        tuya_rtc_time_set(timestamp);
    }
    tuya_rtc_control(TUYA_DRV_CONFIG_CMD, &time_zone_seconds);  //获取时区信息，以s为单位
    uni_time_set_posix(timestamp, 0);
    uni_set_time_zone_seconds(time_zone_seconds);
    init = 1;
    PR_NOTICE("timestamp=%d time_zone_seconds=%d", timestamp, time_zone_seconds);
}
#endif // 0

VOID pre_app_fast_init(VOID)
{
    INT_T read_len = 0;
    TY_UF_CFG uf_cfg = {0};
    OPERATE_RET op_ret = OPRT_OK;
//    system_timer_init();
//    tuya_bord_power_init();
//    tuya_doorbell_init();
//    tuya_power_en_init();
    read_len = tuya_fast_param_read(UF_TY_CFG_PARAM_E, &uf_cfg, SIZEOF(TY_UF_CFG));
    if (read_len <= 0) {
        fast_init = FALSE;
        return;
    }
    if (read_len != SIZEOF(TY_UF_CFG)) {
        fast_init = FALSE;
        return;
    }
//    memcpy(&lord_param,&(uf_cfg.lord_param),SIZEOF(TY_LORD_PARAM));
//    if(ty_get_lcd_is_auto_install_direction()) {
//        PR_NOTICE("LCD_CHECK_GPIO_PA10=%d",tuya_jl_gpio_read(LCD_CHECK_GPIO_PA10));
//        if(0 == tuya_jl_gpio_read(LCD_CHECK_GPIO_PA10)) {
//            uf_cfg.lcd_info.lcd_vertical = !uf_cfg.lcd_info.lcd_vertical;
//        }
//    }
//    if(0 == uf_cfg.lord_param.lcd_open_time) {
//        uf_cfg.lord_param.lcd_open_time = LCD_OPEN_TIME_DEFAULT;
//        lord_param.lcd_open_time = LCD_OPEN_TIME_DEFAULT;
//    }
//    user_ui_lcd_init(&(uf_cfg.lcd_info));
    tuya_video_init(&(uf_cfg.camera_param));
    tuya_audio_init(&(uf_cfg.audio_param));
//    tuya_device_rtc_init();
//    tuya_button_init();
//    PR_NOTICE("lcd if =%d id=%d v=%d h=%d inver=%d lord_param %d %d %d %d %d",uf_cfg.lcd_info.lcd_if,uf_cfg.lcd_info.lcd_type,uf_cfg.lcd_info.lcd_vertical,uf_cfg.lcd_info.lcd_horizontal,uf_cfg.lcd_info.lcd_inversion, \
//                                                                lord_param.static_electricity_close,lord_param.phone_rotation,lord_param.local_door_bell_ring,lord_param.lcd_auto_install_direction_open,lord_param.lcd_open_time);
    fast_init = TRUE;

    return;
}

#if 0
OPERATE_RET tuya_cfg_param_init(VOID)
{
    OPERATE_RET op_ret = OPRT_OK;
    INT_T ret;
    UINT_T read_len = 0;
    TY_UF_CFG uf_cfg = {0};
    struct lcd_user_info info = {0};
    TY_AUDIO_PARAM audio_param = {0};
    TY_CAMERA_PARAM camera_param = {0};
    if (fast_init) {
#if 0
        ty_param_load(LCD_CFG_PARAM_E, &info, SIZEOF(struct lcd_user_info), &read_len);
        PR_NOTICE("LCD_CFG_PARAM_E read_len =%d , %d %d %d %d %d", read_len, info.lcd_if, info.lcd_type, info.lcd_inversion, info.lcd_vertical, info.lcd_horizontal);
        ty_param_load(AUDIO_CFG_PARAM_E, &audio_param, SIZEOF(TY_AUDIO_PARAM), &read_len);
        PR_NOTICE("AUDIO_CFG_PARAM_E read_len=%d ,%d %d %d %d", read_len, audio_param.sample_rate, audio_param.channel_num, audio_param.bit_dept, audio_param.audio_power_off);
        ty_param_load(CAMERA_CFG_PARAM_E, &camera_param, SIZEOF(TY_CAMERA_PARAM), &read_len);
        PR_NOTICE("CAMERA_CFG_PARAM_E  readlen=%d, %d %d %d %d %d", read_len, camera_param.video_width, camera_param.video_height, camera_param.video_rotat_angle, camera_param.video_fps, camera_param.video_power_off);
#endif
        return op_ret;
    }


    UINT_T lcd_type = 0;
    op_ret = ty_param_load(LCD_CFG_PARAM_E, &info, SIZEOF(struct lcd_user_info), &read_len);
    if (op_ret == OPRT_OK) {
        if (read_len == SIZEOF(INT_T)) { //兼容早期参数 只有lcd屏幕类型
            memcpy(&lcd_type, &info, SIZEOF(INT_T));
            memset(&info, 0, SIZEOF(struct lcd_user_info));
            PR_NOTICE("lcd_type=%d", lcd_type);
            info.lcd_inversion = LCD_INVERSION_DEFAULT;
            info.lcd_if = LCD_HW_SEL_DEFAULT;
            info.lcd_type = lcd_type;
        }  else if (read_len == SIZEOF(struct lcd_user_info)) {
            if (info.lcd_if > 1 ||  info.lcd_type > 20 || info.lcd_inversion > 1 || info.lcd_vertical > 1 || info.lcd_horizontal > 1) {
                memset(&info, 0, SIZEOF(struct lcd_user_info));
                info.lcd_type = LCD_TYPE_DEFAULT;
                PR_ERR("param check err");
            }
        } else if (read_len != SIZEOF(struct lcd_user_info)) {
            PR_ERR("read_len=%d", read_len);
            memset(&info, 0, SIZEOF(struct lcd_user_info));
            info.lcd_type = LCD_TYPE_DEFAULT;
        }

    } else {
        memset(&info, 0, SIZEOF(struct lcd_user_info));
        info.lcd_type = LCD_TYPE_DEFAULT;
    }
    PR_NOTICE("LCD_CFG_PARAM_E read_len =%d , %d %d %d %d %d", read_len, info.lcd_if, info.lcd_type, info.lcd_inversion, info.lcd_vertical, info.lcd_horizontal);


    read_len = 0;
    op_ret = ty_param_load(AUDIO_CFG_PARAM_E, &audio_param, SIZEOF(TY_AUDIO_PARAM), &read_len);
    PR_NOTICE("AUDIO_CFG_PARAM_E read_len=%d ,%d %d %d %d", read_len, audio_param.sample_rate, audio_param.channel_num, audio_param.bit_dept, audio_param.audio_power_off);
    if (op_ret == OPRT_OK) {
        if (read_len == SIZEOF(TY_AUDIO_PARAM) - SIZEOF(INT_T)) { //兼容老参数
            if (audio_param.channel_num != 1 || audio_param.bit_dept != 16 || audio_param.sample_rate > 16000) {
                audio_param.channel_num = AUDIO_CHANNEL_DEFAULT;
                audio_param.bit_dept = AUDIO_BIT_DEFAULT;
                audio_param.sample_rate = AUDIO_RATE_DEFAULT;
                audio_param.audio_power_off = USB_POWER_DEFAULT;
                PR_ERR("param check err");
            } else {
                audio_param.audio_power_off = USB_POWER_DEFAULT;
            }

        } else if (read_len == SIZEOF(TY_AUDIO_PARAM)) {
            if (audio_param.channel_num != 1 || audio_param.bit_dept != 16 || audio_param.sample_rate > 16000 || (audio_param.audio_power_off != 0 && audio_param.audio_power_off != 1)) {
                audio_param.channel_num = AUDIO_CHANNEL_DEFAULT;
                audio_param.bit_dept = AUDIO_BIT_DEFAULT;
                audio_param.sample_rate = AUDIO_RATE_DEFAULT;
                audio_param.audio_power_off = USB_POWER_DEFAULT;
                PR_ERR("param check err");
            }
        } else if (read_len != SIZEOF(TY_AUDIO_PARAM)) {
            audio_param.channel_num = AUDIO_CHANNEL_DEFAULT;
            audio_param.bit_dept = AUDIO_BIT_DEFAULT;
            audio_param.sample_rate = AUDIO_RATE_DEFAULT;
            audio_param.audio_power_off = USB_POWER_DEFAULT;
            PR_ERR("read_len=%d", read_len);
        }

    } else {
        audio_param.channel_num = AUDIO_CHANNEL_DEFAULT;
        audio_param.bit_dept = AUDIO_BIT_DEFAULT;
        audio_param.sample_rate = AUDIO_RATE_DEFAULT;
        audio_param.audio_power_off = USB_POWER_DEFAULT;
    }
    PR_NOTICE("AUDIO_CFG_PARAM_E read_len=%d ,%d %d %d %d", read_len, audio_param.sample_rate, audio_param.channel_num, audio_param.bit_dept, audio_param.audio_power_off);



    read_len = 0;
    op_ret = ty_param_load(CAMERA_CFG_PARAM_E, &camera_param, SIZEOF(TY_CAMERA_PARAM), &read_len);
    PR_NOTICE("CAMERA_CFG_PARAM_E op_ret=%d readlen=%d, %d %d %d %d %d", op_ret, read_len, camera_param.video_width, camera_param.video_height, camera_param.video_rotat_angle, camera_param.video_fps, camera_param.video_power_off);
    if (op_ret == OPRT_OK) {
        if (read_len == SIZEOF(TY_CAMERA_PARAM) - SIZEOF(INT_T)) { //兼容老参数
            if ((camera_param.video_width > 1280 && camera_param.video_width < 240) || (camera_param.video_height > 1280 && camera_param.video_height < 240) \
                || (camera_param.video_rotat_angle != 0 && camera_param.video_rotat_angle != 90 && camera_param.video_rotat_angle != 180 && camera_param.video_rotat_angle != 270)) {
                camera_param.video_width = VEDIO_W_DEFAULT;
                camera_param.video_height = VEDIO_H_DEFAULT;
                camera_param.video_rotat_angle = VEDIO_ROTE_DEFAULT;
                camera_param.video_fps = VEDIO_FPS_DEFAULT;
                camera_param.video_power_off = USB_POWER_DEFAULT;
                PR_ERR("param check err");
            } else {
                camera_param.video_power_off = USB_POWER_DEFAULT;
            }

        } else if (read_len == SIZEOF(TY_CAMERA_PARAM)) {
            if ((camera_param.video_width > 1280 && camera_param.video_width < 240) || (camera_param.video_height > 1280 && camera_param.video_height < 240) \
                || (camera_param.video_rotat_angle != 0 && camera_param.video_rotat_angle != 90 && camera_param.video_rotat_angle != 180 && camera_param.video_rotat_angle != 270) \
                || (camera_param.video_power_off != 0 && camera_param.video_power_off != 1)) {
                camera_param.video_width = VEDIO_W_DEFAULT;
                camera_param.video_height = VEDIO_H_DEFAULT;
                camera_param.video_rotat_angle = VEDIO_ROTE_DEFAULT;
                camera_param.video_fps = VEDIO_FPS_DEFAULT;
                camera_param.video_power_off = USB_POWER_DEFAULT;
                PR_ERR("param check err");
            }
        } else if (read_len != SIZEOF(TY_CAMERA_PARAM)) {
            camera_param.video_width = VEDIO_W_DEFAULT;
            camera_param.video_height = VEDIO_H_DEFAULT;
            camera_param.video_rotat_angle = VEDIO_ROTE_DEFAULT;
            camera_param.video_fps = VEDIO_FPS_DEFAULT;
            camera_param.video_power_off = USB_POWER_DEFAULT;
            PR_ERR("read_len=%d", read_len);
        }

    } else {
        camera_param.video_width = VEDIO_W_DEFAULT;
        camera_param.video_height = VEDIO_H_DEFAULT;
        camera_param.video_rotat_angle = VEDIO_ROTE_DEFAULT;
        camera_param.video_fps = VEDIO_FPS_DEFAULT;
        camera_param.video_power_off = USB_POWER_DEFAULT;
    }
    PR_NOTICE("CAMERA_CFG_PARAM_E  readlen=%d, %d %d %d %d %d", read_len, camera_param.video_width, camera_param.video_height, camera_param.video_rotat_angle, camera_param.video_fps, camera_param.video_power_off);

    op_ret = ty_param_load(LORD2_CFG_PARAM_E, &lord_param, SIZEOF(TY_LORD_PARAM), &read_len);
    PR_NOTICE("LORD2_CFG_PARAM_E op_ret=%d readlen=%d, %d %d %d %d %d", op_ret, read_len, lord_param.static_electricity_close, lord_param.phone_rotation, lord_param.local_door_bell_ring, lord_param.lcd_auto_install_direction_open, lord_param.lcd_open_time);
    if (op_ret == OPRT_OK) {
        if (read_len == SIZEOF(TY_LORD_PARAM)) {
            if ((lord_param.phone_rotation != PHONE_ROTE_DEFAULT && lord_param.phone_rotation != 0 && lord_param.phone_rotation != 90 && lord_param.phone_rotation != 180 && lord_param.phone_rotation != 270) \
                || (lord_param.static_electricity_close != 0 && lord_param.static_electricity_close != 1) \
                || (lord_param.local_door_bell_ring != 0 && lord_param.local_door_bell_ring != 1) \
                || (lord_param.lcd_auto_install_direction_open != 0 && lord_param.lcd_auto_install_direction_open != 1)) {
                lord_param.phone_rotation = PHONE_ROTE_DEFAULT;
                lord_param.static_electricity_close = STATIC_ELEC_ST_DEFAULT;
                lord_param.local_door_bell_ring = LOCAL_DOOR_BELL_OPEN_DEFAULT;
                lord_param.lcd_auto_install_direction_open = LCD_AUTO_DIRECTION_OPEN_DEFAULT;
                lord_param.ui_language = UI_LANGUAGE_DEFAULT;
                lord_param.lcd_open_time = LCD_OPEN_TIME_DEFAULT;
                PR_ERR("param check err");
            }
        } else if (read_len != SIZEOF(TY_CAMERA_PARAM)) {
            lord_param.phone_rotation = PHONE_ROTE_DEFAULT;
            lord_param.static_electricity_close = STATIC_ELEC_ST_DEFAULT;
            lord_param.local_door_bell_ring = LOCAL_DOOR_BELL_OPEN_DEFAULT;
            lord_param.lcd_auto_install_direction_open = LCD_AUTO_DIRECTION_OPEN_DEFAULT;
            lord_param.ui_language = UI_LANGUAGE_DEFAULT;
            lord_param.lcd_open_time = LCD_OPEN_TIME_DEFAULT;
            PR_ERR("read_len=%d", read_len);
        }
    } else {
        lord_param.phone_rotation = PHONE_ROTE_DEFAULT;
        lord_param.static_electricity_close = STATIC_ELEC_ST_DEFAULT;
        lord_param.local_door_bell_ring = LOCAL_DOOR_BELL_OPEN_DEFAULT;
        lord_param.lcd_auto_install_direction_open = LCD_AUTO_DIRECTION_OPEN_DEFAULT;
        lord_param.ui_language = UI_LANGUAGE_DEFAULT;
        lord_param.lcd_open_time = LCD_OPEN_TIME_DEFAULT;
    }
    if (0 == lord_param.lcd_open_time) {
        lord_param.lcd_open_time = LCD_OPEN_TIME_DEFAULT;
    }
    PR_NOTICE("LORD2_CFG_PARAM_E op_ret=%d readlen=%d, %d %d %d %d", op_ret, read_len, lord_param.static_electricity_close, lord_param.phone_rotation, lord_param.local_door_bell_ring, lord_param.lcd_auto_install_direction_open);
    memcpy(&uf_cfg.lcd_info, &info, SIZEOF(struct lcd_user_info));
    memcpy(&uf_cfg.camera_param, &camera_param, SIZEOF(TY_CAMERA_PARAM));
    memcpy(&uf_cfg.audio_param, &audio_param, SIZEOF(TY_AUDIO_PARAM));
    memcpy(&uf_cfg.lord_param, &lord_param, SIZEOF(TY_LORD_PARAM));
    op_ret = tuya_fast_param_save(UF_TY_CFG_PARAM_E, &uf_cfg, SIZEOF(TY_UF_CFG));
    PR_NOTICE("tuya_fast_param_save op_ret=%d", op_ret);
    if (ty_get_lcd_is_auto_install_direction()) {
        PR_NOTICE("LCD_CHECK_GPIO_PA10=%d", tuya_jl_gpio_read(LCD_CHECK_GPIO_PA10));
        if (0 == tuya_jl_gpio_read(LCD_CHECK_GPIO_PA10)) {
            uf_cfg.lcd_info.lcd_vertical = !uf_cfg.lcd_info.lcd_vertical;
        }
    }
    user_ui_lcd_init(&(uf_cfg.lcd_info));
    tuya_video_init(&(uf_cfg.camera_param));
    tuya_audio_init(&(uf_cfg.audio_param));
    tuya_device_rtc_init();
    tuya_button_init();
}
#endif // 0

INT_T ty_get_local_ring(VOID)
{
    return lord_param.local_door_bell_ring;
}

INT_T ty_get_static_electricity(VOID)
{
    return lord_param.static_electricity_close;
}

#if 0
INT_T ty_get_lcd_is_auto_install_direction(VOID)
{
    return lord_param.lcd_auto_install_direction_open;
}

INT_T ty_get_ui_default_language(VOID)
{
    return lord_param.ui_language;
}

INT_T ty_get_lcd_open_default_time(VOID)
{
    INT_T time = lord_param.lcd_open_time;
    return time;
}
#endif
