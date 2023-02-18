#include <iostream>

/**
 * Функция для вывода элементов массива в консоль
 */
void print_array(int arr[], int arr_size) {
    std::cout << '{';
    for (int i = 0; i < arr_size; i++) {
        if (i == arr_size - 1) {
            std::cout << arr[i] << '}' << std::endl;
        }
        else std::cout << arr[i] << ' ';
    }
}