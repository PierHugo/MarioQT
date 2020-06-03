#include "header.h"

Header::Header()
{
    this->rect = QRect(0, 0, 900, 40);
    this->color = QColor(Qt::white);
    this->text = QString("vie");
    this->heart = QImage();
    heart.load(":images/heart.png");
    this->heartSize = heart.rect();
   }
