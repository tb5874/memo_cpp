#include <doyouknow_bitfield.hpp>

DOYOUKNOW_CLASS::DOYOUKNOW_CLASS(void)
{
	return;
}

DOYOUKNOW_CLASS::~DOYOUKNOW_CLASS(void)
{
	return;
}

void DOYOUKNOW_CLASS::bitfield(void)
{
	try {

		struct bit_field_test
		{
			signed int a : 1; // Non-compliant
			signed int : 1; // Compliant
			signed int : 0; // Compliant
			signed int b : 2; // Compliant
			signed int : 2; // Compliant
		};

		bit_field_test test_bf;
		test_bf.a = (int32_t)(-1);
		test_bf.b = 1;
		printf("%lld", test_bf.a);
	}
	catch (std::exception& e) {
		printf("C++ Exception( std::exception ) : %s\n", e.what());
	}

	return;
}

void main(void)
{
	DOYOUKNOW_CLASS* do_you_know_ptr;
	do_you_know_ptr = new DOYOUKNOW_CLASS();

	do_you_know_ptr->bitfield();

	delete do_you_know_ptr;
	do_you_know_ptr = nullptr;

	return;
}