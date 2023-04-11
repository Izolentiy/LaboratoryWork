#pragma once
#include <stdint.h>

namespace my {
    class point;
    class vector;
    template <typename T> class matrix;
}

class my::vector {
private:
    float x; float y;
    float l;

public:
    vector(const float &x, const float &y);

    float get_x() const;
    float get_y() const;
    float get_l() const;

    void set(const float &x, const float &y);
    void print_coordinates() const;
    vector get_ort() const;
};

class my::point {
private:
    float x; float y;

public:
    point(const float& x, const float& y);

    float get_x() const;
    float get_y() const;
    
    void set(const float &x, const float &y);
    void print_coordinates();
    void move(const my::vector& v);
};

template<typename T>
class my::matrix {
private:
    T *m;
    int r; int c;

public:
    matrix(uint16_t r_n, uint16_t c_n);

    void print() const;
    void print_elements_between(my::point s, my::point e) const;
    void fill();
    T& operator () (uint16_t r_n, uint16_t c_n);

    ~matrix();
};

#include "matrix.hpp"