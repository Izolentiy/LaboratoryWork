#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>

// for printing double num
const double ZERO_EPSILON = 1E-14;
const double REL_EPSILON = 1E-7;

// error messages
const char * const UNABLE_TO_OPEN_FILE = "Unable to open file";
const char * const INVALID_INPUT = "Invalid input";
const char * const NON_SQUARE_MATRIX = "Non square matrix";
const char * const DEGENERATE_MATRIX = "Degenerate matrix";
const char * const MULTIPLICATION_IS_NOT_APPLICABLE = "Multiplication is not applicable";
const char * const INVALID_DEGREEE_INDICATOR = "Invalid degree indicator";
const char * const OUT_OF_RANGE = "Out of range";

// test statuses
const char * const FAILURE = "FAILURE";
const char * const PASS = "PASS";

namespace str_helper
{
    bool is_digit(char ch);
    bool is_delim(char ch);
    bool is_number_char(char ch);
    size_t count(std::string &str, char ch);
    bool compare(const char *s1, const char *s2);

    template <class T>
    void print_diff(const char *label, T expected, T result);
}

#include "str_helper.hpp"