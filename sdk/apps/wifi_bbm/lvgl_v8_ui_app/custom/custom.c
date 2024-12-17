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

