/*Generate Code, Do NOT Edit!*/
#include "lvgl.h"
#include <stdio.h>
#include <stdlib.h>
#include "../gui_guider.h"
#include "../gui_events/events_init.h"
#include "../gui_events/callback_handler.h"
#include "../gui_timelines/gui_timelines.h"
#include "../../custom/custom.h"

static const char *pair_status_imglist_1_imgs[2] = {
#if LV_USE_GUIBUILDER_SIMULATOR
    "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\unpair.png",
    "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\paired.png"
#else
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/55000003.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/55000004.zip"
#endif
};
static const char *pair_status_imglist_2_imgs[2] = {
#if LV_USE_GUIBUILDER_SIMULATOR
    "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\unpair.png",
    "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\paired.png"
#else
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/55000003.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/55000004.zip"
#endif
};
static const char *pair_status_imglist_3_imgs[2] = {
#if LV_USE_GUIBUILDER_SIMULATOR
    "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\unpair.png",
    "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\paired.png"
#else
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/55000003.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/55000004.zip"
#endif
};
static const char *pair_status_imglist_4_imgs[2] = {
#if LV_USE_GUIBUILDER_SIMULATOR
    "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\unpair.png",
    "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\paired.png"
#else
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/55000003.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/55000004.zip"
#endif
};
static const char *pair_status_imglist_5_imgs[2] = {
#if LV_USE_GUIBUILDER_SIMULATOR
    "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\unpair.png",
    "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\paired.png"
#else
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/55000003.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/55000004.zip"
#endif
};
static const char *pair_status_imglist_6_imgs[2] = {
#if LV_USE_GUIBUILDER_SIMULATOR
    "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\unpair.png",
    "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\paired.png"
#else
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/55000003.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/55000004.zip"
#endif
};
static void kb_pair_status_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *kb = lv_event_get_target(e);
    if (code == LV_EVENT_READY || code == LV_EVENT_CANCEL) {
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
    }
}
__attribute__((unused)) static void ta_pair_status_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *ta = lv_event_get_target(e);
    lv_obj_t *kb = lv_event_get_user_data(e);
    if (code == LV_EVENT_FOCUSED || code == LV_EVENT_CLICKED) {
        lv_keyboard_set_textarea(kb, ta);
        lv_obj_move_foreground(kb);
        lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN);
    }
    if (code == LV_EVENT_CANCEL || code == LV_EVENT_DEFOCUSED) {
        lv_keyboard_set_textarea(kb, NULL);
        lv_obj_move_background(kb);
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
        lv_indev_reset(NULL, ta);
    }
}

lv_obj_t *setup_scr_pair_status(lv_ui *ui)
{
    //Write codes pair_status
    ui->pair_status = lv_obj_create(NULL);

    //Create keyboard on pair_status
    ui->g_kb_pair_status = lv_keyboard_create(ui->pair_status);
    lv_obj_add_event_cb(ui->g_kb_pair_status, kb_pair_status_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_add_flag(ui->g_kb_pair_status, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_style_text_font(ui->g_kb_pair_status, &lv_font_montserratMedium_20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_size(ui->g_kb_pair_status, LV_PCT(70), LV_PCT(40));
    lv_keyboard_set_mode(ui->g_kb_pair_status, LV_KEYBOARD_MODE_TEXT_LOWER);
    lv_group_t *def_group = lv_group_get_default();

    //Set style for pair_status. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui->pair_status, lv_color_make(0xE2, 0xDC, 0xDC), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->pair_status, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->pair_status, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(ui->pair_status, LV_SCROLLBAR_MODE_OFF);
    //Write codes pair_status_imglist_1
    ui->pair_status_imglist_1 = lv_imglist_create(ui->pair_status);

    //Set style for pair_status_imglist_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->pair_status_imglist_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->pair_status_imglist_1, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->pair_status_imglist_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->pair_status_imglist_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->pair_status_imglist_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->pair_status_imglist_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->pair_status_imglist_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for pair_status_imglist_1. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui->pair_status_imglist_1, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_clip_corner(ui->pair_status_imglist_1, true, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(ui->pair_status_imglist_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui->pair_status_imglist_1, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(ui->pair_status_imglist_1, lv_color_make(0x21, 0xB4, 0xF6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->pair_status_imglist_1, 4, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->pair_status_imglist_1, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(ui->pair_status_imglist_1, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor(ui->pair_status_imglist_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor_opa(ui->pair_status_imglist_1, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_opa(ui->pair_status_imglist_1, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->pair_status_imglist_1, 86, 111);
    lv_obj_set_size(ui->pair_status_imglist_1, 128, 128);
    lv_obj_set_scrollbar_mode(ui->pair_status_imglist_1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->pair_status_imglist_1, LV_OBJ_FLAG_CLICKABLE);
    lv_group_add_obj(def_group, ui->pair_status_imglist_1);
    lv_imglist_set_src(ui->pair_status_imglist_1, (const void **) pair_status_imglist_1_imgs, 2);
    lv_imglist_set_act(ui->pair_status_imglist_1, 0);
    //Write codes pair_status_imglist_2
    ui->pair_status_imglist_2 = lv_imglist_create(ui->pair_status);

    //Set style for pair_status_imglist_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->pair_status_imglist_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->pair_status_imglist_2, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->pair_status_imglist_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->pair_status_imglist_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->pair_status_imglist_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->pair_status_imglist_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->pair_status_imglist_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for pair_status_imglist_2. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui->pair_status_imglist_2, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_clip_corner(ui->pair_status_imglist_2, true, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(ui->pair_status_imglist_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui->pair_status_imglist_2, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(ui->pair_status_imglist_2, lv_color_make(0x21, 0xB4, 0xF6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->pair_status_imglist_2, 4, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->pair_status_imglist_2, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(ui->pair_status_imglist_2, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor(ui->pair_status_imglist_2, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor_opa(ui->pair_status_imglist_2, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_opa(ui->pair_status_imglist_2, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->pair_status_imglist_2, 337, 111);
    lv_obj_set_size(ui->pair_status_imglist_2, 128, 128);
    lv_obj_set_scrollbar_mode(ui->pair_status_imglist_2, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->pair_status_imglist_2, LV_OBJ_FLAG_CLICKABLE);
    lv_group_add_obj(def_group, ui->pair_status_imglist_2);
    lv_imglist_set_src(ui->pair_status_imglist_2, (const void **) pair_status_imglist_2_imgs, 2);
    lv_imglist_set_act(ui->pair_status_imglist_2, 0);
    //Write codes pair_status_imglist_3
    ui->pair_status_imglist_3 = lv_imglist_create(ui->pair_status);

    //Set style for pair_status_imglist_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->pair_status_imglist_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->pair_status_imglist_3, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->pair_status_imglist_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->pair_status_imglist_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->pair_status_imglist_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->pair_status_imglist_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->pair_status_imglist_3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for pair_status_imglist_3. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui->pair_status_imglist_3, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_clip_corner(ui->pair_status_imglist_3, true, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(ui->pair_status_imglist_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui->pair_status_imglist_3, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(ui->pair_status_imglist_3, lv_color_make(0x21, 0xB4, 0xF6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->pair_status_imglist_3, 4, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->pair_status_imglist_3, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(ui->pair_status_imglist_3, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor(ui->pair_status_imglist_3, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor_opa(ui->pair_status_imglist_3, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_opa(ui->pair_status_imglist_3, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->pair_status_imglist_3, 590, 111);
    lv_obj_set_size(ui->pair_status_imglist_3, 128, 128);
    lv_obj_set_scrollbar_mode(ui->pair_status_imglist_3, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->pair_status_imglist_3, LV_OBJ_FLAG_CLICKABLE);
    lv_group_add_obj(def_group, ui->pair_status_imglist_3);
    lv_imglist_set_src(ui->pair_status_imglist_3, (const void **) pair_status_imglist_3_imgs, 2);
    lv_imglist_set_act(ui->pair_status_imglist_3, 0);
    //Write codes pair_status_imglist_4
    ui->pair_status_imglist_4 = lv_imglist_create(ui->pair_status);

    //Set style for pair_status_imglist_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->pair_status_imglist_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->pair_status_imglist_4, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->pair_status_imglist_4, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->pair_status_imglist_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->pair_status_imglist_4, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->pair_status_imglist_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->pair_status_imglist_4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for pair_status_imglist_4. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui->pair_status_imglist_4, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_clip_corner(ui->pair_status_imglist_4, true, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(ui->pair_status_imglist_4, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui->pair_status_imglist_4, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(ui->pair_status_imglist_4, lv_color_make(0x21, 0xB4, 0xF6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->pair_status_imglist_4, 4, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->pair_status_imglist_4, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(ui->pair_status_imglist_4, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor(ui->pair_status_imglist_4, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor_opa(ui->pair_status_imglist_4, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_opa(ui->pair_status_imglist_4, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->pair_status_imglist_4, 82, 296);
    lv_obj_set_size(ui->pair_status_imglist_4, 128, 128);
    lv_obj_set_scrollbar_mode(ui->pair_status_imglist_4, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->pair_status_imglist_4, LV_OBJ_FLAG_CLICKABLE);
    lv_group_add_obj(def_group, ui->pair_status_imglist_4);
    lv_imglist_set_src(ui->pair_status_imglist_4, (const void **) pair_status_imglist_4_imgs, 2);
    lv_imglist_set_act(ui->pair_status_imglist_4, 0);
    //Write codes pair_status_imglist_5
    ui->pair_status_imglist_5 = lv_imglist_create(ui->pair_status);

    //Set style for pair_status_imglist_5. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->pair_status_imglist_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->pair_status_imglist_5, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->pair_status_imglist_5, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->pair_status_imglist_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->pair_status_imglist_5, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->pair_status_imglist_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->pair_status_imglist_5, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for pair_status_imglist_5. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui->pair_status_imglist_5, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_clip_corner(ui->pair_status_imglist_5, true, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(ui->pair_status_imglist_5, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui->pair_status_imglist_5, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(ui->pair_status_imglist_5, lv_color_make(0x21, 0xB4, 0xF6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->pair_status_imglist_5, 4, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->pair_status_imglist_5, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(ui->pair_status_imglist_5, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor(ui->pair_status_imglist_5, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor_opa(ui->pair_status_imglist_5, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_opa(ui->pair_status_imglist_5, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->pair_status_imglist_5, 337, 291);
    lv_obj_set_size(ui->pair_status_imglist_5, 128, 128);
    lv_obj_set_scrollbar_mode(ui->pair_status_imglist_5, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->pair_status_imglist_5, LV_OBJ_FLAG_CLICKABLE);
    lv_group_add_obj(def_group, ui->pair_status_imglist_5);
    lv_imglist_set_src(ui->pair_status_imglist_5, (const void **) pair_status_imglist_5_imgs, 2);
    lv_imglist_set_act(ui->pair_status_imglist_5, 0);
    //Write codes pair_status_imglist_6
    ui->pair_status_imglist_6 = lv_imglist_create(ui->pair_status);

    //Set style for pair_status_imglist_6. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->pair_status_imglist_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->pair_status_imglist_6, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->pair_status_imglist_6, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->pair_status_imglist_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->pair_status_imglist_6, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->pair_status_imglist_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->pair_status_imglist_6, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for pair_status_imglist_6. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui->pair_status_imglist_6, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_clip_corner(ui->pair_status_imglist_6, true, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(ui->pair_status_imglist_6, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui->pair_status_imglist_6, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(ui->pair_status_imglist_6, lv_color_make(0x21, 0xB4, 0xF6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->pair_status_imglist_6, 4, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->pair_status_imglist_6, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(ui->pair_status_imglist_6, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor(ui->pair_status_imglist_6, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor_opa(ui->pair_status_imglist_6, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_opa(ui->pair_status_imglist_6, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_pos(ui->pair_status_imglist_6, 590, 295);
    lv_obj_set_size(ui->pair_status_imglist_6, 128, 128);
    lv_obj_set_scrollbar_mode(ui->pair_status_imglist_6, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->pair_status_imglist_6, LV_OBJ_FLAG_CLICKABLE);
    lv_group_add_obj(def_group, ui->pair_status_imglist_6);
    lv_imglist_set_src(ui->pair_status_imglist_6, (const void **) pair_status_imglist_6_imgs, 2);
    lv_imglist_set_act(ui->pair_status_imglist_6, 0);
    //Write codes pair_status_imgbtn_1
    ui->pair_status_imgbtn_1 = lv_imgbtn_create(ui->pair_status);

    //Set style for pair_status_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->pair_status_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->pair_status_imgbtn_1, true, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->pair_status_imgbtn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->pair_status_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->pair_status_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->pair_status_imgbtn_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->pair_status_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->pair_status_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->pair_status_imgbtn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->pair_status_imgbtn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui->pair_status_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->pair_status_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for pair_status_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui->pair_status_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_clip_corner(ui->pair_status_imgbtn_1, true, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(ui->pair_status_imgbtn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui->pair_status_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_shadow_width(ui->pair_status_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(ui->pair_status_imgbtn_1, lv_color_make(0x21, 0xB4, 0xF6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->pair_status_imgbtn_1, 4, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->pair_status_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(ui->pair_status_imgbtn_1, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_color(ui->pair_status_imgbtn_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_font(ui->pair_status_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor(ui->pair_status_imgbtn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_recolor_opa(ui->pair_status_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_img_opa(ui->pair_status_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Set style for pair_status_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_PRESSED
    lv_obj_set_style_radius(ui->pair_status_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_clip_corner(ui->pair_status_imgbtn_1, true, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->pair_status_imgbtn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(ui->pair_status_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->pair_status_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->pair_status_imgbtn_1, lv_color_make(0xFF, 0x33, 0xFF), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->pair_status_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_recolor(ui->pair_status_imgbtn_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_recolor_opa(ui->pair_status_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->pair_status_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_PRESSED);

    //Set style for pair_status_imgbtn_1. Part: LV_PART_MAIN, State: LV_STATE_CHECKED
    lv_obj_set_style_radius(ui->pair_status_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_clip_corner(ui->pair_status_imgbtn_1, true, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui->pair_status_imgbtn_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui->pair_status_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->pair_status_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->pair_status_imgbtn_1, lv_color_make(0xFF, 0x33, 0xFF), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->pair_status_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_recolor(ui->pair_status_imgbtn_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_recolor_opa(ui->pair_status_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->pair_status_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_pos(ui->pair_status_imgbtn_1, 19, 14);
    lv_obj_set_size(ui->pair_status_imgbtn_1, 64, 64);
    lv_obj_set_scrollbar_mode(ui->pair_status_imgbtn_1, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui->pair_status_imgbtn_1);
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_imgbtn_set_src(ui->pair_status_imgbtn_1, LV_IMGBTN_STATE_RELEASED, NULL, "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\back.png", NULL);
    lv_imgbtn_set_src(ui->pair_status_imgbtn_1, LV_IMGBTN_STATE_PRESSED, NULL, "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\back.png", NULL);
    lv_imgbtn_set_src(ui->pair_status_imgbtn_1, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\back.png", NULL);
    lv_imgbtn_set_src(ui->pair_status_imgbtn_1, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "A:\\gitlab-m\\ac792\\ui_prj\\wifi_bbm_800x480\\import\\image\\back.png", NULL);
#else
    lv_imgbtn_set_src(ui->pair_status_imgbtn_1, LV_IMGBTN_STATE_RELEASED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/55000005.zip", NULL);
    lv_imgbtn_set_src(ui->pair_status_imgbtn_1, LV_IMGBTN_STATE_PRESSED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/55000005.zip", NULL);
    lv_imgbtn_set_src(ui->pair_status_imgbtn_1, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/55000005.zip", NULL);
    lv_imgbtn_set_src(ui->pair_status_imgbtn_1, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, "mnt/sdfile/EXT_RESERVED/uipackres/ui/55000005.zip", NULL);
#endif
    lv_obj_add_flag(ui->pair_status_imgbtn_1, LV_OBJ_FLAG_CHECKABLE);
    ui->pair_status_imgbtn_1_label = lv_label_create(ui->pair_status_imgbtn_1);
    lv_label_set_text(ui->pair_status_imgbtn_1_label, "");
    lv_obj_set_style_pad_all(ui->pair_status_imgbtn_1, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui->pair_status_imgbtn_1_label, LV_ALIGN_CENTER, 0, 0);
    //Write codes pair_status_lbl_1
    ui->pair_status_lbl_1 = lv_label_create(ui->pair_status);
    lv_label_set_text(ui->pair_status_lbl_1, "Device 0");
    lv_label_set_long_mode(ui->pair_status_lbl_1, LV_LABEL_LONG_WRAP);

    //Set style for pair_status_lbl_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->pair_status_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->pair_status_lbl_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->pair_status_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->pair_status_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->pair_status_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->pair_status_lbl_1, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->pair_status_lbl_1, &lv_font_montserratMedium_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->pair_status_lbl_1, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->pair_status_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->pair_status_lbl_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->pair_status_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->pair_status_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->pair_status_lbl_1, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->pair_status_lbl_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->pair_status_lbl_1, 85, 240);
    lv_obj_set_size(ui->pair_status_lbl_1, 100, 35);
    lv_obj_set_scrollbar_mode(ui->pair_status_lbl_1, LV_SCROLLBAR_MODE_OFF);
    //Write codes pair_status_lbl_2
    ui->pair_status_lbl_2 = lv_label_create(ui->pair_status);
    lv_label_set_text(ui->pair_status_lbl_2, "Device 1");
    lv_label_set_long_mode(ui->pair_status_lbl_2, LV_LABEL_LONG_WRAP);

    //Set style for pair_status_lbl_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->pair_status_lbl_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->pair_status_lbl_2, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->pair_status_lbl_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->pair_status_lbl_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->pair_status_lbl_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->pair_status_lbl_2, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->pair_status_lbl_2, &lv_font_montserratMedium_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->pair_status_lbl_2, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->pair_status_lbl_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->pair_status_lbl_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->pair_status_lbl_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->pair_status_lbl_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->pair_status_lbl_2, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->pair_status_lbl_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->pair_status_lbl_2, 335, 240);
    lv_obj_set_size(ui->pair_status_lbl_2, 100, 35);
    lv_obj_set_scrollbar_mode(ui->pair_status_lbl_2, LV_SCROLLBAR_MODE_OFF);
    //Write codes pair_status_lbl_3
    ui->pair_status_lbl_3 = lv_label_create(ui->pair_status);
    lv_label_set_text(ui->pair_status_lbl_3, "Device 2");
    lv_label_set_long_mode(ui->pair_status_lbl_3, LV_LABEL_LONG_WRAP);

    //Set style for pair_status_lbl_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->pair_status_lbl_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->pair_status_lbl_3, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->pair_status_lbl_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->pair_status_lbl_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->pair_status_lbl_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->pair_status_lbl_3, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->pair_status_lbl_3, &lv_font_montserratMedium_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->pair_status_lbl_3, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->pair_status_lbl_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->pair_status_lbl_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->pair_status_lbl_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->pair_status_lbl_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->pair_status_lbl_3, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->pair_status_lbl_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->pair_status_lbl_3, 585, 240);
    lv_obj_set_size(ui->pair_status_lbl_3, 100, 35);
    lv_obj_set_scrollbar_mode(ui->pair_status_lbl_3, LV_SCROLLBAR_MODE_OFF);
    //Write codes pair_status_lbl_4
    ui->pair_status_lbl_4 = lv_label_create(ui->pair_status);
    lv_label_set_text(ui->pair_status_lbl_4, "Device 3");
    lv_label_set_long_mode(ui->pair_status_lbl_4, LV_LABEL_LONG_WRAP);

    //Set style for pair_status_lbl_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->pair_status_lbl_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->pair_status_lbl_4, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->pair_status_lbl_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->pair_status_lbl_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->pair_status_lbl_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->pair_status_lbl_4, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->pair_status_lbl_4, &lv_font_montserratMedium_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->pair_status_lbl_4, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->pair_status_lbl_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->pair_status_lbl_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->pair_status_lbl_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->pair_status_lbl_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->pair_status_lbl_4, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->pair_status_lbl_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->pair_status_lbl_4, 85, 425);
    lv_obj_set_size(ui->pair_status_lbl_4, 100, 35);
    lv_obj_set_scrollbar_mode(ui->pair_status_lbl_4, LV_SCROLLBAR_MODE_OFF);
    //Write codes pair_status_lbl_5
    ui->pair_status_lbl_5 = lv_label_create(ui->pair_status);
    lv_label_set_text(ui->pair_status_lbl_5, "Device 4");
    lv_label_set_long_mode(ui->pair_status_lbl_5, LV_LABEL_LONG_WRAP);

    //Set style for pair_status_lbl_5. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->pair_status_lbl_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->pair_status_lbl_5, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->pair_status_lbl_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->pair_status_lbl_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->pair_status_lbl_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->pair_status_lbl_5, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->pair_status_lbl_5, &lv_font_montserratMedium_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->pair_status_lbl_5, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->pair_status_lbl_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->pair_status_lbl_5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->pair_status_lbl_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->pair_status_lbl_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->pair_status_lbl_5, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->pair_status_lbl_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->pair_status_lbl_5, 335, 425);
    lv_obj_set_size(ui->pair_status_lbl_5, 100, 35);
    lv_obj_set_scrollbar_mode(ui->pair_status_lbl_5, LV_SCROLLBAR_MODE_OFF);
    //Write codes pair_status_lbl_6
    ui->pair_status_lbl_6 = lv_label_create(ui->pair_status);
    lv_label_set_text(ui->pair_status_lbl_6, "Device 5");
    lv_label_set_long_mode(ui->pair_status_lbl_6, LV_LABEL_LONG_WRAP);

    //Set style for pair_status_lbl_6. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->pair_status_lbl_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->pair_status_lbl_6, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->pair_status_lbl_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->pair_status_lbl_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->pair_status_lbl_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->pair_status_lbl_6, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->pair_status_lbl_6, &lv_font_montserratMedium_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->pair_status_lbl_6, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->pair_status_lbl_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->pair_status_lbl_6, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->pair_status_lbl_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->pair_status_lbl_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->pair_status_lbl_6, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->pair_status_lbl_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->pair_status_lbl_6, 585, 425);
    lv_obj_set_size(ui->pair_status_lbl_6, 100, 35);
    lv_obj_set_scrollbar_mode(ui->pair_status_lbl_6, LV_SCROLLBAR_MODE_OFF);
    //Write codes pair_status_ddlist_1
    ui->pair_status_ddlist_1 = lv_dropdown_create(ui->pair_status);
    lv_dropdown_set_options(ui->pair_status_ddlist_1, "Channel-1\nChannel-6\nChannel-13");
    lv_dropdown_set_dir(ui->pair_status_ddlist_1, LV_DIR_BOTTOM);
    lv_dropdown_set_symbol(ui->pair_status_ddlist_1, LV_SYMBOL_DOWN);
    lv_dropdown_set_selected(ui->pair_status_ddlist_1, 0);

    //Set style for pair_status_ddlist_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->pair_status_ddlist_1, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->pair_status_ddlist_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->pair_status_ddlist_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->pair_status_ddlist_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->pair_status_ddlist_1, lv_color_make(0x22, 0x53, 0xA2), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->pair_status_ddlist_1, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->pair_status_ddlist_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->pair_status_ddlist_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui->pair_status_ddlist_1, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->pair_status_ddlist_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui->pair_status_ddlist_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui->pair_status_ddlist_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->pair_status_ddlist_1, lv_color_make(0x0D, 0x30, 0x55), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->pair_status_ddlist_1, &lv_font_montserratMedium_20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->pair_status_ddlist_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->pair_status_ddlist_1, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->pair_status_ddlist_1, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->pair_status_ddlist_1, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style for pair_status_ddlist_1. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_radius(ui->pair_status_ddlist_1, 8, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(ui->pair_status_ddlist_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_opa(ui->pair_status_ddlist_1, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_shadow_width(ui->pair_status_ddlist_1, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_border_color(ui->pair_status_ddlist_1, lv_color_make(0x22, 0x53, 0xA2), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_border_width(ui->pair_status_ddlist_1, 3, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_border_opa(ui->pair_status_ddlist_1, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_border_side(ui->pair_status_ddlist_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_color(ui->pair_status_ddlist_1, lv_color_make(0x21, 0xB4, 0xF6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_width(ui->pair_status_ddlist_1, 4, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_opa(ui->pair_status_ddlist_1, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_outline_pad(ui->pair_status_ddlist_1, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_color(ui->pair_status_ddlist_1, lv_color_make(0x0D, 0x30, 0x55), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_font(ui->pair_status_ddlist_1, &lv_font_montserratMedium_20, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_text_letter_space(ui->pair_status_ddlist_1, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_pad_left(ui->pair_status_ddlist_1, 6, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_pad_right(ui->pair_status_ddlist_1, 6, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_pad_top(ui->pair_status_ddlist_1, 8, LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Set style state: LV_STATE_CHECKED for style_pair_status_ddlist_1_extra_list_selected_checked
    static lv_style_t style_pair_status_ddlist_1_extra_list_selected_checked;
    ui_init_style(&style_pair_status_ddlist_1_extra_list_selected_checked);
    lv_style_set_radius(&style_pair_status_ddlist_1_extra_list_selected_checked, 3);
    lv_style_set_bg_color(&style_pair_status_ddlist_1_extra_list_selected_checked, lv_color_make(0xB0, 0xB8, 0xB8));
    lv_style_set_bg_opa(&style_pair_status_ddlist_1_extra_list_selected_checked, 255);
    lv_style_set_border_color(&style_pair_status_ddlist_1_extra_list_selected_checked, lv_color_make(0xe1, 0xe6, 0xee));
    lv_style_set_border_width(&style_pair_status_ddlist_1_extra_list_selected_checked, 1);
    lv_style_set_border_opa(&style_pair_status_ddlist_1_extra_list_selected_checked, 255);
    lv_style_set_border_side(&style_pair_status_ddlist_1_extra_list_selected_checked, LV_BORDER_SIDE_FULL);
    lv_style_set_text_color(&style_pair_status_ddlist_1_extra_list_selected_checked, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_text_font(&style_pair_status_ddlist_1_extra_list_selected_checked, &lv_font_montserratMedium_20);
    lv_style_set_text_letter_space(&style_pair_status_ddlist_1_extra_list_selected_checked, 0);
    lv_obj_add_style(lv_dropdown_get_list(ui->pair_status_ddlist_1), &style_pair_status_ddlist_1_extra_list_selected_checked, LV_PART_SELECTED | LV_STATE_CHECKED);

    //Set style state: LV_STATE_DEFAULT for style_pair_status_ddlist_1_extra_list_main_default
    static lv_style_t style_pair_status_ddlist_1_extra_list_main_default;
    ui_init_style(&style_pair_status_ddlist_1_extra_list_main_default);
    lv_style_set_radius(&style_pair_status_ddlist_1_extra_list_main_default, 5);
    lv_style_set_bg_color(&style_pair_status_ddlist_1_extra_list_main_default, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_bg_opa(&style_pair_status_ddlist_1_extra_list_main_default, 255);
    lv_style_set_border_color(&style_pair_status_ddlist_1_extra_list_main_default, lv_color_make(0xe1, 0xe6, 0xee));
    lv_style_set_border_width(&style_pair_status_ddlist_1_extra_list_main_default, 1);
    lv_style_set_border_opa(&style_pair_status_ddlist_1_extra_list_main_default, 255);
    lv_style_set_border_side(&style_pair_status_ddlist_1_extra_list_main_default, LV_BORDER_SIDE_FULL);
    lv_style_set_text_color(&style_pair_status_ddlist_1_extra_list_main_default, lv_color_make(0x0D, 0x30, 0x55));
    lv_style_set_text_font(&style_pair_status_ddlist_1_extra_list_main_default, &lv_font_montserratMedium_20);
    lv_style_set_text_letter_space(&style_pair_status_ddlist_1_extra_list_main_default, 0);
    lv_style_set_max_height(&style_pair_status_ddlist_1_extra_list_main_default, 90);
    lv_obj_add_style(lv_dropdown_get_list(ui->pair_status_ddlist_1), &style_pair_status_ddlist_1_extra_list_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Set style state: LV_STATE_DEFAULT for style_pair_status_ddlist_1_extra_list_scrollbar_default
    static lv_style_t style_pair_status_ddlist_1_extra_list_scrollbar_default;
    ui_init_style(&style_pair_status_ddlist_1_extra_list_scrollbar_default);
    lv_style_set_radius(&style_pair_status_ddlist_1_extra_list_scrollbar_default, 3);
    lv_style_set_bg_color(&style_pair_status_ddlist_1_extra_list_scrollbar_default, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_bg_opa(&style_pair_status_ddlist_1_extra_list_scrollbar_default, 255);
    lv_obj_add_style(lv_dropdown_get_list(ui->pair_status_ddlist_1), &style_pair_status_ddlist_1_extra_list_scrollbar_default, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->pair_status_ddlist_1, 590, 49);
    lv_obj_set_size(ui->pair_status_ddlist_1, 150, 45);
    lv_obj_set_scrollbar_mode(ui->pair_status_ddlist_1, LV_SCROLLBAR_MODE_OFF);
    //Write codes pair_status_lbl_7
    ui->pair_status_lbl_7 = lv_label_create(ui->pair_status);
    lv_label_set_text(ui->pair_status_lbl_7, "WiFi-Channel");
    lv_label_set_long_mode(ui->pair_status_lbl_7, LV_LABEL_LONG_WRAP);

    //Set style for pair_status_lbl_7. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_radius(ui->pair_status_lbl_7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->pair_status_lbl_7, lv_color_make(0x21, 0x95, 0xf6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->pair_status_lbl_7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->pair_status_lbl_7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->pair_status_lbl_7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->pair_status_lbl_7, lv_color_make(0x2A, 0x09, 0x23), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->pair_status_lbl_7, &lv_font_montserratMedium_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->pair_status_lbl_7, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->pair_status_lbl_7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->pair_status_lbl_7, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->pair_status_lbl_7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->pair_status_lbl_7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->pair_status_lbl_7, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->pair_status_lbl_7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->pair_status_lbl_7, 520, 0);
    lv_obj_set_size(ui->pair_status_lbl_7, 233, 38);
    lv_obj_set_scrollbar_mode(ui->pair_status_lbl_7, LV_SCROLLBAR_MODE_OFF);
    lv_obj_update_layout(ui->pair_status);
    ui->pair_status_del = false;

    //Init events for screen
    events_init_pair_status(ui);
    return ui->pair_status;
}
void unload_scr_pair_status(lv_ui *ui)
{
    ui->pair_status_del = true;
}
