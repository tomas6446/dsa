#ifndef TREE_H
#define TREE_H

#include <iostream>

class Tree {
private:
    struct Node {
        int key;
        Node *left, *right;
    };

    Node *newNode(int item)
    {
        Node *temp = new Node;
        temp->key = item;
        temp->left = temp->right = nullptr;
        return temp;
    }

    Node *minValueNode(Node *node)
    {
        Node *current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

public:
    Node *node = new Node;

    Tree() = default;

    Tree(int key)
    {
        this->node = newNode(key);
    }

    ~Tree()
    {
        delete node;
    }

    void inOrder(Node *root)
    {
        if (root != nullptr) {
            std::cout << root->key << " ";
            inOrder(root->left);
            inOrder(root->right);
        }
    }

    Node *insertNode(Node *root, int key)
    {
        if (root == nullptr) {
            return newNode(key);
        }
        if (key < root->key) {
            root->left = insertNode(root->left, key);
        }
        else {
            root->right = insertNode(root->right, key);
        }
        return root;
    }

    Node *deleteData(Node *root, int key)
    {
        if (root == nullptr) {
            return root;
        }
        if (key < root->key) {
            root->left = deleteData(root->left, key);
        }
        else if (key > root->key) {
            root->right = deleteData(root->right, key);
        }
        else {
            if (root->left == nullptr and root->right == nullptr) {
                return nullptr;
            }
            else if (root->left == nullptr) {
                Node *temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == nullptr) {
                Node *temp = root->left;
                delete root;
                return temp;
            }
            Node *temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteData(root->right, temp->key);
        }
        return root;
    }

    bool searchData(Node *root, int key)
    {
        if (root) {
            if (root->key == key) {
                return true;
            }
            else if (key < root->key) {
                return searchData(root->left, key);
            }
            else {
                return searchData(root->right, key);
            }
        }
        return false;
    }
};


#endif
