#include "flag.h"
#include <iostream>

Flag::Flag(int x, int y) : Block(x, y, ":images/drapeaufin.png")
{

}

Flag::~Flag()
{
    std::cout << ("Flag deleted\n");
}
