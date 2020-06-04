#include "gameboard.h"
#include <QPainter>
#include <QApplication>
#include <QDebug>
#include "model.h"
#include <iostream>


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
    spikeCount=0;
    flagCount=0;
    moveCount=0;
    isSplashScreen = true;
    setIterBackground(0);
    isGameOver = false;
    isWon= false;
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
    QMap< int,Spike*>::const_iterator s = model->getSpikes()->constBegin();
    QMap< int,Flag*>::const_iterator f = model->getFlags()->constBegin();


    while (i != model->getFloors()->constEnd()) {
        painter.drawImage(i.value()->getRect(),i.value()->getImage());
        ++i;
    }
    while (r != model->getBricks()->constEnd()) {
        painter.drawImage(r.value()->getRect(),r.value()->getImage());
        ++r;
    }
    while (s != model->getSpikes()->constEnd()) {
        painter.drawImage(s.value()->getRect(),s.value()->getImage());
        ++s;
    }
    while (e != model->getQuestions()->constEnd()) {
        painter.drawImage(e.value()->getRect(),e.value()->getImage());
        ++e;
    }
    while (f != model->getFlags()->constEnd()) {
        painter.drawImage(f.value()->getRect(),f.value()->getImage());
        ++f;
    }

    QRect sourceRect = QRect(currentFrame, 1, 57, 68);

    if(moveR){
        painter.drawPixmap(model->getMario()->getRect(), model->getMario()->getMoveRSprite(), sourceRect);
    }
    else if(moveL){
        painter.drawPixmap(model->getMario()->getRect(), model->getMario()->getMoveLSprite(), sourceRect);
    }
    else
    {
        painter.drawPixmap(model->getMario()->getRect(), model->getMario()->getStopSprite(), sourceRect);
    }

    // Generate Goomba
    QRect sourceRectGoomba = QRect(currentFrame, 1, 57, 68);
    painter.drawPixmap(model->getGoomba()->getRect(), model->getGoomba()->getMoveLSprite(), sourceRectGoomba);

    // Generate FlyingThing
    QRect sourceRectFlyingThing = QRect(currentFrame, 1, 57, 68);
    painter.drawPixmap(model->getFlyingThing()->getRect(), model->getFlyingThing()->getMoveLSprite(), sourceRectFlyingThing);

    for(int i = 0 ; i < model->getMario()->getLife() ; i++)
        if(isSplashScreen){
            opacity = opacity - 0.0003;
            // 0.0003
            painter.setOpacity(opacity);
            painter.drawImage(model->getSplashScreen()->getRect(), model->getSplashScreen()->getImage());
        }
        else{
            opacity = 1;
            painter.setOpacity(opacity);
        }
    if(isGameOver){
        opacity = 1;
        painter.setOpacity(opacity);
        painter.drawImage(model->getGameOver()->getRect(), model->getGameOver()->getImage());
    }
    if(isWon){
        opacity = 1;
        painter.setOpacity(opacity);
        painter.drawImage(model->getWon()->getRect(), model->getWon()->getImage());
    }


}

void GameBoard::timerEvent(QTimerEvent *event)
{
    splashScreen();
    movementMario();
    movementGoomba();
    movementFlyingThing();
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


void GameBoard::gameOver()
{

    isGameOver = true;
    qDebug() << "Vous êtes mort, Echap pour quitter";

    stopGame();
}

void GameBoard::gameWon()
{
    isWon = true;
    qDebug() << "Vous venez de gagner, Echap pour quitter";
    stopGame();
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
    QMutableMapIterator<int ,Spike* > s(*model->getSpikes());
    while (s.hasNext()) {
        s.next();
        if (s.value()->isDestroyed() ){
            qDebug() << "Remove Spikes:" << s.key() ;
            s.remove();
        }
    }
    QMutableMapIterator<int ,Flag* > f(*model->getFlags());
    while (f.hasNext()) {
        f.next();
        if (f.value()->isDestroyed() ){
            qDebug() << "Remove Flags:" << f.key() ;
            f.remove();
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



        //gagner si on touche le drapeau
        //FIXME : juste le premier est pris en compte
        if(!model->getFlags()->empty() && model->getFlags()->constBegin().value()->getRect().intersects(model->getMario()->getRect()))
        {
            gameWon();
        }

        //mourir si on touche les piques
        //FIXME : juste le premier est pris en compte
        if(!model->getSpikes()->empty() && model->getSpikes()->constBegin().value()->getRect().intersects(model->getMario()->getRect()))
        {
            gameOver();
        }


        //mourir si on tombe
        if(model->getMario()->getRect().y()>=500)
        {
            gameOver();
        }

        //marche à gauche et est à gauche
        if(moveL && model->getMario()->getRect().x()<=20){
            movementMapLeft();
            moveCount--;
        }
        //marche à gauche et est à droite
        else if(moveL && model->getMario()->getRect().x()>=20){
            x-=2;
            moveCount--;
        }
        //marche à droite et est à gauche
        else if(moveR && model->getMario()->getRect().x()<=150){
            x+=2;
            moveCount++;
        }
        //marche à gauche et est à droite
        else if(moveR && model->getMario()->getRect().x()>=150){
            movementMapRight();
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


        //gagner si on touche le drapeau
        //FIXME : juste le premier est pris en compte
        if(!model->getFlags()->empty() && model->getFlags()->constBegin().value()->getRect().intersects(model->getMario()->getRect()))
        {
            gameWon();
        }

        //mourir si on touche les piques
        //FIXME : juste le premier est pris en compte
        if(!model->getSpikes()->empty() && model->getSpikes()->constBegin().value()->getRect().intersects(model->getMario()->getRect()))
        {
            gameOver();
        }

        //mourir
        if(model->getMario()->getRect().y()>=500)
        {
            gameOver();
        }

        //marche à gauche et est à gauche
        if(moveL && model->getMario()->getRect().x()<=20){
            movementMapLeft();
            moveCount--;
        }
        //marche à gauche et est à droite
        else if(moveL && model->getMario()->getRect().x()>=20){
            x-=2;
            moveCount--;
        }
        //marche à droite et est à gauche
        else if(moveR && model->getMario()->getRect().x()<=150){
            x+=2;
            moveCount++;
        }
        //marche à gauche et est à droite
        else if(moveR && model->getMario()->getRect().x()>=150){
            movementMapRight();
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
        //gagner si on touche le drapeau
        //FIXME : juste le premier est pris en compte
        if(!model->getFlags()->empty() && model->getFlags()->constBegin().value()->getRect().intersects(model->getMario()->getRect()))
        {
            gameWon();
        }

        //mourir si on touche les piques
        //FIXME : juste le premier est pris en compte
        if(!model->getSpikes()->empty() && model->getSpikes()->constBegin().value()->getRect().intersects(model->getMario()->getRect()))
        {
            gameOver();
        }

        //mourir
        if(model->getMario()->getRect().y()>=500)
        {
            gameOver();
        }

        //va à gauche et est à gauche
        if(moveL && model->getMario()->getRect().x()<=20){
            movementMapLeft();
            moveCount--;
        }
        //va à gauche et est à droite
        else if(moveL && model->getMario()->getRect().x()>=20){
            x-=3;
            moveCount--;
        }
        //va à droite et est à gauche
        else if(moveR && model->getMario()->getRect().x()<=150){
            x+=3;
            moveCount++;
        }
        //va à gauche et est à droite
        else if(moveR && model->getMario()->getRect().x()>=150){
            movementMapRight();
            moveCount++;
        }

        model->getMario()->move(x, y);
    }
}

void GameBoard::movementMapRight()
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


    QMap< int,Spike*>::const_iterator s = model->getSpikes()->constBegin();
    while (s != model->getSpikes()->constEnd()) {
        x0=s.value()->getRect().x();
        s.value()->moveBlock(x0-4);
        ++s;
    }

    QMap< int,Flag*>::const_iterator f = model->getFlags()->constBegin();
    while (f != model->getFlags()->constEnd()) {
        x0=f.value()->getRect().x();
        f.value()->moveBlock(x0-4);
        ++f;
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
        generateMap();
    }
}

void GameBoard::movementMapLeft()
{
    int x0=0;
    int y0=0;

    QMap< int,Floor *>::const_iterator i = model->getFloors()->constBegin();
    while (i != model->getFloors()->constEnd()) {
        x0=i.value()->getRect().x();
        i.value()->moveBlock(x0+4);
        ++i;
    }

    QMap< int,Background *>::const_iterator k = model->getBackground()->constBegin();
    if(getIterBackground() == 4){
        while (k != model->getBackground()->constEnd()) {
            x0=k.value()->getRect().x();
            k.value()->moveBlock(x0+1);
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
        j.value()->moveBlock(x0+4);
        ++j;
    }

    QMap< int,Brick*>::const_iterator r = model->getBricks()->constBegin();
    while (r != model->getBricks()->constEnd()) {
        x0=r.value()->getRect().x();
        r.value()->moveBlock(x0+4);
        ++r;
    }


    QMap< int,Spike*>::const_iterator s = model->getSpikes()->constBegin();
    while (s != model->getSpikes()->constEnd()) {
        x0=s.value()->getRect().x();
        s.value()->moveBlock(x0+4);
        ++s;
    }

    QMap< int,Flag*>::const_iterator f = model->getFlags()->constBegin();
    while (f != model->getFlags()->constEnd()) {
        x0=f.value()->getRect().x();
        f.value()->moveBlock(x0+4);
        ++f;
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
}

void GameBoard::generateMap()
{

//    int x0=600;
//    int y0=250;
//    Brick* i =new Brick(x0,y0);
//    model->getBricks()->insert(model->getBrickCount(), i);
//    qDebug() << "create Brick:" << model->getBrickCount() ;
//    model->setBrickCount();

//    x0=650;
//    y0=250;
//    Brick* j =new Brick(x0,y0);
//    model->getBricks()->insert(model->getBrickCount(), j);
//    qDebug() << "create Brick:" << model->getBrickCount() ;
//    model->setBrickCount();

//    x0=700;
//    y0=250;
//    Brick* k =new Brick(x0,y0);
//    model->getBricks()->insert(model->getBrickCount(), k);
//    qDebug() << "create Brick:" << model->getBrickCount() ;
//    model->setBrickCount();

//    x0=650;
//    y0=150;
//    Question* l =new Question(x0,y0);
//    model->getQuestions()->insert(model->getQuestionCount(), l);
//    qDebug() << "create Question:" << model->getQuestionCount() ;
//    model->setQuestionCount();


    int x0=800;
    int y0=250;
    Spike* u =new Spike(x0,y0);
    model->getSpikes()->insert(model->getSpikeCount(), u);
    qDebug() << "create Spike:" << model->getSpikeCount() ;
    model->setSpikeCount();

    x0=850;
    y0=250;
    Spike* v =new Spike(x0,y0);
    model->getSpikes()->insert(model->getSpikeCount(), v);
    qDebug() << "create Spike:" << model->getSpikeCount() ;
    model->setSpikeCount();

    x0=900;
    y0=250;
    Spike* w =new Spike(x0,y0);
    model->getSpikes()->insert(model->getSpikeCount(), w);
    qDebug() << "create Spike:" << model->getSpikeCount() ;
    model->setSpikeCount();



    x0=2000;
    y0=190;
    Flag* f =new Flag(x0,y0);
    model->getFlags()->insert(model->getFlagCount(), f);
    qDebug() << "create Flag:" << model->getFlagCount() ;
    model->setFlagCount();



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

void GameBoard::splashScreen()
{
    int x=model->getSplashScreen()->getRect().x();
    int y=model->getSplashScreen()->getRect().y();
    y = y - 0.5;

    if(model->getSplashScreen()->getRect().bottom() > 0 && isSplashScreen)
        model->getSplashScreen()->move(x, y);
    else
        isSplashScreen = false;
}

void GameBoard::movementGoomba(){
    int y=model->getGoomba()->getRect().y();
    int x=model->getGoomba()->getRect().x();

    model->getGoomba()->move(x-1, y);
}

void GameBoard::movementFlyingThing(){
    int x=model->getFlyingThing()->getRect().x();
    int y=model->getFlyingThing()->getRect().y();

    model->getFlyingThing()->move(x-1, y);
}
