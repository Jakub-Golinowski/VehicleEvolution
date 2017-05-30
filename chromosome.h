#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include <array>
#include <string>
#include <Box2D/Box2D.h>
#include <boost/tokenizer.hpp>
#include "wheel.h"

//Wzór chromosomu w stringu:
//x_1 y_1 x_2 y_2 x_3 y_3 x_4 y_4 x_5 y_5 x_6 y_6 x_7 y_7 x_8 y_8 r_1 v_1 r_2 v_2

class Chromosome
{
public:
    Chromosome(){}

    Chromosome(std::string chromosomeString);

    static const int32 NUMBER_OF_WHEELS = 2;
    static const int32 NUMBER_OF_VERTICES = 8;
    static const int32 NUMBER_OF_TOKENS = 2*NUMBER_OF_VERTICES + 2*NUMBER_OF_WHEELS; //Each vertice and each wheel is described by 2 tokens.
    typedef std::array<std::string, NUMBER_OF_TOKENS> TokenizedChromosomeString_t;
    typedef std::array<b2Vec2, NUMBER_OF_VERTICES> VerticesArray_t;
    typedef std::array<b2Vec2, 2> VerticesPair_t;
    typedef std::array<Wheel, NUMBER_OF_WHEELS> WheelsArray_t;
    typedef std::array<b2Vec2, 3> TriangleVertices_t;
    static const std::string CHROMOSOME_STRING_SEPARATOR;
    static const float VERTEX_PROXIMITI_LIMIT;

    TokenizedChromosomeString_t TokenizeChromosomeString(std::string chromosomeString);
    VerticesArray_t GetVerticesArray();
    VerticesPair_t GetVerticesPairByIndex(int32 index);
    TriangleVertices_t CreateTriangleByIndexAndThridVertex(int32 index, b2Vec2 thirdVertex);
    bool MoveAwayIfTooClose(b2Vec2& vertex1, b2Vec2& vertex2);
    WheelsArray_t getWheels();
    TokenizedChromosomeString_t chromosomeTokens_;
    std::string chromosomeString_;

private:
    WheelsArray_t wheels_;
    VerticesArray_t vertices_;



};

#endif // CHROMOSOME_H
