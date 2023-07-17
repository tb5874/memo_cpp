#include <doyouknow_bitwise.hpp>

DOYOUKNOW_CLASS::DOYOUKNOW_CLASS(void)
{
	return;
}

DOYOUKNOW_CLASS::~DOYOUKNOW_CLASS(void)
{
	return;
}

void DOYOUKNOW_CLASS::bitwise(void)
{
	try {
		///////////////////////////////////////////////////////////////

		uint8_t		bitwise_target_u8 = 0U;
		uint16_t	bitwise_target_u16 = 0U;
		uint8_t		bitwise_data_u8 = 0U;

		///////////////////////////////////////////////////////////////

		// [Example]
		// Shift operator -> static_cast(for bit cutting.)

		bitwise_target_u8 = 0U;
		// 0000 0000 
		bitwise_data_u8 = 0x5aU;
		// 0101 1010
		bitwise_target_u8 = (~bitwise_data_u8) >> 4;
		// ~(0101 1010)
		// =
		// (64bit)
		// 1111 1111 1111 1111
		// 1111 1111 1111 1111
		// 1111 1111 1111 1111
		// 1111 1111 1010 0101
		// >> 4
		// = 
		// 0000 1111 1111 1111
		// 1111 1111 1111 1111
		// 1111 1111 1111 1111
		// 1111 1111 1111 1010
		// =
		// bitwise_target = 1111 1010 = 0xFA
		bitwise_target_u8 = (static_cast<uint8_t> (~bitwise_data_u8)) >> 4;
		// ~(0101 1010)
		// =
		// (64bit)
		// 1111 1111 1111 1111
		// 1111 1111 1111 1111
		// 1111 1111 1111 1111
		// 1111 1111 1010 0101
		// static_cast<uint8_t>
		// = 
		// 1010 0101
		// >> 4
		// = 
		// 0000 1010
		// =
		// bitwise_target = 0000 1010 = 0x0A

		///////////////////////////////////////////////////////////////

		// [Example]
		// Same size bitwise.

		bitwise_target_u16 = 0U;
		// 0000 0000 0000 0000
		bitwise_data_u8 = ~(0x10);
		// ~(0001 0000)
		// =
		// (64bit system)
		// 1111 1111 1111 1111
		// 1111 1111 1111 1111
		// 1111 1111 1111 1111
		// 1111 1111 1110 1111
		// =
		// 1110 1111
		bitwise_target_u16 ^= bitwise_data_u8;
		// 0000 0000 0000 0000
		// xor
		//           1110 1111
		// =
		// ???? ???? 1110 1111 (top 8bit did not bitwise.)

		///////////////////////////////////////////////////////////////
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

		do_you_know_ptr->bitwise();

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