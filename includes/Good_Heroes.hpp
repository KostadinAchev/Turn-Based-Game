#ifndef GOOD_HEROES_HPP
#define GOOD_HEROES_HPP
#include <iostream>
#include "Entity.hpp"

// Good heroes
// different classes that inherit Entity
// Entity constructor gets and Enum and sets the values for the different units

class UndeadHunter : public Entity
{
public:
    UndeadHunter() : Entity(UNDEAD_HUNTER) {};

    // eliminate function only used by this hero, it 1 shots (instant kills) the opposite faction's heroes -> DK, DL, Lich
    void eliminate(Entity *target);
};

// just a blade dancer boring hero
class BladeDancer : public Entity
{
public:
    BladeDancer() : Entity(BLADE_DANCER) {};
};

// most op hero imo
class Paladin : public Entity
{
public:
    Paladin() : Entity(PALADIN) {};

    // revive mechanic that lets the paladin to revive an army unit that has the same faction as him
    void paladinRevive(Entity *target);

    // heal that heals a target that is from the same faction as the healer
    void Heal(Entity *target) override;
};

#endif