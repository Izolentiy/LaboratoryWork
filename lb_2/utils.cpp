#include <iostream>
#include <random>
#include <iomanip>
#include <chrono>

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

void run_sorting_with_time_measurement(float a[], int s, void algorithm (float *, int, int)) {
    using namespace std::chrono;

    uint64_t time;
    high_resolution_clock::time_point start;
    high_resolution_clock::time_point end;

    start = high_resolution_clock::now();
    algorithm(a, 0, s-1);
    end = high_resolution_clock::now();

    time = duration_cast<milliseconds>(end - start).count();

    std::cout << "Array[" << s << "] of float" << std::endl;
    std::cout << "Sorting time: " << time << "[ms]" << std::endl;
    
}