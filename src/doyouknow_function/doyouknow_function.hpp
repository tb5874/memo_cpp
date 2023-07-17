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
		const void		before_const_void(void);
		const int32_t	before_const_int(void);
		void const		before_void_const(void);
		int32_t const	before_int_const(void);

		void after_const(void) const;
		void after_throw(void) throw (const char*);

		void just_throw(void);
};
