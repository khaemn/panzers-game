#include "AbstractGameObject.h"

AbstractGameObject::AbstractGameObject(QGraphicsItem *parent){
    alive = true;
}

AbstractGameObject::~AbstractGameObject(){

}

bool AbstractGameObject::isDead(){
    return !alive;
}

void AbstractGameObject::die(){
    alive = false;
}

