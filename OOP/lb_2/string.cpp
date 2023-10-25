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

char *my::string::as_cstring() const{
    return data;
}

char *my::string::as_new_cstring() const {
    char *copy = new char[i_nt + 1];
    for (size_t i = 0; i < i_nt + 1; ++i)
        copy[i] = data[i];
    return copy;
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

void my::string::resize(size_t new_size) {
    char *new_data = new char[new_size];
    size_t i;
    for (i = 0; i < new_size - 1; ++i) {
        if (data[i] == '\0')
            break;
        new_data[i] = data[i];
    }
    new_data[i_nt = i] = '\0';
    delete[] data;
    data = new_data;
}

void my::string::resize_to_fit(const char *str) {
    resize_to_fit(str_len(str));
}

void my::string::resize_to_fit(size_t char_count) {
    size_t free = size - i_nt; // free space

    // check if there is enough space
    if (free < char_count) {
        size_t new_size = size + char_count - free;
        resize(new_size + ADD_CHUNK);
    }
}

bool my::string::operator==(const my::string &other) {
    return str_cmp(data, other.data);
}

my::string &my::string::operator+(const char *other) {
    resize_to_fit(other);
    size_t j = -1;
    while (other[++j] != '\0') {
        data[i_nt + j] = other[j];
    }
    data[i_nt += j] = '\0';
    return *this;
}

my::string &my::string::operator+(int num) {
    // INT_MIN (4 byte) consist of 11 chars
    resize_to_fit(11);
    
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

my::string &my::string::operator+(char ch) {
    resize_to_fit(1);
    data[i_nt] = ch;
    data[++i_nt] = '\0';
    return *this;
}

my::string &my::string::operator+(const my::string &other) {
    return (*this) + other.as_cstring();
}

size_t my::string::find(const char *str) {
    if (str_len(str) > i_nt)
        return npos;
    size_t k = 0; // index for data
    size_t j = 0; // index for str to find
    for (size_t i = 0; i < i_nt; ++i) {
        if (data[i] == str[0]) {
            k = i;
            while (data[++k] == str[++j]);
            if (str[j] == '\0') {
                return i;
            }
            j = 0;
        }
    }
    return npos;
}

void my::string::clear() {
    data[i_nt = 0] = '\0';
}

my::string::~string() {
    delete[] data;
    data = nullptr;
}

std::ostream &my::operator<<(std::ostream &out, const my::string &str) {
    return out << str.as_cstring();
}
