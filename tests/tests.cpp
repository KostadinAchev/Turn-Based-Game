#include <memory>
#include <iostream>
#include "Bad_Entity_Type.hpp"
#include "Good_Entity_Type.hpp"
#include "Good_Heroes.hpp"
#include "Bad_Heroes.hpp"
#include "game_Ui.cpp"

void NecroSkeletons()
{

    auto p = std::make_unique<Paladin>();
    auto k1 = std::make_unique<Knight>();
    auto k2 = std::make_unique<Knight>();
    auto n = std::make_unique<Necromancer>();

    std::vector<Entity *> dead;
    std::vector<Entity *> turn;

    turn.push_back(p.get());
    turn.push_back(k1.get());
    turn.push_back(k2.get());
    turn.push_back(n.get());

    k1->death();
    k2->death();

    n->createSkeletons();

    for (auto &skeleton : n->getSkeletons())
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
            entity->Attack(n.get());
        }
        else
        {
            entity->Attack(p.get());
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