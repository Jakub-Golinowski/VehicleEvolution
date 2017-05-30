#include "evolutioncontroller.h"
#include <random>

const float EvolutionController::CAR_INITIAL_X_POSITION = 0.0;
const float EvolutionController::CAR_INITIAL_Y_POSITION = 15.0;
const unsigned long EvolutionController::NUMBER_OF_WORLD_ITERATIONS = 50000;
const unsigned long EvolutionController::GENERATION_SIZE = 10;
const unsigned long EvolutionController::NUMBER_OF_SELECTED_CHROMOSOMES = 1;
const float EvolutionController::CAR_MAXIMUM_ABSOLUTE_COORDINATE_VALUE = 10.0f;
const float EvolutionController::WHEEL_MAXIMAL_RADIUS = 7.0f;
const float EvolutionController::WHEEL_MINIMAL_RADIUS = 0.5f;

EvolutionController::EvolutionController(): controller(nullptr), model(nullptr), view(nullptr), drawer(nullptr)
{

}


EvolutionController::~EvolutionController()
{
    delete model;
    delete controller;
    delete view;
    delete drawer;
}

void EvolutionController::addChromosome(Chromosome newChromosome)
{
    // Add new chromosome with 0.0 fitness
    currentGeneration_.push_back(ChromosomeAndFitness(newChromosome, 0.0));
}

void EvolutionController::evaluateCurrentGeneration()
{
    for(int i=0; i< currentGeneration_.size(); ++i){
        evaluateChromosome(i);
    }
}

void EvolutionController::addTrackToModel(Model &model)
{
    //TODO : Add proper track
    b2Body* testBody = model.addRectBody(-80.0f,0.0f,b2_staticBody, 0.0f);
    b2Vec2 points[100];
    float x = 0.0;
    for(int i=0; i<100; ++i){
        points[i].x = x;
        x += 50.0;
        float y = static_cast<float>(rand() % 20 - 9);
        points[i].y = y;
    }
    model.addGrounChainShape(testBody, points, 100, 1.0f, 0.3f, 0.3f, 0);

}

void EvolutionController::initializeRandomFirstGeneration()
{
    currentGeneration_.clear();
    //Create new generator with true random seed
    std::default_random_engine generator;
    generator.seed(std::random_device()());
    for(unsigned int numberOfChromosomes=0; numberOfChromosomes<GENERATION_SIZE; ++numberOfChromosomes){
        addChromosome(Chromosome(generateChromosomeString(generator)));
    }
}

std::string EvolutionController::generateChromosomeString(std::default_random_engine &generator){

    std::uniform_real_distribution<float> coordinatesDistribution(-CAR_MAXIMUM_ABSOLUTE_COORDINATE_VALUE, CAR_MAXIMUM_ABSOLUTE_COORDINATE_VALUE);
    std::uniform_real_distribution<float> wheelRadiusDistribution(WHEEL_MINIMAL_RADIUS, WHEEL_MAXIMAL_RADIUS);
    std::uniform_int_distribution<unsigned int> wheelVertexNumberDistribution(0, Chromosome::NUMBER_OF_VERTICES-1);

    std::string newChromosomeString = "";
    //Generate random vertices' coordinates
    for(int numberOfCoordinate=0; numberOfCoordinate<2*Chromosome::NUMBER_OF_VERTICES; ++numberOfCoordinate){
        float newCoordinate = coordinatesDistribution(generator);
        newChromosomeString +=std::to_string(newCoordinate);
        //Add separator
        newChromosomeString += " ";
    }
    //Generate random wheels
    for(int numberOfWheels=0; numberOfWheels < Chromosome::NUMBER_OF_WHEELS; ++numberOfWheels){
        float newWheelRadius = wheelRadiusDistribution(generator);
        unsigned int newWheelVertexNumber = wheelVertexNumberDistribution(generator);
        newChromosomeString += std::to_string(newWheelRadius);
        //Add separator
        newChromosomeString += " ";
        newChromosomeString += std::to_string(newWheelVertexNumber);
        //Add separator
        newChromosomeString += " ";
    }
    return newChromosomeString;
}

void EvolutionController::selectionFromCurrentGeneration()
{
    selectedFromCurrentGeneration.clear();
    //Create new generator with true random seed
    std::default_random_engine generator;
    generator.seed(std::random_device()());

    for(unsigned int i=0; i < NUMBER_OF_SELECTED_CHROMOSOMES; ++i){
        float fitnessSum = 0.0f;
        for( ChromosomeAndFitness chromosomeAndFitness : currentGeneration_){
            fitnessSum += chromosomeAndFitness.second;
        }
        std::uniform_real_distribution<float> fitnessDistribution(0.0, fitnessSum);
        float value = fitnessDistribution(generator);
        std::vector<ChromosomeAndFitness>::iterator it;
        for(it = currentGeneration_.begin(); it != currentGeneration_.end(); ++it){
            value -= (*it).second;
            if(value <=0.0f) {
                break;
            }
        }
        selectedFromCurrentGeneration.push_back(*it);
        currentGeneration_.erase(it);
    }

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

void EvolutionController::visualizeChromosomeFromCurrentGeneration(unsigned int chromosomeIndex)
{
    visualizeChromosome(currentGeneration_.at(chromosomeIndex).first);
}

void EvolutionController::visualizeSelectedChromosome(unsigned int chromosomeIndex)
{
    visualizeChromosome(selectedFromCurrentGeneration.at(chromosomeIndex).first);
}

void EvolutionController::visualizeChromosome(Chromosome chromosome)
{
    drawer = new QB2Draw(QRect(0,0,800,600));
    drawer->SetFlags(0x0001);
    model = new Model(0.0f,-10.f, drawer);
    addTrackToModel(*model);
    model->addCarFromChromosome(chromosome, CAR_INITIAL_X_POSITION, CAR_INITIAL_Y_POSITION);
    view = new View(model, drawer);
    view->setGeometry(0,0,800,600);
    view->show();
    controller = new Controller(model, view);
    controller->startSimulation(5);

}

float EvolutionController::calculateFitness(float distanceTravelled)
{
    // TODO: implement fitness function
    if(distanceTravelled < 0.0f) distanceTravelled = 0.0f;
    return std::pow(distanceTravelled,2.0);
}

