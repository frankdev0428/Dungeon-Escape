#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "core/Player.h"
#include "core/Room.h"
#include "core/Map.h"
#include "core/Item.h"
#include "systems/ItemLoader.h"
#include "ds/HashTable.h"
#include "ds/BST.h"
#include "core/Enemy.h"
#include "ds/MergeSort.h"
#include "systems/Dijkstra.h"
#include "ds/Stack.h"
#include "systems/Display.h"
#include "utils/Colors.h"

int main() {
    srand(time(0));

    std::vector<Item> items = loadItemsFromFile("data/items.txt");
    HashTable ht(10);
    for (int i = 0; i < (int)items.size(); i++) {
        ht.insert(items[i]);
    }

    const int MAP_ROWS    = 8; // change here to resize the whole dungeon
    const int MAP_COLS    = 8;
    const int TOTAL_ROOMS = MAP_ROWS * MAP_COLS;

    printTitle();

    while (true) {  // play-again loop
        Map  map(MAP_ROWS, MAP_COLS);
        Player player(MAP_ROWS, MAP_COLS);
        BST  inventory;
        Stack moveStack;

        while (true) {  // game loop
            // 1. Always render map first
            std::cout << CLEAR_SCREEN << std::flush;
            int steps = findShortestPath(player.getX(), player.getY(),
                                         map.getRows(), map.getCols(),
                                         map.getExitX(), map.getExitY());
            printHUD(player, steps, map.countVisited(), TOTAL_ROOMS);
            printMap(map, player);
            printMenu();

            // 2. Trigger current room's event (visited flag prevents double-firing)
            map.getRoom(player.getX(), player.getY()).triggerEvent(items, inventory, player);

            // 3. Check end conditions after event resolves
            if (player.getHealth() <= 0) {
                std::cout << CLEAR_SCREEN << std::flush;
                printHUD(player, 0, map.countVisited(), TOTAL_ROOMS);
                printMap(map, player);
                std::cout << BOLD_RED << "==============================\n";
                std::cout << "        GAME  OVER            \n";
                std::cout << "  You were defeated...        \n";
                std::cout << "==============================" << RESET << "\n\n";
                break;
            }

            if (player.getX() == map.getExitX() && player.getY() == map.getExitY()) {
                std::cout << CLEAR_SCREEN << std::flush;
                printHUD(player, 0, map.countVisited(), TOTAL_ROOMS);
                printMap(map, player);
                std::cout << BOLD_GREEN << "==============================\n";
                std::cout << "   You escaped the dungeon!   \n";
                std::cout << "==============================" << RESET << "\n\n";
                break;
            }

            // 4. Read command
            std::cout << "  > ";
            std::string input;
            std::cin >> input;
            if (input.empty()) continue;
            char command = toupper(input[0]);

            if (command == 'U') {
                if (moveStack.isEmpty()) {
                    std::cout << "  Nothing to undo.\n";
                } else {
                    int prevX = moveStack.topX();
                    int prevY = moveStack.topY();
                    player.setPosition(prevX, prevY);
                    moveStack.pop();
                    std::cout << "  Moved back to (" << prevX << ", " << prevY << ").\n";
                }
                continue;
            }

            if (command == 'I') {
                inventory.displayInventory();
                std::cin.ignore(1000, '\n');
                std::cout << "\n  Press Enter to continue...";
                std::cin.get();
                continue;
            }

            if (command == 'Q') {
                std::cout << "\n  Thanks for playing. Goodbye!\n\n";
                return 0;
            }

            if (command != 'W' && command != 'S' &&
                command != 'A' && command != 'D') {
                std::cout << "  Unknown command. Use W/A/S/D, U, I, or Q.\n";
                continue;
            }

            // 5. Move
            moveStack.push(player.getX(), player.getY());
            if      (command == 'W') player.moveNorth();
            else if (command == 'S') player.moveSouth();
            else if (command == 'A') player.moveWest();
            else if (command == 'D') player.moveEast();
        }

        std::cout << "  Play again? (Y / N): ";
        std::string again;
        std::cin >> again;
        if (again.empty() || toupper(again[0]) != 'Y') {
            std::cout << "\n  Thanks for playing. Goodbye!\n\n";
            break;
        }

        printTitle();
    }

    return 0;
}
