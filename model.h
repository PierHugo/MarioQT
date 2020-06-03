#ifndef MODEL_H
#define MODEL_H

#include <QMap>
#include <QMutableMapIterator>
#include <QString>
#include <splashscreen.h>
#include "background.h"
#include "flag.h"
#include "castle.h"

class Question;
class Brick;
class Floor;
class Mario;
class Flag;
class Castle;

//inline enum Count { MOVE, QUESTION, FLOOR };

class Model
{
public:
    Model();
    ~Model();
    inline Mario *getMario(){ return mario; }
    SplashScreen *getSplashScreen(){ return splashScreen; }
    inline QMap<int, Question*> *getQuestions(){ return questions; }
    inline QMap<int, Brick*> *getBricks(){ return bricks; }
    inline QMap<int, Floor*> *getFloors(){ return floors; }
    inline QMap<int, Background*> *getBackground(){ return background; }
    inline QMap<int, Flag*> *getFlag(){return flag;}
    inline QMap<int, Castle*> *getCastle(){return castle;}
//    inline QMap<QString, int> *getCount(){ return count; }
    inline int getFloorCount(){ return floorCount; }
    inline void setFloorCount(){ this->floorCount++; }
    inline int getQuestionCount(){ return questionCount; }
    inline void setQuestionCount(){ this->questionCount++; }
    inline int getBrickCount(){ return brickCount; }
    inline void setBrickCount(){ this->brickCount++; }
    inline int getBackgroundCount(){ return backgroundCount; }
    inline void setBackgroundCount(){ this->backgroundCount++; }
    inline int getFlagCount(){return flagCount;}
    inline void setFlagCount(){this->flagCount++;}
    inline int getCastleCount(){return castleCount;}
    inline void setCastleCount(){this->castleCount++;}

    //inline int  getMoveCount(){ return MoveCount; }
    inline void setMario(Mario *mario){ this->mario = mario; }
    inline void setQuestions(QMap<int,Question*> *questions){ this->questions = questions; }
    inline void setBricks(QMap<int,Brick*> *bricks){ this->bricks= bricks; }
    inline void setFloors(QMap<int,Floor*> *floors){ this->floors = floors; }
    inline void setFlag(QMap<int, Flag*> *flag){this->flag = flag;}
    inline void setCastle(QMap<int, Castle*> *castle){this->castle = castle;}
    int const blockSize = 50;

private:
    QMap<int, Question*> *questions;
    QMap<int, Floor*> *floors;
    QMap<int, Brick*> *bricks;
    QMap<int, Flag*> *flag;
    QMap<int, Castle*> *castle;
    //QMap<QString, int> *count;
    Mario *mario;
    SplashScreen *splashScreen;
    QMap<int, Background*> *background;
    int floorCount;
    int questionCount;
    int brickCount;
    int backgroundCount;
    int flagCount;
    int castleCount;
    //int moveCount;

    //signals:

    //public slots:
};

#endif // MODEL_H
