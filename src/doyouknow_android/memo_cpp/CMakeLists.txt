cmake_minimum_required(VERSION 3.9)

# set OpenCL version 2.2
add_definitions(-DCL_TARGET_OPENCL_VERSION=220)
add_definitions(-DCL_HPP_TARGET_OPENCL_VERSION=220)


project("testapi32arm64")

##### [ java to cpp library ]
set(ADD_PATH_HEADER "")
set(ADD_PATH_LIB "")
set(ADD_FILE_LIB "")
if(true)
    list(APPEND ADD_PATH_HEADER "")
    list(APPEND ADD_PATH_LIB "")
elseif(false)
    list(APPEND ADD_PATH_HEADER "")
    list(APPEND ADD_PATH_LIB "")
endif()
list(APPEND ADD_FILE_LIB "android" "log")

add_library("tester_j2c" SHARED tester_j2c.cpp tester_j2c.hpp)
target_include_directories("tester_j2c" PRIVATE ${ADD_PATH_HEADER})
target_link_directories("tester_j2c" PRIVATE ${ADD_PATH_LIB})
target_link_libraries("tester_j2c" PRIVATE ${ADD_FILE_LIB})

##### [ opencl library ]
set(ADD_PATH_HEADER "")
set(ADD_PATH_LIB "")
set(ADD_FILE_LIB "")
if(true)
    # from github
    list(APPEND ADD_PATH_HEADER "C:/Users/k/Desktop/taebin_git/OpenCL-SDK/install/include")
    list(APPEND ADD_PATH_LIB "") # do not include OpenCL library when compile ...
elseif(false)
    # from vcpkg
    list(APPEND ADD_PATH_HEADER "C:/vcpkg/installed/android-arm64v8a-dynamic-r/include")
    list(APPEND ADD_PATH_LIB "") # do not include OpenCL library when compile ...
endif()
list(APPEND ADD_FILE_LIB "android" "log")

add_library("tester_opencl" SHARED tester_opencl.cpp tester_opencl.hpp)
target_include_directories("tester_opencl" PRIVATE ${ADD_PATH_HEADER})
target_link_directories("tester_opencl" PRIVATE ${ADD_PATH_LIB})
target_link_libraries("tester_opencl" PRIVATE ${ADD_FILE_LIB})

##### [ check ]
message(STATUS "[ CMAKE_BUILD_TYPE ] set to ${CMAKE_BUILD_TYPE}")
message(STATUS "[ CL_TARGET_OPENCL_VERSION ] set to ${CL_TARGET_OPENCL_VERSION}")
message(STATUS "[ CL_HPP_TARGET_OPENCL_VERSION ] set to ${CL_HPP_TARGET_OPENCL_VERSION}")
message(STATUS "[ ADD_PATH_HEADER ] set to ${ADD_PATH_HEADER}")
message(STATUS "[ ADD_PATH_LIB ] set to ${ADD_PATH_LIB}")
message(STATUS "[ ADD_FILE_LIB ] set to ${ADD_FILE_LIB}")
message(STATUS "[ CMAKE_LIBRARY_OUTPUT_DIRECTORY ] set to ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
message(STATUS "[ CMAKE_RUNTIME_OUTPUT_DIRECTORY ] set to ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

#message(FATAL_ERROR "stop cmake")
