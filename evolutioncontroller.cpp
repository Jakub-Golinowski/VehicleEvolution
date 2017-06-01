#include "evolutioncontroller.h"
#include <random>

const float EvolutionController::CAR_INITIAL_X_POSITION = 0.0;
const float EvolutionController::CAR_INITIAL_Y_POSITION = 15.0;
const unsigned long EvolutionController::NUMBER_OF_WORLD_ITERATIONS = 10000;
const unsigned long EvolutionController::GENERATION_SIZE = 10;
const unsigned long EvolutionController::NUMBER_OF_SELECTED_CHROMOSOMES = 2;
const float EvolutionController::CAR_MAXIMUM_ABSOLUTE_COORDINATE_VALUE = 10.0f;
const float EvolutionController::WHEEL_MAXIMAL_RADIUS = 7.0f;
const float EvolutionController::WHEEL_MINIMAL_RADIUS = 0.5f;
const float EvolutionController::MUTATION_DECISION_THRESHOLD = 0.01f;

EvolutionController::EvolutionController(): controller_(nullptr), model_(nullptr), view_(nullptr)
{
    // Set seed of randomNumberGenerator to true random number
    randomNumberGenerator_.seed(std::random_device()());
}


EvolutionController::~EvolutionController()
{
    delete model_;
    delete controller_;
    delete view_;
}

void EvolutionController::addChromosome(Chromosome newChromosome, float Fitness)
{
    currentGeneration_.push_back(ChromosomeAndFitness(newChromosome, Fitness));
}

void EvolutionController::evolution(unsigned long numberOfGenerations)
{
    initializeRandomFirstGeneration();
    for(unsigned int i=0; i<numberOfGenerations;++i){
        evaluateCurrentGeneration();
        selectionFromCurrentGeneration();
        // Create next generation. TODO: Move to another function
        currentGeneration_.clear();
        currentGeneration_ = selectedFromCurrentGeneration;
        std::uniform_int_distribution<unsigned int> crossoverPointDistribution(0, Chromosome::NUMBER_OF_TOKENS-1);
        while(currentGeneration_.size() < GENERATION_SIZE)
        {
            unsigned int firstCrossoverPoint = crossoverPointDistribution(randomNumberGenerator_);
            unsigned int secondCrossoverPoint = crossoverPointDistribution(randomNumberGenerator_);
            std::array<Chromosome, 2> newChromosomes = crossoverParentChromosomes(selectedFromCurrentGeneration.at(0).first, selectedFromCurrentGeneration.at(1).first, firstCrossoverPoint, secondCrossoverPoint);
            addChromosome(newChromosomes[0]);
            if(currentGeneration_.size() < GENERATION_SIZE)
            {
                addChromosome(newChromosomes[1]);
            }
        }
        mutateCurrentGeneration();
    }
    evaluateCurrentGeneration();
}

void EvolutionController::evaluateCurrentGeneration()
{
    for(unsigned int i=0; i< currentGeneration_.size(); ++i){
        evaluateChromosome(i);
    }

    // Functor for comparing ChromosomeAndFitness
    struct {
        bool operator ()(const ChromosomeAndFitness &firstPair, const ChromosomeAndFitness &secondPair) const
        {
            return firstPair.second < secondPair.second;
        }
    }compareFitness;

    std::sort(currentGeneration_.begin(), currentGeneration_.end(), compareFitness);
}



void EvolutionController::initializeRandomFirstGeneration()
{
    currentGeneration_.clear();
    for(unsigned int numberOfChromosomes=0; numberOfChromosomes<GENERATION_SIZE; ++numberOfChromosomes){
        addChromosome(Chromosome(generateChromosomeString()));
    }
}

std::string EvolutionController::generateChromosomeString(){

    std::uniform_real_distribution<float> coordinatesDistribution(-CAR_MAXIMUM_ABSOLUTE_COORDINATE_VALUE, CAR_MAXIMUM_ABSOLUTE_COORDINATE_VALUE);
    std::uniform_real_distribution<float> wheelRadiusDistribution(WHEEL_MINIMAL_RADIUS, WHEEL_MAXIMAL_RADIUS);
    std::uniform_int_distribution<unsigned int> wheelVertexNumberDistribution(0, Chromosome::NUMBER_OF_VERTICES-1);

    std::string newChromosomeString = "";
    //Generate random vertices' coordinates
    for(int numberOfCoordinate=0; numberOfCoordinate<2*Chromosome::NUMBER_OF_VERTICES; ++numberOfCoordinate){
        float newCoordinate = coordinatesDistribution(randomNumberGenerator_);
        newChromosomeString +=std::to_string(newCoordinate);
        //Add separator
        newChromosomeString += Chromosome::CHROMOSOME_STRING_SEPARATOR;
    }
    //Generate random wheels
    for(int numberOfWheels=0; numberOfWheels < Chromosome::NUMBER_OF_WHEELS; ++numberOfWheels){
        float newWheelRadius = wheelRadiusDistribution(randomNumberGenerator_);
        unsigned int newWheelVertexNumber = wheelVertexNumberDistribution(randomNumberGenerator_);
        newChromosomeString += std::to_string(newWheelRadius);
        //Add separator
        newChromosomeString += Chromosome::CHROMOSOME_STRING_SEPARATOR;
        newChromosomeString += std::to_string(newWheelVertexNumber);
        //Add separator
        newChromosomeString += Chromosome::CHROMOSOME_STRING_SEPARATOR;
    }
    return newChromosomeString;
}

void EvolutionController::mutateChromosome(Chromosome &chromosome)
{
    std::string newChromosomeString = "";
    std::uniform_real_distribution<float> tokenMutationDistribution(0.0, 1.0);
    std::uniform_real_distribution<float> coordinatesDistribution(-CAR_MAXIMUM_ABSOLUTE_COORDINATE_VALUE, CAR_MAXIMUM_ABSOLUTE_COORDINATE_VALUE);
    std::uniform_real_distribution<float> wheelRadiusDistribution(WHEEL_MINIMAL_RADIUS, WHEEL_MAXIMAL_RADIUS);
    std::uniform_int_distribution<unsigned int> wheelVertexNumberDistribution(0, Chromosome::NUMBER_OF_VERTICES-1);

    // Mutate vertices
    for( b2Vec2 vertex : chromosome.GetVerticesArray()){
        // Decide wether to mutate x coordinate
        bool mutationDecision = tokenMutationDistribution(randomNumberGenerator_) < MUTATION_DECISION_THRESHOLD;
        if( mutationDecision )
        {
            float newCoordinate = coordinatesDistribution(randomNumberGenerator_);
            newChromosomeString += std::to_string(newCoordinate);
        }
        else
        {
            newChromosomeString += std::to_string(vertex.x);
        }
        newChromosomeString += Chromosome::CHROMOSOME_STRING_SEPARATOR;
        // Do the same for y coordinate
        mutationDecision  = tokenMutationDistribution(randomNumberGenerator_) < MUTATION_DECISION_THRESHOLD;
        if( mutationDecision )
        {
            float newCoordinate = coordinatesDistribution(randomNumberGenerator_);
            newChromosomeString += std::to_string(newCoordinate);
        }else
        {
            newChromosomeString += std::to_string(vertex.y);
        }
        newChromosomeString += Chromosome::CHROMOSOME_STRING_SEPARATOR;
    }
    // Mutate wheels
    for( Wheel wheel : chromosome.getWheels()){
        // Decide wether to mutate wheel radius
        bool mutationDecision = tokenMutationDistribution(randomNumberGenerator_) < MUTATION_DECISION_THRESHOLD;
        if( mutationDecision )
        {
            float newWheelRadius = wheelRadiusDistribution(randomNumberGenerator_);
            newChromosomeString += std::to_string(newWheelRadius);
        }
        else
        {
            newChromosomeString += std::to_string(wheel.wheelRadius_);
        }
        newChromosomeString += Chromosome::CHROMOSOME_STRING_SEPARATOR;
        //Decide wether to mutate wheel vertex number
        mutationDecision = tokenMutationDistribution(randomNumberGenerator_) < MUTATION_DECISION_THRESHOLD;
        if( mutationDecision )
        {
            unsigned int newWheelVertexIndex = wheelVertexNumberDistribution(randomNumberGenerator_);
            newChromosomeString += std::to_string(newWheelVertexIndex);
        }
        else
        {
            newChromosomeString += std::to_string(wheel.vertexIndex_);
        }
        newChromosomeString += Chromosome::CHROMOSOME_STRING_SEPARATOR;
    }
}

void EvolutionController::mutateCurrentGeneration()
{
    for(ChromosomeAndFitness chromosomeAndFitness : currentGeneration_)
    {
        //mutateChromosome();
    }
}

void EvolutionController::selectionFromCurrentGeneration()
{
    selectedFromCurrentGeneration.clear();
    for(unsigned int i=0; i < NUMBER_OF_SELECTED_CHROMOSOMES; ++i){
        float fitnessSum = 0.0f;
        for( ChromosomeAndFitness chromosomeAndFitness : currentGeneration_){
            fitnessSum += chromosomeAndFitness.second;
        }
        std::uniform_real_distribution<float> fitnessDistribution(0.0, fitnessSum);
        float value = fitnessDistribution(randomNumberGenerator_);
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
    Model model;
    model.addTrack();
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

    model_ = new Model;
    model_->addTrack();
    model_->addCarFromChromosome(chromosome, CAR_INITIAL_X_POSITION, CAR_INITIAL_Y_POSITION);
    view_ = new View(model_);
    view_->setGeometry(0,0,800,600);
    //window->SetView(model, drawer);
    //view->show();
    controller_ = new Controller(model_, view_);
    controller_->startSimulation(5);

}

float EvolutionController::calculateFitness(float distanceTravelled)
{
    // TODO: implement fitness function
    if(distanceTravelled < 0.0f) distanceTravelled = 0.0f;
    return std::pow(distanceTravelled,2.0);
}

std::array<Chromosome, 2> EvolutionController::crossoverParentChromosomes(const Chromosome &firstParent, const Chromosome &secondParent, unsigned int firstCrossoverPoint, unsigned int secondCrossoverPoint)
{
    std::string firstChild = "";
    std::string secondChild = "";

    // If needed, switch values of first and second point, so the first point is always smaller
    if(secondCrossoverPoint < firstCrossoverPoint){
        unsigned int tempValue = firstCrossoverPoint;
        firstCrossoverPoint = secondCrossoverPoint;
        secondCrossoverPoint = tempValue;
    }

    for(unsigned int i = 0; i < Chromosome::NUMBER_OF_TOKENS; ++i)
    {
        if( i >= firstCrossoverPoint && i <= secondCrossoverPoint){
            firstChild += secondParent.chromosomeTokens_.at(i);
            secondChild += firstParent.chromosomeTokens_.at(i);
        }else{
            firstChild += firstParent.chromosomeTokens_.at(i);
            secondChild += secondParent.chromosomeTokens_.at(i);
        }
        // Add separators
        firstChild += Chromosome::CHROMOSOME_STRING_SEPARATOR;
        secondChild += Chromosome::CHROMOSOME_STRING_SEPARATOR;
    }
    return std::array<Chromosome,2>{Chromosome(firstChild), Chromosome(secondChild)};
}

void EvolutionController::saveCurrentGenerationToFile()
{
    std::time_t currentTime = std::time(NULL);
    char currentTimeString[100];

    if (std::strftime(currentTimeString, sizeof(currentTimeString), "%A %c", std::localtime(&currentTime))) {

        std::string currentGenerationFileNameString = std::string(currentTimeString) + ".txt";
        std::ofstream outfile (currentGenerationFileNameString);

        for (ChromosomeAndFitness chromosomeAndFitness: currentGeneration_)
        {
            outfile << chromosomeAndFitness.first.chromosomeString_ << "; " << chromosomeAndFitness.second << std::endl;
        }

        outfile.close();
   }

}

void EvolutionController::ReadGenerationFromFile()
{
    std::ifstream inFile ("wtorek-wto-30-maj-2017-235246.txt");
    currentGeneration_.clear();

    std::string line;
    while (std::getline(inFile, line))
    {
        std::regex reg("(.*) ; (.*)");
        std::smatch what;
        if(regex_match(line,what,reg))
        {
            Chromosome chromosome = Chromosome(what[1]);
            float fitness = boost::lexical_cast<float>(what[2]);
            currentGeneration_.push_back(ChromosomeAndFitness(chromosome,fitness));
        }


    }


}

