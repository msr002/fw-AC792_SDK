#ifndef VIDEO_STREAM_REQUEST_H
#define VIDEO_STREAM_REQUEST_H
#include "system/includes.h"
#include "video_stream_common.h"

int video_stream_open_request(void *ctp_client_hdl, struct video_stream_info *stream, int device_num, u32 ip_addr);


#endif // VIDEO_STREAM_REQUEST_H

