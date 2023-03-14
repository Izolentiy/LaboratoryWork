#include <iostream>
#include <random>

void print_matrix(float **m, int c, int r) {
    using std::cout;
    for (int i = 0; i < c; ++i) {
        for (int j = 0; j < r; ++j) {
            cout << m[i][j] << ' ';
        }
        cout << '\n';
    }
}

float** create_matrix(int c, int r) {
    float **m = new float*[c];
    for (int i = 0; i < c; ++i) {
        m[i] = new float[r];
    }
    return m;
}

void delete_matrix(float **m, int c) {
    for (int i = 0; i < c; ++i) {
        delete[] m[i];
    }
    delete[] m;
}   

void fill_matrix(float **m, int c, int r, float min, float max) {
    std::random_device dev;
    std::mt19937 engine(dev);
    std::uniform_real_distribution dist(min, max);

    for (int i = 0; i < c; ++i) {
        for (int j = 0; j < r; ++j) {
            m[i][j] = dist(engine);
        }
    }
}