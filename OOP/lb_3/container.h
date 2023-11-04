#pragma once
#include <stdint.h>
#include <stdexcept>

namespace my {
    template <class T>
    class container;
}

template <class T>
class my::container {
  public:
    size_t get_size() const;
    virtual void insert(const T &obj, size_t index) = 0;
    virtual void push_back(const T &obj) = 0;
    virtual void remove(size_t index) = 0;
    virtual T &operator[](size_t index) = 0;
    virtual T operator[](size_t index) const = 0;

  protected:
    size_t size = 0;

    void check_put_range(size_t index) const;
    void check_get_range(size_t index) const;
};

#include "container.hpp"