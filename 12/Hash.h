
#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <list>

using namespace std;

class Hash {
    int capacity;
    list<std::string> *table;
public:
    Hash(int);

    int getCapacity();

    list<std::string> getTable(int);

    void insertItem(std::string);

    int hashFunction(int);

    bool itemExists(std::string);
};


#endif
