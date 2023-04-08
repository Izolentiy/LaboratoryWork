#include "templates.h"
#include <iostream>

int global_var;

template <typename T>
void const_ref_example(const Interval<T> &interval, T end) {
    // interval.set_end(end); // Вызовет ошибку
    interval.get_end(); // const функция-член
}

int get_elem(int *a, int c, int r_i, int c_i) {
    return a[r_i*c + c_i];
}

void two_dim_array() {
    int r = 3, c = 3;
    int *a = new int[r*c];
    
    for (int i = 0; i < r*c; ++i) {
        a[i] = i+1;
        std::cout << a[i] << ' ';
        if (i % c == 2) std::cout << '\n'; 
    }

    std::cout << '\n';
    std::cout << get_elem(a, c, 0, 1) << '\n';
    std::cout << get_elem(a, c, 1, 2) << '\n';
    std::cout << get_elem(a, c, 2, 1) << '\n';

    delete[] a;
}

int main() {
    // Interval i = Interval(1, 7);
    // Константный указатель с неизменяемым значением по адресу
    // const Interval<int> * const j = new Interval(2, 6);
    // const Interval<int>& k = i;
    // const_ref_example(i, 8);
    
    two_dim_array();
}