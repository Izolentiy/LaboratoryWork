#include "bin_tree.h"
#include <vector>

int main() {
    my::bin_tree tree;
    tree += {6, 1, 3, 9, 4, 7, 2, 5};
    std::cout << tree;
}