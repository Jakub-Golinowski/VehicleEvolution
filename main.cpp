#include <QApplication>

#include <fstream>
#include <iostream>
#include <Box2D/Box2D.h>
#include "controller.h"
#include "model.h"
#include "view.h"
#include "chromosome.h"
#include "evolutioncontroller.h"

#include "window.h"

using namespace std;

/*! \mainpage Vehicle Evolution Documentation Main Page
 *
 * \section intro_sec Introduction
 *
 * Vehivle Evolution is a C++ application using QT and Box2D libraries to achieve two-dimesnional car evolution with visualisation and graphical user interface.
 *
 * \section install_sec Application
 *
 * After user starts the application he/she generates new random population of cars. After specifying the number of generations user starts evolution process. When evolution process is finished user can all the cars from the latest generation by changing the car index in the graphical user interface.
 */

int main(int argc, char *argv[])
{
    //Q_INIT_RESOURCE(basicdrawing);

    QApplication a(argc, argv);

    Window window;
    window.show();

//    //std::string chromosomeString = "-20.0 5.0 -15.0 10.0 18.0 20.0 30.0 10.0 40.0 -8.0 25.0 -15.0 -10.0 -20.0 -30.0 -10.0 15.0 5 15.0 6";
//    std::string chromosomeString = "-4.413066 9.602226 4.642906 -6.671811 6.875719 0.210768 2.377907 5.476480 3.196440 2.563803 9.849648 3.031129 4.178925 -4.816052 -3.388288 -6.950301 5.794323 3 0.915325 7";
//    Chromosome chromosome(chromosomeString);



  //  EvolutionController evolutionController;
  //  evolutionController.ReadGenerationFromFile();
   // evolutionController.evolution(10);
    //evolutionController.initializeRandomFirstGeneration();
    //evolutionController.visualizeChromosomeFromCurrentGeneration(evolutionController.currentGeneration_.size()-1);
    //evolutionController.saveCurrentGenerationToFile();



    return a.exec();


}
