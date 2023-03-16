#include "utils.cpp"

#define MIN_VAL 0
#define MAX_VAL 9

void perform_task(int c, int r, int n, void task(int **m, int c, int r)) {
    // Подготовка окружения
    int **m = create_matrix<int>(c, r);
    fill_matrix(m, c, r, MIN_VAL, MAX_VAL);

    std::cout << "\n\n" << "### Task " << n << " ###" << "\n\n";
    print_matrix(m, c, r);

    task(m, c, r); // Выполнение задачи

    delete_matrix(m, c); // Очищение памяти
}

void task_1(int **m, int c, int r) {
    for (int i = 0; i < c; ++i) {
        for (int j = 0; j < r; ++j) {
            std::cout << m[i][abs(j - (r - 1) * (i % 2))] << ' ';
        }
        std::cout << '\n';
    }
}

void task_2(int **m, int c, int r) {
    for (int i = 0; i < c; ++i) {
        for (int j = c - 1; j >= c - 1 - i; --j) {
            m[i][j] = 0;
        }
    }
    print_matrix(m, c, c);
}

void task_3(int **m, int c, int r) {
    int asc_r = 0, des_c = 0;
    
    for (int i = 0; i < r; ++i) {
        ++asc_r;
        for (int j = 1; j < c; ++j) {
            if (m[j][i] < m[j-1][i]) {
                --asc_r;
                break;
            }
        }
    }

    for (int i = 0; i < c; ++i) {
        ++des_c;
        for (int j = 1; j < r; ++j) {
            if (m[i][j] > m[i][j-1]) {
                --des_c;
                break;
            }
        }
    }
    std::cout << "Ascending rows: " << asc_r << ", ";
    std::cout << "Descending columns: " << des_c << "\n\n";
}

int main() {
    perform_task(4, 5, 1, task_1);
    perform_task(4, 4, 2, task_2);
    perform_task(3, 4, 3, task_3);
    return 0;
}