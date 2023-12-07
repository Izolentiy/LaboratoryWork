#pragma once
#include "stdint.h"
#include <iostream>
#include <math.h>
#include <ostream>

namespace my {
    class bin_tree;
    class tree_printer;
} // namespace my

class my::bin_tree {
    struct node {
        int val;
        node *parent = nullptr;
        node *left;
        node *right;
        node(const int &val, node *left = nullptr, node *right = nullptr);
        bool is_leaf() { return left == nullptr && right == nullptr; }
    };
    friend class tree_printer;

  private:
    node *root = nullptr;
    void insert(node *to_insert, node *subroot);
    void remove(node *to_remove);
    void dispose(node *to_delete);
    uint16_t get_height(uint16_t root_distance, node *subroot);
    node *move_to(const int &obj);
    node *get_max(node *subroot);
    node *get_min(node *subroot);
    void clear(node *subroot);
    void copy(node *subroot);

  public:
    bin_tree() = default;
    bin_tree(std::initializer_list<int> list);
    bin_tree(const bin_tree &other);
    bin_tree(bin_tree &&other);
    bin_tree &operator=(const bin_tree &other);
    bin_tree &operator=(bin_tree &&other);
    void insert(const int &obj);
    void remove(const int &obj);
    bool contains(const int &obj);
    uint16_t get_height();
    bin_tree get_subtree(const int &obj);
    int get_min();
    int get_max();
    ~bin_tree();
};