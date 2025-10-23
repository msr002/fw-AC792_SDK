#include "pipeline_core.h"
#include "video/videobuf.h"
#include "device/device.h"
#include "fs/fs.h"

#define __ALIGN_2(a)   (((a) + 1) / 2 * 2)
#define __ALIGN_16(a)   (((a) + 15) / 16 * 16)

static pipe_core_t *pipe_core = NULL;
struct video_device *device = NULL;
char *output_buf = NULL;
int output_buf_len = 2 * 1024 * 1024;

static int video_dev_reqbufs(struct video_reqbufs *b)
{
    return videobuf_reqbufs(&device->video_q, b);
}


static int video_dev_qbuf(struct video_buffer *b)
{
    return videobuf_qbuf(&device->video_q, b);
}

static int video_dev_dqbuf(struct video_buffer *b)
{
    return videobuf_dqbuf(&device->video_q, b);
}


static int video_streamon(int channel)
{
    int err;
    struct video_device *video = device;

    videobuf_streamon(&video->video_q, &channel);

    return 0;
}

static int video_streamoff(int index)
{
    int err;
    struct video_device *video = (struct video_device *)device;

    err = videobuf_streamoff(&video->video_q, index);
    if (err) {
        return err;
    }
    return 0;
}


static int transition_init(struct video_format *f)
{
    struct video_reqbufs breq = {0};

    device = (struct video_device *)zalloc(sizeof(struct video_device));
    if (!device) {
        printf("no mem\n");
        return -ENOMEM;
    }

    device->major = 0;
    device->mijor = 0;

    os_sem_create(&device->sem, 0);
    videobuf_queue_init(&device->video_q, 32, "bts_0");
    output_buf = malloc(output_buf_len);
    if (!output_buf) {
        printf("outputbuf malloc err!");
        return -1;
    }
    breq.buf  = output_buf;
    breq.size = output_buf_len;
    video_dev_reqbufs(&breq);
    pipe_core = pipeline_init(NULL, NULL);
    if (!pipe_core) {
        printf("err!!\n");
        free(device);
        return -1;
    }
    pipe_core->channel = 0;
    int line_cnt = 0;
    pipe_filter_t *jpeg_dec_filter, *imc_filter, *sink_filter, *virtual_filter,
                  *jpeg_enc_filter, *rep_filter;

    char *source = plugin_factory_find("virtual");

    pipe_core->channel = plugin_source_to_channel(source);
    virtual_filter = pipeline_filter_add(pipe_core, source);
    jpeg_dec_filter = pipeline_filter_add(pipe_core, plugin_factory_find("jpeg_dec"));

    jpeg_enc_filter = pipeline_filter_add(pipe_core, plugin_factory_find("jpeg_enc"));
    sink_filter = pipeline_filter_add(pipe_core, plugin_factory_find("videosink"));

    line_cnt = 16;
    rep_filter = pipeline_filter_add(pipe_core, plugin_factory_find("rep"));
    imc_filter = pipeline_filter_add(pipe_core, plugin_factory_find("imc"));

    pipeline_param_set(pipe_core, NULL, PIPELINE_SET_FORMAT, (int)f);
    pipeline_param_set(pipe_core, NULL, PIPELINE_SET_EXTERN_BUFFER, (int)device);
    pipeline_param_set(pipe_core, NULL, PIPELINE_SET_BUFFER_LINE, (int)&line_cnt);

    pipeline_filter_link(virtual_filter, jpeg_dec_filter);
    pipeline_filter_link(jpeg_dec_filter, rep_filter);
    pipeline_filter_link(rep_filter, imc_filter);
    pipeline_filter_link(imc_filter, jpeg_enc_filter);
    pipeline_filter_link(jpeg_enc_filter, sink_filter);

    pipeline_prepare(pipe_core);

    return 0;
}


static int transition_play(int on)
{
    int time_cnt = 0;
    printf("<=%s", __func__);

    if (on) {
        pipeline_start(pipe_core);
        plugin_factory_plugin_status();
    } else {
        pipeline_stop(pipe_core);
    }

    return 0;
}

static u8 *video_dec_find_jpg_frame(u8 *buf, int limit)
{
    u8 *stream;
    int index = 0;

    stream = buf;
    while (index < limit) {
        if (stream[0] == 0xFF && stream[1] == 0xD8) {
            return stream;
        }
        stream++;
        index++;
    }

    return NULL;
}



static int transition_write(void *data, u32 len)
{
    int err = -EINVAL;

    struct video_cap_buffer buffer = {0};

    u8 *frame = video_dec_find_jpg_frame(data, 64);
    if (!frame) {
        return -EFAULT;
    }
    int frame_len = len - ((u8 *)frame - (u8 *)data);
    buffer.size = frame_len;
    buffer.buf = frame;
    pipeline_param_set(pipe_core, NULL, VIDIOC_RDBUF, (int)&buffer);
    return len;
}


static int transition_close()
{
    int channel = 0;
    pipeline_param_set(pipe_core, NULL, PIPELINE_SET_CUR_CHANNEL, &channel);
    pipeline_stop(pipe_core);
    pipeline_reset(pipe_core);
    pipeline_uninit(pipe_core);
    video_streamoff(0);
    pipe_core = NULL;
    return 0;
}

static int jpeg_get_size(u8 *stream, int len, u16 *width, u16 *height, u16 *format)
{
    u8 marker;
    int chunk_len;

    if ((stream[0] != 0xFF) || (stream[1] != 0xD8)) {
        printf("not jpg picture.");
        return -EINVAL;
    }

    stream += 2;

    while (1) {
        if (*stream++ != 0xFF) {
            return -EINVAL;
        }

        while (*stream == 0xFF) {
            stream++;
        }

        marker = *stream++;
        chunk_len = (u16)(stream[0] << 8) | stream[1];

        if (marker == 0xC0) {
            *height = (u16)((stream[3] << 8) | stream[4]);
            *width  = (u16)__ALIGN_16((stream[5] << 8) | stream[6]);
            int offset = 8;
            while (offset < chunk_len) {
                if (*(stream + offset) == 0x1) {
                    u8 sample_Y = *(stream + offset + 1);
                    if (sample_Y == 0x11) {
                        *format = VIDEO_PIX_FMT_YUV444;
                    } else if (sample_Y == 0x22) {
                        *format = VIDEO_PIX_FMT_YUV420;
                    } else {
                        *format = VIDEO_PIX_FMT_YUV422;
                    }
                    break;
                }
                offset += 3;
            }
            break;
        }

        stream += chunk_len;
    }
    return 0;
}

int video_scaler_init(u16 src_w, u16 src_h, u16 dst_w, u16 dst_h)
{
    struct video_format f = {
        .type = VIDEO_BUF_TYPE_VIDEO_CAPTURE,
        .win.width = __ALIGN_2(dst_w),
        .win.height = __ALIGN_2(dst_h),
        .pixelformat = VIDEO_PIX_FMT_JPEG | VIDEO_PIX_FMT_YUV420,
        .src_width = src_w,
        .src_height = src_h,
        .online = 1
    };
    transition_init(&f);
    transition_play(1);
    video_streamon(0);
    return 0;
}

int video_scaler_process(char *jpg_buf, int jpg_len, char **scaled_buf)
{
    struct video_buffer b;

    transition_write(jpg_buf, jpg_len);

    b.noblock = 0;
    b.timeout = 50;
    b.index = 0;

    if (video_dev_dqbuf(&b) < 0) {
        return -1;
    }

    *scaled_buf = malloc(b.len);
    if (!*scaled_buf) {
        printf("malloc err !");
        return -1;
    }
    memcpy(*scaled_buf, b.baddr, b.len);

    video_dev_qbuf(&b);

    return b.len;
}

int video_scaler_release()
{
    transition_close();
    if (output_buf) {
        free(output_buf);
        output_buf = NULL;
    }

    if (device) {
        videobuf_queue_release(&device->video_q);
        free(device);
        device = NULL;
    }
}
