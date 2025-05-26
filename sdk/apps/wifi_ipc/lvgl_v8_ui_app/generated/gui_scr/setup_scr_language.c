/*Generate Code, Do NOT Edit!*/
#include "lvgl.h"
#if LV_USE_GUIBUILDER_SIMULATOR
#include <stdio.h>
#endif
#include <stdlib.h>
#include "../gui_guider.h"
#include "../gui_events/events_init.h"
#include "../gui_events/callback_handler.h"
#include "../gui_events/i18n_handler.h"
#include "../gui_timelines/gui_timelines.h"
#include "../../custom/custom.h"


lv_obj_t *setup_scr_language(lv_ui *ui)
{
    lv_ui_language *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_LANGUAGE);
    if (ui_scr == NULL) {
        ui_scr = lv_mem_alloc(sizeof(lv_ui_language));
        memset(ui_scr, 0, sizeof(lv_ui_language));
        ui->language = ui_scr;
    }

    //Write codes language
    ui_scr->language = lv_obj_create(NULL);
    lv_group_t *def_group = lv_group_get_default();
    lv_obj_set_scrollbar_mode(ui_scr->language, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->language, GUI_CTRL_SCR);

    //Write codes language_btn_return
    ui_scr->language_btn_return = lv_btn_create(ui_scr->language);
    lv_obj_set_pos(ui_scr->language_btn_return, 11, 20);
    lv_obj_set_size(ui_scr->language_btn_return, 460, 67);
    lv_obj_set_scrollbar_mode(ui_scr->language_btn_return, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->language_btn_return, LV_OBJ_FLAG_EVENT_BUBBLE);
    ui_style_set(ui_scr->language_btn_return, GUI_CTRL_BUTTON);
    ui_scr->language_btn_return_label = lv_label_create(ui_scr->language_btn_return);
    lv_obj_set_style_pad_all(ui_scr->language_btn_return, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->language_btn_return_label, LV_ALIGN_CENTER, 0, 0);

    //Write codes language_list_language
    ui_scr->language_list_language = lv_list_create(ui_scr->language);
    lv_obj_set_pos(ui_scr->language_list_language, 6, 266);
    lv_obj_set_size(ui_scr->language_list_language, 465, 210);
    lv_obj_set_scrollbar_mode(ui_scr->language_list_language, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->language_list_language, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_clear_flag(ui_scr->language_list_language, LV_OBJ_FLAG_SCROLLABLE);
    ui_style_set(ui_scr->language_list_language, GUI_CTRL_LIST);

    //Set style state: LV_STATE_DEFAULT for style_language_list_language_extra_btns_main_default
    static lv_style_t style_language_list_language_extra_btns_main_default;
    ui_init_style(&style_language_list_language_extra_btns_main_default);

    //Set style state: LV_STATE_PRESSED for style_language_list_language_extra_btns_main_pressed
    static lv_style_t style_language_list_language_extra_btns_main_pressed;
    ui_init_style(&style_language_list_language_extra_btns_main_pressed);

    //Set style state: LV_STATE_FOCUSED for style_language_list_language_extra_btns_main_focused
    static lv_style_t style_language_list_language_extra_btns_main_focused;
    ui_init_style(&style_language_list_language_extra_btns_main_focused);

    //Set style state: LV_STATE_DEFAULT for style_language_list_language_extra_texts_main_default
    static lv_style_t style_language_list_language_extra_texts_main_default;
    ui_init_style(&style_language_list_language_extra_texts_main_default);

    //Delete extra default style for language_list_language
    lv_obj_remove_style(ui_scr->language_list_language, &gui_list_btn_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(ui_scr->language_list_language, &gui_list_btn_main_pressed_style, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_remove_style(ui_scr->language_list_language, &gui_list_btn_main_focused_style, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_remove_style(ui_scr->language_list_language, &gui_list_txt_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *language_list_language_item;
    language_list_language_item = lv_list_add_btn(ui_scr->language_list_language, NULL, "   <  返回");
    ui_scr->language_list_language_item0 = language_list_language_item;
    lv_obj_add_style(language_list_language_item, &gui_list_btn_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(language_list_language_item, &style_language_list_language_extra_btns_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_style(language_list_language_item, &gui_list_btn_main_pressed_style, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_add_style(language_list_language_item, &style_language_list_language_extra_btns_main_pressed, LV_PART_MAIN | LV_STATE_PRESSED);

    lv_obj_add_style(language_list_language_item, &gui_list_btn_main_focused_style, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_add_style(language_list_language_item, &style_language_list_language_extra_btns_main_focused, LV_PART_MAIN | LV_STATE_FOCUSED);

    language_list_language_item = lv_list_add_btn(ui_scr->language_list_language, NULL, "     中文                                         设置");
    ui_scr->language_list_language_item1 = language_list_language_item;
    lv_obj_add_style(language_list_language_item, &gui_list_btn_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(language_list_language_item, &style_language_list_language_extra_btns_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_style(language_list_language_item, &gui_list_btn_main_pressed_style, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_add_style(language_list_language_item, &style_language_list_language_extra_btns_main_pressed, LV_PART_MAIN | LV_STATE_PRESSED);

    lv_obj_add_style(language_list_language_item, &gui_list_btn_main_focused_style, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_add_style(language_list_language_item, &style_language_list_language_extra_btns_main_focused, LV_PART_MAIN | LV_STATE_FOCUSED);

    language_list_language_item = lv_list_add_btn(ui_scr->language_list_language, NULL, "     英文                                         设置");
    ui_scr->language_list_language_item2 = language_list_language_item;
    lv_obj_add_style(language_list_language_item, &gui_list_btn_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(language_list_language_item, &style_language_list_language_extra_btns_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_style(language_list_language_item, &gui_list_btn_main_pressed_style, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_add_style(language_list_language_item, &style_language_list_language_extra_btns_main_pressed, LV_PART_MAIN | LV_STATE_PRESSED);

    lv_obj_add_style(language_list_language_item, &gui_list_btn_main_focused_style, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_add_style(language_list_language_item, &style_language_list_language_extra_btns_main_focused, LV_PART_MAIN | LV_STATE_FOCUSED);


    lv_obj_update_layout(ui_scr->language);
    ui_scr->language_del = false;
    i18n_refresh_texts("language");

    //Init events for screen
    events_init_language(ui);
    return ui_scr->language;
}
void unload_scr_language(lv_ui *ui)
{
    ui_free_scr_ptr(ui, GUI_SCREEN_LANGUAGE);
}
