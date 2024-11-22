/*Generate Code, Do NOT Edit!*/
#include "gui_blue_msg.h"
#if LV_USE_MSG

static lv_ll_t subs_ll;

void gui_blue_msg_bluetooth_bt_state_set_text_cb(lv_event_t *e)
{
    lv_obj_t *obj = lv_event_get_target(e);
    if (guider_ui.bluetooth_del || obj == NULL) {
        return;
    }
    lv_msg_t *msg = (lv_msg_t *)lv_event_get_param(e);
    if (msg == NULL || msg->id != GUI_BLUE_MSG_ID_BT_STATE) {
        return;
    }

    lv_label_set_text(obj, guider_msg_data.value_string);
}

GUI_WEAK int gui_blue_msg_bt_state_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static char bt_state_init_var[] = "";
    static bool bt_state_is_init = false;
    static char *bt_state_var = NULL;
    if (bt_state_is_init == false) {
        bt_state_var = lv_mem_alloc(strlen(bt_state_init_var) + 1);
        strcpy(bt_state_var, bt_state_init_var);
        bt_state_is_init = true;
    }
    if (access == GUI_MSG_ACCESS_SET) {
        lv_mem_free(bt_state_var);
        bt_state_var = lv_mem_alloc(strlen(data->value_string) + 1);
        strcpy(bt_state_var, data->value_string);
    }
    data->value_string = bt_state_var;
    return 0;
}

void gui_blue_msg_init(lv_ui *ui)
{
    _lv_ll_init(&subs_ll, sizeof(gui_msg_sub_t));
    gui_blue_msg_init_ui();
    gui_blue_msg_init_events();
}

void gui_blue_msg_init_ui()
{
    if (!guider_ui.bluetooth_del) {
        gui_msg_action_change(GUI_BLUE_MSG_ID_BT_STATE, GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_STRING);
        lv_label_set_text(guider_ui.bluetooth_bt_state, guider_msg_data.value_string);
    }
}

void gui_blue_msg_init_events()
{
    void *res = NULL;
    char sub_ids[1] = {0};
    char unsub_ids[1] = {0};
    int32_t first_id = GUI_BLUE_MSG_ID_BT_STATE;

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

    if (!guider_ui.bluetooth_del) {
        lv_obj_remove_event_cb(guider_ui.bluetooth_bt_state, gui_blue_msg_bluetooth_bt_state_set_text_cb);
        lv_obj_add_event_cb(guider_ui.bluetooth_bt_state, gui_blue_msg_bluetooth_bt_state_set_text_cb, LV_EVENT_MSG_RECEIVED, NULL);

        res = lv_msg_subsribe_obj(GUI_BLUE_MSG_ID_BT_STATE, guider_ui.bluetooth_bt_state, NULL);
        gui_msg_insert_list(&subs_ll, res);

        sub_ids[GUI_BLUE_MSG_ID_BT_STATE - first_id] = 1;
    }

    for (int i = 0; i < 1; i++) {
        if (sub_ids[i] == 0 && unsub_ids[i] == 1) {
            gui_msg_subscribe_change(first_id + i, GUI_MSG_UNSUBSCRIBE);
        } else if (sub_ids[i] == 1 && unsub_ids[i] == 0) {
            gui_msg_subscribe_change(first_id + i, GUI_MSG_SUBSCRIBE);
        }
    }
}

void gui_blue_msg_unsubscribe()
{
    char msg_ids[1] = {0};
    int32_t first_id = GUI_BLUE_MSG_ID_BT_STATE;
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

void gui_blue_msg_action_change(int32_t msg_id, gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    switch (msg_id) {
    case GUI_BLUE_MSG_ID_BT_STATE: {
        gui_blue_msg_bt_state_cb(access, data, type);
        break;
    }
    default: {
        break;
    }
    }
}

gui_msg_status_t gui_blue_msg_send(int32_t msg_id, void *value, int32_t len)
{
    if (msg_id == GUI_BLUE_MSG_ID) {
        lv_msg_send(GUI_BLUE_MSG_ID_BT_STATE, NULL);
    } else {
        gui_msg_data_type_t data_type = VALUE_INT;
        switch (msg_id) {
        case GUI_BLUE_MSG_ID_BT_STATE: {
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
