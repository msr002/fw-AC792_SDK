#include <stdio.h>
#include "lvgl.h"
#include "gui_guider.h"

#if !LV_USE_GUIBUILDER_SIMULATOR
#include "app_core.h"
#include "app_config.h"
#include "action.h"
#include "ui.h"
#endif

static int cur_dir_ch = 0;

#if !LV_USE_GUIBUILDER_SIMULATOR

int gui_bbm_get_online_dev_status(void)
{
    int status = 0;

    struct intent it;
    init_intent(&it);
    it.name	= "baby_monitor";
    it.action = ACTION_BBM_GET_ONLINE_DEV_STATUS;
    it.data = &status;
    start_app(&it);

    return status;
}

void gui_bbm_set_cur_dir_ch(int ch)
{
    printf("set cur dir ch:%d \n", ch);
    cur_dir_ch = ch;
}

int gui_bbm_get_cur_dir_ch(void)
{
    return cur_dir_ch;
}

static void dir_select_screen_load(void)
{
    int status;
    char text[10];
    int num = 0;
    int i = 0, j = 0;
    status = gui_bbm_get_online_dev_status();

    //在线设备的ch号对应的bit位置1
    //统计在线设备数量
    for (i = 0; i < 6; i++) {
        if (status & BIT(i)) {
            num++;
        }
    }

    //无在线设备处理
    if (num == 0) {
        printf("dir no online dev \n");
        post_home_msg_to_ui("back_home_page", 0);
        char *lab = "Device Not Online !";
        post_home_msg_to_ui("show_sys_prompt", lab);
        return;
    }

    //最多六个设备
    for (i = 0; i < 6; i++) {
        //这里对应这UI工具生成代码的顺序
        //保证这些控件是第0-5生成的
        //如果改了控件顺序,这里要对应修改
        lv_obj_t *cont = lv_obj_get_child(guider_ui.dir_select, i);
        if (i < num) {
            lv_obj_clear_flag(cont, LV_OBJ_FLAG_HIDDEN);
            lv_obj_t *lab = lv_obj_get_child(cont, 1);
            for (; j < 6; j++) {
                if (status & BIT(j)) {
                    sprintf(text, "CH%d", j);
                    lv_label_set_text(lab, text);
                    status &= ~BIT(j);
                    break;
                }
            }
        } else {
            lv_obj_add_flag(cont, LV_OBJ_FLAG_HIDDEN);
        }
    }
}


static int gui_src_action_dir_select(int action)
{
    int ret;

    switch (action) {
    case GUI_SCREEN_ACTION_LOAD:
        dir_select_screen_load();
        break;
    case GUI_SCREEN_ACTION_UNLOAD:
        break;
    }
}
REGISTER_UI_SCREEN_ACTION_HANDLER(GUI_SCREEN_DIR_SELECT)
.onchange = gui_src_action_dir_select,
};


#endif



