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
    dl_list(const dl_list &other);
    void operator=(const dl_list &other);
    void insert(const T &obj, size_t index) override;
    void push_back(const T &obj) override;
    void remove(size_t index) override;
    T &operator[](size_t index) override;
    T operator[](size_t index) const override;
    ~dl_list();

  private:
    node *head = nullptr;
    node *tail = nullptr;

    void clear();
    void append(const dl_list &other);
    node *move_to(size_t index) const;
};

#include "dl_list.hpp"
