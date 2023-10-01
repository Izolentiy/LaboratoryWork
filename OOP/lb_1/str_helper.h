#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>

namespace str_helper
{
    bool is_digit(char ch);
    bool is_delim(char ch);
    size_t validate(std::string str);
    double to_double(std::string str);
    void add_elements(std::vector<double> &dest, std::string &str);
    std::vector<double> to_vector(std::ifstream &fin);
}
