#include <doyouknow_function.hpp>

DOYOUKNOW_CLASS::DOYOUKNOW_CLASS(void)
{
	member_a = 0;
	member_b = 0;
	return;
}

DOYOUKNOW_CLASS::~DOYOUKNOW_CLASS(void)
{
	return;
}

const void DOYOUKNOW_CLASS::before_const_void(void)
{
	try {
		printf("%s\n",__FUNCTION__);
		return;
	}
	catch (std::exception& e) {
		printf("C++ Exception( std::exception ) : %s\n", e.what());
	}
	catch (...) {
		printf("C++ Exception( std::exception ) : Not std::exception\n");
	}
}

const int32_t DOYOUKNOW_CLASS::before_const_int(void)
{
	try {
		// 'return' copy 'return_value' to outside.
		printf("%s\n", __FUNCTION__);
		int32_t return_value = 123;
		return return_value;
	}
	catch (std::exception& e) {
		printf("C++ Exception( std::exception ) : %s\n", e.what());
	}
	catch (...) {
		printf("C++ Exception( std::exception ) : Not std::exception\n");
	}
}

void const DOYOUKNOW_CLASS::before_void_const(void)
{
	try {
		printf("%s\n", __FUNCTION__);
		return;
	}
	catch (std::exception& e) {
		printf("C++ Exception( std::exception ) : %s\n", e.what());
	}
	catch (...) {
		printf("C++ Exception( std::exception ) : Not std::exception\n");
	}
}

int32_t const DOYOUKNOW_CLASS::before_int_const(void)
{
	try {
		printf("%s\n", __FUNCTION__);
		int32_t return_value = 123;
		return return_value;
	}
	catch (std::exception& e) {
		printf("C++ Exception( std::exception ) : %s\n", e.what());
	}
	catch (...) {
		printf("C++ Exception( std::exception ) : Not std::exception\n");
	}
}

void DOYOUKNOW_CLASS::after_const(void) const
{
	try {
		printf("%s\n", __FUNCTION__);
		// All variable is const.
		// Can't modify class member variable.
		//member_a = 1;
		return;
	}
	catch (std::exception& e) {
		printf("C++ Exception( std::exception ) : %s\n", e.what());
	}
	catch (...) {
		printf("C++ Exception( std::exception ) : Not std::exception\n");
	}
}

void DOYOUKNOW_CLASS::after_throw(void) throw (const char*)
{
	try {
		// throw (const char*) is like comment.
		// throw (const char*) is not force condition.
		// throw (const char*) can ignore. (Warning C4290)
		throw (int32_t)123;
		return;
	}
	catch (std::exception& e) {
		printf("C++ Exception( std::exception ) : %s\n", e.what());
	}
	catch (int32_t catch_int32_t) {
		printf("C++ Exception( std::exception ) : %d\n", catch_int32_t);
	}
	catch (...) {
		printf("C++ Exception( std::exception ) : Not std::exception\n");
	}
}

void DOYOUKNOW_CLASS::just_throw(void)
{
	try {
		throw (int32_t)123;
		return;
	}
	catch (std::exception& e) {
		printf("C++ Exception( std::exception ) : %s\n", e.what());
	}
	catch (...) {
		printf("C++ Exception( std::exception ) : Not std::exception\n");
	}
}

void main(void)
{
	try {
		DOYOUKNOW_CLASS* do_you_know_ptr;
		do_you_know_ptr = new DOYOUKNOW_CLASS();

		int32_t get_return;

		do_you_know_ptr->before_const_void();
		get_return = do_you_know_ptr->before_const_int();
		do_you_know_ptr->before_void_const();
		get_return = do_you_know_ptr->before_int_const();

		do_you_know_ptr->after_const();
		do_you_know_ptr->after_throw();

		do_you_know_ptr->just_throw();

		delete do_you_know_ptr;
		do_you_know_ptr = nullptr;

		return;
	}
	catch (std::exception& e) {
		printf("C++ Exception( std::exception ) : %s\n", e.what());
	}
	catch (...) {
		printf("C++ Exception( std::exception ) : Not std::exception\n");
	}
}