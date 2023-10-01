#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>

bool is_digit(char);
bool is_delim(char);
double to_double(std::string);
std::vector<double> to_vector(std::ifstream &);