#pragma once
#include <fstream>
#include <iostream>

#include "task_typedefs.h"

namespace task_6 {
  void subtask_1(std::ifstream &, std::ofstream &);
  
  subtask_t subtasks[] = {
    subtask_1
  };
}

// expression -> term -> factor -> number
int expression(std::ifstream &fin);
int term(std::ifstream &fin);
int factor(std::ifstream &fin);
int number(std::ifstream &fin);

/**
 * Дана строка, которая содержит натуральные числа, знаки четырех 
 * арифметических действий (сложение, вычитание, умножение, деление)
 * и скобки. Вычислите значение выражения.
 */
void task_6::subtask_1(std::ifstream &fin, std::ofstream &fout) {
  // (12*2)/3
  // формат ввода: пробелы не допускаются, ожидается только корректное выражение
  fout << expression(fin);
}

// Убывание приоритета операции
// 0. интерпретация числа
// 1. -() унарный минус и скобки
// 2. /* умножение и деление
// 3. +- плюс и минус

/**
 * Число
 */
int number(std::ifstream &fin) {
  int result = fin.get() - '0';
  while (fin.peek() >= '0' && fin.peek() <= '9') {
    result = 10*result + fin.get() - '0';
  }
  return result;
}

/**
 * Множитель
 */
int factor(std::ifstream &fin) {
  if (fin.peek() >= '0' && fin.peek() <= '9')
    return number(fin);
  else if (fin.peek() == '(') {
    fin.get(); // '('
    int result = expression(fin);
    fin.get(); // ')'
    return result;
  }
  else if (fin.peek() == '-') {
    fin.get();
    return -factor(fin);
  }
  return 0; // встретился неитрепритируемый символ
}

/**
 * Слагаемое
 */
int term(std::ifstream &fin) {
  int result = factor(fin);
  while (fin.peek() == '*' || fin.peek() == '/')
    if (fin.get() == '*')
      result *= factor(fin);
    else
      result /= factor(fin);
  return result;
}

/**
 * Выражение
 */
int expression(std::ifstream &fin) {
  int result = term(fin);
  while (fin.peek() == '+' || fin.peek() == '-')
    if (fin.get() == '+')
      result += term(fin);
    else
      result -= term(fin);
  return result;
}