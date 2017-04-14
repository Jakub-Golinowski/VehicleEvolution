#ifndef SIMOBJECT_H
#define SIMOBJECT_H

#include <QGraphicsItem>
#include <Box2D/Box2D.h>

class SimObject
{
public:
    SimObject();

private:
    std::shared_ptr<b2Body> body;
    std::shared_ptr<QGraphicsItem> item;
};

#endif // SIMOBJECT_H
