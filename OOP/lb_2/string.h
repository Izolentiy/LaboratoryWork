#pragma once
#include "str_utils.h"
#include <ostream>
#include <iostream>

namespace my {
    class string;
    std::ostream &operator<<(std::ostream &out, const my::string &str);
}

class my::string {
  public:
    string(const char *str);
    string(const my::string &other);
    char *as_cstring() const;
    char *as_new_cstring() const;
    bool operator==(const my::string &other);
    uint32_t hash_code();
    string &operator+(const char *str);
    string &operator+(char ch);
    string &operator+(int num);
    void clear();
    ~string();

    size_t find(const char *ch);
    void print_unique_words();
    size_t count(const string &word);
    size_t npos = SIZE_MAX; // если строка не содержит подстроку

  private:
    size_t size;     // array length
    size_t i_nt = 0; // index of '\0'
    char *data = nullptr;
    void xor_helper(uint32_t &hash, int bound, char *&pcb);
};