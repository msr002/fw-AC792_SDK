#include "jlstream.h"
#include "audio_def.h"
#include "audio_player.h"

#define LOG_TAG_CONST       AUDIO_PLAYER
#define LOG_TAG             "[AUDIO_PLAYER]"
#define LOG_ERROR_ENABLE
#define LOG_INFO_ENABLE
#define LOG_DUMP_ENABLE
#include "debug.h"

#define AUDIO_PLAY_CBUF_SIZE           64 * 1024   //解码音频缓存

static u8 *audio_play_buf;
static cbuffer_t audio_play_cbuf;
static int ref = 0;
static struct vir_source_player *player;

static int virtual_dev_read(void *file, u8 *buf, int len)
{
    u8 cnt = 0;

    while (cbuf_get_data_size(&audio_play_cbuf) < len) {
        if (++cnt == 4) {
            return 0;
        }
        os_time_dly(1);
    }

    return cbuf_read(&audio_play_cbuf, buf, len);
}

static int virtual_dev_get_fmt(void *file, struct stream_fmt *fmt)
{
    fmt->sample_rate = 16000;
    fmt->coding_type = AUDIO_CODING_PCM;
    fmt->channel_mode = AUDIO_CH_L;
    return 0;
}


static const struct stream_file_ops virtual_dev_ops = {
    .read       = virtual_dev_read,
    .get_fmt    = virtual_dev_get_fmt,
};


int audio_player_one_frame(u8 *buf, u32 size)
{
    u32 cur_size;
    cur_size =  cbuf_get_data_size(&audio_play_cbuf);

    if (cur_size + size >= AUDIO_PLAY_CBUF_SIZE) {
        log_info("auido player cbuf full  clean  ! \n");
        cbuf_clear(&audio_play_cbuf);
    }

    cbuf_write(&audio_play_cbuf, buf, size);
    return 0;
}

int audio_player_init(void)
{
    int err;
    ref++;

    if (ref > 1) {
        log_debug("audio player init ref:%d \n", ref);
        return 0;
    }

    audio_play_buf = (u8 *)malloc(AUDIO_PLAY_CBUF_SIZE);
    if (audio_play_buf == NULL) {
        log_error("audio_play_buf malloc fail");
        goto __err;

    }
    cbuf_init(&audio_play_cbuf, audio_play_buf, AUDIO_PLAY_CBUF_SIZE);
    player = vir_source_player_open((void *)&audio_play_cbuf, &virtual_dev_ops);
    if (!player) {
        log_error("vir_source_player_open err");
        goto __err;
    }
    vir_source_player_start(player);

    void app_audio_set_volume(u8 state, s16 volume, u8 fade);
    app_audio_set_volume(app_audio_get_state(), 50, 0);

    return 0;
__err:
    if (player) {
        vir_source_player_close(player);
        player = NULL;
    }
    if (audio_play_buf) {
        free(audio_play_buf);
        audio_play_buf = NULL;
    }

    return -1;
}

int audio_player_exit(void)
{
    ref--;

    if (ref > 0) {
        log_debug("audio_player_exit ref:%d \n", ref);
        return 0;
    }

    if (player) {
        vir_source_player_close(player);
        player = NULL;
    }

    if (audio_play_buf) {
        free(audio_play_buf);
        audio_play_buf = NULL;
    }

    return 0;
}



