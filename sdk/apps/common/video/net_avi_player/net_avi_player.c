#include "audio_def.h"
#include "avi_parse.h"
#include "curl_get_data.h"
#include "net_avi_player.h"

#define NET_BUFFER_SIZE  (512 * 1024)
#define AUDIO_BUFFER_SIZE (256 * 1024)
#define VIDEO_BUFFER_SIZE (512 * 1024)

struct net_avi_player {
    void *net_session;
    struct avi_player *player;
    struct avi_frame_queue frame_queue;
    struct avi_parser_result avi_parser_result;
    struct avi_info avi_info;

    int get_data_task_pid;
    int get_data_task_exit;
};

static void avi_get_data_task(void *priv);
static int queue_init(struct avi_frame_queue *frame_queue, int video_buf_size, int audio_buf_size);
static void queue_deinit(struct avi_frame_queue *frame_queue);


void *net_avi_play_start(const char *url, avi_player_event_callback_t event_callback, void *event_priv)
{
    int ret;
    struct net_avi_player *net_player = malloc(sizeof(struct net_avi_player));
    if (!net_player) {
        printf("malloc net_player fail\n");
        return NULL;
    }
    memset(net_player, 0, sizeof(struct net_avi_player));

    net_player->net_session = curl_session_create(url);
    if (!net_player->net_session) {
        printf("curl_session_create fail\n");
        goto exit;
    }
    ret = curl_session_init(net_player->net_session);
    if (ret != 0) {
        printf("curl_session_init fail %d\n", ret);
        goto exit;
    }

    // 解析AVI头部
    if (net_avi_parse_header(net_player) != 0) {
        printf("net_avi_parse_header fail\n");
        goto exit;
    }
    avi_parser_result_dump(&net_player->avi_parser_result);

    if (!net_player->avi_parser_result.has_audio && !net_player->avi_parser_result.has_video) {
        printf("no audio and video stream\n");
        goto exit;
    }
    // 转换为avi_info
    net_player->avi_info.width = net_player->avi_parser_result.width;
    net_player->avi_info.height = net_player->avi_parser_result.height;
    net_player->avi_info.fps = net_player->avi_parser_result.fps;
    net_player->avi_info.audio_coding_type = AUDIO_CODING_PCM;
    net_player->avi_info.audio_channels = net_player->avi_parser_result.audio_channels;
    net_player->avi_info.audio_sample_rate = net_player->avi_parser_result.audio_sample_rate;
    net_player->avi_info.has_audio = net_player->avi_parser_result.has_audio;
    net_player->avi_info.has_video = net_player->avi_parser_result.has_video;
    net_player->avi_info.total_time_ms = (net_player->avi_parser_result.total_frames * 1000) / net_player->avi_info.fps;

    int video_buf_size = VIDEO_BUFFER_SIZE;
    int audio_buf_size = AUDIO_BUFFER_SIZE;
    ret = queue_init(&net_player->frame_queue, video_buf_size, audio_buf_size);
    if (ret != 0) {
        printf("queue_init fail %d\n", ret);
        goto exit;
    }

    net_player->player = avi_player_init(&net_player->avi_info,
                                         &net_player->frame_queue, event_callback, event_priv);
    if (!net_player->player) {
        printf("avi_player_init fail\n");
        goto exit;
    }

    ret = thread_fork("get_avi_data_task", 20, 2048, 2048,
                      &net_player->get_data_task_pid,
                      avi_get_data_task, net_player);
    if (ret != 0) {
        printf("get_avi_data_task thread fork fail %d\n", ret);
        goto exit;
    }


    return net_player;

exit:
    net_avi_play_stop(net_player);
    return NULL;
}

int net_avi_play_get_info(void *_net_player, struct avi_info *info)
{
    if (!_net_player || !info) {
        return -1;
    }
    struct net_avi_player *net_player = (struct net_avi_player *)_net_player;
    if (net_player->player) {
        memcpy(info, &net_player->avi_info, sizeof(struct avi_info));
        return 0;
    }
    return -1;
}

int net_avi_play_get_total_time_ms(void *_net_player)
{
    if (!_net_player) {
        return 0;
    }

    struct net_avi_player *net_player = (struct net_avi_player *)_net_player;
    if (net_player->player) {
        u32 total_frames = net_player->avi_parser_result.total_frames;
        int fps = net_player->avi_info.fps;
        if (fps > 0) {
            return (total_frames * 1000) / fps;
        }
    }

    return 0;
}

int net_avi_play_pause_resume(void *_net_player, int pause)
{
    if (!_net_player) {
        return -1;
    }
    struct net_avi_player *net_player = (struct net_avi_player *)_net_player;
    if (net_player->player) {
        avi_player_control(net_player->player, pause ? AVI_PLAYER_CMD_PAUSE : AVI_PLAYER_CMD_PLAY, 0);
    }
    return 0;
}

void net_avi_play_stop(void *_net_player)
{
    if (!_net_player) {
        return;
    }
    struct net_avi_player *net_player = (struct net_avi_player *)_net_player;

    if (net_player->get_data_task_pid) {
        net_player->get_data_task_exit = 1;
        thread_kill(&net_player->get_data_task_pid, KILL_WAIT);
        net_player->get_data_task_exit = 0;
    }

    if (net_player->player) {
        avi_player_exit(net_player->player);
    }
    if (net_player->net_session) {
        curl_session_destroy(net_player->net_session);
    }
    queue_deinit(&net_player->frame_queue);
    free(net_player);
}

static void avi_get_data_task(void *priv)
{
    struct net_avi_player *net_player = (struct net_avi_player *)priv;
    printf("avi video play task started\n");
    char index_chunk_id[5] = {'i', 'd', 'x', '1', '\0'};
    int buffer_size = NET_BUFFER_SIZE;
    u8 *buffer = malloc(buffer_size);
    if (!buffer) {
        printf("avi video play task malloc buffer fail\n");
        return;
    }
    u32 buffer_offset = 0;

    //从movi开始读取数据
    u32 offset = net_player->avi_parser_result.movi_offset;
    printf("start read from offset=%d\n", offset);

    if (curl_session_seek(net_player->net_session, offset) != 0) {
        printf("curl_session_seek fail\n");
        free(buffer);
        return;
    }

    while (!net_player->get_data_task_exit) {
        u32 received = 0;
        int ret = curl_session_read(net_player->net_session,
                                    buffer + buffer_offset, buffer_size - buffer_offset, &received);
        if (ret != 0 || received == 0) {
            printf("curl_session_read_at fail %d\n", ret);
            break;
        }
        received += buffer_offset;

        //解析数据
        u32 processed = 0;
        while (processed + 8 < received) {
            //printf("processed=%d, received=%d\n", processed, received);

            char *video_chunk_id = net_player->avi_parser_result.video_chunk_id;
            char *audio_chunk_id = net_player->avi_parser_result.audio_chunk_id;
            u32 chunk_id;
            u32 chunk_size;
            memcpy(&chunk_id, buffer + processed, 4);
            memcpy(&chunk_size, buffer + processed + 4, 4);

            //printf("chunk_id=0x%08x, chunk_size=%d\n", chunk_id, chunk_size);

            if (chunk_id == *(u32 *)video_chunk_id) {
                //printf("video chunk_id:%s , chunk_size=%d\n", video_chunk_id, chunk_size);
                //视频帧
                u32 total_size = 8 + chunk_size;
                if (processed + total_size <= received) {
                    //完整帧
                    struct avi_frame_lbuf_node *video_node = NULL;
                    while (!video_node && !net_player->get_data_task_exit) {
                        video_node = lbuf_alloc(net_player->frame_queue.video_lbuf_handle, chunk_size);
                        if (!video_node) {
                            os_time_dly(2);
                        }
                    }
                    if (video_node) {
                        video_node->len = chunk_size;
                        memcpy(video_node->data, buffer + processed + 8, chunk_size);
                        lbuf_push(video_node, BIT(0));
                        processed += total_size;
                    }
                } else {
                    //不完整帧，等待下次读取
                    break;
                }
            } else if (chunk_id == *(u32 *)audio_chunk_id) {
                //printf("audio chunk_id:%s , chunk_size=%d\n", audio_chunk_id, chunk_size);
                //音频数据
                u32 total_size = 8 + chunk_size;
                if (processed + total_size <= received) {
                    //完整音频数据
                    struct avi_frame_lbuf_node *audio_node = NULL;
                    while (!audio_node && !net_player->get_data_task_exit) {
                        audio_node = lbuf_alloc(net_player->frame_queue.audio_lbuf_handle, chunk_size);
                        if (!audio_node) {
                            os_time_dly(2);
                        }
                    }
                    if (audio_node) {
                        audio_node->len = chunk_size;
                        memcpy(audio_node->data, buffer + processed + 8, chunk_size);
                        lbuf_push(audio_node, BIT(0));
                        processed += total_size;
                    }
                } else {
                    //不完整数据，等待下次读取
                    break;
                }
            } else if (chunk_id == *(u32 *)index_chunk_id) {
                printf("index chunk_id:%s , chunk_size=%d\n", index_chunk_id, chunk_size);
                //退出
                net_player->get_data_task_exit = 1;
                break;
            } else {
                //printf("unknown chunk_id=0x%08x , chunk_size=%d\n", chunk_id, chunk_size);
                //未知chunk，跳过
                processed++;
            }

        }
        //未处理完的数据，移动到buffer起始位置
        if (processed < received) {
            //printf("move remain data, processed=%d, received=%d\n", processed, received);
            u32 remain = received - processed;
            memmove(buffer, buffer + processed, remain);
            buffer_offset = remain;
        } else {
            //printf("all data processed\n");
            buffer_offset = 0;
        }

    }
    if (buffer) {
        free(buffer);
    }
    printf("avi video play task exiting\n");
}

static int net_avi_parse_header(struct net_avi_player *net_player)
{
    int ret = 0;
    u8 *head_buf;
    u32 head_buf_size;
    struct avi_parser_result result;

    head_buf_size = 64 * 1024;
    head_buf = malloc(head_buf_size);
    if (!head_buf) {
        printf("malloc head_buf fail\n");
        return -1;
    }

    u32 received;
    ret = curl_session_read_at(net_player->net_session, 0, head_buf, head_buf_size, &received);
    if (ret != 0) {
        printf("curl_session_read_at fail %d\n", ret);
        free(head_buf);
        return -1;
    }

    ret = avi_parse_header(head_buf, received, &result);
    if (ret != 0) {
        printf("avi_parse_header fail %d\n", ret);
        free(head_buf);
        return -1;
    }

    free(head_buf);

    memcpy(&net_player->avi_parser_result, &result, sizeof(struct avi_parser_result));

    return 0;
}


static int queue_init(struct avi_frame_queue *frame_queue, int video_buf_size, int audio_buf_size)
{
    frame_queue->video_buf_size = video_buf_size;
    frame_queue->video_buf_ptr = malloc(frame_queue->video_buf_size);
    if (!frame_queue->video_buf_ptr) {
        printf("video_buf_ptr malloc fail\n");
        return -1;
    }
    frame_queue->audio_buf_size = audio_buf_size;
    frame_queue->audio_buf_ptr = malloc(frame_queue->audio_buf_size);
    if (!frame_queue->audio_buf_ptr) {
        printf("audio_buf_ptr malloc fail\n");
        free(frame_queue->video_buf_ptr);
        return -1;
    }

    frame_queue->video_lbuf_handle = lbuf_init(frame_queue->video_buf_ptr,
                                     frame_queue->video_buf_size,
                                     8, sizeof(struct avi_frame_lbuf_node));
    if (!frame_queue->video_lbuf_handle) {
        printf("avi video lbuf handle init err \n");
        return -1;
    }

    frame_queue->audio_lbuf_handle = lbuf_init(frame_queue->audio_buf_ptr,
                                     frame_queue->audio_buf_size,
                                     8, sizeof(struct avi_frame_lbuf_node));
    if (!frame_queue->audio_lbuf_handle) {
        printf("avi audio lbuf handle init err \n");
        return -1;
    }

    return 0;
}

static void queue_deinit(struct avi_frame_queue *frame_queue)
{
    if (frame_queue->video_lbuf_handle) {
        free(frame_queue->video_buf_ptr);
        frame_queue->video_lbuf_handle = NULL;
    }
    if (frame_queue->audio_lbuf_handle) {
        free(frame_queue->audio_buf_ptr);
        frame_queue->audio_lbuf_handle = NULL;
    }
}
