#include "utils.cpp"

/**
 * Cортировка выбором элементов с индексами  в отрезке [l, r]
 * @param l левый индекс
 * @param r правый индекс
 */
void choosing_sort(float a[], int l, int r) {
    float t = 0;
    for (int i = l; i < r; i++) {
        for (int j = i+1; j <= r; j++) {
            if (a[j] < a[i]) {
                t = a[j];
                a[j] = a[i];
                a[i] = t;
            }
        }
    }
}

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
 * Сортировка вставками элементов с индексами  в отрезке [l, r]
 * @param l левый индекс
 * @param r правый индекс
 */
void inserting_sort(float a[], int l, int r) {
    float t = 0;
    for (int i = l; i <= r; i++) {
        for (int j = l; j < i; j++) {
            // std::cout << std::fixed << std::setprecision(0) << a[i] << ' ' << a[j] << std::endl;
            
            if (a[i] < a[j]) {
                t = a[i];
                for (int k = i; k > j; k--) {
                    a[k] = a[k-1];
                }
                a[j] = t;
                
                // print_array(a, 6, 0, 0);
            }

        }
    }
}

void time_complexity_growth_example() {
    uint16_t s = 32767;
    float min = 0, max = 1024;
    
    float *a = new float[s];
    fill_array(a, s, min, max);
    
    // Элементанрые алгоритмы сортировки. O(n^2) время выполнения
    // программы состоит в квадратичной зависимости от количества элементов
    
    // bubble_sort(a, 0, s-1);
    // inserting_sort(a, 0, s-1);
    // choosing_sort(a, 0, s-1);
    run_sorting_with_time_measurement(a, s, inserting_sort);

    s = 65535;
    float *b = new float[s];
    fill_array(b, s, min, max);
    
    run_sorting_with_time_measurement(b, s, inserting_sort);

}

void printing_example() {
    uint16_t s = 7;
    float min = 0, max = 1024;
    
    float *a = new float[s];

    fill_array(a, s, min, max);
    print_array(a, s, false, 0);
    
    // bubble_sort(a, 0, s-1);
    inserting_sort(a, 0, s-1);
    // choosing_sort(a, 0, s-1);
    
    print_array(a, s, false, 0);
}

int main() {
    time_complexity_growth_example();
    
    return 0;
}