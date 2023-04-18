#pragma once
#include <stdint.h>

bool str_cmp(char *s_1, const char *s_2) {
  for (size_t i = 0; s_1[i] == s_2[i]; ++i) {
    if (s_1[i] == '\0') return true;
  }
  return false;
}

size_t str_len(char *s) {
  size_t i = 0;
  while (s[i] != '\0') ++i;
  return i;
}