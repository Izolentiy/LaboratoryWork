#include <cmath>

#include "str_utils.h"

bool my::str_cmp(char *s_1, const char *s_2) {
  for (size_t i = 0; s_1[i] == s_2[i]; ++i) {
    if (s_1[i] == '\0') return true;
  }
  return false;
}

size_t my::str_len(char *s) {
  size_t i = 0;
  while (s[i] != '\0') ++i;
  return i;
}

size_t my::count(char *s, char c) {
  size_t r = 0;
  for (size_t i = 0; s[i] != '\0'; ++i) {
    if (s[i] == c) ++r;
  }
  return r;
}

/**
 * Удаление символа из строки (нужно подумать над улучшением алгоритма)
 */
void my::remove_all(char *s, char c) {
  size_t l = str_len(s);
  size_t i = l, j = 0;
  do {
    if (s[i] == c) {
      j = i;
      do s[j] = s[j+1];
      while (s[j++] != '\0');
    }
  } while (i-- > 0);
}



bool my::is_digit(char ch) {
  if ('0' <= ch && ch <= '9') return true;
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
  if (is_neg) res = ~res + 1;
  return res;
}