#ifndef HASH_TABLE_H
#define PHASH_TABLE_H

#include "iostream"
#include "vector"

using namespace std;

#include <iostream>
#include <list>

using namespace std;

class HashTable {
private:
    list<int> *table;
    int total_elements;

    // Hash function to calculate hash for a value:
    int getHash(int key)
    {
        return key % total_elements;
    }

public:
    // Constructor to create a hash table with 'n' indices:
    HashTable(int n)
    {
        total_elements = n;
        table = new list<int>[total_elements];
    }

    // Insert data in the hash table:
    void insertElement(int key)
    {
        table[getHash(key)].push_back(key);
    }

    // Remove data from the hash table:
    void removeElement(int key)
    {
        int x = getHash(key);

        list<int>::iterator i;
        for (i = table[x].begin(); i != table[x].end(); i++) {
            // Check if the iterator points to the required item:
            if (*i == key)
                break;
        }

        // If the item was found in the list, then delete it:
        if (i != table[x].end())
            table[x].erase(i);
    }

    void printAll()
    {
        // Traverse each index:
        for (int i = 0; i < total_elements; i++) {
            cout << "Index " << i << ": ";
            // Traverse the list at current index:
            for (int j: table[i])
                cout << j << " => ";

            cout << endl;
        }
    }
};

#endif
