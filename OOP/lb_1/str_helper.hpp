#pragma once
#include <iostream>

template <class T>
void str_helper::print_diff(const char *label, T expected, T result)
{
    std::cout << "  " << label << '\n'
              << "  expected: " << expected << '\n'
              << "    result: " << result << "\n\n";
}