#ifndef GAME_UI_CPP
#define GAME_UI_CPP
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

//clang-format off
void print_Ui(Entity *e)
{
    std::cout << "=========================================" << std::endl;
    std::cout << "|\t\t" << e->get_type() << "\t\t\t      |" << std::endl;
    std::cout << "|\t\t\t\t\t                             |" << std::endl;
    std::cout << "|\t\t         1. Attack\t\t             |" << std::endl;
    std::cout << "|\t\t         2. Special\t\t            |" << std::endl;
    std::cout << "|\t\t\t\t\t                             |" << std::endl;
    std::cout << "|\t\t         0. Skip\t\t\t             |" << std::endl;
    std::cout << "=========================================" << std::endl;
}

//clang-format on

#endif