#include "str_utils.h"
#include <cmath>

bool my::str_cmp(const char *s_1, const char *s_2) {
    for (size_t i = 0; s_1[i] == s_2[i]; ++i) {
        if (s_1[i] == '\0')
            return true;
    }
    return false;
}

/**
 * @return length of c_string including '\0'
 */
size_t my::str_size(const char *s) {
    size_t i = 0;
    while (s[i++] != '\0');
    return i;
}

size_t my::count(const char *s, const char c) {
    size_t r = 0;
    for (size_t i = 0; s[i] != '\0'; ++i) {
        if (s[i] == c)
            ++r;
    }
    return r;
}

size_t my::count_diff(const char *str_1, const char *str_2) {
    size_t i = 0, diffs = 0;
    while (str_1[i] != '\0') {
        if (str_2[i] == '\0') {
            do {
                ++i;
                ++diffs;
            } while (str_1[i] != '\0');
            return diffs;
        }
        if (str_1[i] != str_2[i])
            ++diffs;
        ++i;
    }
    while (str_2[i] != '\0') {
        ++i;
        ++diffs;
    }
    return diffs;
}

void my::remove_all(char *s, char c) {
    size_t l = str_size(s);
    size_t i = l, j = 0;
    do {
        if (s[i] == c) {
            j = i;
            do
                s[j] = s[j + 1];
            while (s[j++] != '\0');
        }
    } while (i-- > 0);
}


bool my::is_digit(char ch) {
    if ('0' <= ch && ch <= '9')
        return true;
    return false;
}

bool my::is_letter(char ch) {
    bool is_low = 'a' <= ch && ch <= 'z';
    bool is_up = 'A' <= ch && ch <= 'Z';
    if (is_low || is_up)
        return true;
    return false;
}

bool my::is_vowel(char ch) {
    const char vowels[] = "aeiou";
    for (uint8_t i = 0; vowels[i] != '\0'; ++i) {
        if (vowels[i] == ch)
            return true;
    }
    return false;
}

/**
 * 12345 =
 * 10000 +
 *  2000 +
 *   300 +
 *    40 +
 *     5
 * digit_count = 5 // dc
 */
int32_t my::parse_from_str(char *str, bool is_neg, uint8_t dc) {
    int32_t res = 0;
    uint8_t cur = 0;
    for (uint8_t i = 0; str[i] != '\0'; ++i) {
        cur = str[i] - '0';
        res += cur * std::pow(10, --dc);
    }
    if (is_neg)
        res = ~res + 1;
    return res;
}