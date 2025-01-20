#include <stdio.h>
#include "lvgl.h"
#include "gui_guider.h"

#if !LV_USE_GUIBUILDER_SIMULATOR
#include "app_core.h"
#include "app_config.h"
#include "action.h"
#include "ui.h"
#endif

#if !LV_USE_GUIBUILDER_SIMULATOR

void gui_load_home_page(void)
{
    gui_scr_t *screen = gui_scr_get(GUI_SCREEN_HOME);
    if (screen == NULL) {
        screen = gui_scr_create(GUI_SCREEN_HOME, "home", guider_ui.home, (gui_scr_setup_cb_t)setup_scr_home, (gui_scr_unload_cb_t)unload_scr_home);
    }
    ui_load_scr_anim(&guider_ui, screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true, false);
}

void gui_show_sys_prompt(void)
{
    if (guider_ui.sys_prompt_del == false && lv_obj_is_valid(guider_ui.sys_prompt)) {
        lv_obj_clear_flag(guider_ui.sys_prompt, LV_OBJ_FLAG_HIDDEN);
    } else {
        setup_scr_sys_prompt(&guider_ui);
        gui_msg_init_ui();
        gui_msg_init_events();
        delete_gui_timelines();
    }
}

void gui_hide_sys_prompt(void)
{
    if (guider_ui.sys_prompt_del == false && lv_obj_is_valid(guider_ui.sys_prompt)) {
        lv_obj_add_flag(guider_ui.sys_prompt, LV_OBJ_FLAG_HIDDEN);
    }
}

void gui_set_sys_prompt_lab(char *text)
{
    char *lab = lvgl_module_msg_get_ptr(GUI_SYS_PROMPT_MSG_ID_PROMPT_LAB, strlen(text) + 1);
    strcpy(lab, text);
    lvgl_module_msg_send_ptr(lab, 0);
}

void post_home_msg_to_ui(const char *msg, int arg)
{
    if (!strcmp(msg, "back_home_page")) {
        lvgl_rpc_post_func(gui_load_home_page, 0);
    } else if (!strcmp(msg, "show_sys_prompt")) {
        char *text = (char *)arg;
        gui_set_sys_prompt_lab(text);
        lvgl_rpc_post_func(gui_show_sys_prompt, 0);
    } else {
        printf("Unknow Msg\n");
    }
}

static int gui_src_action_home(int action)
{
    struct intent it;
    struct application *app;

    switch (action) {
    case GUI_SCREEN_ACTION_LOAD:
        break;
    case GUI_SCREEN_ACTION_UNLOAD:
        break;
    }
}
REGISTER_UI_SCREEN_ACTION_HANDLER(GUI_SCREEN_HOME)
.onchange = gui_src_action_home,
};
#endif




