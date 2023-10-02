#pragma once
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "str_helper.h"

/**
 * matrix m;
 * m[n]      // returns row with number n
 * m[r][c]   // returns element
 */
class row
{
public:
    row(std::vector<double> &d, int &cc);
    double &operator[](int col);
    void set(int row_num);
    ~row();

private:
    std::vector<double> &data; // data of parent matrix
    int col_count;             // column count of parent matrix
    int row_num;               // row number
};

class matrix
{
public:
    matrix(int rows, int cols);
    matrix(std::vector<double> elems, int rows, int cols);
    matrix(std::ifstream &fin);

    void print_elements();
    double determinant();
    double get_(int row, int col); // index starts with 1
    double get(int row, int col);  // index starts with 0

    int get_cols();
    int get_rows();
    int get_precision();
    int get_print_width();
    void set_print_precision(int prec);
    void set_print_width(int width);

    matrix *transposition();
    matrix *get_inverse();

    matrix *operator*(matrix &other);
    matrix *operator*(matrix *other);
    matrix *operator*(double num);
    void operator*=(double num);
    row &operator[](int row);

    ~matrix();

private:
    int rows;                  // rows
    int cols;                  // columns
    int print_prec = 2;        // print precision
    int print_width = 6;       // print width
    std::vector<double> elems; // elements
    row rp = row(elems, cols); // row proxy

    double get_alg_com(int row, int col); // algebraic complement
    matrix &get_minor(int row, int col, std::vector<matrix *>);
};