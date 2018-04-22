/* drivers/leds/leds-Tiny4412.c
 *
 * (c) 2017 zhaochuang8888@126.com
 *
 * Tiny4412 - LEDs GPIO driver
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/leds.h>

#include <mach/hardware.h>
#include <mach/regs-gpio.h>
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

/* our context */
struct led_desc {
    int           gpio;
    char*       name;
};

static struct led_desc tiny4412_led_gpios[] = {
	{ EXYNOS4212_GPM4(0),"led1"},
	{ EXYNOS4212_GPM4(1),"led2"},
	{ EXYNOS4212_GPM4(2),"led3"},
	{ EXYNOS4212_GPM4(3),"led4"},
};


struct tiny4412_gpio_leds {
	struct led_classdev    cdev;
      int                           gpio;
};

static struct tiny4412_gpio_leds* tiny4412_leds;

static void tiny4412_leds_set(struct led_classdev *led_cdev,
			    enum led_brightness value)
{
    struct tiny4412_gpio_leds * dev = (struct tiny4412_gpio_leds*)led_cdev;
   dev->cdev.brightness = value;
    if(value > 0)
    {
            s3c_gpio_cfgpin(dev->gpio, S3C_GPIO_OUTPUT);
	     gpio_set_value(dev->gpio, 0);        
    } else {
            s3c_gpio_cfgpin(dev->gpio, S3C_GPIO_OUTPUT);
	     gpio_set_value(dev->gpio, 1);     
    }

}


static int __init tiny4412_leds_init(void)
{
       int ret;
       int i=0;
	tiny4412_leds = kzalloc(sizeof(struct tiny4412_gpio_leds)*sizeof(tiny4412_led_gpios)/sizeof(tiny4412_led_gpios[0]), GFP_KERNEL);
	if (tiny4412_leds == NULL) {
		printk( "No memory for device\n");
		return -ENOMEM;
	}
        
        for(i=0; i<sizeof(tiny4412_led_gpios)/sizeof(tiny4412_led_gpios[0]); i++)
        {

            s3c_gpio_cfgpin(tiny4412_led_gpios[i].gpio, S3C_GPIO_OUTPUT);
	     gpio_set_value(tiny4412_led_gpios[i].gpio, 1);
         
            tiny4412_leds[i].cdev.brightness_set = tiny4412_leds_set;
            tiny4412_leds[i].cdev.brightness = LED_OFF;
            tiny4412_leds[i].cdev.max_brightness = LED_FULL;
            tiny4412_leds[i].cdev.name = tiny4412_led_gpios[i].name;
            tiny4412_leds[i].gpio = tiny4412_led_gpios[i].gpio;
          


            ret = led_classdev_register(NULL, &tiny4412_leds[i].cdev);
	     if (ret < 0) {
               i--;
               while(i>=0)
                {
                    led_classdev_unregister(&tiny4412_leds[i].cdev);
                    i--;
                }
	        kfree(tiny4412_leds);
	        return ret;
	     }
        }
        return ret;
}

static void __exit tiny4412_leds_exit(void)
{
    int i=0;
    for(i=0; i<sizeof(tiny4412_led_gpios)/sizeof(tiny4412_led_gpios[0]); i++)
    {
        led_classdev_unregister(&tiny4412_leds[i].cdev);
    }
    kfree(tiny4412_leds);

}

module_init(tiny4412_leds_init);
module_exit(tiny4412_leds_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("zhaochuang@tiny4412.com");

