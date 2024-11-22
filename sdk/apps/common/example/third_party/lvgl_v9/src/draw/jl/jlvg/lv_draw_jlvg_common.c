/*********************
 *      INCLUDES
 *********************/

#include "lv_draw_jlvg.h"

#if LV_USE_DRAW_JLVG

//#define LOG_TAG_CONST       UI
#define LOG_TAG             "[lv_gpu]"
#define LOG_ERROR_ENABLE
#define LOG_DEBUG_ENABLE
#define LOG_INFO_ENABLE
/* #define LOG_DUMP_ENABLE */
#define LOG_CLI_ENABLE
#include "debug.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

jlvg_hw_imageformat_t lv_jlvg_get_color_format(lv_color_format_t lv_cf, bool *cf_flag)
{
    jlvg_hw_imageformat_t jlvg_cf = VGHW_FORMAT_ARGB8888;

    if (cf_flag != NULL) {
        *cf_flag = true;   // false : 不支持：true : 支持
    }

    //printf("lv_color_format_t  = 0x%02x.", lv_cf);
    switch (lv_cf) {
    case LV_COLOR_FORMAT_ARGB8888:
        jlvg_cf = VGHW_FORMAT_ARGB8888;
        break;
    case LV_COLOR_FORMAT_ARGB8565:
        jlvg_cf = VGHW_FORMAT_ARGB8565;
        break;
    case LV_COLOR_FORMAT_RGB888:
        jlvg_cf = VGHW_FORMAT_RGB888;
        break;
    case LV_COLOR_FORMAT_RGB565:
        jlvg_cf = VGHW_FORMAT_RGB565;
        break;
    case LV_COLOR_FORMAT_A8:
        jlvg_cf = VGHW_FORMAT_A8;
        break;
    case LV_COLOR_FORMAT_A4:
        jlvg_cf = VGHW_FORMAT_A4;
        break;
    case LV_COLOR_FORMAT_A2:
        jlvg_cf = VGHW_FORMAT_A2;
        break;
    case LV_COLOR_FORMAT_A1:
        jlvg_cf = VGHW_FORMAT_A1;
        break;
    case LV_COLOR_FORMAT_L8:
        jlvg_cf = VGHW_FORMAT_L8;
        break;
    default:
        if (cf_flag != NULL) {
            *cf_flag = false;   // false : 不支持：true : 支持
        }
        //printf("Unsupported color format.");
        break;
    }

    //printf("jlvg_cf  = 0x%02x.", jlvg_cf);
    return jlvg_cf;
}

uint8_t lv_jlvg_get_blend_mode(lv_blend_mode_t lv_blend_mode, bool *mode_flag)
{
    uint8_t jlvg_blend_mode = VGHW_BLEND_SRC;

    if (mode_flag != NULL) {
        *mode_flag = true;   // false : 不支持：true : 支持
    }

    //printf("lv_blend_mode 0x%02x.", lv_blend_mode);
    switch (lv_blend_mode) {
    case LV_BLEND_MODE_NORMAL:
        jlvg_blend_mode = VGHW_BLEND_SRC_OVER;
        break;
    case LV_BLEND_MODE_ADDITIVE:
        jlvg_blend_mode = VGHW_BLEND_ADDITIVE;
        break;
    case LV_BLEND_MODE_MULTIPLY:
        jlvg_blend_mode = VGHW_BLEND_MULTIPLY;
        break;
    default:
        if (mode_flag != NULL) {
            *mode_flag = false;   // false : 不支持：true : 支持
        }
        //printf("Unsupported blend mode.");
        break;
    }

    //printf("jlvg_blend_mode  = 0x%02x.", jlvg_blend_mode);
    return jlvg_blend_mode;
}

void lv_jlvg_flush_inv_dcache(uint8_t *buf, uint32_t w, uint32_t h, uint32_t stride, uint8_t color_depth)
{
    /* 区域刷新Cache */
    uint8_t *area_ptr = (uint8_t *)buf;
    uint32_t width_bytes = w * color_depth >> 3;
    uint32_t offset = stride * color_depth >> 3;
    for (int y = 0; y < h; y++) {
        DcuFlushinvRegion((u32 *)area_ptr, width_bytes);
        area_ptr += offset;
    }
}
/**********************
 *   STATIC FUNCTIONS
 **********************/

#endif /*LV_USE_DRAW_JLVG*/
