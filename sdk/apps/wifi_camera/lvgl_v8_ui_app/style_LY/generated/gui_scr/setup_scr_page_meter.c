#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE
/*Generate Code, Do NOT Edit!*/
#include "lvgl.h"
#if LV_USE_GUIBUILDER_SIMULATOR
#include <stdio.h>
#endif
#include <stdlib.h>
#include "../gui_guider.h"
#include "../gui_events/events_init.h"
#include "../gui_events/callback_handler.h"
#include "../gui_events/i18n_handler.h"
#include "../gui_timelines/gui_timelines.h"
#include "../../custom/custom.h"

static const char *page_meter_imglist_1_imgs[22] = {
#if LV_USE_GUIBUILDER_SIMULATOR
    "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\meter\\rotate_00000.png",
    "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\meter\\rotate_00001.png",
    "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\meter\\rotate_00002.png",
    "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\meter\\rotate_00003.png",
    "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\meter\\rotate_00004.png",
    "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\meter\\rotate_00005.png",
    "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\meter\\rotate_00006.png",
    "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\meter\\rotate_00007.png",
    "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\meter\\rotate_00010.png",
    "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\meter\\rotate_00011.png",
    "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\meter\\rotate_00012.png",
    "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\meter\\rotate_00013.png",
    "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\meter\\rotate_00014.png",
    "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\meter\\rotate_00015.png",
    "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\meter\\rotate_00016.png",
    "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\meter\\rotate_00017.png",
    "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\meter\\rotate_00020.png",
    "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\meter\\rotate_00021.png",
    "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\meter\\rotate_00022.png",
    "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\meter\\rotate_00023.png",
    "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\meter\\rotate_00024.png",
    "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\meter\\rotate_00025.png"
#else
    "S:/4b800000.zip",
    "S:/4b800001.zip",
    "S:/4b800002.zip",
    "S:/4b800003.zip",
    "S:/4b800004.zip",
    "S:/4b800005.zip",
    "S:/4b800006.zip",
    "S:/4b800007.zip",
    "S:/4b800008.zip",
    "S:/4b800009.zip",
    "S:/4b80000a.zip",
    "S:/4b80000b.zip",
    "S:/4b80000c.zip",
    "S:/4b80000d.zip",
    "S:/4b80000e.zip",
    "S:/4b80000f.zip",
    "S:/4b800010.zip",
    "S:/4b800011.zip",
    "S:/4b800012.zip",
    "S:/4b800013.zip",
    "S:/4b800014.zip",
    "S:/4b800015.zip"
#endif
};
static const char *page_meter_imglist_2_imgs[10] = {
#if LV_USE_GUIBUILDER_SIMULATOR
    "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\speed\\gongli\\numsn_0.png",
    "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\speed\\gongli\\numsn_1.png",
    "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\speed\\gongli\\numsn_2.png",
    "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\speed\\gongli\\numsn_3.png",
    "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\speed\\gongli\\numsn_4.png",
    "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\speed\\gongli\\numsn_5.png",
    "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\speed\\gongli\\numsn_6.png",
    "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\speed\\gongli\\numsn_7.png",
    "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\speed\\gongli\\numsn_8.png",
    "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\speed\\gongli\\numsn_9.png"
#else
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000e9.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000ea.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000eb.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000ec.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000ed.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000ee.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000ef.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000f0.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000f1.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000f2.zip"
#endif
};
static const char *page_meter_imglist_3_imgs[10] = {
#if LV_USE_GUIBUILDER_SIMULATOR
    "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\speed\\gongli\\numsn_0.png",
    "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\speed\\gongli\\numsn_1.png",
    "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\speed\\gongli\\numsn_2.png",
    "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\speed\\gongli\\numsn_3.png",
    "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\speed\\gongli\\numsn_4.png",
    "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\speed\\gongli\\numsn_5.png",
    "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\speed\\gongli\\numsn_6.png",
    "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\speed\\gongli\\numsn_7.png",
    "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\speed\\gongli\\numsn_8.png",
    "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\speed\\gongli\\numsn_9.png"
#else
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000e9.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000ea.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000eb.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000ec.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000ed.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000ee.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000ef.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000f0.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000f1.zip",
    "mnt/sdfile/EXT_RESERVED/uipackres/ui/4b0000f2.zip"
#endif
};

lv_obj_t *setup_scr_page_meter(lv_ui *ui)
{
    lv_ui_page_meter *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_PAGE_METER);
    if (ui_scr == NULL) {
        ui_scr = lv_mem_alloc(sizeof(lv_ui_page_meter));
        if (ui_scr == NULL) {
            return NULL;
        }
        memset(ui_scr, 0, sizeof(lv_ui_page_meter));
        ui->page_meter = ui_scr;
    }

    //Write codes page_meter
    ui_scr->page_meter = lv_obj_create(NULL);
    lv_obj_set_scrollbar_mode(ui_scr->page_meter, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->page_meter, GUI_CTRL_SCR);

    //Set style for page_meter. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->page_meter, lv_color_make(0x00, 0x00, 0x00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_scr->page_meter, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes page_meter_imglist_1
    ui_scr->page_meter_imglist_1 = lv_imglist_create(ui_scr->page_meter);
    lv_obj_set_pos(ui_scr->page_meter_imglist_1, 0, 0);
    lv_obj_set_size(ui_scr->page_meter_imglist_1, 800, 480);
    lv_obj_set_scrollbar_mode(ui_scr->page_meter_imglist_1, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->page_meter_imglist_1, GUI_CTRL_IMGLIST);
    lv_imglist_set_src(ui_scr->page_meter_imglist_1, (const void **) page_meter_imglist_1_imgs, 22);
    lv_imglist_set_act(ui_scr->page_meter_imglist_1, 0);

    // Write Timer page_meter_timer_1
    if (ui_scr->page_meter_timer_1 != NULL) {
        lv_timer_del(ui_scr->page_meter_timer_1);
    }
    ui_scr->page_meter_timer_1 = lv_timer_create(page_meter_timer_1_timer_cb, 30, "");
    lv_timer_set_repeat_count(ui_scr->page_meter_timer_1, -1);

    //Write codes page_meter_imglist_2
    ui_scr->page_meter_imglist_2 = lv_imglist_create(ui_scr->page_meter);
    lv_obj_set_pos(ui_scr->page_meter_imglist_2, 338, 167);
    lv_obj_set_size(ui_scr->page_meter_imglist_2, 58, 61);
    lv_obj_set_scrollbar_mode(ui_scr->page_meter_imglist_2, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->page_meter_imglist_2, GUI_CTRL_IMGLIST);
    lv_imglist_set_src(ui_scr->page_meter_imglist_2, (const void **) page_meter_imglist_2_imgs, 10);
    lv_imglist_set_act(ui_scr->page_meter_imglist_2, 0);

    //Write codes page_meter_imglist_3
    ui_scr->page_meter_imglist_3 = lv_imglist_create(ui_scr->page_meter);
    lv_obj_set_pos(ui_scr->page_meter_imglist_3, 409, 167);
    lv_obj_set_size(ui_scr->page_meter_imglist_3, 58, 61);
    lv_obj_set_scrollbar_mode(ui_scr->page_meter_imglist_3, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->page_meter_imglist_3, GUI_CTRL_IMGLIST);
    lv_imglist_set_src(ui_scr->page_meter_imglist_3, (const void **) page_meter_imglist_3_imgs, 10);
    lv_imglist_set_act(ui_scr->page_meter_imglist_3, 0);

    //Write codes page_meter_img_1
    ui_scr->page_meter_img_1 = lv_img_create(ui_scr->page_meter);
    lv_img_set_src(ui_scr->page_meter_img_1, gui_get_res_path(GUI_RES_READYC_PNG));
    lv_img_set_pivot(ui_scr->page_meter_img_1, 0, 0);
    lv_img_set_angle(ui_scr->page_meter_img_1, 0);
    lv_img_set_zoom(ui_scr->page_meter_img_1, 256);
    lv_obj_set_pos(ui_scr->page_meter_img_1, 368, 266);
    lv_obj_set_size(ui_scr->page_meter_img_1, 76, 15);
    lv_obj_add_flag(ui_scr->page_meter_img_1, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->page_meter_img_1, GUI_CTRL_IMG);

    //Write codes page_meter_img_2
    ui_scr->page_meter_img_2 = lv_img_create(ui_scr->page_meter);
    lv_img_set_src(ui_scr->page_meter_img_2, gui_get_res_path(GUI_RES_LAMP_02_PNG));
    lv_img_set_pivot(ui_scr->page_meter_img_2, 0, 0);
    lv_img_set_angle(ui_scr->page_meter_img_2, 0);
    lv_img_set_zoom(ui_scr->page_meter_img_2, 256);
    lv_obj_set_pos(ui_scr->page_meter_img_2, 123, 345);
    lv_obj_set_size(ui_scr->page_meter_img_2, 40, 40);
    lv_obj_add_flag(ui_scr->page_meter_img_2, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->page_meter_img_2, GUI_CTRL_IMG);

    //Write codes page_meter_img_3
    ui_scr->page_meter_img_3 = lv_img_create(ui_scr->page_meter);
    lv_img_set_src(ui_scr->page_meter_img_3, gui_get_res_path(GUI_RES_FREE_PNG));
    lv_img_set_pivot(ui_scr->page_meter_img_3, 0, 0);
    lv_img_set_angle(ui_scr->page_meter_img_3, 0);
    lv_img_set_zoom(ui_scr->page_meter_img_3, 256);
    lv_obj_set_pos(ui_scr->page_meter_img_3, 56, 147);
    lv_obj_set_size(ui_scr->page_meter_img_3, 84, 32);
    lv_obj_add_flag(ui_scr->page_meter_img_3, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->page_meter_img_3, GUI_CTRL_IMG);

    //Write codes page_meter_img_4
    ui_scr->page_meter_img_4 = lv_img_create(ui_scr->page_meter);
    lv_img_set_src(ui_scr->page_meter_img_4, gui_get_res_path(GUI_RES_LAMP_06_PNG));
    lv_img_set_pivot(ui_scr->page_meter_img_4, 0, 0);
    lv_img_set_angle(ui_scr->page_meter_img_4, 0);
    lv_img_set_zoom(ui_scr->page_meter_img_4, 256);
    lv_obj_set_pos(ui_scr->page_meter_img_4, 79, 279);
    lv_obj_set_size(ui_scr->page_meter_img_4, 40, 40);
    lv_obj_add_flag(ui_scr->page_meter_img_4, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->page_meter_img_4, GUI_CTRL_IMG);

    //Write codes page_meter_img_5
    ui_scr->page_meter_img_5 = lv_img_create(ui_scr->page_meter);
    lv_img_set_src(ui_scr->page_meter_img_5, gui_get_res_path(GUI_RES_LAMP_03_PNG));
    lv_img_set_pivot(ui_scr->page_meter_img_5, 0, 0);
    lv_img_set_angle(ui_scr->page_meter_img_5, 0);
    lv_img_set_zoom(ui_scr->page_meter_img_5, 256);
    lv_obj_set_pos(ui_scr->page_meter_img_5, 115, 73);
    lv_obj_set_size(ui_scr->page_meter_img_5, 40, 40);
    lv_obj_add_flag(ui_scr->page_meter_img_5, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->page_meter_img_5, GUI_CTRL_IMG);

    //Write codes page_meter_img_6
    ui_scr->page_meter_img_6 = lv_img_create(ui_scr->page_meter);
    lv_img_set_src(ui_scr->page_meter_img_6, gui_get_res_path(GUI_RES_LAMP_07_PNG));
    lv_img_set_pivot(ui_scr->page_meter_img_6, 0, 0);
    lv_img_set_angle(ui_scr->page_meter_img_6, 0);
    lv_img_set_zoom(ui_scr->page_meter_img_6, 256);
    lv_obj_set_pos(ui_scr->page_meter_img_6, 43, 211);
    lv_obj_set_size(ui_scr->page_meter_img_6, 40, 40);
    lv_obj_add_flag(ui_scr->page_meter_img_6, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->page_meter_img_6, GUI_CTRL_IMG);

    //Write codes page_meter_img_7
    ui_scr->page_meter_img_7 = lv_img_create(ui_scr->page_meter);
    lv_img_set_src(ui_scr->page_meter_img_7, gui_get_res_path(GUI_RES_LAMP_17_PNG));
    lv_img_set_pivot(ui_scr->page_meter_img_7, 0, 0);
    lv_img_set_angle(ui_scr->page_meter_img_7, 0);
    lv_img_set_zoom(ui_scr->page_meter_img_7, 256);
    lv_obj_set_pos(ui_scr->page_meter_img_7, 49, 402);
    lv_obj_set_size(ui_scr->page_meter_img_7, 40, 40);
    lv_obj_add_flag(ui_scr->page_meter_img_7, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->page_meter_img_7, GUI_CTRL_IMG);

    //Write codes page_meter_img_8
    ui_scr->page_meter_img_8 = lv_img_create(ui_scr->page_meter);
    lv_img_set_src(ui_scr->page_meter_img_8, gui_get_res_path(GUI_RES_LAMP_01_PNG));
    lv_img_set_pivot(ui_scr->page_meter_img_8, 0, 0);
    lv_img_set_angle(ui_scr->page_meter_img_8, 0);
    lv_img_set_zoom(ui_scr->page_meter_img_8, 256);
    lv_obj_set_pos(ui_scr->page_meter_img_8, 49, 30);
    lv_obj_set_size(ui_scr->page_meter_img_8, 40, 40);
    lv_obj_add_flag(ui_scr->page_meter_img_8, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->page_meter_img_8, GUI_CTRL_IMG);

    //Write codes page_meter_img_9
    ui_scr->page_meter_img_9 = lv_img_create(ui_scr->page_meter);
    lv_img_set_src(ui_scr->page_meter_img_9, gui_get_res_path(GUI_RES_LAMP_04_PNG));
    lv_img_set_pivot(ui_scr->page_meter_img_9, 0, 0);
    lv_img_set_angle(ui_scr->page_meter_img_9, 0);
    lv_img_set_zoom(ui_scr->page_meter_img_9, 256);
    lv_obj_set_pos(ui_scr->page_meter_img_9, 701, 30);
    lv_obj_set_size(ui_scr->page_meter_img_9, 40, 40);
    lv_obj_add_flag(ui_scr->page_meter_img_9, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->page_meter_img_9, GUI_CTRL_IMG);

    //Write codes page_meter_img_10
    ui_scr->page_meter_img_10 = lv_img_create(ui_scr->page_meter);
    lv_img_set_src(ui_scr->page_meter_img_10, gui_get_res_path(GUI_RES_GEAR_1_PNG));
    lv_img_set_pivot(ui_scr->page_meter_img_10, 0, 0);
    lv_img_set_angle(ui_scr->page_meter_img_10, 0);
    lv_img_set_zoom(ui_scr->page_meter_img_10, 256);
    lv_obj_set_pos(ui_scr->page_meter_img_10, 429, 408);
    lv_obj_set_size(ui_scr->page_meter_img_10, 28, 28);
    lv_obj_add_flag(ui_scr->page_meter_img_10, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->page_meter_img_10, GUI_CTRL_IMG);

    //Write codes page_meter_img_11
    ui_scr->page_meter_img_11 = lv_img_create(ui_scr->page_meter);
    lv_img_set_src(ui_scr->page_meter_img_11, gui_get_res_path(GUI_RES_GEAR_1_PNG));
    lv_img_set_pivot(ui_scr->page_meter_img_11, 0, 0);
    lv_img_set_angle(ui_scr->page_meter_img_11, 0);
    lv_img_set_zoom(ui_scr->page_meter_img_11, 256);
    lv_obj_set_pos(ui_scr->page_meter_img_11, 402, 408);
    lv_obj_set_size(ui_scr->page_meter_img_11, 28, 28);
    lv_obj_add_flag(ui_scr->page_meter_img_11, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->page_meter_img_11, GUI_CTRL_IMG);

    //Write codes page_meter_img_12
    ui_scr->page_meter_img_12 = lv_img_create(ui_scr->page_meter);
    lv_img_set_src(ui_scr->page_meter_img_12, gui_get_res_path(GUI_RES_GEAR_1_PNG));
    lv_img_set_pivot(ui_scr->page_meter_img_12, 0, 0);
    lv_img_set_angle(ui_scr->page_meter_img_12, 0);
    lv_img_set_zoom(ui_scr->page_meter_img_12, 256);
    lv_obj_set_pos(ui_scr->page_meter_img_12, 376, 408);
    lv_obj_set_size(ui_scr->page_meter_img_12, 28, 28);
    lv_obj_add_flag(ui_scr->page_meter_img_12, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->page_meter_img_12, GUI_CTRL_IMG);

    //Write codes page_meter_img_13
    ui_scr->page_meter_img_13 = lv_img_create(ui_scr->page_meter);
    lv_img_set_src(ui_scr->page_meter_img_13, gui_get_res_path(GUI_RES_GEAR_1_PNG));
    lv_img_set_pivot(ui_scr->page_meter_img_13, 0, 0);
    lv_img_set_angle(ui_scr->page_meter_img_13, 0);
    lv_img_set_zoom(ui_scr->page_meter_img_13, 256);
    lv_obj_set_pos(ui_scr->page_meter_img_13, 353, 408);
    lv_obj_set_size(ui_scr->page_meter_img_13, 28, 28);
    lv_obj_add_flag(ui_scr->page_meter_img_13, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->page_meter_img_13, GUI_CTRL_IMG);

    //Write codes page_meter_img_14
    ui_scr->page_meter_img_14 = lv_img_create(ui_scr->page_meter);
    lv_img_set_src(ui_scr->page_meter_img_14, gui_get_res_path(GUI_RES_MILEAGE_KM_PNG));
    lv_img_set_pivot(ui_scr->page_meter_img_14, 0, 0);
    lv_img_set_angle(ui_scr->page_meter_img_14, 0);
    lv_img_set_zoom(ui_scr->page_meter_img_14, 256);
    lv_obj_set_pos(ui_scr->page_meter_img_14, 459, 418);
    lv_obj_set_size(ui_scr->page_meter_img_14, 15, 16);
    lv_obj_add_flag(ui_scr->page_meter_img_14, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->page_meter_img_14, GUI_CTRL_IMG);

    //Write codes page_meter_img_15
    ui_scr->page_meter_img_15 = lv_img_create(ui_scr->page_meter);
    lv_img_set_src(ui_scr->page_meter_img_15, gui_get_res_path(GUI_RES_VOLTAGE_72V_PNG));
    lv_img_set_pivot(ui_scr->page_meter_img_15, 0, 0);
    lv_img_set_angle(ui_scr->page_meter_img_15, 0);
    lv_img_set_zoom(ui_scr->page_meter_img_15, 256);
    lv_obj_set_pos(ui_scr->page_meter_img_15, 197, 420);
    lv_obj_set_size(ui_scr->page_meter_img_15, 60, 26);
    lv_obj_add_flag(ui_scr->page_meter_img_15, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->page_meter_img_15, GUI_CTRL_IMG);

    //Write codes page_meter_img_16
    ui_scr->page_meter_img_16 = lv_img_create(ui_scr->page_meter);
    lv_img_set_src(ui_scr->page_meter_img_16, gui_get_res_path(GUI_RES_LOGO_PNG));
    lv_img_set_pivot(ui_scr->page_meter_img_16, 0, 0);
    lv_img_set_angle(ui_scr->page_meter_img_16, 0);
    lv_img_set_zoom(ui_scr->page_meter_img_16, 256);
    lv_obj_set_pos(ui_scr->page_meter_img_16, 359, 361);
    lv_obj_set_size(ui_scr->page_meter_img_16, 71, 18);
    lv_obj_add_flag(ui_scr->page_meter_img_16, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->page_meter_img_16, GUI_CTRL_IMG);

    //Write codes page_meter_img_17
    ui_scr->page_meter_img_17 = lv_img_create(ui_scr->page_meter);
    lv_img_set_src(ui_scr->page_meter_img_17, gui_get_res_path(GUI_RES_MILEAGE_TRIP_PNG));
    lv_img_set_pivot(ui_scr->page_meter_img_17, 0, 0);
    lv_img_set_angle(ui_scr->page_meter_img_17, 0);
    lv_img_set_zoom(ui_scr->page_meter_img_17, 256);
    lv_obj_set_pos(ui_scr->page_meter_img_17, 328, 408);
    lv_obj_set_size(ui_scr->page_meter_img_17, 22, 16);
    lv_obj_add_flag(ui_scr->page_meter_img_17, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->page_meter_img_17, GUI_CTRL_IMG);

    //Write codes page_meter_img_18
    ui_scr->page_meter_img_18 = lv_img_create(ui_scr->page_meter);
    lv_img_set_src(ui_scr->page_meter_img_18, gui_get_res_path(GUI_RES_SINGER100_PNG));
    lv_img_set_pivot(ui_scr->page_meter_img_18, 0, 0);
    lv_img_set_angle(ui_scr->page_meter_img_18, 0);
    lv_img_set_zoom(ui_scr->page_meter_img_18, 256);
    lv_obj_set_pos(ui_scr->page_meter_img_18, 658, 191);
    lv_obj_set_size(ui_scr->page_meter_img_18, 100, 100);
    lv_obj_add_flag(ui_scr->page_meter_img_18, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->page_meter_img_18, GUI_CTRL_IMG);

    //Write codes page_meter_btn_1
    ui_scr->page_meter_btn_1 = lv_btn_create(ui_scr->page_meter);
    lv_obj_set_pos(ui_scr->page_meter_btn_1, 154, 11);
    lv_obj_set_size(ui_scr->page_meter_btn_1, 58, 36);
    lv_obj_set_scrollbar_mode(ui_scr->page_meter_btn_1, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->page_meter_btn_1, GUI_CTRL_BUTTON);

    //Set style for page_meter_btn_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->page_meter_btn_1, lv_color_make(0x40, 0xEC, 0xC2), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_scr->page_meter_btn_1, &lv_font_montserratMedium_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Delete extra default style for page_meter_btn_1
    lv_obj_remove_style(ui_scr->page_meter_btn_1, &gui_btn_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    ui_scr->page_meter_btn_1_label = lv_label_create(ui_scr->page_meter_btn_1);
    lv_label_set_text(ui_scr->page_meter_btn_1_label, "back");
    lv_obj_set_style_pad_all(ui_scr->page_meter_btn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->page_meter_btn_1_label, LV_ALIGN_CENTER, 0, 0);

    //Write codes page_meter_btn_2
    ui_scr->page_meter_btn_2 = lv_btn_create(ui_scr->page_meter);
    lv_obj_set_pos(ui_scr->page_meter_btn_2, 218, 11);
    lv_obj_set_size(ui_scr->page_meter_btn_2, 58, 36);
    lv_obj_set_scrollbar_mode(ui_scr->page_meter_btn_2, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->page_meter_btn_2, GUI_CTRL_BUTTON);

    //Set style for page_meter_btn_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_bg_color(ui_scr->page_meter_btn_2, lv_color_make(0x40, 0xEC, 0xC2), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_scr->page_meter_btn_2, &lv_font_montserratMedium_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Delete extra default style for page_meter_btn_2
    lv_obj_remove_style(ui_scr->page_meter_btn_2, &gui_btn_main_focus_key_style, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    ui_scr->page_meter_btn_2_label = lv_label_create(ui_scr->page_meter_btn_2);
    lv_label_set_text(ui_scr->page_meter_btn_2_label, "next");
    lv_obj_set_style_pad_all(ui_scr->page_meter_btn_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->page_meter_btn_2_label, LV_ALIGN_CENTER, 0, 0);

    lv_obj_update_layout(ui_scr->page_meter);
    ui_scr->page_meter_del = false;
    i18n_refresh_texts(GUI_SCREEN_PAGE_METER);

    //Init events for screen
    events_init_page_meter(ui);
    return ui_scr->page_meter;
}
void unload_scr_page_meter(lv_ui *ui)
{
    lv_ui_page_meter *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_PAGE_METER);
    if (ui_scr->page_meter_timer_1 != NULL) {
        lv_timer_del(ui_scr->page_meter_timer_1);
        ui_scr->page_meter_timer_1 = NULL;
    }
    ui_free_scr_ptr(ui, GUI_SCREEN_PAGE_METER);
}

#endif
