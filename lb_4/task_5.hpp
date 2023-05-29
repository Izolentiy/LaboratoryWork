#pragma once
#include <fstream>
#include <iostream>

#include "task_typedefs.h"

namespace task_5 {
  void subtask_1(std::ifstream &, std::ofstream &);
  
  subtask_t subtasks[] = {
    subtask_1
  };
}

/**
 * Дана строка. Вставить после каждого символа пробел.
 */
void task_5::subtask_1(std::ifstream &fin, std::ofstream &fout) {
  std::string src, res;
  if (!getline(fin, src)) return;

  for (size_t i = 0; i < src.size(); ++i) {
    res.push_back(src[i]);
    res.push_back(' ');
  }
  fout << res;
}