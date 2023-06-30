cmake_minimum_required (VERSION 3.9)

################################################################################
# Before project()
################################################################################
message(STATUS "Before project()")
if(MSVC)
    #
elseif(UNIX)
    #
endif()
enable_language(CXX)

################################################################################
# Project name
################################################################################
project ("memo_cpp")
message(STATUS "${PROJECT_NAME} : project() set to ${PROJECT_NAME}")

################################################################################
# x64
################################################################################
if(MSVC)
    if(NOT DEFINED CMAKE_VS_PLATFORM_NAME)
        set(CMAKE_VS_PLATFORM_NAME "x64")
    elseif(NOT ("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64"))
        message(FATAL_ERROR "${CMAKE_VS_PLATFORM_NAME} arch is not supported!")
    endif()
    message(STATUS "${PROJECT_NAME} : CMAKE_VS_PLATFORM_NAME set to ${CMAKE_VS_PLATFORM_NAME}")
elseif(UNIX)
    #
endif()

################################################################################
# C++ 
################################################################################
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD_FORCE True)
if (CMAKE_CXX_STANDARD_FORCE)
    set(CMAKE_CXX_STANDARD 14)
endif()
message(STATUS "${PROJECT_NAME} : CMAKE_CXX_STANDARD_REQUIRED set to ${CMAKE_CXX_STANDARD_REQUIRED}")
message(STATUS "${PROJECT_NAME} : CMAKE_CXX_STANDARD_FORCE set to ${CMAKE_CXX_STANDARD_FORCE}")
message(STATUS "${PROJECT_NAME} : CMAKE_CXX_STANDARD set to ${CMAKE_CXX_STANDARD}")

################################################################################
# MSVC : /Zi /Z7 -> /ZI
################################################################################
if(MSVC)
    # /ZI
    #     Produces a PDB file
    #     Edit and Continue debugging features.
    #     Only x86, x64 processors. Not available ARM processors.
    #     Incompatible with use of the __LINE__ predefined macro.
    #     https://learn.microsoft.com/en-us/cpp/build/reference/z7-zi-zi-debug-information-format?view=msvc-170
    string(REGEX REPLACE "/Z[iI7]" "" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /ZI")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
endif()
message(STATUS "${PROJECT_NAME} : CMAKE_CXX_FLAGS_DEBUG set to ${CMAKE_CXX_FLAGS_DEBUG}")
message(STATUS "${PROJECT_NAME} : CMAKE_CXX_FLAGS_RELEASE set to ${CMAKE_CXX_FLAGS_RELEASE}")

################################################################################
# UNIX : Optimize Level set 0
################################################################################
if(UNIX)
    string(REGEX REPLACE "-O[0123]" "" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
    string(REGEX REPLACE "-O[0123]" "" CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
    set(CMAKE_CXX_FLAGS_DEBUG "-O0 ${CMAKE_CXX_FLAGS_DEBUG}")
    set(CMAKE_CXX_FLAGS_RELEASE "-O0 ${CMAKE_CXX_FLAGS_RELEASE}")
endif()

add_subdirectory(src)