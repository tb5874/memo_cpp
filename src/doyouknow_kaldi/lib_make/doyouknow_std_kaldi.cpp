#include <doyouknow_kaldi.hpp>

#include <doyouknow_std_kaldi.hpp>

void* doyouknow_get(void) {
    try {

        void* get_ptr = new doyouknow_class;

        return get_ptr;

    }
    catch (std::exception& e) {
        printf("Func : %s() : Exception : %s\n", ((std::string)__func__).c_str(), e.what());
    }
    catch (...) {
        printf("Func : %s() : Exception : unknown exception\n", ((std::string)__func__).c_str());
    }

    return nullptr;

}

void doyouknow_func01(void* get_ptr) {
    try {

        ((doyouknow_class*)get_ptr)->func_01();

        return;

    }
    catch (std::exception& e) {
        printf("Func : %s() : Exception : %s\n", ((std::string)__func__).c_str(), e.what());
    }
    catch (...) {
        printf("Func : %s() : Exception : unknown exception\n", ((std::string)__func__).c_str());
    }

    return;

}

void doyouknow_func02(void* get_ptr) {
    try {

        ((doyouknow_class*)get_ptr)->func_02();

        return;

    }
    catch (std::exception& e) {
        printf("Func : %s() : Exception : %s\n", ((std::string)__func__).c_str(), e.what());
    }
    catch (...) {
        printf("Func : %s() : Exception : unknown exception\n", ((std::string)__func__).c_str());
    }

    return;

}

void doyouknow_func03(void* get_ptr) {
    try {

        ((doyouknow_class*)get_ptr)->func_03();

        return;

    }
    catch (std::exception& e) {
        printf("Func : %s() : Exception : %s\n", ((std::string)__func__).c_str(), e.what());
    }
    catch (...) {
        printf("Func : %s() : Exception : unknown exception\n", ((std::string)__func__).c_str());
    }

    return;

}
