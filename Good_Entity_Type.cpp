#include <iostream>
#include "Entity.cpp"



class Infantryman :  public Entity{
    public:
//    type || health || maxHP || armorType || armor || goodOrBad || damage || moneyCost || mana || maxMP || minManaSpell || manaBool || isAlive
    Infantryman() : Entity("Infantryman", 420, 420, MEDIUM, 8, GOOD, 7, 250, 0, 0, 0, false, true){};
};

class Archer : public Entity{
    public:
//    type || health || maxHP || armorType || armor || goodOrBad || damage || moneyCost || mana || maxMP || minManaSpell || manaBool || isAlive
    Archer() : Entity("Archer",535, 535, MEDIUM, 3, GOOD, 10, 300, 0, 0, 0, false, true){};
};

class Knight: public Entity {
    public:
//    type || health || maxHP || armorType || armor || goodOrBad || damage || moneyCost || mana || maxMP || minManaSpell || manaBool || isAlive
    Knight() : Entity("Knight",835, 835, HEAVY, 10, GOOD, 45, 700, 0, 0, 0, false, true){};
};

// 100HP to someone for 100MP from healer, both have to be alive
class Healer : public Entity{
    public:
//    type || health || maxHP || armorType || armor || goodOrBad || damage || moneyCost || mana || maxMP || minManaSpell || manaBool || isAlive
    Healer() : Entity("Healer",290, 290, UNARMORED, 0, GOOD, 2 , 150, 200, 200, 100, true, true){};

    void Heal(Entity *target) override
    {
        if(target->get_fraction() == GOOD)
        {
            if(get_mana() >= get_minManaSpell()){

                float healing=100;
                target->set_health(get_health()+ healing);
                target->set_mana(get_mana()-get_minManaSpell());
                std::cout << target->get_type() << " healed for: " << healing << "\n" << "Health after heal: " << target->get_health() << '\n';
                std::cout << '\n'  << "========================================================================================"<< '\n';

            }
            else 
            {
                std::cout << "OOM, mana regeneration! \n";
                
                manaRegen();
            }
        }
        else std::cout << "Can't heal Bad target" << '\n';

    }
};

//spell costs 50 MP
class Mage : public Entity{
    public:
//    type || health || maxHP || armorType || armor || goodOrBad || damage || moneyCost || mana || maxMP || minManaSpell || manaBool || isAlive
    Mage() : Entity("Mage", 325, 325, LEATHER, 3, GOOD, 10, 250, 200, 200, 50, true, true){};
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


int main(){
    

    Knight k;
    
    Healer h;
    k.printInfo();
    h.printInfo();

    while(k.get_is_alive()==true && h.get_is_alive()==true)
    {
        if(h.get_health() < h.get_maxHP()/2)
        {
            h.Heal(&h);
        }
        // h.Attack(&m);
        k.Attack(&h);

        
    }

}
