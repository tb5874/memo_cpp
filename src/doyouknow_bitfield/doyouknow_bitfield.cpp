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
		// Total size 1 byte (uint32_t)
		struct bitfield_test01
		{
			uint8_t a : 1; // bit position 1
			uint8_t b : 1; // bit position 2
			uint8_t   : 6; // Padding
		};
		bitfield_test01 test_01;
		memset(&test_01, 0, sizeof(struct bitfield_test01));
		printf("test_bf %p\n", &test_01);
		printf("test_bf size %lld\n", (int64_t)sizeof(struct bitfield_test01)); // 1 byte
		// (uint8_t)1 = 0000 0001
		// (uint8_t)2 = 0000 0010
		test_01.a = (uint8_t)1; // save 1bit : 1 (bit position 1)
		test_01.b = (uint8_t)2; // save 1bit : 0 (bit position 2)

		// Total size 4 byte (uint32_t)
		struct bitfield_test02
		{
			uint32_t a : 1; // bit position 1
			uint32_t b : 1; // bit position 2
			uint32_t   : 30; // Padding
		};
		bitfield_test02 test_02;
		memset(&test_02, 0, sizeof(struct bitfield_test02));
		printf("test_bf %p\n", &test_02);
		printf("test_bf size %lld\n", (int64_t)sizeof(struct bitfield_test02)); // 4 byte
		// (uint32_t)1 = 0000 0000 0000 0000 0000 0000 0000 0001
		// (uint32_t)2 = 0000 0000 0000 0000 0000 0000 0000 0010
		test_02.a = (uint32_t)1; // save 1bit : 1 (bit position 1)
		test_02.b = (uint32_t)2; // save 1bit : 0 (bit position 2)

		// Total size 4 byte (uint32_t)
		struct bitfield_test03
		{
			uint32_t a : 1; // bit position 1
			uint32_t   : 7; // Padding
			uint32_t b : 1; // bit position 8
			uint32_t   : 23; // Padding
		};
		bitfield_test03 test_03;
		memset(&test_03, 0, sizeof(struct bitfield_test03));
		printf("test_bf %p\n", &test_03);
		printf("test_bf size %lld\n", (int64_t)sizeof(struct bitfield_test03)); // 4 byte
		// (uint32_t)1 = 0000 0000 0000 0000 0000 0000 0000 0001
		test_03.a = (uint32_t)1; // save 1bit : 1 (bit position 1)
		test_03.b = (uint32_t)1; // save 1bit : 1 (bit position 8)

		// Total size 8 byte (uint32_t x 2)
		struct bitfield_test04
		{
			uint32_t a : 1; // bit position 1
			uint32_t   : 0; // this mean, uint32_t x 2, must be unnamed.
			uint32_t b : 1; // next 4 byte, bit position 1
			uint32_t   : 31; // Padding
		};
		bitfield_test04 test_04;
		memset(&test_04, 0, sizeof(struct bitfield_test04));
		printf("test_bf %p\n", &test_04);
		printf("test_bf size %lld\n", (int64_t)sizeof(struct bitfield_test04)); // 8 byte
		// (uint32_t)1 = 0000 0000 0000 0000 0000 0000 0000 0001
		test_04.a = (uint32_t)1; // save 1bit : 1 (bit position 1)
		test_04.b = (uint32_t)1; // save 1bit : 1 (next 4 byte, bit position 1)

		// Total size 8 byte (uint32_t x 2)
		struct bitfield_test05
		{
			uint32_t a : 32; // use 32 bit
			uint32_t b : 1;  // next 32 bit : bit position 1
		};
		bitfield_test05 test_05;
		memset(&test_05, 0, sizeof(struct bitfield_test05));
		printf("test_bf %p\n", &test_05);
		printf("test_bf size %lld\n", (int64_t)sizeof(struct bitfield_test05)); // 8 byte
		// (uint32_t)4294967295 = 1111 1111 1111 1111 1111 1111 1111 1111
		test_05.a = (uint32_t)4294967295; // save 32bit
		test_05.b = (uint32_t)1;          // save 1bit : 1 (next 4 byte, bit position 1)

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
	try{
		DOYOUKNOW_CLASS* do_you_know_ptr;
		do_you_know_ptr = new DOYOUKNOW_CLASS();

		do_you_know_ptr->bitfield();

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