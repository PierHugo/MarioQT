#-------------------------------------------------
#
# Project created by QtCreator 2015-09-30T22:45:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MarioProject
TEMPLATE = app
QMAKE_CXXFLAGS+= -std=c++11
QMAKE_LFLAGS +=  -std=c++11

RESOURCES += mario.qrc


SOURCES += main.cpp \
    block.cpp \
    brick.cpp \
    gameboard.cpp \
    floor.cpp \
    mario.cpp \
    person.cpp \
    model.cpp \
    question.cpp \
    splashscreen.cpp \
    background.cpp

HEADERS  += gameboard.h \
    block.h \
    brick.h \
    floor.h \
    mario.h \
    person.h \
    model.h \
    question.h \
    splashscreen.h \
    background.h

DISTFILES +=
