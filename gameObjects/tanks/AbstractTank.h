#ifndef ABSTRACTTANK_H
#define ABSTRACTTANK_H

#include <QGraphicsItem>
#include "Bullet.h"
#include "../AbstractGameObject.h"

enum MovingState {
    MOVE_STOP,
    MOVE_UP,
    MOVE_DOWN,
    MOVE_LEFT,
    MOVE_RIGHT
};

class AbstractTank:public AbstractGameObject{

    Q_OBJECT

public:
    AbstractTank(QGraphicsItem * parent=0);
    ~AbstractTank();
    void setMovingStep(unsigned int);

    void setPixmaps(QPixmap up1, QPixmap up2, QPixmap down1, QPixmap down2,
                    QPixmap left1, QPixmap left2, QPixmap right1, QPixmap right2);
    void setGraphicScale(unsigned int scale);

    virtual void move();
    virtual void hurt(int damage);

public slots:
    void handleMyBullet(Bullet* bullet, QGraphicsItem *target);

signals:
    void myBulletHitSomething(Bullet* bullet, QGraphicsItem* target);

protected:
    void init();

    virtual void think();
    void handleStuck();

    void animateMovement(QPixmap *frame1, QPixmap *frame2);
    void fire();
    virtual void moveUp();
    virtual void moveDown();
    virtual void moveLeft();
    virtual void moveRight();
    bool stuck;

    static const unsigned int MOVING_SPEED = OBJECT_MINIMUM_SPEED*2;
    static const unsigned int INITIAL_HEALTH = 1;
    //static const unsigned int ADDITIONAL_MOVEMENT_PIXELS = 1;
    //Cannon muzzle coordinates in pixels when tank is directed up (default)
    //please check it corresponds to tank .png file pixel coordinates of cannon tip:
    static const int UP_MUZZLE_X = 14;
    static const int UP_MUZZLE_Y = -1; //muzzle must be located outside of player sprite to prevent self-shooting
    //Methods to calculate current muzzle location to fire the bullet properly:
    int getMuzzleX(int bulletWidth, int bulletHeight);
    int getMuzzleY(int bulletWidth, int bulletHeight);
    int myHeight;
    int myWidth;

    unsigned int movingStepPixels;
    unsigned int graphicScale;

    QPixmap up1;
    QPixmap up2;
    QPixmap down1;
    QPixmap down2;
    QPixmap left1;
    QPixmap left2;
    QPixmap right1;
    QPixmap right2;

    bool animationFlag;
    bool shotNow;
    bool cannonLoaded;

    int health;

    MovingState currentMovement;
    Direction shootingDirection;

    Bullet * myBullet;
};

#endif // ABSTRACTTANK_H
