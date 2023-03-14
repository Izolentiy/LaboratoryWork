#include <iostream>
#include <random>

void print_matrix(int **m, int c, int r) {
    using std::cout;
    for (int i = 0; i < c; ++i) {
        for (int j = 0; j < r; ++j) {
            cout << m[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << '\n';
}

int** create_matrix(int c, int r) {
    int **m = new int*[c];
    for (int i = 0; i < c; ++i) {
        m[i] = new int[r];
    }
    return m;
}

void delete_matrix(int **m, int c) {
    for (int i = 0; i < c; ++i) {
        delete[] m[i];
    }
    delete[] m;
}   

void fill_matrix(int **m, int c, int r, int min, int max) {
    std::random_device dev;
    // std::mt19937 engine(dev);
    std::uniform_int_distribution dist(min, max);

    for (int i = 0; i < c; ++i) {
        for (int j = 0; j < r; ++j) {
            m[i][j] = dist(dev);
        }
    }
}