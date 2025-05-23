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


lv_obj_t *setup_scr_sysinfo(lv_ui *ui)
{
    lv_ui_sysinfo *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYSINFO);
    if (ui_scr == NULL) {
        ui_scr = lv_mem_alloc(sizeof(lv_ui_sysinfo));
        memset(ui_scr, 0, sizeof(lv_ui_sysinfo));
        ui->sysinfo = ui_scr;
    }

    //Write codes sysinfo
    ui_scr->sysinfo = lv_obj_create(NULL);
    lv_group_t *def_group = lv_group_get_default();
    lv_obj_set_scrollbar_mode(ui_scr->sysinfo, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->sysinfo, GUI_CTRL_SCR);

    //Write codes sysinfo_img_info
    ui_scr->sysinfo_img_info = lv_img_create(ui_scr->sysinfo);
    lv_img_set_src(ui_scr->sysinfo_img_info, gui_get_res_path(GUI_RES_QRCODE_PNG));
    lv_img_set_pivot(ui_scr->sysinfo_img_info, 0, 0);
    lv_img_set_angle(ui_scr->sysinfo_img_info, 0);
    lv_img_set_zoom(ui_scr->sysinfo_img_info, 256);
    lv_obj_set_pos(ui_scr->sysinfo_img_info, 114, 218);
    lv_obj_set_size(ui_scr->sysinfo_img_info, 258, 258);
    lv_obj_add_flag(ui_scr->sysinfo_img_info, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->sysinfo_img_info, GUI_CTRL_IMG);

    //Set style for sysinfo_img_info. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_opa(ui_scr->sysinfo_img_info, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes sysinfo_btn_return
    ui_scr->sysinfo_btn_return = lv_btn_create(ui_scr->sysinfo);
    lv_obj_set_pos(ui_scr->sysinfo_btn_return, 11, 20);
    lv_obj_set_size(ui_scr->sysinfo_btn_return, 460, 67);
    lv_obj_set_scrollbar_mode(ui_scr->sysinfo_btn_return, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->sysinfo_btn_return, LV_OBJ_FLAG_EVENT_BUBBLE);
    ui_style_set(ui_scr->sysinfo_btn_return, GUI_CTRL_BUTTON);
    ui_scr->sysinfo_btn_return_label = lv_label_create(ui_scr->sysinfo_btn_return);
    lv_obj_set_style_pad_all(ui_scr->sysinfo_btn_return, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->sysinfo_btn_return_label, LV_ALIGN_CENTER, 0, 0);

    lv_obj_update_layout(ui_scr->sysinfo);
    ui_scr->sysinfo_del = false;
    i18n_refresh_texts("sysinfo");

    //Init events for screen
    events_init_sysinfo(ui);
    return ui_scr->sysinfo;
}
void unload_scr_sysinfo(lv_ui *ui)
{
    ui_free_scr_ptr(ui, GUI_SCREEN_SYSINFO);
}
