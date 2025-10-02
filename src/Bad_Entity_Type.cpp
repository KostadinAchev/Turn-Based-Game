#include "Bad_Entity_Type.hpp"
#include "Zombie.hpp"

// different classes that inherit Entity
// Entity constructor gets and Enum and sets the values for the different units

// skeletons have a different approach over things they can be raised or not
// not raised can increment dead bodies and attack if their master is dead because they don't have one

// raised skeletons have a master and raised status because skeletons can be raised from dead bodies and have necromancers as their masters
// although they act separately in term of attacking
// they cannot increment dead bodies and they "die" when the Necromancer (master) dies

// overriden Attack for skeletons so if necromancer is dead to not be able to attack
void Skeleton::Attack(Entity *target)
{
    if (m_is_raised && (!m_master || !m_master->get_is_alive()))
    {
        std::cout << get_type() << " refuses to attack. Master is dead.\n"
                  << "========================================================================================" << '\n';
        return;
    }

    Entity::Attack(target);
}

// death is overriden too because if the skeleton is reised it can increment the deadbody counter otherwise no
void Skeleton::death()
{
    if (!get_is_alive())
        return;

    set_health(0);
    set_is_alive(false);
    std::cout << get_type() << " died" << std::endl;
    if (get_is_raised() == false)
    {
        Entity::incrementDeadBody();
    }
}

// necromancers can create skeletons up to 3 on a round, 50 mana per mob, HAS TO HAVE A DEAD BODY TO CREATE SKELETON

// function to create skeletons and add them to the array
void Necromancer::createSkeletons()
{
    int number = 0;
    if (Entity::getDeadBodyCount() > 0)
    {
        if (Spells::NECROMANCER_RAISESKELETON <= get_mana())
        {
            std::cout << "How many skeletons do you wish to summon (1-3)" << '\n'
                      << "Number: ";
            std::cin >> number;

            while (number * Spells::NECROMANCER_RAISESKELETON > get_mana())
            {
                std::cout << "Not enough mana for " << number << " of skeletons!" << '\n'
                          << "Number: ";
                std::cin >> number;
            }
            while (Entity::getDeadBodyCount() < number || (number < 1 || number > 3))
            {
                std::cout << "Invalid number please enter a new one!" << '\n'
                          << "Number: ";
                std::cin >> number;
            }
            for (int i = 0; i < number; i++)
            {
                // this means that the skeletons that are being created are set to raised = true, *master = this
                skeletons[i] = (std::make_unique<Skeleton>(true, this));

                Entity::decrementDeadBody();
                set_mana(get_mana() - 50);
            }

            std::cout << number << " Skeleton/s have risen" << '\n';
        }
        else
        {
            std::cout << "OOM, mana regeneration! \n";

            manaRegen();
            std::cout << '\n'
                      << "========================================================================================" << '\n';
        }
    }
    if (Entity::getDeadBodyCount() < 0)
    {
        Entity::deadBodyCount = 0;
    }
}

// when death is called for the necromancer to be made that skeletons in the array are freed using .reset because they are unique_ptrs
void Necromancer::death()
{
    if (!get_is_alive())
        return;

    set_health(0);
    set_is_alive(false);
    std::cout << get_type() << " died" << std::endl;
    Entity::incrementDeadBody();

    for (auto &skel : skeletons)
    {
        skel->death();
        skel.reset();
    }
}

// attack is overriden here because it uses mana to attack if OOM(out of mana) manaRegen() is called
void Dybbuk::Attack(Entity *target)
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
                if (get_mana() >= Spells::DYBBUK_ATTACK)
                {
                    Damage_Reduction(target);
                    set_mana(get_mana() - Spells::DYBBUK_ATTACK);
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
                if (get_mana() >= Spells::DYBBUK_ATTACK)
                {
                    Damage_NoReduction(target);
                    set_mana(get_mana() - Spells::DYBBUK_ATTACK);
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

// heal overriden so it heals the target and dies after tha
void Phantom::Heal(Entity *target)
{
    float healing = HealValue::PHANTOM_HEAL;
    if (!(get_type() == "Phantom"))
    {
        if (target->get_faction() == BAD)
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
