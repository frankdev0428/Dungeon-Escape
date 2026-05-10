#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <string>
#include "Item.h"

// A hash table that stores Items using chaining.
// "Chaining" means each bucket is a list — if two items hash to the
// same bucket they simply sit in the same inner vector.
class HashTable {
public:
    // Constructor — creates an empty table with the given number of buckets
    HashTable(int size);

    // Insert an item (uses item.getName() as the key)
    void insert(const Item& item);

    // Search by name — returns a pointer to the Item if found, nullptr if not
    Item* search(const std::string& name);

    // Print every bucket and every item inside it (useful for testing)
    void display() const;

private:
    int size;                          // number of buckets
    std::vector<std::vector<Item>> table; // the 2D structure: table[bucket][item]

    // Converts a string key into a bucket index (0 .. size-1)
    int hashFunction(const std::string& key) const;
};

#endif
