#include "system/includes.h"
#include "server/video_server.h"
#include "event/key_event.h"
#include "event/device_event.h"
#include "video_rec.h"
#include "video_system.h"
#include "action.h"
#include "app_config.h"
#include "asm/debug.h"
#include "asm/osd.h"
#include "app_database.h"
#include "storage_device.h"
#include "app_power_manage.h"
#include "lcd_config.h"
#include "vrec_osd.h"

#define LOG_TAG_CONST       VIDEO_REC
#define LOG_TAG             "[VIDEO_REC]"
#define LOG_ERROR_ENABLE
#define LOG_DEBUG_ENABLE
#define LOG_INFO_ENABLE
/* #define LOG_DUMP_ENABLE */
#define LOG_CLI_ENABLE
#include "debug.h"


#define AUDIO_VOLUME	100

#ifndef CONFIG_VIDEO0_ENABLE
#undef VREC0_FBUF_SIZE
#define VREC0_FBUF_SIZE   0
#endif
#ifndef CONFIG_VIDEO1_ENABLE
#undef VREC1_FBUF_SIZE
#define VREC1_FBUF_SIZE   0
#endif
#ifndef CONFIG_VIDEO2_ENABLE
#undef VREC2_FBUF_SIZE
#define VREC2_FBUF_SIZE   0
#endif

#ifdef CONFIG_VIDEO_720P
#define CAP_IMG_SIZE (300*1024)
#else
#define CAP_IMG_SIZE (150*1024)
#endif

struct video_rec_hdl rec_handler;
#define __this 	(&rec_handler)
static int video_rec_get_abr(u32 width);
static const unsigned char video_osd_format_buf[] = "yyyy-nn-dd hh:mm:ss";
char video_rec_osd_buf[64] ALIGNE(64);
int video_rec_start();
int video_rec_stop(u8 close);
static int video_rec_sd_in();
static int video_rec_sd_out();
static int video_rec_get_abr(u32 width);


#ifdef CONFIG_XCIOT_ENABLE
unsigned char REC_FLAG = 1;
unsigned char MIC_FLAG = 1;
unsigned char STREAM_FLAG = 0;
unsigned char MICO_CTL = 0;

extern unsigned char MICO_CTL;


int net_video_rec_get_fps(void)
{
    return VIDEO_REC_FPS;
}
#endif



#ifdef CONFIG_VIDEO2_ENABLE
extern int uvc_host_online(void);
#endif

struct VideoConfig video_configs[] = {

#ifdef CONFIG_VIDEO0_ENABLE
    {
        .channel = 0,
        .path_main = CONFIG_REC_PATH_0,
        .req.rec.channel     = 0,
        .req.rec.camera_type = VIDEO_CAMERA_NORMAL,
        .req.rec.width 	    = 1280,
        .req.rec.height 	    = 720,
        .req.rec.format 	    = VIDEO0_REC_FORMAT,
        .req.rec.state 	    = VIDEO_STATE_START,
        .req.rec.quality     = VIDEO_LOW_Q,
        .req.rec.fps 	    = 10,
        .req.rec.real_fps 	= 10,
        .req.rec.audio.sample_rate = 8000,
        .req.rec.audio.channel 	= 1,
        .req.rec.audio.volume    = AUDIO_VOLUME,
        .req.rec.audio.buf_len = AUDIO_BUF_SIZE,
        .req.rec.pkg_mute.aud_mute = 0,
        .req.rec.enable_dri  = 0,
        .req.rec.online = 1,

        /*
        *码率，I帧和P帧比例，必须是偶数（当录MOV的时候才有效）,
        *roio_xy :值表示宏块坐标， [6:0]左边x坐标 ，[14:8]右边x坐标，[22:16]上边y坐标，[30:24]下边y坐标,写0表示1个宏块有效
        * roio_ratio : 区域比例系数
        */
        .req.rec.abr_kbps = 8000,

        .req.rec.cycle_time = 60, //cyc不能超过10,不能为0

        .req.rec.buf_len = VREC0_FBUF_SIZE,
        .req.rec.rec_small_pic   = 0,

    },
#endif

#ifdef CONFIG_VIDEO1_ENABLE
    {
        .channel = 1,
        .path_main = CONFIG_REC_PATH_1,
        .req.rec.channel     = 0,
        .req.rec.camera_type = VIDEO_CAMERA_NORMAL,
        .req.rec.width 	    = 640,
        .req.rec.height 	    = 480,
        .req.rec.src_w = 640,
        .req.rec.src_h = 480,

        .req.rec.format 	    = VIDEO1_REC_FORMAT,
        .req.rec.state 	    = VIDEO_STATE_START,
        .req.rec.quality     = VIDEO_LOW_Q,
        .req.rec.fps 	    = 20,
        .req.rec.real_fps 	= 20,
        .req.rec.audio.sample_rate = 8000,
        .req.rec.audio.channel 	= 1,
        .req.rec.audio.volume    = AUDIO_VOLUME,
        .req.rec.audio.buf_len = AUDIO_BUF_SIZE,
        .req.rec.pkg_mute.aud_mute = 0,

        /*
        *码率，I帧和P帧比例，必须是偶数（当录MOV的时候才有效）,
        *roio_xy :值表示宏块坐标， [6:0]左边x坐标 ，[14:8]右边x坐标，[22:16]上边y坐标，[30:24]下边y坐标,写0表示1个宏块有效
        * roio_ratio : 区域比例系数
        */
        .req.rec.abr_kbps = 8000,

        .req.rec.cycle_time = 60, //不能超过10,不能为0
        .req.rec.buf_len = VREC1_FBUF_SIZE,
        .req.rec.rec_small_pic   = 0,

    },
#endif

#ifdef CONFIG_VIDEO2_ENABLE
    {
        .channel = 2,
        .path_main = CONFIG_REC_PATH_2,
        .req.rec.channel     = 0,
        .req.rec.camera_type = VIDEO_CAMERA_NORMAL,
        .req.rec.width 	    = 640,
        .req.rec.height 	    = 480,
        .req.rec.src_w = 640,
        .req.rec.src_h = 480,
        .req.rec.format 	    = VIDEO2_REC_FORMAT,
        .req.rec.state 	    = VIDEO_STATE_START,
        .req.rec.quality     = VIDEO_LOW_Q,
        .req.rec.fps 	    = 20,
        .req.rec.real_fps 	= 20,
        .req.rec.audio.sample_rate = 8000,
        .req.rec.audio.channel 	= 1,
        .req.rec.audio.volume    = AUDIO_VOLUME,
        .req.rec.audio.buf_len = AUDIO_BUF_SIZE,
        .req.rec.pkg_mute.aud_mute = 0,

        /*
        *码率，I帧和P帧比例，必须是偶数（当录MOV的时候才有效）,
        *roio_xy :值表示宏块坐标， [6:0]左边x坐标 ，[14:8]右边x坐标，[22:16]上边y坐标，[30:24]下边y坐标,写0表示1个宏块有效
        * roio_ratio : 区域比例系数
        */
        .req.rec.abr_kbps = 8000,

        .req.rec.cycle_time = 60, //不能超过600,不能为0
        .req.rec.buf_len = VREC2_FBUF_SIZE,
        .req.rec.rec_small_pic   = 0,
    },
#endif


#ifdef CONFIG_VIDEO3_ENABLE
    {
        .channel = 3,
        .path_main = CONFIG_REC_PATH_2,
        .req.rec.channel     = 0,
        .req.rec.camera_type = VIDEO_CAMERA_NORMAL,
        .req.rec.width 	    = 1280,
        .req.rec.height 	    = 720,
        .req.rec.format 	    = VIDEO2_REC_FORMAT,
        .req.rec.state 	    = VIDEO_STATE_START,
        .req.rec.quality     = VIDEO_LOW_Q,
        .req.rec.fps 	    = 25,
        .req.rec.real_fps 	= 25,
        .req.rec.audio.sample_rate = 8000,
        .req.rec.audio.channel 	= 1,
        .req.rec.audio.volume    = AUDIO_VOLUME,
        .req.rec.audio.buf_len = AUDIO_BUF_SIZE,
        .req.rec.pkg_mute.aud_mute = 0,

        /*
        *码率，I帧和P帧比例，必须是偶数（当录MOV的时候才有效）,
        *roio_xy :值表示宏块坐标， [6:0]左边x坐标 ，[14:8]右边x坐标，[22:16]上边y坐标，[30:24]下边y坐标,写0表示1个宏块有效
        * roio_ratio : 区域比例系数
        */
        .req.rec.abr_kbps = 8000,

        .req.rec.cycle_time = 60, //不能超过600,不能为0
        .req.rec.buf_len = VREC2_FBUF_SIZE,
        .req.rec.rec_small_pic   = 0,
    },
#endif


};

#define CONFIG_VIDEO_NUM (sizeof(video_configs) / sizeof(video_configs[0]))

struct VideoConfig *get_video_configs(void)
{
    return video_configs;
}

static int video_rec_online_nums()
{
    u8 nums = 0;

    for (int i = 0; i < CONFIG_VIDEO_REC_NUM; i++) {
        if (__this->video_online[i]) {
            nums++;
        }
    }

    return nums;
}


int get_config_viedo_num(void)
{
    u8 nums = 0;
    nums = video_rec_online_nums();
    return nums;
}

int get_bp_num(void)
{
    return CONFIG_VIDEO_NUM;
}

int video_rec_get_audio_sampel_rate(void)
{
#ifdef  VIDEO_REC_AUDIO_SAMPLE_RATE
    return VIDEO_REC_AUDIO_SAMPLE_RATE;
#else
    return 8000;
#endif
}



void *get_video_rec_handler(void)
{
    return (void *)&rec_handler;
}

int video_rec_get_abr_from(u32 width)
{
    return video_rec_get_abr(width);
}

static void video_rec_buf_alloc()
{
    int buf_size[] = {VREC0_FBUF_SIZE, VREC1_FBUF_SIZE, VREC2_FBUF_SIZE};
    if ((!__this->audio_buf) && AUDIO_BUF_SIZE > 0) {
        __this->audio_buf = malloc(AUDIO_BUF_SIZE);
        if (!__this->audio_buf) {
            log_d(">>>>>>>>>> audiobuf alloc err>>>>>>\n");
            return ;
        }
    }
    for (int i = 0; i < ARRAY_SIZE(buf_size); i++) {
        if (buf_size[i]) {
            if (!__this->video_buf[i]) {
                __this->video_buf[i] = malloc(buf_size[i]);
                if (!__this->video_buf[i]) {
                    log_d(">>>>>>>>>> videobuf alloc err>>>>>>\n");
                }
            }
        } else {
            __this->video_buf[i] = NULL;
        }
    }
}
static int video_rec_destroy()
{
    if (__this->state != VIDREC_STA_FORBIDDEN) {
        return -EFAULT;
    }

    for (int i = 0; i < CONFIG_VIDEO_REC_NUM; i++) {
        if (__this->video_buf[i]) {
            free(__this->video_buf[i]);
            __this->video_buf[i] = NULL;
        }
    }
    if (__this->audio_buf) {
        free(__this->audio_buf);
        __this->audio_buf = NULL;
    }

    if (__this->cap_buf) {
        free(__this->cap_buf);
        __this->cap_buf = NULL;
    }

    return 0;
}
/*码率控制，根据具体分辨率设置*/
static int video_rec_get_abr(u32 width)
{
    /*视频码率kbps使用说明:
     码率：一帧图片以K字节为单位大小 * 帧率 * 8，比如：一帧图片为30KB，帧率为20帧，则码率为30*20*8=4800
     VGA图片大小说明：低等质量(小于20K)，中等质量(20K-40K)，高质量(大于40K，极限70K)
     720P图片大小说明：低等质量(小于50K)，中等质量(50k-100K)，高质量(大于100K，极限150K)
    */
    if (width <= 720) {
        /* return 8000; */
        return 4000;
    } else if (width <= 1280) {
        return 8000;
        /* return 10000; */
    } else if (width <= 1920) {
        return 14000;
    } else {
        return 18000;
    }
}

/*
 * 判断SD卡是否挂载成功和簇大小是否大于32K
 */
static int storage_device_available()
{
    struct vfs_partition *part;

    if (storage_device_ready() == 0) {
        return false;
    } else {
        part = fget_partition(CONFIG_ROOT_PATH);
        log_info("part_fs_attr: %x\n", part->fs_attr);
#ifdef CONFIG_JLFAT_ENABLE
        if (part->clust_size < 32 * 1024 || (part->fs_attr & F_ATTR_RO)) {
#else
        if (part->clust_size < 32 || (part->fs_attr & F_ATTR_RO)) {
#endif
            return false;
        }
        __this->total_size = part->total_size;
    }

    return true;
}



#define SCREEN_W   LCD_W
#define SCREEN_H   LCD_H
static struct video_window disp_window[DISP_MAX_WIN][4] = {0};

static void video_set_disp_window()
{
    u16 small_screen_w;
    u16 small_screen_h;

    if (LCD_W > 1280) {
        small_screen_w = 480; //16 aline
        small_screen_h = 400; //16 aline
    } else if (LCD_W > 480) {
        small_screen_w = 320; //16 aline
        small_screen_h = 240; //16 aline
    } else {
        small_screen_w = 192; //16 aline
        small_screen_h = 160; //16 aline
    }

    //DISP_MAIN_WIN
    disp_window[DISP_MAIN_WIN][0].width  = SCREEN_W;
    disp_window[DISP_MAIN_WIN][0].height = SCREEN_H;
    disp_window[DISP_MAIN_WIN][1].width  = small_screen_w;
    disp_window[DISP_MAIN_WIN][1].height = small_screen_h;
    disp_window[DISP_MAIN_WIN][2].left   = SCREEN_W - small_screen_w;
    disp_window[DISP_MAIN_WIN][2].width  = small_screen_w;
    disp_window[DISP_MAIN_WIN][2].height = small_screen_h;

    //DISP_HALF_WIN
    disp_window[DISP_HALF_WIN][0].width  = SCREEN_W / 2;
    disp_window[DISP_HALF_WIN][0].height = SCREEN_H;
    disp_window[DISP_HALF_WIN][1].left   = SCREEN_W / 2;
    disp_window[DISP_HALF_WIN][1].width  = SCREEN_W / 2;
    disp_window[DISP_HALF_WIN][1].height = SCREEN_H;
    disp_window[DISP_HALF_WIN][2].left   = SCREEN_W / 2;
    disp_window[DISP_HALF_WIN][2].width  = SCREEN_W / 2;
    disp_window[DISP_HALF_WIN][2].height = SCREEN_H;

    //DISP_FRONT_WIN
    disp_window[DISP_FRONT_WIN][0].width  = SCREEN_W;
    disp_window[DISP_FRONT_WIN][0].height = SCREEN_H;
    disp_window[DISP_FRONT_WIN][1].width  = (u16) - 1;
    disp_window[DISP_FRONT_WIN][1].height = SCREEN_H;

    //DISP_BACK_WIN
    disp_window[DISP_BACK_WIN][0].width  = (u16) - 1;
    disp_window[DISP_BACK_WIN][0].height = SCREEN_H;
    disp_window[DISP_BACK_WIN][1].width  = SCREEN_W;
    disp_window[DISP_BACK_WIN][1].height = SCREEN_H;
    disp_window[DISP_BACK_WIN][2].width  = SCREEN_W;
    disp_window[DISP_BACK_WIN][2].height = SCREEN_H;

    //DISP_PARK_WIN
    disp_window[DISP_PARK_WIN][0].width  = (u16) - 1;
    disp_window[DISP_PARK_WIN][0].height = SCREEN_H;
    disp_window[DISP_PARK_WIN][1].width  = SCREEN_W;
    disp_window[DISP_PARK_WIN][1].height = SCREEN_H;
    disp_window[DISP_PARK_WIN][2].width  = SCREEN_W;
    disp_window[DISP_PARK_WIN][2].height = SCREEN_H;
}

static void video_set_disp_mirror(int id, u16 mirror)
{
    for (int i = 0; i < DISP_MAX_WIN; i++) {
        disp_window[i][id].mirror = mirror;
    }
}




static int video_disp_pause(int id)
{
    union video_req req = {0};
    req.display.state = VIDEO_STATE_PAUSE;

    return server_request(__this->video_display[id], VIDEO_REQ_DISPLAY, &req);
}

static int video_disp_start(int id, const struct video_window *win)
{
    int err = 0;
    union video_req req = {0};
    static char dev_name[20];
    char fb_name[3];
#ifdef CONFIG_DISPLAY_ENABLE

    printf("video_disp_start: %d, %d x %d\n", id, win->width, win->height);

    if (win->width == (u16) - 1) {
        puts("video_disp_hide\n");
        return 0;
    }

    sprintf(dev_name, "video%d.%d", id, id < 3 ? 0 : __this->uvc_id);

#ifdef CONFIG_VIDEO2_ENABLE
    if (uvc_host_online() < 0) {

        return -EFAULT;
    }
#endif

    if (!__this->video_display[id]) {
        __this->video_display[id] = server_open("video_server", (void *)dev_name);
        if (!__this->video_display[id]) {
            log_e("open video_server: faild, id = %d\n", id);
            return -EFAULT;
        }
    }


    memset(fb_name, 0, sizeof(fb_name));
    sprintf(fb_name, "fb%d", id + 1);
    req.display.fb 		        = fb_name;
    req.display.left  	        = win->left;
    req.display.top 	        = win->top;
    req.display.width 	        = win->width;
    req.display.height 	        = win->height;
    req.display.border_left     = win->border_left;
    req.display.border_top      = win->border_top;
    req.display.border_right    = win->border_right;
    req.display.border_bottom   = win->border_bottom;
    req.display.mirror   		= win->mirror;
    req.display.jaggy			= 0;	// IMC 抗锯齿

    if (id == 0) {
        req.display.camera_config   = NULL;
        /* req.display.camera_config   = load_default_camera_config; */
        req.display.camera_type     = VIDEO_CAMERA_NORMAL;
    } else if ((id == 1) || (id == 3)) {
        /*if (req.display.width < 1280) {
            req.display.width 	+= 32;
            req.display.height 	+= 32;

            req.display.border_left   = 16;
            req.display.border_top    = 16;
            req.display.border_right  = 16;
            req.display.border_bottom = 16;
        }*/

        req.display.camera_config   = NULL;
        req.display.camera_type     = VIDEO_CAMERA_NORMAL;
    } else if (id == 2) {
        /* #ifdef THREE_WAY_ENABLE */
        req.display.uvc_id = __this->uvc_id;
        req.display.camera_config = NULL;
        req.display.camera_type = VIDEO_CAMERA_UVC;
        req.display.src_w = 640;//__this->src_width[3];
        req.display.src_h = 480;//__this->src_height[3];
        //旋转参数配置:
        //0:不旋转,不镜像 (原图)
        //1:逆时针旋转90度,不镜像
        //2:逆时针旋转270度,不镜像
        //3:逆时针旋转90度后,再垂直镜像
        //4:逆时针旋转90度后,再水平镜像
        req.display.rotate = 0; //usb后视频图像旋转显示
    }

    req.display.state 	        = VIDEO_STATE_START;
    req.display.pctl            = NULL;

    /* sys_key_event_disable(); */
    /* sys_touch_event_disable(); */
    err = server_request(__this->video_display[id], VIDEO_REQ_DISPLAY, &req);
    if (err) {
        printf("display req err = %d!!\n", err);
        server_close(__this->video_display[id]);
        __this->video_display[id] = NULL;
    }
#ifndef CONFIG_VIDEO4_ENABLE

    /* video_rec_start_isp_scenes(); */

    /* if (id == 0) { */
    /*rec显示重设曝光补偿*/
    /* __this->exposure_set = 1; */
    /* video_rec_set_exposure(db_select("exp")); */
    /* } */
#endif
#endif
    /* sys_key_event_enable(); */
    /* sys_touch_event_enable(); */

    return err;
}
/**
 * @brief       video3 指定uvc 显示
 *
 * @param: sub_id: uvc id号
 * @param: win:显示窗口配置
 *
 * @return:
 **/
int video3_disp_start(int sub_id, const struct video_window *win)
{
    int err = 0;
    union video_req req = {0};
    static char dev_name[20];
#ifdef CONFIG_DISPLAY_ENABLE

    /* video3.x 子设备号x划分: 0-4为uvc0 5-6为uvc1 7-8为uvc2 9为uvc3*/
    u8 id = sub_id;

    if (win->width == (u16) - 1) {
        puts("video_disp_hide\n");
        return 0;
    }

    sprintf(dev_name, "video3.%d", sub_id * 5);
    if (sub_id >= 2) {
        sprintf(dev_name, "video3.%d", sub_id + 6);
    }
    log_d("video_disp_start: %s, %d x %d\n", dev_name, win->width, win->height);

    if (!__this->video_display[id]) {
        __this->video_display[id] = server_open("video_server", (void *)dev_name);
        if (!__this->video_display[id]) {
            log_e("open video_server: faild, id = %d\n", id);
            return -EFAULT;
        }
    }


    req.display.fb 		        = "fb1";
    req.display.left  	        = win->left;
    req.display.top 	        = win->top;
    req.display.width 	        = win->width;
    req.display.height 	        = win->height;
    req.display.border_left     = win->border_left;
    req.display.border_top      = win->border_top;
    req.display.border_right    = win->border_right;
    req.display.border_bottom   = win->border_bottom;
    req.display.mirror   		= win->mirror;
    req.display.jaggy			= 0;	// IMC 抗锯齿

    req.display.uvc_id = sub_id;
    req.display.camera_config = NULL;
    req.display.camera_type = VIDEO_CAMERA_UVC;
    req.display.src_w = 640;//__this->src_width[3];
    req.display.src_h = 480;//__this->src_height[3];
    //旋转参数配置:
    //0:不旋转,不镜像 (原图)
    //1:逆时针旋转90度,不镜像
    //2:逆时针旋转270度,不镜像
    //3:逆时针旋转90度后,再垂直镜像
    //4:逆时针旋转90度后,再水平镜像
    req.display.rotate = 0; //usb后视频图像旋转显示

    req.display.state 	        = VIDEO_STATE_START;
    req.display.pctl            = NULL;

    /* sys_key_event_disable(); */
    /* sys_touch_event_disable(); */
    err = server_request(__this->video_display[id], VIDEO_REQ_DISPLAY, &req);
    if (err) {
        printf("display req err = %d!!\n", err);
        server_close(__this->video_display[id]);
        __this->video_display[id] = NULL;
    }
#ifndef CONFIG_VIDEO4_ENABLE

    /* video_rec_start_isp_scenes(); */

#endif
#endif
    /* sys_key_event_enable(); */
    /* sys_touch_event_enable(); */

    return err;
}
void video3_disp_stop(int id)
{
#ifdef CONFIG_DISPLAY_ENABLE
    union video_req req = {0};

    if (__this->video_display[id]) {

        req.display.state 	= VIDEO_STATE_STOP;
        server_request(__this->video_display[id], VIDEO_REQ_DISPLAY, &req);

        server_close(__this->video_display[id]);
        __this->video_display[id] = NULL;

    }
#endif
}
/***************************************************/

static void video_disp_stop(int id)
{
#ifdef CONFIG_DISPLAY_ENABLE
    union video_req req = {0};

    if (__this->video_display[id]) {
        if (id == 0) {
            /* video_rec_stop_isp_scenes(1, 0); */
        }

        req.display.state 	= VIDEO_STATE_STOP;
        server_request(__this->video_display[id], VIDEO_REQ_DISPLAY, &req);

        server_close(__this->video_display[id]);
        __this->video_display[id] = NULL;

        if (id == 0) {
            /* video_rec_start_isp_scenes(); */
        }
    }
#endif
}

static int video_disp_win_switch(int mode, int dev_id)
{
    int i;
    int err = 0;
    int next_win = 0;
    int curr_win = __this->disp_state;
    static u16 mirror[4] = {0};

#ifdef CONFIG_DISPLAY_ENABLE
    switch (mode) {
    case DISP_WIN_SW_SHOW_PARKING:
        if (!__this->video_online[__this->disp_park_sel]) {
            return -ENODEV;
        }
        next_win        = DISP_PARK_WIN;
        break;
    case DISP_WIN_SW_HIDE_PARKING:
        next_win = curr_win;
        curr_win = DISP_PARK_WIN;
        break;
    case DISP_WIN_SW_SHOW_SMALL:
        curr_win        = DISP_MAIN_WIN;
        next_win        = DISP_MAIN_WIN;
        break;
    case DISP_WIN_SW_SHOW_NEXT:
        if (video_rec_online_nums() < 2) {
            return 0;
        }
#if 0
        if (get_parking_status() == 1) {
            return 0;
        }
#endif
        next_win = curr_win;

        if (++next_win >= DISP_PARK_WIN) {
            next_win = DISP_MAIN_WIN;
        }
        break;
    case DISP_WIN_SW_DEV_IN:
        if (curr_win != DISP_MAIN_WIN) {
            return 0;
        }
        next_win = curr_win;
        break;
    case DISP_WIN_SW_DEV_OUT:
        next_win = DISP_MAIN_WIN;
        break;
    case DISP_WIN_SW_MIRROR:
        mirror[dev_id] = !mirror[dev_id];
        video_set_disp_mirror(dev_id, mirror[dev_id]);
        next_win = curr_win;
        break;
    default:
        return -EINVAL;
    }


    for (i = 1; i < CONFIG_VIDEO_REC_NUM; i++) {
        video_disp_stop(i);
    }

    if (curr_win != next_win || mode == DISP_WIN_SW_MIRROR) {
        video_disp_stop(0);
        err = video_disp_start(0, &disp_window[next_win][0]);
    }

    for (i = 0; i < CONFIG_VIDEO_REC_NUM; i++) {
        err = video_disp_start(i, &disp_window[next_win][0]);
        if (err == 0) {
            break;
        }
    }

    if (next_win != DISP_PARK_WIN) {
        __this->disp_state = next_win;
    }

#ifndef CONFIG_VIDEO4_ENABLE
    if (__this->disp_state == DISP_BACK_WIN) {
        /* 进入后视窗口前照灯关闭 */
        /* video_rec_post_msg("HlightOff"); */

        /* 后拉全屏显示（非录像状态），固定屏显场景1 */
        /* isp_scr_work_hdl(1); */
    }
#endif

#endif

    return err;
}





static void take_photo(void *priv)
{
#ifdef CONFIG_USR_VIDEO_ENABLE
    int err;
    extern int user_video_rec0_open(void);
    extern int user_video_rec_take_photo(void);
    extern int user_video_rec0_close(void);
    err = user_video_rec0_open();
    if (err) {
        log_error("user_video_open fail!\n");
        return;
    }
    os_time_dly(5);
    user_video_rec_take_photo();
    user_video_rec0_close();
    return;
#endif
    return;
}
int video_rec_take_photo(void)
{
    struct server *server = NULL;
    union video_req req = {0};
    char *path;
    char buf[48];
    char name_buf[20];
    int err;

    if (__this->state == VIDREC_STA_START) {
        server = __this->video_rec0;
        if (!server) {
            log_error("error :video not open\n");
            return -EINVAL;
        }
        req.icap.quality = VIDEO_HIG_Q;
        req.icap.buf_size = CAP_IMG_SIZE;
        req.icap.buf = malloc(CAP_IMG_SIZE);
        if (!req.icap.buf) {
            goto error;
        }
        req.rec.text_osd = NULL;
        req.rec.graph_osd = NULL;
        req.icap.text_label = NULL;
        req.icap.file_name = name_buf;
        req.icap.path = CAMERA0_CAP_PATH"IMG_****.jpg";
        path = CAMERA0_CAP_PATH;
        err = server_request(server, VIDEO_REQ_IMAGE_CAPTURE, &req);
        if (err != 0) {
            log_error("\n\n\ntake photo err\n\n\n");
            goto error;
        }
        sprintf(buf, "%s%s", path, req.icap.file_name);
        log_info("%s\n\n", buf);
        if (req.icap.buf) {
            free(req.icap.buf);
        }
        return 0;

error:
        if (req.icap.buf) {
            free(req.icap.buf);
        }
        return -EINVAL;
    } else if (__this->state != VIDREC_STA_STARTING && __this->state != VIDREC_STA_STOPING) {
        sys_timeout_add_to_task("sys_timer", NULL, take_photo, 10);
#if 0
#ifdef CONFIG_USR_VIDEO_ENABLE
        extern int user_video_rec0_open(void);
        extern int user_video_rec_take_photo(void);
        extern int user_video_rec0_close(void);
        err = user_video_rec0_open();
        if (err) {
            return -EINVAL;
        }
        os_time_dly(5);
        user_video_rec_take_photo();
        user_video_rec0_close();
        return 0;
#endif
#endif
    }
    return -EINVAL;
}

static void rec_dev_server_event_handler(void *priv, int argc, int *argv)
{
    /*
     *该回调函数会在录像过程中，写卡出错被当前录像APP调用，例如录像过程中突然拔卡
     */
    switch (argv[0]) {
    case VIDEO_SERVER_UVM_ERR:
        log_e("APP_UVM_DEAL_ERR\n");
        break;
    case VIDEO_SERVER_PKG_ERR:
        log_e("video_server_pkg_err\n");
        if (__this->state == VIDREC_STA_START) {
            video_rec_stop(0);
        }
        break;
    case VIDEO_SERVER_PKG_END:
        if (db_select("cyc") > 0) {
            video_rec_savefile((int)priv);
        } else {
            video_rec_stop(0);
        }
        break;
    default :
        log_e("unknow rec server cmd %x , %x!\n", argv[0], (int)priv);
        break;
    }
}
void assign_video_rec_params(union video_req *req, struct video_text_osd *text_osd, struct VideoConfig *config)
{

    struct video_graph_osd graph_osd = {0};
    u16 max_one_line_strnum = 0;
    u16 osd_line_num = 0;
    u16 osd_max_heigh = 0;



    req->rec.channel = config->req.rec.channel;
    req->rec.camera_type    = config->req.rec.camera_type;
    req->rec.width	    = config->req.rec.width;
    req->rec.height 	    = config->req.rec.height;
    req->rec.src_w 	    = config->req.rec.src_w;
    req->rec.src_h 	    = config->req.rec.src_h;

    req->rec.format 	    = config->req.rec.format;
    req->rec.state 	    = config->req.rec.state;
    /*
     *帧率为0表示使用摄像头的帧率
     */
    req->rec.quality     = config->req.rec.quality;
    req->rec.fps 	    = config->req.rec.fps;
    req->rec.real_fps 	= config->req.rec.real_fps;

    /*
     *采样率，通道数，录像音量，音频使用的循环BUF,录不录声音
     */
    req->rec.audio.sample_rate = config->req.rec.audio.sample_rate;
    req->rec.audio.channel 	= config->req.rec.audio.channel;
    req->rec.audio.volume    = config->req.rec.audio.volume;
    req->rec.audio.buf_len = config->req.rec.audio.buf_len;
    req->rec.pkg_mute.aud_mute = config->req.rec.pkg_mute.aud_mute;

    /*
     *码率，I帧和P帧比例，必须是偶数（当录MOV的时候才有效）,
     *roio_xy :值表示宏块坐标， [6:0]左边x坐标 ，[14:8]右边x坐标，[22:16]上边y坐标，[30:24]下边y坐标,写0表示1个宏块有效
     * roio_ratio : 区域比例系数
     */
    req->rec.abr_kbps = config->req.rec.abr_kbps;
    req->rec.IP_interval = config->req.rec.IP_interval;
#ifdef CONFIG_OSD_ENABLE

    /////////////////////////////////////////////
    ////////////////////////////////////////////
    memcpy(video_rec_osd_buf, osd_str_buf, strlen(osd_str_buf));
    text_osd->font_w = 16;
    text_osd->font_h = 32;
    max_one_line_strnum = strlen(video_rec_osd_buf);//21;
    printf("max_one_line_strnum=%d", strlen(video_rec_osd_buf));
    osd_line_num = 1;
    osd_max_heigh = (req->rec.height == 1088) ? 1080 : req->rec.height ;
    text_osd->x = (req->rec.width - max_one_line_strnum * text_osd->font_w) / 64 * 64;
    text_osd->y = (osd_max_heigh - text_osd->font_h * osd_line_num) / 16 * 16;
    text_osd->color[0] = 0xe20095;
    /* text_osd->color[0] = 0x057d88; */
    /* text_osd->color[1] = 0xe20095; */
    /* text_osd->color[2] = 0xe20095; */
    text_osd->bit_mode = 1;
    text_osd->text_format = video_rec_osd_buf;
    text_osd->font_matrix_table = osd_str_total;
    text_osd->font_matrix_base = osd_mimc_str_matrix;
    text_osd->font_matrix_len = sizeof(osd_mimc_str_matrix);
    text_osd->direction = 1;
    req->rec.text_osd = text_osd;
#endif


    req->rec.buf = config->req.rec.buf;
    req->rec.buf_len = config->req.rec.buf_len;
    req->rec.rec_small_pic   = config->req.rec.rec_small_pic;
    req->rec.cycle_time = config->req.rec.cycle_time;


    // 其他赋值操作...
}

int video_set_rec_start(void)
{
    int err;
    union video_req req = {0};
    struct video_text_osd text_osd;

    const char *video_server = "video_server";
    const char *video_dev = NULL;
    FILE *file = NULL;
    int *video_rec = NULL;
    void *server_dev;
    int online_num =  video_rec_online_nums();

    for (int index = 0; index < online_num; index++) {

        switch (video_configs[index].channel) {
        case 0:
            if (!__this->video_rec0) {
                server_dev = __this->video_rec0 = server_open("video_server", "video0.0");
                if (!__this->video_rec0) {
                    return VREC_ERR_V0_SERVER_OPEN;
                }
                server_register_event_handler(__this->video_rec0, (void *)0, rec_dev_server_event_handler);
            } else {
                server_dev = __this->video_rec0;//拔插卡之后重新赋值
            }
            break;
        case 1:
            if (!__this->video_rec1) {
                server_dev = __this->video_rec1 = server_open("video_server", "video1.0");
                if (!__this->video_rec1) {
                    return VREC_ERR_V1_SERVER_OPEN;
                }
                server_register_event_handler(__this->video_rec1, (void *)1, rec_dev_server_event_handler);
            } else {
                server_dev = __this->video_rec1;
            }

            break;
        case 2:
            if (!__this->video_rec2) {

#ifdef CONFIG_VIDEO2_ENABLE
                if (uvc_host_online() < 0) {
                    log_e("uvc no online\n");
                    return VREC_ERR_UVC_OFFLINE;
                }
                server_dev = __this->video_rec2 = server_open("video_server", "video2.0");
                if (!__this->video_rec2) {
                    return VREC_ERR_V2_SERVER_OPEN;
                }
                server_register_event_handler(__this->video_rec2, (void *)2, rec_dev_server_event_handler);
#endif
            } else {
                server_dev = __this->video_rec2;
            }
            break;

        case 3:
            if (!__this->video_rec3) {
                server_dev = __this->video_rec3 = server_open("video_server", "video3.0");
                if (!__this->video_rec3) {
                    return VREC_ERR_V3_SERVER_OPEN;
                }
                server_register_event_handler(__this->video_rec3, (void *)3, rec_dev_server_event_handler);
            } else {
                server_dev = __this->video_rec3;
            }

            break;



        default:
            continue;
        }

        int channel  = video_configs[index].channel;
        req.rec.file        = __this->file[channel];
        req.rec.fsize       = __this->new_file_size[channel];
        req.rec.audio.buf   = __this->audio_buf;
        req.rec.buf         = __this->video_buf[channel];
        req.rec.online      = 1;

        assign_video_rec_params(&req, &text_osd, &video_configs[index]);
#ifdef CONFIG_VIDEO2_ENABLE
        req.rec.uvc_id      = uvc_host_online();
#endif
        err = server_request(server_dev, VIDEO_REQ_REC, &req);
        if (err != 0) {
            log_error("\n\n\nstart rec err\n\n\n");
            return VREC_ERR_REQ_START;
        }
        __this->state = VIDREC_STA_START;
    }
    return 0;
}

int video_rec_start()
{
    int err;
    /* u32 clust; */
    u8 cnt = 0;
    u8 state = __this->state;
    int buf_size[] = {VREC0_FBUF_SIZE, VREC1_FBUF_SIZE, VREC2_FBUF_SIZE};

    __this->char_wait = 0;
    __this->need_restart_rec = 0;
    if (__this->state == VIDREC_STA_START) {
        return 0;
    }

    log_d("(((((( video_rec_start: in\n");

    if (!storage_device_available()) {
        return 0;
    }

    while (!get_db_status()) {

        os_time_dly(100);
    }

    /*
     * 申请录像所需要的音频和视频帧buf
     */
    video_rec_buf_alloc();

    /*
     * 判断SD卡空间，删除旧文件并创建新文件
     */
    int online_num  = video_rec_online_nums();

    if (!online_num) {
        log_error("video device all not online!\n");
        return 0;
    }
    log_info("online_num ===%d\n", online_num);
    for (int i = 0; i < online_num; i++) {
        int channel = video_configs[i].channel;
redo:
        err = video_rec_del_old_file(channel);
        if (err) {
            cnt++;
            if (cnt < 3) {
                log_d("retry ... \n\n");
                os_time_dly(50);
                goto redo;
            }
            log_e("start free space err\n");
            return VREC_ERR_START_FREE_SPACE;
        }
        __this->file[channel] = __this->new_file[channel];
        __this->new_file[channel] = NULL;
    }

    err = video_set_rec_start();
    if (err) {
        video_rec_stop(0);
        return err;
    }
    __this->state = VIDREC_STA_START;
    log_d("video_rec_start: out )))))))\n");
    return 0;
}

static int video_rec_storage_device_ready(void *p)
{
    __this->sd_wait = 0;
#ifdef CONFIG_ENABLE_VLIST
    FILE_LIST_INIT(1);
#endif

    if ((int)p == 1) {
        video_rec_start();

    }
    return 0;
}

int video_rec_stop(u8 close)
{
    int err;
    __this->need_restart_rec = 0;
    union video_req req = {0};
    void *server_dev;
    if (__this->state != VIDREC_STA_START) {
        return 0;
    }

    log_info("\nvideo_rec_stop\n");

    __this->state = VIDREC_STA_STOPING;

    for (int index = 0; index < CONFIG_VIDEO_NUM; index++) {
        switch (video_configs[index].channel) {
        case 0:
            if (__this->video_rec0) {
                server_dev = __this->video_rec0;
            }
            break;
        case 1:
            if (__this->video_rec1) {
                server_dev = __this->video_rec1;
            }
            break;
        case 2:
            if (__this->video_rec2) {
                server_dev = __this->video_rec2;
            }
            break;
        case 3:
            if (__this->video_rec3) {
                server_dev = __this->video_rec3;
            }
            break;

        default:
            continue;
        }
        if (server_dev) {
            req.rec.channel = 0;
            req.rec.state = VIDEO_STATE_STOP;
            err = server_request(server_dev, VIDEO_REQ_REC, &req);
            if (err != 0) {
                log_error("\nstop rec err 0x%x\n", err);
                return VREC_ERR_V0_REQ_STOP;
            }
        }
        video_rec_close_file(video_configs[index].channel);

        //video_rec_start_isp_scenes();
        if (close) {
            if (server_dev) {
                server_close(server_dev);
                server_dev = NULL;
            }
        }

    }
    __this->state = VIDREC_STA_STOP;
    log_info("video_rec_stop: exit\n");
    return 0;
}

static int video_rec_close()
{
    for (int index = 0; index < CONFIG_VIDEO_NUM; index++) {
        switch (video_configs[index].channel) {
        case 0:
            if (__this->video_rec0) {
                server_close(__this->video_rec0);
                __this->video_rec0 = NULL;
            }
            break;
        case 1:
            if (__this->video_rec1) {
                server_close(__this->video_rec1);
                __this->video_rec1 = NULL;
            }
            break;
        case 2:
            if (__this->video_rec2) {
                server_close(__this->video_rec2);
                __this->video_rec2 = NULL;
            }
        case 3:
            if (__this->video_rec3) {
                server_close(__this->video_rec3);
                __this->video_rec3 = NULL;
            }

            break;
        default:
            continue;
        }
    }
    return 0;
}

static int device_ready(void *priv)
{
#ifdef CONFIG_VIDEO2_ENABLE
    if (uvc_host_online() < 0 || !storage_device_ready()) {
        return false;
    }

    return true;
#else

    return storage_device_ready();
#endif
}


static int video_rec_init()
{
#ifdef CONFIG_VIDEO0_ENABLE
    __this->video_online[0] = 1;
    /* err = video_disp_start(0, &disp_window[DISP_MAIN_WIN][0]); */
#endif

#ifdef CONFIG_VIDEO1_ENABLE
    __this->video_online[1] = dev_online("video1.*");
#endif

#ifdef CONFIG_VIDEO2_ENABLE
    __this->video_online[2] = dev_online("uvc");
#endif

#ifdef CONFIG_VIDEO3_ENABLE
    __this->video_online[3] = 1;
#endif



    int err = 0;
    __this->sd_wait = wait_completion(device_ready, video_rec_storage_device_ready, (void *)1, NULL);
    return err;
}
static int video_rec_uninit()
{
    /* int err; */
    if (__this->state == VIDREC_STA_START) {
        return -EFAULT;
    }
    if (__this->sd_wait) {
        wait_completion_del(__this->sd_wait);
        __this->sd_wait = 0;
    }
    if (__this->char_wait) {
        wait_completion_del(__this->char_wait);
        __this->char_wait = 0;
    }
    if (__this->state == VIDREC_STA_START) {
        /* err = video_rec_stop(1); */
        video_rec_stop(1);
    }
    video_rec_close();
    __this->state = VIDREC_STA_FORBIDDEN;
    __this->lan_det_setting = 0;
    return 0;
}

/*
 *录像的状态机,进入录像app后就是跑这里
 */
static int video_rec_state_machine(struct application *app, enum app_state state, struct intent *it)
{
    int err = 0;
    /* int len; */

    switch (state) {
    case APP_STA_CREATE:
        log_d("\n >>>>>>> video_rec: create\n");

        memset(__this, 0, sizeof(struct video_rec_hdl));

        video_rec_buf_alloc();
        __this->state = VIDREC_STA_IDLE;
        break;
    case APP_STA_START:
        if (!it) {
            break;
        }
        switch (it->action) {
        case ACTION_VIDEO_REC_MAIN:
            log_info("ACTION_VIDEO_REC_MAIN\n");
            db_update("cyc", 1);


            video_rec_init();
            /* video_set_disp_window(); */
            /* video_disp_win_switch(DISP_WIN_SW_SHOW_SMALL, 0); */



            break;
        case ACTION_VIDEO_REC_DISPLAY:
            log_info("ACTION_VIDEO_REC_DISPLAY\n");
#ifdef CONFIG_VIDEO2_ENABLE
            u8 online_flag  = uvc_host_online();
            if (online_flag) {
                video_set_disp_window();
                video_disp_win_switch(DISP_WIN_SW_DEV_IN, 2);
            }
#else
            video_set_disp_window();
            video_disp_win_switch(DISP_WIN_SW_SHOW_SMALL, 0);
#endif
            break;

        case ACTION_VIDEO_REC_SET_CONFIG:
            break;
        case ACTION_VIDEO_REC_CHANGE_STATUS:
            break;
        }
        break;
    case APP_STA_PAUSE:
        log_info("--------app_rec: APP_STA_PAUSE\n");
        break;
    case APP_STA_RESUME:
        log_info("--------app_rec: APP_STA_RESUME\n");
        break;
    case APP_STA_STOP:
        log_info("--------app_rec: APP_STA_STOP\n");
        if (__this->state == VIDREC_STA_START) {
            video_rec_stop(0);
        }
        if (video_rec_uninit()) {
            err = 1;
            break;
        }
        break;
    case APP_STA_DESTROY:
        log_info("--------app_rec: APP_STA_DESTROY\n");
        if (video_rec_destroy()) {
            err = 2;
            break;
        }
        f_free_cache(CONFIG_ROOT_PATH);
        log_d("<<<<<<< video_rec: destroy\n");
        break;
    }

    return err;
}


/*
 *录像app的按键响应函数
 */
static int video_rec_key_event_handler(struct key_event *key)
{
    /* int err; */

    switch (key->action) {
    case KEY_EVENT_CLICK:
        switch (key->value) {
        case KEY_OK:
            log_debug("video_rec_key_ok: %d\n", __this->state);
            break;
        case KEY_MENU:
            break;
        case KEY_MODE:
            log_info("rec key mode\n");
            break;
        case KEY_UP:
            break;
        case KEY_DOWN:
            break;
        default:
            break;
        }
        break;
    case KEY_EVENT_LONG:

        switch (key->value) {

        case KEY_POWER:
            sys_power_poweroff();
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }

    return false;
}

static int video_rec_sd_in()
{
    __this->lock_fsize_count = 0;
    return 0;
}

static int video_rec_sd_out()
{
    if (__this->sd_wait == 0) {
        __this->sd_wait = wait_completion(device_ready,
                                          video_rec_storage_device_ready, (void *)1, NULL);
    }
    return 0;
}


/*
 *设备响应函数
 */
static int video_rec_device_event_handler(struct sys_event *sys_eve)
{
    struct device_event *device_eve = (struct device_event *)sys_eve->payload;
    int dev_id = 0;
    char *type = NULL;
    static u32 uvc_offline = 0;
    /*
     * SD卡插拔处理
     */
    if (sys_eve->from == DEVICE_EVENT_FROM_SD) {
        dev_id = ((const char *)device_eve->arg)[2] - '0';

        switch (device_eve->event) {
        case DEVICE_EVENT_IN:

            video_rec_sd_in();

            break;
        case DEVICE_EVENT_OUT:
            if (!fdir_exist(CONFIG_STORAGE_PATH)) {
                video_rec_sd_out();
            }

            break;
        }
    } else if (sys_eve->from == DEVICE_EVENT_FROM_POWER) {
        if (device_eve->event == POWER_EVENT_POWER_CHANGE) {
            int battery_per = sys_power_get_battery_persent();
        } else if (device_eve->event == POWER_EVENT_POWER_WARNING) {
        } else if (device_eve->event == POWER_EVENT_POWER_LOW) {
        } else if (device_eve->event == POWER_EVENT_POWER_AUTOOFF) {
        } else if (device_eve->event == POWER_EVENT_POWER_CHARGE) {

        }

#ifdef CONFIG_VIDEO2_ENABLE
    } else if (sys_eve->from == DEVICE_EVENT_FROM_USB_HOST && !strncmp((const char *)device_eve->value, "uvc", 3)) {
        switch (device_eve->event) {
        case DEVICE_EVENT_IN:

            __this->uvc_id  = uvc_host_online();
            if (!__this->video_online[2]) {
                __this->video_online[2] = true;

                log_info("UVC or msd_storage online : %s, id=%d\n", type, __this->uvc_id);

                if (__this->state == VIDREC_STA_START) {
                    video_rec_stop(0);
                    video_rec_start();
                }
                video_set_disp_window();
                video_disp_win_switch(DISP_WIN_SW_DEV_IN, 2);


            }
            break;
        case DEVICE_EVENT_OUT:
            puts("DEVICE_EVENT_OFFLINE: uvc\n");
            if (__this->video_online[2]) {
                __this->video_online[2] = false;

                video_disp_win_switch(DISP_WIN_SW_DEV_OUT, 2);

                if (__this->state == VIDREC_STA_START) {
                    video_rec_stop(0);
                    video_rec_start();
                }
            }
            break;
        }
#endif
    }
}






/*录像app的事件总入口*/
static int video_rec_event_handler(struct application *app, struct sys_event *event)
{
    switch (event->type) {
    case SYS_KEY_EVENT:
        return video_rec_key_event_handler((struct key_event *)event->payload);
    case SYS_DEVICE_EVENT:
        return video_rec_device_event_handler(event);
    default:
        return false;
    }
}

static const struct application_operation video_rec_ops = {
    .state_machine  = video_rec_state_machine,
    .event_handler 	= video_rec_event_handler,
};

REGISTER_APPLICATION(app_video_rec) = {
    .name 	= "video_rec",
    .ops 	= &video_rec_ops,
    .state  = APP_STA_DESTROY,
};

