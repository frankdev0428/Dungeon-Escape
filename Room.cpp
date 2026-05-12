#include <iostream>
#include <queue>   // std::priority_queue
#include <utility> // std::pair
#include <cstdlib> // rand()
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
void Room::triggerEvent(const std::vector<Item>& items, InventoryBST& inventory) {
    if (visited) {
        return; // already seen this room, skip
    }

    if (type == EMPTY) {
        std::cout << ">> This room is empty. Nothing of interest here.\n";

    } else if (type == ENEMY) {
        int roll = rand() % 3;
        Enemy enemy("Unknown", 0, 0);

        if (roll == 0) enemy = Enemy("Goblin",   20, 5);
        else if (roll == 1) enemy = Enemy("Orc",  30, 8);
        else                enemy = Enemy("Skeleton", 15, 4);

        std::cout << "** An enemy blocks your path! **\n";
        std::cout << "   ";
        enemy.displayEnemy();

        std::priority_queue<std::pair<int, std::string>> turnPQ;
        turnPQ.push({10, "Player"});
        turnPQ.push({5,  "Enemy"});

        std::cout << "-- Turn Order --\n";
        while (!turnPQ.empty()) {
            std::pair<int, std::string> current = turnPQ.top();
            turnPQ.pop();

            if (current.second == "Player") {
                std::cout << "   You attack first!\n";
            } else {
                std::cout << "   " << enemy.getName() << " attacks back!\n";
            }
        }
        std::cout << "----------------\n";

    } else if (type == ITEM) {
        if (!items.empty()) {
            int index = rand() % items.size();
            const Item& found = items[index];
            std::cout << ">> You found: " << found.getName()
                      << " (Value: " << found.getValue() << ")"
                      << " -- added to inventory.\n";
            inventory.insertItem(found);
        } else {
            std::cout << ">> This room once had an item, but it is gone.\n";
        }
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
