#pragma once
#include "stdint.h"
#include <iostream>
#include <math.h>
#include <ostream>

namespace my {
    class bin_tree;
    class tree_printer;
    std::ostream &operator<<(std::ostream &out, bin_tree &tree);
} // namespace my

/*
    BINARY TREE

4                    _______________*______________
                    |                              \
3            ______ * ______                  _____ * _____
            |               |                /             \
2        ___*___         __ 1 __          _ * _           __*__
        |       |       |       |        /     \         /     \
1      _*_     _*      _*_      *       *       *       *       *
      |       |       |   |    / \     /       / \     / \     / \
0     *       *       *   *   *   *   *       *   *   *   *   *   *
      |                                               |
     >5                                               2

    height = 5;
    node_count = 31;
    route example: "RLLR"

*/

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
    friend std::ostream &my::operator<<(std::ostream &out, bin_tree &tree);

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
    int get_min();
    int get_max();
    ~bin_tree();
};

class my::tree_printer {
  private:
    std::ostream *out;
    bin_tree::node *print_root;
    uint16_t print_depth = 5;
    uint16_t print_distance = 0;
    bool is_printing_nodes = false;
    bool draw(bin_tree::node *root, uint16_t root_distance);
    void draw_node(bin_tree::node *root, uint16_t root_distance);
    void draw_branch(bin_tree::node *root, uint16_t root_distance);
    void print_char(char ch, int times);
    void print_symmetric(bin_tree::node *subroot);
    void print_straight(bin_tree::node *subroot);
    void print_reversed(bin_tree::node *subroot);
    void print_node(bin_tree::node *node);

  public:
    tree_printer(std::ostream &out, bin_tree::node *root);
    tree_printer(std::ostream &out, bin_tree &tree);
    tree_printer &set_ostream(std::ostream &out);
    tree_printer &set_print_depth(uint16_t depth);
    tree_printer &set_root(bin_tree::node *root);
    void draw_tree();
    void print_symmetric();
    void print_straight();
    void print_reversed();
};