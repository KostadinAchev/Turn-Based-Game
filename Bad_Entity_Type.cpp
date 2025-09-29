#ifndef BADENTITY_CPP
#define BADENTITY_CPP
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <array>
#include "Entity.cpp"
#include "Zombie.hpp"

// different classes that inherit Entity
// Entity constructor gets and Enum and sets the values for the different units
class Skeleton : public Entity
{
public:
    // skeletons have a different approach over things they can be raised or not
    // not raised can increment dead bodies and attack if their master is dead because they don't have one

    // raised skeletons have a master and raised status because skeletons can be raised from dead bodies and have necromancers as their masters
    // although they act separately in term of attacking
    // they cannot increment dead bodies and they "die" when the Necromancer (master) dies
    Skeleton(bool is_raised = false, Entity *master = nullptr) : Entity(SKELETON), m_is_raised(is_raised), m_master(master) {};
    bool get_is_raised() { return m_is_raised; }

    // overriden Attack for skeletons so if necromancer is dead to not be able to attack
    void Attack(Entity *target) override
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
    void death() override
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

private:
    Entity *m_master = nullptr;
    bool m_is_raised;
};

// necromancers can create skeletons up to 3 on a round, 50 mana per mob, HAS TO HAVE A DEAD BODY TO CREATE SKELETON
class Necromancer : public Entity
{
private:
    // array for skeletons
    std::array<std::unique_ptr<Skeleton>, 3> skeletons = {nullptr, nullptr, nullptr};

public:
    Necromancer() : Entity(NECROMANCER) {};

    // function to get skeleton from skeletons array
    std::array<std::unique_ptr<Skeleton>, 3> &getSkeletons() { return skeletons; }

    // prints info of the skeletons in the array
    void getSkeletonsInfo()
    {
        for (auto &skeleton : skeletons)
        {
            std::cout << " Type: " << skeleton->get_type() << " | Health " << skeleton->get_health() << " | Armor Type " << skeleton->armorType2str(skeleton->get_armorType()) << " | Armor " << skeleton->get_armorDurability() << " | Damage " << skeleton->get_damage() << " | Cost " << skeleton->get_moneyCost() << " | Mana " << skeleton->get_mana() << " | Mana State " << (skeleton->get_isCaster() ? " True " : " False ") << " | Alive State " << skeleton->get_is_alive() << std::endl;
            std::cout << '\n'
                      << "========================================================================================" << '\n';
        }
    }

    // function to create skeletons and add them to the array
    void createSkeletons()
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
    void death() override
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

    // code that i have written maybe used later idk
    /*
        void commandSkeletonsAttack(Entity *target)
        {
            if (skeletons.empty())
            {
                std::cout << "No skeletons available to attack.\n";
                return;
            }

            if (target == nullptr || !target->get_is_alive())
            {
                std::cout << "Invalid or dead target.\n";
                return;
            }

            std::cout << "Necromancer commands " << skeletons.size() << " skeleton(s) to attack!\n";

            for (const auto &skeleton : skeletons)
            {
                skeleton->Attack(target);
            }
        }

    can be used later
        void attackNecromancerSkeletons(Entity *attacker)
        {
            auto &skeletons = getSkeletons();

            if (skeletons.empty())
            {
                std::cout << "There are no skeletons to attack.\n";
                std::cout << '\n'
                          << "========================================================================================" << '\n';
                return;
            }

            int index = 0;
            std::cout << "Skeleton you want to attack (1-" << skeletons.size() << "): ";
            std::cin >> index;

            index -= 1;

            while (index < 0 || index >= static_cast<int>(skeletons.size()))
            {
                std::cout << "Invalid skeleton. Enter a new one (1-" << skeletons.size() << "): ";
                std::cin >> index;
                index -= 1;
            }

            Skeleton *target = skeletons[index].get();

            if (target->get_is_alive() && attacker->get_is_alive())
            {
                if (attacker->get_damage() <= 0)
                {
                    std::cout << "No Damage Dealt!\n";
                }
                else
                {
                    if (target->get_armorDurability() > 0)
                    {
                        attacker->Damage_Reduction(target);
                    }
                    else
                    {
                        attacker->Damage_NoReduction(target);
                    }

                    attacker->is_alive_check(target);
                }
            }
            else if (!target->get_is_alive())
            {
                std::cout << "Target is already dead!\n";
            }

            skeletonDeath();
        }

        void skeletonDeath()
        {
            auto &skeletonList = getSkeletons();
            std::cout << "Necromancer Skeleton died!" << std::endl;
            std::cout << '\n'
                      << "========================================================================================" << '\n';

            skeletonList.erase(
                std::remove_if(
                    skeletonList.begin(),
                    skeletonList.end(),
                    [](const std::unique_ptr<Skeleton> &skel)
                    {
                        return !skel->get_is_alive();
                    }),
                skeletonList.end());
        }*/
};

class Ghoul : public Entity
{
public:
    Ghoul() : Entity(GHOUL) {};
};

// zombie is a different class that is used here because both Dybbuk and Revenant are a part of zombie they have the same stats but different
class Dybbuk : public Zombie
{
public:
    //    same as zombie but with different type + is caster + mana
    Dybbuk() : Zombie()
    {
        this->set_type("Dybbuk");
        this->set_isCaster(true);
        this->set_mana(300);
    };

    // attack is overriden here because it uses mana to attack if OOM(out of mana) manaRegen() is called
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
};

// as mentioned above for Dybbuk
class Revenant : public Zombie
{
public:
    //    same as zombie but with different health, armor, armorType
    Revenant() : Zombie()
    {
        this->set_type("Revenant");
        this->set_health(600);
        this->set_armorDurability(0);
        this->set_armorType(UNARMORED);
    }
};

// phantoms are entitites that only heal they are used only for that nothing else, after they heal they die, they are a walking untargetable madkit
class Phantom : public Entity
{
public:
    Phantom() : Entity(PHANTOM) {}

    // heal overriden so it heals the target and dies after tha
    void Heal(Entity *target) override
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
};

#endif
