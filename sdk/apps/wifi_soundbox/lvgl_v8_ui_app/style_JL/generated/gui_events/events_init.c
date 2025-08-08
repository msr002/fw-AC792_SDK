/*Generate Code, Do NOT Edit!*/
#include "./events_init.h"
#if LV_USE_GUIBUILDER_SIMULATOR
#include <stdio.h>
#endif
#include "lvgl.h"
#include "./callback_handler.h"
#include "../gui_timelines/gui_timelines.h"
#include "../gui_group/gui_group.h"

void scr_loaded_handler(lv_event_t *e)
{
    lv_obj_t *src = lv_event_get_target(e);
}

void events_init(lv_ui *ui)
{
}

void events_init_home(lv_ui *ui)
{
    lv_ui_home *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_HOME);
    lv_obj_add_event_cb(ui_scr->home, scr_loaded_handler, LV_EVENT_SCREEN_LOADED, ui);
}
