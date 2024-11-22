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


lv_obj_t *setup_scr_video_photo(lv_ui *ui)
{
    //Write codes video_photo
    ui->video_photo = lv_obj_create(NULL);
    lv_group_t *def_group = lv_group_get_default();

    //Set style for video_photo. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui->video_photo, lv_color_make(0x55, 0xaa, 0xa5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_photo, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->video_photo, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(ui->video_photo, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(ui->video_photo, LV_OBJ_FLAG_SCROLLABLE);
    static bool timer_video_photo_digitclock_1_enabled = false;

    //Write codes video_photo_digitclock_1
    ui->video_photo_digitclock_1 = lv_label_create(ui->video_photo);
    lv_label_set_text_fmt(ui->video_photo_digitclock_1, "%04d-%02d-%02d %02d:%02d:%02d", 2022, 07, 28, 21 % 12, 25, 50);
    lv_obj_set_style_text_align(ui->video_photo_digitclock_1, LV_TEXT_ALIGN_CENTER, 0);

    //Set style for video_photo_digitclock_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->video_photo_digitclock_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_photo_digitclock_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_photo_digitclock_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->video_photo_digitclock_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->video_photo_digitclock_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->video_photo_digitclock_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->video_photo_digitclock_1, &lv_font_FangZhengKaiTiJianTi_1_28, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->video_photo_digitclock_1, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->video_photo_digitclock_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->video_photo_digitclock_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->video_photo_digitclock_1, 7, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->video_photo_digitclock_1, 60, 420);
    lv_obj_set_size(ui->video_photo_digitclock_1, 343, 42);
    //Write codes video_photo_imgbtn_2
    ui->video_photo_imgbtn_2 = lv_imgbtn_create(ui->video_photo);

    //Set style for video_photo_imgbtn_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->video_photo_imgbtn_2, 44, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->video_photo_imgbtn_2, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_photo_imgbtn_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_photo_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->video_photo_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->video_photo_imgbtn_2, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->video_photo_imgbtn_2, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->video_photo_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->video_photo_imgbtn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->video_photo_imgbtn_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->video_photo_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->video_photo_imgbtn_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for video_photo_imgbtn_2. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui->video_photo_imgbtn_2, 44, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_clip_corner(ui->video_photo_imgbtn_2, true, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(ui->video_photo_imgbtn_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui->video_photo_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_shadow_width(ui->video_photo_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(ui->video_photo_imgbtn_2, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->video_photo_imgbtn_2, 4, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->video_photo_imgbtn_2, 128, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(ui->video_photo_imgbtn_2, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_color(ui->video_photo_imgbtn_2, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_font(ui->video_photo_imgbtn_2, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_align(ui->video_photo_imgbtn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor(ui->video_photo_imgbtn_2, lv_color_make(0xFF, 0xE7, 0x00), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor_opa(ui->video_photo_imgbtn_2, 128, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_opa(ui->video_photo_imgbtn_2, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Set style for video_photo_imgbtn_2. Part: LV_PART_MAIN, State: LV_STATE_PRESSED
    lv_obj_set_style_radius(ui->video_photo_imgbtn_2, 44, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_clip_corner(ui->video_photo_imgbtn_2, true, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->video_photo_imgbtn_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(ui->video_photo_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->video_photo_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->video_photo_imgbtn_2, lv_color_make(0xFF, 0x33, 0xFF), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->video_photo_imgbtn_2, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_recolor(ui->video_photo_imgbtn_2, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_recolor_opa(ui->video_photo_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->video_photo_imgbtn_2, 255, LV_PART_MAIN | LV_STATE_PRESSED);

    //Set style for video_photo_imgbtn_2. Part: LV_PART_MAIN, State: LV_STATE_CHECKED
    lv_obj_set_style_radius(ui->video_photo_imgbtn_2, 44, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_clip_corner(ui->video_photo_imgbtn_2, true, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui->video_photo_imgbtn_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui->video_photo_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->video_photo_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->video_photo_imgbtn_2, lv_color_make(0xFF, 0x33, 0xFF), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->video_photo_imgbtn_2, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_recolor(ui->video_photo_imgbtn_2, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_recolor_opa(ui->video_photo_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->video_photo_imgbtn_2, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_pos(ui->video_photo_imgbtn_2, 604, 202);
    lv_obj_set_size(ui->video_photo_imgbtn_2, 89, 86);
    lv_obj_set_scrollbar_mode(ui->video_photo_imgbtn_2, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui->video_photo_imgbtn_2);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_imgbtn_set_src(ui->video_photo_imgbtn_2, LV_IMGBTN_STATE_RELEASED, NULL, "A:\\wl83\\wifi_video_master\\ui_prj\\dvr_800x480\\import\\image\\video_page\\photo_button.png", NULL);
    lv_imgbtn_set_src(ui->video_photo_imgbtn_2, LV_IMGBTN_STATE_PRESSED, NULL, "A:\\wl83\\wifi_video_master\\ui_prj\\dvr_800x480\\import\\image\\video_page\\photo_button_on.png", NULL);
    lv_imgbtn_set_src(ui->video_photo_imgbtn_2, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "A:\\wl83\\wifi_video_master\\ui_prj\\dvr_800x480\\import\\image\\video_page\\photo_button.png", NULL);
    lv_imgbtn_set_src(ui->video_photo_imgbtn_2, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "A:\\wl83\\wifi_video_master\\ui_prj\\dvr_800x480\\import\\image\\video_page\\photo_button_on.png", NULL);
#else
    lv_imgbtn_set_src(ui->video_photo_imgbtn_2, LV_IMGBTN_STATE_RELEASED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000040.rle", NULL);
    lv_imgbtn_set_src(ui->video_photo_imgbtn_2, LV_IMGBTN_STATE_PRESSED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000041.rle", NULL);
    lv_imgbtn_set_src(ui->video_photo_imgbtn_2, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000040.rle", NULL);
    lv_imgbtn_set_src(ui->video_photo_imgbtn_2, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000041.rle", NULL);
#endif
    lv_obj_add_flag(ui->video_photo_imgbtn_2, LV_OBJ_FLAG_CHECKABLE);
    ui->video_photo_imgbtn_2_label = lv_label_create(ui->video_photo_imgbtn_2);
    lv_label_set_text(ui->video_photo_imgbtn_2_label, "");
    lv_obj_set_style_pad_all(ui->video_photo_imgbtn_2, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->video_photo_imgbtn_2_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes video_photo_imgbtn_1
    ui->video_photo_imgbtn_1 = lv_imgbtn_create(ui->video_photo);

    //Set style for video_photo_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->video_photo_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->video_photo_imgbtn_1, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_photo_imgbtn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_photo_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->video_photo_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->video_photo_imgbtn_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->video_photo_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->video_photo_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->video_photo_imgbtn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->video_photo_imgbtn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->video_photo_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->video_photo_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for video_photo_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_PRESSED
    lv_obj_set_style_radius(ui->video_photo_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_clip_corner(ui->video_photo_imgbtn_1, true, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->video_photo_imgbtn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(ui->video_photo_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->video_photo_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->video_photo_imgbtn_1, lv_color_make(0xFF, 0x33, 0xFF), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->video_photo_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_recolor(ui->video_photo_imgbtn_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_recolor_opa(ui->video_photo_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->video_photo_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_PRESSED);

    //Set style for video_photo_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_CHECKED
    lv_obj_set_style_radius(ui->video_photo_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_clip_corner(ui->video_photo_imgbtn_1, true, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui->video_photo_imgbtn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui->video_photo_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->video_photo_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->video_photo_imgbtn_1, lv_color_make(0xFF, 0x33, 0xFF), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->video_photo_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_recolor(ui->video_photo_imgbtn_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_recolor_opa(ui->video_photo_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->video_photo_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_CHECKED);

    //Set style for video_photo_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui->video_photo_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_clip_corner(ui->video_photo_imgbtn_1, true, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(ui->video_photo_imgbtn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui->video_photo_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_shadow_width(ui->video_photo_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(ui->video_photo_imgbtn_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->video_photo_imgbtn_1, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->video_photo_imgbtn_1, 128, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(ui->video_photo_imgbtn_1, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_color(ui->video_photo_imgbtn_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_font(ui->video_photo_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_align(ui->video_photo_imgbtn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor(ui->video_photo_imgbtn_1, lv_color_make(0xFF, 0xE7, 0x00), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor_opa(ui->video_photo_imgbtn_1, 128, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_opa(ui->video_photo_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->video_photo_imgbtn_1, 615, 70);
    lv_obj_set_size(ui->video_photo_imgbtn_1, 64, 64);
    lv_obj_set_scrollbar_mode(ui->video_photo_imgbtn_1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->video_photo_imgbtn_1, LV_OBJ_FLAG_HIDDEN);
    lv_group_add_obj(def_group, ui->video_photo_imgbtn_1);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_imgbtn_set_src(ui->video_photo_imgbtn_1, LV_IMGBTN_STATE_RELEASED, NULL, "A:\\wl83\\wifi_video_master\\ui_prj\\dvr_800x480\\import\\image\\video_page\\switch.png", NULL);
    lv_imgbtn_set_src(ui->video_photo_imgbtn_1, LV_IMGBTN_STATE_PRESSED, NULL, "A:\\wl83\\wifi_video_master\\ui_prj\\dvr_800x480\\import\\image\\video_page\\switch_on.png", NULL);
    lv_imgbtn_set_src(ui->video_photo_imgbtn_1, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "A:\\wl83\\wifi_video_master\\ui_prj\\dvr_800x480\\import\\image\\video_page\\switch.png", NULL);
    lv_imgbtn_set_src(ui->video_photo_imgbtn_1, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "A:\\wl83\\wifi_video_master\\ui_prj\\dvr_800x480\\import\\image\\video_page\\switch_on.png", NULL);
#else
    lv_imgbtn_set_src(ui->video_photo_imgbtn_1, LV_IMGBTN_STATE_RELEASED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/5600001a.rle", NULL);
    lv_imgbtn_set_src(ui->video_photo_imgbtn_1, LV_IMGBTN_STATE_PRESSED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/5600001b.rle", NULL);
    lv_imgbtn_set_src(ui->video_photo_imgbtn_1, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/5600001a.rle", NULL);
    lv_imgbtn_set_src(ui->video_photo_imgbtn_1, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/5600001b.rle", NULL);
#endif
    lv_obj_add_flag(ui->video_photo_imgbtn_1, LV_OBJ_FLAG_CHECKABLE);
    ui->video_photo_imgbtn_1_label = lv_label_create(ui->video_photo_imgbtn_1);
    lv_label_set_text(ui->video_photo_imgbtn_1_label, "");
    lv_obj_set_style_pad_all(ui->video_photo_imgbtn_1, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->video_photo_imgbtn_1_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes video_photo_img_5
    ui->video_photo_img_5 = lv_img_create(ui->video_photo);

    //Set style for video_photo_img_5. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->video_photo_img_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->video_photo_img_5, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_photo_img_5, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_photo_img_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->video_photo_img_5, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->video_photo_img_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->video_photo_img_5, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->video_photo_img_5, 23, 15);
    lv_obj_set_size(ui->video_photo_img_5, 48, 48);
    lv_obj_set_scrollbar_mode(ui->video_photo_img_5, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->video_photo_img_5, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui->video_photo_img_5, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_img_set_src(ui->video_photo_img_5, "A:\\wl83\\wifi_video_master\\ui_prj\\dvr_800x480\\import\\image\\video_page\\timing_photo_2.png");
#else
    lv_img_set_src(ui->video_photo_img_5, "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000042.rle");
#endif
    lv_img_set_pivot(ui->video_photo_img_5, 0, 0);
    lv_img_set_angle(ui->video_photo_img_5, 0);
    lv_img_set_zoom(ui->video_photo_img_5, 256);
    //Write codes video_photo_img_7
    ui->video_photo_img_7 = lv_img_create(ui->video_photo);

    //Set style for video_photo_img_7. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->video_photo_img_7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->video_photo_img_7, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_photo_img_7, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_photo_img_7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->video_photo_img_7, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->video_photo_img_7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->video_photo_img_7, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->video_photo_img_7, 80, 15);
    lv_obj_set_size(ui->video_photo_img_7, 48, 48);
    lv_obj_set_scrollbar_mode(ui->video_photo_img_7, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->video_photo_img_7, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_img_set_src(ui->video_photo_img_7, "A:\\wl83\\wifi_video_master\\ui_prj\\dvr_800x480\\import\\image\\video_page\\continuous.png");
#else
    lv_img_set_src(ui->video_photo_img_7, "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000043.rle");
#endif
    lv_img_set_pivot(ui->video_photo_img_7, 0, 0);
    lv_img_set_angle(ui->video_photo_img_7, 0);
    lv_img_set_zoom(ui->video_photo_img_7, 256);
    //Write codes video_photo_img_8
    ui->video_photo_img_8 = lv_img_create(ui->video_photo);

    //Set style for video_photo_img_8. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->video_photo_img_8, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->video_photo_img_8, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_photo_img_8, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_photo_img_8, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->video_photo_img_8, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->video_photo_img_8, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->video_photo_img_8, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->video_photo_img_8, 134, 15);
    lv_obj_set_size(ui->video_photo_img_8, 48, 48);
    lv_obj_set_scrollbar_mode(ui->video_photo_img_8, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->video_photo_img_8, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_img_set_src(ui->video_photo_img_8, "A:\\wl83\\wifi_video_master\\ui_prj\\dvr_800x480\\import\\image\\video_page\\hand_shake.png");
#else
    lv_img_set_src(ui->video_photo_img_8, "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000044.rle");
#endif
    lv_img_set_pivot(ui->video_photo_img_8, 0, 0);
    lv_img_set_angle(ui->video_photo_img_8, 0);
    lv_img_set_zoom(ui->video_photo_img_8, 256);
    //Write codes video_photo_img_9
    ui->video_photo_img_9 = lv_img_create(ui->video_photo);

    //Set style for video_photo_img_9. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->video_photo_img_9, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->video_photo_img_9, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_photo_img_9, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_photo_img_9, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->video_photo_img_9, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->video_photo_img_9, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->video_photo_img_9, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->video_photo_img_9, 191, 15);
    lv_obj_set_size(ui->video_photo_img_9, 45, 45);
    lv_obj_set_scrollbar_mode(ui->video_photo_img_9, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->video_photo_img_9, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_img_set_src(ui->video_photo_img_9, "A:\\wl83\\wifi_video_master\\ui_prj\\dvr_800x480\\import\\image\\video_page\\SD.png");
#else
    lv_img_set_src(ui->video_photo_img_9, "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000011.rle");
#endif
    lv_img_set_pivot(ui->video_photo_img_9, 0, 0);
    lv_img_set_angle(ui->video_photo_img_9, 0);
    lv_img_set_zoom(ui->video_photo_img_9, 256);
    //Write codes video_photo_img_12
    ui->video_photo_img_12 = lv_img_create(ui->video_photo);

    //Set style for video_photo_img_12. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->video_photo_img_12, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->video_photo_img_12, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_photo_img_12, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_photo_img_12, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->video_photo_img_12, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->video_photo_img_12, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->video_photo_img_12, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->video_photo_img_12, 22, 420);
    lv_obj_set_size(ui->video_photo_img_12, 48, 48);
    lv_obj_set_scrollbar_mode(ui->video_photo_img_12, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->video_photo_img_12, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_img_set_src(ui->video_photo_img_12, "A:\\wl83\\wifi_video_master\\ui_prj\\dvr_800x480\\import\\image\\video_page\\battery\\full.png");
#else
    lv_img_set_src(ui->video_photo_img_12, "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000014.rle");
#endif
    lv_img_set_pivot(ui->video_photo_img_12, 0, 0);
    lv_img_set_angle(ui->video_photo_img_12, 0);
    lv_img_set_zoom(ui->video_photo_img_12, 256);
    //Write codes video_photo_lbl_2
    ui->video_photo_lbl_2 = lv_label_create(ui->video_photo);
    lv_label_set_text(ui->video_photo_lbl_2, "1M");
    lv_label_set_long_mode(ui->video_photo_lbl_2, LV_LABEL_LONG_WRAP);

    //Set style for video_photo_lbl_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->video_photo_lbl_2, 24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_photo_lbl_2, lv_color_make(0xEA, 0xEE, 0xF1), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_photo_lbl_2, 77, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->video_photo_lbl_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->video_photo_lbl_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->video_photo_lbl_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->video_photo_lbl_2, &lv_font_FangZhengKaiTiJianTi_1_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->video_photo_lbl_2, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->video_photo_lbl_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->video_photo_lbl_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->video_photo_lbl_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->video_photo_lbl_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->video_photo_lbl_2, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->video_photo_lbl_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->video_photo_lbl_2, 22, 136);
    lv_obj_set_size(ui->video_photo_lbl_2, 48, 48);
    lv_obj_set_scrollbar_mode(ui->video_photo_lbl_2, LV_SCROLLBAR_MODE_OFF);
    //Write codes video_photo_lbl_3
    ui->video_photo_lbl_3 = lv_label_create(ui->video_photo);
    lv_label_set_text(ui->video_photo_lbl_3, "ISO\n100");
    lv_label_set_long_mode(ui->video_photo_lbl_3, LV_LABEL_LONG_WRAP);

    //Set style for video_photo_lbl_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->video_photo_lbl_3, 24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_photo_lbl_3, lv_color_make(0xEA, 0xEE, 0xF1), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_photo_lbl_3, 77, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->video_photo_lbl_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->video_photo_lbl_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->video_photo_lbl_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->video_photo_lbl_3, &lv_font_FangZhengKaiTiJianTi_1_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->video_photo_lbl_3, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->video_photo_lbl_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->video_photo_lbl_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->video_photo_lbl_3, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->video_photo_lbl_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->video_photo_lbl_3, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->video_photo_lbl_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->video_photo_lbl_3, 22, 202);
    lv_obj_set_size(ui->video_photo_lbl_3, 48, 48);
    lv_obj_set_scrollbar_mode(ui->video_photo_lbl_3, LV_SCROLLBAR_MODE_OFF);
    //Write codes video_photo_lbl_4
    ui->video_photo_lbl_4 = lv_label_create(ui->video_photo);
    lv_label_set_text(ui->video_photo_lbl_4, "remain");
    lv_label_set_long_mode(ui->video_photo_lbl_4, LV_LABEL_LONG_WRAP);

    //Set style for video_photo_lbl_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->video_photo_lbl_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_photo_lbl_4, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_photo_lbl_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->video_photo_lbl_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->video_photo_lbl_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->video_photo_lbl_4, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->video_photo_lbl_4, &lv_font_FangZhengKaiTiJianTi_1_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->video_photo_lbl_4, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->video_photo_lbl_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->video_photo_lbl_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->video_photo_lbl_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->video_photo_lbl_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->video_photo_lbl_4, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->video_photo_lbl_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->video_photo_lbl_4, 269, 15);
    lv_obj_set_size(ui->video_photo_lbl_4, 269, 52);
    lv_obj_set_scrollbar_mode(ui->video_photo_lbl_4, LV_SCROLLBAR_MODE_OFF);
    //Write codes video_photo_view_1
    ui->video_photo_view_1 = lv_obj_create(ui->video_photo);

    //Set style for video_photo_view_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->video_photo_view_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_photo_view_1, lv_color_make(0x31, 0x2B, 0x2B), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_photo_view_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->video_photo_view_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->video_photo_view_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->video_photo_view_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->video_photo_view_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->video_photo_view_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->video_photo_view_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->video_photo_view_1, 725, 0);
    lv_obj_set_size(ui->video_photo_view_1, 80, 480);
    lv_obj_set_scrollbar_mode(ui->video_photo_view_1, LV_SCROLLBAR_MODE_OFF);
    //Write codes video_photo_img_video_set
    ui->video_photo_img_video_set = lv_img_create(ui->video_photo);

    //Set style for video_photo_img_video_set. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->video_photo_img_video_set, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->video_photo_img_video_set, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_photo_img_video_set, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_photo_img_video_set, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->video_photo_img_video_set, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->video_photo_img_video_set, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->video_photo_img_video_set, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for video_photo_img_video_set. Part: LV_PART_MAIN, State: LV_STATE_FOCUSED
    lv_obj_set_style_radius(ui->video_photo_img_video_set, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_clip_corner(ui->video_photo_img_video_set, true, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_bg_color(ui->video_photo_img_video_set, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_bg_opa(ui->video_photo_img_video_set, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_img_recolor(ui->video_photo_img_video_set, lv_color_make(0xFF, 0xEB, 0x3D), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_img_recolor_opa(ui->video_photo_img_video_set, 255, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_img_opa(ui->video_photo_img_video_set, 255, LV_PART_MAIN | LV_STATE_FOCUSED);

    //Set style for video_photo_img_video_set. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui->video_photo_img_video_set, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_clip_corner(ui->video_photo_img_video_set, true, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(ui->video_photo_img_video_set, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui->video_photo_img_video_set, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(ui->video_photo_img_video_set, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->video_photo_img_video_set, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->video_photo_img_video_set, 128, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(ui->video_photo_img_video_set, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor(ui->video_photo_img_video_set, lv_color_make(0xFF, 0xE7, 0x00), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor_opa(ui->video_photo_img_video_set, 128, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_opa(ui->video_photo_img_video_set, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->video_photo_img_video_set, 742, 124);
    lv_obj_set_size(ui->video_photo_img_video_set, 48, 48);
    lv_obj_set_scrollbar_mode(ui->video_photo_img_video_set, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui->video_photo_img_video_set);
    lv_obj_add_flag(ui->video_photo_img_video_set, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_img_set_src(ui->video_photo_img_video_set, "A:\\wl83\\wifi_video_master\\ui_prj\\dvr_800x480\\import\\image\\video_page\\left_tools\\setting.png");
#else
    lv_img_set_src(ui->video_photo_img_video_set, "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000015.rle");
#endif
    lv_img_set_pivot(ui->video_photo_img_video_set, 0, 0);
    lv_img_set_angle(ui->video_photo_img_video_set, 0);
    lv_img_set_zoom(ui->video_photo_img_video_set, 256);
    //Write codes video_photo_img_15
    ui->video_photo_img_15 = lv_img_create(ui->video_photo);

    //Set style for video_photo_img_15. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->video_photo_img_15, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->video_photo_img_15, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_photo_img_15, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_photo_img_15, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->video_photo_img_15, lv_color_make(0xFF, 0xEB, 0x3D), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->video_photo_img_15, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->video_photo_img_15, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for video_photo_img_15. Part: LV_PART_MAIN, State: LV_STATE_FOCUSED
    lv_obj_set_style_radius(ui->video_photo_img_15, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_clip_corner(ui->video_photo_img_15, true, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_bg_color(ui->video_photo_img_15, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_bg_opa(ui->video_photo_img_15, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_img_recolor(ui->video_photo_img_15, lv_color_make(0xFF, 0xEB, 0x3D), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_img_recolor_opa(ui->video_photo_img_15, 255, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_img_opa(ui->video_photo_img_15, 255, LV_PART_MAIN | LV_STATE_FOCUSED);

    //Set style for video_photo_img_15. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui->video_photo_img_15, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_clip_corner(ui->video_photo_img_15, true, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(ui->video_photo_img_15, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui->video_photo_img_15, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(ui->video_photo_img_15, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->video_photo_img_15, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->video_photo_img_15, 128, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(ui->video_photo_img_15, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor(ui->video_photo_img_15, lv_color_make(0xFF, 0xE7, 0x00), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor_opa(ui->video_photo_img_15, 128, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_opa(ui->video_photo_img_15, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->video_photo_img_15, 742, 232);
    lv_obj_set_size(ui->video_photo_img_15, 48, 48);
    lv_obj_set_scrollbar_mode(ui->video_photo_img_15, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui->video_photo_img_15);
    lv_obj_add_flag(ui->video_photo_img_15, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_img_set_src(ui->video_photo_img_15, "A:\\wl83\\wifi_video_master\\ui_prj\\dvr_800x480\\import\\image\\video_page\\left_tools\\video.png");
#else
    lv_img_set_src(ui->video_photo_img_15, "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000045.rle");
#endif
    lv_img_set_pivot(ui->video_photo_img_15, 0, 0);
    lv_img_set_angle(ui->video_photo_img_15, 0);
    lv_img_set_zoom(ui->video_photo_img_15, 256);
    //Write codes video_photo_img_home
    ui->video_photo_img_home = lv_img_create(ui->video_photo);

    //Set style for video_photo_img_home. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->video_photo_img_home, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->video_photo_img_home, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_photo_img_home, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_photo_img_home, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->video_photo_img_home, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->video_photo_img_home, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->video_photo_img_home, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for video_photo_img_home. Part: LV_PART_MAIN, State: LV_STATE_FOCUSED
    lv_obj_set_style_radius(ui->video_photo_img_home, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_clip_corner(ui->video_photo_img_home, true, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_bg_color(ui->video_photo_img_home, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_bg_opa(ui->video_photo_img_home, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_img_recolor(ui->video_photo_img_home, lv_color_make(0xFF, 0xEB, 0x3D), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_img_recolor_opa(ui->video_photo_img_home, 255, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_img_opa(ui->video_photo_img_home, 255, LV_PART_MAIN | LV_STATE_FOCUSED);

    //Set style for video_photo_img_home. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui->video_photo_img_home, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_clip_corner(ui->video_photo_img_home, true, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(ui->video_photo_img_home, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui->video_photo_img_home, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(ui->video_photo_img_home, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->video_photo_img_home, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->video_photo_img_home, 128, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(ui->video_photo_img_home, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor(ui->video_photo_img_home, lv_color_make(0xFF, 0xE7, 0x00), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor_opa(ui->video_photo_img_home, 128, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_opa(ui->video_photo_img_home, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->video_photo_img_home, 742, 339);
    lv_obj_set_size(ui->video_photo_img_home, 48, 48);
    lv_obj_set_scrollbar_mode(ui->video_photo_img_home, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui->video_photo_img_home);
    lv_obj_add_flag(ui->video_photo_img_home, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_img_set_src(ui->video_photo_img_home, "A:\\wl83\\wifi_video_master\\ui_prj\\dvr_800x480\\import\\image\\video_page\\left_tools\\home.png");
#else
    lv_img_set_src(ui->video_photo_img_home, "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000017.rle");
#endif
    lv_img_set_pivot(ui->video_photo_img_home, 0, 0);
    lv_img_set_angle(ui->video_photo_img_home, 0);
    lv_img_set_zoom(ui->video_photo_img_home, 256);
    //Write codes video_photo_view_video_set
    ui->video_photo_view_video_set = lv_obj_create(ui->video_photo);

    //Set style for video_photo_view_video_set. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->video_photo_view_video_set, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_photo_view_video_set, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_photo_view_video_set, 179, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->video_photo_view_video_set, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->video_photo_view_video_set, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->video_photo_view_video_set, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->video_photo_view_video_set, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->video_photo_view_video_set, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->video_photo_view_video_set, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->video_photo_view_video_set, 295, 0);
    lv_obj_set_size(ui->video_photo_view_video_set, 430, 480);
    lv_obj_set_scrollbar_mode(ui->video_photo_view_video_set, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->video_photo_view_video_set, LV_OBJ_FLAG_HIDDEN);
    //Write codes video_photo_img_resolution
    ui->video_photo_img_resolution = lv_img_create(ui->video_photo_view_video_set);

    //Set style for video_photo_img_resolution. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->video_photo_img_resolution, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->video_photo_img_resolution, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_photo_img_resolution, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_photo_img_resolution, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->video_photo_img_resolution, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->video_photo_img_resolution, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->video_photo_img_resolution, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for video_photo_img_resolution. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui->video_photo_img_resolution, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_clip_corner(ui->video_photo_img_resolution, true, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(ui->video_photo_img_resolution, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui->video_photo_img_resolution, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(ui->video_photo_img_resolution, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->video_photo_img_resolution, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->video_photo_img_resolution, 128, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(ui->video_photo_img_resolution, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor(ui->video_photo_img_resolution, lv_color_make(0xFF, 0xE7, 0x00), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor_opa(ui->video_photo_img_resolution, 128, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_opa(ui->video_photo_img_resolution, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->video_photo_img_resolution, 31, 36);
    lv_obj_set_size(ui->video_photo_img_resolution, 80, 80);
    lv_obj_set_scrollbar_mode(ui->video_photo_img_resolution, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->video_photo_img_resolution, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_group_add_obj(def_group, ui->video_photo_img_resolution);
    lv_obj_add_flag(ui->video_photo_img_resolution, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_img_set_src(ui->video_photo_img_resolution, "A:\\wl83\\wifi_video_master\\ui_prj\\dvr_800x480\\import\\image\\video_page\\menu_icon\\resolution_ratio.png");
#else
    lv_img_set_src(ui->video_photo_img_resolution, "mnt/sdfile/EXT_RESERVED/uipackres/ui/5600001c.rle");
#endif
    lv_img_set_pivot(ui->video_photo_img_resolution, 0, 0);
    lv_img_set_angle(ui->video_photo_img_resolution, 0);
    lv_img_set_zoom(ui->video_photo_img_resolution, 256);
    //Write codes video_photo_img_19
    ui->video_photo_img_19 = lv_img_create(ui->video_photo_view_video_set);

    //Set style for video_photo_img_19. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->video_photo_img_19, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->video_photo_img_19, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_photo_img_19, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_photo_img_19, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->video_photo_img_19, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->video_photo_img_19, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->video_photo_img_19, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for video_photo_img_19. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui->video_photo_img_19, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_clip_corner(ui->video_photo_img_19, true, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(ui->video_photo_img_19, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui->video_photo_img_19, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(ui->video_photo_img_19, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->video_photo_img_19, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->video_photo_img_19, 128, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(ui->video_photo_img_19, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor(ui->video_photo_img_19, lv_color_make(0xFF, 0xE7, 0x00), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor_opa(ui->video_photo_img_19, 128, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_opa(ui->video_photo_img_19, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->video_photo_img_19, 133, 36);
    lv_obj_set_size(ui->video_photo_img_19, 80, 80);
    lv_obj_set_scrollbar_mode(ui->video_photo_img_19, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->video_photo_img_19, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_group_add_obj(def_group, ui->video_photo_img_19);
    lv_obj_add_flag(ui->video_photo_img_19, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_img_set_src(ui->video_photo_img_19, "A:\\wl83\\wifi_video_master\\ui_prj\\dvr_800x480\\import\\image\\video_page\\menu_icon\\timing_photo.png");
#else
    lv_img_set_src(ui->video_photo_img_19, "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000046.rle");
#endif
    lv_img_set_pivot(ui->video_photo_img_19, 0, 0);
    lv_img_set_angle(ui->video_photo_img_19, 0);
    lv_img_set_zoom(ui->video_photo_img_19, 256);
    //Write codes video_photo_img_20
    ui->video_photo_img_20 = lv_img_create(ui->video_photo_view_video_set);

    //Set style for video_photo_img_20. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->video_photo_img_20, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->video_photo_img_20, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_photo_img_20, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_photo_img_20, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->video_photo_img_20, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->video_photo_img_20, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->video_photo_img_20, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for video_photo_img_20. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui->video_photo_img_20, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_clip_corner(ui->video_photo_img_20, true, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(ui->video_photo_img_20, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui->video_photo_img_20, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(ui->video_photo_img_20, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->video_photo_img_20, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->video_photo_img_20, 128, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(ui->video_photo_img_20, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor(ui->video_photo_img_20, lv_color_make(0xFF, 0xE7, 0x00), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor_opa(ui->video_photo_img_20, 128, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_opa(ui->video_photo_img_20, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->video_photo_img_20, 235, 36);
    lv_obj_set_size(ui->video_photo_img_20, 80, 80);
    lv_obj_set_scrollbar_mode(ui->video_photo_img_20, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->video_photo_img_20, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_group_add_obj(def_group, ui->video_photo_img_20);
    lv_obj_add_flag(ui->video_photo_img_20, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_img_set_src(ui->video_photo_img_20, "A:\\wl83\\wifi_video_master\\ui_prj\\dvr_800x480\\import\\image\\video_page\\menu_icon\\continuous_photo.png");
#else
    lv_img_set_src(ui->video_photo_img_20, "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000047.rle");
#endif
    lv_img_set_pivot(ui->video_photo_img_20, 0, 0);
    lv_img_set_angle(ui->video_photo_img_20, 0);
    lv_img_set_zoom(ui->video_photo_img_20, 256);
    //Write codes video_photo_img_21
    ui->video_photo_img_21 = lv_img_create(ui->video_photo_view_video_set);

    //Set style for video_photo_img_21. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->video_photo_img_21, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->video_photo_img_21, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_photo_img_21, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_photo_img_21, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->video_photo_img_21, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->video_photo_img_21, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->video_photo_img_21, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for video_photo_img_21. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui->video_photo_img_21, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_clip_corner(ui->video_photo_img_21, true, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(ui->video_photo_img_21, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui->video_photo_img_21, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(ui->video_photo_img_21, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->video_photo_img_21, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->video_photo_img_21, 128, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(ui->video_photo_img_21, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor(ui->video_photo_img_21, lv_color_make(0xFF, 0xE7, 0x00), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor_opa(ui->video_photo_img_21, 128, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_opa(ui->video_photo_img_21, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->video_photo_img_21, 338, 36);
    lv_obj_set_size(ui->video_photo_img_21, 80, 80);
    lv_obj_set_scrollbar_mode(ui->video_photo_img_21, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->video_photo_img_21, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_group_add_obj(def_group, ui->video_photo_img_21);
    lv_obj_add_flag(ui->video_photo_img_21, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_img_set_src(ui->video_photo_img_21, "A:\\wl83\\wifi_video_master\\ui_prj\\dvr_800x480\\import\\image\\video_page\\menu_icon\\photo_quality.png");
#else
    lv_img_set_src(ui->video_photo_img_21, "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000048.rle");
#endif
    lv_img_set_pivot(ui->video_photo_img_21, 0, 0);
    lv_img_set_angle(ui->video_photo_img_21, 0);
    lv_img_set_zoom(ui->video_photo_img_21, 256);
    //Write codes video_photo_lbl_5
    ui->video_photo_lbl_5 = lv_label_create(ui->video_photo_view_video_set);
    lv_label_set_text(ui->video_photo_lbl_5, _("resolution"));
    lv_label_set_long_mode(ui->video_photo_lbl_5, LV_LABEL_LONG_WRAP);

    const lv_font_t *video_photo_lbl_5_font = _font("resolution");
    if (video_photo_lbl_5_font == NULL) {
        video_photo_lbl_5_font = &lv_font_FangZhengKaiTiJianTi_1_16;
    }

    //Set style for video_photo_lbl_5. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->video_photo_lbl_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_photo_lbl_5, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_photo_lbl_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->video_photo_lbl_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->video_photo_lbl_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->video_photo_lbl_5, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->video_photo_lbl_5, video_photo_lbl_5_font, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->video_photo_lbl_5, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->video_photo_lbl_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->video_photo_lbl_5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->video_photo_lbl_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->video_photo_lbl_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->video_photo_lbl_5, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->video_photo_lbl_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->video_photo_lbl_5, 31, 123);
    lv_obj_set_size(ui->video_photo_lbl_5, 72, 53);
    lv_obj_set_scrollbar_mode(ui->video_photo_lbl_5, LV_SCROLLBAR_MODE_OFF);
    //Write codes video_photo_lbl_6
    ui->video_photo_lbl_6 = lv_label_create(ui->video_photo_view_video_set);
    lv_label_set_text(ui->video_photo_lbl_6, _("shoot"));
    lv_label_set_long_mode(ui->video_photo_lbl_6, LV_LABEL_LONG_WRAP);

    const lv_font_t *video_photo_lbl_6_font = _font("shoot");
    if (video_photo_lbl_6_font == NULL) {
        video_photo_lbl_6_font = &lv_font_FangZhengKaiTiJianTi_1_16;
    }

    //Set style for video_photo_lbl_6. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->video_photo_lbl_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_photo_lbl_6, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_photo_lbl_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->video_photo_lbl_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->video_photo_lbl_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->video_photo_lbl_6, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->video_photo_lbl_6, video_photo_lbl_6_font, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->video_photo_lbl_6, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->video_photo_lbl_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->video_photo_lbl_6, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->video_photo_lbl_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->video_photo_lbl_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->video_photo_lbl_6, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->video_photo_lbl_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->video_photo_lbl_6, 133, 123);
    lv_obj_set_size(ui->video_photo_lbl_6, 72, 53);
    lv_obj_set_scrollbar_mode(ui->video_photo_lbl_6, LV_SCROLLBAR_MODE_OFF);
    //Write codes video_photo_lbl_7
    ui->video_photo_lbl_7 = lv_label_create(ui->video_photo_view_video_set);
    lv_label_set_text(ui->video_photo_lbl_7, _("shots"));
    lv_label_set_long_mode(ui->video_photo_lbl_7, LV_LABEL_LONG_WRAP);

    const lv_font_t *video_photo_lbl_7_font = _font("shots");
    if (video_photo_lbl_7_font == NULL) {
        video_photo_lbl_7_font = &lv_font_FangZhengKaiTiJianTi_1_16;
    }

    //Set style for video_photo_lbl_7. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->video_photo_lbl_7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_photo_lbl_7, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_photo_lbl_7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->video_photo_lbl_7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->video_photo_lbl_7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->video_photo_lbl_7, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->video_photo_lbl_7, video_photo_lbl_7_font, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->video_photo_lbl_7, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->video_photo_lbl_7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->video_photo_lbl_7, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->video_photo_lbl_7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->video_photo_lbl_7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->video_photo_lbl_7, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->video_photo_lbl_7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->video_photo_lbl_7, 235, 123);
    lv_obj_set_size(ui->video_photo_lbl_7, 72, 53);
    lv_obj_set_scrollbar_mode(ui->video_photo_lbl_7, LV_SCROLLBAR_MODE_OFF);
    //Write codes video_photo_lbl_8
    ui->video_photo_lbl_8 = lv_label_create(ui->video_photo_view_video_set);
    lv_label_set_text(ui->video_photo_lbl_8, _("quality"));
    lv_label_set_long_mode(ui->video_photo_lbl_8, LV_LABEL_LONG_WRAP);

    const lv_font_t *video_photo_lbl_8_font = _font("quality");
    if (video_photo_lbl_8_font == NULL) {
        video_photo_lbl_8_font = &lv_font_FangZhengKaiTiJianTi_1_16;
    }

    //Set style for video_photo_lbl_8. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->video_photo_lbl_8, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_photo_lbl_8, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_photo_lbl_8, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->video_photo_lbl_8, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->video_photo_lbl_8, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->video_photo_lbl_8, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->video_photo_lbl_8, video_photo_lbl_8_font, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->video_photo_lbl_8, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->video_photo_lbl_8, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->video_photo_lbl_8, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->video_photo_lbl_8, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->video_photo_lbl_8, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->video_photo_lbl_8, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->video_photo_lbl_8, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->video_photo_lbl_8, 342, 123);
    lv_obj_set_size(ui->video_photo_lbl_8, 72, 53);
    lv_obj_set_scrollbar_mode(ui->video_photo_lbl_8, LV_SCROLLBAR_MODE_OFF);
    //Write codes video_photo_img_1
    ui->video_photo_img_1 = lv_img_create(ui->video_photo_view_video_set);

    //Set style for video_photo_img_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->video_photo_img_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->video_photo_img_1, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_photo_img_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_photo_img_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->video_photo_img_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->video_photo_img_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->video_photo_img_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for video_photo_img_1. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui->video_photo_img_1, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_clip_corner(ui->video_photo_img_1, true, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(ui->video_photo_img_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui->video_photo_img_1, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(ui->video_photo_img_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->video_photo_img_1, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->video_photo_img_1, 128, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(ui->video_photo_img_1, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor(ui->video_photo_img_1, lv_color_make(0xFF, 0xE7, 0x00), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor_opa(ui->video_photo_img_1, 128, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_opa(ui->video_photo_img_1, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->video_photo_img_1, 31, 183);
    lv_obj_set_size(ui->video_photo_img_1, 80, 80);
    lv_obj_set_scrollbar_mode(ui->video_photo_img_1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->video_photo_img_1, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_group_add_obj(def_group, ui->video_photo_img_1);
    lv_obj_add_flag(ui->video_photo_img_1, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_img_set_src(ui->video_photo_img_1, "A:\\wl83\\wifi_video_master\\ui_prj\\dvr_800x480\\import\\image\\video_page\\menu_icon\\acuity.png");
#else
    lv_img_set_src(ui->video_photo_img_1, "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000049.rle");
#endif
    lv_img_set_pivot(ui->video_photo_img_1, 0, 0);
    lv_img_set_angle(ui->video_photo_img_1, 0);
    lv_img_set_zoom(ui->video_photo_img_1, 256);
    //Write codes video_photo_img_10
    ui->video_photo_img_10 = lv_img_create(ui->video_photo_view_video_set);

    //Set style for video_photo_img_10. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->video_photo_img_10, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->video_photo_img_10, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_photo_img_10, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_photo_img_10, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->video_photo_img_10, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->video_photo_img_10, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->video_photo_img_10, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for video_photo_img_10. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui->video_photo_img_10, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_clip_corner(ui->video_photo_img_10, true, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(ui->video_photo_img_10, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui->video_photo_img_10, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(ui->video_photo_img_10, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->video_photo_img_10, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->video_photo_img_10, 128, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(ui->video_photo_img_10, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor(ui->video_photo_img_10, lv_color_make(0xFF, 0xE7, 0x00), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor_opa(ui->video_photo_img_10, 128, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_opa(ui->video_photo_img_10, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->video_photo_img_10, 133, 183);
    lv_obj_set_size(ui->video_photo_img_10, 80, 80);
    lv_obj_set_scrollbar_mode(ui->video_photo_img_10, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->video_photo_img_10, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_group_add_obj(def_group, ui->video_photo_img_10);
    lv_obj_add_flag(ui->video_photo_img_10, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_img_set_src(ui->video_photo_img_10, "A:\\wl83\\wifi_video_master\\ui_prj\\dvr_800x480\\import\\image\\video_page\\menu_icon\\AWB.png");
#else
    lv_img_set_src(ui->video_photo_img_10, "mnt/sdfile/EXT_RESERVED/uipackres/ui/5600004a.rle");
#endif
    lv_img_set_pivot(ui->video_photo_img_10, 0, 0);
    lv_img_set_angle(ui->video_photo_img_10, 0);
    lv_img_set_zoom(ui->video_photo_img_10, 256);
    //Write codes video_photo_img_17
    ui->video_photo_img_17 = lv_img_create(ui->video_photo_view_video_set);

    //Set style for video_photo_img_17. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->video_photo_img_17, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->video_photo_img_17, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_photo_img_17, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_photo_img_17, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->video_photo_img_17, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->video_photo_img_17, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->video_photo_img_17, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for video_photo_img_17. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui->video_photo_img_17, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_clip_corner(ui->video_photo_img_17, true, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(ui->video_photo_img_17, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui->video_photo_img_17, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(ui->video_photo_img_17, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->video_photo_img_17, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->video_photo_img_17, 128, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(ui->video_photo_img_17, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor(ui->video_photo_img_17, lv_color_make(0xFF, 0xE7, 0x00), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor_opa(ui->video_photo_img_17, 128, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_opa(ui->video_photo_img_17, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->video_photo_img_17, 235, 183);
    lv_obj_set_size(ui->video_photo_img_17, 80, 80);
    lv_obj_set_scrollbar_mode(ui->video_photo_img_17, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->video_photo_img_17, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_group_add_obj(def_group, ui->video_photo_img_17);
    lv_obj_add_flag(ui->video_photo_img_17, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_img_set_src(ui->video_photo_img_17, "A:\\wl83\\wifi_video_master\\ui_prj\\dvr_800x480\\import\\image\\video_page\\menu_icon\\color.png");
#else
    lv_img_set_src(ui->video_photo_img_17, "mnt/sdfile/EXT_RESERVED/uipackres/ui/5600004b.rle");
#endif
    lv_img_set_pivot(ui->video_photo_img_17, 0, 0);
    lv_img_set_angle(ui->video_photo_img_17, 0);
    lv_img_set_zoom(ui->video_photo_img_17, 256);
    //Write codes video_photo_img_18
    ui->video_photo_img_18 = lv_img_create(ui->video_photo_view_video_set);

    //Set style for video_photo_img_18. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->video_photo_img_18, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->video_photo_img_18, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_photo_img_18, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_photo_img_18, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->video_photo_img_18, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->video_photo_img_18, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->video_photo_img_18, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for video_photo_img_18. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui->video_photo_img_18, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_clip_corner(ui->video_photo_img_18, true, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(ui->video_photo_img_18, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui->video_photo_img_18, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(ui->video_photo_img_18, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->video_photo_img_18, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->video_photo_img_18, 128, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(ui->video_photo_img_18, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor(ui->video_photo_img_18, lv_color_make(0xFF, 0xE7, 0x00), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor_opa(ui->video_photo_img_18, 128, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_opa(ui->video_photo_img_18, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->video_photo_img_18, 338, 183);
    lv_obj_set_size(ui->video_photo_img_18, 80, 80);
    lv_obj_set_scrollbar_mode(ui->video_photo_img_18, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->video_photo_img_18, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_group_add_obj(def_group, ui->video_photo_img_18);
    lv_obj_add_flag(ui->video_photo_img_18, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_img_set_src(ui->video_photo_img_18, "A:\\wl83\\wifi_video_master\\ui_prj\\dvr_800x480\\import\\image\\video_page\\menu_icon\\ISO.png");
#else
    lv_img_set_src(ui->video_photo_img_18, "mnt/sdfile/EXT_RESERVED/uipackres/ui/5600004c.rle");
#endif
    lv_img_set_pivot(ui->video_photo_img_18, 0, 0);
    lv_img_set_angle(ui->video_photo_img_18, 0);
    lv_img_set_zoom(ui->video_photo_img_18, 256);
    //Write codes video_photo_lbl_13
    ui->video_photo_lbl_13 = lv_label_create(ui->video_photo_view_video_set);
    lv_label_set_text(ui->video_photo_lbl_13, _("sharpness"));
    lv_label_set_long_mode(ui->video_photo_lbl_13, LV_LABEL_LONG_WRAP);

    const lv_font_t *video_photo_lbl_13_font = _font("sharpness");
    if (video_photo_lbl_13_font == NULL) {
        video_photo_lbl_13_font = &lv_font_FangZhengKaiTiJianTi_1_16;
    }

    //Set style for video_photo_lbl_13. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->video_photo_lbl_13, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_photo_lbl_13, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_photo_lbl_13, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->video_photo_lbl_13, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->video_photo_lbl_13, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->video_photo_lbl_13, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->video_photo_lbl_13, video_photo_lbl_13_font, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->video_photo_lbl_13, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->video_photo_lbl_13, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->video_photo_lbl_13, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->video_photo_lbl_13, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->video_photo_lbl_13, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->video_photo_lbl_13, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->video_photo_lbl_13, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->video_photo_lbl_13, 22, 264);
    lv_obj_set_size(ui->video_photo_lbl_13, 90, 53);
    lv_obj_set_scrollbar_mode(ui->video_photo_lbl_13, LV_SCROLLBAR_MODE_OFF);
    //Write codes video_photo_lbl_14
    ui->video_photo_lbl_14 = lv_label_create(ui->video_photo_view_video_set);
    lv_label_set_text(ui->video_photo_lbl_14, _("exposure"));
    lv_label_set_long_mode(ui->video_photo_lbl_14, LV_LABEL_LONG_WRAP);

    const lv_font_t *video_photo_lbl_14_font = _font("exposure");
    if (video_photo_lbl_14_font == NULL) {
        video_photo_lbl_14_font = &lv_font_FangZhengKaiTiJianTi_1_16;
    }

    //Set style for video_photo_lbl_14. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->video_photo_lbl_14, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_photo_lbl_14, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_photo_lbl_14, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->video_photo_lbl_14, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->video_photo_lbl_14, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->video_photo_lbl_14, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->video_photo_lbl_14, video_photo_lbl_14_font, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->video_photo_lbl_14, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->video_photo_lbl_14, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->video_photo_lbl_14, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->video_photo_lbl_14, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->video_photo_lbl_14, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->video_photo_lbl_14, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->video_photo_lbl_14, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->video_photo_lbl_14, 31, 413);
    lv_obj_set_size(ui->video_photo_lbl_14, 72, 53);
    lv_obj_set_scrollbar_mode(ui->video_photo_lbl_14, LV_SCROLLBAR_MODE_OFF);
    //Write codes video_photo_img_3
    ui->video_photo_img_3 = lv_img_create(ui->video_photo_view_video_set);

    //Set style for video_photo_img_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->video_photo_img_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->video_photo_img_3, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_photo_img_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_photo_img_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->video_photo_img_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->video_photo_img_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->video_photo_img_3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for video_photo_img_3. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui->video_photo_img_3, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_clip_corner(ui->video_photo_img_3, true, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(ui->video_photo_img_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui->video_photo_img_3, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(ui->video_photo_img_3, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->video_photo_img_3, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->video_photo_img_3, 128, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(ui->video_photo_img_3, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor(ui->video_photo_img_3, lv_color_make(0xFF, 0xE7, 0x00), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor_opa(ui->video_photo_img_3, 128, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_opa(ui->video_photo_img_3, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->video_photo_img_3, 31, 330);
    lv_obj_set_size(ui->video_photo_img_3, 80, 80);
    lv_obj_set_scrollbar_mode(ui->video_photo_img_3, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->video_photo_img_3, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_group_add_obj(def_group, ui->video_photo_img_3);
    lv_obj_add_flag(ui->video_photo_img_3, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_img_set_src(ui->video_photo_img_3, "A:\\wl83\\wifi_video_master\\ui_prj\\dvr_800x480\\import\\image\\video_page\\menu_icon\\exposure.png");
#else
    lv_img_set_src(ui->video_photo_img_3, "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000021.rle");
#endif
    lv_img_set_pivot(ui->video_photo_img_3, 0, 0);
    lv_img_set_angle(ui->video_photo_img_3, 0);
    lv_img_set_zoom(ui->video_photo_img_3, 256);
    //Write codes video_photo_img_22
    ui->video_photo_img_22 = lv_img_create(ui->video_photo_view_video_set);

    //Set style for video_photo_img_22. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->video_photo_img_22, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->video_photo_img_22, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_photo_img_22, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_photo_img_22, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->video_photo_img_22, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->video_photo_img_22, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->video_photo_img_22, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for video_photo_img_22. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui->video_photo_img_22, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_clip_corner(ui->video_photo_img_22, true, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(ui->video_photo_img_22, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui->video_photo_img_22, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(ui->video_photo_img_22, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->video_photo_img_22, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->video_photo_img_22, 128, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(ui->video_photo_img_22, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor(ui->video_photo_img_22, lv_color_make(0xFF, 0xE7, 0x00), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor_opa(ui->video_photo_img_22, 128, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_opa(ui->video_photo_img_22, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->video_photo_img_22, 132, 330);
    lv_obj_set_size(ui->video_photo_img_22, 80, 80);
    lv_obj_set_scrollbar_mode(ui->video_photo_img_22, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->video_photo_img_22, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_group_add_obj(def_group, ui->video_photo_img_22);
    lv_obj_add_flag(ui->video_photo_img_22, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_img_set_src(ui->video_photo_img_22, "A:\\wl83\\wifi_video_master\\ui_prj\\dvr_800x480\\import\\image\\video_page\\menu_icon\\hand_shake.png");
#else
    lv_img_set_src(ui->video_photo_img_22, "mnt/sdfile/EXT_RESERVED/uipackres/ui/5600004d.rle");
#endif
    lv_img_set_pivot(ui->video_photo_img_22, 0, 0);
    lv_img_set_angle(ui->video_photo_img_22, 0);
    lv_img_set_zoom(ui->video_photo_img_22, 256);
    //Write codes video_photo_img_23
    ui->video_photo_img_23 = lv_img_create(ui->video_photo_view_video_set);

    //Set style for video_photo_img_23. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->video_photo_img_23, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->video_photo_img_23, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_photo_img_23, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_photo_img_23, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->video_photo_img_23, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->video_photo_img_23, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->video_photo_img_23, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for video_photo_img_23. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui->video_photo_img_23, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_clip_corner(ui->video_photo_img_23, true, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(ui->video_photo_img_23, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui->video_photo_img_23, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(ui->video_photo_img_23, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->video_photo_img_23, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->video_photo_img_23, 128, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(ui->video_photo_img_23, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor(ui->video_photo_img_23, lv_color_make(0xFF, 0xE7, 0x00), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor_opa(ui->video_photo_img_23, 128, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_opa(ui->video_photo_img_23, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->video_photo_img_23, 233, 330);
    lv_obj_set_size(ui->video_photo_img_23, 80, 80);
    lv_obj_set_scrollbar_mode(ui->video_photo_img_23, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->video_photo_img_23, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_group_add_obj(def_group, ui->video_photo_img_23);
    lv_obj_add_flag(ui->video_photo_img_23, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_img_set_src(ui->video_photo_img_23, "A:\\wl83\\wifi_video_master\\ui_prj\\dvr_800x480\\import\\image\\video_page\\menu_icon\\quick_scan.png");
#else
    lv_img_set_src(ui->video_photo_img_23, "mnt/sdfile/EXT_RESERVED/uipackres/ui/5600004e.rle");
#endif
    lv_img_set_pivot(ui->video_photo_img_23, 0, 0);
    lv_img_set_angle(ui->video_photo_img_23, 0);
    lv_img_set_zoom(ui->video_photo_img_23, 256);
    //Write codes video_photo_img_24
    ui->video_photo_img_24 = lv_img_create(ui->video_photo_view_video_set);

    //Set style for video_photo_img_24. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->video_photo_img_24, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->video_photo_img_24, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_photo_img_24, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_photo_img_24, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->video_photo_img_24, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->video_photo_img_24, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->video_photo_img_24, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for video_photo_img_24. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui->video_photo_img_24, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_clip_corner(ui->video_photo_img_24, true, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(ui->video_photo_img_24, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui->video_photo_img_24, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(ui->video_photo_img_24, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->video_photo_img_24, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->video_photo_img_24, 128, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(ui->video_photo_img_24, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor(ui->video_photo_img_24, lv_color_make(0xFF, 0xE7, 0x00), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor_opa(ui->video_photo_img_24, 128, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_opa(ui->video_photo_img_24, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->video_photo_img_24, 337, 330);
    lv_obj_set_size(ui->video_photo_img_24, 80, 80);
    lv_obj_set_scrollbar_mode(ui->video_photo_img_24, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->video_photo_img_24, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_group_add_obj(def_group, ui->video_photo_img_24);
    lv_obj_add_flag(ui->video_photo_img_24, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_img_set_src(ui->video_photo_img_24, "A:\\wl83\\wifi_video_master\\ui_prj\\dvr_800x480\\import\\image\\video_page\\menu_icon\\date.png");
#else
    lv_img_set_src(ui->video_photo_img_24, "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000023.rle");
#endif
    lv_img_set_pivot(ui->video_photo_img_24, 0, 0);
    lv_img_set_angle(ui->video_photo_img_24, 0);
    lv_img_set_zoom(ui->video_photo_img_24, 256);
    //Write codes video_photo_lbl_15
    ui->video_photo_lbl_15 = lv_label_create(ui->video_photo_view_video_set);
    lv_label_set_text(ui->video_photo_lbl_15, _("awb"));
    lv_label_set_long_mode(ui->video_photo_lbl_15, LV_LABEL_LONG_WRAP);

    const lv_font_t *video_photo_lbl_15_font = _font("awb");
    if (video_photo_lbl_15_font == NULL) {
        video_photo_lbl_15_font = &lv_font_FangZhengKaiTiJianTi_1_16;
    }

    //Set style for video_photo_lbl_15. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->video_photo_lbl_15, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_photo_lbl_15, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_photo_lbl_15, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->video_photo_lbl_15, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->video_photo_lbl_15, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->video_photo_lbl_15, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->video_photo_lbl_15, video_photo_lbl_15_font, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->video_photo_lbl_15, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->video_photo_lbl_15, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->video_photo_lbl_15, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->video_photo_lbl_15, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->video_photo_lbl_15, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->video_photo_lbl_15, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->video_photo_lbl_15, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->video_photo_lbl_15, 129, 264);
    lv_obj_set_size(ui->video_photo_lbl_15, 90, 53);
    lv_obj_set_scrollbar_mode(ui->video_photo_lbl_15, LV_SCROLLBAR_MODE_OFF);
    //Write codes video_photo_lbl_16
    ui->video_photo_lbl_16 = lv_label_create(ui->video_photo_view_video_set);
    lv_label_set_text(ui->video_photo_lbl_16, _("color"));
    lv_label_set_long_mode(ui->video_photo_lbl_16, LV_LABEL_LONG_WRAP);

    const lv_font_t *video_photo_lbl_16_font = _font("color");
    if (video_photo_lbl_16_font == NULL) {
        video_photo_lbl_16_font = &lv_font_FangZhengKaiTiJianTi_1_16;
    }

    //Set style for video_photo_lbl_16. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->video_photo_lbl_16, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_photo_lbl_16, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_photo_lbl_16, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->video_photo_lbl_16, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->video_photo_lbl_16, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->video_photo_lbl_16, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->video_photo_lbl_16, video_photo_lbl_16_font, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->video_photo_lbl_16, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->video_photo_lbl_16, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->video_photo_lbl_16, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->video_photo_lbl_16, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->video_photo_lbl_16, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->video_photo_lbl_16, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->video_photo_lbl_16, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->video_photo_lbl_16, 230, 264);
    lv_obj_set_size(ui->video_photo_lbl_16, 90, 53);
    lv_obj_set_scrollbar_mode(ui->video_photo_lbl_16, LV_SCROLLBAR_MODE_OFF);
    //Write codes video_photo_lbl_17
    ui->video_photo_lbl_17 = lv_label_create(ui->video_photo_view_video_set);
    lv_label_set_text(ui->video_photo_lbl_17, "ISO");
    lv_label_set_long_mode(ui->video_photo_lbl_17, LV_LABEL_LONG_WRAP);

    //Set style for video_photo_lbl_17. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->video_photo_lbl_17, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_photo_lbl_17, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_photo_lbl_17, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->video_photo_lbl_17, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->video_photo_lbl_17, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->video_photo_lbl_17, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->video_photo_lbl_17, &lv_font_FangZhengKaiTiJianTi_1_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->video_photo_lbl_17, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->video_photo_lbl_17, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->video_photo_lbl_17, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->video_photo_lbl_17, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->video_photo_lbl_17, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->video_photo_lbl_17, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->video_photo_lbl_17, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->video_photo_lbl_17, 333, 264);
    lv_obj_set_size(ui->video_photo_lbl_17, 90, 53);
    lv_obj_set_scrollbar_mode(ui->video_photo_lbl_17, LV_SCROLLBAR_MODE_OFF);
    //Write codes video_photo_lbl_18
    ui->video_photo_lbl_18 = lv_label_create(ui->video_photo_view_video_set);
    lv_label_set_text(ui->video_photo_lbl_18, _("handshake"));
    lv_label_set_long_mode(ui->video_photo_lbl_18, LV_LABEL_LONG_WRAP);

    const lv_font_t *video_photo_lbl_18_font = _font("handshake");
    if (video_photo_lbl_18_font == NULL) {
        video_photo_lbl_18_font = &lv_font_FangZhengKaiTiJianTi_1_16;
    }

    //Set style for video_photo_lbl_18. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->video_photo_lbl_18, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_photo_lbl_18, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_photo_lbl_18, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->video_photo_lbl_18, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->video_photo_lbl_18, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->video_photo_lbl_18, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->video_photo_lbl_18, video_photo_lbl_18_font, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->video_photo_lbl_18, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->video_photo_lbl_18, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->video_photo_lbl_18, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->video_photo_lbl_18, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->video_photo_lbl_18, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->video_photo_lbl_18, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->video_photo_lbl_18, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->video_photo_lbl_18, 128, 413);
    lv_obj_set_size(ui->video_photo_lbl_18, 90, 53);
    lv_obj_set_scrollbar_mode(ui->video_photo_lbl_18, LV_SCROLLBAR_MODE_OFF);
    //Write codes video_photo_lbl_19
    ui->video_photo_lbl_19 = lv_label_create(ui->video_photo_view_video_set);
    lv_label_set_text(ui->video_photo_lbl_19, _("preview"));
    lv_label_set_long_mode(ui->video_photo_lbl_19, LV_LABEL_LONG_WRAP);

    const lv_font_t *video_photo_lbl_19_font = _font("preview");
    if (video_photo_lbl_19_font == NULL) {
        video_photo_lbl_19_font = &lv_font_FangZhengKaiTiJianTi_1_16;
    }

    //Set style for video_photo_lbl_19. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->video_photo_lbl_19, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_photo_lbl_19, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_photo_lbl_19, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->video_photo_lbl_19, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->video_photo_lbl_19, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->video_photo_lbl_19, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->video_photo_lbl_19, video_photo_lbl_19_font, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->video_photo_lbl_19, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->video_photo_lbl_19, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->video_photo_lbl_19, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->video_photo_lbl_19, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->video_photo_lbl_19, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->video_photo_lbl_19, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->video_photo_lbl_19, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->video_photo_lbl_19, 225, 413);
    lv_obj_set_size(ui->video_photo_lbl_19, 90, 53);
    lv_obj_set_scrollbar_mode(ui->video_photo_lbl_19, LV_SCROLLBAR_MODE_OFF);
    //Write codes video_photo_lbl_20
    ui->video_photo_lbl_20 = lv_label_create(ui->video_photo_view_video_set);
    lv_label_set_text(ui->video_photo_lbl_20, _("date"));
    lv_label_set_long_mode(ui->video_photo_lbl_20, LV_LABEL_LONG_WRAP);

    const lv_font_t *video_photo_lbl_20_font = _font("date");
    if (video_photo_lbl_20_font == NULL) {
        video_photo_lbl_20_font = &lv_font_FangZhengKaiTiJianTi_1_16;
    }

    //Set style for video_photo_lbl_20. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->video_photo_lbl_20, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_photo_lbl_20, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_photo_lbl_20, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->video_photo_lbl_20, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->video_photo_lbl_20, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->video_photo_lbl_20, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->video_photo_lbl_20, video_photo_lbl_20_font, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->video_photo_lbl_20, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->video_photo_lbl_20, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->video_photo_lbl_20, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->video_photo_lbl_20, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->video_photo_lbl_20, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->video_photo_lbl_20, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->video_photo_lbl_20, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->video_photo_lbl_20, 332, 413);
    lv_obj_set_size(ui->video_photo_lbl_20, 90, 53);
    lv_obj_set_scrollbar_mode(ui->video_photo_lbl_20, LV_SCROLLBAR_MODE_OFF);
    //Write codes video_photo_img_25
    ui->video_photo_img_25 = lv_img_create(ui->video_photo);

    //Set style for video_photo_img_25. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->video_photo_img_25, 24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->video_photo_img_25, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_photo_img_25, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_photo_img_25, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->video_photo_img_25, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->video_photo_img_25, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->video_photo_img_25, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->video_photo_img_25, 22, 70);
    lv_obj_set_size(ui->video_photo_img_25, 48, 48);
    lv_obj_set_scrollbar_mode(ui->video_photo_img_25, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->video_photo_img_25, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_img_set_src(ui->video_photo_img_25, "A:\\wl83\\wifi_video_master\\ui_prj\\dvr_800x480\\import\\image\\video_page\\high.png");
#else
    lv_img_set_src(ui->video_photo_img_25, "mnt/sdfile/EXT_RESERVED/uipackres/ui/5600004f.rle");
#endif
    lv_img_set_pivot(ui->video_photo_img_25, 0, 0);
    lv_img_set_angle(ui->video_photo_img_25, 0);
    lv_img_set_zoom(ui->video_photo_img_25, 256);
    //Write codes video_photo_img_4
    ui->video_photo_img_4 = lv_img_create(ui->video_photo);

    //Set style for video_photo_img_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->video_photo_img_4, 24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->video_photo_img_4, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_photo_img_4, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_photo_img_4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->video_photo_img_4, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->video_photo_img_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->video_photo_img_4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->video_photo_img_4, 23, 263);
    lv_obj_set_size(ui->video_photo_img_4, 48, 48);
    lv_obj_set_scrollbar_mode(ui->video_photo_img_4, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->video_photo_img_4, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_img_set_src(ui->video_photo_img_4, "A:\\wl83\\wifi_video_master\\ui_prj\\dvr_800x480\\import\\image\\video_page\\awb.png");
#else
    lv_img_set_src(ui->video_photo_img_4, "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000050.rle");
#endif
    lv_img_set_pivot(ui->video_photo_img_4, 0, 0);
    lv_img_set_angle(ui->video_photo_img_4, 0);
    lv_img_set_zoom(ui->video_photo_img_4, 256);
    //Write codes video_photo_view_subpage
    ui->video_photo_view_subpage = lv_obj_create(ui->video_photo);

    //Set style for video_photo_view_subpage. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->video_photo_view_subpage, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_photo_view_subpage, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_photo_view_subpage, 204, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->video_photo_view_subpage, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->video_photo_view_subpage, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->video_photo_view_subpage, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->video_photo_view_subpage, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->video_photo_view_subpage, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->video_photo_view_subpage, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->video_photo_view_subpage, 186, 232);
    lv_obj_set_size(ui->video_photo_view_subpage, 539, 244);
    lv_obj_set_scrollbar_mode(ui->video_photo_view_subpage, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->video_photo_view_subpage, LV_OBJ_FLAG_HIDDEN);
    //Write codes video_photo_img_16
    ui->video_photo_img_16 = lv_img_create(ui->video_photo_view_subpage);

    //Set style for video_photo_img_16. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->video_photo_img_16, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->video_photo_img_16, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_photo_img_16, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_photo_img_16, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->video_photo_img_16, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->video_photo_img_16, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->video_photo_img_16, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->video_photo_img_16, 28, 7);
    lv_obj_set_size(ui->video_photo_img_16, 80, 80);
    lv_obj_set_scrollbar_mode(ui->video_photo_img_16, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->video_photo_img_16, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_add_flag(ui->video_photo_img_16, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_flag(ui->video_photo_img_16, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_img_set_src(ui->video_photo_img_16, "A:\\wl83\\wifi_video_master\\ui_prj\\dvr_800x480\\import\\image\\video_page\\menu_icon\\resolution_ratio.png");
#else
    lv_img_set_src(ui->video_photo_img_16, "mnt/sdfile/EXT_RESERVED/uipackres/ui/5600001c.rle");
#endif
    lv_img_set_pivot(ui->video_photo_img_16, 0, 0);
    lv_img_set_angle(ui->video_photo_img_16, 0);
    lv_img_set_zoom(ui->video_photo_img_16, 256);
    //Write codes video_photo_lbl_menu_title
    ui->video_photo_lbl_menu_title = lv_label_create(ui->video_photo_view_subpage);
    lv_label_set_text(ui->video_photo_lbl_menu_title, "menu_title");
    lv_label_set_long_mode(ui->video_photo_lbl_menu_title, LV_LABEL_LONG_WRAP);

    //Set style for video_photo_lbl_menu_title. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->video_photo_lbl_menu_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_photo_lbl_menu_title, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_photo_lbl_menu_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->video_photo_lbl_menu_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->video_photo_lbl_menu_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->video_photo_lbl_menu_title, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->video_photo_lbl_menu_title, &lv_font_FangZhengKaiTiJianTi_1_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->video_photo_lbl_menu_title, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->video_photo_lbl_menu_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->video_photo_lbl_menu_title, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->video_photo_lbl_menu_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->video_photo_lbl_menu_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->video_photo_lbl_menu_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->video_photo_lbl_menu_title, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->video_photo_lbl_menu_title, 111, 7);
    lv_obj_set_size(ui->video_photo_lbl_menu_title, 201, 53);
    lv_obj_set_scrollbar_mode(ui->video_photo_lbl_menu_title, LV_SCROLLBAR_MODE_OFF);
    //Write codes video_photo_lbl_22
    ui->video_photo_lbl_22 = lv_label_create(ui->video_photo_view_subpage);
    lv_label_set_text(ui->video_photo_lbl_22, "这个是预生成控件\n注意与lbl_menu_title字体字号一致\n图像大小\n拍摄方式单次定时秒\n连拍\n质量标准经济优质\n锐度强烈标准柔和\n白平衡日光阴天荧光灯钨丝\n黑白怀旧无特效\n自动\n曝光补偿\n防手抖\n快速预览\n色彩");
    lv_label_set_long_mode(ui->video_photo_lbl_22, LV_LABEL_LONG_WRAP);

    //Set style for video_photo_lbl_22. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->video_photo_lbl_22, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_photo_lbl_22, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_photo_lbl_22, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->video_photo_lbl_22, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->video_photo_lbl_22, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->video_photo_lbl_22, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->video_photo_lbl_22, &lv_font_FangZhengKaiTiJianTi_1_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->video_photo_lbl_22, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->video_photo_lbl_22, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->video_photo_lbl_22, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->video_photo_lbl_22, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->video_photo_lbl_22, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->video_photo_lbl_22, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->video_photo_lbl_22, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->video_photo_lbl_22, 110, 23);
    lv_obj_set_size(ui->video_photo_lbl_22, 415, 69);
    lv_obj_set_scrollbar_mode(ui->video_photo_lbl_22, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->video_photo_lbl_22, LV_OBJ_FLAG_HIDDEN);
    //Write codes video_photo_roller_mutifunc
    ui->video_photo_roller_mutifunc = lv_roller_create(ui->video_photo_view_subpage);

    //Set style for video_photo_roller_mutifunc. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->video_photo_roller_mutifunc, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_photo_roller_mutifunc, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_photo_roller_mutifunc, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->video_photo_roller_mutifunc, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->video_photo_roller_mutifunc, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui->video_photo_roller_mutifunc, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->video_photo_roller_mutifunc, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui->video_photo_roller_mutifunc, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui->video_photo_roller_mutifunc, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->video_photo_roller_mutifunc, lv_color_make(0x33, 0x33, 0x33), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->video_photo_roller_mutifunc, &lv_font_FangZhengKaiTiJianTi_1_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->video_photo_roller_mutifunc, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->video_photo_roller_mutifunc, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->video_photo_roller_mutifunc, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->video_photo_roller_mutifunc, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->video_photo_roller_mutifunc, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->video_photo_roller_mutifunc, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->video_photo_roller_mutifunc, 16, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for video_photo_roller_mutifunc. Part: LV_PART_SELECTED, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui->video_photo_roller_mutifunc, lv_color_make(0x21, 0x95, 0xf6), LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_photo_roller_mutifunc, 153, LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->video_photo_roller_mutifunc, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->video_photo_roller_mutifunc, &lv_font_FangZhengKaiTiJianTi_1_24, LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->video_photo_roller_mutifunc, 0, LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->video_photo_roller_mutifunc, LV_TEXT_ALIGN_CENTER, LV_PART_SELECTED | LV_STATE_DEFAULT);

    //Set style for video_photo_roller_mutifunc. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui->video_photo_roller_mutifunc, 5, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(ui->video_photo_roller_mutifunc, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui->video_photo_roller_mutifunc, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_shadow_width(ui->video_photo_roller_mutifunc, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_border_color(ui->video_photo_roller_mutifunc, lv_color_make(0xe6, 0xe6, 0xe6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_border_width(ui->video_photo_roller_mutifunc, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_border_opa(ui->video_photo_roller_mutifunc, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_border_side(ui->video_photo_roller_mutifunc, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(ui->video_photo_roller_mutifunc, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->video_photo_roller_mutifunc, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->video_photo_roller_mutifunc, 128, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(ui->video_photo_roller_mutifunc, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_color(ui->video_photo_roller_mutifunc, lv_color_make(0x33, 0x33, 0x33), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_font(ui->video_photo_roller_mutifunc, &lv_font_FangZhengKaiTiJianTi_1_24, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_letter_space(ui->video_photo_roller_mutifunc, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_line_space(ui->video_photo_roller_mutifunc, 16, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_align(ui->video_photo_roller_mutifunc, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_pad_left(ui->video_photo_roller_mutifunc, 16, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_pad_right(ui->video_photo_roller_mutifunc, 16, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_pad_top(ui->video_photo_roller_mutifunc, 16, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_pad_bottom(ui->video_photo_roller_mutifunc, 16, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->video_photo_roller_mutifunc, 159, 58);
    lv_obj_set_size(ui->video_photo_roller_mutifunc, 243, 126);
    lv_obj_set_scrollbar_mode(ui->video_photo_roller_mutifunc, LV_SCROLLBAR_MODE_OFF);
    lv_roller_set_options(ui->video_photo_roller_mutifunc, "VGA\n1M\n2M\n3M\n5M\n8M\n10M\n12M\n64M", LV_ROLLER_MODE_INFINITE);
    lv_roller_set_visible_row_count(ui->video_photo_roller_mutifunc, 3);
    //Write codes video_photo_lbl_funkey1
    ui->video_photo_lbl_funkey1 = lv_btn_create(ui->video_photo_view_subpage);

    //Set style for video_photo_lbl_funkey1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->video_photo_lbl_funkey1, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_photo_lbl_funkey1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_photo_lbl_funkey1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->video_photo_lbl_funkey1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->video_photo_lbl_funkey1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui->video_photo_lbl_funkey1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->video_photo_lbl_funkey1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui->video_photo_lbl_funkey1, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui->video_photo_lbl_funkey1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->video_photo_lbl_funkey1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->video_photo_lbl_funkey1, &lv_font_FangZhengKaiTiJianTi_1_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->video_photo_lbl_funkey1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->video_photo_lbl_funkey1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for video_photo_lbl_funkey1. Part: LV_PART_MAIN, State: LV_STATE_FOCUSED
    lv_obj_set_style_radius(ui->video_photo_lbl_funkey1, 5, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_bg_color(ui->video_photo_lbl_funkey1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_bg_opa(ui->video_photo_lbl_funkey1, 255, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_shadow_width(ui->video_photo_lbl_funkey1, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_border_width(ui->video_photo_lbl_funkey1, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_color(ui->video_photo_lbl_funkey1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_width(ui->video_photo_lbl_funkey1, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_opa(ui->video_photo_lbl_funkey1, 128, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_pad(ui->video_photo_lbl_funkey1, 2, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_text_color(ui->video_photo_lbl_funkey1, lv_color_make(0xFF, 0xEB, 0x3B), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_text_font(ui->video_photo_lbl_funkey1, &lv_font_FangZhengKaiTiJianTi_1_24, LV_PART_MAIN | LV_STATE_FOCUSED);

    //Set style for video_photo_lbl_funkey1. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui->video_photo_lbl_funkey1, 5, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(ui->video_photo_lbl_funkey1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui->video_photo_lbl_funkey1, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_shadow_width(ui->video_photo_lbl_funkey1, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_border_width(ui->video_photo_lbl_funkey1, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(ui->video_photo_lbl_funkey1, lv_color_make(0xFF, 0xE7, 0x00), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->video_photo_lbl_funkey1, 4, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->video_photo_lbl_funkey1, 128, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(ui->video_photo_lbl_funkey1, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_color(ui->video_photo_lbl_funkey1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_font(ui->video_photo_lbl_funkey1, &lv_font_FangZhengKaiTiJianTi_1_24, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->video_photo_lbl_funkey1, 28, 190);
    lv_obj_set_size(ui->video_photo_lbl_funkey1, 117, 50);
    lv_obj_set_scrollbar_mode(ui->video_photo_lbl_funkey1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->video_photo_lbl_funkey1, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_flag(ui->video_photo_lbl_funkey1, LV_OBJ_FLAG_EVENT_BUBBLE);
    ui->video_photo_lbl_funkey1_label = lv_label_create(ui->video_photo_lbl_funkey1);
    lv_label_set_text(ui->video_photo_lbl_funkey1_label, "button");
    lv_obj_set_style_pad_all(ui->video_photo_lbl_funkey1, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->video_photo_lbl_funkey1_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes video_photo_lbl_funkey2
    ui->video_photo_lbl_funkey2 = lv_btn_create(ui->video_photo_view_subpage);

    //Set style for video_photo_lbl_funkey2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->video_photo_lbl_funkey2, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_photo_lbl_funkey2, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_photo_lbl_funkey2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->video_photo_lbl_funkey2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->video_photo_lbl_funkey2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui->video_photo_lbl_funkey2, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->video_photo_lbl_funkey2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui->video_photo_lbl_funkey2, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui->video_photo_lbl_funkey2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->video_photo_lbl_funkey2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->video_photo_lbl_funkey2, &lv_font_FangZhengKaiTiJianTi_1_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->video_photo_lbl_funkey2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->video_photo_lbl_funkey2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for video_photo_lbl_funkey2. Part: LV_PART_MAIN, State: LV_STATE_FOCUSED
    lv_obj_set_style_radius(ui->video_photo_lbl_funkey2, 5, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_bg_color(ui->video_photo_lbl_funkey2, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_bg_opa(ui->video_photo_lbl_funkey2, 255, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_shadow_width(ui->video_photo_lbl_funkey2, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_border_width(ui->video_photo_lbl_funkey2, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_color(ui->video_photo_lbl_funkey2, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_width(ui->video_photo_lbl_funkey2, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_opa(ui->video_photo_lbl_funkey2, 128, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_pad(ui->video_photo_lbl_funkey2, 2, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_text_color(ui->video_photo_lbl_funkey2, lv_color_make(0xFF, 0xEB, 0x3B), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_text_font(ui->video_photo_lbl_funkey2, &lv_font_FangZhengKaiTiJianTi_1_24, LV_PART_MAIN | LV_STATE_FOCUSED);

    //Set style for video_photo_lbl_funkey2. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui->video_photo_lbl_funkey2, 5, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(ui->video_photo_lbl_funkey2, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui->video_photo_lbl_funkey2, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_shadow_width(ui->video_photo_lbl_funkey2, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_border_width(ui->video_photo_lbl_funkey2, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(ui->video_photo_lbl_funkey2, lv_color_make(0xFF, 0xE7, 0x00), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->video_photo_lbl_funkey2, 4, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->video_photo_lbl_funkey2, 128, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(ui->video_photo_lbl_funkey2, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_color(ui->video_photo_lbl_funkey2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_font(ui->video_photo_lbl_funkey2, &lv_font_FangZhengKaiTiJianTi_1_24, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->video_photo_lbl_funkey2, 159, 190);
    lv_obj_set_size(ui->video_photo_lbl_funkey2, 117, 50);
    lv_obj_set_scrollbar_mode(ui->video_photo_lbl_funkey2, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->video_photo_lbl_funkey2, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_flag(ui->video_photo_lbl_funkey2, LV_OBJ_FLAG_EVENT_BUBBLE);
    ui->video_photo_lbl_funkey2_label = lv_label_create(ui->video_photo_lbl_funkey2);
    lv_label_set_text(ui->video_photo_lbl_funkey2_label, "button");
    lv_obj_set_size(ui->video_photo_lbl_funkey2_label, 120, 32);
    lv_label_set_long_mode(ui->video_photo_lbl_funkey2_label, LV_LABEL_LONG_SCROLL);
    lv_obj_set_style_pad_all(ui->video_photo_lbl_funkey2, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->video_photo_lbl_funkey2_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes video_photo_lbl_funkey3
    ui->video_photo_lbl_funkey3 = lv_btn_create(ui->video_photo_view_subpage);

    //Set style for video_photo_lbl_funkey3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->video_photo_lbl_funkey3, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_photo_lbl_funkey3, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_photo_lbl_funkey3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->video_photo_lbl_funkey3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->video_photo_lbl_funkey3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui->video_photo_lbl_funkey3, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->video_photo_lbl_funkey3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui->video_photo_lbl_funkey3, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui->video_photo_lbl_funkey3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->video_photo_lbl_funkey3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->video_photo_lbl_funkey3, &lv_font_FangZhengKaiTiJianTi_1_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->video_photo_lbl_funkey3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->video_photo_lbl_funkey3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for video_photo_lbl_funkey3. Part: LV_PART_MAIN, State: LV_STATE_FOCUSED
    lv_obj_set_style_radius(ui->video_photo_lbl_funkey3, 5, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_bg_color(ui->video_photo_lbl_funkey3, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_bg_opa(ui->video_photo_lbl_funkey3, 255, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_shadow_width(ui->video_photo_lbl_funkey3, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_border_width(ui->video_photo_lbl_funkey3, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_color(ui->video_photo_lbl_funkey3, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_width(ui->video_photo_lbl_funkey3, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_opa(ui->video_photo_lbl_funkey3, 128, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_pad(ui->video_photo_lbl_funkey3, 2, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_text_color(ui->video_photo_lbl_funkey3, lv_color_make(0xFF, 0xEB, 0x3B), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_text_font(ui->video_photo_lbl_funkey3, &lv_font_FangZhengKaiTiJianTi_1_24, LV_PART_MAIN | LV_STATE_FOCUSED);

    //Set style for video_photo_lbl_funkey3. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui->video_photo_lbl_funkey3, 5, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(ui->video_photo_lbl_funkey3, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui->video_photo_lbl_funkey3, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_shadow_width(ui->video_photo_lbl_funkey3, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_border_width(ui->video_photo_lbl_funkey3, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(ui->video_photo_lbl_funkey3, lv_color_make(0xFF, 0xE7, 0x00), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->video_photo_lbl_funkey3, 4, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->video_photo_lbl_funkey3, 128, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(ui->video_photo_lbl_funkey3, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_color(ui->video_photo_lbl_funkey3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_font(ui->video_photo_lbl_funkey3, &lv_font_FangZhengKaiTiJianTi_1_24, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->video_photo_lbl_funkey3, 286, 190);
    lv_obj_set_size(ui->video_photo_lbl_funkey3, 117, 50);
    lv_obj_set_scrollbar_mode(ui->video_photo_lbl_funkey3, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->video_photo_lbl_funkey3, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_flag(ui->video_photo_lbl_funkey3, LV_OBJ_FLAG_EVENT_BUBBLE);
    ui->video_photo_lbl_funkey3_label = lv_label_create(ui->video_photo_lbl_funkey3);
    lv_label_set_text(ui->video_photo_lbl_funkey3_label, "button");
    lv_obj_set_size(ui->video_photo_lbl_funkey3_label, 120, 32);
    lv_label_set_long_mode(ui->video_photo_lbl_funkey3_label, LV_LABEL_LONG_SCROLL);
    lv_obj_set_style_pad_all(ui->video_photo_lbl_funkey3, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->video_photo_lbl_funkey3_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes video_photo_lbl_funkey4
    ui->video_photo_lbl_funkey4 = lv_btn_create(ui->video_photo_view_subpage);

    //Set style for video_photo_lbl_funkey4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->video_photo_lbl_funkey4, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_photo_lbl_funkey4, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_photo_lbl_funkey4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->video_photo_lbl_funkey4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->video_photo_lbl_funkey4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui->video_photo_lbl_funkey4, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->video_photo_lbl_funkey4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui->video_photo_lbl_funkey4, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui->video_photo_lbl_funkey4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->video_photo_lbl_funkey4, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->video_photo_lbl_funkey4, &lv_font_FangZhengKaiTiJianTi_1_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->video_photo_lbl_funkey4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->video_photo_lbl_funkey4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for video_photo_lbl_funkey4. Part: LV_PART_MAIN, State: LV_STATE_FOCUSED
    lv_obj_set_style_radius(ui->video_photo_lbl_funkey4, 5, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_bg_color(ui->video_photo_lbl_funkey4, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_bg_opa(ui->video_photo_lbl_funkey4, 255, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_shadow_width(ui->video_photo_lbl_funkey4, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_border_width(ui->video_photo_lbl_funkey4, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_color(ui->video_photo_lbl_funkey4, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_width(ui->video_photo_lbl_funkey4, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_opa(ui->video_photo_lbl_funkey4, 128, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_pad(ui->video_photo_lbl_funkey4, 2, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_text_color(ui->video_photo_lbl_funkey4, lv_color_make(0xFF, 0xEB, 0x3B), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_text_font(ui->video_photo_lbl_funkey4, &lv_font_FangZhengKaiTiJianTi_1_24, LV_PART_MAIN | LV_STATE_FOCUSED);

    //Set style for video_photo_lbl_funkey4. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui->video_photo_lbl_funkey4, 5, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(ui->video_photo_lbl_funkey4, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui->video_photo_lbl_funkey4, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_shadow_width(ui->video_photo_lbl_funkey4, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_border_width(ui->video_photo_lbl_funkey4, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(ui->video_photo_lbl_funkey4, lv_color_make(0xFF, 0xE7, 0x00), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->video_photo_lbl_funkey4, 4, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->video_photo_lbl_funkey4, 128, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(ui->video_photo_lbl_funkey4, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_color(ui->video_photo_lbl_funkey4, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_font(ui->video_photo_lbl_funkey4, &lv_font_FangZhengKaiTiJianTi_1_24, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->video_photo_lbl_funkey4, 415, 190);
    lv_obj_set_size(ui->video_photo_lbl_funkey4, 117, 50);
    lv_obj_set_scrollbar_mode(ui->video_photo_lbl_funkey4, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->video_photo_lbl_funkey4, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_flag(ui->video_photo_lbl_funkey4, LV_OBJ_FLAG_EVENT_BUBBLE);
    ui->video_photo_lbl_funkey4_label = lv_label_create(ui->video_photo_lbl_funkey4);
    lv_label_set_text(ui->video_photo_lbl_funkey4_label, "button");
    lv_obj_set_size(ui->video_photo_lbl_funkey4_label, 120, 32);
    lv_label_set_long_mode(ui->video_photo_lbl_funkey4_label, LV_LABEL_LONG_SCROLL);
    lv_obj_set_style_pad_all(ui->video_photo_lbl_funkey4, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->video_photo_lbl_funkey4_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes video_photo_show_capture_time
    ui->video_photo_show_capture_time = lv_label_create(ui->video_photo);
    lv_label_set_text(ui->video_photo_show_capture_time, "3");
    lv_label_set_long_mode(ui->video_photo_show_capture_time, LV_LABEL_LONG_WRAP);

    //Set style for video_photo_show_capture_time. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->video_photo_show_capture_time, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_photo_show_capture_time, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_photo_show_capture_time, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->video_photo_show_capture_time, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->video_photo_show_capture_time, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->video_photo_show_capture_time, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->video_photo_show_capture_time, &lv_font_montserratMedium_160, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->video_photo_show_capture_time, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->video_photo_show_capture_time, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->video_photo_show_capture_time, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->video_photo_show_capture_time, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->video_photo_show_capture_time, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->video_photo_show_capture_time, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->video_photo_show_capture_time, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->video_photo_show_capture_time, 300, 140);
    lv_obj_set_size(ui->video_photo_show_capture_time, 200, 200);
    lv_obj_set_scrollbar_mode(ui->video_photo_show_capture_time, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->video_photo_show_capture_time, LV_OBJ_FLAG_HIDDEN);
    lv_obj_update_layout(ui->video_photo);
    ui->video_photo_del = false;

    //Init events for screen
    events_init_video_photo(ui);
    return ui->video_photo;
}
void unload_scr_video_photo(lv_ui *ui)
{
    ui->video_photo_del = true;
}

#endif
