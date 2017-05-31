
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

//    //std::string chromosomeString = "-20.0 5.0 -15.0 10.0 18.0 20.0 30.0 10.0 40.0 -8.0 25.0 -15.0 -10.0 -20.0 -30.0 -10.0 15.0 5 15.0 6";
//    std::string chromosomeString = "-4.413066 9.602226 4.642906 -6.671811 6.875719 0.210768 2.377907 5.476480 3.196440 2.563803 9.849648 3.031129 4.178925 -4.816052 -3.388288 -6.950301 5.794323 3 0.915325 7";
//    Chromosome chromosome(chromosomeString);



    EvolutionController evolutionController;
  //  evolutionController.ReadGenerationFromFile();
    evolutionController.initializeRandomFirstGeneration();
    evolutionController.evaluateCurrentGeneration();
    evolutionController.selectionFromCurrentGeneration();
    evolutionController.visualizeSelectedChromosome(0);
//    evolutionController.visualizeChromosomeFromCurrentGeneration(2);
    //evolutionController.saveCurrentGenerationToFile();



    return a.exec();


}
