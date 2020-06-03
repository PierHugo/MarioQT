#include "goomba.h"
#include <iostream>

Goomba::Goomba(int x, int y) : Person(x, y)
{
    //this->setLife(1);
    this->moveLSprite = QPixmap(":images/goomba_right.png");
    this->stopSprite = QPixmap(":images/goomba_right.png");
    this->rect = QRect(x, y, 50, moveRSprite.size().height());
    this->dieRect = QRect(x, y, 50, stopSprite.size().height());

}

Goomba::~Goomba()
{
    std::cout << ("Goomba deleted\n");
}

