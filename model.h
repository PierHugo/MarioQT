#ifndef MODEL_H
#define MODEL_H

#include <QMap>
#include <QMutableMapIterator>
#include <QString>
#include <splashscreen.h>
#include <gameover.h>
#include <won.h>
#include "background.h"
#include "castle.h"
#include "goomba.h"
#include "wingedgoomba.h"

class Question;
class Spike;
class Flag;
class Floor;
class Mario;
class Castle;
class Goomba;
class WingedGoomba;

class Model
{
  public:
      Model();
      ~Model();
      inline Mario *getMario(){ return mario; }
      inline Goomba *getGoomba(){ return goomba; }
      inline WingedGoomba *getWingedGoomba(){ return wingedGoomba; }

      SplashScreen *getSplashScreen(){ return splashScreen; }
      GameOver *getGameOver(){ return gameOver; }
      Won *getWon(){ return won; }
      inline QMap<int, Question*> *getQuestions(){ return questions; }
      inline QMultiMap<int, Spike*> *getSpikes(){ return spikes; }
      inline QMap<int, Flag*> *getFlags(){ return flags; }
      inline QMap<int, Floor*> *getFloors(){ return floors; }
      inline QMap<int, Background*> *getBackground(){ return background; }

      inline QMap<int, Castle*> *getCastle(){return castle;}
      inline int getFloorCount(){ return floorCount; }
      inline void setFloorCount(){ this->floorCount++; }
      inline int getQuestionCount(){ return questionCount; }
      inline void setQuestionCount(){ this->questionCount++; }
      inline int getSpikeCount(){ return spikeCount; }
      inline void setSpikeCount(){ this->spikeCount++; }
      inline int getFlagCount(){ return flagCount; }
      inline void setFlagCount(){ this->flagCount++; }
      inline int getBackgroundCount(){ return backgroundCount; }
      inline void setBackgroundCount(){ this->backgroundCount++; }
      inline int getCastleCount(){return castleCount;}
      inline void setCastleCount(){this->castleCount++;}

      inline void setMario(Mario *mario){ this->mario = mario; }
      inline void setGoomba(Goomba *goomba){ this->goomba = goomba; }
      inline void setWingedGoomba(WingedGoomba *wingedGoomba) { this->wingedGoomba = wingedGoomba; }
      inline void setQuestions(QMap<int,Question*> *questions){ this->questions = questions; }
      inline void setSpikes(QMultiMap<int, Spike*> *spikes){this->spikes = spikes;}
      inline void setFloors(QMap<int,Floor*> *floors){ this->floors = floors; }
      inline void setFlag(QMap<int, Flag*> *flag){this->flags = flag;}
      inline void setCastle(QMap<int, Castle*> *castle){this->castle = castle;}
      int const blockSize = 50;
      void deleteGoomba() { delete this->goomba; }
      void deleteWingedGoomba() { delete this->wingedGoomba; }

  private:
      QMap<int, Question*> *questions;
      QMap<int, Floor*> *floors;
      QMap<int, Castle*> *castle;
      QMultiMap<int, Spike*> *spikes;
      QMap<int, Flag*> *flags;
      Mario *mario;
      Goomba *goomba;
      WingedGoomba *wingedGoomba;


      SplashScreen *splashScreen;
      GameOver *gameOver;
      Won *won;
      QMap<int, Background*> *background;
      int floorCount;
      int questionCount;
      int spikeCount;
      int backgroundCount;

      int flagCount;
      int castleCount;
};
#endif // MODEL_H
