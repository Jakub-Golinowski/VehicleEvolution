
#include <QApplication>


#include <Box2D/Box2D.h>
#include "controller.h"
#include "model.h"
#include "view.h"
#include "chromosome.h"



using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QB2Draw drawer(QRect(0,0,800,600));
    drawer.SetFlags(0x0001);

    Model model(0.0f,-10.f, &drawer);

    View view(&model, &drawer);
    view.setGeometry(0,0,800,600);
    view.show();

    Controller controller(&model, &view);

    //Add Ground
    b2Body* testBody = model.addRectBody(0.0,-50.0f,b2_staticBody, 0.0f);
    model.addRectFixture(testBody, 400.0f, 50.0f, 1.0f, 0.3f, 0.3f, 0);

    //Add Car
    model.addSimpleCarBody(-300.0,80.0,100,40, 30,50);

    //std::string chromosomeString = "5.0 5.1 10.0 10.1 -5.0 -5.1 -10.0 -10.1 5.0 -5.1 10.0 -10.1 -5.0 5.1 -10.0 10.1 4.0 3 3.0 2";
    //std::string chromosomeString = "-9.3448072351495 -69.046675519729 -37.668437525234 52.1939666854 63.3920628292 -72.161740366915 -88.799100536416 95.546979084756 36.313522226479 -2.8598957690793 79.958541175922 -28.646546713395 45.361071864414 -67.887854090023 37.171789557039 -13.937910841696 4.0 3 3.0 2";
    std::string chromosomeString = "-20.0 5.0 -15.0 10.0 18.0 20.0 30.0 10.0 40.0 -8.0 25.0 -15.0 -10.0 -20.0 -30.0 -10.0 15.0 5 15.0 6";
    Chromosome chromosome(chromosomeString);

    model.addCarFromChromosome(chromosome, 0.0, 100);

    /*
    //Add Obstacles
    testBody = model.addBody(0.0f,0.0f,b2_staticBody, 0.0f);
    model.addCircleFixture(testBody, 0.0f,0.0f,40.0f,1.0f,0.3f,0.3f);

    testBody = model.addBody(100.0f,-20.0f,b2_staticBody, 0.0f);
    model.addCircleFixture(testBody, 0.0f,0.0f,40.0f,1.0f,0.3f,0.3f);

    testBody = model.addBody(-100.0f,-20.0f,b2_staticBody, 0.0f);
    model.addCircleFixture(testBody, 0.0f,0.0f,40.0f,1.0f,0.3f,0.3f);*/

    // b2World will be simulated and drawn every 10 ms
    controller.startSimulation(5);

    return a.exec();


}
