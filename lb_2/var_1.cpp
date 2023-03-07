#include <iostream>
#include "utils.cpp"

/**
 * Пузырьковая сортировка элементов с индексами  в отрезке [l, r]
 * @param l левый индекс
 * @param r правый индекс
 */
void bubble_sort(float a[], int l, int r) {
    float t = 0;
    for (int i = l; i < r; i++) {
        for (int j = r; j > i; j--) {

            if (a[j - 1] > a[j]) {
                t = a[j - 1];
                a[j - 1] = a[j];
                a[j] = t;
            }

        }
    }
}

/**
 * 
 */
void inserting_sort(float a[], int l, int r) {

}

int main() {
    using std::cin, std::cout, std::endl;

    // cout << "Enter size of array: ";
    // int s; cin >> s;

    // cout << "min value: ";
    // float min; cin >> min;

    // cout << "max value: ";
    // float max; cin >> max;

    int s = 6;
    float min = 0, max = 1024;
    
    float* a = new float[s];

    fill_array(a, s, min, max);
    print_array(a, s);
    bubble_sort(a, 0, s-1);
    print_array(a, s);
    
    return 0;
}