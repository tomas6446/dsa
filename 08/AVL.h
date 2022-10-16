
#ifndef AVL_H
#define AVL_H

#include <iostream>

using namespace std;

class AVL
{
    struct Node
    {
        int key;
        Node *left;
        Node *right;
        int height;
    };

    int height(Node *N)
    {
        if (N == nullptr)
        {
            return 0;
        }
        return N->height;
    }

    int max(int a, int b)
    {
        return (a > b) ? a : b;
    }

    int getBalanceFactor(Node *N)
    {
        if (N == nullptr)
        {
            return 0;
        }
        return height(N->left) - height(N->right);
    }


public:
    Node *node = new Node;

    AVL() {
        this->node = newNode(0);
    }

    AVL(int key)
    {
        this->node = newNode(key);
    }

    ~AVL()
    {
        delete node;
    }

    Node *newNode(int key)
    {
        Node *newNode = new Node();
        newNode->key = key;
        newNode->left = nullptr;
        newNode->right = nullptr;
        newNode->height = 1;
        return newNode;
    }

    Node *rightRotate(Node *y)
    {
        Node *x = y->left;
        Node *T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;
        return x;
    }

    Node *leftRotate(Node *x)
    {
        Node *y = x->right;
        Node *T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        return y;
    }

    Node *insertNode(Node *root, int key)
    {
        if (root == nullptr)
        {
            return (newNode(key));
        }
        if (key < root->key)
        {
            root->left = insertNode(root->left, key);
        }
        else if (key > root->key)
        {
            root->right = insertNode(root->right, key);
        }
        else
        {
            return root;
        }
        root->height = 1 + max(height(root->left), height(root->right));
        int balanceFactor = getBalanceFactor(root);
        if (balanceFactor > 1)
        {
            if (key < root->left->key)
            {
                return rightRotate(node);
            }
            else if (key > root->left->key)
            {
                root->left = leftRotate(root->left);
                return rightRotate(root);
            }
        }
        if (balanceFactor < -1)
        {
            if (key > root->right->key)
            {
                return leftRotate(root);
            }
            else if (key < root->right->key)
            {
                root->right = rightRotate(root->right);
                return leftRotate(root);
            }
        }
        return root;
    }


    Node *nodeWithMimumValue(Node *node)
    {
        Node *current = node;
        while (current->left != nullptr)
        {
            current = current->left;
        }
        return current;
    }

    Node *deleteNode(Node *root, int key)
    {
        if (root == nullptr)
        {
            return root;
        }
        if (key < root->key)
        {
            root->left = deleteNode(root->left, key);
        }
        else if (key > root->key)
        {
            root->right = deleteNode(root->right, key);
        }
        else
        {
            if ((root->left == nullptr) || (root->right == nullptr))
            {
                Node *temp = root->left ? root->left : root->right;
                if (temp == nullptr)
                {
                    temp = root;
                    root = nullptr;
                }
                else
                {
                    *root = *temp;
                }
                delete temp;
            }
            else
            {
                Node *temp = nodeWithMimumValue(root->right);
                root->key = temp->key;
                root->right = deleteNode(root->right, temp->key);
            }
        }
        if (root == nullptr)
        {
            return root;
        }
        root->height = 1 + max(height(root->left), height(root->right));
        int balanceFactor = getBalanceFactor(root);
        if (balanceFactor > 1)
        {
            if (getBalanceFactor(root->left) >= 0)
            {
                return rightRotate(root);
            }
            else
            {
                root->left = leftRotate(root->left);
                return rightRotate(root);
            }
        }
        if (balanceFactor < -1)
        {
            if (getBalanceFactor(root->right) <= 0)
            {
                return leftRotate(root);
            }
            else
            {
                root->right = rightRotate(root->right);
                return leftRotate(root);
            }
        }
        return root;
    }

    bool searchData(Node *root, int key)
    {
        if (root)
        {
            if (root->key == key)
            {
                return true;
            }
            else if (key < root->key)
            {
                return searchData(root->left, key);
            }
            else
            {
                return searchData(root->right, key);
            }
        }
        return false;
    }

    void inOrder(Node *root)
    {
        if (root != nullptr)
        {
            inOrder(root->left);
            cout << root->key << " ";
            inOrder(root->right);
        }
    }

    void preOrder(Node *root)
    {
        if (root != nullptr)
        {
            cout << root->key << " ";
            inOrder(root->left);
            inOrder(root->right);
        }
    }
};


#endif
