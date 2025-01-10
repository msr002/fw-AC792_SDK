#include "server/ctp_server.h"
#include "server/net_server.h"
#include "json_c/json.h"
#include "json_c/json_tokener.h"
#include "server/server_core.h"
#include "system/app_core.h"
#include "action.h"
#include "storage_device.h"
#include "app_config.h"
#include "fs/fs.h"
#include "app_database.h"
#include "http/http_server.h"
#include "ctp.h"
#include "cdp.h"
#include "os/os_api.h"
#include "action.h"
#include "wifi/wifi_connect.h"
#include "event/key_event.h"
#include "asm/includes.h"
#include "baby_monitor.h"

#define CTP_CMD_HEADER "{\"errno\":%d,\"op\":\"%s\",\"param\":{"
#define CTP_CMD_HEADER_WITHOUT_ERR "{\"op\":\"%s\",\"param\":{"
#define CTP_CMD_END "}}"
#define CTP_ERR_MESSAGE "{\"errno\":%d}"

#define VFLIST_FILE_NAME "vf_list.txt"

static struct ctp_arg info;

int send_ctp_string(int cmd_type, char *buf, const char *_req, void *priv)
{
    struct ctp_req req;
    struct server *ctp = NULL;

    ctp = get_ctp_server_hander();
    if (ctp == NULL) {
        return -1;
    }

    req.parm = buf;
    req.topic = _req;
    req.cli = priv;
    if (!priv) {
        req.cli = info.cli;
    }
    printf("buf:%s ", buf);
    if (server_request(ctp, cmd_type, (void *)&req)) {
        return -1;
    }

    return 0;
}

static inline int _CTP_CMD_COMBINED(int cmd_type, void *priv, u32 err, const char *_req, const char *mothod, char *str)
{
    char *buf = NULL;
    int ret;
    int id = 0;
    char tmp[64];
    char *tmp1 = NULL;
    buf = (char *)malloc(512);

    if (buf == NULL) {
        printf("%s %d mem is fail \n", __func__, __LINE__);
        return -1;
    }

    if (err) {
        ret = snprintf(buf, 512, CTP_CMD_HEADER, err, mothod);
    } else {
        ret = snprintf(buf, 512, CTP_CMD_HEADER_WITHOUT_ERR, mothod);
    }

    char *key;
    char *value;

    if (!err && str != NULL) {
        while (1) {
            key = strtok_r(str, ":", &tmp1); //这函数会改数组，不能用const
            value = strtok_r(NULL, ",", &tmp1);

            if (key == NULL || value == NULL) {
                break;
            }

            ret = sprintf(tmp, "\"%s\":\"%s\",", key, value);
            tmp[ret] = '\0';
            ret = snprintf(buf, 512, "%s%s", buf, tmp);
            str = NULL;
        }

        buf[ret - 1] = '\0';//主要是去掉最后的逗号
        ret = snprintf(buf, 512, "%s%s", buf, CTP_CMD_END);
    } else {
        snprintf(buf, 512, "{\"op\":\"NOTIFY\",\"errno\":%d,\"param\":{%s}}", err, str);
    }

//打开ctp_server
//
    void *cli = NULL;
    if (!strcmp(_req, info.topic) || !priv) {
        cli = info.cli;
    } else {
        cli = priv;
    }


    if (send_ctp_string(cmd_type, buf, _req, cli) < 0) {
        free(buf);
        return -1;
    }
    return 0;
}

int CTP_CMD_COMBINED(void *priv, u32 err, const char *_req, const char *mothod, char *str)
{
    return _CTP_CMD_COMBINED(CTP_NOTIFY_COMMAND, priv, err, _req, mothod, str);
}

int ctp_cmd_analysis(const char *topic, char *content, void *priv)
{
    struct ctp_map_entry *map = NULL;
    char buf[128];
    struct intent it;
    int ret = -1;

    if (strlen(topic) <= 0 || strlen(content) <= 0) {
        printf("%s  %d err....\n", __func__, __LINE__);
        return -1;
    }

    strcpy(info.topic, topic);
    info.content = NULL;
    info.cli = priv;

    list_for_ctp_mapping_tab(map) {
        if (!strcmp(topic, map->ctp_command)) {
            if (strstr(content, "PUT") && map->put != NULL) {
                if (map->sync != true) {
                    map->sync = true;  //防止APP多次发送重发命令
                    ret =  map->put(priv, content);
                } else {
                    printf("Warnning CTP<%s> is doing now\n", map->ctp_command);
                    ret = 0;
                }
            } else if (strstr(content, "GET") && map->get != NULL) {
                if (map->sync != true) {
                    map->sync = true;
                    ret = map->get(priv, content);
                } else {
                    printf("Warnning CTP<%s> is doing now\n", map->ctp_command);
                    ret = 0;
                }
            } else {
                puts("content is error \n\n");
            }

        }

        if (ret != -1) {
            return ret;
        }
    }

    CTP_CMD_COMBINED(priv, CTP_NO_TOPIC, topic, "NOTIFY", CTP_NO_TOPIC_MSG);
    printf("%s %d topic:%s not find it or cb is NULL\n", __func__, __LINE__, topic);
    return -1;

}

int cmd_put_open_rt_stream(void *priv, char *content)
{
    json_object *new_obj = NULL;
    json_object *parm = NULL;

    const char *h, *w, *fps, *abr, *id, *sub_id;
    struct sockaddr_in *addr;
    struct video_rec_config config = {0};
    char net_path[64];
    int ret;

    new_obj = json_tokener_parse(content);
    parm =  json_object_object_get(new_obj, "param");

    h = json_object_get_string(json_object_object_get(parm, "h"));
    w = json_object_get_string(json_object_object_get(parm, "w"));
    abr = json_object_get_string(json_object_object_get(parm, "abr"));
    fps = json_object_get_string(json_object_object_get(parm, "fps"));
    id = json_object_get_string(json_object_object_get(parm, "id"));
    sub_id = json_object_get_string(json_object_object_get(parm, "sub_id"));
    addr = ctp_srv_get_cli_addr(priv);
    sprintf(net_path, "udp://%s:%d", inet_ntoa(addr->sin_addr.s_addr)
            , _FORWARD_PORT);

    config.net_path    = net_path;
    config.width       = atoi(w);
    config.height      = atoi(h);
    config.fps         = atoi(fps);
    config.abr_kbps    = atoi(abr);
    config.id          = atoi(id);
    config.sub_id      = atoi(sub_id);


    struct intent it;
    init_intent(&it);
    it.name = "video_rec";
    it.action = ACTION_VIDEO_START;
    it.exdata = &config;
    ret = start_app(&it);

    if (ret) {
        CTP_CMD_COMBINED(NULL, CTP_RT_OPEN_FAIL, "OPEN_RT_STREAM", "NOTIFY", CTP_RT_OPEN_FAIL_MSG);
    } else {
        char buf[128];
        sprintf(buf, "w:%d h:%d fps:%d abr:%d", config.width, config.height, config.fps, config.abr_kbps);
        CTP_CMD_COMBINED(NULL, CTP_NO_ERR, "OPEN_RT_STREAM", "NOTIFY", buf);
    }

    json_object_put(new_obj);

    return 0;
}

static int cmd_put_close_rt_stream(void *priv, char *content)
{
    json_object *new_obj = NULL;
    json_object *parm = NULL;
    const char *id, *sub_id;
    struct video_rec_config config = {0};

    new_obj = json_tokener_parse(content);
    parm =  json_object_object_get(new_obj, "param");

    id = json_object_get_string(json_object_object_get(parm, "id"));
    sub_id = json_object_get_string(json_object_object_get(parm, "sub_id"));

    config.id          = atoi(id);
    config.sub_id      = atoi(sub_id);

    struct intent it;
    init_intent(&it);
    it.name = "video_rec";
    it.action = ACTION_VIDEO_STOP;
    it.exdata = &config;
    start_app(&it);

    CTP_CMD_COMBINED(NULL, CTP_NO_ERR, "CLOSE_RT_STREAM", "NOTIFY", NULL);

    json_object_put(new_obj);

    return 0;
}

//TODO
int cmd_put_open_rec(void *priv, char *content)
{
    json_object *new_obj = NULL;
    json_object *parm = NULL;

    const char *h, *w, *fps, *id, *sub_id, *abr, *cycle_time;
    struct video_rec_config config = {0};
    int ret;

    new_obj = json_tokener_parse(content);
    parm =  json_object_object_get(new_obj, "param");

    h = json_object_get_string(json_object_object_get(parm, "h"));
    w = json_object_get_string(json_object_object_get(parm, "w"));
    fps = json_object_get_string(json_object_object_get(parm, "fps"));
    abr = json_object_get_string(json_object_object_get(parm, "abr"));
    id = json_object_get_string(json_object_object_get(parm, "id"));
    sub_id = json_object_get_string(json_object_object_get(parm, "sub_id"));
    cycle_time = json_object_get_string(json_object_object_get(parm, "cycle_time"));

    config.width       = atoi(w);
    config.height      = atoi(h);
    config.fps         = atoi(fps);
    config.id          = atoi(id);
    config.sub_id      = atoi(sub_id);
    config.cycle_time  = atoi(cycle_time);
    config.abr_kbps    = atoi(abr);

    struct intent it;
    init_intent(&it);
    it.name = "video_rec";
    it.action = ACTION_VIDEO_START;
    it.exdata = &config;
    ret = start_app(&it);

    if (ret) {
        CTP_CMD_COMBINED(NULL, CTP_REC_OPEN_FAIL, "OPEN_REC", "NOTIFY", CTP_REC_OPEN_FAIL_MSG);
    } else {
        char buf[128];
        sprintf(buf, "w:%d h:%d fps:%d abr:%d", config.width, config.height, config.fps, config.abr_kbps);
        CTP_CMD_COMBINED(NULL, CTP_NO_ERR, "OPEN_REC", "NOTIFY", buf);
    }

    json_object_put(new_obj);

    return 0;
}

static int cmd_put_close_rec(void *priv, char *content)
{
    json_object *new_obj = NULL;
    json_object *parm = NULL;
    const char *id, *sub_id;
    struct video_rec_config config = {0};

    new_obj = json_tokener_parse(content);
    parm =  json_object_object_get(new_obj, "param");

    id = json_object_get_string(json_object_object_get(parm, "id"));
    sub_id = json_object_get_string(json_object_object_get(parm, "sub_id"));

    config.id          = atoi(id);
    config.sub_id      = atoi(sub_id);

    struct intent it;
    init_intent(&it);
    it.name = "video_rec";
    it.action = ACTION_VIDEO_STOP;
    it.exdata = &config;
    start_app(&it);

    CTP_CMD_COMBINED(NULL, CTP_NO_ERR, "CLOSE_REC", "NOTIFY", NULL);

    json_object_put(new_obj);

    return 0;
}

static int cmd_put_make_forward_files_list(void *priv, char *content)
{
    char buf[128];
    char path[64];
    json_object *new_obj = NULL;
    json_object *parm = NULL;
    json_object *tmp = NULL;
    char type = 0;
    u32 file_num = 0;
    new_obj = json_tokener_parse(content);
    parm =  json_object_object_get(new_obj, "param");
    tmp =  json_object_object_get(parm, "type");

    const char *tmp_value = json_object_get_string(tmp);

    tmp =  json_object_object_get(parm, "num");
    if (tmp != NULL) {
        const char *num = json_object_get_string(tmp);
        if (num != NULL && atoi(num) != 0) {
            file_num = atoi(num);
        }
    }
    if (tmp_value == NULL) {
        type = VID_JPG;
    } else {
        type = atoi(tmp_value);
    }
    switch (type) {
    case -1 :
        CTP_CMD_COMBINED(priv, CTP_SD_OFFLINE, "FORWARD_MEDIA_FILES_LIST", "NOTIFY", CTP_SD_OFFLINE_MSG);
        break;
    case NONE:
        /*snprintf(buf, sizeof(buf), "type:0,path:%s", CONFIG_REC_PATH_1"vf_list.txt");*/
        snprintf(buf, sizeof(buf), "type:0,path:%s", CONFIG_REC_PATH_0"vf_list.txt");
        CTP_CMD_COMBINED(priv, CTP_NO_ERR, "FORWARD_MEDIA_FILES_LIST", "NOTIFY", buf);
        break;
    case VID_JPG:

        if (!file_num) {

#if defined CONFIG_ENABLE_VLIST
            if (!FILE_INITIND_CHECK()) {
                FILE_GEN();
                /*snprintf(buf, sizeof(buf), "type:1,path:%s", CONFIG_REC_PATH_1"vf_list.txt");*/
                snprintf(buf, sizeof(buf), "type:1,path:%s", CONFIG_REC_PATH_0"vf_list.txt");
                CTP_CMD_COMBINED(priv, CTP_NO_ERR, "FORWARD_MEDIA_FILES_LIST", "NOTIFY", buf);

            } else {
                CTP_CMD_COMBINED(priv, CTP_REQUEST, "FORWARD_MEDIA_FILES_LIST", "NOTIFY", CTP_REQUEST_MSG);
            }
        } else {
            FILE_LIST_INIT_SMALL(file_num);
            /*snprintf(buf, sizeof(buf), "type:1,path:%s", CONFIG_REC_PATH_1"vf_list_small.txt");*/
            snprintf(buf, sizeof(buf), "type:1,path:%s", CONFIG_REC_PATH_0"vf_list_small.txt");
            CTP_CMD_COMBINED(priv, CTP_NO_ERR, "FORWARD_MEDIA_FILES_LIST", "NOTIFY", buf);
#endif
        }
        break;
    case VIDEO:
        vf_list(type, 1, path);
        snprintf(buf, sizeof(buf), "type:2,path:%s", path);
        CTP_CMD_COMBINED(priv, CTP_NO_ERR, "FORWARD_MEDIA_FILES_LIST", "NOTIFY", buf);
        break;
    case JPG:
        vf_list(type, 1, path);
        snprintf(buf, sizeof(buf), "type:3,path:%s", path);
        CTP_CMD_COMBINED(priv, CTP_NO_ERR, "FORWARD_MEDIA_FILES_LIST", "NOTIFY", buf);
        break;
    default:
        break;
    }


    json_object_put(new_obj);
    return 0;
}

static int cmd_put_multi_cover_figure(void *priv, char *content)
{
    json_object *new_obj = NULL;
    json_object *parm = NULL;
    json_object *tmp = NULL;
    char buf[128];
    u32 i = 0;
    char filename[8];
    u32 ret = 0;
    new_obj = json_tokener_parse(content);
    parm =  json_object_object_get(new_obj, "param");
    char (*file_name_array)[64] = calloc(1, 51 * 64);
    if (file_name_array == NULL) {
        CTP_CMD_COMBINED(priv, CTP_REQUEST, "MULTI_COVER_FIGURE", "NOTIFY", CTP_REQUEST_MSG);
        return 0;
    }

    while (1) {
        sprintf(filename, "path_%d", i);
        tmp =  json_object_object_get(parm, filename);

        if (tmp == NULL) {
            break;
        }

        if (i > 50) {
            printf("path is too many\n");
            CTP_CMD_COMBINED(priv, CTP_REQUEST, "MULTI_COVER_FIGURE", "NOTIFY", CTP_REQUEST_MSG);
            break;
        }

        const char *tmp_value = json_object_get_string(tmp);
        strcpy(file_name_array[i], tmp_value);
        /* printf("%d filename %s \n", i, file_name_array[i]); */
        i++;
    }

    if (!i) {
        free(file_name_array);
        file_name_array = NULL;
        CTP_CMD_COMBINED(priv, CTP_REQUEST, "MULTI_COVER_FIGURE", "NOTIFY", CTP_REQUEST_MSG);
        json_object_put(new_obj);
        return 0;
    }

    struct net_req req;
    memset(&req, 0, sizeof(struct net_req));
    req.pre.type = PREVIEW;
    req.pre.filename = file_name_array;
#ifdef CONFIG_ENABLE_VLIST
    if (video_preview_post_msg(&req)) {
        CTP_CMD_COMBINED(priv, CTP_REQUEST, "MULTI_COVER_FIGURE", "NOTIFY", CTP_REQUEST_MSG);
        json_object_put(new_obj);
        free(file_name_array);
        file_name_array = NULL;
        return 0;
    }
#endif
    json_object_put(new_obj);

    return 0;

}

static int cmd_put_time_axis_play(void *priv, char *content)
{
    struct server *net = NULL;
    json_object *new_obj = NULL;
    json_object *parm = NULL;
    json_object *tmp = NULL;
    u32 i = 0;
    char filename[8];
    u32 ret = 0;
    new_obj = json_tokener_parse(content);
    parm =  json_object_object_get(new_obj, "param");
    tmp =  json_object_object_get(parm, "path");
    const char *file_name = json_object_get_string(tmp);

    tmp =  json_object_object_get(parm, "offset");
    const char *msec = json_object_get_string(tmp);

    printf("filename :%s   msec:%s\n", file_name, msec);
    struct net_req req;
    memset(&req, 0, sizeof(struct net_req));
    strcpy(req.playback.file_name, file_name);
    req.playback.msec = atoi(msec);

#ifdef CONFIG_ENABLE_VLIST
    if (video_playback_post_msg(&req)) {
        CTP_CMD_COMBINED(priv, CTP_REQUEST, "TIME_AXIS_PLAY", "NOTIFY", CTP_REQUEST_MSG);
        json_object_put(new_obj);
        return 0;
    }
#endif
    json_object_put(new_obj);

    return 0;

}

static int cmd_put_time_axis_play_ctrl(void *priv, char *content)
{
    char buf[128];
    struct server *net = NULL;
    json_object *new_obj = NULL;
    json_object *parm = NULL;
    json_object *tmp = NULL;
    u32 i = 0;
    char filename[8];
    u32 ret = 0;
    new_obj = json_tokener_parse(content);
    parm =  json_object_object_get(new_obj, "param");
    tmp =  json_object_object_get(parm, "status");
    const char *status = json_object_get_string(tmp);

    struct sockaddr_in *dst_addr = ctp_srv_get_cli_addr(priv);
    if (!dst_addr) {
        dst_addr = cdp_srv_get_cli_addr(priv);
    }
    printf("status:%s\n", status);

    switch (atoi(status)) {
    case FILE_PLAY_VIDEO_CONTINUE:
#ifdef CONFIG_ENABLE_VLIST
        ret = playback_cli_continue(dst_addr);
#endif
        break;

    case FILE_PLAY_VIDEO_PAUSE:
#ifdef CONFIG_ENABLE_VLIST
        ret = playback_cli_pause(dst_addr);
#endif
        break;

    case FILE_PLAY_VIDEO_STOP:
#ifdef CONFIG_ENABLE_VLIST
        ret = playback_disconnect_cli(dst_addr);
#endif
        break;

    default:
        ret = -1;
        break;
    }

    if (!ret) {

        snprintf(buf, sizeof(buf), "status:%s", status);
        CTP_CMD_COMBINED(priv, CTP_NO_ERR, "TIME_AXIS_PLAY_CTRL", "NOTIFY", buf);
    } else {
        CTP_CMD_COMBINED(priv, CTP_REQUEST, "TIME_AXIS_PLAY_CTRL", "NOTIFY", CTP_REQUEST_MSG);
    }

    json_object_put(new_obj);

    return 0;

}

void ctp_cmd_socket_unregister(void *priv)
{
    if (!priv) {
        priv = info.cli;
        if (!priv) {
            return;
        }
    }
    struct sockaddr_in *addr;
    addr = (struct sockaddr_in *)ctp_srv_get_cli_addr(priv);
    if (!addr) {
        addr = (struct sockaddr_in *)cdp_srv_get_cli_addr(priv);
    }
    if (addr) {
        extern int TCP_client_socket_quit(int addr);
        extern int UDP_client_socket_unreg(int addr);
        TCP_client_socket_quit(addr->sin_addr.s_addr);
        UDP_client_socket_unreg(addr->sin_addr.s_addr);
    }
}

static int cmd_put_ctp_cli_connected(void *priv, char *content)
{
    return 0;
}

static int cmd_put_ctp_cli_disconnect(void *priv, char *content)
{
    char buf[32];
    struct sockaddr_in *dest_addr;
    struct ctp_map_entry *map;
    dest_addr = ctp_srv_get_cli_addr(priv);
    if (!dest_addr) {
        dest_addr = cdp_srv_get_cli_addr(priv);
    }
    info.dest_addr = NULL;
    info.cli = NULL;

    ctp_cmd_socket_unregister(priv);

    printf("|CLI_DISCONNECT 0x%x, 0x%x\n", (u32)priv, (u32)dest_addr->sin_addr.s_addr);

    struct intent it;
    init_intent(&it);
    it.name = "video_rec";
    it.action = ACTION_VIDEO_STOP_ALL;
    start_app(&it);

#ifdef CONFIG_ENABLE_VLIST
    video_preview_and_thus_disconnect(dest_addr);
    playback_disconnect_cli(dest_addr);
#endif
    http_get_server_discpnnect_cli(dest_addr);
    strcpy(buf, "status:1");
    CTP_CMD_COMBINED(priv, CTP_NO_ERR, "CTP_CLI_DISCONNECT", "NOTIFY", buf);
    list_for_ctp_mapping_tab(map) {
        map->sync = false;
    }

    ctp_srv_free_cli(priv);
    cdp_srv_free_cli(priv);

    return 0;
}


const struct ctp_map_entry ctp_video_cmd_tab[] SEC_USED(.ctp_video_cmd) = {
    {NULL, "OPEN_RT_STREAM", NULL, cmd_put_open_rt_stream},
    {NULL, "CLOSE_RT_STREAM", NULL, cmd_put_close_rt_stream},
    {NULL, "OPEN_REC", NULL, cmd_put_open_rec},
    {NULL, "CLOSE_REC", NULL, cmd_put_close_rec},

    {NULL, "CTP_CLI_DISCONNECT", NULL, cmd_put_ctp_cli_disconnect},
    {NULL, "CTP_CLI_CONNECTED", NULL, cmd_put_ctp_cli_connected},

    //TODO
    //以下命令移植行车工程ctp_cmd暂未做修改
    {NULL, "FORWARD_MEDIA_FILES_LIST", NULL, cmd_put_make_forward_files_list},
    {NULL, "MULTI_COVER_FIGURE", NULL, cmd_put_multi_cover_figure},
    {NULL,  "TIME_AXIS_PLAY", NULL, cmd_put_time_axis_play},
    {NULL,  "TIME_AXIS_PLAY_CTRL", NULL, cmd_put_time_axis_play_ctrl},
};


