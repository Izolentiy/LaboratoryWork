#include <iostream>
#include <cmath>

#define PI 3.14159265358979323846  // Число Пи с точностью 20 знаков после запятой

/* Функция для вывода элементов массива в консоль */
void print_array(int arr[], const int& arr_size) {
    std::cout << '{';
    for (int i = 0; i < arr_size; i++) {
        if (i == arr_size - 1) {
            std::cout << arr[i] << '}' << std::endl;
        }
        else std::cout << arr[i] << ' ';
    }
}

// 1 задание 
/* В качестве аргумента принимается ссылка. "const" означает, что этот параметр не изменяется */
/* r_0 радиус самого первого шара */
double calculate_area(const double& r_0, const int& n) {
    double result = 0;
    for (int i = 0; i < n; i++) {
        // Формула площади поверхности шара: 4 * PI * R^2
        result += 4 * PI * (r_0 + i * 0.2) * (r_0 + i * 0.2);
    }
    return result;
}

// 2 задание
/* arr[] это массив в котором надо приоизвести замену первых и последний с элементов */
/* size это размер массива */
void swap_elements(int arr[], const int& size, const int& c) {
    // По условию c < size / 2
    if (c >= size / 2) {
        std::cout << "Некорректное число c" << std::endl;
        return;
    }

    int temp = 0;
    for (int i = 0; i < c; i++) {
        temp = arr[i];
        arr[i] = arr[size - c + i];
        arr[size - c + i] = temp;
    }

}

// 3 задание
double x(const double& t) {
    return 0.13 / t;
}

double y(const double& x, const double& t) {
    return 12 * (sqrt(x) - (t * t));
}

double f(const double& x, const double& y) {
    return (-93 / sin(y)) + (5 / x);
}

int main() {

    // Код проверяющий второе задание снизу
    // int arr[] = {1, 2, 3, 4, 5, 6};
    // print_array(arr, std::size(arr));
    // swap_elements(arr, std::size(arr), 2);
    // print_array(arr, std::size(arr));

}