#include "c_string.h"
#include <iostream>

#define STR_MAX_LEN 32

void c_string_test() {
    // размер сообщения максимум 19 символов, включая '\n'. Не считая '\0'
    my::string str(STR_MAX_LEN);
    uint8_t val = 22;
    uint8_t r = 255, g = 255, b = 255;

    // Построение сообщения
    str + val + " : " + r + ' ' + g + ' ' + b + '\n';
    char* msg = str.as_cstring();

    std::cout << msg;

    str.clear();
    str + ":)";
    std::cout << str.as_cstring() << std::endl;

    int signed_val = -1245;
    r = 0; g = 0; b = 0;

    str.clear();
    str + signed_val + " : " + r + ' ' + g + ' ' + b;
    std::cout << str.as_cstring();
}

void f1(int n) {}
void f2(int n) {}
void f3(int n) {}

void (*func_arr[]) (int) = { f1, f2, f3 };

typedef void (*func_t) (int);
func_t func_arr_2[] = { f1, f2, f3 };

void array_of_functions() {
    (*func_arr[0])(1);
}

// data = {0, 2, 6, 8, 9}
// ch = 1;
// ### 1
// {0, 2, 6, 8, 9}
//  ^     ^     ^
//  l     m     h
// {0, 2, 6, 8, 9}
//  ^     ^     ^
//  l     m     h
// ### 2
// {0, 2, 6, 8, 9}
//  ^  ^  ^
//  l  m  h 
// ### 3
// {0, 2, 6, 8, 9}
//  ^  ^
//  m  h

// data = {0, 2, 6, 8, 9}
// ch = 10;
// ### 1
// {0, 2, 6, 8, 9}
//  ^     ^     ^
//  l     m     h
// ### 2
// {0, 2, 6, 8, 9}
//        ^  ^  ^
//        l  m  h
// ### 3
// {0, 2, 6, 8, 9}
//           ^  ^
//           l  h

char data[64];
uint16_t elem_count = 0;
int8_t sym = 1;

// Ищет позицию в которую необходимо вставить элемент
int16_t search(int8_t ch) {
  int16_t l = 0, m = 0, h = elem_count-1;
  if (elem_count == 0) return 0;
  bool flag = false;
  do {
    m = (l+h) / 2;
    if (ch > data[m]) {
      if (flag)
        if (ch > data[h]) return h+1;
        else
        if (ch < data[h]) return h;
        else return -1;
      l = m;
    }
    else
    if (ch < data[m]) {
      if (flag) return 0;
      h = m;
    }
    else return -1;

    if (h-l <= 1) flag = true;
  } while (true);
}

void add(int8_t ch) {
  int16_t in_pos = search(ch);
  if (in_pos < 0) return; // ch уже есть
  for (int i = ++elem_count; i > in_pos; --i) {
    data[i] = data[i-1];
  }
  data[in_pos] = ch;
}

void search_test() {
    add(','); std::cout << (int)',' << ",\n";
    add('_'); std::cout << (int)'_' << "_\n";

    add('-'); std::cout << (int)'-' << "-\n";
    add('-'); std::cout << (int)'-' << "-\n";
    add('-'); std::cout << (int)'-' << "-\n";
    add('+'); std::cout << (int)'+' << "+\n";

    
    data[7] = '\0';
    std::cout << elem_count << ' ' << data << '\n';
}

void bit_field_test() {
  struct {
    int32_t size;
    int16_t num;
    int16_t id;
    uint8_t signal_1;
    uint8_t signal_2;
  } struct_1; // правильное расположение по адресам

  struct struct_t {
    uint8_t signal_1;
    int32_t size;
    uint8_t signal_2;
    int16_t id;
    int16_t num;
  }; // неправильное расположение по адресам

  struct bit_field_t {
    uint32_t year: 16; // 65536
    uint32_t month: 4; // 16
    uint32_t day: 5; // 32
  } calendar;

  std::cout << "struct 1: " << sizeof(struct_1) << '\n';
  std::cout << "struct 2: " << sizeof(struct_t) << '\n';
  std::cout << "calendar: " << sizeof(calendar) << '\n';
}

int main() {
    // search_test();
    // c_string_test();
    bit_field_test();
}