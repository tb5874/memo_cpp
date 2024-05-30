#include <libuse_wav.hpp>

int main(void) {
	try {

		void* get_ptr = doyouknow_get();
		doyouknow_func01(get_ptr);
		doyouknow_func02(get_ptr);

		return 0;

	}
	catch (std::exception& e) {
		printf("C++ Exception( std::exception ) : %s\n", e.what());
	}
	catch (...) {
		printf("C++ Exception( ... ) : Not std::exception\n");
	}
}
