#pragma once
#include "str_utils.h"
#include <ostream>

namespace my {
    class string;
    std::ostream &operator<<(std::ostream &out, const my::string &str);
}

class my::string {
    friend std::ostream &my::operator<<(std::ostream &out, const my::string &str);

  public:
    string(const char *str);
    string(const my::string &other);
    char *as_cstring() const;
    char *as_new_cstring() const;
    bool operator==(const my::string &other);
    string &operator+(const char *str);
    string &operator+(char ch);
    string &operator+(int num);
    void clear();
    ~string();

    size_t find(const char *ch);
    void print_unique_words();
    size_t count(const string &word);
    size_t npos = UINT16_MAX; // если строка не содержит подстроку

  private:
    size_t size;
    size_t i_nt = 0; // index of '\0'
    char *data = nullptr;
};