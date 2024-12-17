//硬件过滤特定包
#include "system/includes.h"
#include "wifi/wifi_connect.h"
#include "event/net_event.h"
#include "wifi_adapter.h"

//example
void filt_not_my_bssid(void)
{
    wf_rx_filt_set(DROP_NOT_MYBSS);
}

//example
void filt_pack_not_need(void)
{
    wf_rx_filt_set(DROP_CRC_ERR | DROP_PHY_ERR | DROP_DUPL  \
                   | DROP_CFACK | DROP_CFEND | DROP_CTS | DROP_PSPOLL | DROP_RTS | DROP_BA | DROP_BAR | DROP_CTRL_RSV);
}




