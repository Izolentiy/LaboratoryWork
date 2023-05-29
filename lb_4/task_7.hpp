#pragma once
#include <fstream>
#include <iostream>

#include "task_typedefs.h"
#include "str_utils.h"

namespace task_7 {
  void subtask_1(std::ifstream &, std::ofstream &);
  
  subtask_t subtasks[] = {
    subtask_1
  };
}

/**
 * Дан текст и список слов. Найти в тексте все слова, каждое из которых
 * отличается от некоторого слова из списка одной буквой, и исправить
 * такие слова на слова из списка.
 */
void task_7::subtask_1(std::ifstream &fin, std::ofstream &fout) {
  using std::string;
  string src, tem, res;

  // список слов
  char* words[] = {
    "apple",
    "pineapple",
    "pen",
    "banana",
  };
  
  // считываем текст в string
  while(getline(fin, tem)) {
    src += tem;
  }

  // анализируем текст
  // извлекаем отдельные слова из текста
  size_t i = 0, ws = 0, we = 0; // index, word start, word end

  while (i < src.size()) {
    if (my::is_letter(src[i])) {
      if (we >= ws) ws = i;
    } else {
      if (we < ws) {
        we = i;
        tem.clear();
        while (ws < we)
          tem.push_back(src[ws++]);
        // сравниваем слово со словами из списка
        bool write_init = true;
        for (int j = 0; j < 4; ++j) {
          // std::cout << &tem[0] << ' ' << words[j] << "\n";
          // std::cout << "diff count " << my::count_diff(words[j], &tem[0]) << "\n";
          // std::cout << my::str_len(&tem[0]) << " " << my::str_len(words[j]) << "\n";
          if (my::count_diff(words[j], &tem[0]) == 1) {
            fout << words[j] << ' ';
            write_init = false;
            break;
          }
        }
        if (write_init) {
          fout << tem << ' ';
        }
      } else {
        fout << src[i];
      }
    }
    ++i;
  }
  
}