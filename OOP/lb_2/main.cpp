#include "hash.hpp"
#include "map.h"
#include "string.h"
#include <iostream>
#include <vector>

void hash_code_scenario();
void linked_map_scenario();
void string_find_scenario();

void hash_code_scenario() {
    std::vector<my::string> strs = {
        "hello",
        "hello",
        "hella",
    };
    for (my::string &str : strs) {
        std::cout << "hash for " << str << " : "
                  << std::hex << str.hash_code() << "\n";
    }
}

void linked_map_scenario() {
    my::linked_map<double> map;
    my::string key = "hello";
    map.insert(key, 2);
    std::cout << key << " : " << map.get(key) << std::endl;
}

void string_find_scenario() {
    my::string str = "Hello, my friend! I hope you are happy and healthy";
    size_t index = str.find("friend");
    if (index == my::string::npos) {
        std::cout << "substring not found\n";
    } else {
        std::cout << index;
    }
}

int main() {
    // hash_code_scenario();
    string_find_scenario();
}