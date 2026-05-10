#include <iostream>
#include <cstdlib> // rand()
#include "Map.h"

Map::Map() {
    rows = 5;
    cols = 5;

    // Resize the outer vector to hold 'rows' rows,
    // each row is a vector of 'cols' Room objects
    grid.resize(rows, std::vector<Room>(cols));

    // Randomly assign a type to every room
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            int roll = rand() % 3; // gives 0, 1, or 2

            if (roll == 0) {
                grid[row][col].setType(EMPTY);
            } else if (roll == 1) {
                grid[row][col].setType(ENEMY);
            } else {
                grid[row][col].setType(ITEM);
            }
        }
    }
}

// x = column, y = row
Room& Map::getRoom(int x, int y) {
    return grid[y][x];
}

void Map::displayMap(const Player& player) const {
    std::cout << "\n";
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if (row == player.y && col == player.x) {
                std::cout << "P "; // player is here
            } else {
                std::cout << ". "; // unexplored cell
            }
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}
