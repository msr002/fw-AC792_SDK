#ifndef LV_DRAW_JLDMA2D_H
#define LV_DRAW_JLDMA2D_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

#include "../../../lv_conf_internal.h"

#if LV_USE_DRAW_JLDMA2D
#include "../../../display/lv_display_private.h"
#include "../../sw/lv_draw_sw.h"
#include "../../lv_draw.h"

/*********************
 *      DEFINES
 *********************/

#if LV_COLOR_DEPTH == 8
#error "Can't use DMA2D with LV_COLOR_DEPTH == 8"
#endif

#if LV_COLOR_DEPTH == 16
#define LV_DMA2D_COLOR_FORMAT JLDMA2D_FORMAT_RGB565
#elif LV_COLOR_DEPTH == 32
#define LV_DMA2D_COLOR_FORMAT JLDMA2D_FORMAT_ARGB8888
#else
/*Can't use GPU with other formats*/
#endif

#define LV_JL_DMA2D_BE    0   //大小端配置

#define LV_JL_DMA2D_MIN_AREA_SIZE   64  // 交付给 DMA2D 渲染的最小区域大小，小于这个大小则不采用 DMA2D

/**********************
 *      TYPEDEFS
 **********************/

typedef lv_draw_sw_unit_t lv_draw_jldma2d_unit_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

void lv_draw_jldma2d_init(void);

void lv_draw_jldma2d_deinit(void);

void lv_draw_jldma2d_fill(lv_draw_unit_t *draw_unit, const lv_draw_fill_dsc_t *dsc, const lv_area_t *coords);

//common api
void _jldma2d_buf_invalidate_cache_cb(const lv_draw_buf_t *draw_buf, const lv_area_t *area);

/**********************
 *      MACROS
 **********************/
#endif /*LV_USE_DRAW_JLDMA2D*/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_DRAW_JLDMA2D_H*/
