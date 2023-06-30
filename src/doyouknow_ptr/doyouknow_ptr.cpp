#include <doyouknow_ptr.hpp>

DOYOUKNOW_CLASS::DOYOUKNOW_CLASS(void)
{
	return;
}

DOYOUKNOW_CLASS::~DOYOUKNOW_CLASS(void)
{
	return;
}

void DOYOUKNOW_CLASS::ptr_test(void)
{
	try {

		printf("Hello world !!!\n");
	}
	catch (std::exception& e) {
		printf("C++ Exception( std::exception ) : %s\n", e.what());
	}

	return;
}

void main(void)
{
	DOYOUKNOW_CLASS* do_you_know;
	do_you_know = new DOYOUKNOW_CLASS();

	do_you_know->ptr_test();

	delete do_you_know;
	do_you_know = nullptr;

	return;
}