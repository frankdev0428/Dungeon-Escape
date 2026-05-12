#include <iostream>
#include "UI.h"

// Reusable separator lines
static const std::string THICK = "==============================";
static const std::string THIN  = "------------------------------";

void printTitle() {
    std::cout << THICK << "\n";
    std::cout << "        DUNGEON  ESCAPE         \n";
    std::cout << THICK << "\n";
}

// HUD: shows the player's stats and distance to exit on one line block
void printHUD(const Player& player, int stepsToExit) {
    std::cout << THIN << "\n";
    std::cout << " Position : (" << player.getX() << ", " << player.getY() << ")"
              << "   HP : " << player.getHealth()
              << "   Steps to exit : " << stepsToExit << "\n";
    std::cout << THIN << "\n";
}

// Map: draws the 5x5 grid — P = player, E = exit, . = empty cell
void printMap(const Map& map, const Player& player) {
    const int GRID   = 5;
    const int EXIT_X = 4;
    const int EXIT_Y = 4;
    std::cout << "\n";
    for (int row = 0; row < GRID; row++) {
        std::cout << "  ";
        for (int col = 0; col < GRID; col++) {
            if (row == player.getY() && col == player.getX()) {
                std::cout << "P ";
            } else if (row == EXIT_Y && col == EXIT_X) {
                std::cout << "E "; // exit tile — always visible
            } else {
                std::cout << ". ";
            }
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

// Command menu shown below the map every turn
void printMenu() {
    std::cout << THIN << "\n";
    std::cout << "  W = North   S = South   A = West   D = East\n";
    std::cout << "  U = Undo    I = Inventory          Q = Quit\n";
    std::cout << THIN << "\n";
}
