#ifndef SORT_H
#define SORT_H

#include "iostream"
#include "vector"

template<typename T>
void swap(T &a, T &b)
{
    T tmp = a;
    a = b;
    b = tmp;
}

template<typename T>
void insertionSort(std::vector<T> &arr, int low, int high) {
    for (int i = low + 1; i < high + 1; i++) {
        T value = arr[i];
        int j = i;
        while (j > low && arr[j - 1] > value) {
            arr[j] = arr[j - 1];
            j--;
        }
        arr[j] = value;
    }
}

template<typename T>
int partition(std::vector<T> &arr, int low, int high) {
    T pivot = arr[high];
    int i = low, j = low;
    for (; i < high; i++) {
        if (arr[i] < pivot) {
            swap(arr[i], arr[j]);
            j += 1;
        }
    }
    swap(arr[j], arr[high]);

    return j;
}

template<typename T>
void hybridQuickSort(std::vector<T> &arr, int low, int high) {
    if (arr.empty() || (low == 0 && high == 0)) {
        return;
    }
    while (low < high) {
        if (high - low + 1 < 10) {
            insertionSort(arr, low, high);
            break;
        } else {
            int pivot = partition(arr, low, high);
            if (pivot - low < high - pivot) {
                hybridQuickSort(arr, low, pivot - 1);
                low = pivot + 1;
            } else {
                hybridQuickSort(arr, pivot + 1, high);
                high = pivot - 1;
            }
        }
    }
}


#endif
