#pragma once
#include <iostream>

template <class T>
void str_helper::print_diff(const char *label, T expected, T result)
{
    std::cout << "  " << label << '\n'
              << "  expected: " << expected << '\n'
              << "    actual: " << result << "\n\n";
}

bool str_helper::is_digit(char ch)
{
    if ('0' <= ch && ch <= '9')
        return true;
    return false;
}

bool str_helper::is_delim(char ch)
{
    if (ch == '.' || ch == ',')
        return true;
    return false;
}

bool str_helper::is_number_char(char ch)
{
    if (is_delim(ch) || is_digit(ch) || ch == '-')
        return true;
    return false;
}

size_t str_helper::count(std::string &str, char ch)
{
    size_t count = 0, i = 0;
    while (i < str.size())
        if (str[i++] == ch)
            ++count;
    return count;
}

bool str_helper::compare(const char *s1, const char *s2)
{
    for (size_t i = 0; s1[i] == s2[i]; ++i)
    {
        if (s1[i] == '\0') return true;
    }
    return false;
}