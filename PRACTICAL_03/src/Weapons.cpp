#include "Weapons.h"

// Constructor for the Weapon class
Weapon::Weapon(int power, int cooldown) {
    this->power = power;      // Set the power of the weapon
    this->cooldown = cooldown;  // Set the cooldown time of the weapon
}

// Get the power of the weapon
int Weapon::GetPower() const {
    return power;
}

// Get the cooldown time of the weapon 
int Weapon::GetCooldown() const {
    return cooldown;
}

// Apply the cooldown to the weapon
void Weapon::ApplyCooldown() {
    currentCooldown = cooldown;  // Set the currentCooldown to the weapon's cooldown value
}

// Calculate the damage inflicted when using this weapon against another weapon
int Weapon::CalculateDamage(const Weapon& otherWeapon) const {
    if (this->power == otherWeapon.power) {
        // Same weapon type, both characters lose 10 HP
        return -10;
    }
    else if (this->power == 15 && otherWeapon.power == 30) {
        // Bat vs. Sword: -30 HP for the character holding the sword
        return -30;
    }
    else if (this->power == 30 && otherWeapon.power == 15) {
        // Sword vs. Bat: +20 HP for the character holding the sword
        return 20;
    }
    else if (this->power == 20 && otherWeapon.power == 30) {
        // Shield vs. Sword: +30 HP for the character holding the shield
        return 30;
    }
    else if (this->power == 30 && otherWeapon.power == 20) {
        // Sword vs. Shield: -30 HP for the character holding the sword
        return -30;
    }
    else if (this->power == 20 && otherWeapon.power == 15) {
        // Shield vs. Bat: +10 HP for the character holding the shield
        return 10;
    }
    else if (this->power == 15 && otherWeapon.power == 20) {
        // Bat vs. Shield: -10 HP for the character holding the shield
        return -10;
    }

    return 0; // Default case, no damage
}
