/*Generate Code, Do NOT Edit!*/
#include "lvgl.h"
#if LV_USE_GUIBUILDER_SIMULATOR
#include <stdio.h>
#endif
#include <stdlib.h>
#include "../gui_guider.h"
#include "../gui_events/events_init.h"
#include "../gui_events/callback_handler.h"
#include "../gui_timelines/gui_timelines.h"
#include "../../custom/custom.h"


lv_obj_t *setup_scr_home(lv_ui *ui)
{
    lv_ui_home *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_HOME);
    if (ui_scr == NULL) {
        ui_scr = lv_mem_alloc(sizeof(lv_ui_home));
        memset(ui_scr, 0, sizeof(lv_ui_home));
        ui->home = ui_scr;
    }

    //Write codes home
    ui_scr->home = lv_obj_create(NULL);
    lv_group_t *def_group = lv_group_get_default();
    lv_obj_set_scrollbar_mode(ui_scr->home, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(ui_scr->home, LV_OBJ_FLAG_SCROLLABLE);
    ui_style_set(ui_scr->home, GUI_CTRL_SCR);

    //Write codes home_video_1
    ui_scr->home_video_1 = lv_ffmpeg_player_create(ui_scr->home);
    lv_ffmpeg_player_set_src(ui_scr->home_video_1, gui_get_res_path(GUI_RES_JL_480X800_AVI));
    lv_ffmpeg_player_set_auto_restart(ui_scr->home_video_1, true);
    lv_ffmpeg_player_set_cmd(ui_scr->home_video_1, LV_FFMPEG_PLAYER_CMD_START);
    lv_obj_set_pos(ui_scr->home_video_1, 0, 0);
    lv_obj_set_size(ui_scr->home_video_1, 480, 800);

    lv_obj_update_layout(ui_scr->home);
    ui_scr->home_del = false;

    //Init events for screen
    events_init_home(ui);
    return ui_scr->home;
}
void unload_scr_home(lv_ui *ui)
{
    ui_free_scr_ptr(ui, GUI_SCREEN_HOME);
}
