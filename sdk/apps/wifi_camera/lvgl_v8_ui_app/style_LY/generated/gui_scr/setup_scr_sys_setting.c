#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE
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


lv_obj_t *setup_scr_sys_setting(lv_ui *ui)
{
    //Write codes sys_setting
    ui->sys_setting = lv_obj_create(NULL);
    lv_group_t *def_group = lv_group_get_default();

    //Set style for sys_setting. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting, &gui_scr_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(ui->sys_setting, LV_SCROLLBAR_MODE_OFF);
    //Write codes sys_setting_view_menu_b
    ui->sys_setting_view_menu_b = lv_obj_create(ui->sys_setting);

    //Set style for sys_setting_view_menu_b. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_view_menu_b, &gui_cont_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_view_menu_b, 0, 0);
    lv_obj_set_size(ui->sys_setting_view_menu_b, 800, 480);
    lv_obj_set_scrollbar_mode(ui->sys_setting_view_menu_b, LV_SCROLLBAR_MODE_OFF);
    //Write codes sys_setting_view_menu
    ui->sys_setting_view_menu = lv_obj_create(ui->sys_setting_view_menu_b);

    //Set style for sys_setting_view_menu. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_view_menu, &gui_cont_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->sys_setting_view_menu, lv_color_make(0x61, 0x61, 0x61), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->sys_setting_view_menu, 205, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->sys_setting_view_menu, lv_color_make(0x21, 0x95, 0xF6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->sys_setting_view_menu, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui->sys_setting_view_menu, lv_color_make(0x21, 0x95, 0xF6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui->sys_setting_view_menu, 91, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_view_menu, 0, 40);
    lv_obj_set_size(ui->sys_setting_view_menu, 800, 400);
    lv_obj_set_scrollbar_mode(ui->sys_setting_view_menu, LV_SCROLLBAR_MODE_OFF);
    //Write codes sys_setting_view_pro
    ui->sys_setting_view_pro = lv_obj_create(ui->sys_setting_view_menu);

    //Set style for sys_setting_view_pro. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_view_pro, &gui_cont_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for sys_setting_view_pro. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui->sys_setting_view_pro, &gui_cont_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->sys_setting_view_pro, 0, 0);
    lv_obj_set_size(ui->sys_setting_view_pro, 800, 43);
    lv_obj_set_scrollbar_mode(ui->sys_setting_view_pro, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->sys_setting_view_pro, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_add_flag(ui->sys_setting_view_pro, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_group_add_obj(def_group, ui->sys_setting_view_pro);
    //Write codes sys_setting_img_1
    ui->sys_setting_img_1 = lv_img_create(ui->sys_setting_view_pro);
    lv_img_set_src(ui->sys_setting_img_1, gui_get_res_path(GUI_RES_LCD_AU_PNG));
    lv_img_set_pivot(ui->sys_setting_img_1, 0, 0);
    lv_img_set_angle(ui->sys_setting_img_1, 0);
    lv_img_set_zoom(ui->sys_setting_img_1, 256);

    //Set style for sys_setting_img_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_img_1, &gui_img_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->sys_setting_img_1, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_img_1, 8, 6);
    lv_obj_set_size(ui->sys_setting_img_1, 29, 29);
    lv_obj_add_flag(ui->sys_setting_img_1, LV_OBJ_FLAG_CLICKABLE);
    //Write codes sys_setting_lbl_1
    ui->sys_setting_lbl_1 = lv_label_create(ui->sys_setting_view_pro);
    lv_label_set_long_mode(ui->sys_setting_lbl_1, LV_LABEL_LONG_WRAP);

    //Set style for sys_setting_lbl_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_lbl_1, &gui_label_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_lbl_1, 50, 6);
    lv_obj_set_size(ui->sys_setting_lbl_1, 200, 32);
    lv_obj_set_scrollbar_mode(ui->sys_setting_lbl_1, LV_SCROLLBAR_MODE_OFF);
    //Write codes sys_setting_view_autof
    ui->sys_setting_view_autof = lv_obj_create(ui->sys_setting_view_menu);

    //Set style for sys_setting_view_autof. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_view_autof, &gui_cont_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for sys_setting_view_autof. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui->sys_setting_view_autof, &gui_cont_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->sys_setting_view_autof, 0, 45);
    lv_obj_set_size(ui->sys_setting_view_autof, 800, 43);
    lv_obj_set_scrollbar_mode(ui->sys_setting_view_autof, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->sys_setting_view_autof, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_add_flag(ui->sys_setting_view_autof, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_group_add_obj(def_group, ui->sys_setting_view_autof);
    //Write codes sys_setting_img_2
    ui->sys_setting_img_2 = lv_img_create(ui->sys_setting_view_autof);
    lv_img_set_src(ui->sys_setting_img_2, gui_get_res_path(GUI_RES_AUTO_OFF_PNG));
    lv_img_set_pivot(ui->sys_setting_img_2, 0, 0);
    lv_img_set_angle(ui->sys_setting_img_2, 0);
    lv_img_set_zoom(ui->sys_setting_img_2, 256);

    //Set style for sys_setting_img_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_img_2, &gui_img_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->sys_setting_img_2, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_img_2, 8, 6);
    lv_obj_set_size(ui->sys_setting_img_2, 29, 29);
    lv_obj_add_flag(ui->sys_setting_img_2, LV_OBJ_FLAG_CLICKABLE);
    //Write codes sys_setting_lbl_2
    ui->sys_setting_lbl_2 = lv_label_create(ui->sys_setting_view_autof);
    lv_label_set_long_mode(ui->sys_setting_lbl_2, LV_LABEL_LONG_WRAP);

    //Set style for sys_setting_lbl_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_lbl_2, &gui_label_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_lbl_2, 50, 6);
    lv_obj_set_size(ui->sys_setting_lbl_2, 200, 32);
    lv_obj_set_scrollbar_mode(ui->sys_setting_lbl_2, LV_SCROLLBAR_MODE_OFF);
    //Write codes sys_setting_view_hz
    ui->sys_setting_view_hz = lv_obj_create(ui->sys_setting_view_menu);

    //Set style for sys_setting_view_hz. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_view_hz, &gui_cont_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for sys_setting_view_hz. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui->sys_setting_view_hz, &gui_cont_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->sys_setting_view_hz, 0, 90);
    lv_obj_set_size(ui->sys_setting_view_hz, 800, 43);
    lv_obj_set_scrollbar_mode(ui->sys_setting_view_hz, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->sys_setting_view_hz, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_add_flag(ui->sys_setting_view_hz, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_group_add_obj(def_group, ui->sys_setting_view_hz);
    //Write codes sys_setting_img_3
    ui->sys_setting_img_3 = lv_img_create(ui->sys_setting_view_hz);
    lv_img_set_src(ui->sys_setting_img_3, gui_get_res_path(GUI_RES_HZ_PNG));
    lv_img_set_pivot(ui->sys_setting_img_3, 0, 0);
    lv_img_set_angle(ui->sys_setting_img_3, 0);
    lv_img_set_zoom(ui->sys_setting_img_3, 256);

    //Set style for sys_setting_img_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_img_3, &gui_img_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->sys_setting_img_3, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_img_3, 8, 6);
    lv_obj_set_size(ui->sys_setting_img_3, 29, 29);
    lv_obj_add_flag(ui->sys_setting_img_3, LV_OBJ_FLAG_CLICKABLE);
    //Write codes sys_setting_lbl_3
    ui->sys_setting_lbl_3 = lv_label_create(ui->sys_setting_view_hz);
    lv_label_set_long_mode(ui->sys_setting_lbl_3, LV_LABEL_LONG_WRAP);

    //Set style for sys_setting_lbl_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_lbl_3, &gui_label_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_lbl_3, 50, 6);
    lv_obj_set_size(ui->sys_setting_lbl_3, 200, 32);
    lv_obj_set_scrollbar_mode(ui->sys_setting_lbl_3, LV_SCROLLBAR_MODE_OFF);
    //Write codes sys_setting_view_kvo
    ui->sys_setting_view_kvo = lv_obj_create(ui->sys_setting_view_menu);

    //Set style for sys_setting_view_kvo. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_view_kvo, &gui_cont_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for sys_setting_view_kvo. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui->sys_setting_view_kvo, &gui_cont_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->sys_setting_view_kvo, 0, 135);
    lv_obj_set_size(ui->sys_setting_view_kvo, 800, 43);
    lv_obj_set_scrollbar_mode(ui->sys_setting_view_kvo, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->sys_setting_view_kvo, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_add_flag(ui->sys_setting_view_kvo, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_group_add_obj(def_group, ui->sys_setting_view_kvo);
    //Write codes sys_setting_img_4
    ui->sys_setting_img_4 = lv_img_create(ui->sys_setting_view_kvo);
    lv_img_set_src(ui->sys_setting_img_4, gui_get_res_path(GUI_RES_KEY_V_PNG));
    lv_img_set_pivot(ui->sys_setting_img_4, 0, 0);
    lv_img_set_angle(ui->sys_setting_img_4, 0);
    lv_img_set_zoom(ui->sys_setting_img_4, 256);

    //Set style for sys_setting_img_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_img_4, &gui_img_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->sys_setting_img_4, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_img_4, 8, 6);
    lv_obj_set_size(ui->sys_setting_img_4, 29, 29);
    lv_obj_add_flag(ui->sys_setting_img_4, LV_OBJ_FLAG_CLICKABLE);
    //Write codes sys_setting_lbl_4
    ui->sys_setting_lbl_4 = lv_label_create(ui->sys_setting_view_kvo);
    lv_label_set_long_mode(ui->sys_setting_lbl_4, LV_LABEL_LONG_WRAP);

    //Set style for sys_setting_lbl_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_lbl_4, &gui_label_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_lbl_4, 50, 6);
    lv_obj_set_size(ui->sys_setting_lbl_4, 200, 32);
    lv_obj_set_scrollbar_mode(ui->sys_setting_lbl_4, LV_SCROLLBAR_MODE_OFF);
    //Write codes sys_setting_view_lag
    ui->sys_setting_view_lag = lv_obj_create(ui->sys_setting_view_menu);

    //Set style for sys_setting_view_lag. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_view_lag, &gui_cont_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for sys_setting_view_lag. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui->sys_setting_view_lag, &gui_cont_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->sys_setting_view_lag, 0, 180);
    lv_obj_set_size(ui->sys_setting_view_lag, 800, 43);
    lv_obj_set_scrollbar_mode(ui->sys_setting_view_lag, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->sys_setting_view_lag, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_add_flag(ui->sys_setting_view_lag, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_group_add_obj(def_group, ui->sys_setting_view_lag);
    //Write codes sys_setting_img_5
    ui->sys_setting_img_5 = lv_img_create(ui->sys_setting_view_lag);
    lv_img_set_src(ui->sys_setting_img_5, gui_get_res_path(GUI_RES_LANGUAGE_PNG));
    lv_img_set_pivot(ui->sys_setting_img_5, 0, 0);
    lv_img_set_angle(ui->sys_setting_img_5, 0);
    lv_img_set_zoom(ui->sys_setting_img_5, 256);

    //Set style for sys_setting_img_5. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_img_5, &gui_img_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->sys_setting_img_5, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_img_5, 8, 6);
    lv_obj_set_size(ui->sys_setting_img_5, 29, 29);
    lv_obj_add_flag(ui->sys_setting_img_5, LV_OBJ_FLAG_CLICKABLE);
    //Write codes sys_setting_lbl_5
    ui->sys_setting_lbl_5 = lv_label_create(ui->sys_setting_view_lag);
    lv_label_set_long_mode(ui->sys_setting_lbl_5, LV_LABEL_LONG_WRAP);

    //Set style for sys_setting_lbl_5. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_lbl_5, &gui_label_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_lbl_5, 50, 6);
    lv_obj_set_size(ui->sys_setting_lbl_5, 200, 32);
    lv_obj_set_scrollbar_mode(ui->sys_setting_lbl_5, LV_SCROLLBAR_MODE_OFF);
    //Write codes sys_setting_view_time
    ui->sys_setting_view_time = lv_obj_create(ui->sys_setting_view_menu);

    //Set style for sys_setting_view_time. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_view_time, &gui_cont_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for sys_setting_view_time. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui->sys_setting_view_time, &gui_cont_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->sys_setting_view_time, 0, 225);
    lv_obj_set_size(ui->sys_setting_view_time, 800, 43);
    lv_obj_set_scrollbar_mode(ui->sys_setting_view_time, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->sys_setting_view_time, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_add_flag(ui->sys_setting_view_time, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_group_add_obj(def_group, ui->sys_setting_view_time);
    //Write codes sys_setting_img_6
    ui->sys_setting_img_6 = lv_img_create(ui->sys_setting_view_time);
    lv_img_set_src(ui->sys_setting_img_6, gui_get_res_path(GUI_RES_TIME_PNG));
    lv_img_set_pivot(ui->sys_setting_img_6, 0, 0);
    lv_img_set_angle(ui->sys_setting_img_6, 0);
    lv_img_set_zoom(ui->sys_setting_img_6, 256);

    //Set style for sys_setting_img_6. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_img_6, &gui_img_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->sys_setting_img_6, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_img_6, 8, 6);
    lv_obj_set_size(ui->sys_setting_img_6, 29, 29);
    lv_obj_add_flag(ui->sys_setting_img_6, LV_OBJ_FLAG_CLICKABLE);
    //Write codes sys_setting_lbl_6
    ui->sys_setting_lbl_6 = lv_label_create(ui->sys_setting_view_time);
    lv_label_set_long_mode(ui->sys_setting_lbl_6, LV_LABEL_LONG_WRAP);

    //Set style for sys_setting_lbl_6. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_lbl_6, &gui_label_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_lbl_6, 50, 6);
    lv_obj_set_size(ui->sys_setting_lbl_6, 200, 32);
    lv_obj_set_scrollbar_mode(ui->sys_setting_lbl_6, LV_SCROLLBAR_MODE_OFF);
    //Write codes sys_setting_view_tv
    ui->sys_setting_view_tv = lv_obj_create(ui->sys_setting_view_menu);

    //Set style for sys_setting_view_tv. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_view_tv, &gui_cont_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for sys_setting_view_tv. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui->sys_setting_view_tv, &gui_cont_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->sys_setting_view_tv, 0, 270);
    lv_obj_set_size(ui->sys_setting_view_tv, 800, 43);
    lv_obj_set_scrollbar_mode(ui->sys_setting_view_tv, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->sys_setting_view_tv, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_add_flag(ui->sys_setting_view_tv, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_group_add_obj(def_group, ui->sys_setting_view_tv);
    //Write codes sys_setting_img_7
    ui->sys_setting_img_7 = lv_img_create(ui->sys_setting_view_tv);
    lv_img_set_src(ui->sys_setting_img_7, gui_get_res_path(GUI_RES_TV_PNG));
    lv_img_set_pivot(ui->sys_setting_img_7, 0, 0);
    lv_img_set_angle(ui->sys_setting_img_7, 0);
    lv_img_set_zoom(ui->sys_setting_img_7, 256);

    //Set style for sys_setting_img_7. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_img_7, &gui_img_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->sys_setting_img_7, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_img_7, 8, 6);
    lv_obj_set_size(ui->sys_setting_img_7, 29, 29);
    lv_obj_add_flag(ui->sys_setting_img_7, LV_OBJ_FLAG_CLICKABLE);
    //Write codes sys_setting_lbl_7
    ui->sys_setting_lbl_7 = lv_label_create(ui->sys_setting_view_tv);
    lv_label_set_long_mode(ui->sys_setting_lbl_7, LV_LABEL_LONG_WRAP);

    //Set style for sys_setting_lbl_7. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_lbl_7, &gui_label_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_lbl_7, 50, 6);
    lv_obj_set_size(ui->sys_setting_lbl_7, 200, 32);
    lv_obj_set_scrollbar_mode(ui->sys_setting_lbl_7, LV_SCROLLBAR_MODE_OFF);
    //Write codes sys_setting_view_format
    ui->sys_setting_view_format = lv_obj_create(ui->sys_setting_view_menu);

    //Set style for sys_setting_view_format. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_view_format, &gui_cont_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for sys_setting_view_format. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui->sys_setting_view_format, &gui_cont_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->sys_setting_view_format, 0, 315);
    lv_obj_set_size(ui->sys_setting_view_format, 800, 43);
    lv_obj_set_scrollbar_mode(ui->sys_setting_view_format, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->sys_setting_view_format, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_add_flag(ui->sys_setting_view_format, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_group_add_obj(def_group, ui->sys_setting_view_format);
    //Write codes sys_setting_img_8
    ui->sys_setting_img_8 = lv_img_create(ui->sys_setting_view_format);
    lv_img_set_src(ui->sys_setting_img_8, gui_get_res_path(GUI_RES_MDK_PNG));
    lv_img_set_pivot(ui->sys_setting_img_8, 0, 0);
    lv_img_set_angle(ui->sys_setting_img_8, 0);
    lv_img_set_zoom(ui->sys_setting_img_8, 256);

    //Set style for sys_setting_img_8. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_img_8, &gui_img_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->sys_setting_img_8, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_img_8, 8, 6);
    lv_obj_set_size(ui->sys_setting_img_8, 29, 29);
    lv_obj_add_flag(ui->sys_setting_img_8, LV_OBJ_FLAG_CLICKABLE);
    //Write codes sys_setting_lbl_8
    ui->sys_setting_lbl_8 = lv_label_create(ui->sys_setting_view_format);
    lv_label_set_long_mode(ui->sys_setting_lbl_8, LV_LABEL_LONG_WRAP);

    //Set style for sys_setting_lbl_8. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_lbl_8, &gui_label_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_lbl_8, 50, 6);
    lv_obj_set_size(ui->sys_setting_lbl_8, 200, 32);
    lv_obj_set_scrollbar_mode(ui->sys_setting_lbl_8, LV_SCROLLBAR_MODE_OFF);
    //Write codes sys_setting_view_reset
    ui->sys_setting_view_reset = lv_obj_create(ui->sys_setting_view_menu);

    //Set style for sys_setting_view_reset. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_view_reset, &gui_cont_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for sys_setting_view_reset. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui->sys_setting_view_reset, &gui_cont_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->sys_setting_view_reset, 0, 360);
    lv_obj_set_size(ui->sys_setting_view_reset, 800, 43);
    lv_obj_set_scrollbar_mode(ui->sys_setting_view_reset, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->sys_setting_view_reset, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_add_flag(ui->sys_setting_view_reset, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_group_add_obj(def_group, ui->sys_setting_view_reset);
    //Write codes sys_setting_img_9
    ui->sys_setting_img_9 = lv_img_create(ui->sys_setting_view_reset);
    lv_img_set_src(ui->sys_setting_img_9, gui_get_res_path(GUI_RES_DEF_SET_PNG));
    lv_img_set_pivot(ui->sys_setting_img_9, 0, 0);
    lv_img_set_angle(ui->sys_setting_img_9, 0);
    lv_img_set_zoom(ui->sys_setting_img_9, 256);

    //Set style for sys_setting_img_9. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_img_9, &gui_img_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->sys_setting_img_9, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_img_9, 8, 6);
    lv_obj_set_size(ui->sys_setting_img_9, 29, 29);
    lv_obj_add_flag(ui->sys_setting_img_9, LV_OBJ_FLAG_CLICKABLE);
    //Write codes sys_setting_lbl_9
    ui->sys_setting_lbl_9 = lv_label_create(ui->sys_setting_view_reset);
    lv_label_set_long_mode(ui->sys_setting_lbl_9, LV_LABEL_LONG_WRAP);

    //Set style for sys_setting_lbl_9. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_lbl_9, &gui_label_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_lbl_9, 50, 6);
    lv_obj_set_size(ui->sys_setting_lbl_9, 200, 32);
    lv_obj_set_scrollbar_mode(ui->sys_setting_lbl_9, LV_SCROLLBAR_MODE_OFF);
    //Write codes sys_setting_view_ver
    ui->sys_setting_view_ver = lv_obj_create(ui->sys_setting_view_menu);

    //Set style for sys_setting_view_ver. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_view_ver, &gui_cont_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for sys_setting_view_ver. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui->sys_setting_view_ver, &gui_cont_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->sys_setting_view_ver, 0, 405);
    lv_obj_set_size(ui->sys_setting_view_ver, 800, 43);
    lv_obj_set_scrollbar_mode(ui->sys_setting_view_ver, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->sys_setting_view_ver, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_add_flag(ui->sys_setting_view_ver, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_group_add_obj(def_group, ui->sys_setting_view_ver);
    //Write codes sys_setting_img_10
    ui->sys_setting_img_10 = lv_img_create(ui->sys_setting_view_ver);
    lv_img_set_src(ui->sys_setting_img_10, gui_get_res_path(GUI_RES_VERSION_PNG));
    lv_img_set_pivot(ui->sys_setting_img_10, 0, 0);
    lv_img_set_angle(ui->sys_setting_img_10, 0);
    lv_img_set_zoom(ui->sys_setting_img_10, 256);

    //Set style for sys_setting_img_10. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_img_10, &gui_img_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->sys_setting_img_10, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_img_10, 8, 6);
    lv_obj_set_size(ui->sys_setting_img_10, 29, 29);
    lv_obj_add_flag(ui->sys_setting_img_10, LV_OBJ_FLAG_CLICKABLE);
    //Write codes sys_setting_lbl_10
    ui->sys_setting_lbl_10 = lv_label_create(ui->sys_setting_view_ver);
    lv_label_set_long_mode(ui->sys_setting_lbl_10, LV_LABEL_LONG_WRAP);

    //Set style for sys_setting_lbl_10. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_lbl_10, &gui_label_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_lbl_10, 50, 6);
    lv_obj_set_size(ui->sys_setting_lbl_10, 200, 32);
    lv_obj_set_scrollbar_mode(ui->sys_setting_lbl_10, LV_SCROLLBAR_MODE_OFF);
    //Write codes sys_setting_img_11
    ui->sys_setting_img_11 = lv_img_create(ui->sys_setting_view_menu_b);
    lv_img_set_src(ui->sys_setting_img_11, gui_get_res_path(GUI_RES_MENU_STA_PNG));
    lv_img_set_pivot(ui->sys_setting_img_11, 0, 0);
    lv_img_set_angle(ui->sys_setting_img_11, 0);
    lv_img_set_zoom(ui->sys_setting_img_11, 256);

    //Set style for sys_setting_img_11. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_img_11, &gui_img_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui->sys_setting_img_11, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_img_11, 0, 0);
    lv_obj_set_size(ui->sys_setting_img_11, 800, 40);
    lv_obj_add_flag(ui->sys_setting_img_11, LV_OBJ_FLAG_CLICKABLE);
    //Write codes sys_setting_img_12
    ui->sys_setting_img_12 = lv_img_create(ui->sys_setting_view_menu_b);
    lv_img_set_src(ui->sys_setting_img_12, gui_get_res_path(GUI_RES_MENU_STA_PNG));
    lv_img_set_pivot(ui->sys_setting_img_12, 0, 0);
    lv_img_set_angle(ui->sys_setting_img_12, 0);
    lv_img_set_zoom(ui->sys_setting_img_12, 256);

    //Set style for sys_setting_img_12. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_img_12, &gui_img_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui->sys_setting_img_12, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_img_12, 0, 440);
    lv_obj_set_size(ui->sys_setting_img_12, 800, 40);
    lv_obj_add_flag(ui->sys_setting_img_12, LV_OBJ_FLAG_CLICKABLE);
    //Write codes sys_setting_img_13
    ui->sys_setting_img_13 = lv_img_create(ui->sys_setting_view_menu_b);
    lv_img_set_src(ui->sys_setting_img_13, gui_get_res_path(GUI_RES_REC_PNG));
    lv_img_set_pivot(ui->sys_setting_img_13, 0, 0);
    lv_img_set_angle(ui->sys_setting_img_13, 0);
    lv_img_set_zoom(ui->sys_setting_img_13, 256);

    //Set style for sys_setting_img_13. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_img_13, &gui_img_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_img_13, 9, 5);
    lv_obj_set_size(ui->sys_setting_img_13, 40, 30);
    lv_obj_add_flag(ui->sys_setting_img_13, LV_OBJ_FLAG_CLICKABLE);
    //Write codes sys_setting_img_14
    ui->sys_setting_img_14 = lv_img_create(ui->sys_setting_view_menu_b);
    lv_img_set_src(ui->sys_setting_img_14, gui_get_res_path(GUI_RES_SET_PNG));
    lv_img_set_pivot(ui->sys_setting_img_14, 0, 0);
    lv_img_set_angle(ui->sys_setting_img_14, 0);
    lv_img_set_zoom(ui->sys_setting_img_14, 256);

    //Set style for sys_setting_img_14. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_img_14, &gui_img_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->sys_setting_img_14, lv_color_make(0x42, 0xA5, 0xF5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->sys_setting_img_14, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui->sys_setting_img_14, lv_color_make(0x42, 0xA5, 0xF5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->sys_setting_img_14, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui->sys_setting_img_14, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_img_14, 70, 1);
    lv_obj_set_size(ui->sys_setting_img_14, 37, 37);
    lv_obj_add_flag(ui->sys_setting_img_14, LV_OBJ_FLAG_CLICKABLE);
    //Write codes sys_setting_img_15
    ui->sys_setting_img_15 = lv_img_create(ui->sys_setting_view_menu_b);
    lv_img_set_src(ui->sys_setting_img_15, gui_get_res_path(GUI_RES_LEFT_PNG));
    lv_img_set_pivot(ui->sys_setting_img_15, 0, 0);
    lv_img_set_angle(ui->sys_setting_img_15, 0);
    lv_img_set_zoom(ui->sys_setting_img_15, 256);

    //Set style for sys_setting_img_15. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_img_15, &gui_img_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_img_15, 200, 445);
    lv_obj_set_size(ui->sys_setting_img_15, 21, 29);
    lv_obj_add_flag(ui->sys_setting_img_15, LV_OBJ_FLAG_CLICKABLE);
    //Write codes sys_setting_img_16
    ui->sys_setting_img_16 = lv_img_create(ui->sys_setting_view_menu_b);
    lv_img_set_src(ui->sys_setting_img_16, gui_get_res_path(GUI_RES_UP_PNG));
    lv_img_set_pivot(ui->sys_setting_img_16, 0, 0);
    lv_img_set_angle(ui->sys_setting_img_16, 0);
    lv_img_set_zoom(ui->sys_setting_img_16, 256);

    //Set style for sys_setting_img_16. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_img_16, &gui_img_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_img_16, 321, 448);
    lv_obj_set_size(ui->sys_setting_img_16, 29, 21);
    lv_obj_add_flag(ui->sys_setting_img_16, LV_OBJ_FLAG_CLICKABLE);
    //Write codes sys_setting_img_17
    ui->sys_setting_img_17 = lv_img_create(ui->sys_setting_view_menu_b);
    lv_img_set_src(ui->sys_setting_img_17, gui_get_res_path(GUI_RES_DOWN_PNG));
    lv_img_set_pivot(ui->sys_setting_img_17, 0, 0);
    lv_img_set_angle(ui->sys_setting_img_17, 0);
    lv_img_set_zoom(ui->sys_setting_img_17, 256);

    //Set style for sys_setting_img_17. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_img_17, &gui_img_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_img_17, 450, 448);
    lv_obj_set_size(ui->sys_setting_img_17, 29, 21);
    lv_obj_add_flag(ui->sys_setting_img_17, LV_OBJ_FLAG_CLICKABLE);
    //Write codes sys_setting_img_18
    ui->sys_setting_img_18 = lv_img_create(ui->sys_setting_view_menu_b);
    lv_img_set_src(ui->sys_setting_img_18, gui_get_res_path(GUI_RES_RIGHT_PNG));
    lv_img_set_pivot(ui->sys_setting_img_18, 0, 0);
    lv_img_set_angle(ui->sys_setting_img_18, 0);
    lv_img_set_zoom(ui->sys_setting_img_18, 256);

    //Set style for sys_setting_img_18. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_img_18, &gui_img_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_img_18, 579, 445);
    lv_obj_set_size(ui->sys_setting_img_18, 21, 29);
    lv_obj_add_flag(ui->sys_setting_img_18, LV_OBJ_FLAG_CLICKABLE);
    //Write codes sys_setting_view_submenu
    ui->sys_setting_view_submenu = lv_obj_create(ui->sys_setting);

    //Set style for sys_setting_view_submenu. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_view_submenu, &gui_cont_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->sys_setting_view_submenu, lv_color_make(0x75, 0x75, 0x75), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->sys_setting_view_submenu, 250, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->sys_setting_view_submenu, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_view_submenu, 111, 84);
    lv_obj_set_size(ui->sys_setting_view_submenu, 590, 314);
    lv_obj_set_scrollbar_mode(ui->sys_setting_view_submenu, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->sys_setting_view_submenu, LV_OBJ_FLAG_HIDDEN);
    //Write codes sys_setting_submenu_btn_1
    ui->sys_setting_submenu_btn_1 = lv_btn_create(ui->sys_setting_view_submenu);

    //Set style for sys_setting_submenu_btn_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_submenu_btn_1, &gui_btn_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->sys_setting_submenu_btn_1, 203, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for sys_setting_submenu_btn_1. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui->sys_setting_submenu_btn_1, &gui_btn_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->sys_setting_submenu_btn_1, 83, 44);
    lv_obj_set_size(ui->sys_setting_submenu_btn_1, 438, 37);
    lv_obj_set_scrollbar_mode(ui->sys_setting_submenu_btn_1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->sys_setting_submenu_btn_1, LV_OBJ_FLAG_EVENT_BUBBLE);
    ui->sys_setting_submenu_btn_1_label = lv_label_create(ui->sys_setting_submenu_btn_1);
    lv_label_set_text(ui->sys_setting_submenu_btn_1_label, "button1");
    lv_obj_set_style_pad_all(ui->sys_setting_submenu_btn_1, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->sys_setting_submenu_btn_1_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes sys_setting_submenu_btn_2
    ui->sys_setting_submenu_btn_2 = lv_btn_create(ui->sys_setting_view_submenu);

    //Set style for sys_setting_submenu_btn_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_submenu_btn_2, &gui_btn_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->sys_setting_submenu_btn_2, 215, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for sys_setting_submenu_btn_2. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui->sys_setting_submenu_btn_2, &gui_btn_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->sys_setting_submenu_btn_2, 83, 111);
    lv_obj_set_size(ui->sys_setting_submenu_btn_2, 438, 37);
    lv_obj_set_scrollbar_mode(ui->sys_setting_submenu_btn_2, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->sys_setting_submenu_btn_2, LV_OBJ_FLAG_EVENT_BUBBLE);
    ui->sys_setting_submenu_btn_2_label = lv_label_create(ui->sys_setting_submenu_btn_2);
    lv_label_set_text(ui->sys_setting_submenu_btn_2_label, "button2");
    lv_obj_set_style_pad_all(ui->sys_setting_submenu_btn_2, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->sys_setting_submenu_btn_2_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes sys_setting_submenu_btn_3
    ui->sys_setting_submenu_btn_3 = lv_btn_create(ui->sys_setting_view_submenu);

    //Set style for sys_setting_submenu_btn_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_submenu_btn_3, &gui_btn_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->sys_setting_submenu_btn_3, 205, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for sys_setting_submenu_btn_3. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui->sys_setting_submenu_btn_3, &gui_btn_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->sys_setting_submenu_btn_3, 83, 171);
    lv_obj_set_size(ui->sys_setting_submenu_btn_3, 438, 37);
    lv_obj_set_scrollbar_mode(ui->sys_setting_submenu_btn_3, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->sys_setting_submenu_btn_3, LV_OBJ_FLAG_EVENT_BUBBLE);
    ui->sys_setting_submenu_btn_3_label = lv_label_create(ui->sys_setting_submenu_btn_3);
    lv_label_set_text(ui->sys_setting_submenu_btn_3_label, "button3");
    lv_obj_set_style_pad_all(ui->sys_setting_submenu_btn_3, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->sys_setting_submenu_btn_3_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes sys_setting_submenu_btn_4
    ui->sys_setting_submenu_btn_4 = lv_btn_create(ui->sys_setting_view_submenu);

    //Set style for sys_setting_submenu_btn_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_submenu_btn_4, &gui_btn_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->sys_setting_submenu_btn_4, 205, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for sys_setting_submenu_btn_4. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui->sys_setting_submenu_btn_4, &gui_btn_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->sys_setting_submenu_btn_4, 83, 233);
    lv_obj_set_size(ui->sys_setting_submenu_btn_4, 438, 37);
    lv_obj_set_scrollbar_mode(ui->sys_setting_submenu_btn_4, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->sys_setting_submenu_btn_4, LV_OBJ_FLAG_EVENT_BUBBLE);
    ui->sys_setting_submenu_btn_4_label = lv_label_create(ui->sys_setting_submenu_btn_4);
    lv_label_set_text(ui->sys_setting_submenu_btn_4_label, "button4");
    lv_obj_set_style_pad_all(ui->sys_setting_submenu_btn_4, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->sys_setting_submenu_btn_4_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes sys_setting_roller_mutifunc
    ui->sys_setting_roller_mutifunc = lv_roller_create(ui->sys_setting_view_submenu);

    //Set style for sys_setting_roller_mutifunc. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_roller_mutifunc, &gui_roller_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for sys_setting_roller_mutifunc. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui->sys_setting_roller_mutifunc, &gui_roller_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Set style for sys_setting_roller_mutifunc. Part: LV_PART_SELECTED, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_roller_mutifunc, &gui_roller_selected_default_style, LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_roller_mutifunc, 198, 55);
    lv_obj_set_size(ui->sys_setting_roller_mutifunc, 198, 130);
    lv_obj_set_scrollbar_mode(ui->sys_setting_roller_mutifunc, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->sys_setting_roller_mutifunc, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_roller_set_options(ui->sys_setting_roller_mutifunc, "1\n2\n3\n4\n5", LV_ROLLER_MODE_INFINITE);
    lv_roller_set_visible_row_count(ui->sys_setting_roller_mutifunc, 3);
    //Write codes sys_setting_lbl_submenu_warning
    ui->sys_setting_lbl_submenu_warning = lv_label_create(ui->sys_setting_view_submenu);
    lv_label_set_text(ui->sys_setting_lbl_submenu_warning, "格式化\n删除所有数据\n恢复默认设置？");
    lv_label_set_long_mode(ui->sys_setting_lbl_submenu_warning, LV_LABEL_LONG_WRAP);

    //Set style for sys_setting_lbl_submenu_warning. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_lbl_submenu_warning, &gui_label_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->sys_setting_lbl_submenu_warning, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->sys_setting_lbl_submenu_warning, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_lbl_submenu_warning, 81, 40);
    lv_obj_set_size(ui->sys_setting_lbl_submenu_warning, 445, 112);
    lv_obj_set_scrollbar_mode(ui->sys_setting_lbl_submenu_warning, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->sys_setting_lbl_submenu_warning, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_group_add_obj(def_group, ui->sys_setting_lbl_submenu_warning);
    //Write codes sys_setting_view_time_mun
    ui->sys_setting_view_time_mun = lv_obj_create(ui->sys_setting_view_submenu);

    //Set style for sys_setting_view_time_mun. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_view_time_mun, &gui_cont_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_view_time_mun, 76, 44);
    lv_obj_set_size(ui->sys_setting_view_time_mun, 450, 164);
    lv_obj_set_scrollbar_mode(ui->sys_setting_view_time_mun, LV_SCROLLBAR_MODE_OFF);
    //Write codes sys_setting_ddlist_year
    ui->sys_setting_ddlist_year = lv_dropdown_create(ui->sys_setting_view_time_mun);
    lv_dropdown_set_options(ui->sys_setting_ddlist_year, "2024\n2025\n2026\n2027\n2028\n2029\n2030\n2031\n2032\n2033\n2034");
    lv_dropdown_set_dir(ui->sys_setting_ddlist_year, LV_DIR_BOTTOM);
    lv_dropdown_set_symbol(ui->sys_setting_ddlist_year, LV_SYMBOL_DOWN);
    lv_dropdown_set_symbol(ui->sys_setting_ddlist_year, NULL);
    lv_dropdown_set_selected(ui->sys_setting_ddlist_year, 0);

    //Set style for sys_setting_ddlist_year. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_ddlist_year, &gui_ddlist_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for sys_setting_ddlist_year. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui->sys_setting_ddlist_year, &gui_ddlist_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Set style state: LV_STATE_CHECKED for style_sys_setting_ddlist_year_extra_list_selected_checked
    static lv_style_t style_sys_setting_ddlist_year_extra_list_selected_checked;
    ui_init_style(&style_sys_setting_ddlist_year_extra_list_selected_checked);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_year), &gui_ddlist_selected_checked_style, LV_PART_SELECTED | LV_STATE_CHECKED);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_year), &style_sys_setting_ddlist_year_extra_list_selected_checked, LV_PART_SELECTED | LV_STATE_CHECKED);

    //Set style state: LV_STATE_DEFAULT for style_sys_setting_ddlist_year_extra_list_main_default
    static lv_style_t style_sys_setting_ddlist_year_extra_list_main_default;
    ui_init_style(&style_sys_setting_ddlist_year_extra_list_main_default);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_year), &gui_ddlist_dropdown_list_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_year), &style_sys_setting_ddlist_year_extra_list_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style state: LV_STATE_DEFAULT for style_sys_setting_ddlist_year_extra_list_scrollbar_default
    static lv_style_t style_sys_setting_ddlist_year_extra_list_scrollbar_default;
    ui_init_style(&style_sys_setting_ddlist_year_extra_list_scrollbar_default);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_year), &gui_ddlist_scrollbar_default_style, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_year), &style_sys_setting_ddlist_year_extra_list_scrollbar_default, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_ddlist_year, 38, 26);
    lv_obj_set_size(ui->sys_setting_ddlist_year, 87, 31);
    lv_obj_set_scrollbar_mode(ui->sys_setting_ddlist_year, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->sys_setting_ddlist_year, LV_OBJ_FLAG_EVENT_BUBBLE);
    //Write codes sys_setting_ddlist_month
    ui->sys_setting_ddlist_month = lv_dropdown_create(ui->sys_setting_view_time_mun);
    lv_dropdown_set_options(ui->sys_setting_ddlist_month, "1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12");
    lv_dropdown_set_dir(ui->sys_setting_ddlist_month, LV_DIR_BOTTOM);
    lv_dropdown_set_symbol(ui->sys_setting_ddlist_month, LV_SYMBOL_DOWN);
    lv_dropdown_set_symbol(ui->sys_setting_ddlist_month, NULL);
    lv_dropdown_set_selected(ui->sys_setting_ddlist_month, 0);

    //Set style for sys_setting_ddlist_month. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_ddlist_month, &gui_ddlist_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for sys_setting_ddlist_month. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui->sys_setting_ddlist_month, &gui_ddlist_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Set style state: LV_STATE_CHECKED for style_sys_setting_ddlist_month_extra_list_selected_checked
    static lv_style_t style_sys_setting_ddlist_month_extra_list_selected_checked;
    ui_init_style(&style_sys_setting_ddlist_month_extra_list_selected_checked);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_month), &gui_ddlist_selected_checked_style, LV_PART_SELECTED | LV_STATE_CHECKED);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_month), &style_sys_setting_ddlist_month_extra_list_selected_checked, LV_PART_SELECTED | LV_STATE_CHECKED);

    //Set style state: LV_STATE_DEFAULT for style_sys_setting_ddlist_month_extra_list_main_default
    static lv_style_t style_sys_setting_ddlist_month_extra_list_main_default;
    ui_init_style(&style_sys_setting_ddlist_month_extra_list_main_default);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_month), &gui_ddlist_dropdown_list_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_month), &style_sys_setting_ddlist_month_extra_list_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style state: LV_STATE_DEFAULT for style_sys_setting_ddlist_month_extra_list_scrollbar_default
    static lv_style_t style_sys_setting_ddlist_month_extra_list_scrollbar_default;
    ui_init_style(&style_sys_setting_ddlist_month_extra_list_scrollbar_default);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_month), &gui_ddlist_scrollbar_default_style, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_month), &style_sys_setting_ddlist_month_extra_list_scrollbar_default, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_ddlist_month, 190, 26);
    lv_obj_set_size(ui->sys_setting_ddlist_month, 69, 31);
    lv_obj_set_scrollbar_mode(ui->sys_setting_ddlist_month, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->sys_setting_ddlist_month, LV_OBJ_FLAG_EVENT_BUBBLE);
    //Write codes sys_setting_ddlist_day
    ui->sys_setting_ddlist_day = lv_dropdown_create(ui->sys_setting_view_time_mun);
    lv_dropdown_set_options(ui->sys_setting_ddlist_day, "1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n24\n25\n26\n27\n28\n29\n30\n31");
    lv_dropdown_set_dir(ui->sys_setting_ddlist_day, LV_DIR_BOTTOM);
    lv_dropdown_set_symbol(ui->sys_setting_ddlist_day, LV_SYMBOL_DOWN);
    lv_dropdown_set_symbol(ui->sys_setting_ddlist_day, NULL);
    lv_dropdown_set_selected(ui->sys_setting_ddlist_day, 0);

    //Set style for sys_setting_ddlist_day. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_ddlist_day, &gui_ddlist_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for sys_setting_ddlist_day. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui->sys_setting_ddlist_day, &gui_ddlist_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Set style state: LV_STATE_CHECKED for style_sys_setting_ddlist_day_extra_list_selected_checked
    static lv_style_t style_sys_setting_ddlist_day_extra_list_selected_checked;
    ui_init_style(&style_sys_setting_ddlist_day_extra_list_selected_checked);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_day), &gui_ddlist_selected_checked_style, LV_PART_SELECTED | LV_STATE_CHECKED);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_day), &style_sys_setting_ddlist_day_extra_list_selected_checked, LV_PART_SELECTED | LV_STATE_CHECKED);

    //Set style state: LV_STATE_DEFAULT for style_sys_setting_ddlist_day_extra_list_main_default
    static lv_style_t style_sys_setting_ddlist_day_extra_list_main_default;
    ui_init_style(&style_sys_setting_ddlist_day_extra_list_main_default);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_day), &gui_ddlist_dropdown_list_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_day), &style_sys_setting_ddlist_day_extra_list_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style state: LV_STATE_DEFAULT for style_sys_setting_ddlist_day_extra_list_scrollbar_default
    static lv_style_t style_sys_setting_ddlist_day_extra_list_scrollbar_default;
    ui_init_style(&style_sys_setting_ddlist_day_extra_list_scrollbar_default);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_day), &gui_ddlist_scrollbar_default_style, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_day), &style_sys_setting_ddlist_day_extra_list_scrollbar_default, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_ddlist_day, 328, 26);
    lv_obj_set_size(ui->sys_setting_ddlist_day, 69, 31);
    lv_obj_set_scrollbar_mode(ui->sys_setting_ddlist_day, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->sys_setting_ddlist_day, LV_OBJ_FLAG_EVENT_BUBBLE);
    //Write codes sys_setting_ddlist_hour
    ui->sys_setting_ddlist_hour = lv_dropdown_create(ui->sys_setting_view_time_mun);
    lv_dropdown_set_options(ui->sys_setting_ddlist_hour, "0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23");
    lv_dropdown_set_dir(ui->sys_setting_ddlist_hour, LV_DIR_TOP);
    lv_dropdown_set_symbol(ui->sys_setting_ddlist_hour, LV_SYMBOL_UP);
    lv_dropdown_set_symbol(ui->sys_setting_ddlist_hour, NULL);
    lv_dropdown_set_selected(ui->sys_setting_ddlist_hour, 0);

    //Set style for sys_setting_ddlist_hour. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_ddlist_hour, &gui_ddlist_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for sys_setting_ddlist_hour. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui->sys_setting_ddlist_hour, &gui_ddlist_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Set style state: LV_STATE_CHECKED for style_sys_setting_ddlist_hour_extra_list_selected_checked
    static lv_style_t style_sys_setting_ddlist_hour_extra_list_selected_checked;
    ui_init_style(&style_sys_setting_ddlist_hour_extra_list_selected_checked);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_hour), &gui_ddlist_selected_checked_style, LV_PART_SELECTED | LV_STATE_CHECKED);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_hour), &style_sys_setting_ddlist_hour_extra_list_selected_checked, LV_PART_SELECTED | LV_STATE_CHECKED);

    //Set style state: LV_STATE_DEFAULT for style_sys_setting_ddlist_hour_extra_list_main_default
    static lv_style_t style_sys_setting_ddlist_hour_extra_list_main_default;
    ui_init_style(&style_sys_setting_ddlist_hour_extra_list_main_default);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_hour), &gui_ddlist_dropdown_list_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_hour), &style_sys_setting_ddlist_hour_extra_list_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style state: LV_STATE_DEFAULT for style_sys_setting_ddlist_hour_extra_list_scrollbar_default
    static lv_style_t style_sys_setting_ddlist_hour_extra_list_scrollbar_default;
    ui_init_style(&style_sys_setting_ddlist_hour_extra_list_scrollbar_default);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_hour), &gui_ddlist_scrollbar_default_style, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_hour), &style_sys_setting_ddlist_hour_extra_list_scrollbar_default, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_ddlist_hour, 52, 102);
    lv_obj_set_size(ui->sys_setting_ddlist_hour, 69, 31);
    lv_obj_set_scrollbar_mode(ui->sys_setting_ddlist_hour, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->sys_setting_ddlist_hour, LV_OBJ_FLAG_EVENT_BUBBLE);
    //Write codes sys_setting_ddlist_min
    ui->sys_setting_ddlist_min = lv_dropdown_create(ui->sys_setting_view_time_mun);
    lv_dropdown_set_options(ui->sys_setting_ddlist_min, "0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n24\n25\n26\n27\n28\n29\n30\n31\n32\n33\n34\n35\n36\n37\n38\n39\n40\n41\n42\n43\n44\n45\n46\n47\n48\n49\n50\n51\n52\n53\n54\n55\n56\n57\n58\n59");
    lv_dropdown_set_dir(ui->sys_setting_ddlist_min, LV_DIR_TOP);
    lv_dropdown_set_symbol(ui->sys_setting_ddlist_min, LV_SYMBOL_UP);
    lv_dropdown_set_symbol(ui->sys_setting_ddlist_min, NULL);
    lv_dropdown_set_selected(ui->sys_setting_ddlist_min, 0);

    //Set style for sys_setting_ddlist_min. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_ddlist_min, &gui_ddlist_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for sys_setting_ddlist_min. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui->sys_setting_ddlist_min, &gui_ddlist_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Set style state: LV_STATE_CHECKED for style_sys_setting_ddlist_min_extra_list_selected_checked
    static lv_style_t style_sys_setting_ddlist_min_extra_list_selected_checked;
    ui_init_style(&style_sys_setting_ddlist_min_extra_list_selected_checked);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_min), &gui_ddlist_selected_checked_style, LV_PART_SELECTED | LV_STATE_CHECKED);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_min), &style_sys_setting_ddlist_min_extra_list_selected_checked, LV_PART_SELECTED | LV_STATE_CHECKED);

    //Set style state: LV_STATE_DEFAULT for style_sys_setting_ddlist_min_extra_list_main_default
    static lv_style_t style_sys_setting_ddlist_min_extra_list_main_default;
    ui_init_style(&style_sys_setting_ddlist_min_extra_list_main_default);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_min), &gui_ddlist_dropdown_list_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_min), &style_sys_setting_ddlist_min_extra_list_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style state: LV_STATE_DEFAULT for style_sys_setting_ddlist_min_extra_list_scrollbar_default
    static lv_style_t style_sys_setting_ddlist_min_extra_list_scrollbar_default;
    ui_init_style(&style_sys_setting_ddlist_min_extra_list_scrollbar_default);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_min), &gui_ddlist_scrollbar_default_style, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_min), &style_sys_setting_ddlist_min_extra_list_scrollbar_default, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_ddlist_min, 190, 102);
    lv_obj_set_size(ui->sys_setting_ddlist_min, 69, 31);
    lv_obj_set_scrollbar_mode(ui->sys_setting_ddlist_min, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->sys_setting_ddlist_min, LV_OBJ_FLAG_EVENT_BUBBLE);
    //Write codes sys_setting_ddlist_sec
    ui->sys_setting_ddlist_sec = lv_dropdown_create(ui->sys_setting_view_time_mun);
    lv_dropdown_set_options(ui->sys_setting_ddlist_sec, "0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n24\n25\n26\n27\n28\n29\n30\n31\n32\n33\n34\n35\n36\n37\n38\n39\n40\n41\n42\n43\n44\n45\n46\n47\n48\n49\n50\n51\n52\n53\n54\n55\n56\n57\n58\n59");
    lv_dropdown_set_dir(ui->sys_setting_ddlist_sec, LV_DIR_TOP);
    lv_dropdown_set_symbol(ui->sys_setting_ddlist_sec, LV_SYMBOL_UP);
    lv_dropdown_set_symbol(ui->sys_setting_ddlist_sec, NULL);
    lv_dropdown_set_selected(ui->sys_setting_ddlist_sec, 0);

    //Set style for sys_setting_ddlist_sec. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_ddlist_sec, &gui_ddlist_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for sys_setting_ddlist_sec. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_add_style(ui->sys_setting_ddlist_sec, &gui_ddlist_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Set style state: LV_STATE_CHECKED for style_sys_setting_ddlist_sec_extra_list_selected_checked
    static lv_style_t style_sys_setting_ddlist_sec_extra_list_selected_checked;
    ui_init_style(&style_sys_setting_ddlist_sec_extra_list_selected_checked);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_sec), &gui_ddlist_selected_checked_style, LV_PART_SELECTED | LV_STATE_CHECKED);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_sec), &style_sys_setting_ddlist_sec_extra_list_selected_checked, LV_PART_SELECTED | LV_STATE_CHECKED);

    //Set style state: LV_STATE_DEFAULT for style_sys_setting_ddlist_sec_extra_list_main_default
    static lv_style_t style_sys_setting_ddlist_sec_extra_list_main_default;
    ui_init_style(&style_sys_setting_ddlist_sec_extra_list_main_default);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_sec), &gui_ddlist_dropdown_list_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_sec), &style_sys_setting_ddlist_sec_extra_list_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style state: LV_STATE_DEFAULT for style_sys_setting_ddlist_sec_extra_list_scrollbar_default
    static lv_style_t style_sys_setting_ddlist_sec_extra_list_scrollbar_default;
    ui_init_style(&style_sys_setting_ddlist_sec_extra_list_scrollbar_default);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_sec), &gui_ddlist_scrollbar_default_style, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_add_style(lv_dropdown_get_list(ui->sys_setting_ddlist_sec), &style_sys_setting_ddlist_sec_extra_list_scrollbar_default, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_ddlist_sec, 328, 102);
    lv_obj_set_size(ui->sys_setting_ddlist_sec, 69, 31);
    lv_obj_set_scrollbar_mode(ui->sys_setting_ddlist_sec, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->sys_setting_ddlist_sec, LV_OBJ_FLAG_EVENT_BUBBLE);
    //Write codes sys_setting_img_19
    ui->sys_setting_img_19 = lv_img_create(ui->sys_setting_view_time_mun);
    lv_img_set_src(ui->sys_setting_img_19, gui_get_res_path(GUI_RES_NUM_L_PNG));
    lv_img_set_pivot(ui->sys_setting_img_19, 0, 0);
    lv_img_set_angle(ui->sys_setting_img_19, 0);
    lv_img_set_zoom(ui->sys_setting_img_19, 256);

    //Set style for sys_setting_img_19. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_img_19, &gui_img_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_img_19, 151, 35);
    lv_obj_set_size(ui->sys_setting_img_19, 9, 13);
    lv_obj_add_flag(ui->sys_setting_img_19, LV_OBJ_FLAG_CLICKABLE);
    //Write codes sys_setting_img_20
    ui->sys_setting_img_20 = lv_img_create(ui->sys_setting_view_time_mun);
    lv_img_set_src(ui->sys_setting_img_20, gui_get_res_path(GUI_RES_NUM_L_PNG));
    lv_img_set_pivot(ui->sys_setting_img_20, 0, 0);
    lv_img_set_angle(ui->sys_setting_img_20, 0);
    lv_img_set_zoom(ui->sys_setting_img_20, 256);

    //Set style for sys_setting_img_20. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_img_20, &gui_img_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_img_20, 283, 35);
    lv_obj_set_size(ui->sys_setting_img_20, 9, 13);
    lv_obj_add_flag(ui->sys_setting_img_20, LV_OBJ_FLAG_CLICKABLE);
    //Write codes sys_setting_img_21
    ui->sys_setting_img_21 = lv_img_create(ui->sys_setting_view_time_mun);
    lv_img_set_src(ui->sys_setting_img_21, gui_get_res_path(GUI_RES_NUM_D_PNG));
    lv_img_set_pivot(ui->sys_setting_img_21, 0, 0);
    lv_img_set_angle(ui->sys_setting_img_21, 0);
    lv_img_set_zoom(ui->sys_setting_img_21, 256);

    //Set style for sys_setting_img_21. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_img_21, &gui_img_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_img_21, 149, 111);
    lv_obj_set_size(ui->sys_setting_img_21, 9, 13);
    lv_obj_add_flag(ui->sys_setting_img_21, LV_OBJ_FLAG_CLICKABLE);
    //Write codes sys_setting_img_22
    ui->sys_setting_img_22 = lv_img_create(ui->sys_setting_view_time_mun);
    lv_img_set_src(ui->sys_setting_img_22, gui_get_res_path(GUI_RES_NUM_D_PNG));
    lv_img_set_pivot(ui->sys_setting_img_22, 0, 0);
    lv_img_set_angle(ui->sys_setting_img_22, 0);
    lv_img_set_zoom(ui->sys_setting_img_22, 256);

    //Set style for sys_setting_img_22. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->sys_setting_img_22, &gui_img_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_setting_img_22, 287, 111);
    lv_obj_set_size(ui->sys_setting_img_22, 9, 13);
    lv_obj_add_flag(ui->sys_setting_img_22, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_update_layout(ui->sys_setting);
    ui->sys_setting_del = false;
    i18n_refresh_texts("sys_setting");

    //Init events for screen
    events_init_sys_setting(ui);
    return ui->sys_setting;
}
void unload_scr_sys_setting(lv_ui *ui)
{
    ui->sys_setting_del = true;
}

#endif
