#include <iostream>
#include "Entity.cpp"
#include "Zombie.hpp"

// make entity_type to be hpp + declaration of funcs

// make max hp and max mp for classes

class Skeleton : public Entity{
    public:
//    type || health || maxHP || armorType || armor || goodOrBad || damage || moneyCost || mana || maxMP || minManaSpell || manaBool || isAlive

    Skeleton() : Entity("Skeleton", 500, 500, MEDIUM, 8, BAD, 5 , 100, 0, 0, 0, false, true){};
};

class Ghoul : public Entity{
public:
//    type || health || maxHP || armorType || armor || goodOrBad || damage || moneyCost || mana || maxMP || minManaSpell || manaBool || isAlive
    Ghoul() : Entity("Ghoul", 400, 400, HEAVY, 6, BAD, 12, 250, 0, 0, 0, false, true){};
};

// necromancers can create skeletons up to 3 on a round, 50 per mob, HAS TO HAVE A DEAD BODY FROM OPPOSITE FACTION TO CREATE SKELETON
class Necromancer : public Entity{
public:
//    type || health || maxHP || armorType || armor || goodOrBad || damage || moneyCost || mana || maxMP || minManaSpell || manaBool || isAlive
    Necromancer() : Entity("Necromancer", 300, 300, UNARMORED, 0, BAD, 4, 400, 200, 200, 50, true, true){};
};

//150 mana per attack
class Dybbuk : public Zombie{
public:
//    type || health || maxHP || armorType || armor || goodOrBad || damage || moneyCost || mana || maxMP || minManaSpell || manaBool || isAlive
//    same as zombie but with different type + manabool + mana
    Dybbuk() : Zombie(){
        this->set_type("Dybbuk");
        this->set_manaBool(true);
        this->set_mana(300);
    };
    void Attack(Entity *target) override {
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
                    if(get_mana() >= get_minManaSpell())
                    {
                        Damage_Reduction(target);
                        set_mana(get_mana()-get_minManaSpell());
                        is_alive_check(target);
                    }
                    else
                    {
                        std::cout << "Not enough mana, 0 damage delt" << '\n' << "Regenerating mana" << '\n';
                        manaRegen();
                        return;
                    }
                }
                else
                {
                    if(get_mana() >= get_minManaSpell())
                    {
                        Damage_NoReduction(target);
                        set_mana(get_mana()-get_minManaSpell());
                        is_alive_check(target);
                    }
                    else
                    {
                        std::cout << "Not enough mana, 0 damage delt."<< '\n' << "Regenerating mana!" << '\n';
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

class Revenant : public Zombie{
public:
//    type || health || maxHP || armorType || armor || goodOrBad || damage || moneyCost || mana || maxMP || minManaSpell || manaBool || isAlive
//    same as zombie but with different health, armor, armorType 
    Revenant() : Zombie(){
        this->set_health(600);
        this->set_armor(0);
        this->set_armorType(UNARMORED);
    }
};

// dies and heals 250 hp to a BAD type of target
class Phantom : public Entity{
public:
//    type || health || maxHP || armorType || armor || goodOrBad || damage || moneyCost || mana || maxMP || minManaSpell || manaBool || isAlive
    Phantom() : Entity("Phantom", 0, 0, UNARMORED, 0, BAD, 0, 500, 0, 0, 0,false, true){}

    
    void Heal(Entity *target) override
    {
        float healing=250;
        if(!(get_type()== "Phantom")){
            if(target->get_fraction() == BAD)
            {
                target->set_health(get_health()+ healing);
                std::cout << target->get_type() << " healed for: " << healing << "\n" << "Health after heal: " << target->get_health() << '\n';
                std::cout << "After healing the Phantom dies!" << '\n';
                std::cout << '\n'  << "========================================================================================"<< '\n';
        
                set_is_alive(false);
            }
            else std::cout << "Can't heal GOOD target";

        }
        else 
        {
            std::cout << "Can't heal entity of type Phantom";
        }
    }
};

// int main(){

//     Dybbuk d;
//     Zombie z;
//     Revenant r;

//     r.printInfo();
//     z.printInfo();
//     d.printInfo();
// }