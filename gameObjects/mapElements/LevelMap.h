#ifndef PRIMITIVEMAP_H
#define PRIMITIVEMAP_H
#include <QFile>

#define DEFAULT_LEVEL_FILENAME "level"
#define DEFAULT_LEVEL_EXTENSION ".map"


class LevelMap{

public:
    LevelMap();
    ~LevelMap();

    void loadLevel(int levelNum);
    char getElementNameXY(int x, int y);
    char getNextEnemyName();
    int getEnemiesRemain();
    int getTotalEnemies();

private:
    static const char MAP_WIDTH=40;
    static const char MAP_HEIGHT=30;
    static const char MAX_ENEMIES = MAP_WIDTH; //because it is useful to keep enemy list as map line

    char map[MAP_HEIGHT][MAP_WIDTH];
    char enemies[MAP_WIDTH];
    int  totalEnemies;
    int  currentEnemy;

    QFile * mapFile;
};

#endif // PRIMITIVEMAP_H
