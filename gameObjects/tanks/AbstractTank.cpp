#include "AbstractTank.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include "gameObjects/mapElements/AbstractMapElement.h"

AbstractTank::AbstractTank(QGraphicsItem *parent){
    setPixmaps(QPixmap(":/images/images/tanks/basic/forward_1.png"),
               QPixmap(":/images/images/tanks/basic/forward_2.png"),
               QPixmap(":/images/images/tanks/basic/backward_1.png"),
               QPixmap(":/images/images/tanks/basic/backward_2.png"),
               QPixmap(":/images/images/tanks/basic/left_1.png"),
               QPixmap(":/images/images/tanks/basic/left_2.png"),
               QPixmap(":/images/images/tanks/basic/right_1.png"),
               QPixmap(":/images/images/tanks/basic/right_2.png"));
    init();
    //setShapeMode(BoundingRectShape);
}

void AbstractTank::init(){
    setMovingStep(MOVING_SPEED);
    graphicScale = 1;
    setScale(graphicScale);
    setPixmap(up1);
    myHeight = pixmap().height()*graphicScale;
    myWidth = pixmap().width()*graphicScale;


    alive = true;
    health = INITIAL_HEALTH;
    currentMovement = MOVE_DOWN;
    shootingDirection = DIR_DOWN;
    shotNow = false;
    cannonLoaded = true;
    animationFlag = false;
    stuck = false;
}

AbstractTank::~AbstractTank(){
}

void AbstractTank::setMovingStep(unsigned int step){
    movingStepPixels = step;
}

void AbstractTank::moveUp(){
    shootingDirection = DIR_UP;
    animateMovement(&up1,&up2);
    if (pos().y() > 0)
        setPos(x(),y()-movingStepPixels);
}

void AbstractTank::moveDown(){
    shootingDirection = DIR_DOWN;
    animateMovement(&down1,&down2);
    if (pos().y() + myHeight < scene()->height())
        setPos(x(),y()+movingStepPixels);
}

void AbstractTank::moveLeft(){
    shootingDirection = DIR_LEFT;
    animateMovement(&left1,&left2);
    if (pos().x() > 0)
        setPos(x()-movingStepPixels,y());
}

void AbstractTank::moveRight(){
    shootingDirection = DIR_RIGHT;
    animateMovement(&right1,&right2);
    if (pos().x() + myWidth < scene()->width())
        setPos(x()+movingStepPixels,y());
}

void AbstractTank::animateMovement(QPixmap *frame1, QPixmap *frame2){
    if (animationFlag){
        setPixmap(*frame1);
    }else{
        setPixmap(*frame2);
    }
    setScale(graphicScale);
    animationFlag = !animationFlag;
}

void AbstractTank::setPixmaps(QPixmap up1, QPixmap up2,
                              QPixmap down1, QPixmap down2,
                              QPixmap left1, QPixmap left2,
                              QPixmap right1, QPixmap right2){
    this->up1 = up1;
    this->up2 = up2;
    this->down1 = down1;
    this->down2 = down2;
    this->left1 = left1;
    this->left2 = left2;
    this->right1 = right1;
    this->right2 = right2;
}

void AbstractTank::setGraphicScale(unsigned int scale){
    this->graphicScale = scale;
}

void AbstractTank::move(){
    think();

    QList<QGraphicsItem *> colliding = collidingItems();
    int initialCollides = colliding.size();

    if (currentMovement == MOVE_UP){
        moveUp();
    }
    if (currentMovement == MOVE_DOWN){
        moveDown();
    }
    if (currentMovement == MOVE_LEFT){
        moveLeft();
    }
    if (currentMovement == MOVE_RIGHT){
        moveRight();
    }

    colliding = collidingItems();

    if (colliding.size() > initialCollides){
        for (int i =0; i< colliding.size(); i++){
            AbstractGameObject * object = dynamic_cast<AbstractGameObject*>(colliding.at(i));
            if (object->inherits("AbstractMapElement")){
                AbstractMapElement * mapElement = dynamic_cast<AbstractMapElement*>(object);
                if (!mapElement->isTraversable()){
                    handleStuck();
                }
            }else if (object->inherits("AbstractTank")){
                handleStuck();
            }
        }

    }

    if (shotNow && cannonLoaded) {
        fire();
    }
}

void AbstractTank::fire(){
    shotNow = false;
    myBullet = new Bullet(); //will be deleted by game engine later.
    myBullet->setDirection(this->shootingDirection);
    int bulletWidth = myBullet->pixmap().width();
    int bulletHeight = myBullet->pixmap().height();
    int muzzleX = getMuzzleX(bulletWidth,bulletHeight);
    int muzzleY = getMuzzleY(bulletWidth,bulletHeight);
    myBullet->setPos(muzzleX,muzzleY);
    scene()->addItem(myBullet);
    connect(myBullet,SIGNAL(hitTarget(Bullet*,QGraphicsItem*)),this,SLOT(handleMyBullet(Bullet*,QGraphicsItem*)));
    cannonLoaded = false;
}

int AbstractTank::getMuzzleX(int bulletWidth, int bulletHeight){
    switch(shootingDirection){
    case DIR_UP:
    case DIR_DOWN:
        return x() + UP_MUZZLE_X - (bulletWidth>>1);
    case DIR_LEFT:
        return x() + UP_MUZZLE_Y - bulletHeight;
    case DIR_RIGHT:
        return x() - UP_MUZZLE_Y + myWidth;
    }
    return 0;
}

int AbstractTank::getMuzzleY(int bulletWidth, int bulletHeight){
    switch(shootingDirection){
    case DIR_UP:
        return y() - bulletHeight + UP_MUZZLE_Y;
    case DIR_DOWN:
        return y() + bulletHeight + UP_MUZZLE_Y + myHeight;
    case DIR_LEFT:
    case DIR_RIGHT:
        return y() + UP_MUZZLE_X - (bulletWidth>>1);
    }
    return 0;
}

void AbstractTank::handleMyBullet(Bullet *bullet, QGraphicsItem *target){
    cannonLoaded = true;
    emit myBulletHitSomething(bullet,target);
}

void AbstractTank::hurt(int damage){
    health -= damage;
    if (health <= 0){
        alive = false;
    }
}

void AbstractTank::think(){
    //Abstract tank can not think, it is abstraction :)
    //Only real enemies will implement this method.
}

void AbstractTank::handleStuck(){
    //Stuck handling contains shifting tank to reverse direction to prevent
    //penetration into map object or another tank, and also detecting in
    //what direction was this stuck detected.
    stuck = true;
    if (currentMovement == MOVE_UP){
        setPos(x(),y()+(movingStepPixels));
    }
    if (currentMovement == MOVE_DOWN){
        setPos(x(),y()-(movingStepPixels));
    }
    if (currentMovement == MOVE_LEFT){
        setPos(x()+(movingStepPixels),y());
    }
    if (currentMovement == MOVE_RIGHT){
        setPos(x()-(movingStepPixels),y());
    }
}
