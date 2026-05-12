#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
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
#include "UI.h"

int main() {
    srand(time(0));

    // Load items from file and index them in the hash table
    std::vector<Item> items = loadItemsFromFile("items.txt");
    HashTable ht(10);
    for (int i = 0; i < items.size(); i++) {
        ht.insert(items[i]);
    }

    Map map;
    Player player;
    InventoryBST inventory;
    Stack moveStack;

    printTitle();

    // Trigger the starting room so the player sees an event on the first turn
    map.getRoom(player.getX(), player.getY()).triggerEvent(items, inventory, player);

    while (true) {
        int steps = findShortestPath(player.getX(), player.getY());
        printHUD(player, steps);
        printMap(map, player);
        printMenu();

        std::cout << "  > ";

        std::string input;
        std::cin >> input;
        char command = toupper(input[0]);

        if (command == 'U') {
            if (moveStack.isEmpty()) {
                std::cout << "  Nothing to undo.\n";
            } else {
                player.setPosition(moveStack.topX(), moveStack.topY());
                moveStack.pop();
                std::cout << "  Undo move!\n";
            }
            continue;
        }

        if      (command == 'I') { inventory.displayInventory(); continue; }
        else if (command == 'Q') { std::cout << "\n  Thanks for playing. Goodbye!\n\n"; break; }
        else if (command != 'W' && command != 'S' &&
                 command != 'A' && command != 'D') {
            std::cout << "  Unknown command. Use W/A/S/D, U, I, or Q.\n";
            continue;
        }

        moveStack.push(player.getX(), player.getY());

        if      (command == 'W') player.moveNorth();
        else if (command == 'S') player.moveSouth();
        else if (command == 'A') player.moveWest();
        else if (command == 'D') player.moveEast();

        map.getRoom(player.getX(), player.getY()).triggerEvent(items, inventory, player);

        // Game over — player ran out of health
        if (player.getHealth() <= 0) {
            printHUD(player, findShortestPath(player.getX(), player.getY()));
            printMap(map, player);
            std::cout << "==============================\n";
            std::cout << "        GAME  OVER            \n";
            std::cout << "  You were defeated...        \n";
            std::cout << "==============================\n\n";
            break;
        }

        // Win condition — player reached the exit at (4,4)
        if (player.getX() == 4 && player.getY() == 4) {
            int steps = findShortestPath(player.getX(), player.getY());
            printHUD(player, steps);
            printMap(map, player);
            std::cout << "==============================\n";
            std::cout << "   You escaped the dungeon!   \n";
            std::cout << "==============================\n\n";
            break;
        }
    }

    return 0;
}
