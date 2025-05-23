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


lv_obj_t *setup_scr_menu(lv_ui *ui)
{
    lv_ui_menu *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_MENU);
    if (ui_scr == NULL) {
        ui_scr = lv_mem_alloc(sizeof(lv_ui_menu));
        memset(ui_scr, 0, sizeof(lv_ui_menu));
        ui->menu = ui_scr;
    }

    //Write codes menu
    ui_scr->menu = lv_obj_create(NULL);
    lv_group_t *def_group = lv_group_get_default();
    lv_obj_set_scrollbar_mode(ui_scr->menu, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->menu, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_clear_flag(ui_scr->menu, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    ui_style_set(ui_scr->menu, GUI_CTRL_SCR);

    //Write codes menu_edit_return
    ui_scr->menu_edit_return = lv_textarea_create(ui_scr->menu);
    lv_obj_set_pos(ui_scr->menu_edit_return, 62, 218);
    lv_obj_set_size(ui_scr->menu_edit_return, 125, 42);
    lv_obj_set_scrollbar_mode(ui_scr->menu_edit_return, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->menu_edit_return, LV_OBJ_FLAG_EVENT_BUBBLE);
    ui_style_set(ui_scr->menu_edit_return, GUI_CTRL_TEXTAREA);

    //Write codes menu_edit_download
    ui_scr->menu_edit_download = lv_textarea_create(ui_scr->menu);
    lv_obj_set_pos(ui_scr->menu_edit_download, 299, 218);
    lv_obj_set_size(ui_scr->menu_edit_download, 135, 42);
    lv_obj_set_scrollbar_mode(ui_scr->menu_edit_download, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->menu_edit_download, LV_OBJ_FLAG_EVENT_BUBBLE);
    ui_style_set(ui_scr->menu_edit_download, GUI_CTRL_TEXTAREA);

    //Write codes menu_edit_netcfg
    ui_scr->menu_edit_netcfg = lv_textarea_create(ui_scr->menu);
    lv_obj_set_pos(ui_scr->menu_edit_netcfg, 62, 452);
    lv_obj_set_size(ui_scr->menu_edit_netcfg, 125, 42);
    lv_obj_set_scrollbar_mode(ui_scr->menu_edit_netcfg, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->menu_edit_netcfg, LV_OBJ_FLAG_EVENT_BUBBLE);
    ui_style_set(ui_scr->menu_edit_netcfg, GUI_CTRL_TEXTAREA);

    //Write codes menu_edit_language
    ui_scr->menu_edit_language = lv_textarea_create(ui_scr->menu);
    lv_obj_set_pos(ui_scr->menu_edit_language, 302, 452);
    lv_obj_set_size(ui_scr->menu_edit_language, 125, 42);
    lv_obj_set_scrollbar_mode(ui_scr->menu_edit_language, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->menu_edit_language, LV_OBJ_FLAG_EVENT_BUBBLE);
    ui_style_set(ui_scr->menu_edit_language, GUI_CTRL_TEXTAREA);

    //Write codes menu_edit_sysset
    ui_scr->menu_edit_sysset = lv_textarea_create(ui_scr->menu);
    lv_obj_set_pos(ui_scr->menu_edit_sysset, 61, 680);
    lv_obj_set_size(ui_scr->menu_edit_sysset, 125, 42);
    lv_obj_set_scrollbar_mode(ui_scr->menu_edit_sysset, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->menu_edit_sysset, LV_OBJ_FLAG_EVENT_BUBBLE);
    ui_style_set(ui_scr->menu_edit_sysset, GUI_CTRL_TEXTAREA);

    //Write codes menu_img_return
    ui_scr->menu_img_return = lv_img_create(ui_scr->menu);
    lv_img_set_src(ui_scr->menu_img_return, gui_get_res_path(GUI_RES_ICON_BACK_PNG));
    lv_img_set_pivot(ui_scr->menu_img_return, 0, 0);
    lv_img_set_angle(ui_scr->menu_img_return, 0);
    lv_img_set_zoom(ui_scr->menu_img_return, 256);
    lv_obj_set_pos(ui_scr->menu_img_return, 61, 53);
    lv_obj_set_size(ui_scr->menu_img_return, 120, 120);
    lv_obj_add_flag(ui_scr->menu_img_return, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->menu_img_return, GUI_CTRL_IMG);

    //Set style for menu_img_return. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui_scr->menu_img_return, 60, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui_scr->menu_img_return, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui_scr->menu_img_return, lv_color_make(0xFF, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes menu_edit_sysinfo
    ui_scr->menu_edit_sysinfo = lv_textarea_create(ui_scr->menu);
    lv_obj_set_pos(ui_scr->menu_edit_sysinfo, 299, 680);
    lv_obj_set_size(ui_scr->menu_edit_sysinfo, 135, 42);
    lv_obj_set_scrollbar_mode(ui_scr->menu_edit_sysinfo, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->menu_edit_sysinfo, LV_OBJ_FLAG_EVENT_BUBBLE);
    ui_style_set(ui_scr->menu_edit_sysinfo, GUI_CTRL_TEXTAREA);

    //Write codes menu_img_download
    ui_scr->menu_img_download = lv_img_create(ui_scr->menu);
    lv_img_set_src(ui_scr->menu_img_download, gui_get_res_path(GUI_RES_ICON_DOWNLOAD_PNG));
    lv_img_set_pivot(ui_scr->menu_img_download, 0, 0);
    lv_img_set_angle(ui_scr->menu_img_download, 0);
    lv_img_set_zoom(ui_scr->menu_img_download, 256);
    lv_obj_set_pos(ui_scr->menu_img_download, 302, 53);
    lv_obj_set_size(ui_scr->menu_img_download, 120, 120);
    lv_obj_add_flag(ui_scr->menu_img_download, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->menu_img_download, GUI_CTRL_IMG);

    //Set style for menu_img_download. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui_scr->menu_img_download, 60, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui_scr->menu_img_download, true, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes menu_img_netcfg
    ui_scr->menu_img_netcfg = lv_img_create(ui_scr->menu);
    lv_img_set_src(ui_scr->menu_img_netcfg, gui_get_res_path(GUI_RES_ICON_CONFNET_PNG));
    lv_img_set_pivot(ui_scr->menu_img_netcfg, 0, 0);
    lv_img_set_angle(ui_scr->menu_img_netcfg, 0);
    lv_img_set_zoom(ui_scr->menu_img_netcfg, 256);
    lv_obj_set_pos(ui_scr->menu_img_netcfg, 61, 307);
    lv_obj_set_size(ui_scr->menu_img_netcfg, 120, 120);
    lv_obj_add_flag(ui_scr->menu_img_netcfg, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->menu_img_netcfg, GUI_CTRL_IMG);

    //Set style for menu_img_netcfg. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui_scr->menu_img_netcfg, 60, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui_scr->menu_img_netcfg, true, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes menu_img_language
    ui_scr->menu_img_language = lv_img_create(ui_scr->menu);
    lv_img_set_src(ui_scr->menu_img_language, gui_get_res_path(GUI_RES_ICON_LANGUAGE_PNG));
    lv_img_set_pivot(ui_scr->menu_img_language, 0, 0);
    lv_img_set_angle(ui_scr->menu_img_language, 0);
    lv_img_set_zoom(ui_scr->menu_img_language, 256);
    lv_obj_set_pos(ui_scr->menu_img_language, 302, 308);
    lv_obj_set_size(ui_scr->menu_img_language, 120, 120);
    lv_obj_add_flag(ui_scr->menu_img_language, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->menu_img_language, GUI_CTRL_IMG);

    //Set style for menu_img_language. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui_scr->menu_img_language, 60, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui_scr->menu_img_language, true, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes menu_img_sysset
    ui_scr->menu_img_sysset = lv_img_create(ui_scr->menu);
    lv_img_set_src(ui_scr->menu_img_sysset, gui_get_res_path(GUI_RES_ICON_SETTLE_PNG));
    lv_img_set_pivot(ui_scr->menu_img_sysset, 0, 0);
    lv_img_set_angle(ui_scr->menu_img_sysset, 0);
    lv_img_set_zoom(ui_scr->menu_img_sysset, 256);
    lv_obj_set_pos(ui_scr->menu_img_sysset, 61, 532);
    lv_obj_set_size(ui_scr->menu_img_sysset, 120, 120);
    lv_obj_add_flag(ui_scr->menu_img_sysset, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->menu_img_sysset, GUI_CTRL_IMG);

    //Set style for menu_img_sysset. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui_scr->menu_img_sysset, 60, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui_scr->menu_img_sysset, true, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes menu_img_sysinfo
    ui_scr->menu_img_sysinfo = lv_img_create(ui_scr->menu);
    lv_img_set_src(ui_scr->menu_img_sysinfo, gui_get_res_path(GUI_RES_ICON_ABOUT_PNG));
    lv_img_set_pivot(ui_scr->menu_img_sysinfo, 0, 0);
    lv_img_set_angle(ui_scr->menu_img_sysinfo, 0);
    lv_img_set_zoom(ui_scr->menu_img_sysinfo, 256);
    lv_obj_set_pos(ui_scr->menu_img_sysinfo, 307, 532);
    lv_obj_set_size(ui_scr->menu_img_sysinfo, 120, 120);
    lv_obj_add_flag(ui_scr->menu_img_sysinfo, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->menu_img_sysinfo, GUI_CTRL_IMG);

    //Set style for menu_img_sysinfo. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui_scr->menu_img_sysinfo, 60, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui_scr->menu_img_sysinfo, true, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_update_layout(ui_scr->menu);
    ui_scr->menu_del = false;
    i18n_refresh_texts("menu");

    //Init events for screen
    events_init_menu(ui);
    return ui_scr->menu;
}
void unload_scr_menu(lv_ui *ui)
{
    ui_free_scr_ptr(ui, GUI_SCREEN_MENU);
}
