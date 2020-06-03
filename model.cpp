#include "model.h"
#include <mario.h>
#include <question.h>
#include <brick.h>
#include <floor.h>
#include <flag.h>
#include <splashscreen.h>
#include <QDebug>

Model::Model()
{
    this->floors = new QMap<int,Floor *>;
    this->questions = new QMap<int,Question *>;
    this->bricks= new QMap<int,Brick*>;
    this->flag = new QMap<int,Flag*>;
    this->castle = new QMap<int,Castle*>;
    this->mario = new Mario(100,144);
    this->splashScreen = new SplashScreen(100, 100);
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
    QMap<int, Flag*>::const_iterator f = flag->constBegin();
    QMap<int, Castle*>::const_iterator c = castle->constBegin();

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
    while (f != flag->constEnd()) {
        delete f.value();
        ++f;
    }
    while (c != castle->constEnd()) {
        delete c.value();
        ++c;
    }

    floors->clear();
    delete floors;
    bricks->clear();
    delete bricks;
    questions->clear();
    delete questions;
    flag->clear();
    delete flag;
    castle->clear();
    delete castle;
    delete mario;
    delete splashScreen;
}

