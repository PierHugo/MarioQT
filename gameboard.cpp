#include "gameboard.h"
#include <QPainter>
#include <QApplication>
#include <QDebug>

GameBoard::GameBoard(QWidget *parent)
    : QWidget(parent)
{
    timerId = startTimer(10);

    gameStarted = true;
    moveL=false;
    moveR=false;
    isJumping=false;

    floors = new QMap<int,Floor *>;
    mario = new Mario(200,383);

    floorCount=0;
    xRelatif = -100;
    yRelatif = 0;
    questionCount=0;
    moveCount=0;

    for (int i=0; i<13; i++) {
        for (int j=0; j<1; j++) {
            Floor* k =new Floor(i*50,450-j*50);
            floors->insert(floorCount,k);
            floorCount++;
        }
    }
}

GameBoard::~GameBoard()
{
    killTimer(timerId);
    QMap< int,Floor *>::const_iterator i = floors->constBegin();

    while (i != floors->constEnd()) {
        delete i.value();
         ++i;
     }

    floors->clear();
    delete floors;
    delete mario;
}

void GameBoard::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage(mario->getRect(),mario->getImage());

    QMap< int,Floor *>::const_iterator i = floors->constBegin();

    while (i != floors->constEnd()) {
        painter.drawImage(i.value()->getRect(),i.value()->getImage());
        ++i;
    }
}

void GameBoard::timerEvent(QTimerEvent *event)
{
    movementMario();
    removeDestroyed();
    repaint();
}


void GameBoard::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Right && !moveL)
    {
        moveR=true;
    }
    else if(event->key() == Qt::Key_Left && !moveR)
    {
        moveL=true;
    }
    else if(event->key() == Qt::Key_Space && intersect())
    {
        isJumping=true;
    }
    else if (event->key() == Qt::Key_Escape )
    {
        stopGame();
        qApp->exit();
    }
    else
        event->ignore();
}

void GameBoard::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Right )
    {
        moveR=false;

    }
    else if(event->key() == Qt::Key_Left )
    {
        moveL=false;
    }
    else
        event->ignore();
}

void GameBoard::stopGame()
{
    killTimer(timerId);
    gameStarted = false;
}

void GameBoard::removeDestroyed()
{
    QMutableMapIterator<int ,Floor * > i(*floors);
    while (i.hasNext()) {
        i.next();
        if (i.value()->isDestroyed() ){
            qDebug() << "Remove Floor:" << i.key() ;
            i.remove();
        }
    }
}

void GameBoard::movementMap()
{
    int x0=0;
    int y0=0;

    QMap< int,Floor *>::const_iterator i = floors->constBegin();
    while (i != floors->constEnd()) {
        x0=i.value()->getRect().x();
        i.value()->moveBlock(x0-2);
        ++i;
    }
    QMap< int,Floor *>::const_iterator i0= floors->constBegin();
    while (i0 != floors->constEnd()) {
        if(i0.value()->getRect().x()<-50){
            i0.value()->setDestroyed(true);
            x0=i0.value()->getRect().x();
            y0=i0.value()->getRect().y();
            Floor* k =new Floor(x0+13*50,y0);
            floors->insert(floorCount,k);
            qDebug() << "create Floor:" << floorCount ;
            floorCount++;
        }
        ++i0;
    }
}

void GameBoard::movementMario()
{
    int y=mario->getRect().y();
    int x=mario->getRect().x();

    if(isJumping )
    {
        xRelatif+=3;
        yRelatif=(-0.02*(xRelatif*xRelatif)+200);
        y = 330-yRelatif;
        if(moveL && mario->getRect().x()>=2){
            x-=2;
            moveCount--;
        }
        else if(moveR && mario->getRect().x()<=60){
            x+=2;
            moveCount++;
        }
        else if(moveR && mario->getRect().x()>=60){
            movementMap();
            moveCount++;
        }
        mario->move(x,y);

    }

    if(intersect())
    {
        xRelatif=-100;
        yRelatif=0;
        isJumping=false;
        if(moveL && mario->getRect().x()>=2){
            x-=2;
            moveCount--;
        }
        else if(moveR && mario->getRect().x()<=60){
            x+=2;
            moveCount++;
        }
        else if(moveR && mario->getRect().x()>=60){
            movementMap();
            moveCount++;
        }
        mario->move(x,y);
    }
}


bool GameBoard::intersect()
{
    QMap< int,Floor *>::const_iterator i = floors->constBegin();
    while (i != floors->constEnd()) {
        if ((mario->getRect()).intersects(i.value()->getRect())){
            return true;
        }
        ++i;
    }
    return false;
}
