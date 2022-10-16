#include "Hash.h"

Hash::Hash(int b)
{
    this->capacity = b;
    table = new list<std::string>[capacity];
}

// Insert only when in already exists in the table
void Hash::insertItem(std::string item)
{
    int index = hashFunction(item[0]);
    if(!itemExists(item)) {
        table[index].push_back(item);
    }
}

// the function returns true if it found the item
bool Hash::itemExists(std::string item)
{
    int hashIndex = hashFunction(item[0]);
    for (const auto &x: table[hashIndex]) {
        if (x == item) {
            return true;
        }
    }
    return false;
}

// hash funchtion to store alphabetically
int Hash::hashFunction(int x)
{
    return x - 97;
}

int Hash::getCapacity()
{
    return capacity;
}

list<std::string> Hash::getTable(int key)
{
    return table[key];
}
