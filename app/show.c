#include "../include/lib_dev.h"

int main(int argc, char *argv[])
{
    char mac_num[12];
    int retval;

    if (strcasecmp(argv[1], "sn"))
    {
        printf("please input the true argument!!!\n");
        return -1;
    }

    //retval = aplex_num("eth0", mac_num);
    retval = hito_read_serial_number(mac_num);
    printf("mac: %s\n", mac_num);

    return 0;
}
