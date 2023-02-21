#include <iostream>
#include <cmath>

#define PI 3.14159265358979323846  // Число Пи с точностью 20 знаков после запятой

// Функция для вывода элементов массива в консоль
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
// В качестве аргумента принимается ссылка. "const" означает, что этот параметр не изменяется
// a бОльшая длиная катета самого первого треугольника
double traingles_area_sum(const double& a, const int& n) {
    double sum = 0;
    double l_cat = 0;  // (long cathet) длинный катет
    for (int i = 1; i <= n; i++) {
        // Формула площади прямоугольного треугольника: (a * b) / 2
        l_cat = a / i;
        // Длина меньшего катета равна квадратному корню длины большего
        sum += (l_cat * sqrt(l_cat)) / 2;
    }
    return sum;
}

// 2 задание
// Функция перемещает элементы массива, принадлежащие отрезку [c, d] с < d в начало массива
// size - размер массива
void move_to_start(int arr[], const int& size, const int& c, const int& d) {
    // Проверяем выполнение условия c < d, 
    // а также то, что правая граница отрезка не выходит за пределы массива
    if (c >= d || d > size) {
        std::cout << "Введен неправильный отрезок" << std::endl;
        return;
    }

    int temp = 0;
    int i_start = 0; // Индекс начинающийся с нуля в который будем ложить значение из отрезка
    for (int i = 0; i < size; i++) {
        if (arr[i] >= c && arr[i] <= d) {
            temp = arr[i];
            arr[i] = arr[i_start];
            arr[i_start] = temp;
            i_start++;
        }
    }

}

// 3 задание
// Функция для вычисления гиперболического синуса с точностью до e
double sh(double const& x, double const& e) {
    double result = 0;  // результат, сумма ряда
    double member = 0;  // член
    for (int n = 0; n < 300; n++) {
        member = 1;
        for (int k = 1; k <= (2 * n + 1); k++) {
            member *= x / k;
        }

        result += member;
        if (fabs(member) < e) {
            return result;
        }
    }
    return result;
}

int main() {

    // Код проверяющий второе задание снизу
    // int arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
    // print_array(arr, std::size(arr));
    // move_to_start(arr, std::size(arr), 4, 9);
    // print_array(arr, std::size(arr));

    // Код проверяющий третье задание
    // double x = 10;
    // std::cout << sinh(x) << std::endl;
    // std::cout << sh(x, 0.0001) << std::endl;

}