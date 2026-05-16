#include <iostream>
#include "UI.h"
#include "Colors.h"
#include "Utils.h"

static const std::string THICK = "==============================";
static const std::string THIN  = "------------------------------";

void printTitle() {
    std::cout << BOLD_CYAN << THICK << RESET << "\n";
    std::cout << BOLD_CYAN << "        DUNGEON  ESCAPE         " << RESET << "\n";
    std::cout << BOLD_CYAN << THICK << RESET << "\n";
}

void printHUD(const Player& player, int stepsToExit, int roomsVisited, int totalRooms) {
    std::cout << CYAN << THIN << RESET << "\n";
    std::cout << " Pos:(" << player.getX() << "," << player.getY() << ")  ";
    std::cout << "HP:";
    printBar(player.getHealth(), 100);
    std::cout << "  " << YELLOW << "ATK:" << player.getAttack() << RESET;
    std::cout << "  Steps:";
    if (stepsToExit < 0) std::cout << "?";
    else                 std::cout << stepsToExit;
    std::cout << "  Rooms:" << GREEN << roomsVisited << "/" << totalRooms << RESET << "\n";
    std::cout << CYAN << THIN << RESET << "\n";
}

void printMap(const Map& map, const Player& player) {
    const int EXIT_X = map.getExitX();
    const int EXIT_Y = map.getExitY();
    std::cout << "\n";
    for (int row = 0; row < map.getRows(); row++) {
        std::cout << "  ";
        for (int col = 0; col < map.getCols(); col++) {
            if (row == player.getY() && col == player.getX()) {
                std::cout << BOLD_GREEN << "P " << RESET;
            } else if (row == EXIT_Y && col == EXIT_X) {
                std::cout << BOLD_CYAN << "E " << RESET;
            } else if (map.getRoom(col, row).isVisited()) {
                std::cout << YELLOW << "* " << RESET;
            } else {
                std::cout << ". ";
            }
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void printMenu() {
    std::cout << THIN << "\n";
    std::cout << "  W = North   S = South   A = West   D = East\n";
    std::cout << "  U = Undo    I = Inventory          Q = Quit\n";
    std::cout << THIN << "\n";
}
