#include "c_string.h"

my::string::string(uint16_t size) {
  if (size == UINT16_MAX) --size;
  data = new char[size+1];
  this -> size = size;
}

/**
 * !Память будет очищена после вызова деструктора!
 * Если нужен экз
 */
char *my::string::as_cstring() {
  return data;
}

char *my::string::as_new_cstring() {
  char *copy = new char[i_nt+1];
  for (uint16_t i = 0; i < i_nt+1; ++i)
    copy[i] = data[i];
  return copy;
}

my::string& my::string::operator + (const char *other){
  uint16_t j = -1;
  while (other[++j] != '\0') {
    data[i_nt + j] = other[j];
  }
  data[i_nt += j] = '\0';
  return *this;
}

my::string &my::string::operator+(int num){
  uint8_t dc = 0; // digit count - 1
  if (num < 0) {
    num = ~num + 1;
    data[i_nt++] = '-';
  }
  if (num == 0) dc = 0;
  else dc = log10(num);

  for (int i = i_nt + dc; i >= i_nt; --i, num /= 10) {
      data[i] = (num % 10) + '0';
  }
  data[i_nt += dc+1] = '\0';
  return *this;
}

my::string::~string() {
  delete[] data;
}

my::string& my::string::operator+(char ch){
  data[i_nt] = ch;
  data[++i_nt] = '\0';
  return *this;
}

void my::string::clear(){
  data[i_nt = 0] = '\0';
}