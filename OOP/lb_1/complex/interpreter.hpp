#pragma once
#include "complex.h"
#include <iostream>

class cinterpreter
{
public:
    cinterpreter(std::istream &in) : in(&in) {}
    void print_alg(const complex &num);
    void print_exp(const complex &num);
    int peek();
    double real();
    complex number();
    complex factor();
    complex term();
    complex expression();

private:
    std::istream *in;
    std::ostream *out;
};

void cinterpreter::print_alg(const complex &num) {
    double im = num.get_imag();
    if (im < 0) {
        std::cout << num.get_real() << "-j" << -im << "\n";
    } else {
        std::cout << num.get_real() << "+j" << im << "\n";
    }
}

void cinterpreter::print_exp(const complex &num) {
    double arg = num.get_argument();
    if (arg < 0) {
        std::cout << num.get_radius() << " e^(-j" << -arg << ")\n";
    } else {
        std::cout << num.get_radius() << " e^(j" << arg << ")\n";
    }
}

int cinterpreter::peek() {
    while ((*in).peek() == ' ') {
        (*in).get(); // skip whitespace
    }
    return (*in).peek();
}

/**
 * real number
 */
double cinterpreter::real() {
    double integer = (*in).get() - '0';
    while (peek() >= '0' && peek() <= '9') {
        integer = 10 * integer + (*in).get() - '0';
    }
    if (peek() == '.' || peek() == ',') {
        (*in).get();
        double decimal = 0;
        int i = 0;
        while (peek() >= '0' && peek() <= '9') {
            decimal += std::pow(0.1, ++i) * ((*in).get() - '0');
        }
        return integer + decimal;
    }
    return integer;
}

/**
 * complex number
 */
complex cinterpreter::number() {
    if (peek() == 'j' || peek() == 'i') {
        (*in).get(); // i
        if (peek() == '(') {
            complex i = complex::alg(0, 1);
            (*in).get(); // '('
            complex expr = expression();
            (*in).get(); // ')'
            return i * expr;
        } else if (peek() >= '0' && peek() <= '9'){
            double im = real();
            return complex::alg(0, im);
        }
        return complex::alg(0, 1);
    }
    double val = 1; // radius OR real
    if (peek() >= '0' && peek() <= '9')
        val = real();
    if (peek() == 'e') {
        char s[3];
        (*in).get(s, 3); // e^
        if (peek() == '(') {
            (*in).get(); // '('
            complex expr = expression();
            (*in).get(); // ')'
            return complex::exp(val, expr.get_imag());
        }
        (*in).get(); // j
        double arg = real();
        return complex::exp(val, arg);
    } else if (peek() == 'j' || peek() == 'i') {
        (*in).get(); // j
        return complex::alg(0, val);
    }
    return complex::alg(val, 0);
}

/**
 * complex factor
 */
complex cinterpreter::factor() {
    int ch = peek();
    if (ch == 'j' || ch == 'i' || ch == 'e') {
        return number();
    } else if (ch >= '0' && ch <= '9') {
        return number();
    } else if (ch == '(') {
        (*in).get(); // '('
        complex result = expression();
        (*in).get(); // ')'
        if (peek() == 'j' || peek() == 'i') {
            (*in).get(); // 'j'
            result *= complex::alg(0, 1);
        }
        return result;
    } else if (ch == '-') {
        (*in).get(); // '-'
        return -factor();
    }
    return complex::exp(0, 0); // uninterpretable symbol
}

/**
 * complex term
 */
complex cinterpreter::term() {
    complex result = factor();
    while (peek() == '*' || peek() == '/')
        if ((*in).get() == '*')
            result *= factor();
        else
            result /= factor();
    return result;
}

/**
 * complex expression
 */
complex cinterpreter::expression() {
    complex result = term();
    while (peek() == '+' || peek() == '-')
        if ((*in).get() == '+')
            result += term();
        else
            result -= term();
    return result;
}