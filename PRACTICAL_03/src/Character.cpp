#include "Character.h"
#include <iostream>

Character::Character(std::string name, int health) : name(name), health(health), defendingWithShield(false), defensivePower(0), currentWeapon(nullptr) {}

std::string Character::GetName() const {
    return name;
}

int Character::GetHealth() const {
    return health;
}

int Character::Attack(Character* target) {
    if (currentWeapon == nullptr || currentWeapon->GetCooldown() > 0) {
        std::cout << GetName() << " is on cooldown or has no weapon and cannot attack." << std::endl;
        return 0;
    }

    int damage = currentWeapon->CalculateDamage(target->GetCurrentWeapon());
    target->TakeDamage(damage);
    currentWeapon->ApplyCooldown();
    std::cout << GetName() << " attacks " << target->GetName() << " with " << damage << " damage." << std::endl;

    return damage;
}

bool Character::IsDefendingWithShield() const {
    return defendingWithShield;
}

void Character::Defend(Weapon* weapon) {
    defendingWithShield = true;
    defensivePower = weapon->GetPower();
    std::cout << GetName() << " defends with a " << weapon->GetPower() << " defense." << std::endl;
}

bool Character::IsAlive() const {
    return health > 0;
}

void Character::TakeDamage(int damage) {
    if (defendingWithShield) {
        damage -= defensivePower;
        if (damage < 0) {
            damage = 0;
        }
        defensivePower = 0;
    }
    health -= damage;
    if (health < 0) {
        health = 0;
    }
}

Weapon& Character::GetCurrentWeapon() {
    if (currentWeapon == nullptr) {
        // In case no weapon has been assigned, return a dummy weapon with zero power
        static Weapon dummyWeapon(0, 0);
        return dummyWeapon;
    }
    return *currentWeapon;
}
