#include "Bad_Heroes.hpp"

// Lich can revive an entity with the same faction
void Lich::LichRevive(Entity *target)
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

// heals a target of same faction as him
void DeathKnight::Heal(Entity *target)
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
