#pragma once
#include <iostream>

class Test_Class {
	public:
		Test_Class();
		~Test_Class();
	public:
		void Test_Function(void);
	public:
		int64_t Test_Var;
};

Test_Class::Test_Class() {
	Test_Var = 0;
	return;
};

Test_Class::~Test_Class() {
	return;
};

void Test_Class::Test_Function(void) {
	Test_Var = 1;
	return;
};

class Test_GetNullptr {
	public:
		Test_GetNullptr();
		~Test_GetNullptr();
	public:
		Test_GetNullptr(Test_Class* get_ptr);
};

Test_GetNullptr::Test_GetNullptr() {
	return;
};

Test_GetNullptr::~Test_GetNullptr() {
	return;
};

Test_GetNullptr::Test_GetNullptr(Test_Class* get_ptr) {
	// Evenif get_ptr is nullptr, this function don't care.
	// That is No Error, No Exception.
	// So, you need to check 'get_ptr != nullptr'
	get_ptr->Test_Function();
	return;
};

class DOYOUKNOW_CLASS {
public:
	DOYOUKNOW_CLASS(void);
	~DOYOUKNOW_CLASS(void);
public:
	void std_class(void);
	void constructor_nullptr(void);
};

DOYOUKNOW_CLASS::DOYOUKNOW_CLASS(void) {
	return;
}

DOYOUKNOW_CLASS::~DOYOUKNOW_CLASS(void) {
	return;
}

void DOYOUKNOW_CLASS::std_class(void)
{
	try {
		return;
	}
	catch (std::exception& e) {
		printf("C++ Exception( std::exception ) : %s\n", e.what());
	}
	catch (...) {
		printf("C++ Exception( ... ) : Not std::exception\n");
	}
}

void DOYOUKNOW_CLASS::constructor_nullptr(void)
{
	try {
		// Why this is work?
		// Becasue Test_GetEmptyClass have pointer constructor 'Test_GetEmptyClass(Test_EmptyClass* get_ptr)'
		Test_GetNullptr a;
		a = nullptr;
		return;
	}
	catch (std::exception& e) {
		printf("C++ Exception( std::exception ) : %s\n", e.what());
	}
	catch (...) {
		printf("C++ Exception( ... ) : Not std::exception\n");
	}
}
