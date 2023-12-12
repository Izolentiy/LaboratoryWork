#pragma once
#include "bin_tree.h"

namespace my {
    class tree_printer;
    struct char_sequence;
    std::ostream &operator<<(std::ostream &out, char_sequence &seq);
}

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

class my::tree_printer {
  public:
    enum print_mode {
        drawing, symmetric, straight, reversed
    };
    tree_printer(std::ostream &out);
    tree_printer &set_ostream(std::ostream &out);
    tree_printer &set_print_depth(int depth);
    tree_printer &set_root(bin_tree::node *root);
    tree_printer &operator<<(const print_mode &mode);
    tree_printer &operator<<(const bin_tree &tree);
    tree_printer &operator<<(const char *str);
    tree_printer &operator<<(int num);
    tree_printer &operator<<(double num);

  private:
    std::ostream *out;
    print_mode mode = drawing;
    bin_tree::node *print_root = nullptr;
    int print_depth = 5;
    int print_distance = 0;
    bool is_printing_nodes = false;
    void draw_tree(bin_tree::node *root);
    bool draw(bin_tree::node *root, int root_distance);
    void draw_node(bin_tree::node *root, int root_distance);
    void draw_branch(bin_tree::node *root, int root_distance);
    void print_symmetric(bin_tree::node *subroot);
    void print_straight(bin_tree::node *subroot);
    void print_reversed(bin_tree::node *subroot);
    void print_node(bin_tree::node *node);
};

struct my::char_sequence {
    char ch;
    int count;
    char_sequence(char ch, int count);
    char_sequence &operator()(int count);
};