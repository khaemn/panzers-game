#include "LevelMap.h"
#include <QString>

LevelMap::LevelMap(){
    currentEnemy = 0;
    totalEnemies = 0;

    mapFile = new QFile();
}

LevelMap::~LevelMap(){

}

char LevelMap::getElementNameXY(int x, int y){
    if (x>=0 && x < MAP_WIDTH && y >= 0 && y <MAP_HEIGHT)
        return map[y][x];
    else
        return ' ';
}

#define MAX_FILE_LINE_LENGTH 255
void LevelMap::loadLevel(int levelNum){
    QString filename;
    filename.append(DEFAULT_LEVEL_FILENAME);
    filename.append(QString::number(levelNum));
    filename.append(DEFAULT_LEVEL_EXTENSION);
    try{
        mapFile->setFileName(filename);
        if (!mapFile->open(QFile::ReadOnly)){
            throw -1; //Can not open file
        }
        mapFile->seek(0);
        int y=0;
        char lineFromFile[MAX_FILE_LINE_LENGTH];
        while (!mapFile->atEnd() && y < MAP_HEIGHT){
            mapFile->readLine(lineFromFile, MAX_FILE_LINE_LENGTH);
            for (int x = 0; x< MAP_WIDTH; x++){
                map[y][x] = lineFromFile[x];
            }
            y++;
        }
        //The last line of a map file contains enemy list, where
        //b - basic enemy, f - fast enemy, a - armoured enemy
        //there could be up to MAP_WIDTH enemies per level
        if (!mapFile->atEnd()){
            mapFile->readLine(lineFromFile, MAX_FILE_LINE_LENGTH);
            for (int num = 0; num< MAP_WIDTH; num++){
                if (lineFromFile[num] == 'b' || lineFromFile[num] == 'a'){
                    enemies[num] = lineFromFile[num];
                    ++totalEnemies;
                }else{
                    enemies[num] = ' ';
                }
            }
        }
        mapFile->close();
    }catch(...){
        //Loading default enemy count
        totalEnemies = 14;
        throw -1;
    }
}

char LevelMap::getNextEnemyName(){
    char name = ' ';
    if (currentEnemy < totalEnemies){
        name = enemies[currentEnemy];
        ++currentEnemy;
    }
    return name;
}

int LevelMap::getEnemiesRemain(){
    return totalEnemies - currentEnemy;
}

int LevelMap::getTotalEnemies(){
    return totalEnemies;
}
