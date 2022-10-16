#include <iostream>
#include <ctime>
#include <iomanip>
#include <cmath>
#include <vector>
#include <chrono>

#include "Tree.h"
#include "AVL.h"
#include "LinkedList.h"
#include "ArrayList.h"

using namespace std;
const int ELEMENT_COUNT = 100000;
const int PRECISION = 10;
const int OP_COUNT = 4;

class Table
{
private:
    std::chrono::duration<double, std::milli> opTime[OP_COUNT], opAverage[OP_COUNT];
    char opSigns[OP_COUNT] = {'0', '1', '2', '3'};

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
    void calcListTime(int elem)
    {
        auto opStart = std::chrono::high_resolution_clock::now();
        auto opFinish = std::chrono::high_resolution_clock::now();

        ArrayList *array = new ArrayList(elem);
        LinkedList *linkedlist = new LinkedList();
        Tree *tree = new Tree();
        AVL *avlTree = new AVL;

        int randomNum;
        for (int i = 0; i < elem; i++)
        {
            randomNum = rand() % 10;
            array->addData(randomNum, i);
            linkedlist->insertNode(randomNum);
            tree->node = tree->insertNode(tree->node, randomNum);
            avlTree->node = avlTree->insertNode(avlTree->node, randomNum);
        }

        int randomNumber = array->getValue(rand() % elem);

        for (int op = 0; op < OP_COUNT; op++)
        {
            switch (opSigns[op])
            {
                case '0':
                    opStart = std::chrono::high_resolution_clock::now();
                    array->searchData(randomNumber);
                    //array->deleteData(randomNumber);
                    opFinish = std::chrono::high_resolution_clock::now();
                    break;
                case '1':
                    opStart = std::chrono::high_resolution_clock::now();
                    linkedlist->searchData(randomNumber);
                    //linkedlist->deleteData(randomNumber);
                    opFinish = std::chrono::high_resolution_clock::now();
                    break;
                case '2':
                    opStart = std::chrono::high_resolution_clock::now();
                    tree->searchData(tree->node, randomNumber);
                    //tree->deleteData(tree->node, randomNumber);
                    opFinish = std::chrono::high_resolution_clock::now();
                    break;
                case '3':
                    opStart = std::chrono::high_resolution_clock::now();
                    avlTree->searchData(avlTree->node, randomNumber);
                    //avlTree->deleteNode(avlTree->node, randomNumber);
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
        for (char &opSign: opSigns)
        {
            cout << setw(15) << right << opSign;
        }
        //cout << endl;
    }

    void printTime(int elem)
    {
        cout << setw(10) << right << elem << " |";
        for (auto &op: opTime)
        {
            cout << setw(15) << right << fixed << setprecision(PRECISION) << op.count();
        } // time output
        clearTime();
    }

    void printAverage(int elem)
    {
        cout << setw(10) << right << elem << " |";
        for (auto &op: opAverage)
        {
            op /= elem;
            cout << setw(15) << right << fixed << setprecision(PRECISION) << op.count();
        }
        clearAverage();
    }
};

int main()
{
    srand(time(nullptr));

    std::cout << "0 - Array\n"
                 "1 - Linked List\n"
                 "2 - Tree\n"
                 "3 - AvlTree\n"
              << endl;

    Table randomNumbers;

    randomNumbers.printHeader();
    cout << endl;

    for (int elem = 1; elem <= ELEMENT_COUNT; elem *= 2)
    {
        randomNumbers.calcListTime(elem);

        randomNumbers.printAverage(elem); // time output for average of every element
        randomNumbers.printTime(elem); // time output in general

        cout << endl;
    }
    cout << endl;


    return 0;
}
