#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE
/*Generate Code, Do NOT Edit!*/
#include "../gui_guider.h"
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
    case GUI_RES_FANGZHENGKAITIJIANTI_1_22_TTF:
        return "E:\\1111\\ac792\\ui_prj\\Application12\\sdk\\ui_res\\flash\\rle\\font\\35000000.rle";
    case GUI_RES_FANGZHENGKAITIJIANTI_1_26_TTF:
        return "E:\\1111\\ac792\\ui_prj\\Application12\\sdk\\ui_res\\flash\\rle\\font\\35000001.rle";
    case GUI_RES_FANGZHENGKAITIJIANTI_1_18_TTF:
        return "E:\\1111\\ac792\\ui_prj\\Application12\\sdk\\ui_res\\flash\\rle\\font\\35000002.rle";
    case GUI_RES_MONTSERRATMEDIUM_18_TTF:
        return "E:\\1111\\ac792\\ui_prj\\Application12\\sdk\\ui_res\\flash\\rle\\font\\35000003.rle";
    case GUI_RES_FANGZHENGKAITIJIANTI_1_48_TTF:
        return "E:\\1111\\ac792\\ui_prj\\Application12\\sdk\\ui_res\\flash\\rle\\font\\35000004.rle";
    case GUI_RES_MONTSERRATMEDIUM_24_TTF:
        return "E:\\1111\\ac792\\ui_prj\\Application12\\sdk\\ui_res\\flash\\rle\\font\\35000005.rle";
    case GUI_RES_MONTSERRATMEDIUM_12_TTF:
        return "E:\\1111\\ac792\\ui_prj\\Application12\\sdk\\ui_res\\flash\\rle\\font\\35000006.rle";
    case GUI_RES_MONTSERRATMEDIUM_22_TTF:
        return "E:\\1111\\ac792\\ui_prj\\Application12\\sdk\\ui_res\\flash\\rle\\font\\35000007.rle";
    case GUI_RES_FANGZHENGKAITIJIANTI_1_24_TTF:
        return "E:\\1111\\ac792\\ui_prj\\Application12\\sdk\\ui_res\\flash\\rle\\font\\35000008.rle";
    case GUI_RES_FANGZHENGKAITIJIANTI_1_16_TTF:
        return "E:\\1111\\ac792\\ui_prj\\Application12\\sdk\\ui_res\\flash\\rle\\font\\35000009.rle";
    case GUI_RES_MONTSERRATMEDIUM_16_TTF:
        return "E:\\1111\\ac792\\ui_prj\\Application12\\sdk\\ui_res\\flash\\rle\\font\\3500000a.rle";
    case GUI_RES_MONTSERRATMEDIUM_20_TTF:
        return "E:\\1111\\ac792\\ui_prj\\Application12\\sdk\\ui_res\\flash\\rle\\font\\3500000b.rle";
    case GUI_RES_S_PC_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\video_page\\USB\\s_PC.png";
    case GUI_RES_S_MASS_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\video_page\\USB\\s_MASS.png";
    case GUI_RES_I_REC_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\rec\\rec_scan\\i_rec.png";
    case GUI_RES_CYCLIC_VIDEO_3_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\rec\\rec_scan\\cyclic_video_3.png";
    case GUI_RES_EXP_A0_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\rec\\rec_scan\\exp_a0.png";
    case GUI_RES_I_MOT_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\rec\\rec_scan\\i_mot.png";
    case GUI_RES_I_TEAR_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\rec\\rec_scan\\i_tear.png";
    case GUI_RES_MIC_ON_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\rec\\rec_scan\\mic_on.png";
    case GUI_RES_I_HDR_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\rec\\rec_scan\\i_hdr.png";
    case GUI_RES_I_GRA_L_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\rec\\rec_scan\\i_gra_l.png";
    case GUI_RES_PARK_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\rec\\rec_scan\\park.png";
    case GUI_RES_BAT_FULL_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\rec\\rec_scan\\bat_full.png";
    case GUI_RES_CARD_ONLINE_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\rec\\rec_scan\\card_online.png";
    case GUI_RES_RED_CIRCLE_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\rec\\rec_scan\\red_circle.png";
    case GUI_RES_FLIG_ON_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\rec\\rec_scan\\flig_on.png";
    case GUI_RES_KEY_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\rec\\rec_scan\\key.png";
    case GUI_RES_M_SOLU_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\rec\\rec_menu\\m_solu.png";
    case GUI_RES_M_TWO_REC_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\rec\\rec_menu\\m_two_rec.png";
    case GUI_RES_M_CYC_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\rec\\rec_menu\\m_cyc.png";
    case GUI_RES_REC_NOCYC_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\rec\\rec_menu\\rec_nocyc.png";
    case GUI_RES_M_HDR_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\rec\\rec_menu\\m_hdr.png";
    case GUI_RES_M_EXP_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\rec\\rec_menu\\m_exp.png";
    case GUI_RES_M_MOT_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\rec\\rec_menu\\m_mot.png";
    case GUI_RES_M_AUD_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\rec\\rec_menu\\m_aud.png";
    case GUI_RES_M_DAT_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\rec\\rec_menu\\m_dat.png";
    case GUI_RES_M_GRA_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\rec\\rec_menu\\m_gra.png";
    case GUI_RES_M_PARK_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\rec\\rec_menu\\m_park.png";
    case GUI_RES_M_NUM_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\rec\\rec_menu\\m_num.png";
    case GUI_RES_M_FLIG_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\rec\\rec_menu\\m_flig.png";
    case GUI_RES_MENU_STA_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\rec\\rec_menu\\menu_sta.png";
    case GUI_RES_REC_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\rec\\rec_menu\\rec.png";
    case GUI_RES_SET_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\rec\\rec_menu\\set.png";
    case GUI_RES_LEFT_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\direc\\left.png";
    case GUI_RES_UP_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\direc\\up.png";
    case GUI_RES_DOWN_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\direc\\down.png";
    case GUI_RES_RIGHT_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\direc\\right.png";
    case GUI_RES_POP_UP_WINDOW_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\video_page\\pop_up_window.png";
    case GUI_RES_FLIG_ON_1_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\video_page\\flig_on.png";
    case GUI_RES_ASTERN_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\video_page\\astern.png";
    case GUI_RES_LCD_AU_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\sys_menu\\lcd_au.png";
    case GUI_RES_AUTO_OFF_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\sys_menu\\auto_off.png";
    case GUI_RES_HZ_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\sys_menu\\hz.png";
    case GUI_RES_KEY_V_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\sys_menu\\key_v.png";
    case GUI_RES_LANGUAGE_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\sys_menu\\language.png";
    case GUI_RES_TIME_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\sys_menu\\time.png";
    case GUI_RES_TV_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\sys_menu\\tv.png";
    case GUI_RES_MDK_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\sys_menu\\mdk.png";
    case GUI_RES_DEF_SET_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\sys_menu\\def_set.png";
    case GUI_RES_VERSION_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\sys_menu\\version.png";
    case GUI_RES_NUM_L_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\sys_menu\\NUM_l.png";
    case GUI_RES_NUM_D_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\sys_menu\\NUM_d.png";
    case GUI_RES_TP_3_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\photo\\photo_scan\\tp_3.png";
    case GUI_RES_TP_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\photo\\photo_scan\\tp.png";
    case GUI_RES_AWB_AUTO_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\photo\\photo_scan\\awb_auto.png";
    case GUI_RES_ISO_AUTO_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\photo\\photo_scan\\iso_auto.png";
    case GUI_RES_Q1_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\photo\\photo_scan\\q1.png";
    case GUI_RES_DL2_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\photo\\photo_scan\\dl2.png";
    case GUI_RES_SHAKE_OFF_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\photo\\photo_scan\\shake_off.png";
    case GUI_RES_LIANP_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\photo\\photo_scan\\lianp.png";
    case GUI_RES_PAIZ_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\photo\\photo_menu\\paiz.png";
    case GUI_RES_LIANP_1_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\photo\\photo_menu\\lianp.png";
    case GUI_RES_IMG_Q_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\photo\\photo_menu\\img_q.png";
    case GUI_RES_RUIDU_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\photo\\photo_menu\\ruidu.png";
    case GUI_RES_COLOR_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\photo\\photo_menu\\color.png";
    case GUI_RES_ISO_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\photo\\photo_menu\\iso.png";
    case GUI_RES_SHAKE_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\photo\\photo_menu\\shake.png";
    case GUI_RES_SCAN_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\photo\\photo_menu\\scan.png";
    case GUI_RES_PHOTO_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\rec\\rec_menu\\photo.png";
    case GUI_RES_VIDEO_PLAY_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\video_play.png";
    case GUI_RES_VIDEO_PAUSE_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\video_pause.png";
    case GUI_RES_SKIP_PREVIOUS_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\skip_previous.png";
    case GUI_RES_SKIP_NEXT_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\skip_next.png";
    case GUI_RES_VOLUMELOUDER_SOLID_1_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\volumeLouder_solid_1.png";
    case GUI_RES_VOLUMEMUTE_SOLID_1_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\volumeMute_solid_1.png";
    case GUI_RES_PHOTO_1_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\PHOTO.png";
    case GUI_RES_PHOTO_ON_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\photo_on.png";
    case GUI_RES_UP_1_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\up.png";
    case GUI_RES_DOWN_1_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\down.png";
    case GUI_RES_DELET_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\dec\\delet.png";
    case GUI_RES_PROTECT_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\dec\\protect.png";
    case GUI_RES_PLAY_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\rec\\rec_menu\\play.png";
    case GUI_RES_VIDEO_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\dec\\video.png";
    case GUI_RES_PHOTO_2_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\dec\\photo.png";
    case GUI_RES_CARD_OFFLINE_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\rec\\rec_scan\\card_offline.png";
    case GUI_RES_PLAY_1_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\dec\\play.png";
    case GUI_RES_PAUSE_PNG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\dec\\pause.png";
    case RES_0:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\video_page\\battery\\0.png";
    case RES_1:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\video_page\\battery\\1.png";
    case RES_2:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\video_page\\battery\\2.png";
    case RES_3:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\video_page\\battery\\3.png";
    case RES_CHARGING:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\video_page\\battery\\charging.png";
    case RES_FULL:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\video_page\\battery\\full.png";
    case RES_GRAVITY_SENSOR_LOW:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\video_page\\gravity_sensor_low.png";
    case RES_GRAVITY_SENSOR_MIDLLER:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\video_page\\gravity_sensor_midller.png";
    case RES_GRAVITY_SENSOR_HIGH:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\video_page\\gravity_sensor_high.png";
    case RES_INTERVAL_VIDEO_CLOSE:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\video_page\\interval_video_close.png";
    case RES_INTERVAL_VIDEO_500:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\video_page\\interval_video_500.png";
    case RES_INTERVAL_VIDEO_200:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\video_page\\interval_video_200.png";
    case RES_INTERVAL_VIDEO_100:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\video_page\\interval_video_100.png";
    case RES_SD:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\video_page\\SD.png";
    case RES_SD_CLOSE:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\video_page\\SD_close.png";
    case RES_SOUND:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\video_page\\sound.png";
    case RES_SOUND_CLOSE:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\video_page\\sound_close.png";
    case RES_EXPOSURE:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\video_page\\menu_icon\\exposure.png";
    case RES_DOUBLE_VIDEO:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\video_page\\menu_icon\\double_video.png";
    case RES_DATE:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\video_page\\menu_icon\\date.png";
    case RES_CYCLIC_VIDEO:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\video_page\\menu_icon\\cyclic_video.png";
    case RES_CHECK_SPORT:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\video_page\\menu_icon\\check_sport.png";
    case RES_CAR_NUM:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\video_page\\menu_icon\\car_num.png";
    case RES_GRAVITY_SENSOR:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\video_page\\menu_icon\\gravity_sensor.png";
    case RES_HDR:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\video_page\\menu_icon\\HDR.png";
    case RES_INTERVAL_VIDEO:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\video_page\\menu_icon\\interval_video.png";
    case RES_RESOLUTION_RATIO:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\video_page\\menu_icon\\resolution_ratio.png";
    case RES_SOUND_1:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\video_page\\menu_icon\\sound.png";
    case RES_STOPPING_MONITOR:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\video_page\\menu_icon\\stopping_monitor.png";
    case RES_AUTO_OFF:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\video_page\\sys_setting\\icon\\auto_off.png";
    case RES_CAR_NUM_1:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\video_page\\sys_setting\\icon\\car_num.png";
    case RES_FLIG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\video_page\\sys_setting\\icon\\flig.png";
    case RES_FORMAT:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\video_page\\sys_setting\\icon\\format.png";
    case RES_FREQUENCY:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\video_page\\sys_setting\\icon\\frequency.png";
    case RES_LANE:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\video_page\\sys_setting\\icon\\lane.png";
    case RES_LANGUAGES:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\video_page\\sys_setting\\icon\\languages.png";
    case RES_LCD_OFF:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\video_page\\sys_setting\\icon\\lcd_off.png";
    case RES_RESET:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\video_page\\sys_setting\\icon\\reset.png";
    case RES_VERSION:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\video_page\\sys_setting\\icon\\version.png";
    case RES_VOICE:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\video_page\\sys_setting\\icon\\voice.png";
    case RES_DATE_1:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\video_page\\sys_setting\\icon\\date.png";
    case RES_AWB:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\video_page\\awb.png";
    case RES_AWB_FLUORESCENT_LAMP:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\video_page\\awb_fluorescent_lamp.png";
    case RES_AWB_OSRAM_LAMP:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\video_page\\awb_osram_lamp.png";
    case RES_AWB_SUN_CLOUDY:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\video_page\\awb_sun_cloudy.png";
    case RES_AWB_SUN_LIGHT:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\video_page\\awb_sun_light.png";
    case RES_HIGH:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\video_page\\high.png";
    case RES_LOW:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\video_page\\low.png";
    case RES_MIDDLE:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\video_page\\middle.png";
    case RES_TIMING_PHOTO_2:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\video_page\\timing_photo_2.png";
    case RES_TIMING_PHOTO_5:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\video_page\\timing_photo_5.png";
    case RES_TIMING_PHOTO_10:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\video_page\\timing_photo_10.png";
    case RES_FILE_DIR:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\file_dir.png";
    case RES_DELETE:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\DELETE.png";
    case RES_DELETE_ON:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\delete_on.png";
    case RES_EDIT:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\EDIT.png";
    case RES_EDITOR_ON:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\editor_on.png";
    case RES_HOME:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\HOME.png";
    case RES_HOME_ON:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\home_on.png";
    case RES_LOCK:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LOCK.png";
    case RES_LOCK_ON:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\lock_on.png";
    case RES_PHOTO:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\PHOTO.png";
    case RES_PHOTO_ON:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\photo_on.png";
    case RES_RETURN:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\RETURN.png";
    case RES_RETURN_ON:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\return_on.png";
    case RES_SELETE:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\SELETE.png";
    case RES_UNLOCK:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\UNLOCK.png";
    case RES_UNLOCK_ON:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\unlock_on.png";
    case RES_VIDEO:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\VIDEO.png";
    case RES_VOLUMELOUDER_SOLID_1:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\volumeLouder_solid_1.png";
    case RES_VIDEO_PAUSE:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\video_pause.png";
    case RES_SKIP_NEXT:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\skip_next.png";
    case RES_SKIP_PREVIOUS:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\skip_previous.png";
    case RES_PLAY:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\play.png";
    case RES_VIDEO_PLAY:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\video_play.png";
    case RES_VOLUMEMUTE_SOLID_1:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\volumeMute_solid_1.png";
    case RES_SOFTWARE:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\video_page\\menu_icon\\software.png";
    case RES_LOCK_FLAG:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\lock_flag.png";
    case RES_CYCLIC_VIDEO_10:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\rec\\rec_scan\\cyclic_video_10.png";
    case RES_CYCLIC_VIDEO_3:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\rec\\rec_scan\\cyclic_video_3.png";
    case RES_CYCLIC_VIDEO_5:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\rec\\rec_scan\\cyclic_video_5.png";
    case RES_MIC_OFF:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\rec\\rec_scan\\mic_off.png";
    case RES_MIC_ON:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\rec\\rec_scan\\mic_on.png";
    case RES_I_GRA_H:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\rec\\rec_scan\\i_gra_h.png";
    case RES_I_GRA_M:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\rec\\rec_scan\\i_gra_m.png";
    case RES_I_GRA_L:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\rec\\rec_scan\\i_gra_l.png";
    case RES_BAT_0:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\rec\\rec_scan\\bat_0.png";
    case RES_BAT_L:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\rec\\rec_scan\\bat_l.png";
    case RES_BAT_HALF:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\rec\\rec_scan\\bat_half.png";
    case RES_BAT_H:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\rec\\rec_scan\\bat_h.png";
    case RES_CHAR:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\rec\\rec_scan\\char.png";
    case RES_CARD_OFFLINE:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\rec\\rec_scan\\card_offline.png";
    case RES_CARD_ONLINE:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\rec\\rec_scan\\card_online.png";
    case RES_PARK:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\rec\\rec_scan\\park.png";
    case RES_EXP_A3:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\rec\\rec_scan\\exp_a3.png";
    case RES_EXP_A2:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\rec\\rec_scan\\exp_a2.png";
    case RES_EXP_A1:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\rec\\rec_scan\\exp_a1.png";
    case RES_EXP_A0:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\rec\\rec_scan\\exp_a0.png";
    case RES_EXP_D1:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\rec\\rec_scan\\exp_d1.png";
    case RES_EXP_D2:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\rec\\rec_scan\\exp_d2.png";
    case RES_EXP_D3:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\rec\\rec_scan\\exp_d3.png";
    case RES_AWB_AUTO:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\photo\\photo_scan\\awb_auto.png";
    case RES_AWB_CLOUDY:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\photo\\photo_scan\\awb_cloudy.png";
    case RES_AWB_FINE:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\photo\\photo_scan\\awb_fine.png";
    case RES_AWB_FLUORESCENT_LAMP_1:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\photo\\photo_scan\\awb_fluorescent_lamp.png";
    case RES_AWB_TUNGSTEN_LAMP:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\photo\\photo_scan\\awb_tungsten_lamp.png";
    case RES_ISO_1:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\photo\\photo_scan\\iso_1.png";
    case RES_ISO_2:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\photo\\photo_scan\\iso_2.png";
    case RES_ISO_4:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\photo\\photo_scan\\iso_4.png";
    case RES_ISO_AUTO:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\photo\\photo_scan\\iso_auto.png";
    case RES_Q1:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\photo\\photo_scan\\q1.png";
    case RES_Q2:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\photo\\photo_scan\\q2.png";
    case RES_Q3:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\photo\\photo_scan\\q3.png";
    case RES_DL2:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\photo\\photo_scan\\dl2.png";
    case RES_DL5:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\photo\\photo_scan\\dl5.png";
    case RES_DL10:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\photo\\photo_scan\\dl10.png";
    case RES_SHAKE_OFF:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\photo\\photo_scan\\shake_off.png";
    case RES_SHAKE_ON:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\photo\\photo_scan\\shake_on.png";
    case RES_BAT_FULL:
        return "A:\\1111\\ac792\\ui_prj\\Application12\\import\\image\\LY_UI\\rec\\rec_scan\\bat_full.png";
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

#endif
