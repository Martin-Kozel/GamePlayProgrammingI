#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>

class Character {
public:
    Character(std::string name);

    int batPower;
    int swordPower;
    int shieldPower;
    int batCooldown;
    int swordCooldown;
    int shieldCooldown;

    int GetHealth() const; // Add a method to retrieve health
    void SetHealth(int health); // Add a method to set health
    std::string GetName() const;
    virtual ~Character();

private:
    std::string name;
    int health;
};

#endif
