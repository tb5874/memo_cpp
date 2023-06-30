#include <doyouknow_ptr.hpp>

DOYOUKNOW_CLASS::DOYOUKNOW_CLASS(void)
{
	return;
}

DOYOUKNOW_CLASS::~DOYOUKNOW_CLASS(void)
{
	return;
}

void DOYOUKNOW_CLASS::ptr_const(void)
{
	try {
		///////////////////////////////////////////////////////////////
		// ((int8_t) const)*
		// (int8_t*) const
		// (((int8_t*) const)*) const
		///////////////////////////////////////////////////////////////

		///////////////////////////////////////////////////////////////
		int8_t int8_a = 1U;
		int8_t int8_aa = 2U;
		// change value : X
		// change address : O
		int8_t const * int8_ptr_a = nullptr;

		int8_ptr_a = &int8_a;
		printf("int8_ptr_a ptr  : %lld\n", (int64_t)int8_ptr_a);
		printf("int8_ptr_a value : %lld\n", (int64_t)(*int8_ptr_a));

		int8_ptr_a = &int8_aa;
		printf("int8_ptr_a ptr  : %lld\n", (int64_t)int8_ptr_a);
		printf("int8_ptr_a value : %lld\n", (int64_t)(*int8_ptr_a));

		// Can't
		//*int8_ptr_a = int8_aa;
		///////////////////////////////////////////////////////////////

		///////////////////////////////////////////////////////////////
		int8_t int8_b = 3U;
		int8_t int8_bb = 4U;
		// change value : O
		// change address : X
		int8_t* const int8_ptr_b = &int8_bb;

		// Can't
		//int8_ptr_b = &int8_bb;
		printf("int8_ptr_b ptr  : %lld\n", (int64_t)int8_ptr_b);
		printf("int8_ptr_b value : %lld\n", (int64_t)(*int8_ptr_b));

		*int8_ptr_b = int8_b;
		printf("int8_ptr_b ptr  : %lld\n", (int64_t)int8_ptr_b);
		printf("int8_ptr_b value : %lld\n", (int64_t)(*int8_ptr_b));
		///////////////////////////////////////////////////////////////

		///////////////////////////////////////////////////////////////
		int8_t int8_c = 5U;
		int8_t int8_cc = 6U;
		int8_t* int8_ccc = &int8_cc;
		// change value : O
		// change address : X
		int8_t* const * const int8_ptr_c = &int8_ccc;

		// Can't
		//(int8_ptr_c) = &int8_ccc;
		//(*int8_ptr_c) = &int8_ccc;
		printf("int8_ptr_c ptr  : %lld\n", (int64_t)int8_ptr_c);
		printf("int8_ptr_c value (ptr -> ptr) : %lld\n", (int64_t)(*int8_ptr_c));
		printf("int8_ptr_c value-value (ptr -> ptr -> value) : %lld\n", (int64_t)(*(*int8_ptr_c)));

		(*(*int8_ptr_c)) = int8_c;
		printf("int8_ptr_c ptr  : %lld\n", (int64_t)int8_ptr_c);
		printf("int8_ptr_c value (ptr -> ptr) : %lld\n", (int64_t)(*int8_ptr_c));
		printf("int8_ptr_c value-value (ptr -> ptr -> value) : %lld\n", (int64_t)(*(*int8_ptr_c)));
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

	do_you_know->ptr_const();

	delete do_you_know;
	do_you_know = nullptr;

	return;
}