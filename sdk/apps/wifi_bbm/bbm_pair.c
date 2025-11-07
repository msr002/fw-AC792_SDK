#include "system/includes.h"
#include "app_config.h"
#include "pairing_data_model.h"
#include "arp_static_table.h"
#include "lwip/sockets.h"
#include "json_c/json.h"
#include "json_c/json_tokener.h"
#include "udp_multicast.h"

#define RECV_TIMEOUT             1000
#define USB_PAIR_RECV_BUF_SIZE    512

static int pairing_task_pid;
static int pairing_task_exit;
static int usb_pairing_task_pid;
static int usb_pairing_task_exit;

OS_SEM *usb_read_sem;
static u8 usb_pair_recv_buf[USB_PAIR_RECV_BUF_SIZE];
static int usb_pair_recv_len = 0;
static void *cdc_dev = NULL;
u8 g_pair_usb_id;

void bbm_config_arp_entry(struct arp_entry_t *arp_entry);

#if BBM_USB_PAIR_ENABLE
/* //cdc接收数据弱定义函数 */
int host_cdc_rx_callback(u8 usb_id, void *buf, int len)
{
    printf("recv len:%d \n", len);
    put_buf(buf, len);

    if (g_pair_usb_id == usb_id && usb_pairing_task_pid) {
        if (((usb_pair_recv_len + len) < USB_PAIR_RECV_BUF_SIZE)) {
            memcpy(usb_pair_recv_buf + usb_pair_recv_len, buf, len);
            usb_pair_recv_len += len;
            if (usb_read_sem) {
                os_sem_post(usb_read_sem);
            }
        }
    }
}
#endif

static int bbm_pair_usb_recv(u8 *buf, int *len)
{
    *len = 0;
    int waitms = 10;
    while (1) {
        if (OS_TIMEOUT == os_sem_pend(usb_read_sem, waitms)) {
            break;
        }
    }

    if (usb_pair_recv_len != 0) {
        memcpy(buf, usb_pair_recv_buf, usb_pair_recv_len);
    }
    *len = usb_pair_recv_len;
    usb_pair_recv_len = 0;

    return 0;
}

static void fill_request_data(u8 *data, char *bbm_tx_ip_str, u8 *bbm_tx_mac, int wifi_ch)
{
    //获取本机MAC
    u8 bbm_rx_mac[6];
    char bbm_tx_mac_str[20];
    char bbm_rx_mac_str[20];
    char bbm_rx_ip_str[20];
    wifi_raw_get_mac(bbm_rx_mac);
    mac_to_string(bbm_rx_mac_str, bbm_rx_mac);

    //获取本机IP
    struct netif_info netif_info;
    lwip_get_netif_info(WIFI_RAW_NETIF, &netif_info);
    strcpy(bbm_rx_ip_str, inet_ntoa(netif_info.ip));

    mac_to_string(bbm_tx_mac_str, bbm_tx_mac);

    sprintf(data, PAIRING_REQUEST, bbm_rx_ip_str, bbm_rx_mac_str, bbm_tx_ip_str, bbm_tx_mac_str, wifi_ch);
}

static int deal_pair_respone_package(u8 *payload_buf, char *set_bbm_tx_ip, u8 *set_bbm_tx_mac)
{
    //解析json
    json_object *new_obj = NULL;
    json_object *type_obj = NULL;
    json_object *data_obj = NULL;
    char *bbm_tx_ip_str, *bbm_tx_mac_str, *type;
    char mac_str[20];

    new_obj = json_tokener_parse(payload_buf);
    type_obj =  json_object_object_get(new_obj, "type");
    type = json_object_get_string(type_obj);

    if (!strcmp(type, "pair_rsp")) {
        data_obj =  json_object_object_get(new_obj, "data");
        bbm_tx_ip_str = json_object_get_string(json_object_object_get(data_obj, "bbm_tx_ip"));
        bbm_tx_mac_str = json_object_get_string(json_object_object_get(data_obj, "bbm_tx_mac"));

        printf("recv pair_rsp ip:%s mac:%s\n", bbm_tx_ip_str, bbm_tx_mac_str);
        char req_mac_str[20];
        mac_to_string(req_mac_str, set_bbm_tx_mac);
        if (strcmp(set_bbm_tx_ip, bbm_tx_ip_str) == 0 &&
            strcmp(req_mac_str, bbm_tx_mac_str) == 0) {
            return 0;
        }
    }

    return -1;
}

static void config_head_pair(void)
{
    u8 src_mac[6];
    extern const u8 bbm_tx_pair_mac[6];
    extern const int bbm_tx_pair_wifi_channel;
    wifi_set_channel(bbm_tx_pair_wifi_channel);
    wifi_raw_get_mac(src_mac);
    config_send_pkg_head(src_mac, bbm_tx_pair_mac);
}

static int bbm_pairing_task(void *priv)
{
    u8 channel = (u8)priv;

    int ret;
    void *multi_sock = NULL;
    u8 *recv_buf = NULL, *send_buf = NULL, *tem_buf = NULL, *payload_buf = NULL;
    int recv_len, send_len, payload_len;
    struct sockaddr_in recv_addr;
    unsigned int addrlen = sizeof(recv_addr);

    multi_sock = sock_reg(AF_INET, SOCK_DGRAM, 0, NULL, NULL);
    if (multi_sock == NULL) {
        printf("sock_reg err\n");
        goto exit;
    }
    sock_set_recv_timeout(multi_sock, RECV_TIMEOUT);

    struct sockaddr_in dest_addr;
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_addr.s_addr = inet_addr(UDP_MULTICAST_ADDR);
    dest_addr.sin_port = htons(MULTICAST_PORT);

    recv_buf = malloc(PACKAGE_MAX_SIZE);
    send_buf = malloc(PACKAGE_MAX_SIZE);
    tem_buf = malloc(PACKAGE_MAX_SIZE);

    if ((!recv_buf) || (!send_buf) || (!tem_buf)) {
        printf("package buf malloc fail \n");
        goto exit;
    }


    struct arp_entry_t *arp_entry = arp_static_entry_alloc(channel);
    if (!arp_entry) {
        printf("arp_static_entry_alloc err ch:%d used \n", channel);
        goto exit;
    }
    char set_bbm_tx_ip[20];
    u8 set_bbm_tx_mac[6];
    int set_wifi_channel;

    strcpy(set_bbm_tx_ip, inet_ntoa(arp_entry->ipaddr));
    memcpy(set_bbm_tx_mac, arp_entry->ethaddr.addr, sizeof(set_bbm_tx_mac));

    syscfg_read(BBM_WIFI_CH_INDEX, &set_wifi_channel, sizeof(set_wifi_channel));

    //填充发送消息
    fill_request_data(tem_buf, set_bbm_tx_ip, set_bbm_tx_mac, set_wifi_channel);
    send_len = package_assembly(tem_buf, strlen(tem_buf), send_buf, PACKAGE_MAX_SIZE);

    config_head_pair();

    while (1) {

        if (pairing_task_exit) {
            log_d("pairing task exit  \n");
            arp_static_entry_free(channel);
            break;
        }

        //发送配对请求包
        send_len = sock_sendto(multi_sock, send_buf, send_len, 0, &dest_addr, sizeof(dest_addr));
        if (send_len < 0) {
            printf("sock send err\n");
            continue;
        }

        //接收配对响应包
        recv_len = sock_recvfrom(multi_sock, recv_buf, PACKAGE_MAX_SIZE, 0, &recv_addr, &addrlen);
        if (recv_len <= 0) {
            printf("multi recv err");
            continue;
        }
        printf("recv ip:%s port:%d \n", inet_ntoa(recv_addr.sin_addr), ntohs(recv_addr.sin_port));

        //检查包头
        payload_len = get_package_payload_len(recv_buf);
        if (payload_len < 0) {
            printf("package head err \n");
            continue;
        }
        payload_buf = recv_buf + (recv_len - payload_len);

        //检查配对信息是否正确
        ret = deal_pair_respone_package(payload_buf, set_bbm_tx_ip, set_bbm_tx_mac);
        if (ret) {
            printf("no respone package\n");
            continue;
        }

        u8 src_mac[6];
        wifi_raw_get_mac(src_mac);
        config_send_pkg_head(src_mac, set_bbm_tx_mac);

        os_time_dly(30);

        //发送响应
        sprintf(tem_buf, PAIRING_ACK);
        send_len = package_assembly(tem_buf, strlen(tem_buf), send_buf, PACKAGE_MAX_SIZE);
        send_len = sock_sendto(multi_sock, send_buf, send_len, 0, &dest_addr, sizeof(dest_addr));
        if (send_len < 0) {
            printf("sock send err\n");
            continue;
        }

        printf("pair success \n");
        //写入flash
        arp_static_table_update_to_flash();

        //通知UI配对完成
        post_pair_msg_to_ui("pair success");

        break;
    }

exit:
    for (int ch = 0; ch < 6; ch++) {
        struct arp_entry_t *arp_entry  = get_arp_static_entry_by_id(ch);
        if (arp_entry) {
            bbm_config_arp_entry(arp_entry);
            break;
        }
    }
    wifi_set_channel(set_wifi_channel);

    if (multi_sock) {
        sock_unreg(multi_sock);
    }
    if (recv_buf) {
        free(recv_buf);
    }
    if (send_buf) {
        free(send_buf);
    }
    if (tem_buf) {
        free(tem_buf);
    }
}

static int bbm_usb_pairing_task(void *priv)
{
    u8 channel = (u8)priv;

    int ret;
    u8 *recv_buf = NULL, *send_buf = NULL, *tem_buf = NULL, *payload_buf = NULL;
    int recv_len, send_len, payload_len;

    u8 usb_id = 0;
    char cdc_name[16];
    sprintf(cdc_name, "cdc%d", usb_id);
    if (!cdc_dev) {
        cdc_dev = dev_open(cdc_name, NULL); /* 需要在板级定义cdc0设备 */
        if (!cdc_dev) {
            printf("bbm usb pair open %s dev fail \n", cdc_name);
            goto exit;
        }
    }

    recv_buf = malloc(PACKAGE_MAX_SIZE);
    send_buf = malloc(PACKAGE_MAX_SIZE);
    tem_buf = malloc(PACKAGE_MAX_SIZE);
    if ((!recv_buf) || (!send_buf) || (!tem_buf)) {
        printf("package buf malloc fail \n");
        goto exit;
    }

    struct arp_entry_t *arp_entry = arp_static_entry_alloc(channel);
    if (!arp_entry) {
        printf("arp_static_entry_alloc err ch:%d used \n", channel);
        goto exit;
    }
    char set_bbm_tx_ip[20];
    u8 set_bbm_tx_mac[6];
    int set_wifi_channel;

    strcpy(set_bbm_tx_ip, inet_ntoa(arp_entry->ipaddr));
    memcpy(set_bbm_tx_mac, arp_entry->ethaddr.addr, sizeof(set_bbm_tx_mac));

    syscfg_read(BBM_WIFI_CH_INDEX, &set_wifi_channel, sizeof(set_wifi_channel));

    //填充发送消息
    fill_request_data(tem_buf, set_bbm_tx_ip, set_bbm_tx_mac, set_wifi_channel);
    send_len = package_assembly(tem_buf, strlen(tem_buf), send_buf, PACKAGE_MAX_SIZE);

    config_head_pair();

    while (1) {

        if (usb_pairing_task_exit) {
            log_d("pairing task exit  \n");
            arp_static_entry_free(channel);
            break;
        }

        //发送配对请求包
        ret = dev_write(cdc_dev, send_buf, send_len);
        if (ret != send_len) {
            printf("usb pair usb cdc send err\n");
            continue;
        }

        bbm_pair_usb_recv(recv_buf, &recv_len);
        if (recv_len <= 0) {
            printf("usb pair usb cdc recv err\n");
            continue;
        }

        //检查包头
        payload_len = get_package_payload_len(recv_buf);
        if (payload_len < 0) {
            printf("package head err \n");
            continue;
        }
        payload_buf = recv_buf + (recv_len - payload_len);

        //检查配对信息是否正确
        ret = deal_pair_respone_package(payload_buf, set_bbm_tx_ip, set_bbm_tx_mac);
        if (ret) {
            printf("no respone package\n");
            continue;
        }

        u8 src_mac[6];
        wifi_raw_get_mac(src_mac);
        config_send_pkg_head(src_mac, set_bbm_tx_mac);

        //发送响应
        sprintf(tem_buf, PAIRING_ACK);
        send_len = package_assembly(tem_buf, strlen(tem_buf), send_buf, PACKAGE_MAX_SIZE);

        ret = dev_write(cdc_dev, send_buf, send_len);
        if (ret != send_len) {
            printf("usb pair usb cdc send err\n");
            continue;
        }

        printf("pair success \n");
        //写入flash
        arp_static_table_update_to_flash();

        break;
    }

exit:
    for (int ch = 0; ch < 6; ch++) {
        struct arp_entry_t *arp_entry  = get_arp_static_entry_by_id(ch);
        if (arp_entry) {
            bbm_config_arp_entry(arp_entry);
            break;
        }
    }
    wifi_set_channel(set_wifi_channel);

    //TODO，不关闭
    /*     if(cdc_dev){ */
    /* dev_close(cdc_dev); */
    /* cdc_dev =NULL; */
    /* } */

    if (recv_buf) {
        free(recv_buf);
    }
    if (send_buf) {
        free(send_buf);
    }
    if (tem_buf) {
        free(tem_buf);
    }
}

int bbm_set_enter_usb_pairing(u8 channel, u8 usb_id)
{
    if (usb_id == -1) {
        printf("usb id err \n");
        return 0;
    }

    if (usb_pairing_task_pid && !usb_pairing_task_exit) {
        printf("is pairing \n");
        return 0;
    }
    g_pair_usb_id = usb_id;

    if (!usb_read_sem) {
        usb_read_sem = malloc(sizeof(OS_SEM));

        if (!usb_read_sem) {
            printf("usb pair usb sem fail \n");
            goto err;
        }
        os_sem_create(usb_read_sem, 0);
    }

    int ret = thread_fork("bbm_usb_pairing_task", 10, 2048, 2048, &usb_pairing_task_pid,
                          bbm_usb_pairing_task, channel);
    if (ret) {
        printf("bbm rx usb pair task create fail :%d \n", ret);
        goto err;
    }

    return 0;

err:
    if (usb_read_sem) {
        os_sem_del(usb_read_sem, OS_DEL_ALWAYS);
        free(usb_read_sem);
        usb_read_sem = NULL;
    }

    return -1;
}

int bbm_set_exit_usb_pairing(void)
{
    if (usb_pairing_task_pid) {
        usb_pairing_task_exit = 1;
        thread_kill(&usb_pairing_task_pid, KILL_WAIT);
        usb_pairing_task_exit = 0;
    }

    if (usb_read_sem) {
        os_sem_del(usb_read_sem, OS_DEL_ALWAYS);
        free(usb_read_sem);
        usb_read_sem = NULL;
    }

    return 0;
}

//接收端进入配对模式
int bbm_set_enter_pairing(u8 channel)
{
    thread_fork("bbm_pairing_task", 10, 2048, 2048, &pairing_task_pid, bbm_pairing_task, channel);

    return 0;
}

int bbm_set_exit_pairing(void)
{
    if (!pairing_task_pid) {
        log_d("no pairing task run\n");
        return -1;
    }

    pairing_task_exit = 1;
    thread_kill(&pairing_task_pid, KILL_WAIT);
    pairing_task_exit = 0;
    pairing_task_pid = 0;

    return 0;
}


int bbm_set_unpair(u8 channel)
{
    int ret;

    arp_static_entry_free(channel);

    arp_static_table_update_to_flash();

    return 0;
}

u8 bbm_get_pair_status(u8 ch)
{
    struct arp_entry_t *arp_entry  = get_arp_static_entry_by_id(ch);
    if (arp_entry) {
        //已配对
        return 1;
    } else {
        //未配对
        return 0;
    }
}


void bbm_config_arp_entry(struct arp_entry_t *arp_entry)
{
    u8 src_mac[6];
    u8 dest_mac[6];

    wifi_raw_get_mac(src_mac);
    memcpy(dest_mac, arp_entry->ethaddr.addr, sizeof(dest_mac));
    config_send_pkg_head(src_mac, dest_mac);
}


