#pragma once

template <class K, class V>
my::linked_map<K, V>::~linked_map() {
    node *temp = head;
    node *to_delete = temp;
    while (size-- > 0) {
        temp = temp->next;
        delete to_delete;
        to_delete = temp;
    }
}

template <class K, class V>
V &my::linked_map<K, V>::get(const K &key) {
    node *to_get = find(key);
    if (to_get == nullptr)
        throw std::logic_error("No element with such key");
    return to_get->get_val();
}

template <class K, class V>
void my::linked_map<K, V>::insert(const K &key, const V &obj) {
    node *to_insert = find(key);
    if (to_insert != nullptr) { // node already exists
        to_insert->get_val() = obj;  // update value
    } else {                    // not found a node, push_back
        insert(size, key, obj);
    }
}

template <class K, class V>
void my::linked_map<K, V>::remove(const K &key) {
    node *to_delete = find(key);
    if (to_delete == nullptr) {
        throw std::logic_error("No element with such key");
    } else {
        node *prev = to_delete->prev;
        node *next = to_delete->next;
        prev->next = next;
        next->prev = prev;
        delete to_delete;
    }
}

template <class K, class V>
K my::linked_map<K, V>::get_key(size_t index) {
    return move_to(index)->get_key();
}

template <class K, class V>
size_t my::linked_map<K, V>::get_size() const {
    return size;
}

template <class K, class V>
typename my::linked_map<K, V>::node *my::linked_map<K, V>::find(const K &key) {
    if (head != nullptr) {
        node *temp = head;
        do {
            if (temp->get_key() == key)
                return temp; // found node
            temp = temp->next;
        } while (temp != nullptr);
    }
    return nullptr; // doesn't contain node with given key
}

template <class K, class V>
typename my::linked_map<K, V>::node *my::linked_map<K, V>::move_to(size_t index) {
    check_range(index);
    node *temp;
    if (index > (size / 2)) {
        temp = tail;
        while (index++ < size - 1) {
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

template <class K, class V>
void my::linked_map<K, V>::insert(size_t index, const K &key, const V &obj) {
    check_range(index);
    if (size == 0) {
        head = new node(key, obj);
        tail = head;
        ++size;
        return;
    }

    if (index == 0) {
        node *to_insert = new node(key, obj, head, nullptr);
        head->prev = to_insert;
        head = to_insert;
    } else if (index == size) {
        node *to_insert = new node(key, obj, nullptr, tail);
        tail->next = to_insert;
        tail = to_insert;
    } else {
        node *prev = move_to(index - 1);
        node *next = prev->next;
        node *to_insert = new node(key, obj, next, prev);
        prev->next = to_insert;
        next->prev = to_insert;
    }
    ++size;
}

template <class K, class V>
void my::linked_map<K, V>::check_range(size_t index) {
    bool is_correct = (index >= 0) && (index <= size);
    if (!is_correct)
        throw std::out_of_range("Out of range");
}

template <class K, class V>
my::linked_map<K, V>::node::node(K key, const V &val, node *next, node *prev)
    : key(key), val(val), next(next), prev(prev) {}

template <class K, class V>
K my::linked_map<K, V>::node::get_key() const {
    return key;
}

template <class K, class V>
V &my::linked_map<K, V>::node::get_val() {
    return val;
}