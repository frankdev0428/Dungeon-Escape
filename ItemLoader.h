#ifndef ITEMLOADER_H
#define ITEMLOADER_H

#include <vector>
#include <string>
#include "Item.h"

// Reads items from a text file and returns them as a vector.
// Each line must be in the format:  name value
// Example:  Sword 15
std::vector<Item> loadItemsFromFile(const std::string& filename);

#endif
