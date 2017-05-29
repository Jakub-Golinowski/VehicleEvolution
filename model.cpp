#include "model.h"

const float32 Model::BOX2D_TIMESTEP = 1.0f/60.0f;
const int32 Model::BOX2D_VELOCITY_ITERATIONS = 6;
const int32 Model::BOX2D_POSITION_ITERATIONS = 2;
b2Body* chromosomeCarBodyPtr = nullptr;
std::array<b2Body*, Chromosome::NUMBER_OF_WHEELS> WheelBodyPtrArray;

Model::Model(float gravityX, float gravityY, QB2Draw * drawer)
    : _box2dWorld(b2Vec2(gravityX, gravityY)), drawer_(drawer)
{
    _box2dWorld.SetDebugDraw(drawer);
}

Model::Model(float gravityX, float gravityY)
    : _box2dWorld(b2Vec2(gravityX, gravityY))
{
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

b2Fixture* Model::addGrounChainShape(b2Body *parentBody, b2Vec2 * points, unsigned int pointsCount,
                                   float density, float friction, float restitution, uint16 collisionGroup)
{
    groundBodyPtr = parentBody;
    b2ChainShape chainShape;
    chainShape.CreateChain(points,pointsCount);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &chainShape;
    fixtureDef.density = density;
    fixtureDef.friction = friction;
    fixtureDef.restitution = restitution;
    fixtureDef.filter.groupIndex = collisionGroup; //Ustawiam collision group na -1 -> fixtures z tej grupy nie zderzają się ze sobą.
    return parentBody->CreateFixture(&fixtureDef);
}

b2Body* Model::addWheelBody(float posX, float posY)
{
    b2BodyDef bodyDef;
    bodyDef.position.Set(posX,posY);
    bodyDef.type = b2_dynamicBody; //koło jest zawsze dynamic

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

    b2Body* leftWheelBody = this->addWheelBody(posX-width/2, posY-height/2);

    this->addWheelFixture(leftWheelBody,wheelRadius, 1.0, 0.3, 0.3, -1);

    b2Body* rightWheelBody = this->addWheelBody(posX+width/2, posY-height/2);
    this->addWheelFixture(rightWheelBody,wheelRadius, 1.0, 0.3, 0.3, -1);

    b2RevoluteJointDef leftjointDef;
    leftjointDef.enableMotor = true;
    leftjointDef.maxMotorTorque=10000;
    leftjointDef.motorSpeed = -1000;
    leftjointDef.Initialize(carBody, leftWheelBody, leftWheelBody->GetWorldCenter());

    this->addRevoluteJoint(&leftjointDef);

    b2RevoluteJointDef rightjointDef;
    rightjointDef.enableMotor = true;
    rightjointDef.maxMotorTorque=10000;
    rightjointDef.motorSpeed = -1000;
    rightjointDef.Initialize(carBody, rightWheelBody, rightWheelBody->GetWorldCenter());

    this->addRevoluteJoint(&rightjointDef);

}

b2Body* Model::addCarFromChromosome(Chromosome chromosome, float posX, float posY)
{
    //CAR BODY DEFINITION
    b2BodyDef carbodyDef;
    carbodyDef.position.Set(posX,posY);
    carbodyDef.type = b2_dynamicBody;
    //Create CAR FIXTURE DEFINITION STRUCT
    b2FixtureDef fixtureDef;
    fixtureDef.density = 1.0;
    fixtureDef.friction = 0.3;
    fixtureDef.restitution = 0.3;
    fixtureDef.filter.groupIndex = -2;
    //Create CAR BODY
    chromosomeCarBodyPtr = _box2dWorld.CreateBody(&carbodyDef);
    //CAR SHAPES
    b2Vec2 centerPoint(posX, posY);
    b2PolygonShape triangleShape;
    for(int i = 0; i < Chromosome::NUMBER_OF_VERTICES; ++i){
        //TODO -> known issue: w wypadku za małych odstępów pomiędzy punktami Box2D skleja je w jeden i jest błąd bo próubuje utworzyć trójkąt z mniej niż 3 wierzchołków
        triangleShape.Set(chromosome.CreateTriangleByIndexAndThridVertex(i,centerPoint).begin(),3);
        fixtureDef.shape = &triangleShape;
        chromosomeCarBodyPtr->CreateFixture(&fixtureDef);
    }
    //Adding wheels
    int wheelBodyPtrIterator = 0;
    for(Wheel wheel : chromosome.getWheels())
    {
        //TODO znaleźć błąd -> dlaczego tutaj muszę mnożyć razy 2 a nie po prostu brać posX i posY
        //Axles
        // shape def
        b2PolygonShape axleShape;
        axleShape.SetAsBox(1,1);
        // fixture def
        b2FixtureDef axleFixture;
        axleFixture.density=0.5;
        axleFixture.friction=3;
        axleFixture.restitution=0.3;
        axleFixture.shape= &axleShape;
        axleFixture.filter.groupIndex=-2;
        // body def
        b2BodyDef axleBodyDef;
        axleBodyDef.type = b2_dynamicBody;
        axleBodyDef.position.Set(2*posX + wheel.wheelCenterPosition_.x, 2*posY + wheel.wheelCenterPosition_.y);
        // Actual body
        b2Body* axleBody = _box2dWorld.CreateBody(&axleBodyDef);
        // Actual Fixture
        axleBody->CreateFixture(&axleFixture);
        //wheel
        b2Body* wheelBody = addWheelBody(2*posX + wheel.wheelCenterPosition_.x, 2*posY + wheel.wheelCenterPosition_.y);
        addWheelFixture(wheelBody, wheel.wheelRadius_, 1.0, 0.3, 0.3, -2);
        //joint wheel to axle
        b2RevoluteJointDef wheelToAxleJointDef;
        wheelToAxleJointDef.Initialize(wheelBody,axleBody,wheelBody->GetWorldCenter());
        wheelToAxleJointDef.enableMotor=true;
        wheelToAxleJointDef.motorSpeed = 5;
        wheelToAxleJointDef.maxMotorTorque=1000;
        b2Joint* wheelToAxleJoint = addRevoluteJoint(&wheelToAxleJointDef);
        //joint axle to car
        b2PrismaticJointDef axlePrismaticJointDef;
        axlePrismaticJointDef.lowerTranslation=-1;
        axlePrismaticJointDef.upperTranslation=1;
        axlePrismaticJointDef.enableLimit=true;
        axlePrismaticJointDef.enableMotor=true;
        //axle
        b2Vec2 axis(0,1);
        axlePrismaticJointDef.Initialize(chromosomeCarBodyPtr, axleBody, axleBody->GetWorldCenter(), axis);
        b2Joint* axleToCarJoint= _box2dWorld.CreateJoint(&axlePrismaticJointDef);

        WheelBodyPtrArray[wheelBodyPtrIterator] = wheelBody;
        ++wheelBodyPtrIterator;
    }

    return chromosomeCarBodyPtr;
}

void Model::simulate()
{
    _box2dWorld.Step(BOX2D_TIMESTEP, BOX2D_VELOCITY_ITERATIONS, BOX2D_POSITION_ITERATIONS);
}
