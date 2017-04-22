#include "simrect.h"


SimRect::SimRect(SimWorld * simworld,
                 float width, float height,
                 float posX, float posY, float density,
                 float friction, int body_type,
                 float angle_degrees)
{
    b2BodyDef bodyDef;
    bodyDef.position.Set(posX, posY);
    bodyDef.type = (b2BodyType)body_type;
    bodyDef.angle = angle_degrees*M_PI/180.0f;
    body = simworld->getWorld()->CreateBody(&bodyDef);

    b2PolygonShape boxShape;
    boxShape.SetAsBox(width/2, height/2);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &boxShape;
    fixtureDef.density = density;
    fixtureDef.friction = friction;
    body->CreateFixture(&fixtureDef);



    item = new QGraphicsRectItem;
    static_cast<QGraphicsRectItem*>(item)->setRect(-width*SimWorld::BOX2D_QT_SCALE_FACTOR/2,
                  -height*SimWorld::BOX2D_QT_SCALE_FACTOR/2,
                  width*SimWorld::BOX2D_QT_SCALE_FACTOR,
                  height*SimWorld::BOX2D_QT_SCALE_FACTOR);
    simworld->getScene()->addItem(item);


    simworld->addObject(this);



}
