#include "utils.cpp"

#define MIN_VAL 0
#define MAX_VAL 9

void perform_task(int c, int r, int n, void task(int **m, int c, int r)) {
    // Подготовка окружения
    int **m = create_matrix(c, r);
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
    
}

int main() {
    perform_task(4, 5, 1, task_1);
    perform_task(4, 4, 2, task_2);
    perform_task(4, 6, 3, task_3);
    return 0;
}