/*Generate Code, Do NOT Edit!*/
#include "lvgl.h"
#include <stdio.h>
#include <stdlib.h>
#include "../gui_guider.h"
#include "../gui_events/events_init.h"
#include "../gui_events/callback_handler.h"
#include "../gui_timelines/gui_timelines.h"
#include "../../custom/custom.h"


lv_obj_t *setup_scr_rt_stream(lv_ui *ui)
{
    //Write codes rt_stream
    ui->rt_stream = lv_obj_create(NULL);
    lv_group_t *def_group = lv_group_get_default();

    //Set style for rt_stream. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui->rt_stream, lv_color_make(0x55, 0xaa, 0xa5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->rt_stream, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->rt_stream, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(ui->rt_stream, LV_SCROLLBAR_MODE_OFF);
    //Write codes rt_stream_imgbtn_1
    ui->rt_stream_imgbtn_1 = lv_imgbtn_create(ui->rt_stream);

    //Set style for rt_stream_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->rt_stream_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->rt_stream_imgbtn_1, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->rt_stream_imgbtn_1, lv_color_make(0x55, 0xaa, 0xa5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->rt_stream_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->rt_stream_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->rt_stream_imgbtn_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->rt_stream_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->rt_stream_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->rt_stream_imgbtn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->rt_stream_imgbtn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->rt_stream_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->rt_stream_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for rt_stream_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_PRESSED
    lv_obj_set_style_radius(ui->rt_stream_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_clip_corner(ui->rt_stream_imgbtn_1, true, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->rt_stream_imgbtn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(ui->rt_stream_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->rt_stream_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->rt_stream_imgbtn_1, lv_color_make(0xFF, 0x33, 0xFF), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->rt_stream_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_recolor(ui->rt_stream_imgbtn_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_recolor_opa(ui->rt_stream_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->rt_stream_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_PRESSED);

    //Set style for rt_stream_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_CHECKED
    lv_obj_set_style_radius(ui->rt_stream_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_clip_corner(ui->rt_stream_imgbtn_1, true, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui->rt_stream_imgbtn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui->rt_stream_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->rt_stream_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->rt_stream_imgbtn_1, lv_color_make(0xFF, 0x33, 0xFF), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->rt_stream_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_recolor(ui->rt_stream_imgbtn_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_recolor_opa(ui->rt_stream_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->rt_stream_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_pos(ui->rt_stream_imgbtn_1, 636, 70);
    lv_obj_set_size(ui->rt_stream_imgbtn_1, 64, 64);
    lv_obj_set_scrollbar_mode(ui->rt_stream_imgbtn_1, LV_SCROLLBAR_MODE_OFF);

    //Hidden for widget rt_stream_imgbtn_1
    lv_obj_add_flag(ui->rt_stream_imgbtn_1, LV_OBJ_FLAG_HIDDEN);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_imgbtn_set_src(ui->rt_stream_imgbtn_1, LV_IMGBTN_STATE_RELEASED, NULL, "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\switch.png", NULL);
    lv_imgbtn_set_src(ui->rt_stream_imgbtn_1, LV_IMGBTN_STATE_PRESSED, NULL, "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\switch.png", NULL);
    lv_imgbtn_set_src(ui->rt_stream_imgbtn_1, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\switch.png", NULL);
    lv_imgbtn_set_src(ui->rt_stream_imgbtn_1, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\switch.png", NULL);
#else
    lv_imgbtn_set_src(ui->rt_stream_imgbtn_1, LV_IMGBTN_STATE_RELEASED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/55000006.zip", NULL);
    lv_imgbtn_set_src(ui->rt_stream_imgbtn_1, LV_IMGBTN_STATE_PRESSED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/55000006.zip", NULL);
    lv_imgbtn_set_src(ui->rt_stream_imgbtn_1, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/55000006.zip", NULL);
    lv_imgbtn_set_src(ui->rt_stream_imgbtn_1, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/55000006.zip", NULL);
#endif
    lv_obj_add_flag(ui->rt_stream_imgbtn_1, LV_OBJ_FLAG_CHECKABLE);
    ui->rt_stream_imgbtn_1_label = lv_label_create(ui->rt_stream_imgbtn_1);
    lv_label_set_text(ui->rt_stream_imgbtn_1_label, "");
    lv_obj_set_style_pad_all(ui->rt_stream_imgbtn_1, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->rt_stream_imgbtn_1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_update_layout(ui->rt_stream);
    ui->rt_stream_del = false;

    //Init events for screen
    events_init_rt_stream(ui);
    return ui->rt_stream;
}
void unload_scr_rt_stream(lv_ui *ui)
{
    ui->rt_stream_del = true;
}
