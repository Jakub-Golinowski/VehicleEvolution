#include <boost/test/unit_test.hpp>

#include "../chromosome.h"

BOOST_AUTO_TEST_SUITE(CHROMOSOME_CLASS_TEST_SUITE)

BOOST_AUTO_TEST_CASE(CHROMOSOME_CONSTRUCTOR_TEST)
{
    std::string chromosomeString = "-20.0 5.0 -15.0 10.0 18.0 20.0 30.0 10.0 40.0 -8.0 25.0 -15.0 -10.0 -20.0 -30.0 -10.0 15.0 5 15.0 6";
    Chromosome chromosome(chromosomeString);
    Chromosome::WheelsArray_t testedChromosomeWheels = chromosome.getWheels();

    Chromosome::VerticesArray_t vertices = {b2Vec2(-20.0, 5.0), b2Vec2(-15.0,10.0),b2Vec2(18.0,20.0),
                                            b2Vec2(30.0,10.0), b2Vec2(40.0,-8.0), b2Vec2(25.0,-15.0),
                                            b2Vec2(-10.0,-20.0), b2Vec2(-30.0,-10.0)};
    Chromosome::WheelsArray_t wheels = {Wheel(vertices[5], 15.0, 5), Wheel(vertices[6], 15.0, 6)};

    BOOST_CHECK(vertices == chromosome.GetVerticesArray());
    BOOST_CHECK(testedChromosomeWheels[0].wheelCenterPosition_ == wheels[0].wheelCenterPosition_);
    BOOST_CHECK(testedChromosomeWheels[1].wheelCenterPosition_ == wheels[1].wheelCenterPosition_);
    BOOST_CHECK(testedChromosomeWheels[0].wheelRadius_ == wheels[0].wheelRadius_);
    BOOST_CHECK(testedChromosomeWheels[1].wheelRadius_ == wheels[1].wheelRadius_);
    BOOST_CHECK(testedChromosomeWheels[0].vertexIndex_ == wheels[0].vertexIndex_);
    BOOST_CHECK(testedChromosomeWheels[1].vertexIndex_ == wheels[1].vertexIndex_);

}

BOOST_AUTO_TEST_SUITE_END()
