#include "../include/lib_dev.h"

static void string_translate(char *num)
{
    char tmp;
    int i;

    for (i = 0; i < 6; i++)
    {
        tmp = num[i];
        num[i] = num[11 - i];
        num[11 - i] = tmp;
    }

    for (i = 0; i < 6; i++)
    {
        tmp = num[i];
        num[i] = num[i + 6];
        num[i + 6] = tmp;
    }
    for (i = 0; i < 6; i++)
    {
        if(num[i] < ('9' - (char)i) && num[i] > '0')
            num[i] += i;
        if(num[i] < 't' && num[i] > 'a')
            num[i] += (char)i;
        if(num[i] < 'T' && num[i] > 'A')
            num[i] += (char)i;

        if(num[i + 6] < ('9'- (char)i) && num[i + 6] > '0')
            num[i + 6] += (char)i;
        if(num[i + 6] < 't' && num[i + 6] > 'a')
            num[i + 6] += (char)i;
        if(num[i + 6] < 'T' && num[i + 6] > 'A')
            num[i + 6] += (char)i;
    }
}

int aplex_num(const char *eth, char *number)
{
    struct ifreq ifreq;
    int sock;

    if ((sock=socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket");
        return 2;
    }

    strcpy(ifreq.ifr_name, eth);
    if (ioctl(sock, SIOCGIFHWADDR, &ifreq) < 0)
    {
        perror("ioctl");
        return 3;
    }

    sprintf(number, "%02x%02x%02x%02x%02x%02x",
            (unsigned char)ifreq.ifr_hwaddr.sa_data[0],
            (unsigned char)ifreq.ifr_hwaddr.sa_data[1],
            (unsigned char)ifreq.ifr_hwaddr.sa_data[2],
            (unsigned char)ifreq.ifr_hwaddr.sa_data[3],
            (unsigned char)ifreq.ifr_hwaddr.sa_data[4],
            (unsigned char)ifreq.ifr_hwaddr.sa_data[5]);
    string_translate(number);
    return 0;
}

int hito_read_serial_number(char *dest)
{
    int retval;

    retval = aplex_num("eth0", dest);
    return retval;
}


int hito_sys_led_on(void)
{
    system("echo 1 > /sys/class/gpio/gpio29/value");
}

int hito_sys_led_off(void)
{
    system("echo 0 > /sys/class/gpio/gpio29/value");
}

int watchdog_fd = 0;
int hito_watchdog_init(int wdgtimeout)
{
    int ret_val, data;
    watchdog_fd = open("/dev/watchdog", O_WRONLY);
    if(watchdog_fd == -1)
    {
        perror("watchdog");
        return -1;
    }

    /* 获取第一次看门狗超时时间  */
    ret_val = ioctl (watchdog_fd, WDIOC_GETTIMEOUT, &data);
    if(ret_val)
    {
        printf("\nWatchdog Timer : WDIOC_GETTIMEOUT failed\n");
        return -1;
    }
    else
    {
        printf("\nCurrent timeout value is : %d seconds\n", data);
    }

    /* 设置自己的看门狗超时时间  */
    ret_val = ioctl (watchdog_fd, WDIOC_SETTIMEOUT, &wdgtimeout);
    if (ret_val)
    {
        printf ("Watchdog Timer : WDIOC_SETTIMEOUT failed\n");
        return -1;
    }
    else
    {
        printf ("\nNew timeout value is : %d seconds\n", wdgtimeout);
    }

    if (1 != write(watchdog_fd, "\0", 1))
    {
        printf("Write failed\n");
        return -1;
    }
    else
    {
        printf("Write succeeded\n");
        return 0;
    }

    return 0;
}

int hito_watchdog_keep_alive(void)
{
    if (1 != write(watchdog_fd, "\0", 1))
    {
        printf("Write failed\n");
        return -1;
    }
    else
    {
        printf("Write succeeded\n");
        return 0;
    }
}

