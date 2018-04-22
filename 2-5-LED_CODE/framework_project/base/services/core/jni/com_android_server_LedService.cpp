/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_TAG "LedService"

#include "jni.h"
#include "JNIHelp.h"
#include "android_runtime/AndroidRuntime.h"

#include <utils/Log.h>

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <hardware/hal_led.h>

namespace android
{

static  struct  led_device_t* leddev;
static int  LedOpen(JNIEnv *env, jobject clazz)
{
    int err;
    hw_module_t* module;
    struct hw_device_t* device;

    err = hw_get_module("led", (hw_module_t const**)&module);
    if (err == 0) {
        err = module->methods->open(module, NULL, &device);
        leddev = (struct led_device_t *)device;
        leddev->led_open(leddev);
    }
    ALOGI("[%s](%d) LedOpen err = %d\n", __func__, __LINE__, err);
    return 0;
}

static int  LedCtrl(JNIEnv *env, jobject clazz, int which, int status)
{
    int ret;
    ret = leddev->led_ioctrl(leddev, which, status);
    ALOGI("[%s](%d) ledCtrl(%d, %d), ret = %d\n", __func__, __LINE__, which, status, ret);
    return ret;
}

static void LedClose(JNIEnv *env, jobject clazz)
{
    return ;
}

static JNINativeMethod method_table[] = {
    { "native_LedOpen", "()I", (void*)LedOpen },
    { "native_LedCtrl", "(II)I", (void*)LedCtrl },
    { "native_LedClose", "()V", (void*)LedClose }
};

int register_android_server_LedService(JNIEnv *env)
{
    return jniRegisterNativeMethods(env, "com/android/server/LedService",
            method_table, NELEM(method_table));
}
};

