#pragma once
#include <iostream>

template<typename T>
my::matrix<T>::matrix(uint16_t r, uint16_t c) {
    this -> r = r;
    this -> c = c;
    m = new T[r * c];
}

template<typename T>
T& my::matrix<T>::operator () (uint16_t r_n, uint16_t c_n) {
    return m[r_n*c + c_n];
}

template<typename T>
void my::matrix<T>::fill() {
    for (int i = 0; i < r*c; ++i) {
        m[i] = i+1;
    }
}

template<typename T>
void my::matrix<T>::print() const {
    for (int i = 0; i < r*c; ++i) {
        std::cout << m[i] << ' ';
        if (i % c == c-1) std::cout << '\n'; 
    }
}

template <typename T>
inline void my::matrix<T>::print_elements_between(my::point s, my::point e) const {
    my::vector v(e.x - s.x, e.y - s.y);
    my::vector v_0 = v.get_ort();

    int pr_r, pr_c;
    for (int i = 0; i < v.l; ++i) {
        int r = s.y += v_0.y;
        int c = s.x += v_0.x;
        if (pr_r != r || pr_c != c) {
            std::cout << m[r][c] << ' ';
        }
        pr_r = r; pr_c = c;
    }
    std::cout << std::endl;
}

template<typename T>
my::matrix<T>::~matrix() {
    delete[] m;
}