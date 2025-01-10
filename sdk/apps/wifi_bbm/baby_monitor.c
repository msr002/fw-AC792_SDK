#include "system/includes.h"
#include "action.h"
#include "app_config.h"
#include "generic/log.h"
#include "event/key_event.h"
#include "lcd_config.h"
#include "net_event.h"
#include "udp_multicast.h"
#include "pairing_data_model.h"
#include "arp_static_table.h"
#include "baby_monitor.h"

#define DEVICE_ONLINE_TIMEOUT   2000            //设备在线超时时间

#define MAX_PAIR_NUM    MAX_ARP_STATIC_ENTRY    //最大配对数量
#define MIN_PAIR_CH     0                       //0
#define MAX_PAIR_CH     (MAX_PAIR_NUM - 1)      //6

enum {
    BBM_TX_OFFLINE = 0,
    BBM_TX_ONLINE,
};

enum {
    BBM_RT_STOP = 100,
    BBM_RT_RESET,
    BBM_RT_START,
};

enum {
    BBM_MODE_IDLE = 0,
    BBM_MODE_STREAM = 10,
    BBM_MODE_FILE_BROWSER,
    BBM_MODE_VIDEO_PLAY,
};


struct wifi_bbm_hdl {
    u8 online_table[MAX_PAIR_NUM];          //设备在线表
    u8 online_dev_cnt;                      //设备当前在线数量
    u32 online_cnt_table[MAX_PAIR_NUM];     //设备在线包计数
    u32 online_timeout[MAX_PAIR_NUM];       //设备超时定时器
    int cur_channel;                        //当前通讯通道
    int last_opened_ch;                     //上一次开启的通道
    u8 bbm_cur_mode;                        //当前模式,实时流/文件预览/视频文件播放

    struct bbm_client_hdl *bbm_client_hdl[MAX_PAIR_NUM];        //设备client管理句柄
};
static struct wifi_bbm_hdl bbm_hdl;
#define __this (&bbm_hdl)

static int bbm_get_file_num(int ch, int *num)
{
    if (!__this->bbm_client_hdl[ch]) {
        printf("client hdl invalid \n");
        return -1;
    }

    int total_num = __this->bbm_client_hdl[ch]->file_total_num;

    *num = total_num;

    if (!total_num) {
        printf("file total num 0 \n");
        return -1;
    }

    return 0;
}

static int bbm_get_file_name_list(int ch, char ***list)
{
    if (!__this->bbm_client_hdl[ch]) {
        printf("client hdl invalid \n");
        return -1;
    }

    char **name_list  = __this->bbm_client_hdl[ch]->file_name_list;

    *list = name_list;

    if (!name_list) {
        printf("file list is null !\n");
        return -1;
    }

    return 0;
}


static int find_next_camera(int ch)
{
    int find_ch = ch;
    do {
        find_ch++;
        if (find_ch > MAX_PAIR_CH) {
            find_ch = MIN_PAIR_CH;
        }

        //遍历了一圈没有找到可以用设备
        if (ch == find_ch) {
            printf("no available dev \n ");
            return -1;
        }

        if (__this->online_table[find_ch] == BBM_TX_ONLINE) {
            return find_ch;
        }
    } while (1);
}

static int find_any_online_camera(void)
{
    int ch;
    for (ch = 0; ch < MAX_PAIR_NUM; ch++) {
        if (__this->online_table[ch] == BBM_TX_ONLINE) {
            return ch;
        }
    }
    printf("no online camera device \n");
    return -1;
}

static int bbm_reset_camera_pipe_by_ch(int ch, int disp_mode)
{
    printf("rt stream reset:%d mode:%d \n", ch, disp_mode);
    int ret;

    ret = bbm_rt_stream_reset_pipe(__this->bbm_client_hdl[ch]->ctp_cli_hdl, disp_mode);
    if (ret) {
        printf("ch:%d rt stream start err\n", ch);
        return -1;
    }

    return 0;
}

static int bbm_start_camera_by_ch(int ch, int disp_mode)
{
    printf("rt stream start:%d mode:%d \n", ch, disp_mode);
    int ret;

    ret = bbm_ctp_rt_start(__this->bbm_client_hdl[ch]->ctp_cli_hdl, disp_mode);
    if (ret) {
        printf("ch:%d rt stream start err\n", ch);
        return -1;
    }
    __this->cur_channel |= BIT(ch);

    return 0;
}

static int bbm_stop_camera_by_ch(int ch)
{
    printf("rt stream stop:%d \n", ch);
    int ret;

    ret = bbm_ctp_rt_stop(__this->bbm_client_hdl[ch]->ctp_cli_hdl);
    if (ret) {
        printf("ch:%d rt stream stop err\n", ch);
        return -1;
    }
    __this->cur_channel &= ~BIT(ch);

    return 0;
}

static int bbm_start_thumb_by_ch(int ch)
{
    printf("file thumb start:%d \n", ch);
    int ret;

    ret = ctp_file_thumb_start(__this->bbm_client_hdl[ch]);
    if (ret) {
        printf("ch:%d file thumb start err\n", ch);
        return -1;
    }
    __this->cur_channel |= BIT(ch);

    return 0;
}

static int bbm_stop_thumb_by_ch(int ch)
{
    printf("rt thumb stop:%d \n", ch);
    int ret;

    ret = ctp_file_thumb_stop(__this->bbm_client_hdl[ch]);
    if (ret) {
        printf("ch:%d thumb stop err\n", ch);
        return -1;
    }
    __this->cur_channel &= ~BIT(ch);

    return 0;
}

static int bbm_start_file_play_by_ch(int ch, int arg)
{
    printf("file play start:%d \n", ch);
    int ret;

    ret = ctp_file_play_start(__this->bbm_client_hdl[ch], arg);
    if (ret) {
        printf("ch:%d file play start err\n", ch);
        return -1;
    }
    __this->cur_channel |= BIT(ch);

    return 0;
}

static int bbm_switch_file_play_by_ch(int ch, int arg)
{
    printf("file play switch:%d \n", ch);
    int ret;

    ret = ctp_file_play_switch(__this->bbm_client_hdl[ch], arg);
    if (ret) {
        printf("ch:%d file play start err\n", ch);
        return -1;
    }
    __this->cur_channel |= BIT(ch);

    return 0;
}

static int bbm_stop_file_play_by_ch(int ch)
{
    printf("rt play stop:%d \n", ch);
    int ret;

    ret = ctp_file_play_stop(__this->bbm_client_hdl[ch]);
    if (ret) {
        printf("ch:%d file play stop err\n", ch);
        return -1;
    }
    __this->cur_channel &= ~BIT(ch);

    return 0;
}

static int bbm_stop_file_play_all(void)
{
    int ret = 0;
    int ch;

    for (ch = 0; ch < MAX_PAIR_NUM; ch++) {
        if (__this->cur_channel & BIT(ch)) {
            ret = bbm_stop_file_play_by_ch(ch);
        }
    }

    return ret;
}

static int bbm_stop_thumb_all(void)
{
    int ret = 0;
    int ch;

    for (ch = 0; ch < MAX_PAIR_NUM; ch++) {
        if (__this->cur_channel & BIT(ch)) {
            ret = bbm_stop_thumb_by_ch(ch);
        }
    }

    return ret;
}


static int bbm_stop_camera_all(void)
{
    int ret;
    int ch;

    for (ch = 0; ch < MAX_PAIR_NUM; ch++) {
        if (__this->cur_channel & BIT(ch)) {
            printf("rt stream stop:%d \n", ch);
            ret = bbm_ctp_rt_stop(__this->bbm_client_hdl[ch]->ctp_cli_hdl);
            if (ret) {
                printf("ch:%d rt stream stop err\n", ch);
                continue;
            }
            __this->cur_channel &= ~BIT(ch);
        }
    }
    return 0;
}


static int bbm_switch_camera(void)
{
    int ret = -1;
    int ch;
    int i;
    int stop_num = 0;
    int start_ch[2] = {-1, -1};
    int cmd[2] = {-1, -1};
    int win_mode[2] = {0, 0};

    for (ch = 0; ch < MAX_PAIR_NUM; ch++) {
        if (__this->cur_channel & BIT(ch)) {
            start_ch[stop_num] = ch;
            stop_num++;
        }
    }

    if (stop_num == 2) {

        for (i = 0; i < ARRAY_SIZE(start_ch); i++) {
            if (start_ch[i] == __this->last_opened_ch) {
                cmd[i] = BBM_RT_RESET;
                win_mode[i] = RT_DISP_WIN_MAIN;
            } else {
                cmd[i] = BBM_RT_STOP;
            }
        }

    } else if (stop_num == 1) {
        if (__this->online_dev_cnt < 2) {
            cmd[0] = BBM_RT_RESET;
            win_mode[0] = RT_DISP_WIN_MAIN;
            __this->last_opened_ch = start_ch[0];
            /*             cmd[0] = BBM_RT_STOP; */

            /* start_ch[1] = find_any_online_camera(); */
            /* cmd[1] = BBM_RT_START; */
            /* win_mode[1] = RT_DISP_WIN_MAIN; */
        } else {
            start_ch[0] = __this->last_opened_ch;
            cmd[0] = BBM_RT_RESET;
            win_mode[0] = RT_DISP_WIN_LEFT;

            start_ch[1] = find_next_camera(__this->last_opened_ch);
            cmd[1] = BBM_RT_START;
            win_mode[1] = RT_DISP_WIN_RIGHT;
        }

    } else {
        start_ch[0] = find_any_online_camera();
        cmd[0] = BBM_RT_START;
        win_mode[0] = RT_DISP_WIN_MAIN;
    }

    ret = 0;

    for (i = 0; i < ARRAY_SIZE(start_ch); i++) {
        if (start_ch[i] >= 0) {
            if (cmd[i] == BBM_RT_START) {
                ret = bbm_start_camera_by_ch(start_ch[i], win_mode[i]);
                if (ret) {
                    break;
                }
                __this->last_opened_ch = start_ch[i];
            } else if (cmd[i] == BBM_RT_RESET) {
                ret = bbm_reset_camera_pipe_by_ch(start_ch[i], win_mode[i]);
                if (ret) {
                    break;
                }
                /* __this->last_opened_ch = start_ch[i]; */
            } else {
                ret = bbm_stop_camera_by_ch(start_ch[i]);
                if (ret) {
                    break;
                }
            }

        }
    }

    return ret;

}

static int bbm_quit_cur_mode(void)
{
    int ret = 0;

    switch (__this->bbm_cur_mode) {
    case BBM_MODE_STREAM:
        ret = bbm_stop_camera_all();
        bbm_rt_stream_exit();
        break;
    case BBM_MODE_FILE_BROWSER:
        ret = bbm_stop_thumb_all();
        break;
    case BBM_MODE_VIDEO_PLAY:
        ret = bbm_stop_file_play_all();
        ctp_file_play_exit();
        break;
    case BBM_MODE_IDLE:
        printf("bbm cur mode is idle \n");
        //nothing
        break;
    default:
        printf("Unknow cur mode \n");
        break;
    }
    if (ret) {
        printf("bbm quit cur mode err\n");
        return -1;
    }

    __this->bbm_cur_mode = BBM_MODE_IDLE;
    return 0;
}

static int bbm_enter_mode(u8 mode, int ch, int arg)
{
    int ret;
    switch (mode) {
    case BBM_MODE_STREAM:
        bbm_rt_stream_init();
        ret = bbm_switch_camera();
        if (__this->online_dev_cnt > 1) {
            post_stream_msg_to_ui("show switch btn");
        } else {
            post_stream_msg_to_ui("hide switch btn");
        }
        break;
    case BBM_MODE_FILE_BROWSER:
        ret = bbm_start_thumb_by_ch(ch);
        break;
    case BBM_MODE_VIDEO_PLAY:
        ctp_file_play_init();
        ret = bbm_start_file_play_by_ch(ch, arg);
        break;
    case BBM_MODE_IDLE:
        //nothing
        break;
    default:
        printf("Unknow cur mode \n");
        break;
    }

    __this->bbm_cur_mode = mode;

    return ret;
}

static int bbm_switch_mode(u8 mode, int ch, int arg)
{
    int ret = -1;

    if (__this->bbm_cur_mode == mode) {
        printf("cur mode is %d . no switch \n", mode);
        //TODO
        if (__this->bbm_cur_mode == BBM_MODE_STREAM) {
            //nothing
            return 0;
        } else if (__this->bbm_cur_mode == BBM_MODE_FILE_BROWSER) {
            if (__this->cur_channel & BIT(ch)) {
                printf("ch %d no need reopen\n", ch);
            } else {
                bbm_start_thumb_by_ch(ch);
            }
            return 0;
        }
    }

    ret = bbm_quit_cur_mode();

    ret = bbm_enter_mode(mode, ch, arg);

    return ret;
}


static int bbm_tx_offline(void *priv)
{
    int ret;
    int ch = (int)priv;

    if (__this->online_table[ch] == BBM_TX_OFFLINE) {
        printf("device already offline \n");
        return 0;
    }

    //标记不在线
    __this->online_table[ch] = BBM_TX_OFFLINE;
    __this->online_cnt_table[ch] = 0;
    __this->online_dev_cnt--;

    //log
    struct arp_entry_t *arp_entry = get_arp_static_entry_by_id(ch);
    printf("ch:%d ip:%s not online ! ", ch, inet_ntoa(arp_entry->ipaddr));

    if (__this->online_timeout[ch]) {
        sys_timeout_del(__this->online_timeout[ch]);
        __this->online_timeout[ch] = 0;
    }

    switch (__this->bbm_cur_mode) {
    case BBM_MODE_STREAM:
        if (__this->online_dev_cnt < 2) {
            post_stream_msg_to_ui("hide switch btn");
        }
        if (__this->cur_channel & BIT(ch)) {
            bbm_stop_camera_by_ch(ch);

            bbm_switch_camera();
        }
        break;
    case BBM_MODE_FILE_BROWSER:
    case BBM_MODE_VIDEO_PLAY:
        post_home_msg_to_ui("back_home_page", 0);
        char *lab = "Device Not Online !";
        post_home_msg_to_ui("show_sys_prompt", lab);
        bbm_quit_cur_mode();
        break;
    case BBM_MODE_IDLE:
        break;
    }

    //ctp client退出
    bbm_ctp_client_exit(&__this->bbm_client_hdl[ch]->ctp_cli_hdl);
    free(__this->bbm_client_hdl[ch]);
    __this->bbm_client_hdl[ch] = NULL;

}

static int bbm_tx_online(int ch, u32 ip_addr)
{
    int ret;

    __this->online_dev_cnt++;
    __this->online_table[ch] = BBM_TX_ONLINE;
    printf("ch:%d online current dev num:%d \n", ch, __this->online_dev_cnt);

    __this->bbm_client_hdl[ch]  = malloc(sizeof(struct bbm_client_hdl));
    if (!__this->bbm_client_hdl[ch]) {
        printf("ch:%d bbm client malloc err \n", ch);
        goto err;
    }
    memset(__this->bbm_client_hdl[ch], 0x00, sizeof(struct bbm_client_hdl));

    ret = bbm_ctp_client_init(&__this->bbm_client_hdl[ch]->ctp_cli_hdl,
                              ip_addr, __this->bbm_client_hdl[ch]);
    if (ret) {
        goto err;
    }

    switch (__this->bbm_cur_mode) {
    case BBM_MODE_STREAM:
        if (__this->online_dev_cnt > 1 && __this->cur_channel) {
            //两个设备以上,显示切摄像头图标
            post_stream_msg_to_ui("show switch btn");
        } else {
            ret = bbm_switch_camera();
            if (ret) {
                goto err;
            }
        }
        __this->bbm_cur_mode = BBM_MODE_STREAM;
        break;
    case BBM_MODE_FILE_BROWSER:
        break;
    case BBM_MODE_VIDEO_PLAY:
        break;
    case BBM_MODE_IDLE:
        break;
    }

    return 0;

err:
    if (__this->bbm_client_hdl[ch]) {
        free(__this->bbm_client_hdl[ch]);
        __this->bbm_client_hdl[ch] = NULL;
    }

    __this->online_dev_cnt--;
    __this->online_table[ch] = BBM_TX_OFFLINE;
    return -1;
}


static int bbm_online_event_hander(struct intent *it)
{
    int ch;
    int timeout = DEVICE_ONLINE_TIMEOUT;
    u32 ip_addr = it->data;
    u32 online_cnt = it->exdata;

    for (ch = 0; ch < MAX_PAIR_NUM; ch++) {
        struct arp_entry_t *arp_entry = get_arp_static_entry_by_id(ch);

        if (arp_entry && arp_entry->ipaddr.addr == ip_addr) {

            //设备上线处理
            if (__this->online_table[ch] == BBM_TX_OFFLINE) {
                bbm_tx_online(ch, ip_addr);
            } else {
                //设备短时间内重启处理
                if (online_cnt < __this->online_cnt_table[ch]) {
                    printf("ch:%d reboot \n", ch);
                    if (__this->online_timeout[ch]) {
                        sys_timeout_del(__this->online_timeout[ch]);
                        __this->online_timeout[ch] = 0;
                    }
                    bbm_tx_offline(ch);
                }
            }

            __this->online_cnt_table[ch] = online_cnt;

            //创建超时定时器,timeout内还没收到在线时间,认为设备已下线
            //在超时定时器内标记设备下线
            if (!__this->online_timeout[ch]) {
                __this->online_timeout[ch]  = sys_timeout_add(ch, bbm_tx_offline, timeout);
            } else {
                //重置超时定时器时间
                sys_timer_modify(__this->online_timeout[ch], timeout);
            }

            break;
        }

    }

    return 0;
}

static int bbm_rx_init(void)
{
    int ret;
    int ch;

    for (ch = MIN_PAIR_CH; ch < MAX_PAIR_NUM; ch++) {
        struct arp_entry_t *arp_entry  = get_arp_static_entry_by_id(ch);
        if (arp_entry) {
            bbm_config_arp_entry(arp_entry);
            break;
        }
    }

    return 0;
}

static int state_machine(struct application *app, enum app_state state, struct intent *it)
{
    int ret = 0;
    int ch;
    int arg;
    switch (state) {
    case APP_STA_CREATE:
        log_d("\n>>>>> baby_monitor_init <<<<<\n");
        break;
    case APP_STA_START:
        if (!it) {
            break;
        }
        switch (it->action) {
        case ACTION_BBM_MAIN:
            log_d("\n>>>>>baby_monitor_main <<<<<\n");
            bbm_rx_init();
            break;
        case ACTION_BBM_START_RT:
            log_d("\n>>>>>baby_monitor start stream <<<<<\n");
            ret = bbm_switch_mode(BBM_MODE_STREAM, 0, 0);
            break;
        case ACTION_BBM_STOP_RT:
            log_d("\n>>>>>baby_monitor stop stream <<<<<\n");
            break;
        case ACTION_BBM_GET_PAIR_STATUS:
            log_d("\n>>>>>baby_monitor get pair status <<<<<\n");
            ch = it->exdata;
            it->exdata = bbm_get_pair_status(ch);
            log_d("ch:%d pair status:%d \n", ch, it->exdata);
            break;
        case ACTION_BBM_ENTER_PAIRING:
            log_d("\n>>>>>baby_monitor start pairing <<<<<\n");
            ch = it->exdata;
            bbm_set_enter_pairing(ch);
            break;
        case ACTION_BBM_EXIT_PAIRING:
            log_d("\n>>>>>baby_monitor exit pairing <<<<<\n");
            bbm_set_exit_pairing();
            break;
        case ACTION_BBM_UNPAIR:
            log_d("\n>>>>>baby_monitor start unpair <<<<<\n");
            ch = it->exdata;
            bbm_tx_offline(ch);
            bbm_set_unpair(ch);
            break;
        case ACTION_BBM_SWITCH_WIN:
            log_d("\n>>>>>baby_monitor switch win <<<<<\n");
            bbm_switch_camera();
            break;
        case ACTION_BBM_START_FILE_BROWSER:
            log_d("\n>>>>>baby_monitor start file stream <<<<<\n");
            ch = it->data;
            ret = bbm_switch_mode(BBM_MODE_FILE_BROWSER, ch, 0);
            break;
        case ACTION_BBM_STOP_FILE_BROWSER:
            log_d("\n>>>>>baby_monitor stop file stream <<<<<\n");
            break;
        case ACTION_BBM_GET_FILE_NUM:
            log_d("\n>>>>>baby_monitor get_file_browser num <<<<<\n");
            ch = it->data;
            int *num = it->exdata;
            ret = bbm_get_file_num(ch, num);
            break;
        case ACTION_BBM_GET_FILE_LIST:
            log_d("\n>>>>>baby_monitor get_file_browser list <<<<<\n");
            ch = it->data;
            char ***list = it->exdata;
            ret = bbm_get_file_name_list(ch, list);
            break;
        case ACTION_BBM_GET_FILE_THUMB_REQ:
            log_d("\n>>>>>baby_monitor get_file_browser thumb <<<<<\n");
            ch = it->data;
            struct net_ctp_thumb *thumb_data = it->exdata;
            ret = bbm_ctp_get_file_thumb(__this->bbm_client_hdl[ch], thumb_data);
            break;
        case ACTION_BBM_FILE_PLAY_START:
            log_d("\n>>>>>baby_monitor file play start <<<<<\n");
            ch = it->data;
            arg = it->exdata;
            ret = bbm_switch_mode(BBM_MODE_VIDEO_PLAY, ch, arg);
            break;
        case ACTION_BBM_FILE_PLAY_STOP:
            log_d("\n>>>>>baby_monitor file play stop <<<<<\n");
            ch = it->data;
            bbm_stop_file_play_by_ch(ch);
            break;
        case ACTION_BBM_FILE_PLAY_SWITCH:
            log_d("\n>>>>>baby_monitor file play switch <<<<<\n");
            ch = it->data;
            arg = it->exdata;
            ret = bbm_switch_file_play_by_ch(ch, arg);
            break;
        case  ACTION_BBM_ONLINE:
            bbm_online_event_hander(it);
            break;
        case ACTION_BBM_GET_ONLINE_DEV_STATUS:
            int *status = it->data;
            int i;
            for (i = 0; i < ARRAY_SIZE(__this->online_table); i++) {
                if (__this->online_table[i] == BBM_TX_ONLINE) {
                    //在线设备的ch号对应的bit位置1
                    *status |= BIT(i);
                }
            }
            break;
        }
        break;
    case APP_STA_PAUSE:
        break;
    case APP_STA_RESUME:
        break;
    case APP_STA_STOP:
        //todo
        break;
    case APP_STA_DESTROY:
        log_d("\n>>>>> baby_monitor_exit <<<<<\n");
        //todo
        break;
    default:
        break;
    }

    return ret;
}


static int baby_monitor_key_event_handler(struct key_event *key)
{
    int ret = false;
    printf("key->action:%d key->value:%d \n", key->action, key->value);
    if (key->action == KEY_EVENT_CLICK) {
        ret = true;
        switch (key->value) {
        case KEY_POWER:
            printf("KEY1\n");
            break;
        case KEY_MENU:
            printf("KEY2\n");
            break;
        case KEY_UP:
            printf("KEY3\n");
            break;
        case KEY_DOWN:
            printf("KEY4\n");
            bbm_ctp_rec_start(__this->bbm_client_hdl[1]->ctp_cli_hdl);
            break;
        case KEY_OK:
            printf("KEY5\n");
            bbm_ctp_rec_stop(__this->bbm_client_hdl[1]->ctp_cli_hdl);
            //数字变焦测试
            /*             if (__this->bbm_cur_mode == BBM_MODE_STREAM && __this->cur_channel & BIT(1)) { */
            /* bbm_rt_stream_digital_zomm(__this->bbm_client_hdl[1]->ctp_cli_hdl, 2); */
            /* } */
            break;
        default:
            printf("Unknow KEY\n");
            break;
        }
    }

    return ret;
}



static int baby_monitor_device_event_handler(struct sys_event *e)
{
    struct device_event *device_eve = (struct device_event *)e->payload;

    return false;
}

static int event_handler(struct application *app, struct sys_event *event)
{
    switch (event->type) {
    case SYS_KEY_EVENT:
        return  baby_monitor_key_event_handler((struct key_event *)event->payload);
    case SYS_DEVICE_EVENT:
        return  baby_monitor_device_event_handler(event);
    case SYS_NET_EVENT:
    default:
        return false;
    }
}


static const struct application_operation baby_monitor_ops = {
    .state_machine  = state_machine,
    .event_handler  = event_handler,
};

REGISTER_APPLICATION(app_baby_monitor) = {
    .name 	= "baby_monitor",
    .action	= ACTION_BBM_MAIN,
    .ops 	= &baby_monitor_ops,
    .state  = APP_STA_DESTROY,
};



