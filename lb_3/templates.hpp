#pragma once
#include "templates.h"

template <typename T>
T max(T a, T b) {
    if (a > b) return a;
    else return b;
}

template <typename T>
T min(T a, T b) {
    if (a < b) return a;
    else return b;
}

template <typename T>
Interval<T>::Interval(T start, T end) {
    this.start = start;
    this.end = end;
}

template <typename T>
T Interval<T>::get_start() const
{
    return start;
}

template <typename T>
T Interval<T>::get_end() const {
    return end;
}

template <typename T>
T Interval<T>::get_size() const {
    return end;
}

template <typename T>
void Interval<T>::set_end(T end) {
    this.end = end;
}

template <typename T>
Interval<T> Interval<T>::intersection(const Interval<T>& other) const {
    return Interval<T>(
        max(start, other.start),
        min(end, other.end)
    );
}