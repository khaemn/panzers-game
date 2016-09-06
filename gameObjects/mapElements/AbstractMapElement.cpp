#include "AbstractMapElement.h"

AbstractMapElement::AbstractMapElement(){
    setPixmap(QPixmap(":/images/images/terrain/concrete.png"));
    iAmDestructable = false;
    iAmBlocking = true;
    iAmTraversable = true;
    alive = true;
}

AbstractMapElement::~AbstractMapElement(){

}

bool AbstractMapElement::isDestructable(){
    return iAmDestructable;
}

bool AbstractMapElement::isBlocking(){
    return iAmBlocking;
}

bool AbstractMapElement::isTraversable(){
    return iAmTraversable;
}
