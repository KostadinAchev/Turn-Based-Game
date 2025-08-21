#include <iostream>
#include "Entity.hpp"



class Infantryman :  public Entity{
    public:
    
//    type || health || armorType || armor || goodOrBad || damage || moneyCost || mana || manaBool || isAlive
    Infantryman() : Entity("Infantryman",420, MEDIUM, 8, GOOD, 7, 250, 0, false, true){};
};

class Archer : public Entity{
    public:
    Archer() : Entity("Archer",535, MEDIUM, 3, GOOD, 10, 300, 0, false, true){};
};

class Knight: public Entity {
    public:
    Knight() : Entity("Knight",835, HEAVY, 10, GOOD, 45, 700, 0, false, true){};
};

// 100HP to someone for 100MP from healer, both have to be alive
class Healer : public Entity{
    public:
    Healer() : Entity("Healer",290, UNARMORED, 0, GOOD, 2 , 150, 200, true, true){};
};

//spell costs 50 MP
class Mage : public Entity{
    public:
    Mage() : Entity("Mage",325,LEATHER,3,GOOD,10,250, 200, true, true){};
};


int main(){
    

    Mage m;
    
    Healer h;
    m.printInfo();
    h.printInfo();

    while(m.get_is_alive()==true && h.get_is_alive()==true)
    {
        if(h.get_health() !=0)
        h.Attack(&h,&m);
        m.Attack(&m,&h);
        
    }

}
