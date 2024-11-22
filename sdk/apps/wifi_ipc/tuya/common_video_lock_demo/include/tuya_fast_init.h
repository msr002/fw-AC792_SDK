
#ifndef _TUYA_FAST_INIT_H
#define _TUYA_FAST_INIT_H


#ifdef __cplusplus
extern "C" {
#endif
#include "app_config.h"
#include "system/includes.h"
#include "tuya_cloud_types.h"
#include "tuya_cloud_com_defs.h"
#include "tuya_video.h"
#ifdef  __TUYA_FAST_INIT_GLOBALS
#define __TUYA_FAST_INIT_EXT
#else
#define __TUYA_FAST_INIT_EXT extern
#endif

#define UF_TY_CFG_PARAM_E       "uf_ty_cfg"

#define USB_POWER_DEFAULT       0
#define AUDIO_CHANNEL_DEFAULT   1
#define AUDIO_BIT_DEFAULT       16
#define AUDIO_RATE_DEFAULT      8000

#define VEDIO_W_DEFAULT         CONFIG_VIDEO_IMAGE_W
#define VEDIO_H_DEFAULT         CONFIG_VIDEO_IMAGE_H
#define VEDIO_ROTE_DEFAULT      0  //CONFIG_VIDEO_IMAGE_ROTE
#define VEDIO_FPS_DEFAULT       10 //CONFIG_VIDEO_IMAGE_FPS

#define LCD_HW_SEL_DEFAULT      0
#define LCD_VERTICAL_DEFAULT    0
#define LCD_HONRIZONTAL_DEFAULT 0
#define LCD_INVERSION_DEFAULT   0
#define LCD_TYPE_DEFAULT        TY_DEFAULT_LCD_TYPE

#define PHONE_ROTE_DEFAULT       -1
#define STATIC_ELEC_ST_DEFAULT   1
#define LOCAL_DOOR_BELL_OPEN_DEFAULT   0
#define LCD_AUTO_DIRECTION_OPEN_DEFAULT   0
#define UI_LANGUAGE_DEFAULT   0
#define LCD_OPEN_TIME_DEFAULT   20
typedef struct {
    TY_CAMERA_PARAM camera_param;
    TY_AUDIO_PARAM audio_param;
//    struct lcd_user_info lcd_info;
    TY_LORD_PARAM lord_param;
} TY_UF_CFG;

OPERATE_RET tuya_cfg_param_init(VOID);
VOID pre_app_fast_init(VOID);
OPERATE_RET tuya_fast_param_save(IN CONST CHAR_T *file_name, IN UCHAR_T *data, UINT_T len);
INT_T tuya_fast_param_read(IN CONST CHAR_T *file_name, INOUT UCHAR_T *data, IN UINT_T data_buf_max_len);
#ifdef __cplusplus
}
#endif
#endif

