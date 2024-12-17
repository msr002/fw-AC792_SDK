#include <stdio.h>
#include "lvgl.h"
#include "gui_guider.h"

#if !LV_USE_GUIBUILDER_SIMULATOR
#include "app_core.h"
#include "app_config.h"
#include "action.h"
#include "ui.h"
#endif

#if !LV_USE_GUIBUILDER_SIMULATOR
static int gui_src_action_home(int action)
{
    struct intent it;
    struct application *app;

    switch (action) {
    case GUI_SCREEN_ACTION_LOAD:
        break;
    case GUI_SCREEN_ACTION_UNLOAD:
        break;
    }
}
REGISTER_UI_SCREEN_ACTION_HANDLER(GUI_SCREEN_HOME)
.onchange = gui_src_action_home,
};
#endif




