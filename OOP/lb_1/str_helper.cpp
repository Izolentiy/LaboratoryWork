#include "str_helper.h"

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

/**
 * @return delimeter position
 */
size_t str_helper::validate(std::string str)
{
    bool is_num = true;              // is number
    bool df = false;                 // delimeter found
    double res = 0;                  // result
    size_t dpos = std::string::npos; // delimeter position

    if (str.size() == 1 && str[0] == '-')
        throw std::runtime_error(INVALID_INPUT);
    if (is_delim(str[0]) || is_delim(str[str.size() - 1]))
        throw std::runtime_error(INVALID_INPUT);

    for (size_t i = 0; i < str.size(); ++i)
    {
        if (!df && is_delim(str[i]))
        {
            df = true;
            dpos = i;
            continue;
        }
        else if (str[i] == '-' && i != 0)
            is_num = false;
        else if (df && is_delim(str[i]))
            is_num = false;
        else if (!is_number_char(str[i]))
            is_num = false;

        if (!is_num)
            throw std::runtime_error(INVALID_INPUT);
    }
    return dpos;
}

double str_helper::to_double(std::string str)
{
    bool neg = str[0] == '-';    // negative
    double res = 0;              // result
    size_t dpos = validate(str); // delimeter position

    uint8_t cur = 0; // current digit
    int ic = 0;      // integer count
    int dc = 0;      // -decimal count
    if (dpos != std::string::npos)
    {
        ic = dpos - neg;
        dc = (dpos + 1) - str.size();
    }
    else
    {
        ic = str.size() - neg;
        dc = 0;
    }
    for (size_t i = 0; ic > dc; ++i)
    {
        if (str[i] == '-' || is_delim(str[i]))
            continue;
        cur = str[i] - '0';
        res += cur * std::pow(10, --ic);
    }
    if (neg)
        res = -res;

    return res;
}

/**
 * Add elements to vector from string
 * @throw std::logic_error
 * @param dest destination for elements
 * @param str source string
 **/
void str_helper::add_elements(std::vector<double> &dest, std::string &str)
{
    size_t bpos = 0, epos = 0; // begin/end position
    bool ns = false;           // number started
    double temp = 0;           // temp value

    for (size_t i = 0; i < str.size(); ++i)
    {
        if (is_number_char(str[i]) && !ns)
        {
            bpos = i;
            ns = true;
        }
        else if (!is_number_char(str[i]) && ns)
        {
            epos = i;
            ns = false;
        }
        if (i == str.size() - 1 && ns)
            epos = i + 1;
        if (bpos >= epos)
            continue;
        temp = to_double(str.substr(bpos, epos - bpos));
        dest.push_back(temp);
    }
}

bool str_helper::compare(const char *s1, const char *s2)
{
    for (size_t i = 0; s1[i] == s2[i]; ++i)
    {
        if (s1[i] == '\0') return true;
    }
    return false;
}
