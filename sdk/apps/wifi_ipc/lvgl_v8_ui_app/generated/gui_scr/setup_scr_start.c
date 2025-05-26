/*Generate Code, Do NOT Edit!*/
#include "lvgl.h"
#if LV_USE_GUIBUILDER_SIMULATOR
#include <stdio.h>
#endif
#include <stdlib.h>
#include "../gui_guider.h"
#include "../gui_events/events_init.h"
#include "../gui_events/callback_handler.h"
#include "../gui_events/i18n_handler.h"
#include "../gui_timelines/gui_timelines.h"
#include "../../custom/custom.h"


lv_obj_t *setup_scr_start(lv_ui *ui)
{
    lv_ui_start *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_START);
    if (ui_scr == NULL) {
        ui_scr = lv_mem_alloc(sizeof(lv_ui_start));
        memset(ui_scr, 0, sizeof(lv_ui_start));
        ui->start = ui_scr;
    }

    //Write codes start
    ui_scr->start = lv_obj_create(NULL);
    lv_group_t *def_group = lv_group_get_default();
    lv_obj_set_scrollbar_mode(ui_scr->start, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->start, GUI_CTRL_SCR);

    //Write codes start_img_logo
    ui_scr->start_img_logo = lv_img_create(ui_scr->start);
    lv_img_set_src(ui_scr->start_img_logo, &_img_logo_alpha332x82);
    lv_img_set_pivot(ui_scr->start_img_logo, 0, 0);
    lv_img_set_angle(ui_scr->start_img_logo, 0);
    lv_img_set_zoom(ui_scr->start_img_logo, 256);
    lv_obj_set_pos(ui_scr->start_img_logo, 74, 312);
    lv_obj_set_size(ui_scr->start_img_logo, 332, 82);
    lv_obj_add_flag(ui_scr->start_img_logo, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_add_flag(ui_scr->start_img_logo, LV_OBJ_FLAG_CLICKABLE);
    //Effect fadeIn fade_in_up
    lv_anim_effect_args_t start_img_logo_effect_args;
    start_img_logo_effect_args.delay = 0;
    start_img_logo_effect_args.duration = 2000;
    lv_anim_effect_fade_in_up(ui_scr->start_img_logo, &start_img_logo_effect_args);
    ui_style_set(ui_scr->start_img_logo, GUI_CTRL_IMG);

    lv_obj_update_layout(ui_scr->start);
    ui_scr->start_del = false;
    i18n_refresh_texts("start");

    //Init events for screen
    events_init_start(ui);
    return ui_scr->start;
}
void unload_scr_start(lv_ui *ui)
{
    ui_free_scr_ptr(ui, GUI_SCREEN_START);
}
