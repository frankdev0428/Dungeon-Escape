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
    ~InventoryBST();
    InventoryBST(const InventoryBST&)            = delete;
    InventoryBST& operator=(const InventoryBST&) = delete;

    void insertItem(const Item& item);
    void displayInventory() const;

private:
    Node* root;

    Node* insert(Node* node, const Item& item);
    void  inOrder(Node* node) const;
    void  deleteTree(Node* node);
};

#endif
