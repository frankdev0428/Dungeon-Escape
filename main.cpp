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
#include "Colors.h"

int main() {
    srand(time(0));

    std::vector<Item> items = loadItemsFromFile("items.txt");
    HashTable ht(10);
    for (int i = 0; i < items.size(); i++) {
        ht.insert(items[i]);
    }

    const int MAP_ROWS = 8; // change here to resize the whole dungeon
    const int MAP_COLS = 8;

    Map map(MAP_ROWS, MAP_COLS);
    Player player(MAP_ROWS, MAP_COLS);
    InventoryBST inventory;
    Stack moveStack;

    printTitle();

    map.getRoom(player.getX(), player.getY()).triggerEvent(items, inventory, player);

    while (true) {
        int steps = findShortestPath(player.getX(), player.getY(), map.getRows(), map.getCols(), map.getExitX(), map.getExitY());
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

        // Game over
        if (player.getHealth() <= 0) {
            int steps = findShortestPath(player.getX(), player.getY(), map.getRows(), map.getCols(), map.getExitX(), map.getExitY());
            printHUD(player, steps);
            printMap(map, player);
            std::cout << BOLD_RED << "==============================\n";
            std::cout << "        GAME  OVER            \n";
            std::cout << "  You were defeated...        \n";
            std::cout << "==============================" << RESET << "\n\n";
            break;
        }

        // Win condition — player reached the random exit
        if (player.getX() == map.getExitX() && player.getY() == map.getExitY()) {
            int steps = findShortestPath(player.getX(), player.getY(), map.getRows(), map.getCols(), map.getExitX(), map.getExitY());
            printHUD(player, steps);
            printMap(map, player);
            std::cout << BOLD_GREEN << "==============================\n";
            std::cout << "   You escaped the dungeon!   \n";
            std::cout << "==============================" << RESET << "\n\n";
            break;
        }
    }

    return 0;
}
