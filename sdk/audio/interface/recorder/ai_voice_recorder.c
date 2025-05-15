#ifdef MEDIA_SUPPORT_MS_EXTENSIONS
#pragma bss_seg(".ai_voice_recorder.data.bss")
#pragma data_seg(".ai_voice_recorder.data")
#pragma const_seg(".ai_voice_recorder.text.const")
#pragma code_seg(".ai_voice_recorder.text")
#endif
#include "jlstream.h"
#include "server/ai_server.h"
#include "encoder_fmt.h"
#include "vad_node.h"

struct ai_voice_recorder {
    struct jlstream *stream;
    struct ai_voice_param param;
};

static void ai_voice_recorder_callback(void *private_data, int event)
{
    struct jlstream *stream = (struct jlstream *)private_data;

    switch (event) {
    case STREAM_EVENT_START:
        break;
    }
}

static int ai_recorder_data_output(void *priv, u8 *buf, int len)
{
    struct ai_voice_recorder *recorder = (struct ai_voice_recorder *)priv;

    if (recorder->param.output) {
        recorder->param.output(recorder->param.priv, buf, len);
    }

    return len;
}

static const struct stream_file_ops ai_tx_ops = {
    .write = ai_recorder_data_output,
};

static int vad_callback(enum vad_event event)
{
    switch (event) {
    case VAD_EVENT_SPEAK_START:
        break;
    case VAD_EVENT_SPEAK_STOP:
        break;
    }

    return 0;
}

void *ai_voice_recorder_open(struct ai_voice_param *param)
{
    int err;
    struct stream_fmt fmt = {0};
    struct encoder_fmt enc_fmt = {0};
    vad_node_priv_t vad = {0};

    u16 uuid = jlstream_event_notify(STREAM_EVENT_GET_PIPELINE_UUID, (int)"ai_voice");
    if (uuid == 0) {
        return NULL;
    }

    struct ai_voice_recorder *recorder = zalloc(sizeof(*recorder));
    if (!recorder) {
        return NULL;
    }

    memcpy(&recorder->param, param, sizeof(*param));

    recorder->stream = jlstream_pipeline_parse(uuid, NODE_UUID_ADC);
    if (!recorder->stream) {
        goto __exit0;
    }

    switch (param->code_type) {
    case AUDIO_CODING_OPUS:
        //1. quality:bitrate     0:16kbps    1:32kbps    2:64kbps
        //   quality: MSB_2:(bit7_bit6)     format_mode    //0:百度_无头.                   1:酷狗_eng+range.
        //   quality:LMSB_2:(bit5_bit4)     low_complexity //0:高复杂度,高质量.兼容之前库.  1:低复杂度,低质量.
        //2. sample_rate         sample_rate=16k         ignore
        enc_fmt.quality = param->quality;
        fmt.sample_rate = param->sample_rate;
        fmt.coding_type = AUDIO_CODING_OPUS;
        break;
    case AUDIO_CODING_SPEEX:
        enc_fmt.quality = param->quality;
        enc_fmt.complexity = 2;
        fmt.sample_rate = param->sample_rate;
        fmt.coding_type = AUDIO_CODING_SPEEX;
        break;
    default:
        goto __exit1;
    }

    err = jlstream_node_ioctl(recorder->stream, NODE_UUID_ENCODER, NODE_IOC_SET_PRIV_FMT, (int)(&enc_fmt));
    if (err) {
        goto __exit1;
    }

    err = jlstream_node_ioctl(recorder->stream, NODE_UUID_AI_TX, NODE_IOC_SET_FMT, (int)(&fmt));
    if (err) {
        goto __exit1;
    }

    //设置ADC的中断点数
    err = jlstream_node_ioctl(recorder->stream, NODE_UUID_SOURCE, NODE_IOC_SET_PRIV_FMT, 320);
    if (err) {
        goto __exit1;
    }

    vad.vad_callback = vad_callback;
    jlstream_node_ioctl(recorder->stream, NODE_UUID_VAD, NODE_IOC_SET_PRIV_FMT, (int)&vad);

    struct stream_file_info info = {
        .file = (void *)recorder,
        .ops = &ai_tx_ops
    };
    err = stream_node_ioctl((struct stream_node *)recorder->stream->snode, NODE_UUID_AI_TX, NODE_IOC_SET_FILE, (int)&info);
    if (err) {
        goto __exit1;
    }

    jlstream_set_callback(recorder->stream, recorder->stream, ai_voice_recorder_callback);
    jlstream_set_scene(recorder->stream, STREAM_SCENE_AI_VOICE);

    err = jlstream_start(recorder->stream);
    if (err) {
        goto __exit1;
    }

    return recorder;

__exit1:
    jlstream_release(recorder->stream);
__exit0:
    free(recorder);
    return NULL;
}

int ai_voice_recorder_close(void *priv)
{
    struct ai_voice_recorder *recorder = (struct ai_voice_recorder *)priv;

    if (!recorder) {
        return 0;
    }

    jlstream_stop(recorder->stream, 0);
    jlstream_release(recorder->stream);

    free(recorder);

    jlstream_event_notify(STREAM_EVENT_CLOSE_RECORDER, (int)"ai_voice");

    return 0;
}

