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
#include "system/timer.h"
#include "asm/debug.h"
#include "app_config.h"
#include "wifi_adapter.h"
#include "flash_index_config.h"

#define LOG_TAG_CONST       WIFI_RAW
#define LOG_TAG             "[WIFI_RAW]"
#define LOG_ERROR_ENABLE
#define LOG_INFO_ENABLE
#define LOG_DUMP_ENABLE
#include "debug.h"

#define WIFI_RAW_SRC_MAC       "02:12:34:56:78:90"
#define WIFI_RAW_DST_MAC       "02:12:34:56:78:90"
#define WIFI_RAW_BSSID         "02:12:34:56:78:90"
#define WIFI_RAW_CHANNEL        13                  // WiFi信道
#define WIFI_RAW_SHORT_RETRY    2                   // 短包重传次数
#define WIFI_RAW_LONG_RETRY     1                   // 长包重传次数
#define HEAD_802_11_OFFSET      20                  // 802.11头部偏移

#if BBM_WIFI_PA_ENABLE
#define WIFI_MAX_PWR            6                   // 最大发射功率
#else
#define WIFI_MAX_PWR            9                   // 最大发射功率
#endif

typedef struct _head_802_11 {
    unsigned short  fc;
    unsigned short  duration;
    unsigned char   addr1[6];
    unsigned char   addr2[6];
    unsigned char	addr3[6];
    unsigned short	frag: 4;
    unsigned short	sequence: 12;
    unsigned char 	data[0];
} head_802_11, *phead_802_11;

static u16 wifi_raw_info_timer;

static void lwip_set_lan_info(void);
static void wifi_raw_info_timer_cb(void *priv);

void wifi_config_pkg_head(u8 *src_mac, u8 *dest_mac, u8 *bssid_mac)
{
    //设置发送包的802.11头部信息, 设置源mac， 目标mac， seq号等信息
    phead_802_11 pHdr = wifi_get_wifi_send_pkg_ptr() + HEAD_802_11_OFFSET;
    memcpy(pHdr->addr1, dest_mac, 6);
    memcpy(pHdr->addr2, src_mac, 6);
    memcpy(pHdr->addr3, bssid_mac, 6);
    pHdr->frag = 8;
    pHdr->sequence = 0;
}



void wifi_raw_init(void)
{
    log_info("\n========== WiFi Raw Init ==========\n");
    //配置LWIP IP信息
    lwip_set_lan_info();

    //设置软件MAC过滤地址
    wifi_raw_set_mac(WIFI_RAW_SRC_MAC);

    //启动wifi_raw
    wifi_raw_on(1);
    lwip_set_default_netif(WIFI_RAW_NETIF);
    //设置信道
    wifi_set_channel(WIFI_RAW_CHANNEL);

    //配置底层重传次数
    wifi_set_short_retry(WIFI_RAW_SHORT_RETRY);
    wifi_set_long_retry(WIFI_RAW_LONG_RETRY);

    //设置传输速率
    wifi_raw_set_txrate(WIFI_TXRATE_11M);

    //过滤掉一些不用的包
    filt_pack_not_need();

    //配置RAW头部信息
    wifi_config_pkg_head((u8 *)WIFI_RAW_SRC_MAC, (u8 *)WIFI_RAW_DST_MAC, (u8 *)WIFI_RAW_BSSID);

    //设置硬件bssid过滤
    wf_asic_set_bssid(WIFI_RAW_BSSID);
    filt_not_my_bssid();

    //设置本机硬件MAC, 需要在wifi_raw_on后调用
    wf_asic_set_mac((u8 *)WIFI_RAW_SRC_MAC);

    //设置WIFI发射功率
    wifi_set_pwr(WIFI_MAX_PWR);

    wifi_raw_info_timer = sys_timer_add(NULL, wifi_raw_info_timer_cb, 1000);
}

void wifi_raw_exit(void)
{
    log_info("\n========== WiFi Raw Exit ==========\n");

    if (wifi_raw_info_timer) {
        sys_timer_del(wifi_raw_info_timer);
        wifi_raw_info_timer = 0;
    }

    wifi_raw_off();
    wifi_set_frame_cb(NULL, NULL);  //取消底层数据接收回调注册
    lwip_netif_remove(WIFI_RAW_NETIF);
}

static void wifi_raw_info_timer_cb(void *priv)
{
    static u8 cnt = 0;

    //内存统计
    if (++cnt == 5) {
        cnt = 0;
        malloc_stats();
    }

    //接收信号强度
    char rssi = wifi_raw_rssi_get();

    //WIFI发送情况
    extern void wifi_get_tx_stats(u32 * TxRetransmit, u32 * TxSuccess, u32 * TxFailCount);
    u32 retry, succ, fail;
    wifi_get_tx_stats(&retry, &succ, &fail);

    log_debug("rssi:%d retry:%d succ:%d fail:%d \n", rssi, retry, succ, fail);
}

static int get_ip_addr_from_flash(u8 *ip_addr)
{
    int ret;
    ret = syscfg_read(WIFI_RAW_IP_ADDR_INDEX, ip_addr, 4);
    if (ret != 4) {
        log_error("read wifi raw ip addr from flash err :%d \n", ret);
        return -1;
    }
    return 0;
}

static int save_ip_addr_to_flash(u8 *ip_addr)
{
    int ret;
    ret = syscfg_write(WIFI_RAW_IP_ADDR_INDEX, ip_addr, 4);
    if (ret != 4) {
        log_error("write wifi raw ip addr to flash err :%d \n", ret);
        return -1;
    }
    return 0;
}

static void generate_random_ip_addr(u8 *ip_addr)
{
    ip_addr[0] = 192;
    ip_addr[1] = rand32();
    ip_addr[2] = rand32();
    ip_addr[3] = rand32();
}


static void lwip_set_lan_info(void)
{
    struct lan_setting *lan_setting_info = net_get_lan_info(WIFI_RAW_NETIF);
    if (!lan_setting_info) {
        log_error("get lan setting info err \n");
        return;
    }
    u8 ip_addr[4];
    if (get_ip_addr_from_flash(ip_addr) != 0) {
        // flash中没有存储IP地址，生成一个随机IP地址并保存到flash
        generate_random_ip_addr(ip_addr);
        save_ip_addr_to_flash(ip_addr);
    }

    lan_setting_info->WIRELESS_IP_ADDR0  = ip_addr[0];
    lan_setting_info->WIRELESS_IP_ADDR1  = ip_addr[1];
    lan_setting_info->WIRELESS_IP_ADDR2  = ip_addr[2];
    lan_setting_info->WIRELESS_IP_ADDR3  = ip_addr[3];

    lan_setting_info->WIRELESS_NETMASK0  = 0;
    lan_setting_info->WIRELESS_NETMASK1  = 0;
    lan_setting_info->WIRELESS_NETMASK2  = 0;
    lan_setting_info->WIRELESS_NETMASK3  = 0;

    lan_setting_info->WIRELESS_GATEWAY0  = 0;
    lan_setting_info->WIRELESS_GATEWAY1  = 0;
    lan_setting_info->WIRELESS_GATEWAY2  = 0;
    lan_setting_info->WIRELESS_GATEWAY3  = 0;

    lan_setting_info->SERVER_IPADDR1     = 0;
    lan_setting_info->SERVER_IPADDR2     = 0;
    lan_setting_info->SERVER_IPADDR3     = 0;
    lan_setting_info->SERVER_IPADDR4     = 0;

    lan_setting_info->CLIENT_IPADDR1     = 0;
    lan_setting_info->CLIENT_IPADDR2     = 0;
    lan_setting_info->CLIENT_IPADDR3     = 0;
    lan_setting_info->CLIENT_IPADDR4     = 0;

    lan_setting_info->SUB_NET_MASK1      = 0;
    lan_setting_info->SUB_NET_MASK2      = 0;
    lan_setting_info->SUB_NET_MASK3      = 0;
    lan_setting_info->SUB_NET_MASK4      = 0;

    log_debug("wifi raw ip:%d.%d.%d.%d \n",
              lan_setting_info->WIRELESS_IP_ADDR0,
              lan_setting_info->WIRELESS_IP_ADDR1,
              lan_setting_info->WIRELESS_IP_ADDR2,
              lan_setting_info->WIRELESS_IP_ADDR3
             );
}

