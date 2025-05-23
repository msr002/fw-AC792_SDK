/*Generate Code, Do NOT Edit!*/
#ifndef UI_STYLE_H
#define UI_STYLE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

// digitclock
extern lv_style_t gui_digitclock_main_default_style;

// digital_clock
extern lv_style_t gui_digitclock_main_default_style;

// img
extern lv_style_t gui_img_main_default_style;

// scr
extern lv_style_t gui_scr_main_default_style;

// label
extern lv_style_t gui_label_main_default_style;

// list
extern lv_style_t gui_list_main_default_style;
extern lv_style_t gui_list_main_focused_style;
extern lv_style_t gui_list_scrollbar_default_style;
extern lv_style_t gui_list_btn_main_default_style;
extern lv_style_t gui_list_btn_main_pressed_style;
extern lv_style_t gui_list_btn_main_focused_style;
extern lv_style_t gui_list_txt_main_default_style;

// imglist
extern lv_style_t gui_imglist_main_default_style;

// ta
extern lv_style_t gui_ta_main_default_style;
extern lv_style_t gui_ta_scrollbar_default_style;

// textarea
extern lv_style_t gui_ta_main_default_style;
extern lv_style_t gui_ta_scrollbar_default_style;

// btn
extern lv_style_t gui_btn_main_default_style;

enum {
    GUI_CTRL_DIGITALCLOCK,
    GUI_CTRL_IMG,
    GUI_CTRL_SCR,
    GUI_CTRL_LABEL,
    GUI_CTRL_LIST,
    GUI_CTRL_IMGLIST,
    GUI_CTRL_TEXTAREA,
    GUI_CTRL_BUTTON,
};
typedef uint8_t gui_ctrl_type_t;

extern void ui_style_init(void);
extern void ui_style_set(lv_obj_t *obj, gui_ctrl_type_t type);

#ifdef __cplusplus
}
#endif
#endif /* UI_STYLE_H */
