#include "MapProcessor.h"
#include "gameObjects/mapElements/BrickMapElement.h"
#include "gameObjects/mapElements/ConcreteMapElement.h"
#include "gameObjects/mapElements/WaterMapElement.h"
#include "gameObjects/mapElements/NonPlayableChunk.h"
#include "gameObjects/mapElements/ForestMapElement.h"
#include "gameObjects/mapElements/HeadQuarter.h"

#include "gameObjects/tanks/BasicEnemy.h"
#include "gameObjects/tanks/ArmoredEnemy.h"

MapProcessor::MapProcessor(QObject *parent) : QObject(parent){
    scene = NULL;

    level = new LevelMap();

    for (int i=0; i<ENEMY_SPAWNERS; i++){
        enemySpawnerX[i] = -1;
        enemySpawnerY[i] = -1;
    }

    playerSpawnPointX = -1;
    playerSpawnPointY = -1;
}

MapProcessor::~MapProcessor(){
    delete level;
}

QGraphicsScene * MapProcessor::createScene(){
    // create the scene
    scene = new QGraphicsScene();
    this->scene = scene;
    scene->setSceneRect(0,0,GAME_WINDOW_WIDTH,GAME_WINDOW_HEIGHT);
    scene->setBackgroundBrush(QBrush(QImage(":/images/images/terrain/ground.png")));
    return scene;
}

void MapProcessor::clearScene(){
    scene->clear();
}

void MapProcessor::buildLevel(int levelNum){
    try{
        level->loadLevel(levelNum);
    }catch(...){
        throw -1;
    }
    enemiesRemain = level->getEnemiesRemain();
    int spawnerNum = 0;
    for (int x = 0; x<MAP_WIDTH_CHUNKS; x++){
        for (int y = 0; y<MAP_HEIGHT_CHUNKS; y++){
            AbstractMapElement * element = NULL;
            char elementName = level->getElementNameXY(x,y);
            //Element names are:
            //E - enemy spawning point
            //P - player spawning point
            //Spawning points are not map elements and are used just to
            //define a place for spawning player sprite or enemies on the map.
            if (elementName == 'P'){
                if (playerSpawnPointX<0) playerSpawnPointX = x*GRID_STEP;
                if (playerSpawnPointY<0) playerSpawnPointY = y*GRID_STEP;
            }else if (elementName == 'E'){
                if (spawnerNum < ENEMY_SPAWNERS){
                    if (enemySpawnerX[spawnerNum] < 0){
                        enemySpawnerX[spawnerNum] = x*GRID_STEP;
                    }
                    if (enemySpawnerY[spawnerNum] < 0){
                        enemySpawnerY[spawnerNum] = y*GRID_STEP;
                    }
                    ++spawnerNum;
                }
            }else{
                //B,C,W,F,H - bricks, concrete, water, forest, headquarter
                //All theese are map elements need to be spawn.
                element = getMapElement(elementName);
                if (element != NULL){
                    element->setPos(x*GRID_STEP,y*GRID_STEP);
                    scene->addItem(element);
                }
            }
        }
    }
}

AbstractMapElement * MapProcessor::getMapElement(char name){
    //C - concrete indestructible wall
    //B - brick destructible wall
    //W - non-traversable water
    //F - forest
    //H - headquarter
    //X - non-playable part of the screen (indestructible, non-traversable)
    if (name == 'X'){
        return new NonPlayableChunk();
    }else if (name == 'B'){
        return new BrickMapElement();
    }else if (name == 'C'){
        return new ConcreteMapElement();
    }else if (name == 'W'){
        return new WaterMapElement();
    }else if (name == 'F'){
        return new ForestMapElement();
    }else if (name == 'H'){
        return new HeadQuarter();
    }
    return NULL;
}

int MapProcessor::getPlayerSpawnPointX(){
    return playerSpawnPointX;
}
int MapProcessor::getPlayerSpawnPointY(){
    return playerSpawnPointY;
}
int MapProcessor::getEnemySpawnPointX(int pointNum){
    if (pointNum>=0 && pointNum < ENEMY_SPAWNERS)
        return enemySpawnerX[pointNum];
    else
        return 0;
}
int MapProcessor::getEnemySpawnPointY(int pointNum){
    if (pointNum>=0 && pointNum < ENEMY_SPAWNERS)
        return enemySpawnerY[pointNum];
    else
        return 0;
}
AbstractTank* MapProcessor::getEnemy(){
    if (enemiesRemain <= 0) return NULL;

    AbstractTank* enemy = NULL;
    char enemyName = level->getNextEnemyName();
    switch (enemyName) {
    case 'b':
        enemy = new BasicEnemy();
        break;
    case 'a':
        enemy = new ArmoredEnemy();
        break;
    default:
        //Some unknown enemy name reached, fault condition
        enemiesRemain = 0;
        return NULL;
        break;
    }
    enemiesRemain = level->getEnemiesRemain();
    return enemy;
}

int MapProcessor::getEnemiesRemain(){
    return enemiesRemain;
}

int MapProcessor::getTotalEnemies(){
    return level->getTotalEnemies();
}
