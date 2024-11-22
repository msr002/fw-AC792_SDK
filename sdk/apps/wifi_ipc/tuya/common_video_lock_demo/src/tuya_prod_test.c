/* Includes ------------------------------------------------------------------*/
#include "app_config.h"
#include "system/includes.h"

#include "asm/sfc_norflash_api.h"
#include "ename.h"
#include "mem_pool.h"
#include "tuya_hal_system.h"
#include "uni_thread.h"
#include "tuya_prod_test.h"
#include "mf_test.h"
#include "sys_timer.h"
#include "tuya_video.h"
#include "tuya_fast_init.h"
#include "uni_msg_queue.h"
#include "tuya_hal_semaphore.h"
/* Private macros ------------------------------------------------------------*/

#define PRODUCT_TEST_MAX_IMG_SIZE       (80 * 1024)
#define SN_CFG_TYPE_PARAM_E             "sn_param"
/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
STATIC  BOOL_T  get_config_file = FALSE;
STATIC  BOOL_T  get_logo_file = FALSE;
STATIC  BOOL_T  get_rf_file = FALSE;
STATIC INT_T file_max_size = 0;

STATIC UCHAR_T *camera_data = NULL;
STATIC UINT_T camera_data_len = 0;
STATIC TIMER_ID  prod_lp_timer_id = 0;
STATIC THRD_HANDLE  sd_handle = NULL;
/**
 * @brief: 产测-红外灯
 * @param none
 * @attention:
 * @retval: OPERATE_RET
 */
OPERATE_RET product_test_ir_exec(VOID)
{
    OPERATE_RET op_ret = OPRT_OK;

    return op_ret;
}



/**
 * @brief: 产测-抓图
 * @param none
 * @attention:
 * @retval: OPERATE_RET
 */
OPERATE_RET product_test_ipc_catch_img_exec(OUT UINT_T *img_size)
{
    OPERATE_RET ret = OPRT_OK;
    UINT_T count = 0;
    STATIC BOOL_T s_camera_init = FALSE;

    if (img_size == NULL) {
        return OPRT_INVALID_PARM;
    }

    //初始化
    if (s_camera_init == FALSE) {
        s_camera_init = TRUE;
    }
    while (false == ty_video_device_online()) {
        tuya_hal_system_sleep(100);
        count++;
        if (count > 50) {
            return OPRT_INVALID_PARM;
        }
    }
    tuya_video_ctr(TRUE, 0);
    tuya_hal_system_sleep(10);
    ret = get_image_jpeg(&camera_data, &camera_data_len, 3000);

    *img_size = camera_data_len;

    return ret;
}

/**
 * @brief: 产测-拿图
 * @param none
 * @attention:
 * @retval: OPERATE_RET
 */
OPERATE_RET product_test_ipc_get_img_exec(VOID)
{
    OPERATE_RET ret = OPRT_OK;
    tuya_uart_t *uart;
    INT_T i = 0;

    uart = (tuya_uart_t *)tuya_driver_find(TUYA_DRV_UART, TUYA_UART0);
    //直接发送图片数据
    PR_DEBUG("uart->cfg.baudrate=%d ", uart->cfg.baudrate);
    if (camera_data_len != 0 && uart != NULL) {
        tuya_uart_write(uart, camera_data, camera_data_len);
        tuya_hal_system_sleep(1000);
        PR_DEBUG("camera data:%p len = %d", camera_data, camera_data_len);
    } else {
        ret = OPRT_COM_ERROR;
    }
    if (camera_data) {
        Free(camera_data);
        camera_data = NULL;
    }
    //波特率变回9600
    ret = tuya_uart_deinit(uart);
    if (OPRT_OK != ret) {
        PR_ERR("uart deinit failed %d", ret);
        return ret;
    }
    tuya_hal_system_sleep(10);
    TUYA_UART_8N1_CFG(uart, TUYA_UART_BAUDRATE_9600, 4160, TUYA_DRV_NONBLOCK_FLAG);

    ret = tuya_uart_init(uart);
    if (OPRT_OK != ret) {
        PR_ERR("uart init failed %d", ret);
    }

    return ret;
}


/**
 * @brief: 获取产测类型
 * @param obj: 待检测json对象
 * @attention:
 * @retval: type字符串
 */
CHAR_T *product_test_get_test_item(IN ty_cJSON *obj, IN CHAR_T *string_item)
{
    ty_cJSON *item = NULL;

    if (obj == NULL) {
        return NULL;
    }

    //获取type字段
    item = ty_cJSON_GetObjectItem(obj, string_item);
    if (item == NULL) {
        return NULL;
    }

    //查看字段是否为字符类型
    if ((item->type & 0xFF) != ty_cJSON_String) {
        return NULL;
    }

    return item->valuestring;
}



STATIC SEM_HANDLE button_sem;
STATIC UINT_T button_num = 0;
STATIC VOID button_test_cb(INT_T gpio_no, CHAR_T type)
{
    button_num = gpio_no;
    ty_cJSON *root = NULL;
    root = ty_cJSON_CreateObject();
    if (root == NULL) {
        return;
    }
    ty_cJSON_AddNumberToObject(root, "keyID", button_num);

    CHAR_T *ret_data = (CHAR_T *)ty_cJSON_PrintUnformatted(root);
    UINT_T ret_len = 0;
    if (ret_data != NULL) {
        //获取json长度
        ret_len = strlen(ret_data);
    } else {
        ty_cJSON_Delete(root);
        return;
    }
    mf_cmd_product_send(PRODUCT_TEST_BUTTON_SUM_CMD, ret_data, ret_len);
    PR_DEBUG("response data: %s", ret_data);
    if (root != NULL) {
        ty_cJSON_Delete(root);
    }
}


STATIC VOID tuya_device_prod_test_lp_time_cb(UINT_T timerID, PVOID_T pTimerArg)
{
    PR_NOTICE("======================enter low power=====================\n");
    tuya_set_sys_power_off();
}
STATIC OPERATE_RET tuya_prod_low_power_init_and_start(VOID)
{
    OPERATE_RET op_ret = OPRT_OK;
    if (0 == prod_lp_timer_id) {
        op_ret = sys_add_timer(tuya_device_prod_test_lp_time_cb, NULL, &prod_lp_timer_id);
        if (OPRT_OK != op_ret) {
            PR_ERR("sys_add_timer tuya_device_entr_lp_time_cb err:%d", op_ret);
            return op_ret;
        }
    }
    sys_start_timer(prod_lp_timer_id, 100, TIMER_ONCE);
    return op_ret;
}

/**
 * @brief: 获取产测类型
 * @param obj: 待检测json对象
 * @attention:
 * @retval: type字符串
 */
CHAR_T *product_test_get_test_item_or_type(IN ty_cJSON *obj)
{
    ty_cJSON *item = NULL;

    if (obj == NULL) {
        return NULL;
    }

    //获取type字段
    item = ty_cJSON_GetObjectItem(obj, "testItem");
    if (item == NULL) {
        //获取testItem对象失败
        //获取type
        item = ty_cJSON_GetObjectItem(obj, "type");
        if (item == NULL) {
            return NULL;
        }
    }

    //查看字段是否为字符类型
    if ((item->type & 0xFF) != ty_cJSON_String) {
        return NULL;
    }

    return item->valuestring;
}

OPERATE_RET ty_param_load(CHAR_T *type, UCHAR_T *input_param, UINT_T input_len, UINT_T *out_read_len)
{
    OPERATE_RET op_ret = OPRT_OK;
    UCHAR_T *load_param = NULL;
    UINT_T param_len;

    if (NULL == input_param || input_len == 0) {
        PR_ERR("ty_param_load input_param err!");
        return OPRT_INVALID_PARM;
    }

    op_ret = wd_common_read(type, &load_param, &param_len);
    if (OPRT_OK != op_ret) {
        PR_ERR("ty_param_load  err:%0d", op_ret);
        return op_ret;
    } else {
        if (input_len < param_len) {
            PR_ERR("ty_param_load input_len < param_len");
            Free(load_param);
            return OPRT_COM_ERROR;
        }
        memcpy(input_param, load_param, param_len);
        *out_read_len = param_len;
        PR_NOTICE("ty_param_load success!");
        Free(load_param);
    }
    return op_ret;
}

OPERATE_RET ty_param_save(CHAR_T *type, UCHAR_T *input_param, UINT_T inlen)
{
    OPERATE_RET op_ret = OPRT_OK;

    if (NULL == input_param || inlen == 0) {
        PR_ERR("ty_sn_save input_param err!");
        return OPRT_INVALID_PARM;
    }

    op_ret = wd_common_write(type, input_param, inlen);
    if (OPRT_OK != op_ret) {
        PR_ERR("wd_common_write camera_param err:%d", op_ret);
    } else {
        PR_NOTICE("save  success");
    }
    return op_ret;
}

STATIC OPERATE_RET product_test_cameraPara(CHAR_T *param)
{
    OPERATE_RET op_ret = OPRT_COM_ERROR;
    ty_cJSON *root = NULL;
    ty_cJSON *cjson = NULL;
    INT_T read_len = 0;
    TY_CAMERA_PARAM camera_param;
    memset(&camera_param, 0, sizeof(TY_CAMERA_PARAM));
    op_ret = ty_param_load(CAMERA_CFG_PARAM_E, &camera_param, SIZEOF(TY_CAMERA_PARAM), &read_len);
    if ((op_ret != OPRT_OK) || (read_len != SIZEOF(TY_CAMERA_PARAM))) {
        camera_param.video_width = VEDIO_W_DEFAULT;
        camera_param.video_height = VEDIO_H_DEFAULT;
        camera_param.video_fps = VEDIO_FPS_DEFAULT;
        camera_param.video_rotat_angle = VEDIO_ROTE_DEFAULT;
        camera_param.video_power_off = USB_POWER_DEFAULT;
    }
    PR_NOTICE("param:%s", param);

    root = ty_cJSON_Parse(param);
    if (NULL == root) {
        PR_ERR(" parse err");
        return OPRT_CJSON_PARSE_ERR;
    }

    cjson = ty_cJSON_GetObjectItem(root, "width");
    if (cjson) {
        camera_param.video_width = cjson->valueint;
    }

    cjson = ty_cJSON_GetObjectItem(root, "height");
    if (cjson) {
        camera_param.video_height = cjson->valueint;
    }
    cjson = ty_cJSON_GetObjectItem(root, "fps");
    if (cjson) {
        camera_param.video_fps = cjson->valueint;
    }

    cjson = ty_cJSON_GetObjectItem(root, "rotation");
    if (cjson) {
        camera_param.video_rotat_angle = cjson->valueint;
    }
    cjson = ty_cJSON_GetObjectItem(root, "usb_power_off");
    if (cjson) {
        camera_param.video_power_off = cjson->valueint;
    }
    ty_cJSON_Delete(root);

    if ((camera_param.video_width > 1280 && camera_param.video_width < 240) || (camera_param.video_height > 1280 && camera_param.video_height < 240) \
        || (camera_param.video_rotat_angle != 0 && camera_param.video_rotat_angle != 90 && camera_param.video_rotat_angle != 180 && camera_param.video_rotat_angle != 270) \
        || (camera_param.video_power_off != 0 && camera_param.video_power_off != 1)) {

        PR_ERR("camera param check err");
        return OPRT_INVALID_PARM;
    }

    ty_param_save(CAMERA_CFG_PARAM_E, &camera_param, sizeof(TY_CAMERA_PARAM));
    ty_set_camera_pic_w_h_r_f(camera_param.video_width, camera_param.video_height, camera_param.video_rotat_angle, camera_param.video_fps);

    TY_UF_CFG uf_cfg = {0};
    read_len = tuya_fast_param_read(UF_TY_CFG_PARAM_E, &uf_cfg, SIZEOF(TY_UF_CFG));
    if (read_len <= 0) {
        uf_cfg.audio_param.audio_power_off = USB_POWER_DEFAULT;
        uf_cfg.audio_param.channel_num = AUDIO_CHANNEL_DEFAULT;
        uf_cfg.audio_param.bit_dept = AUDIO_BIT_DEFAULT;
        uf_cfg.audio_param.sample_rate = AUDIO_RATE_DEFAULT;
        uf_cfg.camera_param.video_width = VEDIO_W_DEFAULT;
        uf_cfg.camera_param.video_height = VEDIO_H_DEFAULT;
        uf_cfg.camera_param.video_fps = VEDIO_FPS_DEFAULT;
        uf_cfg.camera_param.video_rotat_angle = VEDIO_ROTE_DEFAULT;
        uf_cfg.camera_param.video_power_off = USB_POWER_DEFAULT;
        uf_cfg.lcd_info.lcd_if = LCD_HW_SEL_DEFAULT;
        uf_cfg.lcd_info.lcd_vertical = LCD_VERTICAL_DEFAULT;
        uf_cfg.lcd_info.lcd_horizontal = LCD_HONRIZONTAL_DEFAULT;
        uf_cfg.lcd_info.lcd_inversion = LCD_INVERSION_DEFAULT;
        uf_cfg.lcd_info.lcd_type = LCD_TYPE_DEFAULT;
        uf_cfg.lord_param.phone_rotation = PHONE_ROTE_DEFAULT;
        uf_cfg.lord_param.static_electricity_close = STATIC_ELEC_ST_DEFAULT;
        uf_cfg.lord_param.local_door_bell_ring = LOCAL_DOOR_BELL_OPEN_DEFAULT;
        uf_cfg.lord_param.lcd_auto_install_direction_open = LCD_AUTO_DIRECTION_OPEN_DEFAULT;
        uf_cfg.lord_param.ui_language = UI_LANGUAGE_DEFAULT;
        uf_cfg.lord_param.lcd_open_time = LCD_OPEN_TIME_DEFAULT;
    }
    memcpy(&uf_cfg.camera_param, &camera_param, sizeof(TY_CAMERA_PARAM));
    op_ret = tuya_fast_param_save(UF_TY_CFG_PARAM_E, &uf_cfg, SIZEOF(TY_UF_CFG));
    PR_NOTICE("tuya_fast_param_save op_ret=%d", op_ret);

    memset(&camera_param, 0, sizeof(TY_CAMERA_PARAM));
    ty_param_load(CAMERA_CFG_PARAM_E, &camera_param, sizeof(TY_CAMERA_PARAM), &read_len);
    PR_NOTICE("set camera %d %d %d %d", camera_param.video_width, camera_param.video_height, camera_param.video_fps, camera_param.video_rotat_angle);


    return OPRT_OK;
}

STATIC OPERATE_RET product_test_lordPara(CHAR_T *param)
{
    OPERATE_RET op_ret = OPRT_COM_ERROR;
    ty_cJSON *root = NULL;
    ty_cJSON *cjson = NULL;
    INT_T read_len = 0;
    INT_T lord_param = -1;
    TY_LORD_PARAM lord2_param = {0};
    lord2_param.phone_rotation = -1;
    lord2_param.lcd_open_time = LCD_OPEN_TIME_DEFAULT;
    int ui_language = UI_LANGUAGE_DEFAULT;
    root = ty_cJSON_Parse(param);
    if (NULL == root) {
        PR_ERR(" parse err");
        return OPRT_CJSON_PARSE_ERR;
    }

    cjson = ty_cJSON_GetObjectItem(root, "phone_rotation");
    if (cjson) {
        lord_param = cjson->valueint;
        lord2_param.phone_rotation = cjson->valueint;
    }

    cjson = ty_cJSON_GetObjectItem(root, "static_electricity_close");
    if (cjson) {
        lord2_param.static_electricity_close = cjson->valueint;
    }

    cjson = ty_cJSON_GetObjectItem(root, "local_door_bell_ring");
    if (cjson) {
        lord2_param.local_door_bell_ring = cjson->valueint;
    }

    cjson = ty_cJSON_GetObjectItem(root, "lcd_auto_install_direction_open");
    if (cjson) {
        lord2_param.lcd_auto_install_direction_open = cjson->valueint;
    }

    cjson = ty_cJSON_GetObjectItem(root, "ui_language");
    if (cjson) {
        ui_language = cjson->valueint;
        lord2_param.ui_language = cjson->valueint;
    }
    cjson = ty_cJSON_GetObjectItem(root, "lcd_open_time");
    if (cjson) {
        lord2_param.lcd_open_time = (CHAR_T)(cjson->valueint);
    }
    ty_cJSON_Delete(root);

    if ((lord2_param.phone_rotation != -1 && lord2_param.phone_rotation != 0 && lord2_param.phone_rotation != 90 && lord2_param.phone_rotation != 180 && lord2_param.phone_rotation != 270) \
        || (lord2_param.static_electricity_close != 0 && lord2_param.static_electricity_close != 1) \
        || (lord2_param.local_door_bell_ring != 0 && lord2_param.local_door_bell_ring != 1) \
        || (lord2_param.lcd_auto_install_direction_open != 0 && lord2_param.lcd_auto_install_direction_open != 1) \
        || (lord2_param.lcd_open_time < 10 || lord2_param.lcd_open_time > 30)) {

        return OPRT_INVALID_PARM;
    }

    ty_param_save(LORD_CFG_PARAM_E, &lord_param, sizeof(INT_T));
    ty_param_save(LORD2_CFG_PARAM_E, &lord2_param, sizeof(TY_LORD_PARAM));

    TY_UF_CFG uf_cfg = {0};
    read_len = tuya_fast_param_read(UF_TY_CFG_PARAM_E, &uf_cfg, SIZEOF(TY_UF_CFG));
    if (read_len <= 0) {
        uf_cfg.audio_param.audio_power_off = USB_POWER_DEFAULT;
        uf_cfg.audio_param.channel_num = AUDIO_CHANNEL_DEFAULT;
        uf_cfg.audio_param.bit_dept = AUDIO_BIT_DEFAULT;
        uf_cfg.audio_param.sample_rate = AUDIO_RATE_DEFAULT;
        uf_cfg.camera_param.video_width = VEDIO_W_DEFAULT;
        uf_cfg.camera_param.video_height = VEDIO_H_DEFAULT;
        uf_cfg.camera_param.video_fps = VEDIO_FPS_DEFAULT;
        uf_cfg.camera_param.video_rotat_angle = VEDIO_ROTE_DEFAULT;
        uf_cfg.camera_param.video_power_off = USB_POWER_DEFAULT;
        uf_cfg.lcd_info.lcd_if = LCD_HW_SEL_DEFAULT;
        uf_cfg.lcd_info.lcd_vertical = LCD_VERTICAL_DEFAULT;
        uf_cfg.lcd_info.lcd_horizontal = LCD_HONRIZONTAL_DEFAULT;
        uf_cfg.lcd_info.lcd_inversion = LCD_INVERSION_DEFAULT;
        uf_cfg.lcd_info.lcd_type = LCD_TYPE_DEFAULT;
        uf_cfg.lord_param.phone_rotation = PHONE_ROTE_DEFAULT;
        uf_cfg.lord_param.static_electricity_close = STATIC_ELEC_ST_DEFAULT;
        uf_cfg.lord_param.local_door_bell_ring = LOCAL_DOOR_BELL_OPEN_DEFAULT;
        uf_cfg.lord_param.lcd_auto_install_direction_open = LCD_AUTO_DIRECTION_OPEN_DEFAULT;
        uf_cfg.lord_param.ui_language = UI_LANGUAGE_DEFAULT;
        uf_cfg.lord_param.lcd_open_time = LCD_OPEN_TIME_DEFAULT;
    }
    memcpy(&uf_cfg.lord_param, &lord2_param, SIZEOF(TY_LORD_PARAM));
    op_ret = tuya_fast_param_save(UF_TY_CFG_PARAM_E, &uf_cfg, SIZEOF(TY_UF_CFG));
    PR_NOTICE("tuya_fast_param_save op_ret=%d", op_ret);

    memset(&lord2_param, 0, sizeof(TY_LORD_PARAM));
    ty_param_load(LORD2_CFG_PARAM_E, &lord2_param, sizeof(TY_LORD_PARAM), &read_len);
    PR_NOTICE("set lord_param %d %d %d %d", lord2_param.phone_rotation, lord2_param.static_electricity_close, lord2_param.local_door_bell_ring, lord2_param.lcd_auto_install_direction_open);
    if (ui_language == Chinese_Simplified || ui_language == English) {
        ui_language_set(ui_language);
        tuya_set_ui_language(ui_language);
        tuya_fast_param_save(LCD_UI_LANGUAGE_ID, &ui_language, sizeof(INT_T));
    }
    return OPRT_OK;
}

STATIC OPERATE_RET product_test_audioPara(CHAR_T *param)
{
    OPERATE_RET op_ret = OPRT_COM_ERROR;
    ty_cJSON *root = NULL;
    ty_cJSON *cjson = NULL;

    TY_AUDIO_PARAM audio_param;
    BOOL_T flag = TRUE;
    PR_NOTICE("param:%s", param);
    memset(&audio_param, 0, sizeof(TY_AUDIO_PARAM));
    INT_T read_len = 0;
    op_ret = ty_param_load(AUDIO_CFG_PARAM_E, &audio_param, SIZEOF(TY_AUDIO_PARAM), &read_len);
    if ((op_ret != OPRT_OK) || (read_len != SIZEOF(TY_AUDIO_PARAM))) {
        audio_param.sample_rate = AUDIO_RATE_DEFAULT;
        audio_param.bit_dept = AUDIO_BIT_DEFAULT;
        audio_param.channel_num = AUDIO_CHANNEL_DEFAULT;
        audio_param.audio_power_off = USB_POWER_DEFAULT;
    }
    root = ty_cJSON_Parse(param);
    if (NULL == root) {
        PR_ERR(" parse err");
        return OPRT_CJSON_PARSE_ERR;
    }

    cjson = ty_cJSON_GetObjectItem(root, "audio_bit");
    if (cjson) {
        audio_param.bit_dept  = cjson->valueint;
    }

    cjson = ty_cJSON_GetObjectItem(root, "audio_rate");
    if (cjson) {
        audio_param.sample_rate = cjson->valueint;
    }

    cjson = ty_cJSON_GetObjectItem(root, "audio_channel");
    if (cjson) {
        audio_param.channel_num = cjson->valueint;
    }

    cjson = ty_cJSON_GetObjectItem(root, "usb_power_off");
    if (cjson) {
        audio_param.audio_power_off = cjson->valueint;
    }

    ty_cJSON_Delete(root);

    if (audio_param.channel_num != 1 || audio_param.bit_dept != 16 || audio_param.sample_rate > 16000 || (audio_param.audio_power_off != 0 && audio_param.audio_power_off != 1)) {

        PR_ERR("param check err");
        return OPRT_INVALID_PARM;
    }

    ty_param_save(AUDIO_CFG_PARAM_E, &audio_param, sizeof(TY_AUDIO_PARAM));
    ty_set_audio_cfg(audio_param.channel_num, audio_param.bit_dept, audio_param.sample_rate);

    TY_UF_CFG uf_cfg = {0};
    read_len = tuya_fast_param_read(UF_TY_CFG_PARAM_E, &uf_cfg, SIZEOF(TY_UF_CFG));
    if (read_len <= 0) {
        uf_cfg.audio_param.audio_power_off = USB_POWER_DEFAULT;
        uf_cfg.audio_param.channel_num = AUDIO_CHANNEL_DEFAULT;
        uf_cfg.audio_param.bit_dept = AUDIO_BIT_DEFAULT;
        uf_cfg.audio_param.sample_rate = AUDIO_RATE_DEFAULT;
        uf_cfg.camera_param.video_width = VEDIO_W_DEFAULT;
        uf_cfg.camera_param.video_height = VEDIO_H_DEFAULT;
        uf_cfg.camera_param.video_fps = VEDIO_FPS_DEFAULT;
        uf_cfg.camera_param.video_rotat_angle = VEDIO_ROTE_DEFAULT;
        uf_cfg.camera_param.video_power_off = USB_POWER_DEFAULT;
        uf_cfg.lcd_info.lcd_if = LCD_HW_SEL_DEFAULT;
        uf_cfg.lcd_info.lcd_vertical = LCD_VERTICAL_DEFAULT;
        uf_cfg.lcd_info.lcd_horizontal = LCD_HONRIZONTAL_DEFAULT;
        uf_cfg.lcd_info.lcd_inversion = LCD_INVERSION_DEFAULT;
        uf_cfg.lcd_info.lcd_type = LCD_TYPE_DEFAULT;
        uf_cfg.lord_param.phone_rotation = PHONE_ROTE_DEFAULT;
        uf_cfg.lord_param.static_electricity_close = STATIC_ELEC_ST_DEFAULT;
        uf_cfg.lord_param.local_door_bell_ring = LOCAL_DOOR_BELL_OPEN_DEFAULT;
        uf_cfg.lord_param.lcd_auto_install_direction_open = LCD_AUTO_DIRECTION_OPEN_DEFAULT;
        uf_cfg.lord_param.ui_language = UI_LANGUAGE_DEFAULT;
        uf_cfg.lord_param.lcd_open_time = LCD_OPEN_TIME_DEFAULT;
    }
    memcpy(&uf_cfg.audio_param, &audio_param, SIZEOF(TY_AUDIO_PARAM));
    op_ret = tuya_fast_param_save(UF_TY_CFG_PARAM_E, &uf_cfg, SIZEOF(TY_UF_CFG));
    PR_NOTICE("tuya_fast_param_save op_ret=%d", op_ret);

    memset(&audio_param, 0, sizeof(TY_AUDIO_PARAM));
    ty_param_load(AUDIO_CFG_PARAM_E, &audio_param, SIZEOF(TY_AUDIO_PARAM), &read_len);
    PR_NOTICE("set audio %d %d %d ", audio_param.sample_rate, audio_param.bit_dept, audio_param.channel_num);

    return OPRT_OK;
}

STATIC OPERATE_RET product_test_lcd_Para(CHAR_T *param)
{
    OPERATE_RET op_ret = OPRT_COM_ERROR;
    ty_cJSON *root = NULL;
    ty_cJSON *cjson = NULL;

    struct lcd_user_info user_info;

    PR_NOTICE("param:%s", param);
    INT_T read_len = 0;
    memset(&user_info, 0, sizeof(struct lcd_user_info));
    op_ret = ty_param_load(LCD_CFG_PARAM_E, &user_info, SIZEOF(struct lcd_user_info), &read_len);
    if ((op_ret != OPRT_OK) || (read_len != SIZEOF(struct lcd_user_info))) {
        user_info.lcd_if = LCD_HW_SEL_DEFAULT;
        user_info.lcd_vertical = LCD_VERTICAL_DEFAULT;
        user_info.lcd_horizontal = LCD_HONRIZONTAL_DEFAULT;
        user_info.lcd_inversion = LCD_INVERSION_DEFAULT;
        user_info.lcd_type = LCD_TYPE_DEFAULT;
    }

    root = ty_cJSON_Parse(param);
    if (NULL == root) {
        PR_ERR(" parse err");
        return OPRT_CJSON_PARSE_ERR;
    }

    cjson = ty_cJSON_GetObjectItem(root, "lcd_if");
    if (cjson) {
        user_info.lcd_if = cjson->valueint;
    }
    cjson = ty_cJSON_GetObjectItem(root, "lcd_vertical");
    if (cjson) {
        user_info.lcd_vertical = cjson->valueint;
    }

    cjson = ty_cJSON_GetObjectItem(root, "lcd_horizontal");
    if (cjson) {
        user_info.lcd_horizontal = cjson->valueint;
    }

    cjson = ty_cJSON_GetObjectItem(root, "lcd_inversion");
    if (cjson) {
        user_info.lcd_inversion = cjson->valueint;
    }
    cjson = ty_cJSON_GetObjectItem(root, "lcd_chip");
    if (cjson) {
        user_info.lcd_type = cjson->valueint;
    }
    cjson = ty_cJSON_GetObjectItem(root, "del_logo");
    if (cjson && cjson->valueint) {
        CHAR_T *buff = Malloc(20 * 1024);
        if (NULL != buff) {
            memset(buff, 0, 20 * 1024);
            norflash_open(NULL, NULL, NULL);
            norflash_ioctl(NULL, IOCTL_SET_WRITE_PROTECT, 0);
            for (INT_T i = 0; i < 5; i++) {
                norflash_ioctl(NULL, IOCTL_ERASE_SECTOR, 0x3DD000 + i * 4096);
            }
            norflash_write(NULL, buff, 20 * 1024, 0x3DD000);
            Free(buff);
        }
    }

    ty_cJSON_Delete(root);

    if (user_info.lcd_if > 1 ||  user_info.lcd_type > 20 || user_info.lcd_inversion > 1 || user_info.lcd_vertical > 1 || user_info.lcd_horizontal > 1) {
        return OPRT_INVALID_PARM;
    }
    ty_param_save(LCD_CFG_PARAM_E, &user_info, SIZEOF(struct lcd_user_info));

    TY_UF_CFG uf_cfg = {0};
    read_len = tuya_fast_param_read(UF_TY_CFG_PARAM_E, &uf_cfg, SIZEOF(TY_UF_CFG));
    if (read_len <= 0) {
        uf_cfg.audio_param.audio_power_off = USB_POWER_DEFAULT;
        uf_cfg.audio_param.channel_num = AUDIO_CHANNEL_DEFAULT;
        uf_cfg.audio_param.bit_dept = AUDIO_BIT_DEFAULT;
        uf_cfg.audio_param.sample_rate = AUDIO_RATE_DEFAULT;
        uf_cfg.camera_param.video_width = VEDIO_W_DEFAULT;
        uf_cfg.camera_param.video_height = VEDIO_H_DEFAULT;
        uf_cfg.camera_param.video_fps = VEDIO_FPS_DEFAULT;
        uf_cfg.camera_param.video_rotat_angle = VEDIO_ROTE_DEFAULT;
        uf_cfg.camera_param.video_power_off = USB_POWER_DEFAULT;
        uf_cfg.lcd_info.lcd_if = LCD_HW_SEL_DEFAULT;
        uf_cfg.lcd_info.lcd_vertical = LCD_VERTICAL_DEFAULT;
        uf_cfg.lcd_info.lcd_horizontal = LCD_HONRIZONTAL_DEFAULT;
        uf_cfg.lcd_info.lcd_inversion = LCD_INVERSION_DEFAULT;
        uf_cfg.lcd_info.lcd_type = LCD_TYPE_DEFAULT;
        uf_cfg.lord_param.phone_rotation = PHONE_ROTE_DEFAULT;
        uf_cfg.lord_param.static_electricity_close = STATIC_ELEC_ST_DEFAULT;
        uf_cfg.lord_param.local_door_bell_ring = LOCAL_DOOR_BELL_OPEN_DEFAULT;
        uf_cfg.lord_param.lcd_auto_install_direction_open = LCD_AUTO_DIRECTION_OPEN_DEFAULT;
        uf_cfg.lord_param.ui_language = UI_LANGUAGE_DEFAULT;
        uf_cfg.lord_param.lcd_open_time = LCD_OPEN_TIME_DEFAULT;
    }
    memcpy(&uf_cfg.lcd_info, &user_info, SIZEOF(struct lcd_user_info));
    op_ret = tuya_fast_param_save(UF_TY_CFG_PARAM_E, &uf_cfg, SIZEOF(TY_UF_CFG));
    PR_NOTICE("tuya_fast_param_save op_ret=%d", op_ret);

    memset(&user_info, 0, SIZEOF(struct lcd_user_info));
    ty_param_load(LCD_CFG_PARAM_E, &user_info, SIZEOF(struct lcd_user_info), &read_len);
    PR_NOTICE("set lcd_if %d lcd_vertical %d lcd_horizontal %d  lcd_inversion %d ", user_info.lcd_if, user_info.lcd_vertical, user_info.lcd_horizontal, user_info.lcd_inversion);
    return OPRT_OK;
}

STATIC OPERATE_RET product_test_usb_Para(CHAR_T *param)
{
    OPERATE_RET op_ret = OPRT_COM_ERROR;
    ty_cJSON *root = NULL;
    ty_cJSON *cjson = NULL;

    TY_USB_PARAM usb_params = {0} ;

    PR_NOTICE("param:%s", param);
    INT_T read_len = 0;

    op_ret = ty_param_load(USB_CFG_PARAM_E, &usb_params, SIZEOF(TY_USB_PARAM), &read_len);
    if ((op_ret != OPRT_OK) || (read_len != SIZEOF(TY_USB_PARAM))) {
        memset(&usb_params, 0, sizeof(TY_USB_PARAM));
    }

    root = ty_cJSON_Parse(param);
    if (NULL == root) {
        PR_ERR(" parse err");
        return OPRT_CJSON_PARSE_ERR;
    }

    cjson = ty_cJSON_GetObjectItem(root, "usb_type");
    if (cjson) {
        usb_params.usb_type = cjson->valueint;
    }

    cjson = ty_cJSON_GetObjectItem(root, "usb_speed");
    if (cjson) {
        usb_params.usb_speed = cjson->valueint;
    }

    ty_cJSON_Delete(root);

    if (usb_params.usb_type > USB_TYPE_UVC_UAC_E ||  usb_params.usb_speed > 1) {
        return OPRT_INVALID_PARM;
    }

    ty_param_save(USB_CFG_PARAM_E, &usb_params, SIZEOF(TY_USB_PARAM));

    memset(&usb_params, 0, sizeof(TY_USB_PARAM));
    ty_param_load(USB_CFG_PARAM_E, &usb_params, SIZEOF(TY_USB_PARAM), &read_len);
    PR_NOTICE("usb_params usb_type %d usb_speed %d ", usb_params.usb_type, usb_params.usb_speed);
    return OPRT_OK;
}

OPERATE_RET tuya_prod_test(USHORT_T cmd, UCHAR_T *data, UINT_T len, OUT UCHAR_T **ret_data, OUT USHORT_T *ret_len)
{
    //使用门铃的产测方案
    OPERATE_RET op_ret = OPRT_COM_ERROR;
    ty_cJSON *root = NULL;
    ty_cJSON *val_arr = NULL;
    ty_cJSON *recv = NULL;
    CHAR_T *type = NULL;
    CHAR_T *data_temp = NULL;
    root = ty_cJSON_CreateObject();

    switch (cmd) {
    case PRODUCT_TEST_BUTTON_SUM_CMD: {
        PR_DEBUG("button test");
        STATIC BOOL_T  buton_sem_init = FALSE;
        if (FALSE == buton_sem_init) {
            tuya_button_prod_test_cb_reg(button_test_cb);
            buton_sem_init = TRUE;
        }
        op_ret = OPRT_OK;
    }
    break;

    case PRODUCT_TEST_WRITE_SN_CMD: {
        PR_DEBUG("sn write %s", data);
        op_ret = ty_param_save(SN_CFG_TYPE_PARAM_E, data, len);
        if (op_ret == OPRT_OK) {
            ty_cJSON_AddTrueToObject(root, "ret");
        } else {
            ty_cJSON_AddFalseToObject(root, "ret");
        }
    }
    break;

    case PRODUCT_TEST_READ_SN_CMD: {
        PR_DEBUG("sn read");
        data_temp = Malloc(128);
        memset(data_temp, 0, 128);
        UINT_T len;
        op_ret = ty_param_load(SN_CFG_TYPE_PARAM_E, data_temp, 128, &len);
    }
    break;

    case PRODUCT_TEST_MIC_SPEAKER_START_CMD: {
        PR_DEBUG("product test - mic_speaker_start");
        tuya_video_power_ctrl(TRUE);
        op_ret = ty_device_audio_test(TRUE);
        if (op_ret == OPRT_OK) {
            ty_cJSON_AddTrueToObject(root, "ret");
        } else {
            ty_cJSON_AddFalseToObject(root, "ret");
        }
    }
    break;
    case PRODUCT_TEST_MIC_SPEAKER_STOP_CMD: {
        PR_DEBUG("product test - mic_speaker_stop");
        op_ret = ty_device_audio_test(FALSE);
        if (op_ret == OPRT_OK) {
            ty_cJSON_AddTrueToObject(root, "ret");
        } else {
            ty_cJSON_AddFalseToObject(root, "ret");
        }
    }
    break;
    //图像测试抓图
    case PRODUCT_TEST_IPC_IMG_CATCH_SUB_CMD: {
        UINT_T img_size = 0;
        PR_DEBUG("product test - ipc catch img");
        tuya_video_power_ctrl(TRUE);
        tuya_lcd_ctrl_timer_off();
        //抓图
        if (((op_ret = product_test_ipc_catch_img_exec(&img_size)) == OPRT_OK) && (img_size != 0)) {
            ty_cJSON_AddTrueToObject(root, "ret");
            ty_cJSON_AddNumberToObject(root, "size", img_size);
        }
    }
    break;
    //图像测试拿图
    case PRODUCT_TEST_IPC_IMG_GET_SUB_CMD: {
        PR_DEBUG("product test - ipc get img");
        tuya_video_power_ctrl(TRUE);
        //拿图
        if ((op_ret = product_test_ipc_get_img_exec()) == OPRT_OK) {

        }
    }
    break;
    //通用测试
    case PRODUCT_TEST_COMMON_BOOL_SUB_CMD: {
        PR_DEBUG("common bool product test");
        recv = ty_cJSON_Parse((CHAR_T *)data);
        type = product_test_get_test_item(recv, "testItem");
        if (NULL == type) {
            op_ret = OPRT_NOT_SUPPORTED;
        }
        if (0 == strncmp(type, "start_lcd_test", strlen("start_lcd_test"))) {
            tuya_lcd_ctrl_timer_off();
            tuya_video_power_ctrl(TRUE);
            tuya_video_lcd_open(LCD_FROM_UART);
            INT_T read_len = 0;
            TY_LORD_PARAM lord2_param = {0};
            op_ret = ty_param_load(LORD2_CFG_PARAM_E, &lord2_param, sizeof(TY_LORD_PARAM), &read_len);
            if (lord2_param.local_door_bell_ring) {
                tuya_audio_hw_local_play(1);
            }
            op_ret = OPRT_OK;
            ty_cJSON_AddTrueToObject(root, "ret");
        } else if (0 == strncmp(type, "end_lcd_test", strlen("end_lcd_test"))) {
            tuya_video_backlight_off();
            INT_T read_len = 0;
            TY_LORD_PARAM lord2_param = {0};
            op_ret = ty_param_load(LORD2_CFG_PARAM_E, &lord2_param, sizeof(TY_LORD_PARAM), &read_len);
            if (lord2_param.local_door_bell_ring) {
                tuya_audio_hw_local_stop();
            }
            op_ret = OPRT_OK;
            ty_cJSON_AddTrueToObject(root, "ret");
        } else if (0 == strncmp(type, "IRLamp", strlen("IRLamp"))) {
            if ((op_ret = product_test_ir_exec()) == OPRT_OK) {
                ty_cJSON_AddTrueToObject(root, "ret");
            }
        } else if (0 == strncmp(type, "sleep", strlen("sleep"))) {
            PR_DEBUG("======================enter low power=====================");
            op_ret = OPRT_OK;
            ty_cJSON_AddTrueToObject(root, "ret");
            tuya_prod_low_power_init_and_start();
        } else if (0 == strncmp(type, "rtc", strlen("rtc"))) {
            extern BOOL_T rtc_prod_test_result(VOID);
            PR_DEBUG("======================enter rtc test=====================");
            tuya_hal_system_sleep(2700);
            if (rtc_prod_test_result() == TRUE) {
                op_ret = OPRT_OK;
            } else {
                op_ret = OPRT_COM_ERROR;
            }
            if (op_ret == OPRT_OK) {
                ty_cJSON_AddTrueToObject(root, "ret");
            }

            long timestamp;
            //设置为应用初始设定的2000年，实测无效，后期再看
            tuya_rtc_time_set(946684800);
            tuya_rtc_time_get(&timestamp);
            PR_NOTICE("timestamp:%d", timestamp);
        } else {
            //不支持其他的类型
            op_ret = OPRT_NOT_SUPPORTED;
        }
    }
    break;
    //镜头参数配置
    case PRODUCT_TEST_COMMON_CMD: {
        PR_DEBUG("PRODUCT_TEST_COMMON_CMD cmd !");
        recv = ty_cJSON_Parse((CHAR_T *)data);
        //检测类型是否为相机参数
        if ((type = product_test_get_test_item_or_type(recv)) != NULL && (strncmp(type, "cameraPara", strlen("cameraPara")) == 0)) {
            //红外产测执行
            ty_cJSON *p_item = NULL;
            p_item = ty_cJSON_GetObjectItem(recv, "Value");
            if (p_item != NULL) {
                if ((op_ret = product_test_cameraPara(p_item->valuestring)) == OPRT_OK) {
                    //执行成功
                    ty_cJSON_AddTrueToObject(root, "ret");
                } else {
                    op_ret = OPRT_INVALID_PARM;
                }
            }
        } else if ((type = product_test_get_test_item_or_type(recv)) != NULL && (strncmp(type, "audioPara", strlen("audioPara")) == 0)) {
            //红外产测执行
            ty_cJSON *p_item = NULL;
            p_item = ty_cJSON_GetObjectItem(recv, "Value");
            if (p_item != NULL) {
                if ((op_ret = product_test_audioPara(p_item->valuestring)) == OPRT_OK) {
                    //执行成功
                    ty_cJSON_AddTrueToObject(root, "ret");
                } else {
                    op_ret = OPRT_INVALID_PARM;
                }
            }
        } else if ((type = product_test_get_test_item_or_type(recv)) != NULL && (strncmp(type, "lcdPara", strlen("lcdPara")) == 0)) {
            //红外产测执行
            ty_cJSON *p_item = NULL;
            p_item = ty_cJSON_GetObjectItem(recv, "Value");
            if (p_item != NULL) {
                if ((op_ret = product_test_lcd_Para(p_item->valuestring)) == OPRT_OK) {
                    //执行成功
                    ty_cJSON_AddTrueToObject(root, "ret");
                } else {
                    op_ret = OPRT_INVALID_PARM;
                }
            }
        } else if ((type = product_test_get_test_item_or_type(recv)) != NULL && (strncmp(type, "usbPara", strlen("usbPara")) == 0)) {
            //红外产测执行
            ty_cJSON *p_item = NULL;
            p_item = ty_cJSON_GetObjectItem(recv, "Value");
            if (p_item != NULL) {
                if ((op_ret = product_test_usb_Para(p_item->valuestring)) == OPRT_OK) {
                    //执行成功
                    ty_cJSON_AddTrueToObject(root, "ret");
                } else {
                    op_ret = OPRT_INVALID_PARM;
                }
            }
        } else if ((type = product_test_get_test_item_or_type(recv)) != NULL && (strncmp(type, "lordPara", strlen("lordPara")) == 0)) {
            //红外产测执行
            ty_cJSON *p_item = NULL;
            p_item = ty_cJSON_GetObjectItem(recv, "Value");
            if (p_item != NULL) {
                if ((op_ret = product_test_lordPara(p_item->valuestring)) == OPRT_OK) {
                    //执行成功
                    ty_cJSON_AddTrueToObject(root, "ret");
                } else {
                    op_ret = OPRT_INVALID_PARM;
                }
            }

        } else {
            //不支持以外的类型
            op_ret = OPRT_NOT_SUPPORTED;
        }
    }
    break;

    default:
        break;
    }

    if (op_ret != OPRT_OK) {
        PR_DEBUG("test error %d", op_ret);
        //失败 返回{"ret":FALSE} 不用设置 外部会自动生成错误
        //ty_cJSON_AddFalseToObject(root, "ret");
    } else {
        //成功
        PR_DEBUG("test ok");
    }

    //拿图片和PIR时不发送格式数据
    if ((cmd != PRODUCT_TEST_IPC_IMG_GET_SUB_CMD) && (cmd != PRODUCT_TEST_BUTTON_SUM_CMD)) {

        //生成json字符串
        if (PRODUCT_TEST_READ_SN_CMD != cmd) {
            if (op_ret == OPRT_OK) {
                *ret_data = (UCHAR_T *)ty_cJSON_PrintUnformatted(root);

                if (*ret_data != NULL) {
                    //获取json长度
                    *ret_len = strlen((CHAR_T *)(*ret_data));
                }
                PR_DEBUG_RAW("response: ");
                tuya_print_data(*ret_data, *ret_len);
                PR_DEBUG("data %s", *ret_data);
            }
        } else {
            if (data_temp) {
                if (op_ret == OPRT_OK) {
                    *ret_data = data_temp;
                    *ret_len = strlen((CHAR_T *)(*ret_data));
                    PR_DEBUG_RAW("response: ");
                    tuya_print_data(*ret_data, *ret_len);
                    PR_DEBUG("data %s", *ret_data);
                } else {
                    Free(data_temp);
                }
            }
        }


    }

    //释放root
    if (root != NULL) {
        ty_cJSON_Delete(root);
        root = NULL;
    } else {
        //创建json对象失败
        op_ret = OPRT_CR_CJSON_ERR;
    }

    //释放recv
    if (recv != NULL) {
        ty_cJSON_Delete(recv);
        recv = NULL;
        type = NULL;
    }

    return op_ret;

}

/////////////******************SD卡写logo和修改参数**************///////////

BOOL_T get_fs_is_config(VOID_T)
{
    if (get_config_file || get_logo_file || get_rf_file) {
        return TRUE;
    } else {
        return FALSE;
    }

}
STATIC CHAR_T *fs_config_file_check(CONST CHAR_T *file_path)
{
    VOID_T *fd;
    CHAR_T *buff = NULL;
    fd = fopen(file_path, "r");
    if (!fd) {
        return NULL;
    }
    PR_NOTICE(">>>>>>>>>>>> check file: %s TRUE", file_path);
    file_max_size = flen(fd);

    buff = Malloc(file_max_size + 1);
    if (NULL == buff) {
        fclose(fd);
        return NULL;
    }
    memset(buff, 0, file_max_size + 1);

    INT_T ret = fread(buff, 1, file_max_size, fd);
    if (ret <= 0) {
        Free(buff);
        fclose(fd);
        return NULL;
    }
    fclose(fd);
    return buff;
}




STATIC OPERATE_RET product_test_rf_Para(CHAR_T *param)
{
    OPERATE_RET op_ret = OPRT_COM_ERROR;
    ty_cJSON *root = NULL;
    ty_cJSON *cjson = NULL;

    INT_T lcd_type = 0;

    PR_NOTICE("param:%s", param);

    root = ty_cJSON_Parse(param);
    if (NULL == root) {
        PR_ERR(" parse err");
        return OPRT_CJSON_PARSE_ERR;
    }



    ty_cJSON_Delete(root);

    return OPRT_OK;
}
STATIC OPERATE_RET check_param_content(CHAR_T *param)
{
    OPERATE_RET op_ret = OPRT_OK;
    ty_cJSON *root = NULL;
    ty_cJSON *cjson = NULL;
    PR_NOTICE("param:%s", param);

    root = ty_cJSON_Parse(param);
    if (NULL == root) {
        PR_ERR(" parse err");
        return OPRT_CJSON_PARSE_ERR;
    }



    ty_cJSON_Delete(root);
    return op_ret;
}
STATIC VOID sd_process(PVOID_T pArg)
{
    OPERATE_RET op_ret = OPRT_OK;
#define TY_CONFIG_PATH        CONFIG_ROOT_PATH"typaram.ini"
#define TY_LOGO_PATH        CONFIG_ROOT_PATH"tylogo.jpg"
#define TY_RF_PATH        CONFIG_ROOT_PATH"tyrf.ini"
    CHAR_T *file_buf = NULL;
    TY_LOGO *buff = NULL;
    INT_T ret;
    while (1) {
        while (!storage_device_ready()) {
            tuya_hal_system_sleep(500);
            get_config_file = FALSE;
            get_logo_file = FALSE;
            get_rf_file = FALSE;
        }
        //PR_NOTICE("storage_device_ready!");

        if (!get_config_file) {
            file_buf = fs_config_file_check(TY_CONFIG_PATH);
            if (file_buf) {
                op_ret = check_param_content(file_buf);
            }
            if (file_buf && (op_ret == OPRT_OK)) {
                get_config_file = TRUE;
                tuya_hal_system_sleep(500);
                op_ret = product_test_cameraPara(file_buf);
                if (OPRT_OK != op_ret) {
                    ret = 6;
                    goto flag_one;
                }
                op_ret = product_test_audioPara(file_buf);
                if (OPRT_OK != op_ret) {
                    ret = 6;
                    goto flag_one;
                }
                op_ret = product_test_lcd_Para(file_buf);
                if (OPRT_OK != op_ret) {
                    ret = 6;
                    goto flag_one;
                }
                op_ret = product_test_usb_Para(file_buf);
                if (OPRT_OK != op_ret) {
                    ret = 6;
                    goto flag_one;
                }

                op_ret = product_test_lordPara(file_buf);
                if (OPRT_OK != op_ret) {
                    ret = 6;
                    goto flag_one;
                }

                ret = 4;

flag_one:
                if (file_buf) {
                    Free(file_buf);
                    file_buf = NULL;
                }
                tuya_lcd_back_light_power_ctr(TRUE);
                tuya_send_ui_msg(UI_MSG_UPDATE_ONLY, &ret, sizeof(INT_T));
            }
        }

        if (!get_logo_file) {

            file_buf = fs_config_file_check(TY_LOGO_PATH);
            if (file_buf) {
                get_logo_file = TRUE;
                tuya_hal_system_sleep(500);
                if (file_max_size >= 20 * 1024 - 64) {
                    PR_NOTICE(">>>>>>>>>>>>file =%d > 20K ", file_max_size);
                    ret = 7;
                    goto flag_two;
                }
                buff = (TY_LOGO *)Malloc(file_max_size + SIZEOF(TY_LOGO));
                if (NULL == buff) {
                    ret = 7;
                    goto flag_two;
                }
                memset(buff, 0, file_max_size + SIZEOF(TY_LOGO));

                buff->logo_flag = LOGO_USE_USER;
                buff->logo_len = file_max_size;
                memcpy(buff->logo_data, file_buf, file_max_size);
                norflash_open(NULL, NULL, NULL);
                norflash_ioctl(NULL, IOCTL_SET_WRITE_PROTECT, 0);
                for (INT_T i = 0; i < 5; i++) {
                    norflash_ioctl(NULL, IOCTL_ERASE_SECTOR, 0x3DD000 + i * 4096);
                }
                norflash_write(NULL, buff, file_max_size + SIZEOF(TY_LOGO), 0x3DD000);

                memset(buff, 0, file_max_size + SIZEOF(TY_LOGO));
                norflash_origin_read(buff, 0x3DD000, file_max_size + SIZEOF(TY_LOGO));
                CHAR_T *head_ffd8;
                CHAR_T *tail_ffd9;
                if (my_mem_find_str(buff, file_max_size + SIZEOF(TY_LOGO), &head_ffd8, &tail_ffd9) && (buff->logo_len == file_max_size)) {
                    ret = 5;
                } else {
                    ret = 7;
                    goto flag_two;
                }
                PR_NOTICE("read file size %d buf 0x%x 0x%x 0x%x 0x%x", buff->logo_len, buff->logo_data[0], buff->logo_data[1], buff->logo_data[file_max_size - 2], buff->logo_data[file_max_size - 1]);
flag_two:
                if (buff) {
                    Free(buff);
                    buff = NULL;
                }
                if (file_buf) {
                    Free(file_buf);
                    file_buf = NULL;
                }

                tuya_lcd_back_light_power_ctr(TRUE);
                tuya_send_ui_msg(UI_MSG_UPDATE_ONLY, &ret, sizeof(INT_T));
            }

            if (!get_rf_file) {
                file_buf = fs_config_file_check(TY_RF_PATH);
                if (file_buf) {
                    get_rf_file = TRUE;
                    tuya_hal_system_sleep(500);
                    op_ret = product_test_rf_Para(file_buf);
                    if (OPRT_OK != op_ret) {
                        ret = 6;
                        goto flag_3;
                    }

                    ret = 4;

flag_3:
                    if (file_buf) {
                        Free(file_buf);
                        file_buf = NULL;
                    }
                    tuya_lcd_back_light_power_ctr(TRUE);
                    tuya_send_ui_msg(UI_MSG_UPDATE_ONLY, &ret, sizeof(INT_T));
                }
            }

        }
        while (1) {
            tuya_hal_system_sleep(10000);
        }


    }
}

OPERATE_RET tuya_sd_card_prod_test(VOID)
{
    OPERATE_RET op_ret = OPRT_OK;
    THRD_PARAM_S thrd_param;
    thrd_param.priority = TRD_PRIO_2;
    thrd_param.stackDepth = 1024 * 2;
    thrd_param.thrdname = "ty_sd_prod_task";
    op_ret = CreateAndStart(&sd_handle, NULL, NULL, sd_process, NULL, &thrd_param);
    if (OPRT_OK != op_ret) {
        PR_ERR("CreateAndStart failed!");
        return op_ret;
    }
}


//************整机产测****************************************************************************//

#define TY_DEVICE_TEST_WIFI_CNT        8
#define TY_DEVICE_TEST_SOUND_CNT       12
#define TY_DEVICE_TEST_PRE_LCD_CNT     1
#define TY_DEVICE_TEST_LCD_CNT         8
#define TY_DEVICE_TEST_END_CNT         3

STATIC BOOL_T ener_device_test = FALSE;
STATIC THRD_HANDLE  tuya_device_test_handle = NULL;
STATIC MSG_QUE_HANDLE device_prod_msg_que = NULL;
STATIC TIMER_ID  device_test_timer_id = 0;
STATIC TIMER_ID  device_test_wifi_timer_id = 0;
STATIC UINT_T  device_test_step = TY_DEVICE_TEST_WIFI;
STATIC INT_T  tuya_rssi = 0;
STATIC UINT_T time_cnt = 0;
STATIC OPERATE_RET tuya_send_device_test_msg(IN CONST UINT_T msgid, IN CONST VOID_T *data, IN CONST UINT_T len)
{
    OPERATE_RET op_ret = OPRT_OK;
    INT_T msg_num = 0;
    if (!device_prod_msg_que) {
        return OPRT_MSG_OUT_OF_LMT;
    }
    op_ret = GetMsgNodeNum(device_prod_msg_que, &msg_num);
    if ((OPRT_OK == op_ret) && (msg_num >= 20)) {
        PR_ERR("msg_num is out of range");
        return OPRT_MSG_OUT_OF_LMT;
    }

    P_MSG_DATA msg_data;
    UINT_T cur_len = len;

    if (data && len) {
        msg_data = Malloc(len + 1);
        if (!msg_data) {
            return OPRT_MALLOC_FAILED;
        }
        memset(msg_data, 0, len + 1);
        memcpy(msg_data, data, len);
    } else {
        msg_data = NULL;
        cur_len = 0;
    }

    op_ret = PostMessage(device_prod_msg_que, msgid, msg_data, cur_len);
    if (OPRT_OK != op_ret) {
        return op_ret;
    }

    return OPRT_OK;
}

BOOL_T get_tuya_device_test_st(VOID)
{
    return ener_device_test;
}

STATIC VOID tuya_device_test_time_cb(UINT_T timerID, PVOID_T pTimerArg)
{
    tuya_send_device_test_msg(device_test_step, NULL, 0);
}

STATIC VOID tuya_device_test_wifi_time_cb(UINT_T timerID, PVOID_T pTimerArg)
{
    INT_T data[2];
    if (device_test_step == TY_DEVICE_TEST_WIFI) {
        time_cnt --;
        data[0] = tuya_rssi;
        data[1] = time_cnt;
        tuya_lcd_play_pic(UI_MSG_WIFI_SET_MODE_TEST, data, SIZEOF(data));
        tuya_device_test_wifi_timer_start(1000);
    }

}
STATIC OPERATE_RET tuya_device_test_timer_init(VOID)
{
    OPERATE_RET op_ret = OPRT_OK;

    op_ret = sys_add_timer(tuya_device_test_time_cb, NULL, &device_test_timer_id);
    if (OPRT_OK != op_ret) {
        PR_ERR("sys_add_timer tuya_device_test_lcd_time_cb err:%d", op_ret);
        return op_ret;
    }

    op_ret = sys_add_timer(tuya_device_test_wifi_time_cb, NULL, &device_test_wifi_timer_id);
    if (OPRT_OK != op_ret) {
        PR_ERR("sys_add_timer tuya_device_test_lcd_time_cb err:%d", op_ret);
        return op_ret;
    }
    return op_ret;
}

STATIC OPERATE_RET tuya_device_test_timer_start(UINT_T time_interval)
{
    OPERATE_RET op_ret = OPRT_OK;

    op_ret = sys_start_timer(device_test_timer_id, time_interval, TIMER_ONCE);
    if (OPRT_OK != op_ret) {
        PR_ERR("sys_add_timer device_test_timer_id err:%d", op_ret);
        return op_ret;
    }
    return op_ret;
}

STATIC OPERATE_RET tuya_device_test_wifi_timer_start(UINT_T time_interval)
{
    OPERATE_RET op_ret = OPRT_OK;

    op_ret = sys_start_timer(device_test_wifi_timer_id, time_interval, TIMER_ONCE);
    if (OPRT_OK != op_ret) {
        PR_ERR("sys_add_timer device_test_wifi_timer_id err:%d", op_ret);
        return op_ret;
    }
    return op_ret;
}

STATIC VOID device_button_test_cb(INT_T gpio_no, CHAR_T type)
{
    if (device_test_step == TY_DEVICE_TEST_WIFI) {
        return;
    }
    sys_stop_timer(device_test_timer_id);
    if (KEY_EVENT_CLICK == type) {
        if (device_test_step < TY_DEVICE_TEST_END) {
            device_test_step++;
        }
        tuya_send_device_test_msg(device_test_step, NULL, 0);
    } else {
        device_test_step = TY_DEVICE_TEST_END;
        tuya_send_device_test_msg(device_test_step, NULL, 0);
    }

}

STATIC VOID tuya_device_test_process(PVOID_T pArg)
{
    OPERATE_RET op_ret = OPRT_OK;
    P_MSG_LIST msgListNode;
    UINT_T last_step = 0;
    INT_T data[3];
    INT_T err_type = 0;
    while (1) {
        //阻塞等待消息
        op_ret = WaitMessage(device_prod_msg_que, &msgListNode);
        if (op_ret != OPRT_OK) {
            if (op_ret != OPRT_MSG_LIST_EMPTY) {
                PR_ERR("WaitMessage op_ret:%d", op_ret);
            }
            continue;
        }


        switch (msgListNode->msg.msgID) {
        case TY_DEVICE_TEST_WIFI:
            AP_IF_S *ap = NULL;

            if (last_step != msgListNode->msg.msgID) {
                time_cnt = TY_DEVICE_TEST_WIFI_CNT;
                err_type = 0;
                tuya_video_lcd_ctr(FALSE, LCD_FROM_APP, 0);
                tuya_lcd_play_pic_syn(UI_MSG_NULL_SYN, NULL, 0);
                tuya_video_lcd_open_status_set(TRUE);
                tuya_video_lcd_display_status_set(FALSE);
                tuya_lcd_back_light_power_ctr(TRUE);
                data[0] = tuya_rssi;
                data[1] = time_cnt;
                data[2] = 0;
                tuya_lcd_play_pic(UI_MSG_WIFI_SET_MODE_TEST, data, SIZEOF(data));
                tuya_device_test_wifi_timer_start(1000);
                op_ret = wf_assign_ap_scan("tuya_mdev_test", &ap);
                if (OPRT_OK != op_ret) {
                    PR_NOTICE("wf_assign_ap_scan failed(%d)", op_ret);
                    wf_release_ap(ap);
                    ap = NULL;
                    err_type = 1;
                    device_test_step = TY_DEVICE_TEST_END;
                } else {
                    PR_NOTICE("scan test ssid succ!!!");
                    tuya_rssi = ap->rssi;
                    wf_release_ap(ap);
                    ap = NULL;
                    device_test_step = msgListNode->msg.msgID + 1;
                }
            }

            data[0] = tuya_rssi;
            data[1] = time_cnt;
            tuya_lcd_play_pic(UI_MSG_WIFI_SET_MODE_TEST, data, SIZEOF(data));

            tuya_device_test_timer_start(500);
            break;

        case TY_DEVICE_TEST_SOUND_START:
            tuya_video_power_ctrl(true);
            ty_device_audio_test(TRUE);
            if (last_step != msgListNode->msg.msgID) {
                time_cnt = TY_DEVICE_TEST_SOUND_CNT;

            } else {
                time_cnt --;
            }
            tuya_lcd_play_pic(UI_MSG_SOUND_TEST, &time_cnt, SIZEOF(INT_T));
            if (time_cnt == 1) {
                device_test_step = msgListNode->msg.msgID + 1;
#if TCFG_HOST_AUDIO_ENABLE
                if (FALSE == ty_audio_device_online()) {
                    err_type = 2;
                    device_test_step = TY_DEVICE_TEST_END;
                }
#endif
            }

            tuya_device_test_timer_start(1000);
            break;

        case TY_DEVICE_TEST_SOUND_STOP:
            ty_device_audio_test(FALSE);
            device_test_step = msgListNode->msg.msgID + 1;
            tuya_device_test_timer_start(100);
            break;

        case TY_DEVICE_TEST_PRE_LCD_TEST:
            if (last_step != msgListNode->msg.msgID) {
                time_cnt = TY_DEVICE_TEST_PRE_LCD_CNT;
            } else {
                time_cnt --;
            }
            tuya_lcd_play_pic(UI_MSG_CAMERA_TEST, &time_cnt, SIZEOF(INT_T));
            if (time_cnt == 1) {
                device_test_step = msgListNode->msg.msgID + 1;
            }
            tuya_device_test_timer_start(1000);
            break;

        case TY_DEVICE_TEST_LCD_START:
            if (last_step != msgListNode->msg.msgID) {
                tuya_video_lcd_ctr(TRUE, LCD_FROM_APP, UI_MSG_LOGO);
                time_cnt = TY_DEVICE_TEST_LCD_CNT;
                INT_T read_len = 0;
                TY_LORD_PARAM lord2_param = {0};
                op_ret = ty_param_load(LORD2_CFG_PARAM_E, &lord2_param, sizeof(TY_LORD_PARAM), &read_len);
                if (lord2_param.local_door_bell_ring) {
                    tuya_audio_hw_local_play(1);
                }
            } else {
                time_cnt --;
            }
            if (time_cnt == 1) {
                device_test_step = msgListNode->msg.msgID + 1;
                if (FALSE == dev_online("uvc")) {
                    err_type = 3;
                    device_test_step = TY_DEVICE_TEST_END;
                }
            }
            tuya_device_test_timer_start(1000);
            break;

        case TY_DEVICE_TEST_LCD_STOP:
            tuya_video_lcd_ctr(FALSE, LCD_FROM_APP, 0);
            tuya_lcd_play_pic_syn(UI_MSG_NULL_SYN, NULL, 0);
            device_test_step = msgListNode->msg.msgID + 1;
            tuya_device_test_timer_start(100);
            break;
        case TY_DEVICE_TEST_END:
            if (last_step != msgListNode->msg.msgID) {
                time_cnt = TY_DEVICE_TEST_END_CNT;
                ty_device_audio_test(FALSE);
                tuya_video_stop_new_syn(0);
                tuya_video_lcd_open_status_set(TRUE);
                tuya_video_lcd_display_status_set(FALSE);
                tuya_lcd_back_light_power_ctr(TRUE);
                tuya_low_power_time_set_and_start(0);
                data[1] = last_step;
            } else {
                time_cnt --;
            }
            if (time_cnt == 0) {
                tuya_button_device_prod_test_cb_reg(NULL);
                tuya_low_power_time_set_and_start(0);
                tuya_lcd_bl_off_syn();
                ener_device_test = FALSE;
            } else {
                data[0] = time_cnt;
                data[2] = err_type;
                tuya_lcd_play_pic(UI_MSG_END_TEST, data, SIZEOF(data));
                tuya_device_test_timer_start(1000);
            }
            break;
        }

        PR_NOTICE("device_test_step %d time_cnt %d last_step %d ", device_test_step, time_cnt, last_step);

        last_step = msgListNode->msg.msgID;
        if (msgListNode->msg.pMsgData) {
            Free(msgListNode->msg.pMsgData);
        }
        DelAndFreeMsgNodeFromQueue(device_prod_msg_que, msgListNode);
    }
}
//整机产测入口
OPERATE_RET tuya_device_test(VOID)
{
    STATIC BOOL_T init = FALSE;
    OPERATE_RET op_ret = OPRT_OK;
    PR_NOTICE("tuya_device_test enter");
    tuya_lcd_ctrl_timer_off();
    tuya_low_power_timer_stop();
    if (ener_device_test) {
        return OPRT_COM_ERROR;
    }
    if (!init) {
        CreateMsgQueAndInit(&device_prod_msg_que);
        tuya_device_test_timer_init();
        THRD_PARAM_S thrd_param;
        thrd_param.priority = TRD_PRIO_2;
        thrd_param.stackDepth = 1024 * 4;
        thrd_param.thrdname = "ty_device_prod_task";
        op_ret = CreateAndStart(&tuya_device_test_handle, NULL, NULL, tuya_device_test_process, NULL, &thrd_param);
        if (OPRT_OK != op_ret) {
            PR_ERR("CreateAndStart failed!");
            return op_ret;
        }
    }
    device_test_step = TY_DEVICE_TEST_WIFI;
    tuya_rssi = 0;
    tuya_device_test_timer_start(50);
    tuya_button_device_prod_test_cb_reg(device_button_test_cb);
    ener_device_test = TRUE;
    init = TRUE;
    return op_ret;
}
