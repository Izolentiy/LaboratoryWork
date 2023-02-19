#include <iostream>
#include <math.h>

#define SIZE 4

/**
 * Функция для подсчета веса пирамиды
 * @param n количество слоев в пирамиде. В каждом слое n ^ 2 кубиков. На самом верхнем слое 1 кубик.
 * @param weight вес одного кубика
 */
int weight_calc(const int& n, const int& weight) {
    return n ^ 2 * weight;
}

void pyramid_weight() {
    int n = 10, weight = 15;
    std::cout << "Weight of pyramid: " << weight_calc(n, weight) << std::endl;
}

/**
 * Функция для смещения элементов массива влево на k-ый элемент
 * @param ptr_0 указатель на нулевой элемент массива. Можно передать имя массива в качестве аргумента
 * @param arr_size размер массива
 * @param k на какой элемент нужно сместиться. К примеру если передать k = 1, то значение нулевого элемента станет равно первому, * значение первого элемента второму и так далее. k >= 0
 */
void shift(int *ptr_0, int arr_size, int k) {
    for (int i = 0; i < arr_size; i++) {
        *(ptr_0 + i) = *(ptr_0 + i + k);
    }
}

void shift_runner() {

    int arr[SIZE] = {1, 2, 3, 4};
    // 1 {2, 3, 4, ?}
    shift(arr, SIZE, 1);

    for (int i = 0; i < SIZE; i++)
    {
        std::cout << arr[i] << std::endl;
    }
}

double x(const double &t) {
    return 3 * t + 8;
}

double y(const double &t) {
    return sqrt(t);
}

double f(const double &x, const double &y) {
    return 7 * (x * x) - (13 / y) + cos(x + y);
}

void math_test() {
    double t = 15.3;
    std::cout << f(x(t), y(t)) << std::endl;
}

int main() {

    // 1 задание
    // pyramid_weight();

    // 2 задание
    // shift_runner();

    // 3 задание
    // math_test();

    return 0;
}