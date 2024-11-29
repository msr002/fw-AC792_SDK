#include "app_config.h"
#ifdef CONFIG_UI_STYLE_JL_ENABLE
#include "lvgl.h"
#include <stdio.h>
#include "./gui_fonts.h"

lv_font_t lv_font_montserratMedium_12;
void lv_font_montserratMedium_12_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\rle\\font\\10000000.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin("mnt/sdfile/EXT_RESERVED/uipackres/ui/10000000.rle");
#endif
    if (fnt_font != NULL) {
        lv_font_montserratMedium_12 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\rle\\font\\10000000.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "mnt/sdfile/EXT_RESERVED/uipackres/ui/10000000.rle");
#endif
    }
}
lv_font_t lv_font_FangZhengKaiTiJianTi_1_28;
void lv_font_FangZhengKaiTiJianTi_1_28_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\rle\\font\\10000001.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin("mnt/sdfile/EXT_RESERVED/uipackres/ui/10000001.rle");
#endif
    if (fnt_font != NULL) {
        lv_font_FangZhengKaiTiJianTi_1_28 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\rle\\font\\10000001.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "mnt/sdfile/EXT_RESERVED/uipackres/ui/10000001.rle");
#endif
    }
}
lv_font_t lv_font_FangZhengKaiTiJianTi_1_19;
void lv_font_FangZhengKaiTiJianTi_1_19_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\rle\\font\\10000002.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin("mnt/sdfile/EXT_RESERVED/uipackres/ui/10000002.rle");
#endif
    if (fnt_font != NULL) {
        lv_font_FangZhengKaiTiJianTi_1_19 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\rle\\font\\10000002.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "mnt/sdfile/EXT_RESERVED/uipackres/ui/10000002.rle");
#endif
    }
}
lv_font_t lv_font_FangZhengKaiTiJianTi_1_24;
void lv_font_FangZhengKaiTiJianTi_1_24_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\rle\\font\\10000003.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin("mnt/sdfile/EXT_RESERVED/uipackres/ui/10000003.rle");
#endif
    if (fnt_font != NULL) {
        lv_font_FangZhengKaiTiJianTi_1_24 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\rle\\font\\10000003.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "mnt/sdfile/EXT_RESERVED/uipackres/ui/10000003.rle");
#endif
    }
}
lv_font_t lv_font_FangZhengKaiTiJianTi_1_32;
void lv_font_FangZhengKaiTiJianTi_1_32_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\rle\\font\\10000004.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin("mnt/sdfile/EXT_RESERVED/uipackres/ui/10000004.rle");
#endif
    if (fnt_font != NULL) {
        lv_font_FangZhengKaiTiJianTi_1_32 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\rle\\font\\10000004.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "mnt/sdfile/EXT_RESERVED/uipackres/ui/10000004.rle");
#endif
    }
}
lv_font_t lv_font_FangZhengKaiTiJianTi_1_16;
void lv_font_FangZhengKaiTiJianTi_1_16_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\rle\\font\\10000005.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin("mnt/sdfile/EXT_RESERVED/uipackres/ui/10000005.rle");
#endif
    if (fnt_font != NULL) {
        lv_font_FangZhengKaiTiJianTi_1_16 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\rle\\font\\10000005.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "mnt/sdfile/EXT_RESERVED/uipackres/ui/10000005.rle");
#endif
    }
}
lv_font_t lv_font_montserratMedium_18;
void lv_font_montserratMedium_18_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\rle\\font\\10000006.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin("mnt/sdfile/EXT_RESERVED/uipackres/ui/10000006.rle");
#endif
    if (fnt_font != NULL) {
        lv_font_montserratMedium_18 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\rle\\font\\10000006.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "mnt/sdfile/EXT_RESERVED/uipackres/ui/10000006.rle");
#endif
    }
}
lv_font_t lv_font_montserratMedium_20;
void lv_font_montserratMedium_20_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\rle\\font\\10000007.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin("mnt/sdfile/EXT_RESERVED/uipackres/ui/10000007.rle");
#endif
    if (fnt_font != NULL) {
        lv_font_montserratMedium_20 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\rle\\font\\10000007.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "mnt/sdfile/EXT_RESERVED/uipackres/ui/10000007.rle");
#endif
    }
}
lv_font_t lv_font_FangZhengKaiTiJianTi_1_54;
void lv_font_FangZhengKaiTiJianTi_1_54_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\rle\\font\\10000008.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin("mnt/sdfile/EXT_RESERVED/uipackres/ui/10000008.rle");
#endif
    if (fnt_font != NULL) {
        lv_font_FangZhengKaiTiJianTi_1_54 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\rle\\font\\10000008.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "mnt/sdfile/EXT_RESERVED/uipackres/ui/10000008.rle");
#endif
    }
}
lv_font_t lv_font_FangZhengKaiTiJianTi_1_48;
void lv_font_FangZhengKaiTiJianTi_1_48_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\rle\\font\\10000009.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin("mnt/sdfile/EXT_RESERVED/uipackres/ui/10000009.rle");
#endif
    if (fnt_font != NULL) {
        lv_font_FangZhengKaiTiJianTi_1_48 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\rle\\font\\10000009.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "mnt/sdfile/EXT_RESERVED/uipackres/ui/10000009.rle");
#endif
    }
}
lv_font_t lv_font_FangZhengKaiTiJianTi_1_20;
void lv_font_FangZhengKaiTiJianTi_1_20_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\rle\\font\\1000000a.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin("mnt/sdfile/EXT_RESERVED/uipackres/ui/1000000a.rle");
#endif
    if (fnt_font != NULL) {
        lv_font_FangZhengKaiTiJianTi_1_20 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\rle\\font\\1000000a.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "mnt/sdfile/EXT_RESERVED/uipackres/ui/1000000a.rle");
#endif
    }
}
lv_font_t lv_font_montserratMedium_24;
void lv_font_montserratMedium_24_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\rle\\font\\1000000b.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin("mnt/sdfile/EXT_RESERVED/uipackres/ui/1000000b.rle");
#endif
    if (fnt_font != NULL) {
        lv_font_montserratMedium_24 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\rle\\font\\1000000b.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "mnt/sdfile/EXT_RESERVED/uipackres/ui/1000000b.rle");
#endif
    }
}
lv_font_t lv_font_montserratMedium_48;
void lv_font_montserratMedium_48_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\rle\\font\\1000000c.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin("mnt/sdfile/EXT_RESERVED/uipackres/ui/1000000c.rle");
#endif
    if (fnt_font != NULL) {
        lv_font_montserratMedium_48 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\rle\\font\\1000000c.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "mnt/sdfile/EXT_RESERVED/uipackres/ui/1000000c.rle");
#endif
    }
}
lv_font_t lv_font_montserratMedium_49;
void lv_font_montserratMedium_49_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\rle\\font\\1000000d.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin("mnt/sdfile/EXT_RESERVED/uipackres/ui/1000000d.rle");
#endif
    if (fnt_font != NULL) {
        lv_font_montserratMedium_49 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\rle\\font\\1000000d.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "mnt/sdfile/EXT_RESERVED/uipackres/ui/1000000d.rle");
#endif
    }
}
lv_font_t lv_font_montserratMedium_32;
void lv_font_montserratMedium_32_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\rle\\font\\1000000e.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin("mnt/sdfile/EXT_RESERVED/uipackres/ui/1000000e.rle");
#endif
    if (fnt_font != NULL) {
        lv_font_montserratMedium_32 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\rle\\font\\1000000e.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "mnt/sdfile/EXT_RESERVED/uipackres/ui/1000000e.rle");
#endif
    }
}
lv_font_t lv_font_FangZhengKaiTiJianTi_1_14;
void lv_font_FangZhengKaiTiJianTi_1_14_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\rle\\font\\1000000f.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin("mnt/sdfile/EXT_RESERVED/uipackres/ui/1000000f.rle");
#endif
    if (fnt_font != NULL) {
        lv_font_FangZhengKaiTiJianTi_1_14 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\rle\\font\\1000000f.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "mnt/sdfile/EXT_RESERVED/uipackres/ui/1000000f.rle");
#endif
    }
}
lv_font_t lv_font_montserratMedium_160;
void lv_font_montserratMedium_160_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\rle\\font\\10000010.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin("mnt/sdfile/EXT_RESERVED/uipackres/ui/10000010.rle");
#endif
    if (fnt_font != NULL) {
        lv_font_montserratMedium_160 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\rle\\font\\10000010.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "mnt/sdfile/EXT_RESERVED/uipackres/ui/10000010.rle");
#endif
    }
}
lv_font_t lv_font_FangZhengKaiTiJianTi_1_26;
void lv_font_FangZhengKaiTiJianTi_1_26_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\rle\\font\\10000011.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin("mnt/sdfile/EXT_RESERVED/uipackres/ui/10000011.rle");
#endif
    if (fnt_font != NULL) {
        lv_font_FangZhengKaiTiJianTi_1_26 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\rle\\font\\10000011.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "mnt/sdfile/EXT_RESERVED/uipackres/ui/10000011.rle");
#endif
    }
}
lv_font_t lv_font_montserratMedium_22;
void lv_font_montserratMedium_22_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\rle\\font\\10000012.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin("mnt/sdfile/EXT_RESERVED/uipackres/ui/10000012.rle");
#endif
    if (fnt_font != NULL) {
        lv_font_montserratMedium_22 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\rle\\font\\10000012.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "mnt/sdfile/EXT_RESERVED/uipackres/ui/10000012.rle");
#endif
    }
}
lv_font_t lv_font_montserratMedium_16;
void lv_font_montserratMedium_16_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\rle\\font\\10000013.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin("mnt/sdfile/EXT_RESERVED/uipackres/ui/10000013.rle");
#endif
    if (fnt_font != NULL) {
        lv_font_montserratMedium_16 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\rle\\font\\10000013.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "mnt/sdfile/EXT_RESERVED/uipackres/ui/10000013.rle");
#endif
    }
}
lv_font_t lv_font_FangZhengKaiTiJianTi_1_22;
void lv_font_FangZhengKaiTiJianTi_1_22_file()
{
#if LV_USE_GUIBUILDER_SIMULATOR
    lv_font_t *fnt_font = lv_font_load_bin("A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\rle\\font\\10000014.rle");
#else
    lv_font_t *fnt_font = lv_font_load_bin("mnt/sdfile/EXT_RESERVED/uipackres/ui/10000014.rle");
#endif
    if (fnt_font != NULL) {
        lv_font_FangZhengKaiTiJianTi_1_22 = *fnt_font;
    } else {
#if LV_USE_GUIBUILDER_SIMULATOR
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\rle\\font\\10000014.rle");
#else
        LV_LOG_ERROR("Load Fnt Font Failed %s\n", "mnt/sdfile/EXT_RESERVED/uipackres/ui/10000014.rle");
#endif
    }
}

void init_gui_fonts()
{
    lv_font_montserratMedium_12_file();
    lv_font_FangZhengKaiTiJianTi_1_28_file();
    lv_font_FangZhengKaiTiJianTi_1_19_file();
    lv_font_FangZhengKaiTiJianTi_1_24_file();
    lv_font_FangZhengKaiTiJianTi_1_32_file();
    lv_font_FangZhengKaiTiJianTi_1_16_file();
    lv_font_montserratMedium_18_file();
    lv_font_montserratMedium_20_file();
    lv_font_FangZhengKaiTiJianTi_1_54_file();
    lv_font_FangZhengKaiTiJianTi_1_48_file();
    lv_font_FangZhengKaiTiJianTi_1_20_file();
    lv_font_montserratMedium_24_file();
    lv_font_montserratMedium_48_file();
    lv_font_montserratMedium_49_file();
    lv_font_montserratMedium_32_file();
    lv_font_FangZhengKaiTiJianTi_1_14_file();
    lv_font_montserratMedium_160_file();
    lv_font_FangZhengKaiTiJianTi_1_26_file();
    lv_font_montserratMedium_22_file();
    lv_font_montserratMedium_16_file();
    lv_font_FangZhengKaiTiJianTi_1_22_file();
}
#endif
