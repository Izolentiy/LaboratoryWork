#include "char_set.h"

/**
 * Так как этот класс хранит лишь множество символов
 * ASCII его размер не может быть больше 256
 */
my::char_set::char_set(uint16_t in_size) {
  if (in_size > 256) in_size = 256;
  data = new char[in_size];
  size = in_size;
}

my::char_set::~char_set() {
  delete[] data;
  data = nullptr;
}

/**
 * Не позволит добавить ещё один элемент, если 
 * их количество станет больше изначально заданного размера
 * Не позволит вставить дупликат
 */
void my::char_set::add(char ch) {
  if (elem_count + 1 > size) return;

  int16_t in_pos = search(ch);
  if (in_pos < 0) return; // ch уже есть

  for (int i = ++elem_count; i > in_pos; --i) {
    data[i] = data[i-1];
  }
  data[in_pos] = ch;
}

/**
 * Ищет позицию в которую необходимо вставить элемент
 * Возвращает -1 если элемент уже есть
 */
int16_t my::char_set::search(char ch) {
  if (elem_count == 0) return 0;

  uint16_t l = 0, m = 0, h = elem_count - 1;
  bool flag = false;

  while (true) {
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
  }
}

bool my::char_set::contains(char ch) {
  if (search(ch) < 0) return true;
  return false; // если не содержит
}