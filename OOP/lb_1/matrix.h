#pragma once
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "complex.h"
#include "interpreter.hpp"

template <class T>
class matrix;

template <class P>
std::ostream &operator<<(std::ostream &out, const matrix<P> &m);
template <class P>
void operator<<(const char *output_filename, const matrix<P> &m);

template <class T>
class matrix
{
    class row
    {
        friend matrix;

    public:
        row(std::vector<T> &d, int &cc);
        T &operator[](int col);
        ~row();

    private:
        std::vector<T> &data; // data of parent matrix
        int &col_count;            // column count of parent matrix
        int row_num;               // row number
        void check_range(int col);
    };
    
    friend std::ostream &operator<< <T>(std::ostream &out, const matrix<T> &m);
    friend void operator<< <T>(const char *output_filename, const matrix<T> &m);

public:
    matrix() = default;
    matrix(int rows, int cols);
    matrix(std::vector<T> elems, int rows, int cols);
    matrix(const std::string &input_filename);
    matrix(const matrix &matrix);

    T determinant();
    matrix transposed();
    matrix inversed();
    void export_to_csv(const std::string &filename);

    matrix operator^(int pow);
    matrix operator*(matrix *other);
    matrix operator*(const matrix &other);
    matrix operator*(double num);
    void operator*=(const matrix &other);
    void operator*=(double num);
    matrix &operator=(const matrix &other);
    row &operator[](int row);

    int get_cols() const;
    int get_rows() const;
    int get_print_precision();
    int get_print_width();
    void set_print_delimeter(const std::string &delim);
    void set_print_precision(int prec);
    void set_print_width(int width);

    ~matrix();

private:
    int rows = 0;                  // rows
    int cols = 0;                  // columns
    int print_prec = 2;            // print precision
    int print_width = 6;           // print width
    std::string print_delim = " "; // print delimeter
    std::vector<T> elems;          // elements
    row proxy = row(elems, cols);  // row proxy

    T get_alg_com(int row, int col); // algebraic complement
    T get_minor(int row, int col);
    T &get(int row, int col); // index starts with 0
    T get(int row, int col) const;
    void check_range(int row);
};

#include "matrix.hpp"