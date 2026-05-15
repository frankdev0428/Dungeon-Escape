#ifndef MAP_H
#define MAP_H

#include <vector>
#include "Room.h"
#include "Player.h"

class Map {
public:
    Map(int r, int c);

    int getRows()  const;
    int getCols()  const;
    int getExitX() const;
    int getExitY() const;

    Room& getRoom(int x, int y);
    void displayMap(const Player& player) const;

private:
    int rows;
    int cols;
    int exitX;
    int exitY;
    std::vector<std::vector<Room>> grid;
};

#endif
