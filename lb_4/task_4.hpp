#pragma once
#include <fstream>
#include <iostream>
#include <string>

#include "str_utils.h"
#include "task_typedefs.h"

namespace task_4 {
  void subtask_1(std::ifstream &, std::ofstream &);
  void subtask_2(std::ifstream &, std::ofstream &);
  void subtask_3(std::ifstream &, std::ofstream &);
  void subtask_4(std::ifstream &, std::ofstream &);
  void subtask_5(std::ifstream &, std::ofstream &);
  void subtask_6(std::ifstream &, std::ofstream &);
  void subtask_7(std::ifstream &, std::ofstream &);
  void subtask_8(std::ifstream &, std::ofstream &);

  bool is_email_correct(std::string &);
  bool is_delim(const char);

  subtask_t subtasks[] = {
    subtask_1, subtask_2, subtask_3, subtask_4, subtask_5
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

/**
 * Дана строка. Определите, является ли она действительным числом.
 */
void task_4::subtask_2(std::ifstream &fin, std::ofstream &fout) {
  std::string str;
  if (!getline(fin, str)) return;

  bool is_num = true;
  bool df = false; // delimeter found

  if (is_delim(str[0]) || is_delim(str[str.size()-1])) {
    fout << "No\n" << str << "\nis not a number";
    return;
  }
  for (size_t i = 0; i < str.size(); ++i) {
    if (!df && is_delim(str[i])) {
      df = true;
    } else if (df && is_delim(str[i])) {
      is_num = false; break;
    } else if (!my::is_digit(str[i])) {
      is_num = false; break;
    }
  }
  if (is_num) {
    fout << "Yes\n" << str << "\nis real number";
  } else {
    fout << "No\n" << str << "\nis not a number";
  }
}

void task_4::subtask_3(std::ifstream &fin, std::ofstream &fout) {}
void task_4::subtask_4(std::ifstream &fin, std::ofstream &fout) {}

/**
 * Дан email в строке. Определить, является ли он корректным (наличие
 * символа @ и точки, наличие не менее двух символов после последней
 * точки и т.д.). example : username@domain_2.domain_1
 */
void task_4::subtask_5(std::ifstream &fin, std::ofstream &fout) {
  std::string str;
  if (!getline(fin, str)) return;

  if (is_email_correct(str))
    fout << "Email is correct";
  else
    fout << "Invalid email";
}

bool task_4::is_email_correct(std::string &str) {
  // проверка на отстсутствие некорректных символов
  const char forbid[] = R"(;:*,&^%$#+=()'"!?`~<>/\)";
  for (size_t i = 0; i < str.size(); ++i) {
    for (uint8_t j = 0; forbid[j] != '\0'; ++i) {
      if (str[i] == forbid[j]) return false;
    }
  }

  // наличие @ в единственном экземпляре
  if (my::count(&str[0], '@') != 1) return false;

  // проверка на корректность имени пользователя
  size_t at_pos = str.find('@');
  if (at_pos < 2) return false;

  // проверка на корректность доменного имени
  if (str.size() - at_pos < 5) return false;

  // наличие доменов как минимум до второго уровня
  size_t dot_pos = str.find('.', at_pos);
  if (dot_pos == std::string::npos) return false;

  size_t dll = 0; // domain level length
  for (size_t i = at_pos+1; i < str.size(); ++i) {
    if (str[i] == '.') {
      if (dll < 2) break;
      dll = 0; continue;
    }
    ++dll;
  }
  if (dll < 2) return false;
  std::cout << dll;
  return true;
}

void task_4::subtask_6(std::ifstream &fin, std::ofstream &fout) {}
void task_4::subtask_7(std::ifstream &fin, std::ofstream &fout) {}

/**
 * Вывести слова, в которых заменить каждую большую букву одноименной малой; 
 * удалить все символы, не являющиеся буквами или цифрами; 
 * вывести в алфавитном порядке все гласные буквы,
 * входящие в каждое слово строки.
 */
void task_4::subtask_8(std::ifstream &fin, std::ofstream &fout) {
  std::string str, str_res;
  if (!getline(fin, str)) return;

  // отбор нужных символов
  my::char_set pfv(6), cfv(6); // found vowels in prev/curr word
  char c; // current char
  bool wc = true; // word continues
  size_t wsc = 0; // whitespace count
  for (size_t i = 0; i < str.size(); ++i) {
    c = str[i];
    if ('A' <= c && c <= 'Z') 
      c += 32; // 'a' = 97, 'A' = 65
    else if ('a' <= c && c <= 'z');
    else if ('0' <= c && c <= '9');
    else if (c == ' ') {
      wc = false;
      if (++wsc <= 1) {
        str_res.push_back(c);
      }
      continue;
    } else continue;

    // запоминание всех гласных букв
    if (my::is_vowel(c));
    wsc = 0;
    str_res.push_back(c);
  }

  // подсчет гласных букв и вывод в алфавитном порядке
  for (size_t i = 0; i < str_res.size(); ++i) {

  }
}

bool task_4::is_delim(const char ch) {
  if (ch == '.' || ch == ',') return true;
  return false;
}