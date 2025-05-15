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
    lv_obj_set_style_bg_color(ui->home, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->home, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->home, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(ui->home, LV_SCROLLBAR_MODE_OFF);

    //Write codes home_video_1
    ui->home_video_1 = lv_ffmpeg_player_create(ui->home);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_ffmpeg_player_set_src(ui->home_video_1, "F:\\WL83_NEW\\wifi_video_master\\ui_prj\\wifi_soundbox_480x800\\import\\video\\jl.avi");
#else
    lv_ffmpeg_player_set_src(ui->home_video_1, "storage/sd0/C/bin/31000000.avi");
#endif
    lv_ffmpeg_player_set_auto_restart(ui->home_video_1, true);
    lv_ffmpeg_player_set_cmd(ui->home_video_1, LV_FFMPEG_PLAYER_CMD_START);
    lv_obj_set_pos(ui->home_video_1, 0, 0);
    lv_obj_set_size(ui->home_video_1, 480, 480);
    //Write codes home_lbl_1
    ui->home_lbl_1 = lv_label_create(ui->home);
    lv_label_set_text(ui->home_lbl_1, "Please insert SD card");
    lv_label_set_long_mode(ui->home_lbl_1, LV_LABEL_LONG_WRAP);

    //Set style for home_lbl_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->home_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->home_lbl_1, lv_color_make(0x21, 0x95, 0xF6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->home_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->home_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->home_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->home_lbl_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->home_lbl_1, &lv_font_montserratMedium_30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->home_lbl_1, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->home_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->home_lbl_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->home_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->home_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->home_lbl_1, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->home_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->home_lbl_1, 0, 150);
    lv_obj_set_size(ui->home_lbl_1, 480, 50);
    lv_obj_set_scrollbar_mode(ui->home_lbl_1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_update_layout(ui->home);
    ui->home_del = false;
    return ui->home;
}
void unload_scr_home(lv_ui *ui)
{
    ui->home_del = true;
}
