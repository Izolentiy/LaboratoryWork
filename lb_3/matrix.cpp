#include "matrix.h"
#include <iostream>
#include <cmath>

my::vector::vector(const float& x, const float& y) {
    this -> x = x;
    this -> y = y;
    l = sqrt(x*x + y*y);
};

void my::vector::set(float x, float y) {
    this -> x = x;
    this -> y = y;
    l = sqrt(x*x + y*y);
}

void my::vector::print_coordinates() const {
    std::cout << "vector = {" << x << ", " << y << "}" << std::endl;
}

my::vector my::vector::get_ort() const {
    return my::vector(x/l, y/l);
}

my::point::point(const float &x, const float &y) {
    this -> x = x;
    this -> y = y;
}

void my::point::print_coordinates() {
    std::cout << "(" << x << ", " << y << ")" << std::endl;  
}

void my::point::move(const my::vector& v) {
    x += v.x;
    y += v.y;
}
