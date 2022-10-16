#include <iostream>
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <cmath>
#include <vector>
#include <chrono>
#include "Sort.h"

using namespace std;
const int ELEMENT_COUNT = 100000;
const int PRECISION = 5;
const int OP_COUNT = 4;

class Table {
private:
    std::chrono::duration<double, std::milli> opTime[OP_COUNT], opAverage[OP_COUNT];
    string opSigns[OP_COUNT] = {"Tree", "Heap", "Quick", "Merge"};

    void clearTime()
    {
        for (auto &op: opTime) // clears old time of operators
        {
            op = std::chrono::milliseconds::zero();
        }
    }

    void clearAverage()
    {
        for (auto &op: opAverage) // clears old average time of operators
        {
            op = std::chrono::milliseconds::zero();
        }
    }

    void printTime(int elem)
    {
        cout << setw(10) << right << elem << " |";
        for (auto &op: opTime) {
            cout << setw(15) << right << fixed << setprecision(PRECISION) << op.count();
        } // time output
        clearTime();
    }

    void printAverage(int elem)
    {
        cout << setw(10) << right << elem << " |";
        for (auto &op: opAverage) {
            op /= elem;
            cout << setw(15) << right << fixed << setprecision(PRECISION) << op.count();
        }
        clearAverage();
    }

public:
    void calcTime(std::vector<int> arr, int elem)
    {
        auto opStart = std::chrono::high_resolution_clock::now();
        auto opFinish = std::chrono::high_resolution_clock::now();

        std::vector<int> originalArr;
        originalArr = arr;

        for (int op = 0; op < OP_COUNT; op++) {
            arr = originalArr;

            if (opSigns[op] == "Tree") {
                opStart = std::chrono::high_resolution_clock::now();
                treeSort(arr, elem);
                opFinish = std::chrono::high_resolution_clock::now();
            }
            else if (opSigns[op] == "Heap") {
                opStart = std::chrono::high_resolution_clock::now();
                heapSort(arr, elem);
                opFinish = std::chrono::high_resolution_clock::now();
            }
            else if (opSigns[op] == "Quick") {
                opStart = std::chrono::high_resolution_clock::now();
                quickSort(arr, 0, elem);
                opFinish = std::chrono::high_resolution_clock::now();
            }
            else if (opSigns[op] == "Merge") {
                opStart = std::chrono::high_resolution_clock::now();
                mergeSort(arr, 0, elem);
                opFinish = std::chrono::high_resolution_clock::now();
            }

            std::chrono::duration<double, std::milli> elapsedSeconds = opFinish - opStart;
            opTime[op] += elapsedSeconds;
            opAverage[op] = opTime[op];
        }

        this->printAverage(elem); // time output for average of every element
        this->printTime(elem); // time output in general

        cout << endl;
    }

    void printHeader()
    {
        std::cout << setw(12) << right << "elem";
        for (std::string &opSign: opSigns) {
            cout << setw(15) << right << opSign;
        }
    }
};

int main()
{
    srand(time(nullptr));

    int randomNum;
    std::vector<int> arr;
    for (int i = 0; i < ELEMENT_COUNT; i++) {
        randomNum = rand() % 10;
        arr.push_back(randomNum);
    }

    Table randomNumbers;
    cout << setw(50) << right << "TIME in ms Arg" << setw(100) << "TIME in ms in general" << std::endl;
    randomNumbers.printHeader();
    randomNumbers.printHeader();
    cout << endl;

    for (int elem = 5; elem <= ELEMENT_COUNT; elem *= 2) {
        randomNumbers.calcTime(arr, elem);
    }
    cout << endl;


    return 0;
}
