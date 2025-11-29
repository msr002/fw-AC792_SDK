/**
 * @file lv_arcwheel.h
 */

#ifndef LV_ARCWHEEL_H
#define LV_ARCWHEEL_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "lvgl.h"

#if LV_USE_ARCWHEEL != 0

#if LV_USE_IMG == 0
#error "lv_arcwheel: lv_img is required. Enable it in lv_conf.h (LV_USE_IMG 1)"
#endif

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**
 * @brief 转换参数联合体
 * 用于存储不同转换效果的参数
 */
typedef union {
    /* 滑动缩放效果参数（默认效果） */
    struct {
        uint16_t zoom_min;        /* 最小缩放值（远端） */
        uint16_t zoom_max;        /* 最大缩放值（近端） */
    } slide_scale;

    /* 自定义转换效果的通用参数 */
    struct {
        lv_coord_t param1;
        lv_coord_t param2;
        lv_coord_t param3;
        lv_coord_t param4;
    } custom;
} lv_arcwheel_transform_params_t;

/**
 * @brief arcwheel item transform callback
 * @param arcwheel arcwheel 容器对象
 * @param item 当前正在转换的子项对象
 * @param angle 该子项当前的显示角度（相对角度，已应用 angle_offset）
 * @param item_pos 子项的位置（输入/输出参数，回调可以修改）
 * @return 缩放值（zoom），如果返回 0 则隐藏该子项
 */
typedef uint16_t (*lv_arcwheel_item_transform_cb_t)(
    const lv_obj_t *arcwheel,
    const lv_obj_t *item,
    lv_coord_t angle,
    lv_point_t *item_pos
);

typedef struct {
    lv_obj_t obj;

    lv_coord_t radius_x;
    lv_coord_t radius_y;
    lv_coord_t current_angle;
    lv_coord_t angle_offset;   /* 角度偏移量，用于控制子项的起始方向（0°=下方，90°=左侧，180°=上方，-90°=右侧） */

    uint16_t visible_count;    /* 显示数量 */
    lv_coord_t angle_step;     /* 槽位角度间隔 = 360/visible_count */

    lv_coord_t px_per_degree;

    /* 转换回调和参数 */
    lv_arcwheel_item_transform_cb_t item_transform_cb;
    lv_arcwheel_transform_params_t transform_params;

    bool loop_enabled;

    struct {
        lv_coord_t momentum;
        lv_timer_t *scroll_tmr;
    } scroll;

    struct {
        lv_anim_t anim;
        bool is_animating;
    } snap;

    lv_coord_t friction_factor;
    lv_coord_t snap_factor;
    bool snap_enabled;

    bool _is_init;

} lv_arcwheel_t;

typedef struct {
    lv_img_t img;
} lv_arcwheel_item_t;

extern const lv_obj_class_t lv_arcwheel_class;
extern const lv_obj_class_t lv_arcwheel_item_class;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

lv_obj_t *lv_arcwheel_create(lv_obj_t *parent);
lv_obj_t *lv_arcwheel_add_item(lv_obj_t *wheel, const void *icon);

void lv_arcwheel_set_radius(lv_obj_t *obj, lv_coord_t radius_x, lv_coord_t radius_y);
void lv_arcwheel_set_sensitivity(lv_obj_t *obj, lv_coord_t px_per_degree);
void lv_arcwheel_set_loop(lv_obj_t *obj, bool enabled);
void lv_arcwheel_set_visible_count(lv_obj_t *obj, uint16_t count);
void lv_arcwheel_set_angle_offset(lv_obj_t *obj, lv_coord_t offset);
void lv_arcwheel_rotate_to_angle(lv_obj_t *obj, lv_coord_t angle, bool anim);
void lv_arcwheel_item_set_src(lv_obj_t *item, const void *src);

/**
 * @brief 设置自定义转换回调函数
 * @param obj arcwheel 对象
 * @param transform_cb 转换回调函数
 * @param params 转换参数（可选，传 NULL 使用默认值）
 */
void lv_arcwheel_set_item_transform_cb(lv_obj_t *obj, lv_arcwheel_item_transform_cb_t transform_cb,
                                       lv_arcwheel_transform_params_t *params);

/**
 * @brief 获取转换参数
 * @param obj arcwheel 对象
 * @return 转换参数指针
 */
lv_arcwheel_transform_params_t *lv_arcwheel_get_transform_params(lv_obj_t *obj);

lv_coord_t lv_arcwheel_get_radius_x(lv_obj_t *obj);
lv_coord_t lv_arcwheel_get_radius_y(lv_obj_t *obj);
lv_coord_t lv_arcwheel_get_current_angle(lv_obj_t *obj);
lv_coord_t lv_arcwheel_get_angle_offset(lv_obj_t *obj);
uint16_t lv_arcwheel_get_item_count(lv_obj_t *obj);
uint16_t lv_arcwheel_get_visible_count(lv_obj_t *obj);
lv_coord_t lv_arcwheel_get_sensitivity(lv_obj_t *obj);
bool lv_arcwheel_is_loop_enabled(lv_obj_t *obj);

void lv_arcwheel_set_friction_factor(lv_obj_t *obj, lv_coord_t factor);
void lv_arcwheel_set_snap_factor(lv_obj_t *obj, lv_coord_t factor);
void lv_arcwheel_set_snap_enabled(lv_obj_t *obj, bool enabled);

lv_coord_t lv_arcwheel_get_friction_factor(lv_obj_t *obj);
lv_coord_t lv_arcwheel_get_snap_factor(lv_obj_t *obj);
bool lv_arcwheel_is_snap_enabled(lv_obj_t *obj);

/**********************
 *      MACROS
 **********************/

#endif /*LV_USE_ARCWHEEL*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_ARCWHEEL_H*/

