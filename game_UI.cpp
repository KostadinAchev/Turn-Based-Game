#include <iostream>
#include "Entity.hpp"

void choice_Ui()
{
    int choice;
    std::cout << "Choice: ";
    std::cin >> choice;

    switch (choice)
    {
    case 1:
        // attack glavniq. nqkoi ot negovata armiq ili nego kato te se durjat v masiv
        break;
    case 2:
        // special po sushtiq nachin kato otgore shte e
        break;
    case 0:
        std::cout << "Skipping turn ...";
        break;
    default:
        // no such choice

        break;
    }
}

void print_Infantryman_Ui()
{
    std::cout << "=======================================";
    std::cout << "|              INFANTRYMAN            |";
    std::cout << "|                                     |";
    std::cout << "|              1. Attack              |";
    std::cout << "|              2. Special             |";
    std::cout << "|                                     |";
    std::cout << "|              0. Skip                |";
    std::cout << "=======================================";
}

void print_Archer_Ui()
{
    std::cout << "=======================================";
    std::cout << "|                ARCHER               |";
    std::cout << "|                                     |";
    std::cout << "|              1. Attack              |";
    std::cout << "|              2. Special             |";
    std::cout << "|                                     |";
    std::cout << "|              0. Skip                |";
    std::cout << "=======================================";
}

void print_Knight_Ui()
{
    std::cout << "=======================================";
    std::cout << "|                KNIGHT               |";
    std::cout << "|                                     |";
    std::cout << "|              1. Attack              |";
    std::cout << "|              2. Special             |";
    std::cout << "|                                     |";
    std::cout << "|              0. Skip                |";
    std::cout << "=======================================";
}

void print_Healer_Ui()
{
    std::cout << "=======================================";
    std::cout << "|                HEALER               |";
    std::cout << "|                                     |";
    std::cout << "|              1. Attack              |";
    std::cout << "|              2. Special             |";
    std::cout << "|                                     |";
    std::cout << "|              0. Skip                |";
    std::cout << "=======================================";
}

void print_Mage_Ui()
{
    std::cout << "=======================================";
    std::cout << "|                MAGE                 |";
    std::cout << "|                                     |";
    std::cout << "|              1. Attack              |";
    std::cout << "|              2. Special             |";
    std::cout << "|                                     |";
    std::cout << "|              0. Skip                |";
    std::cout << "=======================================";
}

// bad entity type

void print_Skeleton_Ui()
{
    std::cout << "=======================================";
    std::cout << "|               SKELETON              |";
    std::cout << "|                                     |";
    std::cout << "|              1. Attack              |";
    std::cout << "|              2. Special             |";
    std::cout << "|                                     |";
    std::cout << "|              0. Skip                |";
    std::cout << "=======================================";
}

void print_Necromancer_Ui()
{
    std::cout << "=======================================";
    std::cout << "|              NECROMANCER            |";
    std::cout << "|                                     |";
    std::cout << "|              1. Attack              |";
    std::cout << "|              2. Special             |";
    std::cout << "|                                     |";
    std::cout << "|              0. Skip                |";
    std::cout << "=======================================";
}

void print_Ghoul_Ui()
{
    std::cout << "=======================================";
    std::cout << "|                GHOUL                |";
    std::cout << "|                                     |";
    std::cout << "|              1. Attack              |";
    std::cout << "|              2. Special             |";
    std::cout << "|                                     |";
    std::cout << "|              0. Skip                |";
    std::cout << "=======================================";
}

void print_Zombie_Ui()
{
    std::cout << "=======================================";
    std::cout << "|                ZOMBIE               |";
    std::cout << "|                                     |";
    std::cout << "|              1. Attack              |";
    std::cout << "|              2. Special             |";
    std::cout << "|                                     |";
    std::cout << "|              0. Skip                |";
    std::cout << "=======================================";
}

void print_Dybbuk_Ui()
{
    std::cout << "=======================================";
    std::cout << "|                DYBBUK               |";
    std::cout << "|                                     |";
    std::cout << "|              1. Attack              |";
    std::cout << "|              2. Special             |";
    std::cout << "|                                     |";
    std::cout << "|              0. Skip                |";
    std::cout << "=======================================";
}

void print_Revenant_Ui()
{
    std::cout << "=======================================";
    std::cout << "|               REVENANT              |";
    std::cout << "|                                     |";
    std::cout << "|              1. Attack              |";
    std::cout << "|              2. Special             |";
    std::cout << "|                                     |";
    std::cout << "|              0. Skip                |";
    std::cout << "=======================================";
}

void print_Phantom_Ui()
{
    std::cout << "=======================================";
    std::cout << "|                PHANTOM             |";
    std::cout << "|                                     |";
    std::cout << "|              1. Attack              |";
    std::cout << "|              2. Special             |";
    std::cout << "|                                     |";
    std::cout << "|              0. Skip                |";
    std::cout << "=======================================";
}
