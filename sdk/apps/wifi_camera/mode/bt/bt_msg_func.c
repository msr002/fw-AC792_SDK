#include "btstack/avctp_user.h"

static void volume_up(void)
{
    u8 test_box_vol_up = 0x41;
    s8 cur_vol = 0;
    u8 call_status = bt_get_call_status();
    u8 addr[6];
    a2dp_player_get_btaddr(addr);

    if ((tone_player_runing() || ring_player_runing())) {
        if (bt_get_call_status() == BT_CALL_INCOMING) {
            volume_up_down_direct(1);
        }
        return;
    }

    /*打电话出去彩铃要可以调音量大小*/
    if ((call_status == BT_CALL_ACTIVE) || (call_status == BT_CALL_OUTGOING)) {
        cur_vol = app_audio_get_volume(APP_AUDIO_STATE_CALL);
    } else {
        cur_vol = app_audio_get_volume(APP_AUDIO_STATE_MUSIC);
    }

    if (bt_get_remote_test_flag()) {
        bt_cmd_prepare(USER_CTRL_TEST_KEY, 1, &test_box_vol_up); //音量加
    }

    if (cur_vol >= app_audio_get_max_volume()) {
        /* audio_event_to_user(AUDIO_EVENT_VOL_MAX);	//触发vol max事件 */

#if TCFG_MAX_VOL_PROMPT
        play_tone_file(get_tone_files()->max_vol);
#endif
        if (bt_get_call_status() != BT_CALL_HANGUP) {
            /*本地音量最大，如果手机音量还没最大，继续加，以防显示不同步*/
            if (__this->phone_vol < 15) {
                if (bt_get_curr_channel_state() & HID_CH) {
                    bt_cmd_prepare(USER_CTRL_HID_VOL_UP, 0, NULL);
                } else {
                    bt_cmd_prepare(USER_CTRL_HFP_CALL_VOLUME_UP, 0, NULL);
                }
            }
            return;
        }
#if TCFG_BT_VOL_SYNC_ENABLE
        if (bt_get_call_status() == BT_CALL_HANGUP) {
            s16 music_volume_value = get_music_volume();
            opid_play_vol_sync_fun(&music_volume_value, 1);
            set_music_volume(music_volume_value);
            bt_cmd_prepare_for_addr(addr, USER_CTRL_CMD_SYNC_VOL_INC, 0, NULL);
        }
#endif/* TCFG_BT_VOL_SYNC_ENABLE */
        return;
    }

#if TCFG_BT_VOL_SYNC_ENABLE
    if (bt_get_call_status() == BT_CALL_HANGUP) {
        s16 music_volume_value = get_music_volume();
        opid_play_vol_sync_fun(&music_volume_value, 1);
        set_music_volume(music_volume_value);
        app_audio_set_volume(APP_AUDIO_STATE_MUSIC, get_music_volume(), 1);
    }
#else
    if (app_audio_get_state() == APP_AUDIO_STATE_IDLE) {
        app_audio_state_switch(APP_AUDIO_STATE_MUSIC, app_audio_volume_max_query(AppVol_BT_MUSIC), NULL);
    }
    app_audio_volume_up(1);
#endif/*TCFG_BT_VOL_SYNC_ENABLE*/

    log_info("vol+: %d", app_audio_get_volume(APP_AUDIO_CURRENT_STATE));

    if (bt_get_call_status() != BT_CALL_HANGUP) {
        bt_cmd_prepare(USER_CTRL_HFP_CALL_VOLUME_UP, 0, NULL);
    } else {
#if TCFG_BT_VOL_SYNC_ENABLE
        bt_cmd_prepare_for_addr(addr, USER_CTRL_CMD_SYNC_VOL_INC, 0, NULL); //使用HID调音量
#endif
    }
}

static void volume_down(void)
{
    u8 test_box_vol_down = 0x42;
    u8 addr[6];
    a2dp_player_get_btaddr(addr);

    if ((tone_player_runing() || ring_player_runing())) {
        if (bt_get_call_status() == BT_CALL_INCOMING) {
            volume_up_down_direct(-1);
        }
        return;
    }

    if (bt_get_remote_test_flag()) {
        bt_cmd_prepare(USER_CTRL_TEST_KEY, 1, &test_box_vol_down); //音量减
    }

    if (app_audio_get_volume(APP_AUDIO_CURRENT_STATE) <= 0) {
        /* audio_event_to_user(AUDIO_EVENT_VOL_MIN);	//触发vol mix事件 */
        if (bt_get_call_status() != BT_CALL_HANGUP) {
            /*
             *本地音量最小，如果手机音量还没最小，继续减
             *注意：有些手机通话最小音量是1(GREE G0245D)
             */
            if (__this->phone_vol > 1) {
                if (bt_get_curr_channel_state() & HID_CH) {
                    bt_cmd_prepare(USER_CTRL_HID_VOL_DOWN, 0, NULL);
                } else {
                    bt_cmd_prepare(USER_CTRL_HFP_CALL_VOLUME_DOWN, 0, NULL);
                }
            }
            return;
        }
#if TCFG_BT_VOL_SYNC_ENABLE
        if (bt_get_call_status() == BT_CALL_HANGUP) {
            s16 music_volume_value = get_music_volume();
            opid_play_vol_sync_fun(&music_volume_value, 0);
            set_music_volume(music_volume_value);
            bt_cmd_prepare_for_addr(addr, USER_CTRL_CMD_SYNC_VOL_DEC, 0, NULL);
        }
#endif
        return;
    }

#if TCFG_BT_VOL_SYNC_ENABLE
    if (bt_get_call_status() == BT_CALL_HANGUP) {
        s16 music_volume_value = get_music_volume();
        opid_play_vol_sync_fun(&music_volume_value, 0);
        set_music_volume(music_volume_value);
        app_audio_set_volume(APP_AUDIO_STATE_MUSIC, get_music_volume(), 1);
    }
#else
    if (app_audio_get_state() == APP_AUDIO_STATE_IDLE) {
        app_audio_state_switch(APP_AUDIO_STATE_MUSIC, app_audio_volume_max_query(AppVol_BT_MUSIC), NULL);
    }
    app_audio_volume_down(1);
#endif/*TCFG_BT_VOL_SYNC_ENABLE*/

    log_info("vol-: %d", app_audio_get_volume(APP_AUDIO_CURRENT_STATE));

    if (bt_get_call_status() != BT_CALL_HANGUP) {
        bt_cmd_prepare(USER_CTRL_HFP_CALL_VOLUME_DOWN, 0, NULL);
    } else {
#if TCFG_BT_VOL_SYNC_ENABLE
        /* opid_play_vol_sync_fun(&get_music_volume(), 0); */
        if (app_audio_get_volume(APP_AUDIO_CURRENT_STATE) == 0) {
            app_audio_volume_down(0);
        }
        bt_cmd_prepare_for_addr(addr, USER_CTRL_CMD_SYNC_VOL_DEC, 0, NULL);
#endif
    }
}

static void bt_app_msg_music_pp(void)
{
    if ((bt_get_call_status() == BT_CALL_OUTGOING) ||
        (bt_get_call_status() == BT_CALL_ALERT)) {
        bt_cmd_prepare(USER_CTRL_HFP_CALL_HANGUP, 0, NULL);
    } else if (bt_get_call_status() == BT_CALL_INCOMING) {
        bt_cmd_prepare(USER_CTRL_HFP_CALL_ANSWER, 0, NULL);
    } else if (bt_get_call_status() == BT_CALL_ACTIVE) {
        bt_cmd_prepare(USER_CTRL_HFP_CALL_HANGUP, 0, NULL);
    } else {
        bt_cmd_prepare(USER_CTRL_AVCTP_OPID_PLAY, 0, NULL);
    }
}

static void bt_app_msg_music_play(void)
{
    if (bt_get_call_status() == BT_CALL_INCOMING) {
        bt_cmd_prepare(USER_CTRL_HFP_CALL_ANSWER, 0, NULL);
    } else if (bt_a2dp_get_status() == BT_MUSIC_STATUS_SUSPENDING) {
        bt_cmd_prepare(USER_CTRL_AVCTP_OPID_PLAY, 0, NULL);
    }
}

static void bt_app_msg_music_pause(void)
{
    if ((bt_get_call_status() == BT_CALL_OUTGOING) ||
        (bt_get_call_status() == BT_CALL_ALERT)) {
        bt_cmd_prepare(USER_CTRL_HFP_CALL_HANGUP, 0, NULL);
    } else if (bt_get_call_status() == BT_CALL_ACTIVE) {
        bt_cmd_prepare(USER_CTRL_HFP_CALL_HANGUP, 0, NULL);
    } else if (bt_a2dp_get_status() == BT_MUSIC_STATUS_STARTING) {
        bt_cmd_prepare(USER_CTRL_AVCTP_OPID_PAUSE, 0, NULL);
    }
}

static void bt_app_msg_music_next(void)
{
    bt_cmd_prepare(USER_CTRL_AVCTP_OPID_NEXT, 0, NULL);
}

static void bt_app_msg_music_prev(void)
{
    if (bt_get_call_status() == BT_CALL_INCOMING) {
        bt_cmd_prepare(USER_CTRL_HFP_CALL_HANGUP, 0, NULL);
        return;
    }
    bt_cmd_prepare(USER_CTRL_AVCTP_OPID_PREV, 0, NULL);
}

static void bt_app_msg_vol_up(void)
{
    if (bt_get_call_status() == BT_CALL_ACTIVE && bt_sco_state() == 0) {
        return;
    }

    volume_up();

    u8 call_status = bt_get_call_status();
    u8 vol;

    if ((call_status == BT_CALL_ACTIVE) || (call_status == BT_CALL_OUTGOING)) {
        vol = app_audio_get_volume(APP_AUDIO_STATE_CALL);
    } else {
        vol = app_audio_get_volume(APP_AUDIO_STATE_MUSIC);
    }

    log_info("music_vol:vol=%d, state:%d", vol, app_audio_get_state());

#if TCFG_LOCAL_TWS_ENABLE || TCFG_LOCAL_TWS_SYNC_VOL
    local_tws_sync_vol();
#endif
#if (THIRD_PARTY_PROTOCOLS_SEL & MULTI_BOX_ADV_EN)
    multi_box_bis_change_volume_notify();
#endif
}

static void bt_app_msg_vol_down(void)
{
    if (bt_get_call_status() == BT_CALL_ACTIVE && bt_sco_state() == 0) {
        return;
    }

    volume_down();

    u8 call_status = bt_get_call_status();
    u8 vol;

    if ((call_status == BT_CALL_ACTIVE) || (call_status == BT_CALL_OUTGOING)) {
        vol = app_audio_get_volume(APP_AUDIO_STATE_CALL);
    } else {
        vol = app_audio_get_volume(APP_AUDIO_STATE_MUSIC);
    }

    log_info("music_vol:vol=%d, state:%d", vol, app_audio_get_state());

#if TCFG_LOCAL_TWS_ENABLE || TCFG_LOCAL_TWS_SYNC_VOL
    local_tws_sync_vol();
#endif
#if (THIRD_PARTY_PROTOCOLS_SEL & MULTI_BOX_ADV_EN)
    multi_box_bis_change_volume_notify();
#endif
}

static void bt_app_msg_call_last_on(void)
{
    if (bt_get_call_status() == BT_CALL_INCOMING) {
        bt_cmd_prepare(USER_CTRL_HFP_CALL_HANGUP, 0, NULL);
        return;
    }

    if ((bt_get_call_status() == BT_CALL_ACTIVE) ||
        (bt_get_call_status() == BT_CALL_OUTGOING) ||
        (bt_get_call_status() == BT_CALL_ALERT) ||
        (bt_get_call_status() == BT_CALL_INCOMING)) {
        return;//通话过程不允许回拨
    }

    if (__this->last_call_type ==  BT_STATUS_PHONE_INCOME) {
        bt_cmd_prepare(USER_CTRL_HFP_DIAL_NUMBER, __this->income_phone_len,
                       __this->income_phone_num);
    } else {
        bt_cmd_prepare(USER_CTRL_HFP_CALL_LAST_NO, 0, NULL);
    }
}

static void bt_app_msg_call_hang_up(void)
{
    bt_cmd_prepare(USER_CTRL_HFP_CALL_HANGUP, 0, NULL);
}

static void bt_app_msg_call_siri(void)
{
    bt_cmd_prepare(USER_CTRL_HFP_GET_SIRI_OPEN, 0, NULL);
}

static void bt_app_msg_hid_control(void)
{
    if (bt_get_curr_channel_state() & HID_CH) {
        bt_cmd_prepare(USER_CTRL_HID_IOS, 0, NULL);
    }
}

//蓝牙模式 三方通话 挂断当前去听另一个（未接听或者在保留状态都可以）
static void bt_app_msg_call_three_way_answer1(void)
{
    bt_cmd_prepare(USER_CTRL_HFP_THREE_WAY_ANSWER1, 0, NULL);
}

//蓝牙模式 三方通话 保留当前去接听, 或者用于两个通话的切换
static void bt_app_msg_call_three_way_answer2(void)
{
    bt_cmd_prepare(USER_CTRL_HFP_THREE_WAY_ANSWER2, 0, NULL);
}

static void bt_app_msg_call_switch(void)
{
    if (bt_get_call_status() == BT_CALL_ACTIVE) {
        bt_cmd_prepare(USER_CTRL_SCO_LINK, 0, NULL);
    }
}

static void *get_the_other_device(u8 *addr)
{
    void *devices[2] = {NULL, NULL};
    int num = btstack_get_conn_devices(devices, 2);
    /*printf("bt_device: %p, %p\n", devices[0], devices[1]);
    put_buf(btstack_get_device_mac_addr(devices[0]), 6);
    put_buf(btstack_get_device_mac_addr(devices[1]), 6);*/
    for (int i = 0; i < num; i++) {
        if (memcmp(btstack_get_device_mac_addr(devices[i]), addr, 6)) {
            return devices[i];
        }
    }

    return NULL;
}

static void bt_action_a2dp_play(void *device, u8 *bt_addr)
{
    int slience = bt_slience_detect_get_result(bt_addr);
    int playing = a2dp_player_is_playing(bt_addr);

    log_info("a2dp_play: %d, %d", playing, slience);
    put_buf(bt_addr, 6);

    if (slience == BT_SLIENCE_NO_DETECTING) {
        if (!playing) {
            btstack_device_control(device, USER_CTRL_AVCTP_OPID_PLAY);
        }
    } else if (slience == BT_SLIENCE_NO_ENERGY) {
        btstack_device_control(device, USER_CTRL_AVCTP_OPID_PLAY);
    } else {
        int msg[3];
        msg[0] = APP_MSG_BT_A2DP_PLAY;
        memcpy(msg + 1, bt_addr, 6);
        app_send_message(MSG_FROM_APP, 3, msg);
    }
}

static void bt_action_a2dp_pause(void *device, u8 *bt_addr)
{
    int slience = bt_slience_detect_get_result(bt_addr);
    int playing = a2dp_player_is_playing(bt_addr);

    log_info("a2dp_pause: %d, %d", playing, slience);
    put_buf(bt_addr, 6);

    if (playing) {
        btstack_device_control(device, USER_CTRL_AVCTP_PAUSE_MUSIC);
    } else {
        if (slience == BT_SLIENCE_HAVE_ENERGY) {
            btstack_device_control(device, USER_CTRL_AVCTP_PAUSE_MUSIC);
        }
    }
    int msg[3];
    msg[0] = APP_MSG_BT_A2DP_PAUSE;
    memcpy(msg + 1, bt_addr, 6);
    app_send_message(MSG_FROM_APP, 3, msg);
}

static void bt_app_msg_a2dp_start(u8 *bt_addr)
{
#if TCFG_A2DP_PREEMPTED_ENABLE && TCFG_BT_SUPPORT_PROFILE_A2DP
    /*这里处理有些设备切到后台一直不推a2dp stop，手动切到蓝牙模式后能量检测还在跑，这时候点击设备播放按钮之后，
      能量检测有数据之后结束推APP_MSG_BT_A2DP_START，这种情况需要在这里打开解码*/
#if TCFG_BT_DUAL_CONN_ENABLE
    void *device = get_the_other_device(bt_addr);
    if (device) {
        if (a2dp_player_is_playing(btstack_get_device_mac_addr(device))) {
            bt_action_a2dp_pause(device, btstack_get_device_mac_addr(device));
            bt_action_a2dp_play(btstack_get_conn_device(bt_addr), bt_addr);
            return;
        }
    }
#endif
    app_audio_state_switch(APP_AUDIO_STATE_MUSIC, app_audio_volume_max_query(AppVol_BT_MUSIC), NULL);
    u8 dev_vol = bt_get_music_volume(bt_addr);
    if (dev_vol > 127) {
        dev_vol = app_audio_bt_volume_update(bt_addr, APP_AUDIO_STATE_MUSIC);
    }
    bt_set_music_device_volume(dev_vol);
    rf_coexistence_scene_enter(RF_COEXISTENCE_SCENE_A2DP_PLAY, -1);
    int err = a2dp_player_open(bt_addr);
    if (err == -EBUSY) {
        log_error("bt_app_msg_handler open a2dp_player failed");
        bt_start_a2dp_slience_detect(bt_addr, 50);
    }
#endif
}

