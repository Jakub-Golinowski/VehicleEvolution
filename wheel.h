#ifndef WHEEL_H
#define WHEEL_H

#include <vector>
#include <Box2D/Box2D.h>

class Wheel
{
public:
    Wheel();
    Wheel(b2Vec2 WheelCenterPosition, float WheelRadius, float WheelAngularVelocity) :
            _WheelCenterPosition(WheelCenterPosition), _WheelRadius(WheelRadius), _WheelAngularVelocity(WheelAngularVelocity) {}

public:
    b2Vec2 _WheelCenterPosition;
    float _WheelRadius;
    float _WheelAngularVelocity;
};

#endif // WHEEL_H
