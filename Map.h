#ifndef MAP_H
#define MAP_H

#include <vector>
#include "Room.h"
#include "Player.h"

class Map {
public:
    // Constructor: builds and randomly fills an r x c grid
    Map(int r, int c);

    int getRows() const;
    int getCols() const;

    Room& getRoom(int x, int y);
    void displayMap(const Player& player) const;

private:
    int rows;
    int cols;
    std::vector<std::vector<Room>> grid; // grid[row][col]
};

#endif
