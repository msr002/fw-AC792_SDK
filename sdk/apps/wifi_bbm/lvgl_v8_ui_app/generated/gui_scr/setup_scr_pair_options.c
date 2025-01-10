/*Generate Code, Do NOT Edit!*/
#include "lvgl.h"
#include <stdio.h>
#include <stdlib.h>
#include "../gui_guider.h"
#include "../gui_events/events_init.h"
#include "../gui_events/callback_handler.h"
#include "../gui_timelines/gui_timelines.h"
#include "../../custom/custom.h"


lv_obj_t *setup_scr_pair_options(lv_ui *ui)
{
    //Write codes pair_options
    ui->pair_options = lv_obj_create(NULL);
    lv_group_t *def_group = lv_group_get_default();

    //Set style for pair_options. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui->pair_options, lv_color_make(0xE2, 0xDC, 0xDC), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->pair_options, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->pair_options, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(ui->pair_options, LV_SCROLLBAR_MODE_OFF);
    //Write codes pair_options_imgbtn_1
    ui->pair_options_imgbtn_1 = lv_imgbtn_create(ui->pair_options);

    //Set style for pair_options_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->pair_options_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->pair_options_imgbtn_1, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->pair_options_imgbtn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->pair_options_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->pair_options_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->pair_options_imgbtn_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->pair_options_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->pair_options_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->pair_options_imgbtn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->pair_options_imgbtn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->pair_options_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->pair_options_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for pair_options_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui->pair_options_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_clip_corner(ui->pair_options_imgbtn_1, true, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(ui->pair_options_imgbtn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui->pair_options_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_shadow_width(ui->pair_options_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(ui->pair_options_imgbtn_1, lv_color_make(0x21, 0xB4, 0xF6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->pair_options_imgbtn_1, 4, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->pair_options_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(ui->pair_options_imgbtn_1, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_color(ui->pair_options_imgbtn_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_font(ui->pair_options_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor(ui->pair_options_imgbtn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor_opa(ui->pair_options_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_opa(ui->pair_options_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Set style for pair_options_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_PRESSED
    lv_obj_set_style_radius(ui->pair_options_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_clip_corner(ui->pair_options_imgbtn_1, true, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->pair_options_imgbtn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(ui->pair_options_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->pair_options_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->pair_options_imgbtn_1, lv_color_make(0xFF, 0x33, 0xFF), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->pair_options_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_recolor(ui->pair_options_imgbtn_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_recolor_opa(ui->pair_options_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->pair_options_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_PRESSED);

    //Set style for pair_options_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_CHECKED
    lv_obj_set_style_radius(ui->pair_options_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_clip_corner(ui->pair_options_imgbtn_1, true, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui->pair_options_imgbtn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui->pair_options_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->pair_options_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->pair_options_imgbtn_1, lv_color_make(0xFF, 0x33, 0xFF), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->pair_options_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_recolor(ui->pair_options_imgbtn_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_recolor_opa(ui->pair_options_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->pair_options_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_pos(ui->pair_options_imgbtn_1, 185, 173);
    lv_obj_set_size(ui->pair_options_imgbtn_1, 128, 128);
    lv_obj_set_scrollbar_mode(ui->pair_options_imgbtn_1, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui->pair_options_imgbtn_1);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_imgbtn_set_src(ui->pair_options_imgbtn_1, LV_IMGBTN_STATE_RELEASED, NULL, "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\pair_opt_pair.png", NULL);
#else
    lv_imgbtn_set_src(ui->pair_options_imgbtn_1, LV_IMGBTN_STATE_RELEASED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/55000009.zip", NULL);
#endif
    lv_obj_add_flag(ui->pair_options_imgbtn_1, LV_OBJ_FLAG_CHECKABLE);
    ui->pair_options_imgbtn_1_label = lv_label_create(ui->pair_options_imgbtn_1);
    lv_label_set_text(ui->pair_options_imgbtn_1_label, "");
    lv_obj_set_style_pad_all(ui->pair_options_imgbtn_1, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->pair_options_imgbtn_1_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes pair_options_imgbtn_2
    ui->pair_options_imgbtn_2 = lv_imgbtn_create(ui->pair_options);

    //Set style for pair_options_imgbtn_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->pair_options_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->pair_options_imgbtn_2, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->pair_options_imgbtn_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->pair_options_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->pair_options_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->pair_options_imgbtn_2, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->pair_options_imgbtn_2, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->pair_options_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->pair_options_imgbtn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->pair_options_imgbtn_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->pair_options_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->pair_options_imgbtn_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for pair_options_imgbtn_2. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui->pair_options_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_clip_corner(ui->pair_options_imgbtn_2, true, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(ui->pair_options_imgbtn_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui->pair_options_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_shadow_width(ui->pair_options_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(ui->pair_options_imgbtn_2, lv_color_make(0x21, 0xB4, 0xF6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->pair_options_imgbtn_2, 4, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->pair_options_imgbtn_2, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(ui->pair_options_imgbtn_2, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_color(ui->pair_options_imgbtn_2, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_font(ui->pair_options_imgbtn_2, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor(ui->pair_options_imgbtn_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor_opa(ui->pair_options_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_opa(ui->pair_options_imgbtn_2, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Set style for pair_options_imgbtn_2. Part: LV_PART_MAIN, State: LV_STATE_PRESSED
    lv_obj_set_style_radius(ui->pair_options_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_clip_corner(ui->pair_options_imgbtn_2, true, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->pair_options_imgbtn_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(ui->pair_options_imgbtn_2, 255, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->pair_options_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->pair_options_imgbtn_2, lv_color_make(0xFF, 0x33, 0xFF), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->pair_options_imgbtn_2, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_recolor(ui->pair_options_imgbtn_2, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_recolor_opa(ui->pair_options_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->pair_options_imgbtn_2, 255, LV_PART_MAIN | LV_STATE_PRESSED);

    //Set style for pair_options_imgbtn_2. Part: LV_PART_MAIN, State: LV_STATE_CHECKED
    lv_obj_set_style_radius(ui->pair_options_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_clip_corner(ui->pair_options_imgbtn_2, true, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui->pair_options_imgbtn_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui->pair_options_imgbtn_2, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->pair_options_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->pair_options_imgbtn_2, lv_color_make(0xFF, 0x33, 0xFF), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->pair_options_imgbtn_2, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_recolor(ui->pair_options_imgbtn_2, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_recolor_opa(ui->pair_options_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->pair_options_imgbtn_2, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_pos(ui->pair_options_imgbtn_2, 489, 173);
    lv_obj_set_size(ui->pair_options_imgbtn_2, 128, 128);
    lv_obj_set_scrollbar_mode(ui->pair_options_imgbtn_2, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui->pair_options_imgbtn_2);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_imgbtn_set_src(ui->pair_options_imgbtn_2, LV_IMGBTN_STATE_RELEASED, NULL, "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\pair_opt_unpair.png", NULL);
#else
    lv_imgbtn_set_src(ui->pair_options_imgbtn_2, LV_IMGBTN_STATE_RELEASED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/5500000a.zip", NULL);
#endif
    lv_obj_add_flag(ui->pair_options_imgbtn_2, LV_OBJ_FLAG_CHECKABLE);
    ui->pair_options_imgbtn_2_label = lv_label_create(ui->pair_options_imgbtn_2);
    lv_label_set_text(ui->pair_options_imgbtn_2_label, "");
    lv_obj_set_style_pad_all(ui->pair_options_imgbtn_2, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->pair_options_imgbtn_2_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes pair_options_lbl_1
    ui->pair_options_lbl_1 = lv_label_create(ui->pair_options);
    lv_label_set_text(ui->pair_options_lbl_1, "Go to pairing");
    lv_label_set_long_mode(ui->pair_options_lbl_1, LV_LABEL_LONG_WRAP);

    //Set style for pair_options_lbl_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->pair_options_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->pair_options_lbl_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->pair_options_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->pair_options_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->pair_options_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->pair_options_lbl_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->pair_options_lbl_1, &lv_font_montserratMedium_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->pair_options_lbl_1, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->pair_options_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->pair_options_lbl_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->pair_options_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->pair_options_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->pair_options_lbl_1, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->pair_options_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->pair_options_lbl_1, 170, 306);
    lv_obj_set_size(ui->pair_options_lbl_1, 164, 38);
    lv_obj_set_scrollbar_mode(ui->pair_options_lbl_1, LV_SCROLLBAR_MODE_OFF);
    //Write codes pair_options_lbl_2
    ui->pair_options_lbl_2 = lv_label_create(ui->pair_options);
    lv_label_set_text(ui->pair_options_lbl_2, "Go to unpair");
    lv_label_set_long_mode(ui->pair_options_lbl_2, LV_LABEL_LONG_WRAP);

    //Set style for pair_options_lbl_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->pair_options_lbl_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->pair_options_lbl_2, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->pair_options_lbl_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->pair_options_lbl_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->pair_options_lbl_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->pair_options_lbl_2, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->pair_options_lbl_2, &lv_font_montserratMedium_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->pair_options_lbl_2, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->pair_options_lbl_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->pair_options_lbl_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->pair_options_lbl_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->pair_options_lbl_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->pair_options_lbl_2, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->pair_options_lbl_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->pair_options_lbl_2, 489, 306);
    lv_obj_set_size(ui->pair_options_lbl_2, 141, 27);
    lv_obj_set_scrollbar_mode(ui->pair_options_lbl_2, LV_SCROLLBAR_MODE_OFF);
    //Write codes pair_options_imgbtn_4
    ui->pair_options_imgbtn_4 = lv_imgbtn_create(ui->pair_options);

    //Set style for pair_options_imgbtn_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->pair_options_imgbtn_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->pair_options_imgbtn_4, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->pair_options_imgbtn_4, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->pair_options_imgbtn_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->pair_options_imgbtn_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->pair_options_imgbtn_4, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->pair_options_imgbtn_4, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->pair_options_imgbtn_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->pair_options_imgbtn_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->pair_options_imgbtn_4, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->pair_options_imgbtn_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->pair_options_imgbtn_4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for pair_options_imgbtn_4. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui->pair_options_imgbtn_4, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_clip_corner(ui->pair_options_imgbtn_4, true, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(ui->pair_options_imgbtn_4, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui->pair_options_imgbtn_4, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_shadow_width(ui->pair_options_imgbtn_4, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(ui->pair_options_imgbtn_4, lv_color_make(0x21, 0xB4, 0xF6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->pair_options_imgbtn_4, 4, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->pair_options_imgbtn_4, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(ui->pair_options_imgbtn_4, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_color(ui->pair_options_imgbtn_4, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_font(ui->pair_options_imgbtn_4, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor(ui->pair_options_imgbtn_4, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor_opa(ui->pair_options_imgbtn_4, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_opa(ui->pair_options_imgbtn_4, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Set style for pair_options_imgbtn_4. Part: LV_PART_MAIN, State: LV_STATE_PRESSED
    lv_obj_set_style_radius(ui->pair_options_imgbtn_4, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_clip_corner(ui->pair_options_imgbtn_4, true, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->pair_options_imgbtn_4, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(ui->pair_options_imgbtn_4, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->pair_options_imgbtn_4, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->pair_options_imgbtn_4, lv_color_make(0xFF, 0x33, 0xFF), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->pair_options_imgbtn_4, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_recolor(ui->pair_options_imgbtn_4, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_recolor_opa(ui->pair_options_imgbtn_4, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->pair_options_imgbtn_4, 255, LV_PART_MAIN | LV_STATE_PRESSED);

    //Set style for pair_options_imgbtn_4. Part: LV_PART_MAIN, State: LV_STATE_CHECKED
    lv_obj_set_style_radius(ui->pair_options_imgbtn_4, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_clip_corner(ui->pair_options_imgbtn_4, true, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui->pair_options_imgbtn_4, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui->pair_options_imgbtn_4, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->pair_options_imgbtn_4, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->pair_options_imgbtn_4, lv_color_make(0xFF, 0x33, 0xFF), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->pair_options_imgbtn_4, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_recolor(ui->pair_options_imgbtn_4, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_recolor_opa(ui->pair_options_imgbtn_4, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->pair_options_imgbtn_4, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_pos(ui->pair_options_imgbtn_4, 25, 22);
    lv_obj_set_size(ui->pair_options_imgbtn_4, 64, 64);
    lv_obj_set_scrollbar_mode(ui->pair_options_imgbtn_4, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui->pair_options_imgbtn_4);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_imgbtn_set_src(ui->pair_options_imgbtn_4, LV_IMGBTN_STATE_RELEASED, NULL, "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\back.png", NULL);
    lv_imgbtn_set_src(ui->pair_options_imgbtn_4, LV_IMGBTN_STATE_PRESSED, NULL, "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\back.png", NULL);
    lv_imgbtn_set_src(ui->pair_options_imgbtn_4, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\back.png", NULL);
    lv_imgbtn_set_src(ui->pair_options_imgbtn_4, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\back.png", NULL);
#else
    lv_imgbtn_set_src(ui->pair_options_imgbtn_4, LV_IMGBTN_STATE_RELEASED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/55000005.zip", NULL);
    lv_imgbtn_set_src(ui->pair_options_imgbtn_4, LV_IMGBTN_STATE_PRESSED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/55000005.zip", NULL);
    lv_imgbtn_set_src(ui->pair_options_imgbtn_4, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/55000005.zip", NULL);
    lv_imgbtn_set_src(ui->pair_options_imgbtn_4, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/55000005.zip", NULL);
#endif
    lv_obj_add_flag(ui->pair_options_imgbtn_4, LV_OBJ_FLAG_CHECKABLE);
    ui->pair_options_imgbtn_4_label = lv_label_create(ui->pair_options_imgbtn_4);
    lv_label_set_text(ui->pair_options_imgbtn_4_label, "");
    lv_obj_set_style_pad_all(ui->pair_options_imgbtn_4, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->pair_options_imgbtn_4_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_update_layout(ui->pair_options);
    ui->pair_options_del = false;

    //Init events for screen
    events_init_pair_options(ui);
    return ui->pair_options;
}
void unload_scr_pair_options(lv_ui *ui)
{
    ui->pair_options_del = true;
}
