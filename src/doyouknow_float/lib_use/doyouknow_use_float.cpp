#include <doyouknow_use_float.hpp>

int main(void) {
	try {

		void* get_ptr = doyouknow_float_get();

		doyouknow_float_func01(get_ptr);

		doyouknow_float_func02(get_ptr);

		doyouknow_float_func03(get_ptr);

		return 0;

	}
	catch (std::exception& e) {
		printf("C++ Exception( std::exception ) : %s\n", e.what());
	}
	catch (...) {
		printf("C++ Exception( ... ) : Not std::exception\n");
	}
}
