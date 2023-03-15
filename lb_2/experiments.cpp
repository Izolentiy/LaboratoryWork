#include "utils.cpp"

void exchange(float a[], int i, int j) {
    float t = a[i];
    a[i] = a[j]; a[j] = t;
}

int partition(float a[], int l, int r) {
    int i = l, j = r - 1;
    while (true) {
        for (i; a[i] < a[r]; i++);
        for (j; a[j] > a[r]; j--);
        if (j <= i) break;
        exchange(a, i, j);
    }
    exchange(a, i, r);
    return i;
}

void quick_sort(float a[], int l, int r) {
    if (r <= l) return;

    int i = partition(a, l, r);
    quick_sort(a, l, i - 1);
    quick_sort(a, i + 1, r);
}

void stack_and_heap_arrays() {
    uint32_t s = 131072;
    // Массив алоцированный в стеке, это плохо, особенно если объект большой!
    float a[s];
    // Массив алоцированный на куче, в стеке алоцирован указатель на 0 элемент
    float *b = new float[s];
    fill_array(a, s, 0, 1024);
    fill_array(b, s, 0, 1024);

    qsort(a, s, sizeof(float), {});

    run_with_time_measurement(a, s, quick_sort);
    run_with_time_measurement(b, s, quick_sort);
}

struct Animal {
    char name[32];
    bool is_alive = true;
};

void struct_experiments() {
    using namespace std;

    Animal animal_s = Animal{"Cat", false}; // Алоцирование на стеке
    Animal *animal_h = new Animal{"Dog"}; // Алоцирование на куче

    cout << sizeof(animal_s) << endl;
    cout << sizeof(animal_h) << endl;

    cout << animal_s.name << ' ';
    cout << animal_s.is_alive << endl;

    cout << (*animal_h).name << ' ';
    cout << animal_h -> is_alive << endl;
}

int main() {
    // stack_and_heap_arrays();
    struct_experiments();
    return 0;
}