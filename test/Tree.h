#ifndef TREE_H
#define TREE_H

#include "iostream"
#include "vector"

template<class T>
class Tree {
private:
    class Node {
    public:
        Node() = default;

        T data;
        Node *left{};
        Node *right{};
        int height{};
    };

    Node *root = nullptr;
    int size = 0;

private:
    int height(Node *Node) {
        return Node == nullptr ? 0 : Node->height;
    }

    int max(int a, int b) {
        return (a > b) ? a : b;
    }

    int getBalance(Node *Node) {
        return Node == nullptr ? 0 : height(Node->left) - height(Node->right);
    }

    void Inorder(Node *r) {
        if (!r) {
            return;
        }
        Inorder(r->left);
        Inorder(r->right);
        std::cout << r->data << " ";

    }

    void deleteTree(Node *node) {
        if (node == nullptr) {
            return;
        }
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

    Node *newNode(T data) {
        auto *node = new Node;
        node->data = data;
        node->left = nullptr;
        node->right = nullptr;
        node->height = 1;
        return node;
    }

    Node *deleteNode(Node *r, T data) {
        Node *temp;
        if (r == nullptr) {
            return nullptr;
        } else if (data > r->data) {
            r->right = deleteNode(r->right, data);
            if (getBalance(r) == 2) {
                if (getBalance(r->left) >= 0) {
                    r = LL(r);
                } else {
                    r = LR(r);
                }
            }
        } else if (data < r->data) {
            r->left = deleteNode(r->left, data);
            if (getBalance(r) == -2) {
                if (getBalance(r->right) <= 0) {
                    r = RR(r);
                } else {
                    r = RL(r);
                }
            }
        } else {
            if (r->right != nullptr) {
                temp = r->right;
                while (temp->left != nullptr) {
                    temp = temp->left;
                }
                r->data = temp->data;
                r->right = deleteNode(r->right, temp->data);
                if (getBalance(r) == 2) {
                    if (getBalance(r->left) >= 0) {
                        r = LL(r);
                    } else {
                        r = LR(r);
                    }
                }
            } else {
                return (r->left);
            }
        }
        r->height = height(r);
        return (r);
    }

    Node *rightRotate(Node *second) {
        Node *first = second->left;
        Node *temp = first->right;

        first->right = second;
        second->left = temp;

        second->height = max(height(second->left),
                             height(second->right)) + 1;
        first->height = max(height(first->left),
                            height(first->right)) + 1;

        return first;
    }

    Node *leftRotate(Node *first) {
        Node *second = first->right;
        Node *temp = second->left;

        second->left = first;
        first->right = temp;

        first->height = max(height(first->left),
                            height(first->right)) + 1;
        second->height = max(height(second->left),
                             height(second->right)) + 1;
        return second;
    }

    Node *RR(Node *n) {

        n = leftRotate(n);
        return (n);
    }

    Node *LL(Node *n) {
        n = rightRotate(n);
        return (n);
    }

    Node *LR(Node *n) {

        n->left = leftRotate(n->left);
        n = rightRotate(n);
        return (n);
    }

    Node *RL(Node *node) {
        node->right = rightRotate(node->right);
        node = leftRotate(node);
        return (node);
    }

    Node *insert(Node *node, T data) {
        if (node == nullptr) {
            return newNode(data);
        }
        if (data < node->data) {
            node->left = insert(node->left, data);
        } else if (data > node->data) {
            node->right = insert(node->right, data);
        } else {
            return node;
        }

        node->height = 1 + max(height(node->left),
                               height(node->right));

        int balance = getBalance(node);
        if (balance > 1) {
            if (data < node->left->data) {
                return rightRotate(node);
            }
            if (data > node->left->data) {
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }
        } else if (balance < -1) {
            if (data > node->right->data) {
                return leftRotate(node);
            }
            if (data < node->right->data) {
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }
        }
        return node;
    }

    bool search(Node *r, int data) {
        if (r == nullptr) {
            return false;
        } else if (r->data == data) {
            return true;
        } else if (r->data < data) {
            return search(r->right, data);
        } else {
            return search(r->left, data);
        }
    }

public:
    Tree() = default;

    explicit Tree(const std::vector<T> &arr) {
        for (auto a: arr) {
            insertElem(a);
        }
    }

    ~Tree() = default;

    int getHeight() {
        return height(root);
    }

    int getSize() {
        return size;
    }

    bool search(int key) {
        return search(root, key);
    }

    void insertElem(T data) {
        size++;
        root = insert(root, data);
    }

    void insertElem(std::vector<T> arr) {
        for (auto a: arr) {
            insertElem(a);
        }
    }

    void deleteElem(T data) {
        size--;
        root = deleteNode(root, data);
    }

    void deleteElem(std::vector<T> arr) {
        for (auto a: arr) {
            deleteElem(a);
        }
    }

    void deleteTree() {
        size = 0;
        deleteTree(root);
    }

    void print() {
        Inorder(root);
        std::cout << std::endl;
    }
};

#endif
