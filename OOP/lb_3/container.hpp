#pragma once

template <class T>
inline size_t my::container<T>::get_size() const {
    return this->size;
}

template <class T>
void my::container<T>::check_put_range(size_t index) const {
    if (!(index >= 0 && index <= this->size))
        throw std::out_of_range("Out of range");
}

template <class T>
void my::container<T>::check_get_range(size_t index) const {
    if (!(index >= 0 && index < this->size))
        throw std::out_of_range("Out of range");
}