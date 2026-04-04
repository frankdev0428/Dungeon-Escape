#include "Player.h"

// The grid is 5x5, so valid positions are 0..4 for both x and y
const int GRID_SIZE = 5;

// Start the player at the top-left corner
Player::Player() {
    x = 0;
    y = 0;
}

// Move up — row index decreases
// Check y > 0 so we don't go above the top row
void Player::moveNorth() {
    if (y > 0) {
        y--;
    }
}

// Move down — row index increases
// Check y < GRID_SIZE - 1 so we don't go below the bottom row
void Player::moveSouth() {
    if (y < GRID_SIZE - 1) {
        y++;
    }
}

// Move left — column index decreases
void Player::moveWest() {
    if (x > 0) {
        x--;
    }
}

// Move right — column index increases
void Player::moveEast() {
    if (x < GRID_SIZE - 1) {
        x++;
    }
}
