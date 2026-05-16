#include <iostream>
#include "HashTable.h"

// Set up the table with 'size' empty buckets
HashTable::HashTable(int size) {
    this->size = size;
    table.resize(size); // each element is an empty vector<Item>
}

// Hash function: add up every character's ASCII value, then mod by size.
// This spreads keys across buckets reasonably well for small tables.
// Example: "Sword" -> (83+119+111+114+100) % 10 = 527 % 10 = 7
int HashTable::hashFunction(const std::string& key) const {
    int sum = 0;
    for (int i = 0; i < (int)key.size(); i++) {
        sum += key[i]; // key[i] is a char; adding it treats it as its ASCII value
    }
    return sum % size; // keep index within 0 .. size-1
}

// Insert an item into the bucket that its name hashes to
void HashTable::insert(const Item& item) {
    int bucket = hashFunction(item.getName());
    table[bucket].push_back(item); // append to the chain in that bucket
}

// Search for an item by name.
// Returns a copy of the Item if found, or a default Item() if not found.
// Check result.getName() == "Nothing" to detect a miss.
Item HashTable::search(const std::string& name) const {
    int bucket = hashFunction(name);
    for (int i = 0; i < (int)table[bucket].size(); i++) {
        if (table[bucket][i].getName() == name) {
            return table[bucket][i];
        }
    }
    return Item(); // not found — returns default "Nothing" item
}

// Print the full table — handy for seeing how items are distributed
void HashTable::display() const {
    for (int i = 0; i < size; i++) {
        std::cout << "Bucket " << i << ": ";
        if (table[i].empty()) {
            std::cout << "(empty)";
        } else {
            for (int j = 0; j < (int)table[i].size(); j++) {
                std::cout << table[i][j].getName();
                if (j < (int)table[i].size() - 1) std::cout << " -> ";
            }
        }
        std::cout << "\n";
    }
}
