#ifndef __PLUGIN_BUFFER_H
#define __PLUGIN_BUFFER_H

#include "pipeline_memory.h"
#include "generic/list.h"
#include "videobuf.h"

#define MAX_BUFFER_NAME_LEN (16)

#define LBUF_RESERVE_LEN (256)

typedef enum {
    GENERAL_BUFFER = 0x0,
    FAST_BUFFER,
    QUEUE_BUFFER,
    EXTERN_BUFFER,
} buffer_type;

typedef struct {
    uint32_t id;
    uint32_t format;
    uint16_t width;
    uint16_t height;
    uint16_t line;
    uint16_t block_num;

} video_buffer_meta;

typedef struct {
    size_t     samples;
    int32_t    format;
    int32_t    channel;

} audio_buffer_meta;

typedef union {
    video_buffer_meta vmeta;
    audio_buffer_meta ameta;
} meta_t;

#define PIPELINE_BUFFER_FRAME_RESET     (0x1)

typedef struct {
    meta_t meta;
    int64_t dts;
    int64_t pts;
    int     flag;
    uint8_t *ext_data;
    uint32_t data_len;
    uint8_t data[0];
} buffer_meta_t;

typedef struct _buffer_t buffer_t;
struct buffer_api {
    void *private_data;
    buffer_meta_t *(*get_write_addr)(buffer_t *buffer, size_t size);
    int (*update_data)(buffer_t *buffer, buffer_meta_t *);
    int (*get_free_size)(buffer_t *buffer);
    buffer_meta_t *(*read_data)(buffer_t *buffer, int no_wait);
    int (*free_read_data)(buffer_t *buffer, buffer_meta_t *);
    buffer_meta_t *(*realloc_addr)(buffer_t *buffer, buffer_meta_t *m, size_t size);
};

typedef struct _buffer_t {
    int magic;
    buffer_type type;

    //private:
    struct list_head entry;
    int ref;
    char name[MAX_BUFFER_NAME_LEN];
    memory mem;
    OS_SEM sem;
    int sem_timeout;
    u8 memory_is_ok;

    struct lbuff_head *lbuf;
    buffer_meta_t *meta_addr;

    //func:
    void *private_data;
    buffer_meta_t *(*get_write_addr)(buffer_t *buffer, size_t size);
    int (*update_data)(buffer_t *buffer, buffer_meta_t *);
    int (*get_free_size)(buffer_t *buffer);
    buffer_meta_t *(*read_data)(buffer_t *buffer, int no_wait);
    int (*free_read_data)(buffer_t *buffer, buffer_meta_t *);
    buffer_meta_t *(*realloc_addr)(buffer_t *buffer, buffer_meta_t *m, size_t size);
} buffer_t;

void *buffer_get_memory_address(buffer_t *buffer);
u32 buffer_get_memory_size(buffer_t *buffer);
int buffer_check_vaild(buffer_t *buffer);

#endif
