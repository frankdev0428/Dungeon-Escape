#include <iostream>
#include <string>
#include <cstdlib> // srand()
#include <ctime>   // time()
#include "Player.h"
#include "Room.h"
#include "Map.h"

int main() {
    // Seed random so the map layout is different each run
    srand(time(0));

    // ---- Room test ----
    Room r1;
    Room r2; r2.setType(ENEMY);
    Room r3; r3.setType(ITEM);

    std::cout << "--- Room Test ---\n";
    r1.displayRoomInfo();
    r2.displayRoomInfo();
    r3.displayRoomInfo();
    std::cout << "-----------------\n\n";

    // ---- Map test ----
    Map map;
    Player player; // starts at (0, 0)

    std::cout << "--- Map Test ---\n";
    std::cout << "Room at (0,0): "; map.getRoom(0, 0).displayRoomInfo();
    std::cout << "Room at (2,2): "; map.getRoom(2, 2).displayRoomInfo();
    std::cout << "Room at (4,4): "; map.getRoom(4, 4).displayRoomInfo();
    std::cout << "----------------\n\n";

    // Trigger the starting room's event immediately (player spawns here)
    map.getRoom(player.x, player.y).triggerEvent();

    // ---- Game loop ----
    std::cout << "=== Dungeon Escape ===\n";
    std::cout << "Move with W/S/A/D. Q to quit.\n";

    while (true) {
        map.displayMap(player);

        std::cout << "Position: (" << player.x << ", " << player.y << ")\n";
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
            continue; // skip triggerEvent on invalid input
        }

        // After every valid move, fire the new room's event.
        // triggerEvent() does nothing if the room was already visited.
        map.getRoom(player.x, player.y).triggerEvent();
    }

    return 0;
}
