/*Generate Code, Do NOT Edit!*/
#include "./gui_msg.h"

gui_msg_data_t guider_msg_data = {0};
gui_msg_send_status_t gui_msg_send_status = GUI_MSG_SEND_DONE;
static lv_ll_t subs_ll;

void gui_msg_init(lv_ui *ui)
{
#if LV_USE_OBSERVER
    _lv_ll_init(&subs_ll, sizeof(gui_msg_sub_t));
#endif
}
void gui_msg_init_ui()
{
#if LV_USE_OBSERVER
#endif
}
void gui_msg_init_events()
{
#if LV_USE_OBSERVER
#endif
}
void gui_msg_unsubscribe()
{
#if LV_USE_OBSERVER
#endif
}
gui_msg_status_t gui_msg_send(int32_t msg_id, void *value, int32_t len)
{
#if LV_USE_OBSERVER
    gui_msg_send_status = GUI_MSG_SENDING;
    gui_msg_status_t ret;
    switch (msg_id) {
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
bool gui_msg_has_observer(lv_subject_t *subject, lv_observer_cb_t cb, lv_obj_t *obj, void *user_data)
{
    if (subject == NULL || subject->type == LV_SUBJECT_TYPE_INVALID) {
        return false;
    }
    lv_observer_t *observer = _lv_ll_get_head(&(subject->subs_ll));
    while (observer != NULL) {
        if (observer->cb == cb && observer->target == obj && observer->user_data == user_data) {
            return true;
        }
        observer = _lv_ll_get_next(&(subject->subs_ll), observer);
    }
    return false;
}
void gui_msg_setup_component(bool subscribe_enabled, bool event_enabled, lv_subject_t *subject, lv_obj_t *target_obj, gui_msg_data_t *msg_data, lv_observer_cb_t observer_cb, int32_t msg_id, gui_msg_action_t msg_action, gui_msg_data_type_t data_type, lv_event_cb_t event_cb)
{
    if (subject == NULL || subject->type == LV_SUBJECT_TYPE_INVALID) {
        return;
    }

    if (subscribe_enabled) {
        if (!gui_msg_has_observer(subject, observer_cb, target_obj, msg_data)) {
            gui_msg_action_change(msg_id, msg_action, msg_data, data_type);
            lv_subject_add_observer_obj(subject, observer_cb, target_obj, msg_data);
        }
    }

    if (event_enabled) {
        lv_obj_remove_event_cb(target_obj, event_cb);
        lv_obj_add_event_cb(target_obj, event_cb, LV_EVENT_VALUE_CHANGED, (void *)msg_id);
    }
}

