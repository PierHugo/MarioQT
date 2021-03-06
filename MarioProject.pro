#-------------------------------------------------
#
# Project created by QtCreator 2015-09-30T22:45:53
#
#-------------------------------------------------

QT       += core gui \
        multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MarioProject
TEMPLATE = app
QMAKE_CXXFLAGS+= -std=c++11
QMAKE_LFLAGS +=  -std=c++11

RESOURCES += mario.qrc


SOURCES += main.cpp \
    block.cpp \
    castle.cpp \
    flag.cpp \
    wingedgoomba.cpp \
    gameboard.cpp \
    floor.cpp \
    goomba.cpp \
    gameover.cpp \
    mario.cpp \
    monster.cpp \
    person.cpp \
    model.cpp \
    question.cpp \
    spike.cpp \
    splashscreen.cpp \
    background.cpp \
    won.cpp

HEADERS  += gameboard.h \
    block.h \
    castle.h \
    flag.h \
    floor.h \
    wingedgoomba.h \
    goomba.h \
    gameover.h \
    mario.h \
    monster.h \
    person.h \
    model.h \
    question.h \
    spike.h \
    splashscreen.h \
    background.h \
    won.h

DISTFILES +=
