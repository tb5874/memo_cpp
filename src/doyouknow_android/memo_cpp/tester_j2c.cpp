#include "tester_j2c.hpp"

extern "C" JNIEXPORT jstring JNICALL Java_com_example_testapi32arm64_MainActivity_testCstrToJstr(JNIEnv *env, jobject /* this */) {
    std::string test_str = "this string is std::string from c++";
    __android_log_print(ANDROID_LOG_INFO, "app", "  [ Speak c++ ] : std::string : %s\n", test_str.c_str());
    return env->NewStringUTF(test_str.c_str());
}

extern "C" JNIEXPORT jint JNICALL Java_com_example_testapi32arm64_MainActivity_testCint32ToJint(JNIEnv *env, jobject /* this */) {
    long int test_int32 = 0;
    jint get_jint = static_cast<jint>(test_int32);
    return get_jint;
}

extern "C" JNIEXPORT void JNICALL Java_com_example_testapi32arm64_MainActivity_testJintToCint32(JNIEnv *env, jobject /* this */, jint get_jint) {
    long int get_cint32 = static_cast<long int>(get_jint);
    __android_log_print(ANDROID_LOG_INFO, "app", "  [ Speak c++ ] : jint get_jint -> long int get_cint32 : %d\n", get_cint32);
    return;
}

extern "C" JNIEXPORT void JNICALL Java_com_example_testapi32arm64_MainActivity_testJbufToC(JNIEnv *env, jobject /* this */, jobject get_jbuf) {

    if (get_jbuf == nullptr) {

        __android_log_print(ANDROID_LOG_INFO, "app", "  [ Speak c++ ] : get_jbuf is nullptr\n");

    }
    else{

        void* jbuf = env->GetDirectBufferAddress(get_jbuf);
        __android_log_print(ANDROID_LOG_INFO, "app", "  [ Speak c++ ] : ((unsigned char*)jbuf)[0] : %x\n", ((unsigned char*)jbuf)[0]);
        __android_log_print(ANDROID_LOG_INFO, "app", "  [ Speak c++ ] : ((unsigned char*)jbuf)[1] : %x\n", ((unsigned char*)jbuf)[1]);
        __android_log_print(ANDROID_LOG_INFO, "app", "  [ Speak c++ ] : ((unsigned char*)jbuf)[2] : %x\n", ((unsigned char*)jbuf)[2]);
        __android_log_print(ANDROID_LOG_INFO, "app", "  [ Speak c++ ] : ((unsigned char*)jbuf)[3] : %x\n", ((unsigned char*)jbuf)[3]);

        long int get_cint32 = 0;
        ((char*)&get_cint32)[0] = ((char*)jbuf)[3];
        ((char*)&get_cint32)[1] = ((char*)jbuf)[2];
        ((char*)&get_cint32)[2] = ((char*)jbuf)[1];
        ((char*)&get_cint32)[3] = ((char*)jbuf)[0];
        __android_log_print(ANDROID_LOG_INFO, "app", "  [ Speak c++ ] : ((char*)&get_cint32)[0] = ((char*)jbuf)[3]\n");
        __android_log_print(ANDROID_LOG_INFO, "app", "  [ Speak c++ ] : ((char*)&get_cint32)[1] = ((char*)jbuf)[2]\n");
        __android_log_print(ANDROID_LOG_INFO, "app", "  [ Speak c++ ] : ((char*)&get_cint32)[2] = ((char*)jbuf)[1]\n");
        __android_log_print(ANDROID_LOG_INFO, "app", "  [ Speak c++ ] : ((char*)&get_cint32)[3] = ((char*)jbuf)[0]\n");
        __android_log_print(ANDROID_LOG_INFO, "app", "  [ Speak c++ ] : get_cint32 : %d\n", get_cint32);

        get_cint32 = 4321;
        ((char*)jbuf)[3] = ((char*)&get_cint32)[0];
        ((char*)jbuf)[2] = ((char*)&get_cint32)[1];
        ((char*)jbuf)[1] = ((char*)&get_cint32)[2];
        ((char*)jbuf)[0] = ((char*)&get_cint32)[3];
        __android_log_print(ANDROID_LOG_INFO, "app", "  [ Speak c++ ] : modify get_cint32 : %d\n", get_cint32);
        __android_log_print(ANDROID_LOG_INFO, "app", "  [ Speak c++ ] : = ((char*)jbuf)[3] = ((char*)&get_cint32)[0]\n");
        __android_log_print(ANDROID_LOG_INFO, "app", "  [ Speak c++ ] : = ((char*)jbuf)[2] = ((char*)&get_cint32)[1]\n");
        __android_log_print(ANDROID_LOG_INFO, "app", "  [ Speak c++ ] : = ((char*)jbuf)[1] = ((char*)&get_cint32)[2]\n");
        __android_log_print(ANDROID_LOG_INFO, "app", "  [ Speak c++ ] : = ((char*)jbuf)[0] = ((char*)&get_cint32)[3]\n");

    };

    return;

}
