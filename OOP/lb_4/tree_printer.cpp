#include "tree_printer.h"

void my::tree_printer::draw_tree(bin_tree::node *root) {
    // TODO: Improve algorithm to exclude overwork
    print_distance = 0;
    while (draw(root, 0)) { // print branches
        *out << "\n";
        is_printing_nodes = true;
        draw(root, 0); // print nodes
        is_printing_nodes = false;
        *out << "\n";
        ++print_distance;
    }
}

bool my::tree_printer::draw(bin_tree::node *root, uint16_t root_distance) {
    if (root_distance == print_distance || root == nullptr) {
        if (is_printing_nodes)
            draw_node(root, root_distance);
        else
            draw_branch(root, root_distance);

        if (root == nullptr)
            return false;
        return true;
    }
    if (root_distance < print_distance) {
        // go further
        ++root_distance;
        bool left = draw(root->left, root_distance);
        bool right = draw(root->right, root_distance);
        return left || right;
    }
    return false;
}

void my::tree_printer::draw_node(bin_tree::node *root, uint16_t root_distance) {
    int tab = pow(2, print_depth - 1 - root_distance) - 1;
    char_sequence es {' ', tab * 2}; // edge space
    char_sequence eu {'_', tab * 2}; // edge underscore
    if (root == nullptr) {
        *out << es(tab * 2) << ' ' << es(tab * 2 + 3);
        return;
    }
    if (root->left == nullptr) {
        *out << es(tab * 2) << root->val;
    } else {
        *out << es(tab) << eu(tab) << root->val;
    }
    if (root->right == nullptr) {
        *out << es(tab * 2 + 3);
    } else {
        *out << eu(tab) << es(tab + 3);
    }
}

void my::tree_printer::draw_branch(bin_tree::node *root, uint16_t root_distance) {
    if (root_distance > 0) {
        int tab = pow(2, print_depth - 1 - root_distance) - 1;
        char_sequence es {' ', tab * 2};
        if (root == nullptr) {
            *out << es << ' ' << es(tab * 2 + 3);
        } else {
            *out << es << '|' << es(tab * 2 + 3);
        }
    }
}

void my::tree_printer::print_symmetric(bin_tree::node *subroot) {
    if (subroot == nullptr) return;
    print_symmetric(subroot->left);
    print_node(subroot);
    print_symmetric(subroot->right);
}

void my::tree_printer::print_straight(bin_tree::node *subroot) {
    if (subroot == nullptr) return;
    print_node(subroot);
    print_straight(subroot->left);
    print_straight(subroot->right);
}

void my::tree_printer::print_reversed(bin_tree::node *subroot) {
    if (subroot == nullptr) return;
    print_reversed(subroot->right);
    print_reversed(subroot->left);
    print_node(subroot);
}

void my::tree_printer::print_node(bin_tree::node *node) {
    *out << ' ' << node->val << ' ';
}

my::tree_printer &my::tree_printer::set_print_depth(uint16_t level) {
    this->print_depth = level;
    return *this;
}

my::tree_printer &my::tree_printer::set_root(bin_tree::node *root) {
    this->print_root = root;
    return *this;
}

my::tree_printer &my::tree_printer::operator<<(const print_mode &mode) {
    this->mode = mode;
    return *this;
}

my::tree_printer &my::tree_printer::operator<<(const bin_tree &tree) {
    print_root = tree.root;
    switch (mode) {
    case drawing: draw_tree(print_root); break;
    case symmetric: print_symmetric(print_root); break;
    case straight: print_straight(print_root); break;
    case reversed: print_reversed(print_root); break;
    }
    return *this;
}

my::tree_printer &my::tree_printer::operator<<(const char *str) {
    *out << str;
    return *this;
}

my::tree_printer &my::tree_printer::set_ostream(std::ostream &out) {
    this->out = &out;
    return *this;
}

my::tree_printer::tree_printer(std::ostream &out)
    : out(&out) {}

std::ostream &my::operator<<(std::ostream &out, my::char_sequence &seq) {
    for (int i = 0; i < seq.count; ++i) {
        out << seq.ch;
    }
    return out;
}

my::char_sequence::char_sequence(char ch, int count)
    : ch(ch), count(count) {}

my::char_sequence &my::char_sequence::operator()(int count) {
    this->count = count;
    return *this;
}