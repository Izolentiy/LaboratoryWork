#pragma once
#include <fstream>
#include <iostream>

typedef void (*subtask_t) (std::ifstream &, std::ofstream &);

namespace task_6 {
  void subtask_1(std::ifstream &, std::ofstream &);

  char peek();
  char get();
  
  int expression();
  int term();
  int number();
  int factor();
  
  subtask_t subtasks[] = {
    subtask_1
  };
}

char *expr; // указатель хранящий 

/**
 * Дана строка, которая содержит натуральные числа, знаки четырех 
 * арифметических действий (сложение, вычитание, умножение, деление)
 * и скобки. Вычислите значение выражения.
 */
void task_6::subtask_1(std::ifstream &fin, std::ofstream &fout) {
  // (12*2)/3
  // формат ввода: пробелы не допускаются, ожидается только корректное выражение
  std::string in;
  if (!getline(fin, in)) return;
  expr = &in[0];
  fout << expression();
}

char task_6::peek() {
  return *expr;
}

char task_6::get() {
  return *expr++; // получаем то что лежит по текущему значению указателя и увеличиваем
}

// Убывание приоритета операции
// 1. -()
// 2. /*
// 3. +-

int task_6::number() {
  int result = get() - '0';
  while (peek() >= '0' && peek() <= '9') {
    result = 10*result + get() - '0';
  }
  return result;
}

int task_6::factor() {
  if (peek() >= '0' && peek() <= '9')
    return number();
  else if (peek() == '(') {
    get(); // '('
    int result = expression();
    get(); // ')'
    return result;
  }
  else if (peek() == '-') {
    get();
    return -factor();
  }
  return 0; // встретился нуль терминатор
}

int task_6::term() {
  int result = factor();
  while (peek() == '*' || peek() == '/')
    if (get() == '*')
      result *= factor();
    else
      result /= factor();
  return result;
}

int task_6::expression() {
  int result = term();
  while (peek() == '+' || peek() == '-')
    if (get() == '+')
      result += term();
    else
      result -= term();
  return result;
}