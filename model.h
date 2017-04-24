#ifndef MODEL_H
#define MODEL_H

#include <Box2D/Box2D.h>
#include "qb2draw.h"



// Model is basically a wrappe for b2World. It isn't dependend on the View object

class Model
{
public:
    Model(float gravityX, float gravityY, QB2Draw * drawer);

    void DrawModelData();

    void simulate();

    b2Body* addBody(float posX, float posY, b2BodyType bodyType, float angle_degrees);
    b2Body* addWheelBody(float poxX, float posY, float angularVelocity);
    b2Body* addRectBody(float posX, float posY, b2BodyType bodyType, float angle_radians);
    void addSimpleCarBody(float posX, float posY, float width, float height, float angularVelocity);


    b2Fixture* addCircleFixture(b2Body *parentBody, float posX, float posY, float radius,
                                       float density, float friction, float restitution);

    b2Fixture* addRectFixture(b2Body *parentBody, float posX, float posY, float width, float height,
                                       float density, float friction, float restitution);

private:

    static const float32 BOX2D_TIMESTEP;
    static const int32 BOX2D_VELOCITY_ITERATIONS;
    static const int32 BOX2D_POSITION_ITERATIONS;

    b2World _box2dWorld;







};

#endif // MODEL_H
