#ifndef MODEL_H
#define MODEL_H

#include <Box2D/Box2D.h>

class Model
{
public:
    Model(float gravityX, float gravityY);

private:

    static const float32 BOX2D_TIMESTEP;
    static const int32 BOX2D_VELOCITY_ITERATIONS;
    static const int32 BOX2D_POSITION_ITERATIONS;

    b2World _box2dWorld;

    b2Body* addBody(float posX, float posY, b2BodyType bodyType, float angle_degrees);

    b2Fixture* addCircleFixture(b2Body *parentBody, float posX, float posY, float radius,
                                       float density, float friction, float restitution);

    void simulate();


};

#endif // MODEL_H
