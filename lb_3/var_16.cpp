#include "utils.cpp"

void task_1(int **m, int r, int c) {
    print_matrix(m, r, c);
    if (r % 2 == 0) {
        std::cout << "Matrix is invalid!" << std::endl;
        return;
    }
    my::point s(0, 0), e(r-1, r-1);
    s.print_coordinates();
    e.print_coordinates();
    print_elements_between(m, s, e);

}

void task_2(int **m, int r, int c) {
    print_matrix(m, r, c);
    for (int i = 0; i < r/2; ++i) {
        for (int j = 0; j < i+1; ++j) {
            m[i][j] = 0;
            m[i][r-1-j] = 0;
        }
    }
    for (int i = r/2; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            m[i][j] = 0;
        }
    }
    print_matrix(m, r, c);
}

int main() {
    perform_task(5, 5, 1, task_1);
    // perform_task(3, 3, 2, task_2);
}