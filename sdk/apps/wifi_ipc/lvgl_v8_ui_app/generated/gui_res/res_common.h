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
    GUI_RES_MONTSERRATMEDIUM_22_TTF = 0x35000000,   //E:\1111\ac792\ui_prj\door_bell_480x800\ui_res\flash\rle\font\35000000.rle
    GUI_RES_SIMSUN_22_WOFF = 0x35000001,   //E:\1111\ac792\ui_prj\door_bell_480x800\ui_res\flash\rle\font\35000001.rle
    GUI_RES_MONTSERRATMEDIUM_32_TTF = 0x35000002,   //E:\1111\ac792\ui_prj\door_bell_480x800\ui_res\flash\rle\font\35000002.rle
    GUI_RES_FANGZHENGKAITIJIANTI_1_32_TTF = 0x35000003,   //E:\1111\ac792\ui_prj\door_bell_480x800\ui_res\flash\rle\font\35000003.rle
    GUI_RES_FANGZHENGKAITIJIANTI_1_20_TTF = 0x35000004,   //E:\1111\ac792\ui_prj\door_bell_480x800\ui_res\flash\rle\font\35000004.rle
    GUI_RES_FANGZHENGKAITIJIANTI_1_18_TTF = 0x35000005,   //E:\1111\ac792\ui_prj\door_bell_480x800\ui_res\flash\rle\font\35000005.rle
    GUI_RES_FANGZHENGKAITIJIANTI_1_22_TTF = 0x35000006,   //E:\1111\ac792\ui_prj\door_bell_480x800\ui_res\flash\rle\font\35000006.rle

    GUI_RES_WIFI_04_PNG = 0x4B000007,   //E:\1111\ac792\ui_prj\door_bell_480x800\import\image\wifi_04.png
    GUI_RES_ICON_CALL_OUT_PNG = 0x4B000008,   //E:\1111\ac792\ui_prj\door_bell_480x800\import\image\icon_call_out.png
    GUI_RES_ICON_RECOVER_PNG = 0x4B000009,   //E:\1111\ac792\ui_prj\door_bell_480x800\import\image\icon_recover.png
    GUI_RES_ICON_WALKIE_TALKIE_PNG = 0x4B00000A,   //E:\1111\ac792\ui_prj\door_bell_480x800\import\image\icon_walkie_talkie.png
    GUI_RES_WEATHER_013_HOME_IMG_WEATHER_PNG = 0x4B00000B,   //E:\1111\ac792\ui_prj\door_bell_480x800\import\image\weather_013.png
    GUI_RES_ICON_BATTERY_CHARGING_PNG = 0x4B00000C,   //E:\1111\ac792\ui_prj\door_bell_480x800\import\image\icon_battery_charging.png
    GUI_RES_ICON_BATTERY_15_PNG = 0x4B00000D,   //E:\1111\ac792\ui_prj\door_bell_480x800\import\image\icon_battery_15.png
    GUI_RES_ICON_BATTERY_25_PNG = 0x4B00000E,   //E:\1111\ac792\ui_prj\door_bell_480x800\import\image\icon_battery_25.png
    GUI_RES_ICON_BATTERY_50_PNG = 0x4B00000F,   //E:\1111\ac792\ui_prj\door_bell_480x800\import\image\icon_battery_50.png
    GUI_RES_ICON_BATTERY_75_PNG = 0x4B000010,   //E:\1111\ac792\ui_prj\door_bell_480x800\import\image\icon_battery_75.png
    GUI_RES_ICON_BATTERY_100_PNG = 0x4B000011,   //E:\1111\ac792\ui_prj\door_bell_480x800\import\image\icon_battery_100.png
    GUI_RES_WIFI_00_PNG = 0x4B000012,   //E:\1111\ac792\ui_prj\door_bell_480x800\import\image\wifi_00.png
    GUI_RES_WIFI_01_PNG = 0x4B000013,   //E:\1111\ac792\ui_prj\door_bell_480x800\import\image\wifi_01.png
    GUI_RES_WIFI_2_PNG = 0x4B000014,   //E:\1111\ac792\ui_prj\door_bell_480x800\import\image\wifi_2.png
    GUI_RES_WIFI_03_PNG = 0x4B000015,   //E:\1111\ac792\ui_prj\door_bell_480x800\import\image\wifi_03.png
    GUI_RES_ICON_BACK_PNG = 0x4B000016,   //E:\1111\ac792\ui_prj\door_bell_480x800\import\image\icon_back.png
    GUI_RES_ICON_DOWNLOAD_PNG = 0x4B000017,   //E:\1111\ac792\ui_prj\door_bell_480x800\import\image\icon_download.png
    GUI_RES_ICON_CONFNET_PNG = 0x4B000018,   //E:\1111\ac792\ui_prj\door_bell_480x800\import\image\icon_confnet.png
    GUI_RES_ICON_LANGUAGE_PNG = 0x4B000019,   //E:\1111\ac792\ui_prj\door_bell_480x800\import\image\icon_language.png
    GUI_RES_ICON_SETTLE_PNG = 0x4B00001A,   //E:\1111\ac792\ui_prj\door_bell_480x800\import\image\icon_settle.png
    GUI_RES_ICON_ABOUT_PNG = 0x4B00001B,   //E:\1111\ac792\ui_prj\door_bell_480x800\import\image\icon_about.png
    GUI_RES_ICON_CODE_PNG = 0x4B00001C,   //E:\1111\ac792\ui_prj\door_bell_480x800\import\image\icon_code.png
    GUI_RES_QRCODE_PNG = 0x4B00001D,   //E:\1111\ac792\ui_prj\door_bell_480x800\import\image\qrcode.png
} GUI_RES_ID;

typedef enum {
    RES_ICON_BATTERY_100 = 0x7400001E,   //E:\1111\ac792\ui_prj\door_bell_480x800\import\image\icon_battery_100.png 51x51
    RES_ICON_BATTERY_15 = 0x7400001F,   //E:\1111\ac792\ui_prj\door_bell_480x800\import\image\icon_battery_15.png 51x51
    RES_ICON_BATTERY_25 = 0x74000020,   //E:\1111\ac792\ui_prj\door_bell_480x800\import\image\icon_battery_25.png 51x51
    RES_ICON_BATTERY_50 = 0x74000021,   //E:\1111\ac792\ui_prj\door_bell_480x800\import\image\icon_battery_50.png 51x51
    RES_ICON_BATTERY_75 = 0x74000022,   //E:\1111\ac792\ui_prj\door_bell_480x800\import\image\icon_battery_75.png 51x51
    RES_ICON_BATTERY_CHARGING = 0x74000023,   //E:\1111\ac792\ui_prj\door_bell_480x800\import\image\icon_battery_charging.png 51x51
    RES_ICON_CALL_OUT = 0x74000024,   //E:\1111\ac792\ui_prj\door_bell_480x800\import\image\icon_call_out.png 98x98
    RES_ICON_HANGUP = 0x74000025,   //E:\1111\ac792\ui_prj\door_bell_480x800\import\image\icon_hangup.png 98x98
    RES_ICON_LOUDSPEAKER_OFF = 0x74000026,   //E:\1111\ac792\ui_prj\door_bell_480x800\import\image\icon_loudspeaker_off.png 98x98
    RES_ICON_LOUDSPEAKER_ON = 0x74000027,   //E:\1111\ac792\ui_prj\door_bell_480x800\import\image\icon_loudspeaker_on.png 98x98
    RES_ICON_WALKIE_TALKIE = 0x74000028,   //E:\1111\ac792\ui_prj\door_bell_480x800\import\image\icon_walkie_talkie.png 98x98
    RES_ICON_WIFI = 0x74000029,   //E:\1111\ac792\ui_prj\door_bell_480x800\import\image\icon_wifi.png 48x48
    RES_IC_MIC_OFF = 0x7400002A,   //E:\1111\ac792\ui_prj\door_bell_480x800\import\image\ic_mic_off.png 98x98
    RES_IC_MIC_ON = 0x7400002B,   //E:\1111\ac792\ui_prj\door_bell_480x800\import\image\ic_mic_on.png 98x98
    RES_IMG_LOGO = 0x7400002C,   //E:\1111\ac792\ui_prj\door_bell_480x800\import\image\img_logo.png 332x82
    RES_ICON_RECOVER = 0x7400002D,   //E:\1111\ac792\ui_prj\door_bell_480x800\import\image\icon_recover.png 98x98
    RES_WEATHER_001 = 0x7400002E,   //E:\1111\ac792\ui_prj\door_bell_480x800\import\image\weather_001.png 200x200
    RES_WEATHER_002 = 0x7400002F,   //E:\1111\ac792\ui_prj\door_bell_480x800\import\image\weather_002.png 200x200
    RES_WEATHER_003 = 0x74000030,   //E:\1111\ac792\ui_prj\door_bell_480x800\import\image\weather_003.png 200x200
    RES_WEATHER_004 = 0x74000031,   //E:\1111\ac792\ui_prj\door_bell_480x800\import\image\weather_004.png 200x200
    RES_WEATHER_005 = 0x74000032,   //E:\1111\ac792\ui_prj\door_bell_480x800\import\image\weather_005.png 200x200
    RES_WEATHER_006 = 0x74000033,   //E:\1111\ac792\ui_prj\door_bell_480x800\import\image\weather_006.png 200x200
    RES_WEATHER_008 = 0x74000034,   //E:\1111\ac792\ui_prj\door_bell_480x800\import\image\weather_008.png 200x200
    RES_WEATHER_007 = 0x74000035,   //E:\1111\ac792\ui_prj\door_bell_480x800\import\image\weather_007.png 200x200
    RES_WEATHER_009 = 0x74000036,   //E:\1111\ac792\ui_prj\door_bell_480x800\import\image\weather_009.png 200x200
    RES_WEATHER_010 = 0x74000037,   //E:\1111\ac792\ui_prj\door_bell_480x800\import\image\weather_010.png 200x200
    RES_WEATHER_011 = 0x74000038,   //E:\1111\ac792\ui_prj\door_bell_480x800\import\image\weather_011.png 200x200
    RES_WEATHER_012 = 0x74000039,   //E:\1111\ac792\ui_prj\door_bell_480x800\import\image\weather_012.png 200x200
    RES_WEATHER_013 = 0x7400003A,   //E:\1111\ac792\ui_prj\door_bell_480x800\import\image\weather_013.png 200x200
    RES_WEATHER_014 = 0x7400003B,   //E:\1111\ac792\ui_prj\door_bell_480x800\import\image\weather_014.png 200x200
    RES_WEATHER_015 = 0x7400003C,   //E:\1111\ac792\ui_prj\door_bell_480x800\import\image\weather_015.png 200x200
    RES_WEATHER_016 = 0x7400003D,   //E:\1111\ac792\ui_prj\door_bell_480x800\import\image\weather_016.png 200x200
    RES_WEATHER_017 = 0x7400003E,   //E:\1111\ac792\ui_prj\door_bell_480x800\import\image\weather_017.png 200x200
    RES_WIFI_00 = 0x7400003F,   //E:\1111\ac792\ui_prj\door_bell_480x800\import\image\wifi_00.png 32x32
    RES_WIFI_01 = 0x74000040,   //E:\1111\ac792\ui_prj\door_bell_480x800\import\image\wifi_01.png 32x32
    RES_WIFI_03 = 0x74000041,   //E:\1111\ac792\ui_prj\door_bell_480x800\import\image\wifi_03.png 32x32
    RES_WIFI_04 = 0x74000042,   //E:\1111\ac792\ui_prj\door_bell_480x800\import\image\wifi_04.png 32x32
    RES_WIFI_2 = 0x74000043,   //E:\1111\ac792\ui_prj\door_bell_480x800\import\image\wifi_2.png 32x32
} RES_ID;

extern char *gui_get_res_path(int32_t id);

#ifdef __cplusplus
}
#endif
#endif
