#include "Bullet.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <typeinfo>

Bullet::Bullet(QGraphicsItem *parent){
    direction = DIR_UP;
    alive = true;
}

void Bullet::setDirection(Direction direction){
    this->direction = direction;
    if (direction == DIR_UP)
        setPixmap(QPixmap(":/images/images/tanks/projectile/forward.png"));
    else if (direction == DIR_DOWN)
        setPixmap(QPixmap(":/images/images/tanks/projectile/backward.png"));
    else if (direction == DIR_LEFT)
        setPixmap(QPixmap(":/images/images/tanks/projectile/left.png"));
    else if (direction == DIR_RIGHT)
        setPixmap(QPixmap(":/images/images/tanks/projectile/right.png"));
}

void Bullet::move(){
    handleCollision();
    handleMovement();
}

void Bullet::handleCollision(){
    // get a list of all the items currently colliding with this Projectile
    QList<QGraphicsItem *> targets = collidingItems();

    // if one of the colliding items is an Enemy, destroy both the Projectile and the enemy
    for (int i = 0, n = targets.size(); i < n; ++i){
        AbstractGameObject* target = (AbstractGameObject*)targets[i];
        bool isTargetCorrect = target->inherits("AbstractGameObject");
        if (isTargetCorrect){
            emit hitTarget(this,targets[i]);
            return;
        }
    }
}
void Bullet::handleMovement(){
    if (direction == DIR_UP){
        moveUp();
    }
    if (direction == DIR_DOWN){
        moveDown();
    }
    if (direction == DIR_LEFT){
        moveLeft();
    }
    if (direction == DIR_RIGHT){
        moveRight();
    }
}

void Bullet::moveUp(){
    if (pos().y() > 0){
        setPos(x() , y()-PROJECTILE_SPEED);
    }else die();
}

void Bullet::moveDown(){
    if (pos().y() + pixmap().height() < scene()->height()){
        setPos(x(),y()+PROJECTILE_SPEED);
    }else die();
}

void Bullet::moveLeft(){
    if (pos().x() > 0) {
        setPos(x()-PROJECTILE_SPEED,y());
    }else die();
}

void Bullet::moveRight(){
    if (pos().x() + pixmap().width() < scene()->width()){
        setPos(x()+PROJECTILE_SPEED,y());
    }else die();
}
