#include <iostream>
#include "Enemy.h"

Enemy::Enemy(std::string name, int health, int attack) {
    this->name   = name;
    this->health = health;
    this->attack = attack;
}

std::string Enemy::getName()   const { return name;   }
int         Enemy::getHealth() const { return health; }
int         Enemy::getAttack() const { return attack; }

// Subtract damage from health, but never let it go negative
void Enemy::takeDamage(int dmg) {
    health -= dmg;
    if (health < 0) health = 0;
}

// Enemy is alive as long as it has health remaining
bool Enemy::isAlive() const {
    return health > 0;
}

void Enemy::displayEnemy() const {
    std::cout << "[Enemy] " << name
              << " | HP: " << health
              << " | ATK: " << attack << "\n";
}
