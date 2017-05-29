#ifndef MODEL_H
#define MODEL_H

#include <Box2D/Box2D.h>
#include "qb2draw.h"
#include "chromosome.h"



// Model is basically a wrappe for b2World. It isn't dependent on the View object

class Model
{
public:
    Model(float gravityX, float gravityY, QB2Draw * drawer);

    Model(float gravityX, float gravityY);

    void DrawModelData();

    void simulate();

    b2Body* addBody(float posX, float posY, b2BodyType bodyType, float angle_degrees);

    b2Body* addRectBody(float posX, float posY, b2BodyType bodyType, float angle_radians);
    b2Body* addGroundBody(b2Vec2* vertices, unsigned int verticesCount);
    b2Fixture* addRectFixture(b2Body *parentBody, float width, float height,
                                       float density, float friction, float restitution, uint16 collisionGroup);
    b2Fixture* addGrounChainShape(b2Body *parentBody, b2Vec2 * points, unsigned int pointsCount,
                                       float density, float friction, float restitution, uint16 collisionGroup);

    b2Body* addWheelBody(float poxX, float posY);
    b2Fixture* addWheelFixture(b2Body* parentBody, float radius, float density, float friction, float restitution, uint16 collisionGroup);
    b2Fixture* addCircleFixture(b2Body *parentBody, float posX, float posY, float radius,
                                       float density, float friction, float restitution);

    b2Joint* addRevoluteJoint(b2RevoluteJointDef* revoluteJointDef);

    void addSimpleCarBody(float posX, float posY, float width, float height, float wheelRadius, float angularVelocity);

    b2Body* addCarFromChromosome(Chromosome chromosome, float posX, float posY);

    b2Body* chromosomeCarBodyPtr;
    b2Body* groundBodyPtr;
    std::array<b2Body*, Chromosome::NUMBER_OF_WHEELS> WheelBodyPtrArray;

private:
    static const float32 BOX2D_TIMESTEP;
    static const int32 BOX2D_VELOCITY_ITERATIONS;
    static const int32 BOX2D_POSITION_ITERATIONS;

    b2World _box2dWorld;
    QB2Draw* drawer_;
};

#endif // MODEL_H
