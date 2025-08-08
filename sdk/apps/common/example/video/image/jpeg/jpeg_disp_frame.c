
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
struct _jpeg_disp_f_t jpeg_disp_fh = {0};
#define __this   (&jpeg_disp_fh)
#define JPG_MAX_SIZE 100*1024

int jpeg_disp_one_frame(u16 width, u16 height, u8 *buf, int len)
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

int jpeg_disp_frame_init(void)
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

int jpeg_disp_frame_uninit(void)
{
    union video_dec_req dec_req = {0};
    server_request(__this->dec_server, VIDEO_REQ_DEC_STOP, &dec_req);
    server_close(__this->dec_server);
    __this->dec_server = NULL;
    return 0;
}

#include "fs/fs.h"
void jpeg_disp_test(void *p)
{
    printf("\n[ debug ]--func=%s line=%d\n", __func__, __LINE__);
    static volatile u8 state = 0;
    u16 disp_width = 800;
    u16 disp_height = 480;
    if (state == 0) {
        jpeg_disp_frame_init();
        FILE *profile_fp = fopen("mnt/sdfile/EXT_RESERVED/logopackres/logo/poweron.jpg", "r");
        if (profile_fp == NULL) {
            return;
        }
        u32 jpg_len = flen(profile_fp);
        struct vfs_attr file_attr;
        fget_attrs(profile_fp, &file_attr);
        u8 *jpg_buffer = file_attr.sclust;
        fclose(profile_fp);
        printf("\n[ debug ]--func=%s line=%d %d\n", __func__, __LINE__, jpg_len);
        jpeg_disp_one_frame(disp_width, disp_height, jpg_buffer, jpg_len);
        printf("\n[ debug ]--func=%s line=%d %d\n", __func__, __LINE__, jpg_len);
    } else {
        printf("\n[ debug ]--func=%s line=%d\n", __func__, __LINE__);
        jpeg_disp_frame_uninit();
    }
    state = !state;

}
#endif
