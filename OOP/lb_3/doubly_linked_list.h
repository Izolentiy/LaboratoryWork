#pragma once
#include "container.h"

namespace my {
    template <class T>
    class doubly_linked_list;
};

template <class T>
class my::doubly_linked_list : public my::container {
  public:
    size_t get_size() const;
    void insert(T &obj);
    T &operator[](size_t index);
};

#include "doubly_linked_list.hpp"