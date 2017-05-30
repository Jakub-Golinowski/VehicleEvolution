#ifndef EVOLUTIONCONTROLLER_H
#define EVOLUTIONCONTROLLER_H

#include "chromosome.h"
#include "view.h"
#include "model.h"
#include "controller.h"
#include "Box2D/Box2D.h"

class EvolutionController
{
public:
    EvolutionController();
    ~EvolutionController();
    void addChromosome(Chromosome newChromosome);
    void evaluateChromosome( unsigned int chromosomeIndex);
    void visualizeChromosome(unsigned int chromosomeIndex);
    void initializeRandomFirstGeneration();

private:

    static const unsigned long NUMBER_OF_WORLD_ITERATIONS;
    static const float CAR_INITIAL_X_POSITION;
    static const float CAR_INITIAL_Y_POSITION;
    static const unsigned long GENERATION_SIZE;
    static const float CAR_MAXIMUM_ABSOLUTE_COORDINATE_VALUE;
    static const float WHEEL_MINIMAL_RADIUS;
    static const float WHEEL_MAXIMAL_RADIUS;

    typedef std::pair<Chromosome, float> ChromosomeAndFitness;
    std::vector<ChromosomeAndFitness> currentGeneration_;


    void addTrackToModel( Model& model);
    std::string generateChromosomeString(std::default_random_engine &generator);
    void selectionFromCurrentGeneration();
    void mutateCurrentGeneration();
    float calculateFitness(float distanceTravelled);
    Chromosome crossoverParentChromosomes( const Chromosome& firstParent, const Chromosome& secondParent);

    // Visualisation
    Controller *controller;
    Model *model;
    View *view;
    QB2Draw *drawer;


};

#endif // EVOLUTIONCONTROLLER_H
