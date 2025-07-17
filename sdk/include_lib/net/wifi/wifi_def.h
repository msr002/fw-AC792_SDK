#ifndef _WIFI_DEF_H_
#define _WIFI_DEF_H_

typedef enum _WIFI_802_11_AUTH_MODE {
    WIFI_AUTH_MODE_OPEN,
    WIFI_AUTH_MODE_WEP,
    WIFI_AUTH_MODE_WAPI,
    WIFI_AUTH_MODE_WPA,
    WIFI_AUTH_MODE_WPA2PSK,
    WIFI_AUTH_MODE_WPAWPA2PSK,
    WIFI_AUTH_MODE_WPA3SAE,
    WIFI_AUTH_MODE_WPA2PSKWPA3SAE,
    WIFI_AUTH_MODE_WPA3H2E,
} WIFI_802_11_AUTH_MODE;

struct wifi_scan_ssid_info {
    char ssid[32];
    unsigned int ssid_len;
    unsigned char mac_addr[6];
    char rssi;
    char snr;
    char rssi_db;
    char rssi_rsv;
    unsigned int channel_number;
    unsigned char	SignalStrength;//(in percentage)
    unsigned char	SignalQuality;//(in percentage)
    unsigned char   SupportedRates[16];
    WIFI_802_11_AUTH_MODE auth_mode;
};

#endif
