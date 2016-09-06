#include "HeadQuarter.h"

HeadQuarter::HeadQuarter(){
    setPixmap(QPixmap(":/images/images/terrain/falcon_normal.png"));
    iAmDestructable = true;
    iAmBlocking = true;
    iAmTraversable = false;
    alive = true;
}

HeadQuarter::~HeadQuarter(){

}

