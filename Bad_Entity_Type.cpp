#ifndef BADENTITY_CPP
#define BADENTITY_CPP
#include <iostream>
#include <vector>
#include <memory>
#include "Entity.cpp"
#include "Zombie.hpp"

// make entity_type to be hpp + declaration of funcs

// make max hp and max mp for classes

class Skeleton : public Entity
{
public:
    Skeleton() : Entity(SKELETON) {};
};

// necromancers can create skeletons up to 3 on a round, 50 per mob, HAS TO HAVE A DEAD BODY FROM OPPOSITE FACTION TO CREATE SKELETON
class Necromancer : public Entity
{
public:
    Necromancer() : Entity(NECROMANCER) {};
    std::vector<std::unique_ptr<Skeleton>> skeletons;

    void createSkeletons()
    {
        int number = 0;
        if (Entity::getDeadBodyCount() > 0)
        {
            std::cout << "How many skeletons do you wish to summon (1-3)" << '\n'
                      << "Number: ";
            std::cin >> number;

            while (Entity::getDeadBodyCount() < number || (number < 1 || number > 3))
            {
                std::cout << "Invalid number please enter a new one!" << '\n'
                          << "Number: ";
                std::cin >> number;
            }
            for (int i = 0; i < number; i++)
            {
                std::cout << number << " Skeleton/s have risen" << '\n';
                skeletons.push_back(std::make_unique<Skeleton>());
                Entity::decrementDeadBody();
                set_mana(get_mana() - 50);
            }
        }
        if (Entity::getDeadBodyCount() < 0)
        {
            Entity::deadBodyCount = 0;
        }
    }
};

class Ghoul : public Entity
{
public:
    Ghoul() : Entity(GHOUL) {};
};

// 150 mana per attack
// 300 mana
class Dybbuk : public Zombie
{
public:
    //    same as zombie but with different type + manabool + mana
    Dybbuk() : Zombie()
    {
        this->set_type("Dybbuk");
        this->set_isCaster(true);
        this->set_mana(300);
    };
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

class Revenant : public Zombie
{
public:
    //    type || health || maxHP || armorType || armor || goodOrBad || damage || moneyCost || mana || maxMP || minManaSpell || manaBool || isAlive
    //    same as zombie but with different health, armor, armorType
    Revenant() : Zombie()
    {
        this->set_type("Revenant");
        this->set_health(600);
        this->set_armorDurability(0);
        this->set_armorType(UNARMORED);
    }
};

// dies and heals 250 hp to a BAD type of target
class Phantom : public Entity
{
public:
    //    type || health || maxHP || armorType || armor || goodOrBad || damage || moneyCost || mana || maxMP || minManaSpell || manaBool || isAlive
    Phantom() : Entity(PHANTOM) {}

    void Heal(Entity *target) override
    {
        float healing = 250;
        if (!(get_type() == "Phantom"))
        {
            if (target->get_fraction() == BAD)
            {
                healingDone(target, healing);
                std::cout << target->get_type() << " healed for: " << healing << "\n"
                          << "Health after heal: " << target->get_health() << '\n';
                std::cout << "After healing the Phantom dies!" << '\n';
                std::cout << '\n'
                          << "========================================================================================" << '\n';

                set_is_alive(false);
            }
            else
                std::cout << "Can't heal GOOD target";
        }
        else
        {
            std::cout << "Can't heal entity of type Phantom";
        }
    }
};

#endif
