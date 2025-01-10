#include "system/includes.h"
#include "server/audio_server.h"

#define AUDIO_DEC_BUF_MAX_LEN        2 * 1024   //解码音频缓存

static u8 *audio_dec_buf;
static cbuffer_t audio_dec_save_cbuf;
static struct server *audio_dec_server;
static int ref = 0;

static int vfs_audio_dec_fread(void *file, void *data, u32 len)
{
    u32 rlen = 0;

    do {
        rlen = cbuf_read(&audio_dec_save_cbuf, data, len);
        if (rlen == len) {
            break;
        }
    } while (rlen);

    return len;
}

static int vfs_audio_dec_fclose(void *file)
{
    return 0;
}

static int vfs_audio_dec_flen(void *file)
{
    return 0;
}

static const struct audio_vfs_ops vfs_audio_dec_ops = {
    .fwrite = NULL,
    .fread  = vfs_audio_dec_fread,
    .fclose = vfs_audio_dec_fclose,
    .flen   = vfs_audio_dec_flen,
};


static int audio_dec_write_cbuf(u8 *buf, u32 size)
{
    u32 cur_size;
    cur_size =  cbuf_get_data_size(&audio_dec_save_cbuf);

    if (cur_size + size >= AUDIO_DEC_BUF_MAX_LEN) {
        cbuf_clear(&audio_dec_save_cbuf);
    }

    cbuf_write(&audio_dec_save_cbuf, buf, size);

    return 0;
}

int bbm_audio_dec_one_frame(u8 *buf, u32 size)
{
    audio_dec_write_cbuf(buf, size);

    return 0;
}


int bbm_audio_dec_init(void)
{
    int err;
    union audio_req req = {0};

    ref++;
    printf("audio_dec_init ref:%d \n", ref);

    if (ref > 1) {
        return 0;
    }

    audio_dec_server = server_open("audio_server", "dec");
    if (!audio_dec_server) {
        printf("open audio_dec_server fail");
        goto __err;
    }

    audio_dec_buf = (u8 *)malloc(AUDIO_DEC_BUF_MAX_LEN);
    if (audio_dec_buf == NULL) {
        printf("audio_dec_buf malloc fail");
        goto __err;

    }
    cbuf_init(&audio_dec_save_cbuf, audio_dec_buf, AUDIO_DEC_BUF_MAX_LEN);

    req.dec.cmd             = AUDIO_DEC_OPEN;
    req.dec.volume          = 100;
    req.dec.output_buf      = NULL;
    req.dec.output_buf_len  = 4096;
    req.dec.channel         = 1;
    req.dec.sample_rate     = 8000;
    req.dec.priority        = 1;
    req.dec.vfs_ops         = &vfs_audio_dec_ops;
    req.dec.dec_type 		= "pcm";
    req.dec.sample_source   = "dac";

    err = server_request(audio_dec_server, AUDIO_REQ_DEC, &req);
    if (err) {
        printf("audio server req open err\n");
        goto __err;
    }

    req.dec.cmd = AUDIO_DEC_START;
    err = server_request(audio_dec_server, AUDIO_REQ_DEC, &req);
    if (err) {
        printf("audio server req start err\n");
        goto __err;
    }


    return 0;

__err:
    if (audio_dec_server) {
        req.dec.cmd = AUDIO_DEC_STOP;
        server_request(audio_dec_server, AUDIO_REQ_DEC, &req);

        server_close(audio_dec_server);
        audio_dec_server = NULL;
    }
    if (audio_dec_buf) {
        free(audio_dec_buf);
        audio_dec_buf = NULL;
    }
    return -1;
}

int bbm_audio_dec_exit(void)
{
    union audio_req req = {0};

    ref--;
    printf("audio_dec_exit ref:%d \n", ref);

    if (ref > 0) {
        return 0;
    }

    if (audio_dec_server) {
        req.dec.cmd = AUDIO_DEC_STOP;
        server_request(audio_dec_server, AUDIO_REQ_DEC, &req);

        server_close(audio_dec_server);
        audio_dec_server = NULL;
    }
    if (audio_dec_buf) {
        free(audio_dec_buf);
        audio_dec_buf = NULL;
    }

    return 0;
}



