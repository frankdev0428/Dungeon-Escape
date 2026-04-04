#ifndef PLAYER_H
#define PLAYER_H

// Player class declaration
// Holds the player's position and provides movement functions

class Player {
public:
    int x; // column (left-right)
    int y; // row (up-down)

    // Constructor: start at top-left corner (0,0)
    Player();

    // Movement functions — each tries to move one step in that direction
    void moveNorth(); // up    (decrease y)
    void moveSouth(); // down  (increase y)
    void moveWest();  // left  (decrease x)
    void moveEast();  // right (increase x)
};

#endif
