
#ifndef TREE_H
#define TREE_H

class Node {
public:
    Node() = default;

    const Data *data;
    Node *left{};
    Node *right{};
    int height{};
};

class Tree {
protected:
    int height(Node *node) {
        return node == nullptr ? 0 : node->height;
    }

    int max(int a, int b) {
        return (a > b) ? a : b;
    }

    int getBalance(Node *node) {
        return node == nullptr ? 0 : height(node->left) - height(node->right);
    }

    Node *newNode(const Data *data) {
        Node *node = new Node;
        node->data = data;
        node->left = nullptr;
        node->right = nullptr;
        node->height = 1;
        return node;
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

    Node *RL(Node *T) {
        T->right = rightRotate(T->right);
        T = leftRotate(T);
        return (T);
    }

    virtual Node *insert(Node *node, const Data *data) = 0;

    virtual Node *deleteNode(Node *root, const Data *data) = 0;

    void inOrder(Node *root) {
        if (root != nullptr) {
            inOrder(root->left);
            cout << root->data << " : " << root->data->iField << " " << root->data->sField << " " << root->data->dField << std::endl;
            inOrder(root->right);
        }
    }

public:
    Node *root = nullptr;

    void insertElem(const Data *data) {
        root = insert(root, data);
    }

    void deleteElem(const Data *data) {
        root = deleteNode(root, data);
    }

    void print() {
        inOrder(root);
    }
};

class intTree : public Tree {
public:
    intTree() = default;

    Data *search(int data) {
        return const_cast<Data *>(searchInt(root, data));
    }

    Node *insert(Node *node, const Data *data) override {
        if (node == nullptr) {
            return newNode(data);
        }
        if (data->iField < node->data->iField) {
            node->left = insert(node->left, data);
        } else if (data->iField > node->data->iField) {
            node->right = insert(node->right, data);
        } else {
            return node;
        }

        node->height = 1 + max(height(node->left),
                               height(node->right));

        int balance = getBalance(node);
        if (balance > 1) {
            if (data->iField < node->left->data->iField) {
                return rightRotate(node);
            }
            if (data->iField > node->left->data->iField) {
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }
        } else if (balance < -1) {
            if (data->iField > node->right->data->iField) {
                return leftRotate(node);
            }
            if (data->iField < node->right->data->iField) {
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }
        }
        return node;
    }

    Node *deleteNode(Node *root, const Data *data) override {
        Node *temp;
        if (root == nullptr) {
            return nullptr;
        } else if (data->iField > root->data->iField) {
            root->right = deleteNode(root->right, data);
            if (getBalance(root) == 2) {
                if (getBalance(root->left) >= 0) {
                    root = LL(root);
                } else {
                    root = LR(root);
                }
            }
        } else if (data->iField < root->data->iField) {
            root->left = deleteNode(root->left, data);
            if (getBalance(root) == -2) {
                if (getBalance(root->right) <= 0) {
                    root = RR(root);
                } else {
                    root = RL(root);
                }
            }
        } else {
            if (root->right != nullptr) {
                temp = root->right;
                while (temp->left != nullptr) {
                    temp = temp->left;
                }
                root->data = temp->data;
                root->right = deleteNode(root->right, temp->data);
                if (getBalance(root) == 2) {
                    if (getBalance(root->left) >= 0) {
                        root = LL(root);
                    } else {
                        root = LR(root);
                    }
                }
            } else {
                return (root->left);
            }
        }
        root->height = height(root);
        return (root);
    }

private:
    const Data *searchInt(Node *r, int data) {
        if (r == nullptr) {
            return nullptr;
        }
        if (r->data->iField < data) {
            return searchInt(r->right, data);
        } else if (r->data->iField > data) {
            return searchInt(r->left, data);
        } else if (r->data->iField == data) {
            return r->data;
        }
    }
};

class stringTree : public Tree {
public:
    stringTree() : Tree() {};

    Data *search(const std::string &data) {
        return const_cast<Data *>(searchString(root, data));
    }

    Node *insert(Node *node, const Data *data) override {
        if (node == nullptr) {
            return newNode(data);
        }
        if (data->sField < node->data->sField) {
            node->left = insert(node->left, data);
        } else if (data->sField > node->data->sField) {
            node->right = insert(node->right, data);
        } else {
            return node;
        }

        node->height = 1 + max(height(node->left),
                               height(node->right));
        int balance = getBalance(node);

        if (balance > 1 && data->sField < node->left->data->sField) {
            return rightRotate(node);
        }

        if (balance < -1 && data->sField > node->right->data->sField) {
            return leftRotate(node);
        }
        if (balance > 1 && data->sField > node->left->data->sField) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && data->sField < node->right->data->sField) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }

    Node *deleteNode(Node *root, const Data *data) override {
        Node *temp;
        if (root == nullptr) {
            return nullptr;
        } else if (data->sField > root->data->sField) {
            root->right = deleteNode(root->right, data);
            if (getBalance(root) == 2) {
                if (getBalance(root->left) >= 0) {
                    root = LL(root);
                } else {
                    root = LR(root);
                }
            }
        } else if (data->sField < root->data->sField) {
            root->left = deleteNode(root->left, data);
            if (getBalance(root) == -2) {
                if (getBalance(root->right) <= 0) {
                    root = RR(root);
                } else {
                    root = RL(root);
                }
            }
        } else {
            if (root->right != nullptr) {
                temp = root->right;
                while (temp->left != nullptr) {
                    temp = temp->left;
                }
                root->data = temp->data;
                root->right = deleteNode(root->right, temp->data);
                if (getBalance(root) == 2) {
                    if (getBalance(root->left) >= 0) {
                        root = LL(root);
                    } else {
                        root = LR(root);
                    }
                }
            } else {
                return (root->left);
            }
        }
        root->height = height(root);
        return (root);
    }

private:
    const Data *searchString(Node *r, const std::string &data) {
        if (r == nullptr) {
            return nullptr;
        } else if (r->data->sField == data) {
            return r->data;
        } else if (r->data->sField < data) {
            return searchString(r->right, data);
        } else {
            return searchString(r->left, data);
        }
    }
};

class doubleTree : public Tree {
public:
    doubleTree() : Tree() {};

    Node *insert(Node *node, const Data *data) override {
        if (node == nullptr) {
            return newNode(data);
        }
        if (data->dField < node->data->dField) {
            node->left = insert(node->left, data);
        } else if (data->dField > node->data->dField) {
            node->right = insert(node->right, data);
        } else {
            return node;
        }

        node->height = 1 + max(height(node->left),
                               height(node->right));
        int balance = getBalance(node);

        if (balance > 1 && data->dField < node->left->data->dField) {
            return rightRotate(node);
        }

        if (balance < -1 && data->dField > node->right->data->dField) {
            return leftRotate(node);
        }
        if (balance > 1 && data->dField > node->left->data->dField) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && data->dField < node->right->data->dField) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }

    Data *search(double data) {
        return const_cast<Data *>(searchDouble(root, data));
    }

    Node *deleteNode(Node *root, const Data *data) override {
        Node *temp;
        if (root == nullptr) {
            return nullptr;
        } else if (data->dField > root->data->dField) {
            root->right = deleteNode(root->right, data);
            if (getBalance(root) == 2) {
                if (getBalance(root->left) >= 0) {
                    root = LL(root);
                } else {
                    root = LR(root);
                }
            }
        } else if (data->dField < root->data->dField) {
            root->left = deleteNode(root->left, data);
            if (getBalance(root) == -2) {
                if (getBalance(root->right) <= 0) {
                    root = RR(root);
                } else {
                    root = RL(root);
                }
            }
        } else {
            if (root->right != nullptr) {
                temp = root->right;
                while (temp->left != nullptr) {
                    temp = temp->left;
                }
                root->data = temp->data;
                root->right = deleteNode(root->right, temp->data);
                if (getBalance(root) == 2) {
                    if (getBalance(root->left) >= 0) {
                        root = LL(root);
                    } else {
                        root = LR(root);
                    }
                }
            } else {
                return (root->left);
            }
        }
        root->height = height(root);
        return (root);
    }

private:
    const Data *searchDouble(Node *r, double data) {
        if (r == nullptr) {
            return nullptr;
        } else if (r->data->dField == data) {
            return r->data;
        } else if (r->data->dField < data) {
            return searchDouble(r->right, data);
        } else {
            return searchDouble(r->left, data);
        }
    }
};

#endif
