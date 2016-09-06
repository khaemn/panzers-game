#ifndef EXPLODEDTANK_H
#define EXPLODEDTANK_H
#include "AbstractTank.h"

class ExplodedTank : public AbstractTank
{
public:
    ExplodedTank();
    ~ExplodedTank();
    void move();
    void hurt(int damage);
private:
    static const int animationFrames = 7;
    int animationFrameCounter;

    QPixmap frames[8];
    void setPixmaps(QPixmap up1, QPixmap up2, QPixmap down1, QPixmap down2, QPixmap left1, QPixmap left2, QPixmap right1, QPixmap right2);
};

#endif // EXPLODEDTANK_H
