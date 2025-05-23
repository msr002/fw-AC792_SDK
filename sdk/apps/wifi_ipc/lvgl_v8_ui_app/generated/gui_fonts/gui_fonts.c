#include "lvgl.h"
#if LV_USE_GUIBUILDER_SIMULATOR
#include <stdio.h>
#endif
#include "./gui_fonts.h"
#include "../common.h"

lv_font_t lv_font_montserratMedium_22;
void lv_font_montserratMedium_22_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\ui_res\\flash\\rle\\font\\35000000.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin(gui_get_res_path(GUI_RES_MONTSERRATMEDIUM_22_TTF));
#endif
    if (fnt_font != NULL) {
        lv_font_montserratMedium_22 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\ui_res\\flash\\rle\\font\\35000000.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_MONTSERRATMEDIUM_22_TTF));
#endif
    }
}
lv_font_t lv_font_simsun_22;
void lv_font_simsun_22_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\ui_res\\flash\\rle\\font\\35000001.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin(gui_get_res_path(GUI_RES_SIMSUN_22_WOFF));
#endif
    if (fnt_font != NULL) {
        lv_font_simsun_22 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\ui_res\\flash\\rle\\font\\35000001.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_SIMSUN_22_WOFF));
#endif
    }
}
lv_font_t lv_font_montserratMedium_32;
void lv_font_montserratMedium_32_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\ui_res\\flash\\rle\\font\\35000002.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin(gui_get_res_path(GUI_RES_MONTSERRATMEDIUM_32_TTF));
#endif
    if (fnt_font != NULL) {
        lv_font_montserratMedium_32 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\ui_res\\flash\\rle\\font\\35000002.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_MONTSERRATMEDIUM_32_TTF));
#endif
    }
}
lv_font_t lv_font_FangZhengKaiTiJianTi_1_32;
void lv_font_FangZhengKaiTiJianTi_1_32_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\ui_res\\flash\\rle\\font\\35000003.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin(gui_get_res_path(GUI_RES_FANGZHENGKAITIJIANTI_1_32_TTF));
#endif
    if (fnt_font != NULL) {
        lv_font_FangZhengKaiTiJianTi_1_32 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\ui_res\\flash\\rle\\font\\35000003.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_FANGZHENGKAITIJIANTI_1_32_TTF));
#endif
    }
}
lv_font_t lv_font_FangZhengKaiTiJianTi_1_20;
void lv_font_FangZhengKaiTiJianTi_1_20_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\ui_res\\flash\\rle\\font\\35000004.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin(gui_get_res_path(GUI_RES_FANGZHENGKAITIJIANTI_1_20_TTF));
#endif
    if (fnt_font != NULL) {
        lv_font_FangZhengKaiTiJianTi_1_20 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\ui_res\\flash\\rle\\font\\35000004.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_FANGZHENGKAITIJIANTI_1_20_TTF));
#endif
    }
}
lv_font_t lv_font_FangZhengKaiTiJianTi_1_18;
void lv_font_FangZhengKaiTiJianTi_1_18_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\ui_res\\flash\\rle\\font\\35000005.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin(gui_get_res_path(GUI_RES_FANGZHENGKAITIJIANTI_1_18_TTF));
#endif
    if (fnt_font != NULL) {
        lv_font_FangZhengKaiTiJianTi_1_18 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\ui_res\\flash\\rle\\font\\35000005.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_FANGZHENGKAITIJIANTI_1_18_TTF));
#endif
    }
}
lv_font_t lv_font_FangZhengKaiTiJianTi_1_22;
void lv_font_FangZhengKaiTiJianTi_1_22_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\ui_res\\flash\\rle\\font\\35000006.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin(gui_get_res_path(GUI_RES_FANGZHENGKAITIJIANTI_1_22_TTF));
#endif
    if (fnt_font != NULL) {
        lv_font_FangZhengKaiTiJianTi_1_22 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\ui_res\\flash\\rle\\font\\35000006.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_FANGZHENGKAITIJIANTI_1_22_TTF));
#endif
    }
}

void init_gui_fonts()
{
    lv_font_montserratMedium_22_file();
    lv_font_simsun_22_file();
    lv_font_montserratMedium_32_file();
    lv_font_FangZhengKaiTiJianTi_1_32_file();
    lv_font_FangZhengKaiTiJianTi_1_20_file();
    lv_font_FangZhengKaiTiJianTi_1_18_file();
    lv_font_FangZhengKaiTiJianTi_1_22_file();
}