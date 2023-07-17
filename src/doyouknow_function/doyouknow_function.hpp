#pragma once
#include <iostream>
#include <vector>

class DOYOUKNOW_CLASS
{
	public:
		DOYOUKNOW_CLASS(void);
		~DOYOUKNOW_CLASS(void);
		int32_t member_a;
		int32_t member_b;

public:
		const void function_define_before_const_void(void);
		const int32_t function_define_before_const_int(void);

		void const function_define_before_void_const(void);
		int32_t const function_define_before_int_const(void);

		void function_define_after_const(void) const;
		void function_define_after_throw(void) throw (const char*);
		void function_define_throw(void);
};
