#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include <array>
#include <string>
#include <Box2D/Box2D.h>
#include "wheel.h"

//Wzór chromosomu w stringu:
//x_1 y_1 x_2 y_2 x_3 y_3 x_4 y_4 x_5 y_5 x_6 y_6 x_7 y_7 x_8 y_8 r_1 v_1 r_2 v_2

class Chromosome
{
public:
    Chromosome(){}

    Chromosome(std::string chromosomeString);

    static const int NUMBER_OF_WHEELS = 2;
    static const int NUMBER_OF_VERTICES = 8;
    static const int NUMBER_OF_TOKENS = 2*NUMBER_OF_VERTICES + 2*NUMBER_OF_WHEELS; //Each vertice and each wheel is described by 2 tokens.
    typedef std::array<std::string, NUMBER_OF_TOKENS> TokenizedChromosomeString_Type;

    TokenizedChromosomeString_Type TokenizeChromosomeString(std::string chromosomeString);

private:
    std::string chromosomeString_;
    TokenizedChromosomeString_Type chromosomeTokens_;

    std::array<Wheel, NUMBER_OF_WHEELS> wheels_;
    std::array<b2Vec2, NUMBER_OF_VERTICES> vertices_;



};

#endif // CHROMOSOME_H
