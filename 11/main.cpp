#include <iostream>
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <cmath>
#include <vector>
#include <chrono>
#include <map>
#include <algorithm>
#include <iterator>

using namespace std;
const int ELEMENT_COUNT = 1000;
const int PRECISION = 5;
const int OP_COUNT = 3;

#include "Dijkstra.h"

void vectorRandomFill(int arr[ELEMENT_COUNT][ELEMENT_COUNT])
{
    int randomNum;

    for (int i = 0; i < ELEMENT_COUNT; i++)
    {
        for (int j = 0; j < ELEMENT_COUNT; j++) {
            randomNum = rand() % 10;
            arr[i][j] = randomNum;
        }
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
                 << (opTime[itr->first] / elem).count() << " (general: " << opTime[itr->first].count() << ")";
        } // time output
        clearTime();
    }

public:
    void calcTime(int arr[ELEMENT_COUNT][ELEMENT_COUNT], int elem)
    {
        auto opStart = std::chrono::high_resolution_clock::now();
        auto opFinish = std::chrono::high_resolution_clock::now();


        map<int, string>::iterator itr;

        int originalArr[ELEMENT_COUNT][ELEMENT_COUNT];
        std::copy(&arr[0][0], &arr[0][0]+ELEMENT_COUNT*ELEMENT_COUNT,&originalArr[0][0]);

        for (int i = 1; i < elem; i++) {
            for (itr = opSigns.begin(); itr != opSigns.end(); ++itr) {
                switch (itr->first) {
                    case 0:
                        opStart = std::chrono::high_resolution_clock::now();
                        dijkstra(arr, 0, elem);
                        opFinish = std::chrono::high_resolution_clock::now();
                        break;
                    case 1:
                        opStart = std::chrono::high_resolution_clock::now();

                        opFinish = std::chrono::high_resolution_clock::now();
                        break;

                    default:
                        break;
                }

                std::chrono::duration<double, std::milli> elapsedSeconds = opFinish - opStart;
                opTime[itr->first] += elapsedSeconds;
                std::copy(&arr[0][0], &arr[0][0]+ELEMENT_COUNT*ELEMENT_COUNT,&originalArr[0][0]);
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

    void insertFunctionNames(const vector<string> &arr)
    {
        int x = 0;
        for (const auto &i: arr) {
            opSigns.insert(pair<int, string>(x, i));
            x++;
        }
    }
};

int main()
{
    srand(time(nullptr));
    vector<string> functions = {
            "Dijkstra",
            "A*",
    };
    int arr[ELEMENT_COUNT][ELEMENT_COUNT] = {
            {0, 5, 3, 0},
            {5,0,1,2},
            {3,1,0,4},
            {0,2,4,0}
    };
    dijkstra(arr, 0, ELEMENT_COUNT);
    //vectorRandomFill(arr);

    Table randomNumbers;
    randomNumbers.insertFunctionNames(functions);
    randomNumbers.printHeader();

    for (int elem = 5; elem <= ELEMENT_COUNT; elem *= 2) {
        randomNumbers.calcTime(arr, elem);
    }
    cout << endl;


    return 0;
}
