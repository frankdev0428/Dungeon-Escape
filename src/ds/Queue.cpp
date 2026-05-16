#include <iostream>
#include "Queue.h"

// Empty queue: both pointers are null
Queue::Queue() {
    head = nullptr;
    tail = nullptr;
}

// Destructor: pop everything so no memory is leaked
Queue::~Queue() {
    while (!isEmpty()) {
        pop();
    }
}

// Add a new node to the BACK of the queue
void Queue::push(const std::string& value) {
    QNode* node = new QNode();
    node->data  = value;
    node->next  = nullptr;

    if (tail == nullptr) {
        // Queue was empty — new node is both head and tail
        head = node;
        tail = node;
    } else {
        // Link the current tail to the new node, then advance tail
        tail->next = node;
        tail       = node;
    }
}

// Remove the node at the FRONT of the queue
void Queue::pop() {
    if (isEmpty()) return; // nothing to remove

    QNode* temp = head;   // save pointer so we can delete it
    head        = head->next; // advance head to the next node

    if (head == nullptr) {
        // Queue is now empty — tail must also be null
        tail = nullptr;
    }

    delete temp; // free the old front node
}

// Return the value at the front without removing it
std::string Queue::front() const {
    if (isEmpty()) return ""; // safe fallback
    return head->data;
}

bool Queue::isEmpty() const {
    return head == nullptr;
}
