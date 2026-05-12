#include <iostream>
#include <string>
#include <cstdlib> // srand()
#include <ctime>   // time()
#include "Player.h"
#include "Room.h"
#include "Map.h"
#include "Item.h"
#include "ItemLoader.h"
#include "HashTable.h"
#include "InventoryBST.h"

int main() {
    // ---- Load items from file ----
    std::vector<Item> items = loadItemsFromFile("items.txt");

    std::cout << "--- Loaded Items ---\n";
    for (int i = 0; i < items.size(); i++) {
        items[i].displayItem();
    }
    std::cout << "--------------------\n\n";

    // ---- Hash table test ----
    HashTable ht(10); // create a table with 10 buckets

    // Insert every loaded item into the hash table
    for (int i = 0; i < items.size(); i++) {
        ht.insert(items[i]);
    }

    // Show how items are distributed across buckets
    std::cout << "--- Hash Table ---\n";
    ht.display();
    std::cout << "------------------\n\n";

    // Search for items that exist and one that does not
    std::cout << "--- Search Test ---\n";
    std::string queries[] = { "Sword", "Iron_Boots", "Axe" };
    for (int i = 0; i < 3; i++) {
        Item* found = ht.search(queries[i]);
        if (found != nullptr) {
            std::cout << "Found: "; found->displayItem();
        } else {
            std::cout << "\"" << queries[i] << "\" not found in table.\n";
        }
    }
    std::cout << "-------------------\n\n";

    // Seed random so the map layout differs each run
    srand(time(0));

    Map map;
    Player player; // starts at (0, 0)

    // ---- BST test ----
    // Insert a few items in a deliberate order to show the tree structure:
    //   value 15 goes in first (becomes root)
    //   value 8  is smaller  → goes left
    //   value 30 is larger   → goes right
    //   value 10 is smaller than 15, larger than 8 → goes right of 8
    InventoryBST bst;
    bst.insertItem(Item("Sword",         15));
    bst.insertItem(Item("Iron_Boots",     8));
    bst.insertItem(Item("Health_Potion", 30));
    bst.insertItem(Item("Shield",        10));

    // Display inventory in sorted order to verify the BST is ordered correctly
    // Expected order by value: Iron_Boots(8), Shield(10), Sword(15), Health_Potion(30)
    std::cout << "\n";
    bst.displayInventory();
    std::cout << "\n";

    // Trigger the starting room immediately — player spawns here
    map.getRoom(player.getX(), player.getY()).triggerEvent(items);

    std::cout << "=== Dungeon Escape ===\n";
    std::cout << "Move with W/S/A/D. Q to quit.\n";

    while (true) {
        // Draw the grid with "P" at the player's current position
        map.displayMap(player);

        std::cout << "Position: (" << player.getX() << ", " << player.getY() << ")\n";
        std::cout << "Enter move: ";

        std::string input;
        std::cin >> input;
        char command = toupper(input[0]);

        // Move the player — each function checks bounds internally
        if      (command == 'W') player.moveNorth();
        else if (command == 'S') player.moveSouth();
        else if (command == 'A') player.moveWest();
        else if (command == 'D') player.moveEast();
        else if (command == 'Q') {
            std::cout << "Thanks for playing. Goodbye!\n";
            break;
        } else {
            std::cout << "Unknown command. Use W/A/S/D to move, Q to quit.\n";
            continue; // skip triggerEvent — player didn't actually move
        }

        // Get the room the player just entered and fire its event.
        // triggerEvent(items) does nothing if this room was already visited.
        Room& currentRoom = map.getRoom(player.getX(), player.getY());
        currentRoom.triggerEvent(items);
    }

    return 0;
}
