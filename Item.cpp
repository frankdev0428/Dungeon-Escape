#include <iostream>
#include "Item.h"

// Default: a blank item with no name and zero value
Item::Item() {
    name  = "Nothing";
    value = 0;
}

// Build an item with a specific name and value
Item::Item(std::string name, int value) {
    this->name  = name;  // "this->" distinguishes the member from the parameter
    this->value = value;
}

std::string Item::getName()  const { return name;  }
int         Item::getValue() const { return value; }

// Print a single line describing the item
void Item::displayItem() const {
    std::cout << "[Item] " << name << " (value: " << value << ")\n";
}
