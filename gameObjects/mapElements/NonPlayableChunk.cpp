#include "NonPlayableChunk.h"

NonPlayableChunk::NonPlayableChunk(){
    setPixmap(QPixmap(":/images/images/terrain/grey_screen.png"));
    iAmDestructable = false;
    iAmBlocking = true;
    iAmTraversable = false;
    alive = true;
}

NonPlayableChunk::~NonPlayableChunk(){

}

