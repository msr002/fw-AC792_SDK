/*Generate Code, Do NOT Edit!*/
#include "lvgl.h"
#include <stdio.h>
#include <stdlib.h>
#include "../gui_guider.h"
#include "../gui_events/events_init.h"
#include "../gui_events/callback_handler.h"
#include "../gui_timelines/gui_timelines.h"
#include "../../custom/custom.h"


lv_obj_t *setup_scr_pairing(lv_ui *ui)
{
    //Write codes pairing
    ui->pairing = lv_obj_create(NULL);
    lv_group_t *def_group = lv_group_get_default();

    //Set style for pairing. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui->pairing, lv_color_make(0xE2, 0xDC, 0xDC), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->pairing, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->pairing, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(ui->pairing, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui->pairing);
    //Write codes pairing_lbl_1
    ui->pairing_lbl_1 = lv_label_create(ui->pairing);
    lv_label_set_text(ui->pairing_lbl_1, "Pairing...\n\nPlease press the pairing button of the camera and Make sure the camera is within 30cm");
    lv_label_set_long_mode(ui->pairing_lbl_1, LV_LABEL_LONG_WRAP);

    //Set style for pairing_lbl_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->pairing_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->pairing_lbl_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->pairing_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->pairing_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->pairing_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->pairing_lbl_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->pairing_lbl_1, &lv_font_montserratMedium_36, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->pairing_lbl_1, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->pairing_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->pairing_lbl_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->pairing_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->pairing_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->pairing_lbl_1, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->pairing_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->pairing_lbl_1, 4, 150);
    lv_obj_set_size(ui->pairing_lbl_1, 788, 269);
    lv_obj_set_scrollbar_mode(ui->pairing_lbl_1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_update_layout(ui->pairing);
    ui->pairing_del = false;

    //Init events for screen
    events_init_pairing(ui);
    return ui->pairing;
}
void unload_scr_pairing(lv_ui *ui)
{
    ui->pairing_del = true;
}
