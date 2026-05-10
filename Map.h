#ifndef MAP_H
#define MAP_H

#include <vector>
#include "Room.h"
#include "Player.h"

class Map {
public:
    // Constructor: builds and randomly fills the 5x5 grid
    Map();

    // Returns a reference to the room at column x, row y
    Room& getRoom(int x, int y);

    // Prints the grid — shows "P" at the player's position, "." elsewhere
    void displayMap(const Player& player) const;

private:
    int rows;
    int cols;
    std::vector<std::vector<Room>> grid; // grid[row][col]
};

#endif
