#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP
#include <iostream>
#include "Entity.hpp"


class Zombie : public Entity{
public:
//    type || health || maxHP || armorType || armor || goodOrBad || damage || moneyCost || mana || maxMP || minManaSpell || manaBool || isAlive
    Zombie() : Entity("Zombie", 250, 250, UNARMORED, 0, BAD, 15, 300, 0, 0, 0, false, true){};
};

#endif