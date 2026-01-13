// lyrics_anim_effect_safe.c
#include "lyrics_anim_effect.h"
// 配置参数
#define LYRIC_ANIM_ZOOM_BASE 256  // 256表示100%缩放

// 安全的歌词动画上下文结构
typedef struct {
    lv_obj_t *obj;              // 歌词对象（弱引用）
    uint8_t is_valid;           // 标记是否有效（1=有效，0=无效）
    uint8_t is_animating;       // 标记是否在动画中
    lv_coord_t start_x;         // 起始X坐标
    lv_coord_t start_y;         // 起始Y坐标
    lv_coord_t target_x;        // 目标X坐标
    lv_coord_t target_y;        // 目标Y坐标
} safe_lyrics_context_t;

// 全局上下文池（避免动态内存分配）
#define MAX_SAFE_CONTEXTS 10
static safe_lyrics_context_t safe_contexts[MAX_SAFE_CONTEXTS] = {0};
static int context_index = 0;

// 获取安全上下文
static safe_lyrics_context_t *get_safe_context(lv_obj_t *obj)
{
    if (!obj) {
        return NULL;
    }

    // 寻找空闲位置
    for (int i = 0; i < MAX_SAFE_CONTEXTS; i++) {
        if (safe_contexts[i].obj == NULL) {
            safe_contexts[i].obj = obj;
            safe_contexts[i].is_valid = 1;
            safe_contexts[i].is_animating = 1;
            return &safe_contexts[i];
        }
    }

    // 如果满了，循环使用
    context_index = (context_index + 1) % MAX_SAFE_CONTEXTS;
    safe_contexts[context_index].obj = obj;
    safe_contexts[context_index].is_valid = 1;
    safe_contexts[context_index].is_animating = 1;
    return &safe_contexts[context_index];
}

// 验证上下文是否有效
static int is_context_valid(safe_lyrics_context_t *ctx)
{
    return (ctx != NULL && ctx->is_valid == 1 && ctx->obj != NULL);
}

// 无效化上下文
static void invalidate_context(safe_lyrics_context_t *ctx)
{
    if (ctx) {
        ctx->is_valid = 0;
        ctx->is_animating = 0;
        ctx->obj = NULL;
    }
}

// 安全的对象检查函数
static int is_obj_valid(lv_obj_t *obj)
{
    // 简化检查：确保对象指针不为NULL
    if (!obj) {
        return 0;
    }

    // 如果需要更严格的检查，可以添加更多条件
    // 例如：检查对象是否在有效的内存范围内

    return 1;
}

// 安全的歌词颜色设置（无重绘）
static void safe_lyrics_set_color_no_redraw(lv_obj_t *obj, jlvg_color_t color)
{
    if (!is_obj_valid(obj)) {
        return;
    }

    // 直接设置颜色，不立即重绘
    lv_lyrics_set_color(obj, color);
}

// 安全的歌词缩放设置（无重绘）
static void safe_lyrics_set_zoom_no_redraw(lv_obj_t *obj, int32_t zoom_x, int32_t zoom_y)
{
    if (!is_obj_valid(obj)) {
        return;
    }

    // 边界检查
    if (zoom_x < 0) {
        zoom_x = 0;
    }
    if (zoom_y < 0) {
        zoom_y = 0;
    }
    if (zoom_x > 1000) {
        zoom_x = 1000;    // 限制最大缩放
    }
    if (zoom_y > 1000) {
        zoom_y = 1000;
    }

    // 直接设置缩放，不立即重绘
    lv_lyrics_set_zoom(obj, zoom_x, zoom_y);
}

// 安全的歌词重绘函数（添加保护）
static void safe_lyrics_redraw(lv_obj_t *obj)
{
    if (!is_obj_valid(obj)) {
        printf("[WARN] Attempted to redraw invalid object\n");
        return;
    }

    // 添加延迟或尝试/捕获机制
    // 这里使用简单的延迟机制
    static uint32_t last_redraw_time = 0;
    uint32_t current_time = lv_tick_get();

    // 限制重绘频率（最少间隔20ms）
    if (current_time - last_redraw_time < 20) {
        return;
    }

    last_redraw_time = current_time;

    // 尝试重绘
    lv_lyrics_fontimg_redarw(obj);
}

// 安全的缩放和位置处理（避免在回调中死机）
static void safe_scale_and_translate_handle(lv_obj_t *obj, int32_t scale,
        int32_t translate_x, int32_t translate_y,
        uint8_t alpha)
{
    if (!is_obj_valid(obj)) {
        return;
    }

    // 计算缩放值 (scale为百分比，0-100)
    int32_t zoom_value = scale * LYRIC_ANIM_ZOOM_BASE / 100;

    // 边界检查
    if (zoom_value < 26) {
        zoom_value = 26;    // 最小10%
    }
    if (zoom_value > 512) {
        zoom_value = 512;    // 最大200%
    }

    // 设置缩放（不立即重绘）
    safe_lyrics_set_zoom_no_redraw(obj, zoom_value, zoom_value);

    // 设置透明度（不立即重绘）
    jlvg_color_t color = {0xFF, 0xFF, 0xFF, alpha};
    safe_lyrics_set_color_no_redraw(obj, color);

    // 延迟重绘（避免频繁重绘）
    static uint32_t redraw_count = 0;
    redraw_count++;

    // 每5帧重绘一次（减少重绘频率）
    if (redraw_count % 5 == 0) {
        safe_lyrics_redraw(obj);
    }
}

// 简化的第一阶段动画回调（无上下文）
static void simple_down_in_one_cb(void *var, int32_t v)
{
    lv_obj_t *obj = (lv_obj_t *)var;
    if (!is_obj_valid(obj)) {
        return;
    }

    // 边界检查
    if (v < 0) {
        v = 0;
    }
    if (v > 100) {
        v = 100;
    }

    // 计算缩放：从10%到47.5%
    uint32_t scale = v * 375 / 1000 + 10;  // v * 37.5 / 100 + 10

    // 计算透明度：从0到100%
    uint8_t alpha = v * 255 / 100;

    // 使用安全的处理函数
    safe_scale_and_translate_handle(obj, scale, 0, 0, alpha);
}

// 简化的第二阶段动画回调（无上下文）
static void simple_down_in_two_cb(void *var, int32_t v)
{
    lv_obj_t *obj = (lv_obj_t *)var;
    if (!is_obj_valid(obj)) {
        return;
    }

    // 边界检查
    if (v < 0) {
        v = 0;
    }
    if (v > 100) {
        v = 100;
    }

    // 计算缩放：从52%到100%
    uint32_t scale = v * 48 / 100 + 52;

    // 透明度保持100%
    uint8_t alpha = 255;

    // 使用安全的处理函数
    safe_scale_and_translate_handle(obj, scale, 0, 0, alpha);
}

// 简化的透明度动画回调（无上下文）
static void simple_opa_cb(void *var, int32_t v)
{
    lv_obj_t *obj = (lv_obj_t *)var;
    if (!is_obj_valid(obj)) {
        return;
    }

    // 边界检查
    if (v < 0) {
        v = 0;
    }
    if (v > 100) {
        v = 100;
    }

    // 计算透明度：v是0-100，转换为0-255
    uint8_t alpha = v * 255 / 100;

    // 直接设置颜色，不立即重绘
    jlvg_color_t color = {0xFF, 0xFF, 0xFF, alpha};
    safe_lyrics_set_color_no_redraw(obj, color);

    // 每3帧重绘一次
    static uint32_t opa_redraw_count = 0;
    opa_redraw_count++;
    if (opa_redraw_count % 3 == 0) {
        safe_lyrics_redraw(obj);
    }
}

// 动画完成回调（清理资源）
static void anim_completed_cb(lv_anim_t *anim)
{
    if (!anim) {
        return;
    }

    lv_obj_t *obj = (lv_obj_t *)anim->var;
    printf("[INFO] Animation completed for object %p\n", obj);

    // 清理对应的上下文
    for (int i = 0; i < MAX_SAFE_CONTEXTS; i++) {
        if (safe_contexts[i].obj == obj) {
            invalidate_context(&safe_contexts[i]);
            break;
        }
    }
}

// 简化的ZoomInDown特效（安全版本）
void lyrics_anim_effect_zooming_in_down(lv_obj_t *lyrics_obj, lyrics_anim_effect_args_t *args)
{
    if (!lyrics_obj || !args) {
        printf("[ERROR] Invalid parameters\n");
        return;
    }

    printf("[INFO] Starting safe zoom-in-down animation for object %p\n", lyrics_obj);

    // 获取安全上下文
    safe_lyrics_context_t *ctx = get_safe_context(lyrics_obj);
    if (!ctx) {
        printf("[ERROR] No safe context available\n");
        return;
    }

    // 记录位置
    ctx->start_x = 0;
    ctx->start_y = 0;
    ctx->target_x = 0;
    ctx->target_y = 0;

    // 设置初始状态（使用安全函数）
    safe_lyrics_set_zoom_no_redraw(lyrics_obj, 26, 26);  // 10%缩放

    jlvg_color_t transparent = {0xFF, 0xFF, 0xFF, 0x00};
    safe_lyrics_set_color_no_redraw(lyrics_obj, transparent);

    // 初始重绘
    safe_lyrics_redraw(lyrics_obj);

    // 计算动画时间
    int32_t time = 600;  // 固定600ms第一阶段

    // 第一阶段动画
    lv_anim_t anim1;
    lv_anim_init(&anim1);
    lv_anim_set_var(&anim1, lyrics_obj);  // 直接使用对象指针，而不是上下文
    lv_anim_set_exec_cb(&anim1, (lv_anim_exec_xcb_t)simple_down_in_one_cb);
    lv_anim_set_values(&anim1, 0, 100);
    lv_anim_set_delay(&anim1, args->delay);
    lv_anim_set_path_cb(&anim1, lv_anim_path_ease_in);
    lv_anim_set_time(&anim1, time);
    lv_anim_set_ready_cb(&anim1, anim_completed_cb);
    lv_anim_start(&anim1);

    // 第二阶段动画
    lv_anim_t anim2;
    lv_anim_init(&anim2);
    lv_anim_set_var(&anim2, lyrics_obj);
    lv_anim_set_exec_cb(&anim2, (lv_anim_exec_xcb_t)simple_down_in_two_cb);
    lv_anim_set_values(&anim2, 0, 100);
    lv_anim_set_delay(&anim2, args->delay + time);
    lv_anim_set_path_cb(&anim2, lv_anim_path_ease_out);
    lv_anim_set_time(&anim2, args->duration - time);
    lv_anim_set_ready_cb(&anim2, anim_completed_cb);
    lv_anim_start(&anim2);

    // 透明度动画
    lv_anim_t opa_anim;
    lv_anim_init(&opa_anim);
    lv_anim_set_var(&opa_anim, lyrics_obj);
    lv_anim_set_exec_cb(&opa_anim, (lv_anim_exec_xcb_t)simple_opa_cb);
    lv_anim_set_values(&opa_anim, 0, 100);
    lv_anim_set_delay(&opa_anim, args->delay);
    lv_anim_set_path_cb(&opa_anim, lv_anim_path_ease_in);
    lv_anim_set_time(&opa_anim, time);
    lv_anim_set_ready_cb(&opa_anim, NULL);
    lv_anim_start(&opa_anim);
}

// 简化的ZoomIn特效
void lyrics_anim_effect_zooming_in(lv_obj_t *lyrics_obj, lyrics_anim_effect_args_t *args)
{
    if (!lyrics_obj || !args) {
        return;
    }

    printf("[INFO] Starting safe zoom-in animation for object %p\n", lyrics_obj);

    // 设置初始状态
    safe_lyrics_set_zoom_no_redraw(lyrics_obj, 77, 77);  // 30%缩放

    jlvg_color_t transparent = {0xFF, 0xFF, 0xFF, 0x00};
    safe_lyrics_set_color_no_redraw(lyrics_obj, transparent);

    safe_lyrics_redraw(lyrics_obj);

    // 缩放动画
    lv_anim_t scale_anim;
    lv_anim_init(&scale_anim);
    lv_anim_set_var(&scale_anim, lyrics_obj);
    lv_anim_set_exec_cb(&scale_anim, (lv_anim_exec_xcb_t)simple_down_in_two_cb); // 复用
    lv_anim_set_values(&scale_anim, 30, 100);
    lv_anim_set_delay(&scale_anim, args->delay);
    lv_anim_set_path_cb(&scale_anim, lv_anim_path_linear);
    lv_anim_set_time(&scale_anim, args->duration);
    lv_anim_start(&scale_anim);

    // 透明度动画
    lv_anim_t opa_anim;
    lv_anim_init(&opa_anim);
    lv_anim_set_var(&opa_anim, lyrics_obj);
    lv_anim_set_exec_cb(&opa_anim, (lv_anim_exec_xcb_t)simple_opa_cb);
    lv_anim_set_values(&opa_anim, 0, 100);
    lv_anim_set_delay(&opa_anim, args->delay);
    lv_anim_set_time(&opa_anim, args->duration * 50 / 100);
    lv_anim_set_path_cb(&opa_anim, lv_anim_path_linear);
    lv_anim_start(&opa_anim);
}

// 清理所有动画
void lyrics_anim_effect_cleanup(void)
{
    printf("[INFO] Cleaning up all animation contexts\n");

    // 停止所有动画
    for (int i = 0; i < MAX_SAFE_CONTEXTS; i++) {
        if (safe_contexts[i].obj && safe_contexts[i].is_animating) {
            lv_anim_del(safe_contexts[i].obj, NULL);
            invalidate_context(&safe_contexts[i]);
        }
    }
}
