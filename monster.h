#ifndef MONSTER_H
#define MONSTER_H

#include <QPixmap>
#include <QImage>
#include <QRect>
#include <QString>

class Monster
{
public:
    Monster(int, int);
    ~Monster();

    bool isDead();
    inline void setDead(bool);
    inline QRect getRect(){ return rect; }
    inline void setRect(QRect rect){ this->rect = rect; }
    inline QRect getDieRect(){ return dieRect; }
    inline void setDieRect(QRect dieRect){ this->dieRect = dieRect; }
    inline QImage & getImage(){ return image; }
    inline QPixmap getMoveRSprite(){ return moveRSprite; }
    void move(int , int);
    void moveDie(int ,int );
    inline int getLife(){ return life; }
    inline void setLife(int life){ this->life = life; }

protected:
    QPixmap moveRSprite;
    QRect rect;
    QRect dieRect;

   private:
    QImage image;
    QPixmap imageMap;
    bool dead;
    int life = 1;
};

#endif // MONSTER_H
