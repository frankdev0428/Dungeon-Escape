#ifndef ENEMY_H
#define ENEMY_H

#include <string>

class Enemy {
public:
    // Build an enemy with a name, health pool, and attack power
    Enemy(const std::string& name, int health, int attack);

    std::string getName()   const;
    int         getHealth() const;
    int         getAttack() const;

    // Reduce health by dmg — health never drops below 0
    void takeDamage(int dmg);

    // Returns true as long as health > 0
    bool isAlive() const;

    // Print a one-line summary of this enemy's current state
    void displayEnemy() const;

private:
    std::string name;
    int health;
    int attack;
};

#endif
