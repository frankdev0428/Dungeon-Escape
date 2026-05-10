#include <iostream>
#include <string>
#include "Player.h"
#include "Room.h"

const int GRID_SIZE = 5;

// Draw the 5x5 grid in the console.
// The outer loop goes row by row (y), the inner loop goes column by column (x).
// When the cell matches the player's position, print "P"; otherwise print ".".
void displayGrid(const Player& player) {
    std::cout << "\n";
    for (int row = 0; row < GRID_SIZE; row++) {
        for (int col = 0; col < GRID_SIZE; col++) {
            if (row == player.y && col == player.x) {
                std::cout << "P "; // player's current position
            } else {
                std::cout << ". "; // empty cell
            }
        }
        std::cout << "\n"; // end of this row
    }
    std::cout << "\n";
}

int main() {
    // ---- Room type test ----
    // Create one room of each type and print its info
    Room r1;                   // default → EMPTY
    Room r2;
    r2.setType(ENEMY);
    Room r3;
    r3.setType(ITEM);

    std::cout << "--- Room Test ---\n";
    r1.displayRoomInfo(); // should print: Empty room
    r2.displayRoomInfo(); // should print: Enemy room
    r3.displayRoomInfo(); // should print: Item room
    std::cout << "-----------------\n\n";

    Player player; // create player — starts at (0, 0)

    std::cout << "=== Dungeon Escape ===\n";
    std::cout << "Move with W (north) / S (south) / A (west) / D (east)\n";
    std::cout << "Type Q to quit.\n";

    // ---- Game loop ----
    // Runs forever until the player types Q
    while (true) {
        displayGrid(player);

        std::cout << "Position: (" << player.x << ", " << player.y << ")\n";
        std::cout << "Enter move: ";

        std::string input;
        std::cin >> input;

        // Convert first character to uppercase so 'w' and 'W' both work
        char command = toupper(input[0]);

        if (command == 'W') {
            player.moveNorth();
        } else if (command == 'S') {
            player.moveSouth();
        } else if (command == 'A') {
            player.moveWest();
        } else if (command == 'D') {
            player.moveEast();
        } else if (command == 'Q') {
            std::cout << "Thanks for playing. Goodbye!\n";
            break; // exit the game loop
        } else {
            std::cout << "Unknown command. Use W/A/S/D to move, Q to quit.\n";
        }
    }

    return 0;
}
