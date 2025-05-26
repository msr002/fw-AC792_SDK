#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE
#include "lvgl.h"
#if LV_USE_GUIBUILDER_SIMULATOR
#include <stdio.h>
#endif
#include "./gui_fonts.h"
#include "../common.h"

lv_font_t lv_font_FangZhengKaiTiJianTi_1_22;
void lv_font_FangZhengKaiTiJianTi_1_22_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\Application12\\sdk\\ui_res\\flash\\rle\\font\\35000000.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin(gui_get_res_path(GUI_RES_FANGZHENGKAITIJIANTI_1_22_TTF));
#endif
    if (fnt_font != NULL) {
        lv_font_FangZhengKaiTiJianTi_1_22 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\Application12\\sdk\\ui_res\\flash\\rle\\font\\35000000.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_FANGZHENGKAITIJIANTI_1_22_TTF));
#endif
    }
}
lv_font_t lv_font_FangZhengKaiTiJianTi_1_26;
void lv_font_FangZhengKaiTiJianTi_1_26_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\Application12\\sdk\\ui_res\\flash\\rle\\font\\35000001.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin(gui_get_res_path(GUI_RES_FANGZHENGKAITIJIANTI_1_26_TTF));
#endif
    if (fnt_font != NULL) {
        lv_font_FangZhengKaiTiJianTi_1_26 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\Application12\\sdk\\ui_res\\flash\\rle\\font\\35000001.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_FANGZHENGKAITIJIANTI_1_26_TTF));
#endif
    }
}
lv_font_t lv_font_FangZhengKaiTiJianTi_1_18;
void lv_font_FangZhengKaiTiJianTi_1_18_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\Application12\\sdk\\ui_res\\flash\\rle\\font\\35000002.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin(gui_get_res_path(GUI_RES_FANGZHENGKAITIJIANTI_1_18_TTF));
#endif
    if (fnt_font != NULL) {
        lv_font_FangZhengKaiTiJianTi_1_18 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\Application12\\sdk\\ui_res\\flash\\rle\\font\\35000002.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_FANGZHENGKAITIJIANTI_1_18_TTF));
#endif
    }
}
lv_font_t lv_font_montserratMedium_18;
void lv_font_montserratMedium_18_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\Application12\\sdk\\ui_res\\flash\\rle\\font\\35000003.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin(gui_get_res_path(GUI_RES_MONTSERRATMEDIUM_18_TTF));
#endif
    if (fnt_font != NULL) {
        lv_font_montserratMedium_18 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\Application12\\sdk\\ui_res\\flash\\rle\\font\\35000003.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_MONTSERRATMEDIUM_18_TTF));
#endif
    }
}
lv_font_t lv_font_FangZhengKaiTiJianTi_1_48;
void lv_font_FangZhengKaiTiJianTi_1_48_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\Application12\\sdk\\ui_res\\flash\\rle\\font\\35000004.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin(gui_get_res_path(GUI_RES_FANGZHENGKAITIJIANTI_1_48_TTF));
#endif
    if (fnt_font != NULL) {
        lv_font_FangZhengKaiTiJianTi_1_48 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\Application12\\sdk\\ui_res\\flash\\rle\\font\\35000004.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_FANGZHENGKAITIJIANTI_1_48_TTF));
#endif
    }
}
lv_font_t lv_font_montserratMedium_24;
void lv_font_montserratMedium_24_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\Application12\\sdk\\ui_res\\flash\\rle\\font\\35000005.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin(gui_get_res_path(GUI_RES_MONTSERRATMEDIUM_24_TTF));
#endif
    if (fnt_font != NULL) {
        lv_font_montserratMedium_24 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\Application12\\sdk\\ui_res\\flash\\rle\\font\\35000005.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_MONTSERRATMEDIUM_24_TTF));
#endif
    }
}
lv_font_t lv_font_montserratMedium_12;
void lv_font_montserratMedium_12_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\Application12\\sdk\\ui_res\\flash\\rle\\font\\35000006.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin(gui_get_res_path(GUI_RES_MONTSERRATMEDIUM_12_TTF));
#endif
    if (fnt_font != NULL) {
        lv_font_montserratMedium_12 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\Application12\\sdk\\ui_res\\flash\\rle\\font\\35000006.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_MONTSERRATMEDIUM_12_TTF));
#endif
    }
}
lv_font_t lv_font_montserratMedium_22;
void lv_font_montserratMedium_22_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\Application12\\sdk\\ui_res\\flash\\rle\\font\\35000007.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin(gui_get_res_path(GUI_RES_MONTSERRATMEDIUM_22_TTF));
#endif
    if (fnt_font != NULL) {
        lv_font_montserratMedium_22 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\Application12\\sdk\\ui_res\\flash\\rle\\font\\35000007.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_MONTSERRATMEDIUM_22_TTF));
#endif
    }
}
lv_font_t lv_font_FangZhengKaiTiJianTi_1_24;
void lv_font_FangZhengKaiTiJianTi_1_24_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\Application12\\sdk\\ui_res\\flash\\rle\\font\\35000008.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin(gui_get_res_path(GUI_RES_FANGZHENGKAITIJIANTI_1_24_TTF));
#endif
    if (fnt_font != NULL) {
        lv_font_FangZhengKaiTiJianTi_1_24 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\Application12\\sdk\\ui_res\\flash\\rle\\font\\35000008.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_FANGZHENGKAITIJIANTI_1_24_TTF));
#endif
    }
}
lv_font_t lv_font_FangZhengKaiTiJianTi_1_16;
void lv_font_FangZhengKaiTiJianTi_1_16_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\Application12\\sdk\\ui_res\\flash\\rle\\font\\35000009.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin(gui_get_res_path(GUI_RES_FANGZHENGKAITIJIANTI_1_16_TTF));
#endif
    if (fnt_font != NULL) {
        lv_font_FangZhengKaiTiJianTi_1_16 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\Application12\\sdk\\ui_res\\flash\\rle\\font\\35000009.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_FANGZHENGKAITIJIANTI_1_16_TTF));
#endif
    }
}
lv_font_t lv_font_montserratMedium_16;
void lv_font_montserratMedium_16_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\Application12\\sdk\\ui_res\\flash\\rle\\font\\3500000a.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin(gui_get_res_path(GUI_RES_MONTSERRATMEDIUM_16_TTF));
#endif
    if (fnt_font != NULL) {
        lv_font_montserratMedium_16 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\Application12\\sdk\\ui_res\\flash\\rle\\font\\3500000a.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_MONTSERRATMEDIUM_16_TTF));
#endif
    }
}
lv_font_t lv_font_montserratMedium_20;
void lv_font_montserratMedium_20_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\Application12\\sdk\\ui_res\\flash\\rle\\font\\3500000b.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin(gui_get_res_path(GUI_RES_MONTSERRATMEDIUM_20_TTF));
#endif
    if (fnt_font != NULL) {
        lv_font_montserratMedium_20 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\Application12\\sdk\\ui_res\\flash\\rle\\font\\3500000b.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_MONTSERRATMEDIUM_20_TTF));
#endif
    }
}

void init_gui_fonts()
{
    lv_font_FangZhengKaiTiJianTi_1_22_file();
    lv_font_FangZhengKaiTiJianTi_1_26_file();
    lv_font_FangZhengKaiTiJianTi_1_18_file();
    lv_font_montserratMedium_18_file();
    lv_font_FangZhengKaiTiJianTi_1_48_file();
    lv_font_montserratMedium_24_file();
    lv_font_montserratMedium_12_file();
    lv_font_montserratMedium_22_file();
    lv_font_FangZhengKaiTiJianTi_1_24_file();
    lv_font_FangZhengKaiTiJianTi_1_16_file();
    lv_font_montserratMedium_16_file();
    lv_font_montserratMedium_20_file();
}
#endif
