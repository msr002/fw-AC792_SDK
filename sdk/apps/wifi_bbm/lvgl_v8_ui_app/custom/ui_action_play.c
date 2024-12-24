#include <stdio.h>
#include "lvgl.h"
#include "gui_guider.h"

#if !LV_USE_GUIBUILDER_SIMULATOR
#include "app_core.h"
#include "app_config.h"
#include "action.h"
#include "ui.h"
#endif
static int cur_play_index = 0;

#if !LV_USE_GUIBUILDER_SIMULATOR
void gui_bbm_set_cur_play_index(int index)
{
    cur_play_index = index;
}

int gui_bbm_play_file_start(void)
{
    struct intent it;
    init_intent(&it);
    it.name	= "baby_monitor";
    it.action = ACTION_BBM_FILE_PLAY_START;
    it.data = cur_play_index;
    start_app(&it);

    return 0;
}

int gui_bbm_play_file_stop(void)
{
    struct intent it;
    init_intent(&it);
    it.name	= "baby_monitor";
    it.action = ACTION_BBM_FILE_PLAY_STOP;
    start_app(&it);

    return 0;
}

int gui_bbm_play_file_pause(void)
{
    struct intent it;
    init_intent(&it);
    it.name	= "baby_monitor";
    it.action = ACTION_BBM_FILE_PLAY_PAUSE;
    start_app(&it);

    return 0;
}

int gui_bbm_play_file_resume(void)
{
    struct intent it;
    init_intent(&it);
    it.name	= "baby_monitor";
    it.action = ACTION_BBM_FILE_PLAY_RESUME;
    start_app(&it);

    return 0;
}

static int gui_src_action_play(int action)
{
    switch (action) {
    case GUI_SCREEN_ACTION_LOAD:
#if LV_DISP_UI_FB_NUM
        lv_obj_set_style_bg_opa(guider_ui.video_play, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
#else
        lv_obj_set_style_bg_opa(guider_ui.video_play, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
#endif
        gui_bbm_play_file_start();
        break;
    case GUI_SCREEN_ACTION_UNLOAD:
        gui_bbm_play_file_stop();
        break;
    }
}
REGISTER_UI_SCREEN_ACTION_HANDLER(GUI_SCREEN_VIDEO_PLAY)
.onchange = gui_src_action_play,
};
#endif




