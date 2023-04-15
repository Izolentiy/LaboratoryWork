#include "c_string.h"
#include <iostream>

#define STR_MAX_LEN 32

void c_string_test() {
    // размер сообщения максимум 19 символов, включая '\n'. Не считая '\0'
    my::string str(STR_MAX_LEN);
    uint8_t val = 22;
    uint8_t r = 255, g = 255, b = 255;

    // Построение сообщения
    str + val + " : " + r + ' ' + g + ' ' + b + '\n';
    char* msg = str.as_cstring();

    std::cout << msg;

    str.clear();
    str + ":)";
    std::cout << str.as_cstring() << std::endl;

    int signed_val = -1245;
    r = 0; g = 0; b = 0;

    str.clear();
    str + signed_val + " : " + r + ' ' + g + ' ' + b;
    std::cout << str.as_cstring();
}

void (*func_arr[]) (int) = { f1, f2, f3 };

typedef void (*func_t) (int);
func_t func_arr_2[] = { f1, f2, f3 };

void f1(int n) {}
void f2(int n) {}
void f3(int n) {}

void array_of_functions() {
    (*func_arr[0])();
}

int main() {
    c_string_test();
}