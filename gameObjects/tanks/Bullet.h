#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <QGraphicsItem>
#include "../AbstractGameObject.h"

class Bullet: public AbstractGameObject {

    Q_OBJECT

public:
    Bullet(QGraphicsItem *parent=0);
    void setDirection(Direction direction);
private:
    static const unsigned int PROJECTILE_SPEED = OBJECT_MINIMUM_SPEED*6;

    void handleCollision();
    void handleMovement();
    //! make inherited from virtual AGO
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    Direction direction;

public slots:
    void move();

signals:
    void hitTarget(Bullet* me, QGraphicsItem* target);
};

#endif // PROJECTILE_H
