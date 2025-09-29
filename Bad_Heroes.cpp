#ifndef BAD_HEROES_CPP
#define BAD_HEROES_CPP
#include <iostream>
#include "Entity.cpp"

// different classes that inherit Entity
// Entity constructor gets and Enum and sets the values for the different units

class Lich : Entity
{
public:
    Lich() : Entity(LICH) {};

    // Lich can revive an entity with the same faction
    void LichRevive(Entity *target)
    {
        if (target->get_is_alive() == false)
        {
            revive(target);
            set_mana(get_mana() - Spells::LICH_RAISEDEAD);
            std::cout << "Revived " << target->get_type() << " with " << 0.3 * target->get_maxHP() << " Hp" << std::endl;
            std::cout << '\n'
                      << "========================================================================================" << '\n';
            decrementDeadBody();
        }
    }
};

// can summon Necroes and Ghouls
class DreadLord : Entity
{
public:
    DreadLord() : Entity(DREAD_LORD) {};
};

// 25% chance to be spawned from death of Knight
class DeathKnight : Entity
{
public:
    DeathKnight() : Entity(DEAD_KNIGHT) {};

    // heals a target of same faction as him
    void Heal(Entity *target) override
    {

        if (target->get_faction() == BAD)
        {
            if (get_mana() >= Spells::DEATHKNIGHT_HEAL)
            {

                float healing = HealValue::DEATHKNIGHT_HEAL;
                healingDone(target, healing);
                set_mana(get_mana() - Spells::DEATHKNIGHT_HEAL);
                std::cout << target->get_type() << " healed for: " << healing << "\n"
                          << "Health after heal: " << target->get_health() << '\n';
                std::cout << '\n'
                          << "========================================================================================" << '\n';
            }
            else
            {
                std::cout << "OOM, mana regeneration! \n";

                manaRegen();
                std::cout << '\n'
                          << "========================================================================================" << '\n';
            }
        }
        else
            std::cout << "Can't heal Bad target" << '\n';
    }
};

#endif