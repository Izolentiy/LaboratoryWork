#include "matrix.h"
#include <iostream>
#include <cmath>

float my::vector::get_x() const { return x; }

float my::vector::get_y() const { return y; }

float my::vector::get_l() const { return l; }

my::vector::vector(const float &x, const float &y) { set(x, y); }

void my::vector::set(const float& x, const float& y) {
    this -> x = x;
    this -> y = y;
    l = sqrt(x*x + y*y);
}

void my::vector::print_coordinates() const {
    std::cout << "vector = {" << get_x << ", " << get_y << "}" << std::endl;
}

my::vector my::vector::get_ort() const {
    return my::vector(x/l, y/l);
}

float my::point::get_x() const { return x; }

float my::point::get_y() const { return y; }

my::point::point(const float &x, const float &y) { set(x, y); }

void my::point::set(const float &x, const float &y) {
    this -> x = x;
    this -> y = y;
}

void my::point::print_coordinates()
{
    std::cout << "(" << x << ", " << y << ")" << std::endl;
}

void my::point::move(const my::vector& v) {
    x += v.get_x();
    y += v.get_y();
}
