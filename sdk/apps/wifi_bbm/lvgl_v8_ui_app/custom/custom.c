/**
 * @file custom.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include <stdio.h>
#include "lvgl.h"
#include "custom.h"
#include <time.h>

/*********************
 *      DEFINES
 *********************/
#if !LV_USE_GUIBUILDER_SIMULATOR
#include "app_config.h"
#include "event/key_event.h"

#ifdef CONFIG_BBM_RX

//Baby Monitor RX端LVGL按键映射
//开发板的KEY1 / KEY2 / KEY3 按键映射对应LVGL的PREV / NEXT / ENTER键.按键事件不发送给app_core.
//开发板的KEY4 / KEY5 不映射LVGL. 按键事件发给app_core.

//返回1时，则将按键信息交给app core处理
int ui_scr_key_event_handler_ext(struct key_event *event)
{
    switch (event->value) {
    case KEY_DOWN:
        //KEY4
        return 1;
    case KEY_OK:
        //KEY5
        return 1;
    default:
        //KEY1/2/3...........
        return 0;
    }
}

//LVGL按键映射
void lvgl_key_value_remap(u8 key_value, uint32_t *key_remap)
{
    switch (key_value) {
    case KEY_POWER:
        //KEY1
        *key_remap = LV_KEY_PREV;
        break;
    case KEY_MENU:
        //KEY1
        *key_remap = LV_KEY_NEXT;
        break;
    case KEY_UP:
        //KEY3
        *key_remap = LV_KEY_ENTER;
        break;
    }
    //隐藏顶层提示框
    gui_hide_sys_prompt();
}
#endif


void gui_enable_KeyAndTouch(void)
{
    key_event_enable();
    touch_event_enable();
}

void gui_disable_KeyAndTouch(void)
{
    key_event_disable();
    touch_event_disable();
}

#endif



/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/**
 * Create a demo application
 */

void custom_init(lv_ui *ui)
{
    /* Add your codes here */
}

