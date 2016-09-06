#include "BrickMapElement.h"

BrickMapElement::BrickMapElement(){
    setPixmap(QPixmap(":/images/images/terrain/bricks.png"));
    iAmDestructable = true;
    iAmBlocking = true;
    iAmTraversable = false;
    alive = true;
}

BrickMapElement::~BrickMapElement(){

}

