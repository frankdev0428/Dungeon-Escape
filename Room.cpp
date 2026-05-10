#include <iostream>
#include "Room.h"

// Start every room as empty and unvisited
Room::Room() {
    type    = EMPTY;
    visited = false;
}

void Room::setType(RoomType t) {
    type = t;
}

RoomType Room::getType() const {
    return type;
}

bool Room::isVisited() const {
    return visited;
}

void Room::setVisited(bool v) {
    visited = v;
}

// Fire the room event the first time the player steps in.
// On repeat visits nothing happens — the room is already "spent".
void Room::triggerEvent() {
    if (visited) {
        return; // already seen this room, skip
    }

    // Print a message based on what kind of room this is
    if (type == EMPTY) {
        std::cout << "This room is empty.\n";
    } else if (type == ENEMY) {
        std::cout << "An enemy appears!\n";
    } else if (type == ITEM) {
        std::cout << "You found an item!\n";
    }

    visited = true; // mark so the event won't fire again
}

// Print a human-readable description of this room's type
void Room::displayRoomInfo() const {
    if (type == EMPTY) {
        std::cout << "Empty room\n";
    } else if (type == ENEMY) {
        std::cout << "Enemy room\n";
    } else if (type == ITEM) {
        std::cout << "Item room\n";
    }
}
