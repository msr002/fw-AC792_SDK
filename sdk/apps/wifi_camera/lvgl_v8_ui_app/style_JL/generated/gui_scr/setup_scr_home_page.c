#include "app_config.h"
#ifdef CONFIG_UI_STYLE_JL_ENABLE
/*Generate Code, Do NOT Edit!*/
#include "lvgl.h"
#include <stdio.h>
#include <stdlib.h>
#include "../gui_guider.h"
#include "../gui_events/events_init.h"
#include "../gui_events/callback_handler.h"
#include "../gui_timelines/gui_timelines.h"
#include "../../custom/custom.h"


lv_obj_t *setup_scr_home_page(lv_ui *ui)
{
    //Write codes home_page
    ui->home_page = lv_obj_create(NULL);
    lv_group_t *def_group = lv_group_get_default();

    //Set style for home_page. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui->home_page, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->home_page, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->home_page, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(ui->home_page, LV_SCROLLBAR_MODE_OFF);
    //Write codes home_page_imgbtn_1
    ui->home_page_imgbtn_1 = lv_imgbtn_create(ui->home_page);

    //Set style for home_page_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->home_page_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->home_page_imgbtn_1, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->home_page_imgbtn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->home_page_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->home_page_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui->home_page_imgbtn_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->home_page_imgbtn_1, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui->home_page_imgbtn_1, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui->home_page_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->home_page_imgbtn_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->home_page_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->home_page_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->home_page_imgbtn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->home_page_imgbtn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->home_page_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->home_page_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for home_page_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_PRESSED
    lv_obj_set_style_radius(ui->home_page_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_clip_corner(ui->home_page_imgbtn_1, true, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->home_page_imgbtn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(ui->home_page_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->home_page_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->home_page_imgbtn_1, lv_color_make(0xFF, 0x33, 0xFF), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->home_page_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_recolor(ui->home_page_imgbtn_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_recolor_opa(ui->home_page_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->home_page_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_PRESSED);

    //Set style for home_page_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_CHECKED
    lv_obj_set_style_radius(ui->home_page_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_clip_corner(ui->home_page_imgbtn_1, true, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui->home_page_imgbtn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui->home_page_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->home_page_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->home_page_imgbtn_1, lv_color_make(0xFF, 0x33, 0xFF), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->home_page_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_recolor(ui->home_page_imgbtn_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_recolor_opa(ui->home_page_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->home_page_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_CHECKED);

    //Set style for home_page_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui->home_page_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_clip_corner(ui->home_page_imgbtn_1, true, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(ui->home_page_imgbtn_1, lv_color_make(0xB1, 0x3E, 0x3E), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui->home_page_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_shadow_width(ui->home_page_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(ui->home_page_imgbtn_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->home_page_imgbtn_1, 5, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->home_page_imgbtn_1, 128, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(ui->home_page_imgbtn_1, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_color(ui->home_page_imgbtn_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_font(ui->home_page_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_align(ui->home_page_imgbtn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor(ui->home_page_imgbtn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor_opa(ui->home_page_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_opa(ui->home_page_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->home_page_imgbtn_1, 163, 189);
    lv_obj_set_size(ui->home_page_imgbtn_1, 128, 220);
    lv_obj_set_scrollbar_mode(ui->home_page_imgbtn_1, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui->home_page_imgbtn_1);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_imgbtn_set_src(ui->home_page_imgbtn_1, LV_IMGBTN_STATE_RELEASED, NULL, "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\import\\image\\video_page\\main_page\\video.png", NULL);
    lv_imgbtn_set_src(ui->home_page_imgbtn_1, LV_IMGBTN_STATE_PRESSED, NULL, "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\import\\image\\video_page\\main_page\\video__on.png", NULL);
    lv_imgbtn_set_src(ui->home_page_imgbtn_1, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\import\\image\\video_page\\main_page\\video.png", NULL);
    lv_imgbtn_set_src(ui->home_page_imgbtn_1, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\import\\image\\video_page\\main_page\\video__on.png", NULL);
#else
    lv_imgbtn_set_src(ui->home_page_imgbtn_1, LV_IMGBTN_STATE_RELEASED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/5500003f.zip", NULL);
    lv_imgbtn_set_src(ui->home_page_imgbtn_1, LV_IMGBTN_STATE_PRESSED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/55000040.zip", NULL);
    lv_imgbtn_set_src(ui->home_page_imgbtn_1, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/5500003f.zip", NULL);
    lv_imgbtn_set_src(ui->home_page_imgbtn_1, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/55000040.zip", NULL);
#endif
    lv_obj_add_flag(ui->home_page_imgbtn_1, LV_OBJ_FLAG_CHECKABLE);
    ui->home_page_imgbtn_1_label = lv_label_create(ui->home_page_imgbtn_1);
    lv_label_set_text(ui->home_page_imgbtn_1_label, "");
    lv_obj_set_style_pad_all(ui->home_page_imgbtn_1, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->home_page_imgbtn_1_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes home_page_imgbtn_2
    ui->home_page_imgbtn_2 = lv_imgbtn_create(ui->home_page);

    //Set style for home_page_imgbtn_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->home_page_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->home_page_imgbtn_2, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->home_page_imgbtn_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->home_page_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->home_page_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->home_page_imgbtn_2, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->home_page_imgbtn_2, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->home_page_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->home_page_imgbtn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->home_page_imgbtn_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->home_page_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->home_page_imgbtn_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for home_page_imgbtn_2. Part: LV_PART_MAIN, State: LV_STATE_PRESSED
    lv_obj_set_style_radius(ui->home_page_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_clip_corner(ui->home_page_imgbtn_2, true, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->home_page_imgbtn_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(ui->home_page_imgbtn_2, 255, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->home_page_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->home_page_imgbtn_2, lv_color_make(0xFF, 0x33, 0xFF), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->home_page_imgbtn_2, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_recolor(ui->home_page_imgbtn_2, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_recolor_opa(ui->home_page_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->home_page_imgbtn_2, 255, LV_PART_MAIN | LV_STATE_PRESSED);

    //Set style for home_page_imgbtn_2. Part: LV_PART_MAIN, State: LV_STATE_CHECKED
    lv_obj_set_style_radius(ui->home_page_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_clip_corner(ui->home_page_imgbtn_2, true, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui->home_page_imgbtn_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui->home_page_imgbtn_2, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->home_page_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->home_page_imgbtn_2, lv_color_make(0xFF, 0x33, 0xFF), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->home_page_imgbtn_2, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_recolor(ui->home_page_imgbtn_2, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_recolor_opa(ui->home_page_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->home_page_imgbtn_2, 255, LV_PART_MAIN | LV_STATE_CHECKED);

    //Set style for home_page_imgbtn_2. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui->home_page_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_clip_corner(ui->home_page_imgbtn_2, true, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(ui->home_page_imgbtn_2, lv_color_make(0x00, 0x09, 0x99), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui->home_page_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_shadow_width(ui->home_page_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(ui->home_page_imgbtn_2, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->home_page_imgbtn_2, 5, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->home_page_imgbtn_2, 128, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(ui->home_page_imgbtn_2, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_color(ui->home_page_imgbtn_2, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_font(ui->home_page_imgbtn_2, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_align(ui->home_page_imgbtn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor(ui->home_page_imgbtn_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor_opa(ui->home_page_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_opa(ui->home_page_imgbtn_2, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->home_page_imgbtn_2, 337, 189);
    lv_obj_set_size(ui->home_page_imgbtn_2, 128, 220);
    lv_obj_set_scrollbar_mode(ui->home_page_imgbtn_2, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui->home_page_imgbtn_2);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_imgbtn_set_src(ui->home_page_imgbtn_2, LV_IMGBTN_STATE_RELEASED, NULL, "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\import\\image\\video_page\\main_page\\file.png", NULL);
    lv_imgbtn_set_src(ui->home_page_imgbtn_2, LV_IMGBTN_STATE_PRESSED, NULL, "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\import\\image\\video_page\\main_page\\file_on.png", NULL);
    lv_imgbtn_set_src(ui->home_page_imgbtn_2, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\import\\image\\video_page\\main_page\\file.png", NULL);
    lv_imgbtn_set_src(ui->home_page_imgbtn_2, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\import\\image\\video_page\\main_page\\file_on.png", NULL);
#else
    lv_imgbtn_set_src(ui->home_page_imgbtn_2, LV_IMGBTN_STATE_RELEASED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/55000041.zip", NULL);
    lv_imgbtn_set_src(ui->home_page_imgbtn_2, LV_IMGBTN_STATE_PRESSED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/55000042.zip", NULL);
    lv_imgbtn_set_src(ui->home_page_imgbtn_2, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/55000041.zip", NULL);
    lv_imgbtn_set_src(ui->home_page_imgbtn_2, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/55000042.zip", NULL);
#endif
    lv_obj_add_flag(ui->home_page_imgbtn_2, LV_OBJ_FLAG_CHECKABLE);
    ui->home_page_imgbtn_2_label = lv_label_create(ui->home_page_imgbtn_2);
    lv_label_set_text(ui->home_page_imgbtn_2_label, "");
    lv_obj_set_style_pad_all(ui->home_page_imgbtn_2, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->home_page_imgbtn_2_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes home_page_imgbtn_3
    ui->home_page_imgbtn_3 = lv_imgbtn_create(ui->home_page);

    //Set style for home_page_imgbtn_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->home_page_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->home_page_imgbtn_3, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->home_page_imgbtn_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->home_page_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->home_page_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->home_page_imgbtn_3, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->home_page_imgbtn_3, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->home_page_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->home_page_imgbtn_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->home_page_imgbtn_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->home_page_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->home_page_imgbtn_3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for home_page_imgbtn_3. Part: LV_PART_MAIN, State: LV_STATE_PRESSED
    lv_obj_set_style_radius(ui->home_page_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_clip_corner(ui->home_page_imgbtn_3, true, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->home_page_imgbtn_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(ui->home_page_imgbtn_3, 255, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->home_page_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->home_page_imgbtn_3, lv_color_make(0xFF, 0x33, 0xFF), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->home_page_imgbtn_3, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_recolor(ui->home_page_imgbtn_3, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_recolor_opa(ui->home_page_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->home_page_imgbtn_3, 255, LV_PART_MAIN | LV_STATE_PRESSED);

    //Set style for home_page_imgbtn_3. Part: LV_PART_MAIN, State: LV_STATE_CHECKED
    lv_obj_set_style_radius(ui->home_page_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_clip_corner(ui->home_page_imgbtn_3, true, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui->home_page_imgbtn_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui->home_page_imgbtn_3, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->home_page_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->home_page_imgbtn_3, lv_color_make(0xFF, 0x33, 0xFF), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->home_page_imgbtn_3, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_recolor(ui->home_page_imgbtn_3, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_recolor_opa(ui->home_page_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->home_page_imgbtn_3, 255, LV_PART_MAIN | LV_STATE_CHECKED);

    //Set style for home_page_imgbtn_3. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui->home_page_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_clip_corner(ui->home_page_imgbtn_3, true, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(ui->home_page_imgbtn_3, lv_color_make(0xf9, 0x99, 0x99), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui->home_page_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_shadow_width(ui->home_page_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(ui->home_page_imgbtn_3, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->home_page_imgbtn_3, 5, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->home_page_imgbtn_3, 128, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(ui->home_page_imgbtn_3, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_color(ui->home_page_imgbtn_3, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_font(ui->home_page_imgbtn_3, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_align(ui->home_page_imgbtn_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor(ui->home_page_imgbtn_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor_opa(ui->home_page_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_opa(ui->home_page_imgbtn_3, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->home_page_imgbtn_3, 513, 189);
    lv_obj_set_size(ui->home_page_imgbtn_3, 128, 220);
    lv_obj_set_scrollbar_mode(ui->home_page_imgbtn_3, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui->home_page_imgbtn_3);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_imgbtn_set_src(ui->home_page_imgbtn_3, LV_IMGBTN_STATE_RELEASED, NULL, "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\import\\image\\video_page\\main_page\\setting.png", NULL);
    lv_imgbtn_set_src(ui->home_page_imgbtn_3, LV_IMGBTN_STATE_PRESSED, NULL, "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\import\\image\\video_page\\main_page\\setting_on.png", NULL);
    lv_imgbtn_set_src(ui->home_page_imgbtn_3, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\import\\image\\video_page\\main_page\\setting.png", NULL);
    lv_imgbtn_set_src(ui->home_page_imgbtn_3, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\import\\image\\video_page\\main_page\\setting_on.png", NULL);
#else
    lv_imgbtn_set_src(ui->home_page_imgbtn_3, LV_IMGBTN_STATE_RELEASED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/55000043.zip", NULL);
    lv_imgbtn_set_src(ui->home_page_imgbtn_3, LV_IMGBTN_STATE_PRESSED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/55000044.zip", NULL);
    lv_imgbtn_set_src(ui->home_page_imgbtn_3, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/55000043.zip", NULL);
    lv_imgbtn_set_src(ui->home_page_imgbtn_3, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/55000044.zip", NULL);
#endif
    lv_obj_add_flag(ui->home_page_imgbtn_3, LV_OBJ_FLAG_CHECKABLE);
    ui->home_page_imgbtn_3_label = lv_label_create(ui->home_page_imgbtn_3);
    lv_label_set_text(ui->home_page_imgbtn_3_label, "");
    lv_obj_set_style_pad_all(ui->home_page_imgbtn_3, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->home_page_imgbtn_3_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes home_page_img_1
    ui->home_page_img_1 = lv_img_create(ui->home_page);

    //Set style for home_page_img_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->home_page_img_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->home_page_img_1, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->home_page_img_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->home_page_img_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->home_page_img_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->home_page_img_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->home_page_img_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->home_page_img_1, 28, 21);
    lv_obj_set_size(ui->home_page_img_1, 48, 48);
    lv_obj_set_scrollbar_mode(ui->home_page_img_1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->home_page_img_1, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_img_set_src(ui->home_page_img_1, "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\import\\image\\video_page\\battery\\full.png");
#else
    lv_img_set_src(ui->home_page_img_1, "mnt/sdfile/EXT_RESERVED/uipackres/ui/5500002a.zip");
#endif
    lv_img_set_pivot(ui->home_page_img_1, 0, 0);
    lv_img_set_angle(ui->home_page_img_1, 0);
    lv_img_set_zoom(ui->home_page_img_1, 256);
    static bool timer_home_page_digitclock_1_enabled = false;

    //Write codes home_page_digitclock_1
    ui->home_page_digitclock_1 = lv_label_create(ui->home_page);
    lv_label_set_text_fmt(ui->home_page_digitclock_1, "%04d-%02d-%02d %02d:%02d:%02d", 2024, 06, 13, 21 % 12, 25, 50);
    lv_obj_set_style_text_align(ui->home_page_digitclock_1, LV_TEXT_ALIGN_CENTER, 0);

    //Set style for home_page_digitclock_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->home_page_digitclock_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->home_page_digitclock_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->home_page_digitclock_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->home_page_digitclock_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->home_page_digitclock_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->home_page_digitclock_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->home_page_digitclock_1, &lv_font_FangZhengKaiTiJianTi_1_54, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->home_page_digitclock_1, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->home_page_digitclock_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->home_page_digitclock_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->home_page_digitclock_1, 7, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->home_page_digitclock_1, 92, 14);
    lv_obj_set_size(ui->home_page_digitclock_1, 613, 75);
    //Write codes home_page_lbl_3
    ui->home_page_lbl_3 = lv_label_create(ui->home_page);
    lv_label_set_text(ui->home_page_lbl_3, _("sunny"));
    lv_label_set_long_mode(ui->home_page_lbl_3, LV_LABEL_LONG_WRAP);

    const lv_font_t *home_page_lbl_3_font = _font("sunny");
    if (home_page_lbl_3_font == NULL) {
        home_page_lbl_3_font = &lv_font_FangZhengKaiTiJianTi_1_48;
    }

    //Set style for home_page_lbl_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->home_page_lbl_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->home_page_lbl_3, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->home_page_lbl_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->home_page_lbl_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->home_page_lbl_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->home_page_lbl_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->home_page_lbl_3, home_page_lbl_3_font, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->home_page_lbl_3, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->home_page_lbl_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->home_page_lbl_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->home_page_lbl_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->home_page_lbl_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->home_page_lbl_3, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->home_page_lbl_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->home_page_lbl_3, 515, 93);
    lv_obj_set_size(ui->home_page_lbl_3, 131, 67);
    lv_obj_set_scrollbar_mode(ui->home_page_lbl_3, LV_SCROLLBAR_MODE_OFF);
    //Write codes home_page_lbl_1
    ui->home_page_lbl_1 = lv_label_create(ui->home_page);
    lv_label_set_text(ui->home_page_lbl_1, _("Sun"));
    lv_label_set_long_mode(ui->home_page_lbl_1, LV_LABEL_LONG_WRAP);

    const lv_font_t *home_page_lbl_1_font = _font("Sun");
    if (home_page_lbl_1_font == NULL) {
        home_page_lbl_1_font = &lv_font_FangZhengKaiTiJianTi_1_48;
    }

    //Set style for home_page_lbl_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->home_page_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->home_page_lbl_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->home_page_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->home_page_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->home_page_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->home_page_lbl_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->home_page_lbl_1, home_page_lbl_1_font, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->home_page_lbl_1, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->home_page_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->home_page_lbl_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->home_page_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->home_page_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->home_page_lbl_1, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->home_page_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->home_page_lbl_1, 167, 93);
    lv_obj_set_size(ui->home_page_lbl_1, 197, 67);
    lv_obj_set_scrollbar_mode(ui->home_page_lbl_1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_update_layout(ui->home_page);
    ui->home_page_del = false;

    //Init events for screen
    events_init_home_page(ui);
    return ui->home_page;
}
void unload_scr_home_page(lv_ui *ui)
{
    ui->home_page_del = true;
}

#endif
