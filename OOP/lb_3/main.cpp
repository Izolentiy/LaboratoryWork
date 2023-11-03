#include "dl_list.h"
#include <iostream>

void populate(my::dl_list<int> &list, int elem_count);
void print(my::dl_list<int> &list);
void removal_scenario();
void insertion_scenario();
void extraction_scenario();

int main() {
    extraction_scenario();
    removal_scenario();
    insertion_scenario();
}

void removal_scenario() {
    std::cout << "\n\nRemove scenario\n\n";

    my::dl_list<int> list;
    int size = 8;
    populate(list, size);
    print(list);

    // remove last
    std::cout << "Remove last\n";
    list.remove(size - 1);
    print(list);

    // remove first
    std::cout << "Remove first\n";
    list.remove(0);
    print(list);

    // remove correct index
    int correct = 3;
    std::cout << "Remove " << correct << "\n";
    list.remove(correct);
    print(list);

    // remove wrong index
    try {
        int wrong = 12;
        std::cout << "Remove " << wrong << "\n";
        list.remove(wrong);
    } catch (const std::out_of_range &e) {
        std::cerr << e.what() << '\n';
    }
}

void extraction_scenario() {
    std::cout << "\n\nExtract scenario\n\n";

    my::dl_list<int> list;
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

void insertion_scenario() {
    std::cout << "\n\nInsert scenario\n\n";

    my::dl_list<int> list;
    int size = 8;
    populate(list, size);
    print(list);

    // insert on last
    std::cout << "Insert on last\n";
    list.insert(10, size);
    print(list);

    // insert on first
    std::cout << "Insert on first\n";
    list.insert(11, 0);
    print(list);

    // insert correct index
    int correct = 3;
    std::cout << "Insert on " << correct << "\n";
    list.insert(12, correct);
    print(list);

    // insert wrong index
    try {
        int wrong = 20;
        std::cout << "Insert on " << wrong << "\n";
        list.insert(13, wrong);
    } catch (const std::out_of_range &e) {
        std::cerr << e.what() << '\n';
    }
}

void populate(my::dl_list<int> &list, int elem_count) {
    for (int i = 0; i < elem_count; ++i) {
        list.push_back(i + 1);
    }
}

void print(my::dl_list<int> &list) {
    for (int i = 0; i < list.get_size(); ++i) {
        std::cout << list[i];
        if (i != list.get_size() - 1)
            std::cout << ", ";
    }
    std::cout << "\n";
}