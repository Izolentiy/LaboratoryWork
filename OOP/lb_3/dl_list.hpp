#pragma once

template <class T>
size_t my::dl_list<T>::get_size() const {
    return this->size;
}

template <class T>
void my::dl_list<T>::push_back(const T &obj) {
    insert(obj, this->size);
}

template <class T>
void my::dl_list<T>::insert(const T &obj, size_t index) {
    if (this->size == 0 && index == 0) {
        head = new node(obj);
        tail = head;
        ++(this->size);
        return;
    }

    check_put_range(index);
    if (index == 0) {
        node *to_insert = new node(obj, head, nullptr);
        head->prev = to_insert;
        head = to_insert;
    } else if (index == this->size) {
        node *to_insert = new node(obj, nullptr, tail);
        tail->next = to_insert;
        tail = to_insert;
    } else {
        node *prev = move_to(index - 1);
        node *next = prev->next;
        node *to_insert = new node(obj, next, prev);
        prev->next = to_insert;
        next->prev = to_insert;
    }
    ++(this->size);
}

template <class T>
void my::dl_list<T>::remove(size_t index) {
    if (this->size == 1 && index == 0) {
        node *to_delete = head;
        head = nullptr;
        tail = nullptr;
        delete to_delete;
        --(this->size);
        return;
    }
    
    check_get_range(index);
    if (index == 0) {
        node *to_delete = head;
        head = head->next;
        head->prev = nullptr;
        delete to_delete;
    } else if (index == this->size - 1) {
        node *to_delete = tail;
        tail = tail->prev;
        tail->next = nullptr;
        delete to_delete;
    } else {
        node *to_delete = move_to(index);
        node *prev = to_delete->prev;
        node *next = to_delete->next;
        next->prev = prev;
        prev->next = next;
        delete to_delete;
    }
    --(this->size);
}

template <class T>
T &my::dl_list<T>::operator[](size_t index) {
    check_get_range(index);
    node *target = move_to(index);
    return target->val;
}

template <class T>
T my::dl_list<T>::operator[](size_t index) const {
    check_get_range(index);
    node *target = move_to(index);
    return target->val;
}

template <class T>
my::dl_list<T>::~dl_list() {
    node *temp = head;
    node *to_delete = temp;
    while (this->size-- > 0) {
        temp = temp->next;
        delete to_delete;
        to_delete = temp;
    }
}

template <class T>
typename my::dl_list<T>::node *my::dl_list<T>::move_to(size_t index) const {
    node *temp;
    if (index > (this->size / 2)) {
        temp = tail;
        while (index++ < this->size - 1) {
            temp = temp->prev;
        }
    } else {
        temp = head;
        while (index-- > 0) {
            temp = temp->next;
        }
    }
    return temp;
}

template <class T>
void my::dl_list<T>::check_put_range(size_t index) const {
    if (!(index >= 0 && index <= this->size))
        throw std::out_of_range("Out of range");
}

template <class T>
void my::dl_list<T>::check_get_range(size_t index) const {
    if (!(index >= 0 && index < this->size))
        throw std::out_of_range("Out of range");
}

template <class T>
my::dl_list<T>::node::node(const T &val, node *next, node *prev)
    : val(val), next(next), prev(prev) {}
