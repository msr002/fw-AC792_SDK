#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE
#include "lvgl.h"
#include "../generated/gui_guider.h"

#if !LV_USE_GUIBUILDER_SIMULATOR
#include "app_core.h"
#include "app_config.h"
#include "action.h"
#include "ui.h"
#endif

#if !LV_USE_GUIBUILDER_SIMULATOR

#define CONFIG_FONT_JPEG_PATH "mnt/sdfile/EXT_RESERVED/uipackres/ui/poweron.jpg"

#include "system/includes.h"
#include "pipeline_core.h"
#include "asm/jpeg_codec.h"
#include "app_config.h"
#include "server/video_server.h"//app_struct
#include "server/video_dec_server.h"//dec_struct

#ifdef CONFIG_VIDEO_ENABLE

struct _jpeg_disp_f_t {
    struct server *dec_server;
};
struct _jpeg_disp_f_t map_jpeg_disp_fh = {0};
#define __this   (&map_jpeg_disp_fh)
#define JPG_MAX_SIZE 100*1024

int map_jpeg_disp_one_frame(u16 width, u16 height, u8 *buf, int len)
{
    union video_dec_req dec_req = {0};
    dec_req.dec.fb = "fb1";
    dec_req.dec.left = 0;
    dec_req.dec.top = 0;
    dec_req.dec.width = width;//屏幕的宽高
    dec_req.dec.height = height;
    dec_req.dec.thm_first = 0;
    dec_req.dec.pctl = NULL;
    dec_req.dec.preview = 0;
    dec_req.dec.image.buf = buf;
    dec_req.dec.image.size = len;
    return server_request(__this->dec_server, VIDEO_REQ_DEC_IMAGE, &dec_req);
}

int map_jpeg_disp_frame_init(void)
{
    memset(__this, 0x00, sizeof(struct _jpeg_disp_f_t));

    if (!__this->dec_server) {
        struct video_dec_arg arg = {0};
        arg.dev_name = "video_dec";
        arg.video_buf_size = JPG_MAX_SIZE;
        __this->dec_server = server_open("video_dec_server", &arg);
        if (!__this->dec_server) {
            printf("open video_dec_server fail");
            return -EFAULT;
        }
    }

    return 0;
}

int map_jpeg_disp_frame_uninit(void)
{
    union video_dec_req dec_req = {0};
    server_request(__this->dec_server, VIDEO_REQ_DEC_STOP, &dec_req);
    server_close(__this->dec_server);
    __this->dec_server = NULL;
    return 0;
}

#endif

extern lv_ui guider_ui;// Screen page_map
void update_text_lbl_1(const char *str)
{
    lv_ui_page_map *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_PAGE_MAP);
    lvgl_rpc_post_func(lv_label_set_text, 2, ui_scr->page_map_lbl_1, str);
}
void update_text_lbl_2(const char *str)
{
    lv_ui_page_map *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_PAGE_MAP);
    lvgl_rpc_post_func(lv_label_set_text, 2, ui_scr->page_map_lbl_2, str);
}
void update_text_lbl_3(const char *str)
{
    lv_ui_page_map *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_PAGE_MAP);
    lvgl_rpc_post_func(lv_label_set_text, 2, ui_scr->page_map_lbl_3, str);
}
void update_text_lbl_4(const char *str)
{
    lv_ui_page_map *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_PAGE_MAP);
    lvgl_rpc_post_func(lv_label_set_text, 2, ui_scr->page_map_lbl_4, str);
}

//resolution
void update_text_lbl_10(const char *str)
{
    lv_ui_page_map *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_PAGE_MAP);
    lvgl_rpc_post_func(lv_label_set_text, 2, ui_scr->page_map_lbl_10, str);
}
//fps
void update_text_lbl_7(const char *str)
{
    lv_ui_page_map *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_PAGE_MAP);
    lvgl_rpc_post_func(lv_label_set_text, 2, ui_scr->page_map_lbl_7, str);
}
//bitrate
void update_text_lbl_9(const char *str)
{
    lv_ui_page_map *ui_scr = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_PAGE_MAP);
    lvgl_rpc_post_func(lv_label_set_text, 2, ui_scr->page_map_lbl_9, str);
}

#endif
#endif
