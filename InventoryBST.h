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
    InventoryBST();           // sets root to nullptr (empty tree)
    void insertItem(const Item& item); // public entry point for inserting

private:
    Node* root; // the top of the tree; nullptr when empty

    // Recursive helper — returns the (possibly new) node at this position
    Node* insert(Node* node, const Item& item);
};

#endif
