#include "brick.h"
#include <iostream>

Brick::Brick(int x, int y ) : Block(x,y, ":images/brick.png")
{
}

Brick::~Brick()
{
    std::cout << ("Brick deleted\n");
}
