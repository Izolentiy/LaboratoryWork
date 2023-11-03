#pragma once
#include <stdint.h>

namespace my {
    template <class T>
    class container;
}

template <class T>
class my::container {
  public:
    // pure virtual functions
    virtual size_t get_size() const = 0;
    virtual void insert(const T &obj, size_t index) = 0;
    virtual void push_back(const T &obj) = 0;
    virtual void remove(size_t index) = 0;
    virtual T &operator[](size_t index) = 0;

  protected:
    size_t size = 0;
};