#include <doyouknow_class.hpp>

// need to update : copy operator sample.

DOYOUKNOW_CLASS::DOYOUKNOW_CLASS(void)
{
	return;
}

DOYOUKNOW_CLASS::~DOYOUKNOW_CLASS(void)
{
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

void main(void)
{
	try {
		DOYOUKNOW_CLASS* do_you_know_ptr;
		do_you_know_ptr = new DOYOUKNOW_CLASS();

		do_you_know_ptr->std_class();

		delete do_you_know_ptr;
		do_you_know_ptr = nullptr;

		return;
	}
	catch (std::exception& e) {
		printf("C++ Exception( std::exception ) : %s\n", e.what());
	}
	catch (...) {
		printf("C++ Exception( ... ) : Not std::exception\n");
	}
}