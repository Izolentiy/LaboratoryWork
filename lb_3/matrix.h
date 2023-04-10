#pragma once
#include <stdint.h>

namespace my {
    class point;
    class vector;
    template <typename T> class matrix;
}

class my::vector {
public:
    float x; float y;
    float l;

    vector(const float& x, const float& y);

    void set(float x, float y);
    void print_coordinates() const;
    vector get_ort() const;
};

class my::point {
public:
    float x; float y;
    
    point(const float& x, const float& y);
    
    void print_coordinates();
    void move(const my::vector& v);
};

template<typename T> class my::matrix {
private:
    T *m;
    int r; int c;

public:
    matrix(uint16_t r_n, uint16_t c_n);

    void print() const;
    void fill();
    T& operator () (uint16_t r_n, uint16_t c_n);

    ~matrix();
};

#include "matrix.hpp"