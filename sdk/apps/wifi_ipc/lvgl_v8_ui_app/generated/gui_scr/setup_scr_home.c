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

static const char *home_imglist_bat_imgs[6] = {
#if LV_USE_GUIBUILDER_SIMULATOR
    "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\icon_battery_15.png",
    "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\icon_battery_25.png",
    "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\icon_battery_50.png",
    "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\icon_battery_75.png",
    "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\icon_battery_100.png",
    "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\icon_battery_charging.png"
#else
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00000d.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00000e.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00000f.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000010.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000011.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b00000c.zip"
#endif
};
static const char *home_imglist_wifi_imgs[5] = {
#if LV_USE_GUIBUILDER_SIMULATOR
    "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\wifi_00.png",
    "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\wifi_01.png",
    "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\wifi_2.png",
    "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\wifi_03.png",
    "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\wifi_04.png"
#else
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000012.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000013.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000014.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000015.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b000007.zip"
#endif
};

lv_obj_t *setup_scr_home(lv_ui *ui)
{
    lv_ui_home *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_HOME);
    if (ui_scr == NULL) {
        ui_scr = lv_mem_alloc(sizeof(lv_ui_home));
        memset(ui_scr, 0, sizeof(lv_ui_home));
        ui->home = ui_scr;
    }

    //Write codes home
    ui_scr->home = lv_obj_create(NULL);
    lv_group_t *def_group = lv_group_get_default();
    lv_obj_set_scrollbar_mode(ui_scr->home, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->home, GUI_CTRL_SCR);

    //Set style for home. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->home, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_scr->home, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_scr->home, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_scr->home, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_scr->home, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_scr->home, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes home_img_wifi
    ui_scr->home_img_wifi = lv_img_create(ui_scr->home);
    lv_img_set_src(ui_scr->home_img_wifi, gui_get_res_path(GUI_RES_WIFI_04_PNG));
    lv_img_set_pivot(ui_scr->home_img_wifi, 0, 0);
    lv_img_set_angle(ui_scr->home_img_wifi, 0);
    lv_img_set_zoom(ui_scr->home_img_wifi, 256);
    lv_obj_set_pos(ui_scr->home_img_wifi, 41, 26);
    lv_obj_set_size(ui_scr->home_img_wifi, 32, 32);
    lv_obj_add_flag(ui_scr->home_img_wifi, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_add_flag(ui_scr->home_img_wifi, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_scr->home_img_wifi, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->home_img_wifi, GUI_CTRL_IMG);

    //Set style for home_img_wifi. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_img_recolor(ui_scr->home_img_wifi, lv_color_make(0xCF, 0xCB, 0xCB), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes home_lbl_bat
    ui_scr->home_lbl_bat = lv_label_create(ui_scr->home);
    lv_label_set_text(ui_scr->home_lbl_bat, "100%");
    lv_label_set_long_mode(ui_scr->home_lbl_bat, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->home_lbl_bat, 384, 21);
    lv_obj_set_size(ui_scr->home_lbl_bat, 70, 42);
    lv_obj_set_scrollbar_mode(ui_scr->home_lbl_bat, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->home_lbl_bat, LV_OBJ_FLAG_EVENT_BUBBLE);
    ui_style_set(ui_scr->home_lbl_bat, GUI_CTRL_LABEL);

    //Set style for home_lbl_bat. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_shadow_color(ui_scr->home_lbl_bat, lv_color_make(0x21, 0x95, 0xF6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_scr->home_lbl_bat, &lv_font_montserratMedium_22, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_scr->home_lbl_bat, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes home_lbl_2
    ui_scr->home_lbl_2 = lv_label_create(ui_scr->home);
    lv_label_set_text(ui_scr->home_lbl_2, "远程呼叫");
    lv_label_set_long_mode(ui_scr->home_lbl_2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->home_lbl_2, 27, 694);
    lv_obj_set_size(ui_scr->home_lbl_2, 106, 41);
    lv_obj_set_scrollbar_mode(ui_scr->home_lbl_2, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->home_lbl_2, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_add_flag(ui_scr->home_lbl_2, LV_OBJ_FLAG_HIDDEN);
    ui_style_set(ui_scr->home_lbl_2, GUI_CTRL_LABEL);

    //Write codes home_lbl_4
    ui_scr->home_lbl_4 = lv_label_create(ui_scr->home);
    lv_label_set_text(ui_scr->home_lbl_4, "门外对讲");
    lv_label_set_long_mode(ui_scr->home_lbl_4, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->home_lbl_4, 180, 694);
    lv_obj_set_size(ui_scr->home_lbl_4, 106, 41);
    lv_obj_set_scrollbar_mode(ui_scr->home_lbl_4, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->home_lbl_4, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_add_flag(ui_scr->home_lbl_4, LV_OBJ_FLAG_HIDDEN);
    ui_style_set(ui_scr->home_lbl_4, GUI_CTRL_LABEL);

    //Write codes home_lbl_5
    ui_scr->home_lbl_5 = lv_label_create(ui_scr->home);
    lv_label_set_text(ui_scr->home_lbl_5, "便捷回复");
    lv_label_set_long_mode(ui_scr->home_lbl_5, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->home_lbl_5, 342, 694);
    lv_obj_set_size(ui_scr->home_lbl_5, 106, 41);
    lv_obj_set_scrollbar_mode(ui_scr->home_lbl_5, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->home_lbl_5, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_add_flag(ui_scr->home_lbl_5, LV_OBJ_FLAG_HIDDEN);
    ui_style_set(ui_scr->home_lbl_5, GUI_CTRL_LABEL);

    //Write codes home_img_funkey1
    ui_scr->home_img_funkey1 = lv_img_create(ui_scr->home);
    lv_img_set_src(ui_scr->home_img_funkey1, gui_get_res_path(GUI_RES_ICON_CALL_OUT_PNG));
    lv_img_set_pivot(ui_scr->home_img_funkey1, 0, 0);
    lv_img_set_angle(ui_scr->home_img_funkey1, 0);
    lv_img_set_zoom(ui_scr->home_img_funkey1, 256);
    lv_obj_set_pos(ui_scr->home_img_funkey1, 28, 588);
    lv_obj_set_size(ui_scr->home_img_funkey1, 98, 98);
    lv_obj_add_flag(ui_scr->home_img_funkey1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_scr->home_img_funkey1, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->home_img_funkey1, GUI_CTRL_IMG);

    //Set style for home_img_funkey1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_opa(ui_scr->home_img_funkey1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes home_img_funkey3
    ui_scr->home_img_funkey3 = lv_img_create(ui_scr->home);
    lv_img_set_src(ui_scr->home_img_funkey3, gui_get_res_path(GUI_RES_ICON_RECOVER_PNG));
    lv_img_set_pivot(ui_scr->home_img_funkey3, 0, 0);
    lv_img_set_angle(ui_scr->home_img_funkey3, 0);
    lv_img_set_zoom(ui_scr->home_img_funkey3, 256);
    lv_obj_set_pos(ui_scr->home_img_funkey3, 345, 588);
    lv_obj_set_size(ui_scr->home_img_funkey3, 98, 98);
    lv_obj_add_flag(ui_scr->home_img_funkey3, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_add_flag(ui_scr->home_img_funkey3, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_flag(ui_scr->home_img_funkey3, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_scr->home_img_funkey3, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->home_img_funkey3, GUI_CTRL_IMG);

    //Set style for home_img_funkey3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_opa(ui_scr->home_img_funkey3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes home_img_funkey2
    ui_scr->home_img_funkey2 = lv_img_create(ui_scr->home);
    lv_img_set_src(ui_scr->home_img_funkey2, gui_get_res_path(GUI_RES_ICON_WALKIE_TALKIE_PNG));
    lv_img_set_pivot(ui_scr->home_img_funkey2, 0, 0);
    lv_img_set_angle(ui_scr->home_img_funkey2, 0);
    lv_img_set_zoom(ui_scr->home_img_funkey2, 256);
    lv_obj_set_pos(ui_scr->home_img_funkey2, 188, 589);
    lv_obj_set_size(ui_scr->home_img_funkey2, 98, 98);
    lv_obj_add_flag(ui_scr->home_img_funkey2, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_add_flag(ui_scr->home_img_funkey2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_scr->home_img_funkey2, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->home_img_funkey2, GUI_CTRL_IMG);

    //Set style for home_img_funkey2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_opa(ui_scr->home_img_funkey2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    static bool timer_home_digitclock_time_enabled = false;
    //Write codes home_digitclock_time
    ui_scr->home_digitclock_time = lv_label_create(ui_scr->home);
    lv_label_set_text_fmt(ui_scr->home_digitclock_time, "%04d-%02d-%02d %02d:%02d:%02d", 2022, 07, 28, 21 % 12, 25, 50);
    lv_obj_set_style_text_align(ui_scr->home_digitclock_time, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_pos(ui_scr->home_digitclock_time, 5, 94);
    lv_obj_set_size(ui_scr->home_digitclock_time, 468, 52);
    ui_style_set(ui_scr->home_digitclock_time, GUI_CTRL_DIGITALCLOCK);

    //Write codes home_img_weather
    ui_scr->home_img_weather = lv_img_create(ui_scr->home);
    lv_img_set_src(ui_scr->home_img_weather, gui_get_res_path(GUI_RES_WEATHER_013_HOME_IMG_WEATHER_PNG));
    lv_img_set_pivot(ui_scr->home_img_weather, 0, 0);
    lv_img_set_angle(ui_scr->home_img_weather, 0);
    lv_img_set_zoom(ui_scr->home_img_weather, 256);
    lv_obj_set_pos(ui_scr->home_img_weather, 146, 298);
    lv_obj_set_size(ui_scr->home_img_weather, 200, 200);
    lv_obj_add_flag(ui_scr->home_img_weather, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->home_img_weather, GUI_CTRL_IMG);

    //Write codes home_img_bat
    ui_scr->home_img_bat = lv_img_create(ui_scr->home);
    lv_img_set_src(ui_scr->home_img_bat, gui_get_res_path(GUI_RES_ICON_BATTERY_CHARGING_PNG));
    lv_img_set_pivot(ui_scr->home_img_bat, 0, 0);
    lv_img_set_angle(ui_scr->home_img_bat, 0);
    lv_img_set_zoom(ui_scr->home_img_bat, 256);
    lv_obj_set_pos(ui_scr->home_img_bat, 322, 17);
    lv_obj_set_size(ui_scr->home_img_bat, 51, 51);
    lv_obj_add_flag(ui_scr->home_img_bat, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_scr->home_img_bat, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->home_img_bat, GUI_CTRL_IMG);

    //Write codes home_lbl_note
    ui_scr->home_lbl_note = lv_label_create(ui_scr->home);
    lv_label_set_long_mode(ui_scr->home_lbl_note, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->home_lbl_note, 17, 157);
    lv_obj_set_size(ui_scr->home_lbl_note, 454, 140);
    lv_obj_set_scrollbar_mode(ui_scr->home_lbl_note, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->home_lbl_note, GUI_CTRL_LABEL);

    //Write codes home_img_menu
    ui_scr->home_img_menu = lv_img_create(ui_scr->home);
    lv_img_set_src(ui_scr->home_img_menu, gui_get_res_path(GUI_RES_ICON_RECOVER_PNG));
    lv_img_set_pivot(ui_scr->home_img_menu, 0, 0);
    lv_img_set_angle(ui_scr->home_img_menu, 0);
    lv_img_set_zoom(ui_scr->home_img_menu, 256);
    lv_obj_set_pos(ui_scr->home_img_menu, 180, 676);
    lv_obj_set_size(ui_scr->home_img_menu, 98, 98);
    lv_obj_add_flag(ui_scr->home_img_menu, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_add_flag(ui_scr->home_img_menu, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->home_img_menu, GUI_CTRL_IMG);

    //Write codes home_imglist_bat
    ui_scr->home_imglist_bat = lv_imglist_create(ui_scr->home);
    lv_obj_set_pos(ui_scr->home_imglist_bat, 324, 17);
    lv_obj_set_size(ui_scr->home_imglist_bat, 51, 51);
    lv_obj_set_scrollbar_mode(ui_scr->home_imglist_bat, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->home_imglist_bat, GUI_CTRL_IMGLIST);
    lv_imglist_set_src(ui_scr->home_imglist_bat, (const void **) home_imglist_bat_imgs, 6);
    lv_imglist_set_act(ui_scr->home_imglist_bat, 0);

    //Write codes home_imglist_wifi
    ui_scr->home_imglist_wifi = lv_imglist_create(ui_scr->home);
    lv_obj_set_pos(ui_scr->home_imglist_wifi, 39, 26);
    lv_obj_set_size(ui_scr->home_imglist_wifi, 32, 32);
    lv_obj_set_scrollbar_mode(ui_scr->home_imglist_wifi, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->home_imglist_wifi, GUI_CTRL_IMGLIST);
    lv_imglist_set_src(ui_scr->home_imglist_wifi, (const void **) home_imglist_wifi_imgs, 5);
    lv_imglist_set_act(ui_scr->home_imglist_wifi, 0);

    lv_obj_update_layout(ui_scr->home);
    ui_scr->home_del = false;
    i18n_refresh_texts("home");

    //Init events for screen
    events_init_home(ui);
    return ui_scr->home;
}
void unload_scr_home(lv_ui *ui)
{
    ui_free_scr_ptr(ui, GUI_SCREEN_HOME);
}
