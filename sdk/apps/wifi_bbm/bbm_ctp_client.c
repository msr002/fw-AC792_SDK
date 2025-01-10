#include "system/includes.h"
#include "server/ctp_server.h"
#include "sock_api/sock_api.h"
#include "baby_monitor.h"
#include "json_c/json.h"
#include "json_c/json_tokener.h"


#define CTP_CMD_PORT            3333    //CTP命令端口

static int json_parse_to_path(const char *parm_list, u8 *path)
{
    const char *tmp_value;
    json_object *new_obj = NULL;
    json_object *parm = NULL;
    json_object *tmp = NULL;
    new_obj = json_tokener_parse(parm_list);
    parm =  json_object_object_get(new_obj, "param");
    tmp =  json_object_object_get(parm, "path");
    if (tmp == NULL) {
        printf("err no path object \n");
        json_object_put(new_obj);
        return -1;
    }
    tmp_value = json_object_get_string(tmp);

    strcpy(path, tmp_value);

    printf("content :%s \n", parm_list);
    printf("path:%s \n", path);

    json_object_put(new_obj);
    return 0;
}

static int json_parse_sd_status(const char *parm_list)
{
    const char *tmp_value;
    json_object *new_obj = NULL;
    json_object *parm = NULL;
    json_object *tmp = NULL;
    int online_status;
    new_obj = json_tokener_parse(parm_list);
    parm =  json_object_object_get(new_obj, "param");
    tmp =  json_object_object_get(parm, "online");
    if (tmp == NULL) {
        printf("err no online object \n");
        json_object_put(new_obj);
        return -1;
    }
    tmp_value = json_object_get_string(tmp);

    online_status = atoi(tmp_value);

    json_object_put(new_obj);

    return online_status;
}

static int json_parse_video_finish(const char *parm_list, char *fname)
{
    const char *tmp_value;
    json_object *new_obj = NULL;
    json_object *parm = NULL;
    json_object *desc = NULL;
    json_object *desc_obj = NULL;
    json_object *tmp = NULL;

    new_obj = json_tokener_parse(parm_list);
    parm =  json_object_object_get(new_obj, "param");
    desc =  json_object_object_get(parm, "desc");

    desc_obj = json_tokener_parse(json_object_get_string(desc));
    tmp =  json_object_object_get(desc_obj, "f");
    if (tmp == NULL) {
        printf("err no f object \n");
        json_object_put(desc_obj);
        json_object_put(new_obj);
        return -1;
    }
    tmp_value = json_object_get_string(tmp);

    strcpy(fname, tmp_value);

    json_object_put(desc_obj);
    json_object_put(new_obj);

    return 0;
}


static int bbm_ctp_recv_callback(void *hdl, enum ctp_cli_msg_type type, const char *topic, const char *parm_list, void *priv)
{
    int ret;

    struct bbm_client_hdl *bbm_hdl = priv;
    if (type == CTP_CLI_RECV_MSG) {
        if (strstr(topic, "FORWARD_MEDIA_FILES_LIST")) {
            ret = json_parse_to_path(parm_list, bbm_hdl->vf_list);
            os_sem_post(&bbm_hdl->ctp_msg_sem);
        } else if (strstr(topic, "SD_STATUS")) {

        } else if (strstr(topic, "APP_ACCESS")) {
            os_sem_post(&bbm_hdl->ctp_msg_sem);
        } else if (strstr(topic, "VIDEO_FINISH")) {
            /* printf("parm:%s \n",parm_list); */
            char fname[32];
            ret = json_parse_video_finish(parm_list, fname);
            if (!ret) {
                printf("update file name list \n");
                bbm_hdl->file_total_num++;

                int list_size = bbm_hdl->file_total_num * sizeof(char *);
                bbm_hdl->file_name_list = realloc(bbm_hdl->file_name_list, list_size);
                if (!bbm_hdl->file_name_list) {
                    printf("file_name_list realloc err \n");
                    return -1;
                }
                int list_index = bbm_hdl->file_total_num - 1;
                bbm_hdl->file_name_list[list_index] = (char *)malloc(strlen(fname) + 1);
                if (bbm_hdl->file_name_list[list_index] == NULL) {
                    printf("malloc failed for file_list[%d]\n", list_index);
                    return -1;
                }
                strcpy(bbm_hdl->file_name_list[list_index], fname);
            }
        } else {
            /* printf("This msg not deal:topic:%s content:%s\n", topic, parm_list); */
        }
    } else if (type == CTP_CLI_DISCONNECT) {
        //TODO
    }


    return 0;
}

int bbm_ctp_send_access(void *ctp_cli_hdl)
{
    int ret = 0;
    //TODO
    //BBM_CTP_CMD暂时不需要
#if 0
    struct bbm_client_hdl *bbm_hdl = NULL;
    const char topic_1[] = {"APP_ACCESS"};
    const char content_1[] = {"{\"op\":\"PUT\",\"param\":{\"type\":\"0\",\"ver\":\"20700\"}}"};

    printf("ctp send access \n");

    if (!ctp_cli_hdl) {
        printf("ctp client hdl invalid\n");
        return -1;
    }

    bbm_hdl = ctp_cli_get_hdl_priv(ctp_cli_hdl);

    ret = ctp_cli_send(ctp_cli_hdl, topic_1, content_1);
    if (ret) {
        printf("ctp_cli_send :%s err\n", topic_1);
        return ret;
    }

    os_sem_set(&bbm_hdl->ctp_msg_sem, 0);
    ret = os_sem_pend(&bbm_hdl->ctp_msg_sem, 200);
    if (ret) {
        printf("wait access timeout :%d \n", ret);
        return ret;
    }
#endif

    return ret;
}

int bbm_ctp_client_init(void **ctp_cli_hdl, u32 dest_ip_addr, void *priv)
{
    int ret;
    struct sockaddr_in dest_addr = {0};
    void *hdl = NULL;
    struct bbm_client_hdl *bbm_hdl = priv;
    static int id = 1;

    dest_addr.sin_family = AF_INET;
    dest_addr.sin_addr.s_addr = dest_ip_addr;
    dest_addr.sin_port = htons(CTP_CMD_PORT);

    os_sem_create(&bbm_hdl->ctp_msg_sem, 0);

    hdl = ctp_cli_reg(id++, &dest_addr, bbm_ctp_recv_callback, priv);

    if (hdl == NULL) {
        printf("\n----ctp_cli_reg err----\n");
        os_sem_del(&bbm_hdl->ctp_msg_sem, OS_DEL_ALWAYS);
        return -1;
    }

    *ctp_cli_hdl = hdl;

    bbm_ctp_file_init(priv);

    return 0;
}

int bbm_ctp_client_exit(void **ctp_cli_hdl)
{
    void *hdl = *ctp_cli_hdl;

    struct bbm_client_hdl *bbm_hdl = ctp_cli_get_hdl_priv(hdl);
    if (!bbm_hdl) {
        printf(" cli get priv err \n");
        return -1;
    }

    bbm_ctp_file_exit(bbm_hdl);

    ctp_cli_unreg(hdl);
    os_sem_del(&bbm_hdl->ctp_msg_sem, OS_DEL_ALWAYS);

    *ctp_cli_hdl = NULL;
    return 0;
}


