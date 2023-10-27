#include "hash.hpp"
#include "map.h"
#include "string.h"
#include <iostream>
#include <vector>

void hash_code_scenario();
void linked_map_scenario();
void string_find_scenario();
void string_resize_scenario();
void word_count_scenario();

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
    my::linked_map<my::string, double> map;
    my::string key = "hello";
    map.insert(key, 2);
    std::cout << key << " : " << map.get(key) << std::endl;
}

void string_find_scenario() {
    my::string str = "Hello, my friend! I hope you are happy and healthy";

    const char *to_find = "healthy";
    const char *to_count = "friend";
    size_t index = str.find(to_find);
    size_t count = str.count(to_count);

    std::cout << "count \"" << to_count << "\" : " << count << "\n"; 
    if (index == my::string::npos) {
        std::cout << "substring not found\n";
    } else {
        std::cout << "find \"" << to_find << "\" : " << index << "\n";
    }
}

void string_resize_scenario() {
    my::string str;
    
    std::cout << str << "\n";
    str + "biba" + " and " + "bob";
    std::cout << "\""<< str << "\" size : " << str.get_size() << "\n";
    std::cout << "\""<< str << "\" length : " << str.get_length() << "\n";

    str + 'a';
    std::cout << "\""<< str << "\" size : " << str.get_size() << "\n";
    std::cout << "\""<< str << "\" length : " << str.get_length() << "\n";

    str + 2;
    std::cout << "\""<< str << "\" size : " << str.get_size() << "\n";
    std::cout << "\""<< str << "\" length : " << str.get_length() << "\n";
}

void word_count_scenario() {
    my::string text = "Hello, everybody, my name is Maximillian and would like to say my name again.";
    std::cout << text << "\n\n";
    my::linked_map<my::string, int> result = text.unique_words();
    
    size_t size = result.get_size();
    std::cout << "Unique words : " << size << "\n";
    for (size_t i = 0; i < result.get_size(); ++i) {
        my::string key = result.get_key(i);
        int val = result.get(key);
        std::cout << key << " - " << val << "\n";
    }
}

int main() {
    // hash_code_scenario();
    // string_find_scenario();
    // string_resize_scenario();
    word_count_scenario();
}