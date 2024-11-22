#include "lcd_driver.h"
#include "lcd_config.h"
#include "asm/exti.h"
#include "gpio.h"

#if TCFG_LCD_MCU_ILI9488_320X480

#define REGFLAG_DELAY 0x45

static void ili9488_set_direction(u8 dir)
{
    if (dir == 0) {
        WriteCOM(0x36);
        WriteDAT_8(0xd8);
    } else {
        WriteCOM(0x36);
        WriteDAT_8(0x08);
    }
}

static void ili9488_reset(void)
{
    printf("ili9488 mcu lcd reset\n");
    lcd_rst_pinstate(1);
    lcd_rs_pinstate(1);
    lcd_cs_pinstate(1);

    lcd_rst_pinstate(1);
    lcd_delay(60);
    lcd_rst_pinstate(0);
    lcd_delay(10);
    lcd_rst_pinstate(1);
    lcd_delay(100);
}

typedef struct {
    u8 cmd;
    u8 cnt;
    u8 dat[10];
} InitCode;

static const InitCode ili9488_code[] = {
    {0x21, 0},//开启数据翻转模式
    {0x13, 1, {0x00}},//开始正常显示模式
#if TCFG_LCD_TE_ENABLE
    {0x35, 1, {0x00}},//开启te
#else
    {0x34, 0},//关TE
#endif
    {0xB1, 2, {0x90, 0x11}}, //A0 11 60fps
    {0x36, 1, {0xd8}},//可以控制旋转/flip/rota: D7-Y D6-X B5-V B4-L B3-RGB B2-H
    {0xC1, 1, {0x41}},
    {0XF7, 4, {0xA9, 0x51, 0x2C, 0x82}},
    {0xC1, 1, {0x41}},
    {0xC0, 2, {0x0f, 0x0f}},
    {0xC2, 1, {0x22}},
    {0XC5, 3, {0x00, 0x53, 0x80}},
    {0xB4, 1, {0x02}},
    {0xB7, 1, {0xc6}},
    {0xB6, 2, {0x02, 0x42}},
    {0xBE, 2, {0x00, 0x04}},
    {0xE9, 1, {0x00}},
    {0x3a, 1, {0x55}},
    {0x11, 0},//Sleep out
    {REGFLAG_DELAY, 200},
    {0x29, 0},//开显示
};

static void ili9488_init_code(const InitCode *code, u8 cnt)
{
    for (u8 i = 0; i < cnt; i++) {
        if (code[i].cmd == REGFLAG_DELAY) {
            lcd_delay(code[i].cnt);
        } else {
            WriteCOM(code[i].cmd);
            for (u8 j = 0; j < code[i].cnt; j++) {
                WriteDAT_8(code[i].dat[j]);
            }
        }
    }
}

static int ili9488_show_page(void *data)
{
    WriteCOM(0x2c);
    WriteDAT_one_page((u8 *)data, LCD_RGB565_DATA_SIZE);
    return 0;
}

static void ili9488_test(void)
{
    static u8 *buf = NULL;
    u32 color;
    u32 i;
    buf = malloc(LCD_W * LCD_H * 2);
    if (buf == NULL) {
        printf("[ili9488] malloc buf error\n");
        return;
    }

    color = RED;
    for (i = 0; i < LCD_W * LCD_H * 1 / 4; i++) {
        buf[2 * i] = (color >> 8) & 0xff;
        buf[2 * i + 1] = color & 0xff;
    }

    color = GREEN;
    for (; i < LCD_W * LCD_H * 2 / 4; i++) {
        buf[2 * i] = (color >> 8) & 0xff;
        buf[2 * i + 1] = color & 0xff;
    }

    color = BLUE;
    for (; i < LCD_W * LCD_H * 3 / 4; i++) {
        buf[2 * i] = (color >> 8) & 0xff;
        buf[2 * i + 1] = color & 0xff;
    }

    color = YELLOW;
    for (; i < LCD_W * LCD_H * 4 / 4; i++) {
        buf[2 * i] = (color >> 8) & 0xff;
        buf[2 * i + 1] = color & 0xff;
    }

    while (1) {
        printf("ili9488_test");
        /* ili9488_show_page(buf); */
        for (int j = 0;  j < LCD_W * LCD_H * 2; j++) {
            WriteDAT_8(buf[j]);
        }
        os_time_dly(100);
    }
}

static void ili9488_backctrl(void *_data, u8 on)
{
    struct lcd_platform_data *data = (struct lcd_platform_data *)_data;
    if (on) {
        gpio_direction_output(data->lcd_io.backlight, data->lcd_io.backlight_value);
    } else {
        gpio_direction_output(data->lcd_io.backlight, !data->lcd_io.backlight_value);
    }
}

static int ili9488_init(void *arg)
{
    printf("LCD_ili9488 init_start\n");
    ili9488_reset();
    ili9488_init_code(ili9488_code, ARRAY_SIZE(ili9488_code));
    ili9488_set_direction(0);
    /* thread_fork("ili9488_test", 28, 1024, 0, 0, ili9488_test, NULL); */
    printf("LCD_ili9488 config succes\n");
    return 0;
}

REGISTER_IMD_DEVICE_BEGIN(lcd_mcu_dev) = {
    .info = {
        .test_mode 	     = false,
        .test_mode_color = 0x0000ff,
        .bg_color   	 = 0x00ff00,
        .xres 			 = LCD_W,
        .yres 			 = LCD_H,
        .target_xres 	 = LCD_W,
        .target_yres 	 = LCD_H,
        .sample          = SAMP_YUV420,
        .format          = FORMAT_RGB565,
        .len 			 = LEN_256,
        .interlaced_mode = INTERLACED_NONE,
        .rotate          = ROTATE_0,

        .adjust = {
            .r_gain = 1.0,
            .g_gain = 1.0,
            .b_gain = 1.0,
            .bright_gain = 1.0,
            .contrast_gain = 1.0,
            .saturation_gain = 1.0,
            .mean = 128,
            .angle = 0,
            .mode = 0,
        },

        .in_swap        = false, //输入数据RB交换
        .out_swap       = false, //输出数据RB交换
#if (LV_COLOR_DEPTH == 32)
        .in_fmt         = LCD_IN_ARGB888,
        .dither_en      = true,  //使能dither 使能将低位转换为高位解决光圈问题
#else
        .in_fmt         = LCD_IN_RGB565,
        .dither_en      = false, //使能dither 0低位截断 1dither
#endif
        .out_fmt        = LCD_OUT_RGB565,
        .in_bt601       = false, //yuv422输入 转换0 bt601, 1 bt709
        .out_bt601      = false, //yuv422输出 转换0 bt601, 1 bt709
    },

    .data_out_mode   = MODE_BE,//RGB565模式生效 RGB888调节swap
    .set_io_hd       = 1,
    .ncycle          = CYCLE_TWO,
    .data_width      = PORT_8BITS,

    .dclk_set        = CLK_DIS,
    .sync0_set       = CLK_EN  | SIGNAL_DEN,
    .sync1_set       = CLK_DIS | SIGNAL_HSYNC,
    .sync2_set       = CLK_DIS | SIGNAL_VSYNC,

    .lcd_group       = PORT_GROUP_AA,
    .clk_cfg	 	 = PLL2_CLK_192M   | DIVA_3 | DIVB_2,
    .dclk_cfg        = DPI_CLK_STD_48M | DIVA_1 | DIVB_1,

    .timing = {
        .hori_total 		    = (320 + 40) * 2,
        .hori_sync 		        = 20 * 2,
        .hori_back_porth 	    = 20 * 2,
        .hori_pixel 	        = 320,

        .vert_total 		    = 480 + 20,
        .vert_sync 		        = 10,
        .vert_back_porth_odd 	= 10,
        .vert_back_porth_even 	= 0,
        .vert_pixel 	        = 480,
    },

#if TCFG_LCD_TE_ENABLE
    .te_mode = {
        .te_mode_en      = 1,
        .edge            = EDGE_NEGATIVE,
        .gpio            = TCFG_LCD_TE_IO,
    },
#endif // TCFG_LCD_TE_ENABLE

},
REGISTER_IMD_DEVICE_END()

REGISTER_LCD_DEVICE_DRIVE(lcd_dev_mcu)  = {
    .logo       = "lcd_mcu",
    .type		= LCD_MCU_SINGLE_FRAME,
    /* .type		= LCD_MCU, */
    .dev    	= &lcd_mcu_dev,
    .init		= ili9488_init,
    .draw       = ili9488_show_page,
    .bl_ctrl	= ili9488_backctrl,
};

#endif // TCFG_LCD_MCU_ILI9488_320X480
