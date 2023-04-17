#pragma once
#include <fstream>
#include <filesystem>

#include "c_string.h"
#include "task_1.hpp"
#include "task_2.hpp"

typedef subtask_t *task_t;
task_t tasks[] = { task_1::subtasks, task_2::subtasks };

void input_filename(my::string&, uint8_t, uint8_t);
void output_filename(my::string&, uint8_t, uint8_t);

void run_task(uint8_t tn, uint8_t stn) {
  using std::ifstream, std::ofstream;

  my::string fname(64);
  
  // Открытие файла для чтения
  input_filename(fname, tn, stn);
  ifstream fin(fname.as_cstring());

  // Открытие файла для записи
  output_filename(fname, tn, stn);
  ofstream fout(fname.as_cstring());

  std::cout << "### Task " << (int)tn << '.' << (int)stn << " ###\n";

  if (fin.is_open() && fout.is_open()) {
    (tasks[tn-1][stn-1]) (fin, fout); // Запуск задачи
  } else {
    std::cout << "Unable to open one of the files\n";
  }

  fin.close();
  fout.close();
}

void input_filename(my::string& fname, uint8_t tn, uint8_t stn) {
  fname.clear();
  fname + "input\\task_" + tn + "\\in_" + tn + '_' + stn + ".txt";
}

void output_filename(my::string& fname, uint8_t tn, uint8_t stn) {
  fname.clear();
  fname + "output\\task_" + tn + "\\out_" + tn + '_' + stn + ".txt";
}