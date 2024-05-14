#include <doyouknow_float.hpp>

doyouknow_class::doyouknow_class(void) {
	return;
}

doyouknow_class::~doyouknow_class(void) {
	return;
}

void doyouknow_class::func_set_fpround(int mode) {
    try {

        // default is FE_TONEAREST : -->
        std::fesetround(mode);
        // default is FE_TONEAREST : <--

        int get_rounding_mode = std::fegetround();

        printf("do you know float ? : floating point - rounding mode\n");

        switch (get_rounding_mode) {
            case FE_TONEAREST: {
                printf("  FE_TONEAREST\n");
                break;
            }
            case FE_UPWARD: {
                printf("  FE_UPWARD\n");
                break;
            }
            case FE_DOWNWARD: {
                printf("  FE_DOWNWARD\n");
                break;
            }
            case FE_TOWARDZERO: {
                printf("  FE_TOWARDZERO\n");
                break;
            }
            default: {
                printf("  unknown : %d\n", get_rounding_mode);
                break;
            }
        }

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

void doyouknow_class::func_unit(int iter, float fp32_a, float fp32_b) {
    try {

        float fp32_c = 0.0f;

        fp32_c = 0.0f;
        printf("  %20.20f (1 / 3)\n", iter, fp32_a / fp32_b);

        fp32_c = 0.0f;
        for (int idx = 0; idx < iter; idx++) {
            fp32_c += fp32_a / fp32_b;
        }
        printf("  %20.20f (iter(%d) 1 / 3)\n", iter, fp32_c);

        fp32_c = 0.0f;
        fp32_c = fp32_a / fp32_b * iter;
        printf("  %20.20f (multiple 1 / 3 * %d)\n", fp32_c, iter);

        fp32_c = (float)(iter / 3);
        fp32_c = fp32_c + (fp32_a / fp32_b);
        printf("  %20.20f (math %d + 1 / 3 )\n", iter / 3, fp32_c);

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




void doyouknow_class::func_01(void) {
	try {

		printf("do you know float ? : %s\n", ((std::string)__func__).c_str() );

        int get_rounding_mode = 0;

        int iter = 0;
        float fp32_a = 0.0f;
        float fp32_b = 0.0f;
        float fp32_c = 0.0f;
        
        ////////////////////////////////////////////////////////////////////////////////////////////////////        

        func_set_fpround(FE_TONEAREST);

        iter = 4;
        fp32_a = 1.0f;
        fp32_b = 3.0f;

        func_unit(iter, fp32_a, fp32_b);

        ////////////////////////////////////////////////////////////////////////////////////////////////////        

        func_set_fpround(FE_DOWNWARD);

        iter = 4;
        fp32_a = 1.0f;
        fp32_b = 3.0f;

        func_unit(iter, fp32_a, fp32_b);

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        func_set_fpround(FE_TONEAREST);

        iter = 7;
        fp32_a = 1.0f;
        fp32_b = 3.0f;

        func_unit(iter, fp32_a, fp32_b);

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        func_set_fpround(FE_DOWNWARD);

        iter = 7;
        fp32_a = 1.0f;
        fp32_b = 3.0f;

        func_unit(iter, fp32_a, fp32_b);

        ////////////////////////////////////////////////////////////////////////////////////////////////////


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
