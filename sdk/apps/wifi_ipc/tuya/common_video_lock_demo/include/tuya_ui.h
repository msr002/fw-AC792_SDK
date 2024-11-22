/***********************************************************
*  File: tuya_ui.h
*  Author: mengjinlong
*  Date: 20210401
***********************************************************/
#ifndef _TUYA_UI_H
#define _TUYA_UI_H

#ifdef __cplusplus
extern "C" {
#endif
#include "tuya_cloud_types.h"
#include "tuya_cloud_com_defs.h"

#define  UI_LOG    0
enum {
    UI_MSG_UPDATE = 1,        //ui升级
    UI_MSG_LOGO = 2,   //开机图片显示
    UI_MSG_CAMERA = 3,   //相机画面
    UI_MSG_UPADTE_TIME = 4,   //更新时间
    UI_MSG_UPADTE_PERCENT = 5,   //更新升级进度
    UI_MSG_CONFIG_SET = 6,   //设置界面
    UI_MSG_CONFIG_CLICK = 7,   //设置界面点击按键
    UI_MSG_CLEAN = 8,   //清屏
    UI_MSG_LCD_SET = 9,   //lcd设置页面
    UI_MSG_SYS_SET = 10,   //系统设置页面
    UI_MSG_DEV_INFO = 11,   //本机信息页面
    UI_MSG_WIFI_MODE = 12,   //配网页面
    UI_MSG_LANG_SET = 14,   //语言设置
    UI_MSG_TIME_SET = 15,   //时间设置
    UI_MSG_FACTORY_RESET = 16,   //出厂设置
    UI_MSG_GET_SSID = 17,   //配网成功
    UI_MSG_WIFI_SET_MODE = 18,   //配网页面
    UI_MSG_UPDATE_ONLY = 19,        //ui升级 不带进度
    UI_MSG_LOCAL_IMAGE = 20,        //本地图片显示
    UI_MSG_LOGO_SYN = 21,      //同步开机图片显示
    UI_MSG_CONFIG_SET_SYN = 22,   //同步设置界面
    UI_MSG_CAMERA_SYN = 23,   //同步设置相机画面
    UI_MSG_WIFI_SET_MODE_TEST = 24,   //配网页面
    UI_MSG_SOUND_TEST = 25, //整机音频测试页面
    UI_MSG_CAMERA_TEST = 26, //整机相机测试
    UI_MSG_END_TEST = 27, //整机相机测试结束
    UI_MSG_NULL = 50,   //无
    UI_MSG_NULL_SYN = 51,   //无
};

typedef struct {
    INT_T logo_flag;
    INT_T logo_len;
    INT_T reserve1;
    INT_T reserve2;
    INT_T reserve3;
    CHAR_T logo_data[0];
} TY_LOGO;

#define LCD_UI_LANGUAGE_ID          "language_id"

VOID ty_ui_init(VOID);
INT_T ui_key_control(CHAR_T value, CHAR_T action); //纯ui按键控制

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
