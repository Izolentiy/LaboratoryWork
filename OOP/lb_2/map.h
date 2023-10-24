#pragma once
#include "string.h"
#include <stdexcept>
#include <stdint.h>

/**
 * Что должен уметь словарь:
 * - получение элемента по ключу
 * - добавление элемента с заданным ключом
 * - удаление элемента по ключу
 **/

namespace my {
    template <class V>
    class linked_map;
}

template <class V>
class my::linked_map {
    class node {
      public:
        node(my::string key, const V &data, node *next = nullptr, node *prev = nullptr);
        my::string get_key() const;
        V &get_val();

        node *next;
        node *prev;

      private:
        my::string key;
        V val;
    };

  public:
    linked_map() = default;
    ~linked_map();

    V &get(const my::string &key);
    void insert(const my::string &key, const V &obj);
    void remove(const my::string &key);

  private:
    node *head = nullptr;
    node *tail = nullptr;
    size_t size = 0;
    node *find(const my::string &key);
    node *move_to(size_t index);
    void insert(size_t index, const my::string &key, const V &obj);
    void check_range(size_t index);
};

#include "map.hpp"