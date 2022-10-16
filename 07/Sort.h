#ifndef SORT_H
#define SORT_H

#include <iostream>
#include <vector>

using namespace std;


struct Node {
    int key;
    struct Node *left, *right;
};

struct Node *newNode(int item)
{
    struct Node *temp = new Node;
    temp->key = item;
    temp->left = temp->right = nullptr;
    return temp;
}

void storeSorted(Node *root, std::vector<int> arr, int &i)
{
    if (root != nullptr) {
        storeSorted(root->left, arr, i);
        arr[i++] = root->key;
        storeSorted(root->right, arr, i);
    }
}

Node *insert(Node *node, int key)
{

    if (node == nullptr) {
        return newNode(key);
    }
    if (key < node->key) {
        node->left = insert(node->left, key);
    }
    else if (key > node->key) {
        node->right = insert(node->right, key);
    }
    return node;
}

void treeSort(std::vector<int> arr, int n)
{
    struct Node *root = nullptr;
    root = insert(root, arr[0]);
    for (int i = 1; i < n; i++) {
        root = insert(root, arr[i]);
    }
    int i = 0;
    storeSorted(root, arr, i);
}


void heapify(std::vector<int> arr, int n, int i)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest]) {
        largest = l;
    }
    if (r < n && arr[r] > arr[largest]) {
        largest = r;
    }

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(std::vector<int> arr, int n)
{
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
    for (int i = n - 1; i >= 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

int partition(std::vector<int> arr, int start, int end)
{
    int pivot = arr[start];

    int count = 0;
    for (int i = start + 1; i <= end; i++) {
        if (arr[i] <= pivot) {
            count++;
        }
    }

    int pivotIndex = start + count;
    swap(arr[pivotIndex], arr[start]);

    int i = start, j = end;

    while (i < pivotIndex && j > pivotIndex) {

        while (arr[i] <= pivot) {
            i++;
        }
        while (arr[j] > pivot) {
            j--;
        }
        if (i < pivotIndex && j > pivotIndex) {
            swap(arr[i++], arr[j--]);
        }
    }
    return pivotIndex;
}

void quickSort(std::vector<int> arr, int start, int end)
{
    if (start >= end) {
        return;
    }
    int p = partition(arr, start, end);

    quickSort(arr, start, p - 1);
    quickSort(arr, p + 1, end);
}

void merge(std::vector<int> arr, int const left, int const mid, int const right)
{
    auto const subarrOne = mid - left + 1;
    auto const subarrTwo = right - mid;

    auto *leftarr = new int[subarrOne],
            *rightarr = new int[subarrTwo];

    for (auto i = 0; i < subarrOne; i++)
        leftarr[i] = arr[left + i];
    for (auto j = 0; j < subarrTwo; j++)
        rightarr[j] = arr[mid + 1 + j];

    auto indexOfSubarrOne = 0,
            indexOfSubarrTwo = 0;
    int indexOfMergedarr = left;

    while (indexOfSubarrOne < subarrOne && indexOfSubarrTwo < subarrTwo) {
        if (leftarr[indexOfSubarrOne] <= rightarr[indexOfSubarrTwo]) {
            arr[indexOfMergedarr] = leftarr[indexOfSubarrOne];
            indexOfSubarrOne++;
        }
        else {
            arr[indexOfMergedarr] = rightarr[indexOfSubarrTwo];
            indexOfSubarrTwo++;
        }
        indexOfMergedarr++;
    }

    while (indexOfSubarrOne < subarrOne) {
        arr[indexOfMergedarr] = leftarr[indexOfSubarrOne];
        indexOfSubarrOne++;
        indexOfMergedarr++;
    }

    while (indexOfSubarrTwo < subarrTwo) {
        arr[indexOfMergedarr] = rightarr[indexOfSubarrTwo];
        indexOfSubarrTwo++;
        indexOfMergedarr++;
    }
}

void mergeSort(std::vector<int> arr, int const begin, int const end)
{
    if (begin >= end) {
        return;
    }
    auto mid = begin + (end - begin) / 2;
    mergeSort(arr, begin, mid);
    mergeSort(arr, mid + 1, end);
    merge(arr, begin, mid, end);
}

#endif
