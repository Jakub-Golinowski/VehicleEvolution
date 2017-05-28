#include "evolutioncontroller.h"

const float EvolutionController::CAR_INITIAL_X_POSITION = 0.0;
const float EvolutionController::CAR_INITIAL_Y_POSITION = 10.0;
const unsigned long EvolutionController::NUMBER_OF_WORLD_ITERATIONS = 100000;

EvolutionController::EvolutionController()
{

}

void EvolutionController::addChromosome(Chromosome newChromosome)
{
    // Add new chromosome with 0.0 fitness
    currentGeneration_.push_back(ChromosomeAndFitness(newChromosome, 0.0));
}

void EvolutionController::addTrackToModel(Model &model)
{
    //TODO : Add proper track
    b2Body* testBody = model.addRectBody(0.0,-50.0f,b2_staticBody, 0.0f);
    model.addRectFixture(testBody, 400.0f, 50.0f, 1.0f, 0.3f, 0.3f, 0);

}

void EvolutionController::evaluateChromosome(unsigned int chromosomeIndex)
{
    Model model(0.0f,-10.f);
    addTrackToModel(model);
    b2Body* evaluatedCar = model.addCarFromChromosome(currentGeneration_.at(chromosomeIndex).first, CAR_INITIAL_X_POSITION, CAR_INITIAL_Y_POSITION);

    for(unsigned int i=0; i<NUMBER_OF_WORLD_ITERATIONS; ++i){
        model.simulate();
    }

    b2Vec2 finalPosition = evaluatedCar->GetPosition();
    float distanceTravelled = finalPosition.x - CAR_INITIAL_X_POSITION;
    currentGeneration_.at(chromosomeIndex).second = calculateFitness(distanceTravelled);
}

float EvolutionController::calculateFitness(float distanceTravelled)
{
    // TODO: implement fitness function
    return distanceTravelled;
}

