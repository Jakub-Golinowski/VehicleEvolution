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

void Model::addSimpleCarBody(float posX, float posY, float width, float height, float wheelRadius, float angularVelocity)
{
    b2Body* carBody = this->addRectBody(posX, posY, b2_dynamicBody, 0.0);
    this->addRectFixture(carBody, width/2, height/2, 2.0, 0.5, 0.99, -1);

    b2Body* leftWheelBody = this->addWheelBody(posX-width/2, posY-height/2,-angularVelocity);

    this->addWheelFixture(leftWheelBody,wheelRadius, 1.0, 0.3, 0.3, -1);

    b2Body* rightWheelBody = this->addWheelBody(posX+width/2, posY-height/2,-angularVelocity);
    this->addWheelFixture(rightWheelBody,wheelRadius, 1.0, 0.3, 0.3, -1);

    b2RevoluteJointDef leftjointDef;
    leftjointDef.Initialize(carBody, leftWheelBody, leftWheelBody->GetWorldCenter());

    this->addRevoluteJoint(&leftjointDef);

    b2RevoluteJointDef rightjointDef;
    rightjointDef.Initialize(carBody, rightWheelBody, rightWheelBody->GetWorldCenter());

    this->addRevoluteJoint(&rightjointDef);

}

void Model::addCarFromChromosome(Chromosome chromosome, float posX, float posY)
{
  /*  b2Vec2 vertices[chromosome.vertices_.size()];
    std::copy(chromosome.vertices_.begin(), chromosome.vertices_.end(), vertices);

    //Create car body
    b2BodyDef carbodyDef;
    carbodyDef.position.Set(posX,posY);
    carbodyDef.type = b2_dynamicBody;
    //Create car fixture
    b2PolygonShape polygonShape;
    polygonShape.Set(vertices, chromosome.vertices_.size());
    b2Body* carBody = _box2dWorld.CreateBody(&carbodyDef);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &polygonShape;
    fixtureDef.density = 1.0;
    fixtureDef.friction = 0.3;
    fixtureDef.restitution = 0.3;
    fixtureDef.filter.groupIndex = -2;

    carBody->CreateFixture(&fixtureDef);

    //Adding wheels
   for(Wheel wheel : chromosome.wheels_)
    {
        b2Body* wheelBody = addWheelBody(posX + wheel._WheelCenterPosition.x, posY + wheel._WheelCenterPosition.y, wheel._WheelAngularVelocity );
        this->addWheelFixture(wheelBody, wheel._WheelRadius, 1.0, 0.3, 0.3, -2);
        b2RevoluteJointDef jointDef;
        jointDef.Initialize(carBody, wheelBody, wheelBody->GetWorldCenter());
        this->addRevoluteJoint(&jointDef);
    }


*/

}

void Model::simulate()
{
    _box2dWorld.Step(BOX2D_TIMESTEP, BOX2D_VELOCITY_ITERATIONS, BOX2D_POSITION_ITERATIONS);
}
