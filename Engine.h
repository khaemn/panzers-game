#ifndef ENGINE_H
#define ENGINE_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QTimer>
#include <QLabel>
#include "gameObjects/tanks/AbstractTank.h"
#include <QGraphicsTextItem>
#include "MapProcessor.h"

class Engine: public QGraphicsView
{

    Q_OBJECT

public:
    Engine(QWidget * parent=0);
    ~Engine();

    void run();

    QGraphicsScene * scene;

public slots:
    void handleBulletHit(Bullet* bullet, QGraphicsItem *target); //!todo: what about terrain elements?
    void playerDestroyed();
    void gameOver();
private:
    void init();
    void startGame();
    void buildMap();
    void createTextItems();
    void spawnPlayer();
    void spawnEnemy();
    void checkForEnemyRespawn();
    void startClock();

    void handleObjectCollisions();
    void sendMoveSignals();
    void cleanCorpses();
    void updateGameInfo();

    void levelCompleted();
    void victory();

    static const unsigned int GAME_TIMEFRAME = 20; //milliseconds
    static const unsigned int PLAYER_LIVES = 3;

    AbstractTank * player;
    QTimer * gameClock;
    MapProcessor * mapProcessor;
    QGraphicsTextItem * gameInfo;
    static const unsigned int ENEMY_SPAWN_PERIOD = 5000; //milliseconds

    int playerLivesRemain;
    int enemyKills;

    unsigned int currentLevel;
    static const unsigned int TOTAL_LEVELS=2;

private slots:
    void gameTick();

};

#endif // ENGINE_H
