#pragma once
#include <stdint.h>
#include "list.h"

namespace my
{
    template <class V> class dictionary;
}

/**
 * Что должен уметь словарь:
 * - получение элемента по ключу
 * - добавление элемента с заданным ключом
 * - удаление элемента по ключу
 */
template <class V>
class my::dictionary {
public:
    dictionary();
    ~dictionary();
    V &get(const char *key);
    void insert(const char *key, const V &obj);
    void remove(const char *key);

private:
    my::list<V> data;
    size_t size = 0;
};