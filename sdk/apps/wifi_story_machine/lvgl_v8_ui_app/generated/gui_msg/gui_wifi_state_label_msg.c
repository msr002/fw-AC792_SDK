/*Generate Code, Do NOT Edit!*/
#include "gui_wifi_state_label_msg.h"
#if LV_USE_MSG

static lv_ll_t subs_ll;

void gui_wifi_state_label_msg_wifi_show_current_ssid_set_text_cb(lv_event_t *e)
{
    lv_obj_t *obj = lv_event_get_target(e);
    if (guider_ui.wifi_del || obj == NULL) {
        return;
    }
    lv_msg_t *msg = (lv_msg_t *)lv_event_get_param(e);
    if (msg == NULL || msg->id != GUI_WIFI_STATE_LABEL_MSG_ID_CUR_SSID) {
        return;
    }

    const char *old_text = lv_textarea_get_text(obj);
    if (strcmp(old_text, guider_msg_data.value_string) != 0) {
        lv_textarea_set_text(obj, guider_msg_data.value_string);
    }
}

GUI_WEAK int gui_wifi_state_label_msg_cur_ssid_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static char cur_ssid_init_var[] = "";
    static bool cur_ssid_is_init = false;
    static char *cur_ssid_var = NULL;
    if (cur_ssid_is_init == false) {
        cur_ssid_var = lv_mem_alloc(strlen(cur_ssid_init_var) + 1);
        strcpy(cur_ssid_var, cur_ssid_init_var);
        cur_ssid_is_init = true;
    }
    if (access == GUI_MSG_ACCESS_SET) {
        lv_mem_free(cur_ssid_var);
        cur_ssid_var = lv_mem_alloc(strlen(data->value_string) + 1);
        strcpy(cur_ssid_var, data->value_string);
    }
    data->value_string = cur_ssid_var;
    return 0;
}

void gui_wifi_state_label_msg_init(lv_ui *ui)
{
    _lv_ll_init(&subs_ll, sizeof(gui_msg_sub_t));
    gui_wifi_state_label_msg_init_ui();
    gui_wifi_state_label_msg_init_events();
}

void gui_wifi_state_label_msg_init_ui()
{
    if (!guider_ui.wifi_del) {
        gui_msg_action_change(GUI_WIFI_STATE_LABEL_MSG_ID_CUR_SSID, GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_STRING);
        lv_textarea_set_text(guider_ui.wifi_show_current_ssid, guider_msg_data.value_string);
    }
}

void gui_wifi_state_label_msg_init_events()
{
    void *res = NULL;
    char sub_ids[1] = {0};
    char unsub_ids[1] = {0};
    int32_t first_id = GUI_WIFI_STATE_LABEL_MSG_ID_CUR_SSID;

    gui_msg_sub_t *head = _lv_ll_get_head(&subs_ll);
    while (head != NULL) {
        gui_msg_sub_t *next = _lv_ll_get_next(&subs_ll, head);
        if (head->data != NULL && lv_obj_is_valid((((gui_msg_sub_dsc_t *)head->data)->_priv_data))) {
            lv_msg_unsubscribe_obj(head->msg_id, ((gui_msg_sub_dsc_t *)head->data)->_priv_data);
        }
        unsub_ids[head->msg_id - first_id] = 1;
        _lv_ll_remove(&subs_ll, head);
        lv_mem_free(head);
        head = next;
    }

    if (!guider_ui.wifi_del) {
        lv_obj_remove_event_cb(guider_ui.wifi_show_current_ssid, gui_wifi_state_label_msg_wifi_show_current_ssid_set_text_cb);
        lv_obj_add_event_cb(guider_ui.wifi_show_current_ssid, gui_wifi_state_label_msg_wifi_show_current_ssid_set_text_cb, LV_EVENT_MSG_RECEIVED, NULL);

        res = lv_msg_subsribe_obj(GUI_WIFI_STATE_LABEL_MSG_ID_CUR_SSID, guider_ui.wifi_show_current_ssid, NULL);
        gui_msg_insert_list(&subs_ll, res);

        sub_ids[GUI_WIFI_STATE_LABEL_MSG_ID_CUR_SSID - first_id] = 1;
    }

    for (int i = 0; i < 1; i++) {
        if (sub_ids[i] == 0 && unsub_ids[i] == 1) {
            gui_msg_subscribe_change(first_id + i, GUI_MSG_UNSUBSCRIBE);
        } else if (sub_ids[i] == 1 && unsub_ids[i] == 0) {
            gui_msg_subscribe_change(first_id + i, GUI_MSG_SUBSCRIBE);
        }
    }
}

void gui_wifi_state_label_msg_unsubscribe()
{
    char msg_ids[1] = {0};
    int32_t first_id = GUI_WIFI_STATE_LABEL_MSG_ID_CUR_SSID;
    gui_msg_sub_t *head = _lv_ll_get_head(&subs_ll);
    while (head != NULL) {
        gui_msg_sub_t *next = _lv_ll_get_next(&subs_ll, head);
        if (head->data != NULL && lv_obj_is_valid((((gui_msg_sub_dsc_t *)head->data)->_priv_data))) {
            lv_msg_unsubscribe_obj(head->msg_id, (((gui_msg_sub_dsc_t *)head->data)->_priv_data));
        }
        msg_ids[head->msg_id - first_id] = 1;
        _lv_ll_remove(&subs_ll, head);
        lv_mem_free(head);
        head = next;
    }
    for (int i = 0; i < 1; i++) {
        if (msg_ids[i] == 1) {
            gui_msg_subscribe_change(first_id + i, GUI_MSG_UNSUBSCRIBE);
        }
    }
}

void gui_wifi_state_label_msg_action_change(int32_t msg_id, gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    switch (msg_id) {
    case GUI_WIFI_STATE_LABEL_MSG_ID_CUR_SSID: {
        gui_wifi_state_label_msg_cur_ssid_cb(access, data, type);
        break;
    }
    default: {
        break;
    }
    }
}

gui_msg_status_t gui_wifi_state_label_msg_send(int32_t msg_id, void *value, int32_t len)
{
    if (msg_id == GUI_WIFI_STATE_LABEL_MSG_ID) {
        lv_msg_send(GUI_WIFI_STATE_LABEL_MSG_ID_CUR_SSID, NULL);
    } else {
        gui_msg_data_type_t data_type = VALUE_INT;
        switch (msg_id) {
        case GUI_WIFI_STATE_LABEL_MSG_ID_CUR_SSID: {
            data_type = VALUE_ARRAY;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
            break;
        }
        default:
            break;
        }
        gui_msg_action_change(msg_id, GUI_MSG_ACCESS_SET, &guider_msg_data, data_type);
        bool found = lv_msg_send(msg_id, NULL);
        return found ? GUI_MSG_STATUS_SUCCESS : GUI_MSG_STATUS_NO_SUBSCRIBE;
    }
    return GUI_MSG_STATUS_SUCCESS;
}

#endif
