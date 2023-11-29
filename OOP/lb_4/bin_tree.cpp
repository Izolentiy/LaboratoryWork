#include "bin_tree.h"

void my::bin_tree::insert(const int &obj) {
    node *to_insert = new node(obj);
    if (root == nullptr)
        root = to_insert;
    else
        insert(to_insert, root);
}

void my::bin_tree::insert(node *to_insert, node *subroot) {
    if (subroot->val < to_insert->val) {
        if (subroot->right == nullptr) {
            subroot->right = to_insert;
            return;
        } else {
            insert(to_insert, subroot->right);
            return;
        }
    } else if (subroot->val > to_insert->val) {
        if (subroot->left == nullptr) {
            subroot->left = to_insert;
            return;
        } else {
            insert(to_insert, subroot->left);
            return;
        }
    }
    // values are equal
}

void my::bin_tree::operator+=(std::initializer_list<int> list) {
    for (int item : list) {
        insert(item);
    }
}

void my::bin_tree::remove(const int &obj) {}

uint16_t my::bin_tree::get_height() {
    return uint16_t();
}

int my::bin_tree::get_min() {
    if (root == nullptr)
        throw std::logic_error("Trying to get min of empty tree");
    node *temp = root;
    while (temp->left != nullptr) {
        temp = temp->left;
    }
    return temp->val;
}

int my::bin_tree::get_max() {
    if (root == nullptr)
        throw std::logic_error("Trying to get max of empty tree");
    node *temp = root;
    while (temp->right != nullptr) {
        temp = temp->right;
    }
    return temp->val;
}

bool my::bin_tree::contains(const int &obj) {
    return false;
}

my::bin_tree::~bin_tree() {}

my::bin_tree::node::node(const int &val, node *left, node *right)
    : val(val), left(left), right(right) {}

std::ostream &my::operator<<(std::ostream &out, bin_tree &tree) {
    tree_printer printer(out, tree.root);
    printer.print_tree();
    return out;
}

void my::tree_printer::print_tree() {
    // TODO: Improve algorithm to exclude overwork
    print_distance = 0;
    while (print(print_root, 0)) { // print branches
        out << "\n";
        is_printing_nodes = true;
        print(print_root, 0); // print nodes
        is_printing_nodes = false;
        out << "\n";
        ++print_distance;
    }
}

bool my::tree_printer::print(bin_tree::node *root, uint16_t root_distance) {
    if (root_distance == print_distance || root == nullptr) {
        if (is_printing_nodes) {
            print_node(root, root_distance);
        } else {
            print_branch(root, root_distance);
        }
        if (root == nullptr)
            return false;
        return true;
    }
    if (root_distance < print_distance) {
        // go further
        ++root_distance;
        bool left = print(root->left, root_distance);
        bool right = print(root->right, root_distance);
        return left || right;
    }
    return false;
}

void my::tree_printer::print_node(bin_tree::node *root, uint16_t root_distance) {
    int16_t tab = pow(2, levels_to_print - 1 - root_distance) - 1;
    if (root == nullptr) {
        print_char(' ', tab * 2);
        out << ' ';
        print_char(' ', tab * 2 + 3);
        return;
    }
    print_char(' ', tab);
    print_char('_', tab);
    out << root->val;
    print_char('_', tab);
    print_char(' ', tab + 3);
}

void my::tree_printer::print_branch(bin_tree::node *root, uint16_t root_distance) {
    if (root_distance > 0) {
        int16_t tab = pow(2, levels_to_print - 1 - root_distance) - 1;
        print_char(' ', tab * 2);
        if (root == nullptr)
            out << ' ';
        else
            out << '|';
        print_char(' ', tab * 2 + 3);
    }
}

void my::tree_printer::print_char(char ch, int times) {
    for (int i = 0; i < times; ++i) {
        out << ch;
    }
}

void my::tree_printer::set_level_count(uint16_t level) {
    this->levels_to_print = level;
}

my::tree_printer::tree_printer(std::ostream &out, bin_tree::node *root)
    : out(out), print_root(root) {}
