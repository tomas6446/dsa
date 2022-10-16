#ifndef LIST_H
#define LIST_H

#include "iostream"
#include "vector"

template<class T>
class List {
private:
    class Node {
    public:
        T data;
        Node *next;
        Node *prev;

        Node() = default;

        Node(T data)
        {
            this->data = data;
            this->next = nullptr;
        }
    };

    Node* head = nullptr;
    int size = 0;

public:
    List() = default;

    explicit List(T data) : Node(data) {};

    explicit List(std::vector<T> arr) {
        for(auto a : arr) {
            insertElem(a);
        }
    }

    int getSize() {
        return size;
    }

    void insertElem(T data) {
        size++;
        Node* newNode = new Node(data);
        if (head == nullptr) {
            head = newNode;
            return;
        }
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    void push(T data) {
        size++;
        Node* newNode = new Node(data);
        if (head == nullptr) {
            head = newNode;
            return;
        }
        newNode->next = head;
        head = newNode;
    }

    void deleteElem(T data) {
        size--;
        Node *temp1 = head, *temp2 = nullptr;
        int ListLen = 0;

        if (head == nullptr) {
            return;
        }
        while (temp1 != nullptr) {
            temp1 = temp1->next;
            ListLen++;
        }

        if (ListLen < data) {
            return;
        }
        temp1 = head;
        if (data == 1) {
            head = head->next;
            delete temp1;
            return;
        }
        while (data-- > 1) {
            temp2 = temp1;
            temp1 = temp1->next;
        }
        temp2->next = temp1->next;
        delete temp1;
    }

    void print() {
        Node* temp = head;
        if (head == nullptr) {
            std::cout << "Node empty" << std::endl;
            return;
        }
        while (temp != nullptr) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
    }
};


#endif
