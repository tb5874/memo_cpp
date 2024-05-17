#include <doyouknow_float.hpp>

///////////////////////////////////////////////////////////

// https://learn.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4100?view=msvc-170
    // 4100
    // no reference variables warning.

// https://learn.microsoft.com/en-us/cpp/error-messages/tool-errors/command-line-warning-d9025?view=msvc-170
    // D9025
    // option overriding warning.
    // [ example ] EHs -> EHa
    // EHs : only catch std c++ exception structure.
    // EHa : all catch exception.

///////////////////////////////////////////////////////////

doyouknow_class::doyouknow_class(void) {
	return;
}

doyouknow_class::~doyouknow_class(void) {
	return;
}

void doyouknow_class::func_01(void) {
    try {

        printf("\n");
        printf("[ %s ]\n", ((std::string)__func__).c_str());
        printf("do you know ?\n");

        func_round_fp16();
        func_round_fp32();
        func_round_fp64();

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

        printf("\n");
        printf("[ %s ]\n", ((std::string)__func__).c_str());
        printf("do you know ?\n");

        func_epsilon_fp16();
        func_epsilon_fp32();
        func_epsilon_fp64();

    }
    catch (std::exception& e) {
        printf("C++ Exception( std::exception ) : %s\n", e.what());
    }
    catch (...) {
        printf("C++ Exception( ... ) : Not std::exception\n");
    }

    return;

}

void doyouknow_class::func_round_set(int round_mode) {
    try {

        printf("  %s()\n", ((std::string)__func__).c_str());

        // default is FE_TONEAREST
        std::fesetround(round_mode);

        printf("  round_mode : ");
        int get_round_mode = std::fegetround();
        switch (get_round_mode) {
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
                printf("unknown : %d\n", get_round_mode);
                break;
            }
        }

    }
    catch (std::exception& e) {
        printf("C++ Exception( std::exception ) : %s\n", e.what());
    }
    catch (...) {
        printf("C++ Exception( ... ) : Not std::exception\n");
    }

    return;

}

void doyouknow_class::func_round_fp16(void) {
    try {

        printf("  %s()\n", ((std::string)__func__).c_str());

    }
    catch (std::exception& e) {
        printf("C++ Exception( std::exception ) : %s\n", e.what());
    }
    catch (...) {
        printf("C++ Exception( ... ) : Not std::exception\n");
    }

    return;

}

void doyouknow_class::func_round_fp32(void) {
    try {

        printf("  %s()\n", ((std::string)__func__).c_str());

        int iter = 0;
        float fp32_a = 0.0f;
        float fp32_b = 0.0f;

        iter = 3;
        fp32_a = 1.0f;
        fp32_b = 3.0f;
        func_round_set(FE_TONEAREST);
        func_round_unit_fp32(iter, fp32_a, fp32_b);
        func_round_set(FE_UPWARD);
        func_round_unit_fp32(iter, fp32_a, fp32_b);
        func_round_set(FE_DOWNWARD);
        func_round_unit_fp32(iter, fp32_a, fp32_b);
        func_round_set(FE_TOWARDZERO);
        func_round_unit_fp32(iter, fp32_a, fp32_b);

        iter = 4;
        fp32_a = 1.0f;
        fp32_b = 3.0f;
        func_round_set(FE_TONEAREST);
        func_round_unit_fp32(iter, fp32_a, fp32_b);
        func_round_set(FE_UPWARD);
        func_round_unit_fp32(iter, fp32_a, fp32_b);
        func_round_set(FE_DOWNWARD);
        func_round_unit_fp32(iter, fp32_a, fp32_b);
        func_round_set(FE_TOWARDZERO);
        func_round_unit_fp32(iter, fp32_a, fp32_b);

        iter = 7;
        fp32_a = 1.0f;
        fp32_b = 3.0f;
        func_round_set(FE_TONEAREST);
        func_round_unit_fp32(iter, fp32_a, fp32_b);
        func_round_set(FE_UPWARD);
        func_round_unit_fp32(iter, fp32_a, fp32_b);
        func_round_set(FE_DOWNWARD);
        func_round_unit_fp32(iter, fp32_a, fp32_b);
        func_round_set(FE_TOWARDZERO);
        func_round_unit_fp32(iter, fp32_a, fp32_b);

        iter = (int)1e+6;
        fp32_a = 1.0f;
        fp32_b = 3.0f;
        func_round_set(FE_TONEAREST);
        func_round_unit_fp32(iter, fp32_a, fp32_b);
        func_round_set(FE_UPWARD);
        func_round_unit_fp32(iter, fp32_a, fp32_b);
        func_round_set(FE_DOWNWARD);
        func_round_unit_fp32(iter, fp32_a, fp32_b);
        func_round_set(FE_TOWARDZERO);
        func_round_unit_fp32(iter, fp32_a, fp32_b);

    }
    catch (std::exception& e) {
        printf("C++ Exception( std::exception ) : %s\n", e.what());
    }
    catch (...) {
        printf("C++ Exception( ... ) : Not std::exception\n");
    }

    return;

}

void doyouknow_class::func_round_fp64(void) {
    try {

        printf("  %s()\n", ((std::string)__func__).c_str());

    }
    catch (std::exception& e) {
        printf("C++ Exception( std::exception ) : %s\n", e.what());
    }
    catch (...) {
        printf("C++ Exception( ... ) : Not std::exception\n");
    }

    return;

}

void doyouknow_class::func_round_unit_fp16(int iter, float fp32_a, float fp32_b) {
    try {

        printf("  %s()\n", ((std::string)__func__).c_str());

    }
    catch (std::exception& e) {
        printf("C++ Exception( std::exception ) : %s\n", e.what());
    }
    catch (...) {
        printf("C++ Exception( ... ) : Not std::exception\n");
    }

    return;

}

void doyouknow_class::func_round_unit_fp32(int iter, float fp32_a, float fp32_b) {
    try {

        printf("  %s()\n", ((std::string)__func__).c_str());

        // IEEE 754
        // 
        //       1 bit  : + is 0
        //              : - is 1            ( 1 bit)
        //  2 ~  9 bit  : exponent          ( 8 bit)
        // 10 ~ 32 bit  : mantissa          (23 bit)
        //              : total             (32 bit)

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

        printf("\n");
        printf("  math : ( %f / %f ) x %d\n", fp32_a, fp32_b, iter);               
        printf("  unit : ( %f / %f )\n", fp32_a, fp32_b);
        volatile float fp32_c = 0.0f;
        volatile int get_bit = 0;


        printf("\n");        
        printf("  calc : ( %f / %f )\n", fp32_a, fp32_b);
        printf("  bits : ");
        fp32_c = 0.0f;
        fp32_c = fp32_a / fp32_b;
        for (int bit_index = 31; bit_index >= 0; bit_index--) {
            get_bit = 1 << bit_index;
            printf("%d", *(int*)(&fp32_c) & get_bit ? 1 : 0);
            if (bit_index % 8 == 0) {
                printf(" ");
            }
        }
        printf("\n");
        printf("  fp32 : %-30.20f\n", fp32_c);


        printf("\n");
        printf("  calc : ( %f / %f ) and x %d\n", fp32_a, fp32_b, iter);
        printf("  bits : ");
        fp32_c = 0.0f;
        fp32_c = fp32_a / fp32_b;
        fp32_c = fp32_c * (float)iter;
        for (int bit_index = 31; bit_index >= 0; bit_index--) {
            get_bit = 1 << bit_index;
            printf("%d", *(int*)(&fp32_c) & get_bit ? 1 : 0);
            if (bit_index % 8 == 0) {
                printf(" ");
            }
        }
        printf("\n");
        printf("  fp32 : %-30.20f\n", fp32_c);
        

        printf("\n");
        printf("  calc : ( %f / %f ) x %d\n", fp32_a, fp32_b, iter);
        printf("  bits : ");
        fp32_c = 0.0f;
        fp32_c = fp32_a / fp32_b * (float)iter;
        for (int bit_index = 31; bit_index >= 0; bit_index--) {
            get_bit = 1 << bit_index;
            printf("%d", *(int*)(&fp32_c) & get_bit ? 1 : 0);
            if (bit_index % 8 == 0) {
                printf(" ");
            }
        }
        printf("\n");
        printf("  fp32 : %-30.20f\n", fp32_c);
        

        printf("\n");
        printf("  calc : ( %f / %f ) iter %d\n", fp32_a, fp32_b, iter);
        printf("  bits : ");
        fp32_c = 0.0f;
        for (int idx = 0; idx < iter; idx++) {
            fp32_c += (fp32_a / fp32_b);
        }
        for (int bit_index = 31; bit_index >= 0; bit_index--) {
            get_bit = 1 << bit_index;
            printf("%d", *(int*)(&fp32_c) & get_bit ? 1 : 0);
            if (bit_index % 8 == 0) {
                printf(" ");
            }
        }
        printf("\n");
        printf("  fp32 : %-30.20f\n", fp32_c);

        printf("  ##################################################\n");

    }
    catch (std::exception& e) {
        printf("C++ Exception( std::exception ) : %s\n", e.what());
    }
    catch (...) {
        printf("C++ Exception( ... ) : Not std::exception\n");
    }

    return;

}

void doyouknow_class::func_round_unit_fp64(int iter, float fp32_a, float fp32_b) {
    try {

        printf("  %s()\n", ((std::string)__func__).c_str());

    }
    catch (std::exception& e) {
        printf("C++ Exception( std::exception ) : %s\n", e.what());
    }
    catch (...) {
        printf("C++ Exception( ... ) : Not std::exception\n");
    }

    return;

}

void doyouknow_class::func_epsilon_fp16(void) {
    try {

        printf("  %s()\n", ((std::string)__func__).c_str());

    }
    catch (std::exception& e) {
        printf("C++ Exception( std::exception ) : %s\n", e.what());
    }
    catch (...) {
        printf("C++ Exception( ... ) : Not std::exception\n");
    }

    return;

}

void doyouknow_class::func_epsilon_fp32(void) {
    try {
        
        printf("  %s()\n", ((std::string)__func__).c_str());

        constexpr float fp32_epsilon = std::numeric_limits<float>::epsilon();
            // constexpr variable is " initialize and never change variable "
        float fp32_log_epsilon = std::log(fp32_epsilon);

        printf("  fp32_epsilon         : %15.10f\n", fp32_epsilon);
        printf("  fp32_log_epsilon     : %15.10f\n", fp32_log_epsilon);

        float fp32_exponential = std::exp(1.0f);
        float fp32_log_exponential = std::log(fp32_exponential);

        printf("  fp32_exponential     : %15.10f\n", fp32_exponential);
        printf("  fp32_log_exponential : %15.10f\n", fp32_log_exponential);
        printf("  how to use fp32_epsilon ?\n");
        float fp32_zero = 0.0f;
        if (fp32_zero < fp32_epsilon) {
            printf("    fp32_zero                 : %15.10f\n", fp32_zero);
            printf("    std::log(fp32_zero)       : %15.10f\n", std::log(fp32_zero));
            fp32_zero = fp32_epsilon;
            printf("    fp32_epsilon to fp32_zero : %15.10f\n", fp32_zero);
            printf("    std::log(fp32_zero)       : %15.10f\n", std::log(fp32_zero));            
        }

    }
    catch (std::exception& e) {
        printf("C++ Exception( std::exception ) : %s\n", e.what());
    }
    catch (...) {
        printf("C++ Exception( ... ) : Not std::exception\n");
    }

    return;

}

void doyouknow_class::func_epsilon_fp64(void) {
    try {

        printf("  %s()\n", ((std::string)__func__).c_str());

    }
    catch (std::exception& e) {
        printf("C++ Exception( std::exception ) : %s\n", e.what());
    }
    catch (...) {
        printf("C++ Exception( ... ) : Not std::exception\n");
    }

    return;

}
