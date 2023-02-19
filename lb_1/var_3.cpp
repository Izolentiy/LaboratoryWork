#include <iostream>

#include <cmath>
#include "utils.cpp"

#define ARR_SIZE 7
#define N 200  // Максимальное количество членов в ряде тейлора
#define PI 3.14159265358979323846  // Число Пи с точностью 20 знаков после запятой

/**
 * Функция производящая циклический сдвиг элементов массива влево на k элементов
 * @param arr[] массив, в котором надо произвести сдвиг
 * @param size размер массива
 * @param k количество элементов сдвига
 */
void cycle_shift(int arr[], int size, int k) {
    if (k < 0) {
        std::cout << "Illegal shift value" << std::endl;
        return;
    }

    k %= size;
    if (size % 2 == 0) {
        int pair_elem = 0;
        for (int i = 0; i < (size / 2); i++) {
            pair_elem = arr[i];

            arr[i] = arr[(k + i) % size];
            arr[(k + i) % size] = pair_elem;
        }
    } else {
        int elem_0 = arr[0];
        for (int i = 0; i < size; i++) {
            if (i == size - 1) {
                arr[(k * i) % size] = elem_0;
                break;
            }
            
            arr[(k * i) % size] = arr[(k * (i + 1)) % size];
        }
    }
}

/**
 * Функция производящая циклический сдвиг элементов массива влево на k элементов. (Реализованна через указатели)
 * @param ptr_0 указатель на нулевой элемент массива
 * @param size размер массива
 * @param k количество элементов сдвига
 */
void cycle_shift_ptr(int* ptr_0, int size, int k) {
    if (k < 0) {
        std::cout << "Illegal shift value" << std::endl;
        return;
    }

    k %= size;
    if (size % 2 == 0) {
        int pair_elem = 0;
        for (int i = 0; i < (size / 2); i++) {
            pair_elem = *(ptr_0 + i);

            *(ptr_0 + i) = *(ptr_0 + ((k + i) % size));
            *(ptr_0 + ((k + i) % size)) = pair_elem;
        }
    } else {
        int elem_0 = *ptr_0;
        for (int i = 0; i < size; i++) {
            if (i == size - 1) {
                *(ptr_0 + ((k * i) % size)) = elem_0;
                break;
            }
            
            *(ptr_0 + ((k * i) % size)) = *(ptr_0 + ((k * (i + 1)) % size));
        }
    }
}

/**
 * Функция взятия модуля
 */
double abs_f(const double& f) {
    if (f < 0) {
        return -f;
    } else {
        return f;
    }
}

/**
 * Функция возведения в степень
 * @param a основание
 * @param k показатель степени
 */
int pow_i(int a, const int& k) {
    if (k == 0) {
        return 1;
    }

    int init_a = a;
    for (int i = 1; i < k; i++) {
        a *= init_a;
    }
    return a;
}

/**
 * Функция для вычисления значения синуса в определенной точке с заданной точностью
 * @param x значение для которого надо вычислить синус
 * @param e точность с которой должно быть выполнено вычисление
 */
double sin_taylor(double x, const double& e) {
    x -= (2 * PI) * (int)(x / (2 * PI));  // Смещение x в отрезок [0, 2*PI]
    double sum = 0.0;  // сумма
    double mem = 0;  // (member) член
    for (int n = 0; n < N; n++) {

        if (n == 0) {
            sum += x;
            continue;
        }

        mem = 1;  // Сбрасываем значение члена
        for (int i = 1; i <= (2 * n + 1); i++) {
            mem *= x / i;
        }

        sum += pow_i(-1, n) * mem;
        if (abs_f(mem) < e) {
            return sum;
        }
    }
    return sum;
}

void sin_runner() {
    double x = -1524.734;

    std::cout << "x = " << x << std::endl;
    std::cout << "Library sin: " << sin(x) << std::endl;
    std::cout << "Handmade sin: " << sin_taylor(x, 0.000001) << std::endl;
}

int main() {
    // int arr[ARR_SIZE] = {0, 1, 2, 3, 4, 5, 6};

    // print_array(arr, ARR_SIZE);
    // cycle_shift_ptr(arr, ARR_SIZE, 9);
    // print_array(arr, ARR_SIZE);

    sin_runner();

    return 0;
}