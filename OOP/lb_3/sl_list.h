#pragma once
#include "container.h"

namespace my {
    template <class T>
    class sl_list;
};

template <class T>
class my::sl_list : public my::container<T> {
    class node {
      public:
        node *next;
        T val;

        node(const T &val, node *next = nullptr);
    };

  public:
    sl_list() = default;
    void insert(const T &obj, size_t index);
    void push_back(const T &obj);
    void remove(size_t index);
    T &operator[](size_t index);
    T operator[](size_t index) const;
    ~sl_list();

  private:
    node *head = nullptr;

    node *move_to(size_t index) const;
};

#include "sl_list.hpp"