#include "Good_Heroes.hpp"

// eliminate function only used by this hero, it 1 shots (instant kills) the opposite faction's heroes -> DK, DL, Lich
void UndeadHunter::eliminate(Entity *target)
{
    if ((target->get_type() == "Dead Knight" || target->get_type() == "Dread Lord" || target->get_type() == "Lich") && target->get_is_alive() == true)
    {
        if (get_mana() > Spells::UNDEADHUNTER_ELIMINATE)
        {
            target->death();
            set_mana(get_mana() - Spells::UNDEADHUNTER_ELIMINATE);
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
    {
        std::cout << "Can't eliminate target";
    }
}

// most op hero imo

// revive mechanic that lets the paladin to revive an army unit that has the same faction as him
void Paladin::paladinRevive(Entity *target)
{
    if (target->get_is_alive() == false)
    {
        revive(target);
        set_mana(get_mana() - Spells::PALADIN_REVIVE);
        std::cout << "Revived " << target->get_type() << " with " << 0.3 * target->get_maxHP() << " Hp" << std::endl;
        std::cout << '\n'
                  << "========================================================================================" << '\n';
        decrementDeadBody();
    }
}

// heal that heals a target that is from the same faction as the healer
void Paladin::Heal(Entity *target)
{

    if (target->get_faction() == GOOD)
    {
        if (get_mana() >= Spells::HEALER_HEAL)
        {

            float healing = HealValue::PALADIN_HEAL;
            healingDone(target, healing);
            set_mana(get_mana() - Spells::PALADIN_HEAL);
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
