#include "gameboard.h"
#include <QPainter>
#include <QApplication>
#include <QDebug>
#include "model.h"


GameBoard::GameBoard(Model *model, QWidget *parent)
    : model(model), QWidget(parent)
{
    this->model = model;
    timerId = startTimer(10);
    gameStarted = true;
    moveL=false;
    moveR=false;
    isJumping=false;
    xRelatif = -100;
    yRelatif = 0;
    questionCount=0;
    brickCount=0;
    moveCount=0;
    isSplashScreen = true;
    setIterBackground(0);
}

GameBoard::~GameBoard()
{
    killTimer(timerId);
}

void GameBoard::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    QMap< int,Background *>::const_iterator b = model->getBackground()->constBegin();
    while (b != model->getBackground()->constEnd()) {
        painter.drawImage(b.value()->getRect(),b.value()->getImage());
        ++b;
    }


    QMap< int,Floor *>::const_iterator i = model->getFloors()->constBegin();
    QMap< int,Question *>::const_iterator e = model->getQuestions()->constBegin();
    QMap< int,Brick*>::const_iterator r = model->getBricks()->constBegin();


    while (i != model->getFloors()->constEnd()) {
        painter.drawImage(i.value()->getRect(),i.value()->getImage());
        ++i;
    }
    while (r != model->getBricks()->constEnd()) {
        painter.drawImage(r.value()->getRect(),r.value()->getImage());
        ++r;
    }
    while (e != model->getQuestions()->constEnd()) {
        painter.drawImage(e.value()->getRect(),e.value()->getImage());
        ++e;
    }

    QRect sourceRectMario = QRect(currentFrame, 1, 57, 68);
    if(moveR){
        painter.drawPixmap(model->getMario()->getRect(), model->getMario()->getMoveRSprite(), sourceRectMario);
    }
    else if(moveL){
        painter.drawPixmap(model->getMario()->getRect(), model->getMario()->getMoveLSprite(), sourceRectMario);
    }
    else
    {
        painter.drawPixmap(model->getMario()->getRect(), model->getMario()->getStopSprite(), sourceRectMario);
    }

    QRect sourceRectGoomba = QRect(currentFrame, 1, 57, 68);
    painter.drawPixmap(model->getGoomba()->getRect(), model->getGoomba()->getStopSprite(), sourceRectGoomba);

    for(int i = 0 ; i < model->getMario()->getLife() ; i++)
    if(isSplashScreen){
        opacity = opacity - 0.01;
        painter.setOpacity(opacity);
        painter.drawImage(model->getSplashScreen()->getRect(), model->getSplashScreen()->getImage());
    }
    else{
        opacity = 1;
        painter.setOpacity(opacity);
    }
}

void GameBoard::timerEvent(QTimerEvent *event)
{
    splashScreen();
    movementMario();
    generateGoomba();
    removeDestroyed();
    repaint();
}


void GameBoard::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Right)
    {
        moveR=true;
    }
    else if(event->key() == Qt::Key_Left)
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
    QMutableMapIterator<int ,Floor * > i(*model->getFloors());
    while (i.hasNext()) {
        i.next();
        if (i.value()->isDestroyed() ){
            qDebug() << "Remove Floor:" << i.key() ;
            i.remove();
        }
    }
    QMutableMapIterator<int ,Question * > k(*model->getQuestions());
    while (k.hasNext()) {
        k.next();
        if (k.value()->isDestroyed() ){
            qDebug() << "Remove Question:" << k.key() ;
            k.remove();
        }
    }
    QMutableMapIterator<int ,Brick* > r(*model->getBricks());
    while (r.hasNext()) {
        r.next();
        if (r.value()->isDestroyed() ){
            qDebug() << "Remove Brick:" << r.key() ;
            r.remove();
        }
    }
    QMutableMapIterator<int ,Background * > b(*model->getBackground());
    while (b.hasNext()) {
        b.next();
        if (b.value()->isDestroyed() ){
            qDebug() << "Remove Background:" << b.key() ;
            b.remove();
        }
    }
}

void GameBoard::movementMario()
{
    int y=model->getMario()->getRect().y();
    int x=model->getMario()->getRect().x();
    //Count type=move;
    //QList<QString> valuesList = model->getCount().values();
    if(isJumping)
    {
        xRelatif+=3;
        yRelatif=(-0.02*(xRelatif*xRelatif)+200);
        y = 334-yRelatif;
        if(moveL && model->getMario()->getRect().x()>=2){
            x-=3;
            moveCount--;        }
        else if(moveR && model->getMario()->getRect().x()<=60){
            x+=3;
            moveCount++;
        }
        else if(moveR && model->getMario()->getRect().x()>=60){
            movementMap();
            moveCount++;
        }
        currentFrame = 0;
        model->getMario()->move(x,y);

    }

    if(intersect())
    {
        xRelatif=-100;
        yRelatif=0;
        isJumping=false;
        if(moveL && model->getMario()->getRect().x()>=2){
            x-=3;
            moveCount--;
        }
        else if(moveR && model->getMario()->getRect().x()<=60){
            x+=3;
            moveCount++;
        }
        else if(moveR && model->getMario()->getRect().x()>=60){
            movementMap();
            moveCount++;

        }
        model->getMario()->move(x, y);

        if(moveR && tempMove == 1){
            currentFrame += 60;
            if (currentFrame >= 180 )
                currentFrame = 1;
            tempMove = 0;
        }
        else if(moveR)
            tempMove++;
        else if(moveL && tempMove == 1){
            currentFrame -= 60;
            if (currentFrame <= 0 )
                currentFrame = 179;
            tempMove = 0;
        }
        else if(moveL)
            tempMove++;
        else
            currentFrame = 0;


    }
    if(!intersect() && !isJumping){
        y += 4;
        if(moveL && model->getMario()->getRect().x()>=2){
            x-=3;
            moveCount--;        }
        else if(moveR && model->getMario()->getRect().x()<=60){
            x+=3;
            moveCount++;
        }
        else if(moveR && model->getMario()->getRect().x()>=60){
            movementMap();
            moveCount++;
        }
        model->getMario()->move(x,y);
    }
}

void GameBoard::movementMap()
{
    int x0=0;
    int y0=0;

    QMap< int,Floor *>::const_iterator i = model->getFloors()->constBegin();
    while (i != model->getFloors()->constEnd()) {
        x0=i.value()->getRect().x();
        i.value()->moveBlock(x0-4);
        ++i;
    }

    QMap< int,Background *>::const_iterator k = model->getBackground()->constBegin();
    if(getIterBackground() == 4){
        while (k != model->getBackground()->constEnd()) {
            x0=k.value()->getRect().x();
            k.value()->moveBlock(x0-1);
            ++k;
        }
        setIterBackground(0);
    }
    else{
        while (k != model->getBackground()->constEnd()) {
            x0=k.value()->getRect().x();
            k.value()->moveBlock(x0);
            ++k;
        }
        setIterBackground(getIterBackground() + 1);
    }

    QMap< int,Question *>::const_iterator j = model->getQuestions()->constBegin();
    while (j != model->getQuestions()->constEnd()) {
        x0=j.value()->getRect().x();
        j.value()->moveBlock(x0-4);
        ++j;
    }

    QMap< int,Brick*>::const_iterator r = model->getBricks()->constBegin();
    while (r != model->getBricks()->constEnd()) {
        x0=r.value()->getRect().x();
        r.value()->moveBlock(x0-4);
        ++r;
    }

    QMap< int,Floor *>::const_iterator i0= model->getFloors()->constBegin();
    while (i0 != model->getFloors()->constEnd()) {
        if(i0.value()->getRect().x() < -model->blockSize){
            i0.value()->setDestroyed(true);
            x0=i0.value()->getRect().x();
            y0=i0.value()->getRect().y();
            Floor* k =new Floor(x0+13*50,y0);
            model->getFloors()->insert(model->getFloorCount(),k);
            qDebug() << "create Floor:" << model->getFloorCount() ;
            model->setFloorCount();

        }
        ++i0;
    }

    QMap< int,Background *>::const_iterator b0= model->getBackground()->constBegin();
    while (b0 != model->getBackground()->constEnd()) {
        if(b0.value()->getRect().x() < - b0.value()->getRect().width() + 2){
            b0.value()->setDestroyed(true);
            Background* b = new Background(b0.value()->getRect().width(),0);
            model->getBackground()->insert(model->getBackgroundCount(), b);
            qDebug() << "create Background:" << model->getBackgroundCount() ;
            model->setBackgroundCount();
        }
        ++b0;
    }

    if(moveCount==200){
        x0=600;
        y0=250;
        Brick* i =new Brick(x0,y0);
        model->getBricks()->insert(model->getBrickCount(), i);
        qDebug() << "create Brick:" << model->getBrickCount() ;
        model->setBrickCount();

        x0=650;
        y0=250;
        Brick* j =new Brick(x0,y0);
        model->getBricks()->insert(model->getBrickCount(), j);
        qDebug() << "create Brick:" << model->getBrickCount() ;
        model->setBrickCount();

        x0=700;
        y0=250;
        Brick* k =new Brick(x0,y0);
        model->getBricks()->insert(model->getBrickCount(), k);
        qDebug() << "create Brick:" << model->getBrickCount() ;
        model->setBrickCount();

        x0=650;
        y0=100;
        Question* l =new Question(x0,y0);
        model->getQuestions()->insert(model->getQuestionCount(), l);
        qDebug() << "create Question:" << model->getQuestionCount() ;
        model->setQuestionCount();
    }
}

bool GameBoard::intersect()
{
    QMap< int,Floor *>::const_iterator i = model->getFloors()->constBegin();
    model->getFloors();
    while (i != model->getFloors()->constEnd()) {
        if ((model->getMario()->getRect()).intersects(i.value()->getRect())){
            return true;

        }
        ++i;
    }
    return false;
}

void GameBoard::splashScreen(){
    int x=model->getSplashScreen()->getRect().x();
    int y=model->getSplashScreen()->getRect().y();
    y = y - 2;
    if(model->getSplashScreen()->getRect().bottom() > 0 && isSplashScreen)
        model->getSplashScreen()->move(x, y);
    else
        isSplashScreen = false;
}

void GameBoard::generateGoomba(){
    int y=model->getGoomba()->getRect().y();
    int x=model->getGoomba()->getRect().x();




}
