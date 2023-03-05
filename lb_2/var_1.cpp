#include <iostream>
#include "utils.cpp"

/**
 * 
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

int main() {
    using std::cin, std::cout, std::endl;

    cout << "Enter size of array: ";
    int s; cin >> s;

    cout << "min value: ";
    float min; cin >> min;

    cout << "max value: ";
    float max; cin >> max;
    
    float* a = new float[s];

    fill_array(a, s, min, max);
    print_array(a, s);
    bubble_sort(a, 0, s-1);
    print_array(a, s);
    
    return 0;
}