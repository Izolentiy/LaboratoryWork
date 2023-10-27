#pragma once
#include <stdexcept>
#include <stdint.h>

/**
 * Что должен уметь словарь:
 * - получение элемента по ключу
 * - добавление элемента с заданным ключом
 * - удаление элемента по ключу
 **/

namespace my {
    template <class K, class V>
    class linked_map;
}

template <class K, class V>
class my::linked_map {
    class node {
      public:
        node *next;
        node *prev;

        node(K key, const V &data, node *next = nullptr, node *prev = nullptr);
        K get_key() const;
        V &get_val();

      private:
        K key;
        V val;
    };

  public:
    linked_map() = default;
    ~linked_map();

    V &get(const K &key);
    void insert(const K &key, const V &obj);
    void remove(const K &key);

    K get_key(size_t index);
    size_t get_size() const;

  private:
    node *head = nullptr;
    node *tail = nullptr;
    size_t size = 0;
    node *find(const K &key);
    node *move_to(size_t index);
    void insert(size_t index, const K &key, const V &obj);
    void check_range(size_t index);
};

#include "map.hpp"