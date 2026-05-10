#include "Player.h"

const int GRID_SIZE = 5; // valid positions are 0..4

Player::Player() {
    x = 0;
    y = 0;
}

int Player::getX() const { return x; }
int Player::getY() const { return y; }

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
