#include <bits/stdc++.h>
#include <algorithm>
#include <utility>

using namespace std;

class Node
{
public:
    vector<int> data;
    Node *next;
    Node *prev;
};

void initNode(Node **node, vector<int> array)
{
    (*node) = new Node;
    (*node)->data = std::move(array);
    (*node)->next = nullptr;
    (*node)->prev = nullptr;
}

void add(Node **node, int index, int value)
{
    // create temp array to copy all elements from node
    vector<int> array;
    for (auto data: (*node)->data)
    {
        array.push_back(data);
    }
    array.insert(array.begin() + index, value);

    Node *newNode{};
    initNode(&newNode, array);

    newNode->prev = (*node);
    newNode->next = nullptr;
    (*node) = newNode;
}

void del(Node **node, int index)
{
    // create temp array to copy all elements from node
    vector<int> array;
    for (auto data: (*node)->data)
    {
        array.push_back(data);
    }
    array.erase(array.begin() + index);

    Node *newNode{};
    initNode(&newNode, array);

    newNode->prev = (*node);
    newNode->next = nullptr;
    (*node) = newNode;
}

int main()
{
    //vector<int> array = {9, 6, 4, 2, 1};
    vector<int> array = {1, 2, 4, 6, 9};

    Node *node{};

    initNode(&node, array);
    add(&node, 0, 1);
    add(&node, 3, 3);
    del(&node, 6);
    add(&node, 4, 5);
    del(&node, 1);

    for (; node != nullptr; node = node->prev)
    {
        for (int j: node->data)
        {
            cout << j << " ";
        }
        std::cout << endl;
    }


    return 0;
}

