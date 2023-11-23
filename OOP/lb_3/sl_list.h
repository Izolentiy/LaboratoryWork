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
    sl_list(const sl_list &other);
    void operator=(const sl_list &other);
    void insert(const T &obj, size_t index);
    void push_back(const T &obj);
    void remove(size_t index);
    T &operator[](size_t index);
    T operator[](size_t index) const;
    ~sl_list();

  private:
    node *head = nullptr;

    void clear();
    void append(const sl_list &other);
    node *move_to(size_t index) const;
};

#include "sl_list.hpp"