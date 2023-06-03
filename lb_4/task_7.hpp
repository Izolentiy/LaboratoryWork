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
  size_t ws = 0; // word start
  size_t we = 0; // word end
  size_t wl = 0; // word length
  bool pil = false; // previous is letter

  for (size_t i = 0; i < src.size(); ++i) {
    if (my::is_letter(src[i])) {
      if (!pil) ws = i;
      ++wl;
      pil = true;
    } else {
      if (wl > 0) {
        tem.clear();
        we = ws + wl;
        while (ws < we)
          tem.push_back(src[ws++]);
        // сравниваем слово со словами из списка
        // если находим отличающееся на один символ записываем
        // слово из списка вместо текущего слова
        bool write_init = true;
        for (int j = 0; j < 4; ++j) {
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
      wl = 0;
      pil = false;
    }
  }
  
}