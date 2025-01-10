#include "wifi/wifi_connect.h"
#include "lwip/sockets.h"
#include "lwip/netdb.h"
#include "os/os_api.h"
#include "system/init.h"
#include "lwip.h"
#include "dhcp_srv/dhcp_srv.h"
#include "lwip/dns.h"
#include "device/device.h"
#include "system/app_core.h"
#include "server/server_core.h"
#include "action.h"
#include "system/timer.h"
#include "asm/debug.h"
#include "app_config.h"
#include "http/http_cli.h"
#include "system/timer.h"
#include "database.h"
#include "dev_desc.h"
#include "http/http_server.h"
#include "server/ctp_server.h"
#include "server/net_server.h"
#include "video_rt_tcp.h"
#include "ftpserver/stupid-ftpd.h"
#include "streaming_media_server/fenice_config.h"
#include "syscfg/syscfg_id.h"
#include "udp_multicast.h"
#include "json_c/json.h"
#include "json_c/json_tokener.h"
#include "net_event.h"
#include "pairing_data_model.h"

const u8 bbm_tx_pair_mac[6] = {0x88, 0x88, 0x88, 0x88, 0x88, 0x88};
const u8 bbm_bssid_mac[6] = {0x88, 0x88, 0x88, 0x99, 0x88, 0x77};

#define WIFI_APP_TASK_NAME "wifi_app_task"

#define MAC_ADDR_LEN 6
#define HEAD_802_11_OFFSET 20

static int multicast_recv_task_pid;
static int bbm_tx_online_task_pid;
static int bbm_rx_online_task_pid;
static u8 multicast_recv_task_exit;
static int net_state_timer;

#define DEST_IP_ADDR "192.168.1.1"

static struct server *ctp = NULL;
static const struct ctp_server_info server_info = {
    .ctp_vaild = true,
    .ctp_port = CTP_CTRL_PORT,
    .cdp_vaild = true,
    .cdp_port = CDP_CTRL_PORT,
    .k_alive_type = NOT_USE_ALIVE,
    /*.k_alive_type = CDP_ALIVE,*/
};

#define NET_INFO_FLASH_INDEX     1


#define PACKAGE_MAX_SIZE    1024

struct parse_recv_info {
    u32 bbm_rx_ip;
    u32 bbm_tx_ip;

    u8 bbm_rx_mac[6];
    u8 bbm_tx_mac[6];
};

static char default_dest_ip[20];

typedef struct _head_802_11 {
    unsigned short  fc;
    unsigned short  duration;
    unsigned char   addr1[MAC_ADDR_LEN];
    unsigned char   addr2[MAC_ADDR_LEN];
    unsigned char	addr3[MAC_ADDR_LEN];
    unsigned short	frag: 4;
    unsigned short	sequence: 12;
    unsigned char 	data[0];
} head_802_11, *phead_802_11;

struct lan_setting lan_setting_info = {
    .WIRELESS_IP_ADDR0  = 192,
    .WIRELESS_IP_ADDR1  = 168,
    .WIRELESS_IP_ADDR2  = 1,
#ifdef CONFIG_BBM_RX
    .WIRELESS_IP_ADDR3  = 1,
#else
    .WIRELESS_IP_ADDR3  = 2,
#endif

    .WIRELESS_NETMASK0  = 255,
    .WIRELESS_NETMASK1  = 255,
    .WIRELESS_NETMASK2  = 255,
    .WIRELESS_NETMASK3  = 0,

    .WIRELESS_GATEWAY0  = 192,
    .WIRELESS_GATEWAY1  = 168,
    .WIRELESS_GATEWAY2  = 1,
    .WIRELESS_GATEWAY3  = 1,

    .SERVER_IPADDR1  = 192,
    .SERVER_IPADDR2  = 168,
    .SERVER_IPADDR3  = 1,
    .SERVER_IPADDR4  = 1,

    .CLIENT_IPADDR1  = 192,
    .CLIENT_IPADDR2  = 168,
    .CLIENT_IPADDR3  = 1,
    .CLIENT_IPADDR4  = 2,

    .SUB_NET_MASK1   = 255,
    .SUB_NET_MASK2   = 255,
    .SUB_NET_MASK3   = 255,
    .SUB_NET_MASK4   = 0,
};


static void net_state_timer_func(void *p)
{
    //网速
    /* printf("WIFI U= %d KB/s, D= %d KB/s\r\n", wifi_get_upload_rate() / 1024, wifi_get_download_rate() / 1024); */

    //内存
    malloc_stats();
}

static int lwip_set_lan_info(struct lan_setting *__lan_setting_info)
{
    struct lan_setting *lan_setting_info = net_get_lan_info(WIFI_RAW_NETIF);
    if (!lan_setting_info) {
        return -1;
    }

    lan_setting_info->WIRELESS_IP_ADDR0  = __lan_setting_info->WIRELESS_IP_ADDR0;
    lan_setting_info->WIRELESS_IP_ADDR1  = __lan_setting_info->WIRELESS_IP_ADDR1;
    lan_setting_info->WIRELESS_IP_ADDR2  = __lan_setting_info->WIRELESS_IP_ADDR2;
    lan_setting_info->WIRELESS_IP_ADDR3  = __lan_setting_info->WIRELESS_IP_ADDR3;

    lan_setting_info->WIRELESS_NETMASK0  = __lan_setting_info->WIRELESS_NETMASK0;
    lan_setting_info->WIRELESS_NETMASK1  = __lan_setting_info->WIRELESS_NETMASK1;
    lan_setting_info->WIRELESS_NETMASK2  = __lan_setting_info->WIRELESS_NETMASK2;
    lan_setting_info->WIRELESS_NETMASK3  = __lan_setting_info->WIRELESS_NETMASK3;

    lan_setting_info->WIRELESS_GATEWAY0  = __lan_setting_info->WIRELESS_GATEWAY0;
    lan_setting_info->WIRELESS_GATEWAY1  = __lan_setting_info->WIRELESS_GATEWAY1;
    lan_setting_info->WIRELESS_GATEWAY2  = __lan_setting_info->WIRELESS_GATEWAY2;
    lan_setting_info->WIRELESS_GATEWAY3  = __lan_setting_info->WIRELESS_GATEWAY3;

    lan_setting_info->SERVER_IPADDR1     = __lan_setting_info->SERVER_IPADDR1;
    lan_setting_info->SERVER_IPADDR2     = __lan_setting_info->SERVER_IPADDR2;
    lan_setting_info->SERVER_IPADDR3     = __lan_setting_info->SERVER_IPADDR3;
    lan_setting_info->SERVER_IPADDR4     = __lan_setting_info->SERVER_IPADDR4;

    lan_setting_info->CLIENT_IPADDR1     = __lan_setting_info->CLIENT_IPADDR1;
    lan_setting_info->CLIENT_IPADDR2     = __lan_setting_info->CLIENT_IPADDR2;
    lan_setting_info->CLIENT_IPADDR3     = __lan_setting_info->CLIENT_IPADDR3;
    lan_setting_info->CLIENT_IPADDR4     = __lan_setting_info->CLIENT_IPADDR4;

    lan_setting_info->SUB_NET_MASK1      = __lan_setting_info->SUB_NET_MASK1;
    lan_setting_info->SUB_NET_MASK2      = __lan_setting_info->SUB_NET_MASK2;
    lan_setting_info->SUB_NET_MASK3      = __lan_setting_info->SUB_NET_MASK3;
    lan_setting_info->SUB_NET_MASK4      = __lan_setting_info->SUB_NET_MASK4;

    return 0;
}

void config_send_pkg_head(u8 *src_mac, u8 *dest_mac);

void mac_to_string(char *mac_str, const u8 mac[6])
{
    sprintf(mac_str, "%02x:%02x:%02x:%02x:%02x:%02x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
}

void string_to_mac(const char *mac_str, u8 mac[6])
{
    sscanf(mac_str, "%02x:%02x:%02x:%02x:%02x:%02x",
           &mac[0], &mac[1], &mac[2], &mac[3], &mac[4], &mac[5]);
}



static int ctp_init(void)
{
#ifdef CONFIG_BBM_TX
    ctp = server_open("ctp_server", (void *)&server_info);
    if (!ctp) {
        printf("ctp server fail\n");
    }
    puts("http server init\n");
    extern int http_virfile_reg(const char *path, const char *contents, unsigned long len);

    http_virfile_reg(DEV_DESC_PATH, DEV_DESC_CONTENT, strlen(DEV_DESC_CONTENT)); //注册虚拟文件描述文档,可在dev_desc.h修改
    http_get_server_init(HTTP_PORT); //8080
    video_rt_tcp_server_init(2229);
#ifdef CONFIG_ENABLE_VLIST
    preview_init(VIDEO_PREVIEW_PORT, NULL); //2226
    playback_init(VIDEO_PLAYBACK_PORT, NULL);
#endif

    printf("ftpd server init \n");
    /*extern void ftpd_vfs_interface_cfg(void);*/
    /*ftpd_vfs_interface_cfg();*/
    /*stupid_ftpd_init("MAXUSERS=2\nUSER=FTPX 12345678     0:/      2   A\n", NULL);*/

    void ftpd_server_init(const char *user, const char *pass, const char *ota_name, int fifo_size);
    ftpd_server_init("FTPX", "12345678", "update-ota.ufw", 4096);
#else
    ctp_cli_init();
#endif
}

void ctp_exit(void)
{
    puts("ctp server uninit\n");
    server_close(ctp);
    puts("http server uninit\n");
    http_get_server_uninit(); //8080
    stupid_ftpd_uninit();
    video_rt_tcp_server_uninit();
    preview_uninit(); //2226
    playback_uninit();
}

static int deal_pair_request_package(u8 *payload_buf, struct parse_recv_info *info)
{
    //解析json
    json_object *new_obj = NULL;
    json_object *data_obj = NULL;
    char *bbm_rx_ip_str, *bbm_rx_mac_str, *bbm_tx_ip_str, *bbm_tx_mac_str;

    new_obj = json_tokener_parse(payload_buf);
    data_obj =  json_object_object_get(new_obj, "data");

    bbm_rx_ip_str = json_object_get_string(json_object_object_get(data_obj, "bbm_rx_ip"));
    bbm_rx_mac_str = json_object_get_string(json_object_object_get(data_obj, "bbm_rx_mac"));
    bbm_tx_ip_str = json_object_get_string(json_object_object_get(data_obj, "bbm_tx_ip"));
    bbm_tx_mac_str = json_object_get_string(json_object_object_get(data_obj, "bbm_tx_mac"));

    printf("request rx ip:%s rx mac:%s tx ip:%s tx mac:%s", bbm_rx_ip_str, bbm_rx_mac_str, bbm_tx_ip_str, bbm_tx_mac_str);

    //ip
    info->bbm_rx_ip = inet_addr(bbm_rx_ip_str);
    info->bbm_tx_ip = inet_addr(bbm_tx_ip_str);
    //mac
    string_to_mac(bbm_rx_mac_str, info->bbm_rx_mac);
    string_to_mac(bbm_tx_mac_str, info->bbm_tx_mac);

    return 0;
}

static void fill_respone_data(u8 *data)
{
    //获取本机MAC
    char bbm_tx_mac[6];
    char bbm_tx_mac_str[20];
    wifi_raw_get_mac(bbm_tx_mac);
    mac_to_string(bbm_tx_mac_str, bbm_tx_mac);

    //获取本机IP
    struct netif_info netif_info;
    lwip_get_netif_info(WIFI_RAW_NETIF, &netif_info);
    char *bbm_tx_ip_str = inet_ntoa(netif_info.ip);

    sprintf(data, PAIRING_RESPONE, bbm_tx_ip_str, bbm_tx_mac_str);
}

static void multicast_recv_task(void)
{
    struct sockaddr_in dstaddr;
    u32 addrlen = sizeof(dstaddr);
    void *multi_sock = NULL;
    u8 *recv_buf = NULL, *send_buf = NULL, *tem_buf = NULL, *payload_buf = NULL;
    int recv_len, send_len, payload_len;
    int ret;

    multi_sock = CreateUdpMulticast(MULTICAST_PORT);
    if (multi_sock < 0) {
        printf("CreateUdpMulticast err \n");
        goto exit;
    }

    recv_buf = malloc(PACKAGE_MAX_SIZE);
    send_buf = malloc(PACKAGE_MAX_SIZE);
    tem_buf = malloc(PACKAGE_MAX_SIZE);
    if ((!recv_buf) || (!send_buf) || (!tem_buf)) {
        printf("package buf malloc fail \n");
        goto exit;
    }

    sock_set_recv_timeout(multi_sock, 100);
    while (1) {

        if (multicast_recv_task_exit) {
            printf("multicast_recv_task_exit\n");
            break;
        }

        wifi_raw_set_mac(bbm_tx_pair_mac);

        recv_len = sock_recvfrom(multi_sock, recv_buf, PACKAGE_MAX_SIZE, 0, &dstaddr, &addrlen);
        if (recv_len <= 0) {
            /* printf("multicast udp recv err\n"); */
            continue;
        }
        printf("multi recv \n");

        //检查包头
        payload_len = get_package_payload_len(recv_buf);
        if (payload_len < 0) {
            printf("package head err \n");
            continue;
        }
        payload_buf = recv_buf + (recv_len - payload_len);

        //检查是不是配对请求包
        if (!strstr(payload_buf, "pair_req")) {
            printf("no pair req package \n");
            continue;
        }

        struct parse_recv_info recv_pair_info = {0};

        //解析json
        deal_pair_request_package(payload_buf, &recv_pair_info);

        //配置网络
        wifi_raw_set_static(recv_pair_info.bbm_tx_ip, recv_pair_info.bbm_tx_mac,
                            recv_pair_info.bbm_rx_ip, recv_pair_info.bbm_rx_mac);

        //填充包数据
        fill_respone_data(tem_buf);
        send_len = package_assembly(tem_buf, strlen(tem_buf), send_buf, PACKAGE_MAX_SIZE);

        //接收ack包
        int timeout_cnt = 10;
        int i;
        for (i = 0; i < timeout_cnt; i++) {

            send_len = sock_sendto(multi_sock, send_buf, send_len, 0, &dstaddr, sizeof(dstaddr));
            if (send_len <= 0) {
                printf("respone udp send err\n");
                continue;
            }
            printf("multi send ack \n");

            recv_len = sock_recvfrom(multi_sock, recv_buf, PACKAGE_MAX_SIZE, 0, &dstaddr, &addrlen);
            if (recv_len <= 0) {
                printf("recv ack timeout %d\n", i);
                continue;
            }
            payload_len = get_package_payload_len(recv_buf);
            if (payload_len < 0) {
                continue;
            }
            payload_buf = recv_buf + (recv_len - payload_len);
            if (!strstr(payload_buf, "pair_ack")) {
                continue;
            }
            break;
        }

        if (i < timeout_cnt) {
            //写入flash
            ret = syscfg_write(NET_INFO_FLASH_INDEX, &recv_pair_info, sizeof(struct parse_recv_info));
            if (ret <= 0) {
                printf("syscfg_write err :%d \n", ret);
                goto exit;
            }
            printf("bbm TX pair success !\n");
            break;

        } else {
            printf("bbm TX pair fail ! No recv ack\n");
        }

    }

exit:
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

//修改发送包头部信息、及arp映射
int wifi_raw_set_static(u32 src_ip_addr, u8 *src_mac, u32 dest_ip_addr, u8 *dest_mac)
{
    //mac
    wifi_raw_set_mac(src_mac);

    lwip_etharp_remove_static_entry(default_dest_ip);

    //ip
    struct netif *netif = net_get_netif_handle(WIFI_RAW_NETIF);
    netif_set_ipaddr(netif, &src_ip_addr);

    config_send_pkg_head(src_mac, dest_mac);

    strcpy(default_dest_ip, inet_ntoa(dest_ip_addr));

    lwip_etharp_add_static_entry(default_dest_ip, dest_mac);

    return 0;
}

void config_send_pkg_head(u8 *src_mac, u8 *dest_mac)
{
    //设置发送包的802.11头部信息, 设置源mac， 目标mac， seq号等信息
    phead_802_11 pHdr = wifi_get_wifi_send_pkg_ptr() + HEAD_802_11_OFFSET;
    memcpy(pHdr->addr1, dest_mac, 6);
    memcpy(pHdr->addr2, src_mac, 6);
    memcpy(pHdr->addr3, bbm_bssid_mac, 6);
    pHdr->frag = 8;
}

//TX创建组播线程
#ifdef CONFIG_BBM_TX

void bbm_tx_enter_pairing(void)
{
    if (!multicast_recv_task_pid) {
        thread_fork("multicast_recv_task", 10, 2048, 2048
                    , &multicast_recv_task_pid, multicast_recv_task, NULL);
    }
}

void bbm_tx_exit_pairing(void)
{
    if (multicast_recv_task_pid) {
        multicast_recv_task_exit = 1;
        thread_kill(&multicast_recv_task_pid, KILL_WAIT);
        multicast_recv_task_exit = 0;
        multicast_recv_task_pid = 0;
    }
}

static void bbm_tx_online_task(void)
{
    void *multi_sock = NULL;
    u8 send_buf[32];
    u32 send_len = sizeof(send_buf);
    u32 magic = PACKAGE_MAGIC;
    u32 online_cnt = 0;
    memcpy(send_buf, &magic, sizeof(magic));

    multi_sock = sock_reg(AF_INET, SOCK_DGRAM, 0, NULL, NULL);
    if (multi_sock == NULL) {
        printf("online multi sock_reg err\n");
        return;
    }

    struct sockaddr_in dest_addr;
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_addr.s_addr = inet_addr(UDP_MULTICAST_ADDR);
    dest_addr.sin_port = htons(MULTICAST_ONLINE_PORT);

    while (1) {
        online_cnt++;
        memcpy(send_buf + sizeof(magic), &online_cnt, sizeof(online_cnt));

        send_len = sock_sendto(multi_sock, send_buf, send_len, 0, &dest_addr, sizeof(dest_addr));
        if (send_len < 0) {
            printf("online sock send err\n");
            continue;
        }

        //200ms
        os_time_dly(20);
    }
}

#else

static void bbm_rx_online_task(void)
{
    void *multi_sock = NULL;
    u8 recv_buf[32];
    u32 recv_len = sizeof(recv_buf);
    u32 ip_addr;
    u32 online_cnt;
    u32 magic;

    struct sockaddr_in dstaddr;
    u32 addrlen = sizeof(dstaddr);

    struct intent it;
    init_intent(&it);
    it.name	= "baby_monitor";
    it.action = ACTION_BBM_ONLINE;

    multi_sock = CreateUdpMulticast(MULTICAST_ONLINE_PORT);
    if (multi_sock < 0) {
        printf("CreateUdpMulticast err \n");
        return;
    }

    while (1) {
        recv_len = sock_recvfrom(multi_sock, recv_buf, 32, 0, &dstaddr, &addrlen);
        if (recv_len <= 0) {
            continue;
        }

        memcpy(&magic, recv_buf, sizeof(magic));
        if (magic != PACKAGE_MAGIC) {
            printf("magic err\n");
            continue;
        }

        ip_addr = dstaddr.sin_addr.s_addr;
        memcpy(&online_cnt, recv_buf + sizeof(magic), sizeof(online_cnt));

        it.data = ip_addr;
        it.exdata = online_cnt;
        start_app_async(&it, NULL, NULL);
    }
}
#endif


static void wifi_raw_init(void *priv)
{
    int ret;

    strcpy(default_dest_ip, DEST_IP_ADDR);

    u8 dest_mac[6] = {0x88, 0x88, 0x88, 0x88, 0x88, 0x88};

#ifdef  CONFIG_BBM_TX
    struct parse_recv_info recv_pair_info = {0};
    u8 src_mac[6] = {0x88, 0x88, 0x88, 0x88, 0x88, 0x88};

    //TX根据FLASH来修改IP
    ret = syscfg_read(NET_INFO_FLASH_INDEX, &recv_pair_info, sizeof(struct parse_recv_info));
    if (ret > 0) {
        u32 ip_addr = recv_pair_info.bbm_tx_ip;
        lan_setting_info.WIRELESS_IP_ADDR0 = (ip_addr & 0xFF);
        lan_setting_info.WIRELESS_IP_ADDR1 = (ip_addr >> 8) & 0xFF;
        lan_setting_info.WIRELESS_IP_ADDR2 = (ip_addr >> 16) & 0xFF;
        lan_setting_info.WIRELESS_IP_ADDR3 = (ip_addr >> 24) & 0xFF;

        memcpy(src_mac, recv_pair_info.bbm_tx_mac, sizeof(src_mac));
        memcpy(dest_mac, recv_pair_info.bbm_rx_mac, sizeof(dest_mac));
        strcpy(default_dest_ip, inet_ntoa(recv_pair_info.bbm_rx_ip));
        printf("syscfg read ok ! \n ip:%s \n", inet_ntoa(ip_addr));
    }
#else
    //BBM_RX端MAC地址，多RX同时用时，MAC地址要不一样
    u8 src_mac[6] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66};
#endif

    //设置静态IP
    lwip_set_lan_info(&lan_setting_info);

    //启动wifi_raw
    wifi_raw_on(1);

    //过滤掉一些不用的包
    filt_pack_not_need();

    //设置mac地址,软件mac地址过滤
    wifi_raw_set_mac(src_mac);

    //设置发送包头信息
    config_send_pkg_head(src_mac, dest_mac);

    //设置硬件bssid过滤
    wf_asic_set_bssid(bbm_bssid_mac);

    wifi_set_pwr(6);

#ifdef CONFIG_BBM_RX
    arp_static_table_init();
#else
    lwip_etharp_add_static_entry(default_dest_ip, dest_mac);
#endif

#ifdef CONFIG_BBM_RX
    thread_fork("bbm_rx_online_task", 16, 2048, 2048
                , &bbm_rx_online_task_pid, bbm_rx_online_task, NULL);

#else
    thread_fork("bbm_tx_online_task", 16, 2048, 2048
                , &bbm_tx_online_task_pid, bbm_tx_online_task, NULL);
#endif

    net_state_timer = sys_timer_add_to_task("app_core", NULL, net_state_timer_func, 5000);

    //TX创建CTP_SERVER,RX初始化CTP_CLIENT
    ctp_init();

}

#ifdef CONFIG_WIFI_ENABLE
int wireless_net_init(void)
{
    wifi_raw_init(NULL);
}
late_initcall(wireless_net_init);
#endif

const char *get_root_path(void)
{
    return CONFIG_ROOT_PATH;
}
#if defined CONFIG_ENABLE_VLIST
unsigned short DUMP_PORT()
{
    return _DUMP_PORT;
}

unsigned short FORWARD_PORT()
{
    return _FORWARD_PORT;
}

unsigned short BEHIND_PORT()
{
    return _BEHIND_PORT;
}

const char *get_rec_path_0()
{
    return NULL;
}
const char *get_rec_path_1()
{
    return CONFIG_REC_PATH_0;
}
const char *get_rec_path_2()
{
    return CONFIG_REC_PATH_1;
}
const char *get_rec_path_3()
{
    return CONFIG_REC_PATH_2;
}
const char *get_rec_emr_path_1()
{
#ifdef CONFIG_EMR_REC_PATH_0
    return CONFIG_EMR_REC_PATH_0;
#else
    return NULL;
#endif
}
const char *get_rec_emr_path_2()
{
#ifdef CONFIG_EMR_REC_PATH_1
    return CONFIG_EMR_REC_PATH_1;
#else
    return NULL;
#endif
}
const char *get_rec_emr_path_3()
{
#ifdef CONFIG_EMR_REC_PATH_2
    return CONFIG_EMR_REC_PATH_2;
#else
    return NULL;
#endif
}
#endif
