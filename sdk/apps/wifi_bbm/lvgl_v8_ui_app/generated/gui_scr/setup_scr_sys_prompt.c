/*Generate Code, Do NOT Edit!*/
#include "lvgl.h"
#include <stdio.h>
#include <stdlib.h>
#include "../gui_guider.h"
#include "../gui_events/events_init.h"
#include "../gui_events/callback_handler.h"
#include "../gui_timelines/gui_timelines.h"
#include "../../custom/custom.h"


lv_obj_t *setup_scr_sys_prompt(lv_ui *ui)
{
    if (lv_obj_is_valid(ui->sys_prompt)) {
        lv_obj_del(ui->sys_prompt);
    }
    //Write codes sys_prompt
    ui->sys_prompt = lv_obj_create(lv_layer_top());
    lv_group_t *def_group = lv_group_get_default();

    //Set style for sys_prompt. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui->sys_prompt, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->sys_prompt, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->sys_prompt, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_size(ui->sys_prompt, 800, 480);
    lv_obj_set_scrollbar_mode(ui->sys_prompt, LV_SCROLLBAR_MODE_OFF);
    //Write codes sys_prompt_view_1
    ui->sys_prompt_view_1 = lv_obj_create(ui->sys_prompt);

    //Set style for sys_prompt_view_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->sys_prompt_view_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->sys_prompt_view_1, lv_color_make(0x33, 0x30, 0x30), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->sys_prompt_view_1, 217, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->sys_prompt_view_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->sys_prompt_view_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->sys_prompt_view_1, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->sys_prompt_view_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->sys_prompt_view_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui->sys_prompt_view_1, lv_color_make(0x02, 0x6C, 0xC0), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->sys_prompt_view_1, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui->sys_prompt_view_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui->sys_prompt_view_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->sys_prompt_view_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->sys_prompt_view_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->sys_prompt_view_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->sys_prompt_view_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_prompt_view_1, 238, 137);
    lv_obj_set_size(ui->sys_prompt_view_1, 345, 194);
    lv_obj_set_scrollbar_mode(ui->sys_prompt_view_1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->sys_prompt_view_1, LV_OBJ_FLAG_EVENT_BUBBLE);
    //Write codes sys_prompt_lbl_1
    ui->sys_prompt_lbl_1 = lv_label_create(ui->sys_prompt_view_1);
    lv_label_set_text(ui->sys_prompt_lbl_1, "Connect Error !");
    lv_label_set_long_mode(ui->sys_prompt_lbl_1, LV_LABEL_LONG_WRAP);

    //Set style for sys_prompt_lbl_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->sys_prompt_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->sys_prompt_lbl_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->sys_prompt_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->sys_prompt_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->sys_prompt_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->sys_prompt_lbl_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->sys_prompt_lbl_1, &lv_font_montserratMedium_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->sys_prompt_lbl_1, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->sys_prompt_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->sys_prompt_lbl_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->sys_prompt_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->sys_prompt_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->sys_prompt_lbl_1, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->sys_prompt_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_prompt_lbl_1, 159, 51);
    lv_obj_set_size(ui->sys_prompt_lbl_1, 187, 125);
    lv_obj_set_scrollbar_mode(ui->sys_prompt_lbl_1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->sys_prompt_lbl_1, LV_OBJ_FLAG_EVENT_BUBBLE);
    //Write codes sys_prompt_img_1
    ui->sys_prompt_img_1 = lv_img_create(ui->sys_prompt_view_1);

    //Set style for sys_prompt_img_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->sys_prompt_img_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->sys_prompt_img_1, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->sys_prompt_img_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->sys_prompt_img_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->sys_prompt_img_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->sys_prompt_img_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->sys_prompt_img_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->sys_prompt_img_1, 16, 26);
    lv_obj_set_size(ui->sys_prompt_img_1, 128, 128);
    lv_obj_set_scrollbar_mode(ui->sys_prompt_img_1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->sys_prompt_img_1, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_add_flag(ui->sys_prompt_img_1, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_img_set_src(ui->sys_prompt_img_1, "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\warn.png");
#else
    lv_img_set_src(ui->sys_prompt_img_1, "mnt/sdfile/EXT_RESERVED/uipackres/ui/55000010.zip");
#endif
    lv_img_set_pivot(ui->sys_prompt_img_1, 0, 0);
    lv_img_set_angle(ui->sys_prompt_img_1, 0);
    lv_img_set_zoom(ui->sys_prompt_img_1, 256);
    lv_obj_update_layout(ui->sys_prompt);
    ui->sys_prompt_del = false;

    //Init events for screen
    events_init_sys_prompt(ui);
    return ui->sys_prompt;
}
void unload_scr_sys_prompt(lv_ui *ui)
{
    ui->sys_prompt_del = true;
}
