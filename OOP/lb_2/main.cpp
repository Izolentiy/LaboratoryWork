#include "hash.hpp"
#include "map.h"
#include "string.h"
#include <iostream>
#include <vector>

void print_hash(my::string &str);
void hash_code_scenario();
void linked_map_scenario();

void print_hash(my::string &str) {
    std::cout << "hash for " << str << " : "
              << std::hex << str.hash_code() << "\n";
}

void hash_code_scenario() {
    std::vector<my::string> strs = {
        "hello",
        "hello",
        "hella",
    };
    for (my::string &str : strs) {
        print_hash(str);
    }
}

void linked_map_scenario() {
    my::linked_map<double> map;
    my::string key = "hello";
    map.insert(key, 2);
    std::cout << key << " : " << map.get(key) << std::endl;
}

int main() {
    hash_code_scenario();
}