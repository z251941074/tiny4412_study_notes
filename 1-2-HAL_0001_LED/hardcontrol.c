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
JNI_OnLoad(JavaVM* vm, void *reserved) //����JNI_OnLoad�����������밴�������ķ�ʽ����
{
JNIEnv* env = NULL; //ע��ʱ��JNIEnv��ʵ�ֵģ����Ա������Ȼ�ȡ��
jint result = -1;
jclass cls;

if((*vm)->GetEnv(vm, (void**)&env, JNI_VERSION_1_4) != JNI_OK) //��JavaVM��ȡJNIEnv��һ��ʹ��1.4�İ汾
  return JNI_ERR;


static const char* const kClassName="com/example/administrator/hardlibrary/HardControl";

cls = (*env)->FindClass(env, kClassName); //��������ҵ�Ҫע����࣬ǰ����������Ѿ����ص�java������С� ����˵������̬�����native��������֮�䣬û���κζ�Ӧ��ϵ��

if(cls == NULL)
{
  printf("cannot get class:%s\n", kClassName);
  return JNI_ERR;
}

if((*env)->RegisterNatives(env, cls,methods, sizeof(methods)/sizeof(methods[0]))!= JNI_OK) //������ǹؼ��ˣ��ѱ��غ�����һ��java�෽����������������֮ǰ�Ƿ��������һ�ɰ�֮ǰ���滻����
{
  printf("register native method failed!\n");
  return JNI_ERR;
}

return JNI_VERSION_1_4; //�������Ҫ�����뷵�ذ汾��������ػ�ʧ�ܡ�
}




