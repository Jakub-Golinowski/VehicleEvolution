#ifndef SIMRECT_H
#define SIMRECT_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <Box2D/Box2D.h>

#include "simobject.h"

class SimRect : public SimObject
{
public:
    SimRect( std::shared_ptr<b2World> parentWorld, std::shared_ptr<QGraphicsScene> parentScene,
             unsigned long width, unsigned long height, unsigned long posX, unsigned long posY);
};

#endif // SIMRECT_H
