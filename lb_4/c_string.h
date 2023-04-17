#pragma once
#include <stdint.h>

namespace my {
  class string;
}

class my::string {
public:
  string(uint16_t); // принимает size не считая нуль-терминатора
  char* as_cstring();
  char* as_new_cstring();
  string& operator + (const char *);
  string& operator + (char);
  string& operator + (int);
  void clear();
  ~string();

private:
  uint16_t size; // max size == UINT16_MAX - 1
  uint16_t i_nt = 0; // index of '\0'
  char *data = nullptr;
};