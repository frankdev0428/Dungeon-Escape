#ifndef BST_H
#define BST_H

#include "../core/Item.h"

struct Node {
    Item  data;
    Node* left;
    Node* right;
};

class BST {
public:
    BST();
    ~BST();
    BST(const BST&)            = delete;
    BST& operator=(const BST&) = delete;

    void insertItem(const Item& item);
    void displayInventory() const;

private:
    Node* root;

    Node* insert(Node* node, const Item& item);
    void  inOrder(Node* node) const;
    void  deleteTree(Node* node);
};

#endif
