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

/**
 * Метод абстрактного обменного слияния
 * Реализация через массив со статическим классом памяти
 * Примечение: Нельзя использовать слишком большой размер
 * больше 10^8 (возможно верхняя граница чуть выше, но точно
 * меньше 6 * 10^8)
 */
void merge(float a[], int l, int m, int r) {
    static float b[UINT16_MAX];
    int i, j;
    for (i = m + 1; i > l; i--) b[i - 1] = a[i - 1];
    for (j = m; j < r; j++) b[r + m - j] = a[j + 1];
    for (int k = l; k <= r; k++)
        if (b[j] < b[i])
            a[k] = b[j--];
        else a[k] = b[i++];
}

/**
 * Метод абстрактного обменного слияния
 */
void merge(float a[], float b[], int l, int m, int r) {
    int i, j;
    for (i = m + 1; i > l; i--) b[i - 1] = a[i - 1];
    for (j = m; j < r; j++) b[r + m - j] = a[j + 1];
    for (int k = l; k <= r; k++)
        if (b[j] < b[i])
            a[k] = b[j--];
        else a[k] = b[i++];
}

void merge_sort_helper(float a[], float b[], int l, int r) {
    if (r <= l) return;

    int m = (l + r) / 2;
    merge_sort_helper(a, b, l, m);
    merge_sort_helper(a, b, m + 1, r);

    merge(a, b, l, m, r);
}

void merge_sort(float a[], int l, int r) {
    float *b = new float[r - l + 1];
    merge_sort_helper(a, b, l, r);
    delete[] b;
}

void time_complexity_example() {
    uint32_t s = 32747;
    float min = 0, max = 1024;
    
    float *a = new float[s];
    fill_array(a, s, min, max);
    
    // Элементанрые алгоритмы сортировки. O(n^2) время выполнения
    // программы состоит в квадратичной зависимости от количества элементов
    
    // bubble_sort(a, 0, s-1);
    // inserting_sort(a, 0, s-1);
    // choosing_sort(a, 0, s-1);
    // run_with_time_measurement(a, s, bubble_sort);
    run_with_time_measurement(a, s, merge_sort);

    s = 65535;
    float *b = new float[s];
    fill_array(b, s, min, max);
    
    // run_with_time_measurement(b, s, bubble_sort);
    run_with_time_measurement(b, s, merge_sort);

}

void printing_example() {
    uint16_t s = 15;
    float min = 0, max = 1024;
    
    float *a = new float[s];

    fill_array(a, s, min, max);
    print_array(a, s, false, 0);
    
    // bubble_sort(a, 0, s-1);
    // inserting_sort(a, 0, s-1);
    // choosing_sort(a, 0, s-1);
    merge_sort(a, 0, s-1);
    
    print_array(a, s, false, 0);
}

int main() {
    time_complexity_example();
    // printing_example();
    
    return 0;
}