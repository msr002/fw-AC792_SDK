#include "ctp_client.h"
#include "json_c/json.h"
#include "json_c/json_tokener.h"
#include "video_stream_request.h"

#define LOG_TAG_CONST       VIDEO_STREAM_REQUEST
#define LOG_TAG             "[VIDEO_STREAM_REQUEST]"
#define LOG_ERROR_ENABLE
#define LOG_INFO_ENABLE
#define LOG_DUMP_ENABLE
#include "debug.h"

int video_stream_open_request(void *ctp_client_hdl, struct video_stream_info *stream, int device_num, u32 ip_addr)
{
    int err = 0;
    void *client_hdl = ctp_client_hdl;
    char *topic = "OPEN_VIDEO_CALL";
    char *content = malloc(1024);
    int timeout_ms = 3 * 1000;

    if (!stream || !content) {
        log_error("video stream ptr or content ptr null \n");
        return -1;
    }

    snprintf(content, 1024,
             "{\"op\":\"PUT\",\"param\":{\"img_width\":%d,\"img_height\":%d,\"fps\":%d,"
             "\"bitrate_kbps\":%d,\"online\":%d,\"device_id\":%d,\"osd_enable\":%d,"
             "\"audio_enable\":%d,\"sample_rate\":%d,\"channel\":%d,\"volume\":%d,"
             "\"aud_interval_size\":%d,\"device_num\":%d}}",
             stream->img_width,
             stream->img_height,
             stream->fps,
             stream->bitrate_kbps,
             stream->online,
             stream->device_id,
             stream->osd_enable,
             stream->audio_enable,
             stream->sample_rate,
             stream->channel,
             stream->volume,
             stream->aud_interval_size,
             device_num
            );
    log_debug("request content:%s \n", content);

    //如果传入的ctp_client_hdl为空，则创建一个临时的ctp客户端句柄,用于发送请求，发送完成后销毁该句柄
    if (!client_hdl) {
        err = ctp_client_init(&client_hdl, ip_addr, NULL);
        if (err != 0) {
            log_error("ctp client init err \n");
            return -1;
        }
        err = ctp_client_send_sync(client_hdl, topic, content, timeout_ms);
        if (err != 0) {
            log_error("ctp client send open video stream err \n");
            ctp_client_exit(client_hdl);
            return -1;
        }
        ctp_client_exit(client_hdl);
    } else {
        err = ctp_client_send_sync(client_hdl, topic, content, timeout_ms);
        if (err != 0) {
            log_error("ctp client send open video stream err \n");
            return -1;
        }
    }

    return 0;
}
