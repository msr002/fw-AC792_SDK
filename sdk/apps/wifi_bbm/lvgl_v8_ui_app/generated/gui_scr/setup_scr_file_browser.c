/*Generate Code, Do NOT Edit!*/
#include "lvgl.h"
#include <stdio.h>
#include <stdlib.h>
#include "../gui_guider.h"
#include "../gui_events/events_init.h"
#include "../gui_events/callback_handler.h"
#include "../gui_timelines/gui_timelines.h"
#include "../../custom/custom.h"


lv_obj_t *setup_scr_file_browser(lv_ui *ui)
{
    //Write codes file_browser
    ui->file_browser = lv_obj_create(NULL);
    lv_group_t *def_group = lv_group_get_default();

    //Set style for file_browser. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui->file_browser, lv_color_make(0xE2, 0xDC, 0xDC), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->file_browser, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->file_browser, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(ui->file_browser, LV_SCROLLBAR_MODE_OFF);
    //Write codes file_browser_view_2
    ui->file_browser_view_2 = lv_obj_create(ui->file_browser);

    //Set style for file_browser_view_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->file_browser_view_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->file_browser_view_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->file_browser_view_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->file_browser_view_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->file_browser_view_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->file_browser_view_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->file_browser_view_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->file_browser_view_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->file_browser_view_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->file_browser_view_2, 20, 0);
    lv_obj_set_size(ui->file_browser_view_2, 80, 480);
    lv_obj_set_scrollbar_mode(ui->file_browser_view_2, LV_SCROLLBAR_MODE_OFF);
    //Write codes file_browser_imgbtn_1
    ui->file_browser_imgbtn_1 = lv_imgbtn_create(ui->file_browser_view_2);

    //Set style for file_browser_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->file_browser_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->file_browser_imgbtn_1, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->file_browser_imgbtn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->file_browser_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->file_browser_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->file_browser_imgbtn_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->file_browser_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->file_browser_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->file_browser_imgbtn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->file_browser_imgbtn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->file_browser_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->file_browser_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for file_browser_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui->file_browser_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_clip_corner(ui->file_browser_imgbtn_1, true, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(ui->file_browser_imgbtn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui->file_browser_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_shadow_width(ui->file_browser_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(ui->file_browser_imgbtn_1, lv_color_make(0x21, 0xB4, 0xF6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->file_browser_imgbtn_1, 4, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->file_browser_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(ui->file_browser_imgbtn_1, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_color(ui->file_browser_imgbtn_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_font(ui->file_browser_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor(ui->file_browser_imgbtn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor_opa(ui->file_browser_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_opa(ui->file_browser_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Set style for file_browser_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_PRESSED
    lv_obj_set_style_radius(ui->file_browser_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_clip_corner(ui->file_browser_imgbtn_1, true, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->file_browser_imgbtn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(ui->file_browser_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->file_browser_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->file_browser_imgbtn_1, lv_color_make(0xFF, 0x33, 0xFF), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->file_browser_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_recolor(ui->file_browser_imgbtn_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_recolor_opa(ui->file_browser_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->file_browser_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_PRESSED);

    //Set style for file_browser_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_CHECKED
    lv_obj_set_style_radius(ui->file_browser_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_clip_corner(ui->file_browser_imgbtn_1, true, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui->file_browser_imgbtn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui->file_browser_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->file_browser_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->file_browser_imgbtn_1, lv_color_make(0xFF, 0x33, 0xFF), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->file_browser_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_recolor(ui->file_browser_imgbtn_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_recolor_opa(ui->file_browser_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->file_browser_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_pos(ui->file_browser_imgbtn_1, 8, 30);
    lv_obj_set_size(ui->file_browser_imgbtn_1, 64, 64);
    lv_obj_set_scrollbar_mode(ui->file_browser_imgbtn_1, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui->file_browser_imgbtn_1);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_imgbtn_set_src(ui->file_browser_imgbtn_1, LV_IMGBTN_STATE_RELEASED, NULL, "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\back.png", NULL);
    lv_imgbtn_set_src(ui->file_browser_imgbtn_1, LV_IMGBTN_STATE_PRESSED, NULL, "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\back.png", NULL);
    lv_imgbtn_set_src(ui->file_browser_imgbtn_1, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\back.png", NULL);
    lv_imgbtn_set_src(ui->file_browser_imgbtn_1, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\back.png", NULL);
#else
    lv_imgbtn_set_src(ui->file_browser_imgbtn_1, LV_IMGBTN_STATE_RELEASED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/55000005.zip", NULL);
    lv_imgbtn_set_src(ui->file_browser_imgbtn_1, LV_IMGBTN_STATE_PRESSED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/55000005.zip", NULL);
    lv_imgbtn_set_src(ui->file_browser_imgbtn_1, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/55000005.zip", NULL);
    lv_imgbtn_set_src(ui->file_browser_imgbtn_1, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/55000005.zip", NULL);
#endif
    lv_obj_add_flag(ui->file_browser_imgbtn_1, LV_OBJ_FLAG_CHECKABLE);
    ui->file_browser_imgbtn_1_label = lv_label_create(ui->file_browser_imgbtn_1);
    lv_label_set_text(ui->file_browser_imgbtn_1_label, "");
    lv_obj_set_style_pad_all(ui->file_browser_imgbtn_1, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->file_browser_imgbtn_1_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes file_browser_imgbtn_2
    ui->file_browser_imgbtn_2 = lv_imgbtn_create(ui->file_browser_view_2);

    //Set style for file_browser_imgbtn_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->file_browser_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->file_browser_imgbtn_2, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->file_browser_imgbtn_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->file_browser_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->file_browser_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->file_browser_imgbtn_2, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->file_browser_imgbtn_2, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->file_browser_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->file_browser_imgbtn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->file_browser_imgbtn_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->file_browser_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->file_browser_imgbtn_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for file_browser_imgbtn_2. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui->file_browser_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_clip_corner(ui->file_browser_imgbtn_2, true, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(ui->file_browser_imgbtn_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui->file_browser_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_shadow_width(ui->file_browser_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(ui->file_browser_imgbtn_2, lv_color_make(0x21, 0xB4, 0xF6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->file_browser_imgbtn_2, 4, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->file_browser_imgbtn_2, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(ui->file_browser_imgbtn_2, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_color(ui->file_browser_imgbtn_2, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_font(ui->file_browser_imgbtn_2, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor(ui->file_browser_imgbtn_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor_opa(ui->file_browser_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_opa(ui->file_browser_imgbtn_2, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->file_browser_imgbtn_2, 8, 140);
    lv_obj_set_size(ui->file_browser_imgbtn_2, 64, 63);
    lv_obj_set_scrollbar_mode(ui->file_browser_imgbtn_2, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui->file_browser_imgbtn_2);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_imgbtn_set_src(ui->file_browser_imgbtn_2, LV_IMGBTN_STATE_RELEASED, NULL, "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\up.png", NULL);
    lv_imgbtn_set_src(ui->file_browser_imgbtn_2, LV_IMGBTN_STATE_PRESSED, NULL, "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\up.png", NULL);
    lv_imgbtn_set_src(ui->file_browser_imgbtn_2, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\up.png", NULL);
    lv_imgbtn_set_src(ui->file_browser_imgbtn_2, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\up.png", NULL);
#else
    lv_imgbtn_set_src(ui->file_browser_imgbtn_2, LV_IMGBTN_STATE_RELEASED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/55000007.zip", NULL);
    lv_imgbtn_set_src(ui->file_browser_imgbtn_2, LV_IMGBTN_STATE_PRESSED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/55000007.zip", NULL);
    lv_imgbtn_set_src(ui->file_browser_imgbtn_2, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/55000007.zip", NULL);
    lv_imgbtn_set_src(ui->file_browser_imgbtn_2, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/55000007.zip", NULL);
#endif
    lv_obj_add_flag(ui->file_browser_imgbtn_2, LV_OBJ_FLAG_CHECKABLE);
    ui->file_browser_imgbtn_2_label = lv_label_create(ui->file_browser_imgbtn_2);
    lv_label_set_text(ui->file_browser_imgbtn_2_label, "");
    lv_obj_set_style_pad_all(ui->file_browser_imgbtn_2, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->file_browser_imgbtn_2_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes file_browser_imgbtn_3
    ui->file_browser_imgbtn_3 = lv_imgbtn_create(ui->file_browser_view_2);

    //Set style for file_browser_imgbtn_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->file_browser_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->file_browser_imgbtn_3, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->file_browser_imgbtn_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->file_browser_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->file_browser_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->file_browser_imgbtn_3, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->file_browser_imgbtn_3, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->file_browser_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->file_browser_imgbtn_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->file_browser_imgbtn_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->file_browser_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->file_browser_imgbtn_3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for file_browser_imgbtn_3. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui->file_browser_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_clip_corner(ui->file_browser_imgbtn_3, true, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(ui->file_browser_imgbtn_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui->file_browser_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_shadow_width(ui->file_browser_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(ui->file_browser_imgbtn_3, lv_color_make(0x21, 0xB4, 0xF6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->file_browser_imgbtn_3, 4, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->file_browser_imgbtn_3, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(ui->file_browser_imgbtn_3, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_color(ui->file_browser_imgbtn_3, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_font(ui->file_browser_imgbtn_3, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor(ui->file_browser_imgbtn_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor_opa(ui->file_browser_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_opa(ui->file_browser_imgbtn_3, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->file_browser_imgbtn_3, 8, 300);
    lv_obj_set_size(ui->file_browser_imgbtn_3, 64, 64);
    lv_obj_set_scrollbar_mode(ui->file_browser_imgbtn_3, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui->file_browser_imgbtn_3);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_imgbtn_set_src(ui->file_browser_imgbtn_3, LV_IMGBTN_STATE_RELEASED, NULL, "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\down.png", NULL);
    lv_imgbtn_set_src(ui->file_browser_imgbtn_3, LV_IMGBTN_STATE_PRESSED, NULL, "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\down.png", NULL);
    lv_imgbtn_set_src(ui->file_browser_imgbtn_3, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\down.png", NULL);
    lv_imgbtn_set_src(ui->file_browser_imgbtn_3, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\down.png", NULL);
#else
    lv_imgbtn_set_src(ui->file_browser_imgbtn_3, LV_IMGBTN_STATE_RELEASED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/55000008.zip", NULL);
    lv_imgbtn_set_src(ui->file_browser_imgbtn_3, LV_IMGBTN_STATE_PRESSED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/55000008.zip", NULL);
    lv_imgbtn_set_src(ui->file_browser_imgbtn_3, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/55000008.zip", NULL);
    lv_imgbtn_set_src(ui->file_browser_imgbtn_3, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/55000008.zip", NULL);
#endif
    lv_obj_add_flag(ui->file_browser_imgbtn_3, LV_OBJ_FLAG_CHECKABLE);
    ui->file_browser_imgbtn_3_label = lv_label_create(ui->file_browser_imgbtn_3);
    lv_label_set_text(ui->file_browser_imgbtn_3_label, "");
    lv_obj_set_style_pad_all(ui->file_browser_imgbtn_3, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->file_browser_imgbtn_3_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes file_browser_lbl_1
    ui->file_browser_lbl_1 = lv_label_create(ui->file_browser_view_2);
    lv_label_set_text(ui->file_browser_lbl_1, "50\n/\n1000");
    lv_label_set_long_mode(ui->file_browser_lbl_1, LV_LABEL_LONG_WRAP);

    //Set style for file_browser_lbl_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->file_browser_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->file_browser_lbl_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->file_browser_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->file_browser_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->file_browser_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->file_browser_lbl_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->file_browser_lbl_1, &lv_font_montserratMedium_20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->file_browser_lbl_1, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->file_browser_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->file_browser_lbl_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->file_browser_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->file_browser_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->file_browser_lbl_1, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->file_browser_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->file_browser_lbl_1, 8, 217);
    lv_obj_set_size(ui->file_browser_lbl_1, 64, 80);
    lv_obj_set_scrollbar_mode(ui->file_browser_lbl_1, LV_SCROLLBAR_MODE_OFF);
    //Write codes file_browser_imgbtn_4
    ui->file_browser_imgbtn_4 = lv_imgbtn_create(ui->file_browser_view_2);

    //Set style for file_browser_imgbtn_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->file_browser_imgbtn_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->file_browser_imgbtn_4, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->file_browser_imgbtn_4, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->file_browser_imgbtn_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->file_browser_imgbtn_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->file_browser_imgbtn_4, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->file_browser_imgbtn_4, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->file_browser_imgbtn_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->file_browser_imgbtn_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->file_browser_imgbtn_4, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->file_browser_imgbtn_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->file_browser_imgbtn_4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for file_browser_imgbtn_4. Part: LV_PART_MAIN, State: LV_STATE_FOCUSED
    lv_obj_set_style_radius(ui->file_browser_imgbtn_4, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_clip_corner(ui->file_browser_imgbtn_4, true, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_bg_color(ui->file_browser_imgbtn_4, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_bg_opa(ui->file_browser_imgbtn_4, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_shadow_width(ui->file_browser_imgbtn_4, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_color(ui->file_browser_imgbtn_4, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_width(ui->file_browser_imgbtn_4, 2, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_opa(ui->file_browser_imgbtn_4, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_pad(ui->file_browser_imgbtn_4, 2, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_text_color(ui->file_browser_imgbtn_4, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_text_font(ui->file_browser_imgbtn_4, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_img_recolor(ui->file_browser_imgbtn_4, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_img_recolor_opa(ui->file_browser_imgbtn_4, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_img_opa(ui->file_browser_imgbtn_4, 255, LV_PART_MAIN | LV_STATE_FOCUSED);

    //Set style for file_browser_imgbtn_4. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui->file_browser_imgbtn_4, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_clip_corner(ui->file_browser_imgbtn_4, true, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(ui->file_browser_imgbtn_4, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui->file_browser_imgbtn_4, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_shadow_width(ui->file_browser_imgbtn_4, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(ui->file_browser_imgbtn_4, lv_color_make(0x21, 0xB4, 0xF6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->file_browser_imgbtn_4, 4, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->file_browser_imgbtn_4, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(ui->file_browser_imgbtn_4, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_color(ui->file_browser_imgbtn_4, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_font(ui->file_browser_imgbtn_4, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor(ui->file_browser_imgbtn_4, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor_opa(ui->file_browser_imgbtn_4, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_opa(ui->file_browser_imgbtn_4, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Set style for file_browser_imgbtn_4. Part: LV_PART_MAIN, State: LV_STATE_PRESSED
    lv_obj_set_style_radius(ui->file_browser_imgbtn_4, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_clip_corner(ui->file_browser_imgbtn_4, true, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->file_browser_imgbtn_4, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(ui->file_browser_imgbtn_4, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->file_browser_imgbtn_4, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->file_browser_imgbtn_4, lv_color_make(0xFF, 0x33, 0xFF), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->file_browser_imgbtn_4, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_recolor(ui->file_browser_imgbtn_4, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_recolor_opa(ui->file_browser_imgbtn_4, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->file_browser_imgbtn_4, 255, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_pos(ui->file_browser_imgbtn_4, 8, 390);
    lv_obj_set_size(ui->file_browser_imgbtn_4, 64, 64);
    lv_obj_set_scrollbar_mode(ui->file_browser_imgbtn_4, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui->file_browser_imgbtn_4);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_imgbtn_set_src(ui->file_browser_imgbtn_4, LV_IMGBTN_STATE_RELEASED, NULL, "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\delete.png", NULL);
    lv_imgbtn_set_src(ui->file_browser_imgbtn_4, LV_IMGBTN_STATE_PRESSED, NULL, "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\delete.png", NULL);
    lv_imgbtn_set_src(ui->file_browser_imgbtn_4, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\delete.png", NULL);
    lv_imgbtn_set_src(ui->file_browser_imgbtn_4, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\delete.png", NULL);
#else
    lv_imgbtn_set_src(ui->file_browser_imgbtn_4, LV_IMGBTN_STATE_RELEASED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/55000009.zip", NULL);
    lv_imgbtn_set_src(ui->file_browser_imgbtn_4, LV_IMGBTN_STATE_PRESSED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/55000009.zip", NULL);
    lv_imgbtn_set_src(ui->file_browser_imgbtn_4, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/55000009.zip", NULL);
    lv_imgbtn_set_src(ui->file_browser_imgbtn_4, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/55000009.zip", NULL);
#endif
    lv_obj_add_flag(ui->file_browser_imgbtn_4, LV_OBJ_FLAG_CHECKABLE);
    ui->file_browser_imgbtn_4_label = lv_label_create(ui->file_browser_imgbtn_4);
    lv_label_set_text(ui->file_browser_imgbtn_4_label, "");
    lv_obj_set_style_pad_all(ui->file_browser_imgbtn_4, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->file_browser_imgbtn_4_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes file_browser_browser_cont
    ui->file_browser_browser_cont = lv_obj_create(ui->file_browser);

    //Set style for file_browser_browser_cont. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->file_browser_browser_cont, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->file_browser_browser_cont, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->file_browser_browser_cont, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->file_browser_browser_cont, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->file_browser_browser_cont, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->file_browser_browser_cont, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->file_browser_browser_cont, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->file_browser_browser_cont, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->file_browser_browser_cont, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->file_browser_browser_cont, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->file_browser_browser_cont, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->file_browser_browser_cont, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->file_browser_browser_cont, 104, 30);
    lv_obj_set_size(ui->file_browser_browser_cont, 660, 435);
    lv_obj_set_scrollbar_mode(ui->file_browser_browser_cont, LV_SCROLLBAR_MODE_OFF);
    //Write codes file_browser_file_cont1
    ui->file_browser_file_cont1 = lv_obj_create(ui->file_browser_browser_cont);

    //Set style for file_browser_file_cont1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->file_browser_file_cont1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->file_browser_file_cont1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->file_browser_file_cont1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->file_browser_file_cont1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->file_browser_file_cont1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->file_browser_file_cont1, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->file_browser_file_cont1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->file_browser_file_cont1, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui->file_browser_file_cont1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->file_browser_file_cont1, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui->file_browser_file_cont1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui->file_browser_file_cont1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->file_browser_file_cont1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->file_browser_file_cont1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->file_browser_file_cont1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->file_browser_file_cont1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for file_browser_file_cont1. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui->file_browser_file_cont1, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(ui->file_browser_file_cont1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui->file_browser_file_cont1, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_shadow_width(ui->file_browser_file_cont1, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_border_width(ui->file_browser_file_cont1, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(ui->file_browser_file_cont1, lv_color_make(0x21, 0xB4, 0xF6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->file_browser_file_cont1, 4, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->file_browser_file_cont1, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(ui->file_browser_file_cont1, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_pad_left(ui->file_browser_file_cont1, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_pad_right(ui->file_browser_file_cont1, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_pad_top(ui->file_browser_file_cont1, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_pad_bottom(ui->file_browser_file_cont1, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->file_browser_file_cont1, 20, 10);
    lv_obj_set_size(ui->file_browser_file_cont1, 200, 200);
    lv_obj_set_scrollbar_mode(ui->file_browser_file_cont1, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui->file_browser_file_cont1);
    //Write codes file_browser_img_1
    ui->file_browser_img_1 = lv_img_create(ui->file_browser_file_cont1);

    //Set style for file_browser_img_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->file_browser_img_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->file_browser_img_1, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->file_browser_img_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->file_browser_img_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->file_browser_img_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->file_browser_img_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->file_browser_img_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->file_browser_img_1, 5, 0);
    lv_obj_set_size(ui->file_browser_img_1, 192, 160);
    lv_obj_set_scrollbar_mode(ui->file_browser_img_1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->file_browser_img_1, LV_OBJ_FLAG_EVENT_BUBBLE);
    //Write codes file_browser_lbl_2
    ui->file_browser_lbl_2 = lv_label_create(ui->file_browser_file_cont1);
    lv_label_set_text(ui->file_browser_lbl_2, "VID_0001.AVI");
    lv_label_set_long_mode(ui->file_browser_lbl_2, LV_LABEL_LONG_WRAP);

    //Set style for file_browser_lbl_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->file_browser_lbl_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->file_browser_lbl_2, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->file_browser_lbl_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->file_browser_lbl_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->file_browser_lbl_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->file_browser_lbl_2, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->file_browser_lbl_2, &lv_font_montserratMedium_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->file_browser_lbl_2, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->file_browser_lbl_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->file_browser_lbl_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->file_browser_lbl_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->file_browser_lbl_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->file_browser_lbl_2, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->file_browser_lbl_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->file_browser_lbl_2, 4, 161);
    lv_obj_set_size(ui->file_browser_lbl_2, 192, 30);
    lv_obj_set_scrollbar_mode(ui->file_browser_lbl_2, LV_SCROLLBAR_MODE_OFF);
    //Write codes file_browser_cb_1
    ui->file_browser_cb_1 = lv_checkbox_create(ui->file_browser_file_cont1);
    lv_checkbox_set_text(ui->file_browser_cb_1, "checkbox");

    //Set style for file_browser_cb_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->file_browser_cb_1, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->file_browser_cb_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->file_browser_cb_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->file_browser_cb_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->file_browser_cb_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui->file_browser_cb_1, lv_color_make(0xB4, 0x26, 0x1B), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->file_browser_cb_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui->file_browser_cb_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui->file_browser_cb_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->file_browser_cb_1, lv_color_make(0x0D, 0x30, 0x55), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->file_browser_cb_1, &lv_font_montserratMedium_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->file_browser_cb_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for file_browser_cb_1. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui->file_browser_cb_1, 6, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(ui->file_browser_cb_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui->file_browser_cb_1, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_shadow_width(ui->file_browser_cb_1, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_border_width(ui->file_browser_cb_1, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(ui->file_browser_cb_1, lv_color_make(0x21, 0xB4, 0xF6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->file_browser_cb_1, 4, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->file_browser_cb_1, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(ui->file_browser_cb_1, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_color(ui->file_browser_cb_1, lv_color_make(0x0D, 0x30, 0x55), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_font(ui->file_browser_cb_1, &lv_font_montserratMedium_24, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_letter_space(ui->file_browser_cb_1, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->file_browser_cb_1, 163, 4);
    lv_obj_set_size(ui->file_browser_cb_1, 30, 30);
    lv_obj_set_scrollbar_mode(ui->file_browser_cb_1, LV_SCROLLBAR_MODE_OFF);

    //Hidden for widget file_browser_cb_1
    lv_obj_add_flag(ui->file_browser_cb_1, LV_OBJ_FLAG_HIDDEN);
    //Write codes file_browser_file_cont2
    ui->file_browser_file_cont2 = lv_obj_create(ui->file_browser_browser_cont);

    //Set style for file_browser_file_cont2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->file_browser_file_cont2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->file_browser_file_cont2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->file_browser_file_cont2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->file_browser_file_cont2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->file_browser_file_cont2, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->file_browser_file_cont2, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->file_browser_file_cont2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->file_browser_file_cont2, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui->file_browser_file_cont2, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->file_browser_file_cont2, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui->file_browser_file_cont2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui->file_browser_file_cont2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->file_browser_file_cont2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->file_browser_file_cont2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->file_browser_file_cont2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->file_browser_file_cont2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for file_browser_file_cont2. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui->file_browser_file_cont2, -1, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(ui->file_browser_file_cont2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui->file_browser_file_cont2, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_shadow_width(ui->file_browser_file_cont2, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_border_width(ui->file_browser_file_cont2, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(ui->file_browser_file_cont2, lv_color_make(0x21, 0xB4, 0xF6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->file_browser_file_cont2, 4, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->file_browser_file_cont2, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(ui->file_browser_file_cont2, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_pad_left(ui->file_browser_file_cont2, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_pad_right(ui->file_browser_file_cont2, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_pad_top(ui->file_browser_file_cont2, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_pad_bottom(ui->file_browser_file_cont2, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->file_browser_file_cont2, 230, 10);
    lv_obj_set_size(ui->file_browser_file_cont2, 200, 200);
    lv_obj_set_scrollbar_mode(ui->file_browser_file_cont2, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui->file_browser_file_cont2);
    //Write codes file_browser_img_2
    ui->file_browser_img_2 = lv_img_create(ui->file_browser_file_cont2);

    //Set style for file_browser_img_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->file_browser_img_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->file_browser_img_2, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->file_browser_img_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->file_browser_img_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->file_browser_img_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->file_browser_img_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->file_browser_img_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->file_browser_img_2, 4, 0);
    lv_obj_set_size(ui->file_browser_img_2, 192, 160);
    lv_obj_set_scrollbar_mode(ui->file_browser_img_2, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->file_browser_img_2, LV_OBJ_FLAG_EVENT_BUBBLE);
    //Write codes file_browser_lbl_3
    ui->file_browser_lbl_3 = lv_label_create(ui->file_browser_file_cont2);
    lv_label_set_text(ui->file_browser_lbl_3, "VID_0001.AVI");
    lv_label_set_long_mode(ui->file_browser_lbl_3, LV_LABEL_LONG_WRAP);

    //Set style for file_browser_lbl_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->file_browser_lbl_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->file_browser_lbl_3, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->file_browser_lbl_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->file_browser_lbl_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->file_browser_lbl_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->file_browser_lbl_3, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->file_browser_lbl_3, &lv_font_montserratMedium_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->file_browser_lbl_3, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->file_browser_lbl_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->file_browser_lbl_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->file_browser_lbl_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->file_browser_lbl_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->file_browser_lbl_3, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->file_browser_lbl_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->file_browser_lbl_3, 4, 161);
    lv_obj_set_size(ui->file_browser_lbl_3, 192, 30);
    lv_obj_set_scrollbar_mode(ui->file_browser_lbl_3, LV_SCROLLBAR_MODE_OFF);
    //Write codes file_browser_cb_2
    ui->file_browser_cb_2 = lv_checkbox_create(ui->file_browser_file_cont2);
    lv_checkbox_set_text(ui->file_browser_cb_2, "checkbox");

    //Set style for file_browser_cb_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->file_browser_cb_2, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->file_browser_cb_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->file_browser_cb_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->file_browser_cb_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->file_browser_cb_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui->file_browser_cb_2, lv_color_make(0xB4, 0x26, 0x1B), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->file_browser_cb_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui->file_browser_cb_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui->file_browser_cb_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->file_browser_cb_2, lv_color_make(0x0D, 0x30, 0x55), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->file_browser_cb_2, &lv_font_montserratMedium_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->file_browser_cb_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for file_browser_cb_2. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui->file_browser_cb_2, 6, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(ui->file_browser_cb_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui->file_browser_cb_2, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_shadow_width(ui->file_browser_cb_2, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_border_width(ui->file_browser_cb_2, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(ui->file_browser_cb_2, lv_color_make(0x21, 0xB4, 0xF6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->file_browser_cb_2, 4, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->file_browser_cb_2, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(ui->file_browser_cb_2, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_color(ui->file_browser_cb_2, lv_color_make(0x0D, 0x30, 0x55), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_font(ui->file_browser_cb_2, &lv_font_montserratMedium_24, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_letter_space(ui->file_browser_cb_2, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->file_browser_cb_2, 163, 4);
    lv_obj_set_size(ui->file_browser_cb_2, 30, 30);
    lv_obj_set_scrollbar_mode(ui->file_browser_cb_2, LV_SCROLLBAR_MODE_OFF);

    //Hidden for widget file_browser_cb_2
    lv_obj_add_flag(ui->file_browser_cb_2, LV_OBJ_FLAG_HIDDEN);
    //Write codes file_browser_file_cont3
    ui->file_browser_file_cont3 = lv_obj_create(ui->file_browser_browser_cont);

    //Set style for file_browser_file_cont3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->file_browser_file_cont3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->file_browser_file_cont3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->file_browser_file_cont3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->file_browser_file_cont3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->file_browser_file_cont3, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->file_browser_file_cont3, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->file_browser_file_cont3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->file_browser_file_cont3, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui->file_browser_file_cont3, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->file_browser_file_cont3, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui->file_browser_file_cont3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui->file_browser_file_cont3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->file_browser_file_cont3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->file_browser_file_cont3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->file_browser_file_cont3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->file_browser_file_cont3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for file_browser_file_cont3. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui->file_browser_file_cont3, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(ui->file_browser_file_cont3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui->file_browser_file_cont3, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_shadow_width(ui->file_browser_file_cont3, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_border_color(ui->file_browser_file_cont3, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_border_width(ui->file_browser_file_cont3, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_border_opa(ui->file_browser_file_cont3, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_border_side(ui->file_browser_file_cont3, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(ui->file_browser_file_cont3, lv_color_make(0x21, 0xB4, 0xF6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->file_browser_file_cont3, 4, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->file_browser_file_cont3, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(ui->file_browser_file_cont3, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_pad_left(ui->file_browser_file_cont3, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_pad_right(ui->file_browser_file_cont3, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_pad_top(ui->file_browser_file_cont3, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_pad_bottom(ui->file_browser_file_cont3, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->file_browser_file_cont3, 440, 10);
    lv_obj_set_size(ui->file_browser_file_cont3, 200, 200);
    lv_obj_set_scrollbar_mode(ui->file_browser_file_cont3, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui->file_browser_file_cont3);
    //Write codes file_browser_img_3
    ui->file_browser_img_3 = lv_img_create(ui->file_browser_file_cont3);

    //Set style for file_browser_img_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->file_browser_img_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->file_browser_img_3, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->file_browser_img_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->file_browser_img_3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->file_browser_img_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->file_browser_img_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->file_browser_img_3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->file_browser_img_3, 4, 0);
    lv_obj_set_size(ui->file_browser_img_3, 192, 160);
    lv_obj_set_scrollbar_mode(ui->file_browser_img_3, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->file_browser_img_3, LV_OBJ_FLAG_EVENT_BUBBLE);
    //Write codes file_browser_lbl_4
    ui->file_browser_lbl_4 = lv_label_create(ui->file_browser_file_cont3);
    lv_label_set_text(ui->file_browser_lbl_4, "VID_0001.AVI");
    lv_label_set_long_mode(ui->file_browser_lbl_4, LV_LABEL_LONG_WRAP);

    //Set style for file_browser_lbl_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->file_browser_lbl_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->file_browser_lbl_4, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->file_browser_lbl_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->file_browser_lbl_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->file_browser_lbl_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->file_browser_lbl_4, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->file_browser_lbl_4, &lv_font_montserratMedium_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->file_browser_lbl_4, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->file_browser_lbl_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->file_browser_lbl_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->file_browser_lbl_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->file_browser_lbl_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->file_browser_lbl_4, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->file_browser_lbl_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->file_browser_lbl_4, 4, 161);
    lv_obj_set_size(ui->file_browser_lbl_4, 192, 30);
    lv_obj_set_scrollbar_mode(ui->file_browser_lbl_4, LV_SCROLLBAR_MODE_OFF);
    //Write codes file_browser_cb_3
    ui->file_browser_cb_3 = lv_checkbox_create(ui->file_browser_file_cont3);
    lv_checkbox_set_text(ui->file_browser_cb_3, "checkbox");

    //Set style for file_browser_cb_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->file_browser_cb_3, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->file_browser_cb_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->file_browser_cb_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->file_browser_cb_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->file_browser_cb_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui->file_browser_cb_3, lv_color_make(0xB4, 0x26, 0x1B), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->file_browser_cb_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui->file_browser_cb_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui->file_browser_cb_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->file_browser_cb_3, lv_color_make(0x0D, 0x30, 0x55), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->file_browser_cb_3, &lv_font_montserratMedium_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->file_browser_cb_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for file_browser_cb_3. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui->file_browser_cb_3, 6, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(ui->file_browser_cb_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui->file_browser_cb_3, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_shadow_width(ui->file_browser_cb_3, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_border_width(ui->file_browser_cb_3, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(ui->file_browser_cb_3, lv_color_make(0x21, 0xB4, 0xF6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->file_browser_cb_3, 4, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->file_browser_cb_3, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(ui->file_browser_cb_3, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_color(ui->file_browser_cb_3, lv_color_make(0x0D, 0x30, 0x55), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_font(ui->file_browser_cb_3, &lv_font_montserratMedium_24, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_letter_space(ui->file_browser_cb_3, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->file_browser_cb_3, 163, 4);
    lv_obj_set_size(ui->file_browser_cb_3, 30, 30);
    lv_obj_set_scrollbar_mode(ui->file_browser_cb_3, LV_SCROLLBAR_MODE_OFF);

    //Hidden for widget file_browser_cb_3
    lv_obj_add_flag(ui->file_browser_cb_3, LV_OBJ_FLAG_HIDDEN);
    //Write codes file_browser_file_cont4
    ui->file_browser_file_cont4 = lv_obj_create(ui->file_browser_browser_cont);

    //Set style for file_browser_file_cont4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->file_browser_file_cont4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->file_browser_file_cont4, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->file_browser_file_cont4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->file_browser_file_cont4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->file_browser_file_cont4, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->file_browser_file_cont4, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->file_browser_file_cont4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->file_browser_file_cont4, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui->file_browser_file_cont4, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->file_browser_file_cont4, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui->file_browser_file_cont4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui->file_browser_file_cont4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->file_browser_file_cont4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->file_browser_file_cont4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->file_browser_file_cont4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->file_browser_file_cont4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for file_browser_file_cont4. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui->file_browser_file_cont4, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(ui->file_browser_file_cont4, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui->file_browser_file_cont4, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_shadow_width(ui->file_browser_file_cont4, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_border_color(ui->file_browser_file_cont4, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_border_width(ui->file_browser_file_cont4, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_border_opa(ui->file_browser_file_cont4, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_border_side(ui->file_browser_file_cont4, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(ui->file_browser_file_cont4, lv_color_make(0x21, 0xB4, 0xF6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->file_browser_file_cont4, 4, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->file_browser_file_cont4, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(ui->file_browser_file_cont4, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_pad_left(ui->file_browser_file_cont4, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_pad_right(ui->file_browser_file_cont4, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_pad_top(ui->file_browser_file_cont4, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_pad_bottom(ui->file_browser_file_cont4, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->file_browser_file_cont4, 20, 220);
    lv_obj_set_size(ui->file_browser_file_cont4, 200, 200);
    lv_obj_set_scrollbar_mode(ui->file_browser_file_cont4, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui->file_browser_file_cont4);
    //Write codes file_browser_img_4
    ui->file_browser_img_4 = lv_img_create(ui->file_browser_file_cont4);

    //Set style for file_browser_img_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->file_browser_img_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->file_browser_img_4, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->file_browser_img_4, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->file_browser_img_4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->file_browser_img_4, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->file_browser_img_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->file_browser_img_4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->file_browser_img_4, 4, 0);
    lv_obj_set_size(ui->file_browser_img_4, 192, 160);
    lv_obj_set_scrollbar_mode(ui->file_browser_img_4, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->file_browser_img_4, LV_OBJ_FLAG_EVENT_BUBBLE);
    //Write codes file_browser_lbl_5
    ui->file_browser_lbl_5 = lv_label_create(ui->file_browser_file_cont4);
    lv_label_set_text(ui->file_browser_lbl_5, "VID_0001.AVI");
    lv_label_set_long_mode(ui->file_browser_lbl_5, LV_LABEL_LONG_WRAP);

    //Set style for file_browser_lbl_5. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->file_browser_lbl_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->file_browser_lbl_5, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->file_browser_lbl_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->file_browser_lbl_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->file_browser_lbl_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->file_browser_lbl_5, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->file_browser_lbl_5, &lv_font_montserratMedium_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->file_browser_lbl_5, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->file_browser_lbl_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->file_browser_lbl_5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->file_browser_lbl_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->file_browser_lbl_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->file_browser_lbl_5, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->file_browser_lbl_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->file_browser_lbl_5, 4, 161);
    lv_obj_set_size(ui->file_browser_lbl_5, 192, 30);
    lv_obj_set_scrollbar_mode(ui->file_browser_lbl_5, LV_SCROLLBAR_MODE_OFF);
    //Write codes file_browser_cb_4
    ui->file_browser_cb_4 = lv_checkbox_create(ui->file_browser_file_cont4);
    lv_checkbox_set_text(ui->file_browser_cb_4, "checkbox");

    //Set style for file_browser_cb_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->file_browser_cb_4, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->file_browser_cb_4, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->file_browser_cb_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->file_browser_cb_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->file_browser_cb_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui->file_browser_cb_4, lv_color_make(0xB4, 0x26, 0x1B), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->file_browser_cb_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui->file_browser_cb_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui->file_browser_cb_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->file_browser_cb_4, lv_color_make(0x0D, 0x30, 0x55), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->file_browser_cb_4, &lv_font_montserratMedium_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->file_browser_cb_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for file_browser_cb_4. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui->file_browser_cb_4, 6, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(ui->file_browser_cb_4, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui->file_browser_cb_4, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_shadow_width(ui->file_browser_cb_4, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_border_width(ui->file_browser_cb_4, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(ui->file_browser_cb_4, lv_color_make(0x21, 0xB4, 0xF6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->file_browser_cb_4, 4, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->file_browser_cb_4, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(ui->file_browser_cb_4, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_color(ui->file_browser_cb_4, lv_color_make(0x0D, 0x30, 0x55), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_font(ui->file_browser_cb_4, &lv_font_montserratMedium_24, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_letter_space(ui->file_browser_cb_4, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->file_browser_cb_4, 163, 4);
    lv_obj_set_size(ui->file_browser_cb_4, 30, 30);
    lv_obj_set_scrollbar_mode(ui->file_browser_cb_4, LV_SCROLLBAR_MODE_OFF);

    //Hidden for widget file_browser_cb_4
    lv_obj_add_flag(ui->file_browser_cb_4, LV_OBJ_FLAG_HIDDEN);
    //Write codes file_browser_file_cont5
    ui->file_browser_file_cont5 = lv_obj_create(ui->file_browser_browser_cont);

    //Set style for file_browser_file_cont5. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->file_browser_file_cont5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->file_browser_file_cont5, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->file_browser_file_cont5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->file_browser_file_cont5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->file_browser_file_cont5, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->file_browser_file_cont5, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->file_browser_file_cont5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->file_browser_file_cont5, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui->file_browser_file_cont5, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->file_browser_file_cont5, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui->file_browser_file_cont5, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui->file_browser_file_cont5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->file_browser_file_cont5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->file_browser_file_cont5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->file_browser_file_cont5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->file_browser_file_cont5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for file_browser_file_cont5. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui->file_browser_file_cont5, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(ui->file_browser_file_cont5, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui->file_browser_file_cont5, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_shadow_width(ui->file_browser_file_cont5, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_border_color(ui->file_browser_file_cont5, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_border_width(ui->file_browser_file_cont5, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_border_opa(ui->file_browser_file_cont5, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_border_side(ui->file_browser_file_cont5, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(ui->file_browser_file_cont5, lv_color_make(0x21, 0xB4, 0xF6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->file_browser_file_cont5, 4, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->file_browser_file_cont5, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(ui->file_browser_file_cont5, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_pad_left(ui->file_browser_file_cont5, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_pad_right(ui->file_browser_file_cont5, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_pad_top(ui->file_browser_file_cont5, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_pad_bottom(ui->file_browser_file_cont5, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->file_browser_file_cont5, 230, 220);
    lv_obj_set_size(ui->file_browser_file_cont5, 200, 200);
    lv_obj_set_scrollbar_mode(ui->file_browser_file_cont5, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui->file_browser_file_cont5);
    //Write codes file_browser_img_5
    ui->file_browser_img_5 = lv_img_create(ui->file_browser_file_cont5);

    //Set style for file_browser_img_5. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->file_browser_img_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->file_browser_img_5, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->file_browser_img_5, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->file_browser_img_5, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->file_browser_img_5, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->file_browser_img_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->file_browser_img_5, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->file_browser_img_5, 4, 0);
    lv_obj_set_size(ui->file_browser_img_5, 192, 160);
    lv_obj_set_scrollbar_mode(ui->file_browser_img_5, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->file_browser_img_5, LV_OBJ_FLAG_EVENT_BUBBLE);
    //Write codes file_browser_lbl_6
    ui->file_browser_lbl_6 = lv_label_create(ui->file_browser_file_cont5);
    lv_label_set_text(ui->file_browser_lbl_6, "VID_0001.AVI");
    lv_label_set_long_mode(ui->file_browser_lbl_6, LV_LABEL_LONG_WRAP);

    //Set style for file_browser_lbl_6. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->file_browser_lbl_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->file_browser_lbl_6, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->file_browser_lbl_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->file_browser_lbl_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->file_browser_lbl_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->file_browser_lbl_6, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->file_browser_lbl_6, &lv_font_montserratMedium_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->file_browser_lbl_6, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->file_browser_lbl_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->file_browser_lbl_6, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->file_browser_lbl_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->file_browser_lbl_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->file_browser_lbl_6, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->file_browser_lbl_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->file_browser_lbl_6, 4, 161);
    lv_obj_set_size(ui->file_browser_lbl_6, 192, 30);
    lv_obj_set_scrollbar_mode(ui->file_browser_lbl_6, LV_SCROLLBAR_MODE_OFF);
    //Write codes file_browser_cb_5
    ui->file_browser_cb_5 = lv_checkbox_create(ui->file_browser_file_cont5);
    lv_checkbox_set_text(ui->file_browser_cb_5, "checkbox");

    //Set style for file_browser_cb_5. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->file_browser_cb_5, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->file_browser_cb_5, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->file_browser_cb_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->file_browser_cb_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->file_browser_cb_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui->file_browser_cb_5, lv_color_make(0xB4, 0x26, 0x1B), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->file_browser_cb_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui->file_browser_cb_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui->file_browser_cb_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->file_browser_cb_5, lv_color_make(0x0D, 0x30, 0x55), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->file_browser_cb_5, &lv_font_montserratMedium_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->file_browser_cb_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for file_browser_cb_5. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui->file_browser_cb_5, 6, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(ui->file_browser_cb_5, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui->file_browser_cb_5, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_shadow_width(ui->file_browser_cb_5, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_border_width(ui->file_browser_cb_5, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(ui->file_browser_cb_5, lv_color_make(0x21, 0xB4, 0xF6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->file_browser_cb_5, 4, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->file_browser_cb_5, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(ui->file_browser_cb_5, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_color(ui->file_browser_cb_5, lv_color_make(0x0D, 0x30, 0x55), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_font(ui->file_browser_cb_5, &lv_font_montserratMedium_24, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_letter_space(ui->file_browser_cb_5, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->file_browser_cb_5, 163, 4);
    lv_obj_set_size(ui->file_browser_cb_5, 30, 30);
    lv_obj_set_scrollbar_mode(ui->file_browser_cb_5, LV_SCROLLBAR_MODE_OFF);

    //Hidden for widget file_browser_cb_5
    lv_obj_add_flag(ui->file_browser_cb_5, LV_OBJ_FLAG_HIDDEN);
    //Write codes file_browser_file_cont6
    ui->file_browser_file_cont6 = lv_obj_create(ui->file_browser_browser_cont);

    //Set style for file_browser_file_cont6. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->file_browser_file_cont6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->file_browser_file_cont6, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->file_browser_file_cont6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->file_browser_file_cont6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->file_browser_file_cont6, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->file_browser_file_cont6, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->file_browser_file_cont6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->file_browser_file_cont6, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui->file_browser_file_cont6, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->file_browser_file_cont6, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui->file_browser_file_cont6, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui->file_browser_file_cont6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->file_browser_file_cont6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->file_browser_file_cont6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->file_browser_file_cont6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->file_browser_file_cont6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for file_browser_file_cont6. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui->file_browser_file_cont6, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(ui->file_browser_file_cont6, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui->file_browser_file_cont6, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_shadow_width(ui->file_browser_file_cont6, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_border_color(ui->file_browser_file_cont6, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_border_width(ui->file_browser_file_cont6, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_border_opa(ui->file_browser_file_cont6, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_border_side(ui->file_browser_file_cont6, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(ui->file_browser_file_cont6, lv_color_make(0x21, 0xB4, 0xF6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->file_browser_file_cont6, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->file_browser_file_cont6, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(ui->file_browser_file_cont6, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_pad_left(ui->file_browser_file_cont6, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_pad_right(ui->file_browser_file_cont6, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_pad_top(ui->file_browser_file_cont6, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_pad_bottom(ui->file_browser_file_cont6, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->file_browser_file_cont6, 440, 220);
    lv_obj_set_size(ui->file_browser_file_cont6, 200, 200);
    lv_obj_set_scrollbar_mode(ui->file_browser_file_cont6, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui->file_browser_file_cont6);
    //Write codes file_browser_img_6
    ui->file_browser_img_6 = lv_img_create(ui->file_browser_file_cont6);

    //Set style for file_browser_img_6. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->file_browser_img_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->file_browser_img_6, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->file_browser_img_6, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->file_browser_img_6, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->file_browser_img_6, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->file_browser_img_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->file_browser_img_6, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->file_browser_img_6, 4, 0);
    lv_obj_set_size(ui->file_browser_img_6, 192, 160);
    lv_obj_set_scrollbar_mode(ui->file_browser_img_6, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->file_browser_img_6, LV_OBJ_FLAG_EVENT_BUBBLE);
    //Write codes file_browser_lbl_7
    ui->file_browser_lbl_7 = lv_label_create(ui->file_browser_file_cont6);
    lv_label_set_text(ui->file_browser_lbl_7, "VID_0001.AVI");
    lv_label_set_long_mode(ui->file_browser_lbl_7, LV_LABEL_LONG_WRAP);

    //Set style for file_browser_lbl_7. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->file_browser_lbl_7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->file_browser_lbl_7, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->file_browser_lbl_7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->file_browser_lbl_7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->file_browser_lbl_7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->file_browser_lbl_7, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->file_browser_lbl_7, &lv_font_montserratMedium_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->file_browser_lbl_7, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->file_browser_lbl_7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->file_browser_lbl_7, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->file_browser_lbl_7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->file_browser_lbl_7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->file_browser_lbl_7, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->file_browser_lbl_7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->file_browser_lbl_7, 4, 161);
    lv_obj_set_size(ui->file_browser_lbl_7, 192, 30);
    lv_obj_set_scrollbar_mode(ui->file_browser_lbl_7, LV_SCROLLBAR_MODE_OFF);
    //Write codes file_browser_cb_6
    ui->file_browser_cb_6 = lv_checkbox_create(ui->file_browser_file_cont6);
    lv_checkbox_set_text(ui->file_browser_cb_6, "checkbox");

    //Set style for file_browser_cb_6. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->file_browser_cb_6, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->file_browser_cb_6, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->file_browser_cb_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->file_browser_cb_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->file_browser_cb_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui->file_browser_cb_6, lv_color_make(0xB4, 0x26, 0x1B), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->file_browser_cb_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui->file_browser_cb_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui->file_browser_cb_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->file_browser_cb_6, lv_color_make(0x0D, 0x30, 0x55), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->file_browser_cb_6, &lv_font_montserratMedium_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->file_browser_cb_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for file_browser_cb_6. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui->file_browser_cb_6, 6, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(ui->file_browser_cb_6, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui->file_browser_cb_6, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_shadow_width(ui->file_browser_cb_6, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_border_width(ui->file_browser_cb_6, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(ui->file_browser_cb_6, lv_color_make(0x21, 0xB4, 0xF6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->file_browser_cb_6, 4, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->file_browser_cb_6, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(ui->file_browser_cb_6, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_color(ui->file_browser_cb_6, lv_color_make(0x0D, 0x30, 0x55), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_font(ui->file_browser_cb_6, &lv_font_montserratMedium_24, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_letter_space(ui->file_browser_cb_6, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->file_browser_cb_6, 163, 4);
    lv_obj_set_size(ui->file_browser_cb_6, 30, 30);
    lv_obj_set_scrollbar_mode(ui->file_browser_cb_6, LV_SCROLLBAR_MODE_OFF);

    //Hidden for widget file_browser_cb_6
    lv_obj_add_flag(ui->file_browser_cb_6, LV_OBJ_FLAG_HIDDEN);
    lv_obj_update_layout(ui->file_browser);
    ui->file_browser_del = false;

    //Init events for screen
    events_init_file_browser(ui);
    return ui->file_browser;
}
void unload_scr_file_browser(lv_ui *ui)
{
    ui->file_browser_del = true;
}
