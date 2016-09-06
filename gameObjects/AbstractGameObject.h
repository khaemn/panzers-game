#ifndef ABSTRACTGAMEOBJECT_H
#define ABSTRACTGAMEOBJECT_H

#include <QGraphicsPixmapItem>
#include <QObject>

const int OBJECT_MINIMUM_SPEED=1;

enum Direction{
    DIR_UP,
    DIR_DOWN,
    DIR_LEFT,
    DIR_RIGHT
};

class AbstractGameObject:public QObject, public QGraphicsPixmapItem{

    Q_OBJECT

public:
    AbstractGameObject(QGraphicsItem * parent=0);
    ~AbstractGameObject();

    bool isDead();
    void die();

protected:
    bool alive;
};

#endif // ABSTRACTGAMEOBJECT_H
