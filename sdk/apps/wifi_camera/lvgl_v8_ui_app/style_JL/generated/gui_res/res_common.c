#include "app_config.h"
#ifdef CONFIG_UI_STYLE_JL_ENABLE
/*Generate Code, Do NOT Edit!*/
#include "./res_common.h"
#include <stdlib.h>
#include <string.h>
#if LV_USE_GUIBUILDER_SIMULATOR
#include <stdio.h>
#endif

#if !LV_USE_GUIBUILDER_SIMULATOR
#define max(a, b) ((a) > (b) ? (a) : (b))
char sd_dir[] = "S:/";
char flash_dir[] = "mnt/sdfile/EXT_RESERVED/uipackres/ui/";
char path_buf[max(sizeof(sd_dir), sizeof(flash_dir)) + 20];
#endif

char *gui_get_res_path(int32_t id)
{
#if LV_USE_GUIBUILDER_SIMULATOR
    switch (id) {
    case GUI_RES_MONTSERRATMEDIUM_12_TTF:
        return "E:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\rle\\font\\10000000.rle";
    case GUI_RES_FANGZHENGKAITIJIANTI_1_28_TTF:
        return "E:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\rle\\font\\10000001.rle";
    case GUI_RES_FANGZHENGKAITIJIANTI_1_19_TTF:
        return "E:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\rle\\font\\10000002.rle";
    case GUI_RES_FANGZHENGKAITIJIANTI_1_24_TTF:
        return "E:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\rle\\font\\10000003.rle";
    case GUI_RES_FANGZHENGKAITIJIANTI_1_32_TTF:
        return "E:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\rle\\font\\10000004.rle";
    case GUI_RES_FANGZHENGKAITIJIANTI_1_16_TTF:
        return "E:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\rle\\font\\10000005.rle";
    case GUI_RES_MONTSERRATMEDIUM_18_TTF:
        return "E:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\rle\\font\\10000006.rle";
    case GUI_RES_MONTSERRATMEDIUM_20_TTF:
        return "E:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\rle\\font\\10000007.rle";
    case GUI_RES_FANGZHENGKAITIJIANTI_1_54_TTF:
        return "E:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\rle\\font\\10000008.rle";
    case GUI_RES_FANGZHENGKAITIJIANTI_1_48_TTF:
        return "E:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\rle\\font\\10000009.rle";
    case GUI_RES_FANGZHENGKAITIJIANTI_1_20_TTF:
        return "E:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\rle\\font\\1000000a.rle";
    case GUI_RES_MONTSERRATMEDIUM_24_TTF:
        return "E:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\rle\\font\\1000000b.rle";
    case GUI_RES_MONTSERRATMEDIUM_48_TTF:
        return "E:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\rle\\font\\1000000c.rle";
    case GUI_RES_MONTSERRATMEDIUM_49_TTF:
        return "E:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\rle\\font\\1000000d.rle";
    case GUI_RES_MONTSERRATMEDIUM_32_TTF:
        return "E:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\rle\\font\\1000000e.rle";
    case GUI_RES_FANGZHENGKAITIJIANTI_1_14_TTF:
        return "E:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\rle\\font\\1000000f.rle";
    case GUI_RES_MONTSERRATMEDIUM_160_TTF:
        return "E:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\rle\\font\\10000010.rle";
    case GUI_RES_FANGZHENGKAITIJIANTI_1_26_TTF:
        return "E:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\rle\\font\\10000011.rle";
    case GUI_RES_MONTSERRATMEDIUM_22_TTF:
        return "E:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\rle\\font\\10000012.rle";
    case GUI_RES_MONTSERRATMEDIUM_16_TTF:
        return "E:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\rle\\font\\10000013.rle";
    case GUI_RES_FANGZHENGKAITIJIANTI_1_22_TTF:
        return "E:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\rle\\font\\10000014.rle";
    case GUI_RES_S_PC_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\55000000.zip";
    case GUI_RES_S_MASS_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\55000001.zip";
    case GUI_RES_VIDEO_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\55000002.zip";
    case GUI_RES_VIDEO_ON_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\55000003.zip";
    case GUI_RES_MASS_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\55000004.zip";
    case GUI_RES_MASS_ON_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\55000005.zip";
    case GUI_RES_PCCAM_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\55000006.zip";
    case GUI_RES_PCCAM_ON_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\55000007.zip";
    case GUI_RES_VIDEO_BUTTO_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\55000008.zip";
    case GUI_RES_VIDEO_BUTTO_FLASH1_ON_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\55000009.zip";
    case GUI_RES_VIDEO_BUTTO_FLASH2_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\5500000a.zip";
    case GUI_RES_VIDEO_BUTTO_FLASH2_ON_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\5500000b.zip";
    case GUI_RES_CYCLIC_VIDEO_CLOSE_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\5500000c.zip";
    case GUI_RES_GRAVITY_SENSOR_LOW_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\5500000d.zip";
    case GUI_RES_SOUND_CLOSE_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\5500000e.zip";
    case GUI_RES_STOPPING_MONITOR_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\5500000f.zip";
    case GUI_RES_CHECK_SPORT_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\55000010.zip";
    case GUI_RES_SD_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\55000011.zip";
    case GUI_RES_LOCK_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\55000012.zip";
    case GUI_RES_INTERVAL_VIDEO_CLOSE_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\55000013.zip";
    case GUI_RES_DISCONNECT_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\55000014.zip";
    case GUI_RES_FULL_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\55000015.zip";
    case GUI_RES_SETTING_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\55000016.zip";
    case GUI_RES_CAMERA_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\55000017.zip";
    case GUI_RES_HOME_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\55000018.zip";
    case GUI_RES_BTN_LOCK_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\55000019.zip";
    case GUI_RES_BTN_LOCK_ON_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\5500001a.zip";
    case GUI_RES_SWITCH_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\5500001b.zip";
    case GUI_RES_SWITCH_ON_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\5500001c.zip";
    case GUI_RES_RESOLUTION_RATIO_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\5500001d.zip";
    case GUI_RES_DOUBLE_VIDEO_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\5500001e.zip";
    case GUI_RES_CYCLIC_VIDEO_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\5500001f.zip";
    case GUI_RES_INTERVAL_VIDEO_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\55000020.zip";
    case GUI_RES_HDR_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\55000021.zip";
    case GUI_RES_EXPOSURE_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\55000022.zip";
    case GUI_RES_CHECK_SPORT_1_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\55000023.zip";
    case GUI_RES_DATE_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\55000024.zip";
    case GUI_RES_GRAVITY_SENSOR_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\55000025.zip";
    case GUI_RES_SOUND_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\55000026.zip";
    case GUI_RES_STOPPING_MONITOR_1_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\55000027.zip";
    case GUI_RES_CAR_NUM_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\55000028.zip";
    case GUI_RES_HEADLIGHT_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\55000029.zip";
    case GUI_RES_VIDEO_1_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\5500002a.zip";
    case GUI_RES_VIDEO__ON_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\5500002b.zip";
    case GUI_RES_FILE_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\5500002c.zip";
    case GUI_RES_FILE_ON_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\5500002d.zip";
    case GUI_RES_SETTING_1_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\5500002e.zip";
    case GUI_RES_SETTING_ON_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\5500002f.zip";
    case GUI_RES_POP_UP_WINDOW_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\55000030.zip";
    case GUI_RES_FLIG_ON_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\55000031.zip";
    case GUI_RES_ASTERN_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\55000032.zip";
    case GUI_RES_LCD_OFF_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\55000033.zip";
    case GUI_RES_AUTO_OFF_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\55000034.zip";
    case GUI_RES_FREQUENCY_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\55000035.zip";
    case GUI_RES_VOICE_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\55000036.zip";
    case GUI_RES_LANGUAGES_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\55000037.zip";
    case GUI_RES_SOFTWARE_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\55000038.zip";
    case GUI_RES_CAR_NUM_1_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\55000039.zip";
    case GUI_RES_LANE_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\5500003a.zip";
    case GUI_RES_FLIG_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\5500003b.zip";
    case GUI_RES_FORMAT_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\5500003c.zip";
    case GUI_RES_RESET_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\5500003d.zip";
    case GUI_RES_DATE_1_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\5500003e.zip";
    case GUI_RES_VIDEO_2_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\5500003f.zip";
    case GUI_RES_FILES_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\55000040.zip";
    case GUI_RES_PHOTO_BUTTON_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\55000041.zip";
    case GUI_RES_PHOTO_BUTTON_ON_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\55000042.zip";
    case GUI_RES_TIMING_PHOTO_2_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\55000043.zip";
    case GUI_RES_CONTINUOUS_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\55000044.zip";
    case GUI_RES_HAND_SHAKE_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\55000045.zip";
    case GUI_RES_VIDEO_3_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\55000046.zip";
    case GUI_RES_TIMING_PHOTO_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\55000047.zip";
    case GUI_RES_CONTINUOUS_PHOTO_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\55000048.zip";
    case GUI_RES_PHOTO_QUALITY_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\55000049.zip";
    case GUI_RES_ACUITY_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\5500004a.zip";
    case GUI_RES_AWB_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\5500004b.zip";
    case GUI_RES_COLOR_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\5500004c.zip";
    case GUI_RES_ISO_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\5500004d.zip";
    case GUI_RES_HAND_SHAKE_1_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\5500004e.zip";
    case GUI_RES_QUICK_SCAN_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\5500004f.zip";
    case GUI_RES_HIGH_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\55000050.zip";
    case GUI_RES_AWB_1_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\55000051.zip";
    case GUI_RES_VIDEO_PLAY_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\55000052.zip";
    case GUI_RES_VIDEO_PAUSE_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\55000053.zip";
    case GUI_RES_VOLUMELOUDER_SOLID_1_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\55000054.zip";
    case GUI_RES_VOLUMEMUTE_SOLID_1_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\55000055.zip";
    case GUI_RES_PHOTO_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\55000056.zip";
    case GUI_RES_PHOTO_ON_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\55000057.zip";
    case GUI_RES_RETURN_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\55000058.zip";
    case GUI_RES_RETURN_ON_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\55000059.zip";
    case GUI_RES_SKIP_PREVIOUS_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\5500005a.zip";
    case GUI_RES_SKIP_NEXT_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\5500005b.zip";
    case GUI_RES_UP_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\5500005c.zip";
    case GUI_RES_DOWN_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\5500005d.zip";
    case GUI_RES_EDIT_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\5500005e.zip";
    case GUI_RES_EDITOR_ON_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\5500005f.zip";
    case GUI_RES_LOCK_1_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\55000060.zip";
    case GUI_RES_LOCK_ON_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\55000061.zip";
    case GUI_RES_HOME_1_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\55000062.zip";
    case GUI_RES_HOME_ON_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\55000063.zip";
    case GUI_RES_DELETE_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\55000064.zip";
    case GUI_RES_DELETE_ON_PNG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\55000065.zip";
    case RES_0:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d5000000.zip";
    case RES_1:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d5000001.zip";
    case RES_2:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d5000002.zip";
    case RES_3:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d5000003.zip";
    case RES_CHARGING:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d5000004.zip";
    case RES_FULL:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d5000005.zip";
    case RES_CYCLIC_VIDEO_3:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d5000006.zip";
    case RES_CYCLIC_VIDEO_10:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d5000007.zip";
    case RES_CYCLIC_VIDEO_CLOSE:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d5000008.zip";
    case RES_GRAVITY_SENSOR_LOW:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d5000009.zip";
    case RES_GRAVITY_SENSOR_MIDLLER:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d500000a.zip";
    case RES_GRAVITY_SENSOR_HIGH:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d500000b.zip";
    case RES_INTERVAL_VIDEO_CLOSE:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d500000c.zip";
    case RES_INTERVAL_VIDEO_500:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d500000d.zip";
    case RES_INTERVAL_VIDEO_200:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d500000e.zip";
    case RES_INTERVAL_VIDEO_100:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d500000f.zip";
    case RES_SD:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d5000010.zip";
    case RES_SD_CLOSE:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d5000011.zip";
    case RES_SOUND:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d5000012.zip";
    case RES_SOUND_CLOSE:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d5000013.zip";
    case RES_EXPOSURE:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d5000014.zip";
    case RES_DOUBLE_VIDEO:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d5000015.zip";
    case RES_DATE:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d5000016.zip";
    case RES_CYCLIC_VIDEO:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d5000017.zip";
    case RES_CHECK_SPORT:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d5000018.zip";
    case RES_CAR_NUM:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d5000019.zip";
    case RES_GRAVITY_SENSOR:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d500001a.zip";
    case RES_HDR:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d500001b.zip";
    case RES_INTERVAL_VIDEO:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d500001c.zip";
    case RES_RESOLUTION_RATIO:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d500001d.zip";
    case RES_SOUND_1:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d500001e.zip";
    case RES_STOPPING_MONITOR:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d500001f.zip";
    case RES_AUTO_OFF:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d5000020.zip";
    case RES_CAR_NUM_1:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d5000021.zip";
    case RES_FLIG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d5000022.zip";
    case RES_FORMAT:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d5000023.zip";
    case RES_FREQUENCY:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d5000024.zip";
    case RES_LANE:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d5000025.zip";
    case RES_LANGUAGES:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d5000026.zip";
    case RES_LCD_OFF:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d5000027.zip";
    case RES_RESET:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d5000028.zip";
    case RES_VERSION:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d5000029.zip";
    case RES_VOICE:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d500002a.zip";
    case RES_DATE_1:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d500002b.zip";
    case RES_AWB:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d500002c.zip";
    case RES_AWB_FLUORESCENT_LAMP:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d500002d.zip";
    case RES_AWB_OSRAM_LAMP:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d500002e.zip";
    case RES_AWB_SUN_CLOUDY:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d500002f.zip";
    case RES_AWB_SUN_LIGHT:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d5000030.zip";
    case RES_HIGH:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d5000031.zip";
    case RES_LOW:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d5000032.zip";
    case RES_MIDDLE:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d5000033.zip";
    case RES_TIMING_PHOTO_2:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d5000034.zip";
    case RES_TIMING_PHOTO_5:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d5000035.zip";
    case RES_TIMING_PHOTO_10:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d5000036.zip";
    case RES_FILE_DIR:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d5000037.zip";
    case RES_DELETE:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d5000038.zip";
    case RES_DELETE_ON:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d5000039.zip";
    case RES_EDIT:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d500003a.zip";
    case RES_EDITOR_ON:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d500003b.zip";
    case RES_HOME:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d500003c.zip";
    case RES_HOME_ON:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d500003d.zip";
    case RES_LOCK:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d500003e.zip";
    case RES_LOCK_ON:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d500003f.zip";
    case RES_PHOTO:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d5000040.zip";
    case RES_PHOTO_ON:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d5000041.zip";
    case RES_RETURN:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d5000042.zip";
    case RES_RETURN_ON:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d5000043.zip";
    case RES_SELETE:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d5000044.zip";
    case RES_UNLOCK:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d5000045.zip";
    case RES_UNLOCK_ON:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d5000046.zip";
    case RES_VIDEO:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d5000047.zip";
    case RES_VOLUMELOUDER_SOLID_1:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d5000048.zip";
    case RES_VIDEO_PAUSE:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d5000049.zip";
    case RES_SKIP_NEXT:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d500004a.zip";
    case RES_SKIP_PREVIOUS:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d500004b.zip";
    case RES_PLAY:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d500004c.zip";
    case RES_VIDEO_PLAY:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d500004d.zip";
    case RES_VOLUMEMUTE_SOLID_1:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d500004e.zip";
    case RES_SOFTWARE:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d500004f.zip";
    case RES_CYCLIC_VIDEO_1:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d5000050.zip";
    case RES_LOCK_FLAG:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d5000051.zip";
    case RES_CONNECTED:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d5000052.zip";
    case RES_DISCONNECT:
        return "A:\\1111\\ac792\\ui_prj\\dvr_800x480\\sdk\\ui_res\\zip\\image\\d5000053.zip";
    default:
        return NULL;
    }
#else
    memset(path_buf, 0, sizeof(path_buf));
    if (id >= 0x10000000 && id < 0x20000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.rle", flash_dir, id);
    } else if (id >= 0x20000000 && id < 0x30000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.json", flash_dir, id);
    } else if (id >= 0x30000000 && id < 0x31000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.mp4", flash_dir, id);
    } else if (id >= 0x31000000 && id < 0x32000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.avi", flash_dir, id);
    } else if (id >= 0x32000000 && id < 0x33000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.bin", flash_dir, id);
    } else if (id >= 0x33000000 && id < 0x34000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.rle", flash_dir, id);
    } else if (id >= 0x40000000 && id < 0x50000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.gif", flash_dir, id);
    } else if (id >= 0x50000000 && id < 0x51000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.png", flash_dir, id);
    } else if (id >= 0x51000000 && id < 0x52000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.jpg", flash_dir, id);
    } else if (id >= 0x52000000 && id < 0x53000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.jpeg", flash_dir, id);
    } else if (id >= 0x53000000 && id < 0x54000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.bmp", flash_dir, id);
    } else if (id >= 0x54000000 && id < 0x55000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.svg", flash_dir, id);
    } else if (id >= 0x55000000 && id < 0x56000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.zip", flash_dir, id);
    } else if (id >= 0x80000000 && id < 0x90000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.bin", flash_dir, id);
    } else if (id >= 0x90000000 && id < 0xA0000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.json", flash_dir, id);
    } else if (id >= 0xA0000000 && id < 0xA1000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.mp4", flash_dir, id);
    } else if (id >= 0xA1000000 && id < 0xA2000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.avi", flash_dir, id);
    } else if (id >= 0xA2000000 && id < 0xA3000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.bin", flash_dir, id);
    } else if (id >= 0xA3000000 && id < 0xA4000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.rle", flash_dir, id);
    } else if (id >= 0xB0000000 && id < 0xC0000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.gif", flash_dir, id);
    } else if (id >= 0xD0000000 && id < 0xD1000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.png", flash_dir, id);
    } else if (id >= 0xD1000000 && id < 0xD2000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.jpg", flash_dir, id);
    } else if (id >= 0xD2000000 && id < 0xD3000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.jpeg", flash_dir, id);
    } else if (id >= 0xD3000000 && id < 0xD4000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.bmp", flash_dir, id);
    } else if (id >= 0xD4000000 && id < 0xD5000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.svg", flash_dir, id);
    } else if (id >= 0xD5000000 && id < 0xD6000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.zip", flash_dir, id);
    } else {
        return NULL;
    }
    return path_buf;
#endif
}

#endif
