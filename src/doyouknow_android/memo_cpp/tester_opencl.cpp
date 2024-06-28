#include "tester_opencl.hpp"

// for global definition OpenCL functor
def_clGetPlatformIDs                    func_clGetPlatformIDs                   = nullptr;
def_clGetPlatformInfo                   func_clGetPlatformInfo                  = nullptr;
def_clGetDeviceIDs                      func_clGetDeviceIDs                     = nullptr;
def_clGetDeviceInfo                     func_clGetDeviceInfo                    = nullptr;
def_clCreateContext                     func_clCreateContext                    = nullptr;
def_clCreateCommandQueueWithProperties  func_clCreateCommandQueueWithProperties = nullptr;
def_clCreateProgramWithSource           func_clCreateProgramWithSource          = nullptr;
def_clBuildProgram                      func_clBuildProgram                     = nullptr;
def_clGetProgramBuildInfo               func_clGetProgramBuildInfo              = nullptr;
def_clCreateKernel                      func_clCreateKernel                     = nullptr;
def_clCreateBuffer                      func_clCreateBuffer                     = nullptr;
def_clEnqueueWriteBuffer                func_clEnqueueWriteBuffer               = nullptr;
def_clSetKernelArg                      func_clSetKernelArg                     = nullptr;
def_clEnqueueNDRangeKernel              func_clEnqueueNDRangeKernel             = nullptr;
def_clWaitForEvents                     func_clWaitForEvents                    = nullptr;
def_clEnqueueReadBuffer                 func_clEnqueueReadBuffer                = nullptr;
def_clFlush                             func_clFlush                            = nullptr;
def_clFinish                            func_clFinish                           = nullptr;
def_clReleaseKernel                     func_clReleaseKernel                    = nullptr;
def_clReleaseProgram                    func_clReleaseProgram                   = nullptr;
def_clReleaseMemObject                  func_clReleaseMemObject                 = nullptr;
def_clReleaseCommandQueue               func_clReleaseCommandQueue              = nullptr;
def_clReleaseContext                    func_clReleaseContext                   = nullptr;

extern "C" JNIEXPORT void JNICALL Java_com_example_testapi32arm64_MainActivity_openclopenlib(JNIEnv *env, jobject /* this */) {
    __android_log_print(ANDROID_LOG_INFO, "app", "  [ Speak c++ ] : openclopenlib()\n");

    // AndroidManifest.xml
    // <application ...>
    // ...
    // <uses-native-library android:name="libOpenCL.so" android:required="true"/>
    // ...
    // </application>
    opencl_lib_ptr = dlopen("libOpenCL.so", RTLD_NOW);

    if (opencl_lib_ptr == nullptr) {

        __android_log_print(ANDROID_LOG_INFO, "app", "  opencl_lib_ptr == nullptr\n");

    }
    else {

        __android_log_print(ANDROID_LOG_INFO, "app", "  [ Speak c++ ] : CL_TARGET_OPENCL_VERSION : %d\n", CL_TARGET_OPENCL_VERSION);

        func_clGetPlatformIDs                   = (def_clGetPlatformIDs)( dlsym(opencl_lib_ptr, "clGetPlatformIDs") );
        func_clGetPlatformInfo                  = (def_clGetPlatformInfo)( dlsym(opencl_lib_ptr, "clGetPlatformInfo") );
        func_clGetDeviceIDs                     = (def_clGetDeviceIDs)( dlsym(opencl_lib_ptr, "clGetDeviceIDs") );
        func_clGetDeviceInfo                    = (def_clGetDeviceInfo)( dlsym(opencl_lib_ptr, "clGetDeviceInfo") );
        func_clCreateContext                    = (def_clCreateContext)( dlsym(opencl_lib_ptr, "clCreateContext") );
        func_clCreateCommandQueueWithProperties = (def_clCreateCommandQueueWithProperties)( dlsym(opencl_lib_ptr, "clCreateCommandQueueWithProperties") );
        func_clCreateProgramWithSource          = (def_clCreateProgramWithSource)( dlsym(opencl_lib_ptr, "clCreateProgramWithSource") );
        func_clBuildProgram                     = (def_clBuildProgram)( dlsym(opencl_lib_ptr, "clBuildProgram") );
        func_clGetProgramBuildInfo              = (def_clGetProgramBuildInfo)( dlsym(opencl_lib_ptr, "clGetProgramBuildInfo") );
        func_clCreateKernel                     = (def_clCreateKernel)( dlsym(opencl_lib_ptr, "clCreateKernel") );
        func_clCreateBuffer                     = (def_clCreateBuffer)( dlsym(opencl_lib_ptr, "clCreateBuffer") );
        func_clEnqueueWriteBuffer               = (def_clEnqueueWriteBuffer)( dlsym(opencl_lib_ptr, "clEnqueueWriteBuffer") );
        func_clSetKernelArg                     = (def_clSetKernelArg)( dlsym(opencl_lib_ptr, "clSetKernelArg") );
        func_clEnqueueNDRangeKernel             = (def_clEnqueueNDRangeKernel)( dlsym(opencl_lib_ptr, "clEnqueueNDRangeKernel") );
        func_clWaitForEvents                    = (def_clWaitForEvents)( dlsym(opencl_lib_ptr, "clWaitForEvents") );
        func_clEnqueueReadBuffer                = (def_clEnqueueReadBuffer)( dlsym(opencl_lib_ptr, "clEnqueueReadBuffer") );
        func_clFlush                            = (def_clFlush)( dlsym(opencl_lib_ptr, "clFlush") );
        func_clFinish                           = (def_clFinish)( dlsym(opencl_lib_ptr, "clFinish") );
        func_clReleaseKernel                    = (def_clReleaseKernel)( dlsym(opencl_lib_ptr, "clReleaseKernel") );
        func_clReleaseProgram                   = (def_clReleaseProgram)( dlsym(opencl_lib_ptr, "clReleaseProgram") );
        func_clReleaseMemObject                 = (def_clReleaseMemObject)( dlsym(opencl_lib_ptr, "clReleaseMemObject") );
        func_clReleaseCommandQueue              = (def_clReleaseCommandQueue)( dlsym(opencl_lib_ptr, "clReleaseCommandQueue") );
        func_clReleaseContext                   = (def_clReleaseContext)( dlsym(opencl_lib_ptr, "clReleaseContext") );

        if ((func_clGetPlatformIDs == nullptr)                      ||
            (func_clGetPlatformInfo == nullptr)                     ||
            (func_clGetDeviceIDs == nullptr)                        ||
            (func_clGetDeviceInfo == nullptr)                       ||
            (func_clCreateContext == nullptr)                       ||
            (func_clCreateCommandQueueWithProperties == nullptr)    ||
            (func_clCreateProgramWithSource == nullptr)             ||
            (func_clBuildProgram == nullptr)                        ||
            (func_clGetProgramBuildInfo == nullptr)                 ||
            (func_clCreateKernel == nullptr)                        ||
            (func_clCreateBuffer == nullptr)                        ||
            (func_clEnqueueWriteBuffer == nullptr)                  ||
            (func_clSetKernelArg == nullptr)                        ||
            (func_clEnqueueNDRangeKernel == nullptr)                ||
            (func_clWaitForEvents == nullptr)                       ||
            (func_clEnqueueReadBuffer == nullptr)                   ||
            (func_clFlush == nullptr)                               ||
            (func_clFinish == nullptr)                              ||
            (func_clReleaseKernel == nullptr)                       ||
            (func_clReleaseProgram == nullptr)                      ||
            (func_clReleaseMemObject == nullptr)                    ||
            (func_clReleaseCommandQueue == nullptr)                 ||
            (func_clReleaseContext == nullptr)) {

            __android_log_print(ANDROID_LOG_INFO, "app", "  function load fail ... !!! \n");
            dlclose(opencl_lib_ptr);
            opencl_lib_ptr = nullptr;
        }

        int get_result = 0;
        std::string get_info = "";
        cl_uint opencl_platform_num = 0;
        cl_platform_id *opencl_platform = nullptr;
        cl_uint opencl_device_num = 0;
        cl_device_id *opencl_device = nullptr;
        // get count opencl-platform
        get_result = func_clGetPlatformIDs(0, nullptr, &opencl_platform_num);
        opencl_platform = (cl_platform_id*)std::malloc(sizeof(cl_platform_id) * opencl_platform_num);
        // get all opencl-platform
        get_result = func_clGetPlatformIDs(opencl_platform_num, opencl_platform, nullptr);
        // get info opencl-platform
        get_info += opencl_info_platform(opencl_platform, opencl_platform_num);
        // iteration all opencl-platform
        for (cl_uint idx_plf = 0; idx_plf < opencl_platform_num; idx_plf++) {
            // get count opencl-device
            get_result = func_clGetDeviceIDs(opencl_platform[idx_plf], CL_DEVICE_TYPE_ALL, 0, nullptr, &opencl_device_num);
            opencl_device = (cl_device_id *) std::malloc( sizeof(cl_device_id) * opencl_device_num );
            // get all opencl-device
            get_result = func_clGetDeviceIDs(opencl_platform[idx_plf], CL_DEVICE_TYPE_ALL, opencl_device_num, opencl_device, NULL);
            // get info opencl-device
            get_info += opencl_info_device(opencl_device, opencl_device_num);
        }
        std::free(opencl_device);
        std::free(opencl_platform);
        opencl_device = nullptr;
        opencl_platform = nullptr;

        __android_log_print( ANDROID_LOG_INFO, "app", "  %s\n", get_info.c_str() );

    }

    return;

}

extern "C" JNIEXPORT void JNICALL Java_com_example_testapi32arm64_MainActivity_openclcloselib(JNIEnv *env, jobject /* this */) {
    __android_log_print(ANDROID_LOG_INFO, "app", "  [ Speak c++ ] : openclcloselib()\n");

    if ( opencl_lib_ptr != nullptr ){

        func_clGetPlatformIDs                   = nullptr;
        func_clGetPlatformInfo                  = nullptr;
        func_clGetDeviceIDs                     = nullptr;
        func_clGetDeviceInfo                    = nullptr;
        func_clCreateContext                    = nullptr;
        func_clCreateCommandQueueWithProperties = nullptr;
        func_clCreateProgramWithSource          = nullptr;
        func_clBuildProgram                     = nullptr;
        func_clGetProgramBuildInfo              = nullptr;
        func_clCreateKernel                     = nullptr;
        func_clCreateBuffer                     = nullptr;
        func_clEnqueueWriteBuffer               = nullptr;
        func_clSetKernelArg                     = nullptr;
        func_clEnqueueNDRangeKernel             = nullptr;
        func_clWaitForEvents                    = nullptr;
        func_clEnqueueReadBuffer                = nullptr;
        func_clFlush                            = nullptr;
        func_clFinish                           = nullptr;
        func_clReleaseKernel                    = nullptr;
        func_clReleaseProgram                   = nullptr;
        func_clReleaseMemObject                 = nullptr;
        func_clReleaseCommandQueue              = nullptr;
        func_clReleaseContext                   = nullptr;

        dlclose(opencl_lib_ptr);
        opencl_lib_ptr = nullptr;
    }

    return;

}

extern "C" JNIEXPORT jstring JNICALL Java_com_example_testapi32arm64_MainActivity_openclmatmul(JNIEnv *env, jobject /* this */) {
    __android_log_print(ANDROID_LOG_INFO, "app", "  [ Speak c++ ] : openclmatul()\n");

    std::string get_info = "";

    std::chrono::steady_clock::time_point chrono_tick;
    float chrono_sec = 0.0f;

    if (opencl_lib_ptr == nullptr){

        __android_log_print(ANDROID_LOG_INFO, "app", "  opencl_lib_ptr == nullptr\n");

    }
    else{

        // Matrix A [ M x N ] x Matrix B [ N x K ] = Matrix C [ M x K ]
        int m_size = 256;
        int n_size = 256;
        int k_size = 256; // this value will be used by local_item_size.

        cl_int get_result = 0;

        ////////////////////////////////////////////////// [ for-loop ] : -->
        int* hostbuf_a = (int*)std::malloc( sizeof(int) * m_size * n_size );
        int* hostbuf_b = (int*)std::malloc( sizeof(int) * n_size * k_size );
        int* hostbuf_c = (int*)std::malloc( sizeof(int) * m_size * k_size );
        std::memset(hostbuf_a, 0, sizeof(int) * m_size * n_size);
        std::memset(hostbuf_b, 0, sizeof(int) * n_size * k_size);
        std::memset(hostbuf_c, 0, sizeof(int) * m_size * k_size);
        for (int idx = 0; idx < m_size * n_size; idx++ ) hostbuf_a[idx] = 1;
        for (int idx = 0; idx < n_size * k_size; idx++ ) hostbuf_b[idx] = 1;
        for (int idx = 0; idx < m_size * k_size; idx++ ) hostbuf_c[idx] = 0;

        chrono_tick = std::chrono::steady_clock::now();
        for (int idx_m = 0; idx_m < m_size; idx_m++ ) {
            for (int idx_k = 0; idx_k < k_size; idx_k++ ) {
                get_result = 0;
                for (int idx_n = 0; idx_n < n_size; idx_n++ ) {
                    get_result += hostbuf_a[n_size * idx_m + idx_n] * hostbuf_b[k_size * idx_n + idx_k];
                }
                hostbuf_c[idx_m * k_size + idx_k] = get_result;
            }
        }
        chrono_sec = std::chrono::duration<float>(std::chrono::steady_clock::now() - chrono_tick).count();
        get_info += "  [ openclmatul() ]\n";
        get_info += "  for-loop time : " + std::to_string(chrono_sec) + "\n";
        ////////////////////////////////////////////////// [ for-loop ] : <--

        ////////////////////////////////////////////////// [ opencl ] : -->
        int* hostbuf_d = (int*)std::malloc( sizeof(int) * m_size * k_size );
        std::memset(hostbuf_d, 0, sizeof(int) * m_size * k_size );
        for (int idx = 0; idx < m_size * k_size; idx++ ) hostbuf_d[idx] = 0;

        cl_uint opencl_platform_num = 0;
        cl_platform_id *opencl_platform = nullptr;

        cl_uint opencl_device_num = 0;
        cl_device_id *opencl_device = nullptr;

        cl_command_queue* opencl_queue = nullptr;

        cl_event kernel_event = nullptr;

        if (true){

            // get count opencl-platform
            get_result = func_clGetPlatformIDs(0, nullptr, &opencl_platform_num);
            opencl_platform = (cl_platform_id*)std::malloc(sizeof(cl_platform_id) * opencl_platform_num);
            // get all opencl-platform
            get_result = func_clGetPlatformIDs(opencl_platform_num, opencl_platform, nullptr);

            // iteration all opencl-platform
            for (cl_uint idx_plf = 0; idx_plf < opencl_platform_num; idx_plf++) {

                // get count opencl-device
                get_result = func_clGetDeviceIDs(opencl_platform[idx_plf], CL_DEVICE_TYPE_ALL, 0, nullptr, &opencl_device_num);
                opencl_device = (cl_device_id *) std::malloc(sizeof(cl_device_id) * opencl_device_num);
                // get all opencl-device
                get_result = func_clGetDeviceIDs(opencl_platform[idx_plf], CL_DEVICE_TYPE_ALL, opencl_device_num, opencl_device, NULL);

                // get opencl-context
                // with all device
                cl_context opencl_context = func_clCreateContext(nullptr, opencl_device_num, opencl_device, nullptr, nullptr, &get_result);

                // set opencl-queue property
                cl_queue_properties opencl_queue_prop[] = {CL_QUEUE_PROPERTIES, CL_QUEUE_PROFILING_ENABLE, 0};
                opencl_queue = (cl_command_queue *) std::malloc( sizeof(cl_command_queue) * opencl_device_num);
                for (cl_uint idx_dev = 0; idx_dev < opencl_device_num; idx_dev++) {
                    // get opencl-queue
                    // with all device
                    opencl_queue[idx_dev] = func_clCreateCommandQueueWithProperties(opencl_context, opencl_device[idx_dev], opencl_queue_prop, &get_result);

                }

                // create opencl-program
                // source   : 'opencl_src_matmul'
                // kernel   : 'opencl_kernel_matmul'
                // '1' mean opencl_src_matmul[1] = { "kernel01 hello" }
                // 'N' mean opencl_src_matmul[N] = { "kernel01 hello", "kernel02 world", ... }
                cl_program opencl_program = func_clCreateProgramWithSource(opencl_context, 1, (const char **) &opencl_src_matmul, nullptr, &get_result);
                std::string opencl_kernel_name = "opencl_kernel_matmul";

                // build opencl-program
                // with all device
                get_result = func_clBuildProgram(opencl_program, opencl_device_num, opencl_device, nullptr, nullptr, nullptr);
                // get info opencl-build
                get_info += opencl_info_build(opencl_program, opencl_device_num, opencl_device);

                // create opencl kernel
                cl_kernel opencl_kernel = func_clCreateKernel(opencl_program, opencl_kernel_name.c_str(), &get_result);

                ///// now, your special operation write here : -->
                // create opencl-buffer and distributing it into a opencl-queue
                // below example is just use 1 GPU ( == 1 queue )
                cl_mem hwbuf_a = func_clCreateBuffer(opencl_context, CL_MEM_READ_WRITE, sizeof(int) * m_size * n_size, nullptr, &get_result);
                cl_mem hwbuf_b = func_clCreateBuffer(opencl_context, CL_MEM_READ_WRITE, sizeof(int) * n_size * k_size, nullptr, &get_result);
                cl_mem hwbuf_c = func_clCreateBuffer(opencl_context, CL_MEM_READ_WRITE, sizeof(int) * m_size * k_size, nullptr, &get_result);
                get_result = func_clEnqueueWriteBuffer(opencl_queue[0], hwbuf_a, CL_TRUE, 0, sizeof(int) * m_size * n_size, hostbuf_a, 0, nullptr, nullptr);
                get_result = func_clEnqueueWriteBuffer(opencl_queue[0], hwbuf_b, CL_TRUE, 0, sizeof(int) * n_size * k_size, hostbuf_b, 0, nullptr, nullptr);
                get_result = func_clSetKernelArg(opencl_kernel, 0, sizeof(cl_mem), (void *) &hwbuf_a);
                get_result = func_clSetKernelArg(opencl_kernel, 1, sizeof(cl_mem), (void *) &hwbuf_b);
                get_result = func_clSetKernelArg(opencl_kernel, 2, sizeof(cl_mem), (void *) &hwbuf_c);
                get_result = func_clSetKernelArg(opencl_kernel, 3, sizeof(int), &m_size);
                get_result = func_clSetKernelArg(opencl_kernel, 4, sizeof(int), &n_size);
                get_result = func_clSetKernelArg(opencl_kernel, 5, sizeof(int), &k_size);
                ///// now, your special operation write here : <--

                // 'global_item_size' must be dividable 'local_item_size'
                // 'local_item_size' based on the GPU architecture ( CL_DEVICE_MAX_WORK_GROUP_SIZE )
                // orange-pi-5 : 'local_item_size' is 1000
                size_t global_item_size = m_size * k_size;
                size_t local_item_size = k_size;

                // execute opencl kernel
                chrono_tick = std::chrono::steady_clock::now();
                get_result = func_clEnqueueNDRangeKernel(opencl_queue[0], opencl_kernel, 1, nullptr, &global_item_size, &local_item_size, 0, nullptr, &kernel_event);
                // get_result = func_clEnqueueNDRangeKernel(opencl_queue[0], opencl_kernel, "thread dimension", "input global offset", &global_item_size, &local_item_size, "wait event number", "wait event list", &kernel_event);
                // ...
                // get_result = func_clEnqueueNDRangeKernel(opencl_queue[N], opencl_kernel, "thread dimension", "input global offset", &global_item_size, &local_item_size, "wait event number", "wait event list", &kernel_event);
                func_clWaitForEvents(1, &kernel_event);
                chrono_sec = std::chrono::duration<float>(std::chrono::steady_clock::now() - chrono_tick).count();
                get_info += "  [ openclmatul() ]\n";
                get_info += "  opencl time : " + std::to_string(chrono_sec) + "\n";

                // copy to host
                get_result = func_clEnqueueReadBuffer(opencl_queue[0], hwbuf_c, CL_TRUE, 0, sizeof(int) * m_size * k_size, hostbuf_d, 0, nullptr, &kernel_event);
                func_clWaitForEvents(1, &kernel_event);

                // memory free opencl
                for (cl_uint idx_dev = 0; idx_dev < opencl_device_num; idx_dev++) {
                    get_result = func_clFlush(opencl_queue[idx_dev]);
                    get_result = func_clFinish(opencl_queue[idx_dev]);
                }
                get_result = func_clReleaseKernel(opencl_kernel);
                get_result = func_clReleaseProgram(opencl_program);
                get_result = func_clReleaseMemObject(hwbuf_a);
                get_result = func_clReleaseMemObject(hwbuf_b);
                get_result = func_clReleaseMemObject(hwbuf_c);
                for (cl_uint idx_dev = 0; idx_dev < opencl_device_num; idx_dev++) {
                    get_result = func_clReleaseCommandQueue(opencl_queue[idx_dev]);
                }
                get_result = func_clReleaseContext(opencl_context);
                std::free(opencl_device);
                std::free(opencl_platform);
                opencl_device = nullptr;
                opencl_platform = nullptr;

            }
        }
        else{
            //
        }
        ////////////////////////////////////////////////// [ opencl ] : <--

        // [ Compare ]
        for (int idx_m = 0; idx_m < m_size; idx_m++ ) {
            for (int idx_k = 0; idx_k < k_size; idx_k++ ) {
                if( hostbuf_c[idx_m * k_size + idx_k] != hostbuf_d[idx_m * k_size + idx_k] ){
                    __android_log_print(ANDROID_LOG_INFO, "app", "  hostbuf_c != hostbuf_d [%d, %d]\n", idx_m, idx_k);
                    __android_log_print(ANDROID_LOG_INFO, "app", "  hostbuf_c  : %d\n", hostbuf_c[idx_m * k_size + idx_k] );
                    __android_log_print(ANDROID_LOG_INFO, "app", "  hostbuf_d : %d\n", hostbuf_d[idx_m * k_size + idx_k] );
                    idx_k = k_size;
                    idx_m = m_size;
                    break;
                }
            }
        }

        // C++ memory free
        std::free(hostbuf_a);
        std::free(hostbuf_b);
        std::free(hostbuf_c);
        std::free(hostbuf_d);
        hostbuf_a = nullptr;
        hostbuf_b = nullptr;
        hostbuf_c = nullptr;
        hostbuf_d = nullptr;
    }

    return env->NewStringUTF(get_info.c_str());

}

// Convolution test
// [ row x col x channel ]
// Matrix T(target) : [ t1 x t2 x tc ] : assuming padding is applied
// Matrix K(kernel) : [ k1 x k2 x kc ] : convolution kernel
// Matrix R(result) : [ r1 x r2 x rc ] : result
extern "C" JNIEXPORT jstring JNICALL Java_com_example_testapi32arm64_MainActivity_openclconv2d(JNIEnv *env, jobject /* this */) {
    __android_log_print(ANDROID_LOG_INFO, "app", "  [ Speak c++ ] : openclconv2d()\n");
    std::string get_info = "";

    std::chrono::steady_clock::time_point chrono_tick;
    float chrono_sec = 0.0f;

    ////////////////////////////////////////////////// [ for-loop ] : -->
    // Matrix T : [ T1 x T2 x Tc ]
    int t1_size = 2048;
    int t2_size = 2048;
    int tc_size = 3;
    float* hostbuf_t = (float*)std::malloc( sizeof(float) * t1_size * t2_size * tc_size );
    std::memset(hostbuf_t, 0, sizeof(float) * t1_size * t2_size * tc_size );
    for (int idx = 0; idx < t1_size * t2_size * tc_size; idx++ ) hostbuf_t[idx] = 0.1f;

    // Matrix K : [ K1 x K2 x Kc ]
    int k1_size = 3;
    int k2_size = 3;
    int kc_size = 5;
    if ( ((k1_size-1)<0) || ((k2_size-1)<0) ) {
        __android_log_print(ANDROID_LOG_INFO, "app", "  [ Speak c++ ] : openclconv2d() : kernel size error ()\n");
    }
    float* hostbuf_k = (float*)std::malloc( sizeof(float) * k1_size * k2_size * kc_size );
    std::memset(hostbuf_k, 0, sizeof(float) * k1_size * k2_size * kc_size);
    for (int idx_kc = 0; idx_kc < kc_size; idx_kc++ ) {
        for (int idx_k = 0; idx_k < k1_size * k2_size; idx_k++ ) {
            hostbuf_k[idx_kc * (k1_size * k2_size) + idx_k] = 1.0f;
        }
    }

    // Matrix R : [ R1 x R2 x Rc ]
    int r1_size = t1_size - (k1_size - 1);
    int r2_size = t2_size - (k2_size - 1);
    int rc_size = kc_size;
    if ( !( (r1_size>0) && (r2_size>0) ) ) {
        __android_log_print(ANDROID_LOG_INFO, "app", "  [ Speak c++ ] : openclconv2d() : kernel size error ()\n");
    }
    float* hostbuf_forloop = (float*)std::malloc( sizeof(float) * r1_size * r2_size * rc_size );
    std::memset(hostbuf_forloop, 0, sizeof(float) * r1_size * r2_size * rc_size);
    for (int idx = 0; idx < r1_size * r2_size * rc_size; idx++ ) hostbuf_forloop[idx] = 0.0f;

    chrono_tick = std::chrono::steady_clock::now();
    if(false) {
        for (int idx_r = 0; idx_r < r1_size * r2_size * rc_size; idx_r++) {
            float get_conv = 0.0f;
            int r_ch = idx_r / (r1_size * r2_size);
            int r_mat = idx_r % (r1_size * r2_size);
            int r_row = r_mat / r2_size;
            int r_col = r_mat % r2_size;
            for (int idx_tc = 0; idx_tc < tc_size; idx_tc++) {
                for (int idx_k = 0; idx_k < k1_size * k2_size; idx_k++) {
                    int k_ch = r_ch;
                    int k_mat = idx_k % (k1_size * k2_size);
                    int k_row = k_mat / k2_size;
                    int k_col = k_mat % k2_size;

                    int k_cur = k_ch * (k1_size * k2_size);
                    int k_pos = k_cur + k_row * k2_size + k_col;

                    int t_cur = idx_tc * (t1_size * t2_size) + r_row * t2_size + r_col;
                    int t_pos = t_cur + k_row * t2_size + k_col;

                    get_conv += hostbuf_t[t_pos] * hostbuf_k[k_pos];
                }
            }
            hostbuf_forloop[idx_r] = get_conv;
            //__android_log_print(ANDROID_LOG_INFO, "app", "  [ Speak c++ ] : Matrix R (%d) [ %d, %d, %d ] \n", idx_r, r_row, r_col, r_ch);
        }
    }
    else if(false){
        for (int idx_r = 0; idx_r < r1_size * r2_size * rc_size; idx_r++) {
            int r_ch = idx_r / (r1_size * r2_size);
            int r_mat = idx_r % (r1_size * r2_size);
            int r_row = r_mat / r2_size;
            int r_col = r_mat % r2_size;
            float get_conv = 0.0f;
            for (int idx_tc = 0; idx_tc < tc_size; idx_tc++) {
                int t_cur = idx_tc * (t1_size * t2_size) + r_row * t2_size + r_col;
                for (int idx_k = 0; idx_k < k1_size * k2_size; idx_k++) {
                    int k_ch = r_ch;
                    int k_mat = idx_k;
                    int k_row = k_mat / k2_size;
                    int k_col = k_mat % k2_size;
                    int k_pos = k_ch * (k1_size * k2_size) + idx_k;
                    int t_pos = t_cur + k_row * t2_size + k_col;
                    get_conv += hostbuf_t[t_pos] * hostbuf_k[k_pos];
                }
            }
            hostbuf_forloop[idx_r] = get_conv;
            //__android_log_print(ANDROID_LOG_INFO, "app", "  [ Speak c++ ] : Matrix R (%d) [ %d, %d, %d ] \n", idx_r, r_row, r_col, r_ch);
        }
    }
    else if(true){
        for (int idx_r = 0; idx_r < r1_size * r2_size * rc_size; idx_r++) {
            float get_conv = 0.0f;
            int r_ch = idx_r / (r1_size * r2_size);
            int r_mat = idx_r % (r1_size * r2_size);
            int r_row = r_mat / r2_size;
            int r_col = r_mat % r2_size;
            for (int idx_tc = 0; idx_tc < tc_size; idx_tc++) {
                int t_cur = idx_tc * (t1_size * t2_size) + r_row * t2_size + r_col;
                for (int idx_k = 0; idx_k < k1_size * k2_size; idx_k++) {
                    int k_ch = r_ch;
                    int k_mat = idx_k % (k1_size * k2_size);
                    int k_row = k_mat / k2_size;
                    int k_col = k_mat % k2_size;
                    int k_pos = k_ch * (k1_size * k2_size) + idx_k;
                    int t_pos = t_cur + k_row * t2_size + k_col;
                    get_conv += hostbuf_t[t_pos] * hostbuf_k[k_pos];
                }
            }
            hostbuf_forloop[idx_r] = get_conv;
            //__android_log_print(ANDROID_LOG_INFO, "app", "  [ Speak c++ ] : Matrix R (%d) [ %d, %d, %d ] \n", idx_r, r_row, r_col, r_ch);
        }
    }
    else{
        //
    }
    chrono_sec = std::chrono::duration<float>(std::chrono::steady_clock::now() - chrono_tick).count();
    get_info += "  [ openclconv2d() ]\n";
    get_info += "  for-loop time : " + std::to_string(chrono_sec) + "\n";
    ////////////////////////////////////////////////// [ for-loop ] : <--

    ////////////////////////////////////////////////// [ opencl ] : -->
    float* hostbuf_opencl = (float*)std::malloc( sizeof(float) * r1_size * r2_size * rc_size );
    std::memset(hostbuf_opencl, 0, sizeof(float) * r1_size * r2_size * rc_size);
    for (int idx = 0; idx < r1_size * r2_size * rc_size; idx++ ) hostbuf_opencl[idx] = 0.0f;

    cl_uint opencl_platform_num = 0;
    cl_platform_id *opencl_platform = nullptr;

    cl_uint opencl_device_num = 0;
    cl_device_id *opencl_device = nullptr;

    cl_command_queue* opencl_queue = nullptr;

    cl_event kernel_event = nullptr;

    cl_int get_result = 0;

    get_result = func_clGetPlatformIDs(0, nullptr, &opencl_platform_num);
    opencl_platform = (cl_platform_id*)std::malloc(sizeof(cl_platform_id) * opencl_platform_num);
    get_result = func_clGetPlatformIDs(opencl_platform_num, opencl_platform, nullptr);

    for (cl_uint idx_plf = 0; idx_plf < opencl_platform_num; idx_plf++) {
        get_result = func_clGetDeviceIDs(opencl_platform[idx_plf], CL_DEVICE_TYPE_ALL, 0, nullptr, &opencl_device_num);
        opencl_device = (cl_device_id *) std::malloc(sizeof(cl_device_id) * opencl_device_num);
        get_result = func_clGetDeviceIDs(opencl_platform[idx_plf], CL_DEVICE_TYPE_ALL, opencl_device_num, opencl_device, NULL);
        cl_context opencl_context = func_clCreateContext(nullptr, opencl_device_num, opencl_device, nullptr, nullptr, &get_result);
        cl_queue_properties opencl_queue_prop[] = {CL_QUEUE_PROPERTIES, CL_QUEUE_PROFILING_ENABLE, 0};
        opencl_queue = (cl_command_queue *) std::malloc( sizeof(cl_command_queue) * opencl_device_num);
        for (cl_uint idx_dev = 0; idx_dev < opencl_device_num; idx_dev++) {
            opencl_queue[idx_dev] = func_clCreateCommandQueueWithProperties(opencl_context, opencl_device[idx_dev], opencl_queue_prop, &get_result);
        }
        cl_program opencl_program = func_clCreateProgramWithSource(opencl_context, 1, (const char **) &opencl_src_conv2d, nullptr, &get_result);
        std::string opencl_kernel_name = "opencl_kernel_conv2d";
        get_result = func_clBuildProgram(opencl_program, opencl_device_num, opencl_device, nullptr, nullptr, nullptr);
        get_info += opencl_info_build(opencl_program, opencl_device_num, opencl_device);
        cl_kernel opencl_kernel = func_clCreateKernel(opencl_program, opencl_kernel_name.c_str(), &get_result);

        ///// now, your special operation write here : -->
        // create opencl-buffer and distribute it into opencl-queue
        // below example is just use 1 GPU ( == 1 queue )
        cl_mem hwbuf_t = func_clCreateBuffer(opencl_context, CL_MEM_READ_WRITE, sizeof(float) * t1_size * t2_size * tc_size, nullptr, &get_result);
        cl_mem hwbuf_k = func_clCreateBuffer(opencl_context, CL_MEM_READ_WRITE, sizeof(float) * k1_size * k2_size * kc_size, nullptr, &get_result);
        cl_mem hwbuf_r = func_clCreateBuffer(opencl_context, CL_MEM_READ_WRITE, sizeof(float) * r1_size * r2_size * rc_size, nullptr, &get_result);
        get_result = func_clEnqueueWriteBuffer(opencl_queue[0], hwbuf_t, CL_TRUE, 0, sizeof(float) * t1_size * t2_size * tc_size, hostbuf_t, 0, nullptr, nullptr);
        get_result = func_clEnqueueWriteBuffer(opencl_queue[0], hwbuf_k, CL_TRUE, 0, sizeof(float) * k1_size * k2_size * kc_size, hostbuf_k, 0, nullptr, nullptr);
        get_result = func_clEnqueueWriteBuffer(opencl_queue[0], hwbuf_r, CL_TRUE, 0, sizeof(float) * r1_size * r2_size * rc_size, hostbuf_opencl, 0, nullptr, nullptr);
        get_result = func_clSetKernelArg(opencl_kernel, 0, sizeof(cl_mem), (void *) &hwbuf_t);
        get_result = func_clSetKernelArg(opencl_kernel, 1, sizeof(cl_mem), (void *) &hwbuf_k);
        get_result = func_clSetKernelArg(opencl_kernel, 2, sizeof(cl_mem), (void *) &hwbuf_r);
        get_result = func_clSetKernelArg(opencl_kernel, 3, sizeof(int), &r1_size);
        get_result = func_clSetKernelArg(opencl_kernel, 4, sizeof(int), &r2_size);
        get_result = func_clSetKernelArg(opencl_kernel, 5, sizeof(int), &rc_size);
        get_result = func_clSetKernelArg(opencl_kernel, 6, sizeof(int), &t1_size);
        get_result = func_clSetKernelArg(opencl_kernel, 7, sizeof(int), &t2_size);
        get_result = func_clSetKernelArg(opencl_kernel, 8, sizeof(int), &tc_size);
        get_result = func_clSetKernelArg(opencl_kernel, 9, sizeof(int), &k1_size);
        get_result = func_clSetKernelArg(opencl_kernel, 10, sizeof(int), &k2_size);
        ///// now, your special operation write here : <--

        // 'global_item_size' must be dividable 'local_item_size'
        // 'local_item_size' based on the GPU architecture ( CL_DEVICE_MAX_WORK_GROUP_SIZE )
        // orange-pi-5 : 'local_item_size' is 1000
        size_t global_item_size = r1_size * r2_size * rc_size;
        size_t local_item_size = rc_size;

        // execute opencl kernel
        // get_result = func_clEnqueueNDRangeKernel(opencl_queue[0], opencl_kernel, "thread dimension", "input global offset", &global_item_size, &local_item_size, "wait event number", "wait event list", &kernel_event);
        // ...
        // get_result = func_clEnqueueNDRangeKernel(opencl_queue[N], opencl_kernel, "thread dimension", "input global offset", &global_item_size, &local_item_size, "wait event number", "wait event list", &kernel_event);
        chrono_tick = std::chrono::steady_clock::now();
        get_result = func_clEnqueueNDRangeKernel(opencl_queue[0], opencl_kernel, 1, nullptr, &global_item_size, &local_item_size, 0, nullptr, &kernel_event);
        func_clWaitForEvents(1, &kernel_event);
        chrono_sec = std::chrono::duration<float>(std::chrono::steady_clock::now() - chrono_tick).count();
        get_info += "  [ openclconv2d() ]\n";
        get_info += "  opencl time : " + std::to_string(chrono_sec) + "\n";

        // copy to host
        get_result = func_clEnqueueReadBuffer(opencl_queue[0], hwbuf_r, CL_TRUE, 0, sizeof(float) * r1_size * r2_size * rc_size, hostbuf_opencl, 0, nullptr, &kernel_event);
        func_clWaitForEvents(1, &kernel_event);

        // memory free opencl
        for (cl_uint idx_dev = 0; idx_dev < opencl_device_num; idx_dev++) {
            get_result = func_clFlush(opencl_queue[idx_dev]);
            get_result = func_clFinish(opencl_queue[idx_dev]);
        }
        get_result = func_clReleaseKernel(opencl_kernel);
        get_result = func_clReleaseProgram(opencl_program);
        get_result = func_clReleaseMemObject(hwbuf_t);
        get_result = func_clReleaseMemObject(hwbuf_k);
        get_result = func_clReleaseMemObject(hwbuf_r);
        for (cl_uint idx_dev = 0; idx_dev < opencl_device_num; idx_dev++) {
            get_result = func_clReleaseCommandQueue(opencl_queue[idx_dev]);
        }
        get_result = func_clReleaseContext(opencl_context);
        std::free(opencl_device);
        std::free(opencl_platform);
        opencl_device = nullptr;
        opencl_platform = nullptr;

    }
    ////////////////////////////////////////////////// [ opencl ] : <--

    // [ Compare ]
    for (int idx_r = 0; idx_r < r1_size * r2_size * rc_size; idx_r++ ) {
        if ( hostbuf_forloop[idx_r] != hostbuf_opencl[idx_r] ){
            get_info += "  [ openclconv2d() ]\n";
            get_info += "  compare fail !!!\n";
            break;
        };
    }
    __android_log_print(ANDROID_LOG_INFO, "app", "  [ Speak c++ ] : hostbuf_forloop[0]: %f\n", hostbuf_forloop[0]);
    __android_log_print(ANDROID_LOG_INFO, "app", "  [ Speak c++ ] : hostbuf_opencl[0] : %f\n", hostbuf_opencl[0]);

    // C++ memory free
    std::free(hostbuf_t);
    std::free(hostbuf_k);
    std::free(hostbuf_forloop);
    std::free(hostbuf_opencl);
    hostbuf_t = nullptr;
    hostbuf_k = nullptr;
    hostbuf_forloop = nullptr;
    hostbuf_opencl = nullptr;

    return env->NewStringUTF(get_info.c_str());

}

// OpenCL PlatformInfo
std::string opencl_info_platform(cl_platform_id* get_platform, cl_uint get_num) {
    std::string platform_info = "";

    platform_info += "  [ Platform Info ]\n";

    std::string get_str = "";
    char buffer[1024] = {0, };
    size_t size = 0;

    for (cl_uint idx_plf = 0; idx_plf < get_num; idx_plf++) {

        platform_info += "  Platform : " + std::to_string(idx_plf) + "\n";

        // Get and print platform name
        func_clGetPlatformInfo(get_platform[idx_plf], CL_PLATFORM_NAME, sizeof(buffer), buffer, &size);
        get_str = "";
        get_str.assign(buffer, size - 1);
        platform_info += "  CL_PLATFORM_NAME : " + get_str + "\n";

        // Get and print platform vendor
        func_clGetPlatformInfo(get_platform[idx_plf], CL_PLATFORM_VENDOR, sizeof(buffer), buffer, &size);
        get_str = "";
        get_str.assign(buffer, size - 1);
        platform_info += "  CL_PLATFORM_VENDOR : " + get_str + "\n";

        // Get and print platform version
        func_clGetPlatformInfo(get_platform[idx_plf], CL_PLATFORM_VERSION, sizeof(buffer), buffer, &size);
        get_str = "";
        get_str.assign(buffer, size - 1);
        platform_info += "  CL_PLATFORM_VERSION : " + get_str + "\n";

        // Get and print platform profile
        func_clGetPlatformInfo(get_platform[idx_plf], CL_PLATFORM_PROFILE, sizeof(buffer), buffer, &size);
        get_str = "";
        get_str.assign(buffer, size - 1);
        platform_info += "  CL_PLATFORM_PROFILE : " + get_str + "\n";

        // Get and print platform extensions
        func_clGetPlatformInfo(get_platform[idx_plf], CL_PLATFORM_EXTENSIONS, sizeof(buffer), buffer, &size);
        get_str = "";
        get_str.assign(buffer, size - 1);
        platform_info += "  CL_PLATFORM_EXTENSIONS : " + get_str + "\n";

    }

    return platform_info;

}

// OpenCL DeviceInfo
std::string opencl_info_device(cl_device_id* get_device, cl_uint get_num) {
    std::string device_info = "";

    device_info += "  [ Device Info ]\n";

    std::string get_str = "";
    char buffer[1024] = {0, };
    size_t size = 0;
    cl_uint uintVal = 0;
    cl_ulong ulongVal = 0;

    for (cl_uint idx_dev = 0; idx_dev < get_num; idx_dev++) {

        device_info += "  Device : " + std::to_string(idx_dev) + "\n";

        // Get and print device name
        func_clGetDeviceInfo(get_device[idx_dev], CL_DEVICE_NAME, sizeof(buffer), buffer, &size);
        get_str = "";
        get_str.assign(buffer, size - 1);
        device_info += "  CL_DEVICE_NAME : " + get_str + "\n";

        // Get and print device vendor
        func_clGetDeviceInfo(get_device[idx_dev], CL_DEVICE_VENDOR, sizeof(buffer), buffer, &size);
        get_str = "";
        get_str.assign(buffer, size - 1);
        device_info += "  CL_DEVICE_VENDOR : " + get_str + "\n";

        // Get and print device version
        func_clGetDeviceInfo(get_device[idx_dev], CL_DEVICE_VERSION, sizeof(buffer), buffer, &size);
        get_str = "";
        get_str.assign(buffer, size - 1);
        device_info += "  CL_DEVICE_VERSION : " + get_str + "\n";

        // Get and print driver version
        func_clGetDeviceInfo(get_device[idx_dev], CL_DRIVER_VERSION, sizeof(buffer), buffer, &size);
        get_str = "";
        get_str.assign(buffer, size - 1);
        device_info += "  CL_DRIVER_VERSION : " + get_str + "\n";

        // Get and print device OpenCL C version
        func_clGetDeviceInfo(get_device[idx_dev], CL_DEVICE_OPENCL_C_VERSION, sizeof(buffer), buffer, &size);
        get_str = "";
        get_str.assign(buffer, size - 1);
        device_info += "  CL_DEVICE_OPENCL_C_VERSION : " + get_str + "\n";

        // Get and print device type
        func_clGetDeviceInfo(get_device[idx_dev], CL_DEVICE_TYPE, sizeof(cl_device_type), &uintVal, &size);
        if (uintVal & CL_DEVICE_TYPE_CPU) {
            device_info += "  CL_DEVICE_TYPE : CPU\n";
        }
        if (uintVal & CL_DEVICE_TYPE_GPU) {
            device_info += "  CL_DEVICE_TYPE : GPU\n";
        }
        if (uintVal & CL_DEVICE_TYPE_ACCELERATOR) {
            device_info += "  CL_DEVICE_TYPE : CL_DEVICE_TYPE_ACCELERATOR\n";
        }
        if (uintVal & CL_DEVICE_TYPE_DEFAULT) {
            device_info += "  CL_DEVICE_TYPE : CL_DEVICE_TYPE_DEFAULT\n";
        }

        // Get and print max compute units
        func_clGetDeviceInfo(get_device[idx_dev], CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(uintVal), &uintVal, &size);
        device_info += "  CL_DEVICE_MAX_COMPUTE_UNITS : " + std::to_string(uintVal) + "\n";

        // Get and print max clock frequency
        func_clGetDeviceInfo(get_device[idx_dev], CL_DEVICE_MAX_CLOCK_FREQUENCY, sizeof(uintVal), &uintVal, &size);
        device_info += "  CL_DEVICE_MAX_CLOCK_FREQUENCY : " + std::to_string(uintVal) + " MHz\n";

        // Get and print max work group size
        func_clGetDeviceInfo(get_device[idx_dev], CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(uintVal), &uintVal, &size);
        device_info += "  CL_DEVICE_MAX_WORK_GROUP_SIZE : " + std::to_string(uintVal) + "\n";

        // Get and print max work item size
        func_clGetDeviceInfo(get_device[idx_dev], CL_DEVICE_MAX_WORK_ITEM_SIZES, sizeof(uintVal), &uintVal, &size);
        device_info += "  CL_DEVICE_MAX_WORK_ITEM_SIZES : " + std::to_string(uintVal) + "\n";

        // Get and print global memory size
        func_clGetDeviceInfo(get_device[idx_dev], CL_DEVICE_GLOBAL_MEM_SIZE, sizeof(ulongVal), &ulongVal, &size);
        device_info += "  CL_DEVICE_GLOBAL_MEM_SIZE : " + std::to_string( ulongVal / (1024 * 1024) ) + " MB\n";

        // Get and print max memory allocation size
        func_clGetDeviceInfo(get_device[idx_dev], CL_DEVICE_MAX_MEM_ALLOC_SIZE, sizeof(ulongVal), &ulongVal, &size);
        device_info += "  CL_DEVICE_MAX_MEM_ALLOC_SIZE : " + std::to_string( ulongVal / (1024 * 1024) ) + " MB\n";

    }

    return device_info;

}

// OpenCL DeviceInfo
std::string opencl_info_build(cl_program get_program, cl_uint get_num, const cl_device_id* get_dev) {
    std::string build_info = "";

    build_info += "  [ Build Info ]\n";

    for (cl_uint idx_dev = 0; idx_dev < get_num; idx_dev++) {

        build_info += "  Device : " + std::to_string(idx_dev) + "\n";

        size_t get_size = 0;
        func_clGetProgramBuildInfo(get_program, get_dev[idx_dev], CL_PROGRAM_BUILD_LOG, 0, nullptr, &get_size);

        char* get_log = (char*)std::malloc(get_size);
        func_clGetProgramBuildInfo(get_program, get_dev[idx_dev], CL_PROGRAM_BUILD_LOG, get_size, get_log, nullptr);

        std::string get_str(get_log, get_size - 1);

        if ( get_size == 1 ){
            build_info = "";
        }
        else{
            build_info += get_str + "\n";
        };

        std::free(get_log);

    }

    return build_info;

}
