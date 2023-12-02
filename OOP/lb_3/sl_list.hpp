#pragma once

template <class T>
my::sl_list<T>::sl_list(const sl_list &other) {
    this->append(other);
}

template <class T>
void my::sl_list<T>::clear() {
    node *temp = head;
    node *to_delete = temp;
    while (this->size-- > 0) {
        temp = temp->next;
        delete to_delete;
        to_delete = temp;
    }
    this->size = 0;
}

template <class T>
void my::sl_list<T>::append(const sl_list &other) {
    node *onode = other.head; // other node
    for (size_t i = 0; i < other.size; ++i) {
        this->push_back(onode->val);
        onode = onode->next;
    }
}

template <class T>
my::sl_list<T> &my::sl_list<T>::operator=(const sl_list &other) {
    this->clear();       // clear memory from previous elements
    this->append(other); // append elements from other list
    return *this;
}

template <class T>
void my::sl_list<T>::push_back(const T &obj) {
    insert(obj, this->size);
}

template <class T>
void my::sl_list<T>::insert(const T &obj, size_t index) {
    if (this->size == 0 && index == 0) {
        head = new node(obj);
        ++(this->size);
        return;
    }

    this->check_put_range(index);
    if (index == 0) {
        node *to_insert = new node(obj, head);
        head = to_insert;
    } else {
        node *prev = move_to(index - 1);
        node *to_insert = new node(obj, prev->next);
        prev->next = to_insert;
    }
    ++(this->size);
}

template <class T>
void my::sl_list<T>::remove(size_t index) {
    if (this->size == 1 && index == 0) {
        delete head;
        head = nullptr;
        --(this->size);
        return;
    }

    this->check_get_range(index);
    if (index == 0) {
        node *to_delete = head;
        head = head->next;
        delete to_delete;
    } else {
        node *prev = move_to(index - 1);
        node *to_delete = prev->next;
        prev->next = to_delete->next;
        delete to_delete;
    }
    --(this->size);
}

template <class T>
T &my::sl_list<T>::operator[](size_t index) {
    this->check_get_range(index);
    node *target = move_to(index);
    return target->val;
}

template <class T>
T my::sl_list<T>::operator[](size_t index) const {
    this->check_get_range(index);
    node *target = move_to(index);
    return target->val;
}

template <class T>
my::sl_list<T>::~sl_list() {
    this->clear();
}

template <class T>
typename my::sl_list<T>::node *my::sl_list<T>::move_to(size_t index) const {
    node *temp = head;
    while (index-- > 0) {
        temp = temp->next;
    }
    return temp;
}

template <class T>
my::sl_list<T>::node::node(const T &val, node *next)
    : val(val), next(next) {}
