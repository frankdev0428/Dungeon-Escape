#include <iostream>
#include <queue>
#include <utility>
#include <cstdlib>
#include "Room.h"
#include "../utils/Colors.h"
#include "../utils/Helpers.h"

static void pressEnter(bool hasBufferedNewline) {
    if (hasBufferedNewline)
        std::cin.ignore(1000, '\n');
    std::cout << "\n  Press Enter to continue...";
    std::cin.get();
}

Room::Room() {
    type    = EMPTY;
    visited = false;
}

void Room::setType(RoomType t) { type = t; }
RoomType Room::getType()  const { return type; }
bool Room::isVisited()    const { return visited; }
void Room::setVisited(bool v)   { visited = v; }

void Room::triggerEvent(const std::vector<Item>& items, BST& inventory, Player& player) {
    if (visited) return;

    if (type == EMPTY) {
        std::cout << ">> You step into a quiet corridor. Nothing here.\n";

    } else if (type == ENEMY) {
        int difficulty = player.getX() + player.getY();
        int roll = rand() % 3;
        Enemy enemy("Unknown", 0, 0);

        if      (roll == 0) enemy = Enemy("Goblin",   20, 12 + difficulty);
        else if (roll == 1) enemy = Enemy("Orc",      30, 18 + difficulty);
        else                enemy = Enemy("Skeleton", 15, 10 + difficulty);

        std::cout << YELLOW << "  You sense danger nearby..." << RESET << "\n";
        if (difficulty > 0)
            std::cout << YELLOW << "  Enemy looks stronger..." << RESET << "\n";
        std::cout << RED << "** An enemy blocks your path! **" << RESET << "\n";
        std::cout << "   ";
        enemy.displayEnemy();

        const int ENEMY_MAX_HP = enemy.getHealth();
        bool combatInputDone = false;

        while (enemy.isAlive() && player.getHealth() > 0) {
            std::cout << "------------------------------\n";
            std::cout << "  Your HP  : ";
            printBar(player.getHealth(), 100);
            std::cout << "  ATK:" << player.getAttack() << "\n";
            std::cout << "  " << enemy.getName() << " HP: ";
            printBar(enemy.getHealth(), ENEMY_MAX_HP);
            std::cout << "\n";
            std::cout << "  1. Attack   2. Run\n";
            std::cout << "  > ";

            std::string input;
            std::cin >> input;
            combatInputDone = true;

            int choice = 0;
            if (!input.empty()) choice = input[0] - '0';

            if (choice == 1) {
                int dmgDealt = player.getAttack();
                enemy.takeDamage(dmgDealt);
                std::cout << "  You deal " << dmgDealt << " damage.\n";

                if (!enemy.isAlive()) {
                    std::cout << GREEN << "  " << enemy.getName() << " defeated!" << RESET << "\n";
                    player.increaseAttack(2);
                    std::cout << GREEN << "  You feel stronger! ATK -> " << player.getAttack() << RESET << "\n";
                    break;
                }

                int dmg = enemy.getAttack();
                if (rand() % 5 == 0) {
                    dmg *= 2;
                    std::cout << BOLD_RED << "  ** Critical hit! **" << RESET << "\n";
                }
                player.takeDamage(dmg);
                std::cout << RED << "  " << enemy.getName() << " attacks! You lose "
                          << dmg << " HP." << RESET << "\n";

            } else if (choice == 2) {
                std::cout << "  You fled from the " << enemy.getName() << "!\n";
                break;
            } else {
                std::cout << "  Invalid input. Enter 1 to Attack or 2 to Run.\n";
            }
        }

        if (player.getHealth() <= 0)
            std::cout << RED << "  You were defeated by the " << enemy.getName() << "..." << RESET << "\n";

        std::cout << "------------------------------\n";
        pressEnter(combatInputDone);

    } else if (type == ITEM) {
        std::cout << ">> Something glimmers in the corner...\n";

        if (!items.empty()) {
            int index = rand() % (int)items.size();
            const Item& found = items[index];
            const std::string& name = found.getName();

            std::cout << ">> You found: " << name
                      << " (Value: " << found.getValue() << ")\n";
            inventory.insertItem(found);

            if (name == "Potion") {
                player.heal(15);
                std::cout << GREEN << ">> You used Potion! +15 HP (HP: " << player.getHealth() << ")" << RESET << "\n";
            } else if (name == "Sword") {
                player.increaseAttack(5);
                std::cout << GREEN << ">> Attack increased! (ATK: " << player.getAttack() << ")" << RESET << "\n";
            } else if (name == "Axe") {
                player.increaseAttack(8);
                std::cout << GREEN << ">> Axe equipped! (ATK: " << player.getAttack() << ")" << RESET << "\n";
            } else {
                std::cout << GREEN << ">> You pocket the " << name << "." << RESET << "\n";
            }
        } else {
            std::cout << ">> This room once had an item, but it is gone.\n";
        }

        pressEnter(false);
    }

    visited = true;
}

void Room::displayRoomInfo() const {
    if (type == EMPTY)       std::cout << "Empty room\n";
    else if (type == ENEMY)  std::cout << "Enemy room\n";
    else if (type == ITEM)   std::cout << "Item room\n";
}
