#ifndef ABSTRACTMAPELEMENT_H
#define ABSTRACTMAPELEMENT_H
#include "../AbstractGameObject.h"

class AbstractMapElement: public AbstractGameObject{

    Q_OBJECT

public:
    AbstractMapElement();
    ~AbstractMapElement();
    bool isDestructable();  //can be destroyed when bullet hits it
    bool isBlocking();  //if not, bullet will fly through
    bool isTraversable(); //if not, tanks can not raverse me
protected:
    bool iAmBlocking;
    bool iAmDestructable;
    bool iAmTraversable;
    // bool alive and method die() are inhertited from A.G.O.
};

#endif // ABSTRACTMAPELEMENT_H
