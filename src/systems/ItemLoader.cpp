#include <iostream>
#include <fstream>  // ifstream — reads from files
#include <sstream>  // istringstream — splits a line into parts
#include "ItemLoader.h"

std::vector<Item> loadItemsFromFile(const std::string& filename) {
    std::vector<Item> items; // will hold every item we successfully read

    // Open the file for reading
    std::ifstream file(filename);

    // If the file could not be opened, print an error and return an empty list
    if (!file) {
        std::cout << "Error: could not open file \"" << filename << "\"\n";
        return items;
    }

    std::string line;

    // Read the file one line at a time
    while (std::getline(file, line)) {

        // Skip blank lines
        if (line.empty()) continue;

        // Use istringstream to split the line into a name and a value
        std::istringstream stream(line);
        std::string name;
        int value;

        // Extract the two fields; if either is missing/invalid, skip the line
        if (stream >> name >> value) {
            items.push_back(Item(name, value)); // build Item and add to list
        }
    }

    file.close(); // good practice — release the file handle
    return items;
}
