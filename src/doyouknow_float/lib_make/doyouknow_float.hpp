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

#include <cfenv>	// std::fesetround()
#include <string>
#include <exception>
#include <chrono>
#include <iostream>
#include <complex>	// std::log()
#include <limits>	// std::numeric_limits<float>::epsilon()

class doyouknow_class
{
	public:
		doyouknow_class(void);
		~doyouknow_class(void);

	public:
		void set_fpround(int mode);

	public:
		void func_01(void);
		void func_fp32_round(int iter, float fp32_a, float fp32_b);
		void func_fp32_unit(int iter, float fp32_a, float fp32_b);

	public:
		void func_02(void);
		void func_fp64_round(int iter, float fp32_a, float fp32_b);
		void func_fp64_unit(int iter, float fp32_a, float fp32_b);

	public:
		void func_03(void);
		void func_fp16_round(int iter, float fp32_a, float fp32_b);
		void func_fp16_unit(int iter, float fp32_a, float fp32_b);

	public:
		void func_04(void);
		void func_fp32_epsilon(void);

};
