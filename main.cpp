#include <iostream>
#include <string>
#include <cstdlib> // srand()
#include <ctime>   // time()
#include "Player.h"
#include "Room.h"
#include "Map.h"

int main() {
    // Seed random so the map layout differs each run
    srand(time(0));

    Map map;
    Player player; // starts at (0, 0)

    // Trigger the starting room immediately — player spawns here
    map.getRoom(player.getX(), player.getY()).triggerEvent();

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
        // triggerEvent() does nothing if this room was already visited.
        Room& currentRoom = map.getRoom(player.getX(), player.getY());
        currentRoom.triggerEvent();
    }

    return 0;
}
