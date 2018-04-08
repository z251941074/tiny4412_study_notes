
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/moduleparam.h>
#include <linux/slab.h>
#include <linux/ioctl.h>
#include <linux/cdev.h>
#include <linux/delay.h>
 
#include <linux/gpio.h>
#include <mach/gpio.h>
#include <plat/gpio-cfg.h>

#include <linux/device.h>

static int led_gpios[] = {
	EXYNOS4212_GPM4(0),
	EXYNOS4212_GPM4(1),
	EXYNOS4212_GPM4(2),
	EXYNOS4212_GPM4(3),
};

static int tiny4412_led_open(struct inode *node, struct file *file)
{
	printk("zhch debug [%s](%d)\n", __func__, __LINE__);
	int i=0;
	for(i=0; i<4;i++)
	{
		s3c_gpio_cfgpin(led_gpios[i], S3C_GPIO_OUTPUT);
	}
	return 0;
	
}

static int tiny4412_led_close(struct inode *node, struct file *file)
{
	return 0;
}
/*
 *ioctl(fd, which, status)
 *status 0 -->on  1->off   ---
 *which 0--->3
 */
static long  tiny4412_led_ioctl(struct file *file, unsigned cmd, unsigned arg)
{
	if (arg > 4) 
	{
		return -EINVAL;
	}
	if (cmd !=0 && cmd != 1)
	{
		return -EINVAL;
	}
	gpio_set_value(led_gpios[arg], cmd);
	printk("zhch debug [%s](%d)%d %d\n", __func__, __LINE__, arg, cmd);

	return 0;
}


static struct file_operations tiny4412_led_fops = {
	.owner			= THIS_MODULE,
	.open                   = tiny4412_led_open,
	.release                = tiny4412_led_close,
	.unlocked_ioctl	= tiny4412_led_ioctl,
};


static int major=0;
static struct class *led_cls = NULL;
static int __init tiny4412_led_init(void)
{

	major = register_chrdev(0, "led", &tiny4412_led_fops);
	if(major < 0)
	{
		printk("register_chrdev failed\n");
		return -1;
	}
	printk("major:%d\n", major);

	led_cls =  class_create(THIS_MODULE, "led");
	device_create(led_cls, NULL, MKDEV(major,0), NULL, "led");
	return 0;	
}
static void __exit tiny4412_led_exit(void)
{
	device_destroy(led_cls, MKDEV(major, 0));
	class_destroy(led_cls);
	unregister_chrdev(major, "led");

}

module_init(tiny4412_led_init);
module_exit(tiny4412_led_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("zhaochuang@tiny4412.com");



