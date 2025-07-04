//=============================测试=================================
#include "rt_stream_pkg.h"
#include "system/includes.h"
#include "action.h"
#include "app_config.h"
#include "video_dec_server.h"
#include "lcd_config.h"

#ifdef WIFI_RAW_RX_DEV

#define JPEG_BUF_SIZE  200 * 1024
void wifi_raw_save_no_my_pkt_set_cb(void (*cb)(u8 *data, int len));

struct lbuf_data_head {
    int len;
    u8 data[0];
};

struct parse_info {
    u8 *data_buf;        //解析出来的数据缓存
    int data_len;
    u8 packet_type;     //解析出的数据类型(视频/音频)
    u32 old_frame_seq;  //媒体包序列
};
enum {
    VIDEO_TYPE_PACKET = 10,
    AUDIO_TYPE_PACKET,
    CONTINUE_PARSE_TYPE_PACKET,
    UNKNOW_TYPE_PACKET,
};

struct ip_frag_cache {
    u16 id;
    u16 total_len;
    u16 recv_bytes;
    u32 last_time;
    u8  finished;
    u32 src_ip;
    u32 dst_ip;
};

#define MAX_IP_PACKET_LEN 200 * 1024
static struct ip_frag_cache frag_cache;
static u8 *ip_frag_buf = NULL;


static void *lbuf_handle;

static int frame_lbuf_init(void)
{
    int buf_size = 512 * 1024;
    u8 *buf = malloc(buf_size);
    if (!buf) {
        printf("buf malloc fail \n");
        return -1;
    }

    lbuf_handle = lbuf_init(buf, buf_size, 4, sizeof(struct lbuf_data_head));
    if (!lbuf_handle) {
        printf("lbuf_init fail \n");
        return -1;
    }

    return 0;
}

//保存CPT的jpeg包
static void save_ctp_jpeg_cb(u8 *data, int len)
{
    if (len < 80) {
        return;
    }

    //帧类型 ipv4 0800
    u8 prot_type[2] = {0x08, 0x00};
    u8 *type_ptr = data + 30;
    if (memcmp(type_ptr, prot_type, sizeof(prot_type))) {
        return;
    }

    //ip header
    u8 *ip_header = data + 32;
    u8 ip_header_len = (ip_header[0] & 0x0F) * 4;
    u16 total_len = (ip_header[2] << 8) | ip_header[3];
    u16 frag_info = (ip_header[6] << 8) | ip_header[7];
    u16 frag_offset = (frag_info & 0x1FFF) * 8;
    u8 more_frag = (frag_info & 0x2000) ? 1 : 0;
    u16 ip_id = (ip_header[4] << 8) | ip_header[5];

    u32 src_ip = *(u32 *)(ip_header + 12);
    u32 dst_ip = *(u32 *)(ip_header + 16);

    u8 *ip_payload = ip_header + ip_header_len;
    u16 ip_payload_len = total_len - ip_header_len;

    // 是分片包
    if (frag_offset != 0 || more_frag) {
        if (frag_cache.id != ip_id || frag_cache.src_ip != src_ip || frag_cache.dst_ip != dst_ip) {
            memset(&frag_cache, 0, sizeof(frag_cache));
            memset(ip_frag_buf, 0x00, frag_cache.total_len);
            frag_cache.id = ip_id;
            frag_cache.src_ip = src_ip;
            frag_cache.dst_ip = dst_ip;
            frag_cache.total_len = 0;
        }

        if (frag_offset + ip_payload_len > MAX_IP_PACKET_LEN) {
            return;
        }

        memcpy(ip_frag_buf + frag_offset, ip_payload, ip_payload_len);
        frag_cache.recv_bytes += ip_payload_len;
        frag_cache.last_time = jiffies;

        if (!more_frag) {
            frag_cache.total_len = frag_offset + ip_payload_len;
            frag_cache.finished = 1;
        }

        if (!frag_cache.finished) {
            return;
        }

        // 构造完整IP payload数据
        ip_payload = ip_frag_buf;
        ip_payload_len = frag_cache.total_len;
    }


    //udp header
    /* u8 *udp_header_ptr = data + 52; */
    u8 *udp_header_ptr = ip_payload;
    u8 *dst_port_ptr = udp_header_ptr + 2;

    u8 dst_port[2] = {0x08, 0xB0};   // ctp 实时流接收端口2224
    if (memcmp(dst_port_ptr, dst_port, sizeof(dst_port))) {
        return;
    }

    //udp数据包长度
    u16 payload_len = lwip_ntohs(*(u16 *)(udp_header_ptr + 4)) - 8;
    /* memcpy(&payload_len,udp_header_ptr + 4, 2); */

    //跳过udp头部,到数据部分
    u8 *payload_ptr = udp_header_ptr + 8;

    struct frm_head *frame_head = (struct frm_head *)payload_ptr;
    if (frame_head->type & JPEG_TYPE_VIDEO) {
        if (lbuf_handle) {
            /* printf("udp payload_len:%d \n",payload_len); */
            struct lbuf_data_head *lbuf_data = lbuf_alloc(lbuf_handle, payload_len);
            if (!lbuf_data) {
                return;
            }
            lbuf_data->len = payload_len;
            memcpy(lbuf_data->data, payload_ptr, payload_len);
            lbuf_push(lbuf_data, BIT(0));
        }
    }

    memset(&frag_cache, 0, sizeof(frag_cache));
}


static int parse_recv_packet(u8 *recv_buf, int recv_len, struct parse_info *parse_info)
{
    static u32 total_payload_len = 0;
    static old_frame_cnt = 0;

    u32 position = 0;
    struct frm_head  *head_info;
    u32 frame_head_size = sizeof(struct frm_head);

    if (recv_len < frame_head_size) {
        printf(" recv_recv_len err\n");
        return -1;
    }

    do {
        head_info = (struct frm_head *)(recv_buf + position);
        /*         printf("type:%d seq:%d t:%d frame_size:%d  offset:%d payload_size:%d ", head_info->type, head_info->seq, */
        /* head_info->timestamp, head_info->frm_sz, head_info->offset, */
        /* head_info->payload_size */
        /* ); */

        if (head_info->type & JPEG_TYPE_VIDEO) {
            if (head_info->frm_sz > (JPEG_BUF_SIZE)) {
                printf("jpeg frame size too large :%d \n", head_info->frm_sz);
                return -1;
            }
            recv_len = recv_len - (frame_head_size + head_info->payload_size);
            if (recv_len < 0) {
                printf("remain recv_len err:%d \n", recv_len);
                return -1;
            }

            //如果当前的seq小于旧的seq,说明是旧的数据包,跳过不处理
            if (head_info->seq < parse_info->old_frame_seq) {
                printf("old frame \n");
                old_frame_cnt++;
                goto continue_deal;
            }

            old_frame_cnt = 0;
            //如果当前seq大于旧的seq,认为是新的数据包,组包重新初始
            if (head_info->seq > parse_info->old_frame_seq) {
                parse_info->old_frame_seq = head_info->seq;
                total_payload_len = 0;
            }

            memcpy(parse_info->data_buf + head_info->offset,
                   (recv_buf + position) + frame_head_size,
                   head_info->payload_size);

            total_payload_len += head_info->payload_size;

            //接收到完整一帧
            if (total_payload_len == head_info->frm_sz) {
                parse_info->data_len = total_payload_len;
                total_payload_len = 0;

                if (head_info->type & JPEG_TYPE_VIDEO) {
                    parse_info->packet_type =  VIDEO_TYPE_PACKET;
                } else {
                    parse_info->packet_type =  AUDIO_TYPE_PACKET;
                }
                return 0;
            }
        } else {
            printf("recv type err:%d \n", head_info->type);
            parse_info->packet_type = UNKNOW_TYPE_PACKET;
            return 0;
        }

continue_deal:
        position += (frame_head_size + head_info->payload_size);

    } while (recv_len > 0);

    if (old_frame_cnt > 10) {
        parse_info->old_frame_seq = head_info->seq;
    }

    parse_info->packet_type = CONTINUE_PARSE_TYPE_PACKET;
    return 0;
}



static void disp_jpeg_task(void *priv)
{
    printf("svae jpeg task run \n");
    int ret = 0;
    void *dec_server = NULL;
    union video_dec_req dec_req;
    char fb_name[4];
    struct parse_info parse_info = {0};
    struct frm_head  frame_head;

    parse_info.data_buf = malloc(JPEG_BUF_SIZE);
    if (!parse_info.data_buf) {
        printf("malloc parse data buf err \n");
        return;
    }

    ret = frame_lbuf_init();
    if (ret) {
        return;
    }

    struct video_dec_arg arg = {0};
    arg.dev_name = "video_dec";
    arg.video_buf_size = 512;
    dec_server = server_open("video_dec_server", &arg);
    if (!dec_server) {
        printf("open video_dec_server fail");
        return;
    }

    sprintf(fb_name, "fb2");
    dec_req.dec.fb = fb_name;
    dec_req.dec.width = LCD_W;
    dec_req.dec.height = LCD_H;


    ip_frag_buf = malloc(MAX_IP_PACKET_LEN);
    if (!ip_frag_buf) {
        printf("malloc ip_frag_buf fail \n");
        return;
    }
    wifi_raw_save_no_my_pkt_set_cb(save_ctp_jpeg_cb);

    int fps = 0;
    int start_time = timer_get_ms();

    while (1) {
        struct lbuf_data_head *lbuf_data = lbuf_pop(lbuf_handle, BIT(0));
        if (!lbuf_data) {
            os_time_dly(2);
            continue;
        }

        ret = parse_recv_packet(lbuf_data->data, lbuf_data->len, &parse_info);
        lbuf_free(lbuf_data);
        if (parse_info.packet_type == VIDEO_TYPE_PACKET) {
            fps++;
            //8字节头部
            u8 *jpeg_buf = parse_info.data_buf + 8;
            int jpeg_len = parse_info.data_len - 8;

            dec_req.dec.image.buf = jpeg_buf;
            dec_req.dec.image.size = jpeg_len;
            server_request(dec_server, VIDEO_REQ_DEC_IMAGE, &dec_req);
        }

        if (timer_get_ms() - start_time  > 1000) {
            printf("fps:%d \n", fps);
            start_time = timer_get_ms();
            fps = 0;
        }
    }
}

static void disp_demo_init(void)
{
    thread_fork(NULL, 10, 2048, 2048, NULL, disp_jpeg_task, NULL);
}

late_initcall(disp_demo_init);

#endif


