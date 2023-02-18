#include <iostream>
#include "utils.cpp"

#define ARR_SIZE 12

/**
 * Функция для перемещения элементов меньше среднего значения в начало массива
 * @param arr массив надо которым надо произвести операцию
 * @param size размер массива
 */
void divide_by_mid(int arr[], int size) {
    // Определеяем среднее значение
    int mid = 0;  // Среднее арифметическое значение элементов в массиве
    for (int i = 0; i < size; i++) {
        mid += arr[i];
    }
    mid /= size;

    // Проходимся по массиву смещая элементы меньше среднего в начало
    int cout_l = 0;  // (count of less) Количество элементов которые меньше среднего
    int temp = 0;  // Доп. переменаня для обмена значениями между элементами

    for (int i = 0; i < size; i++) {
        if (arr[i] < mid) {
            temp = arr[i];
            arr[i] = arr[cout_l];
            arr[cout_l] = temp;
            cout_l++;
        }
    }
}

int main() {
    int arr[ARR_SIZE] = {9, 4, 2, 8, 6, 6, 5, 7, 0, 3, 7, 2};
    // arr = {0, 2, 2, 3, 4, 5, 6, 6, 7, 7, 8, 9}  <- отсортированный
    // arr = {2, 0, 3, 2, 4, 9, 8, 6, 6, 5, 7, 7}  <- подходящий по условию
    // Условие: все значения меньше среднего находятся вначале массива. Среднее = 4

    print_array(arr, ARR_SIZE);
    divide_by_mid(arr, ARR_SIZE);
    print_array(arr, ARR_SIZE);

    return 0;
}