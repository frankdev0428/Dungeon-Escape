#include <iostream>
#include <queue>
#include <utility>
#include <cstdlib>
#include "Room.h"
#include "Colors.h"

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
        int difficulty = player.getX() + player.getY();
        int roll = rand() % 3;
        Enemy enemy("Unknown", 0, 0);

        if (roll == 0) enemy = Enemy("Goblin",   20, 12 + difficulty);
        else if (roll == 1) enemy = Enemy("Orc",  30, 18 + difficulty);
        else                enemy = Enemy("Skeleton", 15, 10 + difficulty);

        if (difficulty > 0)
            std::cout << YELLOW << "  Enemy looks stronger..." << RESET << "\n";
        std::cout << RED << "** An enemy blocks your path! **" << RESET << "\n";
        std::cout << "   ";
        enemy.displayEnemy();

        // ---- Combat loop ----
        // Runs until the enemy is defeated, the player dies, or the player runs.
        while (enemy.isAlive() && player.getHealth() > 0) {

            std::cout << "------------------------------\n";
            std::cout << "  Your HP : " << player.getHealth()
                      << "  ATK : " << player.getAttack()
                      << "   " << enemy.getName() << " HP : " << enemy.getHealth() << "\n";
            std::cout << "  1. Attack   2. Run\n";
            std::cout << "  > ";

            // Read as string so non-integer input never breaks cin
            std::string input;
            std::cin >> input;
            int choice = 0;
            if (!input.empty()) choice = input[0] - '0'; // '1'->1, '2'->2, else 0

            if (choice == 1) {
                // Player attacks using their current attack stat
                int dmgDealt = player.getAttack();
                enemy.takeDamage(dmgDealt);
                std::cout << "  You deal " << dmgDealt << " damage."
                          << " " << enemy.getName() << " HP: " << enemy.getHealth() << "\n";

                if (!enemy.isAlive()) {
                    std::cout << GREEN << "  " << enemy.getName() << " defeated!" << RESET << "\n";
                    player.increaseAttack(2);
                    std::cout << GREEN << "  You feel stronger! Attack increased to "
                              << player.getAttack() << "." << RESET << "\n";
                    break;
                }

                // Enemy counter-attacks — 20% chance of dealing double damage
                int dmg = enemy.getAttack();
                if (rand() % 5 == 0) {
                    dmg *= 2;
                    std::cout << BOLD_RED << "  ** Critical hit! **" << RESET << "\n";
                }
                player.takeDamage(dmg);
                std::cout << RED << "  " << enemy.getName() << " attacks!"
                          << " You lose " << dmg << " HP."
                          << " Your HP: " << player.getHealth() << RESET << "\n";

            } else if (choice == 2) {
                std::cout << "  You fled from the " << enemy.getName() << "!\n";
                break;
            } else {
                std::cout << "  Invalid input. Enter 1 to Attack or 2 to Run.\n";
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
            const std::string& name = found.getName();

            std::cout << ">> You found: " << name
                      << " (Value: " << found.getValue() << ")\n";
            inventory.insertItem(found);

            if (name == "Potion") {
                player.heal(15);
                std::cout << GREEN << ">> You used Potion! +15 HP"
                          << " (HP: " << player.getHealth() << ")" << RESET << "\n";
            } else if (name == "Sword") {
                player.increaseAttack(5);
                std::cout << GREEN << ">> Attack increased!"
                          << " (ATK: " << player.getAttack() << ")" << RESET << "\n";
            } else if (name == "Axe") {
                player.increaseAttack(8);
                std::cout << GREEN << ">> Axe equipped! Attack increased!"
                          << " (ATK: " << player.getAttack() << ")" << RESET << "\n";
            } else {
                std::cout << GREEN << ">> You pocket the " << name << "." << RESET << "\n";
            }
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
