/*!
 * @file evolutioncontroller.h
 * @author J.Golinowski, P. Sykulski
 * @date June 2017
 * @brief Header file for EvolutionController class
 */

#ifndef EVOLUTIONCONTROLLER_H
#define EVOLUTIONCONTROLLER_H

#include "chromosome.h"
#include "view.h"
#include "model.h"
#include "controller.h"
#include "Box2D/Box2D.h"
#include <iostream>


/*!
 * \brief The EvolutionController class controls and performs the genetic algorithm
 */

class EvolutionController
{
public:
    /*! EvolutionController construct that initializes model_ to nullptr
     * \brief EvolutionController constructor.
     */
    EvolutionController();
    /*! EvolutionController destructor that destroys model_
     * \brief EvolutionController destructor
     */
    ~EvolutionController();
    /*! Adds new chromosome to currentGeneration_ vector and sets it's fitness
     * \brief Adds new chromosome to currentGeneration_ vector
     * \param new chromosome object
     * \param new chromosome fitness value (default 0.0)
     */
    void addChromosome(Chromosome newChromosome, float Fitness = 0.0);
    /*! Performs given amount of iterations of the genetic algorithm
     * \brief Performs genetic algorithm
     * \param Number of iterations of the genetic algorithm to be performed
     */
    void evolution(unsigned long numberOfGenerations);
    /*! Performs evaluation of all the chromosomes in the currentGeneration_ vector
     * \brief Performs evaluation for the current generation
     */
    void evaluateCurrentGeneration();
    /*! Evaluates the selected chromosome in currentGeneration_ vector
     * \brief Evalutes the selected chromosome
     * \param Index of the chromosome to be evaluated
     */
    void evaluateChromosome( unsigned int chromosomeIndex);
    /*! Fills the currentGeneration_ vector with randomly generated chromosomes
     * \brief Generates random chromosomes
    */
    void initializeRandomFirstGeneration();
    /*! Performs selection algorithm on the currentGeneration_ vector
     * \brief Performs the selection algorithm
     */
    void selectionFromCurrentGeneration();
    /*! Return chromosome from the currentGeneration_ vector
     * \brief Returns chromosome
     * \param Index of the chromosome to be returned
     * \return Selected chromosome
     */
    Chromosome getChromosome(unsigned int chromosomeIndex);
    typedef std::pair<Chromosome, float> ChromosomeAndFitness;
    std::vector<ChromosomeAndFitness> currentGeneration_;
    std::vector<ChromosomeAndFitness> selectedFromCurrentGeneration;

    static const float CAR_INITIAL_X_POSITION;
    static const float CAR_INITIAL_Y_POSITION;
    static const unsigned long GENERATION_SIZE;

#ifndef UNIT_TEST
    private:
#endif
    static const unsigned long NUMBER_OF_WORLD_ITERATIONS;
    static const unsigned long NUMBER_OF_SELECTED_CHROMOSOMES;
    static const float CAR_MAXIMUM_ABSOLUTE_COORDINATE_VALUE;
    static const float WHEEL_MINIMAL_RADIUS;
    static const float WHEEL_MAXIMAL_RADIUS;
    static const float MUTATION_DECISION_THRESHOLD;

    std::default_random_engine randomNumberGenerator_;
    Model *model_;

    /*! Performs crossover between two parent chromosomes and given points in chromosomes
     * \brief Performs crossover
     * \param First parent
     * \param Second parent
     * \param First crossover point
     * \param Second crossover point
     * \return Array of 2 chromosomes created by crossover
     */
    std::array<Chromosome, 2> crossoverParentChromosomes( const Chromosome& firstParent, const Chromosome& secondParent,
                                                          unsigned int firsCrossoverPoint, unsigned int secondCrossoverPoint);
    /*! Generates random chromosome string
     * \brief Generates random chromosome string
     * \return New chromosome string
    */
    std::string generateChromosomeString();
    /*! Mutates selected chromosome
     * \brief Mutates selected chromosome
     * \param Reference to the selected chromosome
    */
    void mutateChromosome(Chromosome &chromosome);
    /*! Mutates all chromosome in the currentGeneration_ vector
     * \brief Mutates all chromosome in the currentGeneration_ vector
    */
    void mutateCurrentGeneration();
    /*! Populates currentGeneration_ vector via crossover of the selected chromosomes
     * \brief Populates currentGeneration_ vector via crossover of the selected chromosomes
    */
    void populateNewGeneration();
    /*! Calculates fitness function output for the givent travelled distance
     * \brief Calculates fitness funtction output
     * \param Distance travelled by the evaluated chromosome
     * \return Output of the fitness function
    */
    float calculateFitness(float distanceTravelled);

};

#endif // EVOLUTIONCONTROLLER_H
