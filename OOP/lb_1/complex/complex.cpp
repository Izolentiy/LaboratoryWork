#include "complex.h"

double complex::get_argument(angle_t angle) const {
    switch (angle) {
    case radian:
        return this->arg;
    case degree:
        return this->arg * 180 / PI;
    }
    return 0;
}

double complex::get_radius() const {
    return this->rad;
}

double complex::get_real() const {
    return rad * std::cos(arg);
}

double complex::get_imag() const {
    return rad * std::sin(arg);
}

void complex::set_radius(double rad) {
    this->rad = rad;
}

void complex::set_argument(double arg) {
    this->arg = arg;
}

complex complex::alg(double re, double im) {
    double rad = std::sqrt(re * re + im * im);
    double arg;
    if (re == 0 && im == 0) {
        arg = 0;
    } else {
        arg = std::atan(im / re);
        if (re < 0) arg += PI;
    }
    return complex::exp(rad, arg, radian);
}

complex complex::exp(double rad, double arg, angle_t angle) {
    switch (angle) {
    case radian:
        return complex(rad, arg);
    case degree:
        return complex(rad, arg * PI / 180);
    }
    return complex(0, 0);
}

complex::complex(double rad, double arg) {
    this->rad = rad;
    this->arg = arg;
}

complex complex::operator+(const complex &other) {
    using std::sin, std::cos;
    double re = rad * cos(arg) + other.rad * cos(other.arg);
    double im = rad * sin(arg) + other.rad * sin(other.arg);
    return complex::alg(re, im);
}

complex complex::operator-(const complex &other) {
    using std::sin, std::cos;
    double re = rad * cos(arg) - other.rad * cos(other.arg);
    double im = rad * sin(arg) - other.rad * sin(other.arg);
    return complex::alg(re, im);
}

complex complex::operator*(const complex &other) {
    return complex::exp(this->rad * other.rad, this->arg + other.arg, radian);
}

complex complex::operator/(const complex &other) {
    return complex::exp(this->rad / other.rad, this->arg - other.arg, radian);
}

complex complex::operator^(int pow) {
    double rad = std::pow(this->rad, pow);
    double arg = this->arg * pow;
    return complex::exp(rad, arg, radian);
}

complex complex::operator-() {
    using std::sin, std::cos;
    double re = rad * cos(this->arg);
    double im = rad * sin(this->arg);
    return complex::alg(-re, -im);
}

void complex::operator+=(const complex &other) {
    using std::sin, std::cos;
    double re = rad * cos(arg) + other.rad * cos(other.arg);
    double im = rad * sin(arg) + other.rad * sin(other.arg);
    this->rad = std::sqrt(re * re + im * im);
    if (re == 0 && im == 0) {
        this->arg = 0;
    } else {
        this->arg = std::atan(im / re);
        if (re < 0) arg += PI;
    }
}

void complex::operator-=(const complex &other) {
    using std::sin, std::cos;
    double re = rad * cos(arg) - other.rad * cos(other.arg);
    double im = rad * sin(arg) - other.rad * sin(other.arg);
    this->rad = std::sqrt(re * re + im * im);
    if (re == 0 && im == 0) {
        this->arg = 0;
    } else {
        this->arg = std::atan(im / re);
        if (re < 0) arg += PI;
    }
}

void complex::operator*=(const complex &other) {
    this->rad *= other.rad;
    this->arg += other.arg;
}

void complex::operator/=(const complex &other) {
    this->rad /= other.rad;
    this->arg -= other.arg;
}

std::ostream &operator<<(std::ostream &out, const complex &num) {
    if (num.get_argument() < 0) {
        return out << num.get_radius() << "e^(-j" << -num.get_argument() << ')';
    } else {
        return out << num.get_radius() << "e^(j" << num.get_argument() << ')';
    }
}

complex::complex(double num) {
    this->rad = num;
    this->arg = 0;
}

complex &complex::operator=(double num) {
    this->rad = num;
    this->arg = 0;
    return *this;
}
