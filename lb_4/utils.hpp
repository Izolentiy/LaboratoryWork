#pragma once
#include <fstream>
#include "c_string.h"
#include "task_1.hpp"

typedef subtask_t *task_t;
task_t tasks[] = { task_1 };

void run_task(uint8_t tn, uint8_t stn) {
  my::string fname(64);
  fname + "input\\task_" + tn + "\\sub_" + stn + ".txt";
  std::ifstream fin(fname.as_cstring()); // Открытие файла для чтения

  fname.clear();
  fname + "output\\task_" + tn + "\\sub_" + stn + ".txt";
  std::ofstream fout(fname.as_cstring()); // Открытие файла для записи

  std::cout << "### Task " << (int)tn << '.' << (int)stn << " ###\n";

  if (fin.is_open() && fout.is_open())
    (tasks[tn-1][stn-1]) (fin, fout); // Запуск задачи
  else std::cout << "Unable to open one of the files" << std::endl;

  fin.close();
  fout.close();
}