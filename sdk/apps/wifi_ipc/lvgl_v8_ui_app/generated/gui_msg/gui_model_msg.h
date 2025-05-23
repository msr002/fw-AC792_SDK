/*Generate Code, Do NOT Edit!*/
#ifndef GUI_MODEL_MSG_H_
#define GUI_MODEL_MSG_H_
#ifdef __cplusplus
extern "C" {
#endif
#include "./gui_msg.h"

#if LV_USE_OBSERVER

typedef enum {
    GUI_MODEL_MSG_ID_POWER = 0x0002,
    GUI_MODEL_MSG_ID_SIGNAL = 0x0003,
    GUI_MODEL_MSG_ID_POWER_NUMBER = 0x0004,
    GUI_MODEL_MSG_ID_KEYFUN1 = 0x0005,
    GUI_MODEL_MSG_ID_TIPS = 0x0006,
    GUI_MODEL_MSG_ID_CALLTIME = 0x0007,
    GUI_MODEL_MSG_ID_WEATHER = 0x0008,
    GUI_MODEL_MSG_ID_SYSTIME = 0x0009,
    GUI_MODEL_MSG_ID_KEYFUN2 = 0x000A,
    GUI_MODEL_MSG_ID_KEYFUN3 = 0x000B,
    GUI_MODEL_MSG_ID_MENU_TITLE = 0x000C,
} gui_model_msg_id_t;

extern int gui_model_msg_power_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_msg_signal_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_msg_power_number_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_msg_keyfun1_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_msg_tips_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_msg_calltime_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_msg_weather_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_msg_systime_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_msg_keyfun2_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_msg_keyfun3_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);
extern int gui_model_msg_menu_title_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);

extern void gui_model_msg_init(lv_ui *ui);
extern void gui_model_msg_init_ui();
extern void gui_model_msg_init_events();
extern void gui_model_msg_unsubscribe();
extern gui_msg_status_t gui_model_msg_send(int32_t msg_id, void *value, int32_t len);
extern gui_msg_data_t *gui_model_msg_get(int32_t msg_id);
extern void gui_model_msg_action_change(int32_t msg_id, gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type);

#endif

#ifdef __cplusplus
}
#endif
#endif /* GUI_MODEL_MSG_H_ */
