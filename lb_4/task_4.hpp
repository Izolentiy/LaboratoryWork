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

  bool is_email_correct(std::string &);
  bool is_email_forbid(const char);
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
  for (size_t i = 0; i < str.size(); ++i) {
    if (is_email_forbid(str[i])) return false;
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

  size_t dom_lvl_len = 0; // domain level length
  for (size_t i = at_pos+1; i < str.size(); ++i) {
    if (str[i] == '.') {
      if (dom_lvl_len < 2) break;
      dom_lvl_len = 0; continue;
    }
    ++dom_lvl_len;
  }
  if (dom_lvl_len < 2) return false;
  std::cout << dom_lvl_len;
  return true;
}

bool task_4::is_email_forbid(const char ch) {
  /*static?*/ const char forbid[] = R"(;:*,&^%$#+=()'"!?`~<>/\)";
  for (uint8_t i = 0; forbid[i] != '\0'; ++i) {
    if (ch == forbid[i]) return true;
  }
  return false;
}

bool task_4::is_delim(const char ch) {
  if (ch == '.' || ch == ',') return true;
  return false;
}