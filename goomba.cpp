#include "goomba.h"
#include <iostream>

Goomba::Goomba(int x, int y) : Person(x, y)
{
    //this->setLife(1);
    this->moveRSprite = QPixmap(":images/goomba_right.png");
    this->rect = QRect(x, y, 50, moveRSprite.size().height());
}

Goomba::~Goomba()
{
    std::cout << ("Goomba deleted\n");
}

