#include <iostream>
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <cmath>
#include <vector>
#include <chrono>
#include <map>
#include <iterator>

#include "hash table.h"
#include "AVL.h"

using namespace std;
const int ELEMENT_COUNT = 100000;
const int PRECISION = 5;
const int OP_COUNT = 3;

void vectorRandomFill(vector<int> &arr)
{
    int randomNum;
    for (int i = 0; i < ELEMENT_COUNT; i++) {
        randomNum = rand() % 10;
        arr.push_back(randomNum);
    }
}

class Table {
private:
    std::chrono::duration<double, std::milli> opTime[OP_COUNT];
    map<int, string> opSigns;

    void clearTime()
    {
        for (auto &op: opTime) // clears old time of operators
        {
            op = std::chrono::milliseconds::zero();
        }
    }

    void printTime(int elem)
    {
        cout << setw(10) << right << elem << " |";
        map<int, string>::iterator itr;
        for (itr = opSigns.begin(); itr != opSigns.end(); ++itr) {
            cout << setw(15) << right << fixed << setprecision(PRECISION)
                 << (opTime[itr->first] / elem).count() << " (in general: " << opTime[itr->first].count() << ")";
        } // time output
        clearTime();
    }

public:
    void calcTime(std::vector<int> arr, int elem)
    {
        auto opStart = std::chrono::high_resolution_clock::now();
        auto opFinish = std::chrono::high_resolution_clock::now();

        HashTable table(elem);
        AVL *avlTree = new AVL();
        std::vector<int> originalArr;
        map<int, string>::iterator itr;

        originalArr = arr;
        for (int i = 1; i < elem; i++) {
            for (itr = opSigns.begin(); itr != opSigns.end(); ++itr) {
                switch (itr->first) {
                    case 0:
                        opStart = std::chrono::high_resolution_clock::now();
                        table.insertElement(arr[i]);
                        opFinish = std::chrono::high_resolution_clock::now();
                        break;
                    case 1:
                        opStart = std::chrono::high_resolution_clock::now();
                        table.removeElement(arr[i]);
                        opFinish = std::chrono::high_resolution_clock::now();
                        break;
                    case 2:
                        opStart = std::chrono::high_resolution_clock::now();
                        avlTree->node = avlTree->insertNode(avlTree->node, arr[i]);
                        opFinish = std::chrono::high_resolution_clock::now();
                        break;

                    default:
                        break;
                }

                std::chrono::duration<double, std::milli> elapsedSeconds = opFinish - opStart;
                opTime[itr->first] += elapsedSeconds;
                arr = originalArr;
            }
        }
        this->printTime(elem); // time output in general

        cout << endl;
    }

    void printHeader()
    {
        cout << setw(50) << right << "TIME in ms Arg"
             << setw(100) << "TIME in ms in general" << std::endl;
        std::cout << setw(12) << right << "elem ";

        map<int, string>::iterator itr;
        for (itr = opSigns.begin(); itr != opSigns.end(); ++itr) {
            cout << setw(35) << right << itr->second;
        }

        cout << endl;
    }

    void insertFunctionNames(const vector<string>& arr)
    {
        int x = 0;
        for (const auto& i: arr) {
            opSigns.insert(pair<int, string>(x, i));
            x++;
        }
    }
};

int main()
{
    srand(time(nullptr));
    vector<string> functions = {
            "hashTable_add",
            "hashTable_remove",
            "avl_add",
    };

    vector<int> arr;
    vectorRandomFill(arr);

    Table randomNumbers;
    randomNumbers.insertFunctionNames(functions);
    randomNumbers.printHeader();

    for (int elem = 5; elem <= ELEMENT_COUNT; elem *= 2) {
        randomNumbers.calcTime(arr, elem);
    }
    cout << endl;


    return 0;
}
