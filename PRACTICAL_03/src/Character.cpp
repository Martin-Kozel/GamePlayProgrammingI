#include "Character.h"
#include <iostream>

// Constructor for the Character class
Character::Character(std::string name, int health) : name(name), health(health), defendingWithShield(false), defensivePower(0), currentWeapon(nullptr) {}

// Get the character's name
std::string Character::GetName() const {
    return name;
}

// Get the character's current health
int Character::GetHealth() const {
    return health;
}

// Perform an attack on a target character
int Character::Attack(Character* target) {
    // Check if the character can attack based on weapon cooldown and having a weapon
    if (currentWeapon == nullptr || currentWeapon->GetCooldown() > 0) {
        std::cout << GetName() << " is on cooldown or has no weapon and cannot attack." << std::endl;
        return 0; // Return 0 damage if unable to attack
    }

    // Calculate damage and apply it to the target character
    int damage = currentWeapon->CalculateDamage(target->GetCurrentWeapon());
    target->TakeDamage(damage);
    currentWeapon->ApplyCooldown();
    std::cout << GetName() << " attacks " << target->GetName() << " with " << damage << " damage." << std::endl;

    return damage; // Return the calculated damage
}

// Check if the character is currently defending with a shield
bool Character::IsDefendingWithShield() const {
    return defendingWithShield;
}

// Set the character to defend with a specific weapon and display a message
void Character::Defend(Weapon* weapon) {
    defendingWithShield = true;
    defensivePower = weapon->GetPower();
    std::cout << GetName() << " defends with a " << weapon->GetPower() << " defense." << std::endl;
}

// Check if the character is alive (has health remaining)
bool Character::IsAlive() const {
    return health > 0;
}

// Apply damage to the character
void Character::TakeDamage(int damage) {
    if (defendingWithShield) {
        damage -= defensivePower; // Reduce damage based on defensive power
        if (damage < 0) {
            damage = 0;
        }
        defensivePower = 0; // Reset defensive power after defending
    }
    health -= damage; // Reduce health by the calculated damage
    if (health < 0) {
        health = 0; // Ensure health doesn't go below 0
    }
}

// Get the character's current weapon
Weapon& Character::GetCurrentWeapon() {
    if (currentWeapon == nullptr) {
        // In case no weapon has been assigned, return a dummy weapon with zero power
        static Weapon dummyWeapon(0, 0);
        return dummyWeapon;
    }
    return *currentWeapon;
}
