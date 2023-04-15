#pragma once
#include <fstream>
#include <iostream>

void subtask_1(std::ifstream &fin, std::ofstream &fout) {
  uint32_t i = 0;
  for (char c = fin.get(); c != EOF; c = fin.get(), ++i) {
    fout << c << '.';
  }
}
void subtask_2(std::ifstream &fin, std::ofstream &fout) {}
void subtask_3(std::ifstream &fin, std::ofstream &fout) {}
void subtask_4(std::ifstream &fin, std::ofstream &fout) {}
void subtask_5(std::ifstream &fin, std::ofstream &fout) {}

typedef void (*subtask_t) (std::ifstream &, std::ofstream &);
subtask_t task_1[] = {
  subtask_1, subtask_2, subtask_3, subtask_4, subtask_5
};