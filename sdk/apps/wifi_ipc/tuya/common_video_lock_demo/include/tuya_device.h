/***********************************************************
*  File: tuya_device.h
*  Author: mjl
*  Date: 20210507
***********************************************************/
#ifndef _TUYA_DEVICE_H
#define _TUYA_DEVICE_H

#include "tuya_cloud_types.h"
#include "tuya_button_app.h"
#include "app_config.h"

#ifdef __cplusplus
extern "C" {
#endif
#define FIRM_KEY	"keympgetu3nv5pkq"

#define USE_TY_PID_MEMORY   1
//???????
#define  POWER_5V_GPIO_PA2                  IO_PORTA_02
#define  POWER_USB_GPIO_PA3                 IO_PORTA_03
#define  POWER_LCD_GPIO_PB5                 IO_PORTB_05
#define  LCD_CHECK_GPIO_PA10                IO_PORTA_10
#define  POWER_SD_CARD_GPIO_PA1             IO_PORTA_01

#if defined(TY_OLD_BORD) && (TY_OLD_BORD == 1)
#define  POWER_LCD_BACKGROUND_GPIO_PH4      IO_PORTH_04
#define  POWER_AUDIO_GPIO_PH7               IO_PORTH_07
#else
#define  POWER_AUDIO_GPIO_PH4               IO_PORTH_04
#define  POWER_LCD_BACKGROUND_GPIO_PB8      IO_PORTB_08
#endif

#ifdef __cplusplus
}
#endif

#endif
