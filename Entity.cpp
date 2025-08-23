#include "Entity.hpp"
 
void Entity::Damage_Reduction(Entity *target){
        float reduction = (100 - target->get_armorType()) / 100.0f;
        float healthAfterDmg = target->get_health() - (get_damage() * reduction);
        target->set_health(healthAfterDmg);                   
        std::cout << get_type() << " Delt: " << get_damage() << " damage to: " << target->get_type() << '\n' << target->get_type() << "'s Health remaining is: "<< target->get_health() << '\n' << get_type() <<" mana remaining: "<< get_mana() <<'\n';
        target->set_armor(target->get_armor() - 1);
        std::cout << '\n' << "========================================================================================"<< '\n';
}

void Entity::Damage_NoReduction(Entity *target)
{
    float healthAfterDmg = target->get_health() - get_damage();
    target->set_health(healthAfterDmg);
    std::cout << get_type() << " Delt: " << get_damage() << " damage to: " << target->get_type() << '\n' << target->get_type() << "'s Health remaining is: "<< target->get_health() << '\n' << get_type() <<" mana remaining: "<< get_mana() <<'\n';
    std::cout << '\n' << "========================================================================================"<< '\n';
}

void is_alive_check(Entity *target)
{
    if (target->get_health() <= 0)
    {
    target->set_is_alive(false);
    }
}
// Done but idk if logic is good may need further improvements
void Entity::manaRegen(){
    
    int manaPerTurn = 75;
    set_mana(get_mana() + manaPerTurn);
    std::cout << "Mana after regeneration: "<<get_mana() << '\n';
}

void Entity::death()
{
        set_health(0);
        std::cout << get_type() << " died" << std::endl;
}

void Entity::Attack(Entity *target)
    {
        float reduction =0;
        float healthAfterDmg=0;
        if (target->get_is_alive() == true && get_is_alive() == true)
        {
            is_alive_check(target);
            
            if (get_damage() <= 0)
            {
                std::cout << "No Damage Delt!" << std::endl;
            }

            else
            {
                //has armor 
                if(target->get_armor() > 0)
                {
                    //damage reduction func
                    Damage_Reduction(target);
                    is_alive_check(target); 
                }
                else
                {
                    //damage with no reduction
                    Damage_NoReduction(target);
                    //is alive check
                    is_alive_check(target);
                
                }

            }
        }
        else if (target->get_is_alive() == false)
        {
            target->death();
        }
    }

void Entity::printInfo(){
    
    std::cout << " Type: " << get_type() << " | Health " << get_health() << " | Armor Type " << getArmorType(get_armorType())  << " | Armor " << get_armor() << " | Damage " << get_damage() << " | Cost " << get_moneyCost() << " | Mana " << get_mana() << " | Mana State " << (get_manaBool()? " True " : " False ") << " | Alive State " << get_is_alive() << std::endl;
    std::cout << '\n' << "========================================================================================"<< '\n';
    
}
    

void Entity::Heal(Entity *target)
{
    float healing=0;
    target->set_health(get_health()+ healing);
    target->set_mana(get_mana()- get_minManaSpell());
}