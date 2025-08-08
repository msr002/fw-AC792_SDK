/*Generate Code, Do NOT Edit!*/
#include "./ui_style.h"
#include "../gui_guider.h"

// scr
lv_style_t gui_scr_main_default_style;

void ui_style_init(void)
{
    // scr
    lv_style_init(&gui_scr_main_default_style);
    lv_style_set_bg_color(&gui_scr_main_default_style, lv_color_make(0xFF, 0xFF, 0xFF));
    lv_style_set_bg_grad_color(&gui_scr_main_default_style, lv_color_make(0xFF, 0xFF, 0xFF));
    lv_style_set_bg_grad_dir(&gui_scr_main_default_style, LV_GRAD_DIR_NONE);
    lv_style_set_bg_opa(&gui_scr_main_default_style, 0);
    lv_style_set_border_color(&gui_scr_main_default_style, lv_color_make(0x21, 0x95, 0xf6));
    lv_style_set_border_width(&gui_scr_main_default_style, 0);
    lv_style_set_border_opa(&gui_scr_main_default_style, 255);

}

void ui_style_set(lv_obj_t *obj, gui_ctrl_type_t type)
{
    switch (type) {
    case GUI_CTRL_SCR:
        lv_obj_add_style(obj, &gui_scr_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
        break;
    default:
        break;
    }
}

