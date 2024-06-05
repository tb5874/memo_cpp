#include <string>
#include <jni.h>
#include <android/log.h>

// for JAVA <-> C++, test function
extern "C" JNIEXPORT jstring JNICALL Java_com_example_testapi32arm64_MainActivity_testCstrToJstr(JNIEnv *env, jobject /* this */);
extern "C" JNIEXPORT jint JNICALL Java_com_example_testapi32arm64_MainActivity_testCint32ToJint(JNIEnv *env, jobject /* this */);
extern "C" JNIEXPORT void JNICALL Java_com_example_testapi32arm64_MainActivity_testJintToCint32(JNIEnv *env, jobject /* this */, jint get_jint);
extern "C" JNIEXPORT void JNICALL Java_com_example_testapi32arm64_MainActivity_testJbufToC(JNIEnv *env, jobject /* this */, jobject get_jbuf);
