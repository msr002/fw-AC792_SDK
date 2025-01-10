/*Generate Code, Do NOT Edit!*/
#include "lvgl.h"
#include <stdio.h>
#include <stdlib.h>
#include "../gui_guider.h"
#include "../gui_events/events_init.h"
#include "../gui_events/callback_handler.h"
#include "../gui_timelines/gui_timelines.h"
#include "../../custom/custom.h"


lv_obj_t *setup_scr_home(lv_ui *ui)
{
    //Write codes home
    ui->home = lv_obj_create(NULL);
    lv_group_t *def_group = lv_group_get_default();

    //Set style for home. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui->home, lv_color_make(0xE2, 0xDC, 0xDC), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->home, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->home, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(ui->home, LV_SCROLLBAR_MODE_OFF);
    //Write codes home_imgbtn_2
    ui->home_imgbtn_2 = lv_imgbtn_create(ui->home);

    //Set style for home_imgbtn_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->home_imgbtn_2, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->home_imgbtn_2, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->home_imgbtn_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->home_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->home_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui->home_imgbtn_2, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->home_imgbtn_2, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui->home_imgbtn_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui->home_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->home_imgbtn_2, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->home_imgbtn_2, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->home_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->home_imgbtn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->home_imgbtn_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->home_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->home_imgbtn_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for home_imgbtn_2. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui->home_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_clip_corner(ui->home_imgbtn_2, true, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(ui->home_imgbtn_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui->home_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_shadow_width(ui->home_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(ui->home_imgbtn_2, lv_color_make(0x21, 0xB4, 0xF6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->home_imgbtn_2, 4, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->home_imgbtn_2, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(ui->home_imgbtn_2, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_color(ui->home_imgbtn_2, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_font(ui->home_imgbtn_2, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor(ui->home_imgbtn_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor_opa(ui->home_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_opa(ui->home_imgbtn_2, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Set style for home_imgbtn_2. Part: LV_PART_MAIN, State: LV_STATE_PRESSED
    lv_obj_set_style_radius(ui->home_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_clip_corner(ui->home_imgbtn_2, true, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->home_imgbtn_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(ui->home_imgbtn_2, 255, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->home_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->home_imgbtn_2, lv_color_make(0xFF, 0x33, 0xFF), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->home_imgbtn_2, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_recolor(ui->home_imgbtn_2, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_recolor_opa(ui->home_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->home_imgbtn_2, 255, LV_PART_MAIN | LV_STATE_PRESSED);

    //Set style for home_imgbtn_2. Part: LV_PART_MAIN, State: LV_STATE_CHECKED
    lv_obj_set_style_radius(ui->home_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_clip_corner(ui->home_imgbtn_2, true, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui->home_imgbtn_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui->home_imgbtn_2, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->home_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->home_imgbtn_2, lv_color_make(0xFF, 0x33, 0xFF), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->home_imgbtn_2, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_recolor(ui->home_imgbtn_2, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_recolor_opa(ui->home_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->home_imgbtn_2, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_pos(ui->home_imgbtn_2, 107, 175);
    lv_obj_set_size(ui->home_imgbtn_2, 128, 128);
    lv_obj_set_scrollbar_mode(ui->home_imgbtn_2, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui->home_imgbtn_2);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_imgbtn_set_src(ui->home_imgbtn_2, LV_IMGBTN_STATE_RELEASED, NULL, "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\camera.png", NULL);
#else
    lv_imgbtn_set_src(ui->home_imgbtn_2, LV_IMGBTN_STATE_RELEASED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/55000000.zip", NULL);
#endif
    lv_obj_add_flag(ui->home_imgbtn_2, LV_OBJ_FLAG_CHECKABLE);
    ui->home_imgbtn_2_label = lv_label_create(ui->home_imgbtn_2);
    lv_label_set_text(ui->home_imgbtn_2_label, "");
    lv_obj_set_style_pad_all(ui->home_imgbtn_2, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->home_imgbtn_2_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes home_imgbtn_1
    ui->home_imgbtn_1 = lv_imgbtn_create(ui->home);

    //Set style for home_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->home_imgbtn_1, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->home_imgbtn_1, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->home_imgbtn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->home_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->home_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui->home_imgbtn_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->home_imgbtn_1, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui->home_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui->home_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->home_imgbtn_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->home_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->home_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->home_imgbtn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->home_imgbtn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->home_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->home_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for home_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui->home_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_clip_corner(ui->home_imgbtn_1, true, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(ui->home_imgbtn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui->home_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_shadow_width(ui->home_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(ui->home_imgbtn_1, lv_color_make(0x21, 0xB4, 0xF6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->home_imgbtn_1, 4, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->home_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(ui->home_imgbtn_1, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_color(ui->home_imgbtn_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_font(ui->home_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor(ui->home_imgbtn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor_opa(ui->home_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_opa(ui->home_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Set style for home_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_PRESSED
    lv_obj_set_style_radius(ui->home_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_clip_corner(ui->home_imgbtn_1, true, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->home_imgbtn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(ui->home_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->home_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->home_imgbtn_1, lv_color_make(0xFF, 0x33, 0xFF), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->home_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_recolor(ui->home_imgbtn_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_recolor_opa(ui->home_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->home_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_PRESSED);

    //Set style for home_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_CHECKED
    lv_obj_set_style_radius(ui->home_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_clip_corner(ui->home_imgbtn_1, true, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui->home_imgbtn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui->home_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->home_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->home_imgbtn_1, lv_color_make(0xFF, 0x33, 0xFF), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->home_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_recolor(ui->home_imgbtn_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_recolor_opa(ui->home_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->home_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_pos(ui->home_imgbtn_1, 336, 175);
    lv_obj_set_size(ui->home_imgbtn_1, 128, 128);
    lv_obj_set_scrollbar_mode(ui->home_imgbtn_1, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui->home_imgbtn_1);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_imgbtn_set_src(ui->home_imgbtn_1, LV_IMGBTN_STATE_RELEASED, NULL, "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\link.png", NULL);
#else
    lv_imgbtn_set_src(ui->home_imgbtn_1, LV_IMGBTN_STATE_RELEASED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/55000001.zip", NULL);
#endif
    lv_obj_add_flag(ui->home_imgbtn_1, LV_OBJ_FLAG_CHECKABLE);
    ui->home_imgbtn_1_label = lv_label_create(ui->home_imgbtn_1);
    lv_label_set_text(ui->home_imgbtn_1_label, "");
    lv_obj_set_style_pad_all(ui->home_imgbtn_1, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->home_imgbtn_1_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes home_imgbtn_3
    ui->home_imgbtn_3 = lv_imgbtn_create(ui->home);

    //Set style for home_imgbtn_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->home_imgbtn_3, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->home_imgbtn_3, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->home_imgbtn_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->home_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->home_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui->home_imgbtn_3, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->home_imgbtn_3, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui->home_imgbtn_3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui->home_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->home_imgbtn_3, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->home_imgbtn_3, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->home_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->home_imgbtn_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->home_imgbtn_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->home_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->home_imgbtn_3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for home_imgbtn_3. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui->home_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_clip_corner(ui->home_imgbtn_3, true, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(ui->home_imgbtn_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui->home_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_shadow_width(ui->home_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(ui->home_imgbtn_3, lv_color_make(0x21, 0xB4, 0xF6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->home_imgbtn_3, 4, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->home_imgbtn_3, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(ui->home_imgbtn_3, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_color(ui->home_imgbtn_3, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_font(ui->home_imgbtn_3, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor(ui->home_imgbtn_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor_opa(ui->home_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_opa(ui->home_imgbtn_3, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Set style for home_imgbtn_3. Part: LV_PART_MAIN, State: LV_STATE_PRESSED
    lv_obj_set_style_radius(ui->home_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_clip_corner(ui->home_imgbtn_3, true, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->home_imgbtn_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(ui->home_imgbtn_3, 255, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->home_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->home_imgbtn_3, lv_color_make(0xFF, 0x33, 0xFF), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->home_imgbtn_3, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_recolor(ui->home_imgbtn_3, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_recolor_opa(ui->home_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->home_imgbtn_3, 255, LV_PART_MAIN | LV_STATE_PRESSED);

    //Set style for home_imgbtn_3. Part: LV_PART_MAIN, State: LV_STATE_CHECKED
    lv_obj_set_style_radius(ui->home_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_clip_corner(ui->home_imgbtn_3, true, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui->home_imgbtn_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui->home_imgbtn_3, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->home_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->home_imgbtn_3, lv_color_make(0xFF, 0x33, 0xFF), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->home_imgbtn_3, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_recolor(ui->home_imgbtn_3, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_recolor_opa(ui->home_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->home_imgbtn_3, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_pos(ui->home_imgbtn_3, 561, 175);
    lv_obj_set_size(ui->home_imgbtn_3, 128, 128);
    lv_obj_set_scrollbar_mode(ui->home_imgbtn_3, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui->home_imgbtn_3);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_imgbtn_set_src(ui->home_imgbtn_3, LV_IMGBTN_STATE_RELEASED, NULL, "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\dir.png", NULL);
#else
    lv_imgbtn_set_src(ui->home_imgbtn_3, LV_IMGBTN_STATE_RELEASED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/55000002.zip", NULL);
#endif
    lv_obj_add_flag(ui->home_imgbtn_3, LV_OBJ_FLAG_CHECKABLE);
    ui->home_imgbtn_3_label = lv_label_create(ui->home_imgbtn_3);
    lv_label_set_text(ui->home_imgbtn_3_label, "");
    lv_obj_set_style_pad_all(ui->home_imgbtn_3, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->home_imgbtn_3_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_update_layout(ui->home);
    ui->home_del = false;

    //Init events for screen
    events_init_home(ui);
    return ui->home;
}
void unload_scr_home(lv_ui *ui)
{
    ui->home_del = true;
}
