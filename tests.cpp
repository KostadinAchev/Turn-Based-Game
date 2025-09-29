#include <iostream>
#include "Bad_Entity_Type.cpp"
#include "Good_Entity_Type.cpp"
#include "Good_Heroes.cpp"
#include "game_Ui.cpp"

void NecroSkeletons()
{

    Paladin p;
    Knight k1;
    Knight k2;
    Necromancer n;

    std::vector<Entity *> dead;
    std::vector<Entity *> turn;

    turn.push_back(&p);
    turn.push_back(&k1);
    turn.push_back(&k2);
    turn.push_back(&n);

    k1.death();
    k2.death();

    n.createSkeletons();

    for (auto &skeleton : n.getSkeletons())
    {
        if (skeleton.get() != nullptr)
        {
            turn.push_back(skeleton.get());
        }
    }

    for (auto &entity : turn)
    {
        entity->printInfo();
    }

    for (auto &entity : turn)
    {
        if (entity->get_is_alive() == false)
        {
            dead.push_back(entity);
        }
        if (entity->get_faction() == Entity::goodOrBad::GOOD)
        {
            entity->Attack(&n);
        }
        else
        {
            entity->Attack(&p);
        }

        for (auto &entity : turn)
        {
            entity->printInfo();
        }
    }
}

void game_Ui()
{
    Paladin p;
    print_Ui(&p);
}