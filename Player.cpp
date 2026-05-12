#include "Player.h"

Player::Player(int gridRows, int gridCols) {
    x       = 0;
    y       = 0;
    health  = 100;
    attack  = 10;
    maxRows = gridRows;
    maxCols = gridCols;
}

int Player::getX()      const { return x;      }
int Player::getY()      const { return y;      }
int Player::getHealth() const { return health; }
int Player::getAttack() const { return attack; }

void Player::setPosition(int newX, int newY) {
    x = newX;
    y = newY;
}

void Player::takeDamage(int dmg) {
    health -= dmg;
    if (health < 0) health = 0;
}

void Player::heal(int amount) {
    health += amount;
    if (health > 100) health = 100;
}

void Player::increaseAttack(int amount) {
    attack += amount;
}

void Player::moveNorth() { if (y > 0)            y--; }
void Player::moveSouth() { if (y < maxRows - 1)  y++; }
void Player::moveWest()  { if (x > 0)            x--; }
void Player::moveEast()  { if (x < maxCols - 1)  x++; }
