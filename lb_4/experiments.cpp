#include "c_string.hpp"
#include <iostream>

int main() {
    // размер сообщения максимум 18 символов не считая '\0'
    my::string str(18);
    uint8_t val = 240;
    uint8_t r = 0, g = 96, b = 175;

    // Построение сообщения
    str + val + " : " + r + ' ' + g + ' ' + b + '\n';
    char* msg = str.as_cstring();

    std::cout << msg;
}