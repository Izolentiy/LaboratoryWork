#include "bin_tree.h"
#include "tree_printer.h"

int main() {
    using mode = my::tree_printer::print_mode;
    my::bin_tree tree = {6, 1, 3, 9, 4, 7, 2, 5, 8};
    my::bin_tree tree_copy = tree;
    my::tree_printer printer(std::cout);

    printer << "\nTree #1:\n" << mode::drawing << tree << "\n";
    printer << "Removing some elements...\n";
    tree.remove(3);
    tree.remove(2);
    tree.remove(6);
    printer << "\nTree #1:\n" << mode::drawing << tree << "\n";
    printer << "\nTree #2:\n" << mode::drawing << tree_copy << "\n";

    printer << "\nReversed\n" << mode::reversed << tree << "\n";
    printer << "\nStraight\n" << mode::straight << tree << "\n";
    printer << "\nSymmetric\n" << mode::symmetric << tree << "\n";

    std::cout << "\nMax: " << tree.get_max();
    std::cout << "\nMin: " << tree.get_min();
    std::cout << "\nHeight: " << tree.get_height() << "\n";

    my::bin_tree subtree_1 = tree.get_subtree(7);
    printer << "\nTree #1:\n" << mode::drawing << tree << "\n";
    printer << "\nSubtree #1:\n" << mode::drawing << subtree_1 << "\n";
    
    tree.remove(7);
    my::bin_tree subtree_2 = tree.get_subtree(7);
    printer << "\nTree #1:\n" << mode::drawing << tree << "\n";
    printer << "\nSubtree #2:\n" << mode::drawing << subtree_2 << "\n";
    
    tree.insert(11);
    tree.insert(15);
    my::bin_tree subtree_3 = tree.get_subtree(10);
    printer << "\nTree #1:\n" << mode::drawing << tree << "\n";
    printer << "\nSubtree #3:\n" << mode::drawing << subtree_3 << "\n";

}