
#include <QApplication>

#include <fstream>
#include <iostream>
#include <Box2D/Box2D.h>
#include "controller.h"
#include "model.h"
#include "view.h"
#include "chromosome.h"
#include"evolutioncontroller.h"



using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    std::string chromosomeString = "-20.0 5.0 -15.0 10.0 18.0 20.0 30.0 10.0 40.0 -8.0 25.0 -15.0 -10.0 -20.0 -30.0 -10.0 15.0 5 15.0 6";
    Chromosome chromosome(chromosomeString);



    EvolutionController evolutionController;
    evolutionController.addChromosome(chromosome);
   // evolutionController.evaluateChromosome(0);
    evolutionController.visualizeChromosome(0);

    return a.exec();


}
