/***********************************************************
*  File: tuya_device.c
*  Author: mjl
*  Date: 20210507
***********************************************************/
#include "app_config.h"
#include "asm/gpio.h"
#include "system/includes.h"
#include "app_config.h"
#include "asm/port_waked_up.h"
#include "device/gpio.h"
#include "tuya_jl_gpio.h"

OPERATE_RET tuya_jl_gpio_inout_set(IN CONST INT_T port, IN CONST BOOL_T in)
{
    if (in) {
        gpio_set_die(port, 1);
        gpio_set_direction(port, 1);
    } else {
        gpio_set_direction(port, 0);
    }
}
OPERATE_RET tuya_jl_gpio_mode_set(IN CONST INT_T port, IN CONST CHAR_T mode)
{
    switch (mode) {
    case PIN_MODE_PULL_UP:
        gpio_set_pull_down(port, 0);
        gpio_set_pull_up(port, 1);
        break;
    case PIN_MODE_PULL_DOWN:
        gpio_set_pull_up(port, 0);
        gpio_set_pull_down(port, 1);
        break;
    case PIN_MODE_PULL_NONE:
        gpio_set_pull_up(port, 0);
        gpio_set_pull_down(port, 0);
        break;
    }
}
INT_T tuya_jl_gpio_read(IN CONST INT_T port)
{
    return gpio_read(port);
}
OPERATE_RET tuya_jl_gpio_write(IN CONST INT_T port, IN CONST BOOL_T high)
{
    return gpio_direction_output(port, high);
}