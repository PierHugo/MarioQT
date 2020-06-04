#include "goumba.h"

Goumba::Goumba(int x, int y ) : Person(x,y)
{
    this->moveLSprite = QPixmap(":images/goumba.png");
    this->stopSprite = QPixmap(":images/mario_stop.png");
    this->rect = QRect(x, y, 60, moveRSprite.size().height());
    this->dieRect = QRect(x, y, 60, stopSprite.size().height());

}

Goumba::~Goumba()
{
    std::cout << ("Goumba deleted\n");
}
