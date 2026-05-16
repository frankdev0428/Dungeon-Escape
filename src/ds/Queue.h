#ifndef QUEUE_H
#define QUEUE_H

#include <string>

// A linked-list node that holds one turn label ("Player" or "Enemy")
struct QNode {
    std::string data;
    QNode* next;
};

// FIFO Queue — first item pushed is the first item popped
class Queue {
public:
    Queue();
    ~Queue();
    Queue(const Queue&)            = delete;
    Queue& operator=(const Queue&) = delete;

    void push(const std::string& value); // add to the back
    void pop();                          // remove from the front
    std::string front() const;           // read the front without removing
    bool isEmpty() const;                // true if no items remain

private:
    QNode* head; // points to the front (next to be removed)
    QNode* tail; // points to the back  (last item added)
};

#endif
