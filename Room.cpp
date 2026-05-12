#include <iostream>
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
        std::cout << "This room is empty.\n";
    } else if (type == ENEMY) {
        // Pick one of three enemy types at random
        int roll = rand() % 3;
        Enemy enemy("Unknown", 0, 0); // placeholder, overwritten below

        if (roll == 0) enemy = Enemy("Goblin",   20, 5);
        else if (roll == 1) enemy = Enemy("Orc",  30, 8);
        else                enemy = Enemy("Skeleton", 15, 4);

        std::cout << "An enemy appears!\n";
        enemy.displayEnemy();

        // ---- Turn queue (FIFO) ----
        // Push both combatants in order — Player always goes first
        Queue turnQueue;
        turnQueue.push("Player");
        turnQueue.push("Enemy");

        // Process each turn: read the front, print the action, remove it
        // FIFO guarantees Player → Enemy order every time
        std::cout << "--- Turn Order ---\n";
        while (!turnQueue.isEmpty()) {
            std::string turn = turnQueue.front(); // peek at who goes next
            turnQueue.pop();                      // remove them from the queue

            if (turn == "Player") {
                std::cout << "Player attacks!\n";
            } else {
                std::cout << enemy.getName() << " attacks!\n";
            }
        }
        std::cout << "------------------\n";

    } else if (type == ITEM) {
        if (!items.empty()) {
            // Pick a random item from the pool and show it
            int index = rand() % items.size();
            const Item& found = items[index];
            std::cout << "You found: " << found.getName()
                      << " (Value: " << found.getValue() << ")\n";
            // Add it to the player's inventory BST (visited flag ensures once only)
            inventory.insertItem(found);
        } else {
            std::cout << "The room is empty — no items left.\n";
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
