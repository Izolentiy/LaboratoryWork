#pragma once
#include <fstream>
#include <filesystem>

#include "c_string.h"
#include "task_typedefs.h"
#include "task_1.hpp"
#include "task_2.hpp"
#include "task_3.hpp"
#include "task_4.hpp"
#include "task_5.hpp"
#include "task_6.hpp"
#include "task_7.hpp"

task_t tasks[] = {
  task_1::subtasks, task_2::subtasks, task_3::subtasks,
  task_4::subtasks, task_5::subtasks, task_6::subtasks,
  task_7::subtasks
};

char *input_filename(my::string&, uint8_t, uint8_t);
char *output_filename(my::string&, uint8_t, uint8_t);

void run_task(char *tn_s) {
  // extract task and subtask numbers from string
  // run_task(tn, stn);
}

void run_task(uint8_t tn, uint8_t stn) {
  static my::string fname(64);
  static std::ifstream fin;
  static std::ofstream fout;

  fin.open(input_filename(fname, tn, stn));
  fout.open(output_filename(fname, tn, stn));

  std::cout.clear();
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