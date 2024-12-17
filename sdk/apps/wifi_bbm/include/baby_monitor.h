#ifndef __BABY_MONITOR_H
#define __BABY_MONITOR_H

#include "system/includes.h"
#include "app_config.h"

struct net_ctp_thumb {
    int start_index;
    int file_num;
    u8 **file_buf_list;
    int *file_buf_len_list;
    OS_SEM sem;
};










#endif /* __BABY_MONITOR_H */

