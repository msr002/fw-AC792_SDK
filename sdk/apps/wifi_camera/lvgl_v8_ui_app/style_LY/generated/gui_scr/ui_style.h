#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE
/*Generate Code, Do NOT Edit!*/
#ifndef UI_STYLE_H
#define UI_STYLE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

// digitclock
extern lv_style_t gui_digitclock_main_default_style;
extern lv_style_t gui_digitclock_main_disabled_style;

// img
extern lv_style_t gui_img_main_default_style;
extern lv_style_t gui_img_main_focus_key_style;

// bar
extern lv_style_t gui_bar_main_default_style;
extern lv_style_t gui_bar_indicator_default_style;

// scr
extern lv_style_t gui_scr_main_default_style;

// imgbtn
extern lv_style_t gui_imgbtn_main_default_style;
extern lv_style_t gui_imgbtn_main_pressed_style;
extern lv_style_t gui_imgbtn_main_checked_style;
extern lv_style_t gui_imgbtn_main_focus_key_style;

// ddlist
extern lv_style_t gui_ddlist_main_default_style;
extern lv_style_t gui_ddlist_main_focus_key_style;
extern lv_style_t gui_ddlist_selected_checked_style;
extern lv_style_t gui_ddlist_dropdown_list_default_style;
extern lv_style_t gui_ddlist_scrollbar_default_style;

// label
extern lv_style_t gui_label_main_default_style;
extern lv_style_t gui_label_main_focused_style;

// cont
extern lv_style_t gui_cont_main_default_style;
extern lv_style_t gui_cont_main_focus_key_style;

// btn
extern lv_style_t gui_btn_main_default_style;
extern lv_style_t gui_btn_main_focus_key_style;
extern lv_style_t gui_btn_main_focused_style;

// roller
extern lv_style_t gui_roller_main_default_style;
extern lv_style_t gui_roller_main_focus_key_style;
extern lv_style_t gui_roller_selected_default_style;

// imglist
extern lv_style_t gui_imglist_main_default_style;

// ta
extern lv_style_t gui_ta_main_default_style;
extern lv_style_t gui_ta_scrollbar_default_style;


extern void ui_style_init(void);

#ifdef __cplusplus
}
#endif
#endif /* UI_STYLE_H */

#endif
