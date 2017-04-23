#include "model.h"

const float32 Model::BOX2D_TIMESTEP = 1.0f/60.0f;
const int32 Model::BOX2D_VELOCITY_ITERATIONS = 6;
const int32 Model::BOX2D_POSITION_ITERATIONS = 2;

Model::Model(float gravityX, float gravityY, QB2Draw * drawer)
    : _box2dWorld(b2Vec2(gravityX, gravityY))
{
    _box2dWorld.SetDebugDraw(drawer);
}

void Model::DrawModelData()
{
    _box2dWorld.DrawDebugData();
}

b2Body* Model::addBody(float posX, float posY, b2BodyType bodyType, float angle_radians)
{
    b2BodyDef bodyDef;
    bodyDef.position.Set(posX,posY);
    bodyDef.type = bodyType;
    bodyDef.angle = angle_radians;

    return _box2dWorld.CreateBody(&bodyDef);
}

b2Fixture* Model::addCircleFixture(b2Body *parentBody, float posX, float posY, float radius,
                                   float density, float friction, float restitution)
{
    b2CircleShape circleShape;
    circleShape.m_radius = radius;
    circleShape.m_p.Set(posX,posY); // Position relative to parent body position

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circleShape;
    fixtureDef.density = density;
    fixtureDef.friction = friction;
    fixtureDef.restitution = restitution;

    return parentBody->CreateFixture(&fixtureDef);
}

void Model::simulate()
{
    _box2dWorld.Step(BOX2D_TIMESTEP, BOX2D_VELOCITY_ITERATIONS, BOX2D_POSITION_ITERATIONS);
}
