#ifndef PLAYER_H
#define PLAYER_H

class Player {
public:
    // Constructor: start at top-left corner (0, 0)
    Player();

    // Getters — the only way to read position from outside the class
    int getX() const;
    int getY() const;

    // Directly set position — used by the undo system to restore a saved spot
    void setPosition(int newX, int newY);

    // Movement — each checks bounds before moving
    void moveNorth(); // up    (decrease y)
    void moveSouth(); // down  (increase y)
    void moveWest();  // left  (decrease x)
    void moveEast();  // right (increase x)

private:
    int x; // column (left-right), 0 = leftmost
    int y; // row    (up-down),    0 = top
};

#endif
