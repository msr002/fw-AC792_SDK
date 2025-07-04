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


#define DEMO_AP_MODE_SSID    "WL83_AP_DEMO"
#define DEMO_AP_MODE_PWD     ""


#define MAC_ADDR_LEN 6
#define HEAD_802_11_OFFSET 20
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

static struct lan_setting lan_setting_info = {
    .WIRELESS_IP_ADDR0  = 192,
    .WIRELESS_IP_ADDR1  = 168,
    .WIRELESS_IP_ADDR2  = 10,
#ifdef WIFI_RAW_RX_DEV
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
    .WIRELESS_GATEWAY2  = 10,
    .WIRELESS_GATEWAY3  = 1,

    .SERVER_IPADDR1  = 192,
    .SERVER_IPADDR2  = 168,
    .SERVER_IPADDR3  = 10,
    .SERVER_IPADDR4  = 1,

    .CLIENT_IPADDR1  = 192,
    .CLIENT_IPADDR2  = 168,
    .CLIENT_IPADDR3  = 10,
    .CLIENT_IPADDR4  = 2,

    .SUB_NET_MASK1   = 255,
    .SUB_NET_MASK2   = 255,
    .SUB_NET_MASK3   = 255,
    .SUB_NET_MASK4   = 0,
};


static struct server *ctp = NULL;
static struct ctp_server_info server_info = {
    .ctp_vaild = true,
    .ctp_port = CTP_CTRL_PORT,
    .cdp_vaild = true,
    .cdp_port = CDP_CTRL_PORT,
    .k_alive_type = CTP_ALIVE,
    /* .k_alive_type = NOT_USE_ALIVE, */
    /*.k_alive_type = CDP_ALIVE,*/
};


static void wifi_ap_mode_init(void);
static void wifi_raw_mode_init(void);
static int wifi_event_callback(void *network_ctx, enum WIFI_EVENT event);

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


static void config_pkg_head(u8 *src_mac, u8 *dest_mac)
{
    //设置发送包的802.11头部信息, 设置源mac， 目标mac， seq号等信息
    phead_802_11 pHdr = wifi_get_wifi_send_pkg_ptr() + HEAD_802_11_OFFSET;
    memcpy(pHdr->addr1, dest_mac, 6);           //dest
    memcpy(pHdr->addr2, src_mac, 6);            //src
#ifdef WIFI_RAW_TX_DEV
    memcpy(pHdr->addr3, src_mac, 6);           //bssid = src
#else
    memcpy(pHdr->addr3, dest_mac, 6);           //bssid = dest
#endif
    pHdr->frag = 8;
}

void wifi_ap_raw_init(void)
{
    const char WIFI_PA_ENABLE;
    if (WIFI_PA_ENABLE) {
        wifi_set_pwr(6);
    }

#ifdef WIFI_RAW_TX_DEV
    wifi_ap_mode_init();
#endif

    wifi_raw_mode_init();

}

#if defined(WIFI_RAW_RX_DEV) || defined(WIFI_RAW_TX_DEV)
late_initcall(wifi_ap_raw_init);
#endif

static void wifi_raw_mode_init(void)
{
    printf("\n========== WiFi Raw Init ==========\n");

#ifdef WIFI_RAW_TX_DEV
    u8 src_mac[6] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};        //与wifi_conf.c MacAddress 对应
    u8 dest_mac[6] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66};

    lwip_set_lan_info(&lan_setting_info);

    //lwip netif 软件mac地址过滤
    wifi_raw_set_mac(src_mac);

    //lwip网卡初始化
    Init_LwIP(WIFI_RAW_NETIF);
    lwip_netif_set_up(WIFI_RAW_NETIF);

    config_pkg_head(src_mac, dest_mac);

    //信道与wifi_conf.c对应
    /* wifi_set_channel(12); */

    lwip_etharp_add_static_entry("192.168.10.1", dest_mac);
#else
    //与TX_DEV相反
    u8 src_mac[6] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66};
    u8 dest_mac[6] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};

    lwip_set_lan_info(&lan_setting_info);

    //lwip netif 软件mac地址过滤
    wifi_raw_set_mac(src_mac);

    wifi_raw_on(1);

    config_pkg_head(src_mac, dest_mac);

    filt_pack_not_need();

    //设置硬件bssid过滤
    wf_asic_set_bssid(dest_mac);
    filt_not_my_bssid();

    //设置本机硬件MAC, 需要在wifi_raw_on后调用
    wf_asic_set_mac(src_mac);

    //配置WIFI RF 通信信道
    wifi_set_channel(12);

    //配置底层重传次数
    wifi_set_long_retry(2);
    wifi_set_short_retry(2);

    lwip_etharp_add_static_entry("192.168.10.2", dest_mac);
#endif
}


static void wifi_ap_mode_init(void)
{
    printf("\n========== WiFi AP Init ==========\n");

    wifi_set_event_callback(wifi_event_callback);
    wifi_on();

    ctp_server_init();
}



static int wifi_connect_sta_mac(int offset, u8 *mac, int len, int index)//存储、查找、删除连接的STA设备的mac
{
    static u8 store_mac[6 * 5] = {0};
    int i;
    offset = offset < sizeof(store_mac) ? offset : sizeof(store_mac);
    for (i = offset; i < sizeof(store_mac); i += 6) { //只支持6个mac地址
        if (index == 0) { //写入
            if (store_mac[i] == 0 || !memcmp(&store_mac[i], mac, len)) {
                memcpy(&store_mac[i], mac, len);
                break;
            }
        } else if (index == 1) { //读取
            if (store_mac[i] != 0) {
                memcpy(mac, &store_mac[i], len);
                return i + len;
            }
        } else if (index == 2) { //清空
            if (!memcmp(&store_mac[i], mac, len)) {
                memset(&store_mac[i], 0, len);
                break;
            }
        }
    }
    return 0;
}

static int wifi_event_callback(void *network_ctx, enum WIFI_EVENT event)
{
    int ret = 0;

    switch (event) {

    case WIFI_EVENT_MODULE_INIT:
        puts("|network_user_callback->WIFI_EVENT_MODULE_INIT\n");
        wifi_set_smp_cfg_timeout(30);       //配置MONITOR模式超时后事件回调通知时间

        struct wifi_store_info wifi_default_mode_parm = {0};
        wifi_default_mode_parm.mode = AP_MODE;
        strcpy(wifi_default_mode_parm.ssid[wifi_default_mode_parm.mode - STA_MODE], DEMO_AP_MODE_SSID);
        strcpy(wifi_default_mode_parm.pwd[wifi_default_mode_parm.mode - STA_MODE], DEMO_AP_MODE_PWD);

        wifi_set_default_mode(&wifi_default_mode_parm, 1, 1);
        break;

    case WIFI_EVENT_MODULE_START:
        if (!get_MassProduction()) {
            u32  tx_rate_control_tab = // 不需要哪个速率就删除掉,可以动态设定
                0
                | BIT(6) //6:CCK 11M
                ;
            wifi_set_tx_rate_control_tab(tx_rate_control_tab);
        }
        break;
    case WIFI_EVENT_MODULE_STOP:
        puts("|network_user_callback->WIFI_EVENT_MODULE_STOP\n");
        break;
    case WIFI_EVENT_AP_START:
        printf("|network_user_callback->WIFI_EVENT_AP_START,CH=%d\n", wifi_get_channel());
        break;
    case WIFI_EVENT_AP_STOP:
        puts("|network_user_callback->WIFI_EVENT_AP_STOP\n");
        break;
    case WIFI_EVENT_STA_START:
        puts("|network_user_callback->WIFI_EVENT_STA_START\n");
        break;
    case WIFI_EVENT_MODULE_START_ERR:
        puts("|network_user_callback->WIFI_EVENT_MODULE_START_ERR\n");
        break;
    case WIFI_EVENT_STA_STOP:
        puts("|network_user_callback->WIFI_EVENT_STA_STOP\n");
        break;
    case WIFI_EVENT_STA_DISCONNECT:
        puts("|network_user_callback->WIFI_STA_DISCONNECT\n");
        break;
    case WIFI_EVENT_STA_SCAN_COMPLETED:
        puts("|network_user_callback->WIFI_STA_SCAN_COMPLETED\n");
        break;
    case WIFI_EVENT_STA_CONNECT_SUCC:
        printf("|network_user_callback->WIFI_STA_CONNECT_SUCC,CH=%d\r\n", wifi_get_channel());
        break;
    case WIFI_EVENT_MP_TEST_START:
        puts("|network_user_callback->WIFI_EVENT_MP_TEST_START\n");
        break;
    case WIFI_EVENT_MP_TEST_STOP:
        puts("|network_user_callback->WIFI_EVENT_MP_TEST_STOP\n");
        break;
    case WIFI_EVENT_STA_CONNECT_TIMEOUT_NOT_FOUND_SSID:
        puts("|network_user_callback->WIFI_STA_CONNECT_TIMEOUT_NOT_FOUND_SSID\n");
        break;
    case WIFI_EVENT_STA_CONNECT_ASSOCIAT_FAIL:
        puts("|network_user_callback->WIFI_STA_CONNECT_ASSOCIAT_FAIL .....\n");
        break;
    case WIFI_EVENT_STA_CONNECT_ASSOCIAT_TIMEOUT:
        puts("|network_user_callback->WIFI_STA_CONNECT_ASSOCIAT_TIMEOUT .....\n");
        break;
    case WIFI_EVENT_STA_NETWORK_STACK_DHCP_SUCC:
        puts("|network_user_callback->WIFI_EVENT_STA_NETWPRK_STACK_DHCP_SUCC\n");
        break;
    case WIFI_EVENT_STA_NETWORK_STACK_DHCP_TIMEOUT:
        puts("|network_user_callback->WIFI_EVENT_STA_NETWPRK_STACK_DHCP_TIMEOUT\n");
        break;
    case WIFI_EVENT_P2P_START:
        puts("|network_user_callback->WIFI_EVENT_P2P_START\n");
        break;
    case WIFI_EVENT_P2P_STOP:
        puts("|network_user_callback->WIFI_EVENT_P2P_STOP\n");
        break;
    case WIFI_EVENT_P2P_GC_DISCONNECTED:
        puts("|network_user_callback->WIFI_EVENT_P2P_GC_DISCONNECTED\n");
        break;
    case WIFI_EVENT_P2P_GC_NETWORK_STACK_DHCP_SUCC:
        puts("|network_user_callback->WIFI_EVENT_P2P_GC_NETWORK_STACK_DHCP_SUCC\n");
        break;
    case WIFI_EVENT_P2P_GC_NETWORK_STACK_DHCP_TIMEOUT:
        puts("|network_user_callback->WIFI_EVENT_P2P_GC_NETWORK_STACK_DHCP_TIMEOUT\n");
        break;
    case WIFI_EVENT_SMP_CFG_START:
        puts("|network_user_callback->WIFI_EVENT_SMP_CFG_START\n");
        break;
    case WIFI_EVENT_SMP_CFG_STOP:
        puts("|network_user_callback->WIFI_EVENT_SMP_CFG_STOP\n");
        break;
    case WIFI_EVENT_SMP_CFG_TIMEOUT:
        puts("|network_user_callback->WIFI_EVENT_SMP_CFG_TIMEOUT\n");
        break;
    case WIFI_EVENT_SMP_CFG_COMPLETED:
        puts("|network_user_callback->WIFI_EVENT_SMP_CFG_COMPLETED\n");
        break;
    case WIFI_EVENT_PM_SUSPEND:
        puts("|network_user_callback->WIFI_EVENT_PM_SUSPEND\n");
        break;
    case WIFI_EVENT_PM_RESUME:
        puts("|network_user_callback->WIFI_EVENT_PM_RESUME\n");
        break;
    case WIFI_EVENT_AP_ON_ASSOC:
#ifdef TCFG_WIFI_ENABLE
        lwip_set_default_netif(WIFI_NETIF);   //设置本地网卡为默认模块,兼容双网卡
#endif
        struct eth_addr *hwaddr = (struct eth_addr *)network_ctx;
        printf("WIFI_EVENT_AP_ON_ASSOC hwaddr = %02x:%02x:%02x:%02x:%02x:%02x \r\n\r\n",
               hwaddr->addr[0], hwaddr->addr[1], hwaddr->addr[2], hwaddr->addr[3], hwaddr->addr[4], hwaddr->addr[5]);
        wifi_connect_sta_mac(0,  hwaddr->addr, 6, 0);//存储mac
        break;
    case WIFI_EVENT_AP_ON_DISCONNECTED:
        hwaddr = (struct eth_addr *)network_ctx;
        struct ip4_addr ipaddr;
        dhcps_get_ipaddr(hwaddr->addr, &ipaddr);
        printf("WIFI_EVENT_AP_ON_DISCONNECTED hwaddr = %02x:%02x:%02x:%02x:%02x:%02x, ipaddr = [%d.%d.%d.%d] \r\n\r\n",
               hwaddr->addr[0], hwaddr->addr[1], hwaddr->addr[2], hwaddr->addr[3], hwaddr->addr[4], hwaddr->addr[5],
               ip4_addr1(&ipaddr), ip4_addr2(&ipaddr), ip4_addr3(&ipaddr), ip4_addr4(&ipaddr));
        ctp_keep_alive_find_dhwaddr_disconnect((struct eth_addr *)hwaddr->addr);
        cdp_keep_alive_find_dhwaddr_disconnect((struct eth_addr *)hwaddr->addr);
        wifi_connect_sta_mac(0,  hwaddr->addr, 6, 2);//清空mac
        break;
    case WIFI_EVENT_STA_IP_GOT_IPV6_SUCC:
        puts("network_user_callback->WIFI_EVENT_STA_IP_GOT_IPV6_SUCC");
        break;
    default:
        break;
    }

    return ret;
}

static int ctp_server_init(void)
{
    ctp = server_open("ctp_server", (void *)&server_info);
    if (!ctp) {
        printf("ctp server fail\n");
    }

    extern int http_virfile_reg(const char *path, const char *contents, unsigned long len);
    http_virfile_reg(DEV_DESC_PATH, DEV_DESC_CONTENT, strlen(DEV_DESC_CONTENT));

    http_get_server_init(HTTP_PORT); //8080
    video_rt_tcp_server_init(2229);
#ifdef CONFIG_ENABLE_VLIST
    preview_init(VIDEO_PREVIEW_PORT, NULL); //2226
    playback_init(VIDEO_PLAYBACK_PORT, NULL);
#endif
}




