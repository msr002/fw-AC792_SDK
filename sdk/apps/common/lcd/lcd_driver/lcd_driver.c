#include "lcd_config.h"
#include "lcd_driver.h"
#include "asm/spi.h"
#include "asm/dpi.h"
#include "asm/dmm.h"
#include "asm/exti.h"
#include "device/gpio.h"
#include "asm/dsi_api.h"
#include "dma2d_common_api.h"
#include "asm/jldma2d.h"
#include "asm/dcache.h"

#if TCFG_LCD_ENABLE

#if TCFG_LCD_TE_ENABLE
/*
 * MCU/SPI屏显示为避免出现撕裂问题(Tearing effect)，lcd driver需要检测到帧TE信号后才开始推数据给屏幕，
 * 并且推屏速率需要遵循2倍关系:
 * 1.不能让读屏指针赶上写屏指针。写屏ram的数据时间(W)应该小于等于2倍MCU/SPI屏的自刷新时间(R)。
 * 2.不能让写屏指针赶上读屏指针。写屏ram的数据时间(W)应该大于MCU/SPI屏的自刷新时间(R)。
 * 即lcd_te_int_time < lcd_push_data_time <= 2 * lcd_te_int_time
 *
 * 可调整接口推屏速率。推屏接口的时钟频率决定了推数据速率，各个接口的时钟频率调整位置:
 * 1.SPI接口——修改波特率和LSB时钟;
 * 2.PAP接口——修改TS、TH、TW时钟以及LSB时钟;(PAP的WR速率 = LSB / (TS + TH + TW))
 * 3.DPI接口——修改.dclk_cfg的时钟源和分配值;
 * 当然，也可以调整MCU/SPI屏刷新帧率，需要咨询屏厂怎么修改。
 */
#define LCD_TE_DEBUG_EN         0          ///< 开启TE调试。通过打印判断推屏速率是否在合适范围。
#if LCD_TE_DEBUG_EN
#include "perf_counter.h"
static volatile u32 lcd_te_int_time;       ///< TE信号中断间隔时间
static u32 lcd_push_data_time;             ///< 接口推一帧数据间隔时间
static u32 lcd_push_data_start;            ///< 开始推数时间
static u32 lcd_push_data_end;              ///< 推数结束时间
static void lcd_te_int_time_calc(void)
{
    static u32 last_time;
    u32 now_time;
    now_time = get_system_us();
    if (last_time) {
        lcd_te_int_time = now_time - last_time;
    }
    last_time = now_time;
}

static void lcd_push_data_time_calc_start(void)
{
    lcd_push_data_start = get_system_us();
}

static void lcd_push_data_time_calc_end(void)
{
    lcd_push_data_end = get_system_us();
    lcd_push_data_time = lcd_push_data_end - lcd_push_data_start;
    if (lcd_te_int_time) {
        printf("\n~~~~~~~~~~~~~~~~~~LCD TE DEBUG~~~~~~~~~~~~~~~~~~\n");
        printf("lcd_te_int_time    = %d\n", lcd_te_int_time);
        printf("lcd_push_data_time = %d\n", lcd_push_data_time);
        if (lcd_te_int_time > lcd_push_data_time) {
            // lcd推数据太快
            printf("TE issue! lcd push data is too fast. diff_time = %d\n", lcd_te_int_time - lcd_push_data_time);
        } else if (lcd_te_int_time * 2 < lcd_push_data_time) {
            // lcd推数据太慢
            printf("TE issue! lcd push data is too slow. diff_time = %d\n", lcd_push_data_time - lcd_te_int_time * 2);
        } else {
            // lcd推数据速率刚刚好
            printf("TE normal! diff_time = %d\n", lcd_te_int_time * 2 - lcd_push_data_time);
        }

    }
}
#endif // LCD_TE_DEBUG_EN
#endif // TCFG_LCD_TE_ENABLE

extern int dma2d_init();
extern int dma2d_free();
extern void jldma2d_endian_trans(uint8_t *dest_buf, uint8_t *src_buf, uint32_t w, uint32_t h, uint32_t format);


struct lcd_device_info {
    struct device device;
    const struct lcd_dev_drive *lcd;
    struct lcd_platform_data *platform_data;
    void *lcd_dev;
    u8 lcd_open_flag;
    OS_SEM *lcd_wait_sem;
    u8 *draw_buf;
    int te_id;
    OS_SEM te_sem;
};
static struct lcd_device_info lcd_dev_info_t = {0};

#define __this (&lcd_dev_info_t)

void lcd_cs_pinstate(u8 state)
{
    if (__this->lcd->type == LCD_MCU || \
        __this->lcd->type == LCD_MCU_SINGLE_FRAME || \
        __this->lcd->type == LCD_SPI) {
        if (__this->platform_data->lcd_io.lcd_cs != -1) {
            gpio_direction_output(__this->platform_data->lcd_io.lcd_cs, state);
        }
    }
}

void lcd_rs_pinstate(u8 state)
{
    if (__this->lcd->type == LCD_MCU || \
        __this->lcd->type == LCD_MCU_SINGLE_FRAME || \
        __this->lcd->type == LCD_SPI) {
        if (__this->platform_data->lcd_io.lcd_rs != -1) {
            gpio_direction_output(__this->platform_data->lcd_io.lcd_rs, state);
        }
    }
}

void lcd_rst_pinstate(u8 state)
{
    if (__this->lcd->type == LCD_MCU || \
        __this->lcd->type == LCD_MCU_SINGLE_FRAME || \
        __this->lcd->type == LCD_SPI) {
        if (__this->platform_data->lcd_io.lcd_reset != -1) {
            gpio_direction_output(__this->platform_data->lcd_io.lcd_reset, state);
        }
    }
}

void lcd_backlight_ctrl(u8 onoff)
{
    if (onoff) {
        printf("[LCD]>>>>>>lcd_backlight open");
    } else {
        printf("[LCD]>>>>>>lcd_backlight close");
    }

    if (__this->lcd && __this->lcd->bl_ctrl) {
        __this->lcd->bl_ctrl(__this->platform_data, onoff);
    }
}

void WriteCOM(u8 cmd)
{
    struct lcd_dev_drive *lcd = (struct lcd_dev_drive *)__this->lcd;

    if (!__this->lcd_dev) {
        printf("[LCD]WriteCOM fail, open device first\n");
        return;
    }

    lcd_cs_pinstate(0);
    lcd_rs_pinstate(0);//cmd

    if (lcd->type == LCD_MCU_SINGLE_FRAME || lcd->type == LCD_MCU) {
        dev_ioctl(__this->lcd_dev, IOCTL_PAP_ENABLE, 0);
        dev_write(__this->lcd_dev, &cmd, 1);
    } else if (lcd->type == LCD_SPI) {
        dev_ioctl(__this->lcd_dev, IOCTL_SPI_SEND_BYTE, (u32)cmd);
    }

    lcd_cs_pinstate(1);
}

void ReadDAT(u8 cmd, u8 *buf, u8 len)
{
    struct lcd_dev_drive *lcd = (struct lcd_dev_drive *)__this->lcd;

    if (!__this->lcd_dev) {
        printf("[LCD]WriteCOM fail, open device first\n");
        return;
    }

    if (lcd->type == LCD_SPI) {
        lcd_cs_pinstate(0);
        lcd_rs_pinstate(0);//cmd
        dev_ioctl(__this->lcd_dev, IOCTL_SPI_SEND_BYTE, (u32)cmd);
        lcd_rs_pinstate(1);//dat
        for (u8 i = 0; i < len; i++) {
            dev_ioctl(__this->lcd_dev, IOCTL_SPI_READ_BYTE, (u32)(buf + i));
        }
        lcd_cs_pinstate(1);
    }
}

void WriteDAT_8(u8 dat)
{
    struct lcd_dev_drive *lcd = (struct lcd_dev_drive *)__this->lcd;

    if (!__this->lcd_dev) {
        printf("[LCD]WriteDAT fail, open device first\n");
        return;
    }

    lcd_cs_pinstate(0);
    lcd_rs_pinstate(1);//dat

    if (lcd->type == LCD_MCU_SINGLE_FRAME || lcd->type == LCD_MCU) {
        dev_ioctl(__this->lcd_dev, IOCTL_PAP_ENABLE, 0);
        dev_write(__this->lcd_dev, &dat, 1);
    } else if (lcd->type == LCD_SPI) {
        dev_ioctl(__this->lcd_dev, IOCTL_SPI_SEND_BYTE, (u32)dat);
    }

    lcd_cs_pinstate(1);
}

void WriteDAT_one_page(u8 *dat, int len)
{
    struct lcd_dev_drive *lcd = (struct lcd_dev_drive *)__this->lcd;
    u8 te_en;

    if (!__this->lcd_dev) {
        printf("[LCD]WriteDAT_one_page fail, open device first\n");
        return;
    }

    lcd_cs_pinstate(0);
    lcd_rs_pinstate(1);//dat

    DcuInvalidRegion((u32 *)dat, len);

    if (lcd->type == LCD_SPI) {
        te_en = __this->lcd->dev->spi.te_mode.te_mode_en;
    } else {
        te_en = __this->lcd->dev->imd.te_mode.te_mode_en;
    }
    if (te_en) {
        os_sem_set(&__this->te_sem, 0);
        int err = os_sem_pend(&__this->te_sem, 100);
        if (err == OS_TIMEOUT) {
            printf("[LCD]wait TE timeout!");
        }
    }

#if LCD_TE_DEBUG_EN
    lcd_push_data_time_calc_start();
#endif

    if (lcd->type == LCD_SPI) {
        dev_write(__this->lcd_dev, dat, (u32)len);
    } else if (lcd->type == LCD_MCU_SINGLE_FRAME) {
        if (__this->lcd_open_flag) {
            dev_ioctl(__this->lcd_dev, IOCTL_PAP_DISABLE, 0);
            dpi_wait_fb_swap_finish((u32)dat); //size
        } else {//mcu测试颜色会跑这里
            if (__this->lcd->dev->imd.dpi_open_flag) {
                dpi_start_display((u32)dat);
                lcd_backlight_ctrl(true); //开启背光
                __this->lcd_open_flag = 1;
            }
        }
    } else if (lcd->type == LCD_MCU) {
        dev_ioctl(__this->lcd_dev, IOCTL_PAP_ENABLE, 0);
        dev_write(__this->lcd_dev, dat, (u32)len);
    }

#if LCD_TE_DEBUG_EN
    lcd_push_data_time_calc_end();
#endif

    lcd_cs_pinstate(1);
}

u16 lcd_get_rotate(void)
{
    if (__this->lcd) {
        return __this->lcd->dev->imd.info.rotate;
    }

    return 0;
}

int lcd_touch_width_height_rotate(u16 *w, u16 *h)
{
    u16 lcd_w;
    u16 lcd_h;
    u16 rotate;
    if (__this->lcd) {
        lcd_w = __this->lcd->dev->imd.info.target_xres;
        lcd_h = __this->lcd->dev->imd.info.target_yres;
        rotate = __this->lcd->dev->imd.info.rotate;
        if (rotate == ROTATE_90 || rotate == ROTATE_270) {
            *w = lcd_h;
            *h = lcd_w;
        } else {
            *w = lcd_w;
            *h = lcd_h;
        }
    }

    return 0;
}
int lcd_touch_xy_coord_rotate(u16 *x, u16 *y, u8 status)
{
    u16 rotate;
    u16 touch_w;
    u16 touch_h;
    u16 tmp = 0;
    if (__this->lcd) {
        touch_w = __this->lcd->dev->imd.info.target_xres;
        touch_h = __this->lcd->dev->imd.info.target_yres;
        rotate = __this->lcd->dev->imd.info.rotate;
        if (status) {
            /* printf("\n>>>> [%d]touch (%d,%d)\n",status,*x,*y); */
            switch (rotate) {
            case ROTATE_90:
                tmp = *y;
                *y = *x;
                *x = touch_w - tmp - 1;
                break;
            case ROTATE_270:
                tmp = *x;
                *x = *y;
                *y = touch_h - tmp - 1;
                break;
            case ROTATE_180:
                *x = touch_w - *x - 1;
                *y = touch_h - *y - 1;
                break;
            }
            /* printf(">>>> [%d]rotate:%d touch (%d,%d)\n",status,rotate,*x,*y); */
        }
    }

    return 0;
}

static struct lcd_dev_drive *lcd_dev_match(const char *name)
{
    struct lcd_dev_drive *p;

    list_for_each_lcd_device_drive(p) {
        if (name == NULL) {
            return p;
        } else {
            ASSERT(p->logo, "::the logo of lcd driver is null,please check it!!!");
            ASSERT(name, "::specified lcd_name that will be opened is null,please check it!!!");
            if (p->logo && name) {
                if (!strcmp(p->logo, name)) {
                    return p;
                }
            } else {
                return NULL;
            }
        }
    }
    return NULL;
}

static int lcd_init_wait_done(void)
{
    int err = 0;
    if (__this->lcd_wait_sem) {
        err = os_sem_pend(__this->lcd_wait_sem, 1000);
        if (err) {
            printf("[LCD]wait init err %d\n", err);
        }
        err = os_sem_del(__this->lcd_wait_sem, OS_DEL_ALWAYS);
        __this->lcd_wait_sem = NULL;
    }
    return err;
}

static int lcd_open_pap(void)
{
    __this->lcd_dev = dev_open("pap", NULL);
    if (!__this->lcd_dev) {
        printf("[LCD]open pap fail\n");
        printf("[LCD]pap device must be register and placed in front of lcd device \n");
        return -1;
    }
    printf("[LCD]open pap ok\n");
    return 0;
}

static int lcd_open_spi(void)
{
    char *if_name = __this->lcd->dev->spi.interface_name;

    __this->lcd_dev = dev_open(if_name, NULL);
    if (!__this->lcd_dev) {
        printf("[LCD]open spi fail\n");
        printf("[LCD]%s device must be register and placed in front of lcd\n", if_name);
        return -1;
    }
    printf("[LCD]open spi ok\n");
    return 0;
}

static int lcd_reopen(void)
{
    struct lcd_platform_data *_data = (struct lcd_platform_data *)__this->platform_data;
    struct lcd_dev_drive *lcd = (struct lcd_dev_drive *)__this->lcd;

    if (lcd) {
        if (lcd->type == LCD_MCU_SINGLE_FRAME || lcd->type == LCD_MCU) {
            if (lcd_open_pap() < 0) {
                return -1;
            }
        }
        if (lcd->type ==  LCD_SPI) {
            if (lcd_open_spi() < 0) {
                return -1;
            }
        }

        if (lcd->init) {
            lcd->init(_data);
        }
        printf("[LCD]lcd reopen done\n");
        return 0;
    }

    return -1;
}

static void lcd_te_interrupt(void *arg, u32 parm)
{
#if LCD_TE_DEBUG_EN
    lcd_te_int_time_calc();
#endif
    os_sem_post(&__this->te_sem);
    /* putchar('a'); */
}

static void lcd_init_task(void *arg)
{
    struct lcd_platform_data *_data = (struct lcd_platform_data *)__this->platform_data;
    struct lcd_dev_drive *lcd = (struct lcd_dev_drive *)__this->lcd;

    OS_SEM _wait_sem;

    if (lcd) {
        //MCU屏依赖于PAP接口进行初始化，需要提前打开。注.板级中PAP设备注册位置在LCD前面。
        if (lcd->type == LCD_MCU_SINGLE_FRAME || lcd->type == LCD_MCU) {
            if (lcd_open_pap() < 0) {
                return;
            }
        }
        //SPI屏依赖于SPI接口进行初始化，需要提前打开。注.板级中SPI设备注册位置在LCD前面。
        if (lcd->type ==  LCD_SPI) {
            if (lcd_open_spi() < 0) {
                return;
            }
        }

        os_sem_create(&_wait_sem, 0);
        __this->lcd_wait_sem = &_wait_sem;
        if (lcd->init) {
            lcd->init(_data);
        }
        os_sem_post(&_wait_sem);
        printf("[LCD]lcd init done\n");
    }
    while (__this->lcd_wait_sem != NULL) {
        os_time_dly(10);
    }

}
static int lcd_init(const struct dev_node *node, void *_data)
{
    int drive_num = 0;
    struct lcd_dev_drive *p;

    list_for_each_lcd_device_drive(p) {
        drive_num++;
    }

    //只支持一个显示屏如果开了多个打开失败
    if (drive_num >= 2) { //直接进断言
        ASSERT(0, "[ERROR]>>>>>>>>>>you enable lcd mub >= 2 you need check lcd_config.h");
    }

    __this->lcd = lcd_dev_match(NULL);
    ASSERT(__this->lcd, "Don't find available lcd driver!!!");
    __this->platform_data = (struct lcd_platform_data *)_data;
    thread_fork("lcd_init", 30, 1024, 0, 0, lcd_init_task, NULL);

    return 0;
}

static int lcd_dev_open(const char *name, struct device **device, void *arg)
{
    union lcd_dev_info *dev;
    *device = &__this->device;
    (*device)->private_data = (void *)__this->lcd;

    if (!__this->lcd) {
        return -ENODEV;
    }
    dev = __this->lcd->dev;

    int err = lcd_init_wait_done();
    if (err) {
        return -ENODEV;
    }
    switch (__this->lcd->type) {
    case LCD_RGB:
        if (!dev->imd.dpi_open_flag) {
            dev->imd.info.drive_mode = LCD_RGB;
            dpi_open(&dev->imd);
            dev->imd.dpi_open_flag = 1;
            printf("[LCD]open lcd_rgb_imd ok");
        } else {
            printf("[LCD]lcd device has been open");
        }
        break;

    case LCD_MIPI:
        if (!dev->mipi.dsi_open_flag) {
            dev->mipi.info.drive_mode = LCD_MIPI;
            dsi_dev_init(&dev->mipi);
            dev->mipi.dsi_open_flag = 1;
            printf("[LCD]open lcd_mipi....");
        } else {
            printf("[LCD]lcd device has been open");
        }
        break;

    case LCD_MCU:
        if (!dev->imd.dpi_open_flag) {
            dev->imd.info.drive_mode = LCD_MCU;
            if ((!__this->lcd_dev) && (lcd_reopen() < 0)) {
                return -ENODEV;
            }
            if (dev->imd.data_out_endian == MODE_BE) {
                __this->draw_buf = malloc(LCD_RGB565_DATA_SIZE);
                if (!__this->draw_buf) {
                    printf("[LCD]lcd driver draw buf malloc fail!!!");
                    return -ENODEV;
                }
                dma2d_init();/// 使用dma2d进行数据端序转换需要先初始化模块
            }
            if (dev->imd.te_mode.te_mode_en) {
                os_sem_create(&__this->te_sem, 0);
                __this->te_id = exti_init(dev->imd.te_mode.gpio, dev->imd.te_mode.edge, lcd_te_interrupt, NULL);
            }
            dev->imd.dpi_open_flag = 1;
        } else {
            printf("[LCD]lcd device has been open");
        }
        break;

    case LCD_MCU_SINGLE_FRAME:
        if (!dev->imd.dpi_open_flag) {
            dev->imd.info.drive_mode = LCD_MCU_SINGLE_FRAME;
            if ((!__this->lcd_dev) && (lcd_reopen() < 0)) {
                return -ENODEV;
            }
            dpi_open(&dev->imd);
            if (dev->imd.te_mode.te_mode_en) {
                os_sem_create(&__this->te_sem, 0);
                __this->te_id = exti_init(dev->imd.te_mode.gpio, dev->imd.te_mode.edge, lcd_te_interrupt, NULL);
            }
            dev->imd.dpi_open_flag = 1;
            printf("[LCD]open lcd_mcu_imd ok");
        } else {
            printf("[LCD]lcd device has been open");
        }
        break;

    case LCD_SPI:
        if (!dev->spi.spi_open_flag) {
            dev->spi.info.drive_mode = LCD_SPI;
            if ((!__this->lcd_dev) && (lcd_reopen() < 0)) {
                return -ENODEV;
            }
            if (dev->spi.data_out_endian == MODE_BE) {
                __this->draw_buf = malloc(LCD_RGB565_DATA_SIZE);
                if (!__this->draw_buf) {
                    printf("[LCD]lcd driver draw buf malloc fail!!!");
                    return -ENODEV;
                }
                dma2d_init();/// 使用dma2d进行数据端序转换需要先初始化模块
            }
            if (dev->spi.te_mode.te_mode_en) {
                os_sem_create(&__this->te_sem, 0);
                __this->te_id = exti_init(dev->spi.te_mode.gpio, dev->spi.te_mode.edge, lcd_te_interrupt, NULL);
            }
            dev->spi.spi_open_flag = 1;
        } else {
            printf("[LCD]lcd device has been open");
        }
        break;
    }

    return 0;
}

static int lcd_dev_ioctl(struct device *device, u32 cmd, u32 arg)
{
    struct lcd_dev_drive *lcd = (struct lcd_dev_drive *)device->private_data;

    if (lcd->type == LCD_MIPI) {
        if (__this->lcd_dev == NULL && lcd->dev->mipi.dsi_open_flag == 0) {
            printf("[LCD]lcd dev not open");
            return 0;
        }
    } else {
        if (__this->lcd_dev == NULL && lcd->dev->imd.dpi_open_flag == 0) {
            printf("[LCD]lcd dev not open");
            return 0;
        }
    }

    switch (cmd) {
    case IOCTL_LCD_RGB_SET_ISR_CB:
        if (lcd->type == LCD_RGB) {
            dpi_set_isr_cb(arg);
        } else if (lcd->type == LCD_MIPI) {
            mipi_set_isr_cb(arg);
        }
        break;
    case IOCTL_LCD_RGB_SET_LINE_ISR_CB:
        if (lcd->type == LCD_RGB) {
            dpi_set_line_isr_cb(arg);
        } else if (lcd->type == LCD_MIPI) {
            mipi_set_line_isr_cb(arg);
        }
        break;

    case IOCTL_LCD_RGB_WAIT_FB_SWAP_FINISH:
        if (lcd->type == LCD_MCU_SINGLE_FRAME) {
            lcd->draw((void *)arg);
        } else if (lcd->type == LCD_MCU) {
            if (__this->lcd->dev->imd.data_out_endian == MODE_BE) {
                jldma2d_endian_trans(__this->draw_buf, (uint8_t *)arg, LCD_W, LCD_H, JLDMA2D_FORMAT_RGB565);
                lcd->draw((void *)__this->draw_buf);
            } else {
                lcd->draw((void *)arg);
            }
        } else if (lcd->type == LCD_SPI) {
            if (__this->lcd->dev->spi.data_out_endian == MODE_BE) {
                jldma2d_endian_trans(__this->draw_buf, (uint8_t *)arg, LCD_W, LCD_H, JLDMA2D_FORMAT_RGB565);
                lcd->draw((void *)__this->draw_buf);
            } else {
                lcd->draw((void *)arg);
            }
        } else if (lcd->type == LCD_MIPI) {
            if (lcd->dev->mipi.info.drive_mode == LCD_MIPI) {
                mipi_wait_fb_swap_finish(0);
            }
        } else {
            if (lcd->dev->imd.info.drive_mode == LCD_RGB) {
                dpi_wait_fb_swap_finish(0);
            }
        }
        break;
    case IOCTL_LCD_RGB_WAIT_LINE_FINISH:
        if (lcd->type == LCD_MIPI) {
            if (lcd->dev->mipi.info.drive_mode == LCD_MIPI) {
                mipi_wait_line_finish(0);
            }
        } else if (lcd->type == LCD_RGB) {
            if (lcd->dev->imd.info.drive_mode == LCD_RGB) {
                dpi_wait_line_finish(0);
            }
        } else {
            printf("[LCD]lcd type unsupport wait line :%d\n", lcd->type);
        }
        break;

    case IOCTL_LCD_RGB_START_DISPLAY:
        if (lcd->type == LCD_MCU_SINGLE_FRAME) {
            lcd->draw((void *)arg);
        } else if (lcd->type == LCD_RGB) {
            dpi_start_display(arg);
        } else if (lcd->type == LCD_MIPI) {
            mipi_start_display(arg);
        }
        __this->lcd_open_flag = 1;

        if (lcd->type == LCD_MCU) {
            if (__this->lcd->dev->imd.data_out_endian == MODE_BE) {
                jldma2d_endian_trans(__this->draw_buf, (uint8_t *)arg, LCD_W, LCD_H, JLDMA2D_FORMAT_RGB565);
                lcd->draw((void *)__this->draw_buf);
            } else {
                lcd->draw((void *)arg);
            }
        }

        if (lcd->type == LCD_SPI) {
            if (__this->lcd->dev->spi.data_out_endian == MODE_BE) {
                jldma2d_endian_trans(__this->draw_buf, (uint8_t *)arg, LCD_W, LCD_H, JLDMA2D_FORMAT_RGB565);
                lcd->draw((void *)__this->draw_buf);
            } else {
                lcd->draw((void *)arg);
            }
        }

        lcd_backlight_ctrl(true);//开启背光
        break;

    case IOCTL_LCD_RGB_GET_LCD_HANDLE:
        *(struct lcd_dev_drive **)arg = lcd;
        break;
    }

    return 0;
}

static int lcd_dev_close(struct device *device)
{
    struct lcd_dev_drive *lcd = (struct lcd_dev_drive *)device->private_data;

    switch (lcd->type) {
    case LCD_RGB:
        if (lcd->dev->imd.dpi_open_flag) {
            dpi_close();
            dmm_deinit();
            lcd->dev->imd.dpi_open_flag = 0;
        }
        break;
    case LCD_MIPI:
        if (lcd->dev->mipi.dsi_open_flag) {
            dsi_video_stop();
            dmm_deinit();
            lcd->dev->mipi.dsi_open_flag = 0;
        }
        break;
    case LCD_MCU_SINGLE_FRAME:
        if (lcd->dev->imd.dpi_open_flag) {
            dpi_close();
            dmm_deinit();
            if (__this->lcd_dev) {
                dev_close(__this->lcd_dev);
                __this->lcd_dev = NULL;
            }
            if (lcd->dev->imd.te_mode.te_mode_en) {
                os_sem_del(&__this->te_sem, OS_DEL_ALWAYS);
                exti_uninit(__this->te_id);
                __this->te_id = 0;
            }
            lcd->dev->imd.dpi_open_flag = 0;
        }
        break;
    case LCD_MCU:
        if (lcd->dev->imd.dpi_open_flag) {
            if (__this->lcd_dev) {
                dev_close(__this->lcd_dev);
                __this->lcd_dev = NULL;
            }
            if (__this->lcd->dev->imd.data_out_endian == MODE_BE) {
                free(__this->draw_buf);
                __this->draw_buf = NULL;
                dma2d_free();
            }
            if (lcd->dev->imd.te_mode.te_mode_en) {
                os_sem_del(&__this->te_sem, OS_DEL_ALWAYS);
                exti_uninit(__this->te_id);
                __this->te_id = 0;
            }
            lcd->dev->imd.dpi_open_flag = 0;
        }
        break;
    case LCD_SPI:
        if (lcd->dev->spi.spi_open_flag) {
            if (__this->lcd_dev) {
                dev_close(__this->lcd_dev);
                __this->lcd_dev = NULL;
            }
            if (__this->lcd->dev->spi.data_out_endian == MODE_BE) {
                free(__this->draw_buf);
                __this->draw_buf = NULL;
                dma2d_free();
            }
            if (lcd->dev->spi.te_mode.te_mode_en) {
                os_sem_del(&__this->te_sem, OS_DEL_ALWAYS);
                exti_uninit(__this->te_id);
                __this->te_id = 0;
            }
            lcd->dev->spi.spi_open_flag = 0;
        }
        break;
    }

    return 0;
}

const struct device_operations lcd_dev_ops = {
    .init  = lcd_init,
    .open  = lcd_dev_open,
    .ioctl = lcd_dev_ioctl,
    .close = lcd_dev_close,
};

#endif
