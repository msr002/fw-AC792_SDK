#include <stdio.h>
#include "lvgl.h"
#include "gui_guider.h"

#if defined CONFIG_NET_ENABLE
#include "net/wifi/wifi_connect.h"
#endif

#if !LV_USE_GUIBUILDER_SIMULATOR
#include "ui.h"
#endif

void gui_connect_wifi(char *ssid, char *pwd)
{
    printf("ssid :%s  pwd: %s \n", ssid, pwd);
#if LV_USE_GUIBUILDER_SIMULATOR

#else
#if defined CONFIG_NET_ENABLE
    printf("-----ssid :%s pwd: %s -----\n", ssid, pwd);
    wifi_enter_sta_mode(ssid, pwd);
    wifi_store_mode_info(STA_MODE, ssid, pwd);
#endif
#endif
}


