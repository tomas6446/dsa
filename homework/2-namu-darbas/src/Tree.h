#ifndef TREE_H
#define TREE_H

#include "iostream"

namespace ADT {
    template<typename T>
    class Tree {
    private:
        class Node {
        public:
            Node() = default;

            T key;
            Node *left{};
            Node *right{};
            long long height{};
        };

        Node *root = nullptr;
        long long size{};
        static long long maxSize;

    public:
        Tree() = default;

        ~Tree() = default;

        void addValue(T val) {
            this->size++;
            this->setMaxSize(this->size);
            this->root = insert(this->root, val);
        }

        void removeVal(T val) {
            size--;
            setMaxSize(size);
            this->root = deleteNode(this->root, val);
        }

        void print() {
            inOrder(this->root);
            std::cout << std::endl;
        }

        bool getVal(T val) {
            Node *temp = this->root;

            while (temp != nullptr) {
                if (temp->key == val) {
                    break;
                }
                if (val > temp->key) {
                    temp = temp->right;
                } else if (val < temp->key) {
                    temp = temp->left;
                }
            }

            if (temp == nullptr) {
                return false;
            }
            if (temp->key == val) {
                return true;
            }

            return false;
        }

        T getFirst() {
            if (root != nullptr) {
                return this->root->key;
            } else {
                return 0;
            }
        }

        long long getSize() {
            return this->size;
        }

        long long getMaxSize() {
            return this->maxSize;
        }

        void destroy() {
            size = 0;
            deleteTree(this->root);
        }

    private:
        void setMaxSize(int s) {
            if (s > this->maxSize) {
                this->maxSize = s;
            }
        }

        long long max(long long a, long long b) {
            return (a > b) ? a : b;
        }

        long long height(Node *N) {
            return N == nullptr ? 0 : N->height;
        }

        long long getBalance(Node *N) {
            return N == nullptr ? 0 : height(N->left) - height(N->right);
        }

        Node *newNode(int key) {
            auto *n = new Node();
            n->key = key;
            n->left = nullptr;
            n->right = nullptr;
            n->height = 1;

            return (n);
        }

        Node *rightRotate(Node *y) {
            Node *x = y->left;
            Node *T2 = x->right;
            x->right = y;
            y->left = T2;
            y->height = max(height(y->left),
                            height(y->right)) + 1;
            x->height = max(height(x->left),
                            height(x->right)) + 1;
            return x;
        }

        Node *leftRotate(Node *x) {
            Node *y = x->right;
            Node *T2 = y->left;
            y->left = x;
            x->right = T2;
            x->height = max(height(x->left),
                            height(x->right)) + 1;
            y->height = max(height(y->left),
                            height(y->right)) + 1;
            return y;
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

        Node *insert(Node *n, int key) {
            if (n == nullptr) {
                return newNode(key);
            }
            if (key < n->key) {
                n->left = insert(n->left, key);
            } else if (key > n->key) {
                n->right = insert(n->right, key);
            } else {
                return n;
            }

            n->height = 1 + max(height(n->left),
                                height(n->right));

            long long balance = getBalance(n);
            if (balance > 1) {
                if (key < n->left->key) {
                    return rightRotate(n);
                }
                if (key > n->left->key) {
                    n->left = leftRotate(n->left);
                    return rightRotate(n);
                }
            } else if (balance < -1) {
                if (key > n->right->key) {
                    return leftRotate(n);
                }
                if (key < n->right->key) {
                    n->right = rightRotate(n->right);
                    return leftRotate(n);
                }
            }
            return n;
        }

        Node *deleteNode(Node *r, int key) {
            Node *temp;
            if (r == nullptr) {
                return nullptr;
            } else if (key > r->key) {
                r->right = deleteNode(r->right, key);
                if (getBalance(r) == 2) {
                    if (getBalance(r->left) >= 0) {
                        r = LL(r);
                    } else {
                        r = LR(r);
                    }
                }
            } else if (key < r->key) {
                r->left = deleteNode(r->left, key);
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
                    r->key = temp->key;
                    r->right = deleteNode(r->right, temp->key);
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

        void deleteTree(Node *node) {
            if (node == nullptr) {
                return;
            }
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }

        void inOrder(Node *r) {
            if (r != nullptr) {
                inOrder(r->left);
                std::cout << r->key << " ";
                inOrder(r->right);
            }
        }
    };

    template<typename T>
    long long Tree<T>::maxSize = 0;
}

#endif
