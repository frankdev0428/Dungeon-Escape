#include <iostream>
#include "InventoryBST.h"

// Start with an empty tree
InventoryBST::InventoryBST() {
    root = nullptr;
}

// Public function — kicks off the recursive insert from the root
void InventoryBST::insertItem(const Item& item) {
    root = insert(root, item);
}

// Recursive helper.
// 'node' is the current position we're examining.
// Returns the node that should sit at this position after the insert.
Node* InventoryBST::insert(Node* node, const Item& item) {

    // Base case: we've reached an empty spot — place the new node here
    if (node == nullptr) {
        Node* newNode  = new Node();
        newNode->data  = item;
        newNode->left  = nullptr;
        newNode->right = nullptr;
        std::cout << "Inserted: " << item.getName()
                  << " (value: " << item.getValue() << ")\n";
        return newNode;
    }

    // Recursive case: decide which subtree to go into
    if (item.getValue() < node->data.getValue()) {
        // New item is smaller — recurse into the left subtree
        node->left = insert(node->left, item);
    } else {
        // New item is larger or equal — recurse into the right subtree
        node->right = insert(node->right, item);
    }

    // Return the unchanged current node so the parent's pointer stays valid
    return node;
}
