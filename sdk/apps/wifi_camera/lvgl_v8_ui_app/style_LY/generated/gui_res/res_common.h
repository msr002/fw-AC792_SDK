#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE
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
    GUI_RES_FANGZHENGKAITIJIANTI_1_22_TTF = 0x10000000,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\sdk\ui_res\rle\font\10000000.rle
    GUI_RES_FANGZHENGKAITIJIANTI_1_26_TTF = 0x10000001,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\sdk\ui_res\rle\font\10000001.rle
    GUI_RES_FANGZHENGKAITIJIANTI_1_18_TTF = 0x10000002,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\sdk\ui_res\rle\font\10000002.rle
    GUI_RES_MONTSERRATMEDIUM_18_TTF = 0x10000003,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\sdk\ui_res\rle\font\10000003.rle
    GUI_RES_FANGZHENGKAITIJIANTI_1_48_TTF = 0x10000004,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\sdk\ui_res\rle\font\10000004.rle
    GUI_RES_MONTSERRATMEDIUM_24_TTF = 0x10000005,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\sdk\ui_res\rle\font\10000005.rle
    GUI_RES_MONTSERRATMEDIUM_12_TTF = 0x10000006,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\sdk\ui_res\rle\font\10000006.rle
    GUI_RES_MONTSERRATMEDIUM_22_TTF = 0x10000007,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\sdk\ui_res\rle\font\10000007.rle
    GUI_RES_FANGZHENGKAITIJIANTI_1_24_TTF = 0x10000008,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\sdk\ui_res\rle\font\10000008.rle
    GUI_RES_FANGZHENGKAITIJIANTI_1_16_TTF = 0x10000009,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\sdk\ui_res\rle\font\10000009.rle
    GUI_RES_MONTSERRATMEDIUM_16_TTF = 0x1000000A,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\sdk\ui_res\rle\font\1000000a.rle

    GUI_RES_S_PC_PNG = 0x56000000,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\video_page\USB\s_PC.png
    GUI_RES_S_MASS_PNG = 0x56000001,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\video_page\USB\s_MASS.png
    GUI_RES_I_REC_PNG = 0x56000002,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\i_rec.png
    GUI_RES_CYCLIC_VIDEO_3_PNG = 0x56000003,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\cyclic_video_3.png
    GUI_RES_EXP_A0_PNG = 0x56000004,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\exp_a0.png
    GUI_RES_I_MOT_PNG = 0x56000005,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\i_mot.png
    GUI_RES_I_TEAR_PNG = 0x56000006,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\i_tear.png
    GUI_RES_MIC_ON_PNG = 0x56000007,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\mic_on.png
    GUI_RES_I_HDR_PNG = 0x56000008,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\i_hdr.png
    GUI_RES_I_GRA_L_PNG = 0x56000009,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\i_gra_l.png
    GUI_RES_PARK_PNG = 0x5600000A,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\park.png
    GUI_RES_BAT_FULL_PNG = 0x5600000B,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\bat_full.png
    GUI_RES_CARD_ONLINE_PNG = 0x5600000C,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\card_online.png
    GUI_RES_RED_CIRCLE_PNG = 0x5600000D,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\red_circle.png
    GUI_RES_FLIG_ON_PNG = 0x5600000E,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\flig_on.png
    GUI_RES_KEY_PNG = 0x5600000F,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\key.png
    GUI_RES_M_SOLU_PNG = 0x56000010,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_menu\m_solu.png
    GUI_RES_M_TWO_REC_PNG = 0x56000011,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_menu\m_two_rec.png
    GUI_RES_M_CYC_PNG = 0x56000012,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_menu\m_cyc.png
    GUI_RES_REC_NOCYC_PNG = 0x56000013,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_menu\rec_nocyc.png
    GUI_RES_M_HDR_PNG = 0x56000014,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_menu\m_hdr.png
    GUI_RES_M_EXP_PNG = 0x56000015,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_menu\m_exp.png
    GUI_RES_M_MOT_PNG = 0x56000016,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_menu\m_mot.png
    GUI_RES_M_AUD_PNG = 0x56000017,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_menu\m_aud.png
    GUI_RES_M_DAT_PNG = 0x56000018,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_menu\m_dat.png
    GUI_RES_M_GRA_PNG = 0x56000019,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_menu\m_gra.png
    GUI_RES_M_PARK_PNG = 0x5600001A,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_menu\m_park.png
    GUI_RES_M_NUM_PNG = 0x5600001B,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_menu\m_num.png
    GUI_RES_M_FLIG_PNG = 0x5600001C,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_menu\m_flig.png
    GUI_RES_MENU_STA_PNG = 0x5600001D,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_menu\menu_sta.png
    GUI_RES_REC_PNG = 0x5600001E,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_menu\rec.png
    GUI_RES_SET_PNG = 0x5600001F,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_menu\set.png
    GUI_RES_LEFT_PNG = 0x56000020,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\direc\left.png
    GUI_RES_UP_PNG = 0x56000021,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\direc\up.png
    GUI_RES_DOWN_PNG = 0x56000022,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\direc\down.png
    GUI_RES_RIGHT_PNG = 0x56000023,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\direc\right.png
    GUI_RES_POP_UP_WINDOW_PNG = 0x56000024,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\video_page\pop_up_window.png
    GUI_RES_FLIG_ON_1_PNG = 0x56000025,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\video_page\flig_on.png
    GUI_RES_ASTERN_PNG = 0x56000026,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\video_page\astern.png
    GUI_RES_LCD_AU_PNG = 0x56000027,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\sys_menu\lcd_au.png
    GUI_RES_AUTO_OFF_PNG = 0x56000028,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\sys_menu\auto_off.png
    GUI_RES_HZ_PNG = 0x56000029,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\sys_menu\hz.png
    GUI_RES_KEY_V_PNG = 0x5600002A,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\sys_menu\key_v.png
    GUI_RES_LANGUAGE_PNG = 0x5600002B,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\sys_menu\language.png
    GUI_RES_TIME_PNG = 0x5600002C,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\sys_menu\time.png
    GUI_RES_TV_PNG = 0x5600002D,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\sys_menu\tv.png
    GUI_RES_MDK_PNG = 0x5600002E,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\sys_menu\mdk.png
    GUI_RES_DEF_SET_PNG = 0x5600002F,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\sys_menu\def_set.png
    GUI_RES_VERSION_PNG = 0x56000030,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\sys_menu\version.png
    GUI_RES_NUM_L_PNG = 0x56000031,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\sys_menu\NUM_l.png
    GUI_RES_NUM_D_PNG = 0x56000032,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\sys_menu\NUM_d.png
    GUI_RES_TP_3_PNG = 0x56000033,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\photo\photo_scan\tp_3.png
    GUI_RES_TP_PNG = 0x56000034,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\photo\photo_scan\tp.png
    GUI_RES_AWB_AUTO_PNG = 0x56000035,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\photo\photo_scan\awb_auto.png
    GUI_RES_ISO_AUTO_PNG = 0x56000036,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\photo\photo_scan\iso_auto.png
    GUI_RES_Q1_PNG = 0x56000037,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\photo\photo_scan\q1.png
    GUI_RES_DL2_PNG = 0x56000038,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\photo\photo_scan\dl2.png
    GUI_RES_SHAKE_OFF_PNG = 0x56000039,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\photo\photo_scan\shake_off.png
    GUI_RES_LIANP_PNG = 0x5600003A,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\photo\photo_scan\lianp.png
    GUI_RES_PAIZ_PNG = 0x5600003B,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\photo\photo_menu\paiz.png
    GUI_RES_LIANP_1_PNG = 0x5600003C,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\photo\photo_menu\lianp.png
    GUI_RES_IMG_Q_PNG = 0x5600003D,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\photo\photo_menu\img_q.png
    GUI_RES_RUIDU_PNG = 0x5600003E,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\photo\photo_menu\ruidu.png
    GUI_RES_COLOR_PNG = 0x5600003F,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\photo\photo_menu\color.png
    GUI_RES_ISO_PNG = 0x56000040,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\photo\photo_menu\iso.png
    GUI_RES_SHAKE_PNG = 0x56000041,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\photo\photo_menu\shake.png
    GUI_RES_SCAN_PNG = 0x56000042,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\photo\photo_menu\scan.png
    GUI_RES_PHOTO_PNG = 0x56000043,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_menu\photo.png
    GUI_RES_VIDEO_PLAY_PNG = 0x56000044,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\video_play.png
    GUI_RES_VIDEO_PAUSE_PNG = 0x56000045,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\video_pause.png
    GUI_RES_SKIP_PREVIOUS_PNG = 0x56000046,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\skip_previous.png
    GUI_RES_SKIP_NEXT_PNG = 0x56000047,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\skip_next.png
    GUI_RES_VOLUMELOUDER_SOLID_1_PNG = 0x56000048,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\volumeLouder_solid_1.png
    GUI_RES_VOLUMEMUTE_SOLID_1_PNG = 0x56000049,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\volumeMute_solid_1.png
    GUI_RES_PHOTO_1_PNG = 0x5600004A,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\PHOTO.png
    GUI_RES_PHOTO_ON_PNG = 0x5600004B,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\photo_on.png
    GUI_RES_UP_1_PNG = 0x5600004C,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\up.png
    GUI_RES_DOWN_1_PNG = 0x5600004D,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\down.png
    GUI_RES_DELET_PNG = 0x5600004E,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\dec\delet.png
    GUI_RES_PROTECT_PNG = 0x5600004F,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\dec\protect.png
    GUI_RES_PLAY_PNG = 0x56000050,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_menu\play.png
} GUI_RES_ID;

typedef enum {
    RES_0 = 0xD6000000,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\video_page\battery\0.png 48x48
    RES_1 = 0xD6000001,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\video_page\battery\1.png 48x48
    RES_2 = 0xD6000002,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\video_page\battery\2.png 48x48
    RES_3 = 0xD6000003,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\video_page\battery\3.png 48x48
    RES_CHARGING = 0xD6000004,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\video_page\battery\charging.png 48x48
    RES_FULL = 0xD6000005,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\video_page\battery\full.png 48x48
    RES_GRAVITY_SENSOR_LOW = 0xD6000006,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\video_page\gravity_sensor_low.png 48x48
    RES_GRAVITY_SENSOR_MIDLLER = 0xD6000007,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\video_page\gravity_sensor_midller.png 48x48
    RES_GRAVITY_SENSOR_HIGH = 0xD6000008,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\video_page\gravity_sensor_high.png 48x48
    RES_INTERVAL_VIDEO_CLOSE = 0xD6000009,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\video_page\interval_video_close.png 48x48
    RES_INTERVAL_VIDEO_500 = 0xD600000A,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\video_page\interval_video_500.png 48x48
    RES_INTERVAL_VIDEO_200 = 0xD600000B,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\video_page\interval_video_200.png 48x48
    RES_INTERVAL_VIDEO_100 = 0xD600000C,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\video_page\interval_video_100.png 48x48
    RES_SD = 0xD600000D,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\video_page\SD.png 45x45
    RES_SD_CLOSE = 0xD600000E,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\video_page\SD_close.png 45x45
    RES_SOUND = 0xD600000F,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\video_page\sound.png 48x48
    RES_SOUND_CLOSE = 0xD6000010,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\video_page\sound_close.png 48x48
    RES_EXPOSURE = 0xD6000011,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\video_page\menu_icon\exposure.png 80x80
    RES_DOUBLE_VIDEO = 0xD6000012,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\video_page\menu_icon\double_video.png 80x80
    RES_DATE = 0xD6000013,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\video_page\menu_icon\date.png 80x80
    RES_CYCLIC_VIDEO = 0xD6000014,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\video_page\menu_icon\cyclic_video.png 80x80
    RES_CHECK_SPORT = 0xD6000015,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\video_page\menu_icon\check_sport.png 80x80
    RES_CAR_NUM = 0xD6000016,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\video_page\menu_icon\car_num.png 80x80
    RES_GRAVITY_SENSOR = 0xD6000017,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\video_page\menu_icon\gravity_sensor.png 80x80
    RES_HDR = 0xD6000018,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\video_page\menu_icon\HDR.png 80x80
    RES_INTERVAL_VIDEO = 0xD6000019,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\video_page\menu_icon\interval_video.png 80x80
    RES_RESOLUTION_RATIO = 0xD600001A,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\video_page\menu_icon\resolution_ratio.png 80x80
    RES_SOUND_1 = 0xD600001B,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\video_page\menu_icon\sound.png 80x80
    RES_STOPPING_MONITOR = 0xD600001C,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\video_page\menu_icon\stopping_monitor.png 80x80
    RES_AUTO_OFF = 0xD600001D,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\video_page\sys_setting\icon\auto_off.png 80x80
    RES_CAR_NUM_1 = 0xD600001E,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\video_page\sys_setting\icon\car_num.png 80x80
    RES_FLIG = 0xD600001F,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\video_page\sys_setting\icon\flig.png 80x80
    RES_FORMAT = 0xD6000020,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\video_page\sys_setting\icon\format.png 80x80
    RES_FREQUENCY = 0xD6000021,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\video_page\sys_setting\icon\frequency.png 80x80
    RES_LANE = 0xD6000022,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\video_page\sys_setting\icon\lane.png 80x80
    RES_LANGUAGES = 0xD6000023,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\video_page\sys_setting\icon\languages.png 80x80
    RES_LCD_OFF = 0xD6000024,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\video_page\sys_setting\icon\lcd_off.png 80x80
    RES_RESET = 0xD6000025,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\video_page\sys_setting\icon\reset.png 80x80
    RES_VERSION = 0xD6000026,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\video_page\sys_setting\icon\version.png 80x80
    RES_VOICE = 0xD6000027,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\video_page\sys_setting\icon\voice.png 80x80
    RES_DATE_1 = 0xD6000028,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\video_page\sys_setting\icon\date.png 80x80
    RES_AWB = 0xD6000029,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\video_page\awb.png 48x48
    RES_AWB_FLUORESCENT_LAMP = 0xD600002A,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\video_page\awb_fluorescent_lamp.png 48x48
    RES_AWB_OSRAM_LAMP = 0xD600002B,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\video_page\awb_osram_lamp.png 48x48
    RES_AWB_SUN_CLOUDY = 0xD600002C,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\video_page\awb_sun_cloudy.png 48x48
    RES_AWB_SUN_LIGHT = 0xD600002D,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\video_page\awb_sun_light.png 48x48
    RES_HIGH = 0xD600002E,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\video_page\high.png 48x48
    RES_LOW = 0xD600002F,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\video_page\low.png 48x48
    RES_MIDDLE = 0xD6000030,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\video_page\middle.png 48x48
    RES_TIMING_PHOTO_2 = 0xD6000031,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\video_page\timing_photo_2.png 48x48
    RES_TIMING_PHOTO_5 = 0xD6000032,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\video_page\timing_photo_5.png 48x48
    RES_TIMING_PHOTO_10 = 0xD6000033,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\video_page\timing_photo_10.png 48x48
    RES_FILE_DIR = 0xD6000034,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\file_dir.png 160x160
    RES_DELETE = 0xD6000035,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\DELETE.png 48x48
    RES_DELETE_ON = 0xD6000036,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\delete_on.png 48x48
    RES_EDIT = 0xD6000037,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\EDIT.png 48x48
    RES_EDITOR_ON = 0xD6000038,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\editor_on.png 48x48
    RES_HOME = 0xD6000039,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\HOME.png 48x48
    RES_HOME_ON = 0xD600003A,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\home_on.png 48x48
    RES_LOCK = 0xD600003B,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LOCK.png 48x48
    RES_LOCK_ON = 0xD600003C,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\lock_on.png 48x48
    RES_PHOTO = 0xD600003D,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\PHOTO.png 48x48
    RES_PHOTO_ON = 0xD600003E,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\photo_on.png 48x48
    RES_RETURN = 0xD600003F,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\RETURN.png 48x48
    RES_RETURN_ON = 0xD6000040,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\return_on.png 48x48
    RES_SELETE = 0xD6000041,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\SELETE.png 48x48
    RES_UNLOCK = 0xD6000042,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\UNLOCK.png 48x48
    RES_UNLOCK_ON = 0xD6000043,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\unlock_on.png 48x48
    RES_VIDEO = 0xD6000044,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\VIDEO.png 48x48
    RES_VOLUMELOUDER_SOLID_1 = 0xD6000045,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\volumeLouder_solid_1.png 48x48
    RES_VIDEO_PAUSE = 0xD6000046,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\video_pause.png 48x48
    RES_SKIP_NEXT = 0xD6000047,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\skip_next.png 48x48
    RES_SKIP_PREVIOUS = 0xD6000048,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\skip_previous.png 48x48
    RES_PLAY = 0xD6000049,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\play.png 32x32
    RES_VIDEO_PLAY = 0xD600004A,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\video_play.png 48x48
    RES_VOLUMEMUTE_SOLID_1 = 0xD600004B,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\volumeMute_solid_1.png 48x48
    RES_SOFTWARE = 0xD600004C,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\video_page\menu_icon\software.png 80x80
    RES_LOCK_FLAG = 0xD600004D,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\lock_flag.png 24x24
    RES_CYCLIC_VIDEO_10 = 0xD600004E,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\cyclic_video_10.png 29x31
    RES_CYCLIC_VIDEO_3 = 0xD600004F,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\cyclic_video_3.png 29x31
    RES_CYCLIC_VIDEO_5 = 0xD6000050,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\cyclic_video_5.png 29x31
    RES_MIC_OFF = 0xD6000051,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\mic_off.png 26x29
    RES_MIC_ON = 0xD6000052,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\mic_on.png 26x29
    RES_I_GRA_H = 0xD6000053,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\i_gra_h.png 34x31
    RES_I_GRA_M = 0xD6000054,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\i_gra_m.png 34x31
    RES_I_GRA_L = 0xD6000055,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\i_gra_l.png 34x31
    RES_BAT_0 = 0xD6000056,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\bat_0.png 25x15
    RES_BAT_L = 0xD6000057,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\bat_l.png 25x15
    RES_BAT_HALF = 0xD6000058,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\bat_half.png 25x15
    RES_BAT_H = 0xD6000059,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\bat_h.png 25x15
    RES_CHAR = 0xD600005A,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\char.png 25x15
    RES_CARD_OFFLINE = 0xD600005B,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\card_offline.png 29x29
    RES_CARD_ONLINE = 0xD600005C,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\card_online.png 29x29
    RES_PARK = 0xD600005D,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\park.png 16x13
    RES_EXP_A3 = 0xD600005E,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\exp_a3.png 29x29
    RES_EXP_A2 = 0xD600005F,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\exp_a2.png 29x29
    RES_EXP_A1 = 0xD6000060,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\exp_a1.png 29x29
    RES_EXP_A0 = 0xD6000061,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\exp_a0.png 29x29
    RES_EXP_D1 = 0xD6000062,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\exp_d1.png 29x29
    RES_EXP_D2 = 0xD6000063,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\exp_d2.png 29x29
    RES_EXP_D3 = 0xD6000064,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\exp_d3.png 29x29
    RES_AWB_AUTO = 0xD6000065,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\photo\photo_scan\awb_auto.png 29x29
    RES_AWB_CLOUDY = 0xD6000066,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\photo\photo_scan\awb_cloudy.png 29x29
    RES_AWB_FINE = 0xD6000067,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\photo\photo_scan\awb_fine.png 29x29
    RES_AWB_FLUORESCENT_LAMP_1 = 0xD6000068,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\photo\photo_scan\awb_fluorescent_lamp.png 29x29
    RES_AWB_TUNGSTEN_LAMP = 0xD6000069,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\photo\photo_scan\awb_tungsten_lamp.png 29x29
    RES_ISO_1 = 0xD600006A,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\photo\photo_scan\iso_1.png 29x29
    RES_ISO_2 = 0xD600006B,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\photo\photo_scan\iso_2.png 29x29
    RES_ISO_4 = 0xD600006C,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\photo\photo_scan\iso_4.png 29x29
    RES_ISO_AUTO = 0xD600006D,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\photo\photo_scan\iso_auto.png 29x29
    RES_Q1 = 0xD600006E,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\photo\photo_scan\q1.png 29x29
    RES_Q2 = 0xD600006F,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\photo\photo_scan\q2.png 29x29
    RES_Q3 = 0xD6000070,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\photo\photo_scan\q3.png 29x29
    RES_DL2 = 0xD6000071,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\photo\photo_scan\dl2.png 29x29
    RES_DL5 = 0xD6000072,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\photo\photo_scan\dl5.png 29x29
    RES_DL10 = 0xD6000073,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\photo\photo_scan\dl10.png 29x29
    RES_SHAKE_OFF = 0xD6000074,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\photo\photo_scan\shake_off.png 29x29
    RES_SHAKE_ON = 0xD6000075,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\photo\photo_scan\shake_on.png 29x29
    RES_BAT_FULL = 0xD6000076,   //D:\gitlab\ac792\ui_prj\dvr_ly_800x480\import\image\LY_UI\rec\rec_scan\bat_full.png 25x15
} RES_ID;

extern char *gui_get_res_path(int32_t id);

#ifdef __cplusplus
}
#endif
#endif

#endif
