#pragma once
#include <stdint.h>

namespace my {
    bool str_cmp(const char *s1, const char *s2);
    size_t str_len(const char *str);
    size_t count(char*, char);
    size_t count_diff(const char*, const char*);
    void remove_all(char *, char);
    void remove(char *, char *);

    bool is_digit(char);
    bool is_letter(char);
    bool is_vowel(char); // гласная
    int32_t parse_from_str(char *, bool, uint8_t);
}