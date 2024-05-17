///////////////////////////////////////////////////////////

#pragma once

// https://learn.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4100?view=msvc-170
// 4100
// no reference variables warning.

// https://learn.microsoft.com/en-us/cpp/error-messages/tool-errors/command-line-warning-d9025?view=msvc-170
// D9025
// overriding option warning.
// EHs : only catch std c++ exception structure.
// -> EHa : all catch exception.

///////////////////////////////////////////////////////////

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
///////////////////////////////////////////////////////////

#include <doyouknow_std_float.hpp>

extern "C" DLL_FLAG void*	doyouknow_float_get(void);
extern "C" DLL_FLAG void	doyouknow_float_func01(void* get_ptr);
extern "C" DLL_FLAG void	doyouknow_float_func02(void* get_ptr);
extern "C" DLL_FLAG void	doyouknow_float_func03(void* get_ptr);
extern "C" DLL_FLAG void	doyouknow_float_func04(void* get_ptr);

///////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////

#include <string>
#include <exception>
#include <chrono>
#include <iostream>

int main(void);

///////////////////////////////////////////////////////////