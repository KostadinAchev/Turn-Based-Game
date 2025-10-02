#ifndef GOOD_ENTITY_TYPE_HPP
#define GOOD_ENTITY_TYPE_HPP
#include <iostream>
#include "Entity.hpp"

class Infantryman : public Entity
{
public:
    Infantryman() : Entity(INFANTRYMAN) {};
};

class Archer : public Entity
{
public:
    Archer() : Entity(ARCHER) {};
};

class Knight : public Entity
{
public:
    Knight() : Entity(KNIGHT) {};
};

class Healer : public Entity
{
public:
    Healer() : Entity(HEALER) {};

    // overriden heal function
    void Heal(Entity *target) override;
};

class Mage : public Entity
{
public:
    Mage() : Entity(MAGE) {};

    // overriden attack for mage because it uses mana to attack if he doesnt have mana it regens and skips its turn either way it deals damage
    void Attack(Entity *target) override;
};

#endif