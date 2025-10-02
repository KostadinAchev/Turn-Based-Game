#ifndef BADENTITY_TYPE_HPP
#define BADENTITY_TYPE_HPP
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <array>
#include "Entity.hpp"
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
    inline bool get_is_raised() { return m_is_raised; }

    // overriden Attack for skeletons so if necromancer is dead to not be able to attack
    void Attack(Entity *target) override;

    // death is overriden too because if the skeleton is reised it can increment the deadbody counter otherwise no
    void death() override;

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
    inline void getSkeletonsInfo()
    {
        for (auto &skeleton : skeletons)
        {
            std::cout << " Type: " << skeleton->get_type() << " | Health " << skeleton->get_health() << " | Armor Type " << skeleton->armorType2str(skeleton->get_armorType()) << " | Armor " << skeleton->get_armorDurability() << " | Damage " << skeleton->get_damage() << " | Cost " << skeleton->get_moneyCost() << " | Mana " << skeleton->get_mana() << " | Mana State " << (skeleton->get_isCaster() ? " True " : " False ") << " | Alive State " << skeleton->get_is_alive() << std::endl;
            std::cout << '\n'
                      << "========================================================================================" << '\n';
        }
    }

    // function to create skeletons and add them to the array
    void createSkeletons();

    // when death is called for the necromancer to be made that skeletons in the array are freed using .reset because they are unique_ptrs
    void death() override;
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
    void Attack(Entity *target) override;
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
    void Heal(Entity *target) override;
};

#endif
