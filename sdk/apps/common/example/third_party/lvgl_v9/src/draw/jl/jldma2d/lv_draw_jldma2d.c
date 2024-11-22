/*********************
 *      INCLUDES
 *********************/

#include "lv_draw_jldma2d.h"
#include "src/draw/lv_draw_buf_private.h"
#include "src/draw/lv_draw_private.h"
#include "src/draw/sw/lv_draw_sw_private.h"

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

#define DRAW_UNIT_ID_JLDMA2D 102

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/*
 * Evaluate a task and set the score and preferred JL DMA2D unit.
 * Return 1 if task is preferred, 0 otherwise (task is not supported).
 */
static int32_t _jldma2d_evaluate(lv_draw_unit_t *draw_unit, lv_draw_task_t *task);

/*
 * Dispatch a task to the JL DMA2D unit.
 * Return 1 if task was dispatched, 0 otherwise (task not supported).
 */
static int32_t _jldma2d_dispatch(lv_draw_unit_t *draw_unit, lv_layer_t *layer);

/*
 * Delete the JL DMA2D draw unit.
 */
static int32_t _jldma2d_delete(lv_draw_unit_t *draw_unit);

#if LV_USE_OS
static void _jldma2d_render_thread_cb(void *ptr);
#endif

static void _jldma2d_execute_drawing(lv_draw_jldma2d_unit_t *u);

/**********************
 *  STATIC VARIABLES
 **********************/

static void lv_draw_buf_jldma2d_init_handlers(void)
{
    lv_draw_buf_handlers_t *handlers = lv_draw_buf_get_handlers();

    handlers->invalidate_cache_cb = _jldma2d_buf_invalidate_cache_cb;
}

void _jldma2d_buf_invalidate_cache_cb(const lv_draw_buf_t *draw_buf, const lv_area_t *area)
{
    uint8_t *dest_buf;
    int32_t i = 0;
    int32_t width = lv_area_get_width(area);
    int32_t lines = lv_area_get_height(area);

    lv_color_format_t color_format = draw_buf->header.cf;
    uint32_t bytes_per_pixel = lv_color_format_get_size(color_format);
    uint32_t width_bytes = width * bytes_per_pixel;
    uint8_t *buf = draw_buf->data;
    uint32_t stride = draw_buf->header.stride;
    //printf("area (x1,y1) = (%d,%d); (x2,y2) = (%d,%d). stride = %d.", area->x1, area->y1, area->x2, area->y2, stride);

    dest_buf = buf + (area->y1 * stride) + (area->x1 * bytes_per_pixel);
    for (i = 0; i < lines; i++) {
        DcuFlushinvRegion((u32 *)dest_buf, width_bytes);    //帧buff,清除 area 大小的相对地址空间
        dest_buf += stride;
    }
}

static int32_t _jldma2d_evaluate(lv_draw_unit_t *draw_unit, lv_draw_task_t *task)
{
    LV_UNUSED(draw_unit);

    lv_draw_jldma2d_unit_t *draw_jldma2d_unit = (lv_draw_jldma2d_unit_t *) draw_unit;

    if (lv_area_get_size(&(task->area)) <= LV_JL_DMA2D_MIN_AREA_SIZE) {
        return 0;   /* 需要渲染的区域太小则放弃使用 DMA2D */
    }

    switch (task->type) {
    case LV_DRAW_TASK_TYPE_FILL: {
        const lv_draw_fill_dsc_t *draw_dsc = (lv_draw_fill_dsc_t *) task->draw_dsc;

        /* Most simple case: just a plain rectangle (no radius, no gradient). */
        if ((draw_dsc->radius != 0) || (draw_dsc->grad.dir != (lv_grad_dir_t)LV_GRAD_DIR_NONE)) {
            return 0;
        }

        if (task->preference_score > 70) {
            task->preference_score = 70;
            task->preferred_draw_unit_id = DRAW_UNIT_ID_JLDMA2D;
        }
        return 1;
    }

    case LV_DRAW_TASK_TYPE_LAYER: {
        const lv_draw_image_dsc_t *draw_dsc = (lv_draw_image_dsc_t *) task->draw_dsc;
        lv_layer_t *layer_to_draw = (lv_layer_t *)draw_dsc->src;


        return 0;       // TODO

        //return 1;
    }

    case LV_DRAW_TASK_TYPE_IMAGE: {
        lv_draw_image_dsc_t *draw_dsc = (lv_draw_image_dsc_t *) task->draw_dsc;
        const lv_image_dsc_t *img_dsc = draw_dsc->src;

        return 0;       // TODO

        //return 1;
    }
    default:
        return 0;
    }

    return 0;
}

static int32_t _jldma2d_dispatch(lv_draw_unit_t *draw_unit, lv_layer_t *layer)
{
    lv_draw_jldma2d_unit_t *draw_jldma2d_unit = (lv_draw_jldma2d_unit_t *) draw_unit;

    /* Return immediately if it's busy with draw task. */
    if (draw_jldma2d_unit->task_act) {
        return 0;
    }

    /* Try to get an ready to draw. */
    lv_draw_task_t *t = lv_draw_get_next_available_task(layer, NULL, DRAW_UNIT_ID_JLDMA2D);

    if (t == NULL || t->preferred_draw_unit_id != DRAW_UNIT_ID_JLDMA2D) {
        return -1;
    }

    void *buf = lv_draw_layer_alloc_buf(layer);
    if (buf == NULL) {
        return -1;
    }

    t->state = LV_DRAW_TASK_STATE_IN_PROGRESS;
    draw_jldma2d_unit->base_unit.target_layer = layer;
    draw_jldma2d_unit->base_unit.clip_area = &t->clip_area;
    draw_jldma2d_unit->task_act = t;

#if LV_USE_OS
    /* Let the render thread work. */
    if (draw_jldma2d_unit->inited) {
        lv_thread_sync_signal(&draw_jldma2d_unit->sync);
    }
#else
    _jldma2d_execute_drawing(draw_jldma2d_unit);

    draw_jldma2d_unit->task_act->state = LV_DRAW_TASK_STATE_READY;
    draw_jldma2d_unit->task_act = NULL;

    /* The draw unit is free now. Request a new dispatching as it can get a new task. */
    lv_draw_dispatch_request();
#endif

    return 1;
}

static int32_t _jldma2d_delete(lv_draw_unit_t *draw_unit)
{
#if LV_USE_OS
    lv_draw_jldma2d_unit_t *draw_jldma2d_unit = (lv_draw_jldma2d_unit_t *) draw_unit;

    LV_LOG_INFO("Cancel JL DMA2D draw thread.");
    draw_jldma2d_unit->exit_status = true;

    if (draw_jldma2d_unit->inited) {
        lv_thread_sync_signal(&draw_jldma2d_unit->sync);
    }

    lv_result_t res = lv_thread_delete(&draw_jldma2d_unit->thread);

    return res;
#else
    LV_UNUSED(draw_unit);

    return 0;
#endif
}

static void _jldma2d_execute_drawing(lv_draw_jldma2d_unit_t *u)
{
    //log_debug("%s()", __func__);

    lv_draw_task_t *t = u->task_act;
    lv_draw_unit_t *draw_unit = (lv_draw_unit_t *)u;
    lv_layer_t *layer = draw_unit->target_layer;
    lv_draw_buf_t *draw_buf = layer->draw_buf;

    /* Set target buffer */
    lv_area_t clip_area;
    lv_area_copy(&clip_area, draw_unit->clip_area);
    lv_area_move(&clip_area, -layer->buf_area.x1, -layer->buf_area.y1);

    lv_area_t draw_area;
    lv_area_copy(&draw_area, &t->area);
    lv_area_move(&draw_area, -layer->buf_area.x1, -layer->buf_area.y1);

    if (!lv_area_intersect(&draw_area, &draw_area, &clip_area)) {
        return;    /*Fully clipped, nothing to do*/
    }

    /* Invalidate only the drawing area */
    lv_draw_buf_invalidate_cache(draw_buf, &draw_area);

    switch (t->type) {
    case LV_DRAW_TASK_TYPE_FILL:
        lv_draw_jldma2d_fill(draw_unit, t->draw_dsc, &t->area);
        break;
    case LV_DRAW_TASK_TYPE_IMAGE:
        // TODO
        //lv_draw_jldma2d_img(draw_unit, t->draw_dsc, &t->area);
        break;
    case LV_DRAW_TASK_TYPE_LAYER:
        // TODO
        //lv_draw_jldma2d_layer(draw_unit, t->draw_dsc, &t->area);
        break;
    default:
        break;
    }
}

#if LV_USE_OS
static void _jldma2d_render_thread_cb(void *ptr)
{
    lv_draw_jldma2d_unit_t *u = ptr;

    lv_thread_sync_init(&u->sync);
    u->inited = true;

    while (1) {
        /* Wait for sync if there is no task set. */
        while (u->task_act == NULL) {
            if (u->exit_status) {
                break;
            }

            lv_thread_sync_wait(&u->sync);
        }

        if (u->exit_status) {
            LV_LOG_INFO("Ready to exit JL DMA2D draw thread.");
            break;
        }

        _jldma2d_execute_drawing(u);

        /* Signal the ready state to dispatcher. */
        u->task_act->state = LV_DRAW_TASK_STATE_READY;

        /* Cleanup. */
        u->task_act = NULL;

        /* The draw unit is free now. Request a new dispatching as it can get a new task. */
        lv_draw_dispatch_request();
    }

    u->inited = false;
    lv_thread_sync_delete(&u->sync);
    LV_LOG_INFO("Exit JL DMA2D draw thread.");
}
#endif

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_draw_jldma2d_init(void)
{
    lv_draw_buf_jldma2d_init_handlers();

    lv_draw_jldma2d_unit_t *draw_jldma2d_unit = lv_draw_create_unit(sizeof(lv_draw_jldma2d_unit_t));
    draw_jldma2d_unit->base_unit.evaluate_cb = _jldma2d_evaluate;
    draw_jldma2d_unit->base_unit.dispatch_cb = _jldma2d_dispatch;
    draw_jldma2d_unit->base_unit.delete_cb = _jldma2d_delete;
    draw_jldma2d_unit->idx = DRAW_UNIT_ID_JLDMA2D;

    /* JL dma2d hw init */
    dma2d_init();

    log_info("jl dma2d hw init.");

#if LV_USE_OS
    draw_jldma2d_unit->thread.task_name = "lv_draw_jldma2d_unit";
    lv_thread_init(&draw_jldma2d_unit->thread, LV_THREAD_PRIO_HIGH, _jldma2d_render_thread_cb, 8 * 1024, draw_jldma2d_unit);
#endif
    return;
}

void lv_draw_jldma2d_deinit(void)
{
    /* JL dma2d hw deinit */
    dma2d_free();

    log_info("jl dma2d hw deinit.");

    return;
}

#endif /*LV_USE_DRAW_JLDMA2D*/
