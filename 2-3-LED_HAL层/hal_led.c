

#include <cutils/log.h>

#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#include <sys/ioctl.h>
#include <sys/types.h>

#include <hardware/hardware.h>
#include <hardware/hal_led.h>

static int fd;
static int open_leddevice(struct led_device_t* dev)
{
	fd =open ("/dev/led", O_RDWR);
	ALOGI("[%s](%d) fd=%d\n", __func__, __LINE__, fd);
	if(fd > 0)
		return 0;
	else
		return -1;
}

static int ioctrl_leddevice(struct led_device_t* dev, int which, int status)
{
	int ret = ioctl(fd, status, which);	
	ALOGI("[%s](%d) ledCtrl(%d, %d),fd =%d, ret = %d\n", __func__, __LINE__, which, status, fd, ret);
	return ret;
}
static void close_leddevice(struct hw_device_t* device)
{
	close(fd);
	ALOGI("[%s](%d)\n", __func__, __LINE__);
	return;
}

static int open_led(const struct hw_module_t* module, const char* id,
            struct hw_device_t** device)
{
	  
    struct led_device_t *dev = malloc(sizeof( struct led_device_t));
    memset(dev, 0, sizeof(*dev));

    dev->common.module = (struct hw_module_t*)module;
    dev->common.close = (int (*)(struct hw_device_t*))close_leddevice;
    dev->led_open = open_leddevice;
    dev->led_ioctrl = ioctrl_leddevice;

    *device = (struct hw_device_t*)dev;  
    return 0;
}


/*
  *第二部: 实现module中methods的open函数
  */

static struct hw_module_methods_t led_module_methods = {
    .open =  open_led,
};

/*
 * 第一步:The led Module
 */
struct hw_module_t HAL_MODULE_INFO_SYM = {
    .tag = HARDWARE_MODULE_TAG,
    .id = "led",
    .methods = &led_module_methods,
};




