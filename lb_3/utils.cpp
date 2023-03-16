#include <iostream>
#include <random>

template <typename T>
void print_matrix(T **m, int c, int r) {
    using std::cout;
    for (int i = 0; i < c; ++i) {
        for (int j = 0; j < r; ++j) {
            cout << m[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << '\n';
}

template <typename T>
T** create_matrix(int c, int r) {
    T **m = new T*[c];
    for (int i = 0; i < c; ++i) {
        m[i] = new T[r];
    }
    return m;
}

template <typename T>
void delete_matrix(T **m, int c) {
    for (int i = 0; i < c; ++i) {
        delete[] m[i];
    }
    delete[] m;
}   

void fill_matrix(int **m, int c, int r, int min, int max) {
    std::random_device dev;
    std::uniform_int_distribution dist(min, max);

    for (int i = 0; i < c; ++i) {
        for (int j = 0; j < r; ++j) {
            m[i][j] = dist(dev);
        }
    }
}