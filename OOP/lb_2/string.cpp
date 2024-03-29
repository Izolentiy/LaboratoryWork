#include "string.h"
#include <cmath>

my::string::string() {
    size = 1;
    data = new char[size];
    data[i_nt] = '\0';
}

my::string::string(const char *str) {
    size = str_size(str);
    i_nt = size - 1;
    delete[] data;
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

char *my::string::as_new_cstring() const {
    return substring(0, i_nt);
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
    for (size_t i = 0; i <= i_nt; ++i) {
        new_data[i] = data[i];
    }
    delete[] data;
    data = new_data;
    size = new_size;
}

void my::string::resize_to_fit(const char *str) {
    resize_to_fit(str_size(str) - 1);
}

void my::string::resize_to_fit(size_t char_count) {
    size_t free = (size - 1) - i_nt; // free space

    // check if there is enough space
    if (free < char_count) {
        size_t new_size = size + char_count - free;
        resize(new_size + ADD_CHUNK);
    }
}

bool my::string::operator==(const my::string &other) {
    return str_cmp(data, other.data);
}

bool my::string::operator>(const string &other) {
    size_t min;
    if (i_nt > other.i_nt) {
        min = other.i_nt;
    } else {
        min = i_nt;
    }
    // hello
    // he
    for (size_t i = 0; i < min; ++i) {
        if (data[i] > other.data[i]) {
            return true;
        } else if (data[i] < other.data[i]) {
            return false;
        }
    }
    return min == other.i_nt;
}

my::string &my::string::operator<<(const char *other) {
    resize_to_fit(other);
    size_t j = -1;
    while (other[++j] != '\0') {
        data[i_nt + j] = other[j];
    }
    data[i_nt += j] = '\0';
    return *this;
}

my::string &my::string::operator<<(int num) {
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

my::string &my::string::operator<<(char ch) {
    resize_to_fit(1);
    data[i_nt] = ch;
    data[++i_nt] = '\0';
    return *this;
}

my::string &my::string::operator<<(const my::string &other) {
    return (*this) << other.data;
}

size_t my::string::count_any(const my::string &str) {
    return count_helper(str.data, find_any);
}

size_t my::string::count_isolated(const my::string &str) {
    return count_helper(str.data, find_isolated);
}

size_t my::string::count_helper(const char *str, find_func find) {
    size_t len = str_size(str) - 1;
    if (len > i_nt)
        return 0;
    size_t c = 0; // counter
    size_t i = (this->*find)(0, len, str);
    while (i != npos) {
        ++c;
        i = (this->*find)(i + 1, len, str);
    }
    return c;
}

size_t my::string::find_any(const my::string &str) {
    size_t len = str_size(str.data) - 1;
    if (len > i_nt)
        return npos;
    return find_any(0, len, str.data);
}

size_t my::string::find_isolated(const my::string &str) {
    size_t len = str_size(str.data) - 1;
    if (len > i_nt)
        return npos;
    return find_isolated(0, len, str.data);
}

size_t my::string::get_size() const {
    return size;
}

size_t my::string::get_length() const {
    return i_nt;
}

size_t my::string::find_any(size_t start, size_t len, const char *str) {
    size_t k = 0; // index for data
    size_t j = 0; // index for str to find

    for (size_t i = start; i <= i_nt - len; ++i) {
        if (data[i] == str[0]) {
            k = i;
            j = 0;
            while (data[++k] == str[++j] && data[k] != '\0');
            if (str[j] == '\0')
                return i;
        }
    }
    return npos;
}

size_t my::string::find_isolated(size_t start, size_t len, const char *str) {
    size_t k = 0; // index for data
    size_t j = 0; // index for str to find  

    if (start == 0 && data[0] == str[0]) {
        while (data[++k] == str[++j] && data[k] != '\0');
        if (str[j] == '\0' && !is_letter_or_dash(data[k]))
            return 0;
        start = k;
    } else {
        ++start;
    }

    for (size_t i = start; i <= i_nt - len; ++i) {
        if (data[i] == str[0]) {
            // check if str is not in the beginning of other word
            if (is_letter_or_dash(data[i - 1]))
                continue;
            k = i;
            j = 0;
            while (data[++k] == str[++j] && data[k] != '\0');
            if (str[j] == '\0' && !is_letter_or_dash(data[k]))
                return i;
        }
    }
    return npos;
}

char *my::string::substring(size_t start, size_t end) const {
    size_t len = end - start;
    char *str = new char[len+1];
    for (size_t i = 0; i < len; ++i, ++start)
        str[i] = data[start];
    str[len] = '\0';
    return str;
}

void my::string::clear() {
    data[i_nt = 0] = '\0';
}

my::string my::string::to_lower_case() {
    my::string res = *this;
    for (size_t i = 0; i < i_nt; ++i) {
        if (res.data[i] >= 'A' && res.data[i] <= 'Z')
            res.data[i] += 32; // ASCII shift between up and low case letters
    }
    return res;
}

my::linked_map<my::string, size_t> my::string::unique_words(sort_type sort) {
    my::linked_map<my::string, size_t> result;
    std::vector<bool> range(i_nt + 1); // to define ignore indexes

    bool started = false; // word started
    size_t ws, we, wc, wl; // word start / end / count / length
    char *word = nullptr;
    for (size_t i = 0; i <= i_nt; ++i) {
        if (range[i] && !started)
            continue;
        if (!is_letter_or_dash(data[i]) && started) {
            started = false;
            we = i;
            wc = 1;
            wl = we - ws;
            if (wl == 1 && data[ws] == '-')
                continue;

            word = substring(ws, we);
            size_t ni = find_isolated(we, wl, word); // next index
            while (ni != npos) {
                ++wc;
                for (size_t j = 0; j < wl; ++j) {
                    range[j + ni] = 1; // update ignore range
                }
                ni = find_isolated(ni + wl, wl, word);
            }
            result.insert(word, wc);
            delete[] word;
        } else if ((is_letter_or_dash(data[i])) && !started) {
            started = true;
            ws = i;
        }
    }
    switch (sort) {
    case alphabetic:
        result.sort_by_key(); break;
    case by_count_in_text:
        result.sort_by_val(); break;
    }
    return result;
}

my::string::~string() {
    // std::cout << "dtor called on " << data << " \n";
    delete[] data;
    data = nullptr;
}

std::ostream &my::operator<<(std::ostream &out, const my::string &str) {
    return out << str.data;
}

void my::operator<<(const char *out, const my::string &str) {
    std::ofstream fout(out, std::ios::binary);
    if (fout.is_open()) {
        fout << str;
    }
    fout.close();
}

void my::operator>>(const char *in, my::string &str) {
    std::ifstream fin(in, std::ios::binary);
    if (fin.is_open()) {
        fin.seekg(0, std::ios::end);
        size_t len = fin.tellg();
        fin.seekg(0, std::ios::beg);

        char *buffer = new char[len + 1];
        fin.read(buffer, len);
        buffer[len] = 0;

        str << buffer; // append to str
        delete[] buffer;
    }
    fin.close();
}
