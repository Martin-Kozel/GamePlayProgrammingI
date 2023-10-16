#include "Character.h"
#include <iostream>
#include <cstdlib>

using namespace std;

Character::Character(std::string name) : name(name) {}

// void Character::Attack(Character* target) {
//     int damage = rand()% attack;
//     target->TakeDamage(damage);
//     cout << name << " attacks " << target->GetName() << " for " << damage << " damage."<<endl;
// }

std::string Character::GetName() const {
    return name;
}

// bool Character::IsAlive() const {
//     return health > 0;
// }

Character::~Character() {}