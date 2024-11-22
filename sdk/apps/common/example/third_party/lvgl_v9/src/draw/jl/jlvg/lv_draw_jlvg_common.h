#ifndef LV_DRAW_JLVG_COMMON_H
#define LV_DRAW_JLVG_COMMON_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

#if LV_USE_DRAW_JLVG

#include "asm/gpu/jlvg.h"
#include "asm/jlgpu_driver.h"

/*********************
 *      DEFINES
 *********************/



/**********************
 *      TYPEDEFS
 **********************/



/**********************
 * GLOBAL PROTOTYPES
 **********************/

jlvg_hw_imageformat_t lv_jlvg_get_color_format(lv_color_format_t lv_cf, bool *cf_flag);
uint8_t lv_jlvg_get_blend_mode(lv_blend_mode_t lv_blend_mode, bool *mode_flag);
void lv_jlvg_flush_inv_dcache(uint8_t *buf, uint32_t w, uint32_t h, uint32_t stride, uint8_t color_depth);

/**********************
 *      MACROS
 **********************/
#endif /*LV_USE_DRAW_JLVG*/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_DRAW_JLVG_COMMON_H*/
