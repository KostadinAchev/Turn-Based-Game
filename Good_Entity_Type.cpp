#ifndef GOODENTITY_CPP
#define GOODENTITY_CPP
#include <iostream>
#include "Entity.cpp"

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

// 100HP to someone for 100MP from healer, both have to be alive
class Healer : public Entity
{
public:
    Healer() : Entity(HEALER) {};

    void Heal(Entity *target) override
    {

        if (target->get_fraction() == GOOD)
        {
            if (get_mana() >= get_minManaSpell())
            {

                float healing = 100;
                healingDone(target, healing);
                set_mana(get_mana() - get_minManaSpell());
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

// spell costs 50 MP
//  mana 200
class Mage : public Entity
{
public:
    Mage() : Entity(MAGE) {};

    void Attack(Entity *target) override
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
                // has armor
                if (target->get_armorDurability() > 0)
                {
                    if (get_mana() >= get_minManaSpell())
                    {
                        Damage_Reduction(target);
                        set_mana(get_mana() - get_minManaSpell());
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
                    if (get_mana() >= get_minManaSpell())
                    {
                        Damage_NoReduction(target);
                        set_mana(get_mana() - get_minManaSpell());
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
};

// int main(){

//     Knight k;

//     Healer h;
//     k.printInfo();
//     h.printInfo();

//     while(k.get_is_alive()==true && h.get_is_alive()==true)
//     {
//         if(h.get_health() < h.get_maxHP()/2)
//         {
//             h.Heal(&h);
//         }
//         // h.Attack(&m);
//         k.Attack(&h);

//     }

// }

#endif