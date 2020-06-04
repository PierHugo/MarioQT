#include "flyingthing.h"
#include <iostream>

FlyingThing::FlyingThing(int x, int y) : Monster(x, y)
{
    this->setLife(1);

    this->moveLSprite = QPixmap(":images/flying_thing.png");
    this->rect = QRect(x, y, 40, moveLSprite.size().height());
}

FlyingThing::~FlyingThing()
{
    std::cout << ("FlyingThing deleted\n");
}



