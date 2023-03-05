#include <iostream>
#include <random>

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

/**
 * Функция для вывода элементов массива в консоль
 */
void print_array(float arr[], int arr_size, bool verticaly = false) {
    if (verticaly) {
        std::cout << '{' << std::endl;
        for (int i = 0; i < arr_size; i++) {
            std::cout << arr[i] << std::endl;
        }
        std::cout << '}' << std::endl;
        return;
    }
    std::cout << "{ ";
    for (int i = 0; i < arr_size; i++) {
        if (i == arr_size - 1) {
            std::cout << arr[i] << " }" << std::endl;
        }
        else std::cout << arr[i] << ' ';
    }
}

// /**
//  * Функция для вывода элементов массива в консоль
//  */
// void print_array(float* ptr_0, int arr_size, bool verticaly = false) {
//     if (verticaly) {
//         std::cout << '{' << std::endl;
//         for (int i = 0; i < arr_size; i++) {
//             std::cout << ptr_0 + i << std::endl;
//         }
//         std::cout << '}' << std::endl;
//         return;
//     }
//     std::cout << "{ ";
//     for (int i = 0; i < arr_size; i++) {
//         if (i == arr_size - 1) {
//             std::cout << ptr_0 + i << " }" << std::endl;
//         }
//         else std::cout << ptr_0 + i << ' ';
//     }
// }

/**
 * Функция для заполнения массива числами из заданного полуинтервала [min; max)
 * @param min нижняя граница значений
 * @param max верхняя граница значений
 */
void fill_array(float arr[], int arr_size, float min, float max) {
    using std::random_device, std::mt19937, std::uniform_real_distribution;
    
    random_device rand_dev;
    
    mt19937 gen(120);

    uniform_real_distribution distr(min, max);
    
    for (int i = 0; i < arr_size; i++) {
        arr[i] = distr(gen);
    }
}