#include <iostream>
#include <random>
#include <iomanip>

#define SEED 120

/**
 * Функция для вывода элементов массива в консоль
 * @param vert если [true] выведет элементы в столбик
 * @param prec задает количество символов после запятой
 */
void print_array(float arr[], int arr_size, bool vert = false, int prec = 2) {
    using std::cout, std::endl, std::setprecision, std::fixed;

    if (vert) {
        cout << '{' << endl;
        for (int i = 0; i < arr_size; i++) {
            cout << fixed << setprecision(prec) << arr[i] << endl;
        }
        cout << '}' << endl;
        return;
    }

    cout << "{ ";
    for (int i = 0; i < arr_size; i++) {
        cout << fixed << setprecision(prec) << arr[i] << ' ';
    }
    cout << '}' << endl;
}

/**
 * Функция для заполнения массива числами из заданного полуинтервала [min; max)
 * @param min нижняя граница значений
 * @param max верхняя граница значений
 */
void fill_array(float arr[], int arr_size, float min, float max) {
    std::mt19937 gen(SEED);
    std::uniform_real_distribution distr(min, max);
    
    for (int i = 0; i < arr_size; i++) {
        arr[i] = distr(gen);
    }
}