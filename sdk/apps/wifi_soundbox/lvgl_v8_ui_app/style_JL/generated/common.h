/*Generate Code, Do NOT Edit!*/
#ifndef __COMMON_H__
#define __COMMON_H__
#ifdef __cplusplus
extern "C" {
#endif

#include "./gui_res/res_common.h"

#define GUI_UIT_VERSION_MAJOR 8
#define GUI_UIT_VERSION_MINOR 4
#define GUI_UIT_VERSION_PATCH 1
#define GUI_UIT_VERSION_INFO "20241112"

#define GUI_CORE_VERSION_MAJOR 2
#define GUI_CORE_VERSION_MINOR 1
#define GUI_CORE_VERSION_PATCH 0
#define GUI_CORE_VERSION_INFO "full(with tools)"

#define GUI_TEMPLATE_VERSION_MAJOR 0
#define GUI_TEMPLATE_VERSION_MINOR 0
#define GUI_TEMPLATE_VERSION_PATCH 1
#define GUI_TEMPLATE_VERSION_INFO "empty480x800"

typedef enum {
    GUI_SCREEN_ACTION_LOAD = 0,
    GUI_SCREEN_ACTION_UNLOAD
} gui_screen_action_t;

typedef enum {
    GUI_SCREEN_HOME = 0,
} gui_screen_id_t;


#ifdef __cplusplus
}
#endif
#endif
