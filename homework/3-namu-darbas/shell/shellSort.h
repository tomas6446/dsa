
#ifndef SELECTIONSORT_H
#define SELECTIONSORT_H

#include <vector>
#include "iostream"
#include "cmath"

template<typename T>
void swap(T &a, T &b) {
    T tmp = a;
    a = b;
    b = tmp;
}

template<typename T>
void shellSort(std::vector<T> &arr) {
    if (arr.empty() || arr.size() < 2) {
        return;
    }
    int j;
    for (int increment = pow(2, (int) (log(arr.size()) / log(2))) - 1; increment > 0; increment /= 2) {
        for (int i = increment; i < arr.size(); i++) {
            T tmp = arr[i];
            for (j = i; j >= increment; j -= increment) {
                if (tmp < arr[j - increment]) {
                    arr[j] = arr[j - increment];
                } else {
                    break;
                }
            }
            arr[j] = tmp;
        }
    }
}

#endif