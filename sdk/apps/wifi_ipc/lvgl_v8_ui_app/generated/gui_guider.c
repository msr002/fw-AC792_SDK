/*Generate Code, Do NOT Edit!*/
#include "lvgl.h"
#if LV_USE_GUIBUILDER_SIMULATOR
#include <stdio.h>
#endif
#include "./gui_guider.h"
#include "./gui_timelines/gui_timelines.h"
#include "./gui_group/gui_group.h"
#include "./gui_events/events_init.h"

void scr_push_stack_loaded_handler(lv_event_t *e)
{
    int32_t scr_id = (int32_t)lv_event_get_user_data(e);
    lv_obj_t *src = lv_event_get_target(e);
    gui_scr_t *scr = ui_get_scr(scr_id);
    if (scr != NULL) {
        gui_scr_stack_push(scr);
    }
}
void ui_load_scr_anim(lv_ui *ui, gui_scr_t *screen, lv_scr_load_anim_t anim_type,	uint32_t time,
                      uint32_t delay, bool is_clean, bool auto_del, bool is_push_satck)
{
    if (screen == NULL) {
        return;
    }

    gui_scr_t *act_screen = gui_scr_get_act();
    if (act_screen == screen) {
        return;
    }

    gui_timelines_delete();
    gui_scr_set_act_anim(screen, ui, anim_type, time, delay, is_clean, auto_del);

    if (is_push_satck) {
        if (screen == gui_scr_get_act()) {
            gui_scr_stack_push(act_screen);
        } else {
            lv_obj_remove_event_cb(screen->scr, scr_push_stack_loaded_handler);
            lv_obj_add_event_cb(screen->scr, scr_push_stack_loaded_handler, LV_EVENT_SCREEN_LOADED, (void *)act_screen->id);
        }
    }
}

void ui_scr_stack_pop_anim(lv_ui *ui, lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay,
                           bool is_clean, bool auto_del, bool is_push_satck)
{
    gui_scr_t *screen = gui_scr_stack_pop();
    if (screen == NULL) {
        return;
    }

    ui_load_scr_anim(ui, screen, anim_type, time, delay, is_clean, auto_del, is_push_satck);
}

gui_scr_t *ui_get_scr(int32_t scr_id)
{
    gui_scr_t *screen = gui_scr_get(scr_id);
    if (screen != NULL) {
        return screen;
    }

    if (scr_id == GUI_SCREEN_START) {
        return gui_scr_create(GUI_SCREEN_START, "start", NULL, (gui_scr_setup_cb_t)setup_scr_start, (gui_scr_unload_cb_t)unload_scr_start);
    }
    if (scr_id == GUI_SCREEN_HOME) {
        return gui_scr_create(GUI_SCREEN_HOME, "home", NULL, (gui_scr_setup_cb_t)setup_scr_home, (gui_scr_unload_cb_t)unload_scr_home);
    }
    if (scr_id == GUI_SCREEN_MENU) {
        return gui_scr_create(GUI_SCREEN_MENU, "menu", NULL, (gui_scr_setup_cb_t)setup_scr_menu, (gui_scr_unload_cb_t)unload_scr_menu);
    }
    if (scr_id == GUI_SCREEN_LANGUAGE) {
        return gui_scr_create(GUI_SCREEN_LANGUAGE, "language", NULL, (gui_scr_setup_cb_t)setup_scr_language, (gui_scr_unload_cb_t)unload_scr_language);
    }
    if (scr_id == GUI_SCREEN_APP) {
        return gui_scr_create(GUI_SCREEN_APP, "app", NULL, (gui_scr_setup_cb_t)setup_scr_app, (gui_scr_unload_cb_t)unload_scr_app);
    }
    if (scr_id == GUI_SCREEN_SYSCFG) {
        return gui_scr_create(GUI_SCREEN_SYSCFG, "syscfg", NULL, (gui_scr_setup_cb_t)setup_scr_syscfg, (gui_scr_unload_cb_t)unload_scr_syscfg);
    }
    if (scr_id == GUI_SCREEN_SYSINFO) {
        return gui_scr_create(GUI_SCREEN_SYSINFO, "sysinfo", NULL, (gui_scr_setup_cb_t)setup_scr_sysinfo, (gui_scr_unload_cb_t)unload_scr_sysinfo);
    }
    return NULL;
}

gui_scr_t *ui_get_setup_scr(int32_t scr_id)
{
    gui_scr_t *screen = ui_get_scr(scr_id);
    if (screen == NULL) {
        return NULL;
    }

    if (screen->scr == NULL || lv_obj_is_valid(screen->scr) == false) {
        if (screen->setup_cb != NULL) {
            screen->scr = screen->setup_cb(&guider_ui);
            screen->is_del = false;
            if (screen->scr == NULL || lv_obj_is_valid(screen->scr) == false) {
                screen->is_del = true;
                return NULL;
            }
        }
    }
    return screen;
}

lv_obj_t *ui_get_setup_scr_obj(int32_t scr_id)
{
    gui_scr_t *screen = ui_get_setup_scr(scr_id);
    if (screen == NULL) {
        return NULL;
    }

    return screen->scr;
}


void *ui_get_scr_ptr(lv_ui *ui, int32_t scr_id)
{
    if (ui == NULL) {
        return NULL;
    }

    if (scr_id == GUI_SCREEN_START) {
        return ui->start;
    }
    if (scr_id == GUI_SCREEN_HOME) {
        return ui->home;
    }
    if (scr_id == GUI_SCREEN_MENU) {
        return ui->menu;
    }
    if (scr_id == GUI_SCREEN_LANGUAGE) {
        return ui->language;
    }
    if (scr_id == GUI_SCREEN_APP) {
        return ui->app;
    }
    if (scr_id == GUI_SCREEN_SYSCFG) {
        return ui->syscfg;
    }
    if (scr_id == GUI_SCREEN_SYSINFO) {
        return ui->sysinfo;
    }
    return NULL;
}

void ui_free_scr_ptr(lv_ui *ui, int32_t scr_id)
{
    if (ui == NULL) {
        return;
    }

    if (scr_id == GUI_SCREEN_START) {
        if (ui->start != NULL) {
            lv_mem_free(ui->start);
        }
        ui->start = NULL;
    }
    if (scr_id == GUI_SCREEN_HOME) {
        if (ui->home != NULL) {
            lv_mem_free(ui->home);
        }
        ui->home = NULL;
    }
    if (scr_id == GUI_SCREEN_MENU) {
        if (ui->menu != NULL) {
            lv_mem_free(ui->menu);
        }
        ui->menu = NULL;
    }
    if (scr_id == GUI_SCREEN_LANGUAGE) {
        if (ui->language != NULL) {
            lv_mem_free(ui->language);
        }
        ui->language = NULL;
    }
    if (scr_id == GUI_SCREEN_APP) {
        if (ui->app != NULL) {
            lv_mem_free(ui->app);
        }
        ui->app = NULL;
    }
    if (scr_id == GUI_SCREEN_SYSCFG) {
        if (ui->syscfg != NULL) {
            lv_mem_free(ui->syscfg);
        }
        ui->syscfg = NULL;
    }
    if (scr_id == GUI_SCREEN_SYSINFO) {
        if (ui->sysinfo != NULL) {
            lv_mem_free(ui->sysinfo);
        }
        ui->sysinfo = NULL;
    }
    gui_scr_t *scr = gui_scr_get(scr_id);
    if (scr != NULL) {
        scr->scr = NULL;
    }
}

bool ui_is_act_scr(int32_t scr_id)
{
    return gui_scr_is_act(ui_get_scr(scr_id));
}

void ui_init_style(lv_style_t *style)
{
    if (style->prop_cnt > 1) {
        lv_style_reset(style);
    } else {
        lv_style_init(style);
    }
}


void setup_ui(lv_ui *ui)
{
    lv_i18n_init(lv_i18n_language_pack);
    lv_i18n_set_locale(lv_i18n_get_default_locale());
    init_gui_fonts();
    ui_style_init();
#if LV_USE_MSG
    gui_msg_init(ui);
#endif
    gui_group_init();
    ui_scr_manager_init();
    gui_scr_t *scr = ui_get_scr(GUI_SCREEN_START);
    ui_load_scr_anim(ui, scr, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, false, false);
    events_init(ui);
    gui_timelines_init(ui);
}
void clock_count_with_year(int *year, int *month, int *day, int *hour, int *min, int *sec)
{
    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((*year % 4 == 0 && *year % 100 != 0) || (*year % 400 == 0)) {
        days_in_month[1] = 29;
    }
    (*sec)++;
    if (*sec >= 60) {
        *sec = 0;
        (*min)++;
    }
    if (*min >= 60) {
        *min = 0;
        (*hour)++;
    }
    if (*hour >= 24) {
        *hour = 0;
        (*day)++;
    }
    if (*day > days_in_month[*month - 1]) {
        *day = 1;
        (*month)++;
        if (*month > 12) {
            *month = 1;
            (*year)++;
        }
    }
}
