
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

    // Add some circles to the model
    /*b2Body * testBody = model.addWheelBody(10.0f,10.0f, 5.0f);
    model.addCircleFixture(testBody, 0.0f,0.0f,20.0f,1.0f,0.3f,0.3f);*/

    model.addSimpleCarBody(100.0, 100.0, 100.0, 30.0, 5.0);

    b2Body* testBody = model.addRectBody(-400.0f,-100.0f,b2_staticBody, 0.0f);
    model.addRectFixture(testBody, 0.0f, 0.0f, 800.0f, 100.0f, 1.0f, 0.3f, 0.3f);

   /* testBody = model.addBody(0.0f,-120.0f,b2_staticBody, 0.0f);
    model.addCircleFixture(testBody, 0.0f,0.0f,80.0f,1.0f,0.3f,0.3f);

    testBody = model.addBody(80.0f,-120.0f,b2_staticBody, 0.0f);
    model.addCircleFixture(testBody, 0.0f,0.0f,80.0f,1.0f,0.3f,0.3f);

    testBody = model.addBody(-80.0f,-120.0f,b2_staticBody, 0.0f);
    model.addCircleFixture(testBody, 0.0f,0.0f,80.0f,1.0f,0.3f,0.3f);*/

    // b2World will be simulated and drawn every 10 ms
    controller.startSimulation(10);


    return a.exec();


}
