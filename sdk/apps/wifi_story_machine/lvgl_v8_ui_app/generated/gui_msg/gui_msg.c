/*Generate Code, Do NOT Edit!*/
#include "gui_msg.h"

gui_msg_data_t guider_msg_data = {0};

void gui_msg_init(lv_ui *ui)
{
#if LV_USE_MSG
    gui_blue_msg_init(ui);
    gui_bluetooth_msg_init(ui);
    gui_key_msg_init(ui);
    gui_local_music_volume_msg_init(ui);
    gui_recorder_volume_msg_init(ui);
    gui_sd_card_msg_init(ui);
    gui_wifi_state_label_msg_init(ui);
#endif
}
void gui_msg_init_ui()
{
#if LV_USE_MSG
    gui_blue_msg_init_ui();
    gui_bluetooth_msg_init_ui();
    gui_key_msg_init_ui();
    gui_local_music_volume_msg_init_ui();
    gui_recorder_volume_msg_init_ui();
    gui_sd_card_msg_init_ui();
    gui_wifi_state_label_msg_init_ui();
#endif
}
void gui_msg_init_events()
{
#if LV_USE_MSG
    gui_blue_msg_init_events();
    gui_bluetooth_msg_init_events();
    gui_key_msg_init_events();
    gui_local_music_volume_msg_init_events();
    gui_recorder_volume_msg_init_events();
    gui_sd_card_msg_init_events();
    gui_wifi_state_label_msg_init_events();
#endif
}
void gui_msg_unsubscribe()
{
#if LV_USE_MSG
    gui_blue_msg_unsubscribe();
    gui_bluetooth_msg_unsubscribe();
    gui_key_msg_unsubscribe();
    gui_local_music_volume_msg_unsubscribe();
    gui_recorder_volume_msg_unsubscribe();
    gui_sd_card_msg_unsubscribe();
    gui_wifi_state_label_msg_unsubscribe();
#endif
}
gui_msg_status_t gui_msg_send(int32_t msg_id, void *value, int32_t len)
{
#if LV_USE_MSG
    switch (msg_id) {
    case GUI_BLUE_MSG_ID_BT_STATE:
        return gui_blue_msg_send(msg_id, value, len);

    case GUI_BLUETOOTH_MSG_ID_BT_NAME:
        return gui_bluetooth_msg_send(msg_id, value, len);

    case GUI_KEY_MSG_ID_KEY_TEXT:
        return gui_key_msg_send(msg_id, value, len);

    case GUI_LOCAL_MUSIC_VOLUME_MSG_ID_VOLUME:
    case GUI_LOCAL_MUSIC_VOLUME_MSG_ID_PLAY_NAME:
    case GUI_LOCAL_MUSIC_VOLUME_MSG_ID_PLAY_TIME:
        return gui_local_music_volume_msg_send(msg_id, value, len);

    case GUI_RECORDER_VOLUME_MSG_ID_VOLUME:
        return gui_recorder_volume_msg_send(msg_id, value, len);

    case GUI_SD_CARD_MSG_ID_SDCARD:
        return gui_sd_card_msg_send(msg_id, value, len);

    case GUI_WIFI_STATE_LABEL_MSG_ID_CUR_SSID:
        return gui_wifi_state_label_msg_send(msg_id, value, len);

    default:
        break;
    }
    return GUI_MSG_STATUS_NO_FOUND_ID;
#else
    return GUI_MSG_STATUS_ERROR;
#endif
}
GUI_WEAK void gui_msg_action_change(int32_t msg_id, gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    gui_msg_action_change_guider(msg_id, access, data, type);
}
void gui_msg_action_change_guider(int32_t msg_id, gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
#if LV_USE_MSG
    switch (msg_id) {
    case GUI_BLUE_MSG_ID:
    case GUI_BLUE_MSG_ID_BT_STATE:
        return gui_blue_msg_action_change(msg_id, access, data, type);

    case GUI_BLUETOOTH_MSG_ID:
    case GUI_BLUETOOTH_MSG_ID_BT_NAME:
        return gui_bluetooth_msg_action_change(msg_id, access, data, type);

    case GUI_KEY_MSG_ID:
    case GUI_KEY_MSG_ID_KEY_TEXT:
        return gui_key_msg_action_change(msg_id, access, data, type);

    case GUI_LOCAL_MUSIC_VOLUME_MSG_ID:
    case GUI_LOCAL_MUSIC_VOLUME_MSG_ID_VOLUME:
    case GUI_LOCAL_MUSIC_VOLUME_MSG_ID_PLAY_NAME:
    case GUI_LOCAL_MUSIC_VOLUME_MSG_ID_PLAY_TIME:
        return gui_local_music_volume_msg_action_change(msg_id, access, data, type);

    case GUI_RECORDER_VOLUME_MSG_ID:
    case GUI_RECORDER_VOLUME_MSG_ID_VOLUME:
        return gui_recorder_volume_msg_action_change(msg_id, access, data, type);

    case GUI_SD_CARD_MSG_ID:
    case GUI_SD_CARD_MSG_ID_SDCARD:
        return gui_sd_card_msg_action_change(msg_id, access, data, type);

    case GUI_WIFI_STATE_LABEL_MSG_ID:
    case GUI_WIFI_STATE_LABEL_MSG_ID_CUR_SSID:
        return gui_wifi_state_label_msg_action_change(msg_id, access, data, type);

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
void *gui_msg_insert_list(lv_ll_t *ll_p, void *data)
{
#if LV_USE_MSG
    gui_msg_sub_t *sub = _lv_ll_ins_tail(ll_p);
    sub->data = data;
    sub->msg_id = ((gui_msg_sub_dsc_t *)data)->msg_id;
    return sub;
#endif
}
gui_msg_data_t *gui_msg_get_data()
{
    return &guider_msg_data;
}
bool gui_msg_id_is_in_list(lv_ll_t *ll_p, int32_t msg_id)
{
#if LV_USE_MSG
    gui_msg_sub_t *head = _lv_ll_get_head(ll_p);
    while (head != NULL) {
        if (head->msg_id == msg_id) {
            return true;
        }
        head = _lv_ll_get_next(ll_p, head);
    }
    return false;
#else
    return false;
#endif
}
