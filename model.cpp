#include "model.h"
#include "goomba.h"
#include <mario.h>
#include <question.h>
#include <brick.h>
#include <spike.h>
#include <flag.h>
#include <floor.h>
#include <splashscreen.h>
#include <gameover.h>
#include <QDebug>

Model::Model()
{
    this->floors = new QMap<int,Floor *>;
    this->questions = new QMap<int,Question *>;
    this->bricks= new QMap<int,Brick*>;
    this->spikes= new QMap<int,Spike*>;
    this->flags= new QMap<int,Flag*>;
    this->mario = new Mario(100,144);
    this->goomba = new Goomba(-50, 0);
    this->flyingThing = new FlyingThing(-50, 0);
    this->splashScreen = new SplashScreen(50, 100);
    this->gameOver = new GameOver(50, 100);
    this->won = new Won(50, 100);
    this->background = new QMap<int,Background *>;


    floorCount=0;

    for (int i=0; i<2; i++) {
        Background* b = new Background(i*800, 0);
        background->insert(backgroundCount, b);
        backgroundCount++;
    }

    for (int i=0; i<13; i++) {
        for (int j=0; j<1; j++) {
            Floor* k = new Floor(i*blockSize,500-blockSize-j*blockSize);
            floors->insert(floorCount,k);
            floorCount++;
        }
    }
}

Model::~Model() {
    QMap< int,Floor *>::const_iterator i = floors->constBegin();
    QMap< int,Question *>::const_iterator e = questions->constBegin();
    QMap< int,Brick*>::const_iterator r = bricks->constBegin();
    QMap< int,Spike*>::const_iterator s = spikes->constBegin();
    QMap< int,Flag*>::const_iterator f = flags->constBegin();

    while (i != floors->constEnd()) {
        delete i.value();
        ++i;
    }
    while (e != questions->constEnd()) {
        delete  e.value();
        ++e;
    }
    while (r != bricks->constEnd()) {
        delete  r.value();
        ++r;
    }
    while (s != spikes->constEnd()) {
        delete  s.value();
        ++s;
    }
    while (f != flags->constEnd()) {
        delete  f.value();
        ++f;
    }
    floors->clear();
    delete floors;
    bricks->clear();
    delete bricks;
    spikes->clear();
    delete spikes;
    flags->clear();
    delete flags;
    questions->clear();
    delete questions;
    delete mario;
    delete splashScreen;
    if(goomba != NULL){ delete goomba; }
    delete flyingThing;
    delete gameOver;
    delete won;
}
