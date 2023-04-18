#pragma once
#include <fstream>
#include <filesystem>

#include "c_string.h"
#include "task_1.hpp"
#include "task_2.hpp"

typedef subtask_t *task_t;
task_t tasks[] = { task_1::subtasks, task_2::subtasks };

char *input_filename(my::string&, uint8_t, uint8_t);
char *output_filename(my::string&, uint8_t, uint8_t);

void run_task(uint8_t tn, uint8_t stn) {
  static my::string fname(64);
  static std::ifstream fin;
  static std::ofstream fout;

  fin.open(input_filename(fname, tn, stn));
  fout.open(output_filename(fname, tn, stn));

  std::cout << "### Task " << (int)tn << '.' << (int)stn << " ###\n";

  if (fin.is_open() && fout.is_open()) {
    (tasks[tn-1][stn-1]) (fin, fout); // Запуск задачи
  } else {
    std::cout << "Unable to open one of the files\n";
  }

  fin.close();
  fout.close();
}

char *input_filename(my::string& fname, uint8_t tn, uint8_t stn) {
  fname.clear();
  fname + "input\\task_" + tn + "\\in_" + tn + '_' + stn + ".txt";
  return fname.as_cstring();
}

char *output_filename(my::string& fname, uint8_t tn, uint8_t stn) {
  fname.clear();
  fname + "output\\task_" + tn + "\\out_" + tn + '_' + stn + ".txt";
  return fname.as_cstring();
}