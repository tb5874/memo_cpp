#include <doyouknow_wav.hpp>
#include <libstandard_wav.hpp>

void* doyouknow_get(void) {

    void* get_ptr = nullptr;

    try {

        get_ptr = new doyouknow_class;

    }
    catch (std::exception& e) {
        printf("Func : %s() : Exception : %s\n", ((std::string)__func__).c_str(), e.what());
    }
    catch (...) {
        printf("Func : %s() : Exception : unknown exception\n", ((std::string)__func__).c_str());
    }

    return get_ptr;

}

void doyouknow_func01(void* get_ptr) {
    try {

        ((doyouknow_class*)get_ptr)->func_01();

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

    }
    catch (std::exception& e) {
        printf("Func : %s() : Exception : %s\n", ((std::string)__func__).c_str(), e.what());
    }
    catch (...) {
        printf("Func : %s() : Exception : unknown exception\n", ((std::string)__func__).c_str());
    }

    return;

}
