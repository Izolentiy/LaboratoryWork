#pragma once
#include <fstream>
#include <iostream>

#include "str_utils.hpp"

typedef void (*subtask_t) (std::ifstream &, std::ofstream &);

namespace task_1 {
  void subtask_1(std::ifstream &, std::ofstream &);
  // void subtask_2(std::ifstream &, std::ofstream &);
  // void subtask_3(std::ifstream &, std::ofstream &);
  // void subtask_4(std::ifstream &, std::ofstream &);
  // void subtask_5(std::ifstream &, std::ofstream &);
  
  subtask_t subtasks[] = {
    subtask_1
    // subtask_1, subtask_2, subtask_3, subtask_4, subtask_5
  };
}

/**
 * Дана строка. Если она начинается на 'abc', то заменить
 * их на 'www', иначе добавить в конец строки 'zzz'.
 */
void task_1::subtask_1(std::ifstream &fin, std::ofstream &fout) {
  char start[4] = "";

  fin.read(start, 3);
  fout << start;

  char ch = fin.get();
  while (ch != EOF) {
    fout << ch;
    ch = fin.get();
  }

  if (str_cmp(start, "abc")) {
    fout.seekp(std::ios::beg);
    fout.write("www", 3);
  }
  else fout << "zzz";
}