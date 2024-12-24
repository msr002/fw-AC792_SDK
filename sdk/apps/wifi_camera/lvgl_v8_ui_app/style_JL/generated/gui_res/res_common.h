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

    GUI_RES_S_PC_PNG = 0x55000015,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\USB\s_PC.png
    GUI_RES_S_MASS_PNG = 0x55000016,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\USB\s_MASS.png
    GUI_RES_VIDEO_PNG = 0x55000017,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\USB\VIDEO.png
    GUI_RES_VIDEO_ON_PNG = 0x55000018,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\USB\VIDEO_on.png
    GUI_RES_MASS_PNG = 0x55000019,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\USB\MASS.png
    GUI_RES_MASS_ON_PNG = 0x5500001A,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\USB\MASS_on.png
    GUI_RES_PCCAM_PNG = 0x5500001B,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\USB\PCCAM.png
    GUI_RES_PCCAM_ON_PNG = 0x5500001C,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\USB\PCCAM_on.png
    GUI_RES_VIDEO_BUTTO_PNG = 0x5500001D,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\video_butto.png
    GUI_RES_VIDEO_BUTTO_FLASH1_ON_PNG = 0x5500001E,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\video_butto_flash1_on.png
    GUI_RES_VIDEO_BUTTO_FLASH2_PNG = 0x5500001F,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\video_butto_flash2.png
    GUI_RES_VIDEO_BUTTO_FLASH2_ON_PNG = 0x55000020,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\video_butto_flash2_on.png
    GUI_RES_CYCLIC_VIDEO_CLOSE_PNG = 0x55000021,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\cyclic_video_close.png
    GUI_RES_GRAVITY_SENSOR_LOW_PNG = 0x55000022,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\gravity_sensor_low.png
    GUI_RES_SOUND_CLOSE_PNG = 0x55000023,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\sound_close.png
    GUI_RES_STOPPING_MONITOR_PNG = 0x55000024,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\stopping_monitor.png
    GUI_RES_CHECK_SPORT_PNG = 0x55000025,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\check_sport.png
    GUI_RES_SD_PNG = 0x55000026,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\SD.png
    GUI_RES_LOCK_PNG = 0x55000027,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\lock.png
    GUI_RES_INTERVAL_VIDEO_CLOSE_PNG = 0x55000028,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\interval_video_close.png
    GUI_RES_DISCONNECT_PNG = 0x55000029,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\disconnect.png
    GUI_RES_FULL_PNG = 0x5500002A,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\battery\full.png
    GUI_RES_SETTING_PNG = 0x5500002B,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\left_tools\setting.png
    GUI_RES_CAMERA_PNG = 0x5500002C,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\left_tools\camera.png
    GUI_RES_HOME_PNG = 0x5500002D,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\left_tools\home.png
    GUI_RES_BTN_LOCK_PNG = 0x5500002E,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\btn_lock.png
    GUI_RES_BTN_LOCK_ON_PNG = 0x5500002F,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\btn_lock_on.png
    GUI_RES_SWITCH_PNG = 0x55000030,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\switch.png
    GUI_RES_SWITCH_ON_PNG = 0x55000031,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\switch_on.png
    GUI_RES_RESOLUTION_RATIO_PNG = 0x55000032,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\resolution_ratio.png
    GUI_RES_DOUBLE_VIDEO_PNG = 0x55000033,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\double_video.png
    GUI_RES_CYCLIC_VIDEO_PNG = 0x55000034,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\cyclic_video.png
    GUI_RES_INTERVAL_VIDEO_PNG = 0x55000035,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\interval_video.png
    GUI_RES_HDR_PNG = 0x55000036,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\HDR.png
    GUI_RES_EXPOSURE_PNG = 0x55000037,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\exposure.png
    GUI_RES_CHECK_SPORT_1_PNG = 0x55000038,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\check_sport.png
    GUI_RES_DATE_PNG = 0x55000039,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\date.png
    GUI_RES_GRAVITY_SENSOR_PNG = 0x5500003A,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\gravity_sensor.png
    GUI_RES_SOUND_PNG = 0x5500003B,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\sound.png
    GUI_RES_STOPPING_MONITOR_1_PNG = 0x5500003C,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\stopping_monitor.png
    GUI_RES_CAR_NUM_PNG = 0x5500003D,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\car_num.png
    GUI_RES_HEADLIGHT_PNG = 0x5500003E,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\headlight.png
    GUI_RES_VIDEO_1_PNG = 0x5500003F,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\main_page\video.png
    GUI_RES_VIDEO__ON_PNG = 0x55000040,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\main_page\video__on.png
    GUI_RES_FILE_PNG = 0x55000041,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\main_page\file.png
    GUI_RES_FILE_ON_PNG = 0x55000042,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\main_page\file_on.png
    GUI_RES_SETTING_1_PNG = 0x55000043,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\main_page\setting.png
    GUI_RES_SETTING_ON_PNG = 0x55000044,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\main_page\setting_on.png
    GUI_RES_POP_UP_WINDOW_PNG = 0x55000045,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\pop_up_window.png
    GUI_RES_FLIG_ON_PNG = 0x55000046,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\flig_on.png
    GUI_RES_ASTERN_PNG = 0x55000047,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\astern.png
    GUI_RES_LCD_OFF_PNG = 0x55000048,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\sys_setting\icon\lcd_off.png
    GUI_RES_AUTO_OFF_PNG = 0x55000049,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\sys_setting\icon\auto_off.png
    GUI_RES_FREQUENCY_PNG = 0x5500004A,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\sys_setting\icon\frequency.png
    GUI_RES_VOICE_PNG = 0x5500004B,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\sys_setting\icon\voice.png
    GUI_RES_LANGUAGES_PNG = 0x5500004C,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\sys_setting\icon\languages.png
    GUI_RES_SOFTWARE_PNG = 0x5500004D,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\software.png
    GUI_RES_CAR_NUM_1_PNG = 0x5500004E,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\sys_setting\icon\car_num.png
    GUI_RES_LANE_PNG = 0x5500004F,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\sys_setting\icon\lane.png
    GUI_RES_FLIG_PNG = 0x55000050,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\sys_setting\icon\flig.png
    GUI_RES_FORMAT_PNG = 0x55000051,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\sys_setting\icon\format.png
    GUI_RES_RESET_PNG = 0x55000052,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\sys_setting\icon\reset.png
    GUI_RES_DATE_1_PNG = 0x55000053,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\sys_setting\icon\date.png
    GUI_RES_VIDEO_2_PNG = 0x55000054,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\sys_setting\left_tools\video.png
    GUI_RES_FILES_PNG = 0x55000055,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\sys_setting\left_tools\FILES.png
    GUI_RES_PHOTO_BUTTON_PNG = 0x55000056,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\photo_button.png
    GUI_RES_PHOTO_BUTTON_ON_PNG = 0x55000057,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\photo_button_on.png
    GUI_RES_TIMING_PHOTO_2_PNG = 0x55000058,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\timing_photo_2.png
    GUI_RES_CONTINUOUS_PNG = 0x55000059,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\continuous.png
    GUI_RES_HAND_SHAKE_PNG = 0x5500005A,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\hand_shake.png
    GUI_RES_VIDEO_3_PNG = 0x5500005B,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\left_tools\video.png
    GUI_RES_TIMING_PHOTO_PNG = 0x5500005C,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\timing_photo.png
    GUI_RES_CONTINUOUS_PHOTO_PNG = 0x5500005D,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\continuous_photo.png
    GUI_RES_PHOTO_QUALITY_PNG = 0x5500005E,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\photo_quality.png
    GUI_RES_ACUITY_PNG = 0x5500005F,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\acuity.png
    GUI_RES_AWB_PNG = 0x55000060,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\AWB.png
    GUI_RES_COLOR_PNG = 0x55000061,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\color.png
    GUI_RES_ISO_PNG = 0x55000062,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\ISO.png
    GUI_RES_HAND_SHAKE_1_PNG = 0x55000063,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\hand_shake.png
    GUI_RES_QUICK_SCAN_PNG = 0x55000064,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\quick_scan.png
    GUI_RES_HIGH_PNG = 0x55000065,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\high.png
    GUI_RES_AWB_1_PNG = 0x55000066,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\awb.png
    GUI_RES_VIDEO_PLAY_PNG = 0x55000067,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_play.png
    GUI_RES_VIDEO_PAUSE_PNG = 0x55000068,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_pause.png
    GUI_RES_VOLUMELOUDER_SOLID_1_PNG = 0x55000069,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\volumeLouder_solid_1.png
    GUI_RES_VOLUMEMUTE_SOLID_1_PNG = 0x5500006A,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\volumeMute_solid_1.png
    GUI_RES_PHOTO_PNG = 0x5500006B,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\PHOTO.png
    GUI_RES_PHOTO_ON_PNG = 0x5500006C,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\photo_on.png
    GUI_RES_RETURN_PNG = 0x5500006D,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\RETURN.png
    GUI_RES_RETURN_ON_PNG = 0x5500006E,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\return_on.png
    GUI_RES_SKIP_PREVIOUS_PNG = 0x5500006F,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\skip_previous.png
    GUI_RES_SKIP_NEXT_PNG = 0x55000070,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\skip_next.png
    GUI_RES_UP_PNG = 0x55000071,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\up.png
    GUI_RES_DOWN_PNG = 0x55000072,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\down.png
    GUI_RES_EDIT_PNG = 0x55000073,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\EDIT.png
    GUI_RES_EDITOR_ON_PNG = 0x55000074,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\editor_on.png
    GUI_RES_LOCK_1_PNG = 0x55000075,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\LOCK.png
    GUI_RES_LOCK_ON_PNG = 0x55000076,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\lock_on.png
    GUI_RES_HOME_1_PNG = 0x55000077,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\HOME.png
    GUI_RES_HOME_ON_PNG = 0x55000078,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\home_on.png
    GUI_RES_DELETE_PNG = 0x55000079,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\DELETE.png
    GUI_RES_DELETE_ON_PNG = 0x5500007A,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\delete_on.png
} GUI_RES_ID;

typedef enum {
    RES_0 = 0xD500007B,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\battery\0.png 48x48
    RES_1 = 0xD500007C,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\battery\1.png 48x48
    RES_2 = 0xD500007D,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\battery\2.png 48x48
    RES_3 = 0xD500007E,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\battery\3.png 48x48
    RES_CHARGING = 0xD500007F,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\battery\charging.png 48x48
    RES_FULL = 0xD5000080,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\battery\full.png 48x48
    RES_CYCLIC_VIDEO_3 = 0xD5000081,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\cyclic_video_3.png 48x48
    RES_CYCLIC_VIDEO_10 = 0xD5000082,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\cyclic_video_10.png 48x48
    RES_CYCLIC_VIDEO_CLOSE = 0xD5000083,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\cyclic_video_close.png 48x48
    RES_GRAVITY_SENSOR_LOW = 0xD5000084,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\gravity_sensor_low.png 48x48
    RES_GRAVITY_SENSOR_MIDLLER = 0xD5000085,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\gravity_sensor_midller.png 48x48
    RES_GRAVITY_SENSOR_HIGH = 0xD5000086,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\gravity_sensor_high.png 48x48
    RES_INTERVAL_VIDEO_CLOSE = 0xD5000087,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\interval_video_close.png 48x48
    RES_INTERVAL_VIDEO_500 = 0xD5000088,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\interval_video_500.png 48x48
    RES_INTERVAL_VIDEO_200 = 0xD5000089,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\interval_video_200.png 48x48
    RES_INTERVAL_VIDEO_100 = 0xD500008A,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\interval_video_100.png 48x48
    RES_SD = 0xD500008B,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\SD.png 45x45
    RES_SD_CLOSE = 0xD500008C,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\SD_close.png 45x45
    RES_SOUND = 0xD500008D,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\sound.png 48x48
    RES_SOUND_CLOSE = 0xD500008E,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\sound_close.png 48x48
    RES_EXPOSURE = 0xD500008F,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\exposure.png 80x80
    RES_DOUBLE_VIDEO = 0xD5000090,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\double_video.png 80x80
    RES_DATE = 0xD5000091,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\date.png 80x80
    RES_CYCLIC_VIDEO = 0xD5000092,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\cyclic_video.png 80x80
    RES_CHECK_SPORT = 0xD5000093,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\check_sport.png 80x80
    RES_CAR_NUM = 0xD5000094,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\car_num.png 80x80
    RES_GRAVITY_SENSOR = 0xD5000095,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\gravity_sensor.png 80x80
    RES_HDR = 0xD5000096,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\HDR.png 80x80
    RES_INTERVAL_VIDEO = 0xD5000097,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\interval_video.png 80x80
    RES_RESOLUTION_RATIO = 0xD5000098,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\resolution_ratio.png 80x80
    RES_SOUND_1 = 0xD5000099,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\sound.png 80x80
    RES_STOPPING_MONITOR = 0xD500009A,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\stopping_monitor.png 80x80
    RES_AUTO_OFF = 0xD500009B,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\sys_setting\icon\auto_off.png 80x80
    RES_CAR_NUM_1 = 0xD500009C,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\sys_setting\icon\car_num.png 80x80
    RES_FLIG = 0xD500009D,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\sys_setting\icon\flig.png 80x80
    RES_FORMAT = 0xD500009E,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\sys_setting\icon\format.png 80x80
    RES_FREQUENCY = 0xD500009F,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\sys_setting\icon\frequency.png 80x80
    RES_LANE = 0xD50000A0,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\sys_setting\icon\lane.png 80x80
    RES_LANGUAGES = 0xD50000A1,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\sys_setting\icon\languages.png 80x80
    RES_LCD_OFF = 0xD50000A2,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\sys_setting\icon\lcd_off.png 80x80
    RES_RESET = 0xD50000A3,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\sys_setting\icon\reset.png 80x80
    RES_VERSION = 0xD50000A4,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\sys_setting\icon\version.png 80x80
    RES_VOICE = 0xD50000A5,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\sys_setting\icon\voice.png 80x80
    RES_DATE_1 = 0xD50000A6,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\sys_setting\icon\date.png 80x80
    RES_AWB = 0xD50000A7,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\awb.png 48x48
    RES_AWB_FLUORESCENT_LAMP = 0xD50000A8,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\awb_fluorescent_lamp.png 48x48
    RES_AWB_OSRAM_LAMP = 0xD50000A9,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\awb_osram_lamp.png 48x48
    RES_AWB_SUN_CLOUDY = 0xD50000AA,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\awb_sun_cloudy.png 48x48
    RES_AWB_SUN_LIGHT = 0xD50000AB,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\awb_sun_light.png 48x48
    RES_HIGH = 0xD50000AC,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\high.png 48x48
    RES_LOW = 0xD50000AD,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\low.png 48x48
    RES_MIDDLE = 0xD50000AE,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\middle.png 48x48
    RES_TIMING_PHOTO_2 = 0xD50000AF,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\timing_photo_2.png 48x48
    RES_TIMING_PHOTO_5 = 0xD50000B0,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\timing_photo_5.png 48x48
    RES_TIMING_PHOTO_10 = 0xD50000B1,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\timing_photo_10.png 48x48
    RES_FILE_DIR = 0xD50000B2,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\file_dir.png 160x160
    RES_DELETE = 0xD50000B3,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\DELETE.png 48x48
    RES_DELETE_ON = 0xD50000B4,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\delete_on.png 48x48
    RES_EDIT = 0xD50000B5,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\EDIT.png 48x48
    RES_EDITOR_ON = 0xD50000B6,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\editor_on.png 48x48
    RES_HOME = 0xD50000B7,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\HOME.png 48x48
    RES_HOME_ON = 0xD50000B8,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\home_on.png 48x48
    RES_LOCK = 0xD50000B9,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\LOCK.png 48x48
    RES_LOCK_ON = 0xD50000BA,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\lock_on.png 48x48
    RES_PHOTO = 0xD50000BB,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\PHOTO.png 48x48
    RES_PHOTO_ON = 0xD50000BC,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\photo_on.png 48x48
    RES_RETURN = 0xD50000BD,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\RETURN.png 48x48
    RES_RETURN_ON = 0xD50000BE,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\return_on.png 48x48
    RES_SELETE = 0xD50000BF,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\SELETE.png 48x48
    RES_UNLOCK = 0xD50000C0,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\UNLOCK.png 48x48
    RES_UNLOCK_ON = 0xD50000C1,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\unlock_on.png 48x48
    RES_VIDEO = 0xD50000C2,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\VIDEO.png 48x48
    RES_VOLUMELOUDER_SOLID_1 = 0xD50000C3,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\volumeLouder_solid_1.png 48x48
    RES_VIDEO_PAUSE = 0xD50000C4,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_pause.png 48x48
    RES_SKIP_NEXT = 0xD50000C5,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\skip_next.png 48x48
    RES_SKIP_PREVIOUS = 0xD50000C6,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\skip_previous.png 48x48
    RES_PLAY = 0xD50000C7,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\play.png 32x32
    RES_VIDEO_PLAY = 0xD50000C8,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_play.png 48x48
    RES_VOLUMEMUTE_SOLID_1 = 0xD50000C9,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\volumeMute_solid_1.png 48x48
    RES_SOFTWARE = 0xD50000CA,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\software.png 80x80
    RES_CYCLIC_VIDEO_1 = 0xD50000CB,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\cyclic_video_1.png 48x48
    RES_LOCK_FLAG = 0xD50000CC,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\lock_flag.png 24x24
    RES_CONNECTED = 0xD50000CD,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\connected.png 45x45
    RES_DISCONNECT = 0xD50000CE,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\disconnect.png 45x45
} RES_ID;

extern char *gui_get_res_path(int32_t id);

#ifdef __cplusplus
}
#endif
#endif

#endif
