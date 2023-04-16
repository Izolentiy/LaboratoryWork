#include "utils.hpp"
#include "matrix.h"

void move_points_and_set_vector(
    my::vector& v, my::point& s, my::point& e, 
    const float& x, const float& y
) {
    s.move(v); // перемещение точки начала в конец
    v.set(x, y); // установка нового вектора перемещения
    e.move(v); // перемещение точки конца в новое положение
}

void task_1(int **m, int r, int c) {
    print_matrix(m, r, c);

    int i = r;
    my::point s(0, -1), e(0, r-1); // точка начала смещена вверх на 1
    my::vector v(0, i); // изначально вектор направлен вниз
    while (i > 0) {
        print_elements_between(m, s, e); // печать вниз
        move_points_and_set_vector(v, s, e, --i, 0);
        if (i <= 0) break;
        
        print_elements_between(m, s, e); // печать вправо
        move_points_and_set_vector(v, s, e, 0, -i);
        
        print_elements_between(m, s, e); // печать вверх
        move_points_and_set_vector(v, s, e, -(--i), 0);

        print_elements_between(m, s, e); // печать влево
        move_points_and_set_vector(v, s, e, 0, i);
    }
}

void task_1_simple(int **m, int r, int c) {
    print_matrix(m, r, c);
    int mg = 0;
    int cl = r/2;
    while (cl > 0) {
        // печать вниз
        for (int i = mg; i < r-1-mg; ++i) {
            std::cout << m[i][mg] << ' ';
        }
        std::cout << std::endl;
        
        // печать вправо
        for (int i = mg; i < r-1-mg; ++i) {
            std::cout << m[r-1-mg][i] << ' ';
        }
        std::cout << std::endl;

        // печать вверх
        for (int i = r-1-mg; i > mg; --i) {
            std::cout << m[i][r-1-mg] << ' ';
        }
        std::cout << std::endl;

        // печать влево
        for (int i = r-1-mg; i > mg; --i) {
            std::cout << m[mg][i] << ' ';
        }
        std::cout << std::endl;
        ++mg; --cl;
    }
    uint16_t i = r/2 + 1;
    std::cout << m[i][i] << std::endl;
    std::cout << "margin: " << mg << '\n';
}

void task_2(int **m, int r, int c) {
    print_matrix(m, r, c);
    for (int i = 0; i < r/2; ++i) {
        for (int j = 0; j <= i; ++j) {
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

void task_2_another(int **m, int r, int c) {
    print_matrix(m, r, c);
    int k = c/2;
    for (int i = 0; i < k; ++i) {
        for (int j = r-1; j >= i; --j) {
            m[j][i] = 0;
            m[j][c-1-i] = 0;
        }
    }
    if (c % 2 != 0) {
        for (int j = r-1; j >= k; --j) {
            m[j][k] = 0;
        }
    }
    print_matrix(m, r, c);
}

int main() {
    perform_task(5, 5, 1, task_1);
    // perform_task(7, 7, 1, task_1_simple);
    perform_task(5, 5, 1, task_2);
    // perform_task(5, 5, 2, task_2_another);
    // perform_task(3, 3, 2, task_2);
}