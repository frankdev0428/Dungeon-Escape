#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item {
public:
    // Default constructor — creates a "nothing" placeholder item
    Item();

    // Parameterized constructor — create a real item with a name and value
    Item(std::string name, int value);

    std::string getName()  const; // returns the item's name
    int         getValue() const; // returns the item's power/value

    void displayItem() const; // prints item info to the console

private:
    std::string name;  // e.g. "Health Potion", "Sword"
    int         value; // e.g. healing amount, attack power
};

#endif
