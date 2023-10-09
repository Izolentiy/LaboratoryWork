#pragma once
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "str_helper.h"

class matrix
{
    class row
    {
        friend matrix;

    public:
        row(std::vector<double> &d, int &cc);
        double &operator[](int col);
        ~row();

    private:
        std::vector<double> &data; // data of parent matrix
        int col_count;             // column count of parent matrix
        int row_num;               // row number
    };
    
    friend std::ostream &operator<<(std::ostream &out, matrix &m);
    friend void operator<<(const char *output_filename, matrix &m);

public:
    matrix();
    matrix(int rows, int cols);
    matrix(std::vector<double> elems, int rows, int cols);
    matrix(const std::string &input_filename);
    matrix(const matrix &matrix);

    double determinant();
    matrix transposition();
    matrix get_inverse();
    void export_to_scv(const std::string &filename);

    matrix operator*(matrix &other);
    matrix operator*(matrix *other);
    matrix operator*(double num);
    matrix operator^(int pow);
    void operator*=(double num);
    void operator*=(matrix &other);
    void operator*=(matrix *other);
    void operator=(const matrix &other);
    row &operator[](int row);

    int get_cols();
    int get_rows();
    int get_print_precision();
    int get_print_width();
    void set_print_precision(int prec);
    void set_print_width(int width);

    ~matrix();

private:
    int rows = 0;                  // rows
    int cols = 0;                  // columns
    int print_prec = 2;            // print precision
    int print_width = 6;           // print width
    std::string print_delim = " "; // print delimeter
    std::vector<double> elems;     // elements
    row rp = row(elems, cols);     // row proxy

    double get_alg_com(int row, int col); // algebraic complement
    matrix &get_minor(int row, int col, std::vector<matrix *>);
    double &get(int row, int col); // index starts with 0
    void copy_from(const matrix &other);
};