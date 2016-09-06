#include "ArmoredEnemy.h"

ArmoredEnemy::ArmoredEnemy(){
    setPixmaps(QPixmap(":/images/images/tanks/armor/forward_1.png"),
               QPixmap(":/images/images/tanks/armor/forward_2.png"),
               QPixmap(":/images/images/tanks/armor/backward_1.png"),
               QPixmap(":/images/images/tanks/armor/backward_2.png"),
               QPixmap(":/images/images/tanks/armor/left_1.png"),
               QPixmap(":/images/images/tanks/armor/left_2.png"),
               QPixmap(":/images/images/tanks/armor/right_1.png"),
               QPixmap(":/images/images/tanks/armor/right_2.png"));
    init();
    health = 3;
    lastX = 0;
    lastY = 0;
    stepCount = 0;
}

ArmoredEnemy::~ArmoredEnemy(){

}

