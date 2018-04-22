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

namespace android
{
static int fd;

static int  LedOpen(JNIEnv *env, jobject clazz)
{
	fd = open("/dev/led", O_RDWR);
	ALOGI("[%s](%d)fd=%d\n", __func__, __LINE__, fd);
	return 0;
}

static int  LedCtrl(JNIEnv *env, jobject clazz, int which, int status)
{
	int ret;
	ret = ioctl(fd, status, which);
	ALOGI("[%s](%d)ret=%d, fd=%d,which=%d, status=%d\n", __func__, __LINE__, ret, fd, which, status);	
	return ret;
}

static void LedClose(JNIEnv *env, jobject clazz)
{
    close(fd);
    ALOGI("[%s](%d)\n", __func__, __LINE__);	
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

