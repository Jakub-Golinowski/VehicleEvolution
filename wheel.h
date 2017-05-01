#ifndef WHEEL_H
#define WHEEL_H

#include <vector>
#include <Box2D/Box2D.h>

class Wheel
{
public:
    Wheel();
    Wheel(b2Vec2 WheelCenterPosition, float WheelRadius, int vertexIndex) :
            wheelCenterPosition_(WheelCenterPosition), wheelRadius_(WheelRadius), vertexIndex_(vertexIndex) {}

public:
    b2Vec2 wheelCenterPosition_;
    float wheelRadius_;
    int vertexIndex_;
};

#endif // WHEEL_H
