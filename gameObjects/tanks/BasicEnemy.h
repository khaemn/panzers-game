#ifndef BASICENEMY_H
#define BASICENEMY_H

#include "AbstractTank.h"

class BasicEnemy : public AbstractTank
{
public:
    BasicEnemy();
    ~BasicEnemy();
protected:
    void think(); //decide where to move and shoot now or not

    int currentX, currentY, lastX, lastY;
    int stepCount;
};

#endif // BASICENEMY_H
