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

    GUI_RES_S_PC_PNG = 0x56000000,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\USB\s_PC.png
    GUI_RES_S_MASS_PNG = 0x56000001,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\USB\s_MASS.png
    GUI_RES_VIDEO_PNG = 0x56000002,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\USB\VIDEO.png
    GUI_RES_VIDEO_ON_PNG = 0x56000003,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\USB\VIDEO_on.png
    GUI_RES_MASS_PNG = 0x56000004,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\USB\MASS.png
    GUI_RES_MASS_ON_PNG = 0x56000005,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\USB\MASS_on.png
    GUI_RES_PCCAM_PNG = 0x56000006,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\USB\PCCAM.png
    GUI_RES_PCCAM_ON_PNG = 0x56000007,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\USB\PCCAM_on.png
    GUI_RES_VIDEO_BUTTO_PNG = 0x56000008,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\video_butto.png
    GUI_RES_VIDEO_BUTTO_FLASH1_ON_PNG = 0x56000009,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\video_butto_flash1_on.png
    GUI_RES_VIDEO_BUTTO_FLASH2_PNG = 0x5600000A,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\video_butto_flash2.png
    GUI_RES_VIDEO_BUTTO_FLASH2_ON_PNG = 0x5600000B,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\video_butto_flash2_on.png
    GUI_RES_CYCLIC_VIDEO_CLOSE_PNG = 0x5600000C,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\cyclic_video_close.png
    GUI_RES_GRAVITY_SENSOR_LOW_PNG = 0x5600000D,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\gravity_sensor_low.png
    GUI_RES_SOUND_CLOSE_PNG = 0x5600000E,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\sound_close.png
    GUI_RES_STOPPING_MONITOR_PNG = 0x5600000F,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\stopping_monitor.png
    GUI_RES_CHECK_SPORT_PNG = 0x56000010,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\check_sport.png
    GUI_RES_SD_PNG = 0x56000011,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\SD.png
    GUI_RES_LOCK_PNG = 0x56000012,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\lock.png
    GUI_RES_INTERVAL_VIDEO_CLOSE_PNG = 0x56000013,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\interval_video_close.png
    GUI_RES_DISCONNECT_PNG = 0x56000014,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\disconnect.png
    GUI_RES_FULL_PNG = 0x56000015,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\battery\full.png
    GUI_RES_SETTING_PNG = 0x56000016,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\left_tools\setting.png
    GUI_RES_CAMERA_PNG = 0x56000017,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\left_tools\camera.png
    GUI_RES_HOME_PNG = 0x56000018,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\left_tools\home.png
    GUI_RES_BTN_LOCK_PNG = 0x56000019,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\btn_lock.png
    GUI_RES_BTN_LOCK_ON_PNG = 0x5600001A,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\btn_lock_on.png
    GUI_RES_SWITCH_PNG = 0x5600001B,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\switch.png
    GUI_RES_SWITCH_ON_PNG = 0x5600001C,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\switch_on.png
    GUI_RES_RESOLUTION_RATIO_PNG = 0x5600001D,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\resolution_ratio.png
    GUI_RES_DOUBLE_VIDEO_PNG = 0x5600001E,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\double_video.png
    GUI_RES_CYCLIC_VIDEO_PNG = 0x5600001F,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\cyclic_video.png
    GUI_RES_INTERVAL_VIDEO_PNG = 0x56000020,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\interval_video.png
    GUI_RES_HDR_PNG = 0x56000021,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\HDR.png
    GUI_RES_EXPOSURE_PNG = 0x56000022,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\exposure.png
    GUI_RES_CHECK_SPORT_1_PNG = 0x56000023,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\check_sport.png
    GUI_RES_DATE_PNG = 0x56000024,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\date.png
    GUI_RES_GRAVITY_SENSOR_PNG = 0x56000025,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\gravity_sensor.png
    GUI_RES_SOUND_PNG = 0x56000026,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\sound.png
    GUI_RES_STOPPING_MONITOR_1_PNG = 0x56000027,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\stopping_monitor.png
    GUI_RES_CAR_NUM_PNG = 0x56000028,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\car_num.png
    GUI_RES_HEADLIGHT_PNG = 0x56000029,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\headlight.png
    GUI_RES_VIDEO_1_PNG = 0x5600002A,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\main_page\video.png
    GUI_RES_VIDEO__ON_PNG = 0x5600002B,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\main_page\video__on.png
    GUI_RES_FILE_PNG = 0x5600002C,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\main_page\file.png
    GUI_RES_FILE_ON_PNG = 0x5600002D,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\main_page\file_on.png
    GUI_RES_SETTING_1_PNG = 0x5600002E,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\main_page\setting.png
    GUI_RES_SETTING_ON_PNG = 0x5600002F,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\main_page\setting_on.png
    GUI_RES_POP_UP_WINDOW_PNG = 0x56000030,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\pop_up_window.png
    GUI_RES_FLIG_ON_PNG = 0x56000031,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\flig_on.png
    GUI_RES_ASTERN_PNG = 0x56000032,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\astern.png
    GUI_RES_LCD_OFF_PNG = 0x56000033,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\sys_setting\icon\lcd_off.png
    GUI_RES_AUTO_OFF_PNG = 0x56000034,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\sys_setting\icon\auto_off.png
    GUI_RES_FREQUENCY_PNG = 0x56000035,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\sys_setting\icon\frequency.png
    GUI_RES_VOICE_PNG = 0x56000036,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\sys_setting\icon\voice.png
    GUI_RES_LANGUAGES_PNG = 0x56000037,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\sys_setting\icon\languages.png
    GUI_RES_SOFTWARE_PNG = 0x56000038,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\software.png
    GUI_RES_CAR_NUM_1_PNG = 0x56000039,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\sys_setting\icon\car_num.png
    GUI_RES_LANE_PNG = 0x5600003A,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\sys_setting\icon\lane.png
    GUI_RES_FLIG_PNG = 0x5600003B,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\sys_setting\icon\flig.png
    GUI_RES_FORMAT_PNG = 0x5600003C,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\sys_setting\icon\format.png
    GUI_RES_RESET_PNG = 0x5600003D,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\sys_setting\icon\reset.png
    GUI_RES_DATE_1_PNG = 0x5600003E,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\sys_setting\icon\date.png
    GUI_RES_VIDEO_2_PNG = 0x5600003F,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\sys_setting\left_tools\video.png
    GUI_RES_FILES_PNG = 0x56000040,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\sys_setting\left_tools\FILES.png
    GUI_RES_PHOTO_BUTTON_PNG = 0x56000041,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\photo_button.png
    GUI_RES_PHOTO_BUTTON_ON_PNG = 0x56000042,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\photo_button_on.png
    GUI_RES_TIMING_PHOTO_2_PNG = 0x56000043,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\timing_photo_2.png
    GUI_RES_CONTINUOUS_PNG = 0x56000044,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\continuous.png
    GUI_RES_HAND_SHAKE_PNG = 0x56000045,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\hand_shake.png
    GUI_RES_VIDEO_3_PNG = 0x56000046,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\left_tools\video.png
    GUI_RES_TIMING_PHOTO_PNG = 0x56000047,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\timing_photo.png
    GUI_RES_CONTINUOUS_PHOTO_PNG = 0x56000048,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\continuous_photo.png
    GUI_RES_PHOTO_QUALITY_PNG = 0x56000049,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\photo_quality.png
    GUI_RES_ACUITY_PNG = 0x5600004A,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\acuity.png
    GUI_RES_AWB_PNG = 0x5600004B,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\AWB.png
    GUI_RES_COLOR_PNG = 0x5600004C,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\color.png
    GUI_RES_ISO_PNG = 0x5600004D,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\ISO.png
    GUI_RES_HAND_SHAKE_1_PNG = 0x5600004E,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\hand_shake.png
    GUI_RES_QUICK_SCAN_PNG = 0x5600004F,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\quick_scan.png
    GUI_RES_HIGH_PNG = 0x56000050,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\high.png
    GUI_RES_AWB_1_PNG = 0x56000051,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\awb.png
    GUI_RES_VIDEO_PLAY_PNG = 0x56000052,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_play.png
    GUI_RES_VIDEO_PAUSE_PNG = 0x56000053,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_pause.png
    GUI_RES_VOLUMELOUDER_SOLID_1_PNG = 0x56000054,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\volumeLouder_solid_1.png
    GUI_RES_VOLUMEMUTE_SOLID_1_PNG = 0x56000055,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\volumeMute_solid_1.png
    GUI_RES_PHOTO_PNG = 0x56000056,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\PHOTO.png
    GUI_RES_PHOTO_ON_PNG = 0x56000057,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\photo_on.png
    GUI_RES_RETURN_PNG = 0x56000058,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\RETURN.png
    GUI_RES_RETURN_ON_PNG = 0x56000059,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\return_on.png
    GUI_RES_SKIP_PREVIOUS_PNG = 0x5600005A,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\skip_previous.png
    GUI_RES_SKIP_NEXT_PNG = 0x5600005B,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\skip_next.png
    GUI_RES_UP_PNG = 0x5600005C,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\up.png
    GUI_RES_DOWN_PNG = 0x5600005D,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\down.png
    GUI_RES_EDIT_PNG = 0x5600005E,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\EDIT.png
    GUI_RES_EDITOR_ON_PNG = 0x5600005F,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\editor_on.png
    GUI_RES_LOCK_1_PNG = 0x56000060,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\LOCK.png
    GUI_RES_LOCK_ON_PNG = 0x56000061,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\lock_on.png
    GUI_RES_HOME_1_PNG = 0x56000062,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\HOME.png
    GUI_RES_HOME_ON_PNG = 0x56000063,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\home_on.png
    GUI_RES_DELETE_PNG = 0x56000064,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\DELETE.png
    GUI_RES_DELETE_ON_PNG = 0x56000065,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\delete_on.png
} GUI_RES_ID;

typedef enum {
    RES_0 = 0xD6000000,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\battery\0.png 48x48
    RES_1 = 0xD6000001,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\battery\1.png 48x48
    RES_2 = 0xD6000002,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\battery\2.png 48x48
    RES_3 = 0xD6000003,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\battery\3.png 48x48
    RES_CHARGING = 0xD6000004,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\battery\charging.png 48x48
    RES_FULL = 0xD6000005,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\battery\full.png 48x48
    RES_CYCLIC_VIDEO_3 = 0xD6000006,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\cyclic_video_3.png 48x48
    RES_CYCLIC_VIDEO_10 = 0xD6000007,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\cyclic_video_10.png 48x48
    RES_CYCLIC_VIDEO_CLOSE = 0xD6000008,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\cyclic_video_close.png 48x48
    RES_GRAVITY_SENSOR_LOW = 0xD6000009,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\gravity_sensor_low.png 48x48
    RES_GRAVITY_SENSOR_MIDLLER = 0xD600000A,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\gravity_sensor_midller.png 48x48
    RES_GRAVITY_SENSOR_HIGH = 0xD600000B,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\gravity_sensor_high.png 48x48
    RES_INTERVAL_VIDEO_CLOSE = 0xD600000C,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\interval_video_close.png 48x48
    RES_INTERVAL_VIDEO_500 = 0xD600000D,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\interval_video_500.png 48x48
    RES_INTERVAL_VIDEO_200 = 0xD600000E,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\interval_video_200.png 48x48
    RES_INTERVAL_VIDEO_100 = 0xD600000F,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\interval_video_100.png 48x48
    RES_SD = 0xD6000010,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\SD.png 45x45
    RES_SD_CLOSE = 0xD6000011,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\SD_close.png 45x45
    RES_SOUND = 0xD6000012,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\sound.png 48x48
    RES_SOUND_CLOSE = 0xD6000013,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\sound_close.png 48x48
    RES_EXPOSURE = 0xD6000014,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\exposure.png 80x80
    RES_DOUBLE_VIDEO = 0xD6000015,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\double_video.png 80x80
    RES_DATE = 0xD6000016,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\date.png 80x80
    RES_CYCLIC_VIDEO = 0xD6000017,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\cyclic_video.png 80x80
    RES_CHECK_SPORT = 0xD6000018,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\check_sport.png 80x80
    RES_CAR_NUM = 0xD6000019,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\car_num.png 80x80
    RES_GRAVITY_SENSOR = 0xD600001A,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\gravity_sensor.png 80x80
    RES_HDR = 0xD600001B,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\HDR.png 80x80
    RES_INTERVAL_VIDEO = 0xD600001C,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\interval_video.png 80x80
    RES_RESOLUTION_RATIO = 0xD600001D,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\resolution_ratio.png 80x80
    RES_SOUND_1 = 0xD600001E,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\sound.png 80x80
    RES_STOPPING_MONITOR = 0xD600001F,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\stopping_monitor.png 80x80
    RES_AUTO_OFF = 0xD6000020,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\sys_setting\icon\auto_off.png 80x80
    RES_CAR_NUM_1 = 0xD6000021,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\sys_setting\icon\car_num.png 80x80
    RES_FLIG = 0xD6000022,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\sys_setting\icon\flig.png 80x80
    RES_FORMAT = 0xD6000023,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\sys_setting\icon\format.png 80x80
    RES_FREQUENCY = 0xD6000024,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\sys_setting\icon\frequency.png 80x80
    RES_LANE = 0xD6000025,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\sys_setting\icon\lane.png 80x80
    RES_LANGUAGES = 0xD6000026,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\sys_setting\icon\languages.png 80x80
    RES_LCD_OFF = 0xD6000027,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\sys_setting\icon\lcd_off.png 80x80
    RES_RESET = 0xD6000028,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\sys_setting\icon\reset.png 80x80
    RES_VERSION = 0xD6000029,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\sys_setting\icon\version.png 80x80
    RES_VOICE = 0xD600002A,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\sys_setting\icon\voice.png 80x80
    RES_DATE_1 = 0xD600002B,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\sys_setting\icon\date.png 80x80
    RES_AWB = 0xD600002C,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\awb.png 48x48
    RES_AWB_FLUORESCENT_LAMP = 0xD600002D,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\awb_fluorescent_lamp.png 48x48
    RES_AWB_OSRAM_LAMP = 0xD600002E,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\awb_osram_lamp.png 48x48
    RES_AWB_SUN_CLOUDY = 0xD600002F,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\awb_sun_cloudy.png 48x48
    RES_AWB_SUN_LIGHT = 0xD6000030,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\awb_sun_light.png 48x48
    RES_HIGH = 0xD6000031,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\high.png 48x48
    RES_LOW = 0xD6000032,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\low.png 48x48
    RES_MIDDLE = 0xD6000033,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\middle.png 48x48
    RES_TIMING_PHOTO_2 = 0xD6000034,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\timing_photo_2.png 48x48
    RES_TIMING_PHOTO_5 = 0xD6000035,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\timing_photo_5.png 48x48
    RES_TIMING_PHOTO_10 = 0xD6000036,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\timing_photo_10.png 48x48
    RES_FILE_DIR = 0xD6000037,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\file_dir.png 160x160
    RES_DELETE = 0xD6000038,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\DELETE.png 48x48
    RES_DELETE_ON = 0xD6000039,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\delete_on.png 48x48
    RES_EDIT = 0xD600003A,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\EDIT.png 48x48
    RES_EDITOR_ON = 0xD600003B,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\editor_on.png 48x48
    RES_HOME = 0xD600003C,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\HOME.png 48x48
    RES_HOME_ON = 0xD600003D,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\home_on.png 48x48
    RES_LOCK = 0xD600003E,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\LOCK.png 48x48
    RES_LOCK_ON = 0xD600003F,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\lock_on.png 48x48
    RES_PHOTO = 0xD6000040,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\PHOTO.png 48x48
    RES_PHOTO_ON = 0xD6000041,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\photo_on.png 48x48
    RES_RETURN = 0xD6000042,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\RETURN.png 48x48
    RES_RETURN_ON = 0xD6000043,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\return_on.png 48x48
    RES_SELETE = 0xD6000044,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\SELETE.png 48x48
    RES_UNLOCK = 0xD6000045,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\UNLOCK.png 48x48
    RES_UNLOCK_ON = 0xD6000046,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\unlock_on.png 48x48
    RES_VIDEO = 0xD6000047,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\VIDEO.png 48x48
    RES_VOLUMELOUDER_SOLID_1 = 0xD6000048,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\volumeLouder_solid_1.png 48x48
    RES_VIDEO_PAUSE = 0xD6000049,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_pause.png 48x48
    RES_SKIP_NEXT = 0xD600004A,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\skip_next.png 48x48
    RES_SKIP_PREVIOUS = 0xD600004B,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\skip_previous.png 48x48
    RES_PLAY = 0xD600004C,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\play.png 32x32
    RES_VIDEO_PLAY = 0xD600004D,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_play.png 48x48
    RES_VOLUMEMUTE_SOLID_1 = 0xD600004E,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\volumeMute_solid_1.png 48x48
    RES_SOFTWARE = 0xD600004F,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\software.png 80x80
    RES_CYCLIC_VIDEO_1 = 0xD6000050,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\cyclic_video_1.png 48x48
    RES_LOCK_FLAG = 0xD6000051,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\lock_flag.png 24x24
    RES_CONNECTED = 0xD6000052,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\connected.png 45x45
    RES_DISCONNECT = 0xD6000053,   //E:\1111\ac792\ui_prj\dvr_800x480\import\image\video_page\menu_icon\disconnect.png 45x45
} RES_ID;

extern char *gui_get_res_path(int32_t id);

#ifdef __cplusplus
}
#endif
#endif

#endif
