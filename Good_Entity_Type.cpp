#include <iostream>
#include "Entity.hpp"

class Infantryman :  public Entity{
    public:
    Infantryman() : Entity("Infantryman",420, MEDIUM, 8, GOOD, 7, 250, false, true){};
    private:  
};

class Archer : public Entity{
    public:
    Archer() : Entity("Archer",535, MEDIUM, 3, GOOD, 10, 300, false, true){};
};

class Knight: public Entity {
    public:
    Knight() : Entity("Knight",835, HEAVY, 10, GOOD, 45, 700, false, true){};
};

class Healer : public Entity{
    public:
    Healer() : Entity("Healer",290, UNARMORED, 0, GOOD, 2 , 150, true, true){
        this->m_mana = 200;
};
private:
int m_mana;
};

class Mage : public Entity{
    public:
    Mage() : Entity("Mage",325,LEATHER,3,GOOD,10,250, true, true)
    {
        this->m_mana = 200;
    }
    private:
    int m_mana;
};


int main(){
    

    Mage m;
    
    Healer h;
    while(m.get_alive()==true && h.get_alive()==true)
    {
        if(h.get_health() !=0)
        h.Attack(&h,&m);
        m.Attack(&m,&h);
        
    }

}
