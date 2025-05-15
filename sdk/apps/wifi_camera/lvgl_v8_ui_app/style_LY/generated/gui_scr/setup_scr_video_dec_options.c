#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE
/*Generate Code, Do NOT Edit!*/
#include "lvgl.h"
#if LV_USE_GUIBUILDER_SIMULATOR
#include <stdio.h>
#endif
#include <stdlib.h>
#include "../gui_guider.h"
#include "../gui_events/events_init.h"
#include "../gui_events/callback_handler.h"
#include "../gui_events/i18n_handler.h"
#include "../gui_timelines/gui_timelines.h"
#include "../../custom/custom.h"


lv_obj_t *setup_scr_video_dec_options(lv_ui *ui)
{
    if (lv_obj_is_valid(ui->video_dec_options)) {
        lv_obj_del(ui->video_dec_options);
    }
    //Write codes video_dec_options
    ui->video_dec_options = lv_obj_create(lv_layer_top());
    lv_group_t *def_group = lv_group_get_default();

    //Set style for video_dec_options. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->video_dec_options, &gui_scr_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_dec_options, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->video_dec_options, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->video_dec_options, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->video_dec_options, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->video_dec_options, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->video_dec_options, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->video_dec_options, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(ui->video_dec_options, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(ui->video_dec_options, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_size(ui->video_dec_options, 800, 480);
    lv_obj_set_scrollbar_mode(ui->video_dec_options, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(ui->video_dec_options, LV_OBJ_FLAG_CLICKABLE);
    //Write codes video_dec_options_view_1
    ui->video_dec_options_view_1 = lv_obj_create(ui->video_dec_options);

    //Set style for video_dec_options_view_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->video_dec_options_view_1, &gui_cont_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->video_dec_options_view_1, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_dec_options_view_1, lv_color_make(0x3D, 0x3B, 0x3B), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_dec_options_view_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->video_dec_options_view_1, lv_color_make(0x3D, 0x3B, 0x3B), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->video_dec_options_view_1, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->video_dec_options_view_1, 199, 100);
    lv_obj_set_size(ui->video_dec_options_view_1, 390, 250);
    lv_obj_set_scrollbar_mode(ui->video_dec_options_view_1, LV_SCROLLBAR_MODE_OFF);
    //Write codes video_dec_options_lbl_1
    ui->video_dec_options_lbl_1 = lv_label_create(ui->video_dec_options_view_1);
    lv_label_set_long_mode(ui->video_dec_options_lbl_1, LV_LABEL_LONG_WRAP);

    //Set style for video_dec_options_lbl_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->video_dec_options_lbl_1, &gui_label_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_dec_options_lbl_1, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->video_dec_options_lbl_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->video_dec_options_lbl_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->video_dec_options_lbl_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->video_dec_options_lbl_1, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->video_dec_options_lbl_1, 15, 0);
    lv_obj_set_size(ui->video_dec_options_lbl_1, 360, 165);
    lv_obj_set_scrollbar_mode(ui->video_dec_options_lbl_1, LV_SCROLLBAR_MODE_OFF);
    //Write codes video_dec_options_btn_1
    ui->video_dec_options_btn_1 = lv_btn_create(ui->video_dec_options_view_1);

    //Set style for video_dec_options_btn_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->video_dec_options_btn_1, &gui_btn_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_dec_options_btn_1, lv_color_make(0x74, 0x72, 0x72), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->video_dec_options_btn_1, lv_color_make(0x74, 0x72, 0x72), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->video_dec_options_btn_1, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->video_dec_options_btn_1, LV_BORDER_SIDE_BOTTOM | LV_BORDER_SIDE_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->video_dec_options_btn_1, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for video_dec_options_btn_1. Part: LV_PART_MAIN, State: LV_STATE_FOCUSED
    lv_obj_add_style(ui->video_dec_options_btn_1, &gui_btn_main_focused_style, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_pos(ui->video_dec_options_btn_1, 14, 132);
    lv_obj_set_size(ui->video_dec_options_btn_1, 181, 72);
    lv_obj_set_scrollbar_mode(ui->video_dec_options_btn_1, LV_SCROLLBAR_MODE_OFF);
    ui->video_dec_options_btn_1_label = lv_label_create(ui->video_dec_options_btn_1);
    lv_obj_set_style_pad_all(ui->video_dec_options_btn_1, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->video_dec_options_btn_1_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes video_dec_options_btn_2
    ui->video_dec_options_btn_2 = lv_btn_create(ui->video_dec_options_view_1);

    //Set style for video_dec_options_btn_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_add_style(ui->video_dec_options_btn_2, &gui_btn_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->video_dec_options_btn_2, lv_color_make(0x74, 0x72, 0x72), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->video_dec_options_btn_2, lv_color_make(0x74, 0x72, 0x72), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->video_dec_options_btn_2, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->video_dec_options_btn_2, LV_BORDER_SIDE_BOTTOM | LV_BORDER_SIDE_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->video_dec_options_btn_2, lv_color_make(0xFF, 0xFF, 0xFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for video_dec_options_btn_2. Part: LV_PART_MAIN, State: LV_STATE_FOCUSED
    lv_obj_add_style(ui->video_dec_options_btn_2, &gui_btn_main_focused_style, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_pos(ui->video_dec_options_btn_2, 195, 132);
    lv_obj_set_size(ui->video_dec_options_btn_2, 181, 72);
    lv_obj_set_scrollbar_mode(ui->video_dec_options_btn_2, LV_SCROLLBAR_MODE_OFF);
    ui->video_dec_options_btn_2_label = lv_label_create(ui->video_dec_options_btn_2);
    lv_obj_set_style_pad_all(ui->video_dec_options_btn_2, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->video_dec_options_btn_2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_update_layout(ui->video_dec_options);
    ui->video_dec_options_del = false;
    i18n_refresh_texts("video_dec_options");

    //Init events for screen
    events_init_video_dec_options(ui);
    return ui->video_dec_options;
}
void unload_scr_video_dec_options(lv_ui *ui)
{
    ui->video_dec_options_del = true;
}

#endif
