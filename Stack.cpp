#include <iostream>
#include "Stack.h"

// Empty stack — no nodes yet
Stack::Stack() {
    top = nullptr;
}

// Destructor: pop everything to avoid memory leaks
Stack::~Stack() {
    while (!isEmpty()) {
        pop();
    }
}

// Push: create a new node on top of the stack
void Stack::push(int x, int y) {
    SNode* node = new SNode();
    node->x    = x;
    node->y    = y;
    node->next = top; // new node points down to the old top
    top        = node; // top now points to the new node
}

// Pop: remove the top node and free its memory
void Stack::pop() {
    if (isEmpty()) return; // nothing to remove

    SNode* temp = top;    // save pointer so we can delete it
    top         = top->next; // move top down to the next node
    delete temp;
}

// Read the x coordinate of the top node (does not remove it)
int Stack::topX() const {
    if (isEmpty()) return -1; // safe fallback
    return top->x;
}

// Read the y coordinate of the top node (does not remove it)
int Stack::topY() const {
    if (isEmpty()) return -1; // safe fallback
    return top->y;
}

bool Stack::isEmpty() const {
    return top == nullptr;
}
