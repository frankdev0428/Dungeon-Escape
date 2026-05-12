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
