#include <iostream>
#include <string>
#include <cstdlib> // srand()
#include <ctime>   // time()
#include "Player.h"
#include "Room.h"
#include "Map.h"

int main() {
    // Seed random so the map is different each run
    srand(time(0));

    // ---- Room type test ----
    Room r1;
    Room r2; r2.setType(ENEMY);
    Room r3; r3.setType(ITEM);

    std::cout << "--- Room Test ---\n";
    r1.displayRoomInfo(); // Empty room
    r2.displayRoomInfo(); // Enemy room
    r3.displayRoomInfo(); // Item room
    std::cout << "-----------------\n\n";

    // ---- Map test ----
    // Build the map and check a few rooms by position
    Map map;
    Player player; // starts at (0, 0)

    std::cout << "--- Map Test ---\n";
    std::cout << "Room at (0,0): "; map.getRoom(0, 0).displayRoomInfo();
    std::cout << "Room at (2,2): "; map.getRoom(2, 2).displayRoomInfo();
    std::cout << "Room at (4,4): "; map.getRoom(4, 4).displayRoomInfo();
    std::cout << "----------------\n";

    // ---- Game loop ----
    std::cout << "=== Dungeon Escape ===\n";
    std::cout << "Move with W/S/A/D. Q to quit.\n";

    while (true) {
        map.displayMap(player); // draw the grid with player position

        std::cout << "Position: (" << player.x << ", " << player.y << ")  ";
        std::cout << "Current room: ";
        map.getRoom(player.x, player.y).displayRoomInfo();

        std::cout << "Enter move: ";
        std::string input;
        std::cin >> input;

        char command = toupper(input[0]);

        if      (command == 'W') player.moveNorth();
        else if (command == 'S') player.moveSouth();
        else if (command == 'A') player.moveWest();
        else if (command == 'D') player.moveEast();
        else if (command == 'Q') {
            std::cout << "Thanks for playing. Goodbye!\n";
            break;
        } else {
            std::cout << "Unknown command. Use W/A/S/D to move, Q to quit.\n";
        }
    }

    return 0;
}
