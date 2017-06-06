/*!
 * @file model.h
 * @author J.Golinowski, P. Sykulski
 * @date June 2017
 * @brief Header file for Model class
 */

#ifndef MODEL_H
#define MODEL_H

#include <Box2D/Box2D.h>
#include "chromosome.h"


/*! Model is a wrapper for b2World. It isn't dependent on the View object.
 * \brief Model is a wrapper for b2World. It isn't dependent on the View object
 */
class Model
{
public:
    /*! Model constructor. It initializes the Box2D world with default gravity.
     * \brief Model constructor
     */
    Model();
    /*!
     * \brief wrapper for Box2D simulation step.
     */
    void simulate();
    /*!
     * \brief Adds track used to evaluate cars.
     */
    void addTrack();
    /*! Adds full car body from chromosome class. The car body is located in the coordinates given in the second and third argument.
     * \brief Adds full car body from chromosome class.
     * \param chromosome class that contains all the parameters needed to create a full car.
     * \param posX x coordinate of the car body center in Box2D world coordinate system.
     * \param posY y coordinate of the car body center in Box2D world coordinate system.
     * \return poiter on newly created car body.
     */
    b2Body* addCarFromChromosome(Chromosome chromosome, float posX, float posY);
    /*! Deletes the car body from the Box2D world. Sets the chromosomeCarBodyPtr_ to nullptr.
     * \brief Deletes the car body from the Box2D world.
     */
    void deleteCar();

    b2Body* chromosomeCarBodyPtr_;
    b2Body* groundBodyPtr_;
    std::array<b2Body*, Chromosome::NUMBER_OF_WHEELS> WheelBodyPtrArray;

private:
    /*!
     * \brief Adds rectangular body to Box2D world.
     * \param posX x coordinate of the body center in Box2D world coordinate system.
     * \param posY y coordinate of the body center in Box2D world coordinate system.
     * \param bodyType type of body (static/dynamic/kinematic).
     * \param angle_radians initial body angle (in radians).
     * \return pointer to newly created body.
     */
    b2Body* addRectBody(float posX, float posY, b2BodyType bodyType, float angle_radians);
    /*! Creates wheel body in Box2D world. The wheel body is centered in coordinates given as arguments
     * \brief Creates wheel body in Box2D world.
     * \param poxX x coordinate of the body center in Box2D world coordinate system.
     * \param posY y coordinate of the body center in Box2D world coordinate system.
     * \return pointer to newly created WheelBody
     */
    b2Body* addWheelBody(float poxX, float posY);
    /*!
     * \brief Creates ground chain fixture which is used as a track used to evaluate cars.
     * \param parentBody body to which ground chain shape will be added.
     * \param points pointer to an array of points that define chain shape.
     * \param pointsCount number of points in points array.
     * \param density physics parameter (mass/volume) used for box2D simulation.
     * \param friction physics parameter used for box2D simulation.
     * \param restitution physics paramtere used for box2D simulation
     * \param collisionGroup number denoting a group to which shape will belong. Shapes in the same group of negative value do not collide.
     * \return Chain shape fixture.
     */
    b2Fixture* addGroundChainFixture(b2Body *parentBody, b2Vec2 * points, unsigned int pointsCount,
                                       float density, float friction, float restitution, int16 collisionGroup);
    /*!
     * \brief Adds revolute joint to the car model.
     * \param revoluteJointDef a data structer that contains revolute joint parameters.
     * \return pointer to the newly created joint.
     */
    b2Joint* addRevoluteJoint(b2RevoluteJointDef* revoluteJointDef);
    /*!
     * \brief Adds wheel fixture that will be used to create a wheel as part od car.
     * \param parentBody body to which wheel fixture is attached (eg. car).
     * \param radius the radius of newly created wheel fixture.
     * \param density physics parameter (mass/volume) used for box2D simulation.
     * \param friction physics parameter used for box2D simulation.
     * \param restitution physics paramtere used for box2D simulation
     * \param collisionGroup number denoting a group to which shape will belong. Shapes in the same group of negative value do not collide.
     * \return Wheel Fixture
     */
    b2Fixture* addWheelFixture(b2Body* parentBody, float radius, float density, float friction, float restitution, int16 collisionGroup);

    static const float TRACK_FIXTURE_DENSITY;
    static const float TRACK_FIXTURE_FRICTION;
    static const float TRACK_FIXTURE_RESTITUTION;
    static const int16 TRACK_FIXTURE_COLLISION_GROUP;
    static const float TRACK_BODY_CENTER_X_COORDINATE;
    static const float TRACK_BODY_CENTER_Y_COORDINATE;
    static const float TRACK_BODY_ANGLE_RADS;
    static const float TRACK_POINTS_SPACING;
    static const int TRACK_BODY_NUMBER_OF_FLAT_POINTS;
    static const float TRACK_Y_MIN_VALUE;
    static const float TRACK_Y_MAX_VALUE;
    static const int NUMBER_OF_TRACK_POINTS;
    static const float FITST_TRACK_POINT_X_COORDINATE;
    static const float CARBODY_FIXTURE_DENSITY;
    static const float CARBODY_FIXTURE_FRICTION;
    static const float CARBODY_FIXTURE_RESTITUTION;
    static const int16 CARBODY_FIXTURE_COLLISION_GROUP;
    static const float AXLE_SHAPE_RECT_SIDE_LENGTH;
    static const float AXLE_FIXTURE_DENSITY;
    static const float AXLE_FIXTURE_FRICTION;
    static const float AXLE_FIXTURE_RESTITUTION;
    static const int16 AXLE_FIXTURE_GROUP_INDEX;
    static const float WHEEL_FIXTURE_DENSITY;
    static const float WHEEL_FIXTURE_FRICTION;
    static const float WHEEL_FIXTURE_RESTITUTION;
    static const int16 WHEEL_FIXTURE_COLLISION_GROUP;
    static const float WHEEL_MOTOR_SPEED;
    static const float WHEEL_MAX_MOTOR_TORQUE;
    static const float PRISMATIC_JOINT_LOWER_TRANSLATION;
    static const float PRISMATIC_JOINT_UPPER_TRANSLATION;
    static const float32 BOX2D_TIMESTEP;
    static const int32 BOX2D_VELOCITY_ITERATIONS;
    static const int32 BOX2D_POSITION_ITERATIONS;
    static const float WORLD_X_GRAVITY_VALUE;
    static const float WORLD_y_GRAVITY_VALUE;

    b2World box2dWorld_;
};

#endif // MODEL_H
