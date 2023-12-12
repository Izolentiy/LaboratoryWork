#include "bin_tree.h"
#include "tree_printer.h"

using mode = my::tree_printer::print_mode;

void overview();
void removal_test();
void insertion_test();
void comparison();

int main() {
    overview();
    // comparison();
    // removal_test();
    // insertion_test();
}

void removal_test() {
    // prepare printer
    my::tree_printer printer(std::cout);
    printer << "\n\n\n ~~~ REMOVAL TESTS:\n";

    // empty tree
    my::bin_tree empty_tree;
    empty_tree.remove(1);
    printer << "\nRemove 1 from empty tree";
    printer << "\nEmpty tree:\n" << mode::drawing << empty_tree << "\n";

    // tree with only one element
    my::bin_tree single_tree = {2};
    printer << "\nSingle tree:\n" << mode::drawing << single_tree << "\n";
    single_tree.remove(1); // non existing element
    single_tree.remove(2); // root
    printer << "\nRemove 1, 2 from single element tree";
    printer << "\nSingle tree:\n" << mode::drawing << single_tree << "\n";

    // random tree
    my::bin_tree tree = {6, 3, 9, 4, 7, 2, 5, 8};
    printer << "\nRandom tree:\n" << mode::drawing << tree << "\n";
    tree.remove(1); // non existing element
    tree.remove(3); // branch
    tree.remove(6); // root
    tree.remove(8); // leaf
    printer << "\nRemove 1, 3, 6, 8 from random tree";
    printer << "\nRandom tree:\n" << mode::drawing << tree << "\n";
}

void insertion_test() {
    // prepare printer
    my::tree_printer printer(std::cout);
    printer << "\n\n\n ~~~ INSERTION TESTS:\n";

    // create empty tree
    my::bin_tree tree;
    printer << "\nEmpty tree:\n" << mode::drawing << tree << "\n";
    printer << "\nInsert 6 in empty tree";
    tree.insert(6);
    printer << "\nTree:\n" << mode::drawing << tree << "\n";
    printer << "\nInsert 3, 4 in tree";
    tree.insert(3);
    tree.insert(4);
    printer << "\nTree:\n" << mode::drawing << tree << "\n";
}

void comparison() {
    my::bin_tree tree = {6, 1, 3, 9, 4, 7, 2, 5, 8};
    my::tree_printer printer(std::cout);

    printer << "\nHeight: " << tree.get_height() << "\n";
    printer << "\nSymmetric\n" << mode::symmetric << tree << "\n";
    printer << "\nReversed\n" << mode::reversed << tree << "\n";
    printer << "\nStraight\n" << mode::straight << tree << "\n";
}

void overview() {
    my::bin_tree tree = {6, 1, 3, 9, 4, 7, 2, 5, 8};
    my::bin_tree tree_copy = tree;
    my::tree_printer printer(std::cout);

    printer << "\nTree #1:\n" << mode::drawing << tree << "\n";
    printer << "Removing some elements...";
    tree.remove(3);
    tree.remove(2);
    tree.remove(6);
    printer << "\nTree #1:\n" << mode::drawing << tree << "\n";
    printer << "\nTree #2:\n" << mode::drawing << tree_copy << "\n";

    printer << "\nSymmetric\n" << mode::symmetric << tree << "\n";
    printer << "\nStraight\n" << mode::straight << tree << "\n";
    printer << "\nReversed\n" << mode::reversed << tree << "\n";

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
