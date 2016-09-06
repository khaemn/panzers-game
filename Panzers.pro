#-------------------------------------------------
#
# Project created by QtCreator 2016-08-26T21:39:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Panzers
TEMPLATE = app


SOURCES += main.cpp \
    Engine.cpp \
    gameObjects/AbstractGameObject.cpp \
    gameObjects/tanks/AbstractTank.cpp \
    gameObjects/tanks/BasicEnemy.cpp \
    gameObjects/tanks/Bullet.cpp \
    gameObjects/tanks/Player.cpp \
    gameObjects/tanks/ExplodedTank.cpp \
    gameObjects/mapElements/AbstractMapElement.cpp \
    MapProcessor.cpp \
    gameObjects/mapElements/LevelMap.cpp \
    gameObjects/mapElements/BrickMapElement.cpp \
    gameObjects/mapElements/ConcreteMapElement.cpp \
    gameObjects/mapElements/WaterMapElement.cpp \
    gameObjects/mapElements/NonPlayableChunk.cpp \
    gameObjects/mapElements/ForestMapElement.cpp \
    gameObjects/mapElements/HeadQuarter.cpp \
    gameObjects/tanks/ArmoredEnemy.cpp

HEADERS  += \
    Engine.h \
    AbstractTank.h \
    gameObjects/AbstractGameObject.h \
    gameObjects/tanks/AbstractTank.h \
    gameObjects/tanks/BasicEnemy.h \
    gameObjects/tanks/Bullet.h \
    gameObjects/tanks/Player.h \
    gameObjects/tanks/ExplodedTank.h \
    gameObjects/mapElements/AbstractMapElement.h \
    MapProcessor.h \
    gameObjects/mapElements/LevelMap.h \
    gameObjects/mapElements/BrickMapElement.h \
    gameObjects/mapElements/ConcreteMapElement.h \
    gameObjects/mapElements/WaterMapElement.h \
    gameObjects/mapElements/NonPlayableChunk.h \
    gameObjects/mapElements/ForestMapElement.h \
    gameObjects/mapElements/HeadQuarter.h \
    gameObjects/tanks/ArmoredEnemy.h

RESOURCES += \
    res1.qrc
