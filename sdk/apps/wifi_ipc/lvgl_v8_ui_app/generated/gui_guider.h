/*Generate Code, Do NOT Edit!*/
#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"
#include "./common.h"
#include "./gui_fonts/gui_fonts.h"
#include "./gui_images/gui_images.h"
#include "./gui_scr/ui_scr_manager.h"
#include "./gui_scr/ui_style.h"
#include "./i18n/lv_i18n.h"

#ifdef JL_GUI_KERNEL_VERSION_MAJOR
#if GUI_CORE_VERSION_MAJOR > JL_GUI_KERNEL_VERSION_MAJOR
#error "Current SDK Version is older than the kernel version. Please update the SDK version!"
#endif
#if GUI_CORE_VERSION_MAJOR < JL_GUI_KERNEL_VERSION_MAJOR
#error "Current SDK Version is newer than the kernel version. Please update the kernel version!"
#endif
#if GUI_CORE_VERSION_MINOR > JL_GUI_KERNEL_VERSION_MINOR
#warning "Current Kernel Version is too low, some features may not be available, please update the kernel version!"
#endif
#else
#error "Current Kernel Version is not defined, please replace or upgrade the kernel!"
#endif

#ifndef LV_USE_GUIBUILDER_SIMULATOR
#if defined(COMPATIBLE_UI_PRJ_TEMPLATE_VERSION_MIN_MAJOR) && defined(COMPATIBLE_UI_PRJ_TEMPLATE_VERSION_MAX_MAJOR)
#if GUI_TEMPLATE_VERSION_MAJOR < COMPATIBLE_UI_PRJ_TEMPLATE_VERSION_MIN_MAJOR || GUI_TEMPLATE_VERSION_MAJOR > COMPATIBLE_UI_PRJ_TEMPLATE_VERSION_MAX_MAJOR
#error "Current Project Template Version is not compatible with the SDK version. Please select a compatible SDK version!"
#endif
#if GUI_TEMPLATE_VERSION_MINOR < COMPATIBLE_UI_PRJ_TEMPLATE_VERSION_MIN_MINOR || GUI_TEMPLATE_VERSION_MINOR > COMPATIBLE_UI_PRJ_TEMPLATE_VERSION_MAX_MINOR
#warning "Current Project Template Version has minor incompatibilities with the SDK. Some features may not be available. Consider updating the SDK version."
#endif
#endif
#endif

typedef struct {
    // Screen start
    lv_obj_t *start;
    bool      start_del;
    lv_obj_t *start_img_logo;
} lv_ui_start;

typedef struct {
    // Screen home
    lv_obj_t *home;
    bool      home_del;
    lv_obj_t *home_img_wifi;
    lv_obj_t *home_lbl_bat;
    lv_obj_t *home_lbl_2;
    lv_obj_t *home_lbl_4;
    lv_obj_t *home_lbl_5;
    lv_obj_t *home_img_funkey1;
    lv_obj_t *home_img_funkey3;
    lv_obj_t *home_img_funkey2;
    lv_obj_t *home_digitclock_time;
    lv_obj_t *home_img_weather;
    lv_obj_t *home_img_bat;
    lv_obj_t *home_lbl_note;
    lv_obj_t *home_img_menu;
    lv_obj_t *home_imglist_bat;
    lv_obj_t *home_imglist_wifi;
} lv_ui_home;

typedef struct {
    // Screen menu
    lv_obj_t *menu;
    bool      menu_del;
    lv_obj_t *menu_edit_return;
    lv_obj_t *menu_edit_download;
    lv_obj_t *menu_edit_netcfg;
    lv_obj_t *menu_edit_language;
    lv_obj_t *menu_edit_sysset;
    lv_obj_t *menu_img_return;
    lv_obj_t *menu_edit_sysinfo;
    lv_obj_t *menu_img_download;
    lv_obj_t *menu_img_netcfg;
    lv_obj_t *menu_img_language;
    lv_obj_t *menu_img_sysset;
    lv_obj_t *menu_img_sysinfo;
} lv_ui_menu;

typedef struct {
    // Screen language
    lv_obj_t *language;
    bool      language_del;
    lv_obj_t *language_btn_return;
    lv_obj_t *language_btn_return_label;
    lv_obj_t *language_list_language;
    lv_obj_t *language_list_language_item0;
    lv_obj_t *language_list_language_item1;
    lv_obj_t *language_list_language_item2;
} lv_ui_language;

typedef struct {
    // Screen app
    lv_obj_t *app;
    bool      app_del;
    lv_obj_t *app_btn_return;
    lv_obj_t *app_btn_return_label;
    lv_obj_t *app_img_qrcode;
} lv_ui_app;

typedef struct {
    // Screen syscfg
    lv_obj_t *syscfg;
    bool      syscfg_del;
    lv_obj_t *syscfg_btn_return;
    lv_obj_t *syscfg_btn_return_label;
    lv_obj_t *syscfg_list_sysset;
    lv_obj_t *syscfg_list_sysset_item0;
    lv_obj_t *syscfg_list_sysset_item1;
    lv_obj_t *syscfg_list_sysset_item2;
} lv_ui_syscfg;

typedef struct {
    // Screen sysinfo
    lv_obj_t *sysinfo;
    bool      sysinfo_del;
    lv_obj_t *sysinfo_img_info;
    lv_obj_t *sysinfo_btn_return;
    lv_obj_t *sysinfo_btn_return_label;
} lv_ui_sysinfo;

// generate lv_ui gui_guider
typedef struct {
    lv_ui_start *start;
    lv_ui_home *home;
    lv_ui_menu *menu;
    lv_ui_language *language;
    lv_ui_app *app;
    lv_ui_syscfg *syscfg;
    lv_ui_sysinfo *sysinfo;

    lv_group_t *default_group;
} lv_ui;

void ui_load_scr_anim(lv_ui *ui, gui_scr_t *screen, lv_scr_load_anim_t anim_type,	uint32_t time,
                      uint32_t delay, bool is_clean, bool auto_del, bool is_push_satck);

void ui_scr_stack_pop_anim(lv_ui *ui, lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay,
                           bool is_clean, bool auto_del, bool is_push_satck);

gui_scr_t *ui_get_scr(int32_t scr_id);
gui_scr_t *ui_get_setup_scr(int32_t scr_id);
lv_obj_t *ui_get_setup_scr_obj(int32_t scr_id);
void *ui_get_scr_ptr(lv_ui *ui, int32_t scr_id);
void ui_free_scr_ptr(lv_ui *ui, int32_t scr_id);
bool ui_is_act_scr(int32_t scr_id);
void ui_init_style(lv_style_t *style);
void setup_ui(lv_ui *ui);
#include "./gui_msg/gui_msg.h"
extern lv_ui guider_ui;// Screen start
lv_obj_t *setup_scr_start(lv_ui *ui);
void unload_scr_start(lv_ui *ui);
// Screen home
lv_obj_t *setup_scr_home(lv_ui *ui);
void unload_scr_home(lv_ui *ui);
/*DigitalClock*/
void clock_count_with_year(int *year, int *month, int *day, int *hour, int *min, int *sec);


// Screen menu
lv_obj_t *setup_scr_menu(lv_ui *ui);
void unload_scr_menu(lv_ui *ui);
// Screen language
lv_obj_t *setup_scr_language(lv_ui *ui);
void unload_scr_language(lv_ui *ui);
// Screen app
lv_obj_t *setup_scr_app(lv_ui *ui);
void unload_scr_app(lv_ui *ui);
// Screen syscfg
lv_obj_t *setup_scr_syscfg(lv_ui *ui);
void unload_scr_syscfg(lv_ui *ui);
// Screen sysinfo
lv_obj_t *setup_scr_sysinfo(lv_ui *ui);
void unload_scr_sysinfo(lv_ui *ui);
#ifdef __cplusplus
}
#endif
#endif
