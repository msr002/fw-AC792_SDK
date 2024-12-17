/*Generate Code, Do NOT Edit!*/
#include "./gui_file_browser_msg.h"
#if LV_USE_OBSERVER

static lv_ll_t subs_ll;


GUI_WEAK int gui_file_browser_msg_file_num_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    char file_num_init_var[] = "0/0";
    static bool file_num_is_init = false;
    static char *file_num_var = NULL;
    if (file_num_is_init == false) {
        file_num_var = lv_mem_alloc(strlen(file_num_init_var) + 1);
        strcpy(file_num_var, file_num_init_var);
        file_num_is_init = true;
    }
    if (access == GUI_MSG_ACCESS_SET) {
        lv_mem_free(file_num_var);
        file_num_var = lv_mem_alloc(strlen(data->value_string) + 1);
        strcpy(file_num_var, data->value_string);
    }
    data->value_string = file_num_var;
    return 0;
}

void gui_file_browser_msg_init(lv_ui *ui)
{
    gui_msg_sub_t *sub;
    sub = gui_msg_create_sub(GUI_FILE_BROWSER_MSG_ID_FILE_NUM);
    if (sub != NULL) {
        lv_subject_init_pointer(sub->subject, &guider_msg_data);
    }
    gui_file_browser_msg_init_ui();
    gui_file_browser_msg_init_events();
}

void gui_file_browser_msg_init_ui()
{
}

void gui_file_browser_msg_init_events()
{
    void *res = NULL;
    _gui_msg_status_t status[1] = {
        {GUI_FILE_BROWSER_MSG_ID_FILE_NUM, 0, 0},
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

    lv_subject_t *subject_file_num = gui_msg_get_subject(GUI_FILE_BROWSER_MSG_ID_FILE_NUM);
    if (!guider_ui.file_browser_del) {
        gui_file_browser_msg_file_num_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_STRING);
        lv_subject_add_observer_obj(subject_file_num, gui_msg_set_label_text_by_string_cb, guider_ui.file_browser_lbl_1, &guider_msg_data);


        for (int i = 0; i < 1; i++) {
            if (status[i].msg_id == GUI_FILE_BROWSER_MSG_ID_FILE_NUM) {
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

void gui_file_browser_msg_unsubscribe()
{
    _gui_msg_status_t status[1] = {
        {GUI_FILE_BROWSER_MSG_ID_FILE_NUM, 0, 0},
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

gui_msg_data_t *gui_file_browser_msg_get(int32_t msg_id)
{
    switch (msg_id) {
    case GUI_FILE_BROWSER_MSG_ID_FILE_NUM: {
        gui_file_browser_msg_file_num_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_STRING);
        break;
    }
    default:
        return NULL;
    }
    return &guider_msg_data;
}

void gui_file_browser_msg_action_change(int32_t msg_id, gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    switch (msg_id) {
    case GUI_FILE_BROWSER_MSG_ID_FILE_NUM: {
        gui_file_browser_msg_file_num_cb(access, data, type);
        break;
    }
    default: {
        break;
    }
    }
}

gui_msg_status_t gui_file_browser_msg_send(int32_t msg_id, void *value, int32_t len)
{
    if (msg_id == GUI_FILE_BROWSER_MSG_ID) {
    } else {
        gui_msg_data_type_t data_type = VALUE_INT;
        switch (msg_id) {
        case GUI_FILE_BROWSER_MSG_ID_FILE_NUM: {
            data_type = VALUE_STRING;
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
