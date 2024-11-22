/*********************
 *      INCLUDES
 *********************/

#include "lv_draw_jldma2d.h"
#include "src/draw/lv_draw_private.h"

#if LV_USE_DRAW_JLDMA2D
#include "asm/dma2d_driver.h"

//#define LOG_TAG_CONST       UI
#define LOG_TAG             "[lv_dma2d]"
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

static void _jldma2d_fill(uint8_t *dest_buf, const lv_area_t *dest_area, int32_t dest_stride,
                          lv_color_format_t dest_cf, const lv_draw_fill_dsc_t *dsc);

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_draw_jldma2d_fill(lv_draw_unit_t *draw_unit, const lv_draw_fill_dsc_t *dsc, const lv_area_t *coords)
{
    //log_debug("%s()", __func__);

    if (dsc->opa <= (lv_opa_t)LV_OPA_MIN) {
        return;
    }

    lv_layer_t *layer = draw_unit->target_layer;
    lv_draw_buf_t *draw_buf = layer->draw_buf;

    lv_area_t rel_coords;
    lv_area_copy(&rel_coords, coords);
    lv_area_move(&rel_coords, -layer->buf_area.x1, -layer->buf_area.y1);

    lv_area_t rel_clip_area;
    lv_area_copy(&rel_clip_area, draw_unit->clip_area);
    lv_area_move(&rel_clip_area, -layer->buf_area.x1, -layer->buf_area.y1);

    lv_area_t blend_area;
    if (!lv_area_intersect(&blend_area, &rel_coords, &rel_clip_area)) {
        return; /*Fully clipped, nothing to do*/
    }

    //开始 DMA2D 渲染动作
    // 1、初始化渲染空间
    uint32_t dest_stride;
    uint8_t *dest_buf;
    lv_color_format_t dest_cf = draw_buf->header.cf;
    uint32_t bytes_per_pixel = lv_color_format_get_size(dest_cf);
    dest_stride = draw_buf->header.stride;
    dest_buf = draw_buf->data + (blend_area.y1 * dest_stride) + (blend_area.x1 * bytes_per_pixel);  //最终会更新到屏幕上面的 buff 区域

    /* 区域刷新Cache, LVGL9 在初始化的时候已经注册了这个回调，因此不需要再手动 cache 清除，debug */
    //_jldma2d_buf_invalidate_cache_cb(layer->buf, layer->buf_stride, dest_cf, &blend_area);

    _jldma2d_fill(dest_buf, &blend_area, dest_stride, dest_cf, dsc);

    return;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void _jldma2d_only_fill(uint8_t *dest_buf, const lv_area_t *dest_area, int32_t dest_stride,
                               lv_color_format_t dest_cf, const lv_draw_fill_dsc_t *dsc)
{
    int32_t dest_w = lv_area_get_width(dest_area);
    int32_t dest_h = lv_area_get_height(dest_area);

    //log_debug("dest_cf = %d. dest_stride = %d.", dest_cf, dest_stride);

    uint32_t packed_color;

    //log_debug("[%s] dsc->opa = %d. dsc->color.red = %d. dsc->color.green = %d. dsc->color.blue = %d.", \
    __func__, dsc->opa, dsc->color.red, dsc->color.green, dsc->color.blue);

#if 1
    packed_color = dma2d_pack_pixel(dsc->opa, dsc->color.red, dsc->color.green, dsc->color.blue, JLDMA2D_FORMAT_ARGB8888);

    dma2d_reset_all_regs();
    dma2d_create_task();
    dma2d_fill(dest_buf, dest_stride, LV_DMA2D_COLOR_FORMAT, LV_JL_DMA2D_BE, packed_color, dest_w, dest_h);
    dma2d_run();
    dma2d_wait_done();

#else
    /* sw fill test : 仅支持测试 RGB565 */
    uint8_t *fill_buf;
    uint32_t bytes_per_pixel = lv_color_format_get_size(dest_cf);

    //packed_color = dma2d_pack_pixel(dsc->opa, dsc->color.red, dsc->color.green, dsc->color.blue, LV_DMA2D_COLOR_FORMAT);

    packed_color = ((uint32_t)(0x00 >> 3)) | ((uint32_t)(0x00 >> 2) << 5) | ((uint32_t)(0xff >> 3) << 11);  //全画红色

    for (uint32_t y = 0; y < dest_h; y++) {
    for (uint32_t x = 0; x < dest_w; x++) {
            fill_buf = (uint8_t *)&dest_buf[y * dest_stride + x * bytes_per_pixel];
            fill_buf[0] = (packed_color) & 0xff;
            fill_buf[1] = (packed_color >> 8) & 0xff;
        }
    }
#endif

    return;
}

static void _jldma2d_blend_fill_with_opa(uint8_t *dest_buf, const lv_area_t *dest_area, int32_t dest_stride,
        lv_color_format_t dest_cf, const lv_draw_fill_dsc_t *dsc)
{
    /*Simply fill an area*/
    int32_t dest_w = lv_area_get_width(dest_area);
    int32_t dest_h = lv_area_get_height(dest_area);

    uint32_t packed_color;

    packed_color = dma2d_pack_pixel(dsc->opa, dsc->color.red, dsc->color.green, dsc->color.blue, JLDMA2D_FORMAT_ARGB8888);

    dma2d_out_layer_params_t out_layer_param = {0};
    dma2d_input_layer_params_t fg_layer_param = {0};
    dma2d_input_layer_params_t bg_layer_param = {0};

    out_layer_param.data = dest_buf;
    out_layer_param.w = dest_w;
    out_layer_param.h = dest_h;
    out_layer_param.stride =  dest_stride;
    out_layer_param.format = LV_DMA2D_COLOR_FORMAT;
    out_layer_param.rbs = 0;
    out_layer_param.endian = LV_JL_DMA2D_BE;

    // 设置源图层
    fg_layer_param.paintmode = 1;
    fg_layer_param.data = NULL;
    fg_layer_param.stride = 0;
    fg_layer_param.format = JLDMA2D_FORMAT_ARGB8888;
    fg_layer_param.alpha_mode = JLDMA2D_NO_MODIF_ALPHA;
    fg_layer_param.rbs = 0;
    fg_layer_param.color = packed_color;

    // 设置目标图层
    bg_layer_param.data = (uint32_t)dest_buf;
    bg_layer_param.stride = dest_stride;
    bg_layer_param.format = LV_DMA2D_COLOR_FORMAT;
    bg_layer_param.alpha_mode = JLDMA2D_NO_MODIF_ALPHA;
    bg_layer_param.rbs = 0;

    dma2d_reset_all_regs();
    dma2d_create_task();
    dma2d_set_fg_layer(&fg_layer_param);
    dma2d_set_bg_layer(&bg_layer_param);
    dma2d_set_out_layer(&out_layer_param);
    dma2d_set_mode(JLDMA2D_M2M_BLEND);
    dma2d_run();
    dma2d_wait_done();
}


static void _jldma2d_fill(uint8_t *dest_buf, const lv_area_t *dest_area, int32_t dest_stride,
                          lv_color_format_t dest_cf, const lv_draw_fill_dsc_t *dsc)
{
    if (dsc->opa >= (lv_opa_t)LV_OPA_MAX) {
        _jldma2d_only_fill(dest_buf, dest_area, dest_stride, dest_cf, dsc);
    } else {
        _jldma2d_blend_fill_with_opa(dest_buf, dest_area, dest_stride, dest_cf, dsc);
    }
}

#endif /*LV_USE_DRAW_JLDMA2D*/
