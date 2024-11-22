/***********************************************************
*  File: tuya_lowpower.h
*  Author: mengjinlong
*  Date: 20210401
***********************************************************/
#ifndef _TUYA_LOW_POWER_H
#define _TUYA_LOW_POWER_H

#ifdef __cplusplus
extern "C" {
#endif
#include "tuya_cloud_types.h"
#include "tuya_cloud_com_defs.h"

#define  LCD_PLAY_MAX_TIME          60000
#define  LCD_PLAY_MIN_TIME          10000
#define  LCD_PLAY_DEFAILT_TIME      20000

#define  LOW_POWER_MIN_TIME         LCD_PLAY_MIN_TIME
#define  LOW_POWER_MAX_TIME         LCD_PLAY_MAX_TIME
#define  LOW_POWER_DEFAILT_TIME     LCD_PLAY_DEFAILT_TIME

//���⹦��ʱ������
#define  LOW_POWER_UPDATE_TIME      180000
#define  LOW_POWER_NET_CFG_TIME     200000
#define  LOW_POWER_STREAM_TIME      40000
#define  LOW_POWER_FIRST_ACTIVE_TIME      60000


VOID tuya_low_power_time_set_and_start(UINT_T time);
VOID tuya_low_power_time_start_from_flash(VOID);
VOID tuya_low_power_timer_deincrease_and_start(UINT_T decrease_time);
VOID tuya_low_power_timer_increase_and_start(UINT_T increase_time);
OPERATE_RET tuya_low_power_timer_stop();
OPERATE_RET tuya_low_power_init(VOID);

OPERATE_RET tuya_video_lcd_ctrl_init(VOID);
VOID tuya_lcd_timer_increase_and_start(UINT_T increase_time);
VOID tuya_lcd_timer_deincrease_and_start(UINT_T decrease_time);
VOID tuya_lcd_off_ctrl_start(VOID);
VOID tuya_lcd_ctrl_timer_off(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
