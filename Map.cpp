#include <iostream>
#include <cstdlib> // rand()
#include "Map.h"

Map::Map(int r, int c) {
    rows = r;
    cols = c;
    grid.resize(rows, std::vector<Room>(cols));

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            int roll = rand() % 3;
            if      (roll == 0) grid[row][col].setType(EMPTY);
            else if (roll == 1) grid[row][col].setType(ENEMY);
            else                grid[row][col].setType(ITEM);
        }
    }
}

int Map::getRows() const { return rows; }
int Map::getCols() const { return cols; }

Room& Map::getRoom(int x, int y) {
    return grid[y][x];
}

void Map::displayMap(const Player& player) const {
    std::cout << "\n";
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if (row == player.getY() && col == player.getX())
                std::cout << "P ";
            else
                std::cout << ". ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}
