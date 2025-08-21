#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP
#include <iostream>
#include "Entity.hpp"


class Zombie : public Entity{
public:
    Zombie() : Entity("Zombie", 250, UNARMORED, 0, BAD, 15, 300, 0, false, true){};
};

#endif