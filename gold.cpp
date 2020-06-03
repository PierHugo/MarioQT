#include "gold.h"
#include <QString>
#include <iostream>

Gold::Gold(int x, int y) : Brick(x,y, ":images/gold_big.png")
{
    std::cout << "Gold created\n";
}

Gold::~Gold()
{
    std::cout << ("Golddeleted\n");
}



