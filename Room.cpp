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
void Room::triggerEvent(const std::vector<Item>& items, InventoryBST& inventory, Player& player) {
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

        const int PLAYER_ATTACK = 10; // fixed damage per attack

        // ---- Combat loop ----
        // Runs until the enemy is defeated, the player dies, or the player runs.
        while (enemy.isAlive() && player.getHealth() > 0) {

            std::cout << "------------------------------\n";
            std::cout << "  Your HP : " << player.getHealth()
                      << "   " << enemy.getName() << " HP : " << enemy.getHealth() << "\n";
            std::cout << "  1. Attack   2. Run\n";
            std::cout << "  > ";

            int choice;
            std::cin >> choice;

            if (choice == 1) {
                // Player attacks enemy
                enemy.takeDamage(PLAYER_ATTACK);
                std::cout << "  You deal " << PLAYER_ATTACK << " damage."
                          << " " << enemy.getName() << " HP: " << enemy.getHealth() << "\n";

                if (!enemy.isAlive()) {
                    std::cout << "  " << enemy.getName() << " defeated!\n";
                    break; // enemy is dead — exit combat
                }

                // Enemy counter-attacks
                int dmg = enemy.getAttack();
                player.takeDamage(dmg);
                std::cout << "  " << enemy.getName() << " attacks!"
                          << " You lose " << dmg << " HP."
                          << " Your HP: " << player.getHealth() << "\n";

            } else {
                // Player chose to run — exit combat immediately
                std::cout << "  You fled from the " << enemy.getName() << "!\n";
                break;
            }
        }

        if (player.getHealth() <= 0) {
            std::cout << "  You were defeated by the " << enemy.getName() << "...\n";
        }
        std::cout << "------------------------------\n";

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
