#include <doyouknow_macro.hpp>

DOYOUKNOW_CLASS::DOYOUKNOW_CLASS(void)
{
	return;
}

DOYOUKNOW_CLASS::~DOYOUKNOW_CLASS(void)
{
	return;
}

void DOYOUKNOW_CLASS::std_macro(void)
{
	try {
		int32_t glue_char(1) = 1;
		int32_t glue_char(10) = 10;

		printf("Macro define variable glue1 : %d\n", glue1);
		printf("Macro define variable glue10 : %d\n", glue10);

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

		do_you_know_ptr->std_macro();

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