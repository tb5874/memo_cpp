#include <string>
#include <jni.h>
#include <android/log.h>
#include <dlfcn.h>
#include <CL/opencl.h>

/////////////////////////////////////////////////////////////////////////////////////////////////

// for define OpenCL functor ( from official OpenCL library header )
typedef cl_int              (*def_clGetPlatformIDs)(cl_uint, cl_platform_id*, cl_uint*);
typedef cl_int              (*def_clGetPlatformInfo)(cl_platform_id, cl_platform_info, size_t, void*, size_t*);
typedef cl_int              (*def_clGetDeviceIDs)(cl_platform_id, cl_device_type, cl_uint, cl_device_id*, cl_uint*);
typedef cl_int              (*def_clGetDeviceInfo)(cl_device_id, cl_device_info, size_t, void*, size_t*);
typedef cl_context          (*def_clCreateContext)(const cl_context_properties*, cl_uint, const cl_device_id*, void(CL_CALLBACK* )(const char*, const void*, size_t, void*), void*, cl_int*);
typedef cl_command_queue    (*def_clCreateCommandQueueWithProperties)(cl_context, cl_device_id, const cl_queue_properties*, cl_int*);
typedef cl_program          (*def_clCreateProgramWithSource)(cl_context, cl_uint, const char**, const size_t*, cl_int*);
typedef cl_int              (*def_clBuildProgram)(cl_program, cl_uint, const cl_device_id*, const char*, void(CL_CALLBACK* )(cl_program, void*), void*);
typedef cl_int              (*def_clGetProgramBuildInfo)(cl_program, cl_device_id, cl_program_build_info, size_t, void*, size_t*);
typedef cl_kernel           (*def_clCreateKernel)(cl_program, const char*, cl_int*);
typedef cl_mem              (*def_clCreateBuffer)(cl_context, cl_mem_flags, size_t, void*, cl_int*);
typedef cl_int              (*def_clEnqueueWriteBuffer)(cl_command_queue, cl_mem, cl_bool, size_t, size_t, const void*, cl_uint, const cl_event*, cl_event*);
typedef cl_int              (*def_clSetKernelArg)(cl_kernel, cl_uint, size_t, const void*);
typedef cl_int              (*def_clEnqueueNDRangeKernel)(cl_command_queue, cl_kernel, cl_uint, const size_t*, const size_t*, const size_t*, cl_uint, const cl_event*, cl_event*);
typedef cl_int              (*def_clWaitForEvents)(cl_uint, const cl_event*);
typedef cl_int              (*def_clEnqueueReadBuffer)(cl_command_queue, cl_mem, cl_bool, size_t, size_t, void*, cl_uint, const cl_event*, cl_event*);
typedef cl_int              (*def_clFlush)(cl_command_queue);
typedef cl_int              (*def_clFinish)(cl_command_queue);
typedef cl_int              (*def_clReleaseKernel)(cl_kernel);
typedef cl_int              (*def_clReleaseProgram)(cl_program);
typedef cl_int              (*def_clReleaseMemObject)(cl_mem);
typedef cl_int              (*def_clReleaseCommandQueue)(cl_command_queue);
typedef cl_int              (*def_clReleaseContext)(cl_context);

/////////////////////////////////////////////////////////////////////////////////////////////////

// for global declaration OpenCL functor
extern def_clGetPlatformIDs                     func_clGetPlatformIDs                  ;
extern def_clGetPlatformInfo                    func_clGetPlatformInfo                 ;
extern def_clGetDeviceIDs                       func_clGetDeviceIDs                    ;
extern def_clGetDeviceInfo                      func_clGetDeviceInfo                   ;
extern def_clCreateContext                      func_clCreateContext                   ;
extern def_clCreateCommandQueueWithProperties   func_clCreateCommandQueueWithProperties;
extern def_clCreateProgramWithSource            func_clCreateProgramWithSource         ;
extern def_clBuildProgram                       func_clBuildProgram                    ;
extern def_clGetProgramBuildInfo                func_clGetProgramBuildInfo             ;
extern def_clCreateKernel                       func_clCreateKernel                    ;
extern def_clCreateBuffer                       func_clCreateBuffer                    ;
extern def_clEnqueueWriteBuffer                 func_clEnqueueWriteBuffer              ;
extern def_clSetKernelArg                       func_clSetKernelArg                    ;
extern def_clEnqueueNDRangeKernel               func_clEnqueueNDRangeKernel            ;
extern def_clWaitForEvents                      func_clWaitForEvents                   ;
extern def_clEnqueueReadBuffer                  func_clEnqueueReadBuffer               ;
extern def_clFlush                              func_clFlush                           ;
extern def_clFinish                             func_clFinish                          ;
extern def_clReleaseKernel                      func_clReleaseKernel                   ;
extern def_clReleaseProgram                     func_clReleaseProgram                  ;
extern def_clReleaseMemObject                   func_clReleaseMemObject                ;
extern def_clReleaseCommandQueue                func_clReleaseCommandQueue             ;
extern def_clReleaseContext                     func_clReleaseContext                  ;

//////////////////////////////////////////////////////////////////////////////////////////////

static void* opencl_lib_ptr = nullptr;

std::string opencl_info_platform(cl_platform_id* get_platform, cl_uint get_num);
std::string opencl_info_device(cl_device_id* get_device, cl_uint get_num);
std::string opencl_info_build(cl_program get_program, cl_uint get_num, const cl_device_id* get_dev);

extern "C" JNIEXPORT void JNICALL Java_com_example_testapi32arm64_MainActivity_openclopenlib(JNIEnv *env, jobject /* this */);
extern "C" JNIEXPORT void JNICALL Java_com_example_testapi32arm64_MainActivity_openclcloselib(JNIEnv *env, jobject /* this */);
extern "C" JNIEXPORT jstring JNICALL Java_com_example_testapi32arm64_MainActivity_openclmatmul(JNIEnv *env, jobject /* this */);
extern "C" JNIEXPORT jstring JNICALL Java_com_example_testapi32arm64_MainActivity_openclconv2d(JNIEnv *env, jobject /* this */);

/////////////////////////////////////////////////////////////////////////////////////////////////

static const char *opencl_src_matmul =\
"__kernel void opencl_kernel_matmul(__global int* mat_a, __global int* mat_b, __global int* mat_c, int m_size, int n_size, int k_size) {\n"\
"    int idx = get_global_id(0);\n"\
"    if( idx < m_size * k_size) {\n"\
"        int get_row = idx / k_size;\n"\
"        int get_col = idx % k_size;\n"\
"        int get_matmul = 0;\n"\
"        for (int idx_n = 0; idx_n < n_size; idx_n++ ) {\n"\
"            get_matmul += mat_a[ get_row * n_size + idx_n ] * mat_b[ idx_n * k_size + get_col ];\n"\
"        }\n"\
"        mat_c[ get_row * k_size + get_col ] = get_matmul;\n"\
"    }\n"\
"    return;\n"\
"}\n";

static const char *opencl_src_conv2d =\
"__kernel void opencl_kernel_conv2d(__global float* mat_t, __global float* mat_k, __global float* mat_r, int r1_size, int r2_size, int rc_size, int t1_size, int t2_size, int tc_size, int k1_size, int k2_size) {\n"\
"    int idx_r = get_global_id(0);\n"\
"    if( idx_r < r1_size * r2_size * rc_size ) {\n"\
"        float get_conv = 0.0f;\n"\
"        int r_ch = idx_r / (r1_size * r2_size);\n"\
"        int r_mat = idx_r % (r1_size * r2_size);\n"\
"        int r_row = r_mat / r2_size;\n"\
"        int r_col = r_mat % r2_size;\n"\
"        for (int idx_tc = 0; idx_tc < tc_size; idx_tc++) {\n"\
"            int t_cur = idx_tc * (t1_size * t2_size) + r_row * t2_size + r_col;\n"\
"            for (int idx_k = 0; idx_k < k1_size * k2_size; idx_k++) {\n"\
"                int k_ch = r_ch;\n"\
"                int k_mat = idx_k % (k1_size * k2_size);\n"\
"                int k_row = k_mat / k2_size;\n"\
"                int k_col = k_mat % k2_size;\n"\
"                int k_pos = k_ch * (k1_size * k2_size) + idx_k;\n"\
"                int t_pos = t_cur + k_row * t2_size + k_col;\n"\
"                get_conv += mat_t[t_pos] * mat_k[k_pos];\n"\
"            }\n"\
"        }\n"\
"        mat_r[idx_r] = get_conv;\n"\
"    }\n"\
"    return;\n"\
"}\n";

/////////////////////////////////////////////////////////////////////////////////////////////////
