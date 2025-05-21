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

#define CONV_RES_ID(id) (((id) >> 24) | ((id) & 0x00FFFFFF) << 8)
typedef enum {
    GUI_RES_FANGZHENGKAITIJIANTI_1_22_TTF = 0x35000000,   //E:\1111\ac792\ui_prj\Application12\sdk\ui_res\flash\rle\font\35000000.rle
    GUI_RES_FANGZHENGKAITIJIANTI_1_26_TTF = 0x35000001,   //E:\1111\ac792\ui_prj\Application12\sdk\ui_res\flash\rle\font\35000001.rle
    GUI_RES_FANGZHENGKAITIJIANTI_1_18_TTF = 0x35000002,   //E:\1111\ac792\ui_prj\Application12\sdk\ui_res\flash\rle\font\35000002.rle
    GUI_RES_MONTSERRATMEDIUM_18_TTF = 0x35000003,   //E:\1111\ac792\ui_prj\Application12\sdk\ui_res\flash\rle\font\35000003.rle
    GUI_RES_FANGZHENGKAITIJIANTI_1_48_TTF = 0x35000004,   //E:\1111\ac792\ui_prj\Application12\sdk\ui_res\flash\rle\font\35000004.rle
    GUI_RES_MONTSERRATMEDIUM_24_TTF = 0x35000005,   //E:\1111\ac792\ui_prj\Application12\sdk\ui_res\flash\rle\font\35000005.rle
    GUI_RES_MONTSERRATMEDIUM_12_TTF = 0x35000006,   //E:\1111\ac792\ui_prj\Application12\sdk\ui_res\flash\rle\font\35000006.rle
    GUI_RES_MONTSERRATMEDIUM_22_TTF = 0x35000007,   //E:\1111\ac792\ui_prj\Application12\sdk\ui_res\flash\rle\font\35000007.rle
    GUI_RES_FANGZHENGKAITIJIANTI_1_24_TTF = 0x35000008,   //E:\1111\ac792\ui_prj\Application12\sdk\ui_res\flash\rle\font\35000008.rle
    GUI_RES_FANGZHENGKAITIJIANTI_1_16_TTF = 0x35000009,   //E:\1111\ac792\ui_prj\Application12\sdk\ui_res\flash\rle\font\35000009.rle
    GUI_RES_MONTSERRATMEDIUM_16_TTF = 0x3500000A,   //E:\1111\ac792\ui_prj\Application12\sdk\ui_res\flash\rle\font\3500000a.rle
    GUI_RES_MONTSERRATMEDIUM_20_TTF = 0x3500000B,   //E:\1111\ac792\ui_prj\Application12\sdk\ui_res\flash\rle\font\3500000b.rle

    GUI_RES_S_PC_PNG = 0x4B00000C,   //E:\1111\ac792\ui_prj\Application12\import\image\video_page\USB\s_PC.png
    GUI_RES_S_MASS_PNG = 0x4B00000D,   //E:\1111\ac792\ui_prj\Application12\import\image\video_page\USB\s_MASS.png
    GUI_RES_I_REC_PNG = 0x4B00000E,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\rec\rec_scan\i_rec.png
    GUI_RES_CYCLIC_VIDEO_3_PNG = 0x4B00000F,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\rec\rec_scan\cyclic_video_3.png
    GUI_RES_EXP_A0_PNG = 0x4B000010,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\rec\rec_scan\exp_a0.png
    GUI_RES_I_MOT_PNG = 0x4B000011,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\rec\rec_scan\i_mot.png
    GUI_RES_I_TEAR_PNG = 0x4B000012,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\rec\rec_scan\i_tear.png
    GUI_RES_MIC_ON_PNG = 0x4B000013,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\rec\rec_scan\mic_on.png
    GUI_RES_I_HDR_PNG = 0x4B000014,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\rec\rec_scan\i_hdr.png
    GUI_RES_I_GRA_L_PNG = 0x4B000015,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\rec\rec_scan\i_gra_l.png
    GUI_RES_PARK_PNG = 0x4B000016,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\rec\rec_scan\park.png
    GUI_RES_BAT_FULL_PNG = 0x4B000017,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\rec\rec_scan\bat_full.png
    GUI_RES_CARD_ONLINE_PNG = 0x4B000018,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\rec\rec_scan\card_online.png
    GUI_RES_RED_CIRCLE_PNG = 0x4B000019,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\rec\rec_scan\red_circle.png
    GUI_RES_FLIG_ON_PNG = 0x4B00001A,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\rec\rec_scan\flig_on.png
    GUI_RES_KEY_PNG = 0x4B00001B,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\rec\rec_scan\key.png
    GUI_RES_M_SOLU_PNG = 0x4B00001C,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\rec\rec_menu\m_solu.png
    GUI_RES_M_TWO_REC_PNG = 0x4B00001D,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\rec\rec_menu\m_two_rec.png
    GUI_RES_M_CYC_PNG = 0x4B00001E,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\rec\rec_menu\m_cyc.png
    GUI_RES_REC_NOCYC_PNG = 0x4B00001F,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\rec\rec_menu\rec_nocyc.png
    GUI_RES_M_HDR_PNG = 0x4B000020,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\rec\rec_menu\m_hdr.png
    GUI_RES_M_EXP_PNG = 0x4B000021,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\rec\rec_menu\m_exp.png
    GUI_RES_M_MOT_PNG = 0x4B000022,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\rec\rec_menu\m_mot.png
    GUI_RES_M_AUD_PNG = 0x4B000023,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\rec\rec_menu\m_aud.png
    GUI_RES_M_DAT_PNG = 0x4B000024,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\rec\rec_menu\m_dat.png
    GUI_RES_M_GRA_PNG = 0x4B000025,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\rec\rec_menu\m_gra.png
    GUI_RES_M_PARK_PNG = 0x4B000026,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\rec\rec_menu\m_park.png
    GUI_RES_M_NUM_PNG = 0x4B000027,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\rec\rec_menu\m_num.png
    GUI_RES_M_FLIG_PNG = 0x4B000028,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\rec\rec_menu\m_flig.png
    GUI_RES_MENU_STA_PNG = 0x4B000029,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\rec\rec_menu\menu_sta.png
    GUI_RES_REC_PNG = 0x4B00002A,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\rec\rec_menu\rec.png
    GUI_RES_SET_PNG = 0x4B00002B,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\rec\rec_menu\set.png
    GUI_RES_LEFT_PNG = 0x4B00002C,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\direc\left.png
    GUI_RES_UP_PNG = 0x4B00002D,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\direc\up.png
    GUI_RES_DOWN_PNG = 0x4B00002E,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\direc\down.png
    GUI_RES_RIGHT_PNG = 0x4B00002F,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\direc\right.png
    GUI_RES_POP_UP_WINDOW_PNG = 0x4B000030,   //E:\1111\ac792\ui_prj\Application12\import\image\video_page\pop_up_window.png
    GUI_RES_FLIG_ON_1_PNG = 0x4B000031,   //E:\1111\ac792\ui_prj\Application12\import\image\video_page\flig_on.png
    GUI_RES_ASTERN_PNG = 0x4B000032,   //E:\1111\ac792\ui_prj\Application12\import\image\video_page\astern.png
    GUI_RES_LCD_AU_PNG = 0x4B000033,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\sys_menu\lcd_au.png
    GUI_RES_AUTO_OFF_PNG = 0x4B000034,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\sys_menu\auto_off.png
    GUI_RES_HZ_PNG = 0x4B000035,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\sys_menu\hz.png
    GUI_RES_KEY_V_PNG = 0x4B000036,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\sys_menu\key_v.png
    GUI_RES_LANGUAGE_PNG = 0x4B000037,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\sys_menu\language.png
    GUI_RES_TIME_PNG = 0x4B000038,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\sys_menu\time.png
    GUI_RES_TV_PNG = 0x4B000039,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\sys_menu\tv.png
    GUI_RES_MDK_PNG = 0x4B00003A,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\sys_menu\mdk.png
    GUI_RES_DEF_SET_PNG = 0x4B00003B,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\sys_menu\def_set.png
    GUI_RES_VERSION_PNG = 0x4B00003C,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\sys_menu\version.png
    GUI_RES_NUM_L_PNG = 0x4B00003D,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\sys_menu\NUM_l.png
    GUI_RES_NUM_D_PNG = 0x4B00003E,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\sys_menu\NUM_d.png
    GUI_RES_TP_3_PNG = 0x4B00003F,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\photo\photo_scan\tp_3.png
    GUI_RES_TP_PNG = 0x4B000040,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\photo\photo_scan\tp.png
    GUI_RES_AWB_AUTO_PNG = 0x4B000041,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\photo\photo_scan\awb_auto.png
    GUI_RES_ISO_AUTO_PNG = 0x4B000042,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\photo\photo_scan\iso_auto.png
    GUI_RES_Q1_PNG = 0x4B000043,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\photo\photo_scan\q1.png
    GUI_RES_DL2_PNG = 0x4B000044,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\photo\photo_scan\dl2.png
    GUI_RES_SHAKE_OFF_PNG = 0x4B000045,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\photo\photo_scan\shake_off.png
    GUI_RES_LIANP_PNG = 0x4B000046,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\photo\photo_scan\lianp.png
    GUI_RES_PAIZ_PNG = 0x4B000047,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\photo\photo_menu\paiz.png
    GUI_RES_LIANP_1_PNG = 0x4B000048,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\photo\photo_menu\lianp.png
    GUI_RES_IMG_Q_PNG = 0x4B000049,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\photo\photo_menu\img_q.png
    GUI_RES_RUIDU_PNG = 0x4B00004A,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\photo\photo_menu\ruidu.png
    GUI_RES_COLOR_PNG = 0x4B00004B,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\photo\photo_menu\color.png
    GUI_RES_ISO_PNG = 0x4B00004C,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\photo\photo_menu\iso.png
    GUI_RES_SHAKE_PNG = 0x4B00004D,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\photo\photo_menu\shake.png
    GUI_RES_SCAN_PNG = 0x4B00004E,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\photo\photo_menu\scan.png
    GUI_RES_PHOTO_PNG = 0x4B00004F,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\rec\rec_menu\photo.png
    GUI_RES_VIDEO_PLAY_PNG = 0x4B000050,   //E:\1111\ac792\ui_prj\Application12\import\image\video_play.png
    GUI_RES_VIDEO_PAUSE_PNG = 0x4B000051,   //E:\1111\ac792\ui_prj\Application12\import\image\video_pause.png
    GUI_RES_SKIP_PREVIOUS_PNG = 0x4B000052,   //E:\1111\ac792\ui_prj\Application12\import\image\skip_previous.png
    GUI_RES_SKIP_NEXT_PNG = 0x4B000053,   //E:\1111\ac792\ui_prj\Application12\import\image\skip_next.png
    GUI_RES_VOLUMELOUDER_SOLID_1_PNG = 0x4B000054,   //E:\1111\ac792\ui_prj\Application12\import\image\volumeLouder_solid_1.png
    GUI_RES_VOLUMEMUTE_SOLID_1_PNG = 0x4B000055,   //E:\1111\ac792\ui_prj\Application12\import\image\volumeMute_solid_1.png
    GUI_RES_PHOTO_1_PNG = 0x4B000056,   //E:\1111\ac792\ui_prj\Application12\import\image\PHOTO.png
    GUI_RES_PHOTO_ON_PNG = 0x4B000057,   //E:\1111\ac792\ui_prj\Application12\import\image\photo_on.png
    GUI_RES_UP_1_PNG = 0x4B000058,   //E:\1111\ac792\ui_prj\Application12\import\image\up.png
    GUI_RES_DOWN_1_PNG = 0x4B000059,   //E:\1111\ac792\ui_prj\Application12\import\image\down.png
    GUI_RES_DELET_PNG = 0x4B00005A,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\dec\delet.png
    GUI_RES_PROTECT_PNG = 0x4B00005B,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\dec\protect.png
    GUI_RES_PLAY_PNG = 0x4B00005C,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\rec\rec_menu\play.png
    GUI_RES_VIDEO_PNG = 0x4B00005D,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\dec\video.png
    GUI_RES_PHOTO_2_PNG = 0x4B00005E,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\dec\photo.png
    GUI_RES_CARD_OFFLINE_PNG = 0x4B00005F,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\rec\rec_scan\card_offline.png
    GUI_RES_PLAY_1_PNG = 0x4B000060,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\dec\play.png
    GUI_RES_PAUSE_PNG = 0x4B000061,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\dec\pause.png
} GUI_RES_ID;

typedef enum {
    RES_0 = 0x74000062,   //E:\1111\ac792\ui_prj\Application12\import\image\video_page\battery\0.png 48x48
    RES_1 = 0x74000063,   //E:\1111\ac792\ui_prj\Application12\import\image\video_page\battery\1.png 48x48
    RES_2 = 0x74000064,   //E:\1111\ac792\ui_prj\Application12\import\image\video_page\battery\2.png 48x48
    RES_3 = 0x74000065,   //E:\1111\ac792\ui_prj\Application12\import\image\video_page\battery\3.png 48x48
    RES_CHARGING = 0x74000066,   //E:\1111\ac792\ui_prj\Application12\import\image\video_page\battery\charging.png 48x48
    RES_FULL = 0x74000067,   //E:\1111\ac792\ui_prj\Application12\import\image\video_page\battery\full.png 48x48
    RES_GRAVITY_SENSOR_LOW = 0x74000068,   //E:\1111\ac792\ui_prj\Application12\import\image\video_page\gravity_sensor_low.png 48x48
    RES_GRAVITY_SENSOR_MIDLLER = 0x74000069,   //E:\1111\ac792\ui_prj\Application12\import\image\video_page\gravity_sensor_midller.png 48x48
    RES_GRAVITY_SENSOR_HIGH = 0x7400006A,   //E:\1111\ac792\ui_prj\Application12\import\image\video_page\gravity_sensor_high.png 48x48
    RES_INTERVAL_VIDEO_CLOSE = 0x7400006B,   //E:\1111\ac792\ui_prj\Application12\import\image\video_page\interval_video_close.png 48x48
    RES_INTERVAL_VIDEO_500 = 0x7400006C,   //E:\1111\ac792\ui_prj\Application12\import\image\video_page\interval_video_500.png 48x48
    RES_INTERVAL_VIDEO_200 = 0x7400006D,   //E:\1111\ac792\ui_prj\Application12\import\image\video_page\interval_video_200.png 48x48
    RES_INTERVAL_VIDEO_100 = 0x7400006E,   //E:\1111\ac792\ui_prj\Application12\import\image\video_page\interval_video_100.png 48x48
    RES_SD = 0x7400006F,   //E:\1111\ac792\ui_prj\Application12\import\image\video_page\SD.png 45x45
    RES_SD_CLOSE = 0x74000070,   //E:\1111\ac792\ui_prj\Application12\import\image\video_page\SD_close.png 45x45
    RES_SOUND = 0x74000071,   //E:\1111\ac792\ui_prj\Application12\import\image\video_page\sound.png 48x48
    RES_SOUND_CLOSE = 0x74000072,   //E:\1111\ac792\ui_prj\Application12\import\image\video_page\sound_close.png 48x48
    RES_EXPOSURE = 0x74000073,   //E:\1111\ac792\ui_prj\Application12\import\image\video_page\menu_icon\exposure.png 80x80
    RES_DOUBLE_VIDEO = 0x74000074,   //E:\1111\ac792\ui_prj\Application12\import\image\video_page\menu_icon\double_video.png 80x80
    RES_DATE = 0x74000075,   //E:\1111\ac792\ui_prj\Application12\import\image\video_page\menu_icon\date.png 80x80
    RES_CYCLIC_VIDEO = 0x74000076,   //E:\1111\ac792\ui_prj\Application12\import\image\video_page\menu_icon\cyclic_video.png 80x80
    RES_CHECK_SPORT = 0x74000077,   //E:\1111\ac792\ui_prj\Application12\import\image\video_page\menu_icon\check_sport.png 80x80
    RES_CAR_NUM = 0x74000078,   //E:\1111\ac792\ui_prj\Application12\import\image\video_page\menu_icon\car_num.png 80x80
    RES_GRAVITY_SENSOR = 0x74000079,   //E:\1111\ac792\ui_prj\Application12\import\image\video_page\menu_icon\gravity_sensor.png 80x80
    RES_HDR = 0x7400007A,   //E:\1111\ac792\ui_prj\Application12\import\image\video_page\menu_icon\HDR.png 80x80
    RES_INTERVAL_VIDEO = 0x7400007B,   //E:\1111\ac792\ui_prj\Application12\import\image\video_page\menu_icon\interval_video.png 80x80
    RES_RESOLUTION_RATIO = 0x7400007C,   //E:\1111\ac792\ui_prj\Application12\import\image\video_page\menu_icon\resolution_ratio.png 80x80
    RES_SOUND_1 = 0x7400007D,   //E:\1111\ac792\ui_prj\Application12\import\image\video_page\menu_icon\sound.png 80x80
    RES_STOPPING_MONITOR = 0x7400007E,   //E:\1111\ac792\ui_prj\Application12\import\image\video_page\menu_icon\stopping_monitor.png 80x80
    RES_AUTO_OFF = 0x7400007F,   //E:\1111\ac792\ui_prj\Application12\import\image\video_page\sys_setting\icon\auto_off.png 80x80
    RES_CAR_NUM_1 = 0x74000080,   //E:\1111\ac792\ui_prj\Application12\import\image\video_page\sys_setting\icon\car_num.png 80x80
    RES_FLIG = 0x74000081,   //E:\1111\ac792\ui_prj\Application12\import\image\video_page\sys_setting\icon\flig.png 80x80
    RES_FORMAT = 0x74000082,   //E:\1111\ac792\ui_prj\Application12\import\image\video_page\sys_setting\icon\format.png 80x80
    RES_FREQUENCY = 0x74000083,   //E:\1111\ac792\ui_prj\Application12\import\image\video_page\sys_setting\icon\frequency.png 80x80
    RES_LANE = 0x74000084,   //E:\1111\ac792\ui_prj\Application12\import\image\video_page\sys_setting\icon\lane.png 80x80
    RES_LANGUAGES = 0x74000085,   //E:\1111\ac792\ui_prj\Application12\import\image\video_page\sys_setting\icon\languages.png 80x80
    RES_LCD_OFF = 0x74000086,   //E:\1111\ac792\ui_prj\Application12\import\image\video_page\sys_setting\icon\lcd_off.png 80x80
    RES_RESET = 0x74000087,   //E:\1111\ac792\ui_prj\Application12\import\image\video_page\sys_setting\icon\reset.png 80x80
    RES_VERSION = 0x74000088,   //E:\1111\ac792\ui_prj\Application12\import\image\video_page\sys_setting\icon\version.png 80x80
    RES_VOICE = 0x74000089,   //E:\1111\ac792\ui_prj\Application12\import\image\video_page\sys_setting\icon\voice.png 80x80
    RES_DATE_1 = 0x7400008A,   //E:\1111\ac792\ui_prj\Application12\import\image\video_page\sys_setting\icon\date.png 80x80
    RES_AWB = 0x7400008B,   //E:\1111\ac792\ui_prj\Application12\import\image\video_page\awb.png 48x48
    RES_AWB_FLUORESCENT_LAMP = 0x7400008C,   //E:\1111\ac792\ui_prj\Application12\import\image\video_page\awb_fluorescent_lamp.png 48x48
    RES_AWB_OSRAM_LAMP = 0x7400008D,   //E:\1111\ac792\ui_prj\Application12\import\image\video_page\awb_osram_lamp.png 48x48
    RES_AWB_SUN_CLOUDY = 0x7400008E,   //E:\1111\ac792\ui_prj\Application12\import\image\video_page\awb_sun_cloudy.png 48x48
    RES_AWB_SUN_LIGHT = 0x7400008F,   //E:\1111\ac792\ui_prj\Application12\import\image\video_page\awb_sun_light.png 48x48
    RES_HIGH = 0x74000090,   //E:\1111\ac792\ui_prj\Application12\import\image\video_page\high.png 48x48
    RES_LOW = 0x74000091,   //E:\1111\ac792\ui_prj\Application12\import\image\video_page\low.png 48x48
    RES_MIDDLE = 0x74000092,   //E:\1111\ac792\ui_prj\Application12\import\image\video_page\middle.png 48x48
    RES_TIMING_PHOTO_2 = 0x74000093,   //E:\1111\ac792\ui_prj\Application12\import\image\video_page\timing_photo_2.png 48x48
    RES_TIMING_PHOTO_5 = 0x74000094,   //E:\1111\ac792\ui_prj\Application12\import\image\video_page\timing_photo_5.png 48x48
    RES_TIMING_PHOTO_10 = 0x74000095,   //E:\1111\ac792\ui_prj\Application12\import\image\video_page\timing_photo_10.png 48x48
    RES_FILE_DIR = 0x74000096,   //E:\1111\ac792\ui_prj\Application12\import\image\file_dir.png 160x160
    RES_DELETE = 0x74000097,   //E:\1111\ac792\ui_prj\Application12\import\image\DELETE.png 48x48
    RES_DELETE_ON = 0x74000098,   //E:\1111\ac792\ui_prj\Application12\import\image\delete_on.png 48x48
    RES_EDIT = 0x74000099,   //E:\1111\ac792\ui_prj\Application12\import\image\EDIT.png 48x48
    RES_EDITOR_ON = 0x7400009A,   //E:\1111\ac792\ui_prj\Application12\import\image\editor_on.png 48x48
    RES_HOME = 0x7400009B,   //E:\1111\ac792\ui_prj\Application12\import\image\HOME.png 48x48
    RES_HOME_ON = 0x7400009C,   //E:\1111\ac792\ui_prj\Application12\import\image\home_on.png 48x48
    RES_LOCK = 0x7400009D,   //E:\1111\ac792\ui_prj\Application12\import\image\LOCK.png 48x48
    RES_LOCK_ON = 0x7400009E,   //E:\1111\ac792\ui_prj\Application12\import\image\lock_on.png 48x48
    RES_PHOTO = 0x7400009F,   //E:\1111\ac792\ui_prj\Application12\import\image\PHOTO.png 48x48
    RES_PHOTO_ON = 0x740000A0,   //E:\1111\ac792\ui_prj\Application12\import\image\photo_on.png 48x48
    RES_RETURN = 0x740000A1,   //E:\1111\ac792\ui_prj\Application12\import\image\RETURN.png 48x48
    RES_RETURN_ON = 0x740000A2,   //E:\1111\ac792\ui_prj\Application12\import\image\return_on.png 48x48
    RES_SELETE = 0x740000A3,   //E:\1111\ac792\ui_prj\Application12\import\image\SELETE.png 48x48
    RES_UNLOCK = 0x740000A4,   //E:\1111\ac792\ui_prj\Application12\import\image\UNLOCK.png 48x48
    RES_UNLOCK_ON = 0x740000A5,   //E:\1111\ac792\ui_prj\Application12\import\image\unlock_on.png 48x48
    RES_VIDEO = 0x740000A6,   //E:\1111\ac792\ui_prj\Application12\import\image\VIDEO.png 48x48
    RES_VOLUMELOUDER_SOLID_1 = 0x740000A7,   //E:\1111\ac792\ui_prj\Application12\import\image\volumeLouder_solid_1.png 48x48
    RES_VIDEO_PAUSE = 0x740000A8,   //E:\1111\ac792\ui_prj\Application12\import\image\video_pause.png 48x48
    RES_SKIP_NEXT = 0x740000A9,   //E:\1111\ac792\ui_prj\Application12\import\image\skip_next.png 48x48
    RES_SKIP_PREVIOUS = 0x740000AA,   //E:\1111\ac792\ui_prj\Application12\import\image\skip_previous.png 48x48
    RES_PLAY = 0x740000AB,   //E:\1111\ac792\ui_prj\Application12\import\image\play.png 32x32
    RES_VIDEO_PLAY = 0x740000AC,   //E:\1111\ac792\ui_prj\Application12\import\image\video_play.png 48x48
    RES_VOLUMEMUTE_SOLID_1 = 0x740000AD,   //E:\1111\ac792\ui_prj\Application12\import\image\volumeMute_solid_1.png 48x48
    RES_SOFTWARE = 0x740000AE,   //E:\1111\ac792\ui_prj\Application12\import\image\video_page\menu_icon\software.png 80x80
    RES_LOCK_FLAG = 0x740000AF,   //E:\1111\ac792\ui_prj\Application12\import\image\lock_flag.png 24x24
    RES_CYCLIC_VIDEO_10 = 0x740000B0,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\rec\rec_scan\cyclic_video_10.png 29x31
    RES_CYCLIC_VIDEO_3 = 0x740000B1,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\rec\rec_scan\cyclic_video_3.png 29x31
    RES_CYCLIC_VIDEO_5 = 0x740000B2,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\rec\rec_scan\cyclic_video_5.png 29x31
    RES_MIC_OFF = 0x740000B3,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\rec\rec_scan\mic_off.png 26x29
    RES_MIC_ON = 0x740000B4,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\rec\rec_scan\mic_on.png 26x29
    RES_I_GRA_H = 0x740000B5,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\rec\rec_scan\i_gra_h.png 34x31
    RES_I_GRA_M = 0x740000B6,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\rec\rec_scan\i_gra_m.png 34x31
    RES_I_GRA_L = 0x740000B7,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\rec\rec_scan\i_gra_l.png 34x31
    RES_BAT_0 = 0x740000B8,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\rec\rec_scan\bat_0.png 25x15
    RES_BAT_L = 0x740000B9,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\rec\rec_scan\bat_l.png 25x15
    RES_BAT_HALF = 0x740000BA,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\rec\rec_scan\bat_half.png 25x15
    RES_BAT_H = 0x740000BB,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\rec\rec_scan\bat_h.png 25x15
    RES_CHAR = 0x740000BC,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\rec\rec_scan\char.png 25x15
    RES_CARD_OFFLINE = 0x740000BD,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\rec\rec_scan\card_offline.png 29x29
    RES_CARD_ONLINE = 0x740000BE,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\rec\rec_scan\card_online.png 29x29
    RES_PARK = 0x740000BF,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\rec\rec_scan\park.png 16x13
    RES_EXP_A3 = 0x740000C0,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\rec\rec_scan\exp_a3.png 29x29
    RES_EXP_A2 = 0x740000C1,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\rec\rec_scan\exp_a2.png 29x29
    RES_EXP_A1 = 0x740000C2,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\rec\rec_scan\exp_a1.png 29x29
    RES_EXP_A0 = 0x740000C3,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\rec\rec_scan\exp_a0.png 29x29
    RES_EXP_D1 = 0x740000C4,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\rec\rec_scan\exp_d1.png 29x29
    RES_EXP_D2 = 0x740000C5,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\rec\rec_scan\exp_d2.png 29x29
    RES_EXP_D3 = 0x740000C6,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\rec\rec_scan\exp_d3.png 29x29
    RES_AWB_AUTO = 0x740000C7,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\photo\photo_scan\awb_auto.png 29x29
    RES_AWB_CLOUDY = 0x740000C8,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\photo\photo_scan\awb_cloudy.png 29x29
    RES_AWB_FINE = 0x740000C9,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\photo\photo_scan\awb_fine.png 29x29
    RES_AWB_FLUORESCENT_LAMP_1 = 0x740000CA,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\photo\photo_scan\awb_fluorescent_lamp.png 29x29
    RES_AWB_TUNGSTEN_LAMP = 0x740000CB,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\photo\photo_scan\awb_tungsten_lamp.png 29x29
    RES_ISO_1 = 0x740000CC,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\photo\photo_scan\iso_1.png 29x29
    RES_ISO_2 = 0x740000CD,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\photo\photo_scan\iso_2.png 29x29
    RES_ISO_4 = 0x740000CE,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\photo\photo_scan\iso_4.png 29x29
    RES_ISO_AUTO = 0x740000CF,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\photo\photo_scan\iso_auto.png 29x29
    RES_Q1 = 0x740000D0,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\photo\photo_scan\q1.png 29x29
    RES_Q2 = 0x740000D1,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\photo\photo_scan\q2.png 29x29
    RES_Q3 = 0x740000D2,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\photo\photo_scan\q3.png 29x29
    RES_DL2 = 0x740000D3,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\photo\photo_scan\dl2.png 29x29
    RES_DL5 = 0x740000D4,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\photo\photo_scan\dl5.png 29x29
    RES_DL10 = 0x740000D5,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\photo\photo_scan\dl10.png 29x29
    RES_SHAKE_OFF = 0x740000D6,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\photo\photo_scan\shake_off.png 29x29
    RES_SHAKE_ON = 0x740000D7,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\photo\photo_scan\shake_on.png 29x29
    RES_BAT_FULL = 0x740000D8,   //E:\1111\ac792\ui_prj\Application12\import\image\LY_UI\rec\rec_scan\bat_full.png 25x15
} RES_ID;

extern char *gui_get_res_path(int32_t id);

#ifdef __cplusplus
}
#endif
#endif

#endif
