#ifndef WEAPONS_H
#define WEAPONS_H

class Weapon {
public:
    Weapon(int power, int cooldown);
    int GetPower() const;
    int GetCooldown() const;
    void ApplyCooldown();
    bool IsOnCooldown() const;
    int CalculateDamage(const Weapon& otherWeapon) const; // Added method
private:
    int power;
    int cooldown;
    int currentCooldown;
    int cooldownCounter;
};

#endif