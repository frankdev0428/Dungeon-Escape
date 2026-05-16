#include <iostream>
#include "BST.h"

BST::BST() {
    root = nullptr;
}

BST::~BST() {
    deleteTree(root);
}

void BST::deleteTree(Node* node) {
    if (node == nullptr) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

void BST::insertItem(const Item& item) {
    root = insert(root, item);
}

Node* BST::insert(Node* node, const Item& item) {
    if (node == nullptr) {
        Node* newNode  = new Node();
        newNode->data  = item;
        newNode->left  = nullptr;
        newNode->right = nullptr;
        return newNode;
    }
    if (item.getValue() < node->data.getValue())
        node->left  = insert(node->left,  item);
    else
        node->right = insert(node->right, item);
    return node;
}

void BST::displayInventory() const {
    std::cout << "--- Inventory (sorted by value) ---\n";
    inOrder(root);
    std::cout << "-----------------------------------\n";
}

void BST::inOrder(Node* node) const {
    if (node == nullptr) return;
    inOrder(node->left);
    std::cout << node->data.getName()
              << " (Value: " << node->data.getValue() << ")\n";
    inOrder(node->right);
}
