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
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000000.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin(gui_get_res_path(GUI_RES_FANGZHENGKAITIJIANTI_1_22_TTF));
#endif
    if (fnt_font != NULL) {
        lv_font_FangZhengKaiTiJianTi_1_22 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000000.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_FANGZHENGKAITIJIANTI_1_22_TTF));
#endif
    }
}
lv_font_t lv_font_FangZhengKaiTiJianTi_1_26;
void lv_font_FangZhengKaiTiJianTi_1_26_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000001.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin(gui_get_res_path(GUI_RES_FANGZHENGKAITIJIANTI_1_26_TTF));
#endif
    if (fnt_font != NULL) {
        lv_font_FangZhengKaiTiJianTi_1_26 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000001.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_FANGZHENGKAITIJIANTI_1_26_TTF));
#endif
    }
}
lv_font_t lv_font_FangZhengKaiTiJianTi_1_18;
void lv_font_FangZhengKaiTiJianTi_1_18_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000002.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin(gui_get_res_path(GUI_RES_FANGZHENGKAITIJIANTI_1_18_TTF));
#endif
    if (fnt_font != NULL) {
        lv_font_FangZhengKaiTiJianTi_1_18 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000002.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_FANGZHENGKAITIJIANTI_1_18_TTF));
#endif
    }
}
lv_font_t lv_font_montserratMedium_18;
void lv_font_montserratMedium_18_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000003.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin(gui_get_res_path(GUI_RES_MONTSERRATMEDIUM_18_TTF));
#endif
    if (fnt_font != NULL) {
        lv_font_montserratMedium_18 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000003.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_MONTSERRATMEDIUM_18_TTF));
#endif
    }
}
lv_font_t lv_font_FangZhengKaiTiJianTi_1_48;
void lv_font_FangZhengKaiTiJianTi_1_48_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000004.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin(gui_get_res_path(GUI_RES_FANGZHENGKAITIJIANTI_1_48_TTF));
#endif
    if (fnt_font != NULL) {
        lv_font_FangZhengKaiTiJianTi_1_48 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000004.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_FANGZHENGKAITIJIANTI_1_48_TTF));
#endif
    }
}
lv_font_t lv_font_montserratMedium_24;
void lv_font_montserratMedium_24_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000005.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin(gui_get_res_path(GUI_RES_MONTSERRATMEDIUM_24_TTF));
#endif
    if (fnt_font != NULL) {
        lv_font_montserratMedium_24 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000005.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_MONTSERRATMEDIUM_24_TTF));
#endif
    }
}
lv_font_t lv_font_montserratMedium_12;
void lv_font_montserratMedium_12_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000006.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin(gui_get_res_path(GUI_RES_MONTSERRATMEDIUM_12_TTF));
#endif
    if (fnt_font != NULL) {
        lv_font_montserratMedium_12 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000006.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_MONTSERRATMEDIUM_12_TTF));
#endif
    }
}
lv_font_t lv_font_montserratMedium_22;
void lv_font_montserratMedium_22_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000007.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin(gui_get_res_path(GUI_RES_MONTSERRATMEDIUM_22_TTF));
#endif
    if (fnt_font != NULL) {
        lv_font_montserratMedium_22 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000007.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_MONTSERRATMEDIUM_22_TTF));
#endif
    }
}
lv_font_t lv_font_FangZhengKaiTiJianTi_1_24;
void lv_font_FangZhengKaiTiJianTi_1_24_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000008.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin(gui_get_res_path(GUI_RES_FANGZHENGKAITIJIANTI_1_24_TTF));
#endif
    if (fnt_font != NULL) {
        lv_font_FangZhengKaiTiJianTi_1_24 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000008.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_FANGZHENGKAITIJIANTI_1_24_TTF));
#endif
    }
}
lv_font_t lv_font_FangZhengKaiTiJianTi_1_16;
void lv_font_FangZhengKaiTiJianTi_1_16_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000009.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin(gui_get_res_path(GUI_RES_FANGZHENGKAITIJIANTI_1_16_TTF));
#endif
    if (fnt_font != NULL) {
        lv_font_FangZhengKaiTiJianTi_1_16 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000009.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_FANGZHENGKAITIJIANTI_1_16_TTF));
#endif
    }
}
lv_font_t lv_font_montserratMedium_16;
void lv_font_montserratMedium_16_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\3500000a.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin(gui_get_res_path(GUI_RES_MONTSERRATMEDIUM_16_TTF));
#endif
    if (fnt_font != NULL) {
        lv_font_montserratMedium_16 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\3500000a.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_MONTSERRATMEDIUM_16_TTF));
#endif
    }
}
lv_font_t lv_font_montserratMedium_20;
void lv_font_montserratMedium_20_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\3500000b.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin(gui_get_res_path(GUI_RES_MONTSERRATMEDIUM_20_TTF));
#endif
    if (fnt_font != NULL) {
        lv_font_montserratMedium_20 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\3500000b.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_MONTSERRATMEDIUM_20_TTF));
#endif
    }
}
lv_font_t lv_font_simsun_22;
void lv_font_simsun_22_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\3500000c.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin(gui_get_res_path(GUI_RES_SIMSUN_22_WOFF));
#endif
    if (fnt_font != NULL) {
        lv_font_simsun_22 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\3500000c.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_SIMSUN_22_WOFF));
#endif
    }
}
lv_font_t lv_font_FangZhengKaiTiJianTi_1_20;
void lv_font_FangZhengKaiTiJianTi_1_20_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\3500000d.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin(gui_get_res_path(GUI_RES_FANGZHENGKAITIJIANTI_1_20_TTF));
#endif
    if (fnt_font != NULL) {
        lv_font_FangZhengKaiTiJianTi_1_20 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\3500000d.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_FANGZHENGKAITIJIANTI_1_20_TTF));
#endif
    }
}
lv_font_t lv_font_simsun_48;
void lv_font_simsun_48_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\3500000e.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin(gui_get_res_path(GUI_RES_SIMSUN_48_WOFF));
#endif
    if (fnt_font != NULL) {
        lv_font_simsun_48 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\3500000e.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_SIMSUN_48_WOFF));
#endif
    }
}
lv_font_t lv_font_fangsong_22;
void lv_font_fangsong_22_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\3500000f.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin(gui_get_res_path(GUI_RES_FANGSONG_22_TTF));
#endif
    if (fnt_font != NULL) {
        lv_font_fangsong_22 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\3500000f.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_FANGSONG_22_TTF));
#endif
    }
}
lv_font_t lv_font_fangsong_20;
void lv_font_fangsong_20_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000010.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin(gui_get_res_path(GUI_RES_FANGSONG_20_TTF));
#endif
    if (fnt_font != NULL) {
        lv_font_fangsong_20 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000010.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_FANGSONG_20_TTF));
#endif
    }
}
lv_font_t lv_font_fangsong_24;
void lv_font_fangsong_24_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000011.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin(gui_get_res_path(GUI_RES_FANGSONG_24_TTF));
#endif
    if (fnt_font != NULL) {
        lv_font_fangsong_24 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000011.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_FANGSONG_24_TTF));
#endif
    }
}
lv_font_t lv_font_fangsong_48;
void lv_font_fangsong_48_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000012.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin(gui_get_res_path(GUI_RES_FANGSONG_48_TTF));
#endif
    if (fnt_font != NULL) {
        lv_font_fangsong_48 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000012.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_FANGSONG_48_TTF));
#endif
    }
}
lv_font_t lv_font_timesnewromanpsmt_22;
void lv_font_timesnewromanpsmt_22_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000013.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin(gui_get_res_path(GUI_RES_TIMESNEWROMANPSMT_22_TTF));
#endif
    if (fnt_font != NULL) {
        lv_font_timesnewromanpsmt_22 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000013.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_TIMESNEWROMANPSMT_22_TTF));
#endif
    }
}
lv_font_t lv_font_timesnewromanpsmt_20;
void lv_font_timesnewromanpsmt_20_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000014.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin(gui_get_res_path(GUI_RES_TIMESNEWROMANPSMT_20_TTF));
#endif
    if (fnt_font != NULL) {
        lv_font_timesnewromanpsmt_20 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000014.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_TIMESNEWROMANPSMT_20_TTF));
#endif
    }
}
lv_font_t lv_font_timesnewromanpsmt_24;
void lv_font_timesnewromanpsmt_24_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000015.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin(gui_get_res_path(GUI_RES_TIMESNEWROMANPSMT_24_TTF));
#endif
    if (fnt_font != NULL) {
        lv_font_timesnewromanpsmt_24 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000015.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_TIMESNEWROMANPSMT_24_TTF));
#endif
    }
}
lv_font_t lv_font_timesnewromanpsmt_48;
void lv_font_timesnewromanpsmt_48_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000016.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin(gui_get_res_path(GUI_RES_TIMESNEWROMANPSMT_48_TTF));
#endif
    if (fnt_font != NULL) {
        lv_font_timesnewromanpsmt_48 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000016.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_TIMESNEWROMANPSMT_48_TTF));
#endif
    }
}
lv_font_t lv_font_timesnewromanpsmt_16;
void lv_font_timesnewromanpsmt_16_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000017.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin(gui_get_res_path(GUI_RES_TIMESNEWROMANPSMT_16_TTF));
#endif
    if (fnt_font != NULL) {
        lv_font_timesnewromanpsmt_16 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000017.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_TIMESNEWROMANPSMT_16_TTF));
#endif
    }
}
lv_font_t lv_font_segoeui_22;
void lv_font_segoeui_22_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000018.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin(gui_get_res_path(GUI_RES_SEGOEUI_22_TTF));
#endif
    if (fnt_font != NULL) {
        lv_font_segoeui_22 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000018.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_SEGOEUI_22_TTF));
#endif
    }
}
lv_font_t lv_font_segoeui_20;
void lv_font_segoeui_20_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000019.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin(gui_get_res_path(GUI_RES_SEGOEUI_20_TTF));
#endif
    if (fnt_font != NULL) {
        lv_font_segoeui_20 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000019.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_SEGOEUI_20_TTF));
#endif
    }
}
lv_font_t lv_font_segoeui_24;
void lv_font_segoeui_24_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\3500001a.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin(gui_get_res_path(GUI_RES_SEGOEUI_24_TTF));
#endif
    if (fnt_font != NULL) {
        lv_font_segoeui_24 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\3500001a.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_SEGOEUI_24_TTF));
#endif
    }
}
lv_font_t lv_font_segoeui_48;
void lv_font_segoeui_48_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\3500001b.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin(gui_get_res_path(GUI_RES_SEGOEUI_48_TTF));
#endif
    if (fnt_font != NULL) {
        lv_font_segoeui_48 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\3500001b.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_SEGOEUI_48_TTF));
#endif
    }
}
lv_font_t lv_font_arialmt_48;
void lv_font_arialmt_48_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\3500001c.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin(gui_get_res_path(GUI_RES_ARIALMT_48_TTF));
#endif
    if (fnt_font != NULL) {
        lv_font_arialmt_48 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\3500001c.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_ARIALMT_48_TTF));
#endif
    }
}
lv_font_t lv_font_leelawadeeui_22;
void lv_font_leelawadeeui_22_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\3500001d.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin(gui_get_res_path(GUI_RES_LEELAWADEEUI_22_TTF));
#endif
    if (fnt_font != NULL) {
        lv_font_leelawadeeui_22 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\3500001d.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_LEELAWADEEUI_22_TTF));
#endif
    }
}
lv_font_t lv_font_leelawadeeui_20;
void lv_font_leelawadeeui_20_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\3500001e.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin(gui_get_res_path(GUI_RES_LEELAWADEEUI_20_TTF));
#endif
    if (fnt_font != NULL) {
        lv_font_leelawadeeui_20 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\3500001e.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_LEELAWADEEUI_20_TTF));
#endif
    }
}
lv_font_t lv_font_leelawadeeui_24;
void lv_font_leelawadeeui_24_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\3500001f.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin(gui_get_res_path(GUI_RES_LEELAWADEEUI_24_TTF));
#endif
    if (fnt_font != NULL) {
        lv_font_leelawadeeui_24 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\3500001f.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_LEELAWADEEUI_24_TTF));
#endif
    }
}
lv_font_t lv_font_tahoma_20;
void lv_font_tahoma_20_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000020.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin(gui_get_res_path(GUI_RES_TAHOMA_20_TTF));
#endif
    if (fnt_font != NULL) {
        lv_font_tahoma_20 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000020.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_TAHOMA_20_TTF));
#endif
    }
}
lv_font_t lv_font_tahoma_22;
void lv_font_tahoma_22_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000021.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin(gui_get_res_path(GUI_RES_TAHOMA_22_TTF));
#endif
    if (fnt_font != NULL) {
        lv_font_tahoma_22 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000021.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_TAHOMA_22_TTF));
#endif
    }
}
lv_font_t lv_font_leelawadeeui_48;
void lv_font_leelawadeeui_48_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000022.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin(gui_get_res_path(GUI_RES_LEELAWADEEUI_48_TTF));
#endif
    if (fnt_font != NULL) {
        lv_font_leelawadeeui_48 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000022.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_LEELAWADEEUI_48_TTF));
#endif
    }
}
lv_font_t lv_font_tahoma_48;
void lv_font_tahoma_48_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000023.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin(gui_get_res_path(GUI_RES_TAHOMA_48_TTF));
#endif
    if (fnt_font != NULL) {
        lv_font_tahoma_48 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000023.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_TAHOMA_48_TTF));
#endif
    }
}
lv_font_t lv_font_malgungothic_22;
void lv_font_malgungothic_22_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000024.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin(gui_get_res_path(GUI_RES_MALGUNGOTHIC_22_TTF));
#endif
    if (fnt_font != NULL) {
        lv_font_malgungothic_22 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000024.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_MALGUNGOTHIC_22_TTF));
#endif
    }
}
lv_font_t lv_font_malgungothic_20;
void lv_font_malgungothic_20_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000025.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin(gui_get_res_path(GUI_RES_MALGUNGOTHIC_20_TTF));
#endif
    if (fnt_font != NULL) {
        lv_font_malgungothic_20 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000025.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_MALGUNGOTHIC_20_TTF));
#endif
    }
}
lv_font_t lv_font_malgungothic_24;
void lv_font_malgungothic_24_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000026.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin(gui_get_res_path(GUI_RES_MALGUNGOTHIC_24_TTF));
#endif
    if (fnt_font != NULL) {
        lv_font_malgungothic_24 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000026.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_MALGUNGOTHIC_24_TTF));
#endif
    }
}
lv_font_t lv_font_malgungothic_48;
void lv_font_malgungothic_48_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000027.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin(gui_get_res_path(GUI_RES_MALGUNGOTHIC_48_TTF));
#endif
    if (fnt_font != NULL) {
        lv_font_malgungothic_48 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000027.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_MALGUNGOTHIC_48_TTF));
#endif
    }
}
lv_font_t lv_font_ms_gothic_22;
void lv_font_ms_gothic_22_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000028.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin(gui_get_res_path(GUI_RES_MS_GOTHIC_22_TTF));
#endif
    if (fnt_font != NULL) {
        lv_font_ms_gothic_22 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000028.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_MS_GOTHIC_22_TTF));
#endif
    }
}
lv_font_t lv_font_calibri_22;
void lv_font_calibri_22_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000029.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin(gui_get_res_path(GUI_RES_CALIBRI_22_TTF));
#endif
    if (fnt_font != NULL) {
        lv_font_calibri_22 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\35000029.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_CALIBRI_22_TTF));
#endif
    }
}
lv_font_t lv_font_calibri_20;
void lv_font_calibri_20_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\3500002a.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin(gui_get_res_path(GUI_RES_CALIBRI_20_TTF));
#endif
    if (fnt_font != NULL) {
        lv_font_calibri_20 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\3500002a.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_CALIBRI_20_TTF));
#endif
    }
}
lv_font_t lv_font_calibri_24;
void lv_font_calibri_24_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\3500002b.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin(gui_get_res_path(GUI_RES_CALIBRI_24_TTF));
#endif
    if (fnt_font != NULL) {
        lv_font_calibri_24 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\3500002b.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_CALIBRI_24_TTF));
#endif
    }
}
lv_font_t lv_font_calibri_48;
void lv_font_calibri_48_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\3500002c.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin(gui_get_res_path(GUI_RES_CALIBRI_48_TTF));
#endif
    if (fnt_font != NULL) {
        lv_font_calibri_48 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\dvr_ly_800x480\\sdk\\ui_res\\flash\\rle\\font\\3500002c.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", gui_get_res_path(GUI_RES_CALIBRI_48_TTF));
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
    lv_font_simsun_22_file();
    lv_font_FangZhengKaiTiJianTi_1_20_file();
    lv_font_simsun_48_file();
    lv_font_fangsong_22_file();
    lv_font_fangsong_20_file();
    lv_font_fangsong_24_file();
    lv_font_fangsong_48_file();
    lv_font_timesnewromanpsmt_22_file();
    lv_font_timesnewromanpsmt_20_file();
    lv_font_timesnewromanpsmt_24_file();
    lv_font_timesnewromanpsmt_48_file();
    lv_font_timesnewromanpsmt_16_file();
    lv_font_segoeui_22_file();
    lv_font_segoeui_20_file();
    lv_font_segoeui_24_file();
    lv_font_segoeui_48_file();
    lv_font_arialmt_48_file();
    lv_font_leelawadeeui_22_file();
    lv_font_leelawadeeui_20_file();
    lv_font_leelawadeeui_24_file();
    lv_font_tahoma_20_file();
    lv_font_tahoma_22_file();
    lv_font_leelawadeeui_48_file();
    lv_font_tahoma_48_file();
    lv_font_malgungothic_22_file();
    lv_font_malgungothic_20_file();
    lv_font_malgungothic_24_file();
    lv_font_malgungothic_48_file();
    lv_font_ms_gothic_22_file();
    lv_font_calibri_22_file();
    lv_font_calibri_20_file();
    lv_font_calibri_24_file();
    lv_font_calibri_48_file();
}
#endif
