#ifndef SIMOBJECT_H
#define SIMOBJECT_H

#include <QGraphicsItem>
#include <Box2D/Box2D.h>

class SimObject
{
public:
    SimObject(){}

    b2Body  * body;
    QGraphicsItem * item;
};

#endif // SIMOBJECT_H
