#pragma once
#include "str_utils.h"
#include "map.h"
#include <vector>
#include <bitset>
#include <ostream>
#include <iostream>

namespace my {
    class string;
    std::ostream &operator<<(std::ostream &out, const my::string &str);
}

class my::string {
  public:
    string();
    string(const char *str);
    string(const my::string &other);
    char *as_cstring() const;
    char *as_new_cstring() const;
    bool operator==(const my::string &other);
    string &operator+(const my::string &other);
    string &operator+(const char *str);
    string &operator+(char ch);
    string &operator+(int num);
    uint32_t hash_code();
    void clear();
    linked_map<int> unique_words();
    size_t count(const char *str);
    size_t find(const char *str);
    size_t get_size() const;
    size_t get_length() const;
    ~string();

    static const size_t npos = SIZE_MAX; // special index

  private:
    size_t size;     // array length
    size_t i_nt = 0; // index of '\0'
    char *data = nullptr;

    static const uint8_t ADD_CHUNK = 8;
  
    void xor_helper(uint32_t &hash, int bound, char *&pcb);
    void resize(size_t new_size);
    void resize_to_fit(const char *str);
    void resize_to_fit(size_t char_count);
    char* substring(size_t start, size_t end) const;
    size_t find(size_t start, size_t len, const char *str);
};