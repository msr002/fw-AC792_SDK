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


lv_obj_t *setup_scr_usb_slave(lv_ui *ui)
{
    //Write codes usb_slave
    ui->usb_slave = lv_obj_create(NULL);
    lv_group_t *def_group = lv_group_get_default();

    //Set style for usb_slave. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui->usb_slave, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->usb_slave, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->usb_slave, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(ui->usb_slave, LV_SCROLLBAR_MODE_OFF);
    //Write codes usb_slave_img_icon_pccam
    ui->usb_slave_img_icon_pccam = lv_img_create(ui->usb_slave);

    //Set style for usb_slave_img_icon_pccam. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->usb_slave_img_icon_pccam, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->usb_slave_img_icon_pccam, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->usb_slave_img_icon_pccam, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->usb_slave_img_icon_pccam, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->usb_slave_img_icon_pccam, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->usb_slave_img_icon_pccam, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->usb_slave_img_icon_pccam, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->usb_slave_img_icon_pccam, 298, 109);
    lv_obj_set_size(ui->usb_slave_img_icon_pccam, 200, 200);
    lv_obj_set_scrollbar_mode(ui->usb_slave_img_icon_pccam, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->usb_slave_img_icon_pccam, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui->usb_slave_img_icon_pccam, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_img_set_src(ui->usb_slave_img_icon_pccam, "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\import\\image\\video_page\\USB\\s_PC.png");
#else
    lv_img_set_src(ui->usb_slave_img_icon_pccam, "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000000.rle");
#endif
    lv_img_set_pivot(ui->usb_slave_img_icon_pccam, 0, 0);
    lv_img_set_angle(ui->usb_slave_img_icon_pccam, 0);
    lv_img_set_zoom(ui->usb_slave_img_icon_pccam, 256);
    //Write codes usb_slave_img_icon_masstorage
    ui->usb_slave_img_icon_masstorage = lv_img_create(ui->usb_slave);

    //Set style for usb_slave_img_icon_masstorage. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->usb_slave_img_icon_masstorage, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->usb_slave_img_icon_masstorage, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->usb_slave_img_icon_masstorage, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->usb_slave_img_icon_masstorage, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->usb_slave_img_icon_masstorage, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->usb_slave_img_icon_masstorage, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->usb_slave_img_icon_masstorage, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->usb_slave_img_icon_masstorage, 298, 116);
    lv_obj_set_size(ui->usb_slave_img_icon_masstorage, 200, 200);
    lv_obj_set_scrollbar_mode(ui->usb_slave_img_icon_masstorage, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->usb_slave_img_icon_masstorage, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui->usb_slave_img_icon_masstorage, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_img_set_src(ui->usb_slave_img_icon_masstorage, "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\import\\image\\video_page\\USB\\s_MASS.png");
#else
    lv_img_set_src(ui->usb_slave_img_icon_masstorage, "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000001.rle");
#endif
    lv_img_set_pivot(ui->usb_slave_img_icon_masstorage, 0, 0);
    lv_img_set_angle(ui->usb_slave_img_icon_masstorage, 0);
    lv_img_set_zoom(ui->usb_slave_img_icon_masstorage, 256);
    //Write codes usb_slave_view_btnlist
    ui->usb_slave_view_btnlist = lv_obj_create(ui->usb_slave);

    //Set style for usb_slave_view_btnlist. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->usb_slave_view_btnlist, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->usb_slave_view_btnlist, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->usb_slave_view_btnlist, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->usb_slave_view_btnlist, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->usb_slave_view_btnlist, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->usb_slave_view_btnlist, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->usb_slave_view_btnlist, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->usb_slave_view_btnlist, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->usb_slave_view_btnlist, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->usb_slave_view_btnlist, 125, 70);
    lv_obj_set_size(ui->usb_slave_view_btnlist, 565, 314);
    lv_obj_set_scrollbar_mode(ui->usb_slave_view_btnlist, LV_SCROLLBAR_MODE_OFF);
    //Write codes usb_slave_imgbtn_videorec
    ui->usb_slave_imgbtn_videorec = lv_imgbtn_create(ui->usb_slave_view_btnlist);

    //Set style for usb_slave_imgbtn_videorec. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->usb_slave_imgbtn_videorec, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->usb_slave_imgbtn_videorec, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->usb_slave_imgbtn_videorec, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->usb_slave_imgbtn_videorec, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->usb_slave_imgbtn_videorec, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->usb_slave_imgbtn_videorec, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->usb_slave_imgbtn_videorec, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->usb_slave_imgbtn_videorec, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->usb_slave_imgbtn_videorec, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->usb_slave_imgbtn_videorec, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->usb_slave_imgbtn_videorec, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->usb_slave_imgbtn_videorec, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for usb_slave_imgbtn_videorec. Part: LV_PART_MAIN, State: LV_STATE_PRESSED
    lv_obj_set_style_radius(ui->usb_slave_imgbtn_videorec, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_clip_corner(ui->usb_slave_imgbtn_videorec, true, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->usb_slave_imgbtn_videorec, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(ui->usb_slave_imgbtn_videorec, 255, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->usb_slave_imgbtn_videorec, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->usb_slave_imgbtn_videorec, lv_color_make(0xFF, 0x33, 0xFF), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->usb_slave_imgbtn_videorec, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_recolor(ui->usb_slave_imgbtn_videorec, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_recolor_opa(ui->usb_slave_imgbtn_videorec, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->usb_slave_imgbtn_videorec, 255, LV_PART_MAIN | LV_STATE_PRESSED);

    //Set style for usb_slave_imgbtn_videorec. Part: LV_PART_MAIN, State: LV_STATE_CHECKED
    lv_obj_set_style_radius(ui->usb_slave_imgbtn_videorec, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_clip_corner(ui->usb_slave_imgbtn_videorec, true, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui->usb_slave_imgbtn_videorec, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui->usb_slave_imgbtn_videorec, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->usb_slave_imgbtn_videorec, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->usb_slave_imgbtn_videorec, lv_color_make(0xFF, 0x33, 0xFF), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->usb_slave_imgbtn_videorec, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_recolor(ui->usb_slave_imgbtn_videorec, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_recolor_opa(ui->usb_slave_imgbtn_videorec, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->usb_slave_imgbtn_videorec, 255, LV_PART_MAIN | LV_STATE_CHECKED);

    //Set style for usb_slave_imgbtn_videorec. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui->usb_slave_imgbtn_videorec, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_clip_corner(ui->usb_slave_imgbtn_videorec, true, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(ui->usb_slave_imgbtn_videorec, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui->usb_slave_imgbtn_videorec, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_shadow_width(ui->usb_slave_imgbtn_videorec, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(ui->usb_slave_imgbtn_videorec, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->usb_slave_imgbtn_videorec, 5, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->usb_slave_imgbtn_videorec, 128, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(ui->usb_slave_imgbtn_videorec, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_color(ui->usb_slave_imgbtn_videorec, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_font(ui->usb_slave_imgbtn_videorec, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_align(ui->usb_slave_imgbtn_videorec, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor(ui->usb_slave_imgbtn_videorec, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor_opa(ui->usb_slave_imgbtn_videorec, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_opa(ui->usb_slave_imgbtn_videorec, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->usb_slave_imgbtn_videorec, 414, 33);
    lv_obj_set_size(ui->usb_slave_imgbtn_videorec, 128, 220);
    lv_obj_set_scrollbar_mode(ui->usb_slave_imgbtn_videorec, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui->usb_slave_imgbtn_videorec);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_imgbtn_set_src(ui->usb_slave_imgbtn_videorec, LV_IMGBTN_STATE_RELEASED, NULL, "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\import\\image\\video_page\\USB\\VIDEO.png", NULL);
    lv_imgbtn_set_src(ui->usb_slave_imgbtn_videorec, LV_IMGBTN_STATE_PRESSED, NULL, "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\import\\image\\video_page\\USB\\VIDEO_on.png", NULL);
    lv_imgbtn_set_src(ui->usb_slave_imgbtn_videorec, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\import\\image\\video_page\\USB\\VIDEO.png", NULL);
    lv_imgbtn_set_src(ui->usb_slave_imgbtn_videorec, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\import\\image\\video_page\\USB\\VIDEO_on.png", NULL);
#else
    lv_imgbtn_set_src(ui->usb_slave_imgbtn_videorec, LV_IMGBTN_STATE_RELEASED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000002.rle", NULL);
    lv_imgbtn_set_src(ui->usb_slave_imgbtn_videorec, LV_IMGBTN_STATE_PRESSED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000003.rle", NULL);
    lv_imgbtn_set_src(ui->usb_slave_imgbtn_videorec, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000002.rle", NULL);
    lv_imgbtn_set_src(ui->usb_slave_imgbtn_videorec, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000003.rle", NULL);
#endif
    lv_obj_add_flag(ui->usb_slave_imgbtn_videorec, LV_OBJ_FLAG_CHECKABLE);
    ui->usb_slave_imgbtn_videorec_label = lv_label_create(ui->usb_slave_imgbtn_videorec);
    lv_label_set_text(ui->usb_slave_imgbtn_videorec_label, "");
    lv_obj_set_style_pad_all(ui->usb_slave_imgbtn_videorec, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->usb_slave_imgbtn_videorec_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes usb_slave_imgbtn_masstorage
    ui->usb_slave_imgbtn_masstorage = lv_imgbtn_create(ui->usb_slave_view_btnlist);

    //Set style for usb_slave_imgbtn_masstorage. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->usb_slave_imgbtn_masstorage, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->usb_slave_imgbtn_masstorage, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->usb_slave_imgbtn_masstorage, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->usb_slave_imgbtn_masstorage, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->usb_slave_imgbtn_masstorage, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->usb_slave_imgbtn_masstorage, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->usb_slave_imgbtn_masstorage, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->usb_slave_imgbtn_masstorage, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->usb_slave_imgbtn_masstorage, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->usb_slave_imgbtn_masstorage, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->usb_slave_imgbtn_masstorage, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->usb_slave_imgbtn_masstorage, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for usb_slave_imgbtn_masstorage. Part: LV_PART_MAIN, State: LV_STATE_PRESSED
    lv_obj_set_style_radius(ui->usb_slave_imgbtn_masstorage, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_clip_corner(ui->usb_slave_imgbtn_masstorage, true, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->usb_slave_imgbtn_masstorage, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(ui->usb_slave_imgbtn_masstorage, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->usb_slave_imgbtn_masstorage, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->usb_slave_imgbtn_masstorage, lv_color_make(0xFF, 0x33, 0xFF), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->usb_slave_imgbtn_masstorage, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_recolor(ui->usb_slave_imgbtn_masstorage, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_recolor_opa(ui->usb_slave_imgbtn_masstorage, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->usb_slave_imgbtn_masstorage, 255, LV_PART_MAIN | LV_STATE_PRESSED);

    //Set style for usb_slave_imgbtn_masstorage. Part: LV_PART_MAIN, State: LV_STATE_CHECKED
    lv_obj_set_style_radius(ui->usb_slave_imgbtn_masstorage, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_clip_corner(ui->usb_slave_imgbtn_masstorage, true, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui->usb_slave_imgbtn_masstorage, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui->usb_slave_imgbtn_masstorage, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->usb_slave_imgbtn_masstorage, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->usb_slave_imgbtn_masstorage, lv_color_make(0xFF, 0x33, 0xFF), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->usb_slave_imgbtn_masstorage, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_recolor(ui->usb_slave_imgbtn_masstorage, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_recolor_opa(ui->usb_slave_imgbtn_masstorage, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->usb_slave_imgbtn_masstorage, 255, LV_PART_MAIN | LV_STATE_CHECKED);

    //Set style for usb_slave_imgbtn_masstorage. Part: LV_PART_MAIN, State: LV_STATE_FOCUSED
    lv_obj_set_style_radius(ui->usb_slave_imgbtn_masstorage, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_clip_corner(ui->usb_slave_imgbtn_masstorage, true, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_bg_color(ui->usb_slave_imgbtn_masstorage, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_bg_opa(ui->usb_slave_imgbtn_masstorage, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_shadow_width(ui->usb_slave_imgbtn_masstorage, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_color(ui->usb_slave_imgbtn_masstorage, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_width(ui->usb_slave_imgbtn_masstorage, 2, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_opa(ui->usb_slave_imgbtn_masstorage, 128, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_pad(ui->usb_slave_imgbtn_masstorage, 2, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_text_color(ui->usb_slave_imgbtn_masstorage, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_text_font(ui->usb_slave_imgbtn_masstorage, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_text_align(ui->usb_slave_imgbtn_masstorage, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_img_recolor(ui->usb_slave_imgbtn_masstorage, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_img_recolor_opa(ui->usb_slave_imgbtn_masstorage, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_img_opa(ui->usb_slave_imgbtn_masstorage, 255, LV_PART_MAIN | LV_STATE_FOCUSED);

    //Set style for usb_slave_imgbtn_masstorage. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui->usb_slave_imgbtn_masstorage, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_clip_corner(ui->usb_slave_imgbtn_masstorage, true, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(ui->usb_slave_imgbtn_masstorage, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui->usb_slave_imgbtn_masstorage, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_shadow_width(ui->usb_slave_imgbtn_masstorage, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(ui->usb_slave_imgbtn_masstorage, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->usb_slave_imgbtn_masstorage, 5, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->usb_slave_imgbtn_masstorage, 128, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(ui->usb_slave_imgbtn_masstorage, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_color(ui->usb_slave_imgbtn_masstorage, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_font(ui->usb_slave_imgbtn_masstorage, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_align(ui->usb_slave_imgbtn_masstorage, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor(ui->usb_slave_imgbtn_masstorage, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor_opa(ui->usb_slave_imgbtn_masstorage, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_opa(ui->usb_slave_imgbtn_masstorage, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->usb_slave_imgbtn_masstorage, 24, 33);
    lv_obj_set_size(ui->usb_slave_imgbtn_masstorage, 128, 220);
    lv_obj_set_scrollbar_mode(ui->usb_slave_imgbtn_masstorage, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui->usb_slave_imgbtn_masstorage);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_imgbtn_set_src(ui->usb_slave_imgbtn_masstorage, LV_IMGBTN_STATE_RELEASED, NULL, "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\import\\image\\video_page\\USB\\MASS.png", NULL);
    lv_imgbtn_set_src(ui->usb_slave_imgbtn_masstorage, LV_IMGBTN_STATE_PRESSED, NULL, "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\import\\image\\video_page\\USB\\MASS_on.png", NULL);
    lv_imgbtn_set_src(ui->usb_slave_imgbtn_masstorage, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\import\\image\\video_page\\USB\\MASS.png", NULL);
    lv_imgbtn_set_src(ui->usb_slave_imgbtn_masstorage, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\import\\image\\video_page\\USB\\MASS_on.png", NULL);
#else
    lv_imgbtn_set_src(ui->usb_slave_imgbtn_masstorage, LV_IMGBTN_STATE_RELEASED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000004.rle", NULL);
    lv_imgbtn_set_src(ui->usb_slave_imgbtn_masstorage, LV_IMGBTN_STATE_PRESSED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000005.rle", NULL);
    lv_imgbtn_set_src(ui->usb_slave_imgbtn_masstorage, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000004.rle", NULL);
    lv_imgbtn_set_src(ui->usb_slave_imgbtn_masstorage, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000005.rle", NULL);
#endif
    lv_obj_add_flag(ui->usb_slave_imgbtn_masstorage, LV_OBJ_FLAG_CHECKABLE);
    ui->usb_slave_imgbtn_masstorage_label = lv_label_create(ui->usb_slave_imgbtn_masstorage);
    lv_label_set_text(ui->usb_slave_imgbtn_masstorage_label, "");
    lv_obj_set_style_pad_all(ui->usb_slave_imgbtn_masstorage, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->usb_slave_imgbtn_masstorage_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes usb_slave_imgbtn_pccam
    ui->usb_slave_imgbtn_pccam = lv_imgbtn_create(ui->usb_slave_view_btnlist);

    //Set style for usb_slave_imgbtn_pccam. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->usb_slave_imgbtn_pccam, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->usb_slave_imgbtn_pccam, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->usb_slave_imgbtn_pccam, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->usb_slave_imgbtn_pccam, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->usb_slave_imgbtn_pccam, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->usb_slave_imgbtn_pccam, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->usb_slave_imgbtn_pccam, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->usb_slave_imgbtn_pccam, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->usb_slave_imgbtn_pccam, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->usb_slave_imgbtn_pccam, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->usb_slave_imgbtn_pccam, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->usb_slave_imgbtn_pccam, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for usb_slave_imgbtn_pccam. Part: LV_PART_MAIN, State: LV_STATE_PRESSED
    lv_obj_set_style_radius(ui->usb_slave_imgbtn_pccam, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_clip_corner(ui->usb_slave_imgbtn_pccam, true, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->usb_slave_imgbtn_pccam, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(ui->usb_slave_imgbtn_pccam, 255, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->usb_slave_imgbtn_pccam, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->usb_slave_imgbtn_pccam, lv_color_make(0xFF, 0x33, 0xFF), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->usb_slave_imgbtn_pccam, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_recolor(ui->usb_slave_imgbtn_pccam, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_recolor_opa(ui->usb_slave_imgbtn_pccam, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->usb_slave_imgbtn_pccam, 255, LV_PART_MAIN | LV_STATE_PRESSED);

    //Set style for usb_slave_imgbtn_pccam. Part: LV_PART_MAIN, State: LV_STATE_CHECKED
    lv_obj_set_style_radius(ui->usb_slave_imgbtn_pccam, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_clip_corner(ui->usb_slave_imgbtn_pccam, true, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui->usb_slave_imgbtn_pccam, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui->usb_slave_imgbtn_pccam, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->usb_slave_imgbtn_pccam, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->usb_slave_imgbtn_pccam, lv_color_make(0xFF, 0x33, 0xFF), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->usb_slave_imgbtn_pccam, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_recolor(ui->usb_slave_imgbtn_pccam, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_recolor_opa(ui->usb_slave_imgbtn_pccam, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->usb_slave_imgbtn_pccam, 255, LV_PART_MAIN | LV_STATE_CHECKED);

    //Set style for usb_slave_imgbtn_pccam. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui->usb_slave_imgbtn_pccam, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_clip_corner(ui->usb_slave_imgbtn_pccam, true, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(ui->usb_slave_imgbtn_pccam, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui->usb_slave_imgbtn_pccam, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_shadow_width(ui->usb_slave_imgbtn_pccam, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(ui->usb_slave_imgbtn_pccam, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->usb_slave_imgbtn_pccam, 5, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->usb_slave_imgbtn_pccam, 128, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(ui->usb_slave_imgbtn_pccam, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_color(ui->usb_slave_imgbtn_pccam, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_font(ui->usb_slave_imgbtn_pccam, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_align(ui->usb_slave_imgbtn_pccam, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor(ui->usb_slave_imgbtn_pccam, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor_opa(ui->usb_slave_imgbtn_pccam, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_opa(ui->usb_slave_imgbtn_pccam, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->usb_slave_imgbtn_pccam, 221, 33);
    lv_obj_set_size(ui->usb_slave_imgbtn_pccam, 128, 220);
    lv_obj_set_scrollbar_mode(ui->usb_slave_imgbtn_pccam, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui->usb_slave_imgbtn_pccam);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_imgbtn_set_src(ui->usb_slave_imgbtn_pccam, LV_IMGBTN_STATE_RELEASED, NULL, "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\import\\image\\video_page\\USB\\PCCAM.png", NULL);
    lv_imgbtn_set_src(ui->usb_slave_imgbtn_pccam, LV_IMGBTN_STATE_PRESSED, NULL, "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\import\\image\\video_page\\USB\\PCCAM_on.png", NULL);
    lv_imgbtn_set_src(ui->usb_slave_imgbtn_pccam, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\import\\image\\video_page\\USB\\PCCAM.png", NULL);
    lv_imgbtn_set_src(ui->usb_slave_imgbtn_pccam, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\import\\image\\video_page\\USB\\PCCAM_on.png", NULL);
#else
    lv_imgbtn_set_src(ui->usb_slave_imgbtn_pccam, LV_IMGBTN_STATE_RELEASED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000006.rle", NULL);
    lv_imgbtn_set_src(ui->usb_slave_imgbtn_pccam, LV_IMGBTN_STATE_PRESSED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000007.rle", NULL);
    lv_imgbtn_set_src(ui->usb_slave_imgbtn_pccam, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000006.rle", NULL);
    lv_imgbtn_set_src(ui->usb_slave_imgbtn_pccam, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/56000007.rle", NULL);
#endif
    lv_obj_add_flag(ui->usb_slave_imgbtn_pccam, LV_OBJ_FLAG_CHECKABLE);
    ui->usb_slave_imgbtn_pccam_label = lv_label_create(ui->usb_slave_imgbtn_pccam);
    lv_label_set_text(ui->usb_slave_imgbtn_pccam_label, "");
    lv_obj_set_style_pad_all(ui->usb_slave_imgbtn_pccam, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->usb_slave_imgbtn_pccam_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_update_layout(ui->usb_slave);
    ui->usb_slave_del = false;

    //Init events for screen
    events_init_usb_slave(ui);
    return ui->usb_slave;
}
void unload_scr_usb_slave(lv_ui *ui)
{
    ui->usb_slave_del = true;
}

#endif
