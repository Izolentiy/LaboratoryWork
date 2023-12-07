#include "bin_tree.h"
#include "tree_printer.h"

using mode = my::tree_printer::print_mode;

void overview();
void removal_test();

void print(my::tree_printer &out, mode mode, std::string &name, my::bin_tree tree);

int main() {
    // overview();
    removal_test();
}

void removal_test() {
    // prepare printer
    my::tree_printer printer(std::cout);

    // empty tree
    my::bin_tree empty_tree;
    empty_tree.remove(1);
    printer << "\nEmpty tree:\n" << mode::drawing << empty_tree << "\n";

    // tree with only one element
    my::bin_tree single_tree = {2};
    printer << "\nSingle tree:\n" << mode::drawing << single_tree << "\n";
    single_tree.remove(1); // non existing element
    single_tree.remove(2); // root
    printer << "\nRemove 1, 2 from single element tree\n";
    printer << "\nSingle tree:\n" << mode::drawing << single_tree << "\n";

    // random tree
    my::bin_tree tree = {6, 3, 9, 4, 7, 2, 5, 8};
    printer << "\nRandom tree:\n" << mode::drawing << tree << "\n";
    tree.remove(1); // non existing element
    tree.remove(3); // branch
    tree.remove(6); // root
    tree.remove(8); // leaf
    printer << "\nRemove 1, 3, 6, 8 from random tree\n";
    printer << "\nRandom tree:\n" << mode::drawing << tree << "\n";

}

void print(my::tree_printer &out, mode mode, std::string &name, my::bin_tree tree) {
    out << "\n" << name.c_str() << ":\n" << mode << tree << "\n";
}

void overview() {
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
