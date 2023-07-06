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

		int8_t					a_i8 = 0U;
		int8_t const*			a_i8_ptr = nullptr;
		int8_t					aa_i8 = 0U;

		int8_t					b_i8 = 0U;
		int8_t* const			b_i8_ptr = &b_i8;
		int8_t					bb_i8 = 0U;

		int8_t					c_i8 = 0U;
		int8_t*					c_i8_ptr = nullptr;
		int8_t					cc_i8 = 0U;
		int8_t*					cc_i8_ptr = nullptr;
		int8_t* const* const	ccc_i8_ptr = &cc_i8_ptr;

		///////////////////////////////////////////////////////////////

		// [Example]
		// ((int8_t) const)* a_i8_ptr
		// change value       : O
		// change value-value : X
		// Value const

		a_i8 = 1U;
		a_i8_ptr = &a_i8;
		// change value       : O
		printf("a_i8_ptr       : %lld\n", (int64_t)a_i8_ptr);
		printf("a_i8_ptr value : %lld\n", (int64_t)(*a_i8_ptr));

		aa_i8 = 2U;
		a_i8_ptr = &aa_i8;
		// change value       : O
		printf("a_i8_ptr       : %lld\n", (int64_t)a_i8_ptr);
		printf("a_i8_ptr value : %lld\n", (int64_t)(*a_i8_ptr));

		// *a_i8_ptr = a_i8;
		// change value-value : X

		///////////////////////////////////////////////////////////////

		printf("\n");

		///////////////////////////////////////////////////////////////

		// [Example]
		// (int8_t*) const b_i8_ptr
		// change value       : X
		// change value-value : O
		// Pointer const

		b_i8 = 3U;
		*b_i8_ptr = b_i8;
		// change value-value : O
		printf("b_i8_ptr       : %lld\n", (int64_t)b_i8_ptr);
		printf("b_i8_ptr value : %lld\n", (int64_t)(*b_i8_ptr));

		bb_i8 = 4U;
		*b_i8_ptr = bb_i8;
		// change value-value : O
		printf("b_i8_ptr       : %lld\n", (int64_t)b_i8_ptr);
		printf("b_i8_ptr value : %lld\n", (int64_t)(*b_i8_ptr));

		// b_i8_ptr = &bb_i8;
		// change value       : X

		///////////////////////////////////////////////////////////////

		printf("\n");

		///////////////////////////////////////////////////////////////

		// [Example]
		// ((int8_t*) const)* const ccc_i8_ptr
		// change value             : X
		// change value-value       : X
		// change value-value-value : O
		// ((Pointer const) Pointer cosnt)

		cc_i8 = 5U;
		cc_i8_ptr = &cc_i8;
		printf("ccc_i8_ptr                                   : %lld\n", (int64_t)ccc_i8_ptr);
		printf("ccc_i8_ptr value (ptr -> ptr)                : %lld\n", (int64_t)(*ccc_i8_ptr));
		printf("ccc_i8_ptr value-value (ptr -> ptr -> value) : %lld\n", (int64_t)(*(*ccc_i8_ptr)));

		c_i8 = 6U;
		cc_i8_ptr = &c_i8;
		printf("ccc_i8_ptr                                   : %lld\n", (int64_t)ccc_i8_ptr);
		printf("ccc_i8_ptr value (ptr -> ptr)                : %lld\n", (int64_t)(*ccc_i8_ptr));
		printf("ccc_i8_ptr value-value (ptr -> ptr -> value) : %lld\n", (int64_t)(*(*ccc_i8_ptr)));

		(*(*ccc_i8_ptr)) = 7U;
		// change value-value-value : O
		printf("ccc_i8_ptr                                   : %lld\n", (int64_t)ccc_i8_ptr);
		printf("ccc_i8_ptr value (ptr -> ptr)                : %lld\n", (int64_t)(*ccc_i8_ptr));
		printf("ccc_i8_ptr value-value (ptr -> ptr -> value) : %lld\n", (int64_t)(*(*ccc_i8_ptr)));

		printf("c_i8                                         : %lld\n", (int64_t)c_i8);
		printf("cc_i8                                        : %lld\n", (int64_t)cc_i8);

		// ccc_i8_ptr = &c_i8_ptr;
		// (*ccc_i8_ptr) = &c_i8_ptr;
		// change value             : X
		// change value-value       : X

		///////////////////////////////////////////////////////////////

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

	do_you_know_ptr->ptr_const();

	delete do_you_know_ptr;
	do_you_know_ptr = nullptr;

	return;
}