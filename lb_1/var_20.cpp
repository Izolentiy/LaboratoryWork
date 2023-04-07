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
// a = {0, 1, 2, 3, 4, 5}; c = 2
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

void uvelichenie(int& chislo) {
    chislo += 1;
}

void primer() {
    int g = 69;  // объявили переменную g
    int* adres_g = &g;  // указатель. "&g" - взятие адреса
    int& vtoroe_imya_g = g;  // ссылка на g
    int ne_g = g;  // другая переменная
    
    g += 1; // g = 70, vtoroye_imya_g = 70
    vtoroe_imya_g -= 1; // g = 69
    adres_g -= 1; // g = 68

    using namespace std;
    int chislo = 69;
    cout << chislo << endl; // выведем "результат" операции
    int& vtoroe_imya = chislo;
    uvelichenie(chislo);
    cout << chislo << endl; // выведем "результат" операции

    int* adres_chisla = &chislo;
    cout << "Adres chisla: " << adres_chisla << " chislo" << *adres_chisla << endl;
    cout << "Izmenenniy adres chisla: " << --adres_chisla << " to chto lezhit po etomu adresu" << *adres_chisla << endl;



}

int main() {

    primer();

    // // Код проверяющий второе задание
    // int radius_samogo_pervogo_shara = 4;
    // int n = 2;
    // int result = calculate_area(radius_samogo_pervogo_shara, 2);

    // // Код проверяющий второе задание снизу
    // using namespace std;
    // int arr[] = {1, 2, 3, 4, 5, 6}; // мы создаем массив
    
    // print_array(arr, size(arr)); // мы его выводим на экран
    // swap_elements(arr, size(arr), 2); // воздействуем на массив
    // print_array(arr, size(arr)); // печатаем изменнённый массив

    // // Код проверяющий третье задание
    // double result = f(x(10), y(x(10), 10));

}