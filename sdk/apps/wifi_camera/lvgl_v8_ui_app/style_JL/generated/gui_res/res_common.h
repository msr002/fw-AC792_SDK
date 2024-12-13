#include "app_config.h"
#ifdef CONFIG_UI_STYLE_JL_ENABLE
/*Generate Code, Do NOT Edit!*/
#ifndef __RES_COMMON_H__
#define __RES_COMMON_H__
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

#if LV_USE_GUIBUILDER_SIMULATOR
#define GUI_WEAKREF __attribute__((weakref))
#define GUI_WEAK __attribute__((weak))
#else
#define GUI_WEAKREF
#define GUI_WEAK __attribute__((weak))
#endif

typedef enum {
    GUI_RES_MONTSERRATMEDIUM_12_TTF = 0x10000000,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\rle\font\10000000.rle
    GUI_RES_FANGZHENGKAITIJIANTI_1_28_TTF = 0x10000001,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\rle\font\10000001.rle
    GUI_RES_FANGZHENGKAITIJIANTI_1_19_TTF = 0x10000002,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\rle\font\10000002.rle
    GUI_RES_FANGZHENGKAITIJIANTI_1_24_TTF = 0x10000003,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\rle\font\10000003.rle
    GUI_RES_FANGZHENGKAITIJIANTI_1_32_TTF = 0x10000004,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\rle\font\10000004.rle
    GUI_RES_FANGZHENGKAITIJIANTI_1_16_TTF = 0x10000005,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\rle\font\10000005.rle
    GUI_RES_MONTSERRATMEDIUM_18_TTF = 0x10000006,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\rle\font\10000006.rle
    GUI_RES_MONTSERRATMEDIUM_20_TTF = 0x10000007,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\rle\font\10000007.rle
    GUI_RES_FANGZHENGKAITIJIANTI_1_54_TTF = 0x10000008,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\rle\font\10000008.rle
    GUI_RES_FANGZHENGKAITIJIANTI_1_48_TTF = 0x10000009,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\rle\font\10000009.rle
    GUI_RES_FANGZHENGKAITIJIANTI_1_20_TTF = 0x1000000A,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\rle\font\1000000a.rle
    GUI_RES_MONTSERRATMEDIUM_24_TTF = 0x1000000B,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\rle\font\1000000b.rle
    GUI_RES_MONTSERRATMEDIUM_48_TTF = 0x1000000C,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\rle\font\1000000c.rle
    GUI_RES_MONTSERRATMEDIUM_49_TTF = 0x1000000D,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\rle\font\1000000d.rle
    GUI_RES_MONTSERRATMEDIUM_32_TTF = 0x1000000E,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\rle\font\1000000e.rle
    GUI_RES_FANGZHENGKAITIJIANTI_1_14_TTF = 0x1000000F,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\rle\font\1000000f.rle
    GUI_RES_MONTSERRATMEDIUM_160_TTF = 0x10000010,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\rle\font\10000010.rle
    GUI_RES_FANGZHENGKAITIJIANTI_1_26_TTF = 0x10000011,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\rle\font\10000011.rle
    GUI_RES_MONTSERRATMEDIUM_22_TTF = 0x10000012,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\rle\font\10000012.rle
    GUI_RES_MONTSERRATMEDIUM_16_TTF = 0x10000013,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\rle\font\10000013.rle
    GUI_RES_FANGZHENGKAITIJIANTI_1_22_TTF = 0x10000014,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\rle\font\10000014.rle

    GUI_RES_S_PC_PNG = 0x55000000,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\55000000.zip
    GUI_RES_S_MASS_PNG = 0x55000001,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\55000001.zip
    GUI_RES_VIDEO_PNG = 0x55000002,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\55000002.zip
    GUI_RES_VIDEO_ON_PNG = 0x55000003,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\55000003.zip
    GUI_RES_MASS_PNG = 0x55000004,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\55000004.zip
    GUI_RES_MASS_ON_PNG = 0x55000005,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\55000005.zip
    GUI_RES_PCCAM_PNG = 0x55000006,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\55000006.zip
    GUI_RES_PCCAM_ON_PNG = 0x55000007,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\55000007.zip
    GUI_RES_VIDEO_BUTTO_PNG = 0x55000008,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\55000008.zip
    GUI_RES_VIDEO_BUTTO_FLASH1_ON_PNG = 0x55000009,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\55000009.zip
    GUI_RES_VIDEO_BUTTO_FLASH2_PNG = 0x5500000A,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\5500000a.zip
    GUI_RES_VIDEO_BUTTO_FLASH2_ON_PNG = 0x5500000B,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\5500000b.zip
    GUI_RES_CYCLIC_VIDEO_CLOSE_PNG = 0x5500000C,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\5500000c.zip
    GUI_RES_GRAVITY_SENSOR_LOW_PNG = 0x5500000D,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\5500000d.zip
    GUI_RES_SOUND_CLOSE_PNG = 0x5500000E,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\5500000e.zip
    GUI_RES_STOPPING_MONITOR_PNG = 0x5500000F,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\5500000f.zip
    GUI_RES_CHECK_SPORT_PNG = 0x55000010,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\55000010.zip
    GUI_RES_SD_PNG = 0x55000011,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\55000011.zip
    GUI_RES_LOCK_PNG = 0x55000012,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\55000012.zip
    GUI_RES_INTERVAL_VIDEO_CLOSE_PNG = 0x55000013,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\55000013.zip
    GUI_RES_DISCONNECT_PNG = 0x55000014,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\55000014.zip
    GUI_RES_FULL_PNG = 0x55000015,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\55000015.zip
    GUI_RES_SETTING_PNG = 0x55000016,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\55000016.zip
    GUI_RES_CAMERA_PNG = 0x55000017,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\55000017.zip
    GUI_RES_HOME_PNG = 0x55000018,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\55000018.zip
    GUI_RES_BTN_LOCK_PNG = 0x55000019,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\55000019.zip
    GUI_RES_BTN_LOCK_ON_PNG = 0x5500001A,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\5500001a.zip
    GUI_RES_SWITCH_PNG = 0x5500001B,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\5500001b.zip
    GUI_RES_SWITCH_ON_PNG = 0x5500001C,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\5500001c.zip
    GUI_RES_RESOLUTION_RATIO_PNG = 0x5500001D,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\5500001d.zip
    GUI_RES_DOUBLE_VIDEO_PNG = 0x5500001E,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\5500001e.zip
    GUI_RES_CYCLIC_VIDEO_PNG = 0x5500001F,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\5500001f.zip
    GUI_RES_INTERVAL_VIDEO_PNG = 0x55000020,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\55000020.zip
    GUI_RES_HDR_PNG = 0x55000021,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\55000021.zip
    GUI_RES_EXPOSURE_PNG = 0x55000022,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\55000022.zip
    GUI_RES_CHECK_SPORT_1_PNG = 0x55000023,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\55000023.zip
    GUI_RES_DATE_PNG = 0x55000024,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\55000024.zip
    GUI_RES_GRAVITY_SENSOR_PNG = 0x55000025,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\55000025.zip
    GUI_RES_SOUND_PNG = 0x55000026,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\55000026.zip
    GUI_RES_STOPPING_MONITOR_1_PNG = 0x55000027,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\55000027.zip
    GUI_RES_CAR_NUM_PNG = 0x55000028,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\55000028.zip
    GUI_RES_HEADLIGHT_PNG = 0x55000029,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\55000029.zip
    GUI_RES_VIDEO_1_PNG = 0x5500002A,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\5500002a.zip
    GUI_RES_VIDEO__ON_PNG = 0x5500002B,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\5500002b.zip
    GUI_RES_FILE_PNG = 0x5500002C,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\5500002c.zip
    GUI_RES_FILE_ON_PNG = 0x5500002D,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\5500002d.zip
    GUI_RES_SETTING_1_PNG = 0x5500002E,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\5500002e.zip
    GUI_RES_SETTING_ON_PNG = 0x5500002F,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\5500002f.zip
    GUI_RES_POP_UP_WINDOW_PNG = 0x55000030,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\55000030.zip
    GUI_RES_FLIG_ON_PNG = 0x55000031,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\55000031.zip
    GUI_RES_ASTERN_PNG = 0x55000032,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\55000032.zip
    GUI_RES_LCD_OFF_PNG = 0x55000033,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\55000033.zip
    GUI_RES_AUTO_OFF_PNG = 0x55000034,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\55000034.zip
    GUI_RES_FREQUENCY_PNG = 0x55000035,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\55000035.zip
    GUI_RES_VOICE_PNG = 0x55000036,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\55000036.zip
    GUI_RES_LANGUAGES_PNG = 0x55000037,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\55000037.zip
    GUI_RES_SOFTWARE_PNG = 0x55000038,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\55000038.zip
    GUI_RES_CAR_NUM_1_PNG = 0x55000039,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\55000039.zip
    GUI_RES_LANE_PNG = 0x5500003A,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\5500003a.zip
    GUI_RES_FLIG_PNG = 0x5500003B,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\5500003b.zip
    GUI_RES_FORMAT_PNG = 0x5500003C,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\5500003c.zip
    GUI_RES_RESET_PNG = 0x5500003D,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\5500003d.zip
    GUI_RES_DATE_1_PNG = 0x5500003E,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\5500003e.zip
    GUI_RES_VIDEO_2_PNG = 0x5500003F,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\5500003f.zip
    GUI_RES_FILES_PNG = 0x55000040,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\55000040.zip
    GUI_RES_PHOTO_BUTTON_PNG = 0x55000041,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\55000041.zip
    GUI_RES_PHOTO_BUTTON_ON_PNG = 0x55000042,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\55000042.zip
    GUI_RES_TIMING_PHOTO_2_PNG = 0x55000043,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\55000043.zip
    GUI_RES_CONTINUOUS_PNG = 0x55000044,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\55000044.zip
    GUI_RES_HAND_SHAKE_PNG = 0x55000045,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\55000045.zip
    GUI_RES_VIDEO_3_PNG = 0x55000046,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\55000046.zip
    GUI_RES_TIMING_PHOTO_PNG = 0x55000047,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\55000047.zip
    GUI_RES_CONTINUOUS_PHOTO_PNG = 0x55000048,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\55000048.zip
    GUI_RES_PHOTO_QUALITY_PNG = 0x55000049,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\55000049.zip
    GUI_RES_ACUITY_PNG = 0x5500004A,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\5500004a.zip
    GUI_RES_AWB_PNG = 0x5500004B,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\5500004b.zip
    GUI_RES_COLOR_PNG = 0x5500004C,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\5500004c.zip
    GUI_RES_ISO_PNG = 0x5500004D,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\5500004d.zip
    GUI_RES_HAND_SHAKE_1_PNG = 0x5500004E,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\5500004e.zip
    GUI_RES_QUICK_SCAN_PNG = 0x5500004F,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\5500004f.zip
    GUI_RES_HIGH_PNG = 0x55000050,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\55000050.zip
    GUI_RES_AWB_1_PNG = 0x55000051,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\55000051.zip
    GUI_RES_VIDEO_PLAY_PNG = 0x55000052,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\55000052.zip
    GUI_RES_VIDEO_PAUSE_PNG = 0x55000053,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\55000053.zip
    GUI_RES_VOLUMELOUDER_SOLID_1_PNG = 0x55000054,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\55000054.zip
    GUI_RES_VOLUMEMUTE_SOLID_1_PNG = 0x55000055,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\55000055.zip
    GUI_RES_PHOTO_PNG = 0x55000056,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\55000056.zip
    GUI_RES_PHOTO_ON_PNG = 0x55000057,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\55000057.zip
    GUI_RES_RETURN_PNG = 0x55000058,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\55000058.zip
    GUI_RES_RETURN_ON_PNG = 0x55000059,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\55000059.zip
    GUI_RES_SKIP_PREVIOUS_PNG = 0x5500005A,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\5500005a.zip
    GUI_RES_SKIP_NEXT_PNG = 0x5500005B,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\5500005b.zip
    GUI_RES_UP_PNG = 0x5500005C,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\5500005c.zip
    GUI_RES_DOWN_PNG = 0x5500005D,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\5500005d.zip
    GUI_RES_EDIT_PNG = 0x5500005E,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\5500005e.zip
    GUI_RES_EDITOR_ON_PNG = 0x5500005F,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\5500005f.zip
    GUI_RES_LOCK_1_PNG = 0x55000060,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\55000060.zip
    GUI_RES_LOCK_ON_PNG = 0x55000061,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\55000061.zip
    GUI_RES_HOME_1_PNG = 0x55000062,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\55000062.zip
    GUI_RES_HOME_ON_PNG = 0x55000063,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\55000063.zip
    GUI_RES_DELETE_PNG = 0x55000064,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\55000064.zip
    GUI_RES_DELETE_ON_PNG = 0x55000065,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\55000065.zip
} GUI_RES_ID;

typedef enum {
    RES_0 = 0xD5000000,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d5000000.zip 48x48
    RES_1 = 0xD5000001,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d5000001.zip 48x48
    RES_2 = 0xD5000002,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d5000002.zip 48x48
    RES_3 = 0xD5000003,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d5000003.zip 48x48
    RES_CHARGING = 0xD5000004,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d5000004.zip 48x48
    RES_FULL = 0xD5000005,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d5000005.zip 48x48
    RES_CYCLIC_VIDEO_3 = 0xD5000006,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d5000006.zip 48x48
    RES_CYCLIC_VIDEO_10 = 0xD5000007,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d5000007.zip 48x48
    RES_CYCLIC_VIDEO_CLOSE = 0xD5000008,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d5000008.zip 48x48
    RES_GRAVITY_SENSOR_LOW = 0xD5000009,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d5000009.zip 48x48
    RES_GRAVITY_SENSOR_MIDLLER = 0xD500000A,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d500000a.zip 48x48
    RES_GRAVITY_SENSOR_HIGH = 0xD500000B,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d500000b.zip 48x48
    RES_INTERVAL_VIDEO_CLOSE = 0xD500000C,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d500000c.zip 48x48
    RES_INTERVAL_VIDEO_500 = 0xD500000D,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d500000d.zip 48x48
    RES_INTERVAL_VIDEO_200 = 0xD500000E,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d500000e.zip 48x48
    RES_INTERVAL_VIDEO_100 = 0xD500000F,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d500000f.zip 48x48
    RES_SD = 0xD5000010,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d5000010.zip 45x45
    RES_SD_CLOSE = 0xD5000011,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d5000011.zip 45x45
    RES_SOUND = 0xD5000012,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d5000012.zip 48x48
    RES_SOUND_CLOSE = 0xD5000013,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d5000013.zip 48x48
    RES_EXPOSURE = 0xD5000014,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d5000014.zip 80x80
    RES_DOUBLE_VIDEO = 0xD5000015,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d5000015.zip 80x80
    RES_DATE = 0xD5000016,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d5000016.zip 80x80
    RES_CYCLIC_VIDEO = 0xD5000017,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d5000017.zip 80x80
    RES_CHECK_SPORT = 0xD5000018,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d5000018.zip 80x80
    RES_CAR_NUM = 0xD5000019,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d5000019.zip 80x80
    RES_GRAVITY_SENSOR = 0xD500001A,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d500001a.zip 80x80
    RES_HDR = 0xD500001B,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d500001b.zip 80x80
    RES_INTERVAL_VIDEO = 0xD500001C,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d500001c.zip 80x80
    RES_RESOLUTION_RATIO = 0xD500001D,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d500001d.zip 80x80
    RES_SOUND_1 = 0xD500001E,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d500001e.zip 80x80
    RES_STOPPING_MONITOR = 0xD500001F,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d500001f.zip 80x80
    RES_AUTO_OFF = 0xD5000020,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d5000020.zip 80x80
    RES_CAR_NUM_1 = 0xD5000021,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d5000021.zip 80x80
    RES_FLIG = 0xD5000022,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d5000022.zip 80x80
    RES_FORMAT = 0xD5000023,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d5000023.zip 80x80
    RES_FREQUENCY = 0xD5000024,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d5000024.zip 80x80
    RES_LANE = 0xD5000025,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d5000025.zip 80x80
    RES_LANGUAGES = 0xD5000026,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d5000026.zip 80x80
    RES_LCD_OFF = 0xD5000027,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d5000027.zip 80x80
    RES_RESET = 0xD5000028,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d5000028.zip 80x80
    RES_VERSION = 0xD5000029,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d5000029.zip 80x80
    RES_VOICE = 0xD500002A,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d500002a.zip 80x80
    RES_DATE_1 = 0xD500002B,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d500002b.zip 80x80
    RES_AWB = 0xD500002C,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d500002c.zip 48x48
    RES_AWB_FLUORESCENT_LAMP = 0xD500002D,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d500002d.zip 48x48
    RES_AWB_OSRAM_LAMP = 0xD500002E,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d500002e.zip 48x48
    RES_AWB_SUN_CLOUDY = 0xD500002F,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d500002f.zip 48x48
    RES_AWB_SUN_LIGHT = 0xD5000030,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d5000030.zip 48x48
    RES_HIGH = 0xD5000031,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d5000031.zip 48x48
    RES_LOW = 0xD5000032,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d5000032.zip 48x48
    RES_MIDDLE = 0xD5000033,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d5000033.zip 48x48
    RES_TIMING_PHOTO_2 = 0xD5000034,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d5000034.zip 48x48
    RES_TIMING_PHOTO_5 = 0xD5000035,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d5000035.zip 48x48
    RES_TIMING_PHOTO_10 = 0xD5000036,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d5000036.zip 48x48
    RES_FILE_DIR = 0xD5000037,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d5000037.zip 160x160
    RES_DELETE = 0xD5000038,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d5000038.zip 48x48
    RES_DELETE_ON = 0xD5000039,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d5000039.zip 48x48
    RES_EDIT = 0xD500003A,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d500003a.zip 48x48
    RES_EDITOR_ON = 0xD500003B,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d500003b.zip 48x48
    RES_HOME = 0xD500003C,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d500003c.zip 48x48
    RES_HOME_ON = 0xD500003D,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d500003d.zip 48x48
    RES_LOCK = 0xD500003E,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d500003e.zip 48x48
    RES_LOCK_ON = 0xD500003F,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d500003f.zip 48x48
    RES_PHOTO = 0xD5000040,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d5000040.zip 48x48
    RES_PHOTO_ON = 0xD5000041,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d5000041.zip 48x48
    RES_RETURN = 0xD5000042,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d5000042.zip 48x48
    RES_RETURN_ON = 0xD5000043,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d5000043.zip 48x48
    RES_SELETE = 0xD5000044,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d5000044.zip 48x48
    RES_UNLOCK = 0xD5000045,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d5000045.zip 48x48
    RES_UNLOCK_ON = 0xD5000046,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d5000046.zip 48x48
    RES_VIDEO = 0xD5000047,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d5000047.zip 48x48
    RES_VOLUMELOUDER_SOLID_1 = 0xD5000048,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d5000048.zip 48x48
    RES_VIDEO_PAUSE = 0xD5000049,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d5000049.zip 48x48
    RES_SKIP_NEXT = 0xD500004A,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d500004a.zip 48x48
    RES_SKIP_PREVIOUS = 0xD500004B,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d500004b.zip 48x48
    RES_PLAY = 0xD500004C,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d500004c.zip 32x32
    RES_VIDEO_PLAY = 0xD500004D,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d500004d.zip 48x48
    RES_VOLUMEMUTE_SOLID_1 = 0xD500004E,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d500004e.zip 48x48
    RES_SOFTWARE = 0xD500004F,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d500004f.zip 80x80
    RES_CYCLIC_VIDEO_1 = 0xD5000050,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d5000050.zip 48x48
    RES_LOCK_FLAG = 0xD5000051,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d5000051.zip 24x24
    RES_CONNECTED = 0xD5000052,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d5000052.zip 45x45
    RES_DISCONNECT = 0xD5000053,   //E:\1111\ac792\ui_prj\dvr_800x480\sdk\ui_res\zip\image\d5000053.zip 45x45
} RES_ID;

extern char *gui_get_res_path(int32_t id);

#ifdef __cplusplus
}
#endif
#endif

#endif
