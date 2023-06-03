#pragma once
#include <fstream>
#include <iostream>
#include <string>

#include "str_utils.h"
#include "task_typedefs.h"

namespace task_3 {
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
 * Дан текст. Сформировать строку из символов, расположенных между
 * первой и второй запятыми данного текста.
 */
void task_3::subtask_1(std::ifstream &fin, std::ofstream &fout) {
  using std::string;
  string str;
  size_t fc = 0, sc = 0;

  fin.seekg(0, std::ios::end);
  str.resize(fin.tellg());
  fin.seekg(0, std::ios::beg);
  fin.read(&str[0], str.size());
  fin.read(&str[0], str.size());
  try {
    fc = str.find(','); // поиск позиции первой запятой
    if (fc == string::npos) return;

    str = str.substr(fc+1, str.size() - fc);
    
    sc = str.find(','); // поиск позиции второй запятой
    if (sc == string::npos) return;
    
    fout << str.substr(0, sc);
  } catch (const std::out_of_range& ex) {
    std::cout << "Out of range\n";
  }
}

void task_3::subtask_2(std::ifstream &fin, std::ofstream &fout) {}
void task_3::subtask_3(std::ifstream &fin, std::ofstream &fout) {}
void task_3::subtask_4(std::ifstream &fin, std::ofstream &fout) {}

/**
 * Даны две строки. Определите, можно ли из некоторых символов
 * первой строки и всех символов второй строки составить новую строку,
 * в которой каждый символ встречается ровно два раза.
 */
void task_3::subtask_5(std::ifstream &fin, std::ofstream &fout) {
  using std::string;
  string str_1, str_2, str_2_p;
  size_t c = 0;

  if (!std::getline(fin, str_1)) return;
  if (!std::getline(fin, str_2)) return; // no second line
  str_2_p.append(str_2);

  // Анализ второй строки:
  // поиск символов встречающихся более 2 раз
  // удаление символов встречающихся 2 раза
  for (size_t i = 0; i < str_2.size(); ++i) {
    c = my::count(&str_2[0], str_2[i]);
    if (c == 2)
      my::remove_all(&str_2_p[0], str_2[i]);
    else
    if (c > 2) {
      fout << "Impossible";
      return;
    }
  }

  // Для каждого символа встречающегося 1 раз во второй строке
  // анализ первой строки на наличие хотя бы одного такого же.
  size_t l = my::str_len(&str_2_p[0]);
  for (size_t i = 0; i < l; ++i) {
    c = my::count(&str_1[0], str_2_p[i]);
    if (c == 0) {
      fout << "-_- Impossible";
      return;
    }
  }
  fout << "Possible!";
}