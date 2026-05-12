#ifndef PLAYER_H
#define PLAYER_H

class Player {
public:
    // Constructor: start at top-left corner (0, 0)
    Player();

    // Getters
    int getX()      const;
    int getY()      const;
    int getHealth() const;

    void setPosition(int newX, int newY); // used by undo to restore position
    void takeDamage(int dmg);             // reduce health; clamps at 0
    void heal(int amount);                // restore health; caps at 100

    // Movement — each checks bounds before moving
    void moveNorth(); // up    (decrease y)
    void moveSouth(); // down  (increase y)
    void moveWest();  // left  (decrease x)
    void moveEast();  // right (increase x)

private:
    int x;
    int y;
    int health; // starts at 100
};

#endif
