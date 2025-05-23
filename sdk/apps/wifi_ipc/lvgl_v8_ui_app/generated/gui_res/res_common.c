/*Generate Code, Do NOT Edit!*/
#include "../gui_guider.h"
#include <stdlib.h>
#include <string.h>
#if LV_USE_GUIBUILDER_SIMULATOR
#include <stdio.h>
#endif

#if !LV_USE_GUIBUILDER_SIMULATOR
#define max(a, b) ((a) > (b) ? (a) : (b))
char sd_dir[] = "storage/sd0/C/";
char flash_dir[] = "mnt/sdfile/EXT_RESERVED/uipackres/ui/";
char path_buf[max(sizeof(sd_dir), sizeof(flash_dir)) + 20];
#endif

char *gui_get_res_path(int32_t id)
{
#if LV_USE_GUIBUILDER_SIMULATOR
    switch (id) {
    case GUI_RES_MONTSERRATMEDIUM_22_TTF:
        return "E:\\1111\\ac792\\ui_prj\\door_bell_480x800\\ui_res\\flash\\rle\\font\\35000000.rle";
    case GUI_RES_SIMSUN_22_WOFF:
        return "E:\\1111\\ac792\\ui_prj\\door_bell_480x800\\ui_res\\flash\\rle\\font\\35000001.rle";
    case GUI_RES_MONTSERRATMEDIUM_32_TTF:
        return "E:\\1111\\ac792\\ui_prj\\door_bell_480x800\\ui_res\\flash\\rle\\font\\35000002.rle";
    case GUI_RES_FANGZHENGKAITIJIANTI_1_32_TTF:
        return "E:\\1111\\ac792\\ui_prj\\door_bell_480x800\\ui_res\\flash\\rle\\font\\35000003.rle";
    case GUI_RES_FANGZHENGKAITIJIANTI_1_20_TTF:
        return "E:\\1111\\ac792\\ui_prj\\door_bell_480x800\\ui_res\\flash\\rle\\font\\35000004.rle";
    case GUI_RES_FANGZHENGKAITIJIANTI_1_18_TTF:
        return "E:\\1111\\ac792\\ui_prj\\door_bell_480x800\\ui_res\\flash\\rle\\font\\35000005.rle";
    case GUI_RES_FANGZHENGKAITIJIANTI_1_22_TTF:
        return "E:\\1111\\ac792\\ui_prj\\door_bell_480x800\\ui_res\\flash\\rle\\font\\35000006.rle";
    case GUI_RES_WIFI_04_PNG:
        return "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\wifi_04.png";
    case GUI_RES_ICON_CALL_OUT_PNG:
        return "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\icon_call_out.png";
    case GUI_RES_ICON_RECOVER_PNG:
        return "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\icon_recover.png";
    case GUI_RES_ICON_WALKIE_TALKIE_PNG:
        return "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\icon_walkie_talkie.png";
    case GUI_RES_WEATHER_013_HOME_IMG_WEATHER_PNG:
        return "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\weather_013.png";
    case GUI_RES_ICON_BATTERY_CHARGING_PNG:
        return "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\icon_battery_charging.png";
    case GUI_RES_ICON_BATTERY_15_PNG:
        return "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\icon_battery_15.png";
    case GUI_RES_ICON_BATTERY_25_PNG:
        return "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\icon_battery_25.png";
    case GUI_RES_ICON_BATTERY_50_PNG:
        return "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\icon_battery_50.png";
    case GUI_RES_ICON_BATTERY_75_PNG:
        return "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\icon_battery_75.png";
    case GUI_RES_ICON_BATTERY_100_PNG:
        return "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\icon_battery_100.png";
    case GUI_RES_WIFI_00_PNG:
        return "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\wifi_00.png";
    case GUI_RES_WIFI_01_PNG:
        return "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\wifi_01.png";
    case GUI_RES_WIFI_2_PNG:
        return "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\wifi_2.png";
    case GUI_RES_WIFI_03_PNG:
        return "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\wifi_03.png";
    case GUI_RES_ICON_BACK_PNG:
        return "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\icon_back.png";
    case GUI_RES_ICON_DOWNLOAD_PNG:
        return "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\icon_download.png";
    case GUI_RES_ICON_CONFNET_PNG:
        return "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\icon_confnet.png";
    case GUI_RES_ICON_LANGUAGE_PNG:
        return "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\icon_language.png";
    case GUI_RES_ICON_SETTLE_PNG:
        return "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\icon_settle.png";
    case GUI_RES_ICON_ABOUT_PNG:
        return "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\icon_about.png";
    case GUI_RES_ICON_CODE_PNG:
        return "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\icon_code.png";
    case GUI_RES_QRCODE_PNG:
        return "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\qrcode.png";
    case RES_ICON_BATTERY_100:
        return "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\icon_battery_100.png";
    case RES_ICON_BATTERY_15:
        return "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\icon_battery_15.png";
    case RES_ICON_BATTERY_25:
        return "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\icon_battery_25.png";
    case RES_ICON_BATTERY_50:
        return "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\icon_battery_50.png";
    case RES_ICON_BATTERY_75:
        return "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\icon_battery_75.png";
    case RES_ICON_BATTERY_CHARGING:
        return "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\icon_battery_charging.png";
    case RES_ICON_CALL_OUT:
        return "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\icon_call_out.png";
    case RES_ICON_HANGUP:
        return "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\icon_hangup.png";
    case RES_ICON_LOUDSPEAKER_OFF:
        return "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\icon_loudspeaker_off.png";
    case RES_ICON_LOUDSPEAKER_ON:
        return "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\icon_loudspeaker_on.png";
    case RES_ICON_WALKIE_TALKIE:
        return "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\icon_walkie_talkie.png";
    case RES_ICON_WIFI:
        return "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\icon_wifi.png";
    case RES_IC_MIC_OFF:
        return "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\ic_mic_off.png";
    case RES_IC_MIC_ON:
        return "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\ic_mic_on.png";
    case RES_IMG_LOGO:
        return "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\img_logo.png";
    case RES_ICON_RECOVER:
        return "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\icon_recover.png";
    case RES_WEATHER_001:
        return "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\weather_001.png";
    case RES_WEATHER_002:
        return "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\weather_002.png";
    case RES_WEATHER_003:
        return "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\weather_003.png";
    case RES_WEATHER_004:
        return "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\weather_004.png";
    case RES_WEATHER_005:
        return "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\weather_005.png";
    case RES_WEATHER_006:
        return "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\weather_006.png";
    case RES_WEATHER_008:
        return "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\weather_008.png";
    case RES_WEATHER_007:
        return "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\weather_007.png";
    case RES_WEATHER_009:
        return "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\weather_009.png";
    case RES_WEATHER_010:
        return "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\weather_010.png";
    case RES_WEATHER_011:
        return "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\weather_011.png";
    case RES_WEATHER_012:
        return "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\weather_012.png";
    case RES_WEATHER_013:
        return "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\weather_013.png";
    case RES_WEATHER_014:
        return "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\weather_014.png";
    case RES_WEATHER_015:
        return "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\weather_015.png";
    case RES_WEATHER_016:
        return "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\weather_016.png";
    case RES_WEATHER_017:
        return "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\weather_017.png";
    case RES_WIFI_00:
        return "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\wifi_00.png";
    case RES_WIFI_01:
        return "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\wifi_01.png";
    case RES_WIFI_03:
        return "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\wifi_03.png";
    case RES_WIFI_04:
        return "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\wifi_04.png";
    case RES_WIFI_2:
        return "A:\\1111\\ac792\\ui_prj\\door_bell_480x800\\import\\image\\wifi_2.png";
    default:
        return NULL;
    }
#else
    memset(path_buf, 0, sizeof(path_buf));
    if (id >= 0x30000000 && id < 0x30800000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "ttf");
    } else if (id >= 0x30800000 && id < 0x31000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "ttf");
    } else if (id >= 0x31000000 && id < 0x31800000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "woff");
    } else if (id >= 0x31800000 && id < 0x32000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "woff");
    } else if (id >= 0x32000000 && id < 0x32800000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "woff2");
    } else if (id >= 0x32800000 && id < 0x33000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "woff2");
    } else if (id >= 0x33000000 && id < 0x33800000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "otf");
    } else if (id >= 0x33800000 && id < 0x34000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "otf");
    } else if (id >= 0x34000000 && id < 0x34800000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "bin");
    } else if (id >= 0x34800000 && id < 0x35000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "bin");
    } else if (id >= 0x35000000 && id < 0x35800000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "rle");
    } else if (id >= 0x35800000 && id < 0x36000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "rle");
    } else if (id >= 0x36000000 && id < 0x36800000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "fnt");
    } else if (id >= 0x36800000 && id < 0x37000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "fnt");
    } else if (id >= 0x37000000 && id < 0x37800000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "lzw");
    } else if (id >= 0x37800000 && id < 0x38000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "lzw");
    } else if (id >= 0x39000000 && id < 0x39800000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "json");
    } else if (id >= 0x39800000 && id < 0x3A000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "json");
    } else if (id >= 0x3A000000 && id < 0x3A800000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "bin");
    } else if (id >= 0x3A800000 && id < 0x3B000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "bin");
    } else if (id >= 0x3B000000 && id < 0x3B800000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "rle");
    } else if (id >= 0x3B800000 && id < 0x3C000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "rle");
    } else if (id >= 0x3D000000 && id < 0x3D800000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "mp4");
    } else if (id >= 0x3D800000 && id < 0x3E000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "mp4");
    } else if (id >= 0x3E000000 && id < 0x3E800000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "avi");
    } else if (id >= 0x3E800000 && id < 0x3F000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "avi");
    } else if (id >= 0x3F000000 && id < 0x3F800000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "bin");
    } else if (id >= 0x3F800000 && id < 0x40000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "bin");
    } else if (id >= 0x40000000 && id < 0x40800000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "rle");
    } else if (id >= 0x40800000 && id < 0x41000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "rle");
    } else if (id >= 0x42000000 && id < 0x42800000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "gif");
    } else if (id >= 0x42800000 && id < 0x43000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "gif");
    } else if (id >= 0x43000000 && id < 0x43800000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "zip");
    } else if (id >= 0x43800000 && id < 0x44000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "zip");
    } else if (id >= 0x46000000 && id < 0x46800000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "png");
    } else if (id >= 0x46800000 && id < 0x47000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "png");
    } else if (id >= 0x47000000 && id < 0x47800000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "jpg");
    } else if (id >= 0x47800000 && id < 0x48000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "jpg");
    } else if (id >= 0x48000000 && id < 0x48800000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "jpeg");
    } else if (id >= 0x48800000 && id < 0x49000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "jpeg");
    } else if (id >= 0x49000000 && id < 0x49800000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "bmp");
    } else if (id >= 0x49800000 && id < 0x4A000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "bmp");
    } else if (id >= 0x4A000000 && id < 0x4A800000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "svg");
    } else if (id >= 0x4A800000 && id < 0x4B000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "svg");
    } else if (id >= 0x4B000000 && id < 0x4B800000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "zip");
    } else if (id >= 0x4B800000 && id < 0x4C000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "zip");
    } else if (id >= 0x6E000000 && id < 0x6E800000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "png");
    } else if (id >= 0x6E800000 && id < 0x6F000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "png");
    } else if (id >= 0x6F000000 && id < 0x6F800000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "jpg");
    } else if (id >= 0x6F800000 && id < 0x70000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "jpg");
    } else if (id >= 0x70000000 && id < 0x70800000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "jpeg");
    } else if (id >= 0x70800000 && id < 0x71000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "jpeg");
    } else if (id >= 0x71000000 && id < 0x71800000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "bmp");
    } else if (id >= 0x71800000 && id < 0x72000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "bmp");
    } else if (id >= 0x72000000 && id < 0x72800000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "svg");
    } else if (id >= 0x72800000 && id < 0x73000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "svg");
    } else if (id >= 0x74000000 && id < 0x74800000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", flash_dir, id, "zip");
    } else if (id >= 0x74800000 && id < 0x75000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.%s", sd_dir, id, "zip");
    } else {
        return NULL;
    }
    return path_buf;
#endif
}
