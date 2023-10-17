#include "Character.h"
#include <iostream>

Character::Character(std::string name) : name(name), health(100) { // Initialize health to 100 or any other value
}

std::string Character::GetName() const {
    return name;
}

int Character::GetHealth() const {
    return health;
}

void Character::SetHealth(int newHealth) {
    health = newHealth;
}

Character::~Character() {
}
