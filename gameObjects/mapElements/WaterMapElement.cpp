#include "WaterMapElement.h"

WaterMapElement::WaterMapElement(){
    setPixmap(QPixmap(":/images/images/terrain/water.png"));
    iAmDestructable = false;
    iAmBlocking = false;
    iAmTraversable = false;
    alive = true;
}

WaterMapElement::~WaterMapElement(){

}

