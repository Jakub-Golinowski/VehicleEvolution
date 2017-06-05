#include <QApplication>
#include "window.h"


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
    QApplication a(argc, argv);

    Window window;
    window.show();

    return a.exec();


}
