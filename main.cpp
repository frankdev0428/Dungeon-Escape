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
#include "Enemy.h"
#include "Sorter.h"

int main() {
    // ---- Sort test ----
    // Create a vector with items in a random order
    std::vector<Item> sortTest;
    sortTest.push_back(Item("Magic_Staff",   20));
    sortTest.push_back(Item("Iron_Boots",     8));
    sortTest.push_back(Item("Health_Potion", 30));
    sortTest.push_back(Item("Sword",         15));
    sortTest.push_back(Item("Shield",        10));

    std::cout << "--- Before Sort ---\n";
    for (int i = 0; i < sortTest.size(); i++) {
        std::cout << sortTest[i].getName()
                  << " (Value: " << sortTest[i].getValue() << ")\n";
    }

    sortItems(sortTest); // run merge sort

    std::cout << "--- After Sort (ascending) ---\n";
    for (int i = 0; i < sortTest.size(); i++) {
        std::cout << sortTest[i].getName()
                  << " (Value: " << sortTest[i].getValue() << ")\n";
    }
    std::cout << "\n";
    // ---- Enemy test ----
    Enemy goblin("Goblin", 30, 5);
    Enemy troll("Troll",   80, 12);

    std::cout << "--- Enemy Test ---\n";
    goblin.displayEnemy();
    troll.displayEnemy();

    // Simulate taking damage
    goblin.takeDamage(10);
    std::cout << "Goblin takes 10 damage:\n";
    goblin.displayEnemy();
    std::cout << "Goblin alive? " << (goblin.isAlive() ? "Yes" : "No") << "\n";

    goblin.takeDamage(999); // overkill — health should clamp to 0
    std::cout << "Goblin takes 999 damage:\n";
    goblin.displayEnemy();
    std::cout << "Goblin alive? " << (goblin.isAlive() ? "Yes" : "No") << "\n";
    std::cout << "------------------\n\n";
    // ---- Load items from file ----
    std::vector<Item> items = loadItemsFromFile("items.txt");

    std::cout << "--- Loaded Items ---\n";
    for (int i = 0; i < items.size(); i++) {
        items[i].displayItem();
    }
    std::cout << "--------------------\n\n";

    // ---- Hash table ----
    HashTable ht(10);
    for (int i = 0; i < items.size(); i++) {
        ht.insert(items[i]);
    }

    std::cout << "--- Hash Table ---\n";
    ht.display();
    std::cout << "------------------\n\n";

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
    Player player;       // starts at (0, 0)
    InventoryBST inventory; // player's inventory — grows as items are picked up

    // Trigger the starting room (inventory passed so ITEM rooms can insert)
    map.getRoom(player.getX(), player.getY()).triggerEvent(items, inventory);

    std::cout << "=== Dungeon Escape ===\n";
    std::cout << "W/S/A/D = move  |  I = inventory  |  Q = quit\n";

    while (true) {
        map.displayMap(player);

        std::cout << "Position: (" << player.getX() << ", " << player.getY() << ")\n";
        std::cout << "Enter command: ";

        std::string input;
        std::cin >> input;
        char command = toupper(input[0]);

        if      (command == 'W') player.moveNorth();
        else if (command == 'S') player.moveSouth();
        else if (command == 'A') player.moveWest();
        else if (command == 'D') player.moveEast();
        else if (command == 'I') {
            // Show everything the player has collected so far (sorted by value)
            inventory.displayInventory();
            continue; // no movement — skip triggerEvent
        } else if (command == 'Q') {
            std::cout << "Thanks for playing. Goodbye!\n";
            break;
        } else {
            std::cout << "Unknown command. Use W/A/S/D to move, I for inventory, Q to quit.\n";
            continue;
        }

        // Fire the new room's event — inserts item into inventory if ITEM room
        Room& currentRoom = map.getRoom(player.getX(), player.getY());
        currentRoom.triggerEvent(items, inventory);
    }

    return 0;
}
