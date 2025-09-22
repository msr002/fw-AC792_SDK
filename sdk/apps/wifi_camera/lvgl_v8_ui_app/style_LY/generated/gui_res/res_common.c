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
const char sd_dir[] = "storage/sd0/C/ui/";
const char flash_dir[] = "mnt/sdfile/EXT_RESERVED/uipackres/ui/";
char path_buf[max(sizeof(sd_dir), sizeof(flash_dir)) + 20];
#endif

char *gui_get_res_path(int32_t id)
{
#if LV_USE_GUIBUILDER_SIMULATOR
    switch (id) {
    case GUI_RES_FANGZHENGKAITIJIANTI_1_22_TTF:
        return "E:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000000.rle";
    case GUI_RES_FANGZHENGKAITIJIANTI_1_26_TTF:
        return "E:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000001.rle";
    case GUI_RES_FANGZHENGKAITIJIANTI_1_18_TTF:
        return "E:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000002.rle";
    case GUI_RES_MONTSERRATMEDIUM_18_TTF:
        return "E:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000003.rle";
    case GUI_RES_FANGZHENGKAITIJIANTI_1_48_TTF:
        return "E:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000004.rle";
    case GUI_RES_MONTSERRATMEDIUM_24_TTF:
        return "E:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000005.rle";
    case GUI_RES_MONTSERRATMEDIUM_12_TTF:
        return "E:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000006.rle";
    case GUI_RES_MONTSERRATMEDIUM_22_TTF:
        return "E:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000007.rle";
    case GUI_RES_FANGZHENGKAITIJIANTI_1_24_TTF:
        return "E:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000008.rle";
    case GUI_RES_FANGZHENGKAITIJIANTI_1_16_TTF:
        return "E:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000009.rle";
    case GUI_RES_MONTSERRATMEDIUM_16_TTF:
        return "E:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\3500000a.rle";
    case GUI_RES_MONTSERRATMEDIUM_20_TTF:
        return "E:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\3500000b.rle";
    case GUI_RES_MONTSERRATMEDIUM_30_TTF:
        return "E:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\3500000c.rle";
    case GUI_RES_MONTSERRATMEDIUM_32_TTF:
        return "E:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\3500000d.rle";
    case GUI_RES_MONTSERRATMEDIUM_28_TTF:
        return "E:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\3500000e.rle";
    case GUI_RES_FANGSONG_16_TTF:
        return "E:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\3500000f.rle";
    case GUI_RES_FANGSONG_24_TTF:
        return "E:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000010.rle";
    case GUI_RES_TIMESNEWROMANPSMT_16_TTF:
        return "E:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000011.rle";
    case GUI_RES_TIMESNEWROMANPSMT_24_TTF:
        return "E:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000012.rle";
    case GUI_RES_SEGOEUI_16_TTF:
        return "E:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000013.rle";
    case GUI_RES_SEGOEUI_24_TTF:
        return "E:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000014.rle";
    case GUI_RES_LEELAWADEEUI_16_TTF:
        return "E:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000015.rle";
    case GUI_RES_LEELAWADEEUI_24_TTF:
        return "E:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000016.rle";
    case GUI_RES_MALGUNGOTHIC_16_TTF:
        return "E:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000017.rle";
    case GUI_RES_MALGUNGOTHIC_24_TTF:
        return "E:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000018.rle";
    case GUI_RES_MS_GOTHIC_16_TTF:
        return "E:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\35000019.rle";
    case GUI_RES_CALIBRI_16_TTF:
        return "E:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\3500001a.rle";
    case GUI_RES_CALIBRI_24_TTF:
        return "E:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\sdk\\ui_res\\flash\\rle\\font\\3500001b.rle";
    case GUI_RES_S_PC_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\USB\\s_PC.png";
    case GUI_RES_S_MASS_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\USB\\s_MASS.png";
    case GUI_RES_I_REC_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\i_rec.png";
    case GUI_RES_CYCLIC_VIDEO_3_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\cyclic_video_3.png";
    case GUI_RES_EXP_A0_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\exp_a0.png";
    case GUI_RES_I_MOT_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\i_mot.png";
    case GUI_RES_I_TEAR_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\i_tear.png";
    case GUI_RES_MIC_ON_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\mic_on.png";
    case GUI_RES_I_HDR_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\i_hdr.png";
    case GUI_RES_I_GRA_L_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\i_gra_l.png";
    case GUI_RES_PARK_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\park.png";
    case GUI_RES_BAT_FULL_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\bat_full.png";
    case GUI_RES_CARD_ONLINE_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\card_online.png";
    case GUI_RES_RED_CIRCLE_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\red_circle.png";
    case GUI_RES_FLIG_ON_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\flig_on.png";
    case GUI_RES_KEY_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\key.png";
    case GUI_RES_M_SOLU_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_menu\\m_solu.png";
    case GUI_RES_M_TWO_REC_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_menu\\m_two_rec.png";
    case GUI_RES_M_CYC_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_menu\\m_cyc.png";
    case GUI_RES_REC_NOCYC_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_menu\\rec_nocyc.png";
    case GUI_RES_M_HDR_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_menu\\m_hdr.png";
    case GUI_RES_M_EXP_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_menu\\m_exp.png";
    case GUI_RES_M_MOT_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_menu\\m_mot.png";
    case GUI_RES_M_AUD_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_menu\\m_aud.png";
    case GUI_RES_M_DAT_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_menu\\m_dat.png";
    case GUI_RES_M_GRA_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_menu\\m_gra.png";
    case GUI_RES_M_PARK_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_menu\\m_park.png";
    case GUI_RES_M_NUM_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_menu\\m_num.png";
    case GUI_RES_M_FLIG_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_menu\\m_flig.png";
    case GUI_RES_MENU_STA_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_menu\\menu_sta.png";
    case GUI_RES_REC_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_menu\\rec.png";
    case GUI_RES_SET_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_menu\\set.png";
    case GUI_RES_LEFT_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\direc\\left.png";
    case GUI_RES_UP_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\direc\\up.png";
    case GUI_RES_DOWN_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\direc\\down.png";
    case GUI_RES_RIGHT_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\direc\\right.png";
    case GUI_RES_POP_UP_WINDOW_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\pop_up_window.png";
    case GUI_RES_FLIG_ON_1_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\flig_on.png";
    case GUI_RES_ASTERN_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\astern.png";
    case GUI_RES_LCD_AU_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\sys_menu\\lcd_au.png";
    case GUI_RES_AUTO_OFF_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\sys_menu\\auto_off.png";
    case GUI_RES_HZ_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\sys_menu\\hz.png";
    case GUI_RES_KEY_V_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\sys_menu\\key_v.png";
    case GUI_RES_LANGUAGE_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\sys_menu\\language.png";
    case GUI_RES_TIME_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\sys_menu\\time.png";
    case GUI_RES_TV_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\sys_menu\\tv.png";
    case GUI_RES_MDK_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\sys_menu\\mdk.png";
    case GUI_RES_DEF_SET_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\sys_menu\\def_set.png";
    case GUI_RES_VERSION_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\sys_menu\\version.png";
    case GUI_RES_NUM_L_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\sys_menu\\NUM_l.png";
    case GUI_RES_NUM_D_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\sys_menu\\NUM_d.png";
    case GUI_RES_TP_3_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\photo\\photo_scan\\tp_3.png";
    case GUI_RES_TP_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\photo\\photo_scan\\tp.png";
    case GUI_RES_AWB_AUTO_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\photo\\photo_scan\\awb_auto.png";
    case GUI_RES_ISO_AUTO_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\photo\\photo_scan\\iso_auto.png";
    case GUI_RES_Q1_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\photo\\photo_scan\\q1.png";
    case GUI_RES_DL2_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\photo\\photo_scan\\dl2.png";
    case GUI_RES_SHAKE_OFF_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\photo\\photo_scan\\shake_off.png";
    case GUI_RES_LIANP_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\photo\\photo_scan\\lianp.png";
    case GUI_RES_PAIZ_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\photo\\photo_menu\\paiz.png";
    case GUI_RES_LIANP_1_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\photo\\photo_menu\\lianp.png";
    case GUI_RES_IMG_Q_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\photo\\photo_menu\\img_q.png";
    case GUI_RES_RUIDU_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\photo\\photo_menu\\ruidu.png";
    case GUI_RES_COLOR_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\photo\\photo_menu\\color.png";
    case GUI_RES_ISO_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\photo\\photo_menu\\iso.png";
    case GUI_RES_SHAKE_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\photo\\photo_menu\\shake.png";
    case GUI_RES_SCAN_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\photo\\photo_menu\\scan.png";
    case GUI_RES_PHOTO_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_menu\\photo.png";
    case GUI_RES_VIDEO_PLAY_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\video_play.png";
    case GUI_RES_VIDEO_PAUSE_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\video_pause.png";
    case GUI_RES_SKIP_PREVIOUS_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\skip_previous.png";
    case GUI_RES_SKIP_NEXT_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\skip_next.png";
    case GUI_RES_VOLUMELOUDER_SOLID_1_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\volumeLouder_solid_1.png";
    case GUI_RES_VOLUMEMUTE_SOLID_1_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\volumeMute_solid_1.png";
    case GUI_RES_PHOTO_1_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\PHOTO.png";
    case GUI_RES_PHOTO_ON_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\photo_on.png";
    case GUI_RES_UP_1_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\up.png";
    case GUI_RES_DOWN_1_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\down.png";
    case GUI_RES_DELET_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\dec\\delet.png";
    case GUI_RES_PROTECT_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\dec\\protect.png";
    case GUI_RES_PLAY_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_menu\\play.png";
    case GUI_RES_VIDEO_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\dec\\video.png";
    case GUI_RES_PHOTO_2_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\dec\\photo.png";
    case GUI_RES_CARD_OFFLINE_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\card_offline.png";
    case GUI_RES_PLAY_1_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\dec\\play.png";
    case GUI_RES_PAUSE_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\dec\\pause.png";
    case GUI_RES_SPORT_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\SPORT.png";
    case GUI_RES_TTFAR_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\TTFAR.png";
    case GUI_RES_FREE_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\FREE.png";
    case GUI_RES_TEM_01_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\main\\tem_01.png";
    case GUI_RES_LAMP_25_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_25.png";
    case GUI_RES_LAMP_26_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_26.png";
    case GUI_RES_LAMP_23_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_23.png";
    case GUI_RES_LAMP_24_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_24.png";
    case GUI_RES_LAMP_29_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_29.png";
    case GUI_RES_LAMP_30_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_30.png";
    case GUI_RES_LAMP_27_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_27.png";
    case GUI_RES_LAMP_28_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_28.png";
    case GUI_RES_READY_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\READY.png";
    case GUI_RES_LAMP_19_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_19.png";
    case GUI_RES_LAMP_20_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_20.png";
    case GUI_RES_LAMP_21_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_21.png";
    case GUI_RES_LAMP_22_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_22.png";
    case GUI_RES_BAT_001_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_001.png";
    case GUI_RES_BAT_002_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_002.png";
    case GUI_RES_BAT_003_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_003.png";
    case GUI_RES_BAT_004_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_004.png";
    case GUI_RES_BAT_005_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_005.png";
    case GUI_RES_BAT_006_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_006.png";
    case GUI_RES_BAT_007_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_007.png";
    case GUI_RES_BAT_008_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_008.png";
    case GUI_RES_BAT_009_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_009.png";
    case GUI_RES_BAT_010_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_010.png";
    case GUI_RES_BAT_011_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_011.png";
    case GUI_RES_BAT_012_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_012.png";
    case GUI_RES_BAT_013_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_013.png";
    case GUI_RES_BAT_014_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_014.png";
    case GUI_RES_BAT_015_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_015.png";
    case GUI_RES_BAT_016_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_016.png";
    case GUI_RES_BAT_017_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_017.png";
    case GUI_RES_BAT_018_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_018.png";
    case GUI_RES_BAT_019_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_019.png";
    case GUI_RES_BAT_020_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_020.png";
    case GUI_RES_BAT_021_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_021.png";
    case GUI_RES_BAT_022_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_022.png";
    case GUI_RES_BAT_023_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_023.png";
    case GUI_RES_BAT_024_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_024.png";
    case GUI_RES_BAT_025_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_025.png";
    case GUI_RES_BAT_026_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_026.png";
    case GUI_RES_BAT_027_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_027.png";
    case GUI_RES_BAT_028_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_028.png";
    case GUI_RES_BAT_029_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_029.png";
    case GUI_RES_BAT_030_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_030.png";
    case GUI_RES_BAT_031_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_031.png";
    case GUI_RES_BAT_032_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_032.png";
    case GUI_RES_BAT_033_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_033.png";
    case GUI_RES_BAT_034_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_034.png";
    case GUI_RES_BAT_035_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_035.png";
    case GUI_RES_BAT_036_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_036.png";
    case GUI_RES_BAT_037_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_037.png";
    case GUI_RES_BAT_038_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_038.png";
    case GUI_RES_BAT_039_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_039.png";
    case GUI_RES_BAT_040_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_040.png";
    case GUI_RES_BAT_041_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_041.png";
    case GUI_RES_BAT_042_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_042.png";
    case GUI_RES_BAT_043_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_043.png";
    case GUI_RES_BAT_044_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_044.png";
    case GUI_RES_BAT_045_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_045.png";
    case GUI_RES_BAT_046_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_046.png";
    case GUI_RES_BAT_047_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_047.png";
    case GUI_RES_BAT_048_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_048.png";
    case GUI_RES_BAT_049_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_049.png";
    case GUI_RES_BAT_050_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_050.png";
    case GUI_RES_BAT_051_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_051.png";
    case GUI_RES_BAT_052_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_052.png";
    case GUI_RES_BAT_053_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_053.png";
    case GUI_RES_BAT_054_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_054.png";
    case GUI_RES_BAT_055_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_055.png";
    case GUI_RES_BAT_056_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_056.png";
    case GUI_RES_BAT_057_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_057.png";
    case GUI_RES_BAT_058_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_058.png";
    case GUI_RES_BAT_059_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_059.png";
    case GUI_RES_BAT_060_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_060.png";
    case GUI_RES_BAT_061_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_061.png";
    case GUI_RES_BAT_062_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_062.png";
    case GUI_RES_BAT_063_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_063.png";
    case GUI_RES_BAT_064_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_064.png";
    case GUI_RES_BAT_065_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_065.png";
    case GUI_RES_BAT_066_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_066.png";
    case GUI_RES_BAT_067_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_067.png";
    case GUI_RES_BAT_068_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_068.png";
    case GUI_RES_BAT_069_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_069.png";
    case GUI_RES_BAT_070_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_070.png";
    case GUI_RES_BAT_071_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_071.png";
    case GUI_RES_BAT_072_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_072.png";
    case GUI_RES_BAT_073_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_073.png";
    case GUI_RES_BAT_074_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_074.png";
    case GUI_RES_BAT_075_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_075.png";
    case GUI_RES_BAT_076_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_076.png";
    case GUI_RES_BAT_077_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_077.png";
    case GUI_RES_BAT_078_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_078.png";
    case GUI_RES_BAT_079_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_079.png";
    case GUI_RES_BAT_080_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_080.png";
    case GUI_RES_BAT_081_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_081.png";
    case GUI_RES_BAT_082_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_082.png";
    case GUI_RES_BAT_083_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_083.png";
    case GUI_RES_BAT_084_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_084.png";
    case GUI_RES_BAT_085_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_085.png";
    case GUI_RES_BAT_086_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_086.png";
    case GUI_RES_BAT_087_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_087.png";
    case GUI_RES_BAT_088_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_088.png";
    case GUI_RES_BAT_089_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_089.png";
    case GUI_RES_BAT_090_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_090.png";
    case GUI_RES_BAT_091_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_091.png";
    case GUI_RES_BAT_092_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_092.png";
    case GUI_RES_BAT_093_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_093.png";
    case GUI_RES_BAT_094_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_094.png";
    case GUI_RES_BAT_095_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_095.png";
    case GUI_RES_BAT_096_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_096.png";
    case GUI_RES_BAT_097_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_097.png";
    case GUI_RES_BAT_098_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_098.png";
    case GUI_RES_BAT_099_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_099.png";
    case GUI_RES_BAT_100_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\battery\\bat_100.png";
    case GUI_RES_LAMP_01_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_01.png";
    case GUI_RES_TIPS_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\tips\\tips.png";
    case GUI_RES_ROTATE_00000_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\meter\\rotate_00000.png";
    case GUI_RES_ROTATE_00001_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\meter\\rotate_00001.png";
    case GUI_RES_ROTATE_00002_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\meter\\rotate_00002.png";
    case GUI_RES_ROTATE_00003_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\meter\\rotate_00003.png";
    case GUI_RES_ROTATE_00004_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\meter\\rotate_00004.png";
    case GUI_RES_ROTATE_00005_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\meter\\rotate_00005.png";
    case GUI_RES_ROTATE_00006_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\meter\\rotate_00006.png";
    case GUI_RES_ROTATE_00007_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\meter\\rotate_00007.png";
    case GUI_RES_ROTATE_00010_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\meter\\rotate_00010.png";
    case GUI_RES_ROTATE_00011_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\meter\\rotate_00011.png";
    case GUI_RES_ROTATE_00012_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\meter\\rotate_00012.png";
    case GUI_RES_ROTATE_00013_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\meter\\rotate_00013.png";
    case GUI_RES_ROTATE_00014_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\meter\\rotate_00014.png";
    case GUI_RES_ROTATE_00015_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\meter\\rotate_00015.png";
    case GUI_RES_ROTATE_00016_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\meter\\rotate_00016.png";
    case GUI_RES_ROTATE_00017_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\meter\\rotate_00017.png";
    case GUI_RES_ROTATE_00020_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\meter\\rotate_00020.png";
    case GUI_RES_ROTATE_00021_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\meter\\rotate_00021.png";
    case GUI_RES_ROTATE_00022_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\meter\\rotate_00022.png";
    case GUI_RES_ROTATE_00023_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\meter\\rotate_00023.png";
    case GUI_RES_ROTATE_00024_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\meter\\rotate_00024.png";
    case GUI_RES_ROTATE_00025_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\meter\\rotate_00025.png";
    case GUI_RES_NUMSN_0_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\speed\\gongli\\numsn_0.png";
    case GUI_RES_NUMSN_1_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\speed\\gongli\\numsn_1.png";
    case GUI_RES_NUMSN_2_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\speed\\gongli\\numsn_2.png";
    case GUI_RES_NUMSN_3_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\speed\\gongli\\numsn_3.png";
    case GUI_RES_NUMSN_4_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\speed\\gongli\\numsn_4.png";
    case GUI_RES_NUMSN_5_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\speed\\gongli\\numsn_5.png";
    case GUI_RES_NUMSN_6_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\speed\\gongli\\numsn_6.png";
    case GUI_RES_NUMSN_7_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\speed\\gongli\\numsn_7.png";
    case GUI_RES_NUMSN_8_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\speed\\gongli\\numsn_8.png";
    case GUI_RES_NUMSN_9_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\speed\\gongli\\numsn_9.png";
    case GUI_RES_READYC_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\gonglihouzhui\\readyc.png";
    case GUI_RES_LAMP_02_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_02.png";
    case GUI_RES_LAMP_06_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_06.png";
    case GUI_RES_LAMP_03_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_03.png";
    case GUI_RES_LAMP_07_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_07.png";
    case GUI_RES_LAMP_17_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_17.png";
    case GUI_RES_LAMP_04_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\alarm\\Lamp_04.png";
    case GUI_RES_GEAR_1_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\new\\englist\\shuzi\\dangwei\\gear_1.png";
    case GUI_RES_MILEAGE_KM_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\new\\englist\\shuzi\\licheng\\mileage_km.png";
    case GUI_RES_VOLTAGE_72V_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\new\\englist\\tubiao\\voltage_72v.png";
    case GUI_RES_LOGO_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\new\\englist\\tubiao\\logo.png";
    case GUI_RES_MILEAGE_TRIP_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\new\\englist\\shuzi\\licheng\\mileage_trip.png";
    case GUI_RES_SINGER100_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\music\\singer100.png";
    case GUI_RES_DIE1_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\music\\die1.png";
    case GUI_RES_ZHEN_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\music\\zhen.png";
    case GUI_RES_SINGER_PNG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\music\\singer.png";
    case RES_0:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\battery\\0.png";
    case RES_1:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\battery\\1.png";
    case RES_2:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\battery\\2.png";
    case RES_3:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\battery\\3.png";
    case RES_CHARGING:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\battery\\charging.png";
    case RES_FULL:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\battery\\full.png";
    case RES_GRAVITY_SENSOR_LOW:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\gravity_sensor_low.png";
    case RES_GRAVITY_SENSOR_MIDLLER:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\gravity_sensor_midller.png";
    case RES_GRAVITY_SENSOR_HIGH:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\gravity_sensor_high.png";
    case RES_INTERVAL_VIDEO_CLOSE:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\interval_video_close.png";
    case RES_INTERVAL_VIDEO_500:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\interval_video_500.png";
    case RES_INTERVAL_VIDEO_200:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\interval_video_200.png";
    case RES_INTERVAL_VIDEO_100:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\interval_video_100.png";
    case RES_SD:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\SD.png";
    case RES_SD_CLOSE:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\SD_close.png";
    case RES_SOUND:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\sound.png";
    case RES_SOUND_CLOSE:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\sound_close.png";
    case RES_EXPOSURE:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\menu_icon\\exposure.png";
    case RES_DOUBLE_VIDEO:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\menu_icon\\double_video.png";
    case RES_DATE:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\menu_icon\\date.png";
    case RES_CYCLIC_VIDEO:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\menu_icon\\cyclic_video.png";
    case RES_CHECK_SPORT:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\menu_icon\\check_sport.png";
    case RES_CAR_NUM:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\menu_icon\\car_num.png";
    case RES_GRAVITY_SENSOR:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\menu_icon\\gravity_sensor.png";
    case RES_HDR:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\menu_icon\\HDR.png";
    case RES_INTERVAL_VIDEO:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\menu_icon\\interval_video.png";
    case RES_RESOLUTION_RATIO:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\menu_icon\\resolution_ratio.png";
    case RES_SOUND_1:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\menu_icon\\sound.png";
    case RES_STOPPING_MONITOR:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\menu_icon\\stopping_monitor.png";
    case RES_AUTO_OFF:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\sys_setting\\icon\\auto_off.png";
    case RES_CAR_NUM_1:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\sys_setting\\icon\\car_num.png";
    case RES_FLIG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\sys_setting\\icon\\flig.png";
    case RES_FORMAT:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\sys_setting\\icon\\format.png";
    case RES_FREQUENCY:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\sys_setting\\icon\\frequency.png";
    case RES_LANE:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\sys_setting\\icon\\lane.png";
    case RES_LANGUAGES:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\sys_setting\\icon\\languages.png";
    case RES_LCD_OFF:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\sys_setting\\icon\\lcd_off.png";
    case RES_RESET:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\sys_setting\\icon\\reset.png";
    case RES_VERSION:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\sys_setting\\icon\\version.png";
    case RES_VOICE:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\sys_setting\\icon\\voice.png";
    case RES_DATE_1:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\sys_setting\\icon\\date.png";
    case RES_AWB:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\awb.png";
    case RES_AWB_FLUORESCENT_LAMP:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\awb_fluorescent_lamp.png";
    case RES_AWB_OSRAM_LAMP:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\awb_osram_lamp.png";
    case RES_AWB_SUN_CLOUDY:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\awb_sun_cloudy.png";
    case RES_AWB_SUN_LIGHT:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\awb_sun_light.png";
    case RES_HIGH:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\high.png";
    case RES_LOW:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\low.png";
    case RES_MIDDLE:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\middle.png";
    case RES_TIMING_PHOTO_2:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\timing_photo_2.png";
    case RES_TIMING_PHOTO_5:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\timing_photo_5.png";
    case RES_TIMING_PHOTO_10:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\timing_photo_10.png";
    case RES_FILE_DIR:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\file_dir.png";
    case RES_DELETE:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\DELETE.png";
    case RES_DELETE_ON:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\delete_on.png";
    case RES_EDIT:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\EDIT.png";
    case RES_EDITOR_ON:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\editor_on.png";
    case RES_HOME:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\HOME.png";
    case RES_HOME_ON:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\home_on.png";
    case RES_LOCK:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LOCK.png";
    case RES_LOCK_ON:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\lock_on.png";
    case RES_PHOTO:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\PHOTO.png";
    case RES_PHOTO_ON:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\photo_on.png";
    case RES_RETURN:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\RETURN.png";
    case RES_RETURN_ON:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\return_on.png";
    case RES_SELETE:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\SELETE.png";
    case RES_UNLOCK:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\UNLOCK.png";
    case RES_UNLOCK_ON:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\unlock_on.png";
    case RES_VIDEO:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\VIDEO.png";
    case RES_VOLUMELOUDER_SOLID_1:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\volumeLouder_solid_1.png";
    case RES_VIDEO_PAUSE:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\video_pause.png";
    case RES_SKIP_NEXT:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\skip_next.png";
    case RES_SKIP_PREVIOUS:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\skip_previous.png";
    case RES_PLAY:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\play.png";
    case RES_VIDEO_PLAY:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\video_play.png";
    case RES_VOLUMEMUTE_SOLID_1:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\volumeMute_solid_1.png";
    case RES_SOFTWARE:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\video_page\\menu_icon\\software.png";
    case RES_LOCK_FLAG:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\lock_flag.png";
    case RES_CYCLIC_VIDEO_10:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\cyclic_video_10.png";
    case RES_CYCLIC_VIDEO_3:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\cyclic_video_3.png";
    case RES_CYCLIC_VIDEO_5:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\cyclic_video_5.png";
    case RES_MIC_OFF:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\mic_off.png";
    case RES_MIC_ON:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\mic_on.png";
    case RES_I_GRA_H:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\i_gra_h.png";
    case RES_I_GRA_M:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\i_gra_m.png";
    case RES_I_GRA_L:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\i_gra_l.png";
    case RES_BAT_0:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\bat_0.png";
    case RES_BAT_L:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\bat_l.png";
    case RES_BAT_HALF:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\bat_half.png";
    case RES_BAT_H:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\bat_h.png";
    case RES_CHAR:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\char.png";
    case RES_CARD_OFFLINE:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\card_offline.png";
    case RES_CARD_ONLINE:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\card_online.png";
    case RES_PARK:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\park.png";
    case RES_EXP_A3:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\exp_a3.png";
    case RES_EXP_A2:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\exp_a2.png";
    case RES_EXP_A1:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\exp_a1.png";
    case RES_EXP_A0:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\exp_a0.png";
    case RES_EXP_D1:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\exp_d1.png";
    case RES_EXP_D2:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\exp_d2.png";
    case RES_EXP_D3:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\exp_d3.png";
    case RES_AWB_AUTO:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\photo\\photo_scan\\awb_auto.png";
    case RES_AWB_CLOUDY:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\photo\\photo_scan\\awb_cloudy.png";
    case RES_AWB_FINE:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\photo\\photo_scan\\awb_fine.png";
    case RES_AWB_FLUORESCENT_LAMP_1:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\photo\\photo_scan\\awb_fluorescent_lamp.png";
    case RES_AWB_TUNGSTEN_LAMP:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\photo\\photo_scan\\awb_tungsten_lamp.png";
    case RES_ISO_1:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\photo\\photo_scan\\iso_1.png";
    case RES_ISO_2:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\photo\\photo_scan\\iso_2.png";
    case RES_ISO_4:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\photo\\photo_scan\\iso_4.png";
    case RES_ISO_AUTO:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\photo\\photo_scan\\iso_auto.png";
    case RES_Q1:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\photo\\photo_scan\\q1.png";
    case RES_Q2:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\photo\\photo_scan\\q2.png";
    case RES_Q3:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\photo\\photo_scan\\q3.png";
    case RES_DL2:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\photo\\photo_scan\\dl2.png";
    case RES_DL5:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\photo\\photo_scan\\dl5.png";
    case RES_DL10:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\photo\\photo_scan\\dl10.png";
    case RES_SHAKE_OFF:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\photo\\photo_scan\\shake_off.png";
    case RES_SHAKE_ON:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\photo\\photo_scan\\shake_on.png";
    case RES_BAT_FULL:
        return "A:\\project\\meter_ui_demo\\WL83_gitlab\\ac792\\ui_prj\\new_ui\\import\\image\\LY_UI\\rec\\rec_scan\\bat_full.png";
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
