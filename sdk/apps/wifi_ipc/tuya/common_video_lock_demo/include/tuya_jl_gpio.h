
#ifndef _TUYA_JL_GPIO_H
#define _TUYA_JL_GPIO_H


#ifdef __cplusplus
extern "C" {
#endif
#include "tuya_cloud_types.h"
#include "tuya_cloud_com_defs.h"

#ifdef  __TUYA_JL_GPIO_GLOBALS
#define __TUYA_JL_GPIO_EXT
#else
#define __TUYA_JL_GPIO_EXT extern
#endif
#define PIN_MODE_PULL_UP  0
#define PIN_MODE_PULL_DOWN  1
#define PIN_MODE_PULL_NONE  2

OPERATE_RET tuya_jl_gpio_inout_set(IN CONST INT_T port, IN CONST BOOL_T in);
OPERATE_RET tuya_jl_gpio_mode_set(IN CONST INT_T port, IN CONST CHAR_T mode);
INT_T tuya_jl_gpio_read(IN CONST INT_T port);
OPERATE_RET tuya_jl_gpio_write(IN CONST INT_T port, IN CONST BOOL_T high);

#ifdef __cplusplus
}
#endif
#endif

