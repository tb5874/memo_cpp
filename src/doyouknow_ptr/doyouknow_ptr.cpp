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
		///////////////////////////////////////////////////////////////
		int8_t int8_a = 1U;
		int8_t int8_aa = 2U;
		// change value : X (int8_t const)
		// change address : O
		int8_t const * int8_ptr_a = nullptr;

		int8_ptr_a = &int8_a;
		printf("int8_ptr_a addr  : %lld\n", (int64_t)int8_ptr_a);
		printf("int8_ptr_a value : %lld\n", (int64_t)(*int8_ptr_a));

		int8_ptr_a = &int8_aa;
		printf("int8_ptr_a addr  : %lld\n", (int64_t)int8_ptr_a);
		printf("int8_ptr_a value : %lld\n", (int64_t)(*int8_ptr_a));

		// Can't
		//*int8_ptr_a = int8_aa;
		///////////////////////////////////////////////////////////////

		///////////////////////////////////////////////////////////////
		int8_t int8_b = 3U;
		int8_t int8_bb = 4U;
		// change value : O
		// change address : X (int8_t* const)
		int8_t* const int8_ptr_b = &int8_b;

		// Can't
		//int8_ptr_b = &int8_bb;
		printf("int8_ptr_b addr  : %lld\n", (int64_t)int8_ptr_b);
		printf("int8_ptr_b value : %lld\n", (int64_t)(*int8_ptr_b));

		*int8_ptr_b = int8_bb;
		printf("int8_ptr_b addr  : %lld\n", (int64_t)int8_ptr_b);
		printf("int8_ptr_b value : %lld\n", (int64_t)(*int8_ptr_b));
		///////////////////////////////////////////////////////////////

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