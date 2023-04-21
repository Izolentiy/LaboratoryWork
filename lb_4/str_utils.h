#pragma once
#include <stdint.h>

namespace my {
  bool str_cmp(char*, const char*);
  size_t str_len(char *);
  size_t count(char*, char);
  void remove_all(char *, char);

  bool is_digit(char);
  int32_t parse_from_str(char *, bool, uint8_t);
}