#pragma once
#include <fstream>
#include <iostream>
#include <math.h>

#include "task_typedefs.h"
#include "str_utils.h"

namespace task_7 {
  void subtask_1(std::ifstream &, std::ofstream &);
  void subtask_2(std::ifstream &, std::ofstream &);
  void subtask_3(std::ifstream &, std::ofstream &);
  void subtask_4(std::ifstream &, std::ofstream &);
  
  subtask_t subtasks[] = {
    subtask_1, subtask_2, subtask_3, subtask_4
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
  const char* words[] = {
    "apple", "pineapple",
    "pen", "banana",
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
        // если находим отличающееся на один символ, записываем
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

void task_7::subtask_2(std::ifstream &, std::ofstream &) {}
void task_7::subtask_3(std::ifstream &, std::ofstream &) {}

/**
 * Дан текст. Заменить все вхождения наибольшей цифры ее словесным написанием.
 */
void task_7::subtask_4(std::ifstream &fin, std::ofstream &fout) {
  std::string txt, str;

  // считываем текст построчно
  while (getline(fin, str)) {
    txt += str;
  }

  // поиск максимальной цифры
  char max_dig = '0' - 1; // maximum digit
  for (size_t i = 0; i < txt.size(); ++i) {
    // это проверка, является текущий символ цифрой
    if ('0' <= txt[i] && txt[i] <= '9') {
      max_dig = std::max(txt[i], max_dig);
    }
  }

  // словесное представление макс. цифры
  std::string max_dig_str;

  switch(max_dig) {
  case '0': max_dig_str = "zero"; break;
  case '1': max_dig_str = "one"; break;
  case '2': max_dig_str = "two"; break;
  case '3': max_dig_str = "three"; break;
  case '4': max_dig_str = "four"; break;
  case '5': max_dig_str = "five"; break;
  case '6': max_dig_str = "six"; break;
  case '7': max_dig_str = "seven"; break;
  case '8': max_dig_str = "eight"; break;
  case '9': max_dig_str = "nine"; break;
  default: fout << txt;
  }

  for (size_t i = 0; i < txt.size(); ++i) {
    if (txt[i] == max_dig) fout << max_dig_str;
    else fout << txt[i];
  }

}