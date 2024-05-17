///////////////////////////////////////////////////////////

#pragma once

// https://learn.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4100?view=msvc-170
	// 4100
	// no reference variables warning.

// https://learn.microsoft.com/en-us/cpp/error-messages/tool-errors/command-line-warning-d9025?view=msvc-170
	// D9025
	// option overriding warning.
	// [ example ] EHs -> EHa
	// EHs : only catch std c++ exception structure.
	// EHa : all catch exception.

///////////////////////////////////////////////////////////

#include <cfenv>
#include <string>
#include <exception>
#include <chrono>
#include <iostream>

class doyouknow_class
{
	public:
		doyouknow_class(void);
		~doyouknow_class(void);

	public:
		void func_01(void);

	public:
		void func_02(void);

	public:
		void func_03(void);

};
