#ifndef SIMRECT_H
#define SIMRECT_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <Box2D/Box2D.h>

#include "simworld.h"
#include "simobject.h"

class SimRect : public SimObject
{
public:
    SimRect( SimWorld * simworld,
             float width, float height,
             float posX, float posY, float density
             , float friction);
};

#endif // SIMRECT_H
