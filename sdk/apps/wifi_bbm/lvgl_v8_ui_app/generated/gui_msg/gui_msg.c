/*Generate Code, Do NOT Edit!*/
#include "./gui_msg.h"

gui_msg_data_t guider_msg_data = {0};
gui_msg_send_status_t gui_msg_send_status = GUI_MSG_SEND_DONE;
static lv_ll_t subs_ll;

void gui_msg_init(lv_ui *ui)
{
#if LV_USE_OBSERVER
    _lv_ll_init(&subs_ll, sizeof(gui_msg_sub_t));
    gui_pair_msg_init(ui);
    gui_rt_stream_msg_init(ui);
    gui_file_browser_msg_init(ui);
#endif
}
void gui_msg_init_ui()
{
#if LV_USE_OBSERVER
    gui_pair_msg_init_ui();
    gui_rt_stream_msg_init_ui();
    gui_file_browser_msg_init_ui();
#endif
}
void gui_msg_init_events()
{
#if LV_USE_OBSERVER
    gui_pair_msg_init_events();
    gui_rt_stream_msg_init_events();
    gui_file_browser_msg_init_events();
#endif
}
void gui_msg_unsubscribe()
{
#if LV_USE_OBSERVER
    gui_pair_msg_unsubscribe();
    gui_rt_stream_msg_unsubscribe();
    gui_file_browser_msg_unsubscribe();
#endif
}
gui_msg_status_t gui_msg_send(int32_t msg_id, void *value, int32_t len)
{
#if LV_USE_OBSERVER
    gui_msg_send_status = GUI_MSG_SENDING;
    gui_msg_status_t ret;
    switch (msg_id) {
    case GUI_PAIR_MSG_ID_PAIR_CH0:
    case GUI_PAIR_MSG_ID_PAIR_CH1:
    case GUI_PAIR_MSG_ID_PAIR_CH2:
    case GUI_PAIR_MSG_ID_PAIR_CH3:
    case GUI_PAIR_MSG_ID_PAIR_CH4:
    case GUI_PAIR_MSG_ID_PAIR_CH5:
    case GUI_PAIR_MSG_ID_PARING_LAB:
    case GUI_PAIR_MSG_ID_UNPAIR_LAB:
        ret = gui_pair_msg_send(msg_id, value, len);
        gui_msg_send_status = GUI_MSG_SEND_DONE;
        return ret;

    case GUI_RT_STREAM_MSG_ID_CAMERA_SWITCH:
        ret = gui_rt_stream_msg_send(msg_id, value, len);
        gui_msg_send_status = GUI_MSG_SEND_DONE;
        return ret;

    case GUI_FILE_BROWSER_MSG_ID_FILE_NUM:
        ret = gui_file_browser_msg_send(msg_id, value, len);
        gui_msg_send_status = GUI_MSG_SEND_DONE;
        return ret;

    default:
        break;
    }
    gui_msg_send_status = GUI_MSG_SEND_DONE;
    return GUI_MSG_STATUS_NO_FOUND_ID;
#else
    return GUI_MSG_STATUS_ERROR;
#endif
}
gui_msg_send_status_t gui_msg_get_send_status()
{
    return gui_msg_send_status;
}
GUI_WEAK gui_msg_data_t *gui_msg_get(int32_t msg_id)
{
    return gui_msg_get_guider(msg_id);
}
gui_msg_data_t *gui_msg_get_guider(int32_t msg_id)
{
#if LV_USE_OBSERVER
    switch (msg_id) {
    case GUI_PAIR_MSG_ID:
    case GUI_PAIR_MSG_ID_PAIR_CH0:
    case GUI_PAIR_MSG_ID_PAIR_CH1:
    case GUI_PAIR_MSG_ID_PAIR_CH2:
    case GUI_PAIR_MSG_ID_PAIR_CH3:
    case GUI_PAIR_MSG_ID_PAIR_CH4:
    case GUI_PAIR_MSG_ID_PAIR_CH5:
    case GUI_PAIR_MSG_ID_PARING_LAB:
    case GUI_PAIR_MSG_ID_UNPAIR_LAB:
        return gui_pair_msg_get(msg_id);

    case GUI_RT_STREAM_MSG_ID:
    case GUI_RT_STREAM_MSG_ID_CAMERA_SWITCH:
        return gui_rt_stream_msg_get(msg_id);

    case GUI_FILE_BROWSER_MSG_ID:
    case GUI_FILE_BROWSER_MSG_ID_FILE_NUM:
        return gui_file_browser_msg_get(msg_id);

    default:
        break;
    }
#endif
    return NULL;
}
GUI_WEAK void gui_msg_action_change(int32_t msg_id, gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    gui_msg_action_change_guider(msg_id, access, data, type);
}
void gui_msg_action_change_guider(int32_t msg_id, gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
#if LV_USE_OBSERVER
    switch (msg_id) {
    case GUI_PAIR_MSG_ID:
    case GUI_PAIR_MSG_ID_PAIR_CH0:
    case GUI_PAIR_MSG_ID_PAIR_CH1:
    case GUI_PAIR_MSG_ID_PAIR_CH2:
    case GUI_PAIR_MSG_ID_PAIR_CH3:
    case GUI_PAIR_MSG_ID_PAIR_CH4:
    case GUI_PAIR_MSG_ID_PAIR_CH5:
    case GUI_PAIR_MSG_ID_PARING_LAB:
    case GUI_PAIR_MSG_ID_UNPAIR_LAB:
        return gui_pair_msg_action_change(msg_id, access, data, type);

    case GUI_RT_STREAM_MSG_ID:
    case GUI_RT_STREAM_MSG_ID_CAMERA_SWITCH:
        return gui_rt_stream_msg_action_change(msg_id, access, data, type);

    case GUI_FILE_BROWSER_MSG_ID:
    case GUI_FILE_BROWSER_MSG_ID_FILE_NUM:
        return gui_file_browser_msg_action_change(msg_id, access, data, type);

    default:
        break;
    }
#endif
}
GUI_WEAK void gui_msg_subscribe_change(int32_t msg_id, gui_msg_subscribe_t sub_type)
{
    gui_msg_subscribe_change_guider(msg_id, sub_type);
}
void gui_msg_subscribe_change_guider(int32_t msg_id, gui_msg_subscribe_t sub_type)
{
}
lv_subject_t *gui_msg_get_subject(int32_t msg_id)
{
    gui_msg_sub_t *sub = gui_msg_get_sub(msg_id);
    if (sub != NULL) {
        return sub->subject;
    }
    return NULL;
}
gui_msg_sub_t *gui_msg_get_sub(int32_t msg_id)
{
    gui_msg_sub_t *head = _lv_ll_get_head(&subs_ll);
    while (head != NULL) {
        if (head->msg_id == msg_id) {
            return head;
        }
        head = _lv_ll_get_next(&subs_ll, head);
    }
    return NULL;
}
gui_msg_sub_t *gui_msg_create_sub(int32_t msg_id)
{
    gui_msg_sub_t *sub = gui_msg_get_sub(msg_id);
    if (sub == NULL) {
        sub = _lv_ll_ins_tail(&subs_ll);
        sub->msg_id = msg_id;
        sub->subject = lv_mem_alloc(sizeof(lv_subject_t));
    }
    return sub;
}
gui_msg_data_t *gui_msg_get_data()
{
    return &guider_msg_data;
}

void gui_msg_set_imglist_selected_index_by_int32_cb(lv_observer_t *observer, lv_subject_t *subject)
{
    lv_obj_t *obj = lv_observer_get_target_obj(observer);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    gui_msg_data_t *data = (gui_msg_data_t *)observer->user_data;
    lv_imglist_set_act(obj, data->value_int);
}
void gui_msg_set_visible_by_bool_cb(lv_observer_t *observer, lv_subject_t *subject)
{
    lv_obj_t *obj = lv_observer_get_target_obj(observer);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    gui_msg_data_t *data = (gui_msg_data_t *)observer->user_data;
    if (data->value_bool) {
        lv_obj_clear_flag(obj, LV_OBJ_FLAG_HIDDEN);
    } else {
        lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
    }
}
void gui_msg_set_label_text_by_string_cb(lv_observer_t *observer, lv_subject_t *subject)
{
    lv_obj_t *obj = lv_observer_get_target_obj(observer);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    gui_msg_data_t *data = (gui_msg_data_t *)observer->user_data;
    lv_label_set_text(obj, data->value_string);
}
