// #pragma once
#include <stdint.h>

namespace my
{
    template <class T> class list;
}

template <class T>
class my::list
{
    class item
    {
    public:
        item(T obj, item *next = nullptr);
        T &get_obj();
        T get_obj() const;

    private:
        item *next = nullptr;
        T obj;
    };

public:
    list();
    ~list();
    void push_back(const T &obj);
    void insert(size_t index, const T &obj);
    void remove(size_t index);

    T &operator[](size_t index);
    T operator[](size_t index) const;

private:
    item *head = nullptr;
    size_t size;

    item *move_to(size_t index);
    item *find(const T &obj);
    void check_range(size_t index);
};

// #pragma once
// #include "list.h"

template <class T>
inline my::list<T>::list()
{
}

template <class T>
inline my::list<T>::~list()
{
}

// list items = { "s", "r", "p", "q" };
//                 ^              ^
// size: 4         0              3
template <class T>
inline void my::list<T>::push_back(const T &obj)
{
    insert(size, obj);
}

template <class T>
inline void my::list<T>::insert(size_t index, const T &obj)
{
    if (index == 0)
    {
        head = new item(obj, head);
    }
    else
    {
        item *prev = move_to(index - 1);
        item *to_insert = new item(obj, prev->next);
        prev->next = to_insert;
    }
    ++size;
}

template <class T>
inline void my::list<T>::remove(size_t index)
{
    if (index == 0)
    {
        delete head;
        head = nullptr;
    }
    else
    {
        item *prev = move_to(index - 1);
        item *to_del = prev->next;
        prev->next = to_del->next;
        delete to_del;
    }
    if (size > 0)
        --size;
}

template <class T>
inline T &my::list<T>::operator[](size_t index)
{
    check_range(index);
    return move_to(index)->get_obj();
}

template <class T>
inline T my::list<T>::operator[](size_t index) const
{
    check_range(index);
    const item *temp = move_to(index);
    return temp->get_obj();
}

template <class T>
inline void my::list<T>::check_range(size_t index)
{
    bool is_correct = (index >= 0) && (index < size);
    if (!is_correct)
        throw std::out_of_range("Out of range");
}

template <class T>
inline my::list<T>::item *my::list<T>::move_to(size_t index)
{
    check_range(index);

    item *temp = head;
    while (index-- > 0)
    {
        temp = temp->next;
    }
    return temp;
}

template <class T>
inline my::list<T>::item *my::list<T>::find(const T &obj)
{
    return nullptr;
}

template <class T>
inline my::list<T>::item::item(T obj, item *next)
    : obj(obj), next(next)
{

}

template <class T>
inline T &my::list<T>::item::get_obj()
{
    return obj;
}

template <class T>
inline T my::list<T>::item::get_obj() const
{
    return obj;
}


// #include "list.hpp"
