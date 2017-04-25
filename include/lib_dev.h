#ifndef __LIB_DEV_H__
#define __LIB_DEV_H__

#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <net/if.h>
#include <string.h>
#include <stdlib.h>
#include <linux/rtc.h>
#include <sys/time.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <asm/types.h>
#include <linux/watchdog.h>
#include <sys/stat.h>
#include <signal.h>


#define IO_VAULE_H          55
#define IO_VAULE_L          56

/*  开灯接口 */
int hito_sys_led_on(void);
/*  关灯接口 */
int hito_sys_led_off(void);

/*  看门狗初始化接口,参数为超时时间  */
int hito_watchdog_init(int wdgtimeout);
/*  喂狗 */
int hito_watchdog_keep_alive(void);

/* read aplex serial number */
int hito_read_serial_number(char *dest);
int aplex_num(const char *eth, char *number);


#endif /* __LIB_DEV_H__ */
