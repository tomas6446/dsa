#include <iostream>
#include <iomanip>
#include <cmath>
#include <ctime>
#include <vector>
#include <chrono>

using namespace std;
const int ELEMENT_COUNT = 100000;
const int PRECISION = 10;
const int OP_COUNT = 7;

const int CONSTANT = 10;

class Table
{
private:
    std::chrono::duration<double, std::milli> opTime[OP_COUNT], opAverage[OP_COUNT];
    char opSigns[OP_COUNT] = {'/', '*', '+', '-', '=', '>', '<'};

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

public:
    void calcOperatorTime(int var)
    {
        auto opStart = std::chrono::high_resolution_clock::now();
        auto opFinish = std::chrono::high_resolution_clock::now();
        for (int op = 0; op < OP_COUNT; op++)
        {
            switch (opSigns[op])
            {
                case '/':
                    opStart = std::chrono::high_resolution_clock::now();
                    var / CONSTANT;
                    opFinish = std::chrono::high_resolution_clock::now();
                    break;
                case '*':
                    opStart = std::chrono::high_resolution_clock::now();
                    var * CONSTANT;
                    opFinish = std::chrono::high_resolution_clock::now();
                    break;
                case '+':
                    opStart = std::chrono::high_resolution_clock::now();
                    var + CONSTANT;
                    opFinish = std::chrono::high_resolution_clock::now();
                    break;
                case '-':
                    opStart = std::chrono::high_resolution_clock::now();
                    var - CONSTANT;
                    opFinish = std::chrono::high_resolution_clock::now();
                    break;
                case '=':
                    opStart = std::chrono::high_resolution_clock::now();
                    var = CONSTANT;
                    opFinish = std::chrono::high_resolution_clock::now();
                    break;
                case '>':
                    opStart = std::chrono::high_resolution_clock::now();
                    var > CONSTANT;
                    opFinish = std::chrono::high_resolution_clock::now();
                    break;
                case '<':
                    opStart = std::chrono::high_resolution_clock::now();
                    var < CONSTANT;
                    opFinish = std::chrono::high_resolution_clock::now();
                    break;
                default:
                    break;
            }
            std::chrono::duration<double, std::milli> elapsedSeconds = opFinish - opStart;
            opTime[op] += elapsedSeconds;
            opAverage[op] = opTime[op];
        }

    }

    void printHeader()
    {
        cout << setw(50) << right << "TIME in ms" << endl << setw(12) << right << "elem";
        for (char & opSign: opSigns)
        {
            cout << setw(15) << right << opSign;
        }
        //cout << endl;
    }

    void printTime(int elem)
    {
        cout << setw(10) << right << elem << " |";
        for (auto & op : opTime)
        {
            cout << setw(15) << right << fixed << setprecision(PRECISION) << op.count();
        } // time output
        clearTime();
    }

    void printAverage(int elem)
    {
        cout << setw(10) << right << elem << " |";
        for (auto & op : opAverage)
        {
            op /= elem;
            cout << setw(15) << right << fixed << setprecision(PRECISION) << op.count();
        }
        clearAverage();
    }
};

void fillVector(vector<int> &array)
{
    for (auto &i: array)
    {
        i = rand() % 100 + 1;
    } // fills vector with random numbers.
}

int main()
{

    vector<int> array(ELEMENT_COUNT);
    srand(time(nullptr));
    fillVector(array);

    Table randomNumbers, constantNumbers;

    randomNumbers.printHeader();
    cout << endl;
    for (int elem = 1; elem <= ELEMENT_COUNT; elem *= 2)
    {
        for (int vect = 0; vect < elem; vect++)
        {
            randomNumbers.calcOperatorTime(array[vect]);
            constantNumbers.calcOperatorTime(1000);
        } // counts time of dividing, multiplying numbers. Number are stored in the vector, time stored in the Class randomNumbers

        randomNumbers.printAverage(elem); // time output for average of every element
        constantNumbers.printAverage(elem); // time output for average of every element

        randomNumbers.printTime(elem); // time output in general
        constantNumbers.printTime(elem); // time output in general

        cout << endl;
    }
    cout << endl;
    return 0;
}
