
#include <QApplication>

#include <fstream>
#include <iostream>
#include <Box2D/Box2D.h>
#include "controller.h"
#include "model.h"
#include "view.h"
#include "chromosome.h"
#include "evolutioncontroller.h"



using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //std::string chromosomeString = "-20.0 5.0 -15.0 10.0 18.0 20.0 30.0 10.0 40.0 -8.0 25.0 -15.0 -10.0 -20.0 -30.0 -10.0 15.0 5 15.0 6";
    std::string chromosomeString = "-4.0 1.0 -3.0 2.0 3.6 5.0 6.0 2.0 8.0 -1.6 5.0 -3.0 -2.0 -4.0 -6.0 -2.0 3.0 5 3.0 6";
    Chromosome chromosome(chromosomeString);



    EvolutionController evolutionController;
    evolutionController.initializeRandomFirstGeneration();
   // evolutionController.evaluateChromosome(0);
    evolutionController.visualizeChromosome(0);
    evolutionController.visualizeChromosome(1);
    evolutionController.visualizeChromosome(2);

    return a.exec();


}
