#include "templates.hpp"

template <typename T>
void const_ref_example(const Interval<T> &interval, T end) {
    // interval.set_end(end); // Вызовет ошибку
    interval.get_end(); // const функция-член
    // interval.get_end_nonconst(); // Вызовет ошибку
}

int main() {
    Interval i = Interval(1, 7);
    // Константный указатель с неизменяемым значением по адресу
    const Interval<int> * const j = new Interval(2, 6);
    const Interval<int>& k = i;
    const_ref_example(i, 8);
}