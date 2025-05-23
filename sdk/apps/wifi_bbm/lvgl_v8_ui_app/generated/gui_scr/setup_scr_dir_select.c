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


lv_obj_t *setup_scr_dir_select(lv_ui *ui)
{
    lv_ui_dir_select *ui_scr = ui_get_scr_ptr(ui, GUI_SCREEN_DIR_SELECT);
    if (ui_scr == NULL) {
        ui_scr = lv_mem_alloc(sizeof(lv_ui_dir_select));
        memset(ui_scr, 0, sizeof(lv_ui_dir_select));
        ui->dir_select = ui_scr;
    }

    //Write codes dir_select
    ui_scr->dir_select = lv_obj_create(NULL);
    lv_group_t *def_group = lv_group_get_default();
    lv_obj_set_scrollbar_mode(ui_scr->dir_select, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->dir_select, GUI_CTRL_SCR);

    //Write codes dir_select_view_1
    ui_scr->dir_select_view_1 = lv_obj_create(ui_scr->dir_select);
    lv_obj_set_pos(ui_scr->dir_select_view_1, 80, 121);
    lv_obj_set_size(ui_scr->dir_select_view_1, 160, 160);
    lv_obj_set_scrollbar_mode(ui_scr->dir_select_view_1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->dir_select_view_1, LV_OBJ_FLAG_CLICKABLE);
    lv_group_add_obj(def_group, ui_scr->dir_select_view_1);
    ui_style_set(ui_scr->dir_select_view_1, GUI_CTRL_CONT);

    //Write codes dir_select_img_1
    ui_scr->dir_select_img_1 = lv_img_create(ui_scr->dir_select_view_1);
    lv_img_set_src(ui_scr->dir_select_img_1, gui_get_res_path(GUI_RES_DIR_PNG));
    lv_img_set_pivot(ui_scr->dir_select_img_1, 0, 0);
    lv_img_set_angle(ui_scr->dir_select_img_1, 0);
    lv_img_set_zoom(ui_scr->dir_select_img_1, 256);
    lv_obj_set_pos(ui_scr->dir_select_img_1, 16, 0);
    lv_obj_set_size(ui_scr->dir_select_img_1, 128, 128);
    lv_obj_add_flag(ui_scr->dir_select_img_1, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_add_flag(ui_scr->dir_select_img_1, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->dir_select_img_1, GUI_CTRL_IMG);

    //Write codes dir_select_lbl_2
    ui_scr->dir_select_lbl_2 = lv_label_create(ui_scr->dir_select_view_1);
    lv_label_set_text(ui_scr->dir_select_lbl_2, "Ch1");
    lv_label_set_long_mode(ui_scr->dir_select_lbl_2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->dir_select_lbl_2, 50, 128);
    lv_obj_set_size(ui_scr->dir_select_lbl_2, 60, 30);
    lv_obj_set_scrollbar_mode(ui_scr->dir_select_lbl_2, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->dir_select_lbl_2, GUI_CTRL_LABEL);

    //Set style for dir_select_lbl_2. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_border_opa(ui_scr->dir_select_lbl_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_scr->dir_select_lbl_2, 128, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes dir_select_view_2
    ui_scr->dir_select_view_2 = lv_obj_create(ui_scr->dir_select);
    lv_obj_set_pos(ui_scr->dir_select_view_2, 320, 120);
    lv_obj_set_size(ui_scr->dir_select_view_2, 160, 160);
    lv_obj_set_scrollbar_mode(ui_scr->dir_select_view_2, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->dir_select_view_2, LV_OBJ_FLAG_CLICKABLE);
    lv_group_add_obj(def_group, ui_scr->dir_select_view_2);
    ui_style_set(ui_scr->dir_select_view_2, GUI_CTRL_CONT);

    //Write codes dir_select_img_2
    ui_scr->dir_select_img_2 = lv_img_create(ui_scr->dir_select_view_2);
    lv_img_set_src(ui_scr->dir_select_img_2, gui_get_res_path(GUI_RES_DIR_PNG));
    lv_img_set_pivot(ui_scr->dir_select_img_2, 0, 0);
    lv_img_set_angle(ui_scr->dir_select_img_2, 0);
    lv_img_set_zoom(ui_scr->dir_select_img_2, 256);
    lv_obj_set_pos(ui_scr->dir_select_img_2, 16, 0);
    lv_obj_set_size(ui_scr->dir_select_img_2, 128, 128);
    lv_obj_add_flag(ui_scr->dir_select_img_2, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_add_flag(ui_scr->dir_select_img_2, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->dir_select_img_2, GUI_CTRL_IMG);

    //Write codes dir_select_lbl_3
    ui_scr->dir_select_lbl_3 = lv_label_create(ui_scr->dir_select_view_2);
    lv_label_set_text(ui_scr->dir_select_lbl_3, "Ch1");
    lv_label_set_long_mode(ui_scr->dir_select_lbl_3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->dir_select_lbl_3, 50, 128);
    lv_obj_set_size(ui_scr->dir_select_lbl_3, 60, 30);
    lv_obj_set_scrollbar_mode(ui_scr->dir_select_lbl_3, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->dir_select_lbl_3, GUI_CTRL_LABEL);

    //Set style for dir_select_lbl_3. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_border_opa(ui_scr->dir_select_lbl_3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_scr->dir_select_lbl_3, 128, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes dir_select_view_3
    ui_scr->dir_select_view_3 = lv_obj_create(ui_scr->dir_select);
    lv_obj_set_pos(ui_scr->dir_select_view_3, 560, 121);
    lv_obj_set_size(ui_scr->dir_select_view_3, 160, 160);
    lv_obj_set_scrollbar_mode(ui_scr->dir_select_view_3, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->dir_select_view_3, LV_OBJ_FLAG_CLICKABLE);
    lv_group_add_obj(def_group, ui_scr->dir_select_view_3);
    ui_style_set(ui_scr->dir_select_view_3, GUI_CTRL_CONT);

    //Write codes dir_select_img_3
    ui_scr->dir_select_img_3 = lv_img_create(ui_scr->dir_select_view_3);
    lv_img_set_src(ui_scr->dir_select_img_3, gui_get_res_path(GUI_RES_DIR_PNG));
    lv_img_set_pivot(ui_scr->dir_select_img_3, 0, 0);
    lv_img_set_angle(ui_scr->dir_select_img_3, 0);
    lv_img_set_zoom(ui_scr->dir_select_img_3, 256);
    lv_obj_set_pos(ui_scr->dir_select_img_3, 16, 0);
    lv_obj_set_size(ui_scr->dir_select_img_3, 128, 128);
    lv_obj_add_flag(ui_scr->dir_select_img_3, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_add_flag(ui_scr->dir_select_img_3, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->dir_select_img_3, GUI_CTRL_IMG);

    //Write codes dir_select_lbl_4
    ui_scr->dir_select_lbl_4 = lv_label_create(ui_scr->dir_select_view_3);
    lv_label_set_text(ui_scr->dir_select_lbl_4, "Ch1");
    lv_label_set_long_mode(ui_scr->dir_select_lbl_4, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->dir_select_lbl_4, 50, 128);
    lv_obj_set_size(ui_scr->dir_select_lbl_4, 60, 30);
    lv_obj_set_scrollbar_mode(ui_scr->dir_select_lbl_4, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->dir_select_lbl_4, GUI_CTRL_LABEL);

    //Set style for dir_select_lbl_4. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_border_opa(ui_scr->dir_select_lbl_4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_scr->dir_select_lbl_4, 128, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes dir_select_view_4
    ui_scr->dir_select_view_4 = lv_obj_create(ui_scr->dir_select);
    lv_obj_set_pos(ui_scr->dir_select_view_4, 80, 300);
    lv_obj_set_size(ui_scr->dir_select_view_4, 160, 160);
    lv_obj_set_scrollbar_mode(ui_scr->dir_select_view_4, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->dir_select_view_4, LV_OBJ_FLAG_CLICKABLE);
    lv_group_add_obj(def_group, ui_scr->dir_select_view_4);
    ui_style_set(ui_scr->dir_select_view_4, GUI_CTRL_CONT);

    //Set style for dir_select_view_4. Part: LV_PART_MAIN, State: LV_STATE_FOCUS_KEY
    lv_obj_set_style_shadow_opa(ui_scr->dir_select_view_4, 0, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
    lv_obj_set_style_border_color(ui_scr->dir_select_view_4, lv_color_make(0x21, 0xB4, 0xF6), LV_PART_MAIN | LV_STATE_FOCUS_KEY);

    //Write codes dir_select_img_4
    ui_scr->dir_select_img_4 = lv_img_create(ui_scr->dir_select_view_4);
    lv_img_set_src(ui_scr->dir_select_img_4, gui_get_res_path(GUI_RES_DIR_PNG));
    lv_img_set_pivot(ui_scr->dir_select_img_4, 0, 0);
    lv_img_set_angle(ui_scr->dir_select_img_4, 0);
    lv_img_set_zoom(ui_scr->dir_select_img_4, 256);
    lv_obj_set_pos(ui_scr->dir_select_img_4, 16, 0);
    lv_obj_set_size(ui_scr->dir_select_img_4, 128, 128);
    lv_obj_add_flag(ui_scr->dir_select_img_4, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_add_flag(ui_scr->dir_select_img_4, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->dir_select_img_4, GUI_CTRL_IMG);

    //Write codes dir_select_lbl_5
    ui_scr->dir_select_lbl_5 = lv_label_create(ui_scr->dir_select_view_4);
    lv_label_set_text(ui_scr->dir_select_lbl_5, "Ch1");
    lv_label_set_long_mode(ui_scr->dir_select_lbl_5, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->dir_select_lbl_5, 50, 128);
    lv_obj_set_size(ui_scr->dir_select_lbl_5, 60, 30);
    lv_obj_set_scrollbar_mode(ui_scr->dir_select_lbl_5, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->dir_select_lbl_5, GUI_CTRL_LABEL);

    //Set style for dir_select_lbl_5. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_border_opa(ui_scr->dir_select_lbl_5, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_scr->dir_select_lbl_5, 128, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes dir_select_view_5
    ui_scr->dir_select_view_5 = lv_obj_create(ui_scr->dir_select);
    lv_obj_set_pos(ui_scr->dir_select_view_5, 320, 300);
    lv_obj_set_size(ui_scr->dir_select_view_5, 160, 160);
    lv_obj_set_scrollbar_mode(ui_scr->dir_select_view_5, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->dir_select_view_5, LV_OBJ_FLAG_CLICKABLE);
    lv_group_add_obj(def_group, ui_scr->dir_select_view_5);
    ui_style_set(ui_scr->dir_select_view_5, GUI_CTRL_CONT);

    //Write codes dir_select_img_5
    ui_scr->dir_select_img_5 = lv_img_create(ui_scr->dir_select_view_5);
    lv_img_set_src(ui_scr->dir_select_img_5, gui_get_res_path(GUI_RES_DIR_PNG));
    lv_img_set_pivot(ui_scr->dir_select_img_5, 0, 0);
    lv_img_set_angle(ui_scr->dir_select_img_5, 0);
    lv_img_set_zoom(ui_scr->dir_select_img_5, 256);
    lv_obj_set_pos(ui_scr->dir_select_img_5, 16, 0);
    lv_obj_set_size(ui_scr->dir_select_img_5, 128, 128);
    lv_obj_add_flag(ui_scr->dir_select_img_5, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_add_flag(ui_scr->dir_select_img_5, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->dir_select_img_5, GUI_CTRL_IMG);

    //Write codes dir_select_lbl_6
    ui_scr->dir_select_lbl_6 = lv_label_create(ui_scr->dir_select_view_5);
    lv_label_set_text(ui_scr->dir_select_lbl_6, "Ch1");
    lv_label_set_long_mode(ui_scr->dir_select_lbl_6, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->dir_select_lbl_6, 50, 128);
    lv_obj_set_size(ui_scr->dir_select_lbl_6, 60, 30);
    lv_obj_set_scrollbar_mode(ui_scr->dir_select_lbl_6, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->dir_select_lbl_6, GUI_CTRL_LABEL);

    //Set style for dir_select_lbl_6. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_border_opa(ui_scr->dir_select_lbl_6, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_scr->dir_select_lbl_6, 128, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes dir_select_view_6
    ui_scr->dir_select_view_6 = lv_obj_create(ui_scr->dir_select);
    lv_obj_set_pos(ui_scr->dir_select_view_6, 560, 300);
    lv_obj_set_size(ui_scr->dir_select_view_6, 160, 160);
    lv_obj_set_scrollbar_mode(ui_scr->dir_select_view_6, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui_scr->dir_select_view_6, LV_OBJ_FLAG_CLICKABLE);
    lv_group_add_obj(def_group, ui_scr->dir_select_view_6);
    ui_style_set(ui_scr->dir_select_view_6, GUI_CTRL_CONT);

    //Write codes dir_select_img_6
    ui_scr->dir_select_img_6 = lv_img_create(ui_scr->dir_select_view_6);
    lv_img_set_src(ui_scr->dir_select_img_6, gui_get_res_path(GUI_RES_DIR_PNG));
    lv_img_set_pivot(ui_scr->dir_select_img_6, 0, 0);
    lv_img_set_angle(ui_scr->dir_select_img_6, 0);
    lv_img_set_zoom(ui_scr->dir_select_img_6, 256);
    lv_obj_set_pos(ui_scr->dir_select_img_6, 16, 0);
    lv_obj_set_size(ui_scr->dir_select_img_6, 128, 128);
    lv_obj_add_flag(ui_scr->dir_select_img_6, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_add_flag(ui_scr->dir_select_img_6, LV_OBJ_FLAG_CLICKABLE);
    ui_style_set(ui_scr->dir_select_img_6, GUI_CTRL_IMG);

    //Write codes dir_select_lbl_7
    ui_scr->dir_select_lbl_7 = lv_label_create(ui_scr->dir_select_view_6);
    lv_label_set_text(ui_scr->dir_select_lbl_7, "Ch1");
    lv_label_set_long_mode(ui_scr->dir_select_lbl_7, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->dir_select_lbl_7, 50, 128);
    lv_obj_set_size(ui_scr->dir_select_lbl_7, 60, 30);
    lv_obj_set_scrollbar_mode(ui_scr->dir_select_lbl_7, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->dir_select_lbl_7, GUI_CTRL_LABEL);

    //Set style for dir_select_lbl_7. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_border_opa(ui_scr->dir_select_lbl_7, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_scr->dir_select_lbl_7, 128, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes dir_select_lbl_1
    ui_scr->dir_select_lbl_1 = lv_label_create(ui_scr->dir_select);
    lv_label_set_text(ui_scr->dir_select_lbl_1, "Select the folder to browser");
    lv_label_set_long_mode(ui_scr->dir_select_lbl_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui_scr->dir_select_lbl_1, 120, 36);
    lv_obj_set_size(ui_scr->dir_select_lbl_1, 559, 52);
    lv_obj_set_scrollbar_mode(ui_scr->dir_select_lbl_1, LV_SCROLLBAR_MODE_OFF);
    ui_style_set(ui_scr->dir_select_lbl_1, GUI_CTRL_LABEL);

    //Set style for dir_select_lbl_1. Part: LV_PART_MAIN, State: LV_STATE_DEFAULT
    lv_obj_set_style_shadow_opa(ui_scr->dir_select_lbl_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_scr->dir_select_lbl_1, &lv_font_montserratMedium_32, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes dir_select_imgbtn_1
    ui_scr->dir_select_imgbtn_1 = lv_imgbtn_create(ui_scr->dir_select);
    lv_obj_set_pos(ui_scr->dir_select_imgbtn_1, 24, 30);
    lv_obj_set_size(ui_scr->dir_select_imgbtn_1, 64, 64);
    lv_obj_set_scrollbar_mode(ui_scr->dir_select_imgbtn_1, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(def_group, ui_scr->dir_select_imgbtn_1);
    ui_style_set(ui_scr->dir_select_imgbtn_1, GUI_CTRL_IMGBTN);
    lv_imgbtn_set_src(ui_scr->dir_select_imgbtn_1, LV_IMGBTN_STATE_RELEASED, NULL, gui_get_res_path(GUI_RES_BACK_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->dir_select_imgbtn_1, LV_IMGBTN_STATE_PRESSED, NULL, gui_get_res_path(GUI_RES_BACK_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->dir_select_imgbtn_1, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, gui_get_res_path(GUI_RES_BACK_PNG), NULL);
    lv_imgbtn_set_src(ui_scr->dir_select_imgbtn_1, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, gui_get_res_path(GUI_RES_BACK_PNG), NULL);
    lv_obj_add_flag(ui_scr->dir_select_imgbtn_1, LV_OBJ_FLAG_CHECKABLE);
    ui_scr->dir_select_imgbtn_1_label = lv_label_create(ui_scr->dir_select_imgbtn_1);
    lv_label_set_text(ui_scr->dir_select_imgbtn_1_label, "");
    lv_obj_set_style_pad_all(ui_scr->dir_select_imgbtn_1, 0, LV_STATE_DEFAULT);
    lv_obj_align(ui_scr->dir_select_imgbtn_1_label, LV_ALIGN_CENTER, 0, 0);

    lv_obj_update_layout(ui_scr->dir_select);
    ui_scr->dir_select_del = false;

    //Init events for screen
    events_init_dir_select(ui);
    return ui_scr->dir_select;
}
void unload_scr_dir_select(lv_ui *ui)
{
    ui_free_scr_ptr(ui, GUI_SCREEN_DIR_SELECT);
}
