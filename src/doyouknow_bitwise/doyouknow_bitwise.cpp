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
		uint8_t mask = ~(0x10);
		uint16_t value = 0U;
		value ^= mask;
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

	do_you_know->bitwise();

	delete do_you_know;
	do_you_know = nullptr;

	return;
}