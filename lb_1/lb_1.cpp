#include <iostream>
#include <math.h>

using namespace std;

// ##### 11 вариант #####

// ##### 1 задание #####
/*
Функция для подсчета веса пирамиды
\param n количество слоев в пирамиде. В каждом слое n ^ 2 кубиков. На самом верхнем слое 1 кубик.
\param weight вес одного кубика
*/
int weight_calc(int n, int weight) {
    return n^2 * weight;
}

void pyramid_weight() {
    int n = 10, weight = 15;
    cout << "Weight of pyramid: " << weight_calc(n, weight) << endl;
}

// ##### 2 задание #####
/*
Функция для смещения элементов массива влево на k-ый элемент
\param ptr_0 указатель на нулевой элемент массива. Можно передать имя массива в качестве аргумента
\param arr_size размер массива
\param k на какой элемент нужно сместиться. К примеру если передать k = 1, то значение нулевого элемента станет равно первому, значение первого элемента второму и так далее. k >= 0
*/
void shift(int* ptr_0, int arr_size, int k) {
    for (int i = 0; i < arr_size; i++) {
        *(ptr_0 + i) = *(ptr_0 + i + k);
    }
}

void shift_runner() {
    
    int arr[] = {1, 2, 3, 4};
    // 1 {2, 3, 4, ?}
    shift(arr, size(arr), 1);

    for (int i = 0; i < size(arr); i++) {
        cout << arr[i] << endl;
    }

}

// ##### 3 задание #####
double x(double& t) {
    return 3 * t + 8;
}

double y(double& t) {
    return sqrt(t);
}

double f(double x, double y) {
    return 7 * (x * x) - (13 / y) + cos(x + y);
}

void math_test() {
    double t = 15.3;
    cout << f(x(t), y(t)) << endl;
}

// ##### main #####
int main(){

    // 1 задание
    // pyramid_weight();

    // 2 задание
    // shift_runner();

    // 3 задание
    // math_test();

    return 0;
}