#include <iostream>
#include <fstream>
#include <vector>

int main() {
    std::ifstream fin("input\\matrix-A.txt");
    int cols = 0, rows = 0;
    do {
        char ch = fin.peek();
        if (ch == '\n' || ch == EOF) {
            ++rows;
        }
    } while (fin.get() != EOF);

    double x;
    std::vector<double> vec;
    fin.clear();              // clear flags
    fin.seekg(std::ios::beg); // set read position to start
    while (fin >> x) {
        vec.push_back(x);
    }

    cols = vec.size() / rows;
    if (!fin.eof() && fin.fail() || cols == 0) {
        // error occured here: "fin >> x"
        // or empty file
        // invalid input
    }
    if (rows * cols != vec.size()) {
        // some row contains extra column
        // or miss column
        // invalid input
    }
    fin.close();
}