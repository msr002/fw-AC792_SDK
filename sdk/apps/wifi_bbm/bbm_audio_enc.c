#include "system/includes.h"
#include "server/audio_server.h"

#define AUDIO_ENC_FRAME_SIZE    640     //每个音频包的大小，越大会导致延迟高
#define AUDIO_ENC_BUF_MAX_LEN        2 * 1024   //编码音频缓存

static OS_SEM  bbm_audio_enc_sem;
static struct server *audio_enc_server;
static u8 *audio_enc_buf;
static cbuffer_t audio_enc_save_cbuf;


//编码器输出PCM数据
static int vfs_audio_enc_fwrite(void *file, void *data, u32 len)
{
    cbuffer_t *cbuf = (cbuffer_t *)file;
    if (0 == cbuf_write(cbuf, data, len)) {
        //上层buf写不进去时清空一下，避免出现声音滞后的情况
        cbuf_clear(cbuf);
    }
    os_sem_set(&bbm_audio_enc_sem, 0);
    os_sem_post(&bbm_audio_enc_sem);

    //此回调返回0录音就会自动停止
    return len;
}

static int vfs_audio_enc_fread(void *file, void *data, u32 len)
{
    cbuffer_t *cbuf = (cbuffer_t *)file;
    u32 rlen;
    int ret;

    do {
        ret = os_sem_pend(&bbm_audio_enc_sem, 100);
        if (ret) {
            return -1;
        }

        rlen = cbuf_get_data_size(cbuf);
        rlen = rlen > len ? len : rlen;
        if (cbuf_read(cbuf, data, rlen) > 0) {
            len = rlen;
            break;
        }

    } while (rlen);

    //返回成功读取的字节数
    return len;
}

static int vfs_audio_enc_fclose(void *file)
{
    return 0;
}

static int vfs_audio_enc_flen(void *file)
{
    return 0;
}

static const struct audio_vfs_ops vfs_audio_enc_ops = {
    .fwrite = vfs_audio_enc_fwrite,
    .fread  = vfs_audio_enc_fread,
    .fclose = vfs_audio_enc_fclose,
    .flen   = vfs_audio_enc_flen,
};


int bbm_audio_enc_get_data(u8 *data_buf)
{
    return vfs_audio_enc_fread(&audio_enc_save_cbuf, data_buf, AUDIO_ENC_FRAME_SIZE);
}

int bbm_audio_enc_init(void)
{
    union audio_req req = {0};
    int err;

    os_sem_create(&bbm_audio_enc_sem, 0);

    audio_enc_server = server_open("audio_server", "enc");
    if (!audio_enc_server) {
        printf("open audio_enc_server fail");
        goto __err;
    }

    audio_enc_buf = (u8 *)malloc(AUDIO_ENC_BUF_MAX_LEN);
    if (audio_enc_buf == NULL) {
        printf("audio_enc_buf malloc fail");
        goto __err;

    }
    cbuf_init(&audio_enc_save_cbuf, audio_enc_buf, AUDIO_ENC_BUF_MAX_LEN);

    req.enc.frame_size = AUDIO_ENC_FRAME_SIZE;
    req.enc.output_buf_len = req.enc.frame_size * 3; //底层缓冲buf至少设成3倍frame_size
    req.enc.cmd = AUDIO_ENC_OPEN;
    req.enc.channel = 1;
    req.enc.volume =  100;
    req.enc.sample_rate = 8000;
    req.enc.format = "pcm";
    req.enc.sample_source = "mic";
    req.enc.vfs_ops = &vfs_audio_enc_ops;
    req.enc.file = (FILE *)&audio_enc_save_cbuf;

    err = server_request(audio_enc_server, AUDIO_REQ_ENC, &req);
    if (err) {
        goto __err;
    }

    return 0;

__err:
    if (audio_enc_server) {
        req.enc.cmd = AUDIO_ENC_CLOSE;
        server_request(audio_enc_server, AUDIO_REQ_ENC, &req);

        server_close(audio_enc_server);
        audio_enc_server = NULL;
    }
    if (audio_enc_buf) {
        free(audio_enc_buf);
        audio_enc_buf = NULL;
    }

    os_sem_del(&bbm_audio_enc_sem, OS_DEL_ALWAYS);

    return -1;
}

int bbm_audio_enc_exit(void)
{
    union audio_req req = {0};

    if (audio_enc_server) {
        req.enc.cmd = AUDIO_ENC_CLOSE;
        server_request(audio_enc_server, AUDIO_REQ_ENC, &req);

        server_close(audio_enc_server);
        audio_enc_server = NULL;
    }
    if (audio_enc_buf) {
        free(audio_enc_buf);
        audio_enc_buf = NULL;
    }

    os_sem_del(&bbm_audio_enc_sem, OS_DEL_ALWAYS);

    return 0;
}


