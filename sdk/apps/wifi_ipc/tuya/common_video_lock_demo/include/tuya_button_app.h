
#ifndef _TUYA_BUTTON_KEY_APP_H
#define _TUYA_BUTTON_KEY_APP_H


#ifdef __cplusplus
extern "C" {
#endif
#include "tuya_cloud_types.h"
#include "tuya_cloud_com_defs.h"
#include "asm/gpio.h"

#ifdef  __TUYA_BUTTON_KEY_APP_GLOBALS
#define __TUYA_BUTTON_KEY_APP_EXT
#else
#define __TUYA_BUTTON_KEY_APP_EXT extern
#endif

#define USE_TUYA_BUTTON  0  //推荐使用杰里按键处理


#define  BUTTON_MENU_GPIO_PD2               IO_PORTD_02
#define  BUTTON_UP_GPIO_PB0                 IO_PORTB_00
#define  BUTTON_DOWN_GPIO_PB2               IO_PORTB_02
#define  BUTTON_NET_GPIO_PA10               IO_PORTA_10

#define APP_KEY_MENU  KEY_0
#define APP_KEY_LEFT  KEY_1
#define APP_KEY_RIGHT KEY_2

typedef VOID(* BUTTON_KEY_CALLBACK)(INT_T gpio_no, CHAR_T type);
__TUYA_BUTTON_KEY_APP_EXT OPERATE_RET tuya_button_init(VOID);

#ifdef __cplusplus
}
#endif
#endif

