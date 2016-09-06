#ifndef PLAYER_H
#define PLAYER_H
#include "AbstractTank.h"

class Player : public AbstractTank{

    Q_OBJECT

public:
    Player(QGraphicsItem * parent=0);
    ~Player();
    //void move();
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent * event);
signals:
    void playerDestroyed();
};

#endif // PLAYER_H
