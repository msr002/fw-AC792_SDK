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


lv_obj_t *setup_scr_syscfg(lv_ui *ui)
{
    lv_ui_syscfg *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_SYSCFG);
    if (ui_scr == NULL) {
        ui_scr = lv_mem_alloc(sizeof(lv_ui_syscfg));
        memset(ui_scr, 0, sizeof(lv_ui_syscfg));
        ui->syscfg = ui_scr;
    }

    //Write codes syscfg
    ui_scr->syscfg = lv_obj_create(NULL);
    lv_group_t *def_group = lv_group_get_default();
    lv_obj_set_scrollbar_mode(ui_scr->syscfg, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->syscfg, GUI_CTRL_SCR);

    //Write codes syscfg_btn_return
    ui_scr->syscfg_btn_return = lv_btn_create(ui_scr->syscfg);
    lv_obj_set_pos(ui_scr->syscfg_btn_return, 11, 20);
    lv_obj_set_size(ui_scr->syscfg_btn_return, 460, 67);
    lv_obj_set_scrollbar_mode(ui_scr->syscfg_btn_return, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->syscfg_btn_return, LV_OBJ_FLAG_EVENT_BUBBLE);
    ui_style_set(ui_scr->syscfg_btn_return, GUI_CTRL_BUTTON);
    ui_scr->syscfg_btn_return_label = lv_label_create(ui_scr->syscfg_btn_return);
    lv_obj_set_style_pad_all(ui_scr->syscfg_btn_return, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->syscfg_btn_return_label, LV_ALIGN_CENTER, 0, 0);

    //Write codes syscfg_list_sysset
    ui_scr->syscfg_list_sysset = lv_list_create(ui_scr->syscfg);
    lv_obj_set_pos(ui_scr->syscfg_list_sysset, 7, 284);
    lv_obj_set_size(ui_scr->syscfg_list_sysset, 466, 212);
    lv_obj_set_scrollbar_mode(ui_scr->syscfg_list_sysset, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->syscfg_list_sysset, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_clear_flag(ui_scr->syscfg_list_sysset, LV_OBJ_FLAG_SCROLLABLE);
    ui_style_set(ui_scr->syscfg_list_sysset, GUI_CTRL_LIST);

    //Set style state: LV_STATE_DEFAULT for style_syscfg_list_sysset_extra_btns_main_default
    static lv_style_t style_syscfg_list_sysset_extra_btns_main_default;
    ui_init_style(&style_syscfg_list_sysset_extra_btns_main_default);

    //Set style state: LV_STATE_PRESSED for style_syscfg_list_sysset_extra_btns_main_pressed
    static lv_style_t style_syscfg_list_sysset_extra_btns_main_pressed;
    ui_init_style(&style_syscfg_list_sysset_extra_btns_main_pressed);

    //Set style state: LV_STATE_FOCUSED for style_syscfg_list_sysset_extra_btns_main_focused
    static lv_style_t style_syscfg_list_sysset_extra_btns_main_focused;
    ui_init_style(&style_syscfg_list_sysset_extra_btns_main_focused);

    //Set style state: LV_STATE_DEFAULT for style_syscfg_list_sysset_extra_texts_main_default
    static lv_style_t style_syscfg_list_sysset_extra_texts_main_default;
    ui_init_style(&style_syscfg_list_sysset_extra_texts_main_default);

    //Delete extra default style for syscfg_list_sysset
    lv_obj_remove_style(ui_scr->syscfg_list_sysset, &gui_list_btn_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(ui_scr->syscfg_list_sysset, &gui_list_btn_main_pressed_style, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_remove_style(ui_scr->syscfg_list_sysset, &gui_list_btn_main_focused_style, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_remove_style(ui_scr->syscfg_list_sysset, &gui_list_txt_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *syscfg_list_sysset_item;
    syscfg_list_sysset_item = lv_list_add_btn(ui_scr->syscfg_list_sysset, NULL, " <  返回");
    ui_scr->syscfg_list_sysset_item0 = syscfg_list_sysset_item;
    lv_obj_add_style(syscfg_list_sysset_item, &gui_list_btn_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(syscfg_list_sysset_item, &style_syscfg_list_sysset_extra_btns_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_style(syscfg_list_sysset_item, &gui_list_btn_main_pressed_style, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_add_style(syscfg_list_sysset_item, &style_syscfg_list_sysset_extra_btns_main_pressed, LV_PART_MAIN | LV_STATE_PRESSED);

    lv_obj_add_style(syscfg_list_sysset_item, &gui_list_btn_main_focused_style, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_add_style(syscfg_list_sysset_item, &style_syscfg_list_sysset_extra_btns_main_focused, LV_PART_MAIN | LV_STATE_FOCUSED);

    syscfg_list_sysset_item = lv_list_add_btn(ui_scr->syscfg_list_sysset, NULL, "   休眠时长                                    永不");
    ui_scr->syscfg_list_sysset_item1 = syscfg_list_sysset_item;
    lv_obj_add_style(syscfg_list_sysset_item, &gui_list_btn_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(syscfg_list_sysset_item, &style_syscfg_list_sysset_extra_btns_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_style(syscfg_list_sysset_item, &gui_list_btn_main_pressed_style, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_add_style(syscfg_list_sysset_item, &style_syscfg_list_sysset_extra_btns_main_pressed, LV_PART_MAIN | LV_STATE_PRESSED);

    lv_obj_add_style(syscfg_list_sysset_item, &gui_list_btn_main_focused_style, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_add_style(syscfg_list_sysset_item, &style_syscfg_list_sysset_extra_btns_main_focused, LV_PART_MAIN | LV_STATE_FOCUSED);

    syscfg_list_sysset_item = lv_list_add_btn(ui_scr->syscfg_list_sysset, NULL, "   天气显示                                     开");
    ui_scr->syscfg_list_sysset_item2 = syscfg_list_sysset_item;
    lv_obj_add_style(syscfg_list_sysset_item, &gui_list_btn_main_default_style, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(syscfg_list_sysset_item, &style_syscfg_list_sysset_extra_btns_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_style(syscfg_list_sysset_item, &gui_list_btn_main_pressed_style, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_add_style(syscfg_list_sysset_item, &style_syscfg_list_sysset_extra_btns_main_pressed, LV_PART_MAIN | LV_STATE_PRESSED);

    lv_obj_add_style(syscfg_list_sysset_item, &gui_list_btn_main_focused_style, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_add_style(syscfg_list_sysset_item, &style_syscfg_list_sysset_extra_btns_main_focused, LV_PART_MAIN | LV_STATE_FOCUSED);


    lv_obj_update_layout(ui_scr->syscfg);
    ui_scr->syscfg_del = false;
    i18n_refresh_texts("syscfg");

    //Init events for screen
    events_init_syscfg(ui);
    return ui_scr->syscfg;
}
void unload_scr_syscfg(lv_ui *ui)
{
    ui_free_scr_ptr(ui, GUI_SCREEN_SYSCFG);
}
