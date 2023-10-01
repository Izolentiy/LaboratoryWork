#include "str_helper.h"

bool is_digit(char ch)
{
    if ('0' <= ch && ch <= '9')
        return true;
    return false;
}

bool is_delim(char ch)
{
    if (ch == '.' || ch == ',')
        return true;
    return false;
}

/**
 * @throw "Invalid input"
 * @return delimeter position
 */
size_t validate(std::string str)
{
    bool is_num = true;              // is number
    bool df = false;                 // delimeter found
    double res = 0;                  // result
    size_t dpos = std::string::npos; // delimeter position

    if (is_delim(str[0]) || is_delim(str[str.size() - 1]))
        throw "Invalid input";

    for (size_t i = 0; i < str.size(); ++i)
    {
        if (!df && is_delim(str[i]))
        {
            df = true;
            dpos = i;
            continue;
        }
        else if (df && is_delim(str[i]))
        {
            is_num = false;
        }
        else if (!is_digit(str[i]))
        {
            is_num = false;
        }
        if (!is_num)
            throw "Invalid input";
    }
    return dpos;
}

/**
 * @throw "Invalid input"
 */
double to_double(std::string str)
{
    double res = 0;              // result
    size_t dpos = validate(str); // delimeter position

    uint8_t cur = 0; // current digit
    int ic = 0;      // integer count
    int dc = 0;      // -decimal count
    if (dpos != std::string::npos)
    {
        ic = dpos;
        dc = (dpos + 1) - str.size();
    }
    else
    {
        ic = str.size();
        dc = 0;
    }
    for (size_t i = 0; ic > dc; ++i)
    {
        if (is_delim(str[i]))
            continue;
        cur = str[i] - '0';
        res += cur * std::pow(10, --ic);
    }

    // std::cout << "ic " << ic << std::endl;
    // std::cout << "dc " << dc << std::endl;

    return res;
}

/**
 * @throw "Invalid input"
 */
std::vector<double> to_vector(std::ifstream &fin)
{
    std::string str;         // string
    std::vector<double> vec; // elements
    int rows = 0;
    int cols = 0;

    while (std::getline(fin, str))
    {
        size_t bpos = 0, epos = 0; // begin/end position
        bool ns = false;           // number started
        double temp = 0;           // temp value

        // std::cout << str << std::endl;
        int cur_cols = 0;
        for (size_t i = 0; i < str.size(); ++i)
        {
            if (ns)
            {
                if (str[i] == ' ')
                    epos = i;
                else if (i == str.size() - 1)
                    epos = i + 1;
                else
                    continue;
                ns = false;
                temp = to_double(str.substr(bpos, epos - bpos));
                vec.push_back(temp);
                ++cur_cols;
            }
            else if (is_digit(str[i]))
            {
                bpos = i;
                ns = true;
                if (i == str.size() - 1)
                {
                    temp = to_double(str.substr(bpos, 1));
                    vec.push_back(temp);
                    ++cur_cols;
                }
            }
        }
        if (rows == 0)
        {
            cols = cur_cols;
        }
        else if (cols != cur_cols)
        {
            throw "Invalid input";
        }
        ++rows;
    }

    return vec;
}