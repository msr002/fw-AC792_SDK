#include "system/includes.h"
#include "pipeline_core.h"
#include "app_config.h"
#include "action.h"
#include "lcd_config.h"
#include "screen_mirror_api.h"

#define LOG_TAG_CONST       SCREEN_MIRROR_API
#define LOG_TAG             "[SCREEN_MIRROR_API]"
#define LOG_ERROR_ENABLE
#define LOG_INFO_ENABLE
#define LOG_DUMP_ENABLE

#include "debug.h"

#ifdef CONFIG_NET_SCR

static pipe_core_t *pipe_core;
static struct __NET_SCR_INFO  net_scr_info;

#define __ALIGN_16(a)   (((a) + 15) / 16 * 16)
#define __ALIGN_8(a)   (((a) + 7) / 8 * 8)

int net_scr_init(struct __NET_SCR_CFG *cfg)
{
    pipe_filter_t *source_filter, *jpeg_dec_filter, *imc_filter, *rep_filter, *disp_filter;
    struct video_format f = {0};

    if (net_scr_info.state) {
        log_error("%s multiple init\n", __func__);
        return 0;
    }
    memcpy(&net_scr_info.cfg, cfg, sizeof(struct __NET_SCR_CFG));
    log_info("scr size: %d x %d", net_scr_info.cfg.src_w, net_scr_info.cfg.src_h);

    pipe_core = pipeline_init(NULL, NULL);
    ASSERT(pipe_core);

    char *source_name = "scr0";
    pipe_core->channel = plugin_source_to_channel(source_name);

    source_filter = pipeline_filter_add(pipe_core, source_name);
    jpeg_dec_filter = pipeline_filter_add(pipe_core, plugin_factory_find("jpeg_dec"));
    rep_filter = pipeline_filter_add(pipe_core, plugin_factory_find("rep"));
    imc_filter = pipeline_filter_add(pipe_core, find_use_for_display_plugin("imc"));
    disp_filter = pipeline_filter_add(pipe_core, plugin_factory_find("disp"));

#if 0   //最新协商,采用设备主动发送过去的宽高,FPS
    //数据源数据格式
    f.src_width = __ALIGN_16(net_scr_info.cfg.src_w);   //为了兼容YUV420格式, 如确认是YUV422/444格式, 可配置8对齐
    f.src_height = net_scr_info.cfg.src_h;
    f.fps = net_scr_info.cfg.fps;
#else
    f.src_width = LCD_W;
    f.src_height = LCD_H;
    f.fps = 25;
#endif

    //显示配置
    f.win.left 	 = 0;
    f.win.top  	 = 0;
    f.win.width = LCD_W;
    f.win.height = LCD_H;
    f.win.combine = 1; //合成显示

    pipeline_param_set(pipe_core, NULL, PIPELINE_SET_FORMAT, &f);
    pipeline_param_set(pipe_core, NULL, PIPELINE_SCR_CLI_ADR, &net_scr_info.cfg.cli_addr);
    int sock_type = SOCK_STREAM;
    pipeline_param_set(pipe_core, NULL, PIPELINE_SCR_SOCK_TYPE, &sock_type);
    int line_cnt = 16;
    pipeline_param_set(pipe_core, NULL, PIPELINE_SET_BUFFER_LINE, (int)&line_cnt);

    pipeline_filter_link(source_filter, jpeg_dec_filter);
    pipeline_filter_link(jpeg_dec_filter, rep_filter);
    pipeline_filter_link(rep_filter, imc_filter);
    pipeline_filter_link(imc_filter, disp_filter);

    pipeline_prepare(pipe_core);
    pipeline_start(pipe_core);

    net_scr_info.state = 1;

    return 0;
}

int net_scr_uninit(struct __NET_SCR_CFG *cfg)
{
    if (!net_scr_info.state || memcmp((char *)&net_scr_info.cfg.cli_addr + 2, (char *)&cfg->cli_addr + 2, 6)) {
        log_error("cli addr not match.\n");
        return -1;
    }

    net_scr_info.state = 0;

    pipeline_stop(pipe_core);
    pipeline_reset(pipe_core);

    pipeline_uninit(pipe_core);

    return 0;
}

u8 get_net_scr_status(void)
{
    return net_scr_info.state;
}





#endif

