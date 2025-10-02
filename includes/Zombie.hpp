#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP
#include <iostream>
#include "Entity.hpp"

// different classes that inherit Entity
// Entity constructor gets and Enum and sets the values for the different units

// type of Entity that can be bought and it has different subclasses
class Zombie : public Entity
{
public:
    //    type || health || maxHP || armorType || armor || goodOrBad || damage || moneyCost || mana || maxMP || minManaSpell || manaBool || isAlive
    Zombie() : Entity(ZOMBIE) {};
};

#endif