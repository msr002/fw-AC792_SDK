/*Generate Code, Do NOT Edit!*/
#include "lvgl.h"
#include <stdio.h>
#include <stdlib.h>
#include "../gui_guider.h"
#include "../gui_events/events_init.h"
#include "../gui_events/callback_handler.h"
#include "../gui_timelines/gui_timelines.h"
#include "../../custom/custom.h"


lv_obj_t *setup_scr_unpair(lv_ui *ui)
{
    //Write codes unpair
    ui->unpair = lv_obj_create(NULL);
    lv_group_t *def_group = lv_group_get_default();

    //Set style for unpair. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui->unpair, lv_color_make(0xE2, 0xDC, 0xDC), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->unpair, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->unpair, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(ui->unpair, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui->unpair);
    //Write codes unpair_lbl_1
    ui->unpair_lbl_1 = lv_label_create(ui->unpair);
    lv_label_set_text(ui->unpair_lbl_1, "Unpair success ! \n\nPlease click to return");
    lv_label_set_long_mode(ui->unpair_lbl_1, LV_LABEL_LONG_WRAP);

    //Set style for unpair_lbl_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->unpair_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->unpair_lbl_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->unpair_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->unpair_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->unpair_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->unpair_lbl_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->unpair_lbl_1, &lv_font_montserratMedium_36, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->unpair_lbl_1, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->unpair_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->unpair_lbl_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->unpair_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->unpair_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->unpair_lbl_1, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->unpair_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->unpair_lbl_1, 6, 150);
    lv_obj_set_size(ui->unpair_lbl_1, 788, 269);
    lv_obj_set_scrollbar_mode(ui->unpair_lbl_1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_update_layout(ui->unpair);
    ui->unpair_del = false;

    //Init events for screen
    events_init_unpair(ui);
    return ui->unpair;
}
void unload_scr_unpair(lv_ui *ui)
{
    ui->unpair_del = true;
}
