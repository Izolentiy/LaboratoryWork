#include "bin_tree.h"

my::bin_tree::bin_tree(std::initializer_list<int> list) {
    for (int item : list) {
        insert(item);
    }
}

my::bin_tree::bin_tree(const bin_tree &other) {
    copy(other.root);
}

my::bin_tree::bin_tree(bin_tree &&other) {
    this->root = other.root;
    other.root = nullptr;
}

my::bin_tree &my::bin_tree::operator=(const bin_tree &other) {
    clear(root);
    copy(other.root);
    return *this;
}

my::bin_tree &my::bin_tree::operator=(bin_tree &&other) {
    clear(root);
    this->root = other.root;
    other.root = nullptr;
    return *this;
}

void my::bin_tree::insert(const int &obj) {
    node *to_insert = new node(obj);
    if (root == nullptr) {
        root = to_insert;
    } else {
        insert(to_insert, root);
    }
}

void my::bin_tree::insert(node *to_insert, node *subroot) {
    if (subroot->val < to_insert->val) {
        if (subroot->right == nullptr) {
            subroot->right = to_insert;
            to_insert->parent = subroot;
            return;
        } else {
            insert(to_insert, subroot->right);
            return;
        }
    } else if (subroot->val > to_insert->val) {
        if (subroot->left == nullptr) {
            subroot->left = to_insert;
            to_insert->parent = subroot;
            return;
        } else {
            insert(to_insert, subroot->left);
            return;
        }
    }
    // values are equal
}

void my::bin_tree::remove(const int &obj) {
    node *subroot = move_to(obj);
    if (subroot == nullptr)
        return; // not found
    remove(subroot);
}

void my::bin_tree::remove(node *to_remove) {
    if (to_remove->is_leaf()) {
        dispose(to_remove);
        return;
    }
    node *max_left = get_max(to_remove->left);
    node *min_right = get_min(to_remove->right);
    size_t dl = SIZE_MAX, dr = SIZE_MAX; // delta left / right
    if (max_left != nullptr)
        dl = std::abs(max_left->val - to_remove->val);
    if (min_right != nullptr)
        dr = std::abs(min_right->val - to_remove->val);

    if (dl == dr) {
        // values are equal
        if (max_left != nullptr) {
            to_remove->val = max_left->val;
            remove(max_left);
        } else {
            to_remove->val = min_right->val;
            remove(min_right);
        }
    } else if (dl < dr) {
        to_remove->val = max_left->val;
        remove(max_left);
    } else if (dr < dl) {
        to_remove->val = min_right->val;
        remove(min_right);
    }
}

void my::bin_tree::dispose(node *to_delete) {
    node *parent = to_delete->parent;
    if (parent == nullptr) {
        // strange scenario
    } else if (parent->left == to_delete) {
        parent->left = nullptr;
    } else if (parent->right == to_delete) {
        parent->right = nullptr;
    }
    delete to_delete;
}

my::bin_tree::node *my::bin_tree::move_to(const int &obj) {
    node *temp = root;
    while (true) {
        if (temp == nullptr) {
            break; // not found
        } else if (temp->val > obj) {
            temp = temp->left;
        } else if (temp->val < obj) {
            temp = temp->right;
        } else if (temp->val == obj) {
            break; // found
        }
    }
    return temp;
}

my::bin_tree::node *my::bin_tree::get_max(node *subroot) {
    node *temp = subroot;
    if (subroot != nullptr)
        while (temp->right != nullptr) {
            temp = temp->right;
        }
    return temp;
}

my::bin_tree::node *my::bin_tree::get_min(node *subroot) {
    node *temp = subroot;
    if (subroot != nullptr)
        while (temp->left != nullptr) {
            temp = temp->left;
        }
    return temp;
}

uint16_t my::bin_tree::get_height() {
    return get_height(0, root);
}

uint16_t my::bin_tree::get_height(uint16_t root_distance, node *subroot) {
    if (subroot == nullptr) {
        if (root_distance == 0)
            return root_distance;
        return --root_distance;
    }
    ++root_distance;
    uint16_t left = get_height(root_distance, subroot->left);
    uint16_t right = get_height(root_distance, subroot->right);
    return std::max(left, right);
}

int my::bin_tree::get_min() {
    node *min = get_min(root);
    if (min == nullptr)
        throw std::logic_error("Trying to get min of empty tree");
    return min->val;
}

int my::bin_tree::get_max() {
    node *max = get_max(root);
    if (max == nullptr)
        throw std::logic_error("Trying to get min of empty tree");
    return max->val;
}

bool my::bin_tree::contains(const int &obj) {
    node *temp = move_to(obj);
    return temp;
}

void my::bin_tree::clear(node *subroot) {
    if (subroot == nullptr) return;
    clear(subroot->right);
    clear(subroot->left);
    delete subroot;
    subroot = nullptr;
}

void my::bin_tree::copy(node *subroot) {
    if (subroot == nullptr) return;
    insert(subroot->val);
    copy(subroot->left);
    copy(subroot->right);
}

my::bin_tree::~bin_tree() {
    clear(root);
}

my::bin_tree::node::node(const int &val, node *left, node *right)
    : val(val), left(left), right(right) {}

std::ostream &my::operator<<(std::ostream &out, bin_tree &tree) {
    tree_printer printer(out, tree.root);
    printer.set_print_depth(5)
        .draw_tree();
    return out;
}

void my::tree_printer::draw_tree() {
    // TODO: Improve algorithm to exclude overwork
    print_distance = 0;
    while (draw(print_root, 0)) { // print branches
        *out << "\n";
        is_printing_nodes = true;
        draw(print_root, 0); // print nodes
        is_printing_nodes = false;
        *out << "\n";
        ++print_distance;
    }
}

void my::tree_printer::print_symmetric() {
    print_symmetric(print_root);
}

void my::tree_printer::print_straight() {
    print_straight(print_root);
}

void my::tree_printer::print_reversed() {
    print_reversed(print_root);
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
    int16_t tab = pow(2, print_depth - 1 - root_distance) - 1;
    if (root == nullptr) {
        print_char(' ', tab * 2);
        *out << ' ';
        print_char(' ', tab * 2 + 3);
        return;
    }
    if (root->left == nullptr) {
        print_char(' ', tab * 2);
    } else {
        print_char(' ', tab);
        print_char('_', tab);
    }
    *out << root->val;
    // out << '*';
    if (root->right == nullptr) {
        print_char(' ', tab * 2 + 3);
    } else {
        print_char('_', tab);
        print_char(' ', tab + 3);
    }
}

void my::tree_printer::draw_branch(bin_tree::node *root, uint16_t root_distance) {
    if (root_distance > 0) {
        int16_t tab = pow(2, print_depth - 1 - root_distance) - 1;
        print_char(' ', tab * 2);
        if (root == nullptr)
            *out << ' ';
        else
            *out << '|';
        print_char(' ', tab * 2 + 3);
    }
}

void my::tree_printer::print_char(char ch, int times) {
    for (int i = 0; i < times; ++i) {
        *out << ch;
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

my::tree_printer &my::tree_printer::set_ostream(std::ostream &out) {
    this->out = &out;
    return *this;
}

my::tree_printer::tree_printer(std::ostream &out, bin_tree::node *root)
    : out(&out), print_root(root) {}

my::tree_printer::tree_printer(std::ostream &out, bin_tree &tree)
    : out(&out), print_root(tree.root) {}
