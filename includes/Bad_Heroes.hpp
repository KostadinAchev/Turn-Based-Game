#ifndef BAD_HEROES_HPP
#define BAD_HEROES_HPP
#include <iostream>
#include "Entity.hpp"

// different classes that inherit Entity
// Entity constructor gets and Enum and sets the values for the different units

class Lich : public Entity
{
public:
    Lich() : Entity(LICH) {};

    // Lich can revive an entity with the same faction
    void LichRevive(Entity *target);
};

// can summon Necroes and Ghouls
class DreadLord : public Entity
{
public:
    DreadLord() : Entity(DREAD_LORD) {};
};

// 25% chance to be spawned from death of Knight
class DeathKnight : public Entity
{
public:
    DeathKnight() : Entity(DEAD_KNIGHT) {};

    // heals a target of same faction as him
    void Heal(Entity *target) override;
};

#endif