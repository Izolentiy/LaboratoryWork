#include "string.h"
#include <cmath>

my::string::string(const char *str) {
    size = str_len(str);
    i_nt = size - 1;
    data = new char[size];
    for (size_t i = 0; i < size; ++i) {
        data[i] = str[i];
    }
}

my::string::string(const my::string &other) {
    data = other.as_new_cstring();
    size = other.size;
    i_nt = other.i_nt;
}

/**
 * !Память будет очищена после вызова деструктора!
 * Если нужен массив, который переживет экземпляр,
 * использовать as_new_cstring()
 */
char *my::string::as_cstring() const{
    return data;
}

char *my::string::as_new_cstring() const {
    char *copy = new char[i_nt + 1];
    for (size_t i = 0; i < i_nt + 1; ++i)
        copy[i] = data[i];
    return copy;
}

bool my::string::operator==(const my::string &other) {
    return str_cmp(data, other.data);
}

uint32_t my::string::hash_code() {
    uint32_t hash = 0x00000000;

    char *pcb = data;     // pointer to current byte
    size_t ic = i_nt / 4; // iteration count

    while (ic-- > 0) {
        xor_helper(hash, 4, pcb);
    }
    xor_helper(hash, i_nt % 4, pcb);
    return hash;
}

void my::string::xor_helper(uint32_t &hash, int bound, char *&pcb) {
    uint32_t xor_pair = 0x00000000;
    for (int j = bound; j > 0; --j) {
        uint8_t cb = *pcb;
        xor_pair += cb << ((j - 1) * 8);
        ++pcb;
    }
    hash = hash ^ xor_pair;
}

my::string &my::string::operator+(const char *other) {
    size_t j = -1;
    while (other[++j] != '\0') {
        data[i_nt + j] = other[j];
    }
    data[i_nt += j] = '\0';
    return *this;
}

my::string &my::string::operator+(int num) {
    uint8_t dc = 0; // digit count - 1
    if (num < 0) {
        num = ~num + 1;
        data[i_nt++] = '-';
    }
    if (num == 0)
        dc = 0;
    else
        dc = log10(num);

    for (int32_t i = i_nt + dc; i >= i_nt; --i, num /= 10) {
        data[i] = (num % 10) + '0';
    }
    data[i_nt += dc + 1] = '\0';
    return *this;
}

my::string::~string() {
    delete[] data;
    data = nullptr;
}

/**
 * @return индекс первого символа вхождения
 */
size_t my::string::find(const char *str) {
    size_t i = 0, diffs = 0;
    while (data[i] != '\0') {
        if (str[i] == '\0') {
            do {
                ++i;
                ++diffs;
            } while (data[i] != '\0');
            return diffs;
        }
        if (data[i] != str[i])
            ++diffs;
        ++i;
    }
    while (str[i] != '\0') {
        ++i;
        ++diffs;
    }
    return diffs;
}

my::string &my::string::operator+(char ch) {
    data[i_nt] = ch;
    data[++i_nt] = '\0';
    return *this;
}

void my::string::clear() {
    data[i_nt = 0] = '\0';
}

std::ostream &my::operator<<(std::ostream &out, const my::string &str) {
    return out << str.as_cstring();
}
