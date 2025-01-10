#include "system/includes.h"
#include "pipeline_core.h"
#include "asm/jpeg_codec.h"

static void on_event(const char *name, int type, void *arg)
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

int bbm_pipe_disp_one_frame(pipe_core_t *pipeline_core, u8 *buf, int len)
{
    if (!pipeline_core) {
        return -1;
    }

    struct video_cap_buffer buffer;
    buffer.buf = buf;
    buffer.size = len;
    pipeline_param_set(pipeline_core, NULL, VIDIOC_RDBUF, &buffer);

    return 0;
}

int bbm_video_pipe_init(pipe_core_t **pipe_core, struct video_window *win)
{
    int ret;
    pipe_core_t *pipeline_core = NULL;
    pipe_filter_t *virtual_filter, *jpeg_dec_filter, *rep_filter, *imc_filter, *disp_filter;

    struct video_format f = {0};

    //TODO
    //暂时固定VGA
    f.src_width = 640;
    f.src_height = 480;
    f.type = VIDEO_BUF_TYPE_VIDEO_PLAY;
    f.pixelformat = VIDEO_PIX_FMT_JPEG | VIDEO_PIX_FMT_YUV420;
    memcpy(&f.win, win, sizeof(struct video_window));

    pipeline_core = pipeline_init(on_event, NULL);
    if (!pipeline_core) {
        printf("pipeline init err\n");
        return -1;
    }

    char *source_name = plugin_factory_find("virtual");

    pipeline_core->channel = plugin_source_to_channel(source_name);
    virtual_filter = pipeline_filter_add(pipeline_core, source_name);
    jpeg_dec_filter = pipeline_filter_add(pipeline_core, plugin_factory_find("jpeg_dec"));
    rep_filter = pipeline_filter_add(pipeline_core, plugin_factory_find("rep"));
    imc_filter = pipeline_filter_add(pipeline_core, plugin_factory_find("imc"));
    disp_filter = pipeline_filter_add(pipeline_core, plugin_factory_find("disp"));


    pipeline_param_set(pipeline_core, NULL, PIPELINE_SET_FORMAT, &f);

    int line_cnt = 16;
    pipeline_param_set(pipeline_core, NULL, PIPELINE_SET_BUFFER_LINE, (int)&line_cnt);

    pipeline_filter_link(virtual_filter, jpeg_dec_filter);

    pipeline_filter_link(jpeg_dec_filter, rep_filter);

    pipeline_filter_link(rep_filter, imc_filter);

    pipeline_filter_link(imc_filter, disp_filter);

    pipeline_prepare(pipeline_core);

    pipeline_start(pipeline_core);

    *pipe_core = pipeline_core;

    return 0;
}



int bbm_video_pipe_exit(pipe_core_t **pipe_core)
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

int bbm_video_pipe_set_zoom(pipe_core_t *pipe_core, void *arg)
{
    if (!pipe_core) {
        return -1;
    }
    return pipeline_param_set(pipe_core, NULL, VIDIOC_SET_DIS_CROP, arg);
}


#if 0

static int video_format_src_init(struct video_format *f, u8 *buf, u32 len)
{
    struct jpeg_image_info info = {0};
    int fmt;
    int err;
    info.input.data.buf = buf;
    info.input.data.len = len;
    err = jpeg_decode_image_info(&info);
    if (err) {
        printf("jpeg_decode_image_info err:%d\n", err);
        return -1;
    }
    switch (info.sample_fmt) {
    case JPG_SAMP_FMT_YUV444:
        fmt = VIDEO_PIX_FMT_YUV444;
        break;
    case JPG_SAMP_FMT_YUV422:
        fmt = VIDEO_PIX_FMT_YUV422;
        break;
    case JPG_SAMP_FMT_YUV420:
        fmt = VIDEO_PIX_FMT_YUV420;
        break;
    default:
        printf("input err fmt\n");
        return -1;
        break;
    }
    f->src_width = info.width;
    f->src_height = info.height;
    f->type = VIDEO_BUF_TYPE_VIDEO_PLAY;
    f->pixelformat = VIDEO_PIX_FMT_JPEG | fmt;

    //todo
    //区分
    if (!f->win.left) {
        sprintf(fb_name, "fb1");
    } else {
        sprintf(fb_name, "fb2");
    }
    /* sprintf(fb_name, "fb%d", fb_num); */
    f->private_data = fb_name;

    return 0;
}


int bbm_video_pipe_init(pipe_core_t **pipe_core, struct video_format *f, u8 *buf, u32 len)
{
    int ret;
    pipe_core_t *pipeline_core = NULL;
    pipe_filter_t *virtual_filter, *jpeg_dec_filter, *rep_filter, *imc_filter, *disp_filter;

    ret = video_format_src_init(f, buf, len);
    if (ret) {
        return -1;
    }

    pipeline_core = pipeline_init(on_event, NULL);
    if (!pipeline_core) {
        printf("pipeline init err\n");
        return -1;
    }

    char *source_name = plugin_factory_find("virtual");

    pipeline_core->channel = plugin_source_to_channel(source_name);
    virtual_filter = pipeline_filter_add(pipeline_core, source_name);
    jpeg_dec_filter = pipeline_filter_add(pipeline_core, plugin_factory_find("jpeg_dec"));
    rep_filter = pipeline_filter_add(pipeline_core, plugin_factory_find("rep"));
    imc_filter = pipeline_filter_add(pipeline_core, plugin_factory_find("imc"));
    disp_filter = pipeline_filter_add(pipeline_core, plugin_factory_find("disp"));


    pipeline_param_set(pipeline_core, NULL, PIPELINE_SET_FORMAT, f);

    int line_cnt = 16;
    pipeline_param_set(pipeline_core, NULL, PIPELINE_SET_BUFFER_LINE, (int)&line_cnt);

    pipeline_filter_link(virtual_filter, jpeg_dec_filter);

    pipeline_filter_link(jpeg_dec_filter, rep_filter);

    pipeline_filter_link(rep_filter, imc_filter);

    pipeline_filter_link(imc_filter, disp_filter);

    pipeline_prepare(pipeline_core);

    pipeline_start(pipeline_core);

    *pipe_core = pipeline_core;

    //todo
    fb_num++;

    return 0;
}
#endif



