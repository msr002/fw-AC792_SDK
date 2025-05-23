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


lv_obj_t *setup_scr_app(lv_ui *ui)
{
    lv_ui_app *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_APP);
    if (ui_scr == NULL) {
        ui_scr = lv_mem_alloc(sizeof(lv_ui_app));
        memset(ui_scr, 0, sizeof(lv_ui_app));
        ui->app = ui_scr;
    }

    //Write codes app
    ui_scr->app = lv_obj_create(NULL);
    lv_group_t *def_group = lv_group_get_default();
    lv_obj_set_scrollbar_mode(ui_scr->app, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->app, GUI_CTRL_SCR);

    //Write codes app_btn_return
    ui_scr->app_btn_return = lv_btn_create(ui_scr->app);
    lv_obj_set_pos(ui_scr->app_btn_return, 11, 20);
    lv_obj_set_size(ui_scr->app_btn_return, 460, 67);
    lv_obj_set_scrollbar_mode(ui_scr->app_btn_return, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->app_btn_return, LV_OBJ_FLAG_EVENT_BUBBLE);
    ui_style_set(ui_scr->app_btn_return, GUI_CTRL_BUTTON);
    ui_scr->app_btn_return_label = lv_label_create(ui_scr->app_btn_return);
    lv_obj_set_style_pad_all(ui_scr->app_btn_return, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->app_btn_return_label, LV_ALIGN_CENTER, 0, 0);

    //Write codes app_img_qrcode
    ui_scr->app_img_qrcode = lv_img_create(ui_scr->app);
    lv_img_set_src(ui_scr->app_img_qrcode, gui_get_res_path(GUI_RES_ICON_CODE_PNG));
    lv_img_set_pivot(ui_scr->app_img_qrcode, 0, 0);
    lv_img_set_angle(ui_scr->app_img_qrcode, 0);
    lv_img_set_zoom(ui_scr->app_img_qrcode, 256);
    lv_obj_set_pos(ui_scr->app_img_qrcode, 108, 282);
    lv_obj_set_size(ui_scr->app_img_qrcode, 264, 267);
    lv_obj_add_flag(ui_scr->app_img_qrcode, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->app_img_qrcode, GUI_CTRL_IMG);

    //Set style for app_img_qrcode. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_opa(ui_scr->app_img_qrcode, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_update_layout(ui_scr->app);
    ui_scr->app_del = false;
    i18n_refresh_texts("app");

    //Init events for screen
    events_init_app(ui);
    return ui_scr->app;
}
void unload_scr_app(lv_ui *ui)
{
    ui_free_scr_ptr(ui, GUI_SCREEN_APP);
}
