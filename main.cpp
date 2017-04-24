
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

    b2Body* testBody = model.addRectBody(0.0,-50.0f,b2_staticBody, 0.0f);
    model.addRectFixture(testBody, 400.0f, 50.0f, 1.0f, 0.3f, 0.3f, 0);

    b2Body* carBody = model.addRectBody(0, 30.0, b2_dynamicBody, 0.0);
    model.addRectFixture(carBody, 40, 20, 2.0, 0.5, 0.99, -1);

    b2Body* leftWheelBody = model.addWheelBody(-40.0, 10.0,20);
    model.addWheelFixture(leftWheelBody,10.0, 1.0, 0.3, 0.3, -1);

    b2Body* rightWheelBody = model.addWheelBody(40.0, 10.0,20);
    model.addWheelFixture(rightWheelBody,10.0, 1.0, 0.3, 0.3, -1);

    b2RevoluteJointDef leftjointDef;
    leftjointDef.Initialize(carBody, leftWheelBody, leftWheelBody->GetWorldCenter());

    model.addRevoluteJoint(&leftjointDef);

    b2RevoluteJointDef rightjointDef;
    rightjointDef.Initialize(carBody, rightWheelBody, rightWheelBody->GetWorldCenter());

    model.addRevoluteJoint(&rightjointDef);




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
