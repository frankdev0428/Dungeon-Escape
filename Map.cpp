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

    // Random exit — anywhere except the starting cell (0,0)
    do {
        exitX = rand() % cols;
        exitY = rand() % rows;
    } while (exitX == 0 && exitY == 0);

    // Exit cell must be empty so no enemy blocks the escape
    grid[exitY][exitX].setType(EMPTY);
}

int Map::getRows()  const { return rows;  }
int Map::getCols()  const { return cols;  }
int Map::getExitX() const { return exitX; }
int Map::getExitY() const { return exitY; }

Room& Map::getRoom(int x, int y) {
    return grid[y][x];
}

const Room& Map::getRoom(int x, int y) const {
    return grid[y][x];
}

int Map::countVisited() const {
    int count = 0;
    for (int row = 0; row < rows; row++)
        for (int col = 0; col < cols; col++)
            if (grid[row][col].isVisited()) count++;
    return count;
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
