#ifndef ANDROID_LED_INTERFACE_H
#define ANDROID_LED_INTERFACE_H

#include <stdint.h>
#include <sys/cdefs.h>
#include <sys/types.h>

#include <hardware/hardware.h>

__BEGIN_DECLS

struct  led_device_t {
    struct hw_device_t common;
    int (*led_ioctrl)(struct led_device_t* dev, int which, int status);
    int (*led_open)(struct led_device_t* dev);
};


__END_DECLS

#endif  // ANDROID_LED_INTERFACE_H

