/*!
 * @file wheel.h
 * @author J.Golinowski, P. Sykulski
 * @date June 2017
 * @brief Header file for Wheel class (there is no .cpp file)
 */

#ifndef WHEEL_H
#define WHEEL_H

#include <vector>
#include <Box2D/Box2D.h>

/*!
 * \brief The Wheel class is a collection of parameters required to fully describe a wheel for the purpose vehicle evolution.
 */

class Wheel
{
public:
    /*!
     * \brief Wheel constructor. Initializes all the fields with given values.
     * \param WheelCenterPosition the 2D vector describing a point in Box2D world that will be the center of the wheel.
     * \param WheelRadius real number describing wheel radius value
     * \param vertexIndex integer number denoting index of vertex to which the wheel will be attached.
     */
    Wheel(b2Vec2 WheelCenterPosition, float WheelRadius, int vertexIndex) :
            wheelCenterPosition_(WheelCenterPosition), wheelRadius_(WheelRadius), vertexIndex_(vertexIndex) {}
    /*! Empty wheel constructor. Required for std::array operations.
     * \brief Empty wheel constructor.
     */
    Wheel(){}

    b2Vec2 wheelCenterPosition_;
    float wheelRadius_;
    int vertexIndex_;
};

#endif // WHEEL_H
