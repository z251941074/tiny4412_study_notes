#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <android/log.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#ifndef  LOG_TAG  
#define  LOG_TAG    "hardcontrolJNI"  
#endif

#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)  
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__) 

static jint fd = 0;
jint ledOpen(JNIEnv *env, jobject cls)
{
	fd =open ("/dev/led", O_RDWR);
	LOGI("[%s](%d) fd=%d\n", __func__, __LINE__, fd);
	if(fd > 0)
		return 0;
	else
		return -1;
}
void ledClose(JNIEnv *env, jobject cls)
{
	close(fd);
	LOGI("[%s](%d)\n", __func__, __LINE__);
	return ;
}
jint ledCtrl(JNIEnv *env, jobject cls, jint which, jint status)
{
	int ret = ioctl(fd, status, which);	
	LOGI("[%s](%d) ledCtrl(%d, %d),fd =%d, ret = %d\n", __func__, __LINE__, which, status, fd, ret);
	return ret;
}


static const JNINativeMethod methods[] = {
		{"ledOpen", "()I",  (void *)ledOpen},
		{"ledClose", "()V", (void *)ledClose},
		{"ledCtrl", "(II)I", (void *)ledCtrl},
};

JNIEXPORT jint  JNICALL
JNI_OnLoad(JavaVM* vm, void *reserved) //这是JNI_OnLoad的声明，必须按照这样的方式声明
{
JNIEnv* env = NULL; //注册时在JNIEnv中实现的，所以必须首先获取它
jint result = -1;
jclass cls;

if((*vm)->GetEnv(vm, (void**)&env, JNI_VERSION_1_4) != JNI_OK) //从JavaVM获取JNIEnv，一般使用1.4的版本
  return JNI_ERR;


static const char* const kClassName="com/example/administrator/hardlibrary/HardControl";

cls = (*env)->FindClass(env, kClassName); //这里可以找到要注册的类，前提是这个类已经加载到java虚拟机中。 这里说明，动态库和有native方法的类之间，没有任何对应关系。

if(cls == NULL)
{
  printf("cannot get class:%s\n", kClassName);
  return JNI_ERR;
}

if((*env)->RegisterNatives(env, cls,methods, sizeof(methods)/sizeof(methods[0]))!= JNI_OK) //这里就是关键了，把本地函数和一个java类方法关联起来。不管之前是否关联过，一律把之前的替换掉！
{
  printf("register native method failed!\n");
  return JNI_ERR;
}

return JNI_VERSION_1_4; //这里很重要，必须返回版本，否则加载会失败。
}




