/*Generate Code, Do NOT Edit!*/
#include "lvgl.h"
#include <stdio.h>
#include <stdlib.h>
#include "../gui_guider.h"
#include "../gui_events/events_init.h"
#include "../gui_events/callback_handler.h"
#include "../gui_timelines/gui_timelines.h"
#include "../../custom/custom.h"

static void kb_wifi_connect_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *kb = lv_event_get_target(e);
    if (code == LV_EVENT_READY || code == LV_EVENT_CANCEL) {
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
    }
}
__attribute__((unused)) static void ta_wifi_connect_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *ta = lv_event_get_target(e);
    lv_obj_t *kb = lv_event_get_user_data(e);
    if (code == LV_EVENT_FOCUSED || code == LV_EVENT_CLICKED) {
        lv_keyboard_set_textarea(kb, ta);
        lv_obj_move_foreground(kb);
        lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN);
    }
    if (code == LV_EVENT_CANCEL || code == LV_EVENT_DEFOCUSED) {
        lv_keyboard_set_textarea(kb, NULL);
        lv_obj_move_background(kb);
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
        lv_indev_reset(NULL, ta);
    }
}

lv_obj_t *setup_scr_wifi_connect(lv_ui *ui)
{
    //Write codes wifi_connect
    ui->wifi_connect = lv_obj_create(NULL);

    //Create keyboard on wifi_connect
    ui->g_kb_wifi_connect = lv_keyboard_create(ui->wifi_connect);
    lv_obj_add_event_cb(ui->g_kb_wifi_connect, kb_wifi_connect_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_add_flag(ui->g_kb_wifi_connect, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_style_text_font(ui->g_kb_wifi_connect, &lv_font_montserratMedium_20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_size(ui->g_kb_wifi_connect, LV_PCT(70), LV_PCT(40));
    lv_keyboard_set_mode(ui->g_kb_wifi_connect, LV_KEYBOARD_MODE_TEXT_LOWER);
    lv_group_t *def_group = lv_group_get_default();

    //Set style for wifi_connect. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui->wifi_connect, lv_color_make(0xE2, 0xDC, 0xDC), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->wifi_connect, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->wifi_connect, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(ui->wifi_connect, LV_SCROLLBAR_MODE_OFF);
    //Write codes wifi_connect_view_1
    ui->wifi_connect_view_1 = lv_obj_create(ui->wifi_connect);

    //Set style for wifi_connect_view_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->wifi_connect_view_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->wifi_connect_view_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->wifi_connect_view_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->wifi_connect_view_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->wifi_connect_view_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->wifi_connect_view_1, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->wifi_connect_view_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->wifi_connect_view_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->wifi_connect_view_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->wifi_connect_view_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->wifi_connect_view_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->wifi_connect_view_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->wifi_connect_view_1, 141, 67);
    lv_obj_set_size(ui->wifi_connect_view_1, 509, 262);
    lv_obj_set_scrollbar_mode(ui->wifi_connect_view_1, LV_SCROLLBAR_MODE_OFF);
    //Write codes wifi_connect_ssid
    ui->wifi_connect_ssid = lv_textarea_create(ui->wifi_connect_view_1);

    //Set style for wifi_connect_ssid. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->wifi_connect_ssid, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->wifi_connect_ssid, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->wifi_connect_ssid, 77, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->wifi_connect_ssid, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->wifi_connect_ssid, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->wifi_connect_ssid, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->wifi_connect_ssid, 204, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->wifi_connect_ssid, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui->wifi_connect_ssid, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->wifi_connect_ssid, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui->wifi_connect_ssid, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui->wifi_connect_ssid, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->wifi_connect_ssid, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->wifi_connect_ssid, &lv_font_montserratMedium_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->wifi_connect_ssid, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->wifi_connect_ssid, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->wifi_connect_ssid, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->wifi_connect_ssid, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->wifi_connect_ssid, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->wifi_connect_ssid, 4, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for wifi_connect_ssid. Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->wifi_connect_ssid, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->wifi_connect_ssid, lv_color_make(0x21, 0x95, 0xf6), LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->wifi_connect_ssid, 255, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->wifi_connect_ssid, 156, 71);
    lv_obj_set_size(ui->wifi_connect_ssid, 228, 39);
    lv_obj_set_scrollbar_mode(ui->wifi_connect_ssid, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(ui->wifi_connect_ssid, LV_OBJ_FLAG_CHECKABLE);

    //use keyboard on wifi_connect_ssid
    lv_obj_add_event_cb(ui->wifi_connect_ssid, ta_wifi_connect_event_cb, LV_EVENT_ALL, ui->g_kb_wifi_connect);
    //Write codes wifi_connect_pwd
    ui->wifi_connect_pwd = lv_textarea_create(ui->wifi_connect_view_1);

    //Set style for wifi_connect_pwd. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->wifi_connect_pwd, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->wifi_connect_pwd, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->wifi_connect_pwd, 77, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->wifi_connect_pwd, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->wifi_connect_pwd, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->wifi_connect_pwd, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->wifi_connect_pwd, 204, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->wifi_connect_pwd, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui->wifi_connect_pwd, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->wifi_connect_pwd, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui->wifi_connect_pwd, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui->wifi_connect_pwd, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->wifi_connect_pwd, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->wifi_connect_pwd, &lv_font_montserratMedium_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->wifi_connect_pwd, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->wifi_connect_pwd, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->wifi_connect_pwd, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->wifi_connect_pwd, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->wifi_connect_pwd, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->wifi_connect_pwd, 4, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for wifi_connect_pwd. Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->wifi_connect_pwd, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->wifi_connect_pwd, lv_color_make(0x21, 0x95, 0xf6), LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->wifi_connect_pwd, 255, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->wifi_connect_pwd, 156, 136);
    lv_obj_set_size(ui->wifi_connect_pwd, 228, 39);
    lv_obj_set_scrollbar_mode(ui->wifi_connect_pwd, LV_SCROLLBAR_MODE_OFF);

    //use keyboard on wifi_connect_pwd
    lv_obj_add_event_cb(ui->wifi_connect_pwd, ta_wifi_connect_event_cb, LV_EVENT_ALL, ui->g_kb_wifi_connect);
    //Write codes wifi_connect_lbl_1
    ui->wifi_connect_lbl_1 = lv_label_create(ui->wifi_connect_view_1);
    lv_label_set_text(ui->wifi_connect_lbl_1, "SSID");
    lv_label_set_long_mode(ui->wifi_connect_lbl_1, LV_LABEL_LONG_WRAP);

    //Set style for wifi_connect_lbl_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->wifi_connect_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->wifi_connect_lbl_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->wifi_connect_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->wifi_connect_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->wifi_connect_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->wifi_connect_lbl_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->wifi_connect_lbl_1, &lv_font_montserratMedium_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->wifi_connect_lbl_1, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->wifi_connect_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->wifi_connect_lbl_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->wifi_connect_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->wifi_connect_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->wifi_connect_lbl_1, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->wifi_connect_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->wifi_connect_lbl_1, 94, 74);
    lv_obj_set_size(ui->wifi_connect_lbl_1, 68, 38);
    lv_obj_set_scrollbar_mode(ui->wifi_connect_lbl_1, LV_SCROLLBAR_MODE_OFF);
    //Write codes wifi_connect_lbl_2
    ui->wifi_connect_lbl_2 = lv_label_create(ui->wifi_connect_view_1);
    lv_label_set_text(ui->wifi_connect_lbl_2, "PWD");
    lv_label_set_long_mode(ui->wifi_connect_lbl_2, LV_LABEL_LONG_WRAP);

    //Set style for wifi_connect_lbl_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->wifi_connect_lbl_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->wifi_connect_lbl_2, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->wifi_connect_lbl_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->wifi_connect_lbl_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->wifi_connect_lbl_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->wifi_connect_lbl_2, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->wifi_connect_lbl_2, &lv_font_montserratMedium_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->wifi_connect_lbl_2, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->wifi_connect_lbl_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->wifi_connect_lbl_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->wifi_connect_lbl_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->wifi_connect_lbl_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->wifi_connect_lbl_2, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->wifi_connect_lbl_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->wifi_connect_lbl_2, 95, 139);
    lv_obj_set_size(ui->wifi_connect_lbl_2, 68, 38);
    lv_obj_set_scrollbar_mode(ui->wifi_connect_lbl_2, LV_SCROLLBAR_MODE_OFF);
    //Write codes wifi_connect_connect
    ui->wifi_connect_connect = lv_btn_create(ui->wifi_connect_view_1);

    //Set style for wifi_connect_connect. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->wifi_connect_connect, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->wifi_connect_connect, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->wifi_connect_connect, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->wifi_connect_connect, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->wifi_connect_connect, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->wifi_connect_connect, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->wifi_connect_connect, 204, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->wifi_connect_connect, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui->wifi_connect_connect, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->wifi_connect_connect, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui->wifi_connect_connect, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui->wifi_connect_connect, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->wifi_connect_connect, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->wifi_connect_connect, &lv_font_montserratMedium_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->wifi_connect_connect, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->wifi_connect_connect, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->wifi_connect_connect, 303, 187);
    lv_obj_set_size(ui->wifi_connect_connect, 82, 33);
    lv_obj_set_scrollbar_mode(ui->wifi_connect_connect, LV_SCROLLBAR_MODE_OFF);
    ui->wifi_connect_connect_label = lv_label_create(ui->wifi_connect_connect);
    lv_label_set_text(ui->wifi_connect_connect_label, "Connect");
    lv_obj_set_style_pad_all(ui->wifi_connect_connect, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->wifi_connect_connect_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes wifi_connect_imgbtn_1
    ui->wifi_connect_imgbtn_1 = lv_imgbtn_create(ui->wifi_connect);

    //Set style for wifi_connect_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->wifi_connect_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->wifi_connect_imgbtn_1, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->wifi_connect_imgbtn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->wifi_connect_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->wifi_connect_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->wifi_connect_imgbtn_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->wifi_connect_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->wifi_connect_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->wifi_connect_imgbtn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->wifi_connect_imgbtn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->wifi_connect_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->wifi_connect_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for wifi_connect_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_PRESSED
    lv_obj_set_style_radius(ui->wifi_connect_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_clip_corner(ui->wifi_connect_imgbtn_1, true, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->wifi_connect_imgbtn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(ui->wifi_connect_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->wifi_connect_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->wifi_connect_imgbtn_1, lv_color_make(0xFF, 0x33, 0xFF), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->wifi_connect_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_recolor(ui->wifi_connect_imgbtn_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_recolor_opa(ui->wifi_connect_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->wifi_connect_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_PRESSED);

    //Set style for wifi_connect_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_CHECKED
    lv_obj_set_style_radius(ui->wifi_connect_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_clip_corner(ui->wifi_connect_imgbtn_1, true, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui->wifi_connect_imgbtn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui->wifi_connect_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->wifi_connect_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->wifi_connect_imgbtn_1, lv_color_make(0xFF, 0x33, 0xFF), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->wifi_connect_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_recolor(ui->wifi_connect_imgbtn_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_recolor_opa(ui->wifi_connect_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->wifi_connect_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_pos(ui->wifi_connect_imgbtn_1, 19, 14);
    lv_obj_set_size(ui->wifi_connect_imgbtn_1, 64, 64);
    lv_obj_set_scrollbar_mode(ui->wifi_connect_imgbtn_1, LV_SCROLLBAR_MODE_OFF);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_imgbtn_set_src(ui->wifi_connect_imgbtn_1, LV_IMGBTN_STATE_RELEASED, NULL, "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\back.png", NULL);
#else
    lv_imgbtn_set_src(ui->wifi_connect_imgbtn_1, LV_IMGBTN_STATE_RELEASED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000003.rle", NULL);
#endif
    lv_obj_add_flag(ui->wifi_connect_imgbtn_1, LV_OBJ_FLAG_CHECKABLE);
    ui->wifi_connect_imgbtn_1_label = lv_label_create(ui->wifi_connect_imgbtn_1);
    lv_label_set_text(ui->wifi_connect_imgbtn_1_label, "");
    lv_obj_set_style_pad_all(ui->wifi_connect_imgbtn_1, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->wifi_connect_imgbtn_1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_update_layout(ui->wifi_connect);
    ui->wifi_connect_del = false;

    //Init events for screen
    events_init_wifi_connect(ui);
    return ui->wifi_connect;
}
void unload_scr_wifi_connect(lv_ui *ui)
{
    ui->wifi_connect_del = true;
}
