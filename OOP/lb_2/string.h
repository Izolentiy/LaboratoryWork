#pragma once
#include "str_utils.h"
#include "map.h"
#include <vector>
#include <bitset>
#include <ostream>
#include <fstream>
#include <iostream>

namespace my {
    class string;
    std::ostream &operator<<(std::ostream &out, const my::string &str);
    void operator<<(const char *out, const my::string &str);
    void operator>>(const char *in, my::string &str);
}

class my::string {
    friend std::ostream &my::operator<<(std::ostream &out, const my::string &str);

  public:
    enum sort_type {
        alphabetic,
        by_order_in_text,
        by_count_in_text
    };
    static const size_t npos = SIZE_MAX; // not found index

    string();
    string(const char *str);
    string(const string &other);
    char *as_new_cstring() const;
    bool operator==(const string &other);
    bool operator>(const string &other);
    string &operator<<(const string &other);
    string &operator<<(const char *str);
    string &operator<<(char ch);
    string &operator<<(int num);
    string to_lower_case();
    uint32_t hash_code();
    void clear();
    linked_map<string, size_t> unique_words(sort_type sort = by_order_in_text);
    size_t count_any(const string &str);
    size_t count_isolated(const string &str);
    size_t find_any(const string &str);
    size_t find_isolated(const string &str);
    size_t get_size() const;
    size_t get_length() const;
    ~string();

  private:
    size_t size;     // array length
    size_t i_nt = 0; // index of '\0'
    char *data = nullptr;

    static const uint8_t ADD_CHUNK = 8;

    typedef size_t (my::string::*find_func)(size_t start, size_t len, const char *str);
  
    void xor_helper(uint32_t &hash, int bound, char *&pcb);
    void resize(size_t new_size);
    void resize_to_fit(const char *str);
    void resize_to_fit(size_t char_count);
    char* substring(size_t start, size_t end) const;
    size_t find_any(size_t start, size_t len, const char *str);
    size_t find_isolated(size_t start, size_t len, const char *str);
    size_t count_helper(const char *str, find_func find);
};