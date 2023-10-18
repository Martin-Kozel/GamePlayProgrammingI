#include "Weapons.h"

Weapon::Weapon(int power, int cooldown) {
    this->power = power;
    this->cooldown = cooldown;
}

int Weapon::GetPower() const {
    return power;
}

int Weapon::GetCooldown() const {
    return cooldown;
}

void Weapon::ApplyCooldown() {
    currentCooldown = cooldown;
}

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
