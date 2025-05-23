/*Generate Code, Do NOT Edit!*/
#include "./gui_group.h"

void add_children_to_group(lv_obj_t *obj, lv_group_t *group);
void set_default_group_cb();

void gui_group_init()
{
    if (guider_ui.default_group == NULL) {
        guider_ui.default_group = lv_group_get_default();
    }
}

void gui_group_set_default(lv_group_t *group)
{
    if (group == NULL) {
        return;
    }

    if (guider_ui.default_group == group) {
        return set_default_group_cb();
    }
}

void gui_group_add_obj(lv_group_t *group, lv_obj_t *obj, bool is_add)
{
    if (group == NULL || obj == NULL) {
        return;
    }

    bool is_group_def = lv_obj_is_group_def(obj);
    if (is_group_def && is_add) {
        lv_group_add_obj(group, obj);
    }

    if (lv_obj_check_type(obj, &lv_list_class) ||
        lv_obj_check_type(obj, &lv_calendar_class) ||
        lv_obj_check_type(obj, &lv_msgbox_class) ||
        lv_obj_check_type(obj, &lv_tabview_class) ||
        lv_obj_check_type(obj, &lv_calendar_header_arrow_class) ||
        lv_obj_check_type(obj, &lv_calendar_header_dropdown_class)) {
        add_children_to_group(obj, group);
    } else if (lv_obj_check_type(obj, &lv_win_class)) {
        lv_obj_t *header = lv_win_get_header(obj);
        add_children_to_group(header, group);
    }

    if (!is_group_def && is_add) {
        lv_group_add_obj(group, obj);
    }
}

void add_children_to_group(lv_obj_t *obj, lv_group_t *group)
{
    if (obj == NULL || group == NULL) {
        return;
    }

    int childCnt = lv_obj_get_child_cnt(obj);
    for (int i = 0; i < childCnt; i++) {
        lv_obj_t *child = lv_obj_get_child(obj, i);
        if (lv_obj_is_group_def(child)) {
            lv_group_add_obj(group, child);
        }
    }
}

void set_default_group_cb()
{
    if (guider_ui.default_group == NULL) {
        return;
    }

    lv_group_remove_all_objs(guider_ui.default_group);
    int32_t act_scr_id = gui_scr_get_id(gui_scr_get_act());

    if (act_scr_id == GUI_SCREEN_MENU) {
        lv_ui_menu *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_MENU);
        gui_group_add_obj(guider_ui.default_group, ui_scr->menu_edit_return, true);
        gui_group_add_obj(guider_ui.default_group, ui_scr->menu_edit_download, true);
        gui_group_add_obj(guider_ui.default_group, ui_scr->menu_edit_netcfg, true);
        gui_group_add_obj(guider_ui.default_group, ui_scr->menu_edit_language, true);
        gui_group_add_obj(guider_ui.default_group, ui_scr->menu_edit_sysset, true);
        gui_group_add_obj(guider_ui.default_group, ui_scr->menu_edit_sysinfo, true);
    } else if (act_scr_id == GUI_SCREEN_LANGUAGE) {
        lv_ui_language *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_LANGUAGE);
        gui_group_add_obj(guider_ui.default_group, ui_scr->language_btn_return, true);
        gui_group_add_obj(guider_ui.default_group, ui_scr->language_list_language, false);
    } else if (act_scr_id == GUI_SCREEN_APP) {
        lv_ui_app *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_APP);
        gui_group_add_obj(guider_ui.default_group, ui_scr->app_btn_return, true);
    } else if (act_scr_id == GUI_SCREEN_SYSCFG) {
        lv_ui_syscfg *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_SYSCFG);
        gui_group_add_obj(guider_ui.default_group, ui_scr->syscfg_btn_return, true);
        gui_group_add_obj(guider_ui.default_group, ui_scr->syscfg_list_sysset, false);
    } else if (act_scr_id == GUI_SCREEN_SYSINFO) {
        lv_ui_sysinfo *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_SYSINFO);
        gui_group_add_obj(guider_ui.default_group, ui_scr->sysinfo_btn_return, true);
    }
    lv_group_set_default(guider_ui.default_group);

    lv_indev_t *indev = NULL;
    while ((indev = lv_indev_get_next(indev)) != NULL) {
        lv_indev_set_group(indev, guider_ui.default_group);
    }
}
