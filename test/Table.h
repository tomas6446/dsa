
#ifndef TABLE_H
#define TABLE_H

#include "iostream"
#include "vector"

template<class T>
class Table {
private:
    class List {
    public:
        List(int key, T data) :
                key(key), data(data), next(nullptr) {
        }

        int getKey() const {
            return key;
        }

        T getValue() {
            return data;
        }

        void setValue(T d) {
            this->data = d;
        }

        List *getNext() const {
            return next;
        }

        void setNext(List *n) {
            this->next = n;
        }

        void print() {
            List *temp = this;
            while (temp != nullptr) {
                std::cout << temp->getValue() << " ";
                temp = temp->next;
            }
        }

    private:
        int key;
        T data;
        List *next;
    };

    List *table[11]{};
    int size = 0;
private:


    void getHash(int &hash, int key) {
        hash =((key%5)*(key%5)) % 11;
    }

    void getHash(int &hash, long long int key) {
        hash = (int) key % 11;
    }

    void getHash(int &hash, double key) {
        union x {
            double f;
            unsigned u;
        };
        x u{};
        u.f = key;
        hash = (int) u.u;
    }

    void getHash(int &hash, const std::string &key) {
        hash = key[0] - '0';
    }

public:
    Table() = default;

    explicit Table(const std::vector<T> &arr) {
        for (auto a: arr) {
            insertElem(a);
        }
    }

    ~Table() {
        for (auto &i: table) {
            List *entry = i;
            while (entry != nullptr) {
                List *prev = entry;
                entry = entry->getNext();
                delete prev;
            }
            i = nullptr;
        }
    }

    int getSize() {
        return size;
    }

    bool search(T key) {
        int hashValue;
        getHash(hashValue, key);
        List *entry = table[hashValue];
        while (entry != nullptr) {
            if (entry->getKey() == hashValue) {
                return true;
            }
            entry = entry->getNext();
        }
        return false;
    }

    void insertElem(T data) {
        size++;
        int hashValue;
        getHash(hashValue, data);
        List *prev = nullptr;
        List *entry = table[hashValue];
        while (entry != nullptr && entry->getKey() != hashValue) {
            prev = entry;
            entry = entry->getNext();
        }
        if (entry == nullptr) {
            entry = new List(hashValue, data);
            if (prev == nullptr) {
                table[hashValue] = entry;
            } else {
                prev->setNext(entry);
            }
        } else {
            entry->setValue(data);
        }
    }

    void insertElem(std::vector<T> arr) {
        for (auto a: arr) {
            insertElem(a);
        }
    }

    void deleteElem(T data) {
        size--;
        int hashValue;
        getHash(hashValue, data);
        List *prev = nullptr;
        List *entry = table[hashValue];
        while (entry != nullptr && entry->getKey() != hashValue) {
            prev = entry;
            entry = entry->getNext();
        }
        if (entry == nullptr) {
            return;
        } else {
            if (prev == nullptr) {
                table[hashValue] = entry->getNext();
            } else {
                prev->setNext(entry->getNext());
            }
            delete entry;
        }
    }

    void deleteElem(std::vector<T> arr) {
        for (auto a: arr) {
            deleteElem(a);
        }
    }

    void print() {
        for (auto &i: table) {
            if (i == nullptr) {
                continue;
            } else {
                i->print();
            }
        }
        std::cout << std::endl;
    }
};


#endif
