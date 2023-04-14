#pragma once
#include <stdint.h>
#include <cmath>

namespace my {
  class string;
}

class my::string {
public:
  string(uint16_t s); // s не считая нуль-терминатора
  char* as_cstring();
  string& operator + (const char *other);
  string& operator + (char ch);
  string& operator + (uint8_t num);
  void clear();
  ~string();

private:
  uint16_t size; // max size == UINT16_MAX - 1
  uint16_t i_nt = 0; // index of '\0'
  char *data = nullptr;
};

// Implementation

my::string::string(uint16_t size) {
  if (size == UINT16_MAX) --size;
  data = new char[size+1];
  this -> size = size;
}

char *my::string::as_cstring() {
  return data;
}

my::string& my::string::operator + (const char *other){
  uint16_t j = -1;
  while (other[++j] != '\0') {
    data[i_nt + j] = other[j];
  }
  data[i_nt += j+1] = '\0';
  return *this;
}

my::string& my::string::operator + (uint8_t num){
  uint8_t dc = 0; // digit count
  if (num != 0) {
    dc = log10(num);
  }

  for (int i = i_nt + dc; i >= i_nt; --i, num /= 10) {
      data[i] = (num % 10) + '0';
  }
  data[i_nt += dc+1] = '\0';
  return *this;
}

my::string::~string() {
  delete [] data;
  data = nullptr;
}

my::string& my::string::operator+(char ch){
  data[i_nt] = ch;
  data[++i_nt] = '\0';
  return *this;
}

void my::string::clear(){
  data[0] = '\0';
}