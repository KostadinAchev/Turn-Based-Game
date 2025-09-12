#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP
#include <iostream>
#include "Entity.hpp"


class Zombie : public Entity{
public:
//    type || health || maxHP || armorType || armor || goodOrBad || damage || moneyCost || mana || maxMP || minManaSpell || manaBool || isAlive
    Zombie() : Entity(ZOMBIE){};
};

#endif