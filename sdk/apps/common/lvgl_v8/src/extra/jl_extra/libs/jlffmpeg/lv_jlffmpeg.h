/**
 * @file lv_ffmpeg.h
 *
 */
#ifndef LV_JLFFMPEG_H
#define LV_JLFFMPEG_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "../../../lvgl.h"
#if LV_USE_JLFFMPEG != 0

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
struct ffmpeg_context_s;

extern const lv_obj_class_t lv_ffmpeg_player_class;

struct ffmpeg_context_s {
    bool has_alpha;
    uint32_t width;
    uint32_t height;
    uint32_t total_time;
    uint32_t total_frame;
    uint32_t idx;
    lv_fs_file_t *lv_file;
    uint32_t size;
    uint8_t *jpg_data;
    uint8_t *buf_act;
    uint8_t *buf1_data;
    uint8_t *buf2_data;
    bool auto_cycle;
};

typedef struct {
    lv_img_t img;
    lv_timer_t *timer;
    lv_img_dsc_t imgdsc;
    bool auto_restart;
    struct ffmpeg_context_s *ffmpeg_ctx;
} lv_ffmpeg_player_t;

typedef enum {
    LV_FFMPEG_PLAYER_CMD_START,
    LV_FFMPEG_PLAYER_CMD_STOP,
    LV_FFMPEG_PLAYER_CMD_PAUSE,
    LV_FFMPEG_PLAYER_CMD_RESUME,
    _LV_FFMPEG_PLAYER_CMD_LAST
} lv_ffmpeg_player_cmd_t;

typedef enum {
    LV_FFMPEG_IMG_DECODE_START,
    LV_FFMPEG_IMG_DECODE_STOP,
    LV_FFMPEG_IMG_DECODE_TASK_KILL
} lv_ffmpeg_img_decode_status_t;
/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Register FFMPEG image decoder
 */
void lv_ffmpeg_init(uint8_t doublebuf_en);
/**
 * Get the number of frames contained in the file
 * @param path image or video file name
 * @return Number of frames, less than 0 means failed
 */
int lv_ffmpeg_get_frame_num(const char *path);

/**
 * Create ffmpeg_player object
 * @param parent pointer to an object, it will be the parent of the new player
 * @return pointer to the created ffmpeg_player
 */
lv_obj_t *lv_ffmpeg_player_create(lv_obj_t *parent);

/**
 * Set the path of the file to be played
 * @param obj pointer to a ffmpeg_player object
 * @param path video file path
 * @return LV_RES_OK: no error; LV_RES_INV: can't get the info.
 */
lv_res_t lv_ffmpeg_player_set_src(lv_obj_t *obj, const char *path);

/**
 * Set command control video player
 * @param obj pointer to a ffmpeg_player object
 * @param cmd control commands
 */
void lv_ffmpeg_player_set_cmd(lv_obj_t *obj, lv_ffmpeg_player_cmd_t cmd);

/**
 * Set the video to automatically replay
 * @param obj pointer to a ffmpeg_player object
 * @param en true: enable the auto restart
 */
void lv_ffmpeg_player_set_auto_restart(lv_obj_t *obj, bool en);

void lv_ffmpeg_player_set_zoom(lv_obj_t *obj, uint16_t zoom);
/*=====================
 * Other functions
 *====================*/

/**********************
 *      MACROS
 **********************/

#endif /*LV_USE_JLFFMPEG*/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_JLFFMPEG_H*/
