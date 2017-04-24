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

b2Body* Model::addRectBody(float posX, float posY, b2BodyType bodyType, float angle_radians)
{
    b2BodyDef bodyDef;
    bodyDef.position.Set(posX,posY);
    bodyDef.type = bodyType;
    bodyDef.angle = angle_radians;

    return _box2dWorld.CreateBody(&bodyDef);
}

b2Fixture* Model::addRectFixture(b2Body *parentBody, float half_width, float half_height,
                                   float density, float friction, float restitution, uint16 collisionGroup)
{
    b2PolygonShape polygonShape;
    polygonShape.SetAsBox(half_width, half_height); // Position relative to parent body position

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &polygonShape;
    fixtureDef.density = density;
    fixtureDef.friction = friction;
    fixtureDef.restitution = restitution;
    fixtureDef.filter.groupIndex = collisionGroup; //Ustawiam collision group na -1 -> fixtures z tej grupy nie zderzają się ze sobą.

    return parentBody->CreateFixture(&fixtureDef);
}

b2Body* Model::addWheelBody(float posX, float posY, float angularVelocity)
{
    b2BodyDef bodyDef;
    bodyDef.position.Set(posX,posY);
    bodyDef.type = b2_dynamicBody; //koło jest zawsze dynamic
    bodyDef.angularVelocity = angularVelocity;

    return _box2dWorld.CreateBody(&bodyDef);
}

b2Fixture* Model::addWheelFixture(b2Body* parentBody, float radius, float density, float friction, float restitution, uint16 collisionGroup)
{
    b2CircleShape circleShape;
    circleShape.m_radius = radius;
    circleShape.m_p.Set(0,0); // Position relative to parent body position

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circleShape;
    fixtureDef.density = density;
    fixtureDef.friction = friction;
    fixtureDef.restitution = restitution;
    fixtureDef.filter.groupIndex = collisionGroup; //Ustawiam collision group na -1 -> fixtures z tej grupy nie zderzają się ze sobą.

    return parentBody->CreateFixture(&fixtureDef);
}

b2Joint* Model::addRevoluteJoint(b2RevoluteJointDef* revoluteJointDef)
{
    return _box2dWorld.CreateJoint(dynamic_cast<b2JointDef*>(revoluteJointDef));
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

void Model::addSimpleCarBody(float posX, float posY, float width, float height, float angularVelocity)
{
    b2Body * carBody = this->addRectBody(posX, posY,b2_dynamicBody, 0.0f);
    b2Body * leftWheelBody = this->addWheelBody(posX, posY, 0.0f);
    //b2Body * rightWheelBody = this->addWheelBody(posX + width, posY - height, -5.0f);

    this->addRectFixture(carBody, width, height, 1.0f, 0.3f, 0.3f, 0);
    this->addCircleFixture(leftWheelBody, posX, posY, 10.0f, 1.0f, 0.3f, 0.3f);
    //this->addCircleFixture(rightWheelBody, posX + width, posY - height, 10.0f, 1.0f, 0.3f, 0.3f);

    b2RevoluteJointDef leftWheelJointDef;
    leftWheelJointDef.Initialize(carBody, leftWheelBody, carBody->GetWorldCenter());
   // leftWheelJointDef.enableMotor = true;
  //  leftWheelJointDef.maxMotorTorque = 100;

}







void Model::simulate()
{
    _box2dWorld.Step(BOX2D_TIMESTEP, BOX2D_VELOCITY_ITERATIONS, BOX2D_POSITION_ITERATIONS);
}
