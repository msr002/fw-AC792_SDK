#ifndef _TUYA_AUDIO_SRC_H
#define _TUYA_AUDIO_SRC_H

#include "tuya_cloud_types.h"

#ifdef __cplusplus
extern "C" {
#endif

//配网成功语音
#define AUDIO_PLAY_VOICE_1   0
//进入配网语音
#define AUDIO_PLAY_VOICE_2   1

//SD 卡升级画面
#define LCD_PLAY_UPDATE   1
//启动logo画面
#define LCD_PLAY_START   2

VOID tuya_play_local_audio(CHAR_T audio_num);

#ifdef __cplusplus
}
#endif

#endif
