#pragma once

#if ( defined(_WIN32) || defined(_WIN64) )

#ifdef EXPORT_FLAG
#define DLL_FLAG __declspec(dllexport)
#else
#define DLL_FLAG __declspec(dllimport)
#endif

#elif ( defined(__unix__) || defined(__linux__) )

#ifdef EXPORT_FLAG
#define DLL_FLAG __attribute__((__visibility__("default")))
#else
#define DLL_FLAG __attribute__((__visibility__("default")))
#endif

#endif

#include <string>
#include <exception>
#include <chrono>
#include <iostream>

extern "C" DLL_FLAG void*	doyouknow_float_get(void);
extern "C" DLL_FLAG void	doyouknow_float_func01(void* get_ptr);
extern "C" DLL_FLAG void	doyouknow_float_func02(void* get_ptr);
