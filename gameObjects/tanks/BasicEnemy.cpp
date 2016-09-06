#include "BasicEnemy.h"
//#include <QGraphicsScene>

BasicEnemy::BasicEnemy(){
    setPixmaps(QPixmap(":/images/images/tanks/basic/forward_1.png"),
               QPixmap(":/images/images/tanks/basic/forward_2.png"),
               QPixmap(":/images/images/tanks/basic/backward_1.png"),
               QPixmap(":/images/images/tanks/basic/backward_2.png"),
               QPixmap(":/images/images/tanks/basic/left_1.png"),
               QPixmap(":/images/images/tanks/basic/left_2.png"),
               QPixmap(":/images/images/tanks/basic/right_1.png"),
               QPixmap(":/images/images/tanks/basic/right_2.png"));
    init();
    health = 1;
    lastX = 0;
    lastY = 0;
    stepCount = 0;
}

BasicEnemy::~BasicEnemy(){
}

#define CONTINUOUS_MOVE_MAX 60
void BasicEnemy::think(){
    //!TODO:
    //!This AI implementation contains some experimental code,
    //!that must be refactored to achieve good readability,
    //!and also adding some parameters to set different behavior
    //!for different enemy types.
    static int continuousMovingCounter = 0;
    if(stuck){
        MovingState whereToMove = currentMovement;
        while (whereToMove == currentMovement){
            if (qrand()%5 == 1){
                whereToMove = MOVE_DOWN;
            }else{
                whereToMove = static_cast<MovingState>(qrand() % 4 + 1);
            }
        }
        stuck = false;
        currentMovement = whereToMove;
    }else{
        if (++continuousMovingCounter > CONTINUOUS_MOVE_MAX){
            if ((int)x() % 32 == 0 && (int)y() % 32 == 0){
                continuousMovingCounter = 0;
                //enemy always try to reach the map bottom, so
                //prbability of going down must be higher.
                if (qrand()%5 == 1){
                    currentMovement = MOVE_DOWN;
                }else{
                    currentMovement = static_cast<MovingState>(qrand() % 4 + 1);
                }
            }
        }
    }

    // 1/32 shooting probability in this step
    if (qrand()%32 == 1){
        if (cannonLoaded) shotNow = true;
    }
}
