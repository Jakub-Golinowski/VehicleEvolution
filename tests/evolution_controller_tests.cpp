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

BOOST_AUTO_TEST_SUITE_END()
