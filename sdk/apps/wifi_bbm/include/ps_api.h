#ifndef PS_API_H__
#define PS_API_H__

enum {
    PS_SPEED_UP = 1,
    PS_SPEED_DOWN = 2
};

typedef struct _PS_CONTEXT_IO_ {
    void *outpriv;
    u32(*output)(void *priv, u8 *buf, int len);
} PS_audio_IO;

typedef struct _PS_CONTEXT_CONF_ {
    u16 chn;
    u16 sr;
    u16 speedV;
    u16 pitchV;
} PS_CONTEXT_CONF;

typedef struct _PS_API_CONTEXT_ {
    u32(*need_size)(void);
    u32(*open)(u8 *ptr, PS_audio_IO *audio_IO);
    u32(*dconfig)(u8 *ptr, PS_CONTEXT_CONF *conf_obj);
    u32(*run)(u8 *ptr, s16 *inbuf, u32 len);
    u32(*run_same)(u8 *ptr, s16 *inbuf, u32 len, s16 *outdata);
} PS_API_CONTEXT;

#define  ABS_LEN_FLAG       0x100

extern PS_API_CONTEXT *get_ps_cal_api();

#endif
