#ifndef TABLE_H
#define TABLE_H

#include "iostream"
#include "vector"
#include "algorithm"

class List {
private:
    class Node {
    public:
        const Data *data{};
        Node *next{};
        Node *prev{};

        Node() = default;

        explicit Node(const Data *data) {
            this->data = data;
            this->next = nullptr;
        }
    };

    Node *head = nullptr;
    int size = 0;

public:
    List() = default;

    void push(const Data *data) {
        Node *newNode = new Node(data);
        newNode->data = data;
        newNode->next = head;
        head = newNode;
        size++;
    }

    void deleteElem(const Data *data) {
        while (head && head->data == data) {
            head = head->next;
        }
        Node *curr = head, *prev = nullptr;

        while (curr) {
            if (curr->data == data) {
                prev->next = curr->next;
            } else {
                prev = curr;
            }
            curr = curr->next;
        }
    }

    Data *search(int key) {
        Node *current = head;
        while (current != nullptr) {
            if (current->data->iField == key) {
                return const_cast<Data *>(current->data);
            }
            current = current->next;
        }
        return nullptr;
    }

    Data *search(const std::string &key) {
        Node *current = head;
        while (current != nullptr) {
            if (current->data->sField == key) {
                return const_cast<Data *>(current->data);
            }
            current = current->next;
        }
        return nullptr;
    }

    Data *search(double key) {
        Node *current = head;
        while (current != nullptr) {
            if (current->data->dField == key) {
                return const_cast<Data *>(current->data);
            }
            current = current->next;
        }
        return nullptr;
    }

    const Data *getValue() {
        return head->data;
    }

    void print() {
        Node *current = head;
        std::cout << " --- " << std::endl;
        while (current != nullptr) {
            std::cout << current->data->iField << " " << current->data->sField << " " << current->data->dField << std::endl;
            current = current->next;
        }
    }
};

class intTable {
private:
    vector <List> table{};
public:
    intTable(int size) : table(size) {}

    void getHash(int &hash, int key) {
        hash = key % table.size();
    }

    void insertElem(const Data *data) {
        int hash;
        getHash(hash, data->iField);
        table[hash].push(data);
    }

    void deleteElem(const Data *data) {
        int hash;
        getHash(hash, data->iField);
        auto &bucket_list = table[hash];
        bucket_list.deleteElem(data);
    }

    Data *search(int key) {
        int hash;
        getHash(hash, key);
        return table[hash].search(key);
    }

    void print() {
        for (int i = 0; i < table.size(); i++) {
            table[i].print();
        }
    }
};

class stringTable  {
private:
    vector <List> table{};
public:
    stringTable(int size) : table(size) {}

    void getHash(int &hash, string key) {
        hash = key[0] - '0';
    }

    void insertElem(const Data *data) {
        int hash;
        getHash(hash, data->sField);
        table[hash].push(data);
    }

    void deleteElem(const Data *data) {
        int hash;
        getHash(hash, data->sField);
        auto &bucket_list = table[hash];
        bucket_list.deleteElem(data);
    }

    Data *search(string key) {
        int hash;
        getHash(hash, key);
        return table[hash].search(key);
    }

    void print() {
        for (int i = 0; i < table.size(); i++) {
            table[i].print();
        }
    }
};


#endif
