#pragma once
#include <fstream>
#include <iostream>
#include <cmath>

#include "char_set.h"
#include "task_typedefs.h"
#include "str_utils.h"

namespace task_2 {
  void subtask_1(std::ifstream &, std::ofstream &);
  void subtask_2(std::ifstream &, std::ofstream &);
  void subtask_3(std::ifstream &, std::ofstream &);
  void subtask_4(std::ifstream &, std::ofstream &);
  void subtask_5(std::ifstream &, std::ofstream &);
  
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
  using namespace my;
  char ch = fin.get();

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
    ch = fin.get();
  }
  fout << "\nSum = " << sum;
}