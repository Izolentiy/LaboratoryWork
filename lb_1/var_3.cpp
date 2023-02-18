#include <iostream>
#include "utils.cpp"

#define ARR_SIZE 7

/**
 * Функция производящая циклический сдвиг элементов массива влево на k элементов
 * @param arr[] массив, в котором надо произвести сдвиг
 * @param size размер массива
 * @param k количество элементов сдвига
 */
void cycle_shift(int arr[], int size, int k) {
    if (k < 0) {
        std::cout << "Illegal shift value" << std::endl;
        return;
    }

    k %= size;
    if (size % 2 == 0) {
        int pair_elem = 0;
        for (int i = 0; i < (size / 2); i++) {
            pair_elem = arr[i];

            arr[i] = arr[(k + i) % size];
            arr[(k + i) % size] = pair_elem;
        }
    } else {
        int elem_0 = arr[0];
        for (int i = 0; i < size; i++) {
            if (i == size - 1) {
                arr[(k * i) % size] = elem_0;
                break;
            }
            
            arr[(k * i) % size] = arr[(k * (i + 1)) % size];
        }
    }
}

/**
 * Функция производящая циклический сдвиг элементов массива влево на k элементов. (Реализованна через указатели)
 * @param ptr_0 указатель на нулевой элемент массива
 * @param size размер массива
 * @param k количество элементов сдвига
 */
void cycle_shift_ptr(int* ptr_0, int size, int k) {
    if (k < 0) {
        std::cout << "Illegal shift value" << std::endl;
        return;
    }

    k %= size;
    if (size % 2 == 0) {
        int pair_elem = 0;
        for (int i = 0; i < (size / 2); i++) {
            pair_elem = *(ptr_0 + i);

            *(ptr_0 + i) = *(ptr_0 + ((k + i) % size));
            *(ptr_0 + ((k + i) % size)) = pair_elem;
        }
    } else {
        int elem_0 = *ptr_0;
        for (int i = 0; i < size; i++) {
            if (i == size - 1) {
                *(ptr_0 + ((k * i) % size)) = elem_0;
                break;
            }
            
            *(ptr_0 + ((k * i) % size)) = *(ptr_0 + ((k * (i + 1)) % size));
        }
    }
}

int main() {
    int arr[ARR_SIZE] = {0, 1, 2, 3, 4, 5, 6};

    print_array(arr, ARR_SIZE);
    cycle_shift_ptr(arr, ARR_SIZE, 9);
    print_array(arr, ARR_SIZE);

    return 0;
}