#ifndef DATA_H
#define DATA_H

#include <iostream>

namespace ADT {
    using namespace std;

    template<typename T>
    class Tree {
    private:
        T *arr;
        int current;
        int capacity;
        static int maxSize;
    public:
        Tree() {
            current = 0;
            capacity = 1;
            arr = new T[capacity];
        }

        ~Tree() = default;

        void add(int pos, T val) {
            if (pos < 0 || pos > capacity) {
                return;
            } else if (pos == capacity) {
                addLast(val);
            } else {
                arr[pos] = val;
                current++;
            }
        }

        void addFirst(T val) {
            if (current == capacity) {
                T *temp = new T[2 * capacity];
                for (int i = 0; i < capacity; i++) {
                    temp[i] = arr[i];
                }
                delete[] arr;
                capacity *= 2;
                arr = temp;
            }
            for (int i = current; i >= 0; i--) {
                arr[i] = arr[i - 1];
            }
            arr[0] = val;
            current++;
            maxSize = maxSize < current ? current : maxSize;
        }

        void addLast(T val) {
            if (current == capacity) {
                T *temp = new T[2 * capacity];
                for (int i = 0; i < capacity; i++) {
                    temp[i] = arr[i];
                }
                delete[] arr;
                capacity *= 2;
                arr = temp;
            }
            arr[current] = val;
            current++;
            maxSize = maxSize < current ? current : maxSize;
        }

        void remove(int pos) {
            if (pos > current || pos < 0) {
                return;
            }
            for (int i = pos; i < current - 1; i++) {
                arr[i] = arr[i + 1];
            }
            current--;
            maxSize = maxSize < current ? current : maxSize;
        }

        void removeVal(T val) {
            for (int i = 0; i < current; i++) {
                if (arr[i] == val) {
                    remove(i);
                    return;
                }
            }
        }

        void removeFirst() {
            remove(0);
        }

        void removeLast() {
            current--;
            maxSize = maxSize < current ? current : maxSize;
        }

        void print() {
            for (int i = 0; i < current; i++) {
                cout << arr[i] << " ";
            }
            cout << endl;
        }

        T get(int pos) {
            if (pos > current || pos < 0) {
                return 0;
            }
            return arr[pos];
        }

        bool getVal(T val) {
            for (int i = 0; i < current; i++) {
                if (arr[i] == val) {
                    return true;
                }
            }
            return false;
        }

        T getFirst() {
            if (current > 0) {
                return arr[0];
            }
            return 0;
        }

        T getLast() {
            if (current > 0) {
                return arr[current - 1];
            }
            return 0;
        }

        int getSize() {
            return current;
        }

        int getMaxSize() {
            return maxSize;
        }

        void destroy() {
            current = 0;
            capacity = 1;
            maxSize = 0;
            delete arr;
        }

        T operator[](int index) {
            return arr[index];
        }

    };

    template<typename T>
    int Tree<T>::Tree::maxSize = 0;
}

#endif
