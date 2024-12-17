#include <stdio.h>
#include "lvgl.h"
#include "gui_guider.h"

static uint8_t cur_pair_channel;

#if !LV_USE_GUIBUILDER_SIMULATOR
#include "app_core.h"
#include "app_config.h"
#include "action.h"
#include "ui.h"
#endif

void set_cur_pair_channel(uint8_t channel)
{
    cur_pair_channel = channel;
}

uint8_t get_cur_pair_channel(void)
{
    return cur_pair_channel;
}


#if !LV_USE_GUIBUILDER_SIMULATOR

void post_pair_msg_to_ui(const char *msg)
{
    printf("post msg :%s \n", msg);

    if (!strcmp(msg, "pair success")) {
        char *lab = lvgl_module_msg_get_ptr(GUI_PAIR_MSG_ID_PARING_LAB, 50);
        sprintf(lab, "Pair Success! \n\nPlease click to return");
        lvgl_module_msg_send_ptr(lab, 0);
    } else {
        printf("Unknow Msg\n");
    }
}

//返回0未配对/返回1已配对
int gui_get_bbm_pair_status(uint8_t ch)
{
    struct intent it;
    init_intent(&it);
    it.name = "baby_monitor";
    it.action = ACTION_BBM_GET_PAIR_STATUS;
    it.exdata = ch;
    start_app(&it);

    return it.exdata;
}

int gui_set_bbm_enter_pairing(uint8_t ch)
{
    struct intent it;
    init_intent(&it);
    it.name = "baby_monitor";
    it.action = ACTION_BBM_ENTER_PAIRING;
    it.exdata = ch;
    start_app(&it);

    return 0;
}

int gui_set_bbm_exit_pairing(void)
{
    struct intent it;
    init_intent(&it);
    it.name = "baby_monitor";
    it.action = ACTION_BBM_EXIT_PAIRING;
    start_app(&it);

    return 0;
}

int gui_set_bbm_unpair(uint8_t ch)
{
    struct intent it;
    init_intent(&it);
    it.name = "baby_monitor";
    it.action = ACTION_BBM_UNPAIR;
    it.exdata = ch;
    start_app(&it);

    return 0;
}

int gui_pair_msg_pair_ch0_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    int pair_ch_var = 0;
    if (access == GUI_MSG_ACCESS_GET) {
        pair_ch_var = gui_get_bbm_pair_status(0);
    }
    data->value_int = pair_ch_var;
    return 0;
}

int gui_pair_msg_pair_ch1_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    int pair_ch_var = 0;
    if (access == GUI_MSG_ACCESS_GET) {
        pair_ch_var = gui_get_bbm_pair_status(1);
    }
    data->value_int = pair_ch_var;
    return 0;
}
int gui_pair_msg_pair_ch2_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    int pair_ch_var = 0;
    if (access == GUI_MSG_ACCESS_GET) {
        pair_ch_var = gui_get_bbm_pair_status(2);
    }
    data->value_int = pair_ch_var;
    return 0;
}
int gui_pair_msg_pair_ch3_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    int pair_ch_var = 0;
    if (access == GUI_MSG_ACCESS_GET) {
        pair_ch_var = gui_get_bbm_pair_status(3);
    }
    data->value_int = pair_ch_var;
    return 0;
}
int gui_pair_msg_pair_ch4_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    int pair_ch_var = 0;
    if (access == GUI_MSG_ACCESS_GET) {
        pair_ch_var = gui_get_bbm_pair_status(4);
    }
    data->value_int = pair_ch_var;
    return 0;
}
int gui_pair_msg_pair_ch5_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    int pair_ch_var = 0;
    if (access == GUI_MSG_ACCESS_GET) {
        pair_ch_var = gui_get_bbm_pair_status(5);
    }
    data->value_int = pair_ch_var;
    return 0;
}


int gui_pair_msg_paring_lab_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    if (access == GUI_MSG_ACCESS_GET) {
        uint8_t pair_ch = get_cur_pair_channel();
        int pair_status = gui_get_bbm_pair_status(pair_ch);

        if (pair_status) {
            //已配对.
            data->value_string = "This channel is paired. \n\nPlease click to return !!";
            //返回解除配对后才能配对

        } else {
            //未配对
            data->value_string = "Pairing... \n\nPlease press the pairing button of the camera and Make sure the camera is within 30cm";
            //开启配对
            gui_set_bbm_enter_pairing(pair_ch);
        }
    }

    return 0;
}

int gui_pair_msg_unpair_lab_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    if (access == GUI_MSG_ACCESS_GET) {
        uint8_t pair_ch = get_cur_pair_channel();
        int pair_status = gui_get_bbm_pair_status(pair_ch);

        if (pair_status) {
            //已配对
            data->value_string = "Unpair success ! \n\nPlease click to return";
            //解除配对
            gui_set_bbm_unpair(pair_ch);
        } else {
            //未配对
            data->value_string = "This channel not paired ! \n\nPlease click to return";
            //返回,配对后才能取消配对
        }
    }

    return 0;
}

REGISTER_UI_MODULE_EVENT_HANDLER(GUI_PAIR_MSG_ID_PAIR_CH0)
.onchange = gui_pair_msg_pair_ch0_cb,
};
REGISTER_UI_MODULE_EVENT_HANDLER(GUI_PAIR_MSG_ID_PAIR_CH1)
.onchange = gui_pair_msg_pair_ch1_cb,
};
REGISTER_UI_MODULE_EVENT_HANDLER(GUI_PAIR_MSG_ID_PAIR_CH2)
.onchange = gui_pair_msg_pair_ch2_cb,
};
REGISTER_UI_MODULE_EVENT_HANDLER(GUI_PAIR_MSG_ID_PAIR_CH3)
.onchange = gui_pair_msg_pair_ch3_cb,
};
REGISTER_UI_MODULE_EVENT_HANDLER(GUI_PAIR_MSG_ID_PAIR_CH4)
.onchange = gui_pair_msg_pair_ch4_cb,
};
REGISTER_UI_MODULE_EVENT_HANDLER(GUI_PAIR_MSG_ID_PAIR_CH5)
.onchange = gui_pair_msg_pair_ch5_cb,
};


REGISTER_UI_MODULE_EVENT_HANDLER(GUI_PAIR_MSG_ID_PARING_LAB)
.onchange = gui_pair_msg_paring_lab_cb,
};
REGISTER_UI_MODULE_EVENT_HANDLER(GUI_PAIR_MSG_ID_UNPAIR_LAB)
.onchange = gui_pair_msg_unpair_lab_cb,
};
#endif
