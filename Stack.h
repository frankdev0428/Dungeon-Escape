#ifndef STACK_H
#define STACK_H

// A linked-list node that holds one (x, y) position
struct SNode {
    int x;
    int y;
    SNode* next; // points to the node below this one in the stack
};

// LIFO Stack — last position pushed is the first one popped (undo order)
class Stack {
public:
    Stack();   // start with an empty stack
    ~Stack();  // free all remaining nodes

    void push(int x, int y);  // save a position on top
    void pop();               // remove the top position
    int  topX() const;        // read x of the top position
    int  topY() const;        // read y of the top position
    bool isEmpty() const;     // true when no positions are saved

private:
    SNode* top; // points to the most recently pushed node
};

#endif
