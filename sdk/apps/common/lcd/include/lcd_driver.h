#ifndef __LCD_DRIVER_H__
#define __LCD_DRIVER_H__

#include "asm/dpi.h"
#include "asm/pap.h"
#include "asm/dsi.h"

#include "system/includes.h"
#include "device/device.h"
#include "os/os_api.h"

#include "device/iic.h"
#include "touch_event.h"

#define   BLACK     0x0000       //黑色
#define   NAVY      0x000F       //深蓝色
#define   DGREEN    0x03E0       //深绿色
#define   DCYAN     0x03EF       //深青色
#define   MAROON    0x7800       //深红色
#define   PURPLE    0x780F       //紫色
#define   OLIVE     0x7BE0       //橄榄绿
#define   LGRAY     0xC618       //灰白色
#define   DGRAY     0x7BEF       //深灰色
#define   BLUE      0x001F       //蓝色
#define   GREEN     0x07E0       //绿色
#define   CYAN      0x07FF       //青色
#define   RED       0xF800       //红色
#define   MAGENTA   0xF81F       //品红
#define   YELLOW    0xFFE0       //黄色
#define   WHITE     0xFFFF       //白色

#define IOCTL_LCD_RGB_SET_ISR_CB                _IOW('F', 1, sizeof(void *(*)(void)))
#define IOCTL_LCD_RGB_WAIT_FB_SWAP_FINISH       _IOW('F', 2, sizeof(int))
#define IOCTL_LCD_RGB_START_DISPLAY             _IOW('F', 3, sizeof(void *))
#define IOCTL_LCD_RGB_GET_LCD_HANDLE            _IOR('F', 4, sizeof(struct lcd_dev_drive **))
#define IOCTL_LCD_RGB_SET_LINE_ISR_CB           _IOW('F', 5, sizeof(int (*)(int)))
#define IOCTL_LCD_RGB_WAIT_LINE_FINISH          _IOW('F', 6, sizeof(int))


struct lcd_platform_data {
    const char *lcd_name;
    struct {
        u8 backlight_value;
        int backlight;
        int lcd_reset;
        int lcd_cs;
        int lcd_rs;
    } lcd_io;
};

#define LCD_PLATFORM_DATA_BEGIN(data) \
static const struct lcd_platform_data data = {

#define LCD_PLATFORM_DATA_END() \
};

struct spi_dev {
    struct basic_info info;
    struct te_mode_ctrl te_mode;
    enum LCD_ENDIAN data_out_endian;
    char *interface_name;
    u8 spi_open_flag;
};

#define REGISTER_IMD_DEVICE_BEGIN(info) \
    static union lcd_dev_info info SEC_USED(.lcd_device) = { \
        .imd

#define REGISTER_IMD_DEVICE_END() \
    };

#define REGISTER_MIPI_DEVICE_BEGIN(info) \
    static union lcd_dev_info info SEC_USED(.lcd_device) = { \
        .mipi
#define REGISTER_MIPI_DEVICE_END() \
    };

#define REGISTER_LCD_SPI_DEVICE_BEGIN(info) \
    static union lcd_dev_info info SEC_USED(.lcd_device) = { \
        .spi
#define REGISTER_LCD_SPI_DEVICE_END() \
    };

union lcd_dev_info {
    struct imd_dev imd;
    struct mipi_dev mipi;
    struct spi_dev spi;
};

struct lcd_dev_drive {
    const char *logo;
    enum LCD_IF type;
    int (*init)(void *_data);
    int (*draw)(void *_data);
    int (*uninit)(void *_data);
    void (*bl_ctrl)(void *_data, u8 onoff);
    union lcd_dev_info *dev;
};

#define REGISTER_LCD_DEVICE_DRIVE(dev) \
	static const struct lcd_dev_drive dev_drive SEC_USED(.lcd_device_drive)

#define list_for_each_lcd_device_drive(p) \
	for (p=lcd_device_drive_begin; p < lcd_device_drive_end; p++)

#define lcd_delay(x) msleep(x)

extern struct lcd_dev_drive lcd_device_drive_begin[];
extern struct lcd_dev_drive lcd_device_drive_end[];
extern const struct device_operations lcd_dev_ops;

void lcd_cs_pinstate(u8 state);
void lcd_rs_pinstate(u8 state);
void lcd_rst_pinstate(u8 state);
void WriteCOM(u8 cmd);
void WriteDAT_8(u8 dat);
void WriteDAT_one_page(u8 *dat, int len);
u16 lcd_get_rotate(void);
int lcd_touch_width_height_rotate(u16 *w, u16 *h);
int lcd_touch_xy_coord_rotate(u16 *x, u16 *y, u8 status);

#endif

