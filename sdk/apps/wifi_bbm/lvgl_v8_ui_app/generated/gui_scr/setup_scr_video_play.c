/*Generate Code, Do NOT Edit!*/
#include "lvgl.h"
#include <stdio.h>
#include <stdlib.h>
#include "../gui_guider.h"
#include "../gui_events/events_init.h"
#include "../gui_events/callback_handler.h"
#include "../gui_timelines/gui_timelines.h"
#include "../../custom/custom.h"

static const char *video_play_imglist_1_imgs[2] = {
#if LV_USE_GUIBUILDER_SIMULATOR
    "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\video_play.png",
    "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\video_pause.png"
#else
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/5500000c.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/5500000d.zip"
#endif
};

lv_obj_t *setup_scr_video_play(lv_ui *ui)
{
    //Write codes video_play
    ui->video_play = lv_obj_create(NULL);
    lv_group_t *def_group = lv_group_get_default();

    //Set style for video_play. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui->video_play, lv_color_make(0x55, 0xaa, 0xa5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_play, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->video_play, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(ui->video_play, LV_SCROLLBAR_MODE_OFF);
    //Write codes video_play_imgbtn_1
    ui->video_play_imgbtn_1 = lv_imgbtn_create(ui->video_play);

    //Set style for video_play_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->video_play_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->video_play_imgbtn_1, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_play_imgbtn_1, lv_color_make(0x55, 0xaa, 0xa5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_play_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->video_play_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->video_play_imgbtn_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->video_play_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->video_play_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->video_play_imgbtn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->video_play_imgbtn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->video_play_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->video_play_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for video_play_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui->video_play_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_clip_corner(ui->video_play_imgbtn_1, true, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(ui->video_play_imgbtn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui->video_play_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_shadow_width(ui->video_play_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(ui->video_play_imgbtn_1, lv_color_make(0x21, 0xB4, 0xF6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->video_play_imgbtn_1, 4, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->video_play_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(ui->video_play_imgbtn_1, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_color(ui->video_play_imgbtn_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_font(ui->video_play_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor(ui->video_play_imgbtn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor_opa(ui->video_play_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_opa(ui->video_play_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Set style for video_play_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_PRESSED
    lv_obj_set_style_radius(ui->video_play_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_clip_corner(ui->video_play_imgbtn_1, true, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->video_play_imgbtn_1, lv_color_make(0x55, 0xaa, 0xa5), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(ui->video_play_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->video_play_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->video_play_imgbtn_1, lv_color_make(0xFF, 0x33, 0xFF), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->video_play_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_recolor(ui->video_play_imgbtn_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_recolor_opa(ui->video_play_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->video_play_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_PRESSED);

    //Set style for video_play_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_CHECKED
    lv_obj_set_style_radius(ui->video_play_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_clip_corner(ui->video_play_imgbtn_1, true, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui->video_play_imgbtn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui->video_play_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->video_play_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->video_play_imgbtn_1, lv_color_make(0xFF, 0x33, 0xFF), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->video_play_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_recolor(ui->video_play_imgbtn_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_recolor_opa(ui->video_play_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->video_play_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_pos(ui->video_play_imgbtn_1, 699, 108);
    lv_obj_set_size(ui->video_play_imgbtn_1, 64, 64);
    lv_obj_set_scrollbar_mode(ui->video_play_imgbtn_1, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui->video_play_imgbtn_1);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_imgbtn_set_src(ui->video_play_imgbtn_1, LV_IMGBTN_STATE_RELEASED, NULL, "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\back_white.png", NULL);
    lv_imgbtn_set_src(ui->video_play_imgbtn_1, LV_IMGBTN_STATE_PRESSED, NULL, "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\back_white.png", NULL);
    lv_imgbtn_set_src(ui->video_play_imgbtn_1, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\back_white.png", NULL);
    lv_imgbtn_set_src(ui->video_play_imgbtn_1, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\back_white.png", NULL);
#else
    lv_imgbtn_set_src(ui->video_play_imgbtn_1, LV_IMGBTN_STATE_RELEASED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/5500000b.zip", NULL);
    lv_imgbtn_set_src(ui->video_play_imgbtn_1, LV_IMGBTN_STATE_PRESSED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/5500000b.zip", NULL);
    lv_imgbtn_set_src(ui->video_play_imgbtn_1, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/5500000b.zip", NULL);
    lv_imgbtn_set_src(ui->video_play_imgbtn_1, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/5500000b.zip", NULL);
#endif
    lv_obj_add_flag(ui->video_play_imgbtn_1, LV_OBJ_FLAG_CHECKABLE);
    ui->video_play_imgbtn_1_label = lv_label_create(ui->video_play_imgbtn_1);
    lv_label_set_text(ui->video_play_imgbtn_1_label, "");
    lv_obj_set_style_pad_all(ui->video_play_imgbtn_1, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->video_play_imgbtn_1_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes video_play_view_1
    ui->video_play_view_1 = lv_obj_create(ui->video_play);

    //Set style for video_play_view_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->video_play_view_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_play_view_1, lv_color_make(0x55, 0xaa, 0xa5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_play_view_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->video_play_view_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->video_play_view_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->video_play_view_1, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->video_play_view_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->video_play_view_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->video_play_view_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->video_play_view_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->video_play_view_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->video_play_view_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->video_play_view_1, 0, 401);
    lv_obj_set_size(ui->video_play_view_1, 800, 80);
    lv_obj_set_scrollbar_mode(ui->video_play_view_1, LV_SCROLLBAR_MODE_OFF);
    //Write codes video_play_imglist_1
    ui->video_play_imglist_1 = lv_imglist_create(ui->video_play_view_1);

    //Set style for video_play_imglist_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->video_play_imglist_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->video_play_imglist_1, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_play_imglist_1, lv_color_make(0x55, 0xaa, 0xa5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_play_imglist_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->video_play_imglist_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->video_play_imglist_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->video_play_imglist_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for video_play_imglist_1. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui->video_play_imglist_1, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_clip_corner(ui->video_play_imglist_1, true, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(ui->video_play_imglist_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui->video_play_imglist_1, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(ui->video_play_imglist_1, lv_color_make(0x21, 0xB4, 0xF6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->video_play_imglist_1, 4, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->video_play_imglist_1, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(ui->video_play_imglist_1, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor(ui->video_play_imglist_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor_opa(ui->video_play_imglist_1, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_opa(ui->video_play_imglist_1, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->video_play_imglist_1, 95, 22);
    lv_obj_set_size(ui->video_play_imglist_1, 48, 48);
    lv_obj_set_scrollbar_mode(ui->video_play_imglist_1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->video_play_imglist_1, LV_OBJ_FLAG_CLICKABLE);
    lv_group_add_obj(def_group, ui->video_play_imglist_1);
    lv_imglist_set_src(ui->video_play_imglist_1, (const void **) video_play_imglist_1_imgs, 2);
    lv_imglist_set_act(ui->video_play_imglist_1, 0);
    //Write codes video_play_imgbtn_3
    ui->video_play_imgbtn_3 = lv_imgbtn_create(ui->video_play_view_1);

    //Set style for video_play_imgbtn_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->video_play_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->video_play_imgbtn_3, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_play_imgbtn_3, lv_color_make(0x55, 0xaa, 0xa5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_play_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->video_play_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->video_play_imgbtn_3, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->video_play_imgbtn_3, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->video_play_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->video_play_imgbtn_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->video_play_imgbtn_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->video_play_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->video_play_imgbtn_3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for video_play_imgbtn_3. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui->video_play_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_clip_corner(ui->video_play_imgbtn_3, true, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(ui->video_play_imgbtn_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui->video_play_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_shadow_width(ui->video_play_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(ui->video_play_imgbtn_3, lv_color_make(0x21, 0xB4, 0xF6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->video_play_imgbtn_3, 4, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->video_play_imgbtn_3, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(ui->video_play_imgbtn_3, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_color(ui->video_play_imgbtn_3, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_font(ui->video_play_imgbtn_3, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor(ui->video_play_imgbtn_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor_opa(ui->video_play_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_opa(ui->video_play_imgbtn_3, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->video_play_imgbtn_3, 172, 22);
    lv_obj_set_size(ui->video_play_imgbtn_3, 48, 48);
    lv_obj_set_scrollbar_mode(ui->video_play_imgbtn_3, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui->video_play_imgbtn_3);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_imgbtn_set_src(ui->video_play_imgbtn_3, LV_IMGBTN_STATE_RELEASED, NULL, "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\skip_next.png", NULL);
#else
    lv_imgbtn_set_src(ui->video_play_imgbtn_3, LV_IMGBTN_STATE_RELEASED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/5500000e.zip", NULL);
#endif
    lv_obj_add_flag(ui->video_play_imgbtn_3, LV_OBJ_FLAG_CHECKABLE);
    ui->video_play_imgbtn_3_label = lv_label_create(ui->video_play_imgbtn_3);
    lv_label_set_text(ui->video_play_imgbtn_3_label, "");
    lv_obj_set_style_pad_all(ui->video_play_imgbtn_3, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->video_play_imgbtn_3_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes video_play_imgbtn_2
    ui->video_play_imgbtn_2 = lv_imgbtn_create(ui->video_play_view_1);

    //Set style for video_play_imgbtn_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->video_play_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->video_play_imgbtn_2, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_play_imgbtn_2, lv_color_make(0x55, 0xaa, 0xa5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_play_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->video_play_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->video_play_imgbtn_2, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->video_play_imgbtn_2, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->video_play_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->video_play_imgbtn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->video_play_imgbtn_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->video_play_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->video_play_imgbtn_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for video_play_imgbtn_2. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui->video_play_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_clip_corner(ui->video_play_imgbtn_2, true, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(ui->video_play_imgbtn_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui->video_play_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_shadow_width(ui->video_play_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(ui->video_play_imgbtn_2, lv_color_make(0x21, 0xB4, 0xF6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->video_play_imgbtn_2, 4, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->video_play_imgbtn_2, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(ui->video_play_imgbtn_2, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_color(ui->video_play_imgbtn_2, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_font(ui->video_play_imgbtn_2, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor(ui->video_play_imgbtn_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor_opa(ui->video_play_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_opa(ui->video_play_imgbtn_2, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->video_play_imgbtn_2, 20, 22);
    lv_obj_set_size(ui->video_play_imgbtn_2, 48, 48);
    lv_obj_set_scrollbar_mode(ui->video_play_imgbtn_2, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui->video_play_imgbtn_2);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_imgbtn_set_src(ui->video_play_imgbtn_2, LV_IMGBTN_STATE_RELEASED, NULL, "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\skip_previous.png", NULL);
#else
    lv_imgbtn_set_src(ui->video_play_imgbtn_2, LV_IMGBTN_STATE_RELEASED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/5500000f.zip", NULL);
#endif
    lv_obj_add_flag(ui->video_play_imgbtn_2, LV_OBJ_FLAG_CHECKABLE);
    ui->video_play_imgbtn_2_label = lv_label_create(ui->video_play_imgbtn_2);
    lv_label_set_text(ui->video_play_imgbtn_2_label, "");
    lv_obj_set_style_pad_all(ui->video_play_imgbtn_2, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->video_play_imgbtn_2_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes video_play_bar_1
    ui->video_play_bar_1 = lv_bar_create(ui->video_play_view_1);

    //Set style for video_play_bar_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->video_play_bar_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_play_bar_1, lv_color_make(0xEC, 0xF0, 0xF5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_play_bar_1, 77, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->video_play_bar_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for video_play_bar_1. Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->video_play_bar_1, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_play_bar_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_play_bar_1, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->video_play_bar_1, 0, 0);
    lv_obj_set_size(ui->video_play_bar_1, 800, 12);
    lv_obj_set_scrollbar_mode(ui->video_play_bar_1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_anim_time(ui->video_play_bar_1, 1000, 0);
    lv_bar_set_mode(ui->video_play_bar_1, LV_BAR_MODE_NORMAL);
    lv_bar_set_range(ui->video_play_bar_1, 0, 100);
    lv_bar_set_value(ui->video_play_bar_1, 0, LV_ANIM_OFF);
    lv_obj_update_layout(ui->video_play);
    ui->video_play_del = false;

    //Init events for screen
    events_init_video_play(ui);
    return ui->video_play;
}
void unload_scr_video_play(lv_ui *ui)
{
    ui->video_play_del = true;
}
