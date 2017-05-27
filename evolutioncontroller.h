#ifndef EVOLUTIONCONTROLLER_H
#define EVOLUTIONCONTROLLER_H

#include "chromosome.h"
#include "model.h"
#include "Box2D/Box2D.h"

class EvolutionController
{
public:
    EvolutionController();

private:

    static const unsigned long NUMBER_OF_WORLD_ITERATIONS;
    static const float CAR_INITIAL_X_POSITION;
    static const float CAR_INITIAL_Y_POSITION;
    typedef std::pair<Chromosome, float> ChromosomeAndFitness;

    void addTrackToModel( Model& model);

    void evaluateChromosome( unsigned int chromosomeIndex);
    void initializeRandomFirstGeneration();
    void selectionFromCurrentGeneration();
    void mutateCurrentGeneration();
    float calculateFitness(float distanceTravelled);
    Chromosome crossoverParentChromosomes( const Chromosome& firstParent, const Chromosome& secondParent);
    std::vector<ChromosomeAndFitness> currentGeneration_;

};

#endif // EVOLUTIONCONTROLLER_H
