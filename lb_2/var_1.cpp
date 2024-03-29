#include "utils.cpp"

/**
 * Cортировка выбором элементов с индексами  в отрезке [l, r]
 * предпочтителен, когда затраты ресурсов на сравнение ключей намного меньше
 * затрат ресурсов на перемещение элементов
 * @param l левый индекс
 * @param r правый индекс
 */
void choosing_sort(float a[], int l, int r) {
    float t = 0;
    for (int i = l; i < r; i++) {
        int min = i;
        for (int j = i+1; j <= r; j++)
            if (a[j] < a[min]) min = j;
        t = a[i];
        a[i] = a[min];
        a[min] = t;
    }
}

/**
 * Пузырьковая сортировка элементов с индексами  в отрезке [l, r]
 * 
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
 * Вариант реализации, который пришел в голову изначально.
 * @param l левый индекс
 * @param r правый индекс
 */
void inserting_sort(float a[], int l, int r) {
    // using std::cout, std::fixed, std::setprecision, std::endl;
    float t = 0;
    for (int i = l; i <= r; i++) {
        for (int j = l; j < i; j++) {
            
            if (a[i] < a[j]) {
                t = a[i];
                for (int k = i; k > j; k--) {
                    a[k] = a[k-1];
                }
                a[j] = t;
                
                // cout << fixed << setprecision(0) << a[i] << ' ' << a[j] << endl;
                
                // print_array(a, l, r, 0, 0);
            }

        }
    }
}

/**
 * Вариант реализации из книги
 */
void inserting_sort_from_book(float a[], int l, int r) {
    // using std::cout, std::fixed, std::setprecision, std::endl;
    
    int i;
    float t;
    // Помещение наименьшего элемента массива на первую позицию
    for (i = r; i > l; --i) {
        if (a[i-1] > a[i]) {
            t = a[i];
            a[i] = a[i-1];
            a[i-1] = t;
        }
    }
    // print_array(a, l, r, 0, 0);
    
    for (i = l+2; i <= r; ++i) {
        int j = i; float v = a[j];
        while (v < a[j-1]) {
            a[j] = a[j-1]; --j;
        }
        // cout << fixed << setprecision(0) << v << ' ' << a[j] << endl;
        a[j]= v;
        
        // print_array(a, l, r, 0, 0);
    }
}

void inserting_sort_reworked(float a[], int l, int r) {
    float t;
    int i, j;
    for (i = r; i > l; --i) {
        if (a[i] < a[i-1]) {
            t = a[i];
            a[i] = a[i-1];
            a[i-1] = t;
        }
    }
    for (i = l+2; i <= r; ++i) {
        j = i; t = a[j];
        while (t < a[j-1]) {
            a[j] = a[j-1]; --j;
        }
        a[j] = t;
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
    for (i = l; i <= m; i++) b[i] = a[i];
    for (j = m; j < r; j++) b[r + m - j] = a[j + 1];
    i = l;
    for (int k = l; k <= r; k++)
        if (b[j] < b[i])
            a[k] = b[j--];
        else a[k] = b[i++];
}

/**
 * Метод абстрактного обменного слияния
 * a[] = {1, 3, 4, 8, 2, 5, 6, 7}, 
 * где a[l] = 1, a[m] = 8, a[r] = 7
 * @param a массив который надо отсортировать
 * @param b вспомогательный массив такого же размера
 * @param l леавая граница отсортированного подмассива 1
 * @param m правая граница отсортированного подмассива 1
 * @param r правая граница отсортированного подмассива 2
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

void exchange(float a[], int i, int j) {
    float t = a[i];
    a[i] = a[j]; a[j] = t;
}

#define SPECIAL_SIZE 8

void special_print(float a[], int l, int r, int s) {
    std::cout << "{ ";
    for (int i = 0; i < s; ++i) {
        if (i >= l && i <= r) std::cout << a[i] << ' ';
        else std::cout << "  ";
    }
    std::cout << '}';
}

int partition(float a[], int l, int r) {
    int i = l, j = r - 1;

    special_print(a, l, r, SPECIAL_SIZE);
    std::cout << std::endl;

    while (true) {
        for (i; a[i] < a[r]; i++);
        for (j; a[j] > a[r]; j--);
        if (j <= i) break;
        exchange(a, i, j);
        // print_array(a, l, r, 0, 0);
    }
    exchange(a, i, r);
    // print_array(a, l, r, 0, 0);
    // print_array(a, 0, 8-1, 0, 0);
    
    special_print(a, l, r, SPECIAL_SIZE);
    std::cout << "; elements < " << a[i] << ": " << i - l << std::endl;
    return i;
}

void quick_sort(float a[], int l, int r) {
    if (r <= l) return;

    int i = partition(a, l, r);
    quick_sort(a, l, i - 1);
    quick_sort(a, i + 1, r);
}

void time_complexity_example() {
    float min = 0, max = 1024;
    
    uint32_t s = 24000;
    float *a = new float[s];
    fill_array(a, s, min, max);
    
    // s = 131072;
    float *b = new float[s];
    fill_array(b, s, min, max);
    
    // Элементарные алгоритмы сортировки. O(n^2) время выполнения
    // программы состоит в квадратичной зависимости от количества элементов
    // bubble_sort(), choosing_sort(), inserting_sort()

    // Более продвинутые алгоритмы сортировки O(N*logN) время выполнения
    // программы состоит в квазилинейной зависимости от количества элементов
    // quick_sort(), merge_sort()

    float *c = new float[s];
    fill_array(c, s, min, max);

    print_array(a, 0, 5, 0, 0);
    print_array(b, 0, 5, 0, 0);

    run_with_time_measurement(c, s, merge_sort);
    run_with_time_measurement(b, s, inserting_sort_from_book);
    run_with_time_measurement(a, s, inserting_sort_from_book);
}

void printing_example() {
    uint16_t s = SPECIAL_SIZE;
    float min = 0, max = 9;
    
    float *a = new float[s];
    float *b = new float[s];

    fill_array(a, s, min, max);
    fill_array(b, s, min, max);

    print_array(a, 0, s-1, false, 0);
    // quick_sort(a, 0, s-1);
    // merge_sort(a, 0, s-1);
    // bubble_sort(a, 0, s-1);
    inserting_sort_reworked(a, 0, s-1);

    std::cout << '\n' << std::endl;
    print_array(a, 0, s-1, false, 0);

    // print_array(b, 0, s-1, false, 0);
    // inserting_sort(b, 0, s-1);
    
}

void comparison_example() {
    using namespace std;

    float f_1 = 1.5;
    float f_2 = 1.49999999; // == f_1
    float f_3 = 1.4999999; // != f_1

    cout << boolalpha;
    cout << "f_1 == f_2: " << (f_1 == f_2) << endl;
    cout << "f_1 == f_3: " << (f_1 == f_3) << endl;
    cout << "f_2 == f_3: " << (f_2 == f_3) << endl;

    float my_epsilon = 0.000001;    
    cout << fixed << setprecision(20) << f_2 - f_3 << '\n'
         << "f_2 == f_3: " << (fabs(f_2 - f_3) < my_epsilon)
         << endl;
    cout << fixed << setprecision(20) << f_2 - f_3 << '\n'
         << "f_2 == f_3: " << (fabs(f_2 - f_3) < __FLT_EPSILON__)
         << endl;

}

int main() {
    time_complexity_example();
    // printing_example();
    // comparison_example();
    
    return 0;
}