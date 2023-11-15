#pragma once
#include "container.h"

namespace my {
    template <class T>
    class dl_list;
};

template <class T>
class my::dl_list : public my::container<T> {
    class node {
      public:
        node *next;
        node *prev;
        T val;

        node(const T &val, node *next = nullptr, node *prev = nullptr);
    };

  public:
    dl_list() = default;
    void insert(const T &obj, size_t index);
    void push_back(const T &obj);
    void remove(size_t index);
    T &operator[](size_t index);
    T operator[](size_t index) const;
    ~dl_list();

  private:
    node *head = nullptr;
    node *tail = nullptr;

    node *move_to(size_t index) const;
};

#include "dl_list.hpp"