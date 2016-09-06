#include "Player.h"
#include <QKeyEvent>
#include "gameObjects/AbstractGameObject.h"
#include "gameObjects/mapElements/AbstractMapElement.h"

Player::Player(QGraphicsItem *parent){
    setPixmaps(QPixmap(":/images/images/tanks/player/forward_1.png"),
               QPixmap(":/images/images/tanks/player/forward_2.png"),
               QPixmap(":/images/images/tanks/player/backward_1.png"),
               QPixmap(":/images/images/tanks/player/backward_2.png"),
               QPixmap(":/images/images/tanks/player/left_1.png"),
               QPixmap(":/images/images/tanks/player/left_2.png"),
               QPixmap(":/images/images/tanks/player/right_1.png"),
               QPixmap(":/images/images/tanks/player/right_2.png"));
    init();
    setShapeMode(MaskShape);
    health = 1;
    currentMovement = MOVE_STOP;
    shootingDirection = DIR_UP;
}

Player::~Player(){
    //emit playerDestroyed();
}
void Player::keyPressEvent(QKeyEvent *event){

    if (event->key() == Qt::Key_Up){
        currentMovement = MOVE_UP;
    }
    if (event->key() == Qt::Key_Down){
        currentMovement = MOVE_DOWN;
    }
    if (event->key() == Qt::Key_Left){
        currentMovement = MOVE_LEFT;
    }
    if (event->key() == Qt::Key_Right){
        currentMovement = MOVE_RIGHT;
    }
    if (event->key() == Qt::Key_Space){
        if (!event->isAutoRepeat() && cannonLoaded){
            shotNow = true;
        }
    }
    event->accept();
}

void Player::keyReleaseEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_Up){
        if (currentMovement == MOVE_UP){
            currentMovement = MOVE_STOP;
        }
    }
    if (event->key() == Qt::Key_Down){
        if (currentMovement == MOVE_DOWN){
            currentMovement = MOVE_STOP;
        }
    }
    if (event->key() == Qt::Key_Left){
        if (currentMovement == MOVE_LEFT){
            currentMovement = MOVE_STOP;
        }
    }
    if (event->key() == Qt::Key_Right){
        if (currentMovement == MOVE_RIGHT){
            currentMovement = MOVE_STOP;
        }
    }
    event->accept();
}
