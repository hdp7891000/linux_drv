#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <fcntl.h>
#include "./led_drv.h"

#define DEV_NAME "/dev/led"

int main(int argc, char *argv[])
{
    int i;
    int fd = 0;
    
    fd = open (DEV_NAME, O_RDONLY);
    if (fd < 0) {
        perror("Open "DEV_NAME" Failed!\n");
        exit(1);
    }
    
    printf("flash 20 1s\n");
    for (i=0; i<20; i++) {
        ioctl(fd, LED_ON);
        sleep(1);
        ioctl(fd, LED_OFF);
        sleep(1);
    }
    
    printf("flash 20 3s\n");
    for (i=0; i<20; i++) {
        ioctl(fd, LED_ON);
        sleep(3);
        ioctl(fd, LED_OFF);
        sleep(3);
    }
    
    printf("flash over\n");
    close(fd);
    return 0;
}