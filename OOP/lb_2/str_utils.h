#pragma once
#include <stdint.h>

namespace my {
    bool str_cmp(const char *s1, const char *s2);
    size_t str_size(const char *str);
    size_t count(const char *s, const char c);
    size_t count_diff(const char *s1, const char *s2);
    void remove_all(char *s, char c);

    bool is_digit(char ch);
    bool is_letter(char ch);
    bool is_vowel(char ch); // гласная
    int32_t parse_from_str(char *, bool, uint8_t);
}