#include "string.h"
#include "map.h"
#include <iostream>

int main() {
    my::linked_map<double> map;
    my::string key = "hello";
    map.insert(key, 2);
    std::cout << key << " : " << map.get(key) << std::endl;
}