/*!
 * @file model.cpp
 * @author J.Golinowski, P. Sykulski
 * @date June 2017
 * @brief Model class implementation
 */

#include "model.h"


const float Model::TRACK_FIXTURE_DENSITY = 1.0;
const float Model::TRACK_FIXTURE_FRICTION = 0.3;
const float Model::TRACK_FIXTURE_RESTITUTION = 0.3;
const int16 Model::TRACK_FIXTURE_COLLISION_GROUP = 0;
const float Model::TRACK_BODY_CENTER_X_COORDINATE = -80.0;
const float Model::TRACK_BODY_CENTER_Y_COORDINATE = 0.0;
const float Model::TRACK_BODY_ANGLE_RADS = 0.0;
const float Model::TRACK_POINTS_SPACING = 40.0;
const int Model::TRACK_BODY_NUMBER_OF_FLAT_POINTS = 7;
const int Model::NUMBER_OF_TRACK_POINTS = 500;
const float Model::TRACK_Y_MIN_VALUE = -15.0;
const float Model::TRACK_Y_MAX_VALUE = 15.0;
const float Model::FITST_TRACK_POINT_X_COORDINATE = -150.0;
const float Model::CARBODY_FIXTURE_DENSITY = 1.0;
const float Model::CARBODY_FIXTURE_FRICTION = 0.3;
const float Model::CARBODY_FIXTURE_RESTITUTION = 0.3;
const int16 Model::CARBODY_FIXTURE_COLLISION_GROUP = -2;
const float Model::AXLE_SHAPE_RECT_SIDE_LENGTH = 1.0;
const float Model::AXLE_FIXTURE_DENSITY = 0.5;
const float Model::AXLE_FIXTURE_FRICTION = 3;
const float Model::AXLE_FIXTURE_RESTITUTION = 0.3;
const int16 Model::AXLE_FIXTURE_GROUP_INDEX = -2;
const float Model::WHEEL_FIXTURE_DENSITY = 1.0;
const float Model::WHEEL_FIXTURE_FRICTION = 0.3;
const float Model::WHEEL_FIXTURE_RESTITUTION = 0.3;
const int16 Model::WHEEL_FIXTURE_COLLISION_GROUP = -2;
const float Model::WHEEL_MOTOR_SPEED = 5;
const float Model::WHEEL_MAX_MOTOR_TORQUE = 1500;
const float Model::PRISMATIC_JOINT_LOWER_TRANSLATION = -1.0;
const float Model::PRISMATIC_JOINT_UPPER_TRANSLATION = 1.0;
const float32 Model::BOX2D_TIMESTEP = 1.0f/60.0f;
const int32 Model::BOX2D_VELOCITY_ITERATIONS = 6;
const int32 Model::BOX2D_POSITION_ITERATIONS = 2;
const float Model::WORLD_X_GRAVITY_VALUE = 0.0;
const float Model::WORLD_y_GRAVITY_VALUE = -10.0;

Model::Model()
    : box2dWorld_(b2Vec2(WORLD_X_GRAVITY_VALUE, WORLD_y_GRAVITY_VALUE))
{
}

b2Body* Model::addRectBody(float posX, float posY, b2BodyType bodyType, float angle_radians)
{
    b2BodyDef bodyDef;
    bodyDef.position.Set(posX,posY);
    bodyDef.type = bodyType;
    bodyDef.angle = angle_radians;

    return box2dWorld_.CreateBody(&bodyDef);
}

b2Fixture* Model::addGroundChainFixture(b2Body *parentBody, b2Vec2 * points, unsigned int pointsCount,
                                   float density, float friction, float restitution, int16 collisionGroup)
{
    groundBodyPtr_ = parentBody;
    b2ChainShape chainShape;
    chainShape.CreateChain(points,pointsCount);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &chainShape;
    fixtureDef.density = density;
    fixtureDef.friction = friction;
    fixtureDef.restitution = restitution;
    fixtureDef.filter.groupIndex = collisionGroup;
    return parentBody->CreateFixture(&fixtureDef);
}

void Model::addTrack()
{
    b2Body* trackBody = addRectBody(TRACK_BODY_CENTER_X_COORDINATE,TRACK_BODY_CENTER_Y_COORDINATE,b2_staticBody, TRACK_BODY_ANGLE_RADS);
    b2Vec2 points[NUMBER_OF_TRACK_POINTS];
    float x = FITST_TRACK_POINT_X_COORDINATE;
    // Set random number generation seed to 1, so the track appears as random, but doesn't change beetween instances
    std::default_random_engine trackGenerator;
    trackGenerator.seed(1);
    std::uniform_real_distribution<float> trackElevationDistribution(TRACK_Y_MIN_VALUE,TRACK_Y_MAX_VALUE);

    for(int i=0; i<NUMBER_OF_TRACK_POINTS; ++i){
        points[i].x = x;
        x += TRACK_POINTS_SPACING;
        float y;
        if( i > TRACK_BODY_NUMBER_OF_FLAT_POINTS){
            y = trackElevationDistribution(trackGenerator);
        }else
        {
            y = 0.0;
        }

        points[i].y = y;
    }

    addGroundChainFixture(trackBody, points, NUMBER_OF_TRACK_POINTS, TRACK_FIXTURE_DENSITY, TRACK_FIXTURE_FRICTION, TRACK_FIXTURE_RESTITUTION, TRACK_FIXTURE_COLLISION_GROUP);
}

b2Body* Model::addWheelBody(float posX, float posY)
{
    b2BodyDef bodyDef;
    bodyDef.position.Set(posX,posY);
    bodyDef.type = b2_dynamicBody;

    return box2dWorld_.CreateBody(&bodyDef);
}

b2Fixture* Model::addWheelFixture(b2Body* parentBody, float radius, float density, float friction, float restitution, int16 collisionGroup)
{
    b2CircleShape circleShape;
    circleShape.m_radius = radius;
    circleShape.m_p.Set(0,0); // Position relative to parent body position

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circleShape;
    fixtureDef.density = density;
    fixtureDef.friction = friction;
    fixtureDef.restitution = restitution;
    fixtureDef.filter.groupIndex = collisionGroup;

    return parentBody->CreateFixture(&fixtureDef);
}

b2Joint* Model::addRevoluteJoint(b2RevoluteJointDef* revoluteJointDef)
{
    return box2dWorld_.CreateJoint(dynamic_cast<b2JointDef*>(revoluteJointDef));
}

b2Body* Model::addCarFromChromosome(Chromosome chromosome, float posX, float posY)
{
    //CAR BODY DEFINITION
    b2BodyDef carbodyDef;
    carbodyDef.position.Set(posX,posY);
    carbodyDef.type = b2_dynamicBody;
    //Create CAR FIXTURE DEFINITION STRUCT
    b2FixtureDef fixtureDef;

    fixtureDef.density = CARBODY_FIXTURE_DENSITY;
    fixtureDef.friction =CARBODY_FIXTURE_FRICTION;
    fixtureDef.restitution = CARBODY_FIXTURE_RESTITUTION;
    fixtureDef.filter.groupIndex = CARBODY_FIXTURE_COLLISION_GROUP;
    //Create CAR BODY
    chromosomeCarBodyPtr_ = box2dWorld_.CreateBody(&carbodyDef);
    //CAR SHAPES
    b2Vec2 centerPoint(posX, posY);
    b2PolygonShape triangleShape;
    for(int i = 0; i < Chromosome::NUMBER_OF_VERTICES; ++i){
        triangleShape.Set(chromosome.CreateTriangleByIndexAndThridVertex(i,centerPoint).begin(),3);
        fixtureDef.shape = &triangleShape;
        chromosomeCarBodyPtr_->CreateFixture(&fixtureDef);
    }
    //Adding wheels
    int wheelBodyPtrIterator = 0;
    for(Wheel wheel : chromosome.getWheels())
    {
        //Axles
        // shape def
        b2PolygonShape axleShape;
        axleShape.SetAsBox(AXLE_SHAPE_RECT_SIDE_LENGTH,AXLE_SHAPE_RECT_SIDE_LENGTH);
        // fixture def
        b2FixtureDef axleFixture;
        axleFixture.density=AXLE_FIXTURE_DENSITY;
        axleFixture.friction=AXLE_FIXTURE_FRICTION;
        axleFixture.restitution=AXLE_FIXTURE_RESTITUTION;
        axleFixture.shape= &axleShape;
        axleFixture.filter.groupIndex=AXLE_FIXTURE_GROUP_INDEX;
        // body def
        b2BodyDef axleBodyDef;
        axleBodyDef.type = b2_dynamicBody;
        axleBodyDef.position.Set(2*posX + wheel.wheelCenterPosition_.x, 2*posY + wheel.wheelCenterPosition_.y);
        // Actual body
        b2Body* axleBody = box2dWorld_.CreateBody(&axleBodyDef);
        // Actual Fixture
        axleBody->CreateFixture(&axleFixture);
        //wheel
        b2Body* wheelBody = addWheelBody(2*posX + wheel.wheelCenterPosition_.x, 2*posY + wheel.wheelCenterPosition_.y);
        addWheelFixture(wheelBody, wheel.wheelRadius_, WHEEL_FIXTURE_DENSITY, WHEEL_FIXTURE_FRICTION, WHEEL_FIXTURE_RESTITUTION, WHEEL_FIXTURE_COLLISION_GROUP);
        //joint wheel to axle
        b2RevoluteJointDef wheelToAxleJointDef;
        wheelToAxleJointDef.Initialize(wheelBody,axleBody,wheelBody->GetWorldCenter());
        wheelToAxleJointDef.enableMotor=true;
        wheelToAxleJointDef.motorSpeed =WHEEL_MOTOR_SPEED;
        wheelToAxleJointDef.maxMotorTorque=WHEEL_MAX_MOTOR_TORQUE;
        addRevoluteJoint(&wheelToAxleJointDef);
        //joint axle to car
        b2PrismaticJointDef axlePrismaticJointDef;
        axlePrismaticJointDef.lowerTranslation=PRISMATIC_JOINT_LOWER_TRANSLATION;
        axlePrismaticJointDef.upperTranslation=PRISMATIC_JOINT_UPPER_TRANSLATION;
        axlePrismaticJointDef.enableLimit=true;
        axlePrismaticJointDef.enableMotor=true;
        //axle
        b2Vec2 axis(0,1);
        axlePrismaticJointDef.Initialize(chromosomeCarBodyPtr_, axleBody, axleBody->GetWorldCenter(), axis);
        box2dWorld_.CreateJoint(&axlePrismaticJointDef);

        WheelBodyPtrArray[wheelBodyPtrIterator] = wheelBody;
        ++wheelBodyPtrIterator;
    }

    return chromosomeCarBodyPtr_;
}

void Model::deleteCar()
{
    if(chromosomeCarBodyPtr_)
    {
        box2dWorld_.DestroyBody(chromosomeCarBodyPtr_);
        chromosomeCarBodyPtr_ = nullptr;
    }
}

void Model::simulate()
{
    box2dWorld_.Step(BOX2D_TIMESTEP, BOX2D_VELOCITY_ITERATIONS, BOX2D_POSITION_ITERATIONS);
}
