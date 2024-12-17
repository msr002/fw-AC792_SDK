/*Generate Code, Do NOT Edit!*/
#include "./gui_rt_stream_msg.h"
#if LV_USE_OBSERVER

static lv_ll_t subs_ll;


GUI_WEAK int gui_rt_stream_msg_camera_switch_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static bool camera_switch_var = false;
    if (access == GUI_MSG_ACCESS_SET) {
        camera_switch_var = data->value_int;
    }
    data->value_int = camera_switch_var;
    return 0;
}

void gui_rt_stream_msg_init(lv_ui *ui)
{
    gui_msg_sub_t *sub;
    sub = gui_msg_create_sub(GUI_RT_STREAM_MSG_ID_CAMERA_SWITCH);
    if (sub != NULL) {
        lv_subject_init_pointer(sub->subject, &guider_msg_data);
    }
    gui_rt_stream_msg_init_ui();
    gui_rt_stream_msg_init_events();
}

void gui_rt_stream_msg_init_ui()
{
}

void gui_rt_stream_msg_init_events()
{
    void *res = NULL;
    _gui_msg_status_t status[1] = {
        {GUI_RT_STREAM_MSG_ID_CAMERA_SWITCH, 0, 0},
    };

    for (int i = 0; i < 1; i++) {
        lv_subject_t *subject = gui_msg_get_subject(status[i].msg_id);
        if (subject == NULL) {
            continue;
        }
        lv_ll_t subject_ll = subject->subs_ll;
        gui_msg_sub_t *head = _lv_ll_get_head(&subject_ll);
        if (head != NULL) {
            status[i].is_unsubscribe = 1;
        }
    }

    lv_subject_t *subject_camera_switch = gui_msg_get_subject(GUI_RT_STREAM_MSG_ID_CAMERA_SWITCH);
    if (!guider_ui.rt_stream_del) {
        gui_rt_stream_msg_camera_switch_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_BOOL);
        lv_subject_add_observer_obj(subject_camera_switch, gui_msg_set_visible_by_bool_cb, guider_ui.rt_stream_imgbtn_1, &guider_msg_data);


        for (int i = 0; i < 1; i++) {
            if (status[i].msg_id == GUI_RT_STREAM_MSG_ID_CAMERA_SWITCH) {
                status[i].is_subscribe = 1;
            }
        }
    }

    for (int i = 0; i < 1; i++) {
        if (status[i].is_subscribe == 0 && status[i].is_unsubscribe == 1) {
            gui_msg_subscribe_change(status[i].msg_id, GUI_MSG_UNSUBSCRIBE);
        } else if (status[i].is_subscribe == 1 && status[i].is_unsubscribe == 0) {
            gui_msg_subscribe_change(status[i].msg_id, GUI_MSG_SUBSCRIBE);
        }
    }
}

void gui_rt_stream_msg_unsubscribe()
{
    _gui_msg_status_t status[1] = {
        {GUI_RT_STREAM_MSG_ID_CAMERA_SWITCH, 0, 0},
    };
    for (int i = 0; i < 1; i++) {
        lv_subject_t *subject = gui_msg_get_subject(status[i].msg_id);
        if (subject == NULL) {
            continue;
        }
        lv_ll_t subject_ll = subject->subs_ll;
        lv_observer_t *head = _lv_ll_get_head(&subject_ll);
        if (head != NULL) {
            status[i].is_unsubscribe = 1;
        }
        while (head != NULL) {
            lv_obj_t *obj = head->target;
            if (obj != NULL && lv_obj_is_valid(obj) == true) {
                lv_subject_remove_all_obj(subject, obj);
            }
            head = _lv_ll_get_head(&subject_ll);
        }
    }

    for (int i = 0; i < 1; i++) {
        if (status[i].is_unsubscribe == 1) {
            gui_msg_subscribe_change(status[i].msg_id, GUI_MSG_UNSUBSCRIBE);
        }
    }
}

gui_msg_data_t *gui_rt_stream_msg_get(int32_t msg_id)
{
    switch (msg_id) {
    case GUI_RT_STREAM_MSG_ID_CAMERA_SWITCH: {
        gui_rt_stream_msg_camera_switch_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_BOOL);
        break;
    }
    default:
        return NULL;
    }
    return &guider_msg_data;
}

void gui_rt_stream_msg_action_change(int32_t msg_id, gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    switch (msg_id) {
    case GUI_RT_STREAM_MSG_ID_CAMERA_SWITCH: {
        gui_rt_stream_msg_camera_switch_cb(access, data, type);
        break;
    }
    default: {
        break;
    }
    }
}

gui_msg_status_t gui_rt_stream_msg_send(int32_t msg_id, void *value, int32_t len)
{
    if (msg_id == GUI_RT_STREAM_MSG_ID) {
    } else {
        gui_msg_data_type_t data_type = VALUE_INT;
        switch (msg_id) {
        case GUI_RT_STREAM_MSG_ID_CAMERA_SWITCH: {
            data_type = VALUE_BOOL;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
            break;
        }
        default:
            break;
        }
        gui_msg_action_change(msg_id, GUI_MSG_ACCESS_SET, &guider_msg_data, data_type);
        lv_subject_t *subject = gui_msg_get_subject(msg_id);
        if (subject == NULL) {
            return GUI_MSG_STATUS_NO_SUBSCRIBE;
        }
        lv_subject_set_pointer(subject, &guider_msg_data);
    }
    return GUI_MSG_STATUS_SUCCESS;
}

#endif
