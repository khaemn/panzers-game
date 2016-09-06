#ifndef MAPPROCESSOR_H
#define MAPPROCESSOR_H

#include <QObject>
#include <QFile>
#include <QGraphicsScene>
#include <QString>
#include "gameObjects/tanks/AbstractTank.h"
#include "gameObjects/mapElements/AbstractMapElement.h"
#include "gameObjects/mapElements/LevelMap.h"

enum MapElements{
    MAP_GROUND,
    MAP_BRICK,
    MAP_CONCRETE,
    MAP_WATER,
    MAP_FOREST,

    MAP_HEADQUARTER,

    MAP_ENEMY_SPAWNER,
    MAP_PLAYER_SPAWNER
};

class MapProcessor : public QObject
{
    Q_OBJECT
public:
    explicit MapProcessor(QObject *parent = 0);
    ~MapProcessor();
    QGraphicsScene * createScene();
    void clearScene();
    QGraphicsScene * scene;
    void buildLevel(int levelNum);

    int getPlayerSpawnPointX();
    int getPlayerSpawnPointY();

    //!TODO: replace it with spawner lists
    int getEnemySpawnPointX(int pointNum);
    int getEnemySpawnPointY(int pointNum);

    static const int ENEMY_SPAWNERS = 3;

    AbstractTank * getEnemy();
    int getEnemiesRemain();
    int getTotalEnemies();

    static const int GRID_STEP = 16;
    static const int MAP_WIDTH_CHUNKS = 40;
    static const int MAP_HEIGHT_CHUNKS = 30;
    static const int MAP_WIDTH_PIXELS = MAP_WIDTH_CHUNKS * GRID_STEP;
    static const int MAP_HEIGHT_PIXELS = MAP_HEIGHT_CHUNKS * GRID_STEP;
    static const int GAME_WINDOW_WIDTH = 640;
    static const int GAME_WINDOW_HEIGHT = 480;
private:
    AbstractMapElement * getMapElement(char name);
    LevelMap * level;


    int playerSpawnPointX,playerSpawnPointY;

    int enemySpawnerX[ENEMY_SPAWNERS],
        enemySpawnerY[ENEMY_SPAWNERS];

    int enemiesRemain;

signals:

public slots:
};

#endif // MAPPROCESSOR_H
