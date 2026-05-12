#ifndef INVENTORYBST_H
#define INVENTORYBST_H

#include "Item.h"

// Each node holds one item and two child pointers
struct Node {
    Item  data;   // the item stored at this node
    Node* left;   // points to items with a smaller value
    Node* right;  // points to items with a larger value
};

class InventoryBST {
public:
    InventoryBST();
    void insertItem(const Item& item);  // public entry point for inserting
    void displayInventory() const;      // prints all items sorted by value

private:
    Node* root;

    Node* insert(Node* node, const Item& item); // recursive insert helper
    void  inOrder(Node* node) const;            // recursive traversal helper
};

#endif
