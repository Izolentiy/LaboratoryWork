#pragma once
#include <fstream>
#include <iostream>
#include <random>

#include "str_utils.hpp"

typedef void (*subtask_t) (std::ifstream &, std::ofstream &);

namespace task_1 {
  void subtask_1(std::ifstream &, std::ofstream &);
  void subtask_2(std::ifstream &, std::ofstream &);
  void subtask_3(std::ifstream &, std::ofstream &);
  // void subtask_4(std::ifstream &, std::ofstream &);
  // void subtask_5(std::ifstream &, std::ofstream &);
  
  subtask_t subtasks[] = {
    subtask_1, subtask_2, subtask_3
    // subtask_1, subtask_2, subtask_3, subtask_4, subtask_5
  };
}

/**
 * Дана строка. Если она начинается на 'abc', то заменить
 * их на 'www', иначе добавить в конец строки 'zzz'.
 */
void task_1::subtask_1(std::ifstream &fin, std::ofstream &fout) {
  char start[4] = "";

  fin.read(start, 3);
  fout << start;

  char ch = fin.get();
  while (ch != EOF) {
    fout << ch;
    ch = fin.get();
  }

  if (str_cmp(start, "abc")) {
    fout.seekp(std::ios::beg);
    fout.write("www", 3);
  }
  else fout << "zzz";
}

/**
 * Дана строка. Если ее длина больше 10, то оставить в строке только
 * первые 6 символов, иначе дополнить строку символами 'o' до длины 12.
 */
void task_1::subtask_2(std::ifstream &fin, std::ofstream &fout) {
  char str[13] = "";
  fin.getline(str, 12, '\n');

  size_t len = str_len(str);
  if (len > 10) str[6] = '\0';
  else {
    for (size_t i = len; i < 12; ++i)
      str[i] = 'o';
    str[12] = '\0';
  }
  fout << str;
}

char random_alphabet_char(char, char);

/**
 * Дана строка. Разделить строку на фрагменты по три подряд идущих
 * символа. В каждом фрагменте средний символ заменить на случайный
 * символ, не совпадающий ни с одним из символов этого фрагмента.
 * Показать фрагменты, упорядоченные по алфавиту.
 */
void task_1::subtask_3(std::ifstream &fin, std::ofstream &fout) {

  size_t str_size = 0;
  char ch = fin.get();
  while (ch != EOF || ch != '\n') {
    fin >> ch; ++str_size;
  }

  fin.seekg(std::ios::beg);

  char buff[4] = "";
  char max_ch;
  fin.getline(buff, 3, '\n');
}

#define ASCII_A_LOW 97
#define ASCII_Z_LOW 122
/**
 * @param exl exclude left
 * @param exr exclude right
 */
char random_alphabet_char(char exl, char exr) {
  std::random_device dev;
  std::uniform_int_distribution dist(ASCII_A_LOW, ASCII_Z_LOW);

  char ch;
  do ch = dist(dev);
  while (ch == exl || ch == exr);
  return ch;
}