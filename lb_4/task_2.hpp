#pragma once
#include <fstream>
#include <iostream>
#include <cmath>

#include "char_set.h"
#include "task_typedefs.h"

namespace task_2 {
  void subtask_1(std::ifstream &, std::ofstream &);
  void subtask_2(std::ifstream &, std::ofstream &);
  void subtask_3(std::ifstream &, std::ofstream &);
  void subtask_4(std::ifstream &, std::ofstream &);
  void subtask_5(std::ifstream &, std::ofstream &);

  bool is_digit(char);
  int32_t parse_from_str(char *, bool, uint8_t);
  
  subtask_t subtasks[] = {
    subtask_1, subtask_2, subtask_3, subtask_4, subtask_5
  };
}

/**
 * Удалить в строке все лишние пробелы, то есть серии подряд идущих
 * пробелов заменить на одиночные пробелы. Крайние пробелы в строке удалить
 */
void task_2::subtask_1(std::ifstream &fin, std::ofstream &fout) {
  char sym = fin.get(); // symbol

  while (sym == ' ') sym = fin.get();
  while (sym != EOF) {
    if (sym == ' ') {
      do sym = fin.get();
      while (sym == ' ');
      if (sym != EOF) fout << ' ';
      continue;
    }
    fout << sym;
    sym = fin.get();
  }

}

/**
 * Дана строка, состоящая из слов, разделенных символами, которые
 * перечислены во второй строке. Показать все слова.
 */
void task_2::subtask_2(std::ifstream &fin, std::ofstream &fout) {
  char sym = fin.get(); // symbol

  // Поиск начала второй строки
  while (sym != EOF) {
    if (sym == '\n') break;
    sym = fin.get();
  }

  if (fin.fail()) {
    std::cout << "Incorrect input\n";
    fout << "Incorrect input";
    return;
  }

  // Считывание разделителей из второй строки
  my::char_set delims(16);
  sym = fin.get();
  while (sym != EOF) {
    if (sym != '\n') break;
    delims.add(sym);
    sym = fin.get();
  }

  // Проход по первой строке с выводом слов
  fin.clear();
  fin.seekg(0, std::ios::beg);
  while ((sym = fin.get()) != '\n') {
    if (delims.contains(sym)) {
      fout << ' '; // для удобочитаемости
      continue;
    }
    fout << sym;
  }
}

void task_2::subtask_3(std::ifstream &fin, std::ofstream &fout) {}
void task_2::subtask_4(std::ifstream &fin, std::ofstream &fout) {}

/**
 * Дан текст. Найти слова, состоящие из цифр, 
 * и сумму чисел, которые образуют эти слова.
 */
void task_2::subtask_5(std::ifstream &fin, std::ofstream &fout) {
  char ch = fin.get();
  std::cout << "subtask 5 " << ch << "\n";

  int32_t num = 0;
  int64_t sum = 0;
  bool is_neg = false;
  char num_s[32] = "";
  uint8_t dc = 0; // digit count
  
  while (ch != EOF) {
    if (ch == '-') is_neg = true;
    else
    if (is_digit(ch)) {
      do num_s[dc++] = ch;
      while (is_digit(ch = fin.get()));
      num_s[dc] = '\0';

      num = parse_from_str(num_s, is_neg, dc);
      fout << num << ' ';
      sum += num;
      dc = 0; is_neg = false;
    }
    else is_neg = false;
    std::cout << ch;
    ch = fin.get();
  }
  fout << "\nSum = " << sum;
}

bool task_2::is_digit(char ch) {
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
int32_t task_2::parse_from_str(char *str, bool is_neg, uint8_t dc) {
  int32_t res = 0;
  uint8_t cur = 0;
  for (uint8_t i = 0; str[i] != '\0'; ++i) {
    cur = str[i] - '0';
    res += cur * std::pow(10, --dc);
  }
  if (is_neg) res = ~res + 1;
  return res;
}