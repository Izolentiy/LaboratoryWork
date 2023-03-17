#include "utils.cpp"

void task_1(int** matrix, int m, int n) {
    int* set = new int[m];
    for (int i = 0; i < m; ++i) {
        set[i] = i + 1;
    }

    for (int j = 0; j < n; ++j) {
        for (int i = 0; i < m; ++i) {
            matrix[i][j] = set[i];
        }
    }

    print_matrix(matrix, m, n);
    delete[] set;
}

int sum_on_diagonal(int **m, int ci, int ri, int n) {
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += m[ci + i][ri + i];
    }
    return sum;
}

void task_2(int** m, int r, int c) {
    print_matrix(m, r, c);

    int diag_count = (r-1) * 2;
    int *sums = new int[diag_count];

    for (int i = 0; i < r-1; ++i) {
        sums[diag_count-1-i] = sum_on_diagonal(m, 0, r-1-i, i+1);
        sums[i] = sum_on_diagonal(m, r-1-i, 0, i+1);
    }
    print_array(sums, 0, diag_count-1, 0, 0);
    delete[] sums;
}

void task_3(int **m, int r, int c) {
    int **m_2 = create_matrix<int>(c, r+2);
    fill_matrix(m_2, c, r+2, MIN_VAL, MAX_VAL);
    
    print_matrix(m, r, c);
    print_matrix(m_2, c, r+2);
    
    int **m_3 = multiply_matrices(m, r, c, m_2, c, r+2);
    if (m_3 != nullptr) {
        print_matrix(m_3, r, r+2);
    }

    int **m_4 = multiply_matrices(m, r, c, m_2, c-1, r+2); // Вернет nullptr
    if (m_4 != nullptr) {
        print_matrix(m_4, r, r+2);
    }

    // m автоматически удаляется после окончания выполнения task
    delete_matrix(m_2, c);
    delete_matrix(m_3, r);
    delete_matrix(m_4, r);
}

int main() {
    perform_task(3, 4, 1, task_1);
    perform_task(4, 4, 2, task_2);
    perform_task(2, 3, 3, task_3);
    return 0;
}