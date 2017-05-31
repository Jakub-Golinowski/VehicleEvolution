#ifndef EVOLUTIONCONTROLLER_H
#define EVOLUTIONCONTROLLER_H

#include "chromosome.h"
#include "view.h"
#include "model.h"
#include "controller.h"
#include "Box2D/Box2D.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <boost/lexical_cast.hpp>
#include <regex>


class EvolutionController
{
public:
    EvolutionController();
    ~EvolutionController();
    void addChromosome(Chromosome newChromosome, float Fitness = 0.0);
    void evolution(unsigned long numberOfGenerations);
    void evaluateCurrentGeneration();
    void evaluateChromosome( unsigned int chromosomeIndex);
    void visualizeChromosomeFromCurrentGeneration(unsigned int chromosomeIndex);
    void visualizeSelectedChromosome(unsigned int chromosomeIndex);
    void initializeRandomFirstGeneration();
    void selectionFromCurrentGeneration();    
    std::array<Chromosome, 2> crossoverParentChromosomes( const Chromosome& firstParent, const Chromosome& secondParent,
                                                          unsigned int firsCrossoverPoint, unsigned int secondCrossoverPoint);
    typedef std::pair<Chromosome, float> ChromosomeAndFitness;
    std::vector<ChromosomeAndFitness> currentGeneration_;
    std::vector<ChromosomeAndFitness> selectedFromCurrentGeneration;

    void saveCurrentGenerationToFile();
    void ReadGenerationFromFile();


private:

    static const unsigned long NUMBER_OF_WORLD_ITERATIONS;
    static const float CAR_INITIAL_X_POSITION;
    static const float CAR_INITIAL_Y_POSITION;
    static const unsigned long GENERATION_SIZE;
    static const unsigned long NUMBER_OF_SELECTED_CHROMOSOMES;
    static const float CAR_MAXIMUM_ABSOLUTE_COORDINATE_VALUE;
    static const float WHEEL_MINIMAL_RADIUS;
    static const float WHEEL_MAXIMAL_RADIUS;
    static const float MUTATION_DECISION_THRESHOLD;

    std::default_random_engine randomNumberGenerator;

    void visualizeChromosome(Chromosome chromosome);
    void addTrackToModel( Model& model);
    std::string generateChromosomeString();
    void mutateChromosome(Chromosome &chromosome);
    void mutateCurrentGeneration();
    float calculateFitness(float distanceTravelled);
    // Visualisation
    Controller *controller;
    Model *model;
    View *view;
    QB2Draw *drawer;


};

#endif // EVOLUTIONCONTROLLER_H
