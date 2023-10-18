#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include "Weapons.h"

class Character {
public:
    Character(std::string name, int health);
    std::string GetName() const;
    int GetHealth() const;
    int Attack(Character* target);
    void Defend(Weapon* weapon);
    bool IsAlive() const;
    void TakeDamage(int damage);
    bool IsDefendingWithShield() const;
    Weapon& GetCurrentWeapon(); // Add this method
private:
    std::string name;
    int health;
    bool defendingWithShield;
    int defensivePower;
    Weapon* currentWeapon; // Added to store the current weapon
};

#endif
