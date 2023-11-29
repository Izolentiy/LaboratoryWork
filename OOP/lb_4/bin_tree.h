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
3            _______*_______                  _____ * _____
            |               |                /             \
2        ___*___         __ 1 __          _ * _           __*__
        |       |       |       |        /     \         /     \
1      _*_     _*_      *      _*_      *       *       *       *
      |   |   |   |   |   |   |   |    / \     / \     / \     / \
0     *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *
      |                                               |
     >5                                               2

    height = 5;
    node_count = 31;
    route example: "RLLR"

*/

class my::bin_tree {
    class node {
      public:
        node *left;
        node *right;
        int val;

        node(const int &val, node *left = nullptr, node *right = nullptr);
    };
    friend class tree_printer;
    friend std::ostream &my::operator<<(std::ostream &out, bin_tree &tree);

  private:
    node *root = nullptr;
    uint8_t levels_to_print = 4;
    void insert(node *to_insert, node *subroot);

  public:
    bin_tree() = default;
    void insert(const int &obj);
    void operator+=(std::initializer_list<int> list);

    void remove(const int &obj);
    uint16_t get_height();
    int get_min();
    int get_max();
    bool contains(const int &obj);
    ~bin_tree();
};

class my::tree_printer {
  private:
    std::ostream &out;
    bin_tree::node *print_root;
    uint16_t levels_to_print = 6;
    uint16_t print_distance = 0;
    bool is_printing_nodes = false;
    bool print(bin_tree::node *root, uint16_t root_distance);
    void print_node(bin_tree::node *root, uint16_t root_distance);
    void print_branch(bin_tree::node *root, uint16_t root_distance);
    void print_char(char ch, int times);

  public:
    tree_printer(std::ostream &out, bin_tree::node *root);
    void print_tree();
    void set_level_count(uint16_t level);
};