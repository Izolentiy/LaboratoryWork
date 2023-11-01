#pragma once
#include <stdint.h>

namespace my {
    template <class T>
    class container;
}

template <class T>
class my::container {
  public:
    // pure virtual function
    virtual size_t get_size() const = 0;
    virtual void insert(T &obj) = 0;
    virtual T &operator[](size_t index) = 0;

  protected:
    size_t size;
};