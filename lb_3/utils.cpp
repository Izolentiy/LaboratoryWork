#include <iostream>
#include <random>
#include <iomanip>

#define MIN_VAL 0
#define MAX_VAL 9

template <typename T>
void print_matrix(T **m, int r, int c) {
    using std::cout;
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            cout << m[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << '\n';
}

template <typename T>
T** create_matrix(int r, int c) {
    T **m = new T*[r];
    for (int i = 0; i < r; ++i) {
        m[i] = new T[c];
    }
    return m;
}

template <typename T>
void delete_matrix(T **m, int r) {
    if (m == nullptr) return;
    for (int i = 0; i < r; ++i) {
        delete[] m[i];
    }
    delete[] m;
}   

void fill_matrix(int **m, int r, int c, int min, int max) {
    std::random_device dev;
    std::uniform_int_distribution dist(min, max);

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            m[i][j] = dist(dev);
        }
    }
}

void perform_task(int r, int c, int n, void task(int **m, int r, int c)) {
    // Подготовка окружения
    int **m = create_matrix<int>(r, c);
    fill_matrix(m, r, c, MIN_VAL, MAX_VAL);

    std::cout << "\n\n" << "### Task " << n << " ###" << "\n\n";

    task(m, r, c); // Выполнение задачи

    delete_matrix(m, r); // Очищение памяти
}

/**
 * Функция для умножения двух матриц, может возвращать [nullptr]
 * в случае если операция не применима для данных матриц
 */
int** multiply_matrices(int **m_1, int r_1, int c_1, int **m_2, int r_2, int c_2) {
    if (c_1 != r_2) {
        std::cerr << "Illegal state c_1 != r_2 "
                  << "mutliplication is not applicable\n" << std::endl;
        return nullptr;
    }
    int** res_m = create_matrix<int>(r_1, c_2);

    for (int i = 0; i < r_1; ++i) {
        for (int k = 0; k < c_2; ++k) {
            int sum = 0;
            for (int j = 0; j < c_1; ++j) {
                sum += m_1[i][j] * m_2[j][k];
            }
            res_m[i][k] = sum;
        }
    }
    return res_m;
}

/**
 * Функция для вывода элементов массива с индексами в отрезке [l, r] в консоль
 * @param vert если [true] выведет элементы в столбик
 * @param prec задает количество символов после запятой
 * @param l левая граница вывода
 * @param r правая граница вывода
 */
template <typename T>
void print_array(T arr[], int l, int r, bool vert = false, int prec = 2) {
    using std::cout, std::endl, std::setprecision, std::fixed;

    if (vert) {
        cout << '{' << endl;
        for (int i = l; i <= r; i++) {
            cout << fixed << setprecision(prec) << arr[i] << endl;
        }
        cout << '}' << endl;
        return;
    }

    cout << "{ ";
    for (int i = l; i <= r; i++) {
        cout << fixed << setprecision(prec) << arr[i] << ' ';
    }
    cout << '}' << endl;
}