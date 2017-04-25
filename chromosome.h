#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include <vector>
#include <Box2D/Box2D.h>
#include "wheel.h"

class Chromosome
{
public:
    Chromosome(){}
    Chromosome(const std::vector<Wheel>& wheels, const std::vector<b2Vec2> vertices) :
        _wheels(wheels), _vertices(vertices){}


public:
    int _numberOfWheels;
    std::vector<Wheel> _wheels;

    int _numberOfVertices;
    std::vector<b2Vec2> _vertices;

};

#endif // CHROMOSOME_H
