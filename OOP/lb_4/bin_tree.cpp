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
        } else {
            insert(to_insert, subroot->right);
        }
    } else if (subroot->val > to_insert->val) {
        if (subroot->left == nullptr) {
            subroot->left = to_insert;
            to_insert->parent = subroot;
        } else {
            insert(to_insert, subroot->left);
        }
    }
}

void my::bin_tree::remove(const int &obj) {
    node *subroot = move_to(obj);
    if (subroot == nullptr)
        return; // not found
    if (subroot == this->root && root->is_leaf())
        root = nullptr;
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
        // disposing root
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

int my::bin_tree::get_height(node *subroot) {
    if (subroot == nullptr) {
        return -1;
    } else {
        int left = get_height(subroot->left);
        int right = get_height(subroot->right);
        return 1 + std::max(left, right);
    }
}

int my::bin_tree::get_height() {
    return get_height(root);
}

my::bin_tree my::bin_tree::get_subtree(const int &obj) {
    bin_tree subtree;
    node *temp = root;
    bool flag = false;
    while (true) {
        if (temp == nullptr) {
            break; // not found
        } else if (temp->val > obj) {
            if (flag) {
                break;
            } else {
                flag = true;
                if (temp->left == nullptr)
                    break;
                temp = temp->left;
            }
        } else if (temp->val <= obj) {
            temp = temp->right;
        }
    }
    subtree.copy(temp);
    return subtree;
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
