#include <boost/test/unit_test.hpp>

#include "../evolutioncontroller.h"
BOOST_AUTO_TEST_SUITE(EVOLUTION_CONTROLLER_CLASS_TEST_SUITE)



BOOST_AUTO_TEST_CASE(EVALUATION_TEST)
{
    EvolutionController evolutionController;
    std::string chromosomeString = "-20.0 5.0 -15.0 10.0 18.0 20.0 30.0 10.0 40.0 -8.0 25.0 -15.0 -10.0 -20.0 -30.0 -10.0 15.0 5 15.0 6";
    Chromosome chromosome(chromosomeString);
    evolutionController.addChromosome(chromosome);
    BOOST_TEST_MESSAGE("Chromosome evaluation starting");
    evolutionController.evaluateChromosome(0);
    float fitness =  evolutionController.currentGeneration_.at(0).second;
    BOOST_CHECK( fitness > 0.0);
    BOOST_TEST_MESSAGE( "Chromosome fitness : " << fitness);
}

BOOST_AUTO_TEST_CASE(CROSSOVER_TEST)
{
    EvolutionController evolutionController;
    std::string chromosomeStringFirstParent = "-20.0 5.0 -15.0 10.0 18.0 20.0 30.0 10.0 40.0 -8.0 25.0 -15.0 -10.0 -20.0 -30.0 -10.0 15.0 5 15.0 6";
    std::string chromosomeStringSecondParent = "-4.0 1.0 -3.0 2.0 3.6 5.0 6.0 2.0 8.0 -1.6 5.0 -3.0 -2.0 -4.0 -6.0 -2.0 3.0 5 3.0 6";
    Chromosome firstParent(chromosomeStringFirstParent);
    Chromosome secondParent(chromosomeStringSecondParent);
    std::array<Chromosome,2> output = evolutionController.crossoverParentChromosomes(firstParent, secondParent, 5, 3);
    BOOST_MESSAGE("First child : " + output.at(0).chromosomeString_);
    BOOST_MESSAGE("Second child: " + output.at(1).chromosomeString_);
    BOOST_CHECK(output.at(0).chromosomeString_ == "-20.0 5.0 -15.0 2.0 3.6 5.0 30.0 10.0 40.0 -8.0 25.0 -15.0 -10.0 -20.0 -30.0 -10.0 15.0 5 15.0 6 ");
    BOOST_CHECK(output.at(1).chromosomeString_ == "-4.0 1.0 -3.0 10.0 18.0 20.0 6.0 2.0 8.0 -1.6 5.0 -3.0 -2.0 -4.0 -6.0 -2.0 3.0 5 3.0 6 ");
}

BOOST_AUTO_TEST_SUITE_END()
