#ifndef ENTITY_CPP
#define ENTITY_CPP
#include "Entity.hpp"

#define MANA_PER_TURN 75

// deadBodyCount for keeping track of dead bodies on the battlefield
int Entity::deadBodyCount = 0;

// damage reduction function uses the armor type of the targetet entity and applies protection to them
void Entity::Damage_Reduction(Entity *target)
{
    // armorDurability is how many hits the target has with the armor protection
    // reduction ammount 100 being the max damage reduction as % - armor type(heavy = 75) / 100 for %
    float reduction = (100 - target->get_armorType()) / 100.0f;
    float healthAfterDmg = target->get_health() - (get_damage() * reduction);
    target->set_health(healthAfterDmg);
    std::cout << get_type() << " Delt: " << get_damage() << " damage to: " << target->get_type() << '\n'
              << target->get_type() << "'s Health remaining is: " << target->get_health() << '\n'
              << get_type() << " mana remaining: " << get_mana() << '\n';
    target->set_armorDurability(target->get_armorDurability() - 1);
    std::cout << '\n'
              << "========================================================================================" << '\n';
}

// damage function with no reduction meaning it's being used after armorDurability = 0
void Entity::Damage_NoReduction(Entity *target)
{
    float healthAfterDmg = target->get_health() - get_damage();
    target->set_health(healthAfterDmg);
    std::cout << get_type() << " Delt: " << get_damage() << " damage to: " << target->get_type() << '\n'
              << target->get_type() << "'s Health remaining is: " << target->get_health() << '\n'
              << get_type() << " mana remaining: " << get_mana() << '\n';
    std::cout << '\n'
              << "========================================================================================" << '\n';
}

// checks if the target is alive
void Entity::is_alive_check(Entity *target)
{
    if (target->get_health() <= 0)
    {
        target->set_is_alive(false);
    }
}

// regenerates mana after every turn
void Entity::manaRegen()
{
    set_mana(get_mana() + MANA_PER_TURN);
    std::cout << "Mana after regeneration: " << get_mana() << '\n';
}

// after the death of an entity it's health gets set to 0 and it's is_alive state to false
void Entity::death()
{
    if (!get_is_alive())
        return;

    set_health(0);
    set_is_alive(false);
    std::cout << get_type() << " died" << std::endl;
    Entity::incrementDeadBody();
}

// main attack function it uses other function mentioned above
void Entity::Attack(Entity *target)
{
    if (target->get_is_alive() != true || get_is_alive() != true)
    {
        std::cout << " Attacker : " << get_type() << " || " << " Target is: " << (target->get_is_alive() ? "Alive" : "Dead") << " Attacker is : " << (get_is_alive() ? "Alive" : "Dead") << std::endl
                  << "========================================================================================" << '\n';
        return;
    }
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
                // damage reduction func
                Damage_Reduction(target);
            }
            else
            {
                // damage with no reduction
                Damage_NoReduction(target);
                // is alive check
            }
            is_alive_check(target);
        }
    }
    else if (target->get_health() <= 0)
    {
        if (target->get_is_alive() == false)
        {
            std::cout << "Target is already dead!" << std::endl;
            return;
        }
        else
        {
            target->set_is_alive(false);
            target->death();
        }
    }
}

// prints the info of the Entity
void Entity::printInfo()
{

    std::cout << " Type: " << get_type() << " | Health " << get_health() << " | Armor Type " << armorType2str(get_armorType()) << " | Armor " << get_armorDurability() << " | Damage " << get_damage() << " | Cost " << get_moneyCost() << " | Mana " << get_mana() << " | Mana State " << (get_isCaster() ? " True " : " False ") << " | Alive State " << get_is_alive() << std::endl;
    std::cout << '\n'
              << "========================================================================================" << '\n';
}

// stays virtual because there are 3 different healers which override it because I can't seem to find common logic between them, I am dumb
void Entity::Heal(Entity *target) {};

// used as a helper function for Heal because it can't access set methods outside the Entity class when we use class inheritance
void Entity::healingDone(Entity *target, float healing)
{
    if ((target->get_health() + healing) > target->get_maxHP())
    {
        target->set_health(get_maxHP());
    }
    else
        target->set_health(get_health() + healing);
}

// used for reviving dead entities
void Entity::revive(Entity *target)
{
    if (target->get_is_alive() == false && target->get_faction() == get_faction())
    {
        target->set_health(0.3 * target->get_maxHP());
    }
    else
    {
        std::cout << "Can't revive target from different fraction";
    }
}

#endif