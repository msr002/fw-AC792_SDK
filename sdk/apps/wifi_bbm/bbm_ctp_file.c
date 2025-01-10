#include "system/includes.h"
#include "json_c/json.h"
#include "json_c/json_tokener.h"
#include "http/http_cli.h"
#include "baby_monitor.h"
#include "sock_api/sock_api.h"
#include "rt_stream_pkg.h"

#define HTTP_PORT               8080    //HTTP解析vs_list.txt端口
#define FILE_THUMB_PORT         2226    //缩略图数据端口
#define CTP_RECV_BUF_MAX_LEN    200 * 1024 //接收缓存,用于接收CTP包

static u32 task_name_cnt;

static int http_get_mothed(const char *url, int (*cb)(char *, void *), void *priv)
{
    int error = 0;
    http_body_obj http_body_buf;
    httpcli_ctx ctx;
    printf("profile_get_url->%s\n", url);
    memset(&http_body_buf, 0x0, sizeof(http_body_obj));
    memset(&ctx, 0x0, sizeof(httpcli_ctx));

    http_body_buf.recv_len = 0;
    http_body_buf.buf_len = 4 * 1024;
    http_body_buf.buf_count = 1;
    http_body_buf.p = (char *) malloc(http_body_buf.buf_len * sizeof(char));

    ctx.url = url;
    ctx.priv = &http_body_buf;
    ctx.connection = "close";
    ctx.timeout_millsec = 5000;
    error = httpcli_get(&ctx);
    if (error == HERROR_OK) {
        error = cb(http_body_buf.p, priv);
    } else {
        printf("http get err :%d \n", error);
        error = -1;
    }
    //关闭连接
    httpcli_close(&ctx);
    if (http_body_buf.p) {
        free(http_body_buf.p);
    }
    return error;
}

static int get_file_name_cb(char *buf, void *priv)
{
    int i;
    json_object *new_obj;
    json_object *new_obj2;
    const char *json_str;
    json_str = strstr(buf, "{\"");
    struct bbm_client_hdl *bbm_hdl = priv;

    if (!json_str) {
        printf("json buf err\n");
        return -1;
    }
    new_obj = json_tokener_parse(json_str);
    if (!new_obj) {
        printf("json_tokener_parse err\n");
        return -1;
    }

    json_object *file_list_array = json_object_object_get(new_obj, "file_list");
    if (file_list_array == NULL) {
        printf("file_list not found in JSON\n");
        json_object_put(new_obj);
        return -1;
    }

    int array_length = json_object_array_length(file_list_array);
    bbm_hdl->file_total_num = array_length;

    int list_size = bbm_hdl->file_total_num * sizeof(char *);
    bbm_hdl->file_name_list = (char **)malloc(list_size);
    if (!bbm_hdl->file_name_list) {
        printf("file_name_list malloc err \n");
        return -1;
    }
    memset(bbm_hdl->file_name_list, 0x00, list_size);

    for (i = 0; i < array_length; i++) {
        new_obj2 = json_object_array_get_idx(file_list_array, i);
        if (new_obj2 == NULL) {
            break;
        }

        const char *file_name = json_object_get_string(json_object_object_get(new_obj2, "f"));
        if (file_name == NULL) {
            printf("No 'f' field in file at index %d\n", i);
            continue;  // Skip this entry if no file name is found
        }

        bbm_hdl->file_name_list[i] = (char *)malloc(strlen(file_name) + 1);
        if (bbm_hdl->file_name_list[i] == NULL) {
            printf("malloc failed for file_list[%d]\n", i);
            json_object_put(new_obj);
            goto err;
        }
        strcpy(bbm_hdl->file_name_list[i], file_name);
    }

    json_object_put(new_obj);

    printf("total file num :%d \n", bbm_hdl->file_total_num);

    return 0;

err:
    if (bbm_hdl->file_name_list) {
        for (i = 0; i < bbm_hdl->file_total_num; i++) {
            if (bbm_hdl->file_name_list[i]) {
                free(bbm_hdl->file_name_list[i]);
                bbm_hdl->file_name_list[i] = NULL;
            }
        }
        free(bbm_hdl->file_name_list);
        bbm_hdl->file_name_list = NULL;
    }
    return -1;
}

static void ctp_get_file_task(void *priv)
{
    int ret;
    char url[100];
    u8 timeout_cnt = 0;

    struct bbm_client_hdl *bbm_hdl = priv;
    struct sockaddr_in *sockaddr = ctp_cli_get_hdl_addr(bbm_hdl->ctp_cli_hdl);
    u32 ip_addr = sockaddr->sin_addr.s_addr;

    const char topic[] = {"FORWARD_MEDIA_FILES_LIST"};
    const char content[] = {"{\"op\":\"PUT\",\"param\":{\"type\":\"1\"}}"};

    //TODO
    //SD ONLINE
    const char topic_1[] = {"SD_STATUS"};
    const char content_1[] = {"{\"op\":\"GET\"}"};

    timeout_cnt = 0;
    do {
        if (bbm_hdl->ctp_get_file_task_exit) {
            goto exit;
        }

        if (timeout_cnt > 10) {
            printf("timeout exit !\n");
            goto exit;
        }
        ret = ctp_cli_send(bbm_hdl->ctp_cli_hdl, topic, content);
        if (ret) {
            printf("ctp_cli_send :%s err\n", topic);
            timeout_cnt++;
            continue;
        }

        os_sem_set(&bbm_hdl->ctp_msg_sem, 0);
        ret = os_sem_pend(&bbm_hdl->ctp_msg_sem, 100);
        if (ret) {
            printf("ctp_msg_sem pend err:%d \n", ret);
            timeout_cnt++;
            continue;
        }

        if (!strstr(bbm_hdl->vf_list, "storage/sd")) {
            ret = -1;
            printf("vf_list format err:%s \n", bbm_hdl->vf_list);
            timeout_cnt++;
            continue;
        }

    } while (ret);

    timeout_cnt = 0;

    while (1) {

        if (bbm_hdl->ctp_get_file_task_exit) {
            goto exit;
        }

        sprintf(url, "http://%s:%d/%s", inet_ntoa(ip_addr), HTTP_PORT, bbm_hdl->vf_list);
        ret = http_get_mothed(url, get_file_name_cb, priv);
        if (ret) {
            printf("http get mothed err\n");
            timeout_cnt++;
            if (timeout_cnt > 5) {
                printf("timeout exit !\n");
                goto exit;
            }
        } else {
            printf("http get mothed success\n");
            goto exit;
        }
    }
exit:
    printf("ctp_get_file_task exit\n");
}


static void recv_ctp_file_thumb(void *sockfd, void *priv, struct net_ctp_thumb *thumb_data)
{
    int recv_len = 0;
    int file_cnt = 0;
    int buf_len = 0;
    int recv_timeout_cnt = 0;

    struct bbm_client_hdl *bbm_hdl = priv;

    // 网络包接收缓存
    u8 *recv_buf = malloc(CTP_RECV_BUF_MAX_LEN);
    if (!recv_buf) {
        printf("ctp recv malloc recv buff err \n");
        goto exit;
    }

    sock_set_recv_timeout(sockfd, 100);

    while (1) {
        if (bbm_hdl->ctp_file_thumb_task_exit) {
            goto exit;
        }

        if (recv_timeout_cnt > 5) {
            goto exit;
        }

        recv_len = sock_recvfrom(sockfd, recv_buf + buf_len, CTP_RECV_BUF_MAX_LEN - buf_len, 0, NULL, NULL);
        if (recv_len <= 0) {
            printf("thumb packet recv err \n");
            recv_timeout_cnt++;
            continue;
        }
        recv_timeout_cnt = 0;
        buf_len += recv_len;

        while (buf_len >= sizeof(struct frm_head)) {
            struct frm_head *frame_head = (struct frm_head *)recv_buf;
            // 检查是否有完整的帧
            int frame_size = sizeof(struct frm_head) + frame_head->frm_sz;
            if (buf_len < frame_size) {
                break; // 不完整帧，等待更多数据
            }
            // 处理帧数据
            char *frame_data = recv_buf + sizeof(struct frm_head);

            switch (frame_head->type) {
            case MEDIA_INFO_TYPE:
                struct media_info *media = (struct media_info *)frame_data;
                printf("media info w:%d h:%d audio_rate:%d dur_time:%d \n"
                       , media->length, media->height, media->audio_rate, media->dur_time);
                break;
            case DATE_TIME_TYPE:
                break;
            case PREVIEW_TYPE:
                printf("recv thumb cnt:%d \n", file_cnt);
                thumb_data->file_buf_len_list[file_cnt] = frame_head->frm_sz;
                memcpy(thumb_data->file_buf_list[file_cnt], frame_data, frame_head->frm_sz);
                file_cnt++;
                break;
            case PLAY_OVER_TYPE | LAST_FREG_MAKER:
                printf("recv end type \n");
                goto exit;
            default:
                printf("default frame type :%d  \n", frame_head->type);
                goto exit;
            }
            // 移动缓冲区内容，移除已处理的帧
            memmove(recv_buf, recv_buf + frame_size, buf_len - frame_size);
            buf_len -= frame_size;
        }
    }

exit:

    if (recv_buf) {
        free(recv_buf);
    }
    printf("recv ctp file thumb exit \n");

}

static void ctp_file_thumb_task(void *priv)
{
    int ret = 0;
    int i;
    int msg[8];
    struct net_ctp_thumb *thumb_data;
    struct sockaddr_in dest;
    struct bbm_client_hdl *bbm_hdl = priv;
    void *ctp_file_thumb_sockfd;

    struct sockaddr_in *sockaddr = ctp_cli_get_hdl_addr(bbm_hdl->ctp_cli_hdl);
    u32 ip_addr = sockaddr->sin_addr.s_addr;

    char topic_1[] = "MULTI_COVER_FIGURE";
    char content_1[512];
    char temp_buf[128];

    while (1) {
        ret = os_task_pend("taskq", msg, ARRAY_SIZE(msg));
        switch (ret) {
        case OS_TASKQ:
            switch (msg[0]) {
            case Q_MSG:
                thumb_data = (struct net_ctp_thumb *)msg[1];
                break;
            case Q_USER:
                //exit
                goto exit;
            }
            break;
        default:
            break;
        }

        memset(content_1, 0x00, sizeof(content_1));
        strcat(content_1, "{\"op\":\"PUT\",\"param\":{");
        for (i = 0; i <  thumb_data->file_num; i++) {
            sprintf(temp_buf, "\"path_%d\":\"%s\",", i, bbm_hdl->file_name_list[thumb_data->start_index + i]);
            strcat(content_1, temp_buf);
        }
        //去除,
        char *ptr = strrchr(content_1, ',');
        *ptr = '\0';
        strcat(content_1, "}}");
        printf("content: %s\n", content_1);

        ret = ctp_cli_send(bbm_hdl->ctp_cli_hdl, topic_1, content_1);
        if (ret) {
            printf("ctp_cli_send :%s err\n", topic_1);
            continue;
        }

        ctp_file_thumb_sockfd = sock_reg(AF_INET, SOCK_STREAM, 0, NULL, NULL);
        if (ctp_file_thumb_sockfd  == NULL) {
            printf("ctp file thumb sock_reg err\n");
            continue;
        }
        dest.sin_family = AF_INET;
        dest.sin_addr.s_addr = ip_addr;
        dest.sin_port = htons(FILE_THUMB_PORT);
        sock_set_connect_to(ctp_file_thumb_sockfd, 1);
        if (0 != sock_connect(ctp_file_thumb_sockfd, (struct sockaddr *)&dest, sizeof(struct sockaddr_in))) {
            printf("sock_connect fail.\n");
            os_sem_post(&thumb_data->sem);
            sock_unreg(ctp_file_thumb_sockfd);
            continue;
        }

        recv_ctp_file_thumb(ctp_file_thumb_sockfd, priv, thumb_data);
        os_sem_post(&thumb_data->sem);

        sock_unreg(ctp_file_thumb_sockfd);
    }
exit:
    printf("ctp file thumb task exit \n");
}


int ctp_file_thumb_start(void *priv)
{
    struct bbm_client_hdl *bbm_hdl = priv;
    sprintf(bbm_hdl->ctp_file_thumb_task_name, "file_thumb_task%d", task_name_cnt++);

    return thread_fork(bbm_hdl->ctp_file_thumb_task_name, 12, 2048, 2048,
                       &bbm_hdl->ctp_file_thumb_task_pid, ctp_file_thumb_task, priv);
}

int ctp_file_thumb_stop(void *priv)
{
    int msg = 1;
    struct bbm_client_hdl *bbm_hdl = priv;

    if (bbm_hdl->ctp_file_thumb_task_pid) {
        bbm_hdl->ctp_file_thumb_task_exit = 1;
        os_taskq_del_type(bbm_hdl->ctp_file_thumb_task_name, Q_MSG);
        os_taskq_post_type(bbm_hdl->ctp_file_thumb_task_name, Q_USER, 1, &msg);
        thread_kill(&bbm_hdl->ctp_file_thumb_task_pid, KILL_WAIT);
        bbm_hdl->ctp_file_thumb_task_pid = 0;
        bbm_hdl->ctp_file_thumb_task_exit = 0;
    }

    return 0;
}

int bbm_ctp_get_file_thumb(void *priv, struct net_ctp_thumb *thumb_data)
{
    int ret;
    int msg = thumb_data;
    struct bbm_client_hdl *bbm_hdl = priv;

    ret = os_taskq_post_type(bbm_hdl->ctp_file_thumb_task_name, Q_MSG, 1, &msg);
    if (ret) {
        printf("thumb post taskq err:%d \n", ret);
        return ret;
    }

    return 0;
}

int bbm_ctp_file_init(void *priv)
{
    struct bbm_client_hdl *bbm_hdl = priv;

    return thread_fork(NULL, 10, 2048, 2048
                       , &bbm_hdl->ctp_get_file_task_pid, ctp_get_file_task, priv);
}

int bbm_ctp_file_exit(void *priv)
{
    int i;
    struct bbm_client_hdl *bbm_hdl = priv;

    if (bbm_hdl->ctp_get_file_task_pid) {
        bbm_hdl->ctp_get_file_task_exit = 1;
        thread_kill(&bbm_hdl->ctp_get_file_task_pid, KILL_WAIT);
        bbm_hdl->ctp_get_file_task_pid = 0;
        bbm_hdl->ctp_get_file_task_exit = 0;
    }

    if (bbm_hdl->file_name_list) {
        for (i = 0; i < bbm_hdl->file_total_num; i++) {
            if (bbm_hdl->file_name_list[i]) {
                free(bbm_hdl->file_name_list[i]);
                bbm_hdl->file_name_list[i] = NULL;
            }
        }
        free(bbm_hdl->file_name_list);
        bbm_hdl->file_name_list = NULL;
    }
}


