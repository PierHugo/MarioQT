#ifndef MODEL_H
#define MODEL_H

#include <QMap>
#include <QMutableMapIterator>
#include <QString>
#include <splashscreen.h>
#include <gameover.h>
#include <won.h>
#include "background.h"

class Question;
class Brick;
class Spike;
class Floor;
class Mario;

//inline enum Count { MOVE, QUESTION, FLOOR };

class Model
{
public:
    Model();
    ~Model();
    inline Mario *getMario(){ return mario; }
    inline Question *getQuestion(){ return question; }

    SplashScreen *getSplashScreen(){ return splashScreen; }
    GameOver *getGameOver(){ return gameOver; }
    Won *getWon(){ return won; }
    inline QMap<int, Question*> *getQuestions(){ return questions; }
    inline QMap<int, Brick*> *getBricks(){ return bricks; }
    inline QMap<int, Spike*> *getSpikes(){ return spikes; }
    inline QMap<int, Floor*> *getFloors(){ return floors; }
    inline QMap<int, Background*> *getBackground(){ return background; }
//    inline QMap<QString, int> *getCount(){ return count; }
    inline int getFloorCount(){ return floorCount; }
    inline void setFloorCount(){ this->floorCount++; }
    inline int getQuestionCount(){ return questionCount; }
    inline void setQuestionCount(){ this->questionCount++; }
    inline int getBrickCount(){ return brickCount; }
    inline void setBrickCount(){ this->brickCount++; }
    inline int getSpikeCount(){ return brickCount; }
    inline void setSpikeCount(){ this->brickCount++; }
    inline int getBackgroundCount(){ return backgroundCount; }
    inline void setBackgroundCount(){ this->backgroundCount++; }
    //inline int  getMoveCount(){ return MoveCount; }
    inline void setMario(Mario *mario){ this->mario = mario; }
    inline void setQuestions(QMap<int,Question*> *questions){ this->questions = questions; }
    inline void setBricks(QMap<int,Brick*> *bricks){ this->bricks= bricks; }
    inline void setFloors(QMap<int,Floor*> *floors){ this->floors = floors; }
    int const blockSize = 50;

private:
    QMap<int, Question*> *questions;
    QMap<int, Floor*> *floors;
    QMap<int, Brick*> *bricks;
    QMap<int, Spike*> *spikes;
    //QMap<QString, int> *count;
    Mario *mario;
    Question *question;
    SplashScreen *splashScreen;
    GameOver *gameOver;
    Won *won;
    QMap<int, Background*> *background;
    int floorCount;
    int questionCount;
    int brickCount;
    int spikeCount;
    int backgroundCount;
    //int moveCount;

    //signals:

    //public slots:
};

#endif // MODEL_H
