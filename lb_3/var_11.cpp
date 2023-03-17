#include "utils.cpp"

void task_1(int **m, int r, int c) {
    print_matrix(m, r, c);
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            std::cout << m[i][abs(j - (c - 1) * (i % 2))] << ' ';
        }
        std::cout << '\n';
    }
}

void task_2(int **m, int r, int c) {
    print_matrix(m, r, c);
    for (int i = 0; i < r; ++i) {
        for (int j = r - 1; j >= r - 1 - i; --j) {
            m[i][j] = 0;
        }
    }
    print_matrix(m, r, r);
}

void task_3(int **m, int r, int c) {
    print_matrix(m, r, c);
    int asc_c = 0, desc_r = 0;
    
    for (int i = 0; i < c; ++i) {
        ++asc_c;
        for (int j = 1; j < r; ++j) {
            if (m[j][i] < m[j-1][i]) {
                --asc_c;
                break;
            }
        }
    }

    for (int i = 0; i < r; ++i) {
        ++desc_r;
        for (int j = 1; j < c; ++j) {
            if (m[i][j] > m[i][j-1]) {
                --desc_r;
                break;
            }
        }
    }
    std::cout << "Ascending columns: " << asc_c << ", ";
    std::cout << "Descending rows: " << desc_r << "\n\n";
}

int main() {
    perform_task(4, 5, 1, task_1);
    perform_task(4, 4, 2, task_2);
    perform_task(3, 4, 3, task_3);
    return 0;
}