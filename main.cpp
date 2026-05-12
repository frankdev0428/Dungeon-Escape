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
#include "Pathfinder.h"
#include "Stack.h"

int main() {
    // ---- Dijkstra test ----
    // On an open 5x5 grid, shortest path = Manhattan distance: |4-x| + |4-y|
    // Test several positions and confirm Dijkstra matches the formula.
    struct TestCase { int x, y, expected; };
    TestCase tests[] = {
        {0, 0, 8}, // corners
        {4, 0, 4},
        {0, 4, 4},
        {4, 4, 0}, // already at exit
        {2, 2, 4}, // center
        {3, 3, 2}, // one step away
        {1, 3, 4}  // mid-grid
    };

    std::cout << "--- Dijkstra Test ---\n";
    bool allPassed = true;
    for (int i = 0; i < 7; i++) {
        int result = findShortestPath(tests[i].x, tests[i].y);
        bool passed = (result == tests[i].expected);
        if (!passed) allPassed = false;
        std::cout << "(" << tests[i].x << "," << tests[i].y << ") → "
                  << result << " steps  [expected " << tests[i].expected << "]  "
                  << (passed ? "PASS" : "FAIL") << "\n";
    }
    std::cout << (allPassed ? "All tests passed!\n" : "Some tests FAILED.\n");
    std::cout << "---------------------\n\n";

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
    Player player;          // starts at (0, 0)
    InventoryBST inventory; // grows as items are picked up
    Stack moveStack;        // remembers previous positions for undo

    // Trigger the starting room (inventory passed so ITEM rooms can insert)
    map.getRoom(player.getX(), player.getY()).triggerEvent(items, inventory);

    std::cout << "=== Dungeon Escape ===\n";
    std::cout << "W/S/A/D = move  |  U = undo  |  I = inventory  |  Q = quit\n";

    while (true) {
        map.displayMap(player);

        std::cout << "Position: (" << player.getX() << ", " << player.getY() << ")\n";

        int steps = findShortestPath(player.getX(), player.getY());
        std::cout << "Shortest path to exit: " << steps << " steps\n";

        std::cout << "Enter command: ";

        std::string input;
        std::cin >> input;
        char command = toupper(input[0]);

        if (command == 'U') {
            // Undo: restore the position saved before the last move
            if (moveStack.isEmpty()) {
                std::cout << "Nothing to undo.\n";
            } else {
                int prevX = moveStack.topX();
                int prevY = moveStack.topY();
                moveStack.pop();
                player.setPosition(prevX, prevY);
                std::cout << "Undo move!\n";
            }
            continue; // skip triggerEvent — no new room entered
        }

        if      (command == 'I') { inventory.displayInventory(); continue; }
        else if (command == 'Q') { std::cout << "Thanks for playing. Goodbye!\n"; break; }
        else if (command != 'W' && command != 'S' &&
                 command != 'A' && command != 'D') {
            std::cout << "Unknown command. Use W/A/S/D, U, I, or Q.\n";
            continue;
        }

        // Save current position BEFORE moving so U can restore it
        moveStack.push(player.getX(), player.getY());

        if      (command == 'W') player.moveNorth();
        else if (command == 'S') player.moveSouth();
        else if (command == 'A') player.moveWest();
        else if (command == 'D') player.moveEast();

        // Fire the new room's event — inserts item into inventory if ITEM room
        Room& currentRoom = map.getRoom(player.getX(), player.getY());
        currentRoom.triggerEvent(items, inventory);
    }

    return 0;
}
