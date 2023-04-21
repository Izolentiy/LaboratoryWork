#pragma once
#include <fstream>
#include <stdint.h>

typedef void (*subtask_t) (std::ifstream &, std::ofstream &);
typedef subtask_t *task_t;


// Легче, и наверное лучше, все же просто следить за тем, что будут объявлены
// все функции подзадач и добавлены в соответствующие массивы
struct subtask_w {
  uint8_t id; // закодированный номер задачи
  subtask_t tptr; // указатель на функцию, в которой реализована логика задачи
}; // subtask wrapper