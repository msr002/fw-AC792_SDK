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


lv_obj_t *setup_scr_video_dir(lv_ui *ui)
{
    //Write codes video_dir
    ui->video_dir = lv_obj_create(NULL);
    lv_group_t *def_group = lv_group_get_default();

    //Set style for video_dir. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui->video_dir, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_dir, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->video_dir, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(ui->video_dir, LV_SCROLLBAR_MODE_OFF);
    //Write codes video_dir_view_7
    ui->video_dir_view_7 = lv_obj_create(ui->video_dir);

    //Set style for video_dir_view_7. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->video_dir_view_7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_dir_view_7, lv_color_make(0x63, 0x61, 0x61), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_dir_view_7, 153, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->video_dir_view_7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->video_dir_view_7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->video_dir_view_7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->video_dir_view_7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->video_dir_view_7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->video_dir_view_7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->video_dir_view_7, 0, 0);
    lv_obj_set_size(ui->video_dir_view_7, 76, 480);
    lv_obj_set_scrollbar_mode(ui->video_dir_view_7, LV_SCROLLBAR_MODE_OFF);
    //Write codes video_dir_imgbtn_4
    ui->video_dir_imgbtn_4 = lv_imgbtn_create(ui->video_dir_view_7);

    //Set style for video_dir_imgbtn_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->video_dir_imgbtn_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->video_dir_imgbtn_4, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_dir_imgbtn_4, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_dir_imgbtn_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->video_dir_imgbtn_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->video_dir_imgbtn_4, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->video_dir_imgbtn_4, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->video_dir_imgbtn_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->video_dir_imgbtn_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->video_dir_imgbtn_4, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->video_dir_imgbtn_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->video_dir_imgbtn_4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for video_dir_imgbtn_4. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui->video_dir_imgbtn_4, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_clip_corner(ui->video_dir_imgbtn_4, true, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(ui->video_dir_imgbtn_4, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui->video_dir_imgbtn_4, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_shadow_width(ui->video_dir_imgbtn_4, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(ui->video_dir_imgbtn_4, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->video_dir_imgbtn_4, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->video_dir_imgbtn_4, 128, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(ui->video_dir_imgbtn_4, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_color(ui->video_dir_imgbtn_4, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_font(ui->video_dir_imgbtn_4, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_align(ui->video_dir_imgbtn_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor(ui->video_dir_imgbtn_4, lv_color_make(0xFF, 0xE7, 0x00), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor_opa(ui->video_dir_imgbtn_4, 128, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_opa(ui->video_dir_imgbtn_4, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Set style for video_dir_imgbtn_4. Part: LV_PART_MAIN, State: LV_STATE_PRESSED
    lv_obj_set_style_radius(ui->video_dir_imgbtn_4, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_clip_corner(ui->video_dir_imgbtn_4, true, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->video_dir_imgbtn_4, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(ui->video_dir_imgbtn_4, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->video_dir_imgbtn_4, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->video_dir_imgbtn_4, lv_color_make(0xFF, 0x33, 0xFF), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->video_dir_imgbtn_4, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_recolor(ui->video_dir_imgbtn_4, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_recolor_opa(ui->video_dir_imgbtn_4, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->video_dir_imgbtn_4, 255, LV_PART_MAIN | LV_STATE_PRESSED);

    //Set style for video_dir_imgbtn_4. Part: LV_PART_MAIN, State: LV_STATE_CHECKED
    lv_obj_set_style_radius(ui->video_dir_imgbtn_4, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_clip_corner(ui->video_dir_imgbtn_4, true, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui->video_dir_imgbtn_4, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui->video_dir_imgbtn_4, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->video_dir_imgbtn_4, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->video_dir_imgbtn_4, lv_color_make(0xFF, 0x33, 0xFF), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->video_dir_imgbtn_4, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_recolor(ui->video_dir_imgbtn_4, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_recolor_opa(ui->video_dir_imgbtn_4, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->video_dir_imgbtn_4, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_pos(ui->video_dir_imgbtn_4, 17, 36);
    lv_obj_set_size(ui->video_dir_imgbtn_4, 48, 48);
    lv_obj_set_scrollbar_mode(ui->video_dir_imgbtn_4, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui->video_dir_imgbtn_4);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_imgbtn_set_src(ui->video_dir_imgbtn_4, LV_IMGBTN_STATE_RELEASED, NULL, "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\import\\image\\RETURN.png", NULL);
    lv_imgbtn_set_src(ui->video_dir_imgbtn_4, LV_IMGBTN_STATE_PRESSED, NULL, "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\import\\image\\return_on.png", NULL);
    lv_imgbtn_set_src(ui->video_dir_imgbtn_4, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\import\\image\\RETURN.png", NULL);
    lv_imgbtn_set_src(ui->video_dir_imgbtn_4, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\import\\image\\return_on.png", NULL);
#else
    lv_imgbtn_set_src(ui->video_dir_imgbtn_4, LV_IMGBTN_STATE_RELEASED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000058.rle", NULL);
    lv_imgbtn_set_src(ui->video_dir_imgbtn_4, LV_IMGBTN_STATE_PRESSED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000059.rle", NULL);
    lv_imgbtn_set_src(ui->video_dir_imgbtn_4, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000058.rle", NULL);
    lv_imgbtn_set_src(ui->video_dir_imgbtn_4, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000059.rle", NULL);
#endif
    lv_obj_add_flag(ui->video_dir_imgbtn_4, LV_OBJ_FLAG_CHECKABLE);
    ui->video_dir_imgbtn_4_label = lv_label_create(ui->video_dir_imgbtn_4);
    lv_label_set_text(ui->video_dir_imgbtn_4_label, "");
    lv_obj_set_style_pad_all(ui->video_dir_imgbtn_4, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->video_dir_imgbtn_4_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes video_dir_img_17
    ui->video_dir_img_17 = lv_img_create(ui->video_dir_view_7);

    //Set style for video_dir_img_17. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->video_dir_img_17, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->video_dir_img_17, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_dir_img_17, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_dir_img_17, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->video_dir_img_17, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->video_dir_img_17, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->video_dir_img_17, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->video_dir_img_17, 7, 190);
    lv_obj_set_size(ui->video_dir_img_17, 64, 64);
    lv_obj_set_scrollbar_mode(ui->video_dir_img_17, LV_SCROLLBAR_MODE_OFF);
    //Write codes video_dir_lbl_path
    ui->video_dir_lbl_path = lv_label_create(ui->video_dir);
    lv_label_set_text(ui->video_dir_lbl_path, "storage/sd0/C/DCIM/");
    lv_label_set_long_mode(ui->video_dir_lbl_path, LV_LABEL_LONG_WRAP);

    //Set style for video_dir_lbl_path. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->video_dir_lbl_path, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_dir_lbl_path, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_dir_lbl_path, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->video_dir_lbl_path, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->video_dir_lbl_path, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->video_dir_lbl_path, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->video_dir_lbl_path, &lv_font_montserratMedium_22, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->video_dir_lbl_path, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->video_dir_lbl_path, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->video_dir_lbl_path, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->video_dir_lbl_path, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->video_dir_lbl_path, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->video_dir_lbl_path, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->video_dir_lbl_path, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->video_dir_lbl_path, 60, 10);
    lv_obj_set_size(ui->video_dir_lbl_path, 666, 38);
    lv_obj_set_scrollbar_mode(ui->video_dir_lbl_path, LV_SCROLLBAR_MODE_OFF);
    //Write codes video_dir_view_8
    ui->video_dir_view_8 = lv_obj_create(ui->video_dir);

    //Set style for video_dir_view_8. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->video_dir_view_8, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_dir_view_8, lv_color_make(0x63, 0x61, 0x61), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_dir_view_8, 153, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->video_dir_view_8, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->video_dir_view_8, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->video_dir_view_8, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->video_dir_view_8, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->video_dir_view_8, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->video_dir_view_8, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->video_dir_view_8, 714, 0);
    lv_obj_set_size(ui->video_dir_view_8, 85, 480);
    lv_obj_set_scrollbar_mode(ui->video_dir_view_8, LV_SCROLLBAR_MODE_OFF);
    //Write codes video_dir_imgbtn_1
    ui->video_dir_imgbtn_1 = lv_imgbtn_create(ui->video_dir_view_8);

    //Set style for video_dir_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->video_dir_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->video_dir_imgbtn_1, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_dir_imgbtn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_dir_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->video_dir_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->video_dir_imgbtn_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->video_dir_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->video_dir_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->video_dir_imgbtn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->video_dir_imgbtn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->video_dir_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->video_dir_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for video_dir_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui->video_dir_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_clip_corner(ui->video_dir_imgbtn_1, true, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(ui->video_dir_imgbtn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui->video_dir_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_shadow_width(ui->video_dir_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(ui->video_dir_imgbtn_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->video_dir_imgbtn_1, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->video_dir_imgbtn_1, 128, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(ui->video_dir_imgbtn_1, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_color(ui->video_dir_imgbtn_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_font(ui->video_dir_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_align(ui->video_dir_imgbtn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor(ui->video_dir_imgbtn_1, lv_color_make(0xFF, 0xE7, 0x00), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor_opa(ui->video_dir_imgbtn_1, 128, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_opa(ui->video_dir_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Set style for video_dir_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_PRESSED
    lv_obj_set_style_radius(ui->video_dir_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_clip_corner(ui->video_dir_imgbtn_1, true, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->video_dir_imgbtn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(ui->video_dir_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->video_dir_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->video_dir_imgbtn_1, lv_color_make(0xFF, 0x33, 0xFF), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->video_dir_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_recolor(ui->video_dir_imgbtn_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_recolor_opa(ui->video_dir_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->video_dir_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_PRESSED);

    //Set style for video_dir_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_CHECKED
    lv_obj_set_style_radius(ui->video_dir_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_clip_corner(ui->video_dir_imgbtn_1, true, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui->video_dir_imgbtn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui->video_dir_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->video_dir_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->video_dir_imgbtn_1, lv_color_make(0xFF, 0x33, 0xFF), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->video_dir_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_recolor(ui->video_dir_imgbtn_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_recolor_opa(ui->video_dir_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->video_dir_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_pos(ui->video_dir_imgbtn_1, 19, 36);
    lv_obj_set_size(ui->video_dir_imgbtn_1, 48, 48);
    lv_obj_set_scrollbar_mode(ui->video_dir_imgbtn_1, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui->video_dir_imgbtn_1);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_imgbtn_set_src(ui->video_dir_imgbtn_1, LV_IMGBTN_STATE_RELEASED, NULL, "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\import\\image\\EDIT.png", NULL);
    lv_imgbtn_set_src(ui->video_dir_imgbtn_1, LV_IMGBTN_STATE_PRESSED, NULL, "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\import\\image\\editor_on.png", NULL);
    lv_imgbtn_set_src(ui->video_dir_imgbtn_1, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\import\\image\\EDIT.png", NULL);
    lv_imgbtn_set_src(ui->video_dir_imgbtn_1, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\import\\image\\editor_on.png", NULL);
#else
    lv_imgbtn_set_src(ui->video_dir_imgbtn_1, LV_IMGBTN_STATE_RELEASED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/5600005e.rle", NULL);
    lv_imgbtn_set_src(ui->video_dir_imgbtn_1, LV_IMGBTN_STATE_PRESSED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/5600005f.rle", NULL);
    lv_imgbtn_set_src(ui->video_dir_imgbtn_1, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/5600005e.rle", NULL);
    lv_imgbtn_set_src(ui->video_dir_imgbtn_1, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/5600005f.rle", NULL);
#endif
    lv_obj_add_flag(ui->video_dir_imgbtn_1, LV_OBJ_FLAG_CHECKABLE);
    ui->video_dir_imgbtn_1_label = lv_label_create(ui->video_dir_imgbtn_1);
    lv_label_set_text(ui->video_dir_imgbtn_1_label, "");
    lv_obj_set_style_pad_all(ui->video_dir_imgbtn_1, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->video_dir_imgbtn_1_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes video_dir_imgbtn_3
    ui->video_dir_imgbtn_3 = lv_imgbtn_create(ui->video_dir_view_8);

    //Set style for video_dir_imgbtn_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->video_dir_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->video_dir_imgbtn_3, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_dir_imgbtn_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_dir_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->video_dir_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->video_dir_imgbtn_3, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->video_dir_imgbtn_3, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->video_dir_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->video_dir_imgbtn_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->video_dir_imgbtn_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->video_dir_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->video_dir_imgbtn_3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for video_dir_imgbtn_3. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui->video_dir_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_clip_corner(ui->video_dir_imgbtn_3, true, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(ui->video_dir_imgbtn_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui->video_dir_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_shadow_width(ui->video_dir_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(ui->video_dir_imgbtn_3, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->video_dir_imgbtn_3, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->video_dir_imgbtn_3, 128, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(ui->video_dir_imgbtn_3, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_color(ui->video_dir_imgbtn_3, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_font(ui->video_dir_imgbtn_3, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_align(ui->video_dir_imgbtn_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor(ui->video_dir_imgbtn_3, lv_color_make(0xFF, 0xE7, 0x00), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor_opa(ui->video_dir_imgbtn_3, 128, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_opa(ui->video_dir_imgbtn_3, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Set style for video_dir_imgbtn_3. Part: LV_PART_MAIN, State: LV_STATE_PRESSED
    lv_obj_set_style_radius(ui->video_dir_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_clip_corner(ui->video_dir_imgbtn_3, true, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->video_dir_imgbtn_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(ui->video_dir_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->video_dir_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->video_dir_imgbtn_3, lv_color_make(0xFF, 0x33, 0xFF), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->video_dir_imgbtn_3, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_recolor(ui->video_dir_imgbtn_3, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_recolor_opa(ui->video_dir_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->video_dir_imgbtn_3, 255, LV_PART_MAIN | LV_STATE_PRESSED);

    //Set style for video_dir_imgbtn_3. Part: LV_PART_MAIN, State: LV_STATE_CHECKED
    lv_obj_set_style_radius(ui->video_dir_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_clip_corner(ui->video_dir_imgbtn_3, true, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui->video_dir_imgbtn_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui->video_dir_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->video_dir_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->video_dir_imgbtn_3, lv_color_make(0xFF, 0x33, 0xFF), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->video_dir_imgbtn_3, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_recolor(ui->video_dir_imgbtn_3, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_recolor_opa(ui->video_dir_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->video_dir_imgbtn_3, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_pos(ui->video_dir_imgbtn_3, 19, 202);
    lv_obj_set_size(ui->video_dir_imgbtn_3, 48, 48);
    lv_obj_set_scrollbar_mode(ui->video_dir_imgbtn_3, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui->video_dir_imgbtn_3);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_imgbtn_set_src(ui->video_dir_imgbtn_3, LV_IMGBTN_STATE_RELEASED, NULL, "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\import\\image\\LOCK.png", NULL);
    lv_imgbtn_set_src(ui->video_dir_imgbtn_3, LV_IMGBTN_STATE_PRESSED, NULL, "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\import\\image\\lock_on.png", NULL);
    lv_imgbtn_set_src(ui->video_dir_imgbtn_3, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\import\\image\\LOCK.png", NULL);
    lv_imgbtn_set_src(ui->video_dir_imgbtn_3, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\import\\image\\lock_on.png", NULL);
#else
    lv_imgbtn_set_src(ui->video_dir_imgbtn_3, LV_IMGBTN_STATE_RELEASED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000060.rle", NULL);
    lv_imgbtn_set_src(ui->video_dir_imgbtn_3, LV_IMGBTN_STATE_PRESSED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000061.rle", NULL);
    lv_imgbtn_set_src(ui->video_dir_imgbtn_3, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000060.rle", NULL);
    lv_imgbtn_set_src(ui->video_dir_imgbtn_3, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000061.rle", NULL);
#endif
    lv_obj_add_flag(ui->video_dir_imgbtn_3, LV_OBJ_FLAG_CHECKABLE);
    ui->video_dir_imgbtn_3_label = lv_label_create(ui->video_dir_imgbtn_3);
    lv_label_set_text(ui->video_dir_imgbtn_3_label, "");
    lv_obj_set_style_pad_all(ui->video_dir_imgbtn_3, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->video_dir_imgbtn_3_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes video_dir_imgbtn_5
    ui->video_dir_imgbtn_5 = lv_imgbtn_create(ui->video_dir_view_8);

    //Set style for video_dir_imgbtn_5. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->video_dir_imgbtn_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->video_dir_imgbtn_5, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_dir_imgbtn_5, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_dir_imgbtn_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->video_dir_imgbtn_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->video_dir_imgbtn_5, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->video_dir_imgbtn_5, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->video_dir_imgbtn_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->video_dir_imgbtn_5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->video_dir_imgbtn_5, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->video_dir_imgbtn_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->video_dir_imgbtn_5, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for video_dir_imgbtn_5. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui->video_dir_imgbtn_5, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_clip_corner(ui->video_dir_imgbtn_5, true, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(ui->video_dir_imgbtn_5, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui->video_dir_imgbtn_5, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_shadow_width(ui->video_dir_imgbtn_5, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(ui->video_dir_imgbtn_5, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->video_dir_imgbtn_5, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->video_dir_imgbtn_5, 128, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(ui->video_dir_imgbtn_5, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_color(ui->video_dir_imgbtn_5, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_font(ui->video_dir_imgbtn_5, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_align(ui->video_dir_imgbtn_5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor(ui->video_dir_imgbtn_5, lv_color_make(0xFF, 0xE7, 0x00), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor_opa(ui->video_dir_imgbtn_5, 128, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_opa(ui->video_dir_imgbtn_5, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Set style for video_dir_imgbtn_5. Part: LV_PART_MAIN, State: LV_STATE_PRESSED
    lv_obj_set_style_radius(ui->video_dir_imgbtn_5, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_clip_corner(ui->video_dir_imgbtn_5, true, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->video_dir_imgbtn_5, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(ui->video_dir_imgbtn_5, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->video_dir_imgbtn_5, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->video_dir_imgbtn_5, lv_color_make(0xFF, 0x33, 0xFF), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->video_dir_imgbtn_5, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_recolor(ui->video_dir_imgbtn_5, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_recolor_opa(ui->video_dir_imgbtn_5, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->video_dir_imgbtn_5, 255, LV_PART_MAIN | LV_STATE_PRESSED);

    //Set style for video_dir_imgbtn_5. Part: LV_PART_MAIN, State: LV_STATE_CHECKED
    lv_obj_set_style_radius(ui->video_dir_imgbtn_5, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_clip_corner(ui->video_dir_imgbtn_5, true, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui->video_dir_imgbtn_5, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui->video_dir_imgbtn_5, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->video_dir_imgbtn_5, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->video_dir_imgbtn_5, lv_color_make(0xFF, 0x33, 0xFF), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->video_dir_imgbtn_5, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_recolor(ui->video_dir_imgbtn_5, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_recolor_opa(ui->video_dir_imgbtn_5, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->video_dir_imgbtn_5, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_pos(ui->video_dir_imgbtn_5, 21, 364);
    lv_obj_set_size(ui->video_dir_imgbtn_5, 48, 56);
    lv_obj_set_scrollbar_mode(ui->video_dir_imgbtn_5, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui->video_dir_imgbtn_5);

    //Hidden for widget video_dir_imgbtn_5
    lv_obj_add_flag(ui->video_dir_imgbtn_5, LV_OBJ_FLAG_HIDDEN);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_imgbtn_set_src(ui->video_dir_imgbtn_5, LV_IMGBTN_STATE_RELEASED, NULL, "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\import\\image\\DELETE.png", NULL);
    lv_imgbtn_set_src(ui->video_dir_imgbtn_5, LV_IMGBTN_STATE_PRESSED, NULL, "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\import\\image\\delete_on.png", NULL);
    lv_imgbtn_set_src(ui->video_dir_imgbtn_5, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\import\\image\\DELETE.png", NULL);
    lv_imgbtn_set_src(ui->video_dir_imgbtn_5, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\import\\image\\delete_on.png", NULL);
#else
    lv_imgbtn_set_src(ui->video_dir_imgbtn_5, LV_IMGBTN_STATE_RELEASED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000064.rle", NULL);
    lv_imgbtn_set_src(ui->video_dir_imgbtn_5, LV_IMGBTN_STATE_PRESSED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000065.rle", NULL);
    lv_imgbtn_set_src(ui->video_dir_imgbtn_5, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000064.rle", NULL);
    lv_imgbtn_set_src(ui->video_dir_imgbtn_5, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000065.rle", NULL);
#endif
    lv_obj_add_flag(ui->video_dir_imgbtn_5, LV_OBJ_FLAG_CHECKABLE);
    ui->video_dir_imgbtn_5_label = lv_label_create(ui->video_dir_imgbtn_5);
    lv_label_set_text(ui->video_dir_imgbtn_5_label, "");
    lv_obj_set_style_pad_all(ui->video_dir_imgbtn_5, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->video_dir_imgbtn_5_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes video_dir_imgbtn_2
    ui->video_dir_imgbtn_2 = lv_imgbtn_create(ui->video_dir_view_8);

    //Set style for video_dir_imgbtn_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->video_dir_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->video_dir_imgbtn_2, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_dir_imgbtn_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_dir_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->video_dir_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->video_dir_imgbtn_2, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->video_dir_imgbtn_2, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->video_dir_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->video_dir_imgbtn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->video_dir_imgbtn_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->video_dir_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->video_dir_imgbtn_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for video_dir_imgbtn_2. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui->video_dir_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_clip_corner(ui->video_dir_imgbtn_2, true, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(ui->video_dir_imgbtn_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui->video_dir_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_shadow_width(ui->video_dir_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(ui->video_dir_imgbtn_2, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->video_dir_imgbtn_2, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->video_dir_imgbtn_2, 128, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(ui->video_dir_imgbtn_2, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_color(ui->video_dir_imgbtn_2, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_font(ui->video_dir_imgbtn_2, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_align(ui->video_dir_imgbtn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor(ui->video_dir_imgbtn_2, lv_color_make(0xFF, 0xE7, 0x00), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor_opa(ui->video_dir_imgbtn_2, 128, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_opa(ui->video_dir_imgbtn_2, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Set style for video_dir_imgbtn_2. Part: LV_PART_MAIN, State: LV_STATE_PRESSED
    lv_obj_set_style_radius(ui->video_dir_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_clip_corner(ui->video_dir_imgbtn_2, true, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->video_dir_imgbtn_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(ui->video_dir_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->video_dir_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->video_dir_imgbtn_2, lv_color_make(0xFF, 0x33, 0xFF), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->video_dir_imgbtn_2, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_recolor(ui->video_dir_imgbtn_2, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_recolor_opa(ui->video_dir_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->video_dir_imgbtn_2, 255, LV_PART_MAIN | LV_STATE_PRESSED);

    //Set style for video_dir_imgbtn_2. Part: LV_PART_MAIN, State: LV_STATE_CHECKED
    lv_obj_set_style_radius(ui->video_dir_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_clip_corner(ui->video_dir_imgbtn_2, true, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui->video_dir_imgbtn_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui->video_dir_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->video_dir_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->video_dir_imgbtn_2, lv_color_make(0xFF, 0x33, 0xFF), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->video_dir_imgbtn_2, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_recolor(ui->video_dir_imgbtn_2, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_recolor_opa(ui->video_dir_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->video_dir_imgbtn_2, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_pos(ui->video_dir_imgbtn_2, 21, 364);
    lv_obj_set_size(ui->video_dir_imgbtn_2, 48, 56);
    lv_obj_set_scrollbar_mode(ui->video_dir_imgbtn_2, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui->video_dir_imgbtn_2);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_imgbtn_set_src(ui->video_dir_imgbtn_2, LV_IMGBTN_STATE_RELEASED, NULL, "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\import\\image\\HOME.png", NULL);
    lv_imgbtn_set_src(ui->video_dir_imgbtn_2, LV_IMGBTN_STATE_PRESSED, NULL, "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\import\\image\\home_on.png", NULL);
    lv_imgbtn_set_src(ui->video_dir_imgbtn_2, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\import\\image\\HOME.png", NULL);
    lv_imgbtn_set_src(ui->video_dir_imgbtn_2, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\import\\image\\home_on.png", NULL);
#else
    lv_imgbtn_set_src(ui->video_dir_imgbtn_2, LV_IMGBTN_STATE_RELEASED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000062.rle", NULL);
    lv_imgbtn_set_src(ui->video_dir_imgbtn_2, LV_IMGBTN_STATE_PRESSED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000063.rle", NULL);
    lv_imgbtn_set_src(ui->video_dir_imgbtn_2, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000062.rle", NULL);
    lv_imgbtn_set_src(ui->video_dir_imgbtn_2, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000063.rle", NULL);
#endif
    lv_obj_add_flag(ui->video_dir_imgbtn_2, LV_OBJ_FLAG_CHECKABLE);
    ui->video_dir_imgbtn_2_label = lv_label_create(ui->video_dir_imgbtn_2);
    lv_label_set_text(ui->video_dir_imgbtn_2_label, "");
    lv_obj_set_style_pad_all(ui->video_dir_imgbtn_2, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->video_dir_imgbtn_2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_update_layout(ui->video_dir);
    ui->video_dir_del = false;

    //Init events for screen
    events_init_video_dir(ui);
    return ui->video_dir;
}
void unload_scr_video_dir(lv_ui *ui)
{
    ui->video_dir_del = true;
}

#endif
