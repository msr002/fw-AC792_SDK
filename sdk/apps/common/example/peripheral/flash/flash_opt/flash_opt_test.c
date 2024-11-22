#include "app_config.h"
#include "system/includes.h"
#include "fs/fs.h"
#include "asm/sfc_norflash_api.h"

#ifdef USE_FLASH_OPT_TEST_DEMO

static void flash_opt_test_task(void *arg)
{
    printf("norflash_otp test \n");

    u8 buf[32];
    for (int i = 0; i < 32; i++) {
        buf[i] = i;
    }
    norflash_eraser_otp(0);//擦除
    norflash_write_otp(0, buf, 32);//写，读写最大字节：768
    memset(buf, 0, 32);
    norflash_read_otp(0, buf, 32);//读，读写最大字节：768
    put_buf(buf, 32);

    while (1) {
        os_time_dly(10);
    }
}

static int c_main_flash_opt()
{
    os_task_create(flash_opt_test_task, NULL, 10, 1000, 0, "flash_opt_test_task");
    return 0;
}

late_initcall(c_main_flash_opt);

#endif // USE_FLASH_OPT_TEST_DEMO
