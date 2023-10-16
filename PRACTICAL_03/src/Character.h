#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>

class Character {

public:
    Character(std::string name);
    std::string GetName() const;
    virtual ~Character();

private:
    std::string name;
};

#endif
