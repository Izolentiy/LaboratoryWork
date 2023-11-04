#include "container.h"
#include "dl_list.h"
#include "sl_list.h"
#include <iostream>

void populate(my::container<int> &list, int elem_count);
void clear(my::container<int> &list);
void print(my::container<int> &list);

void removal_scenario(my::container<int> &list);
void insertion_scenario(my::container<int> &list);
void extraction_scenario(my::container<int> &list);

void doubly_linked_list_tests();
void singly_linked_list_tests();

int main() {
    doubly_linked_list_tests();
    singly_linked_list_tests();
}

void doubly_linked_list_tests() {
    my::dl_list<int> list;
    std::cout << "\n\n\n ~~~ DOUBLY-LINKED LIST TESTS:\n";
    extraction_scenario(list);
    removal_scenario(list);
    insertion_scenario(list);
}

void singly_linked_list_tests() {
    my::sl_list<int> list;
    std::cout << "\n\n\n ~~~ SINGLY-LINKED LIST TESTS:\n";
    extraction_scenario(list);
    removal_scenario(list);
    insertion_scenario(list);
}

void removal_scenario(my::container<int> &list) {
    std::cout << "\n\n ~ Remove scenario\n\n";

    clear(list);
    int size = 8;
    populate(list, size);
    print(list);

    // remove last
    std::cout << "Remove last [" << size - 1 << "]\n";
    list.remove(size - 1);
    print(list);

    // remove first
    std::cout << "Remove first [0]\n";
    list.remove(0);
    print(list);

    // remove correct index
    int correct = 3;
    std::cout << "Remove [" << correct << "]\n";
    list.remove(correct);
    print(list);

    // remove wrong index
    try {
        int wrong = 12;
        std::cout << "Remove [" << wrong << "]\n";
        list.remove(wrong);
    } catch (const std::out_of_range &e) {
        std::cerr << e.what() << '\n';
    }
}

void extraction_scenario(my::container<int> &list) {
    std::cout << "\n\n ~ Extract scenario\n\n";

    clear(list);
    // wrong indeces
    try {
        std::cout << "Try to access element out of range : ";
        double third = list[2];
    } catch (const std::out_of_range &e) {
        std::cerr << e.what() << '\n';
    }
    try {
        std::cout << "Try to access 0 element of empty list : ";
        double first = list[0];
    } catch (const std::out_of_range &e) {
        std::cerr << e.what() << '\n';
    }

    // correct indeces
    int size = 5;
    populate(list, size);
    print(list);

    double first = list[0];
    std::cout << "first element : " << first << "\n";

    double last = list[size - 1];
    std::cout << "last element : " << last << "\n";
}

void insertion_scenario(my::container<int> &list) {
    std::cout << "\n\n ~ Insert scenario\n\n";

    clear(list);
    int size = 8;
    populate(list, size);
    print(list);

    // insert on last
    std::cout << "Insert on last [" << size << "]\n";
    list.insert(10, size);
    print(list);

    // insert on first
    std::cout << "Insert on first [0]\n";
    list.insert(11, 0);
    print(list);

    // insert correct index
    int correct = 3;
    std::cout << "Insert on [" << correct << "]\n";
    list.insert(12, correct);
    print(list);

    // insert wrong index
    try {
        int wrong = 20;
        std::cout << "Insert on [" << wrong << "]\n";
        list.insert(13, wrong);
    } catch (const std::out_of_range &e) {
        std::cerr << e.what() << '\n';
    }
}

void populate(my::container<int> &list, int elem_count) {
    for (int i = 0; i < elem_count; ++i) {
        list.push_back(i + 1);
    }
}

void clear(my::container<int> &list) {
    size_t init_size = list.get_size();
    for (size_t i = 0; i < init_size; ++i) {
        list.remove(0);
    }
}

void print(my::container<int> &list) {
    for (int i = 0; i < list.get_size(); ++i) {
        std::cout << list[i];
        if (i != list.get_size() - 1)
            std::cout << ", ";
    }
    std::cout << "\n";
}