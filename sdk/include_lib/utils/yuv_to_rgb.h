#ifndef _YUV_TO_RGB_H
#define _YUV_TO_RGB_H

#include "generic/typedef.h"

u16 rgb_24_to_565(u8 R, u8 G, u8 B);
/**
 * @param yuvBuffer_in   YUV输入源数据缓存区，存储原始YUV格式数据
 * @param rgbBuffer_out  RGB输出缓存区，用于存储转换后的RGB格式数据
 * @param width          分辨率宽度，单位为像素
 * @param height         分辨率高度，单位为像素
 * @param be             大小端存储标识：1表示大端存储，0表示小端存储
 */
void yuv420p_to_rgb24(unsigned char *yuvBuffer_in, unsigned char *rgbBuffer_out, int width, int height);
void yuv422p_to_rgb24(unsigned char *yuvBuffer_in, unsigned char *rgbBuffer_out, int width, int height);
void yuv444p_to_rgb24(unsigned char *yuvBuffer_in, unsigned char *rgbBuffer_out, int width, int height);
void yuv420p_to_rgb565(unsigned char *yuvBuffer_in, unsigned char *rgbBuffer_out, int width, int height, char be);
void yuv422p_to_rgb565(unsigned char *yuvBuffer_in, unsigned char *rgbBuffer_out, int width, int height, char be);
void yuv444p_to_rgb565(unsigned char *yuvBuffer_in, unsigned char *rgbBuffer_out, int width, int height, char be);
/************************快速查表法**************************************/
void yuv420p_quto_rgb24(unsigned char *yuvBuffer_in, unsigned char *rgbBuffer_out, int width, int height);
void yuv420p_quto_rgb565(unsigned char *yuvBuffer_in, unsigned char *rgbBuffer_out, int width, int height, char be);
void yuv422p_quto_rgb565(unsigned char *yuvBuffer_in, unsigned char *rgbBuffer_out, int width, int height, char be);
void yuv444p_quto_rgb565(unsigned char *yuvBuffer_in, unsigned char *rgbBuffer_out, int width, int height, char be);
/**
 * YUV420P转RGB565并执行旋转缩放
 * @param yuv 输入源数据缓存区，存储YUV420P格式图像数据
 * @param rgb RGB输出缓存区，存储转换后的RGB565格式图像数据
 * @param sw  源数据宽度（像素）
 * @param sh  源数据高度（像素）
 * @param dw  目标数据宽度（像素），缩放后的图像宽度
 * @param dh  目标数据高度（像素），缩放后的图像高度
 */
void yuv420p_quto_rgb565_rotate_zoom(uint8_t *yuv, uint8_t *rgb, int sw, int sh, int dw, int dh);
/**
 * YUV420P转RGB565并旋转180度
 * @param yuv    输入YUV420P格式数据缓存区，需包含完整Y+U+V平面
 * @param rgb    输出RGB565格式数据缓存区，需预先分配width*height*2字节空间
 * @param width  图像宽度（像素），需与源数据匹配
 * @param height 图像高度（像素），需与源数据匹配
 */
void yuv420p_to_rgb565_rot180(uint8_t *yuv, uint16_t *rgb, int width, int height);
void yuv420p_to_rgb565_rot180_1(uint8_t *yuv, uint16_t *rgb, int width, int height);

/**
 * RGB24转YUV420P格式转换
 * @param rgb24     输入RGB24格式数据缓存区，每个像素占3字节(RGBRGB...)
 * @param yuv420p   输出YUV420P格式数据缓存区，需预分配1.5*width*height字节
 * @param width     图像宽度（像素）
 * @param height    图像高度（像素）
 * @return          成功返回数据大小，失败返回0
 */
int rgb24_to_yuv420p(unsigned char *rgb24, unsigned char *yuv420p, int width, int height);

/**
 * RGB565转YUV420P格式转换
 * @param rgb565    输入RGB565格式数据缓存区，每个像素占2字节
 * @param yuv420p   输出YUV420P格式数据缓存区，需预分配1.5*width*height字节
 * @param width     图像宽度（像素）
 * @param height    图像高度（像素）
 * @param be        字节序标识：1表示大端存储(RGB高字节在前)，0表示小端存储
 * @return          成功返回数据大小，失败返回0
 */
int rgb565_to_yuv420p(unsigned char *rgb565, unsigned char *yuv420p, int width, int height, char be);

/**********RGB565转RG24************/
void RGB565_to_RGB888(unsigned char *rgb565, unsigned char *rgb888, int width, int height);
/**********RGB888转RGB565************/
void RGB888_to_RGB565(unsigned char *rgb888, int width, int height);
/**********ARG888转RGB888************/
void ARGB888_to_RGB888(u8 *src, int width, int height, u8 *dst);
/**********ARGA转BGR565************/
void rgba_buf_to_bgr565_buf(unsigned char *rgba_buf, unsigned short *bgr565_buf, int width, int height);
/**********从ARGB帧缓冲区中裁剪指定区域*****************************************/
void crop_rgba_frame(unsigned long *frame, int width, int height, unsigned long *cropped_frame, int x, int y, int crop_width, int crop_height);
/**********RGB888转RGYUV420***********/
void RGB888_to_YUV420(u8 *rgb_buf, u8 *yuv_buf, u16 width, u16 heigh);

//RGB转YUV 一个像素点 效率低
u32 rgb2yuv(u8 r, u8 g, u8 b);

#endif
