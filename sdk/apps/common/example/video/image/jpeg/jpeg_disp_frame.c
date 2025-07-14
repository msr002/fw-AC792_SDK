
#include "system/includes.h"
#include "pipeline_core.h"
#include "asm/jpeg_codec.h"
#include "app_config.h"

#ifdef CONFIG_VIDEO_ENABLE

struct _jpeg_disp_f_t {
    void *pipe_core;
    u16 src_w;
    u16 src_h;
    struct video_window win;
};
struct _jpeg_disp_f_t jpeg_disp_fh = {0};
#define __this   (&jpeg_disp_fh)

static void _on_event(const char *name, int type, void *arg)
{
    switch (type) {
    case EVENT_FRAME_DONE:
        break;
    case EVENT_PREPARE_DONE:
        printf("PREPARE %s done", name);
        break;
    case EVENT_START_DONE:
        printf("START %s done", name);
        break;
    case EVENT_STOP_DONE:
        printf("STOP %s done", name);
        break;
    case EVENT_RESET_DONE:
        printf("RESET %s done", name);
        break;
    case EVENT_BW_FULL:
    case EVENT_BUFFER_FULL:
    case EVENT_SPEED_FULL:
    case EVENT_OSD_ERR:
    case EVENT_LINE_ERR:
        printf("err %s ", name);
        break;
    }
}

int jpeg_disp_one_frame(pipe_core_t **pipe_core, u8 *buf, int len)
{
    pipe_core_t *pipeline_core = *pipe_core;
    struct jpeg_image_info info = {0};
    int err = 0;
    info.input.data.buf = buf;
    info.input.data.len = len;
    err = jpeg_decode_image_info(&info);
    if (err) {
        printf("err jpeg\n");
        return err;
    }
    if (__this->src_w != info.width || __this->src_h != info.height) {
        jpeg_disp_video_pipe_exit(pipe_core);
        __this->src_w = info.width;
        __this->src_h = info.height;
        printf("src_w:%d src_h:%d\n", __this->src_w, __this->src_h);
        jpeg_disp_video_pipe_init(pipe_core, &__this->win, __this->src_w, __this->src_h);
        printf("pipe_core=0x%x\n", pipe_core);
        pipeline_core = *pipe_core;
        printf("pipeline_core=0x%x\n", pipeline_core);
    }

    struct video_cap_buffer buffer;
    buffer.buf = buf;
    buffer.size = len;
    pipeline_param_set(pipeline_core, NULL, VIDIOC_RDBUF, &buffer);

    return 0;
}

int jpeg_disp_video_pipe_init(pipe_core_t **pipe_core, struct video_window *win, int src_w, int src_h)
{
    int ret;
    pipe_core_t *pipeline_core = NULL;
    pipe_filter_t *virtual_filter, *jpeg_dec_filter, *rep_filter, *imc_filter, *disp_filter, *sft_filter;

    struct video_format f = {0};

    f.src_width = src_w;
    f.src_height = src_h;
    f.type = VIDEO_BUF_TYPE_VIDEO_PLAY;
    f.pixelformat = VIDEO_PIX_FMT_JPEG | VIDEO_PIX_FMT_YUV420;
    memcpy(&f.win, win, sizeof(struct video_window));

    pipeline_core = pipeline_init(_on_event, NULL);
    if (!pipeline_core) {
        printf("pipeline init err\n");
        return -1;
    }

    char *rep_name = NULL;
    char *source_name = plugin_factory_find("virtual");

    pipeline_core->channel = plugin_source_to_channel(source_name);
    virtual_filter = pipeline_filter_add(pipeline_core, source_name);

    //todo
    rep_name = plugin_factory_find("rep");
    if (rep_name) {
        rep_filter = pipeline_filter_add(pipeline_core, rep_name);
        jpeg_dec_filter = pipeline_filter_add(pipeline_core, plugin_factory_find("jpeg_dec"));
        imc_filter = pipeline_filter_add(pipeline_core, plugin_factory_find("imc"));
        disp_filter = pipeline_filter_add(pipeline_core, plugin_factory_find("disp"));

        pipeline_param_set(pipeline_core, NULL, PIPELINE_SET_FORMAT, &f);

        int line_cnt = 16;
        pipeline_param_set(pipeline_core, NULL, PIPELINE_SET_BUFFER_LINE, (int)&line_cnt);

        pipeline_filter_link(virtual_filter, jpeg_dec_filter);

        pipeline_filter_link(jpeg_dec_filter, rep_filter);

        pipeline_filter_link(rep_filter, imc_filter);

        pipeline_filter_link(imc_filter, disp_filter);
    }

    pipeline_prepare(pipeline_core);

    pipeline_start(pipeline_core);

    *pipe_core = pipeline_core;

    return 0;
}



int jpeg_disp_video_pipe_exit(pipe_core_t **pipe_core)
{
    pipe_core_t *pipeline_core = *pipe_core;

    if (!pipeline_core) {
        return -1;
    }

    pipeline_stop(pipeline_core);

    pipeline_reset(pipeline_core);

    pipeline_uninit(pipeline_core);

    *pipe_core = NULL;

    return 0;
}

int jpeg_disp_frame_init(struct video_window *win)
{
    memset(__this, 0x00, sizeof(struct _jpeg_disp_f_t));
    memcpy(&__this->win, win, sizeof(struct video_window));

    return 0;
}

int jpeg_disp_frame_uninit(void)
{
    if (__this->pipe_core) {
        jpeg_disp_video_pipe_exit(&__this->pipe_core);
    }
    return 0;
}

#include "fs/fs.h"
void jpeg_disp_test(void *p)
{
    printf("\n[ debug ]--func=%s line=%d\n", __func__, __LINE__);
    static volatile u8 state = 0;
    struct video_window win = {0};
    win.width = 800;
    win.height = 480;
    win.combine = 1;
    if (state == 0) {
        jpeg_disp_frame_init(&win);
        FILE *profile_fp = fopen("mnt/sdfile/EXT_RESERVED/uipackres/ui/poweron.jpg", "r");
        if (profile_fp == NULL) {
            return;
        }
        u32 jpg_len = flen(profile_fp);
        struct vfs_attr file_attr;
        fget_attrs(profile_fp, &file_attr);
        u8 *jpg_buffer = file_attr.sclust;
        fclose(profile_fp);
        printf("\n[ debug ]--func=%s line=%d %d\n", __func__, __LINE__, jpg_len);
        jpeg_disp_one_frame(&__this->pipe_core, jpg_buffer, jpg_len);
        printf("\n[ debug ]--func=%s line=%d %d\n", __func__, __LINE__, jpg_len);
    } else {
        printf("\n[ debug ]--func=%s line=%d\n", __func__, __LINE__);
        jpeg_disp_frame_uninit();
    }
    state = !state;

}
#endif
