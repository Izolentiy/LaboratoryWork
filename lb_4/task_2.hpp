#pragma once
#include <fstream>
#include <iostream>

#include "char_set.h"

typedef void (*subtask_t) (std::ifstream &, std::ofstream &);

namespace task_2 {
  void subtask_1(std::ifstream &, std::ofstream &);
  void subtask_2(std::ifstream &, std::ofstream &);
  
  subtask_t subtasks[] = {
    subtask_1, subtask_2
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
  while (sym != EOF || sym != '\n') {
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