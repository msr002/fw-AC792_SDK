#include "system/includes.h"
#include "app_config.h"
#include "device/uart.h"
#include "lwip.h"
#include "lwip/inet.h"
#include "syscfg/syscfg_id.h"
#include "wifi/wifi_connect.h"
#include "lwip/sockets.h"
#include "lwip/netdb.h"

static char ssid[33];
static char pwd[65];
void wifi_sta_connect(char *ssid, char *pwd, char save);

void cmd_do(char *buf)
{
    char *cmd = buf;
    if (buf == NULL) {
        return;
    }

    printf("cmd rec:%s\n", cmd);

    if (0 == memcmp(buf, "sta", strlen("sta"))) {
        if (sscanf(buf, "sta %s %s", ssid, pwd) == 2) {
            printf("ssid : %s, pwd: %s\n", ssid, pwd);
            wifi_sta_connect(ssid, pwd, 1);
        } else if (sscanf(buf, "sta %s", ssid) == 1) {
            wifi_sta_connect(ssid, "", 1);
        }
    } else if (0 == memcmp(buf, "go_start", strlen("go_start"))) {
    } else if (0 == memcmp(buf, "gc_start", strlen("gc_start"))) {
    } else if (0 == memcmp(buf, "scan", strlen("scan"))) {
        void wifi_get_list_example(void);
        wifi_get_list_example();
    }
}


static u8 buf[1 * 1024] __attribute__((aligned(32))); //用于串口接收缓存数据的循环buf
static void uart_test_main(void *priv)
{
    char recv_buf[256];
    int len;
    int cnt = 0;
    void *hdl = dev_open("uart1", NULL);
    if (!hdl) {
        printf("open uart err !!!\n");
        return ;
    }
    /* 1 . 设置串口接收缓存数据的循环buf地址 */
    dev_ioctl(hdl, IOCTL_UART_SET_CIRCULAR_BUFF_ADDR, (int)buf);

    /* 1 . 设置串口接收缓存数据的循环buf长度 */
    dev_ioctl(hdl, IOCTL_UART_SET_CIRCULAR_BUFF_LENTH, sizeof(buf));

    /* 3 . 设置接收数据为阻塞方式,需要非阻塞可以去掉,建议加上超时设置 */
    dev_ioctl(hdl, IOCTL_UART_SET_RECV_BLOCK, 1);

    /* u32 parm = 1000; */
    /* dev_ioctl(hdl, IOCTL_UART_SET_RECV_TIMEOUT, (u32)parm); //超时设置 */

    /* 4 . 使能特殊串口,启动收发数据 */
    dev_ioctl(hdl, IOCTL_UART_START, 0);

    printf("uart_test_task running");

    while (1) {
        /* 5 . 接收数据 */
        len = dev_read(hdl, recv_buf, sizeof(recv_buf));
        if (len <= 0) {
            printf("\n  uart recv err len = %d\n", len);
            if (len == UART_CIRCULAR_BUFFER_WRITE_OVERLAY) {
                printf("\n UART_CIRCULAR_BUFFER_WRITE_OVERLAY err\n");
                dev_ioctl(hdl, IOCTL_UART_FLUSH, 0); //如果由于用户长期不取走接收的数据导致循环buf接收回卷覆盖,因此直接冲掉循环buf所有数据重新接收
            } else if (len == UART_RECV_TIMEOUT) {
                puts("UART_RECV_TIMEOUT...\r\n");
            }
            continue;
        }
        recv_buf[len] = '\0';
        cmd_do(recv_buf);
    }
    dev_close(hdl);
}

static int c_main(void)
{
    os_task_create(uart_test_main, NULL, 10, 4 * 1024, 0, "uart_test_main");
    return 0;
}

late_initcall(c_main);





