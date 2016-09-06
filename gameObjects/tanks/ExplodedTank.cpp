#include "ExplodedTank.h"

ExplodedTank::ExplodedTank(){
    setPixmaps(QPixmap(":/images/images/tanks/explosion/expl_1.png"),
               QPixmap(":/images/images/tanks/explosion/expl_2.png"),
               QPixmap(":/images/images/tanks/explosion/expl_3.png"),
               QPixmap(":/images/images/tanks/explosion/expl_4.png"),
               QPixmap(":/images/images/tanks/explosion/expl_5.png"),
               QPixmap(":/images/images/tanks/explosion/expl_6.png"),
               QPixmap(":/images/images/tanks/explosion/expl_7.png"),
               QPixmap(":/images/images/terrain/ground.png"));

    init();
    setPixmap(frames[0]);
    animationFrameCounter = 0;
}

ExplodedTank::~ExplodedTank(){

}

#define ANIMATION_FRAME_DURATION 4 //in game engine ticks
void ExplodedTank::move(){
    static int timeCounter = 0;
    if (++timeCounter > ANIMATION_FRAME_DURATION){
        timeCounter = 0;
        if (animationFrameCounter < animationFrames){
            setPixmap(frames[animationFrameCounter]);
            ++animationFrameCounter;
        }else{
            alive = false;
        }
    }
}

void ExplodedTank::setPixmaps(QPixmap frame1, QPixmap frame2,
                              QPixmap frame3, QPixmap frame4,
                              QPixmap frame5, QPixmap frame6,
                              QPixmap frame7, QPixmap frame8){
    frames[0] = frame1;
    frames[1] = frame2;
    frames[2] = frame3;
    frames[3] = frame4;
    frames[4] = frame5;
    frames[5] = frame6;
    frames[6] = frame7;
    frames[7] = frame8;
}

void ExplodedTank::hurt(int damage){
    //already exploding tank can not take any more damage
}
