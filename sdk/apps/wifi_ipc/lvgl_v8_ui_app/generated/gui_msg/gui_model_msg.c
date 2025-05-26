/*Generate Code, Do NOT Edit!*/
#include "./gui_model_msg.h"
#if LV_USE_OBSERVER

static lv_ll_t subs_ll;
static lv_ll_t timer_ll;

typedef struct {
    lv_timer_t *timer;
} timer_dsc_t;
static void delete_all_timer()
{
    timer_dsc_t *head = _lv_ll_get_head(&timer_ll);
    while (head != NULL) {
        timer_dsc_t *next = _lv_ll_get_next(&timer_ll, head);
        if (head->timer != NULL) {
            lv_timer_del(head->timer);
        }
        _lv_ll_remove(&timer_ll, head);
        lv_mem_free(head);
        head = next;
    }
}
static timer_dsc_t *insert_timer(lv_ll_t *ll_p, lv_timer_t *timer)
{
    timer_dsc_t *tail = _lv_ll_ins_tail(ll_p);
    tail->timer = timer;
    return tail;
}
void gui_model_msg_power_number_timer_cb(lv_timer_t *timer)
{
    gui_msg_action_change(GUI_MODEL_MSG_ID_POWER_NUMBER, GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_STRING);
    lv_subject_t *subject = gui_msg_get_subject(GUI_MODEL_MSG_ID_POWER_NUMBER);
    if (subject == NULL) {
        return;
    }
    lv_subject_set_pointer(subject, &guider_msg_data);
}
void gui_model_msg_systime_timer_cb(lv_timer_t *timer)
{
    gui_msg_action_change(GUI_MODEL_MSG_ID_SYSTIME, GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_TIME);
    lv_subject_t *subject = gui_msg_get_subject(GUI_MODEL_MSG_ID_SYSTIME);
    if (subject == NULL) {
        return;
    }
    lv_subject_set_pointer(subject, &guider_msg_data);
}

void gui_model_msg_home_img_wifi_set_img_path_cb(lv_observer_t *observer, lv_subject_t *subject)
{
    lv_obj_t *obj = lv_observer_get_target_obj(observer);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    gui_msg_data_t *data = (gui_msg_data_t *)observer->user_data;
    lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_msg_home_digitclock_time_set_digit_clock_time_cb(lv_observer_t *observer, lv_subject_t *subject)
{
    lv_obj_t *obj = lv_observer_get_target_obj(observer);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    gui_msg_data_t *data = (gui_msg_data_t *)observer->user_data;
    struct tm time = data->value_time;
    lv_label_set_text_fmt(obj, "%04d-%02d-%02d %02d:%02d:%02d", time.tm_year + 1900, time.tm_mon + 1, time.tm_mday, time.tm_hour, time.tm_min, time.tm_sec);
}
void gui_model_msg_home_img_weather_set_img_path_cb(lv_observer_t *observer, lv_subject_t *subject)
{
    lv_obj_t *obj = lv_observer_get_target_obj(observer);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    gui_msg_data_t *data = (gui_msg_data_t *)observer->user_data;
    lv_img_set_src(obj, gui_get_res_path(data->value_int));
}
void gui_model_msg_home_img_bat_set_img_path_cb(lv_observer_t *observer, lv_subject_t *subject)
{
    lv_obj_t *obj = lv_observer_get_target_obj(observer);
    if (obj == NULL || lv_obj_is_valid(obj) == false) {
        return;
    }

    gui_msg_data_t *data = (gui_msg_data_t *)observer->user_data;
    lv_img_set_src(obj, gui_get_res_path(data->value_int));
}

GUI_WEAK int gui_model_msg_power_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t power_var = RES_ICON_BATTERY_100;
    if (access == GUI_MSG_ACCESS_SET) {
        power_var = data->value_int;
    }
    data->value_int = power_var;
    return 0;
}
GUI_WEAK int gui_model_msg_signal_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t signal_var = RES_WIFI_00;
    if (access == GUI_MSG_ACCESS_SET) {
        signal_var = data->value_int;
    }
    data->value_int = signal_var;
    return 0;
}
GUI_WEAK int gui_model_msg_power_number_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    char power_number_init_var[] = "100%";
    static bool power_number_is_init = false;
    static char *power_number_var = NULL;
    if (power_number_is_init == false) {
        power_number_var = lv_mem_alloc(strlen(power_number_init_var) + 1);
        strcpy(power_number_var, power_number_init_var);
        power_number_is_init = true;
    }
    if (access == GUI_MSG_ACCESS_SET) {
        lv_mem_free(power_number_var);
        power_number_var = lv_mem_alloc(strlen(data->value_string) + 1);
        strcpy(power_number_var, data->value_string);
    }
    data->value_string = power_number_var;
    return 0;
}
GUI_WEAK int gui_model_msg_keyfun1_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t keyfun1_var = RES_ICON_CALL_OUT;
    if (access == GUI_MSG_ACCESS_SET) {
        keyfun1_var = data->value_int;
    }
    data->value_int = keyfun1_var;
    return 0;
}
GUI_WEAK int gui_model_msg_tips_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    char tips_init_var[] = "";
    static bool tips_is_init = false;
    static char *tips_var = NULL;
    if (tips_is_init == false) {
        tips_var = lv_mem_alloc(strlen(tips_init_var) + 1);
        strcpy(tips_var, tips_init_var);
        tips_is_init = true;
    }
    if (access == GUI_MSG_ACCESS_SET) {
        lv_mem_free(tips_var);
        tips_var = lv_mem_alloc(strlen(data->value_string) + 1);
        strcpy(tips_var, data->value_string);
    }
    data->value_string = tips_var;
    return 0;
}
GUI_WEAK int gui_model_msg_calltime_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static struct tm calltime_var = {
        .tm_year = 124,
        .tm_mon = 3,
        .tm_mday = 22,
        .tm_hour = 0,
        .tm_min = 0,
        .tm_sec = 0,
    };
    if (access == GUI_MSG_ACCESS_SET) {
        calltime_var = data->value_time;
    }
    data->value_time = calltime_var;
    return 0;
}
GUI_WEAK int gui_model_msg_weather_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t weather_var = RES_WEATHER_010;
    if (access == GUI_MSG_ACCESS_SET) {
        weather_var = data->value_int;
    }
    data->value_int = weather_var;
    return 0;
}
GUI_WEAK int gui_model_msg_systime_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static struct tm systime_var = {
        .tm_year = 124,
        .tm_mon = 4,
        .tm_mday = 15,
        .tm_hour = 9,
        .tm_min = 39,
        .tm_sec = 15,
    };
    if (access == GUI_MSG_ACCESS_SET) {
        systime_var = data->value_time;
    }
    data->value_time = systime_var;
    return 0;
}
GUI_WEAK int gui_model_msg_keyfun2_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t keyfun2_var = RES_ICON_WALKIE_TALKIE;
    if (access == GUI_MSG_ACCESS_SET) {
        keyfun2_var = data->value_int;
    }
    data->value_int = keyfun2_var;
    return 0;
}
GUI_WEAK int gui_model_msg_keyfun3_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    static int32_t keyfun3_var = RES_ICON_RECOVER;
    if (access == GUI_MSG_ACCESS_SET) {
        keyfun3_var = data->value_int;
    }
    data->value_int = keyfun3_var;
    return 0;
}
GUI_WEAK int gui_model_msg_menu_title_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    char menu_title_init_var[] = "return_info";
    static bool menu_title_is_init = false;
    static char *menu_title_var = NULL;
    if (menu_title_is_init == false) {
        menu_title_var = lv_mem_alloc(strlen(menu_title_init_var) + 1);
        strcpy(menu_title_var, menu_title_init_var);
        menu_title_is_init = true;
    }
    if (access == GUI_MSG_ACCESS_SET) {
        lv_mem_free(menu_title_var);
        menu_title_var = lv_mem_alloc(strlen(data->value_string) + 1);
        strcpy(menu_title_var, data->value_string);
    }
    data->value_string = menu_title_var;
    return 0;
}

void gui_model_msg_init(lv_ui *ui)
{
    gui_msg_sub_t *sub;
    sub = gui_msg_create_sub(GUI_MODEL_MSG_ID_POWER);
    if (sub != NULL) {
        lv_subject_init_pointer(sub->subject, &guider_msg_data);
    }
    sub = gui_msg_create_sub(GUI_MODEL_MSG_ID_SIGNAL);
    if (sub != NULL) {
        lv_subject_init_pointer(sub->subject, &guider_msg_data);
    }
    sub = gui_msg_create_sub(GUI_MODEL_MSG_ID_POWER_NUMBER);
    if (sub != NULL) {
        lv_subject_init_pointer(sub->subject, &guider_msg_data);
    }
    sub = gui_msg_create_sub(GUI_MODEL_MSG_ID_KEYFUN1);
    if (sub != NULL) {
        lv_subject_init_pointer(sub->subject, &guider_msg_data);
    }
    sub = gui_msg_create_sub(GUI_MODEL_MSG_ID_TIPS);
    if (sub != NULL) {
        lv_subject_init_pointer(sub->subject, &guider_msg_data);
    }
    sub = gui_msg_create_sub(GUI_MODEL_MSG_ID_CALLTIME);
    if (sub != NULL) {
        lv_subject_init_pointer(sub->subject, &guider_msg_data);
    }
    sub = gui_msg_create_sub(GUI_MODEL_MSG_ID_WEATHER);
    if (sub != NULL) {
        lv_subject_init_pointer(sub->subject, &guider_msg_data);
    }
    sub = gui_msg_create_sub(GUI_MODEL_MSG_ID_SYSTIME);
    if (sub != NULL) {
        lv_subject_init_pointer(sub->subject, &guider_msg_data);
    }
    sub = gui_msg_create_sub(GUI_MODEL_MSG_ID_KEYFUN2);
    if (sub != NULL) {
        lv_subject_init_pointer(sub->subject, &guider_msg_data);
    }
    sub = gui_msg_create_sub(GUI_MODEL_MSG_ID_KEYFUN3);
    if (sub != NULL) {
        lv_subject_init_pointer(sub->subject, &guider_msg_data);
    }
    sub = gui_msg_create_sub(GUI_MODEL_MSG_ID_MENU_TITLE);
    if (sub != NULL) {
        lv_subject_init_pointer(sub->subject, &guider_msg_data);
    }
    _lv_ll_init(&timer_ll, sizeof(timer_dsc_t));
}

void gui_model_msg_init_ui()
{
}

void gui_model_msg_init_events()
{
    void *res = NULL;
    _gui_msg_status_t status[11] = {
        {GUI_MODEL_MSG_ID_POWER, 0, 0},
        {GUI_MODEL_MSG_ID_SIGNAL, 0, 0},
        {GUI_MODEL_MSG_ID_POWER_NUMBER, 0, 0},
        {GUI_MODEL_MSG_ID_KEYFUN1, 0, 0},
        {GUI_MODEL_MSG_ID_TIPS, 0, 0},
        {GUI_MODEL_MSG_ID_CALLTIME, 0, 0},
        {GUI_MODEL_MSG_ID_WEATHER, 0, 0},
        {GUI_MODEL_MSG_ID_SYSTIME, 0, 0},
        {GUI_MODEL_MSG_ID_KEYFUN2, 0, 0},
        {GUI_MODEL_MSG_ID_KEYFUN3, 0, 0},
        {GUI_MODEL_MSG_ID_MENU_TITLE, 0, 0},
    };
    lv_timer_t *timer = NULL;
    bool power_number_timer_enable = false;
    bool systime_timer_enable = false;
    delete_all_timer();

    for (int i = 0; i < 11; i++) {
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

    lv_subject_t *subject_power = gui_msg_get_subject(GUI_MODEL_MSG_ID_POWER);
    lv_subject_t *subject_signal = gui_msg_get_subject(GUI_MODEL_MSG_ID_SIGNAL);
    lv_subject_t *subject_power_number = gui_msg_get_subject(GUI_MODEL_MSG_ID_POWER_NUMBER);
    lv_subject_t *subject_keyfun1 = gui_msg_get_subject(GUI_MODEL_MSG_ID_KEYFUN1);
    lv_subject_t *subject_tips = gui_msg_get_subject(GUI_MODEL_MSG_ID_TIPS);
    lv_subject_t *subject_calltime = gui_msg_get_subject(GUI_MODEL_MSG_ID_CALLTIME);
    lv_subject_t *subject_weather = gui_msg_get_subject(GUI_MODEL_MSG_ID_WEATHER);
    lv_subject_t *subject_systime = gui_msg_get_subject(GUI_MODEL_MSG_ID_SYSTIME);
    lv_subject_t *subject_keyfun2 = gui_msg_get_subject(GUI_MODEL_MSG_ID_KEYFUN2);
    lv_subject_t *subject_keyfun3 = gui_msg_get_subject(GUI_MODEL_MSG_ID_KEYFUN3);
    lv_subject_t *subject_menu_title = gui_msg_get_subject(GUI_MODEL_MSG_ID_MENU_TITLE);
    if (guider_ui.home) {
        lv_ui_home *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_HOME);
        gui_msg_setup_component(true, false, subject_signal, ui_scr->home_img_wifi, &guider_msg_data, gui_model_msg_home_img_wifi_set_img_path_cb, GUI_MODEL_MSG_ID_SIGNAL, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);

        gui_msg_setup_component(true, false, subject_power_number, ui_scr->home_lbl_bat, &guider_msg_data, gui_msg_set_label_text_by_string_cb, GUI_MODEL_MSG_ID_POWER_NUMBER, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);

        gui_msg_setup_component(true, false, subject_systime, ui_scr->home_digitclock_time, &guider_msg_data, gui_model_msg_home_digitclock_time_set_digit_clock_time_cb, GUI_MODEL_MSG_ID_SYSTIME, GUI_MSG_ACCESS_GET, VALUE_TIME, NULL);

        gui_msg_setup_component(true, false, subject_weather, ui_scr->home_img_weather, &guider_msg_data, gui_model_msg_home_img_weather_set_img_path_cb, GUI_MODEL_MSG_ID_WEATHER, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);

        gui_msg_setup_component(true, false, subject_power, ui_scr->home_img_bat, &guider_msg_data, gui_model_msg_home_img_bat_set_img_path_cb, GUI_MODEL_MSG_ID_POWER, GUI_MSG_ACCESS_GET, VALUE_INT, NULL);

        gui_msg_setup_component(true, false, subject_tips, ui_scr->home_lbl_note, &guider_msg_data, gui_msg_set_label_text_by_string_cb, GUI_MODEL_MSG_ID_TIPS, GUI_MSG_ACCESS_GET, VALUE_STRING, NULL);


        for (int i = 0; i < 11; i++) {
            if (status[i].msg_id == GUI_MODEL_MSG_ID_SIGNAL) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_MSG_ID_POWER_NUMBER) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_MSG_ID_SYSTIME) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_MSG_ID_WEATHER) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_MSG_ID_POWER) {
                status[i].is_subscribe = 1;
            }
            if (status[i].msg_id == GUI_MODEL_MSG_ID_TIPS) {
                status[i].is_subscribe = 1;
            }
        }

        power_number_timer_enable = true;
        systime_timer_enable = true;
    }

    for (int i = 0; i < 11; i++) {
        if (status[i].is_subscribe == 0 && status[i].is_unsubscribe == 1) {
            gui_msg_subscribe_change(status[i].msg_id, GUI_MSG_UNSUBSCRIBE);
        } else if (status[i].is_subscribe == 1 && status[i].is_unsubscribe == 0) {
            gui_msg_subscribe_change(status[i].msg_id, GUI_MSG_SUBSCRIBE);
        }
    }
    if (power_number_timer_enable) {
        timer = lv_timer_create(gui_model_msg_power_number_timer_cb, 6000, NULL);
        insert_timer(&timer_ll, timer);
    }
    if (systime_timer_enable) {
        timer = lv_timer_create(gui_model_msg_systime_timer_cb, 500, NULL);
        insert_timer(&timer_ll, timer);
    }
}

void gui_model_msg_unsubscribe()
{
    _gui_msg_status_t status[11] = {
        {GUI_MODEL_MSG_ID_POWER, 0, 0},
        {GUI_MODEL_MSG_ID_SIGNAL, 0, 0},
        {GUI_MODEL_MSG_ID_POWER_NUMBER, 0, 0},
        {GUI_MODEL_MSG_ID_KEYFUN1, 0, 0},
        {GUI_MODEL_MSG_ID_TIPS, 0, 0},
        {GUI_MODEL_MSG_ID_CALLTIME, 0, 0},
        {GUI_MODEL_MSG_ID_WEATHER, 0, 0},
        {GUI_MODEL_MSG_ID_SYSTIME, 0, 0},
        {GUI_MODEL_MSG_ID_KEYFUN2, 0, 0},
        {GUI_MODEL_MSG_ID_KEYFUN3, 0, 0},
        {GUI_MODEL_MSG_ID_MENU_TITLE, 0, 0},
    };
    for (int i = 0; i < 11; i++) {
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

    for (int i = 0; i < 11; i++) {
        if (status[i].is_unsubscribe == 1) {
            gui_msg_subscribe_change(status[i].msg_id, GUI_MSG_UNSUBSCRIBE);
        }
    }
}

gui_msg_data_t *gui_model_msg_get(int32_t msg_id)
{
    switch (msg_id) {
    case GUI_MODEL_MSG_ID_POWER: {
        gui_model_msg_power_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
        break;
    }
    case GUI_MODEL_MSG_ID_SIGNAL: {
        gui_model_msg_signal_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
        break;
    }
    case GUI_MODEL_MSG_ID_POWER_NUMBER: {
        gui_model_msg_power_number_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_STRING);
        break;
    }
    case GUI_MODEL_MSG_ID_KEYFUN1: {
        gui_model_msg_keyfun1_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
        break;
    }
    case GUI_MODEL_MSG_ID_TIPS: {
        gui_model_msg_tips_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_STRING);
        break;
    }
    case GUI_MODEL_MSG_ID_CALLTIME: {
        gui_model_msg_calltime_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_TIME);
        break;
    }
    case GUI_MODEL_MSG_ID_WEATHER: {
        gui_model_msg_weather_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
        break;
    }
    case GUI_MODEL_MSG_ID_SYSTIME: {
        gui_model_msg_systime_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_TIME);
        break;
    }
    case GUI_MODEL_MSG_ID_KEYFUN2: {
        gui_model_msg_keyfun2_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
        break;
    }
    case GUI_MODEL_MSG_ID_KEYFUN3: {
        gui_model_msg_keyfun3_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_INT);
        break;
    }
    case GUI_MODEL_MSG_ID_MENU_TITLE: {
        gui_model_msg_menu_title_cb(GUI_MSG_ACCESS_GET, &guider_msg_data, VALUE_STRING);
        break;
    }
    default:
        return NULL;
    }
    return &guider_msg_data;
}

void gui_model_msg_action_change(int32_t msg_id, gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{
    switch (msg_id) {
    case GUI_MODEL_MSG_ID_POWER: {
        gui_model_msg_power_cb(access, data, type);
        break;
    }
    case GUI_MODEL_MSG_ID_SIGNAL: {
        gui_model_msg_signal_cb(access, data, type);
        break;
    }
    case GUI_MODEL_MSG_ID_POWER_NUMBER: {
        gui_model_msg_power_number_cb(access, data, type);
        break;
    }
    case GUI_MODEL_MSG_ID_KEYFUN1: {
        gui_model_msg_keyfun1_cb(access, data, type);
        break;
    }
    case GUI_MODEL_MSG_ID_TIPS: {
        gui_model_msg_tips_cb(access, data, type);
        break;
    }
    case GUI_MODEL_MSG_ID_CALLTIME: {
        gui_model_msg_calltime_cb(access, data, type);
        break;
    }
    case GUI_MODEL_MSG_ID_WEATHER: {
        gui_model_msg_weather_cb(access, data, type);
        break;
    }
    case GUI_MODEL_MSG_ID_SYSTIME: {
        gui_model_msg_systime_cb(access, data, type);
        break;
    }
    case GUI_MODEL_MSG_ID_KEYFUN2: {
        gui_model_msg_keyfun2_cb(access, data, type);
        break;
    }
    case GUI_MODEL_MSG_ID_KEYFUN3: {
        gui_model_msg_keyfun3_cb(access, data, type);
        break;
    }
    case GUI_MODEL_MSG_ID_MENU_TITLE: {
        gui_model_msg_menu_title_cb(access, data, type);
        break;
    }
    default: {
        break;
    }
    }
}

gui_msg_status_t gui_model_msg_send(int32_t msg_id, void *value, int32_t len)
{
    if (msg_id == GUI_MODEL_MSG_ID) {
    } else {
        gui_msg_data_type_t data_type = VALUE_INT;
        switch (msg_id) {
        case GUI_MODEL_MSG_ID_POWER: {
            data_type = VALUE_INT;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
            break;
        }
        case GUI_MODEL_MSG_ID_SIGNAL: {
            data_type = VALUE_INT;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
            break;
        }
        case GUI_MODEL_MSG_ID_POWER_NUMBER: {
            data_type = VALUE_STRING;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
            break;
        }
        case GUI_MODEL_MSG_ID_KEYFUN1: {
            data_type = VALUE_INT;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
            break;
        }
        case GUI_MODEL_MSG_ID_TIPS: {
            data_type = VALUE_STRING;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
            break;
        }
        case GUI_MODEL_MSG_ID_CALLTIME: {
            data_type = VALUE_TIME;
            if (value) {
                guider_msg_data.value_time = *((struct tm *)value);
            }
            break;
        }
        case GUI_MODEL_MSG_ID_WEATHER: {
            data_type = VALUE_INT;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
            break;
        }
        case GUI_MODEL_MSG_ID_SYSTIME: {
            data_type = VALUE_TIME;
            if (value) {
                guider_msg_data.value_time = *((struct tm *)value);
            }
            break;
        }
        case GUI_MODEL_MSG_ID_KEYFUN2: {
            data_type = VALUE_INT;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
            break;
        }
        case GUI_MODEL_MSG_ID_KEYFUN3: {
            data_type = VALUE_INT;
            guider_msg_data.value_array.ptr = value;
            guider_msg_data.value_array.len = len;
            break;
        }
        case GUI_MODEL_MSG_ID_MENU_TITLE: {
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
