#pragma once
#include <math.h>
#include <ostream>

#define PI 3.14159265358979323846

class complex {
  public:
    enum angle_t {
        radian,
        degree
    };
    static complex alg(double re, double im);
    static complex exp(double rad, double arg, angle_t angle = degree);
    complex() = default;
    complex(double real);
    complex &operator=(double real);
    void operator+=(const complex &other);
    void operator-=(const complex &other);
    void operator*=(const complex &other);
    void operator/=(const complex &other);
    complex operator+(const complex &other);
    complex operator-(const complex &other);
    complex operator*(const complex &other);
    complex operator/(const complex &other);
    complex operator^(int pow);
    complex operator-(); // unary minus

    double get_argument(angle_t ang = degree) const;
    double get_radius() const;
    double get_real() const;
    double get_imag() const;

    void set_radius(double rad);
    void set_argument(double arg);
    
  private:
    double rad;
    double arg; // in radians
    complex(double rad, double arg);
};

std::ostream &operator<<(std::ostream &out, const complex &num);


