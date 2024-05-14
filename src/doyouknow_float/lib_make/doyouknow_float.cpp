#include <doyouknow_float.hpp>

doyouknow_class::doyouknow_class(void) {
	return;
}

doyouknow_class::~doyouknow_class(void) {
	return;
}

void doyouknow_class::func_01(void) {
	try {

		printf("do you know float ? : %s\n", ((std::string)__func__).c_str() );

		int iter = 100000;
		float fp32_a = 1.0f;
		float fp32_b = 3.0f;
		float fp32_c = 0.0f;

		fp32_c = 0.0f;
		for (int idx = 0; idx < iter; idx++) {
			fp32_c += fp32_a / fp32_b;
		}		
		printf("do you know float ? : %20.20f (iter)\n", fp32_c);
		// 33356.55468750000000000000 ( windows10, x64, visual studio 2019 )

		fp32_c = 0.0f;
		fp32_c = fp32_a / fp32_b * iter;
		printf("do you know float ? : %20.20f (multiple)\n", fp32_c);
		// 33333.33593750000000000000 ( windows10, x64, visual studio 2019 )

		return;

	}
	catch (std::exception& e) {
		printf("C++ Exception( std::exception ) : %s\n", e.what());
	}
	catch (...) {
		printf("C++ Exception( ... ) : Not std::exception\n");
	}

	return;

}

void doyouknow_class::func_02(void) {
	try {

		printf("do you know float ? : %s\n", ((std::string)__func__).c_str());

	}
	catch (std::exception& e) {
		printf("C++ Exception( std::exception ) : %s\n", e.what());
	}
	catch (...) {
		printf("C++ Exception( ... ) : Not std::exception\n");
	}

	return;

}
