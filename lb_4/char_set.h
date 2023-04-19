#pragma once
#include <stdint.h>

namespace my {
  class char_set; // множество символов
}

class my::char_set {
public:
  char_set(uint16_t);
  ~char_set();
  void add(char);
  int16_t search(char);
  bool contains(char);

private:
  char *data;
  uint16_t elem_count = 0;
  uint16_t size = 0;
};