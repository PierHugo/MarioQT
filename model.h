#ifndef MODEL_H
#define MODEL_H

#include <QMap>
#include <QMutableMapIterator>
#include <QString>
#include <splashscreen.h>
#include <gameover.h>
#include <won.h>
#include "background.h"
#include "goomba.h"
#include "flyingthing.h"

class Question;
class Brick;
class Spike;
class Flag;
class Floor;
class Mario;
class Goomba;
class FlyingThing;

class Model
{
public:
    Model();
    ~Model();
    inline Mario *getMario(){ return mario; }
    inline Goomba *getGoomba(){ return goomba; }
    inline FlyingThing *getFlyingThing(){ return flyingThing; }

    SplashScreen *getSplashScreen(){ return splashScreen; }
    GameOver *getGameOver(){ return gameOver; }
    Won *getWon(){ return won; }
    inline QMap<int, Question*> *getQuestions(){ return questions; }
    inline QMap<int, Brick*> *getBricks(){ return bricks; }
    inline QMap<int, Spike*> *getSpikes(){ return spikes; }
    inline QMap<int, Flag*> *getFlags(){ return flags; }
    inline QMap<int, Floor*> *getFloors(){ return floors; }
    inline QMap<int, Background*> *getBackground(){ return background; }
    inline int getFloorCount(){ return floorCount; }
    inline void setFloorCount(){ this->floorCount++; }
    inline int getQuestionCount(){ return questionCount; }
    inline void setQuestionCount(){ this->questionCount++; }
    inline int getBrickCount(){ return brickCount; }
    inline void setBrickCount(){ this->brickCount++; }
    inline int getSpikeCount(){ return spikeCount; }
    inline void setSpikeCount(){ this->spikeCount++; }
    inline int getFlagCount(){ return flagCount; }
    inline void setFlagCount(){ this->flagCount++; }
    inline int getBackgroundCount(){ return backgroundCount; }
    inline void setBackgroundCount(){ this->backgroundCount++; }
    inline void setMario(Mario *mario){ this->mario = mario; }
    inline void setGoomba(Goomba *goomba){ this->goomba = goomba; }
    inline void setFlyingThing(FlyingThing *flyingThing) { this->flyingThing = flyingThing; }
    inline void setQuestions(QMap<int,Question*> *questions){ this->questions = questions; }
    inline void setBricks(QMap<int,Brick*> *bricks){ this->bricks= bricks; }
    inline void setFloors(QMap<int,Floor*> *floors){ this->floors = floors; }
    int const blockSize = 50;
    void deleteGoomba() { delete this->goomba; }
    void deleteFlyingThing() { delete this->flyingThing; }

private:
    QMap<int, Question*> *questions;
    QMap<int, Floor*> *floors;
    QMap<int, Brick*> *bricks;
    QMap<int, Spike*> *spikes;
    QMap<int, Flag*> *flags;
    Mario *mario;
    Goomba *goomba;
    FlyingThing *flyingThing;


    SplashScreen *splashScreen;
    GameOver *gameOver;
    Won *won;
    QMap<int, Background*> *background;
    int floorCount;
    int questionCount;
    int brickCount;
    int spikeCount;
    int flagCount;
    int backgroundCount;
};

#endif // MODEL_H
