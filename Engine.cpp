#include <QGraphicsScene>
#include <QList>
#include <QTime>
#include <QMessageBox>
#include <typeinfo>

#include "Engine.h"
#include "gameObjects/tanks/Bullet.h"
#include "gameObjects/tanks/Player.h"
#include "gameObjects/tanks/ExplodedTank.h"
#include "gameObjects/mapElements/AbstractMapElement.h"
#include "gameObjects/mapElements/HeadQuarter.h"

Engine::Engine(QWidget *parent){
    scene = NULL;
    playerLivesRemain = PLAYER_LIVES;
    enemyKills = 0;
    currentLevel = 1;
}

Engine::~Engine(){

}

void Engine::run(){
    qsrand(QTime::currentTime().second());
    init();
    startGame();
}

void Engine::startGame(){
    buildMap();
    createTextItems();
    spawnPlayer();
    spawnEnemy();
    startClock();
}

void Engine::levelCompleted(){
    victory();
}

void Engine::init(){
    mapProcessor = new MapProcessor();
    scene = mapProcessor->createScene();

    //Setting the scene created by MapProcessor as Engine own scene
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(scene->width(),scene->height());

    gameClock = new QTimer();
    connect(gameClock,SIGNAL(timeout()),this,SLOT(gameTick()));
}

void Engine::buildMap(){
    try{
        mapProcessor->buildLevel(currentLevel);
    }catch(...){
        QMessageBox::critical(this,"Map creating error","Can not load map file.");
        exit(-1);
    }
}

void Engine::createTextItems(){
    gameInfo = new QGraphicsTextItem();
    gameInfo->setDefaultTextColor(Qt::white);
    gameInfo->setFont(QFont("times",14));
    gameInfo->setPlainText(QString("Lives: ") + QString::number(playerLivesRemain) +
                           QString("  Enemies left: ") + QString::number(mapProcessor->getEnemiesRemain()));
    gameInfo->setPos(0,-3);
    scene->addItem(gameInfo);
}

void Engine::spawnPlayer(){
    Player* player = new Player();
    int x = mapProcessor->getPlayerSpawnPointX();
    int y = mapProcessor->getPlayerSpawnPointY();
    player->setPos(x,y);
    // add the player to the scene
    scene->addItem(player);
    // make the player focusable and set it to be the current focus
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    connect(player,SIGNAL(myBulletHitSomething(Bullet*,QGraphicsItem*)),this,SLOT(handleBulletHit(Bullet*,QGraphicsItem*)));
    connect(player,SIGNAL(playerDestroyed()),this,SLOT(playerDestroyed()));
    this->player = (AbstractTank*) player;
}

void Engine::spawnEnemy(){
    AbstractTank* enemy = mapProcessor->getEnemy();
    if (enemy==NULL){
        return;
    }

    int spawnerNum = qrand()% MapProcessor::ENEMY_SPAWNERS;
    int x = mapProcessor->getEnemySpawnPointX(spawnerNum);
    int y = mapProcessor->getEnemySpawnPointY(spawnerNum);
    enemy->setPos(x,y);
    scene->addItem(enemy);
    connect(enemy,SIGNAL(myBulletHitSomething(Bullet*,QGraphicsItem*)),this,SLOT(handleBulletHit(Bullet*,QGraphicsItem*)));
}

void Engine::checkForEnemyRespawn(){
    static unsigned int enemyRespawnCounter=0;
    if (++enemyRespawnCounter > (ENEMY_SPAWN_PERIOD/GAME_TIMEFRAME)){
        enemyRespawnCounter = 0;
        if (mapProcessor->getEnemiesRemain() > 0){
            spawnEnemy();
        }
    }
}

void Engine::startClock(){
    gameClock->start(GAME_TIMEFRAME);
}

void Engine::gameTick(){
    cleanCorpses();
    checkForEnemyRespawn();
    updateGameInfo();
    sendMoveSignals();
}

void Engine::cleanCorpses(){
    QList<QGraphicsItem *> objects = scene->items();
    for (int i = 0; i<objects.size(); i++){
        if (typeid(*objects.at(i)) != typeid(QGraphicsTextItem)){
            AbstractGameObject * object = dynamic_cast<AbstractGameObject*>(objects.at(i));
            bool isItTank = object->inherits("AbstractTank");
            bool isItMapElement = object->inherits("AbstractMapElement");
            bool isItBullet = (typeid(*(objects.at(i))) == typeid(Bullet));
            if (isItTank){
                AbstractTank * tank = dynamic_cast<AbstractTank*>(objects.at(i));
                if (tank->isDead()){
                    if (typeid(*tank) != typeid(ExplodedTank)){
                        int explosionX = (int)objects.at(i)->x();
                        int explosionY = (int)objects.at(i)->y();
                        AbstractTank * explosion = new ExplodedTank();
                        explosion->setPos(explosionX,explosionY);
                        scene->addItem(explosion);
                    }
                    scene->removeItem(objects.at(i));
                    delete objects.at(i);
                }
            }else if (isItBullet){
                Bullet * bullet = dynamic_cast<Bullet*>(objects.at(i));
                if (bullet->isDead()){
                    scene->removeItem(objects.at(i));
                    delete objects.at(i);
                }
            }else if (isItMapElement){
                AbstractMapElement * element = dynamic_cast<AbstractMapElement*>(objects.at(i));
                if (element->isDead()){
                    scene->removeItem(objects.at(i));
                    delete (objects.at(i));
                }
            }
        }
    }
}

void Engine::sendMoveSignals(){
    QList<QGraphicsItem *> objects = scene->items();
    for (int i = 0; i<objects.size(); i++){
        if (typeid(*objects.at(i)) != typeid(QGraphicsTextItem)){
            AbstractGameObject * object = dynamic_cast<AbstractGameObject *>(objects.at(i));
            bool isItTank = object->inherits("AbstractTank");
            bool isItBullet = typeid(*(objects.at(i))) == typeid(Bullet);
            if (isItTank){
                AbstractTank * tank = dynamic_cast<AbstractTank*>(objects.at(i));
                tank->move();
            }
            if (isItBullet){
                Bullet * bullet = dynamic_cast<Bullet*>(objects.at(i));
                bullet->move();
            }
        }
    }
}

void Engine::updateGameInfo(){
    gameInfo->setPlainText(QString("Lives: ") + QString::number(playerLivesRemain) +
                           QString("  Enemies left: ") + QString::number(mapProcessor->getEnemiesRemain()));
}

#define DEFAULT_BULLET_DAMAGE   1
void Engine::handleBulletHit(Bullet *bullet, QGraphicsItem *target){
    if (typeid(*target) == typeid(QGraphicsTextItem)) return;

    AbstractGameObject* item = dynamic_cast<AbstractGameObject*>(target);
    bool isTank = item->inherits("AbstractTank");
    bool isMapElement = item->inherits("AbstractMapElement");
    if (isTank){
        AbstractTank * tank = dynamic_cast<AbstractTank*>(target);
        tank->hurt(DEFAULT_BULLET_DAMAGE);
        if (tank->isDead()){
            if (typeid(*tank) != typeid(Player)){
                if (++enemyKills >= mapProcessor->getTotalEnemies()){
                    levelCompleted();
                }
            }else{
                playerDestroyed();
            }
        }
        bullet->die();
    }else if(isMapElement){
        AbstractMapElement * element = dynamic_cast<AbstractMapElement*>(target);
        if (element->isDestructable()){
            element->die();
            bullet->die();
            if (typeid(*element) == typeid(HeadQuarter)){
                gameOver();
            }
        }else if (element->isBlocking()){
            bullet->die();
        }
    }
}

void Engine::playerDestroyed(){
    if (--playerLivesRemain > 0){
        spawnPlayer();
    }else{
        gameOver();
    }
}

void Engine::gameOver(){
    gameClock->stop();

    QGraphicsTextItem * text = new QGraphicsTextItem();
    text->setPlainText(QString("GAME OVER"));
    text->setDefaultTextColor(Qt::white);
    text->setFont(QFont("times",32));
    int x = (int)(scene->width()/2 - text->boundingRect().width()/2);
    int y = (int)(scene->height()/2 - text->boundingRect().height()/2);
    text->setPos(x,y);
    scene->addItem(text);
}

void Engine::victory(){
    gameClock->stop();

    QGraphicsTextItem * text = new QGraphicsTextItem();
    text->setPlainText(QString("YOU WIN!"));
    text->setDefaultTextColor(Qt::white);
    text->setFont(QFont("times",32));
    int x = (int)(scene->width()/2 - text->boundingRect().width()/2);
    int y = (int)(scene->height()/2 - text->boundingRect().height()/2);
    text->setPos(x,y);
    scene->addItem(text);
}
