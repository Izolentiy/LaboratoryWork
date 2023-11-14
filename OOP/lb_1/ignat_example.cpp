#include <iostream>
#include <fstream>
#include <vector>

int main() {
    std::ifstream fin("input\\matrix-A.txt");
    bool is_delim_or_digit;   // is digit / delimeter
    bool num_started = false; // number started
    int cols = 0;             // columns
    do {
        char ch = fin.peek();
        is_delim_or_digit = ch == '.' || ('0' <= ch  && ch <= '9');
        if (!num_started && is_delim_or_digit) {
            num_started = true;
        }
        if (num_started && !is_delim_or_digit) {
            num_started = false;
            ++cols;
        }
    } while (fin.get() != '\n' || fin.eof());

    double x;
    std::vector<double> vec;
    fin.seekg(std::ios::beg); // set read position to start
    while (fin >> x) {
        vec.push_back(x);
    }

    if (fin.fail()) {
        // error occured here: "fin >> x"
        // invalid input
    }
    int rows = vec.size() / cols;
    if (rows * cols != vec.size()) {
        // some row contains extra column
        // or miss column
        // invalid input
    }
}