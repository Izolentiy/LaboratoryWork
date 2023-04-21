#pragma once
#include <fstream>
#include <iostream>
#include <string>

#include "task_typedefs.h"

namespace task_4 {
  void subtask_1(std::ifstream &, std::ofstream &);

  subtask_t subtasks[] = {
    subtask_1
  };
}

/**
 * Даны две строки. Удалить в первой строке первое вхождение второй строки.
 */
void task_4::subtask_1(std::ifstream &fin, std::ofstream &fout) {
  std::string str_1, str_2;

  if (!getline(fin, str_1)) return;
  if (!getline(fin, str_2)) return; // не оказалось второй строки

  size_t pos = str_1.find(str_2, 0);
  if (pos == std::string::npos) {
    fout << "Unable to fit second line in first";
    return;
  }

  size_t pos_e = str_1.length();
  size_t pos_s = pos + str_2.length();
  std::cout << str_1.substr(0, pos) << " " << str_1.substr(pos_s, pos_e);
  str_1 = str_1.substr(0, pos) + str_1.substr(pos_s, pos_e);
  fout << str_1;
}