/*Generate Code, Do NOT Edit!*/
#include "lvgl.h"
#include <stdio.h>
#include <stdlib.h>
#include "../gui_guider.h"
#include "../gui_events/events_init.h"
#include "../gui_events/callback_handler.h"
#include "../gui_timelines/gui_timelines.h"
#include "../../custom/custom.h"


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
    lv_obj_set_pos(ui->video_play_imgbtn_1, 24, 22);
    lv_obj_set_size(ui->video_play_imgbtn_1, 64, 64);
    lv_obj_set_scrollbar_mode(ui->video_play_imgbtn_1, LV_SCROLLBAR_MODE_OFF);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_imgbtn_set_src(ui->video_play_imgbtn_1, LV_IMGBTN_STATE_RELEASED, NULL, "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\back.png", NULL);
    lv_imgbtn_set_src(ui->video_play_imgbtn_1, LV_IMGBTN_STATE_PRESSED, NULL, "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\back.png", NULL);
    lv_imgbtn_set_src(ui->video_play_imgbtn_1, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\back.png", NULL);
    lv_imgbtn_set_src(ui->video_play_imgbtn_1, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\back.png", NULL);
#else
    lv_imgbtn_set_src(ui->video_play_imgbtn_1, LV_IMGBTN_STATE_RELEASED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/55000003.zip", NULL);
    lv_imgbtn_set_src(ui->video_play_imgbtn_1, LV_IMGBTN_STATE_PRESSED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/55000003.zip", NULL);
    lv_imgbtn_set_src(ui->video_play_imgbtn_1, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/55000003.zip", NULL);
    lv_imgbtn_set_src(ui->video_play_imgbtn_1, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/55000003.zip", NULL);
#endif
    lv_obj_add_flag(ui->video_play_imgbtn_1, LV_OBJ_FLAG_CHECKABLE);
    ui->video_play_imgbtn_1_label = lv_label_create(ui->video_play_imgbtn_1);
    lv_label_set_text(ui->video_play_imgbtn_1_label, "");
    lv_obj_set_style_pad_all(ui->video_play_imgbtn_1, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->video_play_imgbtn_1_label, LV_ALIGN_CENTER, 0, 0);
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
