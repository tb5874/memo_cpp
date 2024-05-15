#include <doyouknow_float.hpp>

doyouknow_class::doyouknow_class(void) {
	return;
}

doyouknow_class::~doyouknow_class(void) {
	return;
}

void doyouknow_class::set_fpround(int mode) {
    try {

        // default is FE_TONEAREST : -->
        std::fesetround(mode);
        // default is FE_TONEAREST : <--

        int get_rounding_mode = std::fegetround();

        printf("\nfloating point - rounding mode : ");

        switch (get_rounding_mode) {
            case FE_TONEAREST: {
                printf("FE_TONEAREST\n");
                break;
            }
            case FE_UPWARD: {
                printf("FE_UPWARD\n");
                break;
            }
            case FE_DOWNWARD: {
                printf("FE_DOWNWARD\n");
                break;
            }
            case FE_TOWARDZERO: {
                printf("FE_TOWARDZERO\n");
                break;
            }
            default: {
                printf("unknown : %d\n", get_rounding_mode);
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

void doyouknow_class::func_01(void) {
    try {

        printf("\ndo you know float ? : %s\n", ((std::string)__func__).c_str());

        int iter = 0;
        float fp32_a = 0.0f;
        float fp32_b = 0.0f;

        ////////////////////////////////////////////////////////////////////////////////////////////////////        

        iter = 3;
        fp32_a = 1.0f;
        fp32_b = 3.0f;
        func_fp32_round(iter, fp32_a, fp32_b);

        iter = 4;
        fp32_a = 1.0f;
        fp32_b = 3.0f;
        func_fp32_round(iter, fp32_a, fp32_b);

        iter = 7;
        fp32_a = 1.0f;
        fp32_b = 3.0f;
        func_fp32_round(iter, fp32_a, fp32_b);

        iter = (int)1e+6;
        fp32_a = 1.0f;
        fp32_b = 3.0f;
        func_fp32_round(iter, fp32_a, fp32_b);

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

void doyouknow_class::func_fp32_round(int iter, float fp32_a, float fp32_b) {
    try {

        set_fpround(FE_TONEAREST);
        func_fp32_unit(iter, fp32_a, fp32_b);

        set_fpround(FE_UPWARD);
        func_fp32_unit(iter, fp32_a, fp32_b);

        set_fpround(FE_DOWNWARD);
        func_fp32_unit(iter, fp32_a, fp32_b);

        set_fpround(FE_TOWARDZERO);
        func_fp32_unit(iter, fp32_a, fp32_b);

    }
    catch (std::exception& e) {
        printf("C++ Exception( std::exception ) : %s\n", e.what());
    }
    catch (...) {
        printf("C++ Exception( ... ) : Not std::exception\n");
    }

    return;

}

void doyouknow_class::func_fp32_unit(int iter, float fp32_a, float fp32_b) {
    try {

        // IEEE 754
        // 1 bit        : + is 0 | - is 1   (1)
        // 2 ~ 9 bit    : exponent          (8)
        // 10 ~ 32 bit  : mantissa          (23)

        // ##################################################
        // 1/3
        // [ Step 01 ]
            // 0.333333 ...
            // integer == 0
            // decimal == 010101 ...
                // 0.333333 x 2 : 0.666666 -> 0
                // 0.666666 x 2 : 1.333333 -> 1
                // 0.333333 x 2 : 0.666666 -> 0
                // 0.666666 x 2 : 1.333333 -> 1
                // 0.333333 x 2 : 0.666666 -> 0
                // 0.666666 x 2 : 1.333333 -> 1
                // ...
        // [ Step 02 ]
            // 0.010101 ...
            // 1.010101 ... x 2^-2
            // power    == -2
            // decimal  == 010101 ...
        // [ Step 03 ]
            // -2(power) + 127 == 125
            // 0111 1101
        // [ Step 04 ]
            // Step 02 + Step 03            
            // [ 1 bit ]    + [ 2 ~ 9 bit ] + [ 10 ~ 32 bit ]
            // [ Sign ]     + [ Step 03 ]   + [ decimal of Step 02 ]
            // 00111110 10101010 10101010 10101010
        // ##################################################

        // ##################################################
        // 1.0
        // [ Step 01 ]
            // 1.000000 ... 
            // integer == 1
            // decimal == 000000 ...
                // 0.000000 x 2 : 0.000000 -> 0
                // 0.000000 x 2 : 0.000000 -> 0
                // 0.000000 x 2 : 0.000000 -> 0
                // 0.000000 x 2 : 0.000000 -> 0
                // 0.000000 x 2 : 0.000000 -> 0
                // 0.000000 x 2 : 0.000000 -> 0
                // ...
        // [ Step 02 ]
            // 1.000000 ...
            // 1.000000 ... x 2^0
            // power    == 0
            // decimal  == 000000 ...
        // [ Step 03 ]
            // 0(power) + 127 == 127
            // 0111 1111
        // [ Step 04 ]
            // Step 02 + Step 03            
            // [ 1 bit ]    + [ 2 ~ 9 bit ] + [ 10 ~ 32 bit ]
            // [ Sign ]     + [ Step 03 ]   + [ decimal of Step 02 ]
            // 00111111 10000000 00000000 00000000
        // ##################################################

        printf("\n  [float32]\n");

        printf("\n  math : ( %f / %f ) x %d\n", fp32_a, fp32_b, iter);               


        volatile float fp32_c = 0.0f;

        volatile int get_bit = 0;


        fp32_c = 0.0f;
        fp32_c = fp32_a / fp32_b;
        printf("\n  unit : ( %f / %f )\n", fp32_a, fp32_b);
        printf("  calc : ( %f / %f )\n", fp32_a, fp32_b);
        printf("  bits : ");
        for (int bit_index = 31; bit_index >= 0; bit_index--) {
            get_bit = 1 << bit_index;
            printf("%d", *(int*)(&fp32_c) & get_bit ? 1 : 0);
            if (bit_index % 8 == 0) {
                printf(" ");
            }
        }
        printf("\n  fp32 : %-30.20f\n", fp32_c);


        fp32_c = 0.0f;
        fp32_c = fp32_a / fp32_b;
        fp32_c = fp32_c * (float)iter;
        printf("\n  calc : ( %f / %f ) and x %d\n", fp32_a, fp32_b, iter);
        printf("  bits : ");
        for (int bit_index = 31; bit_index >= 0; bit_index--) {
            get_bit = 1 << bit_index;
            printf("%d", *(int*)(&fp32_c) & get_bit ? 1 : 0);
            if (bit_index % 8 == 0) {
                printf(" ");
            }
        }
        printf("\n  fp32 : %-30.20f\n", fp32_c);
        

        fp32_c = 0.0f;
        fp32_c = fp32_a / fp32_b * (float)iter;
        printf("\n  calc : ( %f / %f ) x %d\n", fp32_a, fp32_b, iter);
        printf("  bits : ");
        for (int bit_index = 31; bit_index >= 0; bit_index--) {
            get_bit = 1 << bit_index;
            printf("%d", *(int*)(&fp32_c) & get_bit ? 1 : 0);
            if (bit_index % 8 == 0) {
                printf(" ");
            }
        }
        printf("\n  fp32 : %-30.20f\n", fp32_c);
        

        fp32_c = 0.0f;
        for (int idx = 0; idx < iter; idx++) {
            fp32_c += (fp32_a / fp32_b);
        }
        printf("\n  calc : ( %f / %f ) iter %d\n", fp32_a, fp32_b, iter);
        printf("  bits : ");
        for (int bit_index = 31; bit_index >= 0; bit_index--) {
            get_bit = 1 << bit_index;
            printf("%d", *(int*)(&fp32_c) & get_bit ? 1 : 0);
            if (bit_index % 8 == 0) {
                printf(" ");
            }
        }
        printf("\n  fp32 : %-30.20f\n", fp32_c);

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

		printf("\ndo you know float ? : %s\n", ((std::string)__func__).c_str());

	}
	catch (std::exception& e) {
		printf("C++ Exception( std::exception ) : %s\n", e.what());
	}
	catch (...) {
		printf("C++ Exception( ... ) : Not std::exception\n");
	}

	return;

}

void doyouknow_class::func_fp64_round(int iter, float fp32_a, float fp32_b) {
    try {

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

void doyouknow_class::func_fp64_unit(int iter, float fp32_a, float fp32_b) {
    try {

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

void doyouknow_class::func_03(void) {
    try {

        printf("\ndo you know float ? : %s\n", ((std::string)__func__).c_str());

    }
    catch (std::exception& e) {
        printf("C++ Exception( std::exception ) : %s\n", e.what());
    }
    catch (...) {
        printf("C++ Exception( ... ) : Not std::exception\n");
    }

    return;

}

void doyouknow_class::func_fp16_round(int iter, float fp32_a, float fp32_b) {
    try {

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

void doyouknow_class::func_fp16_unit(int iter, float fp32_a, float fp32_b) {
    try {

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
