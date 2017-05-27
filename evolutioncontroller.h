#ifndef EVOLUTIONCONTROLLER_H
#define EVOLUTIONCONTROLLER_H

#include "chromosome.h"

class EvolutionController
{
public:
    EvolutionController();



private:
    typedef std::pair<Chromosome, float> ChromosomeAndScore;

    void evaluateChromosome( unsigned int chromosomeIndex);
    void initializeRandomFirstGeneration();
    void selectionFromCurrentGeneration();
    void mutateCurrentGeneration();
    Chromosome crossoverParentChromosomes( const Chromosome& firstParent, const Chromosome& secondParent);
    std::vector<ChromosomeAndScore> currentGeneration_;

};

#endif // EVOLUTIONCONTROLLER_H
