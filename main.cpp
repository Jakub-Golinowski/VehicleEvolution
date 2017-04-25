
#include <QApplication>


#include <Box2D/Box2D.h>
#include "controller.h"
#include "model.h"
#include "view.h"



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

    //Add Obstacles
   testBody = model.addBody(0.0f,0.0f,b2_staticBody, 0.0f);
    model.addCircleFixture(testBody, 0.0f,0.0f,40.0f,1.0f,0.3f,0.3f);

    testBody = model.addBody(100.0f,-20.0f,b2_staticBody, 0.0f);
    model.addCircleFixture(testBody, 0.0f,0.0f,40.0f,1.0f,0.3f,0.3f);

    testBody = model.addBody(-100.0f,-20.0f,b2_staticBody, 0.0f);
    model.addCircleFixture(testBody, 0.0f,0.0f,40.0f,1.0f,0.3f,0.3f);

    // b2World will be simulated and drawn every 10 ms
    controller.startSimulation(5);


    return a.exec();


}
