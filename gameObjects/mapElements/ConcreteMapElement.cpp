#include "ConcreteMapElement.h"

ConcreteMapElement::ConcreteMapElement(){
    setPixmap(QPixmap(":/images/images/terrain/concrete.png"));
    iAmDestructable = false;
    iAmBlocking = true;
    iAmTraversable = false;
    alive = true;
}

ConcreteMapElement::~ConcreteMapElement(){

}

