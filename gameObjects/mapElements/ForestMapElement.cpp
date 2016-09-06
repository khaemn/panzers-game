#include "ForestMapElement.h"

ForestMapElement::ForestMapElement(){
    setPixmap(QPixmap(":/images/images/terrain/camouflage.png"));
    iAmDestructable = false;
    iAmBlocking = false;
    iAmTraversable = true;
    alive = true;
    setZValue(99); //to cover all other items beneath
}

ForestMapElement::~ForestMapElement(){

}

