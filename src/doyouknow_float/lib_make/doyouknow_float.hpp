#pragma once

#include <cfenv>
	// std::fesetround()
#include <string>
#include <exception>
#include <chrono>
#include <iostream>
#include <complex>
	// std::log()
#include <limits>
	// std::numeric_limits<float>::epsilon()

class doyouknow_class {

	public:
		doyouknow_class(void);
		~doyouknow_class(void);

	public:
		void func_01(void);
		void func_02(void);

	public:
		void func_round_set(int round_mode);

	public:
		void func_round_fp16(void);
		void func_round_fp32(void);
		void func_round_fp64(void);
		void func_round_unit_fp16(int iter, float fp32_a, float fp32_b);
		void func_round_unit_fp32(int iter, float fp32_a, float fp32_b);
		void func_round_unit_fp64(int iter, float fp32_a, float fp32_b);

	public:
		void func_epsilon_fp16(void);
		void func_epsilon_fp32(void);
		void func_epsilon_fp64(void);

};
