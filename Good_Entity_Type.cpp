#include <iostream>
#include "Entity.hpp"



class Infantryman :  public Entity{
    public:
    
//    type || health || armorType || armor || goodOrBad || damage || moneyCost || mana || manaBool || isAlive
    Infantryman() : Entity("Infantryman",420, MEDIUM, 8, GOOD, 7, 250, 0, 0, false, true){};
};

class Archer : public Entity{
    public:
//    type || health || armorType || armor || goodOrBad || damage || moneyCost || mana || manaBool || isAlive
    Archer() : Entity("Archer",535, MEDIUM, 3, GOOD, 10, 300, 0, 0, false, true){};
};

class Knight: public Entity {
    public:
//    type || health || armorType || armor || goodOrBad || damage || moneyCost || mana || manaBool || minManaAttack || isAlive
    Knight() : Entity("Knight",835, HEAVY, 10, GOOD, 45, 700, 0, 0, false, true){};
};

// 100HP to someone for 100MP from healer, both have to be alive
class Healer : public Entity{
    public:
//    type || health || armorType || armor || goodOrBad || damage || moneyCost || mana || manaBool || minManaSpell || isAlive
    Healer() : Entity("Healer",290, UNARMORED, 0, GOOD, 2 , 150, 200, 100, true, true){};

    void Heal(Entity e){
        if(Healer::get_mana() >= 100)
        {
            float healingDone = e.get_health() + 100;
            Healer::set_mana(Healer::get_mana()-100);
        }
        else std::cout << "Can't heal oom";
    }

};

//spell costs 50 MP
class Mage : public Entity{
    public:
//    type || health || armorType || armor || goodOrBad || damage || moneyCost || mana || manaBool || minManaSpell || isAlive
    Mage() : Entity("Mage",325,LEATHER,3,GOOD,10,250, 200, 50, true, true){};
};


// int main(){
    

//     Mage m;
    
//     Healer h;
//     m.printInfo();
//     h.printInfo();

//     while(m.get_is_alive()==true && h.get_is_alive()==true)
//     {
//         if(h.get_health() !=0)
//         h.Attack(&m);
//         m.Attack(&h);
        
//     }

// }
