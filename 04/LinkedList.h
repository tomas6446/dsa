#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

class LinkedList
{
private:
    struct Node
    {
        int key;
        Node *next;
    };
    Node *node = new Node;

public:

    LinkedList()
    {
        this->node->key = 0;
        this->node->next = nullptr;
    }

    LinkedList(int key)
    {
        this->node->key = key;
        this->node->next = nullptr;
    }

    ~LinkedList()
    {
        delete node;
    }

    void insertNode(int key)
    {
        Node *newNode = new Node;
        newNode->key = key;
        newNode->next = this->node;

        this->node = newNode;
    }

    void deleteData(int key)
    {
        Node *temp = this->node;

        while (temp != nullptr)
        {
            if (temp->key == key)
            {
                break;
            }
            temp = temp->next;
        }
        temp = temp->next;
    }

    bool searchData(int key)
    {
        Node *temp = this->node;

        while (temp != nullptr)
        {
            if (temp->key == key)
            {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    void printList()
    {
        Node *temp = this->node;

        while (temp != nullptr)
        {
            std::cout << temp->key << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }
};

#endif
