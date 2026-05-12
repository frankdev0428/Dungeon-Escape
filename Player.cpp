#include "Player.h"

const int GRID_SIZE = 5; // valid positions are 0..4

Player::Player() {
    x      = 0;
    y      = 0;
    health = 100;
}

int Player::getX()      const { return x;      }
int Player::getY()      const { return y;      }
int Player::getHealth() const { return health; }

void Player::setPosition(int newX, int newY) {
    x = newX;
    y = newY;
}

void Player::moveNorth() {
    if (y > 0) y--;
}

void Player::moveSouth() {
    if (y < GRID_SIZE - 1) y++;
}

void Player::moveWest() {
    if (x > 0) x--;
}

void Player::moveEast() {
    if (x < GRID_SIZE - 1) x++;
}
