#pragma once

#include <string>
#include <exception>
#include <chrono>
#include <iostream>

#include <cfenv>

class doyouknow_class
{
	public:
		doyouknow_class(void);
		~doyouknow_class(void);

	public:
		void func_set_fpround(int mode);
		void func_unit(int iter, float fp32_a, float fp32_b);
		void func_01(void);
		void func_02(void);		

};
