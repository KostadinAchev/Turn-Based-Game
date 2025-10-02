#include <iostream>
#include "Good_Entity_Type.hpp"

// different classes that inherit Entity
// Entity constructor gets and Enum and sets the values for the different units

// overriden heal function
void Healer::Heal(Entity *target)
{

    if (target->get_faction() == GOOD)
    {
        if (get_mana() >= Spells::HEALER_HEAL)
        {

            float healing = HealValue::HEALER_HEAL;
            healingDone(target, healing);
            set_mana(get_mana() - Spells::HEALER_HEAL);
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

// overriden attack for mage because it uses mana to attack if he doesnt have mana it regens and skips its turn either way it deals damage
void Mage::Attack(Entity *target)
{
    float reduction = 0;
    float healthAfterDmg = 0;
    if (target->get_is_alive() == true && get_is_alive() == true)
    {
        is_alive_check(target);

        if (get_damage() <= 0)
        {
            std::cout << "No Damage Delt!" << std::endl;
        }

        else
        {
            if (target->get_armorDurability() > 0)
            {
                if (get_mana() >= Spells::MAGE_ATTACK)
                {
                    Damage_Reduction(target);
                    set_mana(get_mana() - Spells::MAGE_ATTACK);
                    is_alive_check(target);
                }
                else
                {
                    std::cout << "Not enough mana, 0 damage delt" << '\n'
                              << "Regenerating mana" << '\n';
                    manaRegen();
                    return;
                }
            }
            else
            {
                if (get_mana() >= Spells::MAGE_ATTACK)
                {
                    Damage_NoReduction(target);
                    set_mana(get_mana() - Spells::MAGE_ATTACK);
                    is_alive_check(target);
                }
                else
                {
                    std::cout << "Not enough mana, 0 damage delt." << '\n'
                              << "Regenerating mana!" << '\n';
                    manaRegen();
                    return;
                }
            }
        }
    }
    else if (target->get_is_alive() == false)
    {
        target->death();
    }
}
