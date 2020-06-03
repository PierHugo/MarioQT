#ifndef MODEL_H
#define MODEL_H

#include <QMap>
#include <QMutableMapIterator>
#include <QString>
#include <splashscreen.h>
#include "background.h"
#include "goomba.h"

class Question;
class Brick;
class Floor;
class Mario;
class Goomba;

//inline enum Count { MOVE, QUESTION, FLOOR };

class Model
{
public:
    Model();
    ~Model();
    inline Mario *getMario(){ return mario; }
    inline Goomba *getGoomba(){ return goomba; }
    SplashScreen *getSplashScreen(){ return splashScreen; }
    inline QMap<int, Question*> *getQuestions(){ return questions; }
    inline QMap<int, Brick*> *getBricks(){ return bricks; }
    inline QMap<int, Floor*> *getFloors(){ return floors; }
    inline QMap<int, Background*> *getBackground(){ return background; }
//    inline QMap<QString, int> *getCount(){ return count; }
    inline int getFloorCount(){ return floorCount; }
    inline void setFloorCount(){ this->floorCount++; }
    inline int getQuestionCount(){ return questionCount; }
    inline void setQuestionCount(){ this->questionCount++; }
    inline int getBrickCount(){ return brickCount; }
    inline void setBrickCount(){ this->brickCount++; }
    inline int getBackgroundCount(){ return backgroundCount; }
    inline void setBackgroundCount(){ this->backgroundCount++; }
    //inline int  getMoveCount(){ return MoveCount; }
    inline void setMario(Mario *mario){ this->mario = mario; }
    inline void setGoomba(Goomba *goomba){ this->goomba = goomba; }
    inline void setQuestions(QMap<int,Question*> *questions){ this->questions = questions; }
    inline void setBricks(QMap<int,Brick*> *bricks){ this->bricks= bricks; }
    inline void setFloors(QMap<int,Floor*> *floors){ this->floors = floors; }
    int const blockSize = 50;

private:
    QMap<int, Question*> *questions;
    QMap<int, Floor*> *floors;
    QMap<int, Brick*> *bricks;
    //QMap<QString, int> *count;
    Mario *mario;
    Goomba *goomba;
    SplashScreen *splashScreen;
    QMap<int, Background*> *background;
    int floorCount;
    int questionCount;
    int brickCount;
    int backgroundCount;
    //int moveCount;

    //signals:

    //public slots:
};

#endif // MODEL_H
