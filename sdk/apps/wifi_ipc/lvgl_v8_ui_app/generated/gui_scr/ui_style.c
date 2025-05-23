/*Generate Code, Do NOT Edit!*/
#include "./ui_style.h"
#include "../gui_guider.h"

// digitclock
lv_style_t gui_digitclock_main_default_style;

// digital_clock
lv_style_t gui_digitclock_main_default_style;

// img
lv_style_t gui_img_main_default_style;

// scr
lv_style_t gui_scr_main_default_style;

// label
lv_style_t gui_label_main_default_style;

// list
lv_style_t gui_list_main_default_style;
lv_style_t gui_list_main_focused_style;
lv_style_t gui_list_scrollbar_default_style;
lv_style_t gui_list_btn_main_default_style;
lv_style_t gui_list_btn_main_pressed_style;
lv_style_t gui_list_btn_main_focused_style;
lv_style_t gui_list_txt_main_default_style;

// imglist
lv_style_t gui_imglist_main_default_style;

// ta
lv_style_t gui_ta_main_default_style;
lv_style_t gui_ta_scrollbar_default_style;

// textarea
lv_style_t gui_ta_main_default_style;
lv_style_t gui_ta_scrollbar_default_style;

// btn
lv_style_t gui_btn_main_default_style;

void ui_style_init(void)
{
    // digitclock
    lv_style_init(&gui_digitclock_main_default_style);
    lv_style_set_radius(&gui_digitclock_main_default_style, 0);
    lv_style_set_bg_color(&gui_digitclock_main_default_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_bg_grad_color(&gui_digitclock_main_default_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_bg_grad_dir(&gui_digitclock_main_default_style, LV_GRAD_DIR_NONE);
    lv_style_set_bg_opa(&gui_digitclock_main_default_style, 0);
    lv_style_set_shadow_width(&gui_digitclock_main_default_style, 0);
    lv_style_set_shadow_color(&gui_digitclock_main_default_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_shadow_opa(&gui_digitclock_main_default_style, 255);
    lv_style_set_shadow_spread(&gui_digitclock_main_default_style, 0);
    lv_style_set_shadow_ofs_x(&gui_digitclock_main_default_style, 0);
    lv_style_set_shadow_ofs_y(&gui_digitclock_main_default_style, 0);
    lv_style_set_border_color(&gui_digitclock_main_default_style, lv_color_make(0x00, 0x00, 0x00));
    lv_style_set_border_width(&gui_digitclock_main_default_style, 0);
    lv_style_set_border_opa(&gui_digitclock_main_default_style, 255);
    lv_style_set_border_side(&gui_digitclock_main_default_style, LV_BORDER_SIDE_FULL);
    lv_style_set_outline_color(&gui_digitclock_main_default_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_outline_width(&gui_digitclock_main_default_style, 0);
    lv_style_set_outline_opa(&gui_digitclock_main_default_style, 128);
    lv_style_set_outline_pad(&gui_digitclock_main_default_style, 0);
    lv_style_set_text_color(&gui_digitclock_main_default_style, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_text_font(&gui_digitclock_main_default_style, &lv_font_montserratMedium_32);
    lv_style_set_text_letter_space(&gui_digitclock_main_default_style, 2);
    lv_style_set_pad_left(&gui_digitclock_main_default_style, 0);
    lv_style_set_pad_right(&gui_digitclock_main_default_style, 0);
    lv_style_set_pad_top(&gui_digitclock_main_default_style, 7);

    // digital_clock
    lv_style_init(&gui_digitclock_main_default_style);
    lv_style_set_radius(&gui_digitclock_main_default_style, 0);
    lv_style_set_bg_color(&gui_digitclock_main_default_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_bg_grad_color(&gui_digitclock_main_default_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_bg_grad_dir(&gui_digitclock_main_default_style, LV_GRAD_DIR_NONE);
    lv_style_set_bg_opa(&gui_digitclock_main_default_style, 0);
    lv_style_set_shadow_width(&gui_digitclock_main_default_style, 0);
    lv_style_set_shadow_color(&gui_digitclock_main_default_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_shadow_opa(&gui_digitclock_main_default_style, 255);
    lv_style_set_shadow_spread(&gui_digitclock_main_default_style, 0);
    lv_style_set_shadow_ofs_x(&gui_digitclock_main_default_style, 0);
    lv_style_set_shadow_ofs_y(&gui_digitclock_main_default_style, 0);
    lv_style_set_border_color(&gui_digitclock_main_default_style, lv_color_make(0x00, 0x00, 0x00));
    lv_style_set_border_width(&gui_digitclock_main_default_style, 0);
    lv_style_set_border_opa(&gui_digitclock_main_default_style, 255);
    lv_style_set_border_side(&gui_digitclock_main_default_style, LV_BORDER_SIDE_FULL);
    lv_style_set_outline_color(&gui_digitclock_main_default_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_outline_width(&gui_digitclock_main_default_style, 0);
    lv_style_set_outline_opa(&gui_digitclock_main_default_style, 128);
    lv_style_set_outline_pad(&gui_digitclock_main_default_style, 0);
    lv_style_set_text_color(&gui_digitclock_main_default_style, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_text_font(&gui_digitclock_main_default_style, &lv_font_montserratMedium_32);
    lv_style_set_text_letter_space(&gui_digitclock_main_default_style, 2);
    lv_style_set_pad_left(&gui_digitclock_main_default_style, 0);
    lv_style_set_pad_right(&gui_digitclock_main_default_style, 0);
    lv_style_set_pad_top(&gui_digitclock_main_default_style, 7);

    // img
    lv_style_init(&gui_img_main_default_style);
    lv_style_set_radius(&gui_img_main_default_style, 0);
    lv_style_set_clip_corner(&gui_img_main_default_style, true);
    lv_style_set_bg_color(&gui_img_main_default_style, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_bg_grad_color(&gui_img_main_default_style, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_bg_grad_dir(&gui_img_main_default_style, LV_GRAD_DIR_NONE);
    lv_style_set_bg_opa(&gui_img_main_default_style, 0);
    lv_style_set_outline_color(&gui_img_main_default_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_outline_width(&gui_img_main_default_style, 0);
    lv_style_set_outline_opa(&gui_img_main_default_style, 128);
    lv_style_set_outline_pad(&gui_img_main_default_style, 0);
    lv_style_set_img_recolor(&gui_img_main_default_style, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_img_recolor_opa(&gui_img_main_default_style, 0);
    lv_style_set_img_opa(&gui_img_main_default_style, 255);

    // scr
    lv_style_init(&gui_scr_main_default_style);
    lv_style_set_bg_color(&gui_scr_main_default_style, lv_color_make(0x02, 0x9A, 0xFF));
    lv_style_set_bg_grad_color(&gui_scr_main_default_style, lv_color_make(0xFF, 0x6A, 0x6A));
    lv_style_set_bg_grad_dir(&gui_scr_main_default_style, LV_GRAD_DIR_VER);
    lv_style_set_bg_opa(&gui_scr_main_default_style, 255);
    lv_style_set_border_color(&gui_scr_main_default_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_border_width(&gui_scr_main_default_style, 0);
    lv_style_set_border_opa(&gui_scr_main_default_style, 255);

    // label
    lv_style_init(&gui_label_main_default_style);
    lv_style_set_radius(&gui_label_main_default_style, 0);
    lv_style_set_bg_color(&gui_label_main_default_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_bg_grad_color(&gui_label_main_default_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_bg_grad_dir(&gui_label_main_default_style, LV_GRAD_DIR_NONE);
    lv_style_set_bg_opa(&gui_label_main_default_style, 0);
    lv_style_set_shadow_width(&gui_label_main_default_style, 0);
    lv_style_set_shadow_color(&gui_label_main_default_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_shadow_opa(&gui_label_main_default_style, 255);
    lv_style_set_shadow_spread(&gui_label_main_default_style, 0);
    lv_style_set_shadow_ofs_x(&gui_label_main_default_style, 0);
    lv_style_set_shadow_ofs_y(&gui_label_main_default_style, 0);
    lv_style_set_border_color(&gui_label_main_default_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_border_width(&gui_label_main_default_style, 0);
    lv_style_set_border_opa(&gui_label_main_default_style, 255);
    lv_style_set_border_side(&gui_label_main_default_style, LV_BORDER_SIDE_FULL);
    lv_style_set_outline_color(&gui_label_main_default_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_outline_width(&gui_label_main_default_style, 0);
    lv_style_set_outline_opa(&gui_label_main_default_style, 128);
    lv_style_set_outline_pad(&gui_label_main_default_style, 0);
    lv_style_set_text_color(&gui_label_main_default_style, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_text_font(&gui_label_main_default_style, &lv_font_simsun_22);
    lv_style_set_text_letter_space(&gui_label_main_default_style, 2);
    lv_style_set_text_line_space(&gui_label_main_default_style, 0);
    lv_style_set_text_align(&gui_label_main_default_style, LV_TEXT_ALIGN_CENTER);
    lv_style_set_pad_left(&gui_label_main_default_style, 0);
    lv_style_set_pad_right(&gui_label_main_default_style, 0);
    lv_style_set_pad_top(&gui_label_main_default_style, 8);
    lv_style_set_pad_bottom(&gui_label_main_default_style, 0);

    // list
    lv_style_init(&gui_list_main_default_style);
    lv_style_set_radius(&gui_list_main_default_style, 20);
    lv_style_set_bg_color(&gui_list_main_default_style, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_bg_grad_color(&gui_list_main_default_style, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_bg_grad_dir(&gui_list_main_default_style, LV_GRAD_DIR_NONE);
    lv_style_set_bg_opa(&gui_list_main_default_style, 255);
    lv_style_set_shadow_width(&gui_list_main_default_style, 0);
    lv_style_set_shadow_color(&gui_list_main_default_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_shadow_opa(&gui_list_main_default_style, 0);
    lv_style_set_shadow_spread(&gui_list_main_default_style, 0);
    lv_style_set_shadow_ofs_x(&gui_list_main_default_style, 0);
    lv_style_set_shadow_ofs_y(&gui_list_main_default_style, 0);
    lv_style_set_border_color(&gui_list_main_default_style, lv_color_make(0xFF, 0xFF, 0xFF));
    lv_style_set_border_width(&gui_list_main_default_style, 0);
    lv_style_set_border_opa(&gui_list_main_default_style, 255);
    lv_style_set_border_side(&gui_list_main_default_style, LV_BORDER_SIDE_FULL);
    lv_style_set_outline_color(&gui_list_main_default_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_outline_width(&gui_list_main_default_style, 0);
    lv_style_set_outline_opa(&gui_list_main_default_style, 128);
    lv_style_set_outline_pad(&gui_list_main_default_style, 0);
    lv_style_set_pad_left(&gui_list_main_default_style, 5);
    lv_style_set_pad_right(&gui_list_main_default_style, 5);
    lv_style_set_pad_top(&gui_list_main_default_style, 7);
    lv_style_set_pad_bottom(&gui_list_main_default_style, 5);
    lv_style_init(&gui_list_main_focused_style);
    lv_style_set_radius(&gui_list_main_focused_style, 10);
    lv_style_set_bg_color(&gui_list_main_focused_style, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_bg_grad_color(&gui_list_main_focused_style, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_bg_grad_dir(&gui_list_main_focused_style, LV_GRAD_DIR_NONE);
    lv_style_set_bg_opa(&gui_list_main_focused_style, 255);
    lv_style_set_shadow_width(&gui_list_main_focused_style, 0);
    lv_style_set_shadow_color(&gui_list_main_focused_style, lv_color_make(0xFF, 0xFF, 0xFF));
    lv_style_set_shadow_opa(&gui_list_main_focused_style, 0);
    lv_style_set_shadow_spread(&gui_list_main_focused_style, 0);
    lv_style_set_shadow_ofs_x(&gui_list_main_focused_style, 0);
    lv_style_set_shadow_ofs_y(&gui_list_main_focused_style, 0);
    lv_style_set_border_color(&gui_list_main_focused_style, lv_color_make(0xFF, 0xFF, 0xFF));
    lv_style_set_border_width(&gui_list_main_focused_style, 0);
    lv_style_set_border_opa(&gui_list_main_focused_style, 255);
    lv_style_set_border_side(&gui_list_main_focused_style, LV_BORDER_SIDE_NONE);
    lv_style_set_outline_color(&gui_list_main_focused_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_outline_width(&gui_list_main_focused_style, 2);
    lv_style_set_outline_opa(&gui_list_main_focused_style, 128);
    lv_style_set_outline_pad(&gui_list_main_focused_style, 2);
    lv_style_set_pad_left(&gui_list_main_focused_style, 5);
    lv_style_set_pad_right(&gui_list_main_focused_style, 5);
    lv_style_set_pad_top(&gui_list_main_focused_style, 2);
    lv_style_set_pad_bottom(&gui_list_main_focused_style, 0);
    lv_style_init(&gui_list_scrollbar_default_style);
    lv_style_set_radius(&gui_list_scrollbar_default_style, 3);
    lv_style_set_bg_color(&gui_list_scrollbar_default_style, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_bg_opa(&gui_list_scrollbar_default_style, 255);
    lv_style_init(&gui_list_btn_main_default_style);
    lv_style_set_radius(&gui_list_btn_main_default_style, 4);
    lv_style_set_bg_color(&gui_list_btn_main_default_style, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_bg_grad_color(&gui_list_btn_main_default_style, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_bg_grad_dir(&gui_list_btn_main_default_style, LV_GRAD_DIR_NONE);
    lv_style_set_bg_opa(&gui_list_btn_main_default_style, 255);
    lv_style_set_border_color(&gui_list_btn_main_default_style, lv_color_make(0xFF, 0xFF, 0xFF));
    lv_style_set_border_width(&gui_list_btn_main_default_style, 1);
    lv_style_set_border_opa(&gui_list_btn_main_default_style, 0);
    lv_style_set_border_side(&gui_list_btn_main_default_style, LV_BORDER_SIDE_BOTTOM | LV_BORDER_SIDE_FULL);
    lv_style_set_text_color(&gui_list_btn_main_default_style, lv_color_make(0x00, 0x00, 0x00));
    lv_style_set_text_font(&gui_list_btn_main_default_style, &lv_font_FangZhengKaiTiJianTi_1_22);
    lv_style_set_text_letter_space(&gui_list_btn_main_default_style, 0);
    lv_style_set_pad_left(&gui_list_btn_main_default_style, 5);
    lv_style_set_pad_right(&gui_list_btn_main_default_style, 5);
    lv_style_set_pad_top(&gui_list_btn_main_default_style, 20);
    lv_style_set_pad_bottom(&gui_list_btn_main_default_style, 20);
    lv_style_init(&gui_list_btn_main_pressed_style);
    lv_style_set_radius(&gui_list_btn_main_pressed_style, 4);
    lv_style_set_bg_color(&gui_list_btn_main_pressed_style, lv_color_make(0x00, 0x00, 0x00));
    lv_style_set_bg_grad_color(&gui_list_btn_main_pressed_style, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_bg_grad_dir(&gui_list_btn_main_pressed_style, LV_GRAD_DIR_NONE);
    lv_style_set_bg_opa(&gui_list_btn_main_pressed_style, 26);
    lv_style_set_border_color(&gui_list_btn_main_pressed_style, lv_color_make(0xe1, 0xe6, 0xee));
    lv_style_set_border_width(&gui_list_btn_main_pressed_style, 1);
    lv_style_set_border_opa(&gui_list_btn_main_pressed_style, 0);
    lv_style_set_border_side(&gui_list_btn_main_pressed_style, LV_BORDER_SIDE_FULL);
    lv_style_set_text_color(&gui_list_btn_main_pressed_style, lv_color_make(0x1B, 0x72, 0xCF));
    lv_style_set_text_font(&gui_list_btn_main_pressed_style, &lv_font_simsun_22);
    lv_style_set_text_letter_space(&gui_list_btn_main_pressed_style, 0);
    lv_style_set_pad_left(&gui_list_btn_main_pressed_style, 5);
    lv_style_set_pad_right(&gui_list_btn_main_pressed_style, 5);
    lv_style_set_pad_top(&gui_list_btn_main_pressed_style, 20);
    lv_style_set_pad_bottom(&gui_list_btn_main_pressed_style, 20);
    lv_style_init(&gui_list_btn_main_focused_style);
    lv_style_set_radius(&gui_list_btn_main_focused_style, 4);
    lv_style_set_bg_color(&gui_list_btn_main_focused_style, lv_color_make(0x00, 0x00, 0x00));
    lv_style_set_bg_grad_color(&gui_list_btn_main_focused_style, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_bg_grad_dir(&gui_list_btn_main_focused_style, LV_GRAD_DIR_NONE);
    lv_style_set_bg_opa(&gui_list_btn_main_focused_style, 13);
    lv_style_set_border_color(&gui_list_btn_main_focused_style, lv_color_make(0xe1, 0xe6, 0xee));
    lv_style_set_border_width(&gui_list_btn_main_focused_style, 1);
    lv_style_set_border_opa(&gui_list_btn_main_focused_style, 0);
    lv_style_set_border_side(&gui_list_btn_main_focused_style, LV_BORDER_SIDE_BOTTOM | LV_BORDER_SIDE_FULL);
    lv_style_set_text_color(&gui_list_btn_main_focused_style, lv_color_make(0x1B, 0x72, 0xCF));
    lv_style_set_text_font(&gui_list_btn_main_focused_style, &lv_font_simsun_22);
    lv_style_set_text_letter_space(&gui_list_btn_main_focused_style, 0);
    lv_style_set_pad_left(&gui_list_btn_main_focused_style, 5);
    lv_style_set_pad_right(&gui_list_btn_main_focused_style, 5);
    lv_style_set_pad_top(&gui_list_btn_main_focused_style, 20);
    lv_style_set_pad_bottom(&gui_list_btn_main_focused_style, 20);
    lv_style_init(&gui_list_txt_main_default_style);
    lv_style_set_radius(&gui_list_txt_main_default_style, 3);
    lv_style_set_bg_color(&gui_list_txt_main_default_style, lv_color_make(0xFF, 0xFF, 0xFF));
    lv_style_set_bg_grad_color(&gui_list_txt_main_default_style, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_bg_grad_dir(&gui_list_txt_main_default_style, LV_GRAD_DIR_NONE);
    lv_style_set_bg_opa(&gui_list_txt_main_default_style, 255);
    lv_style_set_border_color(&gui_list_txt_main_default_style, lv_color_make(0xFF, 0xFF, 0xFF));
    lv_style_set_border_width(&gui_list_txt_main_default_style, 0);
    lv_style_set_border_opa(&gui_list_txt_main_default_style, 255);
    lv_style_set_border_side(&gui_list_txt_main_default_style, LV_BORDER_SIDE_FULL);
    lv_style_set_text_color(&gui_list_txt_main_default_style, lv_color_make(0x00, 0x00, 0x00));
    lv_style_set_text_font(&gui_list_txt_main_default_style, &lv_font_FangZhengKaiTiJianTi_1_22);
    lv_style_set_text_letter_space(&gui_list_txt_main_default_style, 0);
    lv_style_set_pad_left(&gui_list_txt_main_default_style, 5);
    lv_style_set_pad_right(&gui_list_txt_main_default_style, 10);
    lv_style_set_pad_top(&gui_list_txt_main_default_style, 25);
    lv_style_set_pad_bottom(&gui_list_txt_main_default_style, 5);

    // imglist
    lv_style_init(&gui_imglist_main_default_style);
    lv_style_set_radius(&gui_imglist_main_default_style, 0);
    lv_style_set_clip_corner(&gui_imglist_main_default_style, true);
    lv_style_set_bg_color(&gui_imglist_main_default_style, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_bg_grad_color(&gui_imglist_main_default_style, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_bg_grad_dir(&gui_imglist_main_default_style, LV_GRAD_DIR_NONE);
    lv_style_set_bg_opa(&gui_imglist_main_default_style, 0);
    lv_style_set_outline_color(&gui_imglist_main_default_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_outline_width(&gui_imglist_main_default_style, 0);
    lv_style_set_outline_opa(&gui_imglist_main_default_style, 128);
    lv_style_set_outline_pad(&gui_imglist_main_default_style, 0);
    lv_style_set_img_recolor(&gui_imglist_main_default_style, lv_color_make(0xff, 0xff, 0xff));
    lv_style_set_img_recolor_opa(&gui_imglist_main_default_style, 0);
    lv_style_set_img_opa(&gui_imglist_main_default_style, 255);

    // ta
    lv_style_init(&gui_ta_main_default_style);
    lv_style_set_radius(&gui_ta_main_default_style, 4);
    lv_style_set_bg_color(&gui_ta_main_default_style, lv_color_make(0x02, 0x9A, 0xFF));
    lv_style_set_bg_grad_color(&gui_ta_main_default_style, lv_color_make(0xFF, 0xA5, 0xA5));
    lv_style_set_bg_grad_dir(&gui_ta_main_default_style, LV_GRAD_DIR_VER);
    lv_style_set_bg_opa(&gui_ta_main_default_style, 255);
    lv_style_set_shadow_width(&gui_ta_main_default_style, 0);
    lv_style_set_shadow_color(&gui_ta_main_default_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_shadow_opa(&gui_ta_main_default_style, 255);
    lv_style_set_shadow_spread(&gui_ta_main_default_style, 0);
    lv_style_set_shadow_ofs_x(&gui_ta_main_default_style, 0);
    lv_style_set_shadow_ofs_y(&gui_ta_main_default_style, 0);
    lv_style_set_border_color(&gui_ta_main_default_style, lv_color_make(0xe6, 0xe6, 0xe6));
    lv_style_set_border_width(&gui_ta_main_default_style, 2);
    lv_style_set_border_opa(&gui_ta_main_default_style, 255);
    lv_style_set_border_side(&gui_ta_main_default_style, LV_BORDER_SIDE_FULL);
    lv_style_set_outline_color(&gui_ta_main_default_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_outline_width(&gui_ta_main_default_style, 0);
    lv_style_set_outline_opa(&gui_ta_main_default_style, 128);
    lv_style_set_outline_pad(&gui_ta_main_default_style, 0);
    lv_style_set_text_color(&gui_ta_main_default_style, lv_color_make(0x00, 0x00, 0x00));
    lv_style_set_text_font(&gui_ta_main_default_style, &lv_font_FangZhengKaiTiJianTi_1_20);
    lv_style_set_text_letter_space(&gui_ta_main_default_style, 2);
    lv_style_set_text_align(&gui_ta_main_default_style, LV_TEXT_ALIGN_CENTER);
    lv_style_set_pad_left(&gui_ta_main_default_style, 4);
    lv_style_set_pad_right(&gui_ta_main_default_style, 4);
    lv_style_set_pad_top(&gui_ta_main_default_style, 4);
    lv_style_set_pad_bottom(&gui_ta_main_default_style, 4);
    lv_style_init(&gui_ta_scrollbar_default_style);
    lv_style_set_radius(&gui_ta_scrollbar_default_style, 0);
    lv_style_set_bg_color(&gui_ta_scrollbar_default_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_bg_opa(&gui_ta_scrollbar_default_style, 255);

    // textarea
    lv_style_init(&gui_ta_main_default_style);
    lv_style_set_radius(&gui_ta_main_default_style, 4);
    lv_style_set_bg_color(&gui_ta_main_default_style, lv_color_make(0x02, 0x9A, 0xFF));
    lv_style_set_bg_grad_color(&gui_ta_main_default_style, lv_color_make(0xFF, 0xA5, 0xA5));
    lv_style_set_bg_grad_dir(&gui_ta_main_default_style, LV_GRAD_DIR_VER);
    lv_style_set_bg_opa(&gui_ta_main_default_style, 255);
    lv_style_set_shadow_width(&gui_ta_main_default_style, 0);
    lv_style_set_shadow_color(&gui_ta_main_default_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_shadow_opa(&gui_ta_main_default_style, 255);
    lv_style_set_shadow_spread(&gui_ta_main_default_style, 0);
    lv_style_set_shadow_ofs_x(&gui_ta_main_default_style, 0);
    lv_style_set_shadow_ofs_y(&gui_ta_main_default_style, 0);
    lv_style_set_border_color(&gui_ta_main_default_style, lv_color_make(0xe6, 0xe6, 0xe6));
    lv_style_set_border_width(&gui_ta_main_default_style, 2);
    lv_style_set_border_opa(&gui_ta_main_default_style, 255);
    lv_style_set_border_side(&gui_ta_main_default_style, LV_BORDER_SIDE_FULL);
    lv_style_set_outline_color(&gui_ta_main_default_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_outline_width(&gui_ta_main_default_style, 0);
    lv_style_set_outline_opa(&gui_ta_main_default_style, 128);
    lv_style_set_outline_pad(&gui_ta_main_default_style, 0);
    lv_style_set_text_color(&gui_ta_main_default_style, lv_color_make(0x00, 0x00, 0x00));
    lv_style_set_text_font(&gui_ta_main_default_style, &lv_font_FangZhengKaiTiJianTi_1_20);
    lv_style_set_text_letter_space(&gui_ta_main_default_style, 2);
    lv_style_set_text_align(&gui_ta_main_default_style, LV_TEXT_ALIGN_CENTER);
    lv_style_set_pad_left(&gui_ta_main_default_style, 4);
    lv_style_set_pad_right(&gui_ta_main_default_style, 4);
    lv_style_set_pad_top(&gui_ta_main_default_style, 4);
    lv_style_set_pad_bottom(&gui_ta_main_default_style, 4);
    lv_style_init(&gui_ta_scrollbar_default_style);
    lv_style_set_radius(&gui_ta_scrollbar_default_style, 0);
    lv_style_set_bg_color(&gui_ta_scrollbar_default_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_bg_opa(&gui_ta_scrollbar_default_style, 255);

    // btn
    lv_style_init(&gui_btn_main_default_style);
    lv_style_set_radius(&gui_btn_main_default_style, 30);
    lv_style_set_bg_color(&gui_btn_main_default_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_bg_grad_color(&gui_btn_main_default_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_bg_grad_dir(&gui_btn_main_default_style, LV_GRAD_DIR_NONE);
    lv_style_set_bg_opa(&gui_btn_main_default_style, 0);
    lv_style_set_shadow_width(&gui_btn_main_default_style, 0);
    lv_style_set_shadow_color(&gui_btn_main_default_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_shadow_opa(&gui_btn_main_default_style, 255);
    lv_style_set_shadow_spread(&gui_btn_main_default_style, 0);
    lv_style_set_shadow_ofs_x(&gui_btn_main_default_style, 0);
    lv_style_set_shadow_ofs_y(&gui_btn_main_default_style, 0);
    lv_style_set_border_color(&gui_btn_main_default_style, lv_color_make(0xFF, 0x58, 0x03));
    lv_style_set_border_width(&gui_btn_main_default_style, 0);
    lv_style_set_border_opa(&gui_btn_main_default_style, 255);
    lv_style_set_border_side(&gui_btn_main_default_style, LV_BORDER_SIDE_FULL);
    lv_style_set_outline_color(&gui_btn_main_default_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_outline_width(&gui_btn_main_default_style, 0);
    lv_style_set_outline_opa(&gui_btn_main_default_style, 128);
    lv_style_set_outline_pad(&gui_btn_main_default_style, 0);
    lv_style_set_text_color(&gui_btn_main_default_style, lv_color_make(0x00, 0x00, 0x00));
    lv_style_set_text_font(&gui_btn_main_default_style, &lv_font_FangZhengKaiTiJianTi_1_32);
    lv_style_set_text_letter_space(&gui_btn_main_default_style, 0);
    lv_style_set_text_align(&gui_btn_main_default_style, LV_TEXT_ALIGN_CENTER);

}

void ui_style_set(lv_obj_t *obj, gui_ctrl_type_t type)
{
    switch (type) {
    case GUI_CTRL_DIGITALCLOCK:
        lv_obj_add_style(obj, &gui_digitclock_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
        break;
    case GUI_CTRL_IMG:
        lv_obj_add_style(obj, &gui_img_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
        break;
    case GUI_CTRL_SCR:
        lv_obj_add_style(obj, &gui_scr_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
        break;
    case GUI_CTRL_LABEL:
        lv_obj_add_style(obj, &gui_label_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
        break;
    case GUI_CTRL_LIST:
        lv_obj_add_style(obj, &gui_list_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_add_style(obj, &gui_list_main_focused_style, LV_PART_MAIN | LV_STATE_FOCUSED);
        lv_obj_add_style(obj, &gui_list_scrollbar_default_style, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
        lv_obj_add_style(obj, &gui_list_btn_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_add_style(obj, &gui_list_btn_main_pressed_style, LV_PART_MAIN | LV_STATE_PRESSED);
        lv_obj_add_style(obj, &gui_list_btn_main_focused_style, LV_PART_MAIN | LV_STATE_FOCUSED);
        lv_obj_add_style(obj, &gui_list_txt_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
        break;
    case GUI_CTRL_IMGLIST:
        lv_obj_add_style(obj, &gui_imglist_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
        break;
    case GUI_CTRL_TEXTAREA:
        lv_obj_add_style(obj, &gui_ta_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_add_style(obj, &gui_ta_scrollbar_default_style, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
        break;
    case GUI_CTRL_BUTTON:
        lv_obj_add_style(obj, &gui_btn_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
        break;
    default:
        break;
    }
}

