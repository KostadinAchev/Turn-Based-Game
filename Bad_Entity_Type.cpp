#include <iostream>
#include "Entity.hpp"
#include "Zombie.hpp"

// make entity_type to be hpp + declaration of funcs

class Skeleton : public Entity{
    public:
//    type || health || armorType || armor || goodOrBad || damage || moneyCost || mana || manaBool || isAlive

    Skeleton() : Entity("Skeleton", 500, MEDIUM, 8, BAD, 5 , 100, 0, false, true){};
};

class Ghoul : public Entity{
public:
    Ghoul() : Entity("Ghoul", 400, HEAVY, 6, BAD, 12, 250, 0, false, true){};
};

// necromancers can create skeletons up to 3 on a round, 50 per mob, HAS TO HAVE A DEAD BODY FROM OPPOSITE FACTION TO CREATE SKELETON
class Necromancer : public Entity{
public:
    Necromancer() : Entity("Necromancer", 300, UNARMORED, 0, BAD, 4, 400, 200, true, true){};
};

//150 mana per attack
class Dybbuk : public Zombie{
public:
    Dybbuk() : Zombie(){
        this->set_type("Dybbuk");
        this->set_manaBool(true);
        this->set_mana(300);
    };
};

class Revenant : public Zombie{
public:
    Revenant() : Zombie(){
        this->set_health(600);
        this->set_armor(0);
        this->set_armorType(UNARMORED);
    }
};

// dies and heals 250 hp to a BAD type of target
class Phantom : public Entity{
public:
    Phantom() : Entity("Phantom", 0, UNARMORED, 0, BAD, 0, 500, 0, 0, 1){}
};

// int main(){

//     Dybbuk d;
//     Zombie z;
//     Revenant r;

//     r.printInfo();
//     z.printInfo();
//     d.printInfo();
// }